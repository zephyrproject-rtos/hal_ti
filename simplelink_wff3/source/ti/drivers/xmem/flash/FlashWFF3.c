/*
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
 */

/*
 * ========== FlashWFF3.c ==========
 */

#include "assert.h"
#include "FlashWFF3.h"
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerWFF3.h>
#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/xmem/XMEMWFF3.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)

/*
 * Globals
 */
uint32_t FlashWFF3_savedPostConfigReturnVal __attribute__((used, section(".internalRAM.bss"))) = 0;

/* Must be in DRAM (.internalRAM.data) - accessed by .TI.ramfunc code during the
 * PS_RAM-inaccessible window (OTFDE disabled / OSPI in flash mode).
 * Initialized at boot time from Flash. */
uint32_t flashClockPTickPeriod __attribute__((section(".internalRAM.data"))) = 1U;

static uint32_t __attribute__((noinline, section(".TI.ramfunc"))) getClockPTickUs(void);
static bool __attribute__((noinline, section(".TI.ramfunc")))
FlashClockPCheckTimeout(uint32_t StartTick, uint32_t TimerInMicroSec);
static FlashStigStatus __attribute__((noinline, section(".TI.ramfunc"))) FlashStigConfigOp(uint8_t configOp);
static FlashStigStatus FlashStigPreConfigOp(uint8_t DeviceNum);
static FlashStigStatus FlashStigPostConfigOp(uint8_t DeviceNum);
static FlashStigStatus __attribute__((used, noinline, section(".TI.ramfunc")))
FlashStigPreConfigOp_impl(uint8_t DeviceNum);
static FlashStigStatus __attribute__((used, noinline, section(".TI.ramfunc")))
FlashStigPostConfigOp_impl(uint8_t DeviceNum);
static int __attribute__((noinline, section(".TI.ramfunc"))) FlashDeviceSwitchConfigOp(uint8_t DeviceNum, bool bEnter);
static uint32_t FlashGetBound(uint8_t directionMode);
static FlashUdmaJobStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashUDMAOperationStatus(uint32_t channelSelect);
static FlashUdmaJobStatus __attribute__((noinline)) FlashPartitioningUDMATransaction(uint32_t *srcAddr,
                                                                                     uint32_t *dstAddr,
                                                                                     uint32_t lengthBytes,
                                                                                     uint8_t directionMode,
                                                                                     uint32_t channelSelect);

extern XMEMWFF3_HWAttrs XMEMWFF3_hwAttrs;

/* Temporary TCM_DRAM stack for the PS_RAM-inaccessible window.
 *
 * On CC35xx, PSRAM is accessed via the OSPI interface. When OSPI switches to target
 * a different device (Flash for STIG operations), the PSRAM address space becomes
 * inaccessible to the CPU.
 *
 * If the FreeRTOS task stack (PSP) resides in PSRAM, any function executing during
 * this window will fault immediately - not because of interrupts, but because:
 *   1. Function parameters and local variables are on the stack: any read/write via
 *      PSP causes a bus fault while PSRAM is inaccessible.
 *   2. Every nested function call does PUSH/POP to save return addresses and
 *      registers via PSP, which also faults.
 *
 * The fix: before switching OSPI away from PSRAM, detect if PSP/MSP point to PSRAM
 * and switch them to these temporary TCM_DRAM stacks. Restore the original PSP/MSP
 * after PSRAM becomes accessible again. This is done by the naked trampolines
 * FlashStigPreConfigOp (switch) and FlashStigPostConfigOp (restore).
 *
 * Both buffers are in .internalRAM (TCM_DRAM) so they remain accessible regardless
 * of OSPI state.
 */
/* __attribute__((used)) prevents "unused variable/function" warnings - these
 * symbols are only referenced from naked-trampoline inline assembly strings,
 * which the compiler does not analyse for variable/function usage.
 */
/* Stringify helper - expands a macro to a string literal for use in inline asm. */
#define _FLASH_STR(x)  #x
#define _FLASH_XSTR(x) _FLASH_STR(x)

/* PSP temp stack - used when the FreeRTOS task stack (PSP) is in PS_RAM. */
#define FLASH_TEMP_STACK_WORDS 256 /* 1024 bytes - covers full Pre-STIG-Post call depth */
uint32_t FlashWFF3_flashTempStackBuf[FLASH_TEMP_STACK_WORDS]
    __attribute__((used, section(".internalRAM.bss"), aligned(8)));

/* MSP temp stack - used when the main stack (MSP / .stack section) is in PS_RAM.
 * Protects interrupt handlers that use MSP during the OTFDE-disabled window.
 * Smaller than PSP buffer since ISR nesting depth is limited.
 */
#define FLASH_TEMP_MSP_STACK_WORDS 64 /* 256 bytes - sufficient for ISR nesting and exception frames */
uint32_t FlashWFF3_flashTempMspStackBuf[FLASH_TEMP_MSP_STACK_WORDS]
    __attribute__((used, section(".internalRAM.bss"), aligned(8)));

/* PS_RAM base address in TCM_DRAM, loaded by trampoline without PS_RAM access.
 * Derived from EXT_PSRAM_BASE (hw_memmap.h) to stay in sync with the SDK.
 * Initialized at boot time from Flash.
 */
uint32_t FlashWFF3_flashPsramBase __attribute__((used, section(".internalRAM.data"))) = EXT_PSRAM_BASE;

/* PS_RAM size, used for upper bound check in stack pointer validation.
 * Initialized at boot time from Flash. */
uint32_t FlashWFF3_flashPsramSize __attribute__((used, section(".internalRAM.data"))) = XMEM_MAX_PSRAM_SIZE;

/* Saved SP values - non-zero = switch was done and must be restored. */
uint32_t FlashWFF3_savedOriginalSP __attribute__((used, section(".internalRAM.bss")));
uint32_t FlashWFF3_savedOriginalMSP __attribute__((used, section(".internalRAM.bss")));

/* Saved stack-limit registers - cleared before switch, restored after. */
uint32_t FlashWFF3_savedOriginalPSPLIM __attribute__((used, section(".internalRAM.bss")));
uint32_t FlashWFF3_savedOriginalMSPLIM __attribute__((used, section(".internalRAM.bss")));

uint32_t FlashWFF3_savedR0toR3[4] __attribute__((used, section(".internalRAM.bss")));

/* Forward declarations - called via 'bl' in naked trampolines; mark used. */
static FlashStigStatus __attribute__((used)) FlashStigPreConfigOp_impl(uint8_t DeviceNum);
static FlashStigStatus __attribute__((used)) FlashStigPostConfigOp_impl(uint8_t DeviceNum);

uint32_t __attribute__((noinline, section(".TI.ramfunc"))) FlashIsXspiIdle()
{
    uint32_t idleXSPICoutnerBefore = 0;

    /* xSPI (accessible) idle check before STIG execution */
    while (OSPI_CONFIG_IDLE_DISABLE == (HWREG(OSPI_REGS_BASE + OSPI_O_CONFIG) & OSPI_CONFIG_IDLE_M) &&
                                        (idleXSPICoutnerBefore < OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT))
    {
        idleXSPICoutnerBefore++;
        if (idleXSPICoutnerBefore > OSPI_IDLE_XSPI_COUNTER_BEFORE_TIMEOUT)
        {
            return FLASH_TIMEOUT_REACHED_ERROR;
        }
    }

    return FLASH_STATUS_SUCCESS;
}

FlashUdmaJobStatus FlashRead(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length)
{
    FlashUdmaJobStatus status;

    /* Prevent sleep during DMA transfer */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    status = FlashPartitioningUDMATransaction(readFromAddr,
                                              writeToAddr,
                                              length,
                                              XIP_UDMA_DIRECTION_EXT_TO_INT,
                                              XIP_UDMA_SECURE_CHANNEL);

    /* Allow sleep after DMA transfer completes */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    return status;
}

FlashUdmaJobStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashWrite(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length)
{
    FlashUdmaJobStatus status;

    /* Prevent sleep during DMA transfer */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    status = FlashPartitioningUDMATransaction(readFromAddr,
                                              writeToAddr,
                                              length,
                                              XIP_UDMA_DIRECTION_INT_TO_EXT,
                                              XIP_UDMA_SECURE_CHANNEL);

    /* Allow sleep after DMA transfer completes */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    return status;
}

void __attribute__((noinline, section(".TI.ramfunc"))) FlashSetOTFDE(uint8_t setState)
{
    DebugP_assert(!((setState == FLASH_OTFDE_DISABLE) || (setState == FLASH_OTFDE_ENABLE)));

    if (setState == FLASH_OTFDE_DISABLE)
    {
        XIPDisableOTFDE();
    }
    else if (setState == FLASH_OTFDE_ENABLE)
    {
        XIPEnableOTFDE();
    }
}

/*
 * ======== FlashExecutePolling ========
 */
uint32_t __attribute__((noinline, section(".TI.ramfunc"))) FlashExecutePolling(void)
{

    uint32_t startTime        = (uint32_t)getClockPTickUs();
    uint32_t timerValMicroSec = XMEMWFF3_hwAttrs.flashType.pollingCfg.timeOut * 1000;
    int pollingCount          = 0;

    /* Check the maximum time in system ticks (microsecond) for the transaction
     to complete and Wait for command completion by polling WIP bit from flash status register */
    if (pollingCount < XMEMWFF3_hwAttrs.flashType.pollingCfg.NumOfIteration)
    {
        do
        {
            if (XMEMWFF3_hwAttrs.flashType.pollingCfg.timeOut != 0)
            {
                if (FlashClockPCheckTimeout(startTime, timerValMicroSec) != 1)
                {
                    return FLASH_TIMEOUT_REACHED_ERROR;
                }
            }

            /* Send Polling Command */
            OSPIStartSTIGCommand(XMEMWFF3_hwAttrs.flashType.pollingCfg.command);

            /* xSPI (accessible) idle check before STIG execution */
            if (FlashIsXspiIdle() != FLASH_STATUS_SUCCESS)
            {
                return FLASH_TIMEOUT_REACHED_ERROR;
            }

            /* Read Status Register */
            if (false == (OSPIGetSTIGDataRegister(OSPI_STIG_READ_DATA_LOWER) & OSPI_FLASH_STA_REG_WIP))
            {
                pollingCount++;
            }
            else
            {
                pollingCount = 0;
            }

        } while (pollingCount < XMEMWFF3_hwAttrs.flashType.pollingCfg.NumOfIteration);
    }

    return FLASH_STATUS_SUCCESS;
}

/*
 * ======== FlashExecuteReadSTIGCommand ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashExecuteReadSTIGCommand(uint32_t srcReadAddr, uint32_t *writeToAddr)
{
    FlashStigStatus status;

    /* Configure STIG address STIG execution */
    OSPISetCommandAddress(srcReadAddr);

    /* Enter STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_ENTER);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Pre STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_PRE_READ);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Execute STIG operation */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXECUTE_READ);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Processing read data */
    *writeToAddr = OSPIGetSTIGDataRegister(OSPI_STIG_READ_DATA_LOWER);

    /* Post STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_POST_READ);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Exit STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXIT);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    return FLASH_STIG_DONE;
}

/*
 * ======== FlashReadSTIG ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashReadSTIG(uint32_t readStartAddr, uint32_t *writeToAddr, uint8_t DeviceNum)
{
    FlashStigStatus status;

    /* Prepare system for STIG operations */
    status = FlashStigPreConfigOp(DeviceNum);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    /* Execute the read command */
    status = FlashExecuteReadSTIGCommand(readStartAddr, writeToAddr);

    /* Always restore system, PostConfigOp must run even on error. */
    if (FlashStigPostConfigOp(DeviceNum) != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    return status;
}

/*
 * ======== FlashExecuteEraseSTIGCommand ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashExecuteEraseSTIGCommand(uint32_t EraseAddr_en, uint32_t srcEraseAddr)
{
    FlashStigStatus status;

    /* Set start address to erase */
    if (EraseAddr_en == 1)
    {
        OSPISetCommandAddress(srcEraseAddr);
    }

    /* Enter STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_ENTER);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Pre STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_PRE_ERASE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Execute STIG operation */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXECUTE_ERASE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Post STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_POST_ERASE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Exit STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXIT);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    return FLASH_STIG_DONE;
}

/*
 * ======== FlashSectorErase ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashSectorErase(uint32_t eraseStartAddr, uint8_t DeviceNum)
{
    FlashStigStatus status;

    /* Prepare system for STIG operations */
    status = FlashStigPreConfigOp(DeviceNum);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    /* Execute the erase command */
    status = FlashExecuteEraseSTIGCommand(1, eraseStartAddr);

    /* Always restore system, PostConfigOp must run even on error to
     * switch OSPI back and restore PSRAM accessibility.
     */
    if (FlashStigPostConfigOp(DeviceNum) != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    return status;
}

/*
 * ======== FlashExecuteWriteSTIGCommandExtend ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashExecuteWriteSTIGCommand(uint32_t srcWriteData, uint32_t srcWriteAddrPhy)
{
    uint32_t status;

    /* configure STIG address and STIG Write data before Write STIG execution */
    OSPISetCommandAddress(srcWriteAddrPhy);
    HWREG(OSPI_REGS_BASE + OSPI_O_FLASH_WR_DATA_LOWER) = srcWriteData;

    /* Enter STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_ENTER);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Pre STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_PRE_WRITE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Execute STIG operation */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXECUTE_WRITE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Post STIG configuration */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_POST_WRITE);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    /* Exit STIG mode */
    status = FlashStigConfigOp(FLASH_STIG_CONFIG_EXIT);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return status;
    }

    return FLASH_STIG_DONE;
}

/*
 * ======== FlashWriteSTIG ========
 */
FlashStigStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashWriteSTIG(uint32_t *readFromAddr, uint32_t *writeToAddr, uint8_t DeviceNum)
{
    FlashStigStatus status;

    /* Prepare system for STIG operations */
    status = FlashStigPreConfigOp(DeviceNum);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    /* Execute the write command */
    status = FlashExecuteWriteSTIGCommand((uint32_t)*readFromAddr, (uint32_t)writeToAddr);

    /* Always restore system, PostConfigOp must run even on error. */
    if (FlashStigPostConfigOp(DeviceNum) != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    return status;
}

/*
 * ======== FlashSetTickPeriod ========
 */
void FlashSetTickPeriod(uint32_t TickPeriod)
{
    flashClockPTickPeriod = TickPeriod;
}

/*
 *  ======== FlashClockPCheckTimeout ========
 *
 * @brief Return indication if configurable timeout excedded.
 *
 * @param[in] StartTick The start Time from which we count #TimerInMicroSec Ticks in micro seconds,
 * if exceeds stop counting #getClockPTickUs.
 *
 * @param[in] TimerInMicroSec Configured time in micro seconds,
 * if exceeds stop counting #getClockPTickUs.
 *
 * @return bool
 * false - Timeout occur
 * true  - Timeout not occur
 *
 */
static bool __attribute__((noinline, section(".TI.ramfunc")))
FlashClockPCheckTimeout(uint32_t StartTick, uint32_t TimerInMicroSec)
{
    uint32_t currTick = getClockPTickUs();

    if ((currTick - StartTick) > TimerInMicroSec)
    {
        return false;
    }

    return true;
}

/*
 *  ======== getClockPTickUs ========
 *
 * @brief Return the current ClockP tick value.
 *
 * @return The current ClockP tick value.
 *
 * @note the global variable #flashClockPTickPeriod will be set by
 * #ClockP_getSystemTickPeriod() before entering RAM routiens.
 *
 */
static uint32_t __attribute__((noinline, section(".TI.ramfunc"))) getClockPTickUs(void)
{
    return (HWREG(SYSTIM_BASE + SYSTIM_O_TIME1U) / flashClockPTickPeriod);
}

/*
 *  ======== FlashGetBound ========
 *
 * @brief Return a bound to obtain an efficient read/write commands through UDMA.
 *
 * @param[in] directionMode XIP_UDMA_DIRECTION_INT_TO_EXT or XIP_UDMA_DIRECTION_EXT_TO_INT
 *                          INT: internal RAM
 *                          EXT: external memory
 *
 * @return Bound value in bytes.
 *
 */
static uint32_t FlashGetBound(uint8_t directionMode)
{
    /* Set resolution, in bytes */
    if (directionMode == XIP_UDMA_DIRECTION_INT_TO_EXT)
    {
        return FLASH_WR_BOUND_SIZE_IN_BYTES;
    }
    else
    {
        return FLASH_RD_BOUND_SIZE_IN_BYTES;
    }
}

/*
 *  ======== FlashUDMAOperationStatus ========
 *
 * @brief return UDMA job status.
 *
 * @param[in] channelSelect check the status of one of the two DMA channels
 * - \ref XIP_UDMA_SECURE_CHANNEL
 * - \ref XIP_UDMA_NON_SECURE_CHANNEL
 *
 * @return status FLASH_UDMA_JOB_DONE or FLASH_UDMA_JOB_ERROR
 *         after checking if UDMA job was completed.
 */
static FlashUdmaJobStatus __attribute__((noinline, section(".TI.ramfunc")))
FlashUDMAOperationStatus(uint32_t channelSelect)
{
    uint32_t jobStatus;

    while (XIPGetUDMAChannelProgressingStatus(channelSelect) == XIP_UDMA_CHANNEL_STATUS_PROGRESS) {};

    while (XIPGetUDMAChannelWordsLeft(channelSelect) != 0) {};

    jobStatus = XIPGetUDMAIrqStatus(channelSelect);
    if (jobStatus == XIP_UDMA_JOB_IRQ_STATUS_DONE)
    {
        return FLASH_UDMA_JOB_DONE;
    }
    else
    {
        return FLASH_UDMA_JOB_ERROR;
    }
}

/*
 *  ======== FlashPartitioningUDMATransaction ========
 *
 * @brief drive UDMA transaction according to write/read jobs restrictions.
 *
 * @param[in] srcAddr the start address from where to read the data
 *
 * @param[in] dstAddr the start address where to place the data
 *
 * @param[in] length number of bytes to transfer
 *
 * @param[in] directionMode XIP_UDMA_DIRECTION_INT_TO_EXT or XIP_UDMA_DIRECTION_EXT_TO_INT
 *                          INT: internal RAM
 *                          EXT: external memory
 *
 * @param[in] channelSelect one of the two DMA channels (SECURED & NON-SECURED)
 * - \ref XIP_UDMA_SECURE_CHANNEL
 * - \ref XIP_UDMA_NON_SECURE_CHANNEL
 *
 * @note use only SECURED channel see Jira: LPRFXXWARE-979
 */
static FlashUdmaJobStatus __attribute__((noinline)) FlashPartitioningUDMATransaction(uint32_t *srcAddr,
                                                                                     uint32_t *dstAddr,
                                                                                     uint32_t lengthBytes,
                                                                                     uint8_t directionMode,
                                                                                     uint32_t channelSelect)
{
    uint32_t JobStatus;
    uint32_t bound;
    uint32_t startAddr;

    if ((uint8_t)directionMode == XIP_UDMA_DIRECTION_EXT_TO_INT)
    {
        startAddr = (uint32_t)srcAddr;
    }
    else /* XIP_UDMA_DIRECTION_INT_TO_EXT */
    {
        startAddr = (uint32_t)dstAddr;
    };

    bound = FlashGetBound(directionMode); /* Bound should not equal '0'*/

    /* Calculate srcAddr offset from bound [Bytes]
     * assume bound is power of two
     */

    uint32_t sourceOffsetToGrid = startAddr & (bound - 1);

    /* AlignedJobLength in Bytes */
    uint32_t alignedJobLength = bound - sourceOffsetToGrid;

    /* Check if source address is not aligned to bound
     * and check the size to be copy is actually cross the bound
     */
    if (sourceOffsetToGrid != 0 && lengthBytes > alignedJobLength)
    {
        /* Align transaction - transact the first bytes between the source address and the followed bound
         * in order to align the original srcAddr to the bound.
         */
        JobStatus = XIPStartUDMATransaction(srcAddr, dstAddr, alignedJobLength / 4, directionMode, channelSelect);

        /* Return an error if UDMA is busy and is unable to start a new job */
        if (JobStatus != FLASH_STATUS_SUCCESS)
        {
            return FLASH_UDMA_JOB_ERROR;
        }

        if (FlashUDMAOperationStatus(channelSelect) == FLASH_UDMA_JOB_DONE)
        {
            /* Update parameters */
            srcAddr = (uint32_t *)((uint32_t)srcAddr + alignedJobLength);
            dstAddr = (uint32_t *)((uint32_t)dstAddr + alignedJobLength);
            lengthBytes -= alignedJobLength;
        }
        else
        {
            return FLASH_UDMA_JOB_ERROR;
        }
    }

    /* Transact the rest of lengthBytes (when previous align procedure has been executed)
     * or directly when original srcAddr aligned to bound.
     */
    while (lengthBytes > 0)
    {
        /* Condition for the optional last remaining bytes (when lengthBytes is not aligned to bound) */
        uint32_t transSizeBytes;
        if (lengthBytes > bound)
        {
            transSizeBytes = bound;
        }
        else
        {
            transSizeBytes = lengthBytes;
        }

        JobStatus = XIPStartUDMATransaction(srcAddr, dstAddr, transSizeBytes / 4, directionMode, channelSelect);

        /* Return an error if UDMA is busy and is unable to start a new job */
        if (JobStatus != FLASH_STATUS_SUCCESS)
        {
            return FLASH_UDMA_JOB_ERROR;
        }

        if (FlashUDMAOperationStatus(channelSelect) == FLASH_UDMA_JOB_DONE)
        {
            /* Update parameters */
            srcAddr = (uint32_t *)((uint32_t)srcAddr + transSizeBytes);
            dstAddr = (uint32_t *)((uint32_t)dstAddr + transSizeBytes);
            lengthBytes -= transSizeBytes;
        }
        else
        {
            return FLASH_UDMA_JOB_ERROR;
        }
    }

    return FLASH_UDMA_JOB_DONE;
}

/**
 * @brief Generic function to handle all STIG configuration operations
 *
 * @param configOp One of the FLASH_STIG_CONFIG_* operation types
 * @return FlashStigStatus Status of the operation
 */
static FlashStigStatus __attribute__((noinline, section(".TI.ramfunc"))) FlashStigConfigOp(uint8_t configOp)
{
    FlashStigStatus status;
    int i;
    uint32_t configEnabled         = 0;
    FlashRegister *configOperation = NULL;
    size_t operationSize           = 0;
    bool isPollingStage            = false;

    /* Select the appropriate configuration based on operation type */
    switch (configOp)
    {
        case FLASH_STIG_CONFIG_ENTER:
            configOperation = XMEMWFF3_hwAttrs.flashType.enterStigCfg;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.enterStigCfg);
            configEnabled   = 1; /* Always enabled */
            break;

        case FLASH_STIG_CONFIG_EXIT:
            configOperation = XMEMWFF3_hwAttrs.flashType.exitStigCfg;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.exitStigCfg);
            configEnabled   = 1; /* Always enabled */
            break;

        case FLASH_STIG_CONFIG_PRE_READ:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.readStigCfg.preStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.readStigCfg.preStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.readStigCfg.preStigOperation);
            break;

        case FLASH_STIG_CONFIG_EXECUTE_READ:
            configEnabled   = 1; /* Assuming always enabled for the main operation */
            configOperation = XMEMWFF3_hwAttrs.flashType.readStigCfg.stigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.readStigCfg.stigOperation);
            isPollingStage  = true;
            break;

        case FLASH_STIG_CONFIG_POST_READ:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.readStigCfg.postStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.readStigCfg.postStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.readStigCfg.postStigOperation);
            break;

        case FLASH_STIG_CONFIG_PRE_WRITE:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.writeStigCfg.preStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.writeStigCfg.preStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.writeStigCfg.preStigOperation);
            break;

        case FLASH_STIG_CONFIG_EXECUTE_WRITE:
            configEnabled   = 1; /* Assuming always enabled for the main operation */
            configOperation = XMEMWFF3_hwAttrs.flashType.writeStigCfg.stigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.writeStigCfg.stigOperation);
            isPollingStage  = true;
            break;

        case FLASH_STIG_CONFIG_POST_WRITE:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.writeStigCfg.postStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.writeStigCfg.postStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.writeStigCfg.postStigOperation);
            break;

        case FLASH_STIG_CONFIG_PRE_ERASE:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.preStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.preStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.eraseStigCfg.preStigOperation);
            break;

        case FLASH_STIG_CONFIG_EXECUTE_ERASE:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.StigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.stigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.eraseStigCfg.stigOperation);
            isPollingStage  = true;
            break;

        case FLASH_STIG_CONFIG_POST_ERASE:
            configEnabled   = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.postStigCfg;
            configOperation = XMEMWFF3_hwAttrs.flashType.eraseStigCfg.postStigOperation;
            operationSize   = sizeof(XMEMWFF3_hwAttrs.flashType.eraseStigCfg.postStigOperation);
            break;

        default:
            return FLASH_STIG_ERROR;
    }

    /* Check if configuration is needed */
    if (configEnabled)
    {
        for (i = 0; i < operationSize / sizeof(FlashRegister); i++)
        {
            if (isPollingStage && (configOperation[i].address & OSPI_O_FLASH_CMD_CTRL))
            {
                /* For Polling stage, we need to poll before command */
                status = FlashExecutePolling();
                if (status != FLASH_STATUS_SUCCESS)
                {
                    return FLASH_STIG_TIMEOUT;
                }

                OSPIStartSTIGCommand(configOperation[i].data);

                /* For Polling stage, we need to poll after command only for
                 *  write/erase and not for read
                 */
                if (configOp != FLASH_STIG_CONFIG_EXECUTE_READ)
                {
                    status = FlashExecutePolling();
                    if (status != FLASH_STATUS_SUCCESS)
                    {
                        return FLASH_STIG_TIMEOUT;
                    }
                }
            }
            else if (configOperation[i].address & OSPI_O_FLASH_CMD_CTRL)
            {
                /* xSPI (accessible) idle check before STIG execution */
                status = FlashIsXspiIdle();
                if (status != FLASH_STATUS_SUCCESS)
                {
                    return FLASH_STIG_ERROR;
                }

                /* For other stages with STIG commands */
                OSPIStartSTIGCommand(configOperation[i].data);
            }
            else
            {
                /* xSPI (accessible) idle check before STIG execution */
                status = FlashIsXspiIdle();
                if (status != FLASH_STATUS_SUCCESS)
                {
                    return FLASH_STIG_ERROR;
                }

                /* Configuration of unprotected registers */
                HWREG(configOperation[i].address) = configOperation[i].data;
            }
        }
    }

    return FLASH_STATUS_SUCCESS;
}

/*!
 *  @brief  Pre-configuration for STIG operations
 *
 *  This function prepares the flash memory system for STIG (Serial Transfer
 *  Interface Gateway) operations.
 *  It performs two critical initialization steps:
 *  1. Disables OTFDE (On-The-Fly Decryption/Encryption) to allow direct STIG
 *     command execution.
 *  2. Verifies that the xSPI interface is in an idle state and ready to accept
 *     commands.
 *
 *  @param[in] DeviceNum  Device identifier (XMEM_MEM_FLASH or XMEM_MEM_PSRAM)
 *
 *  @return FlashStigStatus FLASH_STATUS_SUCCESS if successful, FLASH_STIG_ERROR
 *          if xSPI is not idle
 */
/* FlashStigPreConfigOp - naked trampoline for stack switching before OTFDE
 * disable.
 *
 * Using __attribute__((naked)) suppresses compiler-generated prologue
 * (PUSH {LR,...}) so we can switch stack pointers BEFORE any stack operations.
 * This is critical because once OTFDE is disabled, PSRAM becomes inaccessible.
 * If the stack resides in PSRAM, any PUSH/POP would fault.
 *
 * Stack Switch Logic:
 *  - Checks both PSP (Process Stack Pointer) and MSP (Main Stack Pointer)
 *  - Only switches IF the pointer is >= FlashWFF3_flashPsramBase (i.e., in
 *    PSRAM range)
 *  - If pointer < FlashWFF3_flashPsramBase (in DRAM/TCM), leaves it unchanged
 *  - Saves original pointer values for restoration in FlashStigPostConfigOp
 *  - Sets PLIM registers to 0 to disable stack limit checking during switch
 *
 * Steps:
 *  1. Initialize FlashWFF3_savedOriginalSP and FlashWFF3_savedOriginalMSP to 0
 *     (no switch flags)
 *  2. Check PSP: if in PSRAM, save original PSP and switch to
 *     FlashWFF3_flashTempStackBuf
 *  3. Check MSP: if in PSRAM, save original MSP and switch to
 *     FlashWFF3_flashTempMspStackBuf
 *  4. Call FlashStigPreConfigOp_impl which disables OTFDE (making PSRAM
 *     inaccessible)
 *  5. Implementation performs STIG operations safely on temp stack
 *  6. Return to caller (stack restored in FlashStigPostConfigOp)
 *
 * Non-zero FlashWFF3_savedOriginalSP/MSP values act as restoration flags for
 * the post-config function.
 */
/* clang-format off */
__attribute__((naked, noinline, section(".TI.ramfunc"))) static FlashStigStatus FlashStigPreConfigOp(uint8_t DeviceNum)
{
    __asm__ volatile(

        /* Save parameters */
        "ldr  r12, =FlashWFF3_savedR0toR3          \n\t"
        "stm  r12, {r0-r3}                         \n\t"

        /* Default: no PSP/MSP switch */
        "ldr  r12, =FlashWFF3_savedOriginalSP      \n\t"
        "movs r0, #0                               \n\t"
        "str  r0, [r12]                            \n\t"

        "ldr  r12, =FlashWFF3_savedOriginalMSP     \n\t"
        "str  r0, [r12]                            \n\t"

        /*
         * Check PSP
         */
        "mrs  r0, psp                              \n\t"
        "ldr  r12, =FlashWFF3_flashPsramBase       \n\t"
        "ldr  r12, [r12]                           \n\t"
        "cmp  r0, r12                              \n\t"
        "blo  .Lskip_psp_switch                    \n\t"

        /* Check upper bound: PSP < FlashWFF3_flashPsramBase + FlashWFF3_flashPsramSize */
        "ldr  r12, =FlashWFF3_flashPsramSize       \n\t"
        "ldr  r12, [r12]                           \n\t"
        "ldr  r1, =FlashWFF3_flashPsramBase        \n\t"
        "ldr  r1, [r1]                             \n\t"
        "add  r12, r12, r1                         \n\t"
        "cmp  r0, r12                              \n\t"
        "bhs  .Lskip_psp_switch                    \n\t"

        /* PSP is in PSRAM - save and switch */
        "ldr  r12, =FlashWFF3_savedOriginalSP      \n\t"
        "str  r0, [r12]                            \n\t"

        "ldr  r12, =FlashWFF3_savedOriginalPSPLIM  \n\t"
        "mrs  r0, psplim                           \n\t"
        "str  r0, [r12]                            \n\t"

        "movs r0, #0                               \n\t"
        "msr  psplim, r0                           \n\t"

        "ldr  r12, =FlashWFF3_flashTempStackBuf    \n\t"
        "add  r12, r12, #(" _FLASH_XSTR(FLASH_TEMP_STACK_WORDS) "*4) \n\t"
        "msr  psp, r12                             \n\t"

        ".Lskip_psp_switch:                        \n\t"

        /*
         * Check MSP
         * Needed for exceptions
         */
        "mrs  r0, msp                              \n\t"
        "ldr  r12, =FlashWFF3_flashPsramBase       \n\t"
        "ldr  r12, [r12]                           \n\t"
        "cmp  r0, r12                              \n\t"
        "blo  .Lskip_msp_switch                    \n\t"

        /* Check upper bound: MSP < FlashWFF3_flashPsramBase + FlashWFF3_flashPsramSize */
        "ldr  r12, =FlashWFF3_flashPsramSize       \n\t"
        "ldr  r12, [r12]                           \n\t"
        "ldr  r1, =FlashWFF3_flashPsramBase        \n\t"
        "ldr  r1, [r1]                             \n\t"
        "add  r12, r12, r1                         \n\t"
        "cmp  r0, r12                              \n\t"
        "bhs  .Lskip_msp_switch                    \n\t"

        /* MSP is in PSRAM - save and switch */
        "ldr  r12, =FlashWFF3_savedOriginalMSP     \n\t"
        "str  r0, [r12]                            \n\t"

        "ldr  r12, =FlashWFF3_savedOriginalMSPLIM  \n\t"
        "mrs  r0, msplim                           \n\t"
        "str  r0, [r12]                            \n\t"

        "movs r0, #0                               \n\t"
        "msr  msplim, r0                           \n\t"

        "ldr  r12, =FlashWFF3_flashTempMspStackBuf \n\t"
        "add  r12, r12, #(" _FLASH_XSTR(FLASH_TEMP_MSP_STACK_WORDS) "*4) \n\t"
        "msr  msp, r12                             \n\t"

        ".Lskip_msp_switch:                        \n\t"

        /*
         * Restore parameters
         */
        "ldr  r12, =FlashWFF3_savedR0toR3          \n\t"
        "ldm  r12, {r0-r3}                         \n\t"

        /* Save caller's return address (LR) to the current stack (already switched to
         * temp stack if PSP was in PSRAM). The bl instruction below will overwrite LR,
         * and internal calls within FlashStigPreConfigOp_impl will further clobber it.
         */
        "push {lr}                                 \n\t"
        "bl   FlashStigPreConfigOp_impl            \n\t"
        "pop  {lr}                                 \n\t"
        "bx   lr                                   \n\t"

        ::
            : "r12", "memory");
}
/* clang-format on */

/* Real implementation - runs on DRAM stack, PS_RAM may be inaccessible. */
static FlashStigStatus __attribute__((noinline, section(".TI.ramfunc"))) FlashStigPreConfigOp_impl(uint8_t DeviceNum)
{
    FlashStigStatus status;

    /* OTFDE Disable - from here PS_RAM is inaccessible.
     * Stack is already on DRAM so nested calls are safe.
     * Interrupts are already disabled by the naked trampoline.
     */
    FlashSetOTFDE(FLASH_OTFDE_DISABLE);

    /* Switch OSPI to target device */
    status = FlashDeviceSwitchConfigOp(DeviceNum, true);
    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    /* xSPI idle check */
    status = FlashIsXspiIdle();
    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    return FLASH_STATUS_SUCCESS;
}

/*!
 *  @brief  Post-configuration cleanup after STIG operations
 *
 *  Mirrors FlashStigPreConfigOp but in reverse: restores OTFDE and original
 *  SP/MSP.
 *
 *  Critical ordering:
 *  1. Still running on DRAM temp stack on entry (PSP/MSP = temp if they were
 *     switched)
 *  2. Call FlashStigPostConfigOp_impl which re-enables OTFDE
 *  3. AFTER OTFDE is enabled, PSRAM becomes accessible again
 *  4. THEN restore original PSP and MSP (which may point to PSRAM)
 *  5. Restoration flags (FlashWFF3_savedOriginalSP/MSP) are checked:
 *     non-zero = restore needed
 *
 *  This ordering ensures that when we restore stacks back to PSRAM addresses,
 *  PSRAM is already accessible, avoiding any data faults during restoration.
 */
__attribute__((naked, noinline, section(".TI.ramfunc"))) static FlashStigStatus FlashStigPostConfigOp(uint8_t DeviceNum)
{
    __asm__ volatile(

        /* Save parameters */
        "ldr  r12, =FlashWFF3_savedR0toR3              \n\t"
        "stm  r12, {r0-r3}                             \n\t"

        /* Execute post configuration.
         * OTFDE is enabled inside the implementation.
         * After return PSRAM is accessible again.
         * Save LR before bl - it will be clobbered by internal calls inside the impl.
         */
        "push {lr}                                     \n\t"
        "bl   FlashStigPostConfigOp_impl               \n\t"
        "pop  {lr}                                     \n\t"

        /* Save return value - MSP/PSP restore code uses R0 as scratch */
        "ldr  r12, =FlashWFF3_savedPostConfigReturnVal \n\t"
        "str  r0, [r12]                                \n\t"

        /*
         * Restore MSP if it was switched
         */
        "ldr  r12, =FlashWFF3_savedOriginalMSP         \n\t"
        "ldr  r0, [r12]                                \n\t"
        "cbz  r0, .Lskip_msp_restore                   \n\t"

        "msr  msp, r0                                  \n\t"

        "ldr  r12, =FlashWFF3_savedOriginalMSPLIM      \n\t"
        "ldr  r0, [r12]                                \n\t"
        "msr  msplim, r0                               \n\t"

        /* Clear MSP restore flag */
        "ldr  r12, =FlashWFF3_savedOriginalMSP         \n\t"
        "movs r0, #0                                   \n\t"
        "str  r0, [r12]                                \n\t"

        ".Lskip_msp_restore:                           \n\t"

        /*
         * Restore PSP if it was switched
         */
        "ldr  r12, =FlashWFF3_savedOriginalSP          \n\t"
        "ldr  r0, [r12]                                \n\t"
        "cbz  r0, .Lskip_psp_restore                   \n\t"

        "msr  psp, r0                                  \n\t"

        "ldr  r12, =FlashWFF3_savedOriginalPSPLIM      \n\t"
        "ldr  r0, [r12]                                \n\t"
        "msr  psplim, r0                               \n\t"

        /* Clear PSP restore flag */
        "ldr  r12, =FlashWFF3_savedOriginalSP          \n\t"
        "movs r0, #0                                   \n\t"
        "str  r0, [r12]                                \n\t"

        ".Lskip_psp_restore:                           \n\t"

        /* Restore return value from .internalRAM global */
        "ldr  r12, =FlashWFF3_savedPostConfigReturnVal \n\t"
        "ldr  r0, [r12]                                \n\t"

        "bx   lr                                       \n\t"

        ::
            : "r12", "memory");
}

/* Real implementation - still on DRAM stack, re-enables OTFDE. */
static FlashStigStatus __attribute__((noinline, section(".TI.ramfunc"))) FlashStigPostConfigOp_impl(uint8_t DeviceNum)
{
    FlashStigStatus status;

    /* Switch OSPI back to active device */
    status = FlashDeviceSwitchConfigOp(DeviceNum, false);

    /* Re-enable OTFDE unconditionally - must restore PS_RAM access regardless of switch result. */
    FlashSetOTFDE(FLASH_OTFDE_ENABLE);

    if (status != FLASH_STATUS_SUCCESS)
    {
        return FLASH_STIG_ERROR;
    }

    /* Force a Flash data read to verify XIP is ready before returning to Flash-based code.
     * After OSPI switch-back and OTFDE enable, the first instruction fetch from Flash may
     * fault if the hardware hasn't fully settled.
     */
    (void)(*(volatile uint32_t *)EXT_FLASH_SEC_BASE);

    return FLASH_STATUS_SUCCESS;
}

/*!
 * @brief Configure OSPI interface by reading configuration from XIP (OTFDE) registers.
 *
 * This function configures the OSPI (Octal SPI) peripheral for a specific device
 * (Flash or PSRAM) by reading configuration data from XIP (Execute-In-Place) registers.
 * The function supports both entering and exiting device switch mode.
 *
 * XIP Register Layout:
 * --------------------
 * The configuration data is stored in [data, address] pairs starting at the base address:
 *
 * - HOST_XIP_REGS_BASE + 0x0:  First OSPI configuration data value
 * - HOST_XIP_REGS_BASE + 0x4:  First address control register
 *                              Bits [5:0]: Offset value (must be shifted left by 2 to get byte offset)
 *                              Bit  [6]:   Stop bit (1 = last configuration pair)
 *                              Bits [7]:   Reserved
 *
 * - HOST_XIP_REGS_BASE + 0x8:  Second OSPI configuration data value
 * - HOST_XIP_REGS_BASE + 0xC:  Second address control register (same format as above)
 *
 * This pattern repeats every 8 bytes until the stop bit is encountered.
 *
 * Address Calculation:
 * --------------------
 * OSPI register address = OSPI_REGS_BASE + ((offset_bits[5:0]) << 2)
 *
 * Device Selection:
 * -----------------
 * - XMEM_MEM_FLASH: XIP base = HOST_XIP_REGS_BASE + HOST_XIP_O_OTOSMEM
 * - XMEM_MEM_PSRAM: XIP base = HOST_XIP_REGS_BASE + HOST_XIP_O_OTOSMEM + PSRAM_XIP_OFFSET
 *
 * Operation Modes:
 * ----------------
 * - ENTER (true):  Configure OSPI for DeviceNum
 *                  Tracks what device OSPI is configured for
 *                  Allows nested enters - always ensures correct configuration
 * - EXIT (false):  Configure OSPI for current DeviceIsActive (read from HW)
 *                  Can be called without prior ENTER
 *
 * State Tracking:
 * ---------------
 * The function tracks the current OSPI configuration state internally:
 * - 0xFF = uninitialized (first call)
 * - 0x00 = OSPI configured for XMEM_MEM_FLASH
 * - 0x01 = OSPI configured for XMEM_MEM_PSRAM
 *
 * This allows the function to skip redundant configurations and handle
 * nested enters gracefully.
 *
 * @param[in] DeviceNum  Device identifier (XMEM_MEM_FLASH or XMEM_MEM_PSRAM)
 *                       Used only in ENTER mode, ignored in EXIT mode
 * @param[in] bEnter     Operation mode:
 *                       - true:  Enter device switch (configure TO DeviceNum)
 *                       - false: Exit device switch (configure TO current DeviceIsActive from HW)
 *
 * @return int
 *         - FLASH_STATUS_SUCCESS: Configuration completed successfully or no action needed
 *         - DEVICE_SWITCH_ERROR:  Invalid device number or OSPI not idle
 *
 * @note DeviceIsActive is ALWAYS read from hardware OTFDE status register
 * @note Multiple consecutive ENTERs are allowed - function handles them gracefully
 * @note EXIT can be called without prior ENTER
 * @note Function tracks actual OSPI configuration state internally
 *
 *
 * @example
 * // Flexible usage - nested enters allowed
 * FlashDeviceSwitchConfigOp(XMEM_MEM_FLASH, true);   // ENTER Flash
 * // ... Flash operations ...
 * FlashDeviceSwitchConfigOp(XMEM_MEM_PSRAM, true);   // ENTER PSRAM (allowed, reconfigures)
 * // ... PSRAM operations ...
 * FlashDeviceSwitchConfigOp(XMEM_MEM_PSRAM, false);  // EXIT (configure to DeviceIsActive)
 */
static int __attribute__((noinline, section(".TI.ramfunc"))) FlashDeviceSwitchConfigOp(uint8_t DeviceNum, bool bEnter)
{
    static uint8_t CurrentOSPIConfig __attribute__((section(".internalRAM.data"))) = 0xFF; // Track actual OSPI
                                                                                           // configuration (0xFF =
                                                                                           // uninitialized)
    uint8_t DeviceIsActive;
    uint8_t TargetDevice;
    uint8_t StopBit = 0;
    uint8_t status;
    uint32_t DeviceXIPBaseAddr;
    uint32_t DeviceXIPAddrOffset = 0;
    uint32_t DeviceOSPICfgAddrOffset;
    FlashRegister Register;

    /* Always read current device state from hardware OTFDE status register */
    DeviceIsActive = (HWREG(HOST_XIP_REGS_BASE + HOST_XIP_O_OTSTA) & HOST_XIP_OTSTA_TASKDEVICE) >>
                      HOST_XIP_OTSTA_TASKDEVICE_S;

    /* Determine target device based on enter/exit mode */
    if (bEnter)
    {
        /* ENTER mode: configure OSPI for DeviceNum */
        TargetDevice = DeviceNum;

        /* If OSPI is already configured for this device, do nothing */
        if (CurrentOSPIConfig == DeviceNum)
        {
            return FLASH_STATUS_SUCCESS;
        }
    }
    else
    {
        /* EXIT mode: configure OSPI for current DeviceIsActive from HW (ignore DeviceNum) */
        TargetDevice = DeviceIsActive;

        /* If OSPI is already configured for DeviceIsActive, do nothing */
        if (CurrentOSPIConfig == DeviceIsActive)
        {
            return FLASH_STATUS_SUCCESS;
        }
    }

    /* Validate target device */
    if (TargetDevice != XMEM_MEM_FLASH && TargetDevice != XMEM_MEM_PSRAM)
    {
        /* Invalid device number */
        return DEVICE_SWITCH_ERROR;
    }

    /* Determine XIP base address based on target device type */
    if (XMEM_MEM_FLASH == TargetDevice)
    {
        DeviceXIPBaseAddr = HOST_XIP_REGS_BASE + HOST_XIP_O_OTOSMEM;
    }
    else /* XMEM_MEM_PSRAM */
    {
        DeviceXIPBaseAddr = HOST_XIP_REGS_BASE + HOST_XIP_O_OTOSMEM + PSRAM_XIP_OFFSET;
    }

    /* Iterate through configuration pairs until stop bit is set */
    while (!StopBit)
    {
        /* Read 32-bit configuration data from XIP register */
        Register.data = HWREG(DeviceXIPBaseAddr + DeviceXIPAddrOffset);

        /* Read address control register */
        uint32_t addrControl = HWREG(DeviceXIPBaseAddr + DeviceXIPAddrOffset + 0x4);

        /* Extract offset value (bits [5:0]) and convert to byte offset */
        DeviceOSPICfgAddrOffset = (addrControl & 0x3F) << 2;
        Register.address        = OSPI_REGS_BASE + DeviceOSPICfgAddrOffset;

        /* Extract stop bit (bit [6]) */
        StopBit = (addrControl & 0x40) >> 6;

        /* xSPI (accessible) idle check before STIG execution */
        status = FlashIsXspiIdle();
        if (status != FLASH_STATUS_SUCCESS)
        {
            return DEVICE_SWITCH_ERROR;
        }

        /* Write configuration data to target OSPI register */
        HWREG(Register.address) = Register.data;

        /* Move to next configuration pair (8 bytes forward) */
        DeviceXIPAddrOffset += 0x8;
    }

    /* Update tracked OSPI configuration state after successful switch */
    CurrentOSPIConfig = TargetDevice;

    return FLASH_STATUS_SUCCESS;
}
