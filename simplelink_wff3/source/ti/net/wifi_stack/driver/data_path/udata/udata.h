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
/** \file   udata.h
 *  \brief  The internal definitions of the upper data path (UDATA) component.
 *          This includes definitions common to more than one module in the UDATA.
 * 
 *  \see    udata.c, udata_Api.h
 */

#ifndef _UDATA_H_
#define _UDATA_H_


#include "ti_qos_types.h"
#include "tw_driver.h"
#include "udata_api.h"
#include "public_defines.h"

#include "cc3xxx_public_types.h"

//#define UDATA_LOG_REPORT
#ifdef UDATA_LOG_REPORT
#define UDATA_PRINT Report
#define UDATA_PRINT_ERROR Report
#else
#define UDATA_PRINT(...)
#define UDATA_PRINT_ERROR Report
#endif

extern const EAcTrfcType WMEQosTagToACTable[MAX_NUM_OF_802_1d_TAGS];

#define MGMT_QUEUES_DEPTH      8    /* Up to 4 packets per queue. */

/* RX/TX debug functions */
typedef enum
{
/* Tx debug functions */
/*  0   */  TX_RX_DBG_FUNCTIONS,
/*  1   */  PRINT_TX_CTRL_INFO,
/*  2   */  PRINT_TX_CTRL_COUNTERS,
/*  3   */  PRINT_TX_DATA_QUEUE_INFO,
/*  4   */  PRINT_TX_DATA_QUEUE_COUNTERS,
/*  5   */  PRINT_TX_MGMT_QUEUE_INFO,
/*  6   */  PRINT_TX_MGMT_QUEUE_COUNTERS,
/*  7   */  PRINT_TX_CTRL_BLK_INFO,
/*  8   */  PRINT_TX_HW_QUEUE_INFO,
/*  9   */  PRINT_TX_XFER_INFO,
/*  10  */  PRINT_TX_RESULT_INFO,
/*  11  */  PRINT_TX_DATA_CLSFR_TABLE,
/*  20  */  RESET_TX_CTRL_COUNTERS          = 20,
/*  21  */  RESET_TX_DATA_QUEUE_COUNTERS,
/*  22  */  RESET_TX_DATA_CLSFR_TABLE,
/*  23  */  RESET_TX_MGMT_QUEUE_COUNTERS,
/*  24  */  RESET_TX_RESULT_COUNTERS,
/*  25  */  RESET_TX_XFER_COUNTERS,
    
/* Rx debug functions */
/*  50  */  PRINT_RX_BLOCK                  = 50,
/*  51  */  PRINT_RX_COUNTERS,
/*  52  */  RESET_RX_COUNTERS

} ERxTxDbgFunc;

#define IS_ROLE_TYPE_AP_OR_P2PGO(eRoleType)     ((eRoleType == ROLE_AP)  || (eRoleType == ROLE_P2P_GO))
#define IS_ROLE_TYPE_STA_OR_P2PCL(eRoleType)    ((eRoleType == ROLE_STA) || (eRoleType == ROLE_P2P_CL))





#endif /* _UDATA_H_ */

