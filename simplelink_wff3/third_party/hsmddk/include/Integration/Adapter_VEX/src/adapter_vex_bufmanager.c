/* adapter_vex_bufmanager.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the buffer manager related functionality.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // API implementation
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_bufmanager.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_sleep.h>

#define VEX_DMA_TOKEN_ID_SIZE   sizeof(uint32_t)


/*----------------------------------------------------------------------------
 * vexLocal_CB_SizeAlignment
 */
static size_t
vexLocal_CB_SizeAlignment(
        const size_t Size)
{
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
    /* 32-bit alignment + extra size for the TokenID */
    return (((Size + 3U) & (size_t)~3UL) + VEX_DMA_TOKEN_ID_SIZE);
#else
    /* 32-bit alignment */
    return ((Size + 3U) & (size_t)~3UL);
#endif
}


/*----------------------------------------------------------------------------
 * vexLocal_CB_CheckClear
 */
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
static int
vexLocal_CB_CheckClear(
        void * Buffer_p,
        const size_t Size,
        void * UserData_p)
{
    if (UserData_p != NULL)
    {
        /* Zeroize TokenID area */
        uint8_t * Ptr_p = (uint8_t *)Buffer_p;
        Ptr_p = &Ptr_p[(Size - VEX_DMA_TOKEN_ID_SIZE)];
        (void)memset(Ptr_p, 0, sizeof(uint32_t));
    }
    return 0;
}
#endif


/*----------------------------------------------------------------------------
 * vexLocal_CB_CheckReady
 */
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
static int
vexLocal_CB_CheckReady(
        void * Buffer_p,
        const size_t Size,
        void * UserData_p)
{
    int32_t retval = 0;

    if (UserData_p != NULL)
    {
        uint32_t TokenID = (uint32_t)*(uint16_t *)UserData_p;
        uint8_t * Ptr_p = (uint8_t *)Buffer_p;

#ifdef VEX_DISABLE_TOKENID_WR_KEYPAIR
        if (TokenID == 0)
        {
            int32_t i = (int32_t)(Size - VEX_DMA_TOKEN_ID_SIZE);
            uint8_t d = 0;

            /* Special case:
             * Where the TokenID cannot be used to check buffer readiness.
             * However, the buffer is zeroized before it was passed on */
            for (; i >= 0; i--)
            {
                d |= *Ptr_p++;
            }
            if (d == 0)
            {
                /* Assume not yet ready */
                retval = -1;
            }
        }
        else
#endif
        {
            uint8_t TokenBuf[VEX_DMA_TOKEN_ID_SIZE];

            /* The HW writes 32-bit word in Little Endian format, so convert the
             * TokenID to a byte array in Little Endian format */
            TokenBuf[0] = (uint8_t)(TokenID & 0x000000FFU); // LSB first
            TokenBuf[1] = (uint8_t)((TokenID & 0x0000FF00U) >> 8);
            TokenBuf[2] = 0;
            TokenBuf[3] = 0;

            /* Check the TokenID */
            Ptr_p = &Ptr_p[(Size - VEX_DMA_TOKEN_ID_SIZE)];
            if (memcmp(Ptr_p, TokenBuf, sizeof(uint32_t)) != 0)
            {
                retval = -1;
            }
        }

        LOG_INFO(VEX_LOG_PREFIX "%s: Data ready\n", __func__);
    }
    else
    {
        /* Force some delay to increase the chance that the data is available */
        Adapter_SleepMS(VEX_POLLING_DELAY_MS);
    }

    return retval;
}
#endif


void
vex_InitBufManager(void)
{
#ifdef VEX_CHECK_DMA_WITH_TOKEN_ID
    (void)BufManager_Register(vexLocal_CB_SizeAlignment,
                              vexLocal_CB_CheckClear,
                              vexLocal_CB_CheckReady);
#else
    (void)BufManager_Register(vexLocal_CB_SizeAlignment,
                              NULL,
                              NULL);
#endif
}


/* end of file adapter_vex_bufmanager.c */
