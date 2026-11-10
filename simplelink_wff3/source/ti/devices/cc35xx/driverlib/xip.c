/******************************************************************************
 *  Filename:       xip.c
 *
 *  Description:    Driver for the XIP peripheral
 *
 *  Copyright (c) 2024-2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#include "xip.h"
#include "debug.h"

//! UDMA secure channel offset
#define XIP_UDMA_SEC_CH_OFFSET     0
//! UDMA non-secure channel offset, in bytes
#define XIP_UDMA_NONSEC_CH_OFFSET  HOST_XIP_O_UDNSCFG0 - HOST_XIP_O_UDSCFG0
//! UDMA Maximum configurable job size, in words
#define XIP_UDMA_MAX_JOB_SIZE      HOST_XIP_UDSCFG2_JLEN_M
//! Status bit to indicate that DMA is processing (secure and non-secure)
#define XIP_UDMA_JOB_CONFIGURED    HOST_XIP_UDSSTA_JSTA
#define XIP_UDMA_NO_JOB_CONFIGURED 0

#define XIP_OTFDE_DISABLE_M (HOST_XIP_OTSTA_ACTIVESTA_M | HOST_XIP_OTSTA_TASKSUS)
#define XIP_OTFDE_DISABLE   0

//*****************************************************************************
//
// Functions
//
//*****************************************************************************
//*****************************************************************************
//
// Start a uDMA transaction
//
//*****************************************************************************
uint32_t XIPStartUDMATransaction(const uint32_t *srcAddr,
                                 uint32_t *dstAddr,
                                 uint32_t length,
                                 uint8_t directionMode,
                                 uint32_t channelSelect)
{
    // Assert when length is not supported by the DMA (UDMA_MAX_TRANSACTION_BYTES)
    ASSERT(length <= XIP_UDMA_MAX_JOB_SIZE);

    // Secure channel is the UDMA default channel
    uint32_t chOffset = XIP_UDMA_SEC_CH_OFFSET;

    // If requested, change to non-secure channel
    if (channelSelect == XIP_UDMA_NON_SECURE_CHANNEL)
    {
        chOffset = XIP_UDMA_NONSEC_CH_OFFSET;
    }

    // Check if job already configured (clear after job processing finished)
    if ((HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSSTA) & HOST_XIP_UDSSTA_JSTA_M) !=
         XIP_UDMA_NO_JOB_CONFIGURED)
    {
        // UDMA job did not started, because an ongoing job
        return XIP_UDMA_JOB_NOT_START;
    };

    HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSCFG0) = ((uint32_t)srcAddr << HOST_XIP_UDSCFG0_JSRCADDR_S) &
                                                                HOST_XIP_UDSCFG0_JSRCADDR_M;

    HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSCFG1) = ((uint32_t)dstAddr << HOST_XIP_UDSCFG1_JDESTADDR_S) &
                                                                HOST_XIP_UDSCFG1_JDESTADDR_M;

    HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSCFG2) = (length << HOST_XIP_UDSCFG2_JLEN_S) &
                                                                HOST_XIP_UDSCFG2_JLEN_M;

    HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSCFG3) = (directionMode << HOST_XIP_UDSCFG3_JDIR_S) &
                                                                HOST_XIP_UDSCFG3_JDIR_M;

    // Start the UDMA job
    HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSCTL0) = HOST_XIP_UDSCTL0_JSTART;

    return XIP_UDMA_JOB_STARTED;
}

//*****************************************************************************
//
// Get channel status
//
//*****************************************************************************
uint32_t XIPGetUDMAChannelProgressingStatus(uint32_t channelSelect)
{
    // Secure channel is the UDMA default channel
    uint32_t chOffset = XIP_UDMA_SEC_CH_OFFSET;
    uint32_t chStatus;

    if (channelSelect == XIP_UDMA_NON_SECURE_CHANNEL)
    {
        chOffset = XIP_UDMA_NONSEC_CH_OFFSET;
    }

    chStatus = (HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSSTA) & HOST_XIP_UDSSTA_JINPROG_M) >>
                HOST_XIP_UDSSTA_JINPROG_S;

    return chStatus;
}

//*****************************************************************************
//
// Get channel remain number of bytes to transmit
//
//*****************************************************************************
uint32_t XIPGetUDMAChannelWordsLeft(uint32_t channelSelect)
{
    // Secure channel is the UDMA default channel
    uint32_t chOffset = XIP_UDMA_SEC_CH_OFFSET;
    uint32_t chWordLeft;

    if (channelSelect == XIP_UDMA_NON_SECURE_CHANNEL)
    {
        chOffset = XIP_UDMA_NONSEC_CH_OFFSET;
    }

    chWordLeft = (HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSSTA) & HOST_XIP_UDSSTA_RDWRDSLFT_M) >>
                  HOST_XIP_UDSSTA_RDWRDSLFT_S;

    return chWordLeft;
}

//*****************************************************************************
//
// Get job status after interrupt
//
//*****************************************************************************
uint32_t XIPGetUDMAIrqStatus(uint32_t channelSelect)
{
    // Secure channel is the UDMA default channel
    uint32_t chOffset = XIP_UDMA_SEC_CH_OFFSET;
    uint32_t reqStatus;

    if (channelSelect == XIP_UDMA_NON_SECURE_CHANNEL)
    {
        chOffset = XIP_UDMA_NONSEC_CH_OFFSET;
    }

    reqStatus = (HWREG(HOST_XIP_REGS_BASE + chOffset + HOST_XIP_O_UDSIRQ) & HOST_XIP_UDSIRQ_JIRQSTA_M) >>
                 HOST_XIP_UDSIRQ_JIRQSTA_S;

    return reqStatus;
}

//*****************************************************************************
//
// Disable the OTFDE peripheral
//
//*****************************************************************************
void __attribute__((noinline, section(".TI.ramfunc"))) XIPDisableOTFDE(void)
{
    // Assume the user know when it is ok to disable the OTFDE
    // (not in a middle of udma transactions and not when executing code from flash)
    HWREG(HOST_XIP_REGS_BASE + HOST_XIP_O_OTSWCTL1) = HOST_XIP_OTSWCTL1_DISREQ;

    while (HOST_XIP_OTSTA_ACTIVESTA == (HWREG(HOST_XIP_REGS_BASE + HOST_XIP_O_OTSTA) & HOST_XIP_OTSTA_ACTIVESTA_M)) {};
}

//*****************************************************************************
//
// Enable the OTFDE peripheral
//
//*****************************************************************************
void __attribute__((noinline, section(".TI.ramfunc"))) XIPEnableOTFDE(void)
{

    HWREG(HOST_XIP_REGS_BASE + HOST_XIP_O_OTSWCTL0) = HOST_XIP_OTSWCTL0_ENREQ;

    while ((HWREG(HOST_XIP_REGS_BASE + HOST_XIP_O_OTSTA) & XIP_OTFDE_DISABLE_M) ==
           XIP_OTFDE_DISABLE) {};
}
