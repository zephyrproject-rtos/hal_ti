/*
 * Copyright (c) 2020-2024, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_handlers_ieee_h__include
#define ti_drivers_RCL_handlers_ieee_h__include

#include <stdint.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/commands/ieee.h>

/* Handler functions */
RCL_Events RCL_Handler_Ieee_RxTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_Ieee_TxTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);

/**
 *  @brief Result of IEEE command update API
 *
 *  Tells if update of IEEE command fields succeeded
 */
typedef enum
{
    RCL_IEEE_UpdateOk,          /*!< Update was successful */
    RCL_IEEE_UpdateIndexError,  /*!< Index was out of range or pointer was NULL */
} RCL_IEEE_UpdateResult;

/**
 *  @brief Result of entering ACK frame
 *
 *  Tells if ACK frame was entered successfully
 */
typedef enum
{
    RCL_IEEE_AckOk,             /*!< ACK was entered successfully */
    RCL_IEEE_AckNotExpected,    /*!< Ack was not expected */
    RCL_IEEE_AckTooLate,        /*!< Ack was provided too late */
    RCL_IEEE_AckError,          /*!< Data entry or pointer was not correct */
} RCL_IEEE_AckEntryResult;


/* API functions */
/**
 *  @brief  Update short source matching table
 *
 *  Update the given source matching table filter list in a way that is safe even if a running command is using
 *  the filter table.
 *
 *  @param  newAddr             New address and PAN ID to apply; NULL to leave unchanged
 *  @param  framePending        Value of frame pending bit
 *  @param  table               Source matching table to update
 *  @param  index               Index into source matching table to update
 *
 * @return                      Result telling if update was successful
 * @note                        Not supported in this version
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableShort(RCL_CmdIeee_PanIdAddr *newAddr, uint8_t framePending, RCL_CmdIeee_SourceMatchingTableShort *table, uint32_t index);

/**
 *  @brief  Update frame filtering settings extended source matching table
 *
 *  Update the given frame filtering settings in a way that is safe even if a running command is receiving a frame
 *
 *  @param  cmd                 Existing IEEE command to update
 *  @param  newPanConfig        New PAN configuration to apply
 *  @param  panNumber           Index of PAN to update
 *
 * @return                      Result telling if update was successful
 * @note                        Not supported in this version
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableExt(RCL_CmdIeeeRxTx *cmd, RCL_CmdIeee_PanConfig *newPanConfig, uint32_t panNumber);

/**
 *  @brief  Provide ACK frame to be transmitted in response to received packet
 *
 *  Provide an ACK frame, which will be transmitted if the frame was received successfully
 *
 *  @param  cmd                 Existing IEEE command for which to enter ACK
 *  @param  ackEntry            ACK to be transmitted over the air
 *
 * @return                      Result telling if update was successful
 * @note                        Not supported in this version
 *
 */
RCL_IEEE_AckEntryResult RCL_IEEE_enterAck(RCL_CmdIeeeRxTx *cmd, RCL_Buffer_DataEntry *ackEntry);

/**
 *  @brief  Update tx action
 *
 *  @param  cmd                 Existing IEEE command to submit the TX on top of
 *  @param  txAction            TX action to apply
 *
 * @return                      %RCL_CommandStatus result of the submission
 *
 */
RCL_CommandStatus RCL_IEEE_Tx_submit(RCL_CmdIeeeRxTx *cmd, RCL_CmdIeee_TxAction *txAction);

/**
 * @brief Stop a Tx action in an IEEE command
 *
 * Sends the message to try to stop a TX action. When the function returns, the command may still be
 * running. Depending on the stop type, the operation may stop after some time.
 *
 * @param cmd [in]              IEEE command
 * @param stopType [in]         Stop type; telling which situations the operation will stop
 *
 * @return                      Status of the TX operation; if the operation is not finished, a wait is needed.
 *
 */
RCL_CommandStatus RCL_IEEE_Tx_stop(RCL_CmdIeeeRxTx *cmd, RCL_StopType stopType);

/**
 * @brief Wait for a submitted TX operation to complete.
 *
 * Uses %SemaphoreP_pend to block in the callers context.
 *
 * @pre This function must be called from a task context, with interrupts enabled.
 *
 * @param[in] cmd               IEEE command running
 *
 * @return                      Status of the TX operation
 * @note                        Not supported in this version
 *
 */
RCL_CommandStatus RCL_IEEE_Tx_pend(RCL_CmdIeeeRxTx *cmd);

/**
 * @brief  Get received RSSI from packet
 *
 * Returns the RSSI field of a received packet, or LRF_RSSI_INVALID if RSSI is not enabled
 *
 * @param  rxEntry              Received data entry
 *
 * @return                      Reported RSSI of received packet
 * @note                        Not supported in this version
 *
 */
int8_t RCL_IEEE_getRxRssi(const RCL_Buffer_DataEntry *rxEntry);

/**
 * @brief  Get received timestamp from packet
 *
 * Returns the timestamp a received packet, adjusted to point to the start of the preamble.
 * If timestamp is not enabled, 0 is returned.
 * Note that 0 is a valid value, so it cannot be used for error checking.
 *
 * @param  rxEntry              Received data entry
 *
 * @return                      Timestamp of received packet
 * @note                        Not supported in this version
 *
 */
uint32_t RCL_IEEE_getRxTimestamp(const RCL_Buffer_DataEntry *rxEntry);

#endif /* ti_drivers_RCL_handlers_ble5_h__include */
