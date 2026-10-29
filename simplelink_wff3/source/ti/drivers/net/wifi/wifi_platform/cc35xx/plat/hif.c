/******************************************************************************
 *  Filename:       hif.c
 *
 *  Description:    Driver for the HIF peripheral
 *
 *  Copyright (c) 2023-2025 Texas Instruments Incorporated
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
#include "hif.h"
#include "ti/devices/cc35xx/inc/hw_soc_ic.h"
#include "ti/drivers/power/PowerWFF3.h"
#include <ti/devices/cc35xx/inc/hw_hif.h> //from driverlib
#include <ti/devices/cc35xx/inc/hw_memmap.h> //from driverlib
#include "osi_kernel.h"
#include "ti/drivers/xmem/XMEMWFF3.h" //for PSRAM access via UDMA

#define HIF_BLOCK_SIZE_BYTES          (16) // 16 this is the maximum that can be set
#define HIF_DMA_WORD_SIZE_4B_IN_BYTES (4)
#define HIF_DMA_BLOCK_SIZE_IN_WORDS   ((HIF_BLOCK_SIZE_BYTES / HIF_DMA_WORD_SIZE_4B_IN_BYTES))

// Use SDK API for PSRAM address detection instead of hardcoded range
#define IS_PSRAM_ADDR(addr)           (XMEMWFF3_addrToType((uintptr_t)(addr)) == XMEM_MEM_PSRAM)

// Maximum HIF transfer size (defines staging buffer size)
// Must be >= largest PSRAM buffer (gFwEventRxTxBuffer = 13000 bytes)
#define MAX_HIF_TRANSFER_SIZE         (16384) // 16KB staging buffer for PSRAM transfers

#define STATUS_PROCESSING (0x0)   // Processing.
#define STATUS_TRANS_DONE (0x1)   // Transaction Done.
#define STATUS_ABORT      (0x2)  // Channel Aborted by SW.
#define STATUS_EXCEPTION  (0x4) // Exception.

#define NAB_NOT_READY     (0x0)  //the nab is still processing

#define RX_DATA_SIZE_OF_RECV_RX_HEADER (16)

typedef enum
{
    HIF_MODE_DIRECT_ACCESS_WR = 0x0, // write without using DMA
    HIF_MODE_DMA_WR           = 0x1, // write using DMA
    HIF_MODE_DIRECT_ACCESS_RD = 0x2, // read without using DMA
    HIF_MODE_DMA_RD           = 0x3, // read using DMA
} HIF_MODE;

#define RD_DMA_IF_EN_WRCL (0x1)
#define HOST_CNYS_PATTERN (0xC5C5C5C5UL)
#define HOST_SYNC_PATTERN (0x5C5C5C5CUL)

#define NAB_READ_DATA_OPCODE (0x940BU)

#define ALIGN_TO_4(x) (((x) + 3) & (~3)) // Rounds up x to the nearest multiple of 4

typedef struct
{
    uint32_t syn;    // init word = HOST_SYNC_PATTERN
    uint16_t opcode; // NAB opcode, should always be NAB_READ_DATA_OPCODE
    uint16_t len;    // should be always set to 4
    uint16_t length; // number of bytes to read
    uint8_t sd;      // unused, should be always set to 0
    uint8_t flags;   // unused, should be always set to 0
} recvRxData_t;

typedef struct
{
    Power_NotifyObj HIFpostNotify;
    uint32_t dmaChannel;
    XMEM_Handle xmemHandle;      // XMEM handle for PSRAM access via UDMA
}HIFHandle_t;


HIFHandle_t HIFHandle;
int32_t HIFReadDirect(uint8_t *destStartAddr, uint16_t length);
int32_t HIFWriteDirect(uint8_t *srcStartAddr, uint16_t length);
static int HIFWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static int32_t HIFConfigure(uint32_t dmaChannel);
uint32 gHifDebugStsl,gHifDebugUnderFlow,g_HifDebugoverFlow;

// Staging buffer for HIF transfers: PSRAM <-> RAM (MUST be in RAM for SYSDMA access)
// Placed in .hif_ram section (linker places this in DRAM_NON_SECURE)
// Shared by HIFRead and HIFWrite (they don't execute simultaneously)
static uint8_t g_hif_staging_buffer[MAX_HIF_TRANSFER_SIZE] __attribute__((aligned(4), section(".internalRAM")));

#if defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize("O0")
#endif

//*****************************************************************************
//
// HIFInit
// Initialize HIF for PSRAM-aware transfers
// 1. Configure DMA Channel and HIF peripheral
// 2. Initialize XMEM driver for PSRAM access via UDMA
// 3. Register power management notification
//
//*****************************************************************************
int32_t HIFInit(uint32_t dmaChannel)
{
    XMEM_Params xmemParams;

    HIFConfigure(dmaChannel);
    HIFHandle.dmaChannel = dmaChannel;

    XMEMWFF3_init();

    xmemParams.regionBase      = 0x00000000;
    xmemParams.regionStartAddr = EXT_PSRAM_BASE;
    xmemParams.regionSize      = XMEM_MAX_PSRAM_SIZE;
    xmemParams.deviceNum       = XMEM_MEM_PSRAM;


    HIFHandle.xmemHandle = XMEMWFF3_open(&xmemParams);
    if (HIFHandle.xmemHandle == NULL)
    {
        Report("HIFInit: Failed to open XMEM handle for PSRAM access");
        return HIF_ERR_INIT_FAIL;
    }

    Power_registerNotify(&(HIFHandle.HIFpostNotify), PowerWFF3_AWAKE_SLEEP, HIFWFF3_postNotifyFxn, (uintptr_t)&HIFHandle);
    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// HIFDeinit
// 1.  Unregister from power save module
// 2.  Close XMEM handle for PSRAM access
//
//*****************************************************************************
int32_t HIFDeinit(void)
{
    Power_unregisterNotify(&(HIFHandle.HIFpostNotify));

    if (HIFHandle.xmemHandle != NULL)
    {
        XMEMWFF3_close(HIFHandle.xmemHandle);
        HIFHandle.xmemHandle = NULL;
    }

    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// HIF configure
// 1.  INIT DMA Channel
// 2.  INIT HIF
//
//*****************************************************************************
static int32_t HIFConfigure(uint32_t dmaChannel)
{
    DMAInitChannel((uint32_t)dmaChannel, DMA_PERIPH_HIF);
    DMAConfigureChannel(dmaChannel, HIF_DMA_BLOCK_SIZE_IN_WORDS, DMA_WORD_SIZE_4B, 0);
    // Configure HIF Threshold --> has to align with DMA_BLK_SIZE
    // Due to some concerns regarding the DMA_REQ indication from hif toward DMA we configure the HIF TH to 'DMA BLOCK SIZE + 1' to avoid the H race issue.
    uint32_t hifTh = HIF_DMA_BLOCK_SIZE_IN_WORDS ;
    if (hifTh >= HIF_FIFOTH_THR_M)
    {
        ASSERT_GENERAL(0);
    }
    HWREG(HIF_BASE + HIF_O_FIFOTH) = (HIF_DMA_BLOCK_SIZE_IN_WORDS)  & HIF_FIFOTH_THR_M;
    //HWREG(SOC_IC_REGS_BASE + SOC_IC_O_PRIO3) = 0x2c86295c;
    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// HIF postNotifyFxn
// 1.  after the host wake-up reconfigure the HIF
//
//*****************************************************************************
static int HIFWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    HIFHandle_t* HIFarg = (HIFHandle_t*)clientArg;

    if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        HIFConfigure(HIFarg->dmaChannel);
    }
    return Power_NOTIFYDONE; // success
}

//*****************************************************************************
//
// Read from NAB , direct read
//
//*****************************************************************************
int32_t HIFReadDirect(uint8_t *destStartAddr, uint16_t length)
{
    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }

    // Changing mode only after write FIFO is empty
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;

    while (length > 0)
    {
        // Wait for FIFO to have some data from the NAB
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

        // Read word (4 bytes)
        *((uint32_t *)(destStartAddr)) = HWREG(HIF_BASE + HIF_O_ICRDFIFO);

        destStartAddr += 4;
        length -= 4;
    }
    return HIF_STATUS_SUCCESS;
}

//*****************************************************************************
//
// HIFRead
// Read from NAB using DMA - supports PSRAM destination addresses
// Data path: HIF (from NAB) -> RAM staging buffer -> PSRAM
//
// Transfer pipeline for PSRAM destinations:
//   1. HIF -> RAM staging buffer (via SYSDMA)
//   2. RAM staging buffer -> PSRAM (via XMEM/UDMA)
//
//*****************************************************************************
int32_t HIFRead(uint32_t dmaChannel,
                uint32_t srcAddr,
                uint8_t *destStartAddr,
                uint16_t length,
                uint32_t *actualLengthRead)
{
    bool useBurstReq = 1;
    uint32_t temp;
    uint32_t offset = 0;
    volatile uint16_t lengthAfterAlignment;
    uint32_t chStatus;
    recvRxData_t recvRxData;
    uint8_t *actualDestAddr = destStartAddr;
    bool usedStagingBuffer = false;

    // **Check if destination address is in PSRAM**
    if (IS_PSRAM_ADDR(destStartAddr))
    {
        // Verify staging buffer can hold the data
        if (length > MAX_HIF_TRANSFER_SIZE)
        {
            return HIF_ERR_BUFFER_TOO_LARGE;
        }

        // Use staging buffer as destination for SYSDMA
        actualDestAddr = g_hif_staging_buffer;
        usedStagingBuffer = true;
    }

    // Wait until fifo is empty
    while (!((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

    // Change mode to write
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_WR;

    if (srcAddr == HIF_NAB_DATA_ADDR)
    {
        if (length < 16)
        {
            // Minimum length to read is 16 bytes (NAB_header_t is not included in the length)
            return HIF_ERR_BUFFER_OVERFLOW;
        }
        recvRxData.syn    = HOST_SYNC_PATTERN;
        recvRxData.opcode = NAB_READ_DATA_OPCODE;
        recvRxData.len    = 4;
        recvRxData.length = length - RX_DATA_SIZE_OF_RECV_RX_HEADER; // It includes all bytes that comes after the
                                                                     // descriptor word
        recvRxData.sd     = 0;
        recvRxData.flags  = 0;

        // Request for Rx data
        if (HIFWriteDirect((uint8_t *)&recvRxData, sizeof(recvRxData)) != HIF_STATUS_SUCCESS)
        {
            return HIF_ERR_WRITE_FAIL; // dma write failure
        }

        lengthAfterAlignment = length;
        *actualLengthRead    = length;

        // Changing mode only after write FIFO is empty
        HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;

        // Wait until read FIFO is not empty, i.e the NAB set data on the read FIFO
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
    }
    else if (srcAddr == HIF_NAB_CONTROL_ADDR)
    {
        // Wait until write FIFO is not full
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

        // Write 32-bit word to the event mailbox
        HWREG(HIF_BASE + HIF_O_ICWRFIFO) = HOST_CNYS_PATTERN;

        // Changing mode only after write FIFO is empty
        HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;
        // Wait until read FIFO is not empty
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
        // Read first word (4 bytes) - use actualDestAddr
        temp                                    = HWREG(HIF_BASE + HIF_O_ICRDFIFO);
        *((uint32_t *)(actualDestAddr + offset)) = temp;
        offset += 4;

        // Wait until read FIFO is not empty
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
        // read second word (4 bytes) - use actualDestAddr
        temp                                    = HWREG(HIF_BASE + HIF_O_ICRDFIFO);
        *((uint32_t *)(actualDestAddr + offset)) = temp;
        // Read what is the actual number of bytes that the NAB has to send
        *actualLengthRead                       = (temp >> 16) & 0xFFFF;
        offset += 4;

        if ((ALIGN_TO_4(*actualLengthRead) + 4 /*header*/) > length) // verify that there is no overflow
        {
            return HIF_ERR_BUFFER_OVERFLOW;
        }
        lengthAfterAlignment = (uint16_t)ALIGN_TO_4((*actualLengthRead));
    }
    else
    {
        return HIF_ERR_INVALID_SRC_ADDR; // src address not supported
    }

    // **Stage 1: HIF -> RAM staging buffer (via SYSDMA)**
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DMA_RD;

    DMAConfigureChannelFlags(dmaChannel, DMA_CONFIG_SRC_PTR_FIFO);
    DMAStartTransaction(dmaChannel,
                        (uint32_t *)(HIF_BASE + HIF_O_ICRDFIFO),
                        (uint32_t *)((uint8_t *)actualDestAddr + offset),
                        lengthAfterAlignment,
                        useBurstReq);

    // Wait for SYSDMA transaction to finish
    while ((chStatus = DMAGetChannelStatus(dmaChannel)) == STATUS_PROCESSING) {};
    if (chStatus & (STATUS_ABORT | STATUS_EXCEPTION))
    {
        uint32_t  hifstat = HWREG(HIF_BASE + HIF_O_FIFOSTA);
        uint32_t  hifmod = HWREG(HIF_BASE + HIF_O_MOD);
        Report("chStatus error! status 0x%x, channel 0x%x, hifmod: 0x%x hif status: 0x%x",
               chStatus, dmaChannel, hifmod, hifstat);
        ASSERT_GENERAL(0);
        return HIF_ERR_DMA_READ_FAIL;
    }

#ifdef REMOVE_HIF_READ_DELAY
    while((HWREG(HIF_BASE + HIF_O_NABRDY) & HIF_NABRDY_RCVDONE) == NAB_NOT_READY) {};
    __asm__ __volatile__( "nop" );
    __asm__ __volatile__( "nop" );
#endif

    // **If destination is PSRAM, copy staging buffer -> PSRAM via XMEM**
    if (usedStagingBuffer)
    {
        // **Stage 2: RAM staging buffer -> PSRAM (via XMEM/UDMA)**
        // Write only the bytes actually received: the 8-byte header written
        // directly (offset) plus the DMA payload (lengthAfterAlignment).
        // Using the caller's 'length' here would write stale staging-buffer
        // bytes beyond the real payload when the caller passes an oversized buffer.
        size_t psramOffset = XMEMWFF3_addrToOffset((uintptr_t)destStartAddr);
        int_fast16_t xmemStatus = XMEMWFF3_write(HIFHandle.xmemHandle,
                                                  psramOffset,
                                                  g_hif_staging_buffer,  // Source is RAM staging buffer
                                                  offset + lengthAfterAlignment,
                                                  XMEM_WRITE);

        if (xmemStatus != XMEM_STATUS_SUCCESS)
        {
            Report(">>> HIFRead: ERROR - XMEM write to PSRAM failed, status=%d, offset=0x%x, length=%d",
                   xmemStatus, psramOffset, offset + lengthAfterAlignment);
            return HIF_ERR_PSRAM_WRITE_FAIL;
        }
    }

    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// Write to the NAB
//
//*****************************************************************************
int32_t HIFWriteDirect(uint8_t *srcStartAddr, uint16_t length)
{
    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }
    //Wait untill fifo is empty
    while (!((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_WR;
    while (length > 0)
    {
        // Wait until FIFO is not full
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};
        // event mailbox
        HWREG(HIF_BASE) = (uint32_t)(*((uint32_t *)srcStartAddr));

        srcStartAddr += 4;
        length -= 4;
    }
    // Wait until FIFO is not full
    while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// HIFWrite
// Write to NAB using DMA - supports PSRAM source addresses
// Data path: PSRAM -> RAM staging buffer -> HIF (to NAB)
//
// Transfer pipeline for PSRAM sources:
//   1. PSRAM -> RAM staging buffer (via XMEM/UDMA)
//   2. RAM staging buffer -> HIF (via SYSDMA)
//
//*****************************************************************************
int32_t HIFWrite(uint32_t dmaChannel, uint8_t *srcStartAddr, uint16_t length)
{
    bool useBurstReq = 1;
    uint32_t chStatus;
    uint8_t *actualSrcAddr = srcStartAddr;

    // Alignment check
    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }

    // **Check if source address is in PSRAM**
    if (IS_PSRAM_ADDR(srcStartAddr))
    {
        // Verify staging buffer size
        if (length > MAX_HIF_TRANSFER_SIZE)
        {
            return HIF_ERR_BUFFER_TOO_LARGE;
        }

        // **Stage 1: PSRAM -> RAM staging buffer (via XMEM/UDMA)**
        size_t psramOffset = XMEMWFF3_addrToOffset((uintptr_t)srcStartAddr);
        int_fast16_t xmemStatus = XMEMWFF3_read(HIFHandle.xmemHandle,
                                                 psramOffset,
                                                 g_hif_staging_buffer,
                                                 length,
                                                 XMEM_READ);

        if (xmemStatus != XMEM_STATUS_SUCCESS)
        {
            Report("HIFWrite: XMEM read from PSRAM failed, status=%d, offset=0x%x, length=%d",
                   xmemStatus, psramOffset, length);
            return HIF_ERR_PSRAM_READ_FAIL;
        }

        // Use staging buffer as source for SYSDMA
        actualSrcAddr = g_hif_staging_buffer;
    }

    // **Stage 2: RAM -> HIF (via SYSDMA)**

    // Wait until fifo is empty
    while (!((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DMA_WR;

    // Wait until FIFO is not full (commented out in original)
    //while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

    DMAConfigureChannelFlags(dmaChannel, DMA_CONFIG_DST_PTR_FIFO);

    DMAStartTransaction(dmaChannel,
                        (uint32_t *)actualSrcAddr,  // Use actualSrcAddr (may be staging buffer)
                        (uint32_t *)(HIF_BASE + HIF_O_ICWRFIFO),
                        length,
                        useBurstReq);

    // Wait for the DMA transaction to finish
    while ((chStatus = DMAGetChannelStatus(dmaChannel)) == STATUS_PROCESSING) {};
    if (chStatus & (STATUS_ABORT | STATUS_EXCEPTION)) // this is fatal error and should not happen
    {
        uint32_t  hifstat = HWREG(HIF_BASE + HIF_O_FIFOSTA);
        uint32_t  hifmod = HWREG(HIF_BASE + HIF_O_MOD);
        Report("chStatus error! status 0x%x, channel 0x%x, hifmod: 0x%x hif status: 0x%x",
               chStatus, dmaChannel, hifmod, hifstat);
        ASSERT_GENERAL(0);
        return HIF_ERR_DMA_WRITE_FAIL;
    }
    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// Wait for fifo to be empty before switching to mode 0 - idle
//
//*****************************************************************************
void HIFSetIdle(void)
{
    //Wait untill fifo is empty
    while (!((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

    HWREG(HIF_BASE+HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_WR; //HIF_MODE_DIRECT_ACCESS_WR - set IDLE mode
}

void HIFCollectDebugInfo(void)
{
    //collect values for debug purpose
    gHifDebugStsl = HWREG32(HIF_BASE+HIF_O_FIFOSTA);
    gHifDebugUnderFlow = HWREG32(HIF_BASE+HIF_O_UNDER);
    g_HifDebugoverFlow = HWREG32(HIF_BASE+HIF_O_OVER);
}



#if defined(__GNUC__)
    #pragma GCC pop_options
#endif
