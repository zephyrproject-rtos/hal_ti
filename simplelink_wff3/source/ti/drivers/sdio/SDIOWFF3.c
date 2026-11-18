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
 *  ======== SDIOWFF3.c ========
 */

#include <ti/drivers/sdio/SDIOWFF3.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/dma/DMAWFF3.h>
#include <ti/drivers/GPIO.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/dma.h)

/* ========================================================================== */
/*                          Local Defines                                     */
/* ========================================================================== */

#define SDIOWFF3_ALL_STATUS       ((uint32_t)0xFFFFFFFF)
#define SDIOWFF3_REG_IS_WR_ONLY   1
#define SDIOWFF3_HEADER_LEN_WORDS (SDIOWFF3_attrs_P->headerLen >> 2)
#define SDIOWFF3_ALL_INTR         0xD63F

/* ========================================================================== */
/*                          Global Variable                                   */
/* ========================================================================== */

SDIO_Handle SDIOWFF3_handle_P;
SDIOWFF3_HwAttrs *SDIOWFF3_attrs_P;
SDIOWFF3_Object *SDIOWFF3_object_P;
SDIOWFF3_Param *SDIOWFF3_param_P;
Power_NotifyObj SDIOWFF3_NotifyObj;

/* ========================================================================== */
/*                          Local Function Prototypes                         */
/* ========================================================================== */
static void SDIOWFF3_initSdioHw(void);
static void SDIOWFF3_configIomux(void);
static void SDIOWFF3_overrideIomux(void);
static void SDIOWFF3_initParam(SDIOWFF3_Object *object);
static int SDIOWFF3_notifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static void SDIOWFF3_irqEnable(uint32_t statusBits);
static void SDIOWFF3_irqDisable(uint32_t statusBits);
static uint32_t SDIOWFF3_statusRead(void);
static void SDIOWFF3_statusClear(uint32_t statusBits);
static void SDIOWFF3_HwipFxn(uintptr_t arg);
static void SDIOWFF3_writeFifo(uint32_t numByte, uint32_t *data_point);
static void SDIOWFF3_readFifo(uint32_t numByte, uint32_t *data_point);
static void SDIOWFF3_configTxThreshold(int_fast32_t numByte);
static void SDIOWFF3_cardReset(void);
static void SDIOWFF3_rxCrcError(void);
static void SDIOWFF3_cardInitiated(void);
static void SDIOWFF3_sleep(void);
static void SDIOWFF3_wakeup(void);

/* Extern globals */
extern const SDIO_Config SDIO_config[];
extern const uint_least8_t SDIO_count;

/* Static globals */
static bool isInitialized = false;

/* ========================================================================== */
/*                          API Implementation                                */
/* ========================================================================== */

/*
 *  ======== SDIOWFF3_init ========
 */
void SDIO_init()
{
    if (!isInitialized)
    {
        isInitialized = true;
    }
}

/*
 *  ======== SDMMCWFF3_open ========
 */
SDIO_Handle SDIO_open(uint_least8_t index, SDIO_Params *params)
{
    uintptr_t key;
    SDIOWFF3_param_P         = (SDIOWFF3_Param *)params;
    uintptr_t clientArg_temp = (uintptr_t)NULL;

    if (index > SDIO_count)
    {
        return NULL;
    }

    SDIOWFF3_handle_P = (SDIO_Handle) & (SDIO_config[index]);
    SDIOWFF3_object_P = (SDIOWFF3_Object *)SDIOWFF3_handle_P->object;
    SDIOWFF3_attrs_P  = (SDIOWFF3_HwAttrs *)SDIOWFF3_handle_P->hwAttrs;

    key = HwiP_disable();

    if (!isInitialized || SDIOWFF3_object_P->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }

    SDIOWFF3_object_P->isOpen = true;

    HwiP_restore(key);

    /* Init parameters for interrupts handler */
    HwiP_Params_init(&(SDIOWFF3_attrs_P->hwiPrms));
    SDIOWFF3_attrs_P->hwiPrms.priority = SDIOWFF3_attrs_P->intPriority;

    if (SDIOWFF3_param_P != NULL)
    {
        /*
         * Application callback function
         * SDIOCallbackFxn will be call for each event form enum 'SDIOWFF3_Event_Type'
         */
        if (SDIOWFF3_param_P->SDIOWFF3_CallbackFxn != NULL)
        {
            SDIOWFF3_attrs_P->SDIOWFF3_CBFunction = SDIOWFF3_param_P->SDIOWFF3_CallbackFxn;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }

    /*
     * Register to be called when Host goes to sleep and wake-up
     * SDWFF3_notifyFxn function will be called
     */
    Power_registerNotify(&(SDIOWFF3_NotifyObj),
                         PowerWFF3_ENTERING_SLEEP | PowerWFF3_AWAKE_SLEEP,
                         SDIOWFF3_notifyFxn,
                         clientArg_temp);

    /* Initialize the SDIO hardware module */
    SDIOWFF3_initSdioHw();

    /* Configure selected GPIO pins */
    SDIOWFF3_configIomux();

    /* Enable SDIO IRQ */
    HwiP_construct(&(SDIOWFF3_attrs_P->hwiStruct),
                   SDIOWFF3_attrs_P->intNum,
                   SDIOWFF3_HwipFxn,
                   &(SDIOWFF3_attrs_P->hwiPrms));

    return SDIOWFF3_handle_P;
}

/*
 *  ======== SDIOWFF3_close ========
 */
void SDIO_close(SDIO_Handle handle)
{
    /* Disable SDIO IRQ */
    HwiP_destruct(&(SDIOWFF3_attrs_P->hwiStruct));

    SDIOWFF3_overrideIomux();

    Power_unregisterNotify(&(SDIOWFF3_NotifyObj));

    Power_releaseDependency(SDIOWFF3_attrs_P->powerID);
    SDIOWFF3_object_P->isOpen = false;
}

/*
 *  ======== SDIOWFF3_write ========
 */
int_fast16_t SDIO_write(SDIO_Handle handle, void *buf, int_fast32_t numByte)
{
    if (!(SDIOWFF3_object_P->isOpen))
    {
        return (SDIO_STATUS_ERROR);
    }

    if (!(SDIOWFF3_object_P->cardInitiated))
    {
        return (SDIO_STATUS_ERROR);
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    SDIOWFF3_configTxThreshold(numByte);

    DMAConfigureChannel(SDIOWFF3_attrs_P->txDmaChannel,
                        32,
                        DMA_WORD_SIZE_4B,
                        DMA_CONFIG_DST_PTR_FIFO | DMA_CONFIG_TX | DMA_CONFIG_CLEAR_AT_JOB_START);

    SDIOWFF3_writeFifo(numByte, (uint32_t *)buf);

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    return SDIO_STATUS_SUCCESS;
}

/*
 *  ======== SDIOWFF3_read ========
 */
int_fast16_t SDIO_read(SDIO_Handle handle, void *buf, int_fast32_t numByte)
{
    if (!(SDIOWFF3_object_P->isOpen))
    {
        return (SDIO_STATUS_ERROR);
    }

    if (!(SDIOWFF3_object_P->cardInitiated))
    {
        return (SDIO_STATUS_ERROR);
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    DMAConfigureChannel(SDIOWFF3_attrs_P->rxDmaChannel,
                        32,
                        DMA_WORD_SIZE_4B,
                        DMA_CONFIG_SRC_PTR_FIFO | DMA_CONFIG_CLEAR_AT_JOB_START); // read from card

    SDIOWFF3_readFifo(numByte, (uint32_t *)buf);

    SDIOWFF3_statusClear(SDIO_CARD_FN1_IRQSTA_RXALMSFULL_M);
    SDIOWFF3_irqEnable(SDIO_CARD_FN1_IRQSTA_RXALMSFULL_M);

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    return SDIO_STATUS_SUCCESS;
}

bool SDIOWFF3_isSdioInitialized()
{
    return (SDIOWFF3_object_P->cardInitiated);
}

/* ========================================================================== */
/*                     Local Function Implementation                          */
/* ========================================================================== */

void SDIOWFF3_initSdioHw()
{
    /* Enable the clock of SDIO hardware module */
    Power_setDependency(SDIOWFF3_attrs_P->powerID);

    _setField(0x01,
              SDIOWFF3_attrs_P->FN0baseAddr,
              SDIO_CORE_O_CCCR08,
              SDIO_CORE_CCCR08_E4MI_M,
              SDIO_CORE_CCCR08_E4MI_S,
              !SDIOWFF3_REG_IS_WR_ONLY);
    _setField(0x01,
              SDIOWFF3_attrs_P->FN0baseAddr,
              SDIO_CORE_O_CCCR14,
              SDIO_CORE_CCCR14_EAI_M,
              SDIO_CORE_CCCR14_EAI_S,
              !SDIOWFF3_REG_IS_WR_ONLY);

    /* Config DMA-SDIO block size */
    _setField(0x05,
              SDIOWFF3_attrs_P->FN1baseAddr,
              SDIO_CARD_FN1_O_DMABLKTHR,
              SDIO_CARD_FN1_DMABLKTHR_RXDMABLK_M,
              SDIO_CARD_FN1_DMABLKTHR_RXDMABLK_S,
              !SDIOWFF3_REG_IS_WR_ONLY);
    _setField(0x05,
              SDIOWFF3_attrs_P->FN1baseAddr,
              SDIO_CARD_FN1_O_DMABLKTHR,
              SDIO_CARD_FN1_DMABLKTHR_TXDMABLK_M,
              SDIO_CARD_FN1_DMABLKTHR_TXDMABLK_S,
              !SDIOWFF3_REG_IS_WR_ONLY);

    HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_RXTHR) = SDIOWFF3_attrs_P->thresholdLen;

    /* Set Rx and Tx DMA channels to input and output respectively */
    DMAConfigureChannel(SDIOWFF3_attrs_P->txDmaChannel, DMAWFF3_BLOCK_SIZE_4B, DMAWFF3_WORD_SIZE_4B, DMA_CONFIG_TX);
    DMAConfigureChannel(SDIOWFF3_attrs_P->rxDmaChannel, DMAWFF3_BLOCK_SIZE_4B, DMAWFF3_WORD_SIZE_4B, DMA_CONFIG_RX);

    SDIOWFF3_statusClear(SDIOWFF3_ALL_STATUS);
    SDIOWFF3_irqEnable(SDIOWFF3_ALL_INTR);
}

void SDIOWFF3_configTxThreshold(int_fast32_t numByte)
{
    if (numByte > 0x80) // Tx FIFO length is 128 Bytes
    {
        HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_TXIRQTHR) = 0x80;
    }
    else
    {
        HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_TXIRQTHR) = numByte;
    }
}

void SDIOWFF3_writeFifo(uint32_t numByte, uint32_t *data_point)
{

    uint32_t status     = 0;
    uint32_t *dest_addr = (uint32_t *)(SDIOWFF3_attrs_P->FN1baseAddr + SDIO_CARD_FN1_O_DATAFIFO);

    DMAStartTransaction(SDIOWFF3_attrs_P->txDmaChannel, data_point, dest_addr, (uint16_t)numByte, false);
    do
    {
        status = DMAGetChannelStatus(SDIOWFF3_attrs_P->txDmaChannel);
    } while (status != DMA_HW_EVT_TRANS_DONE);
}

void SDIOWFF3_readFifo(uint32_t numByte, uint32_t *data_point)
{
    uint32_t status        = 0;
    uint32_t *source_addr  = (uint32_t *)(SDIOWFF3_attrs_P->FN1baseAddr + SDIO_CARD_FN1_O_DATAFIFO);
    uint32_t num_data_fifo = 0;
    uint32_t num_words;

    DMAStartTransaction(SDIOWFF3_attrs_P->rxDmaChannel, source_addr, data_point, (uint16_t)numByte, false);
    do
    {
        status = DMAGetChannelStatus(SDIOWFF3_attrs_P->rxDmaChannel);
    } while (status != DMA_HW_EVT_TRANS_DONE);
}

static void SDIOWFF3_HwipFxn(uintptr_t arg)
{
    uint32_t status;
    uint32_t Rx_data_header;
    uint32_t header_of_rx;
    uint32_t header_num_byte;

    status = SDIOWFF3_statusRead();

    if (status & SDIO_CARD_FN1_IRQSTA_RXALMSFULL_M)
    {
        SDIOWFF3_irqDisable(SDIO_CARD_FN1_IRQSTA_RXALMSFULL_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_DATA_IN_RX_FIFO);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_FN1EN_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_FN1EN_M);
        SDIOWFF3_cardInitiated();
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_CARD_INIT);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_RXBUFOVR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_RXBUFOVR_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_RX_BUFF_OVERRUN);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_RXBUFUNR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_RXBUFUNR_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_RX_BUFF_UNDERRUN);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_TXBUFOVR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_TXBUFOVR_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_TX_BUFF_OVERRUN);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_TXBUFUNR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_TXBUFUNR_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_TX_BUFF_UNDERRUN);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_HCIACK_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_HCIACK_M);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_HCINACK_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_HCINACK_M);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_HCIWRRET_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_HCIWRRET_M);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_PHYIFERR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_PHYIFERR_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_HOST_WRONG_ACCESS);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_CARDRST_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_CARDRST_M);
        SDIOWFF3_cardReset();
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_CARD_DEINIT);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_PHYINT_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_PHYINT_M);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_CRCERR_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_CRCERR_M);
        SDIOWFF3_rxCrcError();
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_RX_CRC_ERROR);
    }
    if (status & SDIO_CARD_FN1_IRQSTA_HOST2CORE_M)
    {
        SDIOWFF3_statusClear(status & SDIO_CARD_FN1_IRQSTA_HOST2CORE_M);
        SDIOWFF3_attrs_P->SDIOWFF3_CBFunction(SDIOWFF3_handle_P, SDIOWFF3_HOST_SENT_MSG);
    }
}

void SDIOWFF3_rxCrcError()
{
    DMAWFF3_disableChannel(SDIOWFF3_attrs_P->rxDmaChannel);

    ClockP_usleep(1); // reset take 50ns

    DMAInitChannel(SDIOWFF3_attrs_P->rxDmaChannel, DMA_PERIPH_SDIO);

    DMAWFF3_initChannel(SDIOWFF3_attrs_P->rxDmaChannel);
}

void SDIOWFF3_cardReset()
{
    SDIOWFF3_irqDisable(SDIOWFF3_ALL_STATUS);

    DMAWFF3_disableChannel(SDIOWFF3_attrs_P->txDmaChannel);
    DMAWFF3_disableChannel(SDIOWFF3_attrs_P->rxDmaChannel);

    HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_RSTREQ) = 0x01;

    Power_releaseDependency(SDIOWFF3_attrs_P->powerID);

    ClockP_usleep(1); // rst occur 50ns

    /* Initialize the SDIO hardware module - FN1 only*/
    SDIOWFF3_initSdioHw();

    DMAInitChannel(SDIOWFF3_attrs_P->txDmaChannel, DMA_PERIPH_SDIO);
    DMAInitChannel(SDIOWFF3_attrs_P->rxDmaChannel, DMA_PERIPH_SDIO);

    DMAWFF3_initChannel(SDIOWFF3_attrs_P->txDmaChannel);
    DMAWFF3_initChannel(SDIOWFF3_attrs_P->rxDmaChannel);

    SDIOWFF3_object_P->cardInitiated = false;
}

void SDIOWFF3_cardInitiated()
{
    _setField(0x01,
              SDIOWFF3_attrs_P->FN0baseAddr,
              SDIO_CORE_O_CCCR00,
              SDIO_CORE_CCCR00_FN1RDY_M,
              SDIO_CORE_CCCR00_FN1RDY_S,
              !SDIOWFF3_REG_IS_WR_ONLY);
    SDIOWFF3_object_P->cardInitiated = true;
}

static int SDIOWFF3_notifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    if (eventType == PowerWFF3_ENTERING_SLEEP)
    {
        SDIOWFF3_sleep();
    }
    else if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        SDIOWFF3_wakeup();
    }
    return (Power_NOTIFYDONE);
}

void SDIOWFF3_sleep()
{
    HwiP_destruct(&(SDIOWFF3_attrs_P->hwiStruct));

    SDIOWFF3_overrideIomux();

    Power_releaseDependency(SDIOWFF3_attrs_P->powerID);
}

void SDIOWFF3_wakeup()
{
    /* Initialize the SDIO hardware module */
    SDIOWFF3_initSdioHw();

    /* Configure selected GPIO pins */
    SDIOWFF3_configIomux();

    /* Enable SDIO IRQ */
    HwiP_construct(&(SDIOWFF3_attrs_P->hwiStruct),
                   SDIOWFF3_attrs_P->intNum,
                   SDIOWFF3_HwipFxn,
                   &(SDIOWFF3_attrs_P->hwiPrms));
}

void SDIOWFF3_irqDisable(uint32_t statusBits)
{
    uint32_t ret_reg;

    ret_reg = HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQMASK);
    HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQMASK) = ret_reg | statusBits;
}

void SDIOWFF3_irqEnable(uint32_t statusBits)
{
    uint32_t ret_reg;

    ret_reg = HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQMASK);
    HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQMASK) = ret_reg & (~statusBits);
}

void SDIOWFF3_statusClear(uint32_t statusBits)
{
    HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQCLR) = statusBits;
}

uint32_t SDIOWFF3_statusRead()
{
    return (HWREG(SDIOWFF3_attrs_P -> FN1baseAddr + SDIO_CARD_FN1_O_IRQSTA));
}

void SDIOWFF3_initParam(SDIOWFF3_Object *object)
{
    object->isOpen        = false;
    object->cardInitiated = false;
}

void SDIOWFF3_configIomux()
{

    /* ======== config clock GPIO ======== */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->clkPin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->clkPinMux);

    /* ======== config command GPIO ======== */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->cmdPin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->cmdPinMux);

    /* ======== config data 0 GPIO ========= */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->data0Pin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->data0PinMux);

    /* ======== config data 1 GPIO ========= */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->data1Pin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->data1PinMux);

    /* ======== config data 2 GPIO ========= */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->data2Pin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->data2PinMux);

    /* ======== config data 3 GPIO ========= */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->data3Pin, IOMUX_GPIO2CFG_IE_M, SDIOWFF3_attrs_P->data3PinMux);

    /* ======== config OOB irq GPIO ======== */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->irqPin, IOMUX_GPIO17CFG_IOSTR_LOW, SDIOWFF3_attrs_P->irqPinMux);
}

void SDIOWFF3_overrideIomux()
{
    /* ======== reset config clock GPIO ========== */
    GPIO_resetConfig(SDIOWFF3_attrs_P->clkPin);

    /* ======== reset config command GPIO ======== */
    GPIO_resetConfig(SDIOWFF3_attrs_P->cmdPin);

    /* ======== override data 0 GPIO ============= */
    GPIO_setConfigAndMux(SDIOWFF3_attrs_P->data0Pin,
                         IOMUX_GPIO2CFG_OUTDISOVREN_M | IOMUX_GPIO20CFG_IOSTR_M | IOMUX_GPIO2CTL_OUTOVREN_M,
                         SDIOWFF3_attrs_P->data0PinMux);

    /* ======== reset config data 1 GPIO ========= */
    GPIO_resetConfig(SDIOWFF3_attrs_P->data1Pin);

    /* ======== reset config data 2 GPIO ========= */
    GPIO_resetConfig(SDIOWFF3_attrs_P->data2Pin);

    /* ======== reset config data 3 GPIO ========= */
    GPIO_resetConfig(SDIOWFF3_attrs_P->data3Pin);

    /* ======== reset config OOB irq GPIO ======== */
    GPIO_resetConfig(SDIOWFF3_attrs_P->irqPin);
}
