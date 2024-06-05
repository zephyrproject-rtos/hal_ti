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

#ifndef ti_drivers_RCL_handlers_ble5_h__include
#define ti_drivers_RCL_handlers_ble5_h__include

#include <stdint.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/commands/ble5.h>

/* Handler functions */
RCL_Events RCL_Handler_BLE5_adv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_scan_init(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_conn(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_dtmTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_genericRx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_genericTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_Ble5_txTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_aux_adv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_periodicAdv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);
RCL_Events RCL_Handler_BLE5_periodicScan(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn);

/**
 *  @brief Result of filter list update API
 *
 *  Tells if RCL_BLE5_FilterListUpdateResult succeeded
 */
typedef enum
{
    RCL_BLE5_FilterListUpdateOk,         /*!< Update was successful */
    RCL_BLE5_FilterListUpdateIndexError, /*!< Index was outside size of filter list or filter list was NULL */
} RCL_BLE5_FilterListUpdateResult;

/* API functions */
/**
 *  @brief  Update filter list
 *
 *  Update the given filter list in a way that is safe even if a running command is using
 *  the filter list. The contents of %newEntry will be copied into %filterList->entries[%index].
 *
 *  If a scanner or initiator function is running, the filter list in use in the radio will also be
 *  updated in a way that ensures no match will be found on a non-existing entry. In a short time,
 *  neither the old nor new entry will give a match.
 *
 *  If an advertiser command is running, the update will not apply until the next time the advertiser
 *  is started
 *
 *  @param  newEntry           New filter list entry to apply
 *  @param  filterList         Filter accept list to update
 *  @param  index              Index into filter accept list to update
 *
 * @return                     Result telling if update was successful
 *
 */
RCL_BLE5_FilterListUpdateResult RCL_BLE5_updateFilterList(const RCL_FL_Entry *newEntry, RCL_FilterList *filterList, uint32_t index);

/**
 *  @brief  Set RF frequency to use if custom frequency is specified
 *
 *  If a command specifies to use a custom frequency, it will program the frequency last set using
 *  this function.
 *
 *  @param  rfFrequency        RF frequency in Hz
 *
 */
void RCL_BLE5_setDefaultRfFrequency(uint32_t rfFrequency);

/**
 *  @brief  Get channel field from packet
 *
 *  Returns the channel that the packet was received on
 *
 *  @param  rxEntry            Received data entry
 *
 *  @return Channel for receiving packet
 */
static inline RCL_Ble5Channel RCL_BLE5_getRxChannel(const RCL_Buffer_DataEntry *rxEntry)
{
    return (RCL_Ble5Channel) rxEntry->pad0;
}

/**
 *  @brief  Get received status field from packet
 *
 *  Returns the packet status field of a received packet, or {.value = RCL_BLE5_RX_PKT_STATUS_INVALID} if status is not enabled
 *
 *  @param  rxEntry            Received data entry
 *
 *  @return Receive packet status
 */
RCL_Ble5_RxPktStatus RCL_BLE5_getRxStatus(const RCL_Buffer_DataEntry *rxEntry);

/**
 *  @brief  Get received RSSI from packet
 *
 *  Returns the RSSI field of a received packet, or LRF_RSSI_INVALID if RSSI is not enabled
 *
 *  @param  rxEntry            Received data entry
 *
 *  @return Reported RSSI of received packet
 */
int8_t RCL_BLE5_getRxRssi(const RCL_Buffer_DataEntry *rxEntry);

/**
 *  @brief  Get received timestamp from packet
 *
 *  Returns the timestamp a received packet, adjusted according to the PHY it was received on
 *  (1 Mbps assumed if packet status is not available). If timestamp is not enabled, 0 is returned.
 *  Note that this is a valid value, so it can not be used for error checking.
 *
 *  @param  rxEntry            Received data entry
 *
 *  @return Timestamp of received packet
 */
uint32_t RCL_BLE5_getRxTimestamp(const RCL_Buffer_DataEntry *rxEntry);

/**
 *  @brief  Get the expected start time delta associated with sending an auxiliary advertising indication
 *
 *  Returns the expected time delta between the start time of a non-connectable/non-scannable ADV_EXT_IND
 *  sent over a specific PHY on a defined channel map, and the start time of an AUX_ADV_IND that contains
 *  the SyncInfo field needed for periodic advertising establishment.
 *
 *  @param  phyFeatures         PHY feature selector
 *  @param  chMap               Channel map. Bit positions 0-2 correspond to channels 37-39
 *  @param  advPayloadLen       Payload length of ADV_EXT_IND
 *
 *  @return Time delta in 250[ns] units between the start time of the ADV_EXT_IND and the start time of the AUX_ADV_IND
 */
uint32_t RCL_BLE5_getAuxAdvStartTimeDelta(uint16_t phyFeatures, uint8_t chMap, uint8_t advPayloadLen);


#endif /* ti_drivers_RCL_handlers_ble5_h__include */
