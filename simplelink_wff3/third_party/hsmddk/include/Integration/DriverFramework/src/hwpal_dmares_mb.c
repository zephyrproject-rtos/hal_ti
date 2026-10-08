/* hwpal_dmares_mb.c
 *
 * MicroBlaze implementation of the Driver Framework v4 DMAResource API.
 *
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

#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_mgmt.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_buf.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/DMAResource_API/incl/dmares_rw.h>

// Internal API implemented here
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/dmares_hwpal.h>


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Default configuration
#include <third_party/hsmddk/include/Integration/DriverFramework/incl/c_hwpal_dmares_mb.h> // get the configuration options

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>           // memset

#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_swap.h>    // Device_SwapEndian32

#include <third_party/hsmddk/include/Integration/DriverFramework/incl/dmares_gen.h>     // Helpers from Generic DMAResource API

#undef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX  HWPAL_LOG_SEVERITY
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <stdlib.h>

extern void
DMAResource_Write32Array(
        const DMAResource_Handle_t Handle,
        const uint32_t StartWordOffset,
        const uint32_t WordCount,
        const uint32_t * Values_p);

extern int32_t
DMAResource_SwapEndianness_Get(
        const DMAResource_Handle_t Handle);


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*

 Requirements on the records:
  - pre-allocated array of records
  - valid between Create and Destroy
  - re-use on a least-recently-used basis to make sure accidental continued
    use after destroy does not cause crashes, allowing us to detect the
    situation instead of crashing quickly.

 Requirements on the handles:
  - one handle per record
  - valid between Create and Destroy
  - quickly find the ptr-to-record belonging to the handle
  - detect continued use of a handle after Destroy
  - caller-hidden admin/status, thus not inside the record
  - report leaking handles upon exit

 Solution:
  - handle cannot be a record number (no post-destroy use detection possible)
  - recnr/destroyed in separate memory location for each handle: gl_mb_DMAResHandles_p
  - Array of records: gl_mb_DMAResRecords_p
  - free locations in Array1: Freelist1 (gl_mb_DMAResFreeHandles)
  - free record numbers list: Freelist2 (gl_mb_DMAResFreeRecords)
 */

typedef struct
{
    int ReadIndex;
    int WriteIndex;
    int * Nrs_p;
} DMAResourceLib_FreeList_t;

typedef struct
{
    int CurIndex;
} DMAResourceLib_InUseHandles_Iterator_t;

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
// Lock data structure
typedef struct
{
    SemaphoreHandle_t SemHandle;
} DMAResourceLib_Lock_t;
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE

#define HWPAL_RECNR_DESTROYED                       -1

#undef HWPAL_DMARESOURCE_DCACHE_LINE_SIZE

#ifdef XPAR_MICROBLAZE_0_DCACHE_LINE_LEN
#define HWPAL_DMARESOURCE_DCACHE_LINE_SIZE    \
                    (XPAR_MICROBLAZE_0_DCACHE_LINE_LEN * sizeof(uint32_t))
#else
#define HWPAL_DMARESOURCE_DCACHE_LINE_SIZE    1
#endif

#define HWPAL_LOG       HWPAL_DMARESOURCE_LOG_LEVEL


/*----------------------------------------------------------------------------
 * Local variables
 */

static int gl_mb_DMAResHandlesCount = 0; // remainder are valid only when this is != 0
static int * gl_mb_DMAResHandles_p;
static DMAResource_Record_t * gl_mb_DMAResRecords_p;
static DMAResourceLib_FreeList_t gl_mb_DMAResFreeHandles;
static DMAResourceLib_FreeList_t gl_mb_DMAResFreeRecords;

/*----------------------------------------------------------------------------
 * DMAResourceLib_FreeList_Get
 *
 * Gets the next entry from the freelist. Returns -1 when the list is empty.
 */
static inline int
DMAResourceLib_FreeList_Get(
        DMAResourceLib_FreeList_t * const List_p)
{
    int Nr = -1;
    int ReadIndex_Updated = List_p->ReadIndex + 1;

    if (ReadIndex_Updated >= gl_mb_DMAResHandlesCount)
    {
        ReadIndex_Updated = 0;
    }

    // if post-increment ReadIndex == WriteIndex, the list is empty
    if (ReadIndex_Updated != List_p->WriteIndex)
    {
        // grab the next number
        Nr = List_p->Nrs_p[List_p->ReadIndex];
        List_p->ReadIndex = ReadIndex_Updated;
    }

    return Nr;
}


/*----------------------------------------------------------------------------
 * DMAResourceLib_FreeList_Add
 *
 * Adds an entry to the freelist.
 */
static inline void
DMAResourceLib_FreeList_Add(
        DMAResourceLib_FreeList_t * const List_p,
        int Nr)
{
    if (List_p->WriteIndex == List_p->ReadIndex)
    {
        LOG_CRIT("%s: failed, attempt to add value %d to full list\n",
                 __func__, Nr);
        return;
    }

    if (Nr < 0 || Nr >= gl_mb_DMAResHandlesCount)
    {
        LOG_CRIT("%s: failed, attempt to put invalid value: %d\n",
                 __func__, Nr);
        return;
    }

    {
        int WriteIndex_Updated = List_p->WriteIndex + 1;
        if (WriteIndex_Updated >= gl_mb_DMAResHandlesCount)
        {
            WriteIndex_Updated = 0;
        }

        // store the number
        List_p->Nrs_p[List_p->WriteIndex] = Nr;
        List_p->WriteIndex = WriteIndex_Updated;
    }
}


/*----------------------------------------------------------------------------
 * DMAResourceLib_InUseHandles_*
 *
 * Helper functions to iterate over all currently in-use handles.
 *
 * Usage:
 *     DMAResourceLib_InUseHandles_Iterator_t it;
 *     for (Handle = DMAResourceLib_InUseHandles_First(&it);
 *          Handle != NULL;
 *          Handle = DMAResourceLib_InUseHandles_Next(&it))
 *     { ...
 *
 */
static inline DMAResource_Record_t *
DMAResourceLib_InUseHandles_Get(
        DMAResourceLib_InUseHandles_Iterator_t * const it)
{
    DMAResource_Record_t * Rec_p;

    do
    {
        if (it->CurIndex >= gl_mb_DMAResHandlesCount)
        {
            return NULL;
        }

        Rec_p = gl_mb_DMAResRecords_p + it->CurIndex++;

        if (Rec_p->Magic != DMARES_RECORD_MAGIC)
        {
            Rec_p = NULL;
        }
    }
    while(Rec_p == NULL);

    return Rec_p;
}


static inline DMAResource_Record_t *
DMAResourceLib_InUseHandles_First(
        DMAResourceLib_InUseHandles_Iterator_t * const it)
{
    it->CurIndex = 0;
    return DMAResourceLib_InUseHandles_Get(it);
}


static inline DMAResource_Record_t *
DMAResourceLib_InUseHandles_Next(
        DMAResourceLib_InUseHandles_Iterator_t * const it)
{
    return DMAResourceLib_InUseHandles_Get(it);
}


/*----------------------------------------------------------------------------
 * DMAResourceLib_IsSubRangeOf
 *
 * Return true if the address range defined by 'AddrPair1' and 'Size1' is
 * within the address range defined by 'AddrPair2' and 'Size2'.
 */
static bool
DMAResourceLib_IsSubRangeOf(
        const DMAResource_AddrPair_t * const AddrPair1,
        const unsigned int Size1,
        const DMAResource_AddrPair_t * const AddrPair2,
        const unsigned int Size2)
{
    if (AddrPair1->Domain == AddrPair2->Domain)
    {
        const uint8_t * Addr1 = AddrPair1->Address_p;
        const uint8_t * Addr2 = AddrPair2->Address_p;

        if ((Size1 <= Size2) &&
            (Addr2 <= Addr1) &&
            ((Addr1 + Size1) <= (Addr2 + Size2)))
        {
            return true;
        }
    }

    return false;
}


/*----------------------------------------------------------------------------
 * DMAResourceLib_Find_Matching_DMAResource
 *
 * Return a pointer to the DMAResource record for a currently allocated or
 * attached DMA buffer that matches the given 'Properties' and 'AddrPair'.
 * The match can be either exact or indicate that the buffer defined by
 * 'Properties and 'AddrPair' is a proper sub section of the allocated or
 * attached buffer.
 */
static DMAResource_Record_t *
DMAResourceLib_Find_Matching_DMAResource(
        const DMAResource_Properties_t * const Properties,
        const DMAResource_AddrPair_t AddrPair)
{
    DMAResourceLib_InUseHandles_Iterator_t it;
    DMAResource_AddrPair_t * Pair_p;
    DMAResource_Record_t * Rec_p;
    unsigned int Size;

    for (Rec_p = DMAResourceLib_InUseHandles_First(&it);
         Rec_p != NULL;
         Rec_p = DMAResourceLib_InUseHandles_Next(&it))
    {
        if (Rec_p->AllocatorRef == 'R' || Rec_p->AllocatorRef == 'N')
        {
            // skip registered buffers when looking for a match,
            // i.e. only consider allocated or attached buffers.
            continue;
        }

        if (Properties->Bank != Rec_p->Props.Bank  ||
            Properties->Size > Rec_p->Props.Size ||
            Properties->Alignment > Rec_p->Props.Alignment)
        {
            // obvious mismatch in properties
            continue;
        }

        Size = Properties->Size;
        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_HOST);
        if (Pair_p != NULL &&
            DMAResourceLib_IsSubRangeOf(&AddrPair, Size, Pair_p, Rec_p->Props.Size))
        {
            return Rec_p;
        }

        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_BUS);
        if (Pair_p != NULL &&
            DMAResourceLib_IsSubRangeOf(&AddrPair, Size, Pair_p, Rec_p->Props.Size))
        {
            return Rec_p;
        }
    }

    return NULL;
}


/*----------------------------------------------------------------------------
 * DMAResourceLib_Setup_Record
 *
 * Setup most fields of a given DMAResource record, except for the
 * AddrPairs array.
 */
static void
DMAResourceLib_Setup_Record(
        const DMAResource_Properties_t * const Props_p,
        void * DriverHandle,
        const char AllocatorRef,
        DMAResource_Record_t * const Rec_p,
        const unsigned int AllocatedSize)
{
    Rec_p->Magic = DMARES_RECORD_MAGIC;
    Rec_p->Props = *Props_p;
    Rec_p->DriverHandle = DriverHandle;
    Rec_p->AllocatorRef = AllocatorRef;
    Rec_p->BufferSize = AllocatedSize;
}


#ifndef HWPAL_ARCH_COHERENT
/*----------------------------------------------------------------------------
 * DMAResourceLib_Handle2RecordPtr
 *
 * Return a pointer to the DMAResource record referenced by Handle and check
 * that the record's "magic value" field has the expected value.
 * Return NULL on error.
 */
static DMAResource_Record_t *
DMAResourceLib_Handle2RecordPtr(
        const DMAResource_Handle_t Handle)
{
    DMAResource_Record_t * Rec_p = DMAResource_Handle2RecordPtr(Handle);
    if (NULL != Rec_p && Rec_p->Magic != DMARES_RECORD_MAGIC)
    {
        LOG_CRIT("%s: Bad magic value %08x\n", __func__, Rec_p->Magic);
        Rec_p = NULL;
    }

    return Rec_p;
}
#endif // !HWPAL_ARCH_COHERENT


/*----------------------------------------------------------------------------
 * DMAResourceLib_ChildBusAddress
 *
 * Assuming the given ChildHostAddress is within the host address range
 * for the DMAResource defined by ParentRec_p, return the bus address
 * for the child buffer.
 */
static void *
DMAResourceLib_ChildBusAddress(
        const DMAResource_Record_t * ParentRec_p,
        const void * ChildHostAddr)
{
    ptrdiff_t DevAddrOffset;
    DMAResource_AddrPair_t * Pair_p;

    Pair_p = DMAResourceLib_LookupDomain(ParentRec_p, DMARES_DOMAIN_HOST);
    if (Pair_p == NULL)
    {
        return NULL;
    }

    DevAddrOffset = (const uint8_t *)ChildHostAddr - (uint8_t *)Pair_p->Address_p;

    Pair_p = DMAResourceLib_LookupDomain(ParentRec_p, DMARES_DOMAIN_BUS);
    if (Pair_p == NULL)
    {
        return NULL;
    }

    return  ((uint8_t *)Pair_p->Address_p) + DevAddrOffset;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MaxAlignment_Get
 */
uint32_t
HWPAL_DMAResource_MaxAlignment_Get(void)
{
    return HWPAL_DMARESOURCE_MAX_ALIGNMENT;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_DCache_Alignment_Get
 */
uint32_t
HWPAL_DMAResource_DCache_Alignment_Get(void)
{
#ifdef HWPAL_ARCH_COHERENT
    unsigned int AlignTo = 1; // No cache line alignment required
#else
    unsigned int AlignTo = HWPAL_DMARESOURCE_DCACHE_LINE_SIZE;
#endif // HWPAL_ARCH_COHERENT

    return AlignTo;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemAlloc
 */
void *
HWPAL_DMAResource_MemAlloc(
        size_t ByteCount)
{
    return malloc(ByteCount);
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_MemFree
 */
void
HWPAL_DMAResource_MemFree(
        void * Buf_p)
{
    free(Buf_p);
}

#ifdef HWPAL_DMARESOURCE_BANKS_ENABLE
/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Alloc
 */
void *
HWPAL_DMAResource_Lock_Alloc(void)
{
    DMAResourceLib_Lock_t * Lock_p = pvPortMalloc(sizeof(DMAResourceLib_Lock_t));
    if (Lock_p != NULL)
    {
        vSemaphoreCreateBinary(Lock_p->SemHandle);

        if (Lock_p->SemHandle)
        {
            return Lock_p; // success
        }

        vPortFree(Lock_p);
    }

    return NULL; // error
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Free
 */
void
HWPAL_DMAResource_Lock_Free(void * Lock_p)
{
    if (Lock_p != NULL)
    {
        DMAResourceLib_Lock_t * p = Lock_p;

        vSemaphoreDelete(p->SemHandle);

        vPortFree(p);
    }
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Acquire
 */
void
HWPAL_DMAResource_Lock_Acquire(
        void * Lock_p,
        ulong_t * Flags)
{
    IDENTIFIER_NOT_USED(Flags);

    if (Lock_p != NULL)
    {
        DMAResourceLib_Lock_t * p = Lock_p;

        xSemaphoreTake(p->SemHandle, portMAX_DELAY);
    }
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Lock_Release
 */
void
HWPAL_DMAResource_Lock_Release(
        void * Lock_p,
        ulong_t * Flags)
{
    IDENTIFIER_NOT_USED(Flags);

    if (Lock_p != NULL)
    {
        DMAResourceLib_Lock_t * p = Lock_p;

        xSemaphoreGive(p->SemHandle);
    }
}
#endif // HWPAL_DMARESOURCE_BANKS_ENABLE


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Init
 *
 * This function must be used to initialize the DMAResource administration.
 * It must be called before any of the other DMAResource_* functions may be
 * called. It may be called anew only after DMAResource_UnInit has been called.
 *
 * Return Value
 *     true   Initialization successfully, rest of the API may now be used.
 *     false  Initialization failed.
 */
bool
HWPAL_DMAResource_Init(void)
{
    unsigned int MaxHandles = HWPAL_DMA_NRESOURCES;

    // already initialized?
    if (gl_mb_DMAResHandlesCount != 0)
    {
        return false;
    }

    // this implementation only supports MaxHandles != 0
    if (MaxHandles == 0)
    {
        return false;
    }

    gl_mb_DMAResRecords_p = HWPAL_DMAResource_MemAlloc(MaxHandles * sizeof(DMAResource_Record_t));
    gl_mb_DMAResHandles_p = HWPAL_DMAResource_MemAlloc(MaxHandles * sizeof(int));
    gl_mb_DMAResFreeHandles.Nrs_p = HWPAL_DMAResource_MemAlloc(MaxHandles * sizeof(int));
    gl_mb_DMAResFreeRecords.Nrs_p = HWPAL_DMAResource_MemAlloc(MaxHandles * sizeof(int));

    // if any allocation failed, free the whole lot
    if (gl_mb_DMAResRecords_p == NULL ||
        gl_mb_DMAResHandles_p == NULL ||
        gl_mb_DMAResFreeHandles.Nrs_p == NULL ||
        gl_mb_DMAResFreeRecords.Nrs_p == NULL)
    {
        if (gl_mb_DMAResRecords_p)
        {
            HWPAL_DMAResource_MemFree(gl_mb_DMAResRecords_p);
        }

        if (gl_mb_DMAResHandles_p)
        {
            HWPAL_DMAResource_MemFree(gl_mb_DMAResHandles_p);
        }

        if (gl_mb_DMAResFreeHandles.Nrs_p)
        {
            HWPAL_DMAResource_MemFree(gl_mb_DMAResFreeHandles.Nrs_p);
        }

        if (gl_mb_DMAResFreeRecords.Nrs_p)
        {
            HWPAL_DMAResource_MemFree(gl_mb_DMAResFreeRecords.Nrs_p);
        }

        gl_mb_DMAResRecords_p = NULL;
        gl_mb_DMAResHandles_p = NULL;
        gl_mb_DMAResFreeHandles.Nrs_p = NULL;
        gl_mb_DMAResFreeRecords.Nrs_p = NULL;

        return false;
    }

    // initialize the record numbers freelist
    // initialize the handle numbers freelist
    // initialize the handles array
    {
        unsigned int i;

        for (i = 0; i < MaxHandles; i++)
        {
            gl_mb_DMAResHandles_p[i] = HWPAL_RECNR_DESTROYED;
            gl_mb_DMAResFreeHandles.Nrs_p[i] = MaxHandles - 1 - i;
            gl_mb_DMAResFreeRecords.Nrs_p[i] = i;
            gl_mb_DMAResRecords_p[i].Magic = 0;
        }

        gl_mb_DMAResFreeHandles.ReadIndex = 0;
        gl_mb_DMAResFreeHandles.WriteIndex = 0;

        gl_mb_DMAResFreeRecords.ReadIndex = 0;
        gl_mb_DMAResFreeRecords.WriteIndex = 0;
    }

    gl_mb_DMAResHandlesCount = MaxHandles;

    return true;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_UnInit
 *
 * This function can be used to uninitialize the DMAResource administration.
 * The caller must make sure that handles will not be used after this function
 * returns.
 * If memory was allocated by HWPAL_DMAResource_Init,
 * this function will free it.
 */
void
HWPAL_DMAResource_UnInit(void)
{
    // exit if not initialized
    if (gl_mb_DMAResHandlesCount == 0)
    {
        return;
    }

#ifdef HWPAL_TRACE_DMARESOURCE_LEAKS
    // find resource leaks
    {
        int i;
        bool fFirstPrint = true;

        for (i = 0; i < gl_mb_DMAResHandlesCount; i++)
        {
            int RecNr = gl_mb_DMAResHandles_p[i];

            if (RecNr >= 0)
            {
                if (fFirstPrint)
                {
                    fFirstPrint = false;
                    Log_FormattedMessage("%s found leaking handles:\n", __func__);
                }

                Log_FormattedMessage("Handle %p => Record %d\n",
                                     (void*)(gl_mb_DMAResHandles_p + i), RecNr);

                {
                    DMAResource_Record_t * Rec_p = gl_mb_DMAResRecords_p + RecNr;

                    Log_FormattedMessage("  BufferSize = %d\n"
                                         "  Alignment = %d\n"
                                         "  Bank = %d\n"
                                         "  BankType = %d\n"
                                         "  Address = %p (Domain = %d)\n",
                                         Rec_p->Props.Size,
                                         Rec_p->Props.Alignment,
                                         Rec_p->Props.Bank,
                                         Rec_p->BankType,
                                         Rec_p->AddrPairs[0].Address_p,
                                         Rec_p->AddrPairs[0].Domain);
                }
            }
        }

        if (fFirstPrint)
        {
            Log_FormattedMessage("%s: no leaks found\n", __func__);
        }
    }
#endif /* HWPAL_TRACE_DMARESOURCE_LEAKS */

    gl_mb_DMAResHandlesCount = 0;

    HWPAL_DMAResource_MemFree(gl_mb_DMAResFreeHandles.Nrs_p);
    HWPAL_DMAResource_MemFree(gl_mb_DMAResFreeRecords.Nrs_p);
    HWPAL_DMAResource_MemFree(gl_mb_DMAResHandles_p);
    HWPAL_DMAResource_MemFree(gl_mb_DMAResRecords_p);

    gl_mb_DMAResFreeHandles.Nrs_p = NULL;
    gl_mb_DMAResFreeRecords.Nrs_p = NULL;
    gl_mb_DMAResHandles_p = NULL;
    gl_mb_DMAResRecords_p = NULL;

}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Alloc
 */
int32_t
HWPAL_DMAResource_Alloc(
        const DMAResource_Properties_t RequestedProperties,
        const HWPAL_DMAResource_Properties_Ext_t RequestedPropertiesExt,
        DMAResource_AddrPair_t * const AddrPair_p,
        DMAResource_Handle_t * const Handle_p)
{
    DMAResource_Properties_t ActualProperties;

    DMAResource_AddrPair_t * Pair_p;
    DMAResource_Handle_t Handle;
    DMAResource_Record_t * Rec_p = NULL;
    unsigned int ActualSize, Alignment /*, Bank */;
    void * BufPtr = NULL;
    void * AlignedAddr_p = NULL;

    // ZEROINIT(ActualProperties);
    // TI Modification
    (void)memset(&ActualProperties, 0, sizeof(ActualProperties));

    if ((NULL == AddrPair_p) || (NULL == Handle_p))
    {
        return -1;
    }

    if (!DMAResourceLib_IsSaneInput(NULL, NULL, &RequestedProperties))
    {
        return -1;
    }

    // Allocate record
    Handle = DMAResource_CreateRecord();
    if (NULL != Handle)
    {
        Rec_p = DMAResource_Handle2RecordPtr(Handle);
    }
    if ((NULL == Handle) || (NULL == Rec_p))
    {
        return -1;
    }

#ifdef HWPAL_ARCH_COHERENT
    ActualProperties.fCached    = false;
#else
    // This implementation does not allocate to non-cached resources
    ActualProperties.fCached    = true;
#endif // HWPAL_ARCH_COHERENT

    // Hide the actual size from the caller, since (s)he is not
    // supposed to access/use any space beyond what was requested
    ActualProperties.Size = RequestedProperties.Size;

    ActualProperties.Bank = RequestedProperties.Bank;

    if (ActualProperties.fCached &&
        HWPAL_DMAResource_DCache_Alignment_Get() >
            (unsigned int)RequestedProperties.Alignment)
    {
        Alignment = HWPAL_DMAResource_DCache_Alignment_Get();
    }
    else
        Alignment = (unsigned int)RequestedProperties.Alignment;

    ActualProperties.Alignment = (int)Alignment;

    // Align if required
    ActualSize = DMAResourceLib_AlignForAddress(
                    DMAResourceLib_AlignForSize(RequestedProperties.Size,
                                                Alignment),
                    Alignment);

    // Allocate a buffer with the adjusted properties
    BufPtr = HWPAL_DMAResource_MemAlloc(ActualSize);
    if (BufPtr == NULL)
    {
        LOG_CRIT("%s: failed, (Size/Bank/Align=0x%x/%d/0x%x)\n",
                 __func__, ActualSize, RequestedProperties.Bank, Alignment);

        DMAResource_DestroyRecord(Handle);
        return -1;
    }

    DMAResourceLib_Setup_Record(&ActualProperties,
                                BufPtr,
                                'A',
                                Rec_p,
                                ActualSize);

    Rec_p->BankType = RequestedPropertiesExt.BankType;

    // Align the allocated buffer
    {
        unsigned long AlignmentOffset;
        unsigned long UnalignedAddress = ((unsigned long)BufPtr);

        AlignmentOffset = UnalignedAddress % Alignment;

        // Check if address needs to be aligned
        if( AlignmentOffset )
        {
            AlignedAddr_p =
                    (void*)(UnalignedAddress + Alignment - AlignmentOffset);
        }
        else
        {
            AlignedAddr_p = BufPtr; // No alignment required
        }
    }

    // put the host/bus address first, presumably being the most
    // frequently looked-up domain.
    Pair_p = Rec_p->AddrPairs;

    // Host and DMA address are the same in this implementation

#ifdef HWPAL_DMARES_UMDEVXS_OPT2
    Pair_p->Address_p   = AlignedAddr_p;
    Pair_p->Domain      = DMARES_DOMAIN_HOST;
    *AddrPair_p = *Pair_p; // Return this address
    ++Pair_p;
    Pair_p->Address_p   = (void*)AlignedAddr_p;
    Pair_p->Domain      = DMARES_DOMAIN_BUS;
#else
    Pair_p->Address_p   = (void*)AlignedAddr_p;
    Pair_p->Domain      = DMARES_DOMAIN_BUS;
    ++Pair_p;
    Pair_p->Address_p   = AlignedAddr_p;
    Pair_p->Domain      = DMARES_DOMAIN_HOST;
    *AddrPair_p = *Pair_p; // Return this address
#endif

    // This host address will be used for freeing the allocated buffer
    ++Pair_p;
    Pair_p->Address_p = BufPtr;
    Pair_p->Domain = DMARES_DOMAIN_HOST_UNALIGNED;

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
    Log_FormattedMessage("%s: handle = %p, allocator='%c', size allocated/requested=%d/%d,"
                         " alignment/bank/cached=%d/%d/%d, bus addr=%p,"
                         " host addr un-/aligned=%p/%p\n",
                         __func__, Handle, Rec_p->AllocatorRef,
                         Rec_p->BufferSize, Rec_p->Props.Size,
                         Rec_p->Props.Alignment, Rec_p->Props.Bank, Rec_p->Props.fCached,
                         AlignedAddr_p, BufPtr, AlignedAddr_p);
#endif

    // return results
    *Handle_p = Handle;

    return 0;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Release
 */
int32_t
HWPAL_DMAResource_Release(
        const DMAResource_Handle_t Handle)
{
    DMAResource_Record_t * Rec_p;
    void * HostAddr_p = NULL;
    int rv = 0;

    Rec_p = DMAResource_Handle2RecordPtr(Handle);
    if (Rec_p == NULL)
    {
        LOG_CRIT("%s: Invalid handle %p\n", __func__, Handle);
        return -1;
    }

    if (Rec_p->AllocatorRef == 'N' ||
        Rec_p->AllocatorRef == 'k' ||
        Rec_p->AllocatorRef == 'R')
    {
        rv = 0; // No DMA resource was allocated for this buffer
    }
    else if (Rec_p->AllocatorRef == 'A')
    {
        DMAResource_AddrPair_t * Pair_p;

        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_HOST_UNALIGNED);
        if (Pair_p != NULL)
        {
            HostAddr_p = Pair_p->Address_p;

            HWPAL_DMAResource_MemFree(HostAddr_p);
            rv = 0;
        }
        else
            rv = -1;
    }
    else
    {
        rv = -2; // error, unsupported allocator
    }

    if (rv < 0)
    {
        LOG_CRIT("%s: Driver returned with error: %u\n", __func__, rv);
        // no return here, e.g. destroy/free record anyway
    }

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
    {
        DMAResource_AddrPair_t * Pair_p;
        void * DMAAddr_p = NULL;

        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_BUS);
        if (Pair_p != NULL)
            DMAAddr_p = Pair_p->Address_p;

        Log_FormattedMessage("%s: handle = %p, allocator='%c', size allocated/requested=%d/%d,"
                             " alignment/bank/cached=%d/%d/%d,"
                             " bus addr=%p, unaligned host addr=%p\n",
                             __func__, Handle, Rec_p->AllocatorRef,
                             Rec_p->BufferSize, Rec_p->Props.Size,
                             Rec_p->Props.Alignment, Rec_p->Props.Bank, Rec_p->Props.fCached,
                             DMAAddr_p, HostAddr_p);
    }
#endif

    // free administration resources
    DMAResource_DestroyRecord(Handle);

    return rv;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_CheckAndRegister
 */
int32_t
HWPAL_DMAResource_CheckAndRegister(
        const DMAResource_Properties_t RequestedProperties,
        const DMAResource_AddrPair_t AddrPair,
        const char AllocatorRef,
        DMAResource_Handle_t * const Handle_p)
{
    void * DriverHandle;
    void * BufPtr;

    DMAResource_AddrPair_t * Pair_p;
    DMAResource_Record_t * ParentRec_p;
    DMAResource_Record_t * Rec_p;
    DMAResource_Handle_t Handle;
    DMAResource_Properties_t ActualProperties = RequestedProperties;

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
    void * DMAAddr_p = NULL;
#endif

    if (NULL == Handle_p)
    {
        return -1;
    }

    // This implementation only accepts an AddrPair with an address
    // from domain DMARES_DOMAIN_HOST and 'R' as AllocatorRef.
    // Also, the given address and properties must match an already
    // allocated or attached DMA buffer so that the buffer is known
    // to be DMA-safe.
    //
    // The AllocatorRef 'N" is also accepted. A non-DMA-safe buffer
    // is allocated, which will only exist in the address space of the
    // application.
    //
    // The AllocatorRef 'k' is also accepted if the provided buffer is DMA-safe,
    // e.g. resides within the allowed DMA boundaries and its address and size
    // are properly aligned.

    if (!DMAResourceLib_IsSaneInput(&AddrPair,
                                    &AllocatorRef,
                                    &RequestedProperties))
    {
        return -2;
    }

    if (AddrPair.Domain != DMARES_DOMAIN_HOST)
    {
        LOG_CRIT("%s: failed, unsupported domain: %u\n", __func__, AddrPair.Domain);
        return -3;
    }

    switch(AllocatorRef)
    {
        case 'k':
#ifndef HWPAL_ARCH_COHERENT
            // DMA-safe buffer address and size must be aligned
            // for D-cache line size
            if (((uintptr_t)AddrPair.Address_p &
                    (HWPAL_DMAResource_DCache_Alignment_Get()-1)) ||
                RequestedProperties.Size &
                    (HWPAL_DMAResource_DCache_Alignment_Get()-1))
            {
                HWPAL_LOG("%s: failed, address 0x%08x or size %d"
                          " not D-cache line size (%d bytes) aligned\n",
                          __func__, AddrPair.Address_p,
                          RequestedProperties.Size,
                          HWPAL_DMAResource_DCache_Alignment_Get());
                return -5;
            }
            ActualProperties.fCached = true;
#endif
            BufPtr = AddrPair.Address_p;
            DriverHandle = BufPtr;
            break;

        case 'N':
            BufPtr = AddrPair.Address_p;
            DriverHandle = BufPtr;
            break;

        case 'R':
            ParentRec_p = DMAResourceLib_Find_Matching_DMAResource(
                                                            &RequestedProperties,
                                                            AddrPair);
            if (ParentRec_p == NULL)
            {
                LOG_WARN("%s: Rejecting register request\n", __func__);
                return -6;
            }

            BufPtr = AddrPair.Address_p;
            DriverHandle = BufPtr;
            break;

        default:
            LOG_CRIT("%s: failed, unsupported allocator: %c\n",
                     __func__, AllocatorRef);
            return -7;
    }

    DriverHandle = NULL;
    ParentRec_p = NULL;

    // allocate record -> Handle & Rec_p
    Handle = DMAResource_CreateRecord();
    if (Handle == NULL)
    {
        return -8;
    }

    Rec_p = DMAResource_Handle2RecordPtr(Handle);
    if (Rec_p == NULL)
    {
        DMAResource_DestroyRecord(Handle);
        return -9;
    }

    DMAResourceLib_Setup_Record(&ActualProperties,
                                DriverHandle,
                                AllocatorRef,
                                Rec_p,
                                ActualProperties.Size);

    if (ParentRec_p)
    {
        Rec_p->BankType = ParentRec_p->BankType;
    }

    Pair_p = Rec_p->AddrPairs;

    if (AllocatorRef == 'R')
    {
        Pair_p->Address_p = DMAResourceLib_ChildBusAddress(ParentRec_p,
                                                           AddrPair.Address_p);
        Pair_p->Domain = DMARES_DOMAIN_BUS;

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
        DMAAddr_p = Pair_p->Address_p;
#endif
    }
    else if (AllocatorRef == 'k')
    {
        Pair_p->Address_p = BufPtr;
        Pair_p->Domain = DMARES_DOMAIN_BUS;

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
        DMAAddr_p = Pair_p->Address_p;
#endif
    }

    if (Pair_p->Address_p != NULL)
    {
        Pair_p++;
    }

    Pair_p->Address_p = AddrPair.Address_p;
    Pair_p->Domain = DMARES_DOMAIN_HOST;

#ifdef HWPAL_TRACE_DMARESOURCE_BUF
    Rec_p->BufferSize = RequestedProperties.Size;

    Log_FormattedMessage("%s: handle = %p, allocator='%c', size allocated/requested=%d/%d,"
                         " alignment/bank/cached=%d/%d/%d,"
                         " bus addr=%p, host addr=%p\n",
                         __func__, Handle, Rec_p->AllocatorRef,
                         Rec_p->BufferSize, Rec_p->Props.Size,
                         Rec_p->Props.Alignment, Rec_p->Props.Bank, Rec_p->Props.fCached,
                         DMAAddr_p, AddrPair.Address_p);
#endif

    *Handle_p = Handle;
    return 0;
}


/*----------------------------------------------------------------------------
 * HWPAL_DMAResource_Record_Update
 */
int32_t
HWPAL_DMAResource_Record_Update(
        const int32_t Identifier,
        DMAResource_Record_t * const Rec_p)
{
    Rec_p->DriverHandle = (void*)(uintptr_t)Identifier;

    return 0; // Success
}


/*----------------------------------------------------------------------------
 * DMAResource_CreateRecord
 *
 * This function can be used to create a record. The function returns a handle
 * for the record. Use DMAResource_Handle2RecordPtr to access the record.
 * Destroy the record when no longer required, see DMAResource_Destroy.
 * This function initializes the record to all zeros.
 *
 * Return Values
 *     Handle for the DMA Resource.
 *     NULL is returned when the creation failed.
 */
DMAResource_Handle_t
DMAResource_CreateRecord(void)
{
    int HandleNr;
    int RecNr = 0;

    // return NULL when not initialized
    if (gl_mb_DMAResHandlesCount == 0)
    {
        return NULL;
    }

    HandleNr = DMAResourceLib_FreeList_Get(&gl_mb_DMAResFreeHandles);
    if (HandleNr != -1)
    {
        RecNr = DMAResourceLib_FreeList_Get(&gl_mb_DMAResFreeRecords);
        if (RecNr == -1)
        {
            DMAResourceLib_FreeList_Add(&gl_mb_DMAResFreeHandles, HandleNr);
            HandleNr = -1;
        }
    }

    // return NULL when reservation failed
    if (HandleNr == -1)
    {
        return NULL;
    }

    // initialize the record
    {
        DMAResource_Record_t * Rec_p = gl_mb_DMAResRecords_p + RecNr;
        memset(Rec_p, 0, sizeof(DMAResource_Record_t));
    }

    // initialize the handle
    gl_mb_DMAResHandles_p[HandleNr] = RecNr;

    // fill in the handle position
    return gl_mb_DMAResHandles_p + HandleNr;
}


/*----------------------------------------------------------------------------
 * DMAResource_DestroyRecord
 *
 * This function invalidates the handle and the record instance.
 *
 * Handle
 *     A valid handle that was once returned by DMAResource_CreateRecord or
 *     one of the DMA Buffer Management functions (Alloc/Register/Attach).
 *
 * Return Values
 *     None
 */
void
DMAResource_DestroyRecord(
        const DMAResource_Handle_t Handle)
{
    if (DMAResource_IsValidHandle(Handle))
    {
        int * p = (int *)Handle;
        int RecNr = *p;

        if (RecNr >= 0 &&
            RecNr < gl_mb_DMAResHandlesCount)
        {
            int HandleNr = p - gl_mb_DMAResHandles_p;

            // unset record field with magic value
            gl_mb_DMAResRecords_p[RecNr].Magic = 0;

            // note handle is no longer value
            *p = HWPAL_RECNR_DESTROYED;

            // add the HandleNr and RecNr to respective LRU lists
            DMAResourceLib_FreeList_Add(&gl_mb_DMAResFreeHandles, HandleNr);
            DMAResourceLib_FreeList_Add(&gl_mb_DMAResFreeRecords, RecNr);

        }
        else
        {
            LOG_WARN("%s: Handle %p was already destroyed\n", __func__, Handle);
        }
    }
    else
    {
        LOG_CRIT("%s: Invalid handle %p\n", __func__, Handle);
    }
}


/*----------------------------------------------------------------------------
 * DMAResource_IsValidHandle
 *
 * This function tells whether a handle is valid.
 *
 * Handle
 *     A valid handle that was once returned by DMAResource_CreateRecord or
 *     one of the DMA Buffer Management functions (Alloc/Register/Attach).
 *
 * Return Value
 *     true   The handle is valid
 *     false  The handle is NOT valid
 */
bool
DMAResource_IsValidHandle(
        const DMAResource_Handle_t Handle)
{
    int * p = (int *)Handle;

    if (p < gl_mb_DMAResHandles_p ||
        p >= gl_mb_DMAResHandles_p + gl_mb_DMAResHandlesCount)
    {
        return false;
    }

#ifndef HWPAL_DMARES_UMDEVXS_OPT1
    // check that the handle has not been destroyed yet
    if (*p < 0 ||
        *p >= gl_mb_DMAResHandlesCount)
    {
        return false;
    }
#endif

    return true;
}


/*----------------------------------------------------------------------------
 * DMAResource_Handle2RecordPtr
 *
 * This function can be used to get a pointer to the DMA resource record
 * (DMAResource_Record_t) for the provided handle. The pointer is valid until
 * the record and handle are destroyed.
 *
 * Handle
 *     A valid handle that was once returned by DMAResource_CreateRecord or
 *     one of the DMA Buffer Management functions (Alloc/Register/Attach).
 *
 * Return Value
 *     Pointer to the DMAResource_Record_t memory for this handle.
 *     NULL is returned if the handle is invalid.
 */
DMAResource_Record_t *
DMAResource_Handle2RecordPtr(
        const DMAResource_Handle_t Handle)
{
#ifndef HWPAL_DMARES_UMDEVXS_OPT1
    if (gl_mb_DMAResHandlesCount < HWPAL_DMA_NRESOURCES)
    {
        LOG_CRIT("%s: Module not initialized? (HandlesCount=%d)\n",
                 __func__, gl_mb_DMAResHandlesCount);
    }

    if (DMAResource_IsValidHandle(Handle))
#endif // HWPAL_DMARES_UMDEVXS_OPT1
    {
        int * p = (int *)Handle;
        int RecNr = *p;

#ifndef HWPAL_DMARES_UMDEVXS_OPT1
        if (RecNr >= 0 &&
            RecNr < gl_mb_DMAResHandlesCount)
#endif
        {
            return gl_mb_DMAResRecords_p + RecNr;
        }
    }

    return NULL;
}


/*----------------------------------------------------------------------------
 * DMAResource_PreDMA
 */
void
DMAResource_PreDMA(
        const DMAResource_Handle_t Handle,
        const uint32_t ByteOffset,
        const uint32_t ByteCount)
{
#ifdef HWPAL_ARCH_COHERENT
    IDENTIFIER_NOT_USED(Handle);
    IDENTIFIER_NOT_USED(ByteOffset);
    IDENTIFIER_NOT_USED(ByteCount);
#else
    DMAResource_Record_t *Rec_p;
    unsigned int NBytes = ByteCount;

    Rec_p = DMAResourceLib_Handle2RecordPtr(Handle);
    if (Rec_p == NULL)
    {
        LOG_CRIT("%s: Invalid handle %p\n", __func__, Handle);
        return;
    }

    if (NBytes == 0)
    {
        NBytes = Rec_p->Props.Size;
    }

    if ((ByteOffset >= Rec_p->Props.Size) ||
        (NBytes > Rec_p->Props.Size) ||
        (ByteOffset + NBytes > Rec_p->Props.Size))
    {
        LOG_CRIT("%s: Invalid range 0x%08x-0x%08x (not in 0x0-0x%08x)\n",
                 __func__, ByteOffset, ByteOffset + NBytes, Rec_p->Props.Size);
        return;
    }

    if (Rec_p->Props.fCached)
    {
        DMAResource_AddrPair_t * Pair_p;

        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_BUS);
        if( Pair_p == NULL)
        {
            LOG_CRIT("%s: Failed for DMA resource handle %p\n",
                     __func__, Handle);
            return;
        }

        // Xil_L1DCacheFlushRange(
        //         (uint32_t)((char*)Pair_p->Address_p + ByteOffset), NBytes);

        // Xil_L2CacheFlushRange(
        //         (uint32_t)((char*)Pair_p->Address_p + ByteOffset), NBytes);

        LOG_INFO("%s: Bus addr %p, range 0x%08x-0x%08x, size %d\n",
                 __func__, Pair_p->Address_p, ByteOffset, ByteOffset + NBytes,
                 Rec_p->Props.Size);
    }
#endif // !HWPAL_ARCH_COHERENT
}


/*----------------------------------------------------------------------------
 * DMAResource_PostDMA
 */
void
DMAResource_PostDMA(
        const DMAResource_Handle_t Handle,
        const uint32_t ByteOffset,
        const uint32_t ByteCount)
{
#ifdef HWPAL_ARCH_COHERENT
    IDENTIFIER_NOT_USED(Handle);
    IDENTIFIER_NOT_USED(ByteOffset);
    IDENTIFIER_NOT_USED(ByteCount);
#else
    DMAResource_Record_t *Rec_p;
    uint32_t NBytes = ByteCount;

    Rec_p = DMAResourceLib_Handle2RecordPtr(Handle);
    if (Rec_p == NULL)
    {
        LOG_CRIT("%s: Invalid handle %p\n", __func__, Handle);
        return;
    }

    if (NBytes == 0)
    {
        NBytes = Rec_p->Props.Size;
    }

    if ((ByteOffset >= Rec_p->Props.Size) ||
        (NBytes > Rec_p->Props.Size) ||
        (ByteOffset + NBytes > Rec_p->Props.Size))
    {
        LOG_CRIT("%s: Invalid range 0x%08x-0x%08x (not in 0x0-0x%08x)\n",
                 __func__, ByteOffset, ByteOffset + NBytes, Rec_p->Props.Size);
        return;
    }

    if (Rec_p->Props.fCached)
    {
        DMAResource_AddrPair_t * Pair_p;

        Pair_p = DMAResourceLib_LookupDomain(Rec_p, DMARES_DOMAIN_BUS);
        if( Pair_p == NULL)
        {
            LOG_CRIT("%s: Failed for DMA resource handle %p\n",
                     __func__, Handle);
            return;
        }

        // Xil_L1DCacheInvalidateRange(
        //         (uint32_t)((char*)Pair_p->Address_p + ByteOffset),
        //         NBytes);

        // Xil_L2CacheInvalidateRange(
        //         (uint32_t)((char*)Pair_p->Address_p + ByteOffset),
        //         NBytes);

        LOG_INFO("%s: Bus addr %p, range 0x%08x-0x%08x, size %d\n",
                 __func__, Pair_p->Address_p, ByteOffset, ByteOffset + NBytes,
                 Rec_p->Props.Size);
    }
#endif // !HWPAL_ARCH_COHERENT
}


#ifndef HWPAL_DMARESOURCE_REMOVE_ATTACH
/*----------------------------------------------------------------------------
 * DMAResource_Attach
 */
int32_t
DMAResource_Attach(
        const DMAResource_Properties_t ActualProperties,
        const DMAResource_AddrPair_t AddrPair,
        DMAResource_Handle_t * const Handle_p)
{
    IDENTIFIER_NOT_USED(ActualProperties);
    IDENTIFIER_NOT_USED(AddrPair);
    IDENTIFIER_NOT_USED(Handle_p);
}
#endif

/*
 * Some API functions are implemented by the Generic DMA Resource
 * implementation..
 */


/* end of file hwpal_dmares_mb.c */
