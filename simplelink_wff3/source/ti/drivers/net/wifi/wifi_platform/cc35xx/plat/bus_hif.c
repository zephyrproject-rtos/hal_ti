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
#ifndef FW_EVENT_H
#define FW_EVENT_H

#include <bus_if.h>
#include "nab.h"
#define HIF_DMA_CHANNEL 11
#include "fw_status.h"
#include "hif.h"
#include "macro_utils.h"
#include "osi_kernel.h"


#define __FILE_ID__     FILE_ID_89


typedef struct{
    uint32_t dmaChannel;
}WBUS_HIF_DB_STRCT;
WBUS_HIF_DB_STRCT wbus_hif_db = {.dmaChannel = HIF_DMA_CHANNEL};

#define CORE_AON_HOST_BASE                                   (0x41C00000)
#define CORE_AON_REGS_O_NAB_HINT_STATUS_CLR_ON_RD            (0x000000B0)
#define CORE_AON_REGS_O_RX_STATUS_AON                        (0x0000000C)
/*========================================*/

volatile core_fw_status_t gFwStatusInfo __attribute((section(".connectivity_shared_status_section")));
/*=====================*/


static int HIFReadStatusRegs(FwStatus_t* rcv_bufffer, uint32_t flags);


uint8_t init_done = 0;

//#define HIF_COLLECT_DEBUG_STAT
#ifdef HIF_COLLECT_DEBUG_STAT

#define DEBUG_ARR_LENGTH 200
#define RX_BYTE_COUNT_MASK 0xFFFF
typedef struct
{
    uint32_t   tsf;
    uint32_t  readLength;
    uint32_t  totalReadLength;
    uint32_t  readstatus;
}debug_stat_t;
uint32 g_debug_arr_offset=0;
debug_stat_t debugStatArr[DEBUG_ARR_LENGTH];
#endif


uint32_t bus_AlignLength(uint32_t length)
{
    return ALIGN_TO_4_BYTE(length);
}


// Sends a Init command (to turn the chip over into mode)
int bus_sendInitCommand(uint32_t config, uint8_t fbrw)
{
    // marking the parameters as unused to bypass 'unused parameter' warning
    (void)config;
    (void)fbrw;

    HIFInit((uint32_t)wbus_hif_db.dmaChannel);
    init_done = 1;
    return 0;
}


 // Sends a  Read command
 //for flags see @HIF_STATUS_REQ_FLAGS_T
 int bus_sendReadCommand(uint32_t address, uint8_t *data, uint32_t length, uint8_t isFixed,uint32_t flags)
 {
     uint32_t actualLengthRead = 0;
     int32_t  ret;
#ifndef REMOVE_HIF_READ_DELAY
     volatile int32_t tmp_cnt = 0;
#endif
     if (length < sizeof(FwStatus_t))
     {
         ASSERT_GENERAL(0);
         return(1);
     }
     if(!init_done)
     {
         ASSERT_GENERAL(0);
         return(1);
     }

     if(address != FW_STATUS_ADDR)// read data and then status, else read only status
     {
         if(address == NAB_CONTROL_ADDR)
         {
             memset((void *)data,0x0, length);//for this cases, sometimes the actual length is less than length
         }
#ifdef HIF_COLLECT_DEBUG_STAT
         uint32 os_GetTimeInUS();
         if(address == NAB_DATA_ADDR)
         {
             debugStatArr[g_debug_arr_offset].tsf =  os_GetTimeInUS();
         }
#endif
         ret = HIFRead( wbus_hif_db.dmaChannel, address, data, length-sizeof(FwStatus_t), &actualLengthRead);
         if(ret<0)
         {
             HIFCollectDebugInfo();
             ASSERT_GENERAL(0);
         }
         
         data += length-sizeof(FwStatus_t);
         

     }

#ifndef REMOVE_HIF_READ_DELAY
     //Work Around
     //Wait for the NAB to finish his job
     while(tmp_cnt < 100)
     {
         tmp_cnt++;
     }
     tmp_cnt = 0;
#endif
     HIFReadStatusRegs((FwStatus_t *)data,flags);

     HIFSetIdle();

#ifdef HIF_COLLECT_DEBUG_STAT
         uint32 os_GetTimeInUS();


         if(address == NAB_DATA_ADDR)
         {
             debugStatArr[g_debug_arr_offset].readLength = actualLengthRead;
             debugStatArr[g_debug_arr_offset].totalReadLength += actualLengthRead;
             debugStatArr[g_debug_arr_offset].readstatus = ((FwStatus_t *)data)->rx_status & RX_BYTE_COUNT_MASK;

             if((++g_debug_arr_offset) >= DEBUG_ARR_LENGTH)
             {
                 g_debug_arr_offset = 0;
             }

         }
#endif

     return 0;
 }

// Sends a  Write command
int bus_sendWriteCommand(uint32_t address, uint8_t *data, uint32_t length, uint8_t isFixed)
{
    if(!init_done)
    {
        return(1);
    }
    HIFWrite(wbus_hif_db.dmaChannel, data, length);

    HIFSetIdle();

    return 0;
}

int bus_sendDeInitCommand()
{
    HIFDeinit();
    init_done = 0;
    return(0);
}


static int HIFReadStatusRegs(FwStatus_t* fwStatus, uint32_t flags)
{
    if (flags & HIF_GET_RX_HINT_CNTRL_STATUS)
    {
        fwStatus->host_interrupt_status = HWREG32(HIF_BASE + HIF_O_HNTSTACLR);
        fwStatus->rx_status = HWREG32(HIF_BASE + HIF_O_RXAON);
    }
    if (flags & HIF_GET_TX_CNTRL_STATUS)
    {
        memcpy(&fwStatus->fwInfo, (uint8_t*)(&gFwStatusInfo), sizeof(fwStatus->fwInfo));
    }
    if (flags & HIF_GET_TSF_STATUS)
    {
        memset(&fwStatus->tsf, 0, sizeof(fwStatus->tsf));
    }
    return 0;
}


#endif
