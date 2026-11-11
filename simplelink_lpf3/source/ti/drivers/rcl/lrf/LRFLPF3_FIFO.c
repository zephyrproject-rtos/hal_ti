/*
 * Copyright (c) 2026, Texas Instruments Incorporated
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
#include <stdbool.h>

#include <ti/drivers/rcl/LRF.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)

/* ============================================================================
 * Static Global Variables
 * ============================================================================
 */

/* Status to tell if the RX FIFO is already in a deallocated state (SRP and RP being the same) */
static bool rxFifoDeallocated = true;

/* ============================================================================
 * Forward Declarations
 * ============================================================================
 */

static void LRF_writeFifoPtr(uint32_t value, uintptr_t regAddr);
static void LRF_writeFifoPtrs(uint32_t value, uintptr_t regAddr0, uintptr_t regAddr1);

/* ============================================================================
 * Implementations
 * ============================================================================
 */

/*
 *  ======== LRF_getTxFifoWritable ========
 */
uint32_t LRF_getTxFifoWritable(void)
{
    return HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE);
}

/*
 *  ======== LRF_prepareTxFifo ========
 */
uint32_t LRF_prepareTxFifo(void)
{
    /* Reset TXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);
    /* Set up TXFIFO with auto commit, without auto deallocate */
    uint32_t fcfg0 = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0);
    fcfg0 &= ~LRFDPBE_FCFG0_TXADEAL_M;
    fcfg0 |=  LRFDPBE_FCFG0_TXACOM_M;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) = fcfg0;
    /* Return writable bytes, which is the FIFO size */
    return HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE);
}

/*
 *  ======== LRF_peekRxFifo ========
 */
uint32_t LRF_peekRxFifo(int32_t offset)
{
    uint32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + offset;
    uint32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2U;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    return HWREG_READ_LRF(LRFD_BUFRAM_BASE + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) << 2U) + index);
}

/*
 *  ======== LRF_peekTxFifo ========
 */
uint32_t LRF_peekTxFifo(int32_t offset)
{
    uint32_t index = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFRP) + offset;
    uint32_t fifosz = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2U;
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    return HWREG_READ_LRF(LRFD_BUFRAM_BASE + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) << 2U) + index);
}

/*
 *  ======== LRF_getTxFifoWrAddr ========
 */
uint8_t *LRF_getTxFifoWrAddr(int32_t offset)
{
    int32_t index = (int32_t) (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWP) + offset);
    return (uint8_t *) (TXF_UNWRAPPED_BASE_ADDR + (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) << 2U) + index);
}

/*
 *  ======== LRF_writeFifoPtr ========
 */
/* Use the workaround of RCL-367 to write the FIFO pointer register with
 * address regAddr to the given value. This allows PBE to protect against
 * writing FCMD at the same time */
static void LRF_writeFifoPtr(uint32_t value, uintptr_t regAddr)
{
    /* Run in protected region to avoid unnecessary delays */
    uintptr_t key = HwiP_disable();
    /* Direct PBE to write FIFO commands to FSTAT register to make them ignored */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FSTAT) & 0x0FFFU) >> 2U;
    /* Wait a little so that PBE has time to finish any pending command writes */
    /* Do the wait by dummy reads of FIFOCMDADD */
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    /* Write to specified register */
    HWREG_WRITE_LRF(regAddr) = value;
    /* Set PBE back to writing FIFO commands to FCMD */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFFU) >> 2U;
    HwiP_restore(key);
}

/*
 *  ======== LRF_writeFifoPtrs ========
 */
/* Use the workaround of RCL-367 to write both FIFO pointer registers with
 * addresses regAddr0 and regAddr1 to the given value. This allows PBE to
 * protect against writing FCMD at the same time */
static void LRF_writeFifoPtrs(uint32_t value, uintptr_t regAddr0, uintptr_t regAddr1)
{
    /* Run in protected region to avoid unnecessary delays */
    uintptr_t key = HwiP_disable();
    /* Direct PBE to write FIFO commands to FSTAT register to make them ignored */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FSTAT) & 0x0FFFU) >> 2U;
    /* Wait a little so that PBE has time to finish any pending command writes */
    /* Do the wait by dummy reads of FIFOCMDADD */
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    (void) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD);
    /* Write to specified registers */
    HWREG_WRITE_LRF(regAddr0) = value;
    HWREG_WRITE_LRF(regAddr1) = value;
    /* Set PBE back to writing FIFO commands to FCMD */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_FIFOCMDADD) = ((LRFDPBE_BASE + LRFDPBE_O_FCMD) & 0x0FFFU) >> 2U;
    HwiP_restore(key);
}

/*
 *  ======== LRF_skipTxFifoWords ========
 */
void LRF_skipTxFifoWords(uint32_t wordLength)
{
    int32_t index = (int32_t) (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFRP) + (wordLength * 4U));
    int32_t fifosz = (int32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2);
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr((uint32_t) index, (LRFDPBE_BASE + LRFDPBE_O_TXFRP));
}

/*
 *  ======== LRF_discardRxFifoWords ========
 */
void LRF_discardRxFifoWords(uint32_t wordLength)
{
    int32_t index = (int32_t) (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + (wordLength * 4U));
    int32_t fifosz = (int32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2);
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    /* Write updated pointer to rp and srp */
    LRF_writeFifoPtrs((uint32_t) index, (LRFDPBE_BASE + LRFDPBE_O_RXFRP), (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
    /* RX FIFO is now deallocated */
    rxFifoDeallocated = true;
}

/*
 *  ======== LRF_readRxFifoWords ========
 */
void LRF_readRxFifoWords(uint32_t *data32, uint32_t wordLength)
{
    /* Due to RCL-367, the packet is read from memory, and the read pointer is updated afterwards */
    /* Pointer to unwrapped FIFO RAM representation */
    uint32_t fifoStart = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) & LRFDPBE_FCFG3_RXSTRT_M) >> LRFDPBE_FCFG3_RXSTRT_S) << 2U;
    uint32_t readPointer = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) & ~0x0003U;
    volatile uint32_t *fifoReadPtr = (volatile uint32_t *) (RXF_UNWRAPPED_BASE_ADDR + fifoStart + readPointer);

    /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    ASM_4_NOPS();
#endif
    for (uint32_t i = 0U; i < wordLength; i++)
    {
        *data32++ = *fifoReadPtr++;
    }
    /* Update read pointer */
    int32_t index = (int32_t) (readPointer + (wordLength * 4U));
    int32_t fifosz = (int32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2);
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr((uint32_t) index, (LRFDPBE_BASE + LRFDPBE_O_RXFRP));
    /* RP was moved, so RX FIFO is not deallocated */
    rxFifoDeallocated = false;
}

/*
 *  ======== LRF_writeTxFifoWords ========
 */
void LRF_writeTxFifoWords(const uint32_t *data32, uint32_t wordLength)
{
    /* Due to RCL-367, the packet is written to memory, and the write pointer is updated afterwards */
    /* Pointer to unwrapped FIFO RAM representation */
    uint32_t fifoStart = ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) & LRFDPBE_FCFG1_TXSTRT_M) >> LRFDPBE_FCFG1_TXSTRT_S) << 2U;
    uint32_t writePointer = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWP) & ~0x0003U;
    volatile uint32_t *fifoWritePtr = (volatile uint32_t *) (TXF_UNWRAPPED_BASE_ADDR + fifoStart + writePointer);

    /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    ASM_4_NOPS();
#endif
    for (uint32_t i = 0U; i < wordLength; i++)
    {
        *fifoWritePtr++ = *data32++;
    }
    /* Update write pointer */
    int32_t index = (int32_t) (writePointer + (wordLength * 4U));
    int32_t fifosz = (int32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) & LRFDPBE_FCFG2_TXSIZE_M) >> LRFDPBE_FCFG2_TXSIZE_S) << 2);
    if (index >= fifosz)
    {
        index -= fifosz;
    }
    LRF_writeFifoPtr((uint32_t) index, (LRFDPBE_BASE + LRFDPBE_O_TXFWP));
}

/*
 *  ======== LRF_setRxFifoEffSz ========
 */
void LRF_setRxFifoEffSz(uint32_t maxSz)
{
    uint32_t fifoSz = (uint32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2);
    if (maxSz >= fifoSz)
    {
        /* Deallocate RX FIFO to get no additional FIFO restriction */
        /* Due to RCL-367, the operation is done with a FIFO pointer register write */
        if (!rxFifoDeallocated)
        {
            /* We should not do this write if the FIFO was already deallocated, as it would move the SRP one full round */
            LRF_writeFifoPtr(HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP), (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
            rxFifoDeallocated = true;
        }
    }
    else
    {
        uint32_t newSrp;
        /* A limit of 0 can't be achieved through manipulating SRP. For all practical purposes, a limit of 1 has the same effect. */
        if (maxSz == 0U)
        {
            maxSz = 1U;
        }

        newSrp = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP) + maxSz;
        if (newSrp >= fifoSz)
        {
            newSrp -= fifoSz;
        }
        /* The new SRP value will always be a write forward in the FIFO */
        /* Do not write if the value is the same as before, as this will be
            interpreted by the FIFO HW as going a full round forward */

        if (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFSRP) != newSrp)
        {
            LRF_writeFifoPtr(newSrp, (LRFDPBE_BASE + LRFDPBE_O_RXFSRP));
            /* SRP is now different from RP, so RX FIFO is not deallocated */
            rxFifoDeallocated = false;
        }
    }
}

/*
 *  ======== LRF_peekRxFifoWords ========
 */
void LRF_peekRxFifoWords(uint32_t *data32, uint32_t wordLength, uint32_t startRp)
{
    uint32_t fifoStart = (uint32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) & LRFDPBE_FCFG3_RXSTRT_M) >> LRFDPBE_FCFG3_RXSTRT_S) << 2);
    uint32_t *dataEntry = (uint32_t *) (RXF_UNWRAPPED_BASE_ADDR + fifoStart + startRp);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    ASM_4_NOPS();
#endif
    for (uint32_t i = 0U; i < wordLength; i++)
    {
        *data32++ = *dataEntry++;
    }
}

/*
 *  ======== LRF_getUncommittedFifoStatus ========
 */
uint32_t LRF_getUncommittedFifoStatus(uint32_t *currentRp)
{
    /* Find information  on RX FIFO */
    int32_t fifosz = (int32_t) (((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) & LRFDPBE_FCFG4_RXSIZE_M) >> LRFDPBE_FCFG4_RXSIZE_S) << 2);

    uintptr_t key = HwiP_disable();
    /* Check RX FIFO read and write pointers */
    int32_t rp = (int32_t) HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP);
    int32_t wp = (int32_t) HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFWP);
    HwiP_restore(key);

    /* Find number of bytes written to FIFO (including uncommitted) */
    int32_t ptrDiff = wp - rp;
    if (ptrDiff < 0)
    {
        ptrDiff += fifosz;
    }
    *currentRp = (uint32_t)rp;
    return (uint32_t) ptrDiff;
}

/*
 *  ======== LRF_prepareRxFifo ========
 */
uint32_t LRF_prepareRxFifo(void)
{
    uint32_t fifoSize;
    /* Reset RXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_RXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);
    /* Set up RXFIFO without auto commit or deallocate */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) & (~(LRFDPBE_FCFG0_RXADEAL_M | LRFDPBE_FCFG0_RXACOM_M));
    /* Read writable bytes, which is the FIFO size */
    fifoSize = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFWRITABLE);
    /* Write SRP to 0. This sets no available space for writing; to be updated
       by calling LRF_setRxFifoEffSz().
       This write can be done without protection since PBE is not allowed to be
       running here, ref RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFSRP) = 0U;
    rxFifoDeallocated = false;

    return fifoSize;
}

/*
 *  ======== LRF_retryTxFifo ========
 */
void LRF_retryTxFifo(void)
{
    /* Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RETRY);
}

/*
 *  ======== LRF_hasRxWordToRead ========
 */
bool LRF_hasRxWordToRead(void)
{
    /* LRFDPBE_O_RXFREADABLE returns the number of bytes available in the LRF RX FIFO.
     * Compare it against 4 (a word is 4 bytes in SYSCPU memory space) to determine
     * if a full word can be read.
     */
    return (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4U);
}
