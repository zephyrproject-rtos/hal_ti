/*
 * Copyright (c) 2023-2026, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>

#include <ti/drivers/dma/DMAWFF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/dma.h)

/* Bit mask for all defined DMA events */
#define DMA_INT_ALL SOC_AAON_DMASICLR_ICLR_M

static void DMAWFF3_initHw(void);
static void DMAWFF3_issueCmd(uint32_t channel, DMACommand command);

static bool isInitialized = false;

/*
 *  ======== DMAWFF3_disableChannel ========
 *
 */
void DMAWFF3_disableChannel(uint32_t channel)
{
    /* Issue ABORT command */
    DMAWFF3_issueCmd(channel, DMA_CMD_ABORT);

    /* Wait for ABORT command to finish.
     * The command finishes within maximum eight clock cycles.
     */
    while ((HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0STA + (channel * DMA_CH_OFFSET)) & HOST_DMA_CH0STA_RUN_M) ==
            HOST_DMA_CH0STA_RUN)
    {}
}

/*
 *  ======== DMAWFF3_getRemainingBytes ========
 *
 */
uint16_t DMAWFF3_getRemainingBytes(uint32_t channel)
{
    uint32_t dmaStatus;

    dmaStatus = HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0TSTA + (channel * DMA_CH_OFFSET));

    return ((dmaStatus & HOST_DMA_CH0TSTA_REMAINB_M) >> HOST_DMA_CH0TSTA_REMAINB_S);
}

/*
 *  ======== DMAWFF3_init ========
 *
 */
void DMAWFF3_init(void)
{
    /* Init the DMA hardware only once */
    if (!isInitialized)
    {
        isInitialized = true;

        /* Initialize the DMA hardware */
        DMAWFF3_initHw();
    }
}

/*
 *  ======== DMAWFF3_initChannel ========
 *
 */
void DMAWFF3_initChannel(uint32_t channel)
{
    /* Issue INIT command */
    DMAWFF3_issueCmd(channel, DMA_CMD_INIT);
}

/*
 *  ======== DMAWFF3_initHw ========
 *  This function initializes the DMA hardware module.
 *
 */
static void DMAWFF3_initHw(void)
{
    /* Disable interrupt for all channels */
    DMADisableInt(DMA_INT_ALL);

    /* Clear interrupt flags for all channels*/
    DMAClearInt(DMA_INT_ALL);

    /* Disconnect all DMA channels */
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CHCTL0) = 0xFFFFFFFFU;
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CHCTL1) = 0xFFFFFFFFU;
}

/*
 *  ======== DMAWFF3_issueCmd ========
 *  This functions issues specified command to specified channel.
 *
 */
static void DMAWFF3_issueCmd(uint32_t channel, DMACommand command)
{
    /* Issue command to write-only register */
    HWREG(HOST_DMA_TGT_BASE + HOST_DMA_O_CH0TCTL2 + (channel * DMA_CH_OFFSET)) = command;
}
