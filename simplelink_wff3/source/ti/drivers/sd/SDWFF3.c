/*
 * Copyright (c) 2025, Texas Instruments Incorporated
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

/*
 *  ======== SDWFF3.c ========
 */

#include <stdbool.h>

#include <ti/drivers/sd/SDWFF3.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/dma/DMAWFF3.h>
#include <ti/drivers/GPIO.h>

/* ========================================================================== */
/*                          Local Defines                                     */
/* ========================================================================== */

/* Ceiling division macro: returns ceil(x/y) for positive integers.
 * Adds (y-1) to numerator to force rounding up instead of truncation. */
#define CEIL_DIV(x, y) (((x) + (y)-1) / (y))

/** sleep cycles calculators */
/*
 * POWER_UP_TIME - From SD Physical Layer spec, after power is applied to the SD card
 *                 the host must wait at least 100 card clock cycles.
 * The card clock frequency defined by sysconfig so lets take the worth case, 100ns.
 */
#define CARD_CLK_PER_NS 100
/*
 * POWER_UP_TIME = (num_of_cycles * CARD_CLK_PER_NS) / NS_IN_US
 */
#define POWER_UP_TIME   CEIL_DIV((100 * CARD_CLK_PER_NS), 1000)

/*
 * ACMD41 - It recommended from SD spec to send ACMD41 100 times with 10us delay
 * between each command
 */
#define ACMD41_RETRY 100
#define ACMD41_sleep 10

/*
 * FIFO_WR_DELAY - From verification sequence delay need to be added between writing block to the FIFO
 */
#define FIFO_WR_DELAY CEIL_DIV((100 * CARD_CLK_PER_NS), 1000)

/*
 * WP_CD_DELAY - Write protect and card detect indication sampled by slow clock (32KHz)
 *               Those indications go throw a synchronizer and filter.
 * After changing the polarity of WP and CD need to add 8 slow clock cycles delay for stability.
 */
#define SLOW_CLK_PER_NS 31250
/*
 * WP_CD_DELAY = (num_of_cycles * SLOW_CLK_PER_NS) / NS_IN_US
 */
#define WP_CD_DELAY     CEIL_DIV((8 * SLOW_CLK_PER_NS), 1000)

#define SDWFF3_REG_IS_WR_ONLY 1
#define SDWFF3_REG_ENABLE     1
#define SDWFF3_REG_DISABLE    0

#define SDWFF3_CARD_VOL_3P3 7

/** \brief SD Commands enumeration. */
#define SDWFF3_CMD(x) (x)

/** \brief Bit mask. */
#define BIT(x) (((uint32_t)1U) << (x))

#define ENABLE_SD_CARD_CLK  true
#define DISABLE_SD_CARD_CLK false

/**
 * Command/Response flags for notifying some information to controller
 */

/** \brief To indicate no response. */
#define SDWFF3_CMDRSP_NONE (0U)

/** \brief Command to configure for 136 bits data width. */
#define SDWFF3_CMDRSP_136BITS (1U)

/** \brief Command to configure for 48bit R1 response */
#define SDWFF3_CMDRSP_48BITS (2U)

/** \brief Response to indicate busy state. */
#define SDWFF3_CMDRSP_BUSY (3U)

/** \brief Temporary define before card is classified */
#define CARD_UNKNOWEN_YET ((uint32_t)0x3)

/** \brief SD voltage enumeration as per VHS field, after the CHECK PATTERN FIELD */
#define SDWFF3_VOLT_2P7_3P6 (0x00000100U)

/** \brief Check pattern for command 8 */
#define SDWFF3_CMD_CHECK_PATTERN (0x000000AAU)

/** \brief Interrupt Index mask, used for mask all interrupts */
#define SDWFF3_INTR_ALL (0xFFFFFFFFU)

/** \brief Wildcard to configure for VDD level */
#define SDWFF3_OCR_VDD_WILDCARD  (((uint32_t)0x1FFU) << 15U)
#define SDWFF3_OCR_HIGH_CAPACITY (BIT(30U))

#define SDWFF3_HIGH_CAPACITY ((uint32_t)0x40000000)
#define SDWFF3_STD_CAPACITY  ((uint32_t)0x00000000)

#define SDIO_CMD0TIMEOUT ((uint32_t)0x00002710)

#define SDWFF3_DATATIMEOUT ((uint32_t)0x0000FFFF)

#define SDWFF3_CARD_TRANS_STATE ((uint32_t)0x00000004)

#define SDWFF3_SECTOR_SIZE (512)

/*---------------------------------STATUS DEF---------------------------*/
#define SDWFF3_STATUS_CMD_COMPLETE     (BIT(0U))
#define SDWFF3_STATUS_TRANS_COMPLETE   (BIT(1U))
#define SDWFF3_STATUS_BLK_GAP_COMP     (BIT(2U))
#define SDWFF3_STATUS_DMA_INTR         (BIT(3U))
#define SDWFF3_STATUS_BUFF_WR_RDY      (BIT(4U))
#define SDWFF3_STATUS_BUFF_RD_RDY      (BIT(5U))
#define SDWFF3_STATUS_CARD_INS         (BIT(6U))
#define SDWFF3_STATUS_CARD_REM         (BIT(7U))
#define SDWFF3_STATUS_CARD_INTR        (BIT(8U))
#define SDWFF3_STATUS_OBI_STAT         (BIT(9U))
#define SDWFF3_STATUS_ERR_INTR         (BIT(15U))
#define SDWFF3_STATUS_CMD_TIMEOUT_ERR  (BIT(16U))
#define SDWFF3_STATUS_CMD_CRC_ERR      (BIT(17U))
#define SDWFF3_STATUS_CMD_END_BIT_ERR  (BIT(18U))
#define SDWFF3_STATUS_CMD_IDX_ERR      (BIT(19U))
#define SDWFF3_STATUS_DATA_TIMEOUT_ERR (BIT(20U))
#define SDWFF3_STATUS_DATA_CRC_ERR     (BIT(21U))
#define SDWFF3_STATUS_DATA_END_BIT_ERR (BIT(22U))
#define SDWFF3_STATUS_CMD12_ERR        (BIT(24U))
#define SDWFF3_STATUS_CARD_ERR         (BIT(28U))
#define SDWFF3_STATUS_BAD_ACCESS_ERR   (BIT(29U))
#define SDWFF3_STATUS_ALL_ERRORS       ((uint32_t)0xFFFFFF3F)

/* Mask for errors Card Status R1 (OCR Register) */
#define SDWFF3_OCR_ADDR_OUT_OF_RANGE     ((uint32_t)0x80000000)
#define SDWFF3_OCR_ADDR_MISALIGNED       ((uint32_t)0x40000000)
#define SDWFF3_OCR_BLOCK_LEN_ERR         ((uint32_t)0x20000000)
#define SDWFF3_OCR_ERASE_SEQ_ERR         ((uint32_t)0x10000000)
#define SDWFF3_OCR_BAD_ERASE_PARAM       ((uint32_t)0x08000000)
#define SDWFF3_OCR_WRITE_PROT_VIOLATION  ((uint32_t)0x04000000)
#define SDWFF3_OCR_LOCK_UNLOCK_FAILED    ((uint32_t)0x01000000)
#define SDWFF3_OCR_COM_CRC_FAILED        ((uint32_t)0x00800000)
#define SDWFF3_OCR_ILLEGAL_CMD           ((uint32_t)0x00400000)
#define SDWFF3_OCR_CARD_ECC_FAILED       ((uint32_t)0x00200000)
#define SDWFF3_OCR_CC_ERROR              ((uint32_t)0x00100000)
#define SDWFF3_OCR_GENERAL_UNKNOWN_ERROR ((uint32_t)0x00080000)
#define SDWFF3_OCR_STREAM_READ_UNDERRUN  ((uint32_t)0x00040000)
#define SDWFF3_OCR_STREAM_WRITE_OVERRUN  ((uint32_t)0x00020000)
#define SDWFF3_OCR_CID_CSD_OVERWRIETE    ((uint32_t)0x00010000)
#define SDWFF3_OCR_WP_ERASE_SKIP         ((uint32_t)0x00008000)
#define SDWFF3_OCR_CARD_ECC_DISABLED     ((uint32_t)0x00004000)
#define SDWFF3_OCR_ERASE_RESET           ((uint32_t)0x00002000)
#define SDWFF3_OCR_AKE_SEQ_ERROR         ((uint32_t)0x00000008)
#define SDWFF3_OCR_ERRORBITS             ((uint32_t)0xFDFFE008)

/* Masks for R6 Response */
#define SDWFF3_R6_GENERAL_UNKNOWN_ERROR ((uint32_t)0x00002000)
#define SDWFF3_R6_ILLEGAL_CMD           ((uint32_t)0x00004000)
#define SDWFF3_R6_COM_CRC_FAILED        ((uint32_t)0x00008000)

#define SDWFF3_ALLZERO ((uint32_t)0x00000000)

#define SDWFF3_BUSWIDTH_1B ((uint32_t)0x00000000)
#define SDWFF3_BUSWIDTH_4B ((uint32_t)0x00000001)

/* ========================================================================== */
/*                          Local Enum Declaration                            */
/* ========================================================================== */
typedef enum
{
    /* SDIO specific error defines */
    SDWFF3_CMD_CRC_FAIL,    /* Command response received (but CRC check failed) */
    SDWFF3_CMD_RSP_TIMEOUT, /* Command response timeout */
    SDWFF3_ADDR_MISALIGNED, /* Misaligned address */
    SDWFF3_BLOCK_LEN_ERR,   /* Transferred block length is not allowed for the card or the number of transferred bytes
                               does not match the block length */
    SDWFF3_ERASE_SEQ_ERR,   /* An error in the sequence of erase command occurs.*/
    SDWFF3_BAD_ERASE_PARAM, /* An Invalid selection for erase groups */
    SDWFF3_WRITE_PROT_VIOLATION,  /* Attempt to program a write protect block */
    SDWFF3_LOCK_UNLOCK_FAILED,    /* Sequence or password error has been detected in unlock command or if there was an
                                     attempt to access a locked card */
    SDWFF3_COM_CRC_FAILED,        /* CRC check of the previous command failed */
    SDWFF3_ILLEGAL_CMD,           /* Command is not legal for the card state */
    SDWFF3_CARD_ECC_FAILED,       /* Card internal ECC was applied but failed to correct the data */
    SDWFF3_CC_ERROR,              /* Internal card controller error */
    SDWFF3_GENERAL_UNKNOWN_ERROR, /* General or Unknown error */
    SDWFF3_STREAM_READ_UNDERRUN,  /* The card could not sustain data transfer in stream read operation. */
    SDWFF3_STREAM_WRITE_OVERRUN,  /* The card could not sustain data programming in stream mode */
    SDWFF3_CID_CSD_OVERWRITE,     /* CID/CSD overwrite error */
    SDWFF3_WP_ERASE_SKIP,         /* only partial address space was erased */
    SDWFF3_CARD_ECC_DISABLED,     /* Command has been executed without using internal ECC */
    SDWFF3_ERASE_RESET,   /* Erase sequence was cleared before executing because an out of erase sequence command was
                             received */
    SDWFF3_AKE_SEQ_ERROR, /* Error in sequence of authentication. */
    SDWFF3_INVALID_VOLTRANGE,
    SDWFF3_ADDR_OUT_OF_RANGE,
    SDWFF3_SUPPORT_1D_ONLY,
    SDWFF3_DOESNT_SUPPORT_HS,

    /* Standard error defines */
    SDWFF3_UNSUPPORTED_CARD,
    SDWFF3_ERROR,
    SDWFF3_OK,
} SDWFF3_Status;

/* ========================================================================== */
/*                          Local Structure Declaration                       */
/* ========================================================================== */

typedef struct
{
    uint32_t dma_enable;
    uint32_t blk_cnt_en;
    uint32_t multi_block;
    uint32_t auto_cmd_en;
    uint32_t data_dir;
    uint32_t resp_type;
    uint32_t data_present;
    uint32_t cdm_index;
} SDWFF3_cmdParams;

/* ========================================================================== */
/*                   SD function table for SDWFF3                             */
/* ========================================================================== */
const SD_FxnTable SDWFF3_fxnTable = {SDWFF3_close,
                                     SDWFF3_control,
                                     SDWFF3_getNumSectors,
                                     SDWFF3_getSectorSize,
                                     SDWFF3_init,
                                     SDWFF3_initialize,
                                     SDWFF3_open,
                                     SDWFF3_read,
                                     SDWFF3_write};

/* ========================================================================== */
/*                          Global Variable                                   */
/* ========================================================================== */

SDWFF3_cmdParams *trans_cmd;
uint32_t cmd_resp[4];

Power_NotifyObj SDWFF3_NotifyObj;
SDWFF3_Object *SDWFF3_object_P;
SDWFF3_HwAttrs *SDWFF3_hwAttrs_P;
SD_Handle SDWFF3_handle;
SDWFF3_Param *SDWFF3_param;

/*! Semaphore handle for DMA operation */
SemaphoreP_Handle sdSemaphore;

/* ========================================================================== */
/*                          Local Function Prototypes                         */
/* ========================================================================== */
static void SDWFF3_setBusSpeed(uint32_t clkDiv, bool outputHigh);
static SDWFF3_Status SDWFF3_setBusWidth(SDWFF3_Object *object, uint32_t bus_width);
static SDWFF3_Status SDWFF3_writeFifo(SDWFF3_Object *object,
                                      uint32_t numBlks,
                                      uint32_t *data_point,
                                      bool dma_operation);
static SDWFF3_Status SDWFF3_readFifo(SDWFF3_Object *object, uint32_t numBlks, uint32_t *data_point, bool dma_operation);
static SDWFF3_Status SDWFF3_prepareCardWrite(SDWFF3_Object *object,
                                             int_fast32_t sector,
                                             uint_fast32_t secCount,
                                             bool dma_operation);
static SDWFF3_Status SDWFF3_prepareCardRead(SDWFF3_Object *object,
                                            uint32_t startBlk,
                                            uint32_t numBlks,
                                            bool dma_operation);
static SDWFF3_Status SDWFF3_initSD(SDWFF3_Object *object);
static void SDWFF3_openCardClk(bool clk_open);
static void SDWFF3_configIomux(void);
static void SDWFF3_clearCmdVar(void);
static void SDWFF3_writeProtect(SDWFF3_Object *object);
static void SDWFF3_cardDetect(SDWFF3_Object *object);
static void SDWFF3_initHost(void);
static void SDWFF3_initParam(SDWFF3_Object *object);
static void SDWFF3_sendCommand(uint32_t cmd_arg);
static void SDWFF3_readResp(uint32_t resp_type);
static void SDWFF3_statEn(uint32_t intrIdx);
static void SDWFF3_intrEn(uint32_t intrIdx);
static void SDWFF3_intrDis(uint32_t intrIdx);
static void SDWFF3_statusClear(uint32_t statusBits);
static SDWFF3_Status SDWFF3_CmdResp7Error(void);
static SDWFF3_Status SDWFF3_CmdResp1Error(uint8_t cmd);
static SDWFF3_Status SDWFF3_PowerON(SDWFF3_Object *object);
static SDWFF3_Status SDWFF3_CmdResp3Error(void);
static SDWFF3_Status SDWFF3_InitializeCards(SDWFF3_Object *object);
static SDWFF3_Status SDWFF3_CmdResp2Error(void);
static SDWFF3_Status SDWFF3_CmdResp6Error(SDWFF3_Object *object);
static void SDWFF3_GetCardInfo(SDWFF3_Object *object);
static SDWFF3_Status SDWFF3_SelectDeselect(SDWFF3_Object *object);
static SDWFF3_Status SDWFF3_FindSCR(SDWFF3_Object *object);
static void SDWFF3_SetBLKsize(uint32_t blk_len);
static void SDWFF3_SetNumBLK(uint32_t num_blk);
static uint32_t SDWFF3_readStatusReg(void);
static SDWFF3_Status SDWFF3_CmdError(void);
static void SDWFF3HwipFxn(uintptr_t arg);
static int SDWFF3_notifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static void SDWFF3_overrideIomux(void);
static void SDWFF3_sleep(void);
static void SDWFF3_wakeup(void);
static void SDWFF3_SoftReset(void);
static void SDWFF3_CDandWP(SDWFF3_Object *object);
static void SDWFF3_prepareIpForInit(void);
static SDWFF3_Status SDWFF3_IsCardProgramming(SDWFF3_Object *object, uint8_t *pstatus);
static SDWFF3_Status SDWFF3_setHighSpeedMode();

/* ========================================================================== */
/*                          API Implementation                                   */
/* ========================================================================== */

/*
 *  ======== SDWFF3_init ========
 */
void SDWFF3_init(SD_Handle handle)
{
    uintptr_t clientArg_temp = (uintptr_t)NULL;
    SDWFF3_handle            = handle;
    SDWFF3_hwAttrs_P         = (SDWFF3_HwAttrs *)handle->hwAttrs;
    SDWFF3_object_P          = (SDWFF3_Object *)handle->object;

    SDWFF3_initParam(SDWFF3_object_P);

    /* Init parameters for interrupts handler */
    HwiP_Params_init(&(SDWFF3_object_P->SDhwiPrms));
    SDWFF3_object_P->SDhwiPrms.priority = SDWFF3_hwAttrs_P->intPriority;

    /*
     * Register to be called when Host goes to sleep and wake-up
     * SDWFF3_notifyFxn function will be called
     */
    Power_registerNotify(&(SDWFF3_NotifyObj),
                         PowerWFF3_ENTERING_SLEEP | PowerWFF3_AWAKE_SLEEP,
                         SDWFF3_notifyFxn,
                         clientArg_temp);
}

/*
 *  ======== SDWFF3_open ========
 */
SD_Handle SDWFF3_open(SD_Handle handle, SD_Params *params)
{
    SDWFF3_param     = (SDWFF3_Param *)params;
    SDWFF3_hwAttrs_P = (SDWFF3_HwAttrs *)handle->hwAttrs;
    SDWFF3_object_P  = (SDWFF3_Object *)handle->object;
    uintptr_t key;

    if (SDWFF3_param != NULL)
    {
        /*
         * Application Call-Back function
         * SDWFF3CallbackFxn will be call for each event form enum 'Event_Type'
         */
        if (SDWFF3_param->SDWFF3CallbackFxn != NULL)
        {
            SDWFF3_object_P->SDWFF3_CB_function = SDWFF3_param->SDWFF3CallbackFxn;
        }
        else
        {
            SDWFF3_object_P->SDWFF3_CB_function = NULL;
        }

        /*
         * minDmaTransferSize define the threshold for transferring data
         * If the number of blocks is bigger than minDmaTransferSize
         * Then DMA will be active
         * Else read and write will apply with Core M33 only
         */
        if (SDWFF3_param->minDmaTransferSize > 0)
        {
            SDWFF3_object_P->SDminDmaTransferSize = SDWFF3_param->minDmaTransferSize;
        }
        else
        {
            SDWFF3_object_P->SDminDmaTransferSize = 0;
        }
    }
    else
    {
        SDWFF3_object_P->SDWFF3_CB_function   = NULL;
        SDWFF3_object_P->SDminDmaTransferSize = 0;
    }

    /*
     * SDWFF3_init() must be called before SDWFF3_open()
     */
    key = HwiP_disable();

    if (SDWFF3_object_P->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }
    SDWFF3_object_P->isOpen = true;

    HwiP_restore(key);

    /*
     * Create a semaphore to block task execution for the duration of the
     * SD transfer in DMA operation
     */
    sdSemaphore = SemaphoreP_createBinary(0);
    /* Enable the clock of SDWFF3 hardware module */
    Power_setDependency(SDWFF3_hwAttrs_P->powerID);

    /* Initialize the SDWFF3 hardware module */
    SDWFF3_initHost();

    /* Configure selected GPIO pins */
    SDWFF3_configIomux();

    /* Check if the card is connected and whether the card is write protected */
    SDWFF3_CDandWP(SDWFF3_object_P);

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
    HwiP_construct(&(SDWFF3_object_P->SDhwiStruct),
                   SDWFF3_hwAttrs_P->intNum,
                   SDWFF3HwipFxn,
                   &(SDWFF3_object_P->SDhwiPrms));

    return SDWFF3_handle;
}

/*
 *  ======== SDWFF3_close ========
 */
void SDWFF3_close(SD_Handle handle)
{
    SDWFF3_hwAttrs_P = (SDWFF3_HwAttrs *)handle->hwAttrs;

    HwiP_destruct(&(SDWFF3_object_P->SDhwiStruct));

    SemaphoreP_delete(sdSemaphore);

    SDWFF3_overrideIomux();

    Power_releaseDependency(SDWFF3_hwAttrs_P->powerID);

    SDWFF3_object_P->isOpen   = false;
    SDWFF3_object_P->cardType = SD_NOCARD;
}

/*
 *  ======== SDWFF3_initialize ========
 */
int_fast16_t SDWFF3_initialize(SD_Handle handle)
{

    SDWFF3_Status errorstatus = SDWFF3_OK;
    SDWFF3_object_P           = (SDWFF3_Object *)handle->object;

    /*
     * SDWFF3_open() must be called before SDWFF3_initialize()
     */
    if (!(SDWFF3_object_P->isOpen))
    {
        return (SD_STATUS_ERROR);
    }

    /*
     * Card can't be initialized if it not connected
     */
    if (!(SDWFF3_object_P->card_inserted))
    {
        return (SD_STATUS_ERROR);
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    errorstatus = SDWFF3_initSD(SDWFF3_object_P);

    if (SDWFF3_hwAttrs_P->numData == 4)
    {
        /*
         * Configure card to use 4 data lines if define
         */
        if (errorstatus == SDWFF3_OK)
        {
            errorstatus = SDWFF3_setBusWidth(SDWFF3_object_P, SDWFF3_BUSWIDTH_4B);
        }
    }

    if ((errorstatus == SDWFF3_OK) || (errorstatus == SDWFF3_SUPPORT_1D_ONLY))
    {
        if (SDWFF3_hwAttrs_P->divClk == 0)
        {
            errorstatus = SDWFF3_setHighSpeedMode();
        }

        SDWFF3_setBusSpeed(SDWFF3_hwAttrs_P->divClk, false);
    }

    SDWFF3_openCardClk(DISABLE_SD_CARD_CLK);
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    /*
     * Check if the initialization of the card works correctly
     * If so, 'errorstatus' expected be 'SDWFF3_OK'
     */
    if (errorstatus != SDWFF3_OK)
    {
        return SD_STATUS_ERROR;
    }

    SDWFF3_object_P->cardInitiated = true;

    return SD_STATUS_SUCCESS;
}

/*
 *  ======== SDWFF3_write ========
 */
int_fast16_t SDWFF3_write(SD_Handle handle, const void *buf, int_fast32_t sector, uint_fast32_t secCount)
{
    SDWFF3_object_P  = (SDWFF3_Object *)handle->object;
    SDWFF3_hwAttrs_P = (SDWFF3_HwAttrs *)handle->hwAttrs;

    SDWFF3_Status errorstatus = SDWFF3_OK;

    /*
     * SDWFF3_initialize() must be called before SDWFF3_write()
     */
    if (!(SDWFF3_object_P->cardInitiated))
    {
        return (SD_STATUS_ERROR);
    }

    /*
     * Can't perform write transaction if the card is not connected
     */
    if (!(SDWFF3_object_P->card_inserted))
    {
        return (SD_STATUS_ERROR);
    }

    /*
     * Can't perform write transaction if the card is write protected
     */
    if (SDWFF3_object_P->write_protected)
    {
        return (SD_STATUS_ERROR);
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    bool dma_operation = false;
    if ((SDWFF3_object_P->SDminDmaTransferSize) < secCount)
    {
        /*
         * Perform write transaction using the DMA
         * And configure the defined channel for Tx
         */
        dma_operation = true;
        DMAConfigureChannel(SDWFF3_hwAttrs_P->DmaChannel,
                            32,
                            DMA_WORD_SIZE_4B,
                            DMA_CONFIG_DST_PTR_FIFO | DMA_CONFIG_TX | DMA_CONFIG_CLEAR_AT_JOB_START);
    }

    SDWFF3_openCardClk(ENABLE_SD_CARD_CLK);

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    /*
     * Sending command 25 to the card to start writing
     */
    errorstatus = SDWFF3_prepareCardWrite(SDWFF3_object_P, sector, secCount, dma_operation);

    if (errorstatus == SDWFF3_OK)
    {
        /*
         * Read from SDWFF3 internal FIFO the transmitted data
         */
        errorstatus = SDWFF3_writeFifo(SDWFF3_object_P, secCount, (uint32_t *)buf, dma_operation);
    }

    SDWFF3_openCardClk(DISABLE_SD_CARD_CLK);
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    /*
     * Check if the write transaction works correctly
     * If so, 'errorstatus' expected be 'SDWFF3_OK'
     */
    if (errorstatus != SDWFF3_OK)
    {
        return (SD_STATUS_ERROR);
    }

    return SD_STATUS_SUCCESS;
}

/*
 *  ======== SDWFF3_read ========
 */
int_fast16_t SDWFF3_read(SD_Handle handle, void *buf, int_fast32_t sector, uint_fast32_t secCount)
{
    SDWFF3_object_P  = (SDWFF3_Object *)handle->object;
    SDWFF3_hwAttrs_P = (SDWFF3_HwAttrs *)handle->hwAttrs;

    /*
     * SDWFF3_initialize() must be called before SDWFF3_read()
     */
    if (!(SDWFF3_object_P->cardInitiated))
    {
        return (SD_STATUS_ERROR);
    }

    /*
     * Can't perform read transaction if the card is not connected
     */
    if (!(SDWFF3_object_P->card_inserted))
    {
        return (SD_STATUS_ERROR);
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    bool dma_operation = false;
    if ((SDWFF3_object_P->SDminDmaTransferSize) < secCount)
    {
        /*
         * Perform read transaction using the DMA
         * And configure the defined channel for Rx
         */
        dma_operation = true;
        DMAConfigureChannel(SDWFF3_hwAttrs_P->DmaChannel,
                            32,
                            DMA_WORD_SIZE_4B,
                            DMA_CONFIG_SRC_PTR_FIFO | DMA_CONFIG_CLEAR_AT_JOB_START);
    }

    SDWFF3_Status errorstatus = SDWFF3_OK;

    SDWFF3_openCardClk(ENABLE_SD_CARD_CLK);

    /*
     * Sending command 18 to the card to start reading
     */
    errorstatus = SDWFF3_prepareCardRead(SDWFF3_object_P, sector, secCount, dma_operation);

    if (errorstatus == SDWFF3_OK)
    {
        /*
         * write to SDWFF3 internal FIFO the data for transmitting
         */
        errorstatus = SDWFF3_readFifo(SDWFF3_object_P, secCount, (uint32_t *)buf, dma_operation);
    }

    SDWFF3_openCardClk(DISABLE_SD_CARD_CLK);
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    /*
     * Check if the read transaction works correctly
     * If so, 'errorstatus' expected be 'SDWFF3_OK'
     */
    if (errorstatus != SDWFF3_OK)
    {
        return (SD_STATUS_ERROR);
    }

    return SD_STATUS_SUCCESS;
}

/*
 *  ======== SDWFF3_getSectorSize ========
 */
uint_fast32_t SDWFF3_getSectorSize(SD_Handle handle)
{
    return (SDWFF3_SECTOR_SIZE);
}

/*
 *  ======== SDWFF3_getNumSectors ========
 */
uint_fast32_t SDWFF3_getNumSectors(SD_Handle handle)
{
    return (SDWFF3_object_P->numSectors);
}

/*
 *  ======== SDWFF3_control ========
 */
int_fast16_t SDWFF3_control(SD_Handle handle, uint_fast16_t cmd, void *arg)
{
    SDWFF3_object_P = (SDWFF3_Object *)handle->object;

    /* Initialize return value */
    int ret = SD_STATUS_ERROR;

    /* Perform command */
    switch (cmd)
    {
        case SDWFF3_CMD_IS_CARD_CONNECTED:

            if (SDWFF3_object_P->card_inserted)
            {
                /* Card is connected */
                ret = SD_STATUS_SUCCESS;
            }
            else
            {
                /* Card is NOT connected */
                ret = SD_STATUS_ERROR;
            }
            break;

        case SDWFF3_CMD_IS_CARD_WRITE_PROTECTED:

            if (SDWFF3_object_P->write_protected)
            {
                /* Card is write protected */
                ret = SD_STATUS_SUCCESS;
            }
            else
            {
                /* Card is NOT write protected */
                ret = SD_STATUS_ERROR;
            }
            break;

        default:
            /* This command is not defined */
            ret = SD_STATUS_UNDEFINEDCMD;
            break;
    }

    return (ret);
}

/* ========================================================================== */
/*                          Local Functions Implementation                    */
/* ========================================================================== */

/*
 * Function to check if the card is connected. If SD card detect is not enabled so card indicated as connected.
 * Also check if the card is write protected. If so write to the card return error
 */
void SDWFF3_CDandWP(SDWFF3_Object *object)
{
    if (SDWFF3_hwAttrs_P->cdEnable)
    {
        SDWFF3_cardDetect(object);
    }
    else
    {
        SDWFF3_object_P->card_inserted = true;
        if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
        {
            (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_INSERTED);
        }
    }

    if (SDWFF3_hwAttrs_P->wpEnable)
    {
        SDWFF3_writeProtect(object);
    }
    else
    {
        SDWFF3_object_P->write_protected = false;
    }
}

/*
 * function to implement soft reset on SDWFF3 host controller
 */
void SDWFF3_SoftReset()
{
    uint32_t retReg = 0;

    _setField(0x01,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCTL,
              SDMMC_SYSCTL_SRA_M,
              SDMMC_SYSCTL_SRA_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // polling SYS_STATUS and wait to reset done  -- ADDR = 0x0114
    while (retReg != SDMMC_SYSSTA_RSTDONE_COMPLETE)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_SYSSTA, SDMMC_SYSSTA_RSTDONE_M, SDMMC_SYSSTA_RSTDONE_S);
    }
}

/*
 * Call-back function from power driver that indicate sleep and wake-up
 */
static int SDWFF3_notifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    if (eventType == PowerWFF3_ENTERING_SLEEP)
    {
        SDWFF3_sleep();
    }
    else if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        SDWFF3_wakeup();
    }
    return (Power_NOTIFYDONE);
}

/*
 *  ======== SDWFF3_sleep ========
 */
void SDWFF3_sleep()
{

    HwiP_destruct(&(SDWFF3_object_P->SDhwiStruct));

    SemaphoreP_delete(sdSemaphore);

    SDWFF3_overrideIomux();

    SDWFF3_SoftReset();

    SDWFF3_object_P->isOpen = false;

    Power_releaseDependency(SDWFF3_hwAttrs_P->powerID);
}

void SDWFF3_wakeup()
{
    uint32_t errorstatus = SDWFF3_OK;
    uint8_t cardstate    = 0;
    uint32_t configReg   = 0;

    SDWFF3_open((SD_Handle)SDWFF3_handle, (SD_Params *)SDWFF3_param);

    if (SDWFF3_hwAttrs_P->powerOffInSleep)
    {
        /*
         * If the power switched off while sleeping,
         * Card must be initialized again
         */
        if (SDWFF3_object_P->card_inserted)
        {
            SDWFF3_initialize((SD_Handle)SDWFF3_handle);
        }
    }
    else
    {
        if (SDWFF3_object_P->card_inserted)
        {
            // Set bus clock frequency
            SDWFF3_setBusSpeed(SDWFF3_hwAttrs_P->divClk, false);

            SDWFF3_openCardClk(ENABLE_SD_CARD_CLK);

            uint32_t write_reg = SDWFF3_INTR_ALL;
            SDWFF3_statEn(write_reg);

            /*
             * Check if different card connected while sleep.
             * If so then the state of the card should be idle and then we will get an error of timeout on cmd13
             */
            errorstatus = SDWFF3_IsCardProgramming(SDWFF3_object_P, &cardstate);

            if (errorstatus != SDWFF3_OK)
            {
                SDWFF3_initialize((SD_Handle)SDWFF3_handle);
            }
            else
            {
                if (SDWFF3_hwAttrs_P->numData == 4)
                {

                    _setField(SDWFF3_BUSWIDTH_4B,
                              SDWFF3_hwAttrs_P->baseAddr,
                              SDMMC_O_HCTL,
                              SDMMC_HCTL_DTW_M,
                              SDMMC_HCTL_DTW_S,
                              !SDWFF3_REG_IS_WR_ONLY);
                }
            }
        }
        SDWFF3_openCardClk(DISABLE_SD_CARD_CLK);
    }
}

void SDWFF3_initParam(SDWFF3_Object *object)
{
    object->curBlockSize  = 512;
    object->isOpen        = false;
    object->cardInitiated = false;
}

SDWFF3_Status SDWFF3_prepareCardRead(SDWFF3_Object *object, uint32_t startBlk, uint32_t numBlks, bool dma_operation)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t cmd_arg          = 0;

    uint32_t addr = 0U;

    /*
     * Address is in blocks for high capacity cards and in actual bytes
     * for standard capacity cards
     */
    if (object->cardType == SD_SDHC)
    {
        addr = startBlk;
    }
    else
    {
        addr = startBlk * 512;
    }

    SDWFF3_SetBLKsize(object->curBlockSize);
    SDWFF3_SetNumBLK(numBlks);

    uint32_t configReg = numBlks;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SDMASA,
              SDMMC_SDMASA_ADDR_M,
              SDMMC_SDMASA_ADDR_S,
              !SDWFF3_REG_IS_WR_ONLY);

    if (dma_operation)
    {
        trans_cmd->dma_enable = 0x01;
    }
    else
    {
        trans_cmd->dma_enable = 0x00;
    }

    trans_cmd->cdm_index    = SDWFF3_CMD(18);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x01;
    trans_cmd->multi_block  = 0x01;
    trans_cmd->data_present = 0x01;
    trans_cmd->data_dir     = 0x01;
    trans_cmd->auto_cmd_en  = 0x02;
    cmd_arg                 = addr;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(18));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    return errorstatus;
}

SDWFF3_Status SDWFF3_prepareCardWrite(SDWFF3_Object *object,
                                      int_fast32_t sector,
                                      uint_fast32_t secCount,
                                      bool dma_operation)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t cmd_arg          = 0;

    uint32_t addr = 0U;
    uint32_t cardstatus;
    uint32_t timeout;

    /*
     * Address is in blocks for high capacity cards and in actual bytes
     * for standard capacity cards
     */
    if (object->cardType == SD_SDHC)
    {
        addr = sector;
    }
    else
    {
        addr = sector * 512;
    }

    SDWFF3_SetBLKsize(object->curBlockSize);
    SDWFF3_SetNumBLK(secCount);

    /* Send CMD13 APP_CMD with argument as card's RCA */

    trans_cmd->cdm_index    = SDWFF3_CMD(13);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x00;
    trans_cmd->multi_block  = 0x00;
    trans_cmd->data_present = 0x00;
    trans_cmd->data_dir     = 0x00;
    trans_cmd->auto_cmd_en  = 0x00;
    cmd_arg                 = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(13));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    cardstatus = cmd_resp[0];

    timeout = SDWFF3_DATATIMEOUT;

    while (((cardstatus & 0x00000100) == 0) && (timeout > 0))
    {
        timeout--;

        trans_cmd->cdm_index    = SDWFF3_CMD(13);
        trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
        trans_cmd->blk_cnt_en   = 0x00;
        trans_cmd->multi_block  = 0x00;
        trans_cmd->data_present = 0x00;
        trans_cmd->data_dir     = 0x00;
        trans_cmd->auto_cmd_en  = 0x00;
        cmd_arg                 = (object->rca << 16U);
        SDWFF3_sendCommand(cmd_arg);

        errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(13));

        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }
        cardstatus = cmd_resp[0];
    }

    if (timeout == 0)
    {
        return (SDWFF3_ERROR);
    }

    /* Send CMD25 APP_CMD with argument as card's RCA */

    if (dma_operation)
    {
        trans_cmd->dma_enable = 0x01;
    }
    else
    {
        trans_cmd->dma_enable = 0x00;
    }

    trans_cmd->cdm_index    = SDWFF3_CMD(25);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x01;
    trans_cmd->multi_block  = 0x01;
    trans_cmd->data_present = 0x01;
    trans_cmd->data_dir     = 0x00;
    trans_cmd->auto_cmd_en  = 0x01;
    cmd_arg                 = addr;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(25));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    return errorstatus;
}

SDWFF3_Status SDWFF3_initSD(SDWFF3_Object *object)
{

    SDWFF3_Status errorstatus = SDWFF3_OK;

    SDWFF3_prepareIpForInit();

    // Waiting for the card voltage will stable
    ClockP_usleep(POWER_UP_TIME);

    errorstatus = SDWFF3_PowerON(object);

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    errorstatus = SDWFF3_InitializeCards(object);

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    SDWFF3_GetCardInfo(object);

    errorstatus = SDWFF3_SelectDeselect(object);

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    return (errorstatus);
}

void SDWFF3_prepareIpForInit()
{
    // Enable internal clock and card clock
    uint32_t regAddress = SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_SYSCTL;
    uint32_t configReg  = 0;

    configReg |= ((0xE << SDMMC_SYSCTL_DTO_S) & SDMMC_SYSCTL_DTO_M);
    configReg |= ((0x000000C8 << SDMMC_SYSCTL_CLKD_S) & SDMMC_SYSCTL_CLKD_M);
    configReg |= ((SDWFF3_REG_ENABLE << SDMMC_SYSCTL_CEN_S) & SDMMC_SYSCTL_CEN_M);
    configReg |= ((SDWFF3_REG_ENABLE << SDMMC_SYSCTL_ICE_S) & SDMMC_SYSCTL_ICE_M);

    HWREG(regAddress) = configReg;

    // polling SYSCTL and wait to Internal clock stable
    uint32_t retReg = 0;
    while (!retReg)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_SYSCTL, SDMMC_SYSCTL_ICS_M, SDMMC_SYSCTL_ICS_S);
    }

    SDWFF3_openCardClk(ENABLE_SD_CARD_CLK);

    uint32_t write_reg = SDWFF3_INTR_ALL;
    SDWFF3_statEn(write_reg);
}

void SDWFF3_openCardClk(bool clk_open)
{
    if (clk_open)
    {
        // Enable external clock free running
        _setField(0x01,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_CLKEXTFREE_M,
                  SDMMC_CON_CLKEXTFREE_S,
                  !SDWFF3_REG_IS_WR_ONLY);
    }
    else
    {
        _setField(0x00,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_CLKEXTFREE_M,
                  SDMMC_CON_CLKEXTFREE_S,
                  !SDWFF3_REG_IS_WR_ONLY);
    }
}

SDWFF3_Status SDWFF3_SelectDeselect(SDWFF3_Object *object)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t cmd_arg          = 0;

    trans_cmd->cdm_index = SDWFF3_CMD(7);
    trans_cmd->resp_type = SDWFF3_CMDRSP_BUSY;
    cmd_arg              = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(7));

    return (errorstatus);
}

SDWFF3_Status SDWFF3_PowerON(SDWFF3_Object *object)
{
    uint32_t cmd_arg          = 0;
    SDWFF3_Status errorstatus = SDWFF3_OK;

    uint32_t SDType = SDWFF3_STD_CAPACITY;

    object->cardType = SD_SDSC;

    /* CMD0: GO_IDLE_STATE */
    /* No CMD response required */
    SDWFF3_clearCmdVar();

    trans_cmd->cdm_index = SDWFF3_CMD(0);
    trans_cmd->resp_type = SDWFF3_CMDRSP_NONE;
    cmd_arg              = 0U;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdError();

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    /* CMD8: SEND_IF_COND --------------------------------------------------------*/
    /* Send CMD8 to verify SD card interface operating condition */
    /* Argument: - [31:12]: Reserved (shall be set to '0')
                 - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
                 - [7:0]: Check Pattern (recommended 0xAA) */
    /* CMD Response: R7 */

    cmd_arg = SDWFF3_VOLT_2P7_3P6 | SDWFF3_CMD_CHECK_PATTERN;

    trans_cmd->cdm_index = SDWFF3_CMD(8);
    trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp7Error();

    /* If errorstatus is Command TimeOut, it is a MMC card */
    /* If errorstatus is SDWFF3_OK it is a SD card: SD card 2.0 (voltage range mismatch)
       or SD card 1.x */
    if (errorstatus == SDWFF3_CMD_RSP_TIMEOUT)
    {
        object->cardType = SD_SDSC; /* SD Card 1.x */
    }
    else
    {
        SDWFF3_readResp(SDWFF3_CMDRSP_48BITS);

        if ((cmd_resp[0] == (SDWFF3_VOLT_2P7_3P6 | SDWFF3_CMD_CHECK_PATTERN)) & (errorstatus == SDWFF3_OK))
        {
            object->cardType = CARD_UNKNOWEN_YET; /* SD Card 2.0 OR High capacity */
            SDType           = SDWFF3_HIGH_CAPACITY;
        }
        else
        {
            return (SDWFF3_UNSUPPORTED_CARD);
        }
    }

    /* SD CARD */
    /* Send ACMD41 SDWFF3_APP_OP_COND with Argument 0x80100000 */
    uint32_t retry = ACMD41_RETRY;
    uint32_t acmd_busy;
    /* Poll until we get the card status (BIT31 of OCR) is powered up */
    do
    {
        // It is takes some ms to ACMD41 to response ready
        ClockP_usleep(ACMD41_sleep);
        /* ======== Send CMD 55 ======== */

        trans_cmd->cdm_index = SDWFF3_CMD(55);
        trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
        cmd_arg              = 0;
        SDWFF3_sendCommand(cmd_arg);

        errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(55));

        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }

        /* ======== Send ACMD 41 ======== */
        trans_cmd->cdm_index = SDWFF3_CMD(41);
        trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
        cmd_arg              = SDType | SDWFF3_OCR_VDD_WILDCARD;
        SDWFF3_sendCommand(cmd_arg);

        errorstatus = SDWFF3_CmdResp3Error();
        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }

        // check response for ACMD 41
        SDWFF3_readResp(SDWFF3_CMDRSP_48BITS);

        retry--;
        acmd_busy = cmd_resp[0] & ((uint32_t)BIT(31U));
    } while ((acmd_busy == 0U) && (retry != 0));

    if (retry == 0U)
    {
        /* No point in continuing */
        errorstatus = SDWFF3_INVALID_VOLTRANGE;
        return (errorstatus);
    }

    if (cmd_resp[0] & SDWFF3_HIGH_CAPACITY)
    {
        object->cardType = SD_SDHC;
    }
    else
    {
        object->cardType = SD_SDSC;
    }

    if ((errorstatus == SDWFF3_OK) & ((cmd_resp[0] & SDWFF3_OCR_VDD_WILDCARD) == SDWFF3_OCR_VDD_WILDCARD))
    {
        return (errorstatus);
    }
    else
    {
        return (errorstatus);
    }

    return (errorstatus);
}

SDWFF3_Status SDWFF3_InitializeCards(SDWFF3_Object *object)
{
    uint32_t cmd_arg          = 0;
    SDWFF3_Status errorstatus = SDWFF3_OK;

    /* ======== Send CMD 2 ======== */
    /* Send CMD2, to get the card identification register */

    trans_cmd->cdm_index = SDWFF3_CMD(2);
    trans_cmd->resp_type = SDWFF3_CMDRSP_136BITS;
    cmd_arg              = 0x00;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp2Error();
    if (SDWFF3_OK != errorstatus)
    {
        return (errorstatus);
    }

    // check response for CMD2
    SDWFF3_readResp(SDWFF3_CMDRSP_136BITS);

    object->cid[0] = cmd_resp[0];
    object->cid[1] = cmd_resp[1];
    object->cid[2] = cmd_resp[2];
    object->cid[3] = cmd_resp[3];

    /* ======== Send CMD 3 ======== */
    /* Send CMD3, to get the card relative address*/
    trans_cmd->cdm_index = SDWFF3_CMD(3);
    trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
    cmd_arg              = 0x00;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp6Error(object);

    if (SDWFF3_OK != errorstatus)
    {
        return (errorstatus);
    }

    /* ======== Send CMD 9 ======== */
    /* Send CMD9, to get the card specific data */

    trans_cmd->cdm_index = SDWFF3_CMD(9);
    trans_cmd->resp_type = SDWFF3_CMDRSP_136BITS;
    cmd_arg              = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp2Error();

    if (SDWFF3_OK != errorstatus)
    {
        return (errorstatus);
    }

    SDWFF3_readResp(SDWFF3_CMDRSP_136BITS);

    object->csd[0] = cmd_resp[0];
    object->csd[1] = cmd_resp[1];
    object->csd[2] = cmd_resp[2];
    object->csd[3] = cmd_resp[3];

    return (errorstatus);
}

/**
 * @brief  Checks if the SD card is in programming state.
 * @param  pstatus: pointer to the variable that will contain the SD
 *   card state.
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_IsCardProgramming(SDWFF3_Object *object, uint8_t *pstatus)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t cmd_arg          = 0;

    /* Send CMD13 APP_CMD with argument as card's RCA */

    trans_cmd->cdm_index    = SDWFF3_CMD(13);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x00;
    trans_cmd->multi_block  = 0x00;
    trans_cmd->data_present = 0x00;
    trans_cmd->data_dir     = 0x00;
    trans_cmd->auto_cmd_en  = 0x00;
    cmd_arg                 = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(13));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    *pstatus = (uint8_t)((cmd_resp[0] >> 9) & 0x0000000F);

    return (errorstatus);
}

SDWFF3_Status SDWFF3_readFifo(SDWFF3_Object *object, uint32_t numBlks, uint32_t *data_point, bool dma_operation)
{

    uint32_t status           = 0;
    uint32_t retReg           = 0;
    uint32_t errorstatus      = SDWFF3_OK;
    uint8_t cardstate         = 0;
    uint32_t *source_addr     = (uint32_t *)(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
    uint32_t pstate_bre       = 0;
    uint32_t num_words_in_blk = ((object->curBlockSize) >> 2);

    if (dma_operation)
    {
        DMAStartTransaction(SDWFF3_hwAttrs_P->DmaChannel,
                            source_addr,
                            data_point,
                            (uint16_t)(numBlks * (object->curBlockSize)),
                            0);

        SDWFF3_intrEn(SDMMC_STAT_TC_M);
        if (SemaphoreP_OK != SemaphoreP_pend(sdSemaphore, SemaphoreP_WAIT_FOREVER))
        {
            return (SDWFF3_ERROR);
        }
    }
    else
    {
        for (uint32_t n = 0; n < numBlks; n++)
        {
            while (!(pstate_bre))
            {
                pstate_bre = _getField(SDWFF3_hwAttrs_P->baseAddr,
                                       SDMMC_O_PSTATE,
                                       SDMMC_PSTATE_BRE_M,
                                       SDMMC_PSTATE_BRE_S);
            }
            for (uint32_t j = 0; j < num_words_in_blk; j++)
            {
                data_point[n * num_words_in_blk + j] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
            }
        }
    }

    while (!retReg)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_TC_M, SDMMC_STAT_TC_S);
    }

    status = SDWFF3_readStatusReg();

    if (status & SDWFF3_STATUS_ERR_INTR)
    {
        return (SDWFF3_ERROR);
    }

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    /* Wait till the card is in programming state */
    errorstatus = SDWFF3_IsCardProgramming(object, &cardstate);
    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    while ((errorstatus == SDWFF3_OK) && (cardstate != SDWFF3_CARD_TRANS_STATE))
    {
        errorstatus = SDWFF3_IsCardProgramming(object, &cardstate);

        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }
    }

    return (errorstatus);
}

SDWFF3_Status SDWFF3_writeFifo(SDWFF3_Object *object, uint32_t numBlks, uint32_t *data_point, bool dma_operation)
{
    uint32_t status             = 0;
    uint32_t buf_ready_for_data = SDMMC_PSTATE_DATI_M | SDMMC_PSTATE_DLA_M | SDMMC_PSTATE_WTA_M | SDMMC_PSTATE_BWE_M;
    uint32_t retReg             = 0;
    uint32_t errorstatus        = SDWFF3_OK;
    uint8_t cardstate           = 0;
    uint32_t *dest_addr         = (uint32_t *)(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
    uint32_t pstate_bwe         = 0;
    uint32_t num_words_in_blk   = ((object->curBlockSize) >> 2);

    if (dma_operation)
    {
        status = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_PSTATE);
        status &= buf_ready_for_data;
        while (status != buf_ready_for_data)
        {
            status = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_PSTATE);
            status &= buf_ready_for_data;
        }

        DMAStartTransaction(SDWFF3_hwAttrs_P->DmaChannel,
                            data_point,
                            dest_addr,
                            (uint16_t)(numBlks * (object->curBlockSize)),
                            0);

        SDWFF3_intrEn(SDMMC_STAT_TC_M);
        if (SemaphoreP_OK != SemaphoreP_pend(sdSemaphore, SemaphoreP_WAIT_FOREVER))
        {
            return (SDWFF3_ERROR);
        }
    }
    else
    {
        for (uint32_t n = 0; n < numBlks; n++)
        {
            while (!(pstate_bwe))
            {
                pstate_bwe = _getField(SDWFF3_hwAttrs_P->baseAddr,
                                       SDMMC_O_PSTATE,
                                       SDMMC_PSTATE_BWE_M,
                                       SDMMC_PSTATE_BWE_S);
            }
            /*
             *  Delay for the HW to be prepared for new data
             */
            ClockP_usleep(FIFO_WR_DELAY);

            for (uint32_t j = 0; j < num_words_in_blk; j++)
            {
                HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA) = data_point[n * num_words_in_blk + j];
            }
        }
    }

    while (!retReg)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_TC_M, SDMMC_STAT_TC_S);
    }

    status = SDWFF3_readStatusReg();

    if (status & SDWFF3_STATUS_ERR_INTR)
    {
        return (SDWFF3_ERROR);
    }

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    /* Wait till the card is in programming state */
    errorstatus = SDWFF3_IsCardProgramming(object, &cardstate);
    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    while ((errorstatus == SDWFF3_OK) && (cardstate != SDWFF3_CARD_TRANS_STATE))
    {
        errorstatus = SDWFF3_IsCardProgramming(object, &cardstate);

        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }
    }

    return (errorstatus);
}

SDWFF3_Status SDWFF3_setBusWidth(SDWFF3_Object *object, uint32_t bus_width)
{

    uint32_t errorstatus = SDWFF3_OK;
    uint32_t cmd_arg     = 0;
    uint32_t cmd6_arg;
    uint32_t status = 0;

    errorstatus = SDWFF3_FindSCR(object);

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }
    if (bus_width == SDWFF3_BUSWIDTH_4B)
    {
        cmd6_arg = 0x00000002;
    }
    else
    {
        cmd6_arg = 0x00000000;
    }

    /* Send CMD55 APP_CMD with argument as card's RCA */
    trans_cmd->cdm_index = SDWFF3_CMD(55);
    trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
    cmd_arg              = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(55));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    /* Send CMD6 set bus width */
    trans_cmd->cdm_index = SDWFF3_CMD(6);
    trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
    cmd_arg              = cmd6_arg;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(6));

    if (errorstatus != SDWFF3_OK)
    {
        SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
        return (SDWFF3_SUPPORT_1D_ONLY);
    }

    _setField(bus_width,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_HCTL,
              SDMMC_HCTL_DTW_M,
              SDMMC_HCTL_DTW_S,
              !SDWFF3_REG_IS_WR_ONLY);

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    return (errorstatus);
}

/*
 *  Compilation may optimize this function wrongly
 *  If so, change the function to:
 *  __attribute__((optnone)) SDWFF3_Status SDWFF3_setHighSpeedMode()
 */
SDWFF3_Status SDWFF3_setHighSpeedMode()
{
    uint32_t cmd_arg;
    uint32_t errorstatus = SDWFF3_OK;
    uint32_t status      = 0;

    SDWFF3_SetBLKsize(64);
    SDWFF3_SetNumBLK(1);

    trans_cmd->cdm_index    = SDWFF3_CMD(6);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x01;
    trans_cmd->multi_block  = 0x00;
    trans_cmd->data_present = 0x01;
    trans_cmd->data_dir     = 0x01;
    trans_cmd->dma_enable   = 0x00;
    cmd_arg                 = 0x00FFFFF0;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(6));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    uint32_t pstate_bre = 0;
    uint32_t retReg     = 0;

    uint32_t function_resp[16];

    while (!(pstate_bre))
    {
        pstate_bre = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_PSTATE, SDMMC_PSTATE_BRE_M, SDMMC_PSTATE_BRE_S);
    }

    for (uint32_t j = 0; j < 16; j++)
    {
        function_resp[j] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
    }

    while (!retReg)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_TC_M, SDMMC_STAT_TC_S);
    }

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
    status = SDWFF3_readStatusReg();

    if (status & SDWFF3_STATUS_ERR_INTR)
    {
        return (SDWFF3_ERROR);
    }

    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    uint32_t cmd6sent = 0;

    // check for HIGH SPEED Mode support in the SD card
    if ((function_resp[3] & 0x00000200) == 0x00000200) // True if HIGH SPEED MODE is supported in the SD_CARD
    {

        cmd6sent = 1;

        SDWFF3_SetBLKsize(64);
        SDWFF3_SetNumBLK(1);

        trans_cmd->cdm_index    = SDWFF3_CMD(6);
        trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
        trans_cmd->blk_cnt_en   = 0x01;
        trans_cmd->multi_block  = 0x00;
        trans_cmd->data_present = 0x01;
        trans_cmd->data_dir     = 0x01;
        trans_cmd->dma_enable   = 0x00;
        cmd_arg                 = 0x80FFFFF1;
        SDWFF3_sendCommand(cmd_arg);

        errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(6));

        if (errorstatus != SDWFF3_OK)
        {
            return (errorstatus);
        }
    }
    else
    {
        SDWFF3_object_P->clockDiv = 2;
        return (SDWFF3_DOESNT_SUPPORT_HS);
    }

    if (cmd6sent == 1)
    {
        pstate_bre = 0;
        retReg     = 0;

        while (!(pstate_bre))
        {
            pstate_bre = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_PSTATE, SDMMC_PSTATE_BRE_M, SDMMC_PSTATE_BRE_S);
        }

        for (uint32_t j = 0; j < 16; j++)
        {
            function_resp[j] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
        }

        while (!retReg)
        {
            retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_TC_M, SDMMC_STAT_TC_S);
        }

        status = SDWFF3_readStatusReg();

        if (status & SDWFF3_STATUS_ERR_INTR)
        {
            return (SDWFF3_ERROR);
        }

        SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

        if (((function_resp[4] & 0x00000001) == 0x00000001))
        {
            SDWFF3_object_P->clockDiv = 1;
        }
        else
        {
            SDWFF3_object_P->clockDiv = 2;
        }
    }

    return (SDWFF3_OK);
}

void SDWFF3_setBusSpeed(uint32_t clkDiv, bool outputHigh)
{

    _setField(0x00,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCTL,
              SDMMC_SYSCTL_ICE_M,
              SDMMC_SYSCTL_ICE_S,
              !SDWFF3_REG_IS_WR_ONLY);
    _setField(0x00,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCTL,
              SDMMC_SYSCTL_CEN_M,
              SDMMC_SYSCTL_CEN_S,
              !SDWFF3_REG_IS_WR_ONLY);

    uint32_t regAddress = SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_SYSCTL;
    uint32_t configReg  = 0;

    if (outputHigh)
    {
        _setField(0x01,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_HCTL,
                  SDMMC_HCTL_HSPE_M,
                  SDMMC_HCTL_HSPE_S,
                  !SDWFF3_REG_IS_WR_ONLY);
    }

    configReg |= ((0xE << SDMMC_SYSCTL_DTO_S) & SDMMC_SYSCTL_DTO_M);
    configReg |= ((clkDiv << SDMMC_SYSCTL_CLKD_S) & SDMMC_SYSCTL_CLKD_M);
    configReg |= ((SDWFF3_REG_ENABLE << SDMMC_SYSCTL_CEN_S) & SDMMC_SYSCTL_CEN_M);
    configReg |= ((SDWFF3_REG_ENABLE << SDMMC_SYSCTL_ICE_S) & SDMMC_SYSCTL_ICE_M);

    HWREG(regAddress) = configReg;

    // polling SYSCTL and wait to Internal clock stable
    uint32_t retReg = 0;
    while (!retReg)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_SYSCTL, SDMMC_SYSCTL_ICS_M, SDMMC_SYSCTL_ICS_S);
    }
}

void SDWFF3_initHost(void)
{
    uint32_t configReg  = 0;
    uint32_t retReg     = 0;
    uint32_t regAddress = 0;

    // polling SYS_STATUS and wait to reset done  -- ADDR = 0x0114
    while (retReg != SDMMC_SYSSTA_RSTDONE_COMPLETE)
    {
        retReg = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_SYSSTA, SDMMC_SYSSTA_RSTDONE_M, SDMMC_SYSSTA_RSTDONE_S);
    }

    // config functional clock to be post-swallowing
    configReg = SDMMC_CLKSEL_VAL_SYNC;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_CLKSEL,
              SDMMC_CLKSEL_VAL_M,
              SDMMC_CLKSEL_VAL_S,
              !SDWFF3_REG_IS_WR_ONLY);

    configReg = SDWFF3_REG_ENABLE;

    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_CAPA,
              SDMMC_CAPA_VS33_M,
              SDMMC_CAPA_VS33_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // Disable AutoIdle gating
    configReg = 0x00;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCFG,
              SDMMC_SYSCFG_AUTOIDLE_M,
              SDMMC_SYSCFG_AUTOIDLE_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config card detect  -- It will be active only if the customer will enable it
    // config Card Detect Signal Selection to test mode to avoid soft reset  -- ADDR = 0x0228
    configReg = SDWFF3_REG_ENABLE;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_HCTL,
              SDMMC_HCTL_CDSS_M,
              SDMMC_HCTL_CDSS_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config SIDLEMODE to 0x03 to change CON.DVAL  -- ADDR = 0x0110
    configReg = 0x03;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCFG,
              SDMMC_SYSCFG_SIDLEMODE_M,
              SDMMC_SYSCFG_SIDLEMODE_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config DVAL to 0x00 to choose debounce period of 33us  -- ADDR = 0x012C
    configReg = 0x00;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_CON,
              SDMMC_CON_DVAL_M,
              SDMMC_CON_DVAL_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config SIDLEMODE to 0x02 to the reset value  -- ADDR = 0x0110
    configReg = 0x02;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCFG,
              SDMMC_SYSCFG_SIDLEMODE_M,
              SDMMC_SYSCFG_SIDLEMODE_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config DATA timeout to 0x02 to the reset value  -- ADDR = 0x0110
    configReg = 0x0E;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SYSCTL,
              SDMMC_SYSCTL_DTO_M,
              SDMMC_SYSCTL_DTO_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // config DATA timeout to 0x02 to the reset value  -- ADDR = 0x0110
    configReg = 0x04;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_SDMASA,
              SDMMC_SDMASA_ADDR_M,
              SDMMC_SDMASA_ADDR_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // Set bus voltage to 3.3V
    configReg = SDWFF3_CARD_VOL_3P3;

    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_HCTL,
              SDMMC_HCTL_SDVS_M,
              SDMMC_HCTL_SDVS_S,
              !SDWFF3_REG_IS_WR_ONLY);

    // Set card bus power
    configReg = SDWFF3_REG_ENABLE;
    _setField(configReg,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_HCTL,
              SDMMC_HCTL_SDBP_M,
              SDMMC_HCTL_SDBP_S,
              !SDWFF3_REG_IS_WR_ONLY);

    SDWFF3_statEn(SDWFF3_INTR_ALL);

    SDWFF3_SetBLKsize(512);
}

static void SDWFF3HwipFxn(uintptr_t arg)
{

    Event_Type event              = SDWFF3_NULL;
    uint32_t inserted_and_removal = (SDMMC_STAT_CINS_M | SDMMC_STAT_CREM_M);

    uint32_t status = SDWFF3_readStatusReg();

    if (status & SDMMC_STAT_TC_M)
    {
        SDWFF3_intrDis(SDMMC_STAT_TC_M);
        SemaphoreP_post(sdSemaphore);
    }
    else
    {
        if ((status & inserted_and_removal) == inserted_and_removal)
        {
            // If the card was connected so now it has been removed
            if (SDWFF3_object_P->card_inserted)
            {
                event                          = SDWFF3_CARD_REMOVED;
                SDWFF3_object_P->card_inserted = false;
                SDWFF3_object_P->cardInitiated = false;
                SDWFF3_statusClear(SDWFF3_STATUS_CARD_INS);
                SDWFF3_intrEn(SDMMC_ISE_CINSSEN_M);
                SDWFF3_intrDis(SDMMC_ISE_CREMSEN_M);
            }
            else
            {
                event                          = SDWFF3_CARD_INSERTED;
                SDWFF3_object_P->card_inserted = true;
                SDWFF3_statusClear(SDWFF3_STATUS_CARD_REM);
                SDWFF3_intrEn(SDMMC_ISE_CREMSEN_M);
                SDWFF3_intrDis(SDMMC_ISE_CINSSEN_M);
            }
        }
        else if (status & SDMMC_STAT_ERRI_M)
        {
            SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
            event = SDWFF3_STATUS_ERR;
        }
        if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
        {
            (SDWFF3_object_P->SDWFF3_CB_function)(event);
        }
    }
}

void SDWFF3_writeProtect(SDWFF3_Object *object)
{

    uint32_t card_wp;
    if (SDWFF3_hwAttrs_P->wpPolHigh)
    {
        _setField(0x01,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_WPP_M,
                  SDMMC_CON_WPP_S,
                  !SDWFF3_REG_IS_WR_ONLY);
    }
    else
    {
        _setField(0x00,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_WPP_M,
                  SDMMC_CON_WPP_S,
                  !SDWFF3_REG_IS_WR_ONLY);
    }
    /*
     *  Delay for HW to detect current status of write protect
     */
    ClockP_usleep(WP_CD_DELAY);
    card_wp = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_PSTATE, SDMMC_PSTATE_WP_M, SDMMC_PSTATE_WP_S);
    if (card_wp)
    {
        object->write_protected = false;
    }
    else
    {
        object->write_protected = true;
        if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
        {
            (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_WRITE_PROTECTED);
        }
    }
}

void SDWFF3_cardDetect(SDWFF3_Object *object)
{
    uint32_t regRead = 0;
    uint32_t card_stat;

    regRead = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_STAT);

    if (SDWFF3_hwAttrs_P->cdPolHigh)
    {
        _setField(0x01,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_CDP_M,
                  SDMMC_CON_CDP_S,
                  !SDWFF3_REG_IS_WR_ONLY);
        /*
         *  Delay for HW to detect current status of card detect
         */
        ClockP_usleep(WP_CD_DELAY);
        card_stat = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_CINS_M, SDMMC_STAT_CINS_S);

        if (card_stat)
        {
            SDWFF3_statusClear(SDWFF3_STATUS_CARD_REM);
            SDWFF3_intrDis(SDMMC_ISE_CINSSEN_M);
            SDWFF3_intrEn(SDMMC_ISE_CREMSEN_M);
            object->card_inserted = true;
            if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
            {
                (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_INSERTED);
            }
        }
        else
        {
            SDWFF3_statusClear(SDWFF3_STATUS_CARD_INS);
            SDWFF3_intrDis(SDMMC_ISE_CREMSEN_M);
            SDWFF3_intrEn(SDMMC_ISE_CINSSEN_M);
            object->card_inserted = false;
            if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
            {
                (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_REMOVED);
            }
        }
    }
    else
    {
        _setField(0x00,
                  SDWFF3_hwAttrs_P->baseAddr,
                  SDMMC_O_CON,
                  SDMMC_CON_CDP_M,
                  SDMMC_CON_CDP_S,
                  !SDWFF3_REG_IS_WR_ONLY);
        /*
         *  Delay for HW to detect current status of card detect
         */
        ClockP_usleep(WP_CD_DELAY);
        card_stat = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_CREM_M, SDMMC_STAT_CREM_S);

        if (card_stat)
        {
            SDWFF3_statusClear(SDWFF3_STATUS_CARD_INS);
            SDWFF3_intrDis(SDMMC_ISE_CREMSEN_M);
            SDWFF3_intrEn(SDMMC_ISE_CINSSEN_M);
            object->card_inserted = false;
            if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
            {
                (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_REMOVED);
            }
        }
        else
        {
            SDWFF3_statusClear(SDWFF3_STATUS_CARD_REM);
            SDWFF3_intrDis(SDMMC_ISE_CINSSEN_M);
            SDWFF3_intrEn(SDMMC_ISE_CREMSEN_M);
            object->card_inserted = true;
            if ((SDWFF3_object_P->SDWFF3_CB_function) != NULL)
            {
                (SDWFF3_object_P->SDWFF3_CB_function)(SDWFF3_CARD_INSERTED);
            }
        }
    }
}

void SDWFF3_sendCommand(uint32_t cmd_arg)
{

    uint32_t cmdConfig = 0;

    cmdConfig |= (trans_cmd->dma_enable << SDMMC_CMD_DE_S);
    cmdConfig |= (trans_cmd->blk_cnt_en << SDMMC_CMD_BCE_S);
    cmdConfig |= (trans_cmd->multi_block << SDMMC_CMD_MSBS_S);
    cmdConfig |= (trans_cmd->auto_cmd_en << SDMMC_CMD_ACEN_S);
    cmdConfig |= (trans_cmd->data_dir << SDMMC_CMD_DDIR_S);
    cmdConfig |= (trans_cmd->resp_type << SDMMC_CMD_RSPTYPE_S);
    cmdConfig |= (trans_cmd->data_present << SDMMC_CMD_DP_S);
    cmdConfig |= (trans_cmd->cdm_index << SDMMC_CMD_IDX_S);

    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_ARG) = cmd_arg;
    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_CMD) = cmdConfig;

    SDWFF3_clearCmdVar();
}

void SDWFF3_readResp(uint32_t resp_type)
{
    if (resp_type == SDWFF3_CMDRSP_136BITS)
    {
        cmd_resp[3] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_RSP76);
        cmd_resp[2] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_RSP54);
        cmd_resp[1] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_RSP32);
    }
    cmd_resp[0] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_RSP10);
}

void SDWFF3_clearCmdVar()
{
    memset(trans_cmd, 0, sizeof(SDWFF3_cmdParams));
}

void SDWFF3_configIomux()
{
    /* ======== config clock GPIO ======== */
    GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->clkPin,
                         IOMUX_GPIO14CFG_IE_ENABLE | IOMUX_GPIO14PCTL_CTL_DOWN,
                         SDWFF3_hwAttrs_P->clkPinMux);

    /* ======== config cmd GPIO ======== */
    GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->cmdPin,
                         IOMUX_GPIO15CFG_IE_ENABLE | IOMUX_GPIO15PCTL_CTL_DOWN,
                         SDWFF3_hwAttrs_P->cmdPinMux);

    /* ======== config data 0 GPIO ======== */
    GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data0Pin,
                         IOMUX_GPIO13CFG_IE_ENABLE | IOMUX_GPIO13PCTL_CTL_DOWN,
                         SDWFF3_hwAttrs_P->data0PinMux);

    if (SDWFF3_hwAttrs_P->numData == 4)
    {
        /* ======== config data 1 GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data1Pin,
                             IOMUX_GPIO12CFG_IE_ENABLE | IOMUX_GPIO12PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->data1PinMux);

        /* ======== config data 2 GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data2Pin,
                             IOMUX_GPIO11CFG_IE_ENABLE | IOMUX_GPIO11PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->data2PinMux);

        /* ======== config data 3 GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data3Pin,
                             IOMUX_GPIO10CFG_IE_ENABLE | IOMUX_GPIO10PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->data3PinMux);
    }

    if (SDWFF3_hwAttrs_P->cdEnable)
    {
        /* ======== config Card detect GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->cdPin,
                             IOMUX_GPIO10CFG_IE_ENABLE | IOMUX_GPIO10PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->cdPinMux);
    }

    if (SDWFF3_hwAttrs_P->wpEnable)
    {
        /* ======== config Write protect GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->wpPin,
                             IOMUX_GPIO10CFG_IE_ENABLE | IOMUX_GPIO10PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->wpPinMux);
    }

    if (SDWFF3_hwAttrs_P->powEnable)
    {
        /* ======== config Power signal GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->powPin,
                             IOMUX_GPIO10CFG_IE_ENABLE | IOMUX_GPIO10PCTL_CTL_DOWN,
                             SDWFF3_hwAttrs_P->powPinMux);
    }
}

void SDWFF3_overrideIomux()
{
    /* ======== config clock GPIO ======== */
    GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->clkPin,
                         IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                         SDWFF3_hwAttrs_P->clkPinMux);

    if (SDWFF3_hwAttrs_P->powerOffInSleep)
    {
        /* ======== config cmd GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->cmdPin,
                             IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                             SDWFF3_hwAttrs_P->cmdPinMux);

        /* ======== config data 0 GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data0Pin,
                             IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                             SDWFF3_hwAttrs_P->data0PinMux);

        if (SDWFF3_hwAttrs_P->numData == 4)
        {
            /* ======== config data 1 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data1Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                                 SDWFF3_hwAttrs_P->data1PinMux);

            /* ======== config data 2 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data2Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                                 SDWFF3_hwAttrs_P->data2PinMux);

            /* ======== config data 3 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data3Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                                 SDWFF3_hwAttrs_P->data3PinMux);
        }

        /* ======== config Power signal GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->powPin,
                             IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE,
                             SDWFF3_hwAttrs_P->powPinMux);
    }
    else
    {
        /* ======== config cmd GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->cmdPin,
                             IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                 IOMUX_GPIO15CTL_OUT_HIGH,
                             SDWFF3_hwAttrs_P->cmdPinMux);

        /* ======== config data 0 GPIO ======== */
        GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data0Pin,
                             IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                 IOMUX_GPIO15CTL_OUT_HIGH,
                             SDWFF3_hwAttrs_P->data0PinMux);

        if (SDWFF3_hwAttrs_P->numData == 4)
        {
            /* ======== config data 1 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data1Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                     IOMUX_GPIO15CTL_OUT_HIGH,
                                 SDWFF3_hwAttrs_P->data1PinMux);

            /* ======== config data 2 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data2Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                     IOMUX_GPIO15CTL_OUT_HIGH,
                                 SDWFF3_hwAttrs_P->data2PinMux);

            /* ======== config data 3 GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->data3Pin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                     IOMUX_GPIO15CTL_OUT_HIGH,
                                 SDWFF3_hwAttrs_P->data3PinMux);
        }
        if (SDWFF3_hwAttrs_P->powEnable)
        {
            /* ======== config Power signal GPIO ======== */
            GPIO_setConfigAndMux(SDWFF3_hwAttrs_P->powPin,
                                 IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE | IOMUX_GPIO14CTL_OUTOVREN_ENABLE |
                                     IOMUX_GPIO15CTL_OUT_HIGH,
                                 SDWFF3_hwAttrs_P->powPinMux);
        }
    }

    if (SDWFF3_hwAttrs_P->cdEnable)
    {
        /* ======== config Card detect GPIO ======== */
        GPIO_resetConfig(SDWFF3_hwAttrs_P->cdPin);
    }

    if (SDWFF3_hwAttrs_P->wpEnable)
    {
        /* ======== config Write protect GPIO ======== */
        GPIO_resetConfig(SDWFF3_hwAttrs_P->wpPin);
    }
}

void SDWFF3_statEn(uint32_t intrIdx)
{
    uint32_t intrRead = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_IE);
    intrRead |= intrIdx;
    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_IE) = intrRead;
}

void SDWFF3_intrEn(uint32_t intrIdx)
{
    uint32_t intrRead                               = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_ISE);
    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_ISE) = intrRead | intrIdx;
}

void SDWFF3_intrDis(uint32_t intrIdx)
{
    uint32_t intrRead                               = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_ISE);
    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_ISE) = intrRead & !intrIdx;
}

void SDWFF3_statusClear(uint32_t statusBits)
{
    HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_STAT) = statusBits;
}

uint32_t SDWFF3_readStatusReg()
{

    uint32_t stat = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_STAT);

    return stat;
}

/**
 * @brief  Checks for error conditions for CMD0.
 * @param  None
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdError(void)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t timeout;
    uint32_t wait_card_complete = 0;

    timeout = SDIO_CMD0TIMEOUT; /* 10000 */

    while ((timeout > 0) && !wait_card_complete)
    {
        timeout--;
        wait_card_complete = _getField(SDWFF3_hwAttrs_P->baseAddr, SDMMC_O_STAT, SDMMC_STAT_CC_M, SDMMC_STAT_CC_S);
    }

    if (timeout == 0)
    {
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        return (errorstatus);
    }

    // clear command complete status
    SDWFF3_statusClear(SDWFF3_STATUS_CMD_COMPLETE);

    return (errorstatus);
}

/**
 * @brief  Checks for error conditions for R7.
 *   response.
 * @param  None
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdResp7Error(void)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t timeout          = SDIO_CMD0TIMEOUT;
    uint32_t status;

    status = SDWFF3_readStatusReg();

    while (!(status & (SDWFF3_STATUS_CMD_CRC_ERR | SDWFF3_STATUS_CMD_COMPLETE | SDWFF3_STATUS_CMD_TIMEOUT_ERR)))
    {
        timeout--;
        status = SDWFF3_readStatusReg();
    }

    if ((timeout == 0) || (status & SDWFF3_STATUS_CMD_TIMEOUT_ERR))
    {
        /* Card is not V2.0 compliment or card does not support the set voltage range */
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
        return (errorstatus);
    }

    if (status & SDWFF3_STATUS_CMD_COMPLETE)
    {
        /* Card is SD V2.0 compliant */
        errorstatus = SDWFF3_OK;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_COMPLETE);
        return (errorstatus);
    }
    return (errorstatus);
}

/**
 * @brief  Checks for error conditions for R1.
 *   response
 * @param  cmd: The sent command index.
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdResp1Error(uint8_t cmd)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t status;
    uint32_t response_r1;

    status = SDWFF3_readStatusReg();

    while (!(status & (SDWFF3_STATUS_CMD_CRC_ERR | SDWFF3_STATUS_CMD_COMPLETE | SDWFF3_STATUS_CMD_TIMEOUT_ERR)))
    {
        status = SDWFF3_readStatusReg();
    }

    if (status & SDWFF3_STATUS_CMD_TIMEOUT_ERR)
    {
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_TIMEOUT_ERR);
        return (errorstatus);
    }
    else if (status & SDWFF3_STATUS_CMD_CRC_ERR)
    {
        errorstatus = SDWFF3_CMD_CRC_FAIL;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_CRC_ERR);
        return (errorstatus);
    }

    /* Clear all the static flags */
    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    /* We have received response, retrieve it for analysis  */
    SDWFF3_readResp(SDWFF3_CMDRSP_48BITS);
    response_r1 = cmd_resp[0];

    if ((response_r1 & SDWFF3_OCR_ERRORBITS) == SDWFF3_ALLZERO)
    {
        return (errorstatus);
    }

    if (response_r1 & SDWFF3_OCR_ADDR_OUT_OF_RANGE)
    {
        return (SDWFF3_ADDR_OUT_OF_RANGE);
    }

    if (response_r1 & SDWFF3_OCR_ADDR_MISALIGNED)
    {
        return (SDWFF3_ADDR_MISALIGNED);
    }

    if (response_r1 & SDWFF3_OCR_BLOCK_LEN_ERR)
    {
        return (SDWFF3_BLOCK_LEN_ERR);
    }

    if (response_r1 & SDWFF3_OCR_ERASE_SEQ_ERR)
    {
        return (SDWFF3_ERASE_SEQ_ERR);
    }

    if (response_r1 & SDWFF3_OCR_BAD_ERASE_PARAM)
    {
        return (SDWFF3_BAD_ERASE_PARAM);
    }

    if (response_r1 & SDWFF3_OCR_WRITE_PROT_VIOLATION)
    {
        return (SDWFF3_WRITE_PROT_VIOLATION);
    }

    if (response_r1 & SDWFF3_OCR_LOCK_UNLOCK_FAILED)
    {
        return (SDWFF3_LOCK_UNLOCK_FAILED);
    }

    if (response_r1 & SDWFF3_OCR_COM_CRC_FAILED)
    {
        return (SDWFF3_COM_CRC_FAILED);
    }

    if (response_r1 & SDWFF3_OCR_ILLEGAL_CMD)
    {
        return (SDWFF3_ILLEGAL_CMD);
    }

    if (response_r1 & SDWFF3_OCR_CARD_ECC_FAILED)
    {
        return (SDWFF3_CARD_ECC_FAILED);
    }

    if (response_r1 & SDWFF3_OCR_CC_ERROR)
    {
        return (SDWFF3_CC_ERROR);
    }

    if (response_r1 & SDWFF3_OCR_GENERAL_UNKNOWN_ERROR)
    {
        return (SDWFF3_GENERAL_UNKNOWN_ERROR);
    }

    if (response_r1 & SDWFF3_OCR_STREAM_READ_UNDERRUN)
    {
        return (SDWFF3_STREAM_READ_UNDERRUN);
    }

    if (response_r1 & SDWFF3_OCR_STREAM_WRITE_OVERRUN)
    {
        return (SDWFF3_STREAM_WRITE_OVERRUN);
    }

    if (response_r1 & SDWFF3_OCR_CID_CSD_OVERWRIETE)
    {
        return (SDWFF3_CID_CSD_OVERWRITE);
    }

    if (response_r1 & SDWFF3_OCR_WP_ERASE_SKIP)
    {
        return (SDWFF3_WP_ERASE_SKIP);
    }

    if (response_r1 & SDWFF3_OCR_CARD_ECC_DISABLED)
    {
        return (SDWFF3_CARD_ECC_DISABLED);
    }

    if (response_r1 & SDWFF3_OCR_ERASE_RESET)
    {
        return (SDWFF3_ERASE_RESET);
    }

    if (response_r1 & SDWFF3_OCR_AKE_SEQ_ERROR)
    {
        return (SDWFF3_AKE_SEQ_ERROR);
    }

    return (errorstatus);
}

/**
 * @brief  Checks for error conditions for R3 (OCR).
 *   response.
 * @param  None
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdResp3Error(void)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t status;

    status = SDWFF3_readStatusReg();

    while (!(status & (SDWFF3_STATUS_CMD_CRC_ERR | SDWFF3_STATUS_CMD_COMPLETE | SDWFF3_STATUS_CMD_TIMEOUT_ERR)))
    {
        status = SDWFF3_readStatusReg();
    }

    if (status & SDWFF3_STATUS_CMD_TIMEOUT_ERR)
    {
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_TIMEOUT_ERR);
        return (errorstatus);
    }
    /* Clear all the static flags */
    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);
    return (errorstatus);
}

/**
 * @brief  Checks for error conditions for R2 (CID or CSD).
 *   response.
 * @param  None
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdResp2Error(void)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t status;

    status = SDWFF3_readStatusReg();

    while (!(status & (SDWFF3_STATUS_CMD_CRC_ERR | SDWFF3_STATUS_CMD_COMPLETE | SDWFF3_STATUS_CMD_TIMEOUT_ERR)))
    {
        status = SDWFF3_readStatusReg();
    }

    if (status & SDWFF3_STATUS_CMD_TIMEOUT_ERR)
    {
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_TIMEOUT_ERR);
        return (errorstatus);
    }
    else if (status & SDWFF3_STATUS_CMD_CRC_ERR)
    {
        errorstatus = SDWFF3_CMD_CRC_FAIL;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_CRC_ERR);
        return (errorstatus);
    }

    /* Clear all the static flags */
    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    return (errorstatus);
}

/**
 * @brief  Checks for error conditions for R6 (RCA).
 *   response.
 * @param  cmd: The sent command index.
 * @param  prca: pointer to the variable that will contain the SD
 *   card relative address RCA.
 * @retval SDWFF3_Status: SD Card Error code.
 */
static SDWFF3_Status SDWFF3_CmdResp6Error(SDWFF3_Object *object)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t status;
    uint32_t response_r1;

    status = SDWFF3_readStatusReg();

    while (!(status & (SDWFF3_STATUS_CMD_CRC_ERR | SDWFF3_STATUS_CMD_COMPLETE | SDWFF3_STATUS_CMD_TIMEOUT_ERR)))
    {
        status = SDWFF3_readStatusReg();
    }

    if (status & SDWFF3_STATUS_CMD_TIMEOUT_ERR)
    {
        errorstatus = SDWFF3_CMD_RSP_TIMEOUT;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_TIMEOUT_ERR);
        return (errorstatus);
    }
    else if (status & SDWFF3_STATUS_CMD_CRC_ERR)
    {
        errorstatus = SDWFF3_CMD_CRC_FAIL;
        SDWFF3_statusClear(SDWFF3_STATUS_CMD_CRC_ERR);
        return (errorstatus);
    }

    /* Clear all the static flags */
    SDWFF3_statusClear(SDWFF3_STATUS_ALL_ERRORS);

    /* We have received response, retrieve it.  */
    SDWFF3_readResp(SDWFF3_CMDRSP_48BITS);
    response_r1 = cmd_resp[0];

    if (SDWFF3_ALLZERO ==
        (response_r1 & (SDWFF3_R6_GENERAL_UNKNOWN_ERROR | SDWFF3_R6_ILLEGAL_CMD | SDWFF3_R6_COM_CRC_FAILED)))
    {
        object->rca = (response_r1 >> 16);
        return (errorstatus);
    }

    if (response_r1 & SDWFF3_R6_GENERAL_UNKNOWN_ERROR)
    {
        return (SDWFF3_GENERAL_UNKNOWN_ERROR);
    }

    if (response_r1 & SDWFF3_R6_ILLEGAL_CMD)
    {
        return (SDWFF3_ILLEGAL_CMD);
    }

    if (response_r1 & SDWFF3_R6_COM_CRC_FAILED)
    {
        return (SDWFF3_COM_CRC_FAILED);
    }

    return (errorstatus);
}

/**
 * @brief  Returns information about specific card.
 * @param  cardinfo : pointer to a SDWFF3_CardInfo structure
 *   that contains all SD card information.
 * @retval SDWFF3_Status: SD Card Error code.
 */
void SDWFF3_GetCardInfo(SDWFF3_Object *object)
{
    uint32_t c_size_csd2;
    uint32_t c_size_csd1;
    uint32_t c_size;
    uint32_t c_size_mult;
    uint32_t mult;

    object->tranSpeed    = (uint8_t)(object->csd[3] & 0x000000FFU);
    object->maxBlockSize = ((uint32_t)1U) << ((object->csd[2] & 0x000F0000U) >> 16U);

    if ((object->csd[2] & 0x00008000U) >> 15U)
    {
        object->partialBlock = true;
    }
    else
    {
        object->partialBlock = false;
    }

    if (((object->csd[3] & 0xC0000000U) >> 30U) == 0x1)
    {
        c_size_csd2        = (object->csd[2] & 0x0000003FU);
        c_size_csd1        = ((object->csd[1] & 0xFFFF0000U) >> 16U);
        c_size             = (c_size_csd2 << 16) | c_size_csd1;
        object->numSectors = c_size + 1;
    }
    else
    {
        c_size_csd2        = (object->csd[2] & 0x000003FFU);
        c_size_csd1        = ((object->csd[1] & 0xC0000000U) >> 30U);
        c_size             = (c_size_csd2 << 2) | c_size_csd1;
        c_size_mult        = ((object->csd[1] & 0x00038000U) >> 15U);
        mult               = 1 << (c_size_mult + 2);
        object->numSectors = (c_size + 1) * mult;
    }
}

/**
 * @brief  Find the SD card SCR register value.
 * @param  rca: selected card address.
 * @param  pscr: pointer to the buffer that will contain the SCR value.
 * @retval SDWFF3_Status: SD Card Error code.
 */
SDWFF3_Status SDWFF3_FindSCR(SDWFF3_Object *object)
{
    SDWFF3_Status errorstatus = SDWFF3_OK;
    uint32_t cmd_arg          = 0;
    uint32_t status           = 0;

    /* Send CMD55 APP_CMD with argument as card's RCA */

    trans_cmd->cdm_index = SDWFF3_CMD(55);
    trans_cmd->resp_type = SDWFF3_CMDRSP_48BITS;
    cmd_arg              = (object->rca << 16U);
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(55));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    SDWFF3_SetBLKsize(8);
    SDWFF3_SetNumBLK(1);

    /* Send CMD51 APP_CMD with argument as card's RCA */

    trans_cmd->cdm_index    = SDWFF3_CMD(51);
    trans_cmd->resp_type    = SDWFF3_CMDRSP_48BITS;
    trans_cmd->blk_cnt_en   = 0x01;
    trans_cmd->multi_block  = 0x00;
    trans_cmd->data_present = 0x01;
    trans_cmd->data_dir     = 0x01;
    trans_cmd->dma_enable   = 0x00;
    cmd_arg                 = 0;
    SDWFF3_sendCommand(cmd_arg);

    errorstatus = SDWFF3_CmdResp1Error(SDWFF3_CMD(51));

    if (errorstatus != SDWFF3_OK)
    {
        return (errorstatus);
    }

    uint32_t buf_ready_for_data = SDMMC_PSTATE_DATI_M | SDMMC_PSTATE_DLA_M | SDMMC_PSTATE_RTA_M | SDMMC_PSTATE_BRE_M;

    while (status != buf_ready_for_data)
    {
        status = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_PSTATE);
        status &= buf_ready_for_data;
    }

    object->scr[0] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);
    object->scr[1] = HWREG(SDWFF3_hwAttrs_P->baseAddr + SDMMC_O_DATA);

    object->maxBusWidth = ((object->scr[0] & 0x000F0000) >> 16);

    SDWFF3_SetBLKsize(512);

    return (errorstatus);
}

void SDWFF3_SetBLKsize(uint32_t blk_len)
{
    _setField(blk_len,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_BLK,
              SDMMC_BLK_BLEN_M,
              SDMMC_BLK_BLEN_S,
              !SDWFF3_REG_IS_WR_ONLY);
}

void SDWFF3_SetNumBLK(uint32_t num_blk)
{
    _setField(num_blk,
              SDWFF3_hwAttrs_P->baseAddr,
              SDMMC_O_BLK,
              SDMMC_BLK_NBLK_M,
              SDMMC_BLK_NBLK_S,
              !SDWFF3_REG_IS_WR_ONLY);
}
