/* adapter_bufmanager.c
 *
 * Buffer Manager intended for EIP-130 tokens.
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/c_adapter_bufmanager.h>   // ADAPTER_BUFMAN_*

#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_types.h>           // DMAResource_Handle_t
                                    // DMAResource_Properties_t
                                    // DMAResource_AddrPair_t
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_buf.h>             // DMAResource_Alloc, DMAResource_Release
                                    // DMAResource_CheckAndRegister
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_addr.h>            // DMAResource_Translate
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_rw.h>             // DMAResource_PreDMA, DMAResource_PostDMA
#ifdef MODULE
#include <linux/uaccess.h>          // copy_to_user, copy_from_user
#endif

#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_sleep.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#ifndef BUFMANAGER_ADMIN_ENTRIES
#define BUFMANAGER_ADMIN_ENTRIES    12U
#endif


/*----------------------------------------------------------------------------
 * BufManager_AdminEntry_t
 * BufManager adminstration entry
 */
typedef struct
{
    DMAResource_Handle_t BufferHandle;  // Buffer handle
    uint64_t BufferAddress;             // Physic buffer address
    void * Buffer_p;                    // Host pointer to buffer
    size_t BufferSize;                  // Actual buffer size
    bool fBounced;                      // Bounce buffer indication
    bool fFromUserSpace;                // Data_p is from User Space indication
    BufManager_BufferType_t Type;       // Buffer type: NOT_USED, IN, OUT, INOUT
    union
    {
        const void * c_p;
        void * n_p;
    } Data;                             // Caller data buffer pointer
    size_t DataSize;                    // Caller data buffer size
    void * UserData_p;                  // Caller user data
} BufManager_AdminEntry_t;


/*----------------------------------------------------------------------------
 * Local variables
 */
static bool gl_BufManager_InitDone = false;
static BufManager_AdminEntry_t gl_BufManager_Admin[BUFMANAGER_ADMIN_ENTRIES];
static BufManager_CB_SizeAlignment_t gl_BufManager_SizeAlignment = NULL;
static BufManager_CB_CheckClear_t gl_BufManager_CheckClear = NULL;
static BufManager_CB_CheckReady_t gl_BufManager_CheckReady = NULL;


/*----------------------------------------------------------------------------
 * BufManagerLocal_GetEntry
 */
static BufManager_AdminEntry_t *
BufManagerLocal_GetEntry(
        uint64_t BufferAddress,
        bool fOutputBuffer)
{
    BufManager_AdminEntry_t * Entry_p = gl_BufManager_Admin;
    bool IsBufferFound = false;
    uint32_t i;

    if (!gl_BufManager_InitDone)
    {
        // Initialize the buffer manager administration
        (void)memset(Entry_p, 0, (BUFMANAGER_ADMIN_ENTRIES * sizeof(BufManager_AdminEntry_t)));
        gl_BufManager_InitDone = true;
    }

    // Search for the requested buffer
    for (i = 0U; i < BUFMANAGER_ADMIN_ENTRIES; i++)
    {
        if (Entry_p->BufferAddress == BufferAddress)
        {
            if (!fOutputBuffer ||
                (Entry_p->Type == BUFMANAGER_BUFFERTYPE_OUT) ||
                (Entry_p->Type == BUFMANAGER_BUFFERTYPE_INOUT))
            {
                IsBufferFound = true;
                break;
            }
        }
        Entry_p++;
    }

    if (IsBufferFound == false)
    {
        Entry_p = (BufManager_AdminEntry_t *)NULL;
    }

    return Entry_p;
}


/*----------------------------------------------------------------------------
 * BufManager_Alloc
 */
static uint64_t
BufManagerLocal_AllocBuffer(
        bool fFromUserSpace,
        bool fBounce,
        BufManager_BufferType_t Type,
        size_t BufferSize,
        const void * const Data_p,
        size_t DataSize,
        void * UserData_p)
{
    uint64_t BufferAddress = 0;
    BufManager_AdminEntry_t *Entry_p = NULL;

    switch (Type)
    {
    case BUFMANAGER_BUFFERTYPE_IN:
    case BUFMANAGER_BUFFERTYPE_OUT:
    case BUFMANAGER_BUFFERTYPE_INOUT:
        Entry_p = BufManagerLocal_GetEntry(0, false);
        break;
    default:
        /* MISRA - Intentially empty */
        break;
    }
    if (Entry_p != NULL)
    {
        DMAResource_Properties_t Props;
        DMAResource_AddrPair_t AddrPair;
        bool FunctionStatus = true;

        // Found a free entry
        (void)memset(&Props, 0, sizeof(Props));

        Entry_p->Type = Type;
        Entry_p->fFromUserSpace = fFromUserSpace;
        Entry_p->Data.c_p = Data_p;
        Entry_p->DataSize = DataSize;
        Entry_p->UserData_p = UserData_p;

        // Determine buffer size
        Props.Alignment = 1;
        Props.Size = (uint32_t)((BufferSize + 3U) & (~3U));
        if ((gl_BufManager_SizeAlignment != NULL) &&
            ((Type == BUFMANAGER_BUFFERTYPE_OUT) ||
             (Type == BUFMANAGER_BUFFERTYPE_INOUT)))
        {
            Props.Size = (uint32_t)gl_BufManager_SizeAlignment(Props.Size);
        }
        Entry_p->BufferSize = Props.Size;

        AddrPair.Address_p = Entry_p->Data.n_p;
        AddrPair.Domain = (uint32_t)DMARES_DOMAIN_HOST;

        if (!fFromUserSpace && !fBounce &&
            (Entry_p->BufferSize == (uint32_t)((DataSize + 3U) & (~3U))))
        {
            // Check if current buffer is usable
            if (DMAResource_CheckAndRegister(Props, AddrPair, 'k',
                                             &Entry_p->BufferHandle) == 0)
            {
                Entry_p->Buffer_p = AddrPair.Address_p;

#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
                DMAResource_SwapEndianness_Set(Entry_p->BufferHandle, true);
#endif
            }
        }

        if (Entry_p->Buffer_p == NULL)
        {
            Props.Alignment = 4;
            if (DMAResource_Alloc(Props, &AddrPair, &Entry_p->BufferHandle) < 0)
            {
                // Internal error
                FunctionStatus = false;
            }
            else
            {
                Entry_p->Buffer_p = AddrPair.Address_p;
                Entry_p->fBounced = true;

#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
                DMAResource_SwapEndianness_Set(Entry_p->BufferHandle, true);
#endif
            }
        }

        if (FunctionStatus)
        {
            // Translate address to get the physical address of the buffer
            if (DMAResource_Translate(Entry_p->BufferHandle,
                                      (uint32_t)DMARES_DOMAIN_BUS,
                                      &AddrPair) == 0)
            {
                Entry_p->BufferAddress = (uint64_t)(uintptr_t)AddrPair.Address_p;

                // If needed, clear/reset output ready check
                if ((gl_BufManager_CheckClear != NULL) &&
                    ((Type == BUFMANAGER_BUFFERTYPE_OUT) ||
                     (Type == BUFMANAGER_BUFFERTYPE_INOUT)))
                {
                    if(gl_BufManager_CheckClear(Entry_p->Buffer_p,
                                                Entry_p->BufferSize,
                                                Entry_p->UserData_p) < 0)
                    {
                        // Internal error
                        FunctionStatus = false;
                    }
                }

                if (FunctionStatus)
                {
                    // Copy the input data
                    if (Entry_p->fBounced &&
                        ((Type == BUFMANAGER_BUFFERTYPE_IN) ||
                         (Type == BUFMANAGER_BUFFERTYPE_INOUT)))
                    {
#ifdef MODULE
                        if (fFromUserSpace)
                        {
                            if (copy_from_user(Entry_p->Buffer_p, Data_p, DataSize) != 0)
                            {
                                // Internal error
                                FunctionStatus = false;
                            }
                        }
                        else
#endif
                        {
                            (void)memcpy(Entry_p->Buffer_p, Data_p, DataSize);
                        }
                        if (DataSize < Entry_p->DataSize)
                        {
                            uint8_t * ptr = (uint8_t *)Entry_p->Buffer_p;
                            (void)memset(&ptr[DataSize], 0, (Entry_p->DataSize - DataSize));
                        }
                    }

#ifdef MODULE
                    if (FunctionStatus)
                    {
                        BufferAddress = Entry_p->BufferAddress;
                    }
#else
                    BufferAddress = Entry_p->BufferAddress;
#endif
                }
            }
        }

        if (BufferAddress == 0U)
        {
            if (Entry_p->BufferHandle != NULL)
            {
                // Release the buffer
                (void)DMAResource_Release(Entry_p->BufferHandle);
            }

            // Clear the administration entry
            (void)memset(Entry_p, 0, sizeof(BufManager_AdminEntry_t));
        }
    }
    return BufferAddress;
}


/*----------------------------------------------------------------------------
 * BufManager_GetInAddress
 */
int32_t
BufManager_Register(
        BufManager_CB_SizeAlignment_t SizeAlignment,
        BufManager_CB_CheckClear_t CheckClear,
        BufManager_CB_CheckReady_t CheckReady)
{
    gl_BufManager_SizeAlignment = SizeAlignment;
    gl_BufManager_CheckClear = CheckClear;
    gl_BufManager_CheckReady = CheckReady;
    return 0;
}


/*----------------------------------------------------------------------------
 * BufManager_GetInAddress
 */
uint64_t
BufManager_Map(
        bool fFromUserSpace,
        BufManager_BufferType_t Type,
        const void * const Data_p,
        size_t DataSize,
        void * UserData_p)
{
    uint64_t BufferAddress = 0;

    if (Data_p != NULL)
    {
        BufferAddress = BufManagerLocal_AllocBuffer(fFromUserSpace,
#ifdef ADAPTER_REMOVE_BOUNCEBUFFERS
                                                    false,
#else
                                                    true,
#endif
                                                    Type,
                                                    DataSize,
                                                    Data_p,
                                                    DataSize,
                                                    UserData_p);
        if (BufferAddress != 0U)
        {
            (void)BufManager_PreDmaAddress(BufferAddress);
        }
    }
    return BufferAddress;
}


/*----------------------------------------------------------------------------
 * BufManager_Alloc
 */
uint64_t
BufManager_Alloc(
        bool fFromUserSpace,
        BufManager_BufferType_t Type,
        size_t BufferSize,
        const void * const Data_p,
        size_t DataSize,
        void * UserData_p)
{
    return BufManagerLocal_AllocBuffer(fFromUserSpace,
                                       true,
                                       Type,
                                       BufferSize,
                                       Data_p,
                                       DataSize,
                                       UserData_p);
}


/*----------------------------------------------------------------------------
 * BufManager_GetInAddress
 */
int32_t
BufManager_Unmap(
        uint64_t BufferAddress,
        bool fOutputBuffer,
        bool fCopy,
        size_t ActualSize)
{
    int32_t rc = -1;

    if (BufferAddress != 0U)
    {
        BufManager_AdminEntry_t * const Entry_p = BufManagerLocal_GetEntry(BufferAddress, fOutputBuffer);
        if (Entry_p != NULL)
        {
            rc = 0;                    // Looks OK

            if (fCopy &&
                ((Entry_p->Type == BUFMANAGER_BUFFERTYPE_OUT) ||
                 (Entry_p->Type == BUFMANAGER_BUFFERTYPE_INOUT)))
            {
                DMAResource_PostDMA(Entry_p->BufferHandle, 0,
                                    (uint32_t)Entry_p->BufferSize);

#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
                if (DMAResource_SwapEndianness_Get(Entry_p->BufferHandle) == 1)
                {
                    uint8_t * p = Entry_p->Buffer_p;

                    p += Entry_p->BufferSize - sizeof(uint32_t);
                    DMAResource_Write32Array(Entry_p->BufferHandle,
                                             Entry_p->BufferSize / sizeof(uint32_t) - 1,
                                             1,
                                             (uint32_t*)p);
                }
#endif

                if (gl_BufManager_CheckReady != NULL)
                {
                    int32_t SkipSleep = ADAPTER_BUFMAN_POLLING_SKIP_FIRST_DELAYS;
                    int32_t LoopsLeft = ADAPTER_BUFMAN_POLLING_MAXLOOPS;

                    // Poll for TokenID available
                    while (rc == 0)
                    {
                        if (gl_BufManager_CheckReady(Entry_p->Buffer_p,
                                                     Entry_p->BufferSize,
                                                     Entry_p->UserData_p) == 0)
                        {
                            break; // buffer ready
                        }

                        if (SkipSleep > 0)
                        {
                            // First few rounds are without sleep
                            // this avoids sleeping unnecessarily for fast tokens
                            SkipSleep--;
                        }
                        else
                        {
                            // Sleep a bit
                            Adapter_SleepMS(ADAPTER_BUFMAN_POLLING_DELAY_MS);

                            LoopsLeft--;
                            if (LoopsLeft <= 0)
                            {
                                // Report internal error
                                rc = -3; // buffer not ready, timeout
                            }
                        }

                        DMAResource_PostDMA(Entry_p->BufferHandle, 0,
                                            (uint32_t)Entry_p->BufferSize);
#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
                        if (DMAResource_SwapEndianness_Get(Entry_p->BufferHandle) == 1)
                        {
                            uint8_t * p = Entry_p->Buffer_p;

                            p += Entry_p->BufferSize - sizeof(uint32_t);
                            DMAResource_Write32Array(Entry_p->BufferHandle,
                                                     Entry_p->BufferSize / sizeof(uint32_t) - 1,
                                                     1,
                                                     (uint32_t*)p);
                        }
#endif
                    }
                }

                if (rc == 0)
                {
                    size_t DataSize;

                    if (ActualSize == 0)
                    {
                        DataSize = Entry_p->DataSize;
                    }
                    else
                    {
                        DataSize = ActualSize;
                    }

#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
                    // Endianness conversion
                    if (DMAResource_SwapEndianness_Get(Entry_p->BufferHandle) == 1)
                    {
                        DMAResource_Write32Array(Entry_p->BufferHandle,
                                                 0,
                                                 Entry_p->BufferSize / sizeof(uint32_t) - 1,
                                                 (uint32_t*)Entry_p->Buffer_p);
                    }
#endif

                    // Copy output data
#ifdef MODULE
                    if (Entry_p->fFromUserSpace)
                    {
                        if (copy_to_user(Entry_p->Data.n_p,
                                         Entry_p->Buffer_p,
                                         DataSize) != 0)
                        {
                            // Report internal error
                            rc = -2;
                        }
                    }
                    else if (Entry_p->fBounced)
#else
                    if (Entry_p->fBounced)
#endif
                    {
                        (void)memcpy(Entry_p->Data.n_p,
                                     Entry_p->Buffer_p,
                                     DataSize);
                    } // buffer bounced
                } // buffer ready
            } // copy buffer

#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
            // Unswap the bytes in words of the input buffer to restore data
            if (!Entry_p->fBounced && (Entry_p->Type == BUFMANAGER_BUFFERTYPE_IN))
            {
                DMAResource_Write32Array(Entry_p->BufferHandle,
                                         0,
                                         Entry_p->BufferSize / 4,
                                         (uint32_t*)Entry_p->Buffer_p);
            }
#endif

            // Release buffer and clear administration entry
            (void)DMAResource_Release(Entry_p->BufferHandle);
            (void)memset(Entry_p, 0, sizeof(BufManager_AdminEntry_t));
        }
    }

    return rc;
}


#ifdef ADAPTER_BUFMAN_ZEROIZE
/*----------------------------------------------------------------------------
 * BufManager_Zeroize
 */
void
BufManager_Zeroize(
        uint64_t BufferAddress)
{
    if (BufferAddress != 0U)
    {
        const BufManager_AdminEntry_t * const Entry_p = BufManagerLocal_GetEntry(BufferAddress, true);
        if (Entry_p != NULL)
        {
            (void)memset(Entry_p->Buffer_p, 0, Entry_p->BufferSize);

            DMAResource_PreDMA(Entry_p->BufferHandle,
                               0,
                               (uint32_t)Entry_p->BufferSize);
        }
    }
}
#endif


/*----------------------------------------------------------------------------
 * BufManager_GetSize
 */
size_t
BufManager_GetSize(
        uint64_t BufferAddress)
{
    size_t BufferSize = 0;

    if (BufferAddress != 0U)
    {
        const BufManager_AdminEntry_t * const Entry_p = BufManagerLocal_GetEntry(BufferAddress, true);
        if (Entry_p != NULL)
        {
            BufferSize = Entry_p->BufferSize;
        }
    }

    return BufferSize;
}


/*----------------------------------------------------------------------------
 * BufManager_GetHostAddress
 */
void *
BufManager_GetHostAddress(
        uint64_t BufferAddress)
{
    void * Buffer_p = NULL;

    if (BufferAddress != 0U)
    {
        const BufManager_AdminEntry_t * const Entry_p = BufManagerLocal_GetEntry(BufferAddress, false);
        if (Entry_p != NULL)
        {
            Buffer_p = Entry_p->Buffer_p;
        }
    }

    return Buffer_p;
}


/*----------------------------------------------------------------------------
 * BufManager_PreDmaAddress
 */
int32_t
BufManager_PreDmaAddress(
        uint64_t BufferAddress)
{
    int32_t funcres = -1;

    if (BufferAddress != 0U)
    {
        const BufManager_AdminEntry_t * const Entry_p = BufManagerLocal_GetEntry(BufferAddress, false);
        if (Entry_p != NULL)
        {
#ifdef ADAPTER_BUFMAN_SWAP_ENABLE
            if (DMAResource_SwapEndianness_Get(Entry_p->BufferHandle) == 1)
            {
                DMAResource_Write32Array(Entry_p->BufferHandle,
                                         0,
                                         Entry_p->BufferSize / sizeof(uint32_t),
                                         (uint32_t*)Entry_p->Buffer_p);
            }
#endif

            DMAResource_PreDMA(Entry_p->BufferHandle,
                               0,
                               (uint32_t)Entry_p->BufferSize);

            funcres = 0;
        }
    }
    return funcres;
}


/*----------------------------------------------------------------------------
 * BufManager_PostDmaAddress
 */
void
BufManager_PostDmaAddress(
        const void * const Buffer_p)
{
    if ((Buffer_p != NULL) && gl_BufManager_InitDone)
    {
        const BufManager_AdminEntry_t * Entry_p = gl_BufManager_Admin;
        uint32_t i;

        // Search for the requested buffer
        for (i = 0U; i < BUFMANAGER_ADMIN_ENTRIES; i++)
        {
            if (Entry_p->Buffer_p == Buffer_p)
            {
                DMAResource_PostDMA(Entry_p->BufferHandle, 0,
                                    (uint32_t)Entry_p->BufferSize);
                break;
            }
            Entry_p++;
        }
    }
}


/* end of file adapter_bufmanager.c */
