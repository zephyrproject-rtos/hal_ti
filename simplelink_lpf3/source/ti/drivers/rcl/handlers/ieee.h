/*
 * Copyright (c) 2020-2026, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_handlers_ieee__include
#define ti_drivers_rcl_handlers_ieee__include

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
    RCL_IEEE_UpdateDone,        /*!< Update was successfully done; no wait needed */
    RCL_IEEE_UpdatePending,     /*!< Update was successfully submitted; callback will be sent when done */
    RCL_IEEE_UpdateCmdError,    /*!< The requested update was not applicable or another update was pending */
    RCL_IEEE_UpdateParamError,  /*!< An invalid parameter was provided */
    RCL_IEEE_UpdateIndexError,  /*!< Index was out of range */
} RCL_IEEE_UpdateResult;

/**
 *  @brief Result of entering ACK frame
 *
 *  Tells if ACK frame was entered successfully
 */
typedef enum
{
    RCL_IEEE_AckOk,             /*!< ACK was entered successfully */
    RCL_IEEE_AckPartial,        /*!< Part of ACK entered successfully; more data expected */
    RCL_IEEE_AckNotExpected,    /*!< Ack was not expected or payload was provided too late */
    RCL_IEEE_AckAborted,        /*!< Ack transmission was aborted because of request or error */
    RCL_IEEE_AckError,          /*!< Data entry or pointer was not correct */
    RCL_IEEE_AckNotProcessed,   /*!< Ack processing not finished as expected */
} RCL_IEEE_AckEntryResult;

typedef enum
{
    RCL_IEEE_DisableEntry,              /*!< Disable the entry */
    RCL_IEEE_EnableEntry,               /*!< Enable the entry */
    RCL_IEEE_FrameNotPending,           /*!< Set frame not pending */
    RCL_IEEE_FramePending,              /*!< Set frame pending */
    RCL_IEEE_NewAddrFrameNotPending,    /*!< Change the address of the entry, enable, and set frame not pending */
    RCL_IEEE_NewAddrFramePending,       /*!< Change the address of the entry, enable, and set frame pending */
} RCL_IEEE_SourceMatchingOperation;

typedef struct
{
    uint8_t panNo;                              /*!< PAN number to update  */
    uint8_t index;                              /*!< Index into source matching table to update */
    RCL_IEEE_SourceMatchingOperation operation; /*!< Operation to perform on entry */
} RCL_IEEE_SourceMatchingUpdate;


/* API functions */
/**
 *  @brief  Update RX Action contents
 *
 *  Re-read the contents of the receive action of the given command. All elements will be re-read
 *  at an appropriate time; until then, the old value is used. The rxBuffers element should only
 *  be updated through normal RCL_Buffer functions, though. If the status indicates that the update
 *  is pending, a cmdUpdateDone event is raised when it is done. If an error occurred during the
 *  update, the command will end with error.
 *
 *  @param  cmd                 Existing IEEE command for which to re-read the RX action contents
 *
 *  @return                     Result telling if update was successful
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateRxAction(RCL_CmdIeeeRxTx *cmd);

/**
 *  @brief  Update short source matching table
 *
 *  Update the given source matching table in a way that is safe even if a running command is using
 *  the source matching table.
 *
 *  @param  cmd                 Existing IEEE command for which to update the source matching table
 *  @param  description         Description of operation to perform
 *  @param  newPanIdAddr        If entry is changed: New PAN ID and address to set
 *
 * @return                      Result telling if update was successful
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableShort(RCL_CmdIeeeRxTx *cmd, RCL_IEEE_SourceMatchingUpdate description, RCL_CmdIeee_PanIdAddr newPanIdAddr);

/**
 *  @brief  Update extended source matching table
 *
 *  Update the given source matching table in a way that is safe even if a running command is using
 *  the source matching table.
 *
 *  @param  cmd                 Existing IEEE command for which to update the source matching table
 *  @param  description         Description of operation to perform
 *  @param  newAddr             If entry is changed: Pointer to the new address to set
 *
 * @return                      Result telling if update was successful
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableExt(RCL_CmdIeeeRxTx *cmd, RCL_IEEE_SourceMatchingUpdate description, const uint64_t *newAddr);

/**
 *  @brief  Update TX power
 *
 *  Update the TX power used for future frames sent with TX actions or as ACKs for a running command.
 *  The command structure will be updated with the new value if the update was successful.
 *
 *  @param  cmd                 Existing IEEE command for which to update the TX power
 *  @param  newTxPower          New TX power value
 *
 * @return                      Result telling if update was successful
 *
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateTxPower(RCL_CmdIeeeRxTx *cmd, RCL_Command_TxPower newTxPower);

/**
 *  @brief  Provide ACK data to be transmitted in response to received frame
 *
 *  Provide an ACK frame or the parts of it, which will be transmitted if the frame was received successfully
 *
 *  @param  cmd                 Existing IEEE command for which to enter ACK
 *  @param  ackData             Pointer to data that will be appended; first part should be of type %RCL_Buffer_DataEntry
 *  @param  numWords            Number of 32-bit words provided at this point; 0 if entry is complete
 *
 * @return                      Result telling if update was successful
 * @note                        All pieces of data must be provided in portions of 32-bit words
 *
 */
RCL_IEEE_AckEntryResult RCL_IEEE_enterAck(RCL_CmdIeeeRxTx *cmd, uint32_t *ackData, uint8_t numWords);

/**
 *  @brief  Cancel transmission of ACK in response to received frame
 *
 *  Cancel transmission of an ACK by not starting it or aborting transmission
 *
 *  @param  cmd                 Existing IEEE command for which to enter ACK
 *
 * @return                      Result telling if update was successful
 *
 */
RCL_IEEE_AckEntryResult RCL_IEEE_cancelAck(RCL_CmdIeeeRxTx *cmd);

/**
 *  @brief  Read partially received frame into buffer
 *
 *  @param    cmd            Existing IEEE command receiving the frame
 *  @param    dataEntry      Entry for storing data
 *  @param    entrySize      Number of bytes available in entry, including header fields (should be a multiple of 4)
 *
 * @return                   Number of bytes read into entry, including header fields
 *
 */
size_t RCL_IEEE_readPartialFrame(RCL_CmdIeeeRxTx *cmd, RCL_Buffer_DataEntry *dataEntry, size_t entrySize);

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
 * @brief  Get received RSSI from frame
 *
 * Returns the RSSI field of a received frame, or LRF_RSSI_INVALID if appending RSSI is not enabled
 *
 * @param  rxEntry              Received data entry
 *
 * @return                      Reported RSSI of received frame
 *
 */
int8_t RCL_IEEE_getRxRssi(const RCL_Buffer_DataEntry *rxEntry);

/**
 * @brief  Get received LQI from frame
 *
 * Returns the LQI field of a received frame, or 0 if appending LQI is not enabled
 *
 * @param  rxEntry              Received data entry
 *
 * @return                      Reported LQI of received frame
 *
 */
uint8_t RCL_IEEE_getRxLqi(const RCL_Buffer_DataEntry *rxEntry);

/**
 * @brief  Get received timestamp from frame
 *
 * Returns the timestamp in 0.25 us units of a received frame, adjusted to point to the start of
 * the preamble. If appending timestamp is not enabled, 0 is returned.
 * Note that 0 is a valid value, so it cannot be used for error checking.
 *
 * @param  rxEntry              Received data entry
 *
 * @return                      Timestamp of received frame
 *
 */
uint32_t RCL_IEEE_getRxTimestamp(const RCL_Buffer_DataEntry *rxEntry);

#endif /* ti_drivers_rcl_handlers_ieee__include */
