/*This file is AUTO GENERATED, DO NOT EDIT manually*/

/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

/**
 * @defgroup DL_UNICOMMI2CC_AM13E230X  Driverlib I2CC API
 * @ingroup DL_AM13E230X
 *
 * @{
 */

#ifndef DL_UNICOMMI2CC_H
#define DL_UNICOMMI2CC_H

#include <stdbool.h>
#include <stdint.h>

#include "soc.h"
#include "dl_common.h"
#include "hw_unicommi2cc.h"
#include "dl_unicomm.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @name DL_I2C_CONTROLLER_MACROS
 *  @anchor DL_I2C_CONTROLLER_MACROS
 *  Macros to retain compatibility with standalone dl_i2c controller APIs
 *  @{
 */
/*! Redirects to @ref DL_I2CC_STATUS_BUSY */
#define DL_I2C_CONTROLLER_STATUS_BUSY                  DL_I2CC_STATUS_BUSY
/*! Redirects to @ref DL_I2CC_STATUS_ERROR */
#define DL_I2C_CONTROLLER_STATUS_ERROR                 DL_I2CC_STATUS_ERROR
/*! Redirects to @ref DL_I2CC_STATUS_ADDR_ACK */
#define DL_I2C_CONTROLLER_STATUS_ADDR_ACK              DL_I2CC_STATUS_ADDR_ACK
/*! Redirects to @ref DL_I2CC_STATUS_DATA_ACK */
#define DL_I2C_CONTROLLER_STATUS_DATA_ACK              DL_I2CC_STATUS_DATA_ACK
/*! Redirects to @ref DL_I2CC_STATUS_ARBITRATION_LOST */
#define DL_I2C_CONTROLLER_STATUS_ARBITRATION_LOST      DL_I2CC_STATUS_ARBITRATION_LOST
/*! Redirects to @ref DL_I2CC_STATUS_IDLE */
#define DL_I2C_CONTROLLER_STATUS_IDLE                  DL_I2CC_STATUS_IDLE
/*! Redirects to @ref DL_I2CC_STATUS_BUSY_BUS */
#define DL_I2C_CONTROLLER_STATUS_BUSY_BUS              DL_I2CC_STATUS_BUSY_BUS
/*! Redirects to @ref DL_I2CC_INTERRUPT_RX_DONE */
#define DL_I2C_INTERRUPT_CONTROLLER_RX_DONE            DL_I2CC_INTERRUPT_RX_DONE
/*! Redirects to @ref DL_I2CC_INTERRUPT_TX_DONE */
#define DL_I2C_INTERRUPT_CONTROLLER_TX_DONE            DL_I2CC_INTERRUPT_TX_DONE
/*! Redirects to @ref DL_I2CC_INTERRUPT_NACK */
#define DL_I2C_INTERRUPT_CONTROLLER_NACK               DL_I2CC_INTERRUPT_NACK
/*! Redirects to @ref DL_I2CC_INTERRUPT_START */
#define DL_I2C_INTERRUPT_CONTROLLER_START              DL_I2CC_INTERRUPT_START
/*! Redirects to @ref DL_I2CC_INTERRUPT_STOP */
#define DL_I2C_INTERRUPT_CONTROLLER_STOP               DL_I2CC_INTERRUPT_STOP
/*! Redirects to @ref DL_I2CC_DIRECTION */
#define DL_I2C_CONTROLLER_DIRECTION                    DL_I2CC_DIRECTION
/*! Redirects to @ref DL_I2CC_ADDRESSING_MODE */
#define DL_I2C_CONTROLLER_ADDRESSING_MODE              DL_I2CC_ADDRESSING_MODE
/*! Redirects to @ref DL_I2CC_PEC_STATUS */
#define DL_I2C_CONTROLLER_PEC_STATUS                   DL_I2CC_PEC_STATUS
/*! Redirects to @ref DL_I2CC_PEC_CHECK_ERROR */
#define DL_I2C_CONTROLLER_PEC_CHECK_ERROR              DL_I2CC_PEC_CHECK_ERROR
/*! Redirects to @ref DL_I2CC_SCL */
#define DL_I2C_CONTROLLER_SCL                          DL_I2CC_SCL
/*! Redirects to @ref DL_I2CC_SDA */
#define DL_I2C_CONTROLLER_SDA                          DL_I2CC_SDA
/*! Redirects to @ref DL_I2CC_INTERRUPT_RXFIFO_TRIGGER */
#define DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_TRIGGER     DL_I2CC_INTERRUPT_RXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_INTERRUPT_TXFIFO_TRIGGER */
#define DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER     DL_I2CC_INTERRUPT_TXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_INTERRUPT_RXFIFO_FULL */
#define DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_FULL        DL_I2CC_INTERRUPT_RXFIFO_FULL
/*! Redirects to @ref DL_I2CC_INTERRUPT_TXFIFO_EMPTY */
#define DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_EMPTY       DL_I2CC_INTERRUPT_TXFIFO_EMPTY
/*! Redirects to @ref DL_I2CC_INTERRUPT_ARBITRATION_LOST */
#define DL_I2C_INTERRUPT_CONTROLLER_ARBITRATION_LOST   DL_I2CC_INTERRUPT_ARBITRATION_LOST
/*! Redirects to @ref DL_I2CC_INTERRUPT_EVENT1_DMA_DONE */
#define DL_I2C_INTERRUPT_CONTROLLER_EVENT1_DMA_DONE    DL_I2CC_INTERRUPT_EVENT1_DMA_DONE
/*! Redirects to @ref DL_I2CC_INTERRUPT_EVENT2_DMA_DONE */
#define DL_I2C_INTERRUPT_CONTROLLER_EVENT2_DMA_DONE    DL_I2CC_INTERRUPT_EVENT2_DMA_DONE
/*! Redirects to @ref DL_I2CC_INTERRUPT_PEC_RX_ERROR */
#define DL_I2C_INTERRUPT_CONTROLLER_PEC_RX_ERROR       DL_I2CC_INTERRUPT_PEC_RX_ERROR
/*! Redirects to @ref DL_I2CC_DMA_INTERRUPT_TXFIFO_TRIGGER */
#define DL_I2C_DMA_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER DL_I2CC_DMA_INTERRUPT_TXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_DMA_INTERRUPT_RXFIFO_TRIGGER */
#define DL_I2C_DMA_INTERRUPT_CONTROLLER_RXFIFO_TRIGGER DL_I2CC_DMA_INTERRUPT_RXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_DIRECTION_TX */
#define DL_I2C_CONTROLLER_DIRECTION_TX                 DL_I2CC_DIRECTION_TX
/*! Redirects to @ref DL_I2CC_DIRECTION_RX */
#define DL_I2C_CONTROLLER_DIRECTION_RX                 DL_I2CC_DIRECTION_RX
/*! Redirects to @ref DL_I2CC_ADDRESSING_MODE_7_BIT */
#define DL_I2C_CONTROLLER_ADDRESSING_MODE_7_BIT        DL_I2CC_ADDRESSING_MODE_7_BIT
/*! Redirects to @ref DL_I2CC_ADDRESSING_MODE_10_BIT */
#define DL_I2C_CONTROLLER_ADDRESSING_MODE_10_BIT       DL_I2CC_ADDRESSING_MODE_10_BIT
/*! Redirects to @ref DL_I2CC_PEC_STATUS_CHECKED */
#define DL_I2C_CONTROLLER_PEC_STATUS_CHECKED           DL_I2CC_PEC_STATUS_CHECKED
/*! Redirects to @ref DL_I2CC_PEC_STATUS_NOT_CHECKED */
#define DL_I2C_CONTROLLER_PEC_STATUS_NOT_CHECKED       DL_I2CC_PEC_STATUS_NOT_CHECKED
/*! Redirects to @ref DL_I2CC_PEC_CHECK_ERROR_SET */
#define DL_I2C_CONTROLLER_PEC_CHECK_ERROR_SET          DL_I2CC_PEC_CHECK_ERROR_SET
/*! Redirects to @ref DL_I2CC_PEC_CHECK_ERROR_CLEARED */
#define DL_I2C_CONTROLLER_PEC_CHECK_ERROR_CLEARED      DL_I2CC_PEC_CHECK_ERROR_CLEARED
/*! Redirects to @ref DL_I2CC_SCL_HIGH */
#define DL_I2C_CONTROLLER_SCL_HIGH                     DL_I2CC_SCL_HIGH
/*! Redirects to @ref DL_I2CC_SCL_LOW */
#define DL_I2C_CONTROLLER_SCL_LOW                      DL_I2CC_SCL_LOW
/*! Redirects to @ref DL_I2CC_SDA_HIGH */
#define DL_I2C_CONTROLLER_SDA_HIGH                     DL_I2CC_SDA_HIGH
/*! Redirects to @ref DL_I2CC_SDA_LOW */
#define DL_I2C_CONTROLLER_SDA_LOW                      DL_I2CC_SDA_LOW
/*! Redirects to @ref DL_I2CC_START_ENABLE */
#define DL_I2C_CONTROLLER_START_ENABLE                 DL_I2CC_START_ENABLE
/*! Redirects to @ref DL_I2CC_START_DISABLE */
#define DL_I2C_CONTROLLER_START_DISABLE                DL_I2CC_START_DISABLE
/*! Redirects to @ref DL_I2CC_ACK_ENABLE */
#define DL_I2C_CONTROLLER_ACK_ENABLE                   DL_I2CC_ACK_ENABLE
/*! Redirects to @ref DL_I2CC_ACK_DISABLE */
#define DL_I2C_CONTROLLER_ACK_DISABLE                  DL_I2CC_ACK_DISABLE
/*! Redirects to @ref DL_I2CC_IIDX_RX_DONE */
#define DL_I2C_IIDX_CONTROLLER_RX_DONE                 DL_I2CC_IIDX_RX_DONE
/*! Redirects to @ref DL_I2CC_IIDX_TX_DONE */
#define DL_I2C_IIDX_CONTROLLER_TX_DONE                 DL_I2CC_IIDX_TX_DONE
/*! Redirects to @ref DL_I2CC_IIDX_RXFIFO_TRIGGER */
#define DL_I2C_IIDX_CONTROLLER_RXFIFO_TRIGGER          DL_I2CC_IIDX_RXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_IIDX_TXFIFO_TRIGGER */
#define DL_I2C_IIDX_CONTROLLER_TXFIFO_TRIGGER          DL_I2CC_IIDX_TXFIFO_TRIGGER
/*! Redirects to @ref DL_I2CC_IIDX_RXFIFO_FULL */
#define DL_I2C_IIDX_CONTROLLER_RXFIFO_FULL             DL_I2CC_IIDX_RXFIFO_FULL
/*! Redirects to @ref DL_I2CC_IIDX_TXFIFO_EMPTY */
#define DL_I2C_IIDX_CONTROLLER_TXFIFO_EMPTY            DL_I2CC_IIDX_TXFIFO_EMPTY
/*! Redirects to @ref DL_I2CC_IIDX_NACK */
#define DL_I2C_IIDX_CONTROLLER_NACK                    DL_I2CC_IIDX_NACK
/*! Redirects to @ref DL_I2CC_IIDX_START */
#define DL_I2C_IIDX_CONTROLLER_START                   DL_I2CC_IIDX_START
/*! Redirects to @ref DL_I2CC_IIDX_STOP */
#define DL_I2C_IIDX_CONTROLLER_STOP                    DL_I2CC_IIDX_STOP
/*! Redirects to @ref DL_I2CC_IIDX_ARBITRATION_LOST */
#define DL_I2C_IIDX_CONTROLLER_ARBITRATION_LOST        DL_I2CC_IIDX_ARBITRATION_LOST
/*! Redirects to @ref DL_I2CC_IIDX_EVENT1_DMA_DONE */
#define DL_I2C_IIDX_CONTROLLER_EVENT1_DMA_DONE         DL_I2CC_IIDX_EVENT1_DMA_DONE
/*! Redirects to @ref DL_I2CC_IIDX_EVENT2_DMA_DONE */
#define DL_I2C_IIDX_CONTROLLER_EVENT2_DMA_DONE         DL_I2CC_IIDX_EVENT2_DMA_DONE
/*! Redirects to @ref DL_I2CC_IIDX_PEC_RX_ERROR */
#define DL_I2C_IIDX_CONTROLLER_PEC_RX_ERROR            DL_I2CC_IIDX_PEC_RX_ERROR

/*! Redirects to @ref DL_I2CC_fillTXFIFO */
#define DL_I2C_fillControllerTXFIFO               DL_I2CC_fillTXFIFO
/*! Redirects to @ref DL_I2CC_flushTXFIFO */
#define DL_I2C_flushControllerTXFIFO              DL_I2CC_flushTXFIFO
/*! Redirects to @ref DL_I2CC_flushRXFIFO */
#define DL_I2C_flushControllerRXFIFO              DL_I2CC_flushRXFIFO
/*! Redirects to @ref DL_I2CC_isTXFIFOFull */
#define DL_I2C_isControllerTXFIFOFull             DL_I2CC_isTXFIFOFull
/*! Redirects to @ref DL_I2CC_isTXFIFOEmpty */
#define DL_I2C_isControllerTXFIFOEmpty            DL_I2CC_isTXFIFOEmpty
/*! Redirects to @ref DL_I2CC_isRXFIFOEmpty */
#define DL_I2C_isControllerRXFIFOEmpty            DL_I2CC_isRXFIFOEmpty
/*! Redirects to @ref DL_I2CC_resetTransfer */
#define DL_I2C_resetControllerTransfer            DL_I2CC_resetTransfer
/*! Redirects to @ref DL_I2CC_startTransfer */
#define DL_I2C_startControllerTransfer            DL_I2CC_startTransfer
/*! Redirects to @ref DL_I2CC_startTransferAdvanced */
#define DL_I2C_startControllerTransferAdvanced    DL_I2CC_startTransferAdvanced
/*! Redirects to @ref DL_I2CC_getDirection */
#define DL_I2C_getControllerDirection             DL_I2CC_getDirection
/*! Redirects to @ref DL_I2CC_setDirection */
#define DL_I2C_setControllerDirection             DL_I2CC_setDirection
/*! Redirects to @ref DL_I2CC_getAddressingMode */
#define DL_I2C_getControllerAddressingMode        DL_I2CC_getAddressingMode
/*! Redirects to @ref DL_I2CC_setAddressingMode */
#define DL_I2C_setControllerAddressingMode        DL_I2CC_setAddressingMode
/*! Redirects to @ref DL_I2CC_disableACKOverride */
#define DL_I2C_disableControllerACKOverride       DL_I2CC_disableACKOverride
/*! Redirects to @ref DL_I2CC_isACKOverrideEnabled */
#define DL_I2C_isControllerACKOverrideEnabled     DL_I2CC_isACKOverrideEnabled
/*! Redirects to @ref DL_I2CC_enableACKOverride */
#define DL_I2C_enableControllerACKOverride        DL_I2CC_enableACKOverride
/*! Redirects to @ref DL_I2CC_disableReadOnTXEmpty */
#define DL_I2C_disableControllerReadOnTXEmpty     DL_I2CC_disableReadOnTXEmpty
/*! Redirects to @ref DL_I2CC_isReadOnTXEmptyEnabled */
#define DL_I2C_isControllerReadOnTXEmptyEnabled   DL_I2CC_isReadOnTXEmptyEnabled
/*! Redirects to @ref DL_I2CC_enableReadOnTXEmpty */
#define DL_I2C_enableControllerReadOnTXEmpty      DL_I2CC_enableReadOnTXEmpty
/*! Redirects to @ref DL_I2CC_getPECCountValue */
#define DL_I2C_getControllerPECCountValue         DL_I2CC_getPECCountValue
/*! Redirects to @ref DL_I2CC_setPECCountValue */
#define DL_I2C_setControllerPECCountValue         DL_I2CC_setPECCountValue
/*! Redirects to @ref DL_I2CC_disablePEC */
#define DL_I2C_disableControllerPEC               DL_I2CC_disablePEC
/*! Redirects to @ref DL_I2CC_isPECEnabled */
#define DL_I2C_isControllerPECEnabled             DL_I2CC_isPECEnabled
/*! Redirects to @ref DL_I2CC_enablePEC */
#define DL_I2C_enableControllerPEC                DL_I2CC_enablePEC
/*! Redirects to @ref DL_I2CC_getCurrentPECCount */
#define DL_I2C_getControllerCurrentPECCount       DL_I2CC_getCurrentPECCount
/*! Redirects to @ref DL_I2CC_getPECCheckedStatus */
#define DL_I2C_getControllerPECCheckedStatus      DL_I2CC_getPECCheckedStatus
/*! Redirects to @ref DL_I2CC_getPECCheckError */
#define DL_I2C_getControllerPECCheckError         DL_I2CC_getPECCheckError
/*! Redirects to @ref DL_I2CC_disableACK */
#define DL_I2C_disableControllerACK               DL_I2CC_disableACK
/*! Redirects to @ref DL_I2CC_isACKEnabled */
#define DL_I2C_isControllerACKEnabled             DL_I2CC_isACKEnabled
/*! Redirects to @ref DL_I2CC_enableACK */
#define DL_I2C_enableControllerACK                DL_I2CC_enableACK
/*! Redirects to @ref DL_I2CC_getStatus */
#define DL_I2C_getControllerStatus                DL_I2CC_getStatus
/*! Redirects to @ref DL_I2CC_receiveData */
#define DL_I2C_receiveControllerData              DL_I2CC_receiveData
/*! Redirects to @ref DL_I2CC_transmitData */
#define DL_I2C_transmitControllerData             DL_I2CC_transmitData
/*! Redirects to @ref DL_I2CC_disableMultiMode */
#define DL_I2C_disableMultiControllerMode         DL_I2CC_disableMultiMode
/*! Redirects to @ref DL_I2CC_isMultiModeEnabled */
#define DL_I2C_isMultiControllerModeEnabled       DL_I2CC_isMultiModeEnabled
/*! Redirects to @ref DL_I2CC_enableMultiMode */
#define DL_I2C_enableMultiControllerMode          DL_I2CC_enableMultiMode
/*! Redirects to @ref DL_I2CC_disable */
#define DL_I2C_disableController                  DL_I2CC_disable
/*! Redirects to @ref DL_I2CC_isEnabled */
#define DL_I2C_isControllerEnabled                DL_I2CC_isEnabled
/*! Redirects to @ref DL_I2CC_enable */
#define DL_I2C_enableController                   DL_I2CC_enable
/*! Redirects to @ref DL_I2CC_disableClockStretching */
#define DL_I2C_disableControllerClockStretching   DL_I2CC_disableClockStretching
/*! Redirects to @ref DL_I2CC_isClockStretchingEnabled */
#define DL_I2C_isControllerClockStretchingEnabled DL_I2CC_isClockStretchingEnabled
/*! Redirects to @ref DL_I2CC_enableClockStretching */
#define DL_I2C_enableControllerClockStretching    DL_I2CC_enableClockStretching
/*! Redirects to @ref DL_I2CC_getTXFIFOThreshold */
#define DL_I2C_getControllerTXFIFOThreshold       DL_I2CC_getTXFIFOThreshold
/*! Redirects to @ref DL_I2CC_setTXFIFOThreshold */
#define DL_I2C_setControllerTXFIFOThreshold       DL_I2CC_setTXFIFOThreshold
/*! Redirects to @ref DL_I2CC_stopFlushTXFIFO */
#define DL_I2C_stopFlushControllerTXFIFO          DL_I2CC_stopFlushTXFIFO
/*! Redirects to @ref DL_I2CC_startFlushTXFIFO */
#define DL_I2C_startFlushControllerTXFIFO         DL_I2CC_startFlushTXFIFO
/*! Redirects to @ref DL_I2CC_getRXFIFOThreshold */
#define DL_I2C_getControllerRXFIFOThreshold       DL_I2CC_getRXFIFOThreshold
/*! Redirects to @ref DL_I2CC_setRXFIFOThreshold */
#define DL_I2C_setControllerRXFIFOThreshold       DL_I2CC_setRXFIFOThreshold
/*! Redirects to @ref DL_I2CC_stopFlushRXFIFO */
#define DL_I2C_stopFlushControllerRXFIFO          DL_I2CC_stopFlushRXFIFO
/*! Redirects to @ref DL_I2CC_startFlushRXFIFO */
#define DL_I2C_startFlushControllerRXFIFO         DL_I2CC_startFlushRXFIFO
/*! Redirects to @ref DL_I2CC_getRXFIFOCounter */
#define DL_I2C_getControllerRXFIFOCounter         DL_I2CC_getRXFIFOCounter
/*! Redirects to @ref DL_I2CC_getTXFIFOCounter */
#define DL_I2C_getControllerTXFIFOCounter         DL_I2CC_getTXFIFOCounter
/*! Redirects to @ref DL_I2CC_isRXFIFOFlushActive */
#define DL_I2C_isControllerRXFIFOFlushActive      DL_I2CC_isRXFIFOFlushActive
/*! Redirects to @ref DL_I2CC_isTXFIFOFlushActive */
#define DL_I2C_isControllerTXFIFOFlushActive      DL_I2CC_isTXFIFOFlushActive

/** @}*/

/** @name DL_I2CC_STATUS
 *  @anchor DL_I2CC_STATUS
 *  @{
 */
/*!
 * @brief I2CC is busy
 *
 * The BUSY bit is set during an ongoing transaction, so is set during the
 * transmit/receive of the amount of data set in WBLEN including START, RESTART,
 * Address and STOP signal generation when required for the current transaction
 */
#define DL_I2CC_STATUS_BUSY (UNICOMMI2CC_SR_BUSY_MASK)

/*!
 * @brief I2CC error detected
 *
 * The error can be from the target address not being acknowledged or the
 * transmit data not being acknowledged
 */
#define DL_I2CC_STATUS_ERROR (UNICOMMI2CC_SR_ERR_MASK)

/*!
 * @brief I2CC address acknowledged
 */
#define DL_I2CC_STATUS_ADDR_ACK (UNICOMMI2CC_SR_ADRACK_MASK)

/*!
 * @brief I2CC data acknowledged
 */
#define DL_I2CC_STATUS_DATA_ACK (UNICOMMI2CC_SR_DATACK_MASK)

/*!
 * @brief I2CC arbitration lost
 */
#define DL_I2CC_STATUS_ARBITRATION_LOST (UNICOMMI2CC_SR_ARBLST_MASK)

/*!
 * @brief I2CC idle
 */
#define DL_I2CC_STATUS_IDLE (UNICOMMI2CC_SR_IDLE_MASK)

/*!
 * @brief I2CC bus busy
 *
 * The bit changes based on the START and STOP conditions
 */
#define DL_I2CC_STATUS_BUSY_BUS (UNICOMMI2CC_SR_BUSBSY_MASK)

/** @}*/

/** @name DL_I2CC_INTERRUPT
 *  @anchor DL_I2CC_INTERRUPT
 *  @{
 */
/*!
 * @brief Receive Transaction completed Interrupt
 */
#define DL_I2CC_INTERRUPT_RX_DONE (UNICOMMI2CC_CPU_INT_IMASK_RXDONE_SET)

/*!
 * @brief Transmit Transaction completed Interrupt
 */
#define DL_I2CC_INTERRUPT_TX_DONE (UNICOMMI2CC_CPU_INT_IMASK_TXDONE_SET)

/*!
 * @brief Receive FIFO Trigger when >= defined bytes
 */
#define DL_I2CC_INTERRUPT_RXFIFO_TRIGGER (UNICOMMI2CC_CPU_INT_IMASK_RXTRG_SET)

/*!
 * @brief Transmit FIFO Trigger when <= defined bytes
 */
#define DL_I2CC_INTERRUPT_TXFIFO_TRIGGER (UNICOMMI2CC_CPU_INT_IMASK_TXTRG_SET)

/*!
 * @brief Receive FIFO is full
 */
#define DL_I2CC_INTERRUPT_RXFIFO_FULL (UNICOMMI2CC_CPU_INT_IMASK_RXFIFOFULL_SET)

/*!
 * @brief Transmit FIFO is empty
 */
#define DL_I2CC_INTERRUPT_TXFIFO_EMPTY (UNICOMMI2CC_CPU_INT_IMASK_TXEMPTY_SET)

/*!
 * @brief Address/Data NACK Interrupt
 */
#define DL_I2CC_INTERRUPT_NACK (UNICOMMI2CC_CPU_INT_IMASK_NACK_SET)

/*!
 * @brief START Detection Interrupt
 */
#define DL_I2CC_INTERRUPT_START (UNICOMMI2CC_CPU_INT_IMASK_START_SET)

/*!
 * @brief STOP Detection Interrupt
 */
#define DL_I2CC_INTERRUPT_STOP (UNICOMMI2CC_CPU_INT_IMASK_STOP_SET)

/*!
 * @brief Arbitration Lost Interrupt
 */
#define DL_I2CC_INTERRUPT_ARBITRATION_LOST (UNICOMMI2CC_CPU_INT_IMASK_ARBLOST_SET)

/*!
 * @brief DMA Done on Event 1 publisher
 */
#define DL_I2CC_INTERRUPT_EVENT1_DMA_DONE (UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_TX_SET)

/*!
 * @brief DMA Done on Event 2 publisher
 */
#define DL_I2CC_INTERRUPT_EVENT2_DMA_DONE (UNICOMMI2CC_CPU_INT_IMASK_DMA_DONE_RX_SET)

/*!
 * @brief SMBus/PMBus PEC Receive Error Interrupt
 */
#define DL_I2CC_INTERRUPT_PEC_RX_ERROR (UNICOMMI2CC_CPU_INT_IMASK_PEC_RX_ERR_SET)

/*!
 * @brief Timeout A Interrupt
 */
#define DL_I2CC_INTERRUPT_TIMEOUT_A (UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTA_SET)

/*!
 * @brief Timeout B Interrupt
 */
#define DL_I2CC_INTERRUPT_TIMEOUT_B (UNICOMMI2CC_CPU_INT_IMASK_TIMEOUTB_SET)

/** @}*/

/** @name DL_I2CC_DMA_INTERRUPT
 *  @anchor DL_I2CC_DMA_INTERRUPT
 *  @{
 */

/*!
 * @brief Transmit FIFO Trigger when <= defined bytes for DMA trigger
 */
#define DL_I2CC_DMA_INTERRUPT_TXFIFO_TRIGGER (UNICOMMI2CC_DMA_TRIG1_IMASK_TXTRG_SET)

/*!
 * @brief Receive FIFO Trigger when >= defined bytes for DMA trigger
 */
#define DL_I2CC_DMA_INTERRUPT_RXFIFO_TRIGGER (UNICOMMI2CC_DMA_TRIG1_IMASK_RXTRG_SET)

/** @}*/

/** @brief DL_I2CC_EVENT_ROUTE */
typedef enum
{
    /*! I2CC event route 1 */
    DL_I2CC_EVENT_ROUTE_1 = 0,
    /*! I2CC event route 2 */
    DL_I2CC_EVENT_ROUTE_2 = 12
} DL_I2CC_EVENT_ROUTE;

/** @brief DL_I2CC_CLOCK */
typedef enum
{
    /*!  BUSCLK enabled as I2CC clock source */
    DL_I2CC_CLOCK_BUSCLK = UNICOMMI2CC_CLKSEL_BUSCLK_SEL_ENABLE,

} DL_I2CC_CLOCK;

/** @brief DL_I2CC_CLOCK_DIVIDE */
typedef enum
{
    /*!  I2CC Clock Divided by 1 */
    DL_I2CC_CLOCK_DIVIDE_1 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_1,
    /*!  I2CC Clock Divided by 2 */
    DL_I2CC_CLOCK_DIVIDE_2 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_2,
    /*!  I2CC Clock Divided by 3 */
    DL_I2CC_CLOCK_DIVIDE_3 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_3,
    /*!  I2CC Clock Divided by 4 */
    DL_I2CC_CLOCK_DIVIDE_4 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_4,
    /*!  I2CC Clock Divided by 5 */
    DL_I2CC_CLOCK_DIVIDE_5 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_5,
    /*!  I2CC Clock Divided by 6 */
    DL_I2CC_CLOCK_DIVIDE_6 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_6,
    /*!  I2CC Clock Divided by 7 */
    DL_I2CC_CLOCK_DIVIDE_7 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_7,
    /*!  I2CC Clock Divided by 8 */
    DL_I2CC_CLOCK_DIVIDE_8 = UNICOMMI2CC_CLKDIV_RATIO_DIV_BY_8,
} DL_I2CC_CLOCK_DIVIDE;

/** @brief DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH */
typedef enum
{
    /*!  Pulses filtering disabled.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_DISABLED  = UNICOMMI2CC_GFCTL_DGFSEL_DISABLED,
    /*!  Pulses shorter than 1 functional clock tick in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_1  = UNICOMMI2CC_GFCTL_DGFSEL_CLK_1,
    /*!  Pulses shorter than 2 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_2  = UNICOMMI2CC_GFCTL_DGFSEL_CLK_2,
    /*!  Pulses shorter than 3 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_3  = UNICOMMI2CC_GFCTL_DGFSEL_CLK_3,
    /*!  Pulses shorter than 4 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_4  = UNICOMMI2CC_GFCTL_DGFSEL_CLK_4,
    /*!  Pulses shorter than 8 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_8  = UNICOMMI2CC_GFCTL_DGFSEL_CLK_8,
    /*!  Pulses shorter than 16 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_16 = UNICOMMI2CC_GFCTL_DGFSEL_CLK_16,
    /*!  Pulses shorter than 31 functional clock ticks in length are filtered.  */
    DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH_CLOCKS_31 = UNICOMMI2CC_GFCTL_DGFSEL_CLK_31,
} DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH;

/** @brief DL_I2CC_DIRECTION */
typedef enum
{
    /*! Set direction to transmitting to target */
    DL_I2CC_DIRECTION_TX = UNICOMMI2CC_TA_DIR_TRANSMIT,
    /*! Set direction to receiving from target */
    DL_I2CC_DIRECTION_RX = UNICOMMI2CC_TA_DIR_RECEIVE,
} DL_I2CC_DIRECTION;

/** @brief DL_I2CC_ADDRESSING_MODE */
typedef enum
{
    /*! Enable in 7-bit addressing mode */
    DL_I2CC_ADDRESSING_MODE_7_BIT  = UNICOMMI2CC_TA_MODE_MODE7,
    /*! Enable in 10-bit addressing mode */
    DL_I2CC_ADDRESSING_MODE_10_BIT = UNICOMMI2CC_TA_MODE_MODE10,
} DL_I2CC_ADDRESSING_MODE;

/** @brief DL_I2CC_PEC_STATUS */
typedef enum
{
    /*!  I2CC SMBus/PMBus PEC was checked in the transaction that
     *   occurred before the last Stop */
    DL_I2CC_PEC_STATUS_CHECKED     = UNICOMMI2CC_PECSR_PECSTS_CHECK_SET,
    /*!  I2CC SMBus/PMBus PEC was not checked in the transaction that
     *   occurred the last Stop */
    DL_I2CC_PEC_STATUS_NOT_CHECKED = UNICOMMI2CC_PECSR_PECSTS_CHECK_CLEARED,
} DL_I2CC_PEC_STATUS;

/** @brief DL_I2CC_PEC_CHECK_ERROR */
typedef enum
{
    /*! I2CC SMBus/PMBus PEC check error occurred in the transaction
     *  before the last stop */
    DL_I2CC_PEC_CHECK_ERROR_SET     = UNICOMMI2CC_PECSR_PECSTS_ERROR_SET,
    /*! I2CC SMBus/PMBus PEC check error did not occur in the
     *  transaction before the last stop */
    DL_I2CC_PEC_CHECK_ERROR_CLEARED = UNICOMMI2CC_PECSR_PECSTS_ERROR_CLEARED,
} DL_I2CC_PEC_CHECK_ERROR;

/** @brief DL_I2CC_SCL */
typedef enum
{
    /*!  I2CC SCL signal high */
    DL_I2CC_SCL_HIGH = UNICOMMI2CC_BMON_SCL_SET,
    /*!  I2CC SCL signal low */
    DL_I2CC_SCL_LOW  = UNICOMMI2CC_BMON_SCL_CLEARED,
} DL_I2CC_SCL;

/** @brief DL_I2CC_SDA */
typedef enum
{
    /*!  I2CC SDA signal high */
    DL_I2CC_SDA_HIGH = UNICOMMI2CC_BMON_SDA_SET,
    /*!  I2CC SDA signal low */
    DL_I2CC_SDA_LOW  = UNICOMMI2CC_BMON_SDA_CLEARED,
} DL_I2CC_SDA;

/** @brief DL_I2CC_START */
typedef enum
{
    /*!  generates START condition */
    DL_I2CC_START_ENABLE  = UNICOMMI2CC_CTR_START_ENABLE,
    /*!  doesn't generate START condition */
    DL_I2CC_START_DISABLE = UNICOMMI2CC_CTR_START_DISABLE,
} DL_I2CC_START;

/** @brief DL_I2CC_STOP */
typedef enum
{
    /*!  generates STOP condition */
    DL_I2CC_STOP_ENABLE  = UNICOMMI2CC_CTR_STOP_ENABLE,
    /*!  doesn't generate STOP condition */
    DL_I2CC_STOP_DISABLE = UNICOMMI2CC_CTR_STOP_DISABLE,
} DL_I2CC_STOP;

/** @brief DL_I2CC_ACK */
typedef enum
{
    /*!  Last received data byte of a transaction is not ACKed automatically */
    DL_I2CC_ACK_ENABLE  = UNICOMMI2CC_CTR_ACK_ENABLE,
    /*!  Last received data byte of a transaction is ACKed automatically */
    DL_I2CC_ACK_DISABLE = UNICOMMI2CC_CTR_ACK_DISABLE,
} DL_I2CC_ACK;

/** @brief DL_I2CC_TX_FIFO_LEVEL */
typedef enum
{
    /*! Interrupt triggers when FIFO <= 3/4 empty */
    DL_I2CC_TX_FIFO_LEVEL_3_4_EMPTY    = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_3_4,
    /*! Interrupt triggers when FIFO <= 1/2 empty */
    DL_I2CC_TX_FIFO_LEVEL_1_2_EMPTY    = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_1_2,
    /*! Interrupt triggers when FIFO <= 1/4 empty */
    DL_I2CC_TX_FIFO_LEVEL_1_4_EMPTY    = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_1_4,
    /*! Interrupt triggers when FIFO is not full */
    DL_I2CC_TX_FIFO_LEVEL_NOT_FULL     = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_NOT_FULL,
    /*! Interrupt triggers when FIFO is empty */
    DL_I2CC_TX_FIFO_LEVEL_EMPTY        = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_EMPTY,
    /*! Interrupt triggers when FIFO is almost empty (FIFO <= 1) */
    DL_I2CC_TX_FIFO_LEVEL_ALMOST_EMPTY = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_ALMOST_EMPTY,
    /*! Interrupt triggers when FIFO is almost full (FIFO >= (MAX_FIFO_LEN - 1)) */
    DL_I2CC_TX_FIFO_LEVEL_ALMOST_FULL  = UNICOMMI2CC_IFLS_TXIFLSEL_LVL_ALMOST_FULL
} DL_I2CC_TX_FIFO_LEVEL;

/** @brief DL_I2CC_RX_FIFO_LEVEL */
typedef enum
{
    /*! Interrupt triggers when FIFO >= 3/4 Full */
    DL_I2CC_RX_FIFO_LEVEL_3_4_FULL     = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_3_4,
    /*! Interrupt triggers when FIFO >= 1/2 Full */
    DL_I2CC_RX_FIFO_LEVEL_1_2_FULL     = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_1_2,
    /*! Interrupt triggers when FIFO >= 1/4 Full */
    DL_I2CC_RX_FIFO_LEVEL_1_4_FULL     = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_1_4,
    /*! Interrupt triggers when FIFO is not empty */
    DL_I2CC_RX_FIFO_LEVEL_NOT_EMPTY    = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_NOT_EMPTY,
    /*! Interrupt triggers when FIFO is full */
    DL_I2CC_RX_FIFO_LEVEL_FULL         = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_FULL,
    /*! Interrupt triggers when FIFO is almost empty (FIFO <= 1) */
    DL_I2CC_RX_FIFO_LEVEL_ALMOST_EMPTY = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_ALMOST_EMPTY,
    /*! Interrupt triggers when FIFO is almost full (FIFO >= (MAX_FIFO_LEN - 1)) */
    DL_I2CC_RX_FIFO_LEVEL_ALMOST_FULL  = UNICOMMI2CC_IFLS_RXIFLSEL_LVL_ALMOST_FULL
} DL_I2CC_RX_FIFO_LEVEL;

/*! @brief DL_I2CC_IIDX */
typedef enum
{
    /*! Interrupt index for I2CC if no interrupt is pending */
    DL_I2CC_IIDX_NO_INT           = UNICOMMI2CC_IIDX_STAT_NO_INTR,
    /*! Interrupt index for I2CC Receive Transaction completed */
    DL_I2CC_IIDX_RX_DONE          = UNICOMMI2CC_IIDX_STAT_RXDONEFG,
    /*! Interrupt index for Transmit Transaction completed */
    DL_I2CC_IIDX_TX_DONE          = UNICOMMI2CC_IIDX_STAT_TXDONEFG,
    /*! Interrupt index for I2CC Receive FIFO Trigger */
    DL_I2CC_IIDX_RXFIFO_TRIGGER   = UNICOMMI2CC_IIDX_STAT_RXTRG,
    /*! Interrupt index for I2CC Transmit FIFO Trigger */
    DL_I2CC_IIDX_TXFIFO_TRIGGER   = UNICOMMI2CC_IIDX_STAT_TXTRG,
    /*! Interrupt index for I2CC Receive when FIFO is full */
    DL_I2CC_IIDX_RXFIFO_FULL      = UNICOMMI2CC_IIDX_STAT_RXFULL,
    /*! Interrupt index for I2CC when Transmit FIFO is empty */
    DL_I2CC_IIDX_TXFIFO_EMPTY     = UNICOMMI2CC_IIDX_STAT_TXEMPTY,
    /*! Interrupt index for Address/Data NACK */
    DL_I2CC_IIDX_NACK             = UNICOMMI2CC_IIDX_STAT_NACKFG,
    /*! Interrupt index for I2CC START Detection */
    DL_I2CC_IIDX_START            = UNICOMMI2CC_IIDX_STAT_STARTFG,
    /*! Interrupt index for I2CC STOP Detection */
    DL_I2CC_IIDX_STOP             = UNICOMMI2CC_IIDX_STAT_STOPFG,
    /*! Interrupt index for I2CC Arbitration Lost */
    DL_I2CC_IIDX_ARBITRATION_LOST = UNICOMMI2CC_IIDX_STAT_ARBLOSTFG,
    /*! Interrupt index for I2CC Event 1 DMA Done */
    DL_I2CC_IIDX_EVENT1_DMA_DONE  = UNICOMMI2CC_IIDX_STAT_DMA_DONE_TX,
    /*! Interrupt index for I2CC Event 2 DMA Done */
    DL_I2CC_IIDX_EVENT2_DMA_DONE  = UNICOMMI2CC_IIDX_STAT_DMA_DONE_RX,
    /*! Interrupt index for I2CC receive pre-emptive interrupt */
    DL_I2CC_IIDX_PREEMPT_INT_TX   = UNICOMMI2CC_IIDX_STAT_DMA_PREIRQ_TX,
    /*! Interrupt index for I2CC receive pre-emptive interrupt */
    DL_I2CC_IIDX_PREEMPT_INT_RX   = UNICOMMI2CC_IIDX_STAT_DMA_PREIRQ_RX,
    /*! Interrupt index for I2CC SMBus/PMBus PEC Receive Error Event */
    DL_I2CC_IIDX_PEC_RX_ERROR     = UNICOMMI2CC_IIDX_STAT_PEC_RX_ERR,
    /*! Interrupt index for I2CC Timeout A Event */
    DL_I2CC_IIDX_TIMEOUT_A        = UNICOMMI2CC_IIDX_STAT_TIMEOUTA,
    /*! Interrupt index for I2CC Timeout B Event */
    DL_I2CC_IIDX_TIMEOUT_B        = UNICOMMI2CC_IIDX_STAT_TIMEOUTB,
} DL_I2CC_IIDX;

/**
 * @brief  Configuration struct for @ref DL_I2CC_setClockConfig.
 */
typedef struct
{
    /*! I2CC module clock source. One of @ref DL_I2CC_CLOCK */
    DL_I2CC_CLOCK        clockSel;
    /*! I2CC clock divider selection. One of @ref DL_I2CC_CLOCK_DIVIDE */
    DL_I2CC_CLOCK_DIVIDE divideRatio;
} DL_I2CC_ClockConfig;

/**
 *  @brief      Configure I2CC source clock
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  config  Pointer to the clock configuration struct
 *                       @ref DL_I2CC_ClockConfig.
 */
void DL_I2CC_setClockConfig(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_ClockConfig *config);

/**
 *  @brief      Get I2CC source clock configuration
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  config  Pointer to the clock configuration struct
 *                      @ref DL_I2CC_ClockConfig.
 */
void DL_I2CC_getClockConfig(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_ClockConfig *config);

/**
 *  @brief      Fills the TX FIFO with data
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  buffer  Pointer to buffer of bytes
 *  @param[in]  count   Number of bytes to fill TX FIFO from buffer
 *
 *  @return     Number of bytes that were successfully written
 */
uint16_t DL_I2CC_fillTXFIFO(DL_UNICOMM_Inst_Regs *unicomm, uint8_t *buffer, uint16_t count);

/**
 *  @brief      Flushes/removes all elements in the controller TX FIFO
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
void DL_I2CC_flushTXFIFO(DL_UNICOMM_Inst_Regs *unicomm);

/**
 *  @brief      Flushes/removes all elements in the controller RX FIFO
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
void DL_I2CC_flushRXFIFO(DL_UNICOMM_Inst_Regs *unicomm);

/**
 *  @brief      Checks if TX FIFO is full
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If TX FIFO is full
 *
 *  @retval     true if TX FIFO is full
 *  @retval     false if TX FIFO is not full
 */
__STATIC_INLINE bool DL_I2CC_isTXFIFOFull(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->SR & UNICOMMI2CC_SR_TXFF_MASK) == UNICOMMI2CC_SR_TXFF_SET);
}

/**
 *  @brief      Checks if TX FIFO is empty
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If TX FIFO is empty
 *
 *  @retval     true if TX FIFO is empty
 *  @retval     false if TX FIFO is not empty
 */
__STATIC_INLINE bool DL_I2CC_isTXFIFOEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->SR & UNICOMMI2CC_SR_TXFE_MASK) == UNICOMMI2CC_SR_TXFE_SET);
}

/**
 *  @brief      Checks if RX FIFO is empty
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If RX FIFO is empty
 *
 *  @retval     true if RX FIFO is empty
 *  @retval     false if RX FIFO is not empty
 */
__STATIC_INLINE bool DL_I2CC_isRXFIFOEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->SR & UNICOMMI2CC_SR_RXFE_MASK) == UNICOMMI2CC_SR_RXFE_SET);
}

/**
 *  @brief      Reset transfers from from UNICOMMI2CC
 *
 *  Resets transfer register to initialize UNICOMMI2CC
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_resetTransfer(DL_UNICOMM_Inst_Regs *unicomm)
{
    // Resets all functionality
    unicomm->i2cc->CTR = 0x00;
}

/**
 *  @brief      Sets up a transfer from UNICOMMI2CC
 *
 *  Set target address, transfer direction, burst length, START+STOP generation.
 *  @note   Reading/writing data must be done separately.
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *  @param[in]  targetAddr  Target address [0x00, 0x3FF]
 *  @param[in]  direction   One of @ref DL_I2CC_DIRECTION
 *  @param[in]  length      Intended burst length in number of bytes
 */
__STATIC_INLINE void DL_I2CC_startTransfer(DL_UNICOMM_Inst_Regs *unicomm, uint32_t targetAddr,
                                           DL_I2CC_DIRECTION direction, uint16_t length)
{
    bool isUnicommAdvance = DL_UNICOMM_isAdvanceFeaturesEnabled(unicomm);
    if (length > 1)
    {
        ASSERT(isUnicommAdvance);
    }
    // Specify target address and read/write mode
    DL_Common_updateReg(&unicomm->i2cc->TA, ((targetAddr << UNICOMMI2CC_TA_ADDR_OFS) | (uint32_t)direction),
                        (UNICOMMI2CC_TA_ADDR_MASK | UNICOMMI2CC_TA_DIR_MASK));

    uint32_t controlValue = UNICOMMI2CC_CTR_START_ENABLE | UNICOMMI2CC_CTR_STOP_ENABLE;
    // Only include BLEN in the update if unicomm is advanced
    if (isUnicommAdvance)
    {
        controlValue |= ((uint32_t)length << UNICOMMI2CC_CTR_BLEN_OFS);
        DL_Common_updateReg(&unicomm->i2cc->CTR, controlValue,
                            (UNICOMMI2CC_CTR_BLEN_MASK | UNICOMMI2CC_CTR_START_MASK | UNICOMMI2CC_CTR_STOP_MASK));
    }
    else
    {
        // For non-advanced unicomm, don't include BLEN in the update
        DL_Common_updateReg(&unicomm->i2cc->CTR, controlValue,
                            (UNICOMMI2CC_CTR_START_MASK | UNICOMMI2CC_CTR_STOP_MASK));
    }
    // Start the frame
    DL_Common_updateReg(&unicomm->i2cc->CTR, UNICOMMI2CC_CTR_FRM_START_ENABLE, UNICOMMI2CC_CTR_FRM_START_MASK);
}

/**
 *  @brief      Sets up a transfer from I2CC with control of START,
 *  STOP and ACK
 *
 *  @note   Reading/writing data must be done separately.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  targetAddr  7-bit target address [0x00, 0x7f]
 *  @param[in]  direction   One of @ref DL_I2CC_DIRECTION
 *  @param[in]  length      Intended burst length in number of bytes
 *  @param[in]  start       One of @ref DL_I2CC_START
 *  @param[in]  stop        One of @ref DL_I2CC_STOP
 *  @param[in]  ack         One of @ref DL_I2CC_ACK
 */
__STATIC_INLINE void DL_I2CC_startTransferAdvanced(DL_UNICOMM_Inst_Regs *unicomm, uint32_t targetAddr,
                                                   DL_I2CC_DIRECTION direction, uint16_t length, DL_I2CC_START start,
                                                   DL_I2CC_STOP stop, DL_I2CC_ACK ack)
{
    bool isUnicommAdvance = DL_UNICOMM_isAdvanceFeaturesEnabled(unicomm);
    if (length > 1)
    {
        ASSERT(isUnicommAdvance);
    }

    // Specify target address and read/write mode
    DL_Common_updateReg(&unicomm->i2cc->TA, ((targetAddr << UNICOMMI2CC_TA_ADDR_OFS) | (uint32_t)direction),
                        (UNICOMMI2CC_TA_ADDR_MASK | UNICOMMI2CC_TA_DIR_MASK));

    uint32_t controlValue = (uint32_t)start | (uint32_t)stop | (uint32_t)ack;
    // Only include BLEN in the update if unicomm is advanced
    if (isUnicommAdvance)
    {
        controlValue |= ((uint32_t)length << UNICOMMI2CC_CTR_BLEN_OFS);
        DL_Common_updateReg(&unicomm->i2cc->CTR, controlValue,
                            (UNICOMMI2CC_CTR_BLEN_MASK | UNICOMMI2CC_CTR_START_MASK | UNICOMMI2CC_CTR_STOP_MASK |
                             UNICOMMI2CC_CTR_ACK_MASK));
    }
    else
    {
        // For non-advanced unicomm, don't include BLEN in the update
        DL_Common_updateReg(&unicomm->i2cc->CTR, controlValue,
                            (UNICOMMI2CC_CTR_START_MASK | UNICOMMI2CC_CTR_STOP_MASK | UNICOMMI2CC_CTR_ACK_MASK));
    }

    // Start the frame
    DL_Common_updateReg(&unicomm->i2cc->CTR, UNICOMMI2CC_CTR_FRM_START_ENABLE, UNICOMMI2CC_CTR_FRM_START_MASK);
}

/**
 * @brief Enables power on UNICOMM I2C module
 *
 * @param[in] unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_enablePower(unicomm);

    if (unicomm->fixedMode == false)
    {
        DL_UNICOMM_setIPMode(unicomm, DL_UNICOMM_I2C_CONTROLLER);
    }
}

/**
 * @brief Disables power on UNICOMM I2C module
 *
 * @param[in] unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_disablePower(unicomm);
}

/**
 * @brief Returns if  power on UNICOMM I2C module
 *
 * @param[in] unicomm        Pointer to the register overlay for the peripheral
 *
 * @return true if power is enabled
 * @return false if power is disabled
 */
__STATIC_INLINE bool DL_I2CC_isPowerEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return DL_UNICOMM_isPowerEnabled(unicomm);
}

/**
 * @brief Resets UNICOMM I2C peripheral
 *
 * @param[in] unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_reset(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_reset(unicomm);
}

/**
 * @brief Returns if UNICOMM I2C peripheral was reset
 *
 * @param[in] unicomm        Pointer to the register overlay for the peripheral
 *
 * @return true if peripheral was reset
 * @return false if peripheral wasn't reset
 *
 */
__STATIC_INLINE bool DL_I2CC_isReset(DL_UNICOMM_Inst_Regs *unicomm)
{
    return DL_UNICOMM_isReset(unicomm);
}

/**
 * @brief Set Clock Source
 *
 *  Clock sources depend on device and clock should be enabled
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  clockSource    One of @ref DL_I2CC_CLOCK.
 *
 */
__STATIC_INLINE void DL_I2CC_selectClockSource(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_CLOCK clockSource)
{
    DL_Common_updateReg(&unicomm->i2cc->CLKSEL, (uint32_t)clockSource, UNICOMMI2CC_CLKSEL_BUSCLK_SEL_MASK);
}

/**
 * @brief Set Clock Divider
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  clockDivider   One of @ref DL_I2CC_CLOCK_DIVIDE.
 *
 */
__STATIC_INLINE void DL_I2CC_selectClockDivider(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_CLOCK_DIVIDE clockDivider)
{
    DL_Common_updateReg(&unicomm->i2cc->CLKDIV, (uint32_t)clockDivider, UNICOMMI2CC_CLKDIV_RATIO_MASK);
}

/**
 *  @brief      Get Digital Glitch Suppression Pulse Width
 *
 *  Pulse width for the digital glitch suppression on SCL/SDA lines.
 *  Values are in terms of functional clock ticks.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Digital glitch suppression pulse width
 *
 *  @retval     One of @ref DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH.
 */
__STATIC_INLINE DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH
DL_I2CC_getDigitalGlitchFilterPulseWidth(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t filterWidth = unicomm->i2cc->GFCTL & UNICOMMI2CC_GFCTL_DGFSEL_MASK;

    return (DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH)(filterWidth);
}

/**
 *  @brief      Set Digital Glitch Suppression Pulse Width
 *
 *  Pulse width for the digital glitch suppression on SCL/SDA lines.
 *  Values are in terms of functional clock ticks.
 *
 *  @param[in]  unicomm             Pointer to the register overlay for the
 *                              peripheral
 *  @param[in]  filterWidth     One of @ref DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH.
 */
__STATIC_INLINE void DL_I2CC_setDigitalGlitchFilterPulseWidth(DL_UNICOMM_Inst_Regs               *unicomm,
                                                              DL_I2CC_DIGITAL_GLITCH_FILTER_WIDTH filterWidth)
{
    DL_Common_updateReg(&unicomm->i2cc->GFCTL, (uint32_t)filterWidth, UNICOMMI2CC_GFCTL_DGFSEL_MASK);
}

/**
 *  @brief      Disable Analog Glitch Suppression
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableAnalogGlitchFilter(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->GFCTL &= ~(UNICOMMI2CC_GFCTL_AGFEN_MASK);
}

/**
 *  @brief      Checks if analog glitch suppression is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If analog glitch suppression is enabled
 *
 *  @retval     true if analog glitch suppression is enabled
 *  @retval     false if analog glitch suppression is disabled
 */
__STATIC_INLINE bool DL_I2CC_isAnalogGlitchFilterEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->GFCTL & UNICOMMI2CC_GFCTL_AGFEN_MASK) == UNICOMMI2CC_GFCTL_AGFEN_ENABLE);
}

/**
 *  @brief      Enable Analog Glitch Suppression
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableAnalogGlitchFilter(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->GFCTL |= UNICOMMI2CC_GFCTL_AGFEN_ENABLE;
}

/**
 *  @brief      Get direction of next operation
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Direction of next operation
 *
 *  @retval     One of @ref DL_I2CC_DIRECTION
 */
__STATIC_INLINE DL_I2CC_DIRECTION DL_I2CC_getDirection(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t direction = unicomm->i2cc->TA & UNICOMMI2CC_TA_DIR_MASK;

    return (DL_I2CC_DIRECTION)(direction);
}

/**
 *  @brief      Set direction of next operation
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @param[in]  direction   Direction of next operation.
 *                          One of @ref DL_I2CC_DIRECTION.
 */
__STATIC_INLINE void DL_I2CC_setDirection(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_DIRECTION direction)
{
    DL_Common_updateReg(&unicomm->i2cc->TA, (uint32_t)direction, UNICOMMI2CC_TA_DIR_MASK);
}

/**
 *  @brief      Get the address of the target being addressed when configured
 *              as an UNICOMMI2CC
 *
 *  Specifies bits A9 through A0 of the target address.
 *  In 7-bit addressing mode as selected by @ref DL_I2CC_setAddressingMode,
 *  the top 3 bits are don't care.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The target address
 *
 *  @retval     [0x00, 0x07FE]
 *
 *  @sa         DL_I2CC_setAddressingMode
 */
__STATIC_INLINE uint32_t DL_I2CC_getTargetAddress(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->TA & UNICOMMI2CC_TA_ADDR_MASK) >> UNICOMMI2CC_TA_ADDR_OFS);
}

/**
 *  @brief      Set the address of the target being addressed when configured
 *              as an UNICOMMI2CC
 *
 *  Specifies bits A9 through A0 of the target address.
 *  In 7-bit addressing mode as selected by @ref DL_I2CC_setAddressingMode,
 *  the top 3 bits are don't care.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  targetAddress    Target address to set [0x00, 0x07FE]
 *
 *  @sa         DL_I2CC_setAddressingMode
 */
__STATIC_INLINE void DL_I2CC_setTargetAddress(DL_UNICOMM_Inst_Regs *unicomm, uint32_t targetAddress)
{
    DL_Common_updateReg(&unicomm->i2cc->TA, (targetAddress << UNICOMMI2CC_TA_ADDR_OFS), UNICOMMI2CC_TA_ADDR_MASK);
}

/**
 *  @brief      Get addressing mode
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Addressing mode the is set to
 *
 *  @retval     One of @ref DL_I2CC_ADDRESSING_MODE
 *
 */
__STATIC_INLINE DL_I2CC_ADDRESSING_MODE DL_I2CC_getAddressingMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t mode = unicomm->i2cc->TA & UNICOMMI2CC_TA_MODE_MASK;

    return (DL_I2CC_ADDRESSING_MODE)(mode);
}

/**
 *  @brief      Set addressing mode between 7-bit and 10-bit mode
 *
 *  Selects the addressing mode between 7-bit and 10-bit mode to be used when
 *  device is configured as a
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  mode    Addressing mode to set the target to.
 *                      One of @ref DL_I2CC_ADDRESSING_MODE.
 */
__STATIC_INLINE void DL_I2CC_setAddressingMode(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_ADDRESSING_MODE mode)
{
    DL_Common_updateReg(&unicomm->i2cc->TA, (uint32_t)mode, UNICOMMI2CC_TA_MODE_MASK);
}

/**
 *  @brief      Disable ACK override
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableACKOverride(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR &= ~(UNICOMMI2CC_CTR_ACKOEN_MASK);
}

/**
 *  @brief      Checks if ACK override is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If ACK override is enabled
 *
 *  @retval     true if ACK override is enabled
 *  @retval     false if ACK override is disabled
 */
__STATIC_INLINE bool DL_I2CC_isACKOverrideEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_ACKOEN_MASK) == UNICOMMI2CC_CTR_ACKOEN_ENABLE);
}

/**
 *  @brief      Enable ACK override
 *
 *  When enabled and the is receiving data and the number of bytes
 *  indicated in CTR.MBLEN have been received, the state machine will generate
 *  an RXDONE interrupt and wait at the start of the ACK for FW to indicate if
 *  an ACK or NACK should be sent. The ACK or NACK is selected by writing the
 *  CTR register and setting ACK accordingly. The other fields in this register
 *  can also be written at this time to continue on with the transaction. If a
 *  NACK is sent the state machine will automatically send a Stop.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 * @sa          DL_I2CC_setTransactionLength
 */
__STATIC_INLINE void DL_I2CC_enableACKOverride(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR |= UNICOMMI2CC_CTR_ACKOEN_ENABLE;
}

/**
 *  @brief      Disable read on TX empty
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableReadOnTXEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR &= ~(UNICOMMI2CC_CTR_RD_ON_TXEMPTY_MASK);
}

/**
 *  @brief      Checks if read on TX empty is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If read on TX empty is enabled
 *
 *  @retval     true if read on TX empty is enabled
 *  @retval     false if read on TX empty is disabled
 */
__STATIC_INLINE bool DL_I2CC_isReadOnTXEmptyEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_RD_ON_TXEMPTY_MASK) == UNICOMMI2CC_CTR_RD_ON_TXEMPTY_ENABLE);
}

/**
 *  @brief      Enable read on TX empty
 *
 *  When enabled, the will transmit all bytes from the TX FIFO
 *  before continuing with the programmed Burst Run Read. If the DIR is not
 *  set to Read in the MSA then this bit is ignored. The Start must be set in
 *  the CTR for proper I2CC protocol. The will first send the Start
 *  Condition, I2CC Address with R/W bit set to write, before sending the bytes
 *  in the TX FIFO. When the TX FIFO is empty, the I2CC transaction will
 *  continue as programmed in MTCR and MSA without sending a Stop Condition.
 *  This is intended to be used to perform simple I2CC command based reads
 *  transition that will complete after initiating them without having to get
 *  an interrupt to turn the bus around.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 */
__STATIC_INLINE void DL_I2CC_enableReadOnTXEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR |= UNICOMMI2CC_CTR_RD_ON_TXEMPTY_ENABLE;
}

/**
 *  @brief      Get the SMBus/PMBus Packet Error Checking (PEC) count value
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The value the PEC count is set to
 *
 *  @retval     Value between [0x0, 0x01FF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getPECCountValue(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->PECCTL & UNICOMMI2CC_PECCTL_PECCNT_MASK);
}

/**
 *  @brief      Set the SMBus/PMBus Packet Error Checking (PEC) count value
 *
 *  When this field is non zero, the number of I2CC data bytes are counted.
 *  Refer to the device TRM for more details.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  count   The value to set the PEC count to.
 *                      Value between [0x0, 0x01FF]
 */
__STATIC_INLINE void DL_I2CC_setPECCountValue(DL_UNICOMM_Inst_Regs *unicomm, uint32_t count)
{
    DL_Common_updateReg(&unicomm->i2cc->PECCTL, count, UNICOMMI2CC_PECCTL_PECCNT_MASK);
}

/**
 *  @brief      Disable SMBus/PMBus Packet Error Checking (PEC)
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disablePEC(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->PECCTL &= ~(UNICOMMI2CC_PECCTL_PECEN_MASK);
}

/**
 *  @brief      Checks if SMBus/PMBus Packet Error Checking (PEC)
 *              is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If PEC is enabled
 *
 *  @retval     true if PEC is enabled
 *  @retval     false if PEC is disabled
 */
__STATIC_INLINE bool DL_I2CC_isPECEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->PECCTL & UNICOMMI2CC_PECCTL_PECEN_MASK) == UNICOMMI2CC_PECCTL_PECEN_ENABLE);
}

/**
 *  @brief      Enable SMBus/PMBus Packet Error Checking (PEC)
 *
 *  When enabled, the PEC is calculated on all bits accept the Start, Stop, ACK
 *  and NACK. The PEC LSFR and the Byte Counter is set to 0 when the State
 *  Machine is in the IDLE state, which occurs following a Stop or when a
 *  timeout occurs. The Counter is also set to 0 after the PEC byte is sent or
 *  received. Note that the NACK is automatically sent following a PEC byte
 *  that results in a PEC error.
 *  The PEC Polynomial is x^8 + x^2 + x^1 + 1.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 */
__STATIC_INLINE void DL_I2CC_enablePEC(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->PECCTL |= UNICOMMI2CC_PECCTL_PECEN_ENABLE;
}

/**
 *  @brief      Get the current SMBus/PMBus PEC byte count of the
 *              state machine
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The current PEC byte count of the state machine
 *
 *  @retval     Value between [0x0, 0x01FF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getCurrentPECCount(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->PECSR & UNICOMMI2CC_PECSR_PECSTS_CHECK_MASK);
}

/**
 *  @brief      If SMBus/PMBus PEC was checked in last transaction
 *
 *  The status of if the PEC was checked in the transaction that
 *  occurred before the last Stop. Latched on Stop.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Status of PEC checked in last transaction
 *
 *  @retval     One of @ref DL_I2CC_PEC_STATUS
 */
__STATIC_INLINE DL_I2CC_PEC_STATUS DL_I2CC_getPECCheckedStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t status = unicomm->i2cc->PECSR & UNICOMMI2CC_PECSR_PECSTS_CHECK_MASK;

    return (DL_I2CC_PEC_STATUS)(status);
}

/**
 *  @brief      Get the status of the SMBus/PMBus PEC Check error
 *
 *  The status of if a PEC check error occurred in the transaction that
 *  occurred before the last Stop. Latched on Stop.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Status of PEC check error
 *
 *  @retval     One of @ref DL_I2CC_PEC_CHECK_ERROR
 */
__STATIC_INLINE DL_I2CC_PEC_CHECK_ERROR DL_I2CC_getPECCheckError(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t error = unicomm->i2cc->PECSR & UNICOMMI2CC_PECSR_PECSTS_ERROR_MASK;

    return (DL_I2CC_PEC_CHECK_ERROR)(error);
}

/**
 *  @brief      Disable I2CC START generation
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableStartCondition(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR &= ~(UNICOMMI2CC_CTR_START_MASK);
}

/**
 *  @brief      Checks if I2CC START generation is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If I2CC START generation is enabled
 *
 *  @retval     true if I2CC START generation is enabled
 *  @retval     false if I2CC START generation is disabled
 */
__STATIC_INLINE bool DL_I2CC_isStartConditionEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_START_MASK) == UNICOMMI2CC_CTR_START_ENABLE);
}

/**
 *  @brief      Enable I2CC START generation
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableStartCondition(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR |= UNICOMMI2CC_CTR_START_ENABLE;
}

/**
 *  @brief      Disable I2CC STOP generation
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableStopCondition(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR &= ~(UNICOMMI2CC_CTR_STOP_MASK);
}

/**
 *  @brief      Checks if I2CC STOP generation is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If I2CC STOP generation is enabled
 *
 *  @retval     true if I2CC STOP generation is enabled
 *  @retval     false if I2CC STOP generation is disabled
 */
__STATIC_INLINE bool DL_I2CC_isStopConditionEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_STOP_MASK) == UNICOMMI2CC_CTR_STOP_ENABLE);
}

/**
 *  @brief      Enable I2CC STOP generation
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableStopCondition(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR |= UNICOMMI2CC_CTR_STOP_ENABLE;
}

/**
 *  @brief      Disable I2CC data acknowledge (ACK or NACK)
 *
 *  When the I2CC module operates in receiver mode, the ACK bit can be
 *  cleared when no further data needs to be received from the target
 *  transmitter.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableACK(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR &= ~(UNICOMMI2CC_CTR_ACK_MASK);
}

/**
 *  @brief      Checks if I2CC data acknowledge (ACK or NACK) is
 *              enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If I2CC data acknowledge is enabled
 *
 *  @retval     true if I2CC data acknowledge is enabled
 *  @retval     false if I2CC data acknowledge is disabled
 */
__STATIC_INLINE bool DL_I2CC_isACKEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_ACK_MASK) == UNICOMMI2CC_CTR_ACK_ENABLE);
}

/**
 *  @brief      Enable I2CC data acknowledge (ACK or NACK)
 *
 *  When the I2CC module operates in receiver mode, the ACK bit is
 *  normally set causing the I2CC bus to transmit an acknowledge
 *  automatically after each byte.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableACK(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CTR |= UNICOMMI2CC_CTR_ACK_MASK;
}

/**
 *  @brief      Get transaction length in bytes
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     Length of I2CC transaction in bytes
 *
 *  @retval     [0x000, 0xfff]
 */
__STATIC_INLINE uint32_t DL_I2CC_getTransactionLength(DL_UNICOMM_Inst_Regs *unicomm)
{
    // Only allow this feature if the unicomm can support it
    ASSERT(DL_UNICOMM_isAdvanceFeaturesEnabled(unicomm));
    return ((unicomm->i2cc->CTR & UNICOMMI2CC_CTR_BLEN_MASK) >> UNICOMMI2CC_CTR_BLEN_OFS);
}

/**
 *  @brief      Set transaction length in bytes
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @param[in]  length      Length of I2CC transaction in bytes [0x000, 0xfff]
 */
__STATIC_INLINE void DL_I2CC_setTransactionLength(DL_UNICOMM_Inst_Regs *unicomm, uint32_t length)
{
    // Only allow this feature if the unicomm can support it
    ASSERT(DL_UNICOMM_isAdvanceFeaturesEnabled(unicomm));

    DL_Common_updateReg(&unicomm->i2cc->CTR, (length << UNICOMMI2CC_CTR_BLEN_OFS), UNICOMMI2CC_CTR_BLEN_MASK);
}

/**
 *  @brief      Get status of I2CC bus for
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Status of I2CC bus for
 *
 *  @retval     Bitwise OR of @ref DL_I2CC_STATUS
 */
__STATIC_INLINE uint32_t DL_I2CC_getStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->SR);
}

/**
 *  @brief      Get transaction count in bytes
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Current 12-bit countdown value of the transaction
 *
 *  @retval     [0x000, 0xfff]
 */
__STATIC_INLINE uint16_t DL_I2CC_getTransactionCount(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint16_t)((unicomm->i2cc->SR & UNICOMMI2CC_SR_BCNT_MASK) >> UNICOMMI2CC_SR_BCNT_OFS));
}

/**
 *  @brief      Get byte of data from UNICOMMI2CC
 *
 *  If using FIFO, it is first byte from the RX FIFO.
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Last received byte of data
 *
 *  @retval     [0x00, 0xff]
 */
__STATIC_INLINE uint8_t DL_I2CC_receiveData(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint8_t)(unicomm->i2cc->RXDATA & UNICOMMI2CC_RXDATA_DATA_MASK));
}

/**
 *  @brief      Set next byte to be transferred during the next transaction
 *
 *  Does not transmit data until @ref DL_I2CC_startTransfer
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  data    Data to be transferred during the next transaction.
 *                      [0x00, 0xff]
 */
__STATIC_INLINE void DL_I2CC_transmitData(DL_UNICOMM_Inst_Regs *unicomm, uint8_t data)
{
    unicomm->i2cc->TXDATA = data;
}

/**
 *  @brief      Get timer period
 *  This field is used in the equation to configure SCL_PERIOD:
 *
 *  SCL_PERIOD = (1 + TPR) * (SCL_LP + SCL_HP) * INT_CLK_PRD
 *
 *  where:
 *  SCL_PRD is the SCL line period (I2CC clock)
 *
 *  TPR is the Timer Period register value (range of 1 to 127)
 *
 *  SCL_LP is the SCL Low period (fixed at 6)
 *  SCL_HP is the SCL High period (fixed at 4)
 *
 *  CLK_PRD is the functional clock period in ns
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @return     Timer period
 *
 *  @retval     [0x00, 0x7f]
 */
__STATIC_INLINE uint8_t DL_I2CC_getTimerPeriod(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint8_t)(unicomm->i2cc->TPR & UNICOMMI2CC_TPR_TPR_MASK));
}

/**
 *  @brief      Set timer period
 *  This field is used in the equation to configure SCL_PERIOD:
 *
 *  SCL_PERIOD = (1 + TPR) * (SCL_LP + SCL_HP) * INT_CLK_PRD
 *
 *  where:
 *  SCL_PRD is the SCL line period (I2CC clock)
 *
 *  TPR is the Timer Period register value (range of 1 to 127)
 *
 *  SCL_LP is the SCL Low period (fixed at 6)
 *  SCL_HP is the SCL High period (fixed at 4)
 *
 *  CLK_PRD is the functional clock period in ns
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  period  Timer period [0x00, 0x7f]
 */
__STATIC_INLINE void DL_I2CC_setTimerPeriod(DL_UNICOMM_Inst_Regs *unicomm, uint8_t period)
{
    unicomm->i2cc->TPR = period;
}

/**
 *  @brief      Disable multimode
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableMultiMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR &= ~(UNICOMMI2CC_CR_MCTL_MASK);
}

/**
 *  @brief      Checks if multimode is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If multimode is enabled
 *
 *  @retval     true if multimode is enabled
 *  @retval     false if multimode is disabled
 */
__STATIC_INLINE bool DL_I2CC_isMultiModeEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CR & UNICOMMI2CC_CR_MCTL_MASK) == UNICOMMI2CC_CR_MCTL_ENABLE);
}

/**
 *  @brief      Enable multimode
 *
 *  In multimode, the SCL high time counts once the SCL line has been
 *  detected high. If this is not enabled, the high time counts as soon as the
 *  SCL line has been set high by the UNICOMMI2CC
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableMultiMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR |= UNICOMMI2CC_CR_MCTL_ENABLE;
}

/**
 *  @brief      Disable controller
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disable(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR &= ~(UNICOMMI2CC_CR_ENABLE_MASK);
}

/**
 *  @brief      Checks if controller is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If is enabled
 *
 *  @retval     true if is enabled
 *  @retval     false if is disabled
 */
__STATIC_INLINE bool DL_I2CC_isEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CR & UNICOMMI2CC_CR_ENABLE_MASK) == UNICOMMI2CC_CR_ENABLE_ENABLE);
}

/**
 *  @brief      Enable controller
 *
 *  After has enabled, it should not be re-enabled unless it has been
 *  disabled or by a reset, otherwise transfer failures may occur.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enable(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR |= UNICOMMI2CC_CR_ENABLE_ENABLE;
}

/**
 *  @brief      Disable clock stretching
 *
 *  Clock stretching can be disabled if no target on the bus supports clock
 *  stretching; however, it should be typically enabled to be compliant with
 *  I2CC specification.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableClockStretching(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR &= ~(UNICOMMI2CC_CR_CLKSTRETCH_MASK);
}

/**
 *  @brief      Checks if clock stretching is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If clock stretching is enabled
 *
 *  @retval     true if clock stretching is enabled
 *  @retval     false if clock stretching is disabled
 */
__STATIC_INLINE bool DL_I2CC_isClockStretchingEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->CR & UNICOMMI2CC_CR_CLKSTRETCH_MASK) == UNICOMMI2CC_CR_CLKSTRETCH_ENABLE);
}

/**
 *  @brief      Enable clock stretching
 *
 *  Clock stretching can be disabled if no target on the bus supports clock
 *  stretching; however, it should be typically enabled to be compliant with UNICOMMI2CC
 *  specification.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableClockStretching(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->CR |= UNICOMMI2CC_CR_CLKSTRETCH_ENABLE;
}

/**
 *  @brief      Get SCL signal status
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Status of SCL signal
 *
 *  @retval     One of @ref DL_I2CC_SCL
 */
__STATIC_INLINE DL_I2CC_SCL DL_I2CC_getSCLStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t sclStatus = unicomm->i2cc->BMON & UNICOMMI2CC_BMON_SCL_MASK;

    return (DL_I2CC_SCL)(sclStatus);
}

/**
 *  @brief      Get SDA signal status
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Status of SDA signal
 *
 *  @retval     One of @ref DL_I2CC_SDA
 */
__STATIC_INLINE DL_I2CC_SDA DL_I2CC_getSDAStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t sdaStatus = unicomm->i2cc->BMON & UNICOMMI2CC_BMON_SDA_MASK;

    return (DL_I2CC_SDA)(sdaStatus);
}

/**
 *  @brief      Get TX FIFO threshold level
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @return     Indicates at what fill level in the TX FIFO a threshold will be
 *              generated
 *
 *  @retval     One of @ref DL_I2CC_TX_FIFO_LEVEL
 */
__STATIC_INLINE DL_I2CC_TX_FIFO_LEVEL DL_I2CC_getTXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t level = unicomm->i2cc->IFLS & UNICOMMI2CC_IFLS_TXIFLSEL_MASK;

    return (DL_I2CC_TX_FIFO_LEVEL)(level);
}

/**
 *  @brief      Set TX FIFO threshold level
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  level   Indicates at what fill level in the TX FIFO a threshold
 *                      will be generated.
 *                      One of @ref DL_I2CC_TX_FIFO_LEVEL.
 */
__STATIC_INLINE void DL_I2CC_setTXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_TX_FIFO_LEVEL level)
{
    DL_Common_updateReg(&unicomm->i2cc->IFLS, (uint32_t)level, UNICOMMI2CC_IFLS_TXIFLSEL_MASK);
}

/**
 *  @brief      Stop controller TX FIFO flush
 *
 *  Before stopping the flush, check if @ref DL_I2C_isControllerTXFIFOEmpty,
 *  indicating flush is complete.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_stopFlushTXFIFO(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->IFLS &= ~(UNICOMMI2CC_IFLS_TXCLR_ENABLE);
}

/**
 *  @brief      Start controller TX FIFO flush
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_startFlushTXFIFO(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->IFLS |= (UNICOMMI2CC_IFLS_TXCLR_ENABLE);
}

/**
 *  @brief      Get RX FIFO threshold level
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @return     Indicates at what fill level in the RX FIFO a threshold will be
 *              generated
 *
 *  @retval     One of @ref DL_I2CC_RX_FIFO_LEVEL
 */
__STATIC_INLINE DL_I2CC_RX_FIFO_LEVEL DL_I2CC_getRXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t level = unicomm->i2cc->IFLS & UNICOMMI2CC_IFLS_RXIFLSEL_MASK;

    return (DL_I2CC_RX_FIFO_LEVEL)(level);
}

/**
 *  @brief      Set RX FIFO threshold level
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  level   Indicates at what fill level in the RX FIFO a threshold
 *                      will be generated.
 *                      One of @ref DL_I2CC_RX_FIFO_LEVEL.
 */
__STATIC_INLINE void DL_I2CC_setRXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_RX_FIFO_LEVEL level)
{
    DL_Common_updateReg(&unicomm->i2cc->IFLS, (uint32_t)level, UNICOMMI2CC_IFLS_RXIFLSEL_MASK);
}

/**
 *  @brief      Stop controller RX FIFO flush
 *
 *  Before stopping the flush, check if @ref DL_I2C_isControllerRXFIFOEmpty,
 *  indicating flush is complete.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_stopFlushRXFIFO(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->IFLS &= ~(UNICOMMI2CC_IFLS_RXCLR_ENABLE);
}

/**
 *  @brief      Start controller RX FIFO flush
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_startFlushRXFIFO(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->IFLS |= (UNICOMMI2CC_IFLS_RXCLR_ENABLE);
}

/**
 *  @brief      Get number of bytes which can be read from RX FIFO
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Number of bytes which can be read from RX FIFO
 *
 *  @retval     [0x0, 0x8]
 */
__STATIC_INLINE uint32_t DL_I2CC_getRXFIFOCounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->SR & UNICOMMI2CC_SR_BCNT_MASK);
}

/**
 *  @brief      Get number of bytes which can be put into TX FIFO
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *
 *  @return     Number of bytes which can be put into TX FIFO
 *
 *  @retval     [0x0, 0x8]
 */
__STATIC_INLINE uint32_t DL_I2CC_getTXFIFOCounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->SR & UNICOMMI2CC_SR_BCNT_MASK) >> UNICOMMI2CC_SR_BCNT_OFS);
}

/**
 *  @brief      Checks if controller RX FIFO flush is active
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     If controller RX FIFO flush is active
 *
 *  @retval     true if controller RX FIFO flush is active
 *  @retval     false if controller RX FIFO flush is not active
 */
__STATIC_INLINE bool DL_I2CC_isRXFIFOFlushActive(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->IFLS & UNICOMMI2CC_IFLS_RXCLR_MASK) == UNICOMMI2CC_IFLS_RXCLR_ENABLE);
}

/**
 *  @brief      Checks if controller TX FIFO flush is active
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     If controller TX FIFO flush is active
 *
 *  @retval     true if controller TX FIFO flush is active
 *  @retval     false if controller TX FIFO flush is not active
 */
__STATIC_INLINE bool DL_I2CC_isTXFIFOFlushActive(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->IFLS & UNICOMMI2CC_IFLS_TXCLR_MASK) == UNICOMMI2CC_IFLS_TXCLR_ENABLE);
}

/**
 *  @brief      Enable I2CC interrupts
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to enable. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 */
__STATIC_INLINE void DL_I2CC_enableInterrupt(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->i2cc->CPU_INT.IMASK |= interruptMask;
}

/**
 *  @brief      Disable I2CC interrupts
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to disable. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 */
__STATIC_INLINE void DL_I2CC_disableInterrupt(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->i2cc->CPU_INT.IMASK &= ~(interruptMask);
}

/**
 *  @brief      Check which I2CC interrupts are enabled
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 *
 *  @return     Which of the requested I2CC interrupts are enabled
 *
 *  @retval     Bitwise OR of @ref DL_I2CC_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_I2CC_getEnabledInterrupts(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->i2cc->CPU_INT.IMASK & interruptMask);
}

/**
 *  @brief      Check interrupt flag of enabled I2CC interrupts
 *
 *  Checks if any of the I2CC interrupts that were previously enabled are
 *  pending.
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 *
 *  @return     Which of the requested I2CC interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_I2CC_INTERRUPT values
 *
 *  @sa         DL_I2CC_enableInterrupt
 */
__STATIC_INLINE uint32_t DL_I2CC_getEnabledInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->i2cc->CPU_INT.MIS & interruptMask);
}

/**
 *  @brief      Check interrupt flag of any I2CC interrupt
 *
 *  Checks if any of the I2CC interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 *
 *  @return     Which of the requested I2CC interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_I2CC_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_I2CC_getRawInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->i2cc->CPU_INT.RIS & interruptMask);
}

/**
 *  @brief      Get highest priority pending I2CC interrupt
 *
 *  Checks if any of the I2CC interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The highest priority pending I2CC interrupt
 *
 *  @retval     One of @ref DL_I2CC_IIDX
 */
__STATIC_INLINE DL_I2CC_IIDX DL_I2CC_getPendingInterrupt(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((DL_I2CC_IIDX)unicomm->i2cc->CPU_INT.IIDX);
}

/**
 *  @brief      Clear pending I2CC interrupts
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to clear. Bitwise OR of
 *                             @ref DL_I2CC_INTERRUPT.
 */
__STATIC_INLINE void DL_I2CC_clearInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->i2cc->CPU_INT.ICLR = interruptMask;
}

/**
 *  @brief Enables I2CC interrupt for triggering DMA events
 *
 * Enables the I2CC interrupt to be used as the condition to generate an
 * event to directly trigger the DMA.
 *
 * Each event publisher @ref DL_I2CC_EVENT_ROUTE can set any one of
 * @ref DL_I2CC_DMA_INTERRUPT.
 *
 * @note Only one interrupt source should be enabled at a time.
 *
 *  @param[in]  unicomm        Pointer to the register overlay for the peripheral
 *  @param[in]  index      Specifies the register event publisher to configure
 *  @param[in]  interrupt  Interrupt to enable as the trigger condition for
 *                         the DMA. One of @ref DL_I2CC_DMA_INTERRUPT.
 */
__STATIC_INLINE void DL_I2CC_enableDMAEvent(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_EVENT_ROUTE index,
                                            uint32_t interrupt)
{
    switch (index)
    {
        case DL_I2CC_EVENT_ROUTE_1:
            unicomm->i2cc->DMA_TRIG1.IMASK = interrupt;
            break;
        case DL_I2CC_EVENT_ROUTE_2:
            unicomm->i2cc->DMA_TRIG0.IMASK = interrupt;
            break;
        default:
            break;
    }
}

/**
 *  @brief Disables I2CC interrupt from triggering DMA events
 *
 * Disables the I2CC interrupt from being used as the condition to generate an
 * event to directly trigger the DMA.
 *
 * Each event publisher @ref DL_I2CC_EVENT_ROUTE can set any one of
 * @ref DL_I2CC_DMA_INTERRUPT.
 *
 *  @param[in]  unicomm        Pointer to the register overlay for the peripheral
 *  @param[in]  index      Specifies the register event publisher to configure
 *  @param[in]  interrupt  Interrupt to disable as the trigger condition for
 *                         the DMA. One of @ref DL_I2CC_DMA_INTERRUPT.
 */
__STATIC_INLINE void DL_I2CC_disableDMAEvent(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_EVENT_ROUTE index,
                                             uint32_t interrupt)
{
    switch (index)
    {
        case DL_I2CC_EVENT_ROUTE_1:
            unicomm->i2cc->DMA_TRIG1.IMASK &= ~(interrupt);
            break;
        case DL_I2CC_EVENT_ROUTE_2:
            unicomm->i2cc->DMA_TRIG0.IMASK &= ~(interrupt);
            break;
        default:
            break;
    }
}

/**
 *  @brief Check which I2CC interrupt for DMA receive events is enabled
 *
 *  This API checks the event publisher register as selected by
 *  @ref DL_I2CC_EVENT_ROUTE, which are used for triggering the DMA for
 *  or Target and receive or transmit events.
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the peripheral
 *  @param[in]  index          Specifies the register event publisher to configure
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_DMA_INTERRUPT.
 *
 *  @note Only one interrupt source should be enabled at a time.
 *
 *  @return     The requested I2CC interrupt status
 *
 *  @retval     One of @ref DL_I2CC_DMA_INTERRUPT
 */
__STATIC_INLINE uint32_t DL_I2CC_getEnabledDMAEvents(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_EVENT_ROUTE index,
                                                     uint32_t interruptMask)
{
    volatile uint32_t *pReg = &unicomm->i2cc->DMA_TRIG1.IMASK;

    return ((*(pReg + (uint32_t)index) & interruptMask));
}

/**
 *  @brief Check interrupt flag of enabled I2CC interrupt for DMA event
 *
 *  Checks if any of the I2CC interrupts for the DMA receive event that were
 *  previously enabled are pending.
 *  This API checks the event publisher register as selected by
 *  @ref DL_I2CC_EVENT_ROUTE, which are used for triggering the DMA for
 *  or Target and receive or transmit events.
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the peripheral
 *  @param[in]  index          Specifies the register event publisher to configure
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_DMA_INTERRUPT.
 *
 *  @note Only one interrupt source should be enabled at a time.
 *
 *  @return     The requested I2CC interrupt status
 *
 *  @retval     One of @ref DL_I2CC_DMA_INTERRUPT
 *
 *  @sa         DL_I2CC_enableDMAEvent
 */
__STATIC_INLINE uint32_t DL_I2CC_getEnabledDMAEventStatus(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_EVENT_ROUTE index,
                                                          uint32_t interruptMask)
{
    const volatile uint32_t *pReg = &unicomm->i2cc->DMA_TRIG1.MIS;

    return ((*(pReg + (uint32_t)index) & interruptMask));
}

/**
 *  @brief Check interrupt flag of any I2CC interrupt for DMA event
 *
 *  Checks if any of the I2CC interrupts for DMA receive event are pending.
 *  Interrupts do not have to be previously enabled.
 *  This API checks the event publisher register as selected by
 *  @ref DL_I2CC_EVENT_ROUTE, which are used for triggering the DMA for
 *  or Target and receive or transmit events.
 *
 *  @param[in]  unicomm            Pointer to the register overlay for the peripheral
 *  @param[in]  index          Specifies the register event publisher to configure
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_I2CC_DMA_INTERRUPT.
 *
 *  @return     Which of the requested I2CC interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_I2CC_DMA_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_I2CC_getRawDMAEventStatus(DL_UNICOMM_Inst_Regs *unicomm, DL_I2CC_EVENT_ROUTE index,
                                                      uint32_t interruptMask)
{
    const volatile uint32_t *pReg = &unicomm->i2cc->DMA_TRIG1.RIS;

    return ((*(pReg + (uint32_t)index) & interruptMask));
}

/**
 *  @brief      Get the Timeout Counter A value
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The Timeout A counter value
 *
 *  @retval     Value between [0x0, 0xFF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getTimeoutACount(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->TIMEOUT_CTL & UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_MASK);
}

/**
 *  @brief      Set the Timeout Counter A value
 *
 *  Timeout A is used for SCL low detection. This field contains the upper 8
 *  bits of a 12-bit pre-load value for the Timeout A count.
 *  NOTE: The value of the counter must be greater than 1 to enable the
 *  timeout. Each count is equal to 520 times the timeout period of the
 *  functional clock. For example, with 8MHz functional clock and a
 *  100KHz operating I2CC clock, one timeout period will be equal to
 *  (1 / 8MHz) * 520 = 65us.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  count   The value to set the Timeout A counter to.
 *                      Value between [0x0, 0xFF]
 */
__STATIC_INLINE void DL_I2CC_setTimeoutACount(DL_UNICOMM_Inst_Regs *unicomm, uint32_t count)
{
    DL_Common_updateReg(&unicomm->i2cc->TIMEOUT_CTL, count, UNICOMMI2CC_TIMEOUT_CTL_TCNTLA_MASK);
}

/**
 *  @brief      Disable Timeout Counter A
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableTimeoutA(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->TIMEOUT_CTL &= ~(UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_MASK);
}

/**
 *  @brief      Checks if Timeout Counter A is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If Timeout Counter A is enabled
 *
 *  @retval     true if Timeout Counter A is enabled
 *  @retval     false if Timeout Counter A is disabled
 */
__STATIC_INLINE bool DL_I2CC_isTimeoutAEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->TIMEOUT_CTL & UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_MASK) ==
            UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_ENABLE);
}

/**
 *  @brief      Enable Timeout Counter A
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableTimeoutA(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->TIMEOUT_CTL |= UNICOMMI2CC_TIMEOUT_CTL_TCNTAEN_ENABLE;
}

/**
 *  @brief      Get the current Timer Counter A value
 *
 *  This field contains the upper 8 bits of a 12-bit current counter for
 *  Timeout Counter A.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The Timeout A counter value
 *
 *  @retval     Value between [0x0, 0xFF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getCurrentTimeoutACounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->TIMEOUT_CNT & UNICOMMI2CC_TIMEOUT_CNT_TCNTA_MASK);
}

/**
 *  @brief      Get the Timeout Counter B value
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The Timeout B counter value
 *
 *  @retval     Value between [0x0, 0xFF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getTimeoutBCount(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->TIMEOUT_CTL & UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_MASK) >> UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_OFS);
}

/**
 *  @brief      Set the Timeout Counter B value
 *
 *  Timeout B is used for SCL high detection. This field contains the upper 8
 *  bits of a 12-bit pre-load value for the Timeout A count.
 *  NOTE: The value of the counter must be greater than 1 to enable the
 *  timeout. Each count is equal to 1* clock period. For example, with 10MHz
 *  functional clock one timeout period will be equal to 1 * 10ns.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  count   The value to set the Timeout A counter to.
 *                      Value between [0x0, 0xFF]
 */
__STATIC_INLINE void DL_I2CC_setTimeoutBCount(DL_UNICOMM_Inst_Regs *unicomm, uint32_t count)
{
    DL_Common_updateReg(&unicomm->i2cc->TIMEOUT_CTL, (count << UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_OFS),
                        UNICOMMI2CC_TIMEOUT_CTL_TCNTLB_MASK);
}

/**
 *  @brief      Disable Timeout Counter B
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_disableTimeoutB(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->TIMEOUT_CTL &= ~(UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_MASK);
}

/**
 *  @brief      Checks if Timeout Counter B is enabled
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     If Timeout Counter B is enabled
 *
 *  @retval     true if Timeout Counter B is enabled
 *  @retval     false if Timeout Counter B is disabled
 */
__STATIC_INLINE bool DL_I2CC_isTimeoutBEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->i2cc->TIMEOUT_CTL & UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_MASK) ==
            UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_ENABLE);
}

/**
 *  @brief      Enable Timeout Counter B
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_I2CC_enableTimeoutB(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->i2cc->TIMEOUT_CTL |= UNICOMMI2CC_TIMEOUT_CTL_TCNTBEN_ENABLE;
}

/**
 *  @brief      Get the current Timer Counter B value
 *
 *  This field contains the upper 8 bits of a 12-bit current counter for
 *  Timeout Counter B.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *
 *  @return     The Timeout B counter value
 *
 *  @retval     Value between [0x0, 0xFF]
 */
__STATIC_INLINE uint32_t DL_I2CC_getCurrentTimeoutBCounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->i2cc->TIMEOUT_CNT & UNICOMMI2CC_TIMEOUT_CNT_TCNTB_MASK);
}

#ifdef __cplusplus
}
#endif

#endif /* DL_UNICOMMI2C_H */
       /** @}*/
