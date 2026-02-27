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
 * @defgroup DL_UNICOMMUART_AM13E230X  Driverlib UART API
 * @ingroup DL_AM13E230X
 *
 * @{
 */

#ifndef DL_UNICOMMUART_H
#define DL_UNICOMMUART_H

#include <stdbool.h>
#include <stdint.h>

#include "soc.h"
#include "dl_common.h"
#include "hw_unicommuart.h"
#include "dl_unicomm.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @name DL_UART_MAIN_MACROS
 *  @anchor DL_UART_MAIN_MACROS
 *  Macros to retain compatibility with standalone dl_uart_main APIs
 *  @{
 */
/*! Redirects to @ref DL_UART_INTERRUPT_DMA_DONE_TX */
#define DL_UART_MAIN_INTERRUPT_DMA_DONE_TX      DL_UART_INTERRUPT_DMA_DONE_TX
/*! Redirects to @ref DL_UART_INTERRUPT_DMA_DONE_RX */
#define DL_UART_MAIN_INTERRUPT_DMA_DONE_RX      DL_UART_INTERRUPT_DMA_DONE_RX
/*! Redirects to @ref DL_UART_INTERRUPT_CTS_DONE */
#define DL_UART_MAIN_INTERRUPT_CTS_DONE         DL_UART_INTERRUPT_CTS_DONE
/*! Redirects to @ref DL_UART_INTERRUPT_EOT_DONE */
#define DL_UART_MAIN_INTERRUPT_EOT_DONE         DL_UART_INTERRUPT_EOT_DONE
/*! Redirects to @ref DL_UART_INTERRUPT_TX */
#define DL_UART_MAIN_INTERRUPT_TX               DL_UART_INTERRUPT_TX
/*! Redirects to @ref DL_UART_INTERRUPT_RX */
#define DL_UART_MAIN_INTERRUPT_RX               DL_UART_INTERRUPT_RX
/*! Redirects to @ref DL_UART_INTERRUPT_LTOUT */
#define DL_UART_MAIN_INTERRUPT_LTOUT            DL_UART_INTERRUPT_LTOUT
/*! Redirects to @ref DL_UART_INTERRUPT_RXD_POS_EDGE */
#define DL_UART_MAIN_INTERRUPT_RXD_POS_EDGE     DL_UART_INTERRUPT_RXD_POS_EDGE
/*! Redirects to @ref DL_UART_INTERRUPT_RXD_NEG_EDGE */
#define DL_UART_MAIN_INTERRUPT_RXD_NEG_EDGE     DL_UART_INTERRUPT_RXD_NEG_EDGE
/*! Redirects to @ref DL_UART_INTERRUPT_OVERRUN_ERROR */
#define DL_UART_MAIN_INTERRUPT_OVERRUN_ERROR    DL_UART_INTERRUPT_OVERRUN_ERROR
/*! Redirects to @ref DL_UART_INTERRUPT_BREAK_ERROR */
#define DL_UART_MAIN_INTERRUPT_BREAK_ERROR      DL_UART_INTERRUPT_BREAK_ERROR
/*! Redirects to @ref DL_UART_INTERRUPT_PARITY_ERROR */
#define DL_UART_MAIN_INTERRUPT_PARITY_ERROR     DL_UART_INTERRUPT_PARITY_ERROR
/*! Redirects to @ref DL_UART_INTERRUPT_FRAMING_ERROR */
#define DL_UART_MAIN_INTERRUPT_FRAMING_ERROR    DL_UART_INTERRUPT_FRAMING_ERROR
/*! Redirects to @ref DL_UART_INTERRUPT_RX_TIMEOUT_ERROR */
#define DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR DL_UART_INTERRUPT_RX_TIMEOUT_ERROR
/*! Redirects to @ref DL_UART_INTERRUPT_NOISE_ERROR */
#define DL_UART_MAIN_INTERRUPT_NOISE_ERROR      DL_UART_INTERRUPT_NOISE_ERROR
/*! Redirects to @ref DL_UART_IIDX_DMA_DONE_TX */
#define DL_UART_MAIN_IIDX_DMA_DONE_TX           DL_UART_IIDX_DMA_DONE_TX
/*! Redirects to @ref DL_UART_IIDX_DMA_DONE_RX */
#define DL_UART_MAIN_IIDX_DMA_DONE_RX           DL_UART_IIDX_DMA_DONE_RX
/*! Redirects to @ref DL_UART_IIDX_CTS_DONE */
#define DL_UART_MAIN_IIDX_CTS_DONE              DL_UART_IIDX_CTS_DONE
/*! Redirects to @ref DL_UART_IIDX_EOT_DONE */
#define DL_UART_MAIN_IIDX_EOT_DONE              DL_UART_IIDX_EOT_DONE
/*! Redirects to @ref DL_UART_IIDX_TX */
#define DL_UART_MAIN_IIDX_TX                    DL_UART_IIDX_TX
/*! Redirects to @ref DL_UART_IIDX_RX */
#define DL_UART_MAIN_IIDX_RX                    DL_UART_IIDX_RX
/*! Redirects to @ref DL_UART_IIDX_RXD_POS_EDGE */
#define DL_UART_MAIN_IIDX_RXD_POS_EDGE          DL_UART_IIDX_RXD_POS_EDGE
/*! Redirects to @ref DL_UART_IIDX_RXD_NEG_EDGE */
#define DL_UART_MAIN_IIDX_RXD_NEG_EDGE          DL_UART_IIDX_RXD_NEG_EDGE
/*! Redirects to @ref DL_UART_IIDX_OVERRUN_ERROR */
#define DL_UART_MAIN_IIDX_OVERRUN_ERROR         DL_UART_IIDX_OVERRUN_ERROR
/*! Redirects to @ref DL_UART_IIDX_BREAK_ERROR */
#define DL_UART_MAIN_IIDX_BREAK_ERROR           DL_UART_IIDX_BREAK_ERROR
/*! Redirects to @ref DL_UART_IIDX_PARITY_ERROR */
#define DL_UART_MAIN_IIDX_PARITY_ERROR          DL_UART_IIDX_PARITY_ERROR
/*! Redirects to @ref DL_UART_IIDX_FRAMING_ERROR */
#define DL_UART_MAIN_IIDX_FRAMING_ERROR         DL_UART_IIDX_FRAMING_ERROR
/*! Redirects to @ref DL_UART_IIDX_RX_TIMEOUT_ERROR */
#define DL_UART_MAIN_IIDX_RX_TIMEOUT_ERROR      DL_UART_IIDX_RX_TIMEOUT_ERROR
/*! Redirects to @ref DL_UART_IIDX_NOISE_ERROR */
#define DL_UART_MAIN_IIDX_NOISE_ERROR           DL_UART_IIDX_NOISE_ERROR
/*! Redirects to @ref DL_UART_IIDX_NO_INTERRUPT */
#define DL_UART_MAIN_IIDX_NO_INTERRUPT          DL_UART_IIDX_NO_INTERRUPT
/*! Redirects to @ref DL_UART_DMA_INTERRUPT_RX */
#define DL_UART_MAIN_DMA_INTERRUPT_RX           DL_UART_DMA_INTERRUPT_RX
/*! Redirects to @ref DL_UART_DMA_INTERRUPT_RX_TIMEOUT */
#define DL_UART_MAIN_DMA_INTERRUPT_RX_TIMEOUT   DL_UART_DMA_INTERRUPT_RX_TIMEOUT
/*! Redirects to @ref DL_UART_DMA_INTERRUPT_TX */
#define DL_UART_MAIN_DMA_INTERRUPT_TX           DL_UART_DMA_INTERRUPT_TX
/*! Redirects to @ref DL_UART_ERROR_OVERRUN */
#define DL_UART_MAIN_ERROR_OVERRUN              DL_UART_ERROR_OVERRUN
/*! Redirects to @ref DL_UART_ERROR_BREAK */
#define DL_UART_MAIN_ERROR_BREAK                DL_UART_ERROR_BREAK
/*! Redirects to @ref DL_UART_ERROR_PARITY */
#define DL_UART_MAIN_ERROR_PARITY               DL_UART_ERROR_PARITY
/*! Redirects to @ref DL_UART_ERROR_FRAMING */
#define DL_UART_MAIN_ERROR_FRAMING              DL_UART_ERROR_FRAMING
/*! Redirects to @ref DL_UART_OVERSAMPLING_RATE_16X */
#define DL_UART_MAIN_OVERSAMPLING_RATE_16X      DL_UART_OVERSAMPLING_RATE_16X
/*! Redirects to @ref DL_UART_OVERSAMPLING_RATE_8X */
#define DL_UART_MAIN_OVERSAMPLING_RATE_8X       DL_UART_OVERSAMPLING_RATE_8X
/*! Redirects to @ref DL_UART_OVERSAMPLING_RATE_3X */
#define DL_UART_MAIN_OVERSAMPLING_RATE_3X       DL_UART_OVERSAMPLING_RATE_3X
/*! Redirects to @ref DL_UART_PARITY_EVEN */
#define DL_UART_MAIN_PARITY_EVEN                DL_UART_PARITY_EVEN
/*! Redirects to @ref DL_UART_PARITY_ODD */
#define DL_UART_MAIN_PARITY_ODD                 DL_UART_PARITY_ODD
/*! Redirects to @ref DL_UART_PARITY_STICK_ONE */
#define DL_UART_MAIN_PARITY_STICK_ONE           DL_UART_PARITY_STICK_ONE
/*! Redirects to @ref DL_UART_PARITY_STICK_ZERO */
#define DL_UART_MAIN_PARITY_STICK_ZERO          DL_UART_PARITY_STICK_ZERO
/*! Redirects to @ref DL_UART_PARITY_NONE */
#define DL_UART_MAIN_PARITY_NONE                DL_UART_PARITY_NONE
/*! Redirects to @ref DL_UART_WORD_LENGTH_5_BITS */
#define DL_UART_MAIN_WORD_LENGTH_5_BITS         DL_UART_WORD_LENGTH_5_BITS
/*! Redirects to @ref DL_UART_WORD_LENGTH_6_BITS */
#define DL_UART_MAIN_WORD_LENGTH_6_BITS         DL_UART_WORD_LENGTH_6_BITS
/*! Redirects to @ref DL_UART_WORD_LENGTH_7_BITS */
#define DL_UART_MAIN_WORD_LENGTH_7_BITS         DL_UART_WORD_LENGTH_7_BITS
/*! Redirects to @ref DL_UART_WORD_LENGTH_8_BITS */
#define DL_UART_MAIN_WORD_LENGTH_8_BITS         DL_UART_WORD_LENGTH_8_BITS
/*! Redirects to @ref DL_UART_MODE_NORMAL */
#define DL_UART_MAIN_MODE_NORMAL                DL_UART_MODE_NORMAL
/*! Redirects to @ref DL_UART_MODE_RS485 */
#define DL_UART_MAIN_MODE_RS485                 DL_UART_MODE_RS485
/*! Redirects to @ref DL_UART_MODE_IDLE_LINE */
#define DL_UART_MAIN_MODE_IDLE_LINE             DL_UART_MODE_IDLE_LINE
/*! Redirects to @ref DL_UART_MODE_ADDR_9_BIT */
#define DL_UART_MAIN_MODE_ADDR_9_BIT            DL_UART_MODE_ADDR_9_BIT
/*! Redirects to @ref DL_UART_DIRECTION_TX */
#define DL_UART_MAIN_DIRECTION_TX               DL_UART_DIRECTION_TX
/*! Redirects to @ref DL_UART_DIRECTION_RX */
#define DL_UART_MAIN_DIRECTION_RX               DL_UART_DIRECTION_RX
/*! Redirects to @ref DL_UART_DIRECTION_TX_RX */
#define DL_UART_MAIN_DIRECTION_TX_RX            DL_UART_DIRECTION_TX_RX
/*! Redirects to @ref DL_UART_DIRECTION_NONE */
#define DL_UART_MAIN_DIRECTION_NONE             DL_UART_DIRECTION_NONE
/*! Redirects to @ref DL_UART_CLOCK_BUSCLK */
#define DL_UART_MAIN_CLOCK_BUSCLK               DL_UART_CLOCK_BUSCLK
/*! Redirects to @ref DL_UART_FLOW_CONTROL_RTS */
#define DL_UART_MAIN_FLOW_CONTROL_RTS           DL_UART_FLOW_CONTROL_RTS
/*! Redirects to @ref DL_UART_FLOW_CONTROL_CTS */
#define DL_UART_MAIN_FLOW_CONTROL_CTS           DL_UART_FLOW_CONTROL_CTS
/*! Redirects to @ref DL_UART_FLOW_CONTROL_RTS_CTS */
#define DL_UART_MAIN_FLOW_CONTROL_RTS_CTS       DL_UART_FLOW_CONTROL_RTS_CTS
/*! Redirects to @ref DL_UART_FLOW_CONTROL_NONE */
#define DL_UART_MAIN_FLOW_CONTROL_NONE          DL_UART_FLOW_CONTROL_NONE
/*! Redirects to @ref DL_UART_RTS_ASSERT */
#define DL_UART_MAIN_RTS_ASSERT                 DL_UART_RTS_ASSERT
/*! Redirects to @ref DL_UART_RTS_DEASSERT */
#define DL_UART_MAIN_RTS_DEASSERT               DL_UART_RTS_DEASSERT
/*! Redirects to @ref DL_UART_STOP_BITS_ONE */
#define DL_UART_MAIN_STOP_BITS_ONE              DL_UART_STOP_BITS_ONE
/*! Redirects to @ref DL_UART_STOP_BITS_TWO */
#define DL_UART_MAIN_STOP_BITS_TWO              DL_UART_STOP_BITS_TWO
/*! Redirects to @ref DL_UART_TXD_OUT_LOW */
#define DL_UART_MAIN_TXD_OUT_LOW                DL_UART_TXD_OUT_LOW
/*! Redirects to @ref DL_UART_TXD_OUT_HIGH */
#define DL_UART_MAIN_TXD_OUT_HIGH               DL_UART_TXD_OUT_HIGH
/*! Redirects to @ref DL_UART_TX_FIFO_LEVEL_3_4_EMPTY */
#define DL_UART_MAIN_TX_FIFO_LEVEL_3_4_EMPTY    DL_UART_TX_FIFO_LEVEL_3_4_EMPTY
/*! Redirects to @ref DL_UART_TX_FIFO_LEVEL_1_4_EMPTY */
#define DL_UART_MAIN_TX_FIFO_LEVEL_1_4_EMPTY    DL_UART_TX_FIFO_LEVEL_1_4_EMPTY
/*! Redirects to @ref DL_UART_TX_FIFO_LEVEL_EMPTY */
#define DL_UART_MAIN_TX_FIFO_LEVEL_EMPTY        DL_UART_TX_FIFO_LEVEL_EMPTY
/*! Redirects to @ref DL_UART_RX_FIFO_LEVEL_FULL */
#define DL_UART_MAIN_RX_FIFO_LEVEL_FULL         DL_UART_RX_FIFO_LEVEL_FULL
/*! Redirects to @ref DL_UART_RX_FIFO_LEVEL_3_4_FULL */
#define DL_UART_MAIN_RX_FIFO_LEVEL_3_4_FULL     DL_UART_RX_FIFO_LEVEL_3_4_FULL
/*! Redirects to @ref DL_UART_RX_FIFO_LEVEL_1_2_FULL */
#define DL_UART_MAIN_RX_FIFO_LEVEL_1_2_FULL     DL_UART_RX_FIFO_LEVEL_1_2_FULL
/*! Redirects to @ref DL_UART_RX_FIFO_LEVEL_1_4_FULL */
#define DL_UART_MAIN_RX_FIFO_LEVEL_1_4_FULL     DL_UART_RX_FIFO_LEVEL_1_4_FULL
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_1 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1       DL_UART_CLOCK_DIVIDE_RATIO_1
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_2 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_2       DL_UART_CLOCK_DIVIDE_RATIO_2
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_3 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_3       DL_UART_CLOCK_DIVIDE_RATIO_3
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_4 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_4       DL_UART_CLOCK_DIVIDE_RATIO_4
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_5 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_5       DL_UART_CLOCK_DIVIDE_RATIO_5
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_6 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_6       DL_UART_CLOCK_DIVIDE_RATIO_6
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_7 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_7       DL_UART_CLOCK_DIVIDE_RATIO_7
/*! Redirects to @ref DL_UART_CLOCK_DIVIDE_RATIO_8 */
#define DL_UART_MAIN_CLOCK_DIVIDE_RATIO_8       DL_UART_CLOCK_DIVIDE_RATIO_8
/*! Redirects to @ref DL_UART_backupConfig */
#define DL_UART_Main_backupConfig               DL_UART_backupConfig
/*! Redirects to @ref DL_UART_saveConfiguration */
#define DL_UART_Main_saveConfiguration          DL_UART_saveConfiguration
/*! Redirects to @ref DL_UART_restoreConfiguration */
#define DL_UART_Main_restoreConfiguration       DL_UART_restoreConfiguration

/*! Redirects to @ref DL_UART_Config */
#define DL_UART_Main_Config                          DL_UART_Config
/*! Redirects to @ref DL_UART_ClockConfig */
#define DL_UART_Main_ClockConfig                     DL_UART_ClockConfig
/*! Redirects to @ref DL_UART_init */
#define DL_UART_Main_init                            DL_UART_init
/*! Redirects to @ref DL_UART_enablePower */
#define DL_UART_Main_enablePower                     DL_UART_enablePower
/*! Redirects to @ref DL_UART_disablePower */
#define DL_UART_Main_disablePower                    DL_UART_disablePower
/*! Redirects to @ref DL_UART_isPowerEnabled */
#define DL_UART_Main_isPowerEnabled                  DL_UART_isPowerEnabled
/*! Redirects to @ref DL_UART_reset */
#define DL_UART_Main_reset                           DL_UART_reset
/*! Redirects to @ref DL_UART_enable */
#define DL_UART_Main_enable                          DL_UART_enable
/*! Redirects to @ref DL_UART_isEnabled */
#define DL_UART_Main_isEnabled                       DL_UART_isEnabled
/*! Redirects to @ref DL_UART_disable */
#define DL_UART_Main_disable                         DL_UART_disable
/*! Redirects to @ref DL_UART_setClockConfig */
#define DL_UART_Main_setClockConfig                  DL_UART_setClockConfig
/*! Redirects to @ref DL_UART_getClockConfig */
#define DL_UART_Main_getClockConfig                  DL_UART_getClockConfig
/*! Redirects to @ref DL_UART_configBaudRate */
#define DL_UART_Main_configBaudRate                  DL_UART_configBaudRate
/*! Redirects to @ref DL_UART_setOversampling */
#define DL_UART_Main_setOversampling                 DL_UART_setOversampling
/*! Redirects to @ref DL_UART_getOversampling */
#define DL_UART_Main_getOversampling                 DL_UART_getOversampling
/*! Redirects to @ref DL_UART_enableLoopbackMode */
#define DL_UART_Main_enableLoopbackMode              DL_UART_enableLoopbackMode
/*! Redirects to @ref DL_UART_isLoopbackModeEnabled */
#define DL_UART_Main_isLoopbackModeEnabled           DL_UART_isLoopbackModeEnabled
/*! Redirects to @ref DL_UART_disableLoopbackMode */
#define DL_UART_Main_disableLoopbackMode             DL_UART_disableLoopbackMode
/*! Redirects to @ref DL_UART_setDirection */
#define DL_UART_Main_setDirection                    DL_UART_setDirection
/*! Redirects to @ref DL_UART_getDirection */
#define DL_UART_Main_getDirection                    DL_UART_getDirection
/*! Redirects to @ref DL_UART_enableMajorityVoting */
#define DL_UART_Main_enableMajorityVoting            DL_UART_enableMajorityVoting
/*! Redirects to @ref DL_UART_isMajorityVotingEnabled */
#define DL_UART_Main_isMajorityVotingEnabled         DL_UART_isMajorityVotingEnabled
/*! Redirects to @ref DL_UART_disableMajorityVoting */
#define DL_UART_Main_disableMajorityVoting           DL_UART_disableMajorityVoting
/*! Redirects to @ref DL_UART_enableMSBFirst */
#define DL_UART_Main_enableMSBFirst                  DL_UART_enableMSBFirst
/*! Redirects to @ref DL_UART_isMSBFirstEnabled */
#define DL_UART_Main_isMSBFirstEnabled               DL_UART_isMSBFirstEnabled
/*! Redirects to @ref DL_UART_disableMSBFirst */
#define DL_UART_Main_disableMSBFirst                 DL_UART_disableMSBFirst
/*! Redirects to @ref DL_UART_enableTransmitPinManualControl */
#define DL_UART_Main_enableTransmitPinManualControl  DL_UART_enableTransmitPinManualControl
/*! Redirects to @ref DL_UART_isTransmitPinManualControlEnabled */
#define DL_UART_Main_isTransmitPinManualControlEnabl DL_UART_isTransmitPinManualControlEnabled
/*! Redirects to @ref DL_UART_disableTransmitPinManualControl */
#define DL_UART_Main_disableTransmitPinManualControl DL_UART_disableTransmitPinManualControl
/*! Redirects to @ref DL_UART_setTransmitPinManualOutput */
#define DL_UART_Main_setTransmitPinManualOutput      DL_UART_setTransmitPinManualOutput
/*! Redirects to @ref DL_UART_getTransmitPinManualOutput */
#define DL_UART_Main_getTransmitPinManualOutput      DL_UART_getTransmitPinManualOutput
/*! Redirects to @ref DL_UART_setCommunicationMode */
#define DL_UART_Main_setCommunicationMode            DL_UART_setCommunicationMode
/*! Redirects to @ref DL_UART_getCommunicationMode */
#define DL_UART_Main_getCommunicationMode            DL_UART_getCommunicationMode
/*! Redirects to @ref DL_UART_setFlowControl */
#define DL_UART_Main_setFlowControl                  DL_UART_setFlowControl
/*! Redirects to @ref DL_UART_getFlowControl */
#define DL_UART_Main_getFlowControl                  DL_UART_getFlowControl
/*! Redirects to @ref DL_UART_setRTSOutput */
#define DL_UART_Main_setRTSOutput                    DL_UART_setRTSOutput
/*! Redirects to @ref DL_UART_enableFIFOs */
#define DL_UART_Main_enableFIFOs                     DL_UART_enableFIFOs
/*! Redirects to @ref DL_UART_disableFIFOs */
#define DL_UART_Main_disableFIFOs                    DL_UART_disableFIFOs
/*! Redirects to @ref DL_UART_isFIFOsEnabled */
#define DL_UART_Main_isFIFOsEnabled                  DL_UART_isFIFOsEnabled
/*! Redirects to @ref DL_UART_isParityEnabled */
#define DL_UART_Main_isParityEnabled                 DL_UART_isParityEnabled
/*! Redirects to @ref DL_UART_setParityMode */
#define DL_UART_Main_setParityMode                   DL_UART_setParityMode
/*! Redirects to @ref DL_UART_getParityMode */
#define DL_UART_Main_getParityMode                   DL_UART_getParityMode
/*! Redirects to @ref DL_UART_setStopBits */
#define DL_UART_Main_setStopBits                     DL_UART_setStopBits
/*! Redirects to @ref DL_UART_getStopBits */
#define DL_UART_Main_getStopBits                     DL_UART_getStopBits
/*! Redirects to @ref DL_UART_setWordLength */
#define DL_UART_Main_setWordLength                   DL_UART_setWordLength
/*! Redirects to @ref DL_UART_getWordLength */
#define DL_UART_Main_getWordLength                   DL_UART_getWordLength
/*! Redirects to @ref DL_UART_enableSendIdlePattern */
#define DL_UART_Main_enableSendIdlePattern           DL_UART_enableSendIdlePattern
/*! Redirects to @ref DL_UART_disableSendIdlePattern */
#define DL_UART_Main_disableSendIdlePattern          DL_UART_disableSendIdlePattern
/*! Redirects to @ref DL_UART_isSendIdlePatternEnabled */
#define DL_UART_Main_isSendIdlePatternEnabled        DL_UART_isSendIdlePatternEnabled
/*! Redirects to @ref DL_UART_setExternalDriverSetup */
#define DL_UART_Main_setExternalDriverSetup          DL_UART_setExternalDriverSetup
/*! Redirects to @ref DL_UART_getExternalDriverSetup */
#define DL_UART_Main_getExternalDriverSetup          DL_UART_getExternalDriverSetup
/*! Redirects to @ref DL_UART_setExternalDriverHold */
#define DL_UART_Main_setExternalDriverHold           DL_UART_setExternalDriverHold
/*! Redirects to @ref DL_UART_getExternalDriverHold */
#define DL_UART_Main_getExternalDriverHold           DL_UART_getExternalDriverHold
/*! Redirects to @ref DL_UART_isBusy */
#define DL_UART_Main_isBusy                          DL_UART_isBusy
/*! Redirects to @ref DL_UART_isRXFIFOEmpty */
#define DL_UART_Main_isRXFIFOEmpty                   DL_UART_isRXFIFOEmpty
/*! Redirects to @ref DL_UART_isRXFIFOFull */
#define DL_UART_Main_isRXFIFOFull                    DL_UART_isRXFIFOFull
/*! Redirects to @ref DL_UART_isTXFIFOEmpty */
#define DL_UART_Main_isTXFIFOEmpty                   DL_UART_isTXFIFOEmpty
/*! Redirects to @ref DL_UART_isTXFIFOFull */
#define DL_UART_Main_isTXFIFOFull                    DL_UART_isTXFIFOFull
/*! Redirects to @ref DL_UART_isClearToSend */
#define DL_UART_Main_isClearToSend                   DL_UART_isClearToSend
/*! Redirects to @ref DL_UART_isIdleModeDetected */
#define DL_UART_Main_isIdleModeDetected              DL_UART_isIdleModeDetected
/*! Redirects to @ref DL_UART_setTXFIFOThreshold */
#define DL_UART_Main_setTXFIFOThreshold              DL_UART_setTXFIFOThreshold
/*! Redirects to @ref DL_UART_getTXFIFOThreshold */
#define DL_UART_Main_getTXFIFOThreshold              DL_UART_getTXFIFOThreshold
/*! Redirects to @ref DL_UART_setRXFIFOThreshold */
#define DL_UART_Main_setRXFIFOThreshold              DL_UART_setRXFIFOThreshold
/*! Redirects to @ref DL_UART_getRXFIFOThreshold */
#define DL_UART_Main_getRXFIFOThreshold              DL_UART_getRXFIFOThreshold
/*! Redirects to @ref DL_UART_setRXInterruptTimeout */
#define DL_UART_Main_setRXInterruptTimeout           DL_UART_setRXInterruptTimeout
/*! Redirects to @ref DL_UART_getRXInterruptTimeout */
#define DL_UART_Main_getRXInterruptTimeout           DL_UART_getRXInterruptTimeout
/*! Redirects to @ref DL_UART_getIntegerBaudRateDivisor */
#define DL_UART_Main_getIntegerBaudRateDivisor       DL_UART_getIntegerBaudRateDivisor
/*! Redirects to @ref DL_UART_getFractionalBaudRateDivisor */
#define DL_UART_Main_getFractionalBaudRateDivisor    DL_UART_getFractionalBaudRateDivisor
/*! Redirects to @ref DL_UART_setBaudRateDivisor */
#define DL_UART_Main_setBaudRateDivisor              DL_UART_setBaudRateDivisor
/*! Redirects to @ref DL_UART_transmitData */
#define DL_UART_Main_transmitData                    DL_UART_transmitData
/*! Redirects to @ref DL_UART_receiveData */
#define DL_UART_Main_receiveData                     DL_UART_receiveData
/*! Redirects to @ref DL_UART_getErrorStatus */
#define DL_UART_Main_getErrorStatus                  DL_UART_getErrorStatus
/*! Redirects to @ref DL_UART_enableInterrupt */
#define DL_UART_Main_enableInterrupt                 DL_UART_enableInterrupt
/*! Redirects to @ref DL_UART_disableInterrupt */
#define DL_UART_Main_disableInterrupt                DL_UART_disableInterrupt
/*! Redirects to @ref DL_UART_getEnabledInterrupts */
#define DL_UART_Main_getEnabledInterrupts            DL_UART_getEnabledInterrupts
/*! Redirects to @ref DL_UART_getEnabledInterruptStatus */
#define DL_UART_Main_getEnabledInterruptStatus       DL_UART_getEnabledInterruptStatus
/*! Redirects to @ref DL_UART_getRawInterruptStatus */
#define DL_UART_Main_getRawInterruptStatus           DL_UART_getRawInterruptStatus
/*! Redirects to @ref DL_UART_getPendingInterrupt */
#define DL_UART_Main_getPendingInterrupt             DL_UART_getPendingInterrupt
/*! Redirects to @ref DL_UART_clearInterruptStatus */
#define DL_UART_Main_clearInterruptStatus            DL_UART_clearInterruptStatus
/*! Redirects to @ref DL_UART_changeConfig */
#define DL_UART_Main_changeConfig                    DL_UART_changeConfig
/*! Redirects to @ref DL_UART_transmitDataBlocking */
#define DL_UART_Main_transmitDataBlocking            DL_UART_transmitDataBlocking
/*! Redirects to @ref DL_UART_receiveDataBlocking */
#define DL_UART_Main_receiveDataBlocking             DL_UART_receiveDataBlocking
/*! Redirects to @ref DL_UART_transmitDataCheck */
#define DL_UART_Main_transmitDataCheck               DL_UART_transmitDataCheck
/*! Redirects to @ref DL_UART_receiveDataCheck */
#define DL_UART_Main_receiveDataCheck                DL_UART_receiveDataCheck
/*! Redirects to @ref DL_UART_drainRXFIFO */
#define DL_UART_Main_drainRXFIFO                     DL_UART_drainRXFIFO
/*! Redirects to @ref DL_UART_fillTXFIFO */
#define DL_UART_Main_fillTXFIFO                      DL_UART_fillTXFIFO
/*! Redirects to @ref DL_UART_enableDMAReceiveEvent */
#define DL_UART_Main_enableDMAReceiveEvent           DL_UART_enableDMAReceiveEvent
/*! Redirects to @ref DL_UART_enableDMATransmitEvent */
#define DL_UART_Main_enableDMATransmitEvent          DL_UART_enableDMATransmitEvent
/*! Redirects to @ref DL_UART_disableDMAReceiveEvent */
#define DL_UART_Main_disableDMAReceiveEvent          DL_UART_disableDMAReceiveEvent
/*! Redirects to @ref DL_UART_disableDMATransmitEvent */
#define DL_UART_Main_disableDMATransmitEvent         DL_UART_disableDMATransmitEvent
/*! Redirects to @ref DL_UART_getEnabledDMAReceiveEvent */
#define DL_UART_Main_getEnabledDMAReceiveEvent       DL_UART_getEnabledDMAReceiveEvent
/*! Redirects to @ref DL_UART_getEnabledDMATransmitEvent */
#define DL_UART_Main_getEnabledDMATransmitEvent      DL_UART_getEnabledDMATransmitEvent
/*! Redirects to @ref DL_UART_getEnabledDMAReceiveEventStatus */
#define DL_UART_Main_getEnabledDMAReceiveEventStatus DL_UART_getEnabledDMAReceiveEventStatus
/*! Redirects to @ref DL_UART_getEnabledDMATransmitEventStatus */
#define DL_UART_Main_getEnabledDMATransmitEventStatu DL_UART_getEnabledDMATransmitEventStatus
/*! Redirects to @ref DL_UART_getRawDMAReceiveEventStatus */
#define DL_UART_Main_getRawDMAReceiveEventStatus     DL_UART_getRawDMAReceiveEventStatus
/*! Redirects to @ref DL_UART_getRawDMATransmitEventStatus */
#define DL_UART_Main_getRawDMATransmitEventStatus    DL_UART_getRawDMATransmitEventStatus
/** @}*/

/** @name DL_UART_INTERRUPT
 *  @anchor DL_UART_INTERRUPT
 *  @{
 */
/*!
 * @brief DMA done on transmit interrupt
 */
#define DL_UART_INTERRUPT_DMA_DONE_TX (UNICOMMUART_CPU_INT_IMASK_DMA_DONE_TX_SET)

/*!
 * @brief DMA done on receive interrupt
 */
#define DL_UART_INTERRUPT_DMA_DONE_RX (UNICOMMUART_CPU_INT_IMASK_DMA_DONE_RX_SET)

/*!
 * @brief Clear to send interrupt
 */
#define DL_UART_INTERRUPT_CTS_DONE (UNICOMMUART_CPU_INT_IMASK_CTS_SET)

/*!
 * @brief 9-bit mode address match interrupt
 */
#define DL_UART_INTERRUPT_ADDRESS_MATCH (UNICOMMUART_CPU_INT_IMASK_ADDR_MATCH_SET)

/*!
 * @brief LINC0 match interrupt
 */
#define DL_UART_INTERRUPT_LINC0_MATCH (UNICOMMUART_CPU_INT_IMASK_LINC0_SET)

/*!
 * @brief End of transmission interrupt
 */
#define DL_UART_INTERRUPT_EOT_DONE (UNICOMMUART_CPU_INT_IMASK_EOT_SET)

/*!
 * @brief UART transmit interrupt
 */
#define DL_UART_INTERRUPT_TX (UNICOMMUART_CPU_INT_IMASK_TXINT_SET)

/*!
 * @brief UART receive interrupt
 */
#define DL_UART_INTERRUPT_RX (UNICOMMUART_CPU_INT_IMASK_RXINT_SET)

/*!
 * @brief UART Line Time Out interrupt
 */
#define DL_UART_INTERRUPT_LTOUT (UNICOMMUART_CPU_INT_IMASK_LTOUT_SET)

/*!
 * @brief LIN hardware counter overflow interrupt
 */
#define DL_UART_INTERRUPT_LIN_COUNTER_OVERFLOW (UNICOMMUART_CPU_INT_IMASK_LINOVF_SET)

/*!
 * @brief LIN rising edge LINC1 interrupt
 */
#define DL_UART_INTERRUPT_LIN_RISING_EDGE (UNICOMMUART_CPU_INT_IMASK_LINC1_SET)

/*!
 * @brief LIN falling edge LINC0 interrupt
 */
#define DL_UART_INTERRUPT_LIN_FALLING_EDGE (UNICOMMUART_CPU_INT_IMASK_LINC0_SET)

/*!
 * @brief Positive Edge on UNICOMMUARTxRXD interrupt
 */
#define DL_UART_INTERRUPT_RXD_POS_EDGE (UNICOMMUART_CPU_INT_IMASK_RXPE_SET)

/*!
 * @brief Negative Edge on UNICOMMUARTxRXD interrupt
 */
#define DL_UART_INTERRUPT_RXD_NEG_EDGE (UNICOMMUART_CPU_INT_IMASK_RXNE_SET)

/*!
 * @brief Overrun error interrupt
 */
#define DL_UART_INTERRUPT_OVERRUN_ERROR (UNICOMMUART_CPU_INT_IMASK_OVRERR_SET)

/*!
 * @brief Break error interrupt
 */
#define DL_UART_INTERRUPT_BREAK_ERROR (UNICOMMUART_CPU_INT_IMASK_BRKERR_SET)

/*!
 * @brief Parity error interrupt
 */
#define DL_UART_INTERRUPT_PARITY_ERROR (UNICOMMUART_CPU_INT_IMASK_PARERR_SET)

/*!
 * @brief Framing error interrupt
 */
#define DL_UART_INTERRUPT_FRAMING_ERROR (UNICOMMUART_CPU_INT_IMASK_FRMERR_SET)

/*!
 * @brief Receive timeout interrupt
 */
#define DL_UART_INTERRUPT_RX_TIMEOUT_ERROR (UNICOMMUART_CPU_INT_IMASK_RTOUT_SET)

/*!
 * @brief Noise error interrupt
 */
#define DL_UART_INTERRUPT_NOISE_ERROR (UNICOMMUART_CPU_INT_IMASK_NERR_SET)

/** @}*/

/*! @brief DL_UART_IIDX */
typedef enum
{
    /*! UART interrupt index for DMA done on transmit */
    DL_UART_IIDX_DMA_DONE_TX          = UNICOMMUART_IIDX_STAT_DMA_DONE_TX,
    /*! UART interrupt index for DMA done on receive */
    DL_UART_IIDX_DMA_DONE_RX          = UNICOMMUART_IIDX_STAT_DMA_DONE_RX,
    /*! Interrupt index for UART receive pre-emptive interrupt */
    DL_UART_IIDX_PREEMPT_INT_TX       = UNICOMMUART_IIDX_STAT_DMA_PREIRQ_TX,
    /*! Interrupt index for UART receive pre-emptive interrupt */
    DL_UART_IIDX_PREEMPT_INT_RX       = UNICOMMUART_IIDX_STAT_DMA_PREIRQ_RX,
    /*! UART interrupt index for clear to send */
    DL_UART_IIDX_CTS_DONE             = UNICOMMUART_IIDX_STAT_CTS,
    /*! UART interrupt index for end of transmission */
    DL_UART_IIDX_EOT_DONE             = UNICOMMUART_IIDX_STAT_EOT,
    /*! UART interrupt index for UART transmit */
    DL_UART_IIDX_TX                   = UNICOMMUART_IIDX_STAT_TXIFG,
    /*! UART interrupt index for UART receive */
    DL_UART_IIDX_RX                   = UNICOMMUART_IIDX_STAT_RXIFG,
    /*! UART interrupt index for Line Time Out */
    DL_UART_IIDX_LTOUT                = UNICOMMUART_IIDX_STAT_LTFG,
    /*! UART interrupt index for LIN hardware counter overflow */
    DL_UART_IIDX_LIN_COUNTER_OVERFLOW = UNICOMMUART_IIDX_STAT_LINOVF,
    /*! UART interrupt index for LIN rising edge LINC1 */
    DL_UART_IIDX_LIN_RISING_EDGE      = UNICOMMUART_IIDX_STAT_LINC1,
    /*! UART interrupt index for LIN falling edge LINC0 */
    DL_UART_IIDX_LIN_FALLING_EDGE     = UNICOMMUART_IIDX_STAT_LINC0,
    /*! UART interrupt index for positive edge on UNICOMMUARTxRXD */
    DL_UART_IIDX_RXD_POS_EDGE         = UNICOMMUART_IIDX_STAT_RXPE,
    /*! UART interrupt index for negative edge on UNICOMMUARTxRXD */
    DL_UART_IIDX_RXD_NEG_EDGE         = UNICOMMUART_IIDX_STAT_RXNE,
    /*! UART interrupt index for overrun error */
    DL_UART_IIDX_OVERRUN_ERROR        = UNICOMMUART_IIDX_STAT_OEFG,
    /*! UART interrupt index for break error */
    DL_UART_IIDX_BREAK_ERROR          = UNICOMMUART_IIDX_STAT_BEFG,
    /*! UART interrupt index for parity error */
    DL_UART_IIDX_PARITY_ERROR         = UNICOMMUART_IIDX_STAT_PEFG,
    /*! UART interrupt index for framing error */
    DL_UART_IIDX_FRAMING_ERROR        = UNICOMMUART_IIDX_STAT_FEFG,
    /*! UART interrupt index for receive timeout */
    DL_UART_IIDX_RX_TIMEOUT_ERROR     = UNICOMMUART_IIDX_STAT_RTFG,
    /*! UART interrupt index for noise error */
    DL_UART_IIDX_NOISE_ERROR          = UNICOMMUART_IIDX_STAT_NERR_EVT,
    /*! UART interrupt index for no interrupt */
    DL_UART_IIDX_NO_INTERRUPT         = UNICOMMUART_IIDX_STAT_NO_INTR
} DL_UART_IIDX;

/** @name DL_UART_DMA_INTERRUPT_RX
 *  @anchor DL_UART_DMA_INTERRUPT_RX
 *  @{
 */
/*!
 * @brief UART interrupt for enabling UART receive as DMA trigger
 */
#define DL_UART_DMA_INTERRUPT_RX (UNICOMMUART_DMA_TRIG_RX_IMASK_RXINT_SET)

/*!
 * @brief UART interrupt for enabling UART receive timeout as DMA trigger
 */
#define DL_UART_DMA_INTERRUPT_RX_TIMEOUT (UNICOMMUART_DMA_TRIG_RX_IMASK_RTOUT_SET)

/** @}*/

/*!
 * @brief UART interrupt for enabling UART transmit as DMA trigger
 */
#define DL_UART_DMA_INTERRUPT_TX (UNICOMMUART_DMA_TRIG_TX_IMASK_TXINT_SET)

/** @name DL_UART_ERROR
 *  @anchor DL_UART_ERROR
 *  @{
 */
/*!
 * @brief Overrun error ocurred
 */
#define DL_UART_ERROR_OVERRUN (UNICOMMUART_RXDATA_OVRERR_SET)

/*!
 * @brief Break error ocurred
 */
#define DL_UART_ERROR_BREAK (UNICOMMUART_RXDATA_BRKERR_SET)

/*!
 * @brief Parity error ocurred
 */
#define DL_UART_ERROR_PARITY (UNICOMMUART_RXDATA_PARERR_SET)

/*!
 * @brief Framing error ocurred
 */
#define DL_UART_ERROR_FRAMING (UNICOMMUART_RXDATA_FRMERR_SET)

/** @}*/

/*! @brief UART Oversampling Rate values */
typedef enum
{
    /*! 16x */
    DL_UART_OVERSAMPLING_RATE_16X = UNICOMMUART_CTL0_HSE_OVS16,
    /*! 8x */
    DL_UART_OVERSAMPLING_RATE_8X  = UNICOMMUART_CTL0_HSE_OVS8,
    /*! 3x.
     * IrDA, Manchester and DALI are not supported when 3x oversampling is
     * enabled. */
    DL_UART_OVERSAMPLING_RATE_3X  = UNICOMMUART_CTL0_HSE_OVS3
} DL_UART_OVERSAMPLING_RATE;

/*! @brief Different Parity generation options */
typedef enum
{
    /*! Even parity.
     * Checks for an even number of 1s
     */
    DL_UART_PARITY_EVEN       = (UNICOMMUART_LCRH_PEN_ENABLE | UNICOMMUART_LCRH_EPS_EVEN),
    /*! Odd parity.
     * Checks for an odd number of 1s
     */
    DL_UART_PARITY_ODD        = (UNICOMMUART_LCRH_PEN_ENABLE | UNICOMMUART_LCRH_EPS_ODD),
    /*! Stick parity with a parity bit of '1'.
     * When enabled, a permanent '1' is set as parity when transmitting and
     * checked as '1' when receiving data. */
    DL_UART_PARITY_STICK_ONE  = (UNICOMMUART_LCRH_PEN_ENABLE | UNICOMMUART_LCRH_SPS_ENABLE | UNICOMMUART_LCRH_EPS_ODD),
    /*! Stick parity with a parity bit of '0'.
     * When enabled, a permanent '0' is set as parity when transmitting and
     * checked as '0' when receiving data. */
    DL_UART_PARITY_STICK_ZERO = (UNICOMMUART_LCRH_PEN_ENABLE | UNICOMMUART_LCRH_SPS_ENABLE | UNICOMMUART_LCRH_EPS_EVEN),
    /*! Disable parity checking and generation */
    DL_UART_PARITY_NONE       = UNICOMMUART_LCRH_PEN_DISABLE
} DL_UART_PARITY;

/*! @brief UART Word length in Bits */
typedef enum
{
    /*! 5 bits */
    DL_UART_WORD_LENGTH_5_BITS = UNICOMMUART_LCRH_WLEN_DATABIT5,
    /*! 6 bits */
    DL_UART_WORD_LENGTH_6_BITS = UNICOMMUART_LCRH_WLEN_DATABIT6,
    /*! 7 bits */
    DL_UART_WORD_LENGTH_7_BITS = UNICOMMUART_LCRH_WLEN_DATABIT7,
    /*! 8 bits */
    DL_UART_WORD_LENGTH_8_BITS = UNICOMMUART_LCRH_WLEN_DATABIT8
} DL_UART_WORD_LENGTH;

/*! @brief UART Operation Mode */
typedef enum
{
    /*! Normal operation */
    DL_UART_MODE_NORMAL     = UNICOMMUART_CTL0_MODE_UART,
    /*! RS485 mode */
    DL_UART_MODE_RS485      = UNICOMMUART_CTL0_MODE_RS485,
    /*! Idle Line mode */
    DL_UART_MODE_IDLE_LINE  = UNICOMMUART_CTL0_MODE_IDLELINE,
    /*! 9 Bit Address mode */
    DL_UART_MODE_ADDR_9_BIT = UNICOMMUART_CTL0_MODE_ADDR9BIT,
    /*! ISO7816 Smart Card Support mode */
    DL_UART_MODE_SMART_CARD = UNICOMMUART_CTL0_MODE_SMART,
    /*! DALI mode */
    DL_UART_MODE_DALI       = UNICOMMUART_CTL0_MODE_DALI
} DL_UART_MODE;

/*! @brief UART Transfer Direction */
typedef enum
{
    /*! Transmitter */
    DL_UART_DIRECTION_TX    = UNICOMMUART_CTL0_TXE_ENABLE,
    /*! Receiver */
    DL_UART_DIRECTION_RX    = UNICOMMUART_CTL0_RXE_ENABLE,
    /*! Transmitter and Receiver */
    DL_UART_DIRECTION_TX_RX = (UNICOMMUART_CTL0_RXE_ENABLE | UNICOMMUART_CTL0_TXE_ENABLE),
    /*! Disable Transmitter and Receiver */
    DL_UART_DIRECTION_NONE  = (UNICOMMUART_CTL0_RXE_DISABLE | UNICOMMUART_CTL0_TXE_DISABLE)
} DL_UART_DIRECTION;

/*! @brief Clock Sources supported by UART */
typedef enum
{
    /*! BUSCLK */
    DL_UART_CLOCK_BUSCLK = UNICOMMUART_CLKSEL_BUSCLK_SEL_ENABLE,
} DL_UART_CLOCK;

/*! @brief Different flow control options */
typedef enum
{
    /*! Request to send */
    DL_UART_FLOW_CONTROL_RTS     = UNICOMMUART_CTL0_RTSEN_ENABLE,
    /*! Clear to send */
    DL_UART_FLOW_CONTROL_CTS     = UNICOMMUART_CTL0_CTSEN_ENABLE,
    /*! Request to send and Clear to send */
    DL_UART_FLOW_CONTROL_RTS_CTS = (UNICOMMUART_CTL0_RTSEN_ENABLE | UNICOMMUART_CTL0_CTSEN_ENABLE),
    /*! Disable flow control */
    DL_UART_FLOW_CONTROL_NONE    = (UNICOMMUART_CTL0_CTSEN_DISABLE | UNICOMMUART_CTL0_RTSEN_DISABLE)
} DL_UART_FLOW_CONTROL;

/*! @brief DL_UART_RTS */
typedef enum
{
    /*! RTS is asserted indicating data in RX FIFO is below threshold */
    DL_UART_RTS_ASSERT   = UNICOMMUART_CTL0_RTS_SET,
    /*! RTS is deasserted indicating data in RX FIFO is at or above threshold */
    DL_UART_RTS_DEASSERT = UNICOMMUART_CTL0_RTS_CLR
} DL_UART_RTS;

/*! @brief Number of stop bits transmitted at end of frame */
typedef enum
{
    /*! One stop bit */
    DL_UART_STOP_BITS_ONE = UNICOMMUART_LCRH_STP2_DISABLE,
    /*! Two stop bits */
    DL_UART_STOP_BITS_TWO = UNICOMMUART_LCRH_STP2_ENABLE
} DL_UART_STOP_BITS;

/*! @brief DL_UART_TXD_OUT */
typedef enum
{
    /*! TXD pin is low */
    DL_UART_TXD_OUT_LOW  = UNICOMMUART_CTL0_TXD_OUT_LOW,
    /*! TXD pin is high */
    DL_UART_TXD_OUT_HIGH = UNICOMMUART_CTL0_TXD_OUT_HIGH
} DL_UART_TXD_OUT;

/*! @brief Different FIFO Levels at which TX interrupt can be triggered */
typedef enum
{
    /*! FIFO <= 3/4 empty */
    DL_UART_TX_FIFO_LEVEL_3_4_EMPTY    = UNICOMMUART_IFLS_TXIFLSEL_LVL_3_4,
    /*! FIFO <= 1/2 empty */
    DL_UART_TX_FIFO_LEVEL_1_2_EMPTY    = UNICOMMUART_IFLS_TXIFLSEL_LVL_1_2,
    /*! FIFO <= 1/4 empty */
    DL_UART_TX_FIFO_LEVEL_1_4_EMPTY    = UNICOMMUART_IFLS_TXIFLSEL_LVL_1_4,
    /*! FIFO is not full */
    DL_UART_TX_FIFO_LEVEL_NOT_FULL     = UNICOMMUART_IFLS_TXIFLSEL_LVL_NOT_FULL,
    /*! FIFO is empty */
    DL_UART_TX_FIFO_LEVEL_EMPTY        = UNICOMMUART_IFLS_TXIFLSEL_LVL_EMPTY,
    /*! FIFO is almost empty (FIFO <= 1) */
    DL_UART_TX_FIFO_LEVEL_ALMOST_EMPTY = UNICOMMUART_IFLS_TXIFLSEL_LVL_ALMOST_EMPTY,
    /*! FIFO is almost full (FIFO >= (MAX_FIFO_LEN - 1)) */
    DL_UART_TX_FIFO_LEVEL_ALMOST_FULL  = UNICOMMUART_IFLS_TXIFLSEL_LVL_ALMOST_FULL
} DL_UART_TX_FIFO_LEVEL;

/*! @brief Different FIFO Levels at which RX interrupt can be triggered */
typedef enum
{
    /*! FIFO >= 1/4 full */
    DL_UART_RX_FIFO_LEVEL_1_4_FULL     = UNICOMMUART_IFLS_RXIFLSEL_LVL_1_4,
    /*! FIFO >= 1/2 full */
    DL_UART_RX_FIFO_LEVEL_1_2_FULL     = UNICOMMUART_IFLS_RXIFLSEL_LVL_1_2,
    /*! FIFO >= 3/4 full */
    DL_UART_RX_FIFO_LEVEL_3_4_FULL     = UNICOMMUART_IFLS_RXIFLSEL_LVL_3_4,
    /*! FIFO is not empty */
    DL_UART_RX_FIFO_LEVEL_NOT_EMPTY    = UNICOMMUART_IFLS_RXIFLSEL_LVL_NOT_EMPTY,
    /*! FIFO is full */
    DL_UART_RX_FIFO_LEVEL_FULL         = UNICOMMUART_IFLS_RXIFLSEL_LVL_FULL,
    /*! FIFO is almost full (FIFO >= (MAX_FIFO_LEN - 1)) */
    DL_UART_RX_FIFO_LEVEL_ALMOST_FULL  = UNICOMMUART_IFLS_RXIFLSEL_LVL_ALMOST_FULL,
    /*! FIFO is almost empty (FIFO <= 1) */
    DL_UART_RX_FIFO_LEVEL_ALMOST_EMPTY = UNICOMMUART_IFLS_RXIFLSEL_LVL_ALMOST_EMPTY
} DL_UART_RX_FIFO_LEVEL;

/*!
 * @brief Sets the IrDA pulse width to 3/16 bit period when using the BITCLK16
 */
#define DL_UART_PULSE_WIDTH_3_16_BIT_PERIOD ((uint32_t)0x00000000U)

/*! @brief Divider value used on UART Clock SOurce */
typedef enum
{
    /*! Divide Ratio 1 */
    DL_UART_CLOCK_DIVIDE_RATIO_1 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_1,
    /*! Divide Ratio 2 */
    DL_UART_CLOCK_DIVIDE_RATIO_2 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_2,
    /*! Divide Ratio 3 */
    DL_UART_CLOCK_DIVIDE_RATIO_3 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_3,
    /*! Divide Ratio 4 */
    DL_UART_CLOCK_DIVIDE_RATIO_4 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_4,
    /*! Divide Ratio 5 */
    DL_UART_CLOCK_DIVIDE_RATIO_5 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_5,
    /*! Divide Ratio 6 */
    DL_UART_CLOCK_DIVIDE_RATIO_6 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_6,
    /*! Divide Ratio 7 */
    DL_UART_CLOCK_DIVIDE_RATIO_7 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_7,
    /*! Divide Ratio 8 */
    DL_UART_CLOCK_DIVIDE_RATIO_8 = UNICOMMUART_CLKDIV_RATIO_DIV_BY_8
} DL_UART_CLOCK_DIVIDE_RATIO;

/*!
 *  @brief  Configuration struct for @ref DL_UART_init
 */
typedef struct
{
    /*! The communication mode and protocol used. One of @ref DL_UART_MODE */
    DL_UART_MODE mode;

    /*! The communication direction. One of @ref DL_UART_DIRECTION. */
    DL_UART_DIRECTION direction;

    /*! The flow control configuration. One of @ref DL_UART_FLOW_CONTROL */
    DL_UART_FLOW_CONTROL flowControl;

    /*! The parity configuration. One of @ref DL_UART_PARITY */
    DL_UART_PARITY parity;

    /*! The size of the data transfer. One of @ref DL_UART_WORD_LENGTH */
    DL_UART_WORD_LENGTH wordLength;

    /*! One of @ref DL_UART_STOP_BITS  */
    DL_UART_STOP_BITS stopBits;

} DL_UART_Config;

/*!
 *  @brief  Configuration struct for @ref DL_UART_setClockConfig.
 */
typedef struct
{
    /*! Selects uart module clock source @ref DL_UART_CLOCK */
    DL_UART_CLOCK clockSel;

    /*! Selects the divide ratio. One of @ref DL_UART_CLOCK_DIVIDE_RATIO */
    DL_UART_CLOCK_DIVIDE_RATIO divideRatio;

} DL_UART_ClockConfig;

/**
 * @brief Configuration structure to backup UART Extend peripheral state before
 *        going to STOP/STANDBY mode. Used by
 *        @ref DL_UART_saveConfiguration and
 *        @ref DL_UART_restoreConfiguration
 */
typedef struct
{
    /*! Combination of basic UART control configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. See @ref DL_UART_init for how the peripheral control word
     *  is created. */
    uint32_t controlWord;

    /*! UART module clock source. One of  @ref DL_UART_CLOCK */
    uint32_t clockSel;

    /*! UART clock divider. One of @ref DL_UART_CLOCK_DIVIDE_RATIO */
    uint32_t divideRatio;

    /*! Combination of UART Line Control Register configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. See @ref DL_UART_init for how the peripheral control word
     *  is created. */
    uint32_t lineControlRegisterWord;

    /*! Combination of UART interrupt FIFO level select configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     * registers. */
    uint32_t interruptFifoLevelSelectWord;

    /*! UART integer baud rate divisor. Value between 0 - 65535. */
    uint32_t ibrd;

    /*! UART fractional baud rate divisor. Value between 0 - 63. */
    uint32_t fbrd;

    /*! Combination of UART glitch filter configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. */
    uint32_t glitchFilterControlWord;
    /*! UART LIN counter value that is
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. */
    uint32_t linCounterWord;
    /*! Combination of UART LIN basic configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. */
    uint32_t linControlWord;

    /*! Combination of UART IrDA basic configurations that are
     *  compressed to a single word as they are stored in the UNICOMMUART
     *  registers. */
    uint32_t irdaControlWord;

    /*! UART address mask for 9-bit or Idle mode. */
    uint32_t addressMask;

    /*! UART address that should be matched for 9-bit or Idle mode. */
    uint32_t address;

    /*! UART interrupt status for EVENT0.
     * Bitwise OR of @ref DL_UART_INTERRUPT */
    uint32_t interruptMask0;

    /*! UART interrupt status for EVENT1.
     * Bitwise OR of @ref DL_UART_DMA_INTERRUPT_RX */
    uint32_t interruptMask1;

    /*! UART interrupt status for EVENT2.
     * Bitwise OR of @ref DL_UART_DMA_INTERRUPT_TX */
    uint32_t interruptMask2;

    /*! Boolean flag indicating whether or not a valid configuration structure
     *  exists. Should not be modified by the user. */
    bool backupRdy;
} DL_UART_backupConfig;

/**
 *  @brief      Initialize the UART peripheral
 *
 *  Initializes all the common configurable options for the UART peripheral. Any
 *  other custom configuration can be done after calling this API. The UART is
 *  not enabled in this API.
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the peripheral
 *  @param[in]  config  Configuration for UART peripheral
 */
void DL_UART_init(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_Config *config);

/**
 * @brief Enables power on UART module
 *
 * @param unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_enablePower(unicomm);

    if (unicomm->fixedMode == false)
    {
        DL_UNICOMM_setIPMode(unicomm, DL_UNICOMM_UART);
    }
}

/**
 * @brief Disables power on unicomm module
 *
 * @param unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disablePower(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_disablePower(unicomm);
}

/**
 * @brief Returns if  power on unicomm module
 *
 * @param unicomm        Pointer to the register overlay for the peripheral
 *
 * @return true if power is enabled
 * @return false if power is disabled
 */
__STATIC_INLINE bool DL_UART_isPowerEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return DL_UNICOMM_isPowerEnabled(unicomm);
}

/**
 * @brief Resets unicomm peripheral
 *
 * @param unicomm        Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_reset(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UNICOMM_reset(unicomm);
}

/**
 * @brief Returns if unicomm peripheral was reset
 *
 * @param unicomm        Pointer to the register overlay for the peripheral
 *
 * @return true if peripheral was reset
 * @return false if peripheral wasn't reset
 *
 */
__STATIC_INLINE bool DL_UART_isReset(DL_UNICOMM_Inst_Regs *unicomm)
{
    return DL_UNICOMM_isReset(unicomm);
}

/**
 *  @brief      Enable the UART peripheral
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enable(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 |= UNICOMMUART_CTL0_ENABLE_ENABLE;
}

/**
 *  @brief      Checks if the UART peripheral is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the enabled status of the UNICOMMUART
 *
 *  @retval     true  The UART peripheral is enabled
 *  @retval     false The UART peripheral is disabled

 */
__STATIC_INLINE bool DL_UART_isEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->CTL0 & UNICOMMUART_CTL0_ENABLE_MASK) == UNICOMMUART_CTL0_ENABLE_ENABLE);
}

/**
 *  @brief      Disable the UART peripheral
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disable(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 &= ~(UNICOMMUART_CTL0_ENABLE_MASK);
}

/**
 *  @brief      Configure UART source clock
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  config  Pointer to the clock configuration struct
 *                       @ref DL_UART_ClockConfig.
 */
void DL_UART_setClockConfig(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_ClockConfig *config);

/**
 *  @brief      Get UART source clock configuration
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the
 *                      peripheral
 *  @param[in]  config  Pointer to the clock configuration struct
 *                      @ref DL_UART_ClockConfig.
 */
void DL_UART_getClockConfig(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_ClockConfig *config);

/**
 *  @brief      Configure the baud rate
 *
 *  Given the target baud rate and the frequency of the UART clock source, this
 *  API determines and sets the recommended oversampling setting, and then
 *  calculates and sets the required baud rate divisors.
 *
 * The oversampling rate that will be set is the highest possible oversampling
 * rate given the target baud rate and UART clock frequency.
 *
 * If the user wishes to avoid having the CPU calculate the baud rate divisors
 * or not use the recommended calculated values, the user can call
 * @ref DL_UART_setOversampling and @ref DL_UART_setBaudRateDivisor directly.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  clockFreq  The clock frequency in Hz of the UART clock source
 *  @param[in]  baudRate   The target baud rate
 *
 * @sa          DL_UART_setOversampling
 * @sa          DL_UART_setBaudRateDivisor
 */
void DL_UART_configBaudRate(DL_UNICOMM_Inst_Regs *unicomm, uint32_t clockFreq, uint32_t baudRate);

/**
 *  @brief      Set the oversampling rate
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  rate  The oversampling rate to use.
 *                    One of @ref DL_UART_OVERSAMPLING_RATE
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_setOversampling(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_OVERSAMPLING_RATE rate)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, (uint32_t)rate, UNICOMMUART_CTL0_HSE_MASK);
}

/**
 *  @brief      Get the oversampling rate
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The current oversampling rate
 *
 *  @retval     One of @ref DL_UART_OVERSAMPLING_RATE
 *
 */
__STATIC_INLINE DL_UART_OVERSAMPLING_RATE DL_UART_getOversampling(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t rate = unicomm->uart->CTL0 & UNICOMMUART_CTL0_HSE_MASK;

    return (DL_UART_OVERSAMPLING_RATE)(rate);
}

/**
 *  @brief      Enable loopback mode
 *
 *  Enables the loopback mode. When enabled, the UNICOMMUARTxTXD path is fed through
 *  the UNICOMMUARTxRXD path.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_enableLoopbackMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 |= UNICOMMUART_CTL0_LBE_ENABLE;
}

/**
 *  @brief      Check if loopback mode is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of loopback mode
 *
 *  @retval     true  Loopback mode is enabled
 *  @retval     false Loopback mode is disabled
 */
__STATIC_INLINE bool DL_UART_isLoopbackModeEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->CTL0 & UNICOMMUART_CTL0_LBE_MASK) == UNICOMMUART_CTL0_LBE_ENABLE);
}

/**
 *  @brief      Disable loopback mode
 *
 *  Disables the loopback mode. When disabled, the UNICOMMUARTxTXD path is not fed through
 *  the UNICOMMUARTxRXD path.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_disableLoopbackMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 &= ~(UNICOMMUART_CTL0_LBE_MASK);
}

/**
 *  @brief      Set the direction of the UART communication
 *
 *  If the UART is disabled in the middle of a transmit or receive, it
 *  completes the current character before stopping.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  direction  Direction to set UART communication to.
 *                         One of @ref DL_UART_DIRECTION.
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 *
 */
__STATIC_INLINE void DL_UART_setDirection(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_DIRECTION direction)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, (uint32_t)direction,
                        UNICOMMUART_CTL0_TXE_MASK | UNICOMMUART_CTL0_RXE_MASK);
}

/**
 *  @brief      Get the direction of the UART communication
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The direction of UART communication.
 *
 *  @retval     One of @ref DL_UART_DIRECTION
 */
__STATIC_INLINE DL_UART_DIRECTION DL_UART_getDirection(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t direction = unicomm->uart->CTL0 & (UNICOMMUART_CTL0_TXE_MASK | UNICOMMUART_CTL0_RXE_MASK);

    return (DL_UART_DIRECTION)(direction);
}

/**
 *  @brief      Enable majority voting control
 *
 *  When enabled, the three center bits are used to determine received sample
 *  value. The value corresponding to at least two of the three samples is
 *  considered to be the received value.In case of error (i.e. all 3 bits are
 *  not the same), noise error is detected and bits RIS.NERR and register
 *  RXDATA.NERR are set.
 *
 *  When enabled with oversampling of 16, samples 7, 8, and 9 are
 *  majority voted to decide the sampled bit value.
 *
 *  When enabled with oversampling of 8, samples 3, 4, and 5 are majority
 *  voted to decide the sampled bit value. The value corresponding to at least 2
 *  of the 3 samples is considered to be the received value.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 *
 *  @sa          DL_UART_setOversampling
 */
__STATIC_INLINE void DL_UART_enableMajorityVoting(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 |= UNICOMMUART_CTL0_MAJVOTE_ENABLE;
}

/**
 *  @brief      Check if majority voting is enabled
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     The status of majority control feature
 *
 *  @retval     true  Majority voting is enabled
 *  @retval     false Majority voting is disabled
 */
__STATIC_INLINE bool DL_UART_isMajorityVotingEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->CTL0 & UNICOMMUART_CTL0_MAJVOTE_MASK) == UNICOMMUART_CTL0_MAJVOTE_ENABLE);
}

/**
 *  @brief      Disable majority voting control
 *
 *  When disabled, only a single sample of the received bit of is taken.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_disableMajorityVoting(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 &= ~(UNICOMMUART_CTL0_MAJVOTE_MASK);
}

/**
 *  @brief      Enable most significant bit (MSB) first
 *
 *  When enabled, the most significant bit (MSB) is sent first in the protocol
 *  packet. This bit has effect on both the way the protocol byte is
 *  transmitted and received.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_enableMSBFirst(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 |= UNICOMMUART_CTL0_MSBFIRST_ENABLE;
}

/**
 *  @brief      Check if most significant bit (MSB) first is enabled
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     The status of majority control feature
 *
 *  @retval     true  MSB first is enabled
 *  @retval     false MSB first is disabled
 */
__STATIC_INLINE bool DL_UART_isMSBFirstEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->CTL0 & UNICOMMUART_CTL0_MSBFIRST_MASK) == UNICOMMUART_CTL0_MSBFIRST_ENABLE);
}

/**
 *  @brief      Disable most significant bit (MSB) first
 *
 *  When disabled, the least significant bit (LSB) is sent first in the protocol
 *  packet. This bit has effect on both the way the protocol byte is
 *  transmitted and received.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_disableMSBFirst(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 &= ~(UNICOMMUART_CTL0_MSBFIRST_MASK);
}

/**
 *  @brief      Enable control of the TXD pin
 *
 *  When enabled, the TXD pin can be controlled by the TXD_OUT bit. The UNICOMMUART
 *  transmit section must first be disabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 *
 *  @sa          DL_UART_setDirection
 *  @sa          DL_UART_setTXDPin
 */
__STATIC_INLINE void DL_UART_enableTransmitPinManualControl(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 |= UNICOMMUART_CTL0_TXD_OUT_EN_ENABLE;
}

/**
 *  @brief      Check if control of the TXD pin is enabled
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     The status of control of the TXD pin
 *
 *  @retval     true  Control of the TXD pin is enabled
 *  @retval     false Control of the TXD pin is disabled
 */
__STATIC_INLINE bool DL_UART_isTransmitPinManualControlEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->CTL0 & UNICOMMUART_CTL0_TXD_OUT_EN_MASK) == UNICOMMUART_CTL0_TXD_OUT_EN_ENABLE);
}

/**
 *  @brief      Disable control of the TXD pin
 *
 *  When disabled, the TXD pin can not be controlled by the TXD_OUT bit
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_disableTransmitPinManualControl(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->CTL0 &= ~(UNICOMMUART_CTL0_TXD_OUT_EN_MASK);
}

/**
 *  @brief      Set the output of the TXD pin
 *
 *  Control the output transmit data pin only when TXD_OUT_EN is enabled and
 *  TXE is disabled.
 *
 *  The TXD pin is set to manual control if it hadn't been
 *  previously set.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  txdOutVal  Value to set the TXD pin output to.
 *                         One of @ref DL_UART_TXD_OUT
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 *
 *  @sa          DL_UART_disableTransmitPinManualControl
 *  @sa          DL_UART_enableTransmitPinManualControl
 */
__STATIC_INLINE void DL_UART_setTransmitPinManualOutput(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_TXD_OUT txdOutVal)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, UNICOMMUART_CTL0_TXD_OUT_EN_ENABLE | (uint32_t)txdOutVal,
                        UNICOMMUART_CTL0_TXD_OUT_EN_MASK | UNICOMMUART_CTL0_TXD_OUT_MASK);
}

/**
 *  @brief      Get the output value of the TXD pin
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The value of the TXD pin
 *
 *  @retval     One of @ref DL_UART_TXD_OUT
 */
__STATIC_INLINE DL_UART_TXD_OUT DL_UART_getTransmitPinManualOutput(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t txdOutVal = unicomm->uart->CTL0 & UNICOMMUART_CTL0_TXD_OUT_MASK;

    return (DL_UART_TXD_OUT)(txdOutVal);
}

/**
 *  @brief      Set the communication mode/protocol to use
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  mode  Value to set the UART communication protocol to.
 *                     One of @ref DL_UART_MODE
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_setCommunicationMode(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_MODE mode)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, (uint32_t)mode, UNICOMMUART_CTL0_MODE_MASK);
}

/**
 *  @brief      Get the communication mode/protocol being used
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The communication mode/protocol being used by the UNICOMMUART
 *
 *  @retval     One of @ref DL_UART_MODE
 */
__STATIC_INLINE DL_UART_MODE DL_UART_getCommunicationMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t mode = unicomm->uart->CTL0 & UNICOMMUART_CTL0_MODE_MASK;

    return (DL_UART_MODE)(mode);
}

/**
 *  @brief      Set the flow control configuration
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the peripheral
 *  @param[in]  config  The flow control configuration to use.
 *                      One of @ref DL_UART_FLOW_CONTROL.
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 */
__STATIC_INLINE void DL_UART_setFlowControl(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_FLOW_CONTROL config)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, (uint32_t)config,
                        UNICOMMUART_CTL0_RTSEN_MASK | UNICOMMUART_CTL0_CTSEN_MASK);
}

/**
 *  @brief      Check the flow control configuration
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the
 *                    peripheral
 *
 *  @return     The flow control configuration
 *
 *  @retval     One of @ref DL_UART_FLOW_CONTROL values
 */
__STATIC_INLINE DL_UART_FLOW_CONTROL DL_UART_getFlowControl(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t config = unicomm->uart->CTL0 & (UNICOMMUART_CTL0_RTSEN_MASK | UNICOMMUART_CTL0_CTSEN_MASK);

    return (DL_UART_FLOW_CONTROL)(config);
}

/**
 *  @brief      Set the request to send output signal
 *
 *  The RTS output signal indicates the state of the RX FIFO, and is
 *  linked to the programmable receive FIFO threshold levels. When RTS flow
 *  control is enabled, the RTS signal is asserted (low) when the data in the
 *  RX FIFO is less than the threshold level. When the RX FIFO threshold level
 *  is reached, the RTS signal is deasserted (high). The RTS signal is
 *  reasserted (low) when data has been read out  of the RX FIFO so it is less
 *  than the threshold.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  val   The RTS output signal. One of @ref DL_UART_RTS
 *
 *  @pre  If the UART has already been enabled, then it must be made ready for
 *        configuration by first calling @ref DL_UART_changeConfig
 *  @post If @ref DL_UART_changeConfig was called, then the UART must be
 *        re-enabled by calling @ref DL_UART_enable
 *
 *  @sa         DL_UART_setTXFIFOThreshold
 */
__STATIC_INLINE void DL_UART_setRTSOutput(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_RTS val)
{
    DL_Common_updateReg(&unicomm->uart->CTL0, (uint32_t)val, UNICOMMUART_CTL0_RTS_MASK);
}

/**
 *  @brief      Get the request to send output signal
 *
 *  The RTS output signal indicates the state of the RX FIFO, and is
 *  linked to the programmable receive FIFO threshold levels. When RTS flow
 *  control is enabled, the RTS signal is asserted (low) when the data in the
 *  RX FIFO is less than the threshold level. When the RX FIFO threshold level
 *  is reached, the RTS signal is deasserted (high). The RTS signal is
 *  reasserted (low) when data has been read out  of the RX FIFO so it is less
 *  than the threshold.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The RTS signal status
 *
 *  @retval     One of @ref DL_UART_RTS
 *
 *  @sa         DL_UART_setTXFIFOThreshold
 */
__STATIC_INLINE DL_UART_RTS DL_UART_getRTSOutput(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t val = unicomm->uart->CTL0 & UNICOMMUART_CTL0_RTS_MASK;

    return (DL_UART_RTS)(val);
}

/**
 *  @brief      Enable FIFOs
 *
 *  @deprecated UNICOMM FIFOs are always eanbled. This API is provided for backwards compatiblity ONLY.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableFIFOs(DL_UNICOMM_Inst_Regs *unicomm)
{
    return;
}

/**
 *  @brief      Disable FIFOs
 *
 *  @deprecated UNICOMM FIFOs are always eanbled. This API is provided for backwards compatiblity ONLY.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableFIFOs(DL_UNICOMM_Inst_Regs *unicomm)
{
    return;
}

/**
 *  @brief      Check if FIFOs are enabled
 *
 *  @deprecated UNICOMM FIFOs are always eanbled. This API is provided for backwards compatiblity ONLY.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Always returns true
 */
__STATIC_INLINE bool DL_UART_isFIFOsEnabled(const DL_UNICOMM_Inst_Regs *unicomm)
{
    return true;
}

/**
 *  @brief      Enable send break (for LIN protocol)
 *
 *  When enabled, a low level is continually output on the TXD signal after completing
 *  transmission of the current character. For the proper execution of the
 *  break command, software must set this bit for at least two frames (character periods).
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableLINSendBreak(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LCRH |= UNICOMMUART_LCRH_BRK_ENABLE;
}

/**
 *  @brief      Disable send break
 *
 *  When disabled, a low level is not continually output on the TXD signal
 *  after completing transmission of the current character.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINSendBreak(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LCRH &= ~(UNICOMMUART_LCRH_BRK_MASK);
}

/**
 *  @brief      Check if send break is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of send break
 *
 *  @retval     true  Send break is enabled
 *  @retval     false Send break is disabled
 */
__STATIC_INLINE bool DL_UART_isLINSendBreakEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LCRH & UNICOMMUART_LCRH_BRK_MASK) == UNICOMMUART_LCRH_BRK_ENABLE);
}

/**
 *  @brief      Check if parity is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of parity
 *
 *  @retval     true  Parity is enabled
 *  @retval     false Parity is disabled
 */
__STATIC_INLINE bool DL_UART_isParityEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LCRH & UNICOMMUART_LCRH_PEN_MASK) == UNICOMMUART_LCRH_PEN_ENABLE);
}

/**
 *  @brief      Set the parity mode
 *
 *  For 9-bit UART mode transmissions, the parity mode affects the address
 *  byte and data byte indication (9th bit). If DL_UART_PARITY_EVEN or
 *  DL_UART_PARITY_STICK_ZERO is enabled, then the transferred byte is a data
 *  byte.  If DL_UART_PARITY_EVEN or DL_UART_PARITY_STICK_ZERO is not enabled,
 *  then the transferred byte is an address byte.
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the peripheral
 *  @param[in]  parity  Parity mode to set UART to.
 *                      One of @ref DL_UART_PARITY
 */
__STATIC_INLINE void DL_UART_setParityMode(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_PARITY parity)
{
    DL_Common_updateReg(&unicomm->uart->LCRH, (uint32_t)parity,
                        (UNICOMMUART_LCRH_PEN_MASK | UNICOMMUART_LCRH_EPS_MASK | UNICOMMUART_LCRH_SPS_MASK));
}

/**
 *  @brief      Get parity mode
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The current parity mode being used
 *
 *  @retval     One of @ref DL_UART_PARITY
 *
 */
__STATIC_INLINE DL_UART_PARITY DL_UART_getParityMode(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t parity =
        unicomm->uart->LCRH & (UNICOMMUART_LCRH_PEN_MASK | UNICOMMUART_LCRH_EPS_MASK | UNICOMMUART_LCRH_SPS_MASK);

    return (DL_UART_PARITY)(parity);
}

/**
 *  @brief      Set the number of stop bits
 *
 *  When in 7816 smart code mode (DL_UART_MODE_SMART_CARD mode), the number of
 *  stop bits is forced to 2
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *  @param[in]  numStopBits  The number of stop bits transmitted.
 *                           One of @ref DL_UART_STOP_BITS
 */
__STATIC_INLINE void DL_UART_setStopBits(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_STOP_BITS numStopBits)
{
    DL_Common_updateReg(&unicomm->uart->LCRH, (uint32_t)numStopBits, UNICOMMUART_LCRH_STP2_MASK);
}

/**
 *  @brief      Get the number of stop bits
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The number of stop bits transmitted.
 *
 *  @retval     One of @ref DL_UART_STOP_BITS
 */
__STATIC_INLINE DL_UART_STOP_BITS DL_UART_getStopBits(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t numStopBits = unicomm->uart->LCRH & UNICOMMUART_LCRH_STP2_MASK;

    return (DL_UART_STOP_BITS)(numStopBits);
}

/**
 *  @brief      Set the word length
 *
 *  @param[in]  unicomm        Pointer to the register overlay for the peripheral
 *  @param[in]  wordLength  The number of data bits transmitted or received in
 *                           a frame. One of @ref DL_UART_WORD_LENGTH
 */
__STATIC_INLINE void DL_UART_setWordLength(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_WORD_LENGTH wordLength)
{
    DL_Common_updateReg(&unicomm->uart->LCRH, (uint32_t)wordLength, UNICOMMUART_LCRH_WLEN_MASK);
}

/**
 *  @brief      Get the word length
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The length of the data bits transmitted or received in a frame
 *
 *  @retval     One of @ref DL_UART_WORD_LENGTH
 */
__STATIC_INLINE DL_UART_WORD_LENGTH DL_UART_getWordLength(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t wordLength = unicomm->uart->LCRH & UNICOMMUART_LCRH_WLEN_MASK;

    return (DL_UART_WORD_LENGTH)(wordLength);
}

/**
 *  @brief      Send idle pattern
 *
 *  When enabled, a SENDIDLE period of 11 bit times will be sent on the TX
 *  line. The bit is cleared by hardware afterwards.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableSendIdlePattern(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LCRH |= UNICOMMUART_LCRH_SENDIDLE_ENABLE;
}

/**
 *  @brief      Disable send idle pattern
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableSendIdlePattern(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LCRH &= ~(UNICOMMUART_LCRH_SENDIDLE_MASK);
}

/**
 *  @brief      Check if send idle pattern is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of the send idle pattern
 *
 *  @retval     true  Send idle pattern is enabled
 *  @retval     false Send idle pattern is disabled
 */
__STATIC_INLINE bool DL_UART_isSendIdlePatternEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LCRH & UNICOMMUART_LCRH_SENDIDLE_MASK) == UNICOMMUART_LCRH_SENDIDLE_ENABLE);
}

/**
 *  @brief      Set external driver setup value
 *
 *  Defines the number of UNICOMMUARTclk ticks the signal to control the external
 *  driver for the RS485 will be set before the START bit is sent
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  val   The number of UNICOMMUARTclk ticks the signal before the RS485
 *                    is setup. Value between 0 - 31.
 */
__STATIC_INLINE void DL_UART_setExternalDriverSetup(DL_UNICOMM_Inst_Regs *unicomm, uint32_t val)
{
    DL_Common_updateReg(&unicomm->uart->LCRH, val << UNICOMMUART_LCRH_EXTDIR_SETUP_OFS,
                        UNICOMMUART_LCRH_EXTDIR_SETUP_MASK);
}

/**
 *  @brief      Get the external driver setup value
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return    The number of UNICOMMUARTclk ticks the signal to control the
 *             external driver
 *
 *  @retval     0 - 31 The number of UNICOMMUARTclk ticks
 */
__STATIC_INLINE uint32_t DL_UART_getExternalDriverSetup(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LCRH & UNICOMMUART_LCRH_EXTDIR_SETUP_MASK >> UNICOMMUART_LCRH_EXTDIR_SETUP_OFS));
}

/**
 *  @brief      Set external driver setup hold
 *
 *  Defines the number of UNICOMMUARTclk ticks the signal to control the external
 *  driver for the RS485 will be reset after the beginning of the stop bit.
 *  If 2 STOP bits are enabled, the RS485 will be reset at the beginning of
 *  the 2nd STOP bit.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  val   The number of UNICOMMUARTclk ticks the signal to hold the
 *                    external driver before the RS485 will be reset.
 *                    Value between 0 - 31.
 */
__STATIC_INLINE void DL_UART_setExternalDriverHold(DL_UNICOMM_Inst_Regs *unicomm, uint32_t val)
{
    DL_Common_updateReg(&unicomm->uart->LCRH, val << UNICOMMUART_LCRH_EXTDIR_HOLD_OFS,
                        UNICOMMUART_LCRH_EXTDIR_HOLD_MASK);
}

/**
 *  @brief      Get the external driver setup hold
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *
 *  @return     The number of UNICOMMUARTclk ticks the signal to hold the
 *              external driver before the RS485 will be reset
 *
 *  @retval     0 - 31 The number of UNICOMMUARTclk ticks
 */
__STATIC_INLINE uint32_t DL_UART_getExternalDriverHold(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LCRH & UNICOMMUART_LCRH_EXTDIR_HOLD_MASK >> UNICOMMUART_LCRH_EXTDIR_HOLD_OFS));
}

/**
 *  @brief      Checks if the UART is busy
 *
 *  This bit is set as soon as the transmit FIFO or TXDATA register becomes
 *  non-empty (regardless of whether UART is enabled) or if a receive data is
 *  currently ongoing (after the start edge have been detected until a complete
 *  byte, including all stop bits, has been received by the shift register).
 *
 *  In IDLE Line mode the Busy signal also stays set during the idle time
 *  generation.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of the UART Busy bit
 *
 *  @retval     true   The UART is busy
 *  @retval     false  The UART is not busy
 *
 */
__STATIC_INLINE bool DL_UART_isBusy(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_BUSY_MASK) == UNICOMMUART_STAT_BUSY_SET);
}

/**
 *  @brief      Checks if the RX FIFO is empty
 *
 *  The meaning of this bit depends on if the FIFOs were enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the empty status of the RX FIFO
 *
 *  @retval     true   If the FIFO is enabled, the receive FIFO is empty.
 *                     If the FIFO is disabled, the receiver has no data.
 *  @retval     false  The receiver is not empty
 */
__STATIC_INLINE bool DL_UART_isRXFIFOEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_RXFE_MASK) == UNICOMMUART_STAT_RXFE_SET);
}

/**
 *  @brief      Checks if the RX FIFO is full
 *
 *  The meaning of this bit depends on if the FIFOs were enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the full status of the RX FIFO
 *
 *  @retval     true   If the FIFO is enabled, the receive FIFO is full.
 *                     If the FIFO is disabled, the receiver has 1-byte
 *                     of data.
 *  @retval     false  The receiver is not full
 */
__STATIC_INLINE bool DL_UART_isRXFIFOFull(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_RXFF_MASK) == UNICOMMUART_STAT_RXFF_SET);
}

/**
 *  @brief      Checks if the TX FIFO is empty
 *
 *  The meaning of this bit depends on if the FIFOs were enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the empty status of the TX FIFO
 *
 *  @retval     true   If the FIFO is enabled, the transmit FIFO is empty.
 *                     If the FIFO is disabled, the transmitter has no data.
 *  @retval     false  The transmitter is not empty
 */
__STATIC_INLINE bool DL_UART_isTXFIFOEmpty(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_TXFE_MASK) == UNICOMMUART_STAT_TXFE_SET);
}

/**
 *  @brief      Checks if the TX FIFO is full
 *
 *  The meaning of this bit depends on if the FIFOs were enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the full status of the TX FIFO
 *
 *  @retval     true   If the FIFO is enabled, the transmit FIFO is full.
 *                     If the FIFO is disabled, the transmitter has 1-byte
 *                     of data.
 *  @retval     false  The transmitter is not full
 */
__STATIC_INLINE bool DL_UART_isTXFIFOFull(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_TXFF_MASK) == UNICOMMUART_STAT_TXFF_SET);
}

/**
 *  @brief      Checks if UART is clear to send
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the status of the CTS signal
 *
 *  @retval     true   The CTS signal is asserted (low)
 *  @retval     false  The CTS signal is not asserted (high)
 *
 *  @sa         DL_UART_isClearToSendEnabled
 */
__STATIC_INLINE bool DL_UART_isClearToSend(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_CTS_MASK) == UNICOMMUART_STAT_CTS_SET);
}

/**
 *  @brief      Checks if Idle mode has been detected
 *
 *  Idle mode has been detected in Idleline-Multiprocessor-Mode. The IDLE bit
 *  is used as an address tag for each block of characters. In idle-line
 *  multiprocessor format, this bit is set when a received character is an
 *  address.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     Returns the status if Idle mode has been detected
 *
 *  @retval     true  Idle has been detected before last received character
 *  @retval     false Idle has not been detected before last received character
 *
 */
__STATIC_INLINE bool DL_UART_isIdleModeDetected(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->STAT & UNICOMMUART_STAT_IDLE_MASK) == UNICOMMUART_STAT_IDLE_SET);
}

/**
 *  @brief      Set the TX FIFO interrupt threshold level
 *
 *  Select the threshold for the transmit FIFO interrupt. The interrupts are
 *  generated based on a transition through a level rather than being based on
 *  the level. That is, the interrupts are generated when the fill level
 *  progresses through the trigger level. For example, if the transmit trigger
 *  level is set to the half-way mark, the interrupt is triggered when the
 *  transmit FIFO becomes half empty. In other words, if the transmit FIFO was
 *  filled with four characters, the interrupt would trigger once there are
 *  two or less characters after transmitting.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  threshold  One of @ref DL_UART_TX_FIFO_LEVEL
 *
 */
__STATIC_INLINE void DL_UART_setTXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_TX_FIFO_LEVEL threshold)
{
    DL_Common_updateReg(&unicomm->uart->IFLS, (uint32_t)threshold, UNICOMMUART_IFLS_TXIFLSEL_MASK);
}

/**
 *  @brief      Get the TX FIFO interrupt threshold level
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The TX FIFO interrupt threshold level
 *
 *  @retval     One of @ref DL_UART_TX_FIFO_LEVEL
 */
__STATIC_INLINE DL_UART_TX_FIFO_LEVEL DL_UART_getTXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t threshold = unicomm->uart->IFLS & UNICOMMUART_IFLS_TXIFLSEL_MASK;

    return (DL_UART_TX_FIFO_LEVEL)(threshold);
}

/**
 *  @brief      Set the RX FIFO interrupt threshold level. The interrupts are
 *  generated based on a transition through a level rather than being based on
 *  the level. That is, the interrupts are generated when the fill level
 *  progresses through the trigger level. For example, if the receive trigger
 *  level is set to the half-way mark, the interrupt is triggered when the
 *  receive FIFO becomes half full. In other words, the interrupt is triggered
 *  after the receive FIFO is filled with two or more characters.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  threshold  One of @ref DL_UART_RX_FIFO_LEVEL
 */
__STATIC_INLINE void DL_UART_setRXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_RX_FIFO_LEVEL threshold)
{
    DL_Common_updateReg(&unicomm->uart->IFLS, (uint32_t)threshold, UNICOMMUART_IFLS_RXIFLSEL_MASK);
}

/**
 *  @brief      Get the RX FIFO interrupt threshold level
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The RX FIFO interrupt threshold level
 *
 *  @retval     One of @ref DL_UART_RX_FIFO_LEVEL
 */
__STATIC_INLINE DL_UART_RX_FIFO_LEVEL DL_UART_getRXFIFOThreshold(DL_UNICOMM_Inst_Regs *unicomm)
{
    uint32_t threshold = unicomm->uart->IFLS & UNICOMMUART_IFLS_RXIFLSEL_MASK;

    return (DL_UART_RX_FIFO_LEVEL)(threshold);
}

/**
 *  @brief      Set the RX interrupt timeout
 *
 *  When an additional character has not been received within the set
 *  timeout, a RX interrupt will still trigger even if the FIFO level has not
 *  been reached. A value of 0 disables this function.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  timeout  Timeout to set the RX interrupt to.
 *                       Value between 0 - 15
 */
__STATIC_INLINE void DL_UART_setRXInterruptTimeout(DL_UNICOMM_Inst_Regs *unicomm, uint32_t timeout)
{
    DL_Common_updateReg(&unicomm->uart->IFLS, timeout << UNICOMMUART_IFLS_RXTOSEL_OFS, UNICOMMUART_IFLS_RXTOSEL_MASK);
}

/**
 *  @brief      Get the RX interrupt timeout
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The RX interrupt timeout value
 *
 *  @retval     0 - 15  The RX interrupt timeout value
 *
 */
__STATIC_INLINE uint32_t DL_UART_getRXInterruptTimeout(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->IFLS & UNICOMMUART_IFLS_RXTOSEL_MASK) >> UNICOMMUART_IFLS_RXTOSEL_OFS);
}

/**
 *  @brief      Get Integer Baud-Rate Divisor
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The integer component of the baud rate divisor
 *
 *  @retval     0 - 65535 The integer baud date divisor
 */
__STATIC_INLINE uint32_t DL_UART_getIntegerBaudRateDivisor(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->IBRD & UNICOMMUART_IBRD_DIVINT_MASK);
}

/**
 *  @brief      Get Fractional Baud-Rate Divisor
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The fractional component of the baud rate divisor
 *
 *  @retval     0 - 63  The fractional baud date divisor
 */
__STATIC_INLINE uint32_t DL_UART_getFractionalBaudRateDivisor(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->FBRD & UNICOMMUART_FBRD_DIVFRAC_MASK);
}

/**
 *  @brief      Set the baud rate divisor
 *
 *  Set the integer baud rate divisor and fractional baud rate divisor
 *  components of the baud rate divisor
 *
 *  @param[in]  unicomm               Pointer to the register overlay for the
 *                                 peripheral
 *  @param[in]  integerDivisor     The integer component of the baud rate
 *                                 divisor
 *  @param[in]  fractionalDivisor  The fractional component of the baud rate
 *                                 divisor
 */
__STATIC_INLINE void DL_UART_setBaudRateDivisor(DL_UNICOMM_Inst_Regs *unicomm, uint32_t integerDivisor,
                                                uint32_t fractionalDivisor)
{
    DL_Common_updateReg(&unicomm->uart->IBRD, integerDivisor, UNICOMMUART_IBRD_DIVINT_MASK);
    DL_Common_updateReg(&unicomm->uart->FBRD, fractionalDivisor, UNICOMMUART_FBRD_DIVFRAC_MASK);

    // When updating the baud-rate divisor (UNICOMMUARTIBRD or UNICOMMUARTIFRD),
    // the LCRH register must also be written to (any bit in LCRH can
    // be written to for updating the baud-rate divisor).
    DL_Common_updateReg(&unicomm->uart->LCRH, (unicomm->uart->LCRH & UNICOMMUART_LCRH_BRK_MASK),
                        UNICOMMUART_LCRH_BRK_MASK);
}

/**
 *  @brief      Set the pulse width select for the digital glitch suppresion
 *
 *  Controls the pulse width select for glitch suppression on the RX line.
 *  The glitch suppression values are in terms of functional clocks.
 *
 *  In IrDA mode, this sets the receive filter length. The minimum pulse
 *  length for receive is given by: t(MIN) = (DGFSEL) / f(IRTXCLK)
 *
 *  @param[in]  unicomm        Pointer to the register overlay for the peripheral
 *  @param[in]  pulseWidth  Pulse width select for the glitch suppresion.
 *                          Value between 0 - 63.
 */
__STATIC_INLINE void DL_UART_setDigitalPulseWidth(DL_UNICOMM_Inst_Regs *unicomm, uint32_t pulseWidth)
{
    DL_Common_updateReg(&unicomm->uart->GFCTL, pulseWidth, UNICOMMUART_GFCTL_DGFSEL_MASK);
}

/**
 *  @brief      Get the pulse width select for the digital glitch suppresion
 *
 *  Gets the pulse width select for glitch suppression on the RX line.
 *  The glitch suppression values are in terms of functional clocks.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The digital glitch suppression pulse width
 *
 *  @retval     0 indicating digital glitch suppression is disabled
 *  @retval     1 - 63 the digital glitch suppression pulse width
 */
__STATIC_INLINE uint32_t DL_UART_getDigitalPulseWidth(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->GFCTL & UNICOMMUART_GFCTL_DGFSEL_MASK);
}

/**
 *  @brief      Writes data into the TX FIFO to transmit
 *
 *  Puts the data into the TX FIFO without checking it's status. Use if already
 *  sure the TX FIFO has space for the write. See related APIs for additional
 *  transmit options.
 *
 *  For transmitted data, if the FIFO is enabled, data written to this
 *  location is pushed onto the transmit FIFO. If the FIFO is disabled,
 *  data is stored in the 1-byte deep transmitter.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *  @param[in]  data  The data to transmit
 *
 *
 *  @sa         DL_UART_transmitDataBlocking
 *  @sa         DL_UART_transmitDataCheck
 */
__STATIC_INLINE void DL_UART_transmitData(DL_UNICOMM_Inst_Regs *unicomm, uint8_t data)
{
    unicomm->uart->TXDATA = data;
}

/**
 *  @brief      Reads data from the RX FIFO
 *
 *  Reads the data from the RX FIFO without checking its status. Use if
 *  already sure the RX FIFO has data available. See related APIs for
 *  additional receive options.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The data in the RX FIFO
 *
 *  @sa         DL_UART_receiveDataBlocking
 *  @sa         DL_UART_receiveDataCheck
 */
__STATIC_INLINE uint8_t DL_UART_receiveData(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint8_t)(unicomm->uart->RXDATA & UNICOMMUART_RXDATA_DATA_MASK));
}

/**
 *  @brief      Gets the status of the error flags of the received data
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the peripheral
 *  @param[in]  errorMask  Bit mask of error flags to check. Bitwise OR of
 *                         @ref DL_UART_ERROR.
 *
 *  @return     The status of the requested UART error flags
 *
 *  @retval     Bitwise OR of @ref DL_UART_ERROR values
 */
__STATIC_INLINE uint32_t DL_UART_getErrorStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t errorMask)
{
    return (unicomm->uart->RXDATA & errorMask);
}

/**
 *  @brief      Set the LIN counter value
 *
 *  The LIN counter is a 16 bit up counter clocked by the functional clock of
 *  the UNICOMMUART
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *  @param[in]  value  Pulse width select for the glitch suppresion.
 */
__STATIC_INLINE void DL_UART_setLINCounterValue(DL_UNICOMM_Inst_Regs *unicomm, uint16_t value)
{
    DL_Common_updateReg(&unicomm->uart->LINCNT, value, UNICOMMUART_LINCNT_VALUE_MASK);
}

/**
 *  @brief      Get the LIN counter value
 *
 *  The LIN counter is a 16 bit up counter clocked by the module clock of
 *  the UNICOMMUART
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The clock counter value
 *
 *  @retval     0 - 65535  The clock counter value
 *
 */
__STATIC_INLINE uint16_t DL_UART_getLINCounterValue(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint16_t)(unicomm->uart->LINCNT & UNICOMMUART_LINCNT_VALUE_MASK));
}

/**
 *  @brief      Enable the LIN counter
 *
 *  The LIN counter will only count when enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableLINCounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL |= UNICOMMUART_LINCTL_CTRENA_ENABLE;
}

/**
 *  @brief      Check if the LIN counter is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of the LIN counter
 *
 *  @retval     true   LIN counter is enabled
 *  @retval     false  LIN counter is disabled
 */
__STATIC_INLINE bool DL_UART_isLINCounterEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_CTRENA_MASK) == UNICOMMUART_LINCTL_CTRENA_ENABLE);
}

/**
 *  @brief      Disable the LIN counter
 *
 *  LIN counter will only count when enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINCounter(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_CTRENA_MASK);
}

/**
 *  @brief   Enable LIN counter clear and start counting on falling edge of RXD
 *
 *  When enabled, the counter is set to 0 and starts counting on the LIN counter
 *  on a falling edge of RXD.
 *
 *  The LIN counter will only count when it is enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @sa  DL_UART_enableLINCounter
 */
__STATIC_INLINE void DL_UART_enableLINCounterClearOnFallingEdge(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL |= UNICOMMUART_LINCTL_ZERONE_ENABLE;
}

/**
 *  @brief      Check if LIN counting on falling edge of RXD is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of counting on falling edge of RXD
 *
 *  @retval     true   Counting on falling edge is enabled
 *  @retval     false  Counting on falling edge is disabled
 */
__STATIC_INLINE bool DL_UART_isLINCounterClearOnFallingEdge(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_ZERONE_MASK) == UNICOMMUART_LINCTL_ZERONE_ENABLE);
}

/**
 *  @brief      Disable LIN counting on falling edge of RXD
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINCounterClearOnFallingEdge(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_ZERONE_MASK);
}

/**
 *  @brief      Enable LIN counter incrementing while RXD signal is low
 *
 *  When LIN counter is enabled and the signal on RXD is low, the counter
 *  increments
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @sa  DL_UART_enableLINCounter
 */
__STATIC_INLINE void DL_UART_enableLINCountWhileLow(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL |= UNICOMMUART_LINCTL_CNTRXLOW_ENABLE;
}

/**
 *  @brief   Check if LIN counter increments while RXD signal is low is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of counter increments while RXD signal is low
 *
 *  @retval     true   Counter increments while RXD signal is low is enabled
 *  @retval     false  Counter increments while RXD signal is low is disabled
 */
__STATIC_INLINE bool DL_UART_isLINCountWhileLowEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_CNTRXLOW_MASK) == UNICOMMUART_LINCTL_CNTRXLOW_ENABLE);
}

/**
 *  @brief      Disable LIN counter increments while RXD signal is low
 *
 *  LIN counter will not increment while the RXD signal is low
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINCountWhileLow(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_CNTRXLOW_MASK);
}

/**
 *  @brief      Enable capture of the LIN counter on a falling edge
 *
 *  When enabled, the LIN counter value is captured to the LINC0 register on
 *  each falling RXD edge. A LINC0 interrupt is triggered when enabled.
 *  Disables counter compare match mode if enabled.
 *
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @sa  DL_UART_configLINMode
 */
__STATIC_INLINE void DL_UART_enableLINFallingEdgeCapture(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_Common_updateReg(&unicomm->uart->LINCTL,
                        UNICOMMUART_LINCTL_LINC0CAP_ENABLE | UNICOMMUART_LINCTL_LINC0_MATCH_DISABLE,
                        UNICOMMUART_LINCTL_LINC0CAP_MASK | UNICOMMUART_LINCTL_LINC0_MATCH_MASK);
}

/**
 *  @brief      Check status of capture of LIN counter on a falling edge
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of capture the LIN counter on a falling edge
 *
 *  @retval     true   Capture to LINC0 on falling RXD edge is enabled
 *  @retval     false  Capture to LINC0 on falling RXD edge is disabled
 */
__STATIC_INLINE bool DL_UART_isLINFallingEdgeCaptureEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_LINC0CAP_MASK) == UNICOMMUART_LINCTL_LINC0CAP_ENABLE);
}

/**
 *  @brief      Disable capture of LIN counter on a falling edge
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINFallingEdgeCapture(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_LINC0CAP_MASK);
}

/**
 *  @brief      Enable capture of the LIN counter on a rising edge
 *
 *  When enabled the LIN counter value is captured to LINC1 register on each
 *  rising RXD edge. A LINC1 interrupt is triggered when enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 */
__STATIC_INLINE void DL_UART_enableLINRisingEdgeCapture(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL |= UNICOMMUART_LINCTL_LINC1CAP_ENABLE;
}

/**
 *  @brief      Check status of capture of LIN counter on a rising edge
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of capture of LIN counter on a rising edge
 *
 *  @retval     true   Capture to LINC1 on rising RXD edge is enabled
 *  @retval     false  Capture to LINC1 on rising RXD edge is disabled
 */
__STATIC_INLINE bool DL_UART_isLINRisingEdgeCaptureEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_LINC1CAP_MASK) == UNICOMMUART_LINCTL_LINC1CAP_ENABLE);
}

/**
 *  @brief      Disable capture of LIN counter on a rising edge
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINRisingEdgeCapture(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_LINC1CAP_MASK);
}

/**
 *  @brief      Enable LIN counter compare match mode
 *
 *  When enabled, a match between a value in LINC0 and the LIN counter can
 *  trigger a LINC0 interrupt. Disables capture on falling edge if enabled.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableLINCounterCompareMatch(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_Common_updateReg(&unicomm->uart->LINCTL,
                        UNICOMMUART_LINCTL_LINC0_MATCH_ENABLE | UNICOMMUART_LINCTL_LINC0CAP_DISABLE,
                        UNICOMMUART_LINCTL_LINC0CAP_MASK | UNICOMMUART_LINCTL_LINC0_MATCH_MASK);
}

/**
 *  @brief      Setup LIN counter control for sync field validation
 *
 *  Enable LIN counter capture on rising RX edge. Enable LIN counter capture on falling RX edge.
 *  Enable LIN counter clearing on RX falling edge. Enable LIN counter.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableLINSyncFieldValidationCounterControl(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_Common_updateReg(&unicomm->uart->LINCTL,
                        UNICOMMUART_LINCTL_LINC0CAP_ENABLE | UNICOMMUART_LINCTL_LINC1CAP_ENABLE |
                            UNICOMMUART_LINCTL_ZERONE_ENABLE | UNICOMMUART_LINCTL_CTRENA_ENABLE,
                        UNICOMMUART_LINCTL_LINC0CAP_MASK | UNICOMMUART_LINCTL_LINC1CAP_MASK |
                            UNICOMMUART_LINCTL_ZERONE_MASK | UNICOMMUART_LINCTL_CTRENA_MASK);
}

/**
 *  @brief      Setup LIN counter control for LIN reception
 *
 * Enable count while low signal on RXD. Enable LIN counter clearing on RXD falling edge.
 * Enable LIN counter.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_enableLINReceptionCountControl(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_Common_updateReg(
        &unicomm->uart->LINCTL,
        UNICOMMUART_LINCTL_CNTRXLOW_ENABLE | UNICOMMUART_LINCTL_ZERONE_ENABLE | UNICOMMUART_LINCTL_CTRENA_ENABLE,
        UNICOMMUART_LINCTL_CNTRXLOW_MASK | UNICOMMUART_LINCTL_ZERONE_MASK | UNICOMMUART_LINCTL_CTRENA_MASK);
}

/**
 *  @brief      Check if LIN counter compare match mode is enabled
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The status of counter compare match mode
 *
 *  @retval     true   LIN counter compare match mode is enabled
 *  @retval     false  LIN counter compare match mode is disabled
 */
__STATIC_INLINE bool DL_UART_isLINCounterCompareMatchEnabled(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((unicomm->uart->LINCTL & UNICOMMUART_LINCTL_LINC0_MATCH_MASK) == UNICOMMUART_LINCTL_LINC0_MATCH_ENABLE);
}

/**
 *  @brief      Disable LIN counter compare match mode
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_disableLINCounterCompareMatch(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->LINCTL &= ~(UNICOMMUART_LINCTL_LINC0_MATCH_MASK);
}

/**
 *  @brief      Set the value to be compared to the LIN counter
 *
 *  Sets the value of LINC0 to be used to compare to the LIN counter. For use
 *  when LIN counter compare match mode is enabled.
 *
 *  @param[in]  unicomm   Pointer to the register overlay for the peripheral
 *  @param[in]  value  Value to be compared to the LIN counter for matching.
 *                     Value between 0 - 65535.
 *
 *  @sa  DL_UART_enableLINCounterCompareMatch
 */
__STATIC_INLINE void DL_UART_setLINCounterCompareValue(DL_UNICOMM_Inst_Regs *unicomm, uint16_t value)
{
    DL_Common_updateReg(&unicomm->uart->LINC0, value, UNICOMMUART_LINC0_DATA_MASK);
}

/**
 *  @brief      Get the LINC0 counter value
 *
 *  Captures current LINCTR value on RXD falling edge.
 *
 *  If capture is enabled with @ref DL_UART_enableLINFallingEdgeCapture, a
 *  capture can generate a LINC0 interrupt.
 *  If compare mode is enabled with @ref DL_UART_enableLINCounterCompareMatch,
 *  a counter match can generate a LINC0 interrupt.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The LINC0 counter value
 *
 *  @retval     0 - 65535  The LINC0 counter value
 *
 *  @sa  DL_UART_enableLINFallingEdgeCapture
 *  @sa  DL_UART_enableLINCounterCompareMatch
 */
__STATIC_INLINE uint16_t DL_UART_getLINFallingEdgeCaptureValue(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint16_t)(unicomm->uart->LINC0 & UNICOMMUART_LINC0_DATA_MASK));
}

/**
 *  @brief      Get the LINC1 counter value
 *
 *  Captures current LINCTR value on RXD rising edge. For use when LIN rising
 *  edge capture is enabled. It can generate a LINC1 interrupt on capture.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The LINC1 counter value
 *
 *  @retval     0 - 65535  The LINC1 counter value
 *
 *  @sa  DL_UART_enableLINRisingEdgeCapture
 */
__STATIC_INLINE uint16_t DL_UART_getLINRisingEdgeCaptureValue(DL_UNICOMM_Inst_Regs *unicomm)
{
    return ((uint16_t)(unicomm->uart->LINC1 & UNICOMMUART_LINC1_DATA_MASK));
}

/**
 *  @brief      Set the address mask for DALI, 9-bit, or Idle-Line mode
 *
 *  The address bits are masked to create a set of addresses to be matched
 *  with the received address byte.
 *
 *  A 0 bit in the MSK bitfield configures that the corresponding bit in the
 *  ADDR bitfield of the ADDR register is don't care.
 *  A 1 bit in the MSK bitfield configures, that the corresponding bit in the
 *  ADDR bitfield of the ADDR register must match.
 *
 *  Used in DALI, UART 9-Bit or Idle-Line mode.
 *
 *  @param[in]  unicomm         Pointer to the register overlay for the peripheral
 *  @param[in]  addressMask  The address mask to set
 */
__STATIC_INLINE void DL_UART_setAddressMask(DL_UNICOMM_Inst_Regs *unicomm, uint32_t addressMask)
{
    DL_Common_updateReg(&unicomm->uart->AMASK, addressMask, UNICOMMUART_AMASK_VALUE_MASK);
}

/**
 *  @brief      Get the address mask being used
 *
 *  The address bits are masked to create a set of addresses to be matched
 *  with the received address byte.
 *
 *  A 0 bit in the MSK bitfield configures that the corresponding bit in the
 *  ADDR bitfield of the ADDR register is don't care.
 *  A 1 bit in the MSK bitfield configures, that the corresponding bit in the
 *  ADDR bitfield of the ADDR register must match.
 *
 *  Used in DALI, UART 9-Bit or Idle-Line mode.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The address mask being used
 *
 *  @retval     0-255  The address mask
 *
 */
__STATIC_INLINE uint32_t DL_UART_getAddressMask(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->AMASK & UNICOMMUART_AMASK_VALUE_MASK);
}

/**
 *  @brief      Set the address
 *
 *  Used to write the specific address that should be matched with the
 *  receiving byte when the Address Mask (AMASK) is set to FFh. This register
 *  is used in conjunction with AMASK to form a match for address-byte
 *  received.
 *
 *  Used in DALI, UART 9-Bit or Idle-Line mode.
 *
 *  @param[in]  unicomm     Pointer to the register overlay for the peripheral
 *  @param[in]  address  The address to set
 */
__STATIC_INLINE void DL_UART_setAddress(DL_UNICOMM_Inst_Regs *unicomm, uint32_t address)
{
    DL_Common_updateReg(&unicomm->uart->ADDR, address, UNICOMMUART_ADDR_VALUE_MASK);
}

/**
 *  @brief      Get the address being used
 *
 *  Used to write the specific address that should be matched with the
 *  receiving byte when the Address Mask (AMASK) is set to FFh. This register
 *  is used in conjunction with AMASK to form a match for address-byte
 *  received.
 *
 *  Used in DALI, UART 9-Bit or Idle-Line mode.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @return     The address being used
 *
 *  @retval     0-255  The address being used
 *
 */
__STATIC_INLINE uint32_t DL_UART_getAddress(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->ADDR & UNICOMMUART_ADDR_VALUE_MASK);
}

/**
 *  @brief      Enable UART interrupts
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to enable. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 */
__STATIC_INLINE void DL_UART_enableInterrupt(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->uart->CPU_INT.IMASK |= interruptMask;
}

/**
 *  @brief      Disable UART interrupts
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to disable. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 */
__STATIC_INLINE void DL_UART_disableInterrupt(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->uart->CPU_INT.IMASK &= ~(interruptMask);
}

/**
 *  @brief      Check which UART interrupts are enabled
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 *
 *  @return     Which of the requested UART interrupts are enabled
 *
 *  @retval     Bitwise OR of @ref DL_UART_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledInterrupts(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->CPU_INT.IMASK & interruptMask);
}

/**
 *  @brief      Check interrupt flag of enabled UART interrupts
 *
 *  Checks if any of the UART interrupts that were previously enabled are
 *  pending.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 *
 *  @return     Which of the requested UART interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_UART_INTERRUPT values
 *
 *  @sa         DL_UART_enableInterrupt
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->CPU_INT.MIS & interruptMask);
}

/**
 *  @brief      Check interrupt flag of any UART interrupt
 *
 *  Checks if any of the UART interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 *
 *  @return     Which of the requested UART interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_UART_INTERRUPT values
 */
__STATIC_INLINE uint32_t DL_UART_getRawInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->CPU_INT.RIS & interruptMask);
}

/**
 *  @brief      Get highest priority pending UART interrupt
 *
 *  Checks if any of the UART interrupts are pending. Interrupts do not have to
 *  be previously enabled.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *
 *  @return     The highest priority pending UART interrupt
 *
 *  @retval     TBD
 */
__STATIC_INLINE DL_UART_IIDX DL_UART_getPendingInterrupt(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (DL_UART_IIDX)(unicomm->uart->CPU_INT.IIDX);
}

/**
 *  @brief      Clear pending UART interrupts
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to clear. Bitwise OR of
 *                             @ref DL_UART_INTERRUPT.
 */
__STATIC_INLINE void DL_UART_clearInterruptStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    unicomm->uart->CPU_INT.ICLR = interruptMask;
}

/**
 *  @brief      Prepares the UART to change the configuration
 *
 *  If the UART has already been enabled, then it is recommended to call this
 *  function before calling other APIs that make changes to the CTL0 register.
 *  If changes are made to the CTL0 register without disabling the UNICOMMUART, then
 *  results are unpredictable. This API performs the following:
 *  1. Disable the UNICOMMUART.
 *  2. Wait for the end of transmission or reception of the current character.
 *  3. Flush the transmit FIFO by clearing bit FEN in the UART control
 *  register CTL0.
 *
 *  @post After calling this API, the user must be re-enabled by calling
 *        @ref DL_UART_enable.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 */
__STATIC_INLINE void DL_UART_changeConfig(DL_UNICOMM_Inst_Regs *unicomm)
{
    DL_UART_disable(unicomm);
    while (DL_UART_isBusy(unicomm))
    {
        ;
    }
}

/**
 *  @brief      Blocks to ensure transmit is ready before sending data
 *
 *  Puts the data into the TX FIFO after blocking to ensure the TX FIFO is not
 *  full. Will wait indefintely until there is space in the TX FIFO. See
 *  related APIs for additional transmit options.
 *
 *  Can be used for any data transfers that are less than or equal to 8 bits.
 *
 *  @param[in]  unicomm  pointer to the register overlay for the peripheral
 *  @param[in]  data  data to send
 *
 *  @sa         DL_UART_transmitData
 *  @sa         DL_UART_transmitDataCheck
 */
void DL_UART_transmitDataBlocking(DL_UNICOMM_Inst_Regs *unicomm, uint8_t data);

/**
 *  @brief      Blocks to ensure receive is ready before reading data
 *
 *  Reads the data from the RX FIFO after blocking to ensure the RX FIFO is not
 *  empty. Will wait indefintely until there is data in the RX FIFO. See
 *  related APIs for additional receive options.
 *
 *  Can be used for any data transfers that are less than or equal to 8 bits.
 *
 *  @param[in]  unicomm  pointer to the register overlay for the peripheral
 *
 *  @return     The data in the RX FIFO
 *
 *  @sa         DL_UART_transmitData
 *  @sa         DL_UART_transmitDataCheck
 */
uint8_t DL_UART_receiveDataBlocking(DL_UNICOMM_Inst_Regs *unicomm);

/**
 *  @brief      Checks the TX FIFO before trying to transmit data
 *
 *  Checks if the TX FIFO is already full before trying to add new data to the
 *  FIFO. Exits immediately if full rather than trying to block. See related
 *  APIs for additional transmit options.
 *
 *  Can be used for any data transfers that are less than or equal to 8 bits.
 *
 *  @param[in]  unicomm  pointer to the register overlay for the peripheral
 *  @param[in]  data  data to send
 *
 *  @return     If the transmit occurred
 *
 *  @retval     true  if data was added to the TX FIFO
 *  @retval     false if the TX FIFO was full and data was not added
 *
 *  @sa         DL_UART_transmitData
 *  @sa         DL_UART_transmitDataBlocking
 */
bool DL_UART_transmitDataCheck(DL_UNICOMM_Inst_Regs *unicomm, uint8_t data);

/**
 *  @brief      Checks the RX FIFO before trying to transmit data
 *
 *  Checks if the RX FIFO is already empty before trying to read new data from
 *  the FIFO. Exits immediately if empty rather than trying to block. See
 *  related APIs for additional receive options.
 *
 *  Can be used for any data transfers that are less than or equal to 8 bits.
 *
 *  @param[in]  unicomm   pointer to the register overlay for the peripheral
 *  @param[in]  buffer a buffer to write the received data into
 *
 *  @return     If the receive occurred
 *
 *  @retval     true  if data was read from the RX FIFO
 *  @retval     false if the RX FIFO was empty and data was not read
 *
 *  @sa         DL_UART_receiveData
 *  @sa         DL_UART_receiveDataBlocking
 */
bool DL_UART_receiveDataCheck(DL_UNICOMM_Inst_Regs *unicomm, uint8_t *buffer);

/**
 *  @brief       Read all available data out of the RX FIFO using 8 bit access
 *
 *  @param[in]   unicomm   Pointer to the register overlay for the peripheral
 *  @param[out]  buffer    Buffer to write received data into
 *  @param[in]   maxCount  Max number of bytes to read from the RX FIFO
 *
 *  @return      Number of bytes read from the RX FIFO
 */
uint32_t DL_UART_drainRXFIFO(DL_UNICOMM_Inst_Regs *unicomm, uint8_t *buffer, uint32_t maxCount);

/**
 *  @brief      Fill the TX FIFO until full using 8 bit access
 *
 *  Continuously write data into the TX FIFO until it is filled up or count has
 *  been reached.
 *
 *  @param[in]  unicomm    Pointer to the register overlay for the peripheral
 *  @param[in]  buffer  Buffer of data to write to the TX FIFO
 *  @param[in]  count   Max number of bytes to write to the TX FIFO
 *
 *  @return     Number of bytes written to the TX FIFO
 */
uint32_t DL_UART_fillTXFIFO(DL_UNICOMM_Inst_Regs *unicomm, uint8_t *buffer, uint32_t count);

/**
 *  @brief      Enable UART interrupt for triggering the DMA receive event
 *
 * Enables the UART interrupt to be used as the condition to generate an
 * event to directly trigger the DMA. This API configures the DMA_TRIG_RX
 * register, which is the event publisher used for triggering the DMA to do
 * a receive data transfer.
 *
 * @note Only one interrupt source should be enabled at a time.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the
 *                         peripheral
 *  @param[in]  interrupt  Interrupt to enable as the trigger condition for
 *                         the DMA. One of @ref DL_UART_DMA_INTERRUPT_RX.
 */
__STATIC_INLINE void DL_UART_enableDMAReceiveEvent(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interrupt)
{
    unicomm->uart->DMA_TRIG_RX.IMASK = interrupt;
}

/**
 *  @brief      Enable UART interrupt for triggering the DMA transmit event
 *
 * Enables the UART interrupt to be used as the condition to generate an
 * event to directly trigger the DMA. This API configures the DMA_TRIG_TX
 * register, which is the event publisher used for triggering the DMA to do
 * a transmit data transfer.
 *
 * @note DMA_TRIG_TX only has one transmit interrupt source
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the
 *                         peripheral
 */
__STATIC_INLINE void DL_UART_enableDMATransmitEvent(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->DMA_TRIG_TX.IMASK = UNICOMMUART_DMA_TRIG_TX_IMASK_TXINT_SET;
}

/**
 *  @brief      Disables UART interrupt from triggering the DMA receive event
 *
 * Disables the UART interrupt as the condition to generate an event to
 * directly trigger the DMA. This API configures the DMA_TRIG_RX
 * register, which is the event publisher used for triggering the DMA to do
 * a receive data transfer.
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the
 *                         peripheral
 *  @param[in]  interrupt  Interrupt to disable as the trigger condition for
 *                         the DMA. One of @ref DL_UART_DMA_INTERRUPT_RX.
 */
__STATIC_INLINE void DL_UART_disableDMAReceiveEvent(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interrupt)
{
    unicomm->uart->DMA_TRIG_RX.IMASK &= ~(interrupt);
}

/**
 *  @brief      Disables UART interrupt from triggering the DMA transmit event
 *
 * Disables the UART interrupt as the condition to generate an event to
 * directly trigger the DMA. This API configures the DMA_TRIG_TX
 * register, which is the event publisher used for triggering the DMA to do
 * a transmit data transfer.
 *
 * @note DMA_TRIG_TX only has one transmit interrupt source
 *
 *  @param[in]  unicomm       Pointer to the register overlay for the
 *                         peripheral
 */
__STATIC_INLINE void DL_UART_disableDMATransmitEvent(DL_UNICOMM_Inst_Regs *unicomm)
{
    unicomm->uart->DMA_TRIG_TX.IMASK = UNICOMMUART_DMA_TRIG_TX_IMASK_TXINT_CLR;
}

/**
 *  @brief      Check which UART interrupt for DMA receive events is enabled
 *
 *  This API checks the DMA_TRIG_RX register, which is the event publisher used
 *  for triggering the DMA to do a receive data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check Bitwise OR of
 *                             @ref DL_UART_DMA_INTERRUPT_RX.
 *
 *  @return     Which of the requested UART interrupts is enabled
 *
 *  @retval     One of @ref DL_UART_DMA_INTERRUPT_RX
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledDMAReceiveEvent(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->DMA_TRIG_RX.IMASK & interruptMask);
}

/**
 *  @brief      Check if UART interrupt for DMA transmit event is enabled
 *
 *  This API checks the DMA_TRIG_TX register, which is the event publisher used
 *  for triggering the DMA to do a transmit data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *
 *  @return     The requested UART interrupt status
 *
 *  @retval     DL_UART_DMA_INTERRUPT_TX if enabled, 0 if not enabled
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledDMATransmitEvent(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->DMA_TRIG_TX.IMASK & UNICOMMUART_DMA_TRIG_TX_IMASK_TXINT_MASK);
}

/**
 *  @brief      Check interrupt flag of enabled UART interrupt for DMA receive event
 *
 * Checks if any of the UART interrupts for the DMA receive event that were
 * previously enabled are pending.
 * This API checks the DMA_TRIG_RX register, which is the event publisher used
 * for triggering the DMA to do a receive data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_UART_DMA_INTERRUPT_RX.
 *
 *  @return     The requested UART interrupt status
 *
 *  @retval     One of @ref DL_UART_DMA_INTERRUPT_RX
 *
 *  @sa         DL_UART_enableDMAReceiveEvent
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledDMAReceiveEventStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->DMA_TRIG_RX.MIS & interruptMask);
}

/**
 *  @brief      Check interrupt flag of enabled UART interrupt for DMA transmit event
 *
 * Checks if the UART interrupt for the DMA transmit event that was
 * previously enabled is pending.
 * This API checks the DMA_TRIG_TX register, which is the event publisher used
 * for triggering the DMA to do a transmit data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *
 *  @return     The requested UART interrupt status
 *
 *  @retval     DL_UART_DMA_INTERRUPT_TX if enabled, 0 if not enabled
 *
 *  @sa         DL_UART_enableDMATransmitEvent
 */
__STATIC_INLINE uint32_t DL_UART_getEnabledDMATransmitEventStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->DMA_TRIG_TX.MIS & UNICOMMUART_DMA_TRIG_TX_MIS_TXINT_MASK);
}

/**
 *  @brief      Check interrupt flag of any UART interrupt for DMA receive event
 *
 *  Checks if any of the UART interrupts for DMA receive event are pending.
 *  Interrupts do not have to be previously enabled.
 *  This API checks the DMA_TRIG_RX register, which is the event publisher used
 *  for triggering the DMA to do a receive data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *  @param[in]  interruptMask  Bit mask of interrupts to check. Bitwise OR of
 *                             @ref DL_UART_DMA_INTERRUPT_RX.
 *
 *  @return     Which of the requested UART interrupts are pending
 *
 *  @retval     Bitwise OR of @ref DL_UART_DMA_INTERRUPT_RX values
 */
__STATIC_INLINE uint32_t DL_UART_getRawDMAReceiveEventStatus(DL_UNICOMM_Inst_Regs *unicomm, uint32_t interruptMask)
{
    return (unicomm->uart->DMA_TRIG_RX.RIS & interruptMask);
}

/**
 *  @brief      Check interrupt flag of any UART interrupt for DMA transmit event
 *
 *  Checks if any of the UART interrupts for DMA transmit event are pending.
 *  Interrupts do not have to be previously enabled.
 *  This API checks the DMA_TRIG_TX register, which is the event publisher used
 *  for triggering the DMA to do a transmit data transfer.
 *
 *  @param[in]  unicomm           Pointer to the register overlay for the
 *                             peripheral
 *
 *  @return     The requested UART interrupt status
 *
 *  @retval     DL_UART_DMA_INTERRUPT_TX if enabled, 0 if not enabled
 */
__STATIC_INLINE uint32_t DL_UART_getRawDMATransmitEventStatus(DL_UNICOMM_Inst_Regs *unicomm)
{
    return (unicomm->uart->DMA_TRIG_TX.RIS & UNICOMMUART_DMA_TRIG_TX_RIS_TXINT_MASK);
}

/**
 *  @brief      Save UART configuration before entering a power loss
 *              state.
 *
 *  Some MSPM0G peripherals residing in PD1 domain do not retain register
 *  contents when entering STOP or STANDBY modes. Please refer to the datasheet
 *  for the full list of peripheral instances that exhibit this behavior.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @param[in]  ptr   Configuration backup setup structure. See
 *                    @ref DL_UART_backupConfig.
 *
 *  @retval     FALSE if a configuration already exists in ptr (will not be
 *              overwritten). TRUE if a configuration was successfully saved
 *
 */
bool DL_UART_saveConfiguration(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_backupConfig *ptr);

/**
 *  @brief      Restore UART configuration after leaving a power loss
 *              state.
 *
 *  Some MSPM0G peripherals residing in PD1 domain do not retain register
 *  contents when entering STOP or STANDBY modes. Please refer to the datasheet
 *  for the full list of peripheral instances that exhibit this behavior.
 *
 *  @param[in]  unicomm  Pointer to the register overlay for the peripheral
 *
 *  @param[in]  ptr   Configuration backup setup structure. See
 *                    @ref DL_UART_backupConfig.
 *
 *  @retval     FALSE if a configuration does not exist in ptr (will not be
 *              loaded). TRUE if a configuration successfully loaded
 *
 */
bool DL_UART_restoreConfiguration(DL_UNICOMM_Inst_Regs *unicomm, DL_UART_backupConfig *ptr);

#ifdef __cplusplus
}
#endif

#endif /* DL_UNICOMMUART_H */

/**@}*/
