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
#ifndef _CORE_DEFAULT_PARAMS_H
#define _CORE_DEFAULT_PARAMS_H


#include "tw_driver.h"
#include "public_types.h"

/************************************/
/*      Min, Max & Default values   */
/************************************/

/* In this section are defined default, min & max values for parameters, according to the MIB */
/* This values are used as following:
        - By the OS abstraction layer in order to fill the init table with the default values
        if the NVRAM/Registry value for the parameter is invalid
        - By the core modules in order to perform validity check upon setting a parameter. */

#define DEFAULT_CHANNEL_NUM (1)

/* RegDomain ini default values*/
#define TI_REG_DOMAIN_NUM_OF_COUNTRIES_MIN      2
#define TI_REG_DOMAIN_NUM_OF_COUNTRIES_MAX      200

#define TI_REG_DOMAIN_COUNTRY_CONFIG_LENGTH     22


/* This is the max possible string length from INI file */
#define BEACON_FILTER_STRING_MAX_LEN            300

/* Band B&G*/
#define TI_PARAM_CHANNEL_B_G_MAX                14

#define TI_PARAM_DOT_11_MODE_MIN                DOT11_B_MODE
#define TI_PARAM_DOT_11_MODE_MAX                DOT11_DUAL_MODE
#define TI_PARAM_DOT_11_MODE_DEF                DOT11_DUAL_MODE

/* Driver inactivity period (msec) before allowing to sleep when optimized for performance */
#define INACTIVITY_PERIOD_DEF                   0
#define INACTIVITY_PERIOD_MIN                   0
#define INACTIVITY_PERIOD_MAX                   1000

#define TI_PARAM_PREAMBLE_TYPE_DEF              PREAMBLE_SHORT

/* Beacon broadcast options */
#define BCN_RX_TIMEOUT_DEF_VALUE 10000
#define BCN_RX_TIMEOUT_MIN_VALUE 1
#define BCN_RX_TIMEOUT_MAX_VALUE 65535

#define BROADCAST_RX_TIMEOUT_DEF_VALUE 20000
#define BROADCAST_RX_TIMEOUT_MIN_VALUE 1
#define BROADCAST_RX_TIMEOUT_MAX_VALUE 65535

#define RX_BROADCAST_IN_PS_DEF_VALUE 1
#define RX_BROADCAST_IN_PS_MIN_VALUE 0
#define RX_BROADCAST_IN_PS_MAX_VALUE 1

#define CONSECUTIVE_PS_POLL_FAILURE_DEF 4
#define CONSECUTIVE_PS_POLL_FAILURE_MIN 1
#define CONSECUTIVE_PS_POLL_FAILURE_MAX 100
/*---------------------------*/
/*  Classifier parameters    */
/*---------------------------*/

/* 0 - Dtag, 1 - DSCP, 2 - Port, 3 - IP & port */
#define CLSFR_TYPE_MIN                      0
#define CLSFR_TYPE_DEF                      1
#define CLSFR_TYPE_MAX                      3

/* general values of D-tags */
#define CLASSIFIER_DTAG_MIN                 0
#define CLASSIFIER_DTAG_MAX                 7
#define CLASSIFIER_DTAG_DEF                 0

/* general values of code points in
the DSCP classification table*/
#define CLASSIFIER_CODE_POINT_MIN       0
#define CLASSIFIER_CODE_POINT_MAX       63
#define CLASSIFIER_CODE_POINT_DEF       0

/* general values of port numbers */
#define CLASSIFIER_PORT_MIN                 1
#define CLASSIFIER_PORT_MAX                 65535
#define CLASSIFIER_PORT_DEF                 1024

/* General values of IP addresses */
/* TBD according to spec!*/
#define CLASSIFIER_IPADDRESS_MIN                0x0
/* MY IP ... TBD according to spec!*/
#define CLASSIFIER_IPADDRESS_DEF                0x0A030DC4
/* TBD according to spec!*/
#define CLASSIFIER_IPADDRESS_MAX                0xFFFFFFFF

/* DSCP (differentiated services code
point) classifier parameters
--------------------------------*/
/* number of classifier entries in the
   classification table (in case of DSCP classifier) */

#define NUM_OF_CODE_POINTS_MIN              0
#define NUM_OF_CODE_POINTS_MAX              16
#define NUM_OF_CODE_POINTS_DEF              8

/* def values of code points in the DSCP classification table*/
#define DSCP_CLASSIFIER_CODE_POINT_DEF  0x0
#define DSCP_CLASSIFIER_CODE_POINT_00  0
#define DSCP_CLASSIFIER_CODE_POINT_01  8
#define DSCP_CLASSIFIER_CODE_POINT_02  16
#define DSCP_CLASSIFIER_CODE_POINT_03  24
#define DSCP_CLASSIFIER_CODE_POINT_04  32
#define DSCP_CLASSIFIER_CODE_POINT_05  40
#define DSCP_CLASSIFIER_CODE_POINT_06  48
#define DSCP_CLASSIFIER_CODE_POINT_07  56
/* def values of D-tags in the DSCP classification table*/
#define DSCP_CLASSIFIER_DTAG_DEF            0
#define DSCP_CLASSIFIER_DTAG_00            0
#define DSCP_CLASSIFIER_DTAG_01            1
#define DSCP_CLASSIFIER_DTAG_02            2
#define DSCP_CLASSIFIER_DTAG_03            3
#define DSCP_CLASSIFIER_DTAG_04            4
#define DSCP_CLASSIFIER_DTAG_05            5
#define DSCP_CLASSIFIER_DTAG_06            6
#define DSCP_CLASSIFIER_DTAG_07            7

/* Port Classifier parameters
--------------------------------*/

/* number of entries in the classification table (in case of destination port classifier) */
#define NUM_OF_PORT_CLASSIFIERS_MIN         0
#define NUM_OF_PORT_CLASSIFIERS_MAX         16
#define NUM_OF_PORT_CLASSIFIERS_DEF         0

/* def values of port numbers in the destination port classification table*/
#define PORT_CLASSIFIER_PORT_DEF            5000

/* def values of D-tags in the destination port classification table*/
#define PORT_CLASSIFIER_DTAG_DEF            7

/* IP&Port Classifier parameters
--------------------------------*/

/* number of active entries in the
IP&Port classification table  */
#define NUM_OF_IPPORT_CLASSIFIERS_MIN       0
#define NUM_OF_IPPORT_CLASSIFIERS_MAX       16
#define NUM_OF_IPPORT_CLASSIFIERS_DEF       0

/* def values of IP addresses in the IP&Port classification table*/
#define IPPORT_CLASSIFIER_IPADDRESS_DEF 167972292

/* def values of port numbers in the IP&Port classification table*/
#define IPPORT_CLASSIFIER_PORT_DEF      5004

/* def values of D-tags in the IP&Port classification table*/
#define IPPORT_CLASSIFIER_DTAG_DEF      7

/* end of classifier parameters */

#define MAX_USER_PRIORITY                       7



#define  WME_ENABLED_MIN                        FALSE
#define  WME_ENABLED_MAX                        TRUE
#define  WME_ENABLED_DEF                        TRUE

#define  QOS_TRAFFIC_ADM_CTRL_ENABLED_MIN       FALSE
#define  QOS_TRAFFIC_ADM_CTRL_ENABLED_MAX       TRUE
#define  QOS_TRAFFIC_ADM_CTRL_ENABLED_DEF       TRUE

#define  QOS_DESIRED_PS_MODE_MIN            PS_SCHEME_LEGACY
#define  QOS_DESIRED_PS_MODE_MAX            MAX_PS_SCHEME
#define  QOS_DESIRED_PS_MODE_DEF            PS_SCHEME_UPSD_TRIGGER

#define  QOS_TAG_ZERO_PRIO_MIN                  FALSE
#define  QOS_TAG_ZERO_PRIO_MAX                  TRUE
#define  QOS_TAG_ZERO_PRIO_DEF                  TRUE


/* for the AC */
#define  QOS_TX_OP_CONTINUATION_MIN             0
#define  QOS_TX_OP_CONTINUATION_MAX             1
#define  QOS_TX_OP_CONTINUATION_DEF            1

#define  QOS_TX_OP_LIMIT_MIN                   0
#define  QOS_TX_OP_LIMIT_MAX                   32000
#define  QOS_TX_OP_LIMIT_DEF                   0

/* for packet burst in non-qos protocol */
#define  QOS_PACKET_BURST_ENABLE_MIN             0
#define  QOS_PACKET_BURST_ENABLE_DEF            0
#define  QOS_PACKET_BURST_ENABLE_MAX             1

#define  QOS_PACKET_BURST_TXOP_LIMIT_MIN         0
#define  QOS_PACKET_BURST_TXOP_LIMIT_MAX         1000
#define  QOS_PACKET_BURST_TXOP_LIMIT_DEF         93

#define  QOS_RX_TIMEOUT_PS_POLL_MIN                0
#define  QOS_RX_TIMEOUT_PS_POLL_MAX             200000
#define  QOS_RX_TIMEOUT_PS_POLL_DEF                15

#define  QOS_RX_TIMEOUT_UPSD_MIN                   0
#define  QOS_RX_TIMEOUT_UPSD_MAX                200000
#define  QOS_RX_TIMEOUT_UPSD_DEF                   15

#define  QOS_MSDU_LIFE_TIME_MIN                0
#ifndef AP_MODE_ENABLED
#define  QOS_MSDU_LIFE_TIME_MAX                1024
#else
#define  QOS_MSDU_LIFE_TIME_MAX                12000
#endif
#define  QOS_MSDU_LIFE_TIME_BE_MIN              QOS_MSDU_LIFE_TIME_MIN
#define  QOS_MSDU_LIFE_TIME_BE_MAX              QOS_MSDU_LIFE_TIME_MAX
#ifndef AP_MODE_ENABLED
#define  QOS_MSDU_LIFE_TIME_BE_DEF              1024
#else
#define  QOS_MSDU_LIFE_TIME_BE_DEF              8000
#endif

#define  QOS_MSDU_LIFE_TIME_BK_MIN              QOS_MSDU_LIFE_TIME_MIN
#define  QOS_MSDU_LIFE_TIME_BK_MAX              QOS_MSDU_LIFE_TIME_MAX
#ifndef AP_MODE_ENABLED
#define  QOS_MSDU_LIFE_TIME_BK_DEF              512
#else
#define  QOS_MSDU_LIFE_TIME_BK_DEF              8000
#endif

#define  QOS_MSDU_LIFE_TIME_VI_MIN              QOS_MSDU_LIFE_TIME_MIN
#define  QOS_MSDU_LIFE_TIME_VI_MAX              QOS_MSDU_LIFE_TIME_MAX
#ifndef AP_MODE_ENABLED
#define  QOS_MSDU_LIFE_TIME_VI_DEF              1024
#else
#define  QOS_MSDU_LIFE_TIME_VI_DEF              8000
#endif

#define  QOS_MSDU_LIFE_TIME_VO_MIN              QOS_MSDU_LIFE_TIME_MIN
#define  QOS_MSDU_LIFE_TIME_VO_MAX              QOS_MSDU_LIFE_TIME_MAX
#ifndef AP_MODE_ENABLED
#define  QOS_MSDU_LIFE_TIME_VO_DEF              512
#else
#define  QOS_MSDU_LIFE_TIME_VO_DEF              8000
#endif

#define  QOS_WME_PS_MODE_BE_MIN                 PS_SCHEME_LEGACY
#define  QOS_WME_PS_MODE_BE_MAX                 MAX_PS_SCHEME
#define  QOS_WME_PS_MODE_BE_DEF                 PS_SCHEME_LEGACY

#define  QOS_WME_PS_MODE_BK_MIN                 PS_SCHEME_LEGACY
#define  QOS_WME_PS_MODE_BK_MAX                 MAX_PS_SCHEME
#define  QOS_WME_PS_MODE_BK_DEF                 PS_SCHEME_LEGACY

#define  QOS_WME_PS_MODE_VI_MIN                 PS_SCHEME_LEGACY
#define  QOS_WME_PS_MODE_VI_MAX                 MAX_PS_SCHEME
#define  QOS_WME_PS_MODE_VI_DEF                 PS_SCHEME_LEGACY

#define  QOS_WME_PS_MODE_VO_MIN                 PS_SCHEME_LEGACY
#define  QOS_WME_PS_MODE_VO_MAX                 MAX_PS_SCHEME
#define  QOS_WME_PS_MODE_VO_DEF                 PS_SCHEME_UPSD_TRIGGER


/* TxHwQueue thresholds */

#define  QOS_TX_BLKS_THRESHOLD_MIN              0
#define  QOS_TX_BLKS_THRESHOLD_MAX              200
#define  QOS_TX_BLKS_THRESHOLD_VO_DEF           6

#define  RX_MEM_BLKS_NUM_MIN                    20
#define  RX_MEM_BLKS_NUM_MAX                    120
#define  RX_MEM_BLKS_NUM_DEF                    40

#define  DYNAMIC_MEMORY_ENABLE_MIN              0
#define  DYNAMIC_MEMORY_ENABLE_MAX              1
#define  DYNAMIC_MEMORY_ENABLE_DEF              1

#define  TX_FREE_REQ_MIN                        0
#define  TX_FREE_REQ_MAX                        120
#define  TX_FREE_REQ_DEF                        45

#define  RX_FREE_REQ_MIN                        0
#define  RX_FREE_REQ_MAX                        120
#define  RX_FREE_REQ_DEF                        22

#define  TX_MIN_MIN                             0
#define  TX_MIN_MAX                             120
#define  TX_MIN_DEF                             27

#define  HOST_TX_DESCRIPTORS_DEF                NUM_TX_DESCRIPTORS
#define  HOST_TX_DESCRIPTORS_MIN                0
#define  HOST_TX_DESCRIPTORS_MAX                64

/* Tx Data resources */
#define  TX_DATA_MIN_GUARANTEE_BE_DEF           0//6
#define  TX_DATA_MIN_GUARANTEE_BK_DEF           0//2
#define  TX_DATA_MIN_GUARANTEE_VI_DEF           0//4
#define  TX_DATA_MIN_GUARANTEE_VO_DEF           0// 8
#define  TX_DATA_MIN_GUARANTEE_AC_MIN           0//0
#define  TX_DATA_MIN_GUARANTEE_AC_MAX           10

#define  TX_DATA_MIN_GUARANTEE_LINK_DEF         0//4
#define  TX_DATA_MIN_GUARANTEE_LINK_MIN         0
#define  TX_DATA_MIN_GUARANTEE_LINK_MAX         10

/* Maximum AMPDU Size */
#define MAX_MPDU_DEF                            MAX_MPDU_16383_OCTETS

/* Tx send pacing threshold: num of Tx pkts to queue before handling them (excluding voice queue) */
#define  TX_SEND_PACE_THRESH_DEF                1
#define  TX_SEND_PACE_THRESH_MIN                1
#define  TX_SEND_PACE_THRESH_MAX                16

#define  QOS_QID_MIN                           0
#define  QOS_QID_MAX                           3

#define  QOS_AC_MIN                            QOS_QID_MIN
#define  QOS_AC_MAX                            QOS_QID_MAX

#define  QOS_AIFS_MIN                          1
#define  QOS_AIFS_MAX                          15

#define QOS_CWMIN_MIN                          0
#define QOS_CWMIN_MAX                          15

#define QOS_CWMAX_MIN                          0
#define QOS_CWMAX_MAX                          15

#define QOS_TIMEOUT_MIN                        0
#define QOS_TIMEOUT_MAX                        65535

#define QOS_ACK_POLICY_MIN                     0
#define QOS_ACK_POLICY_MAX                     1

#define QOS_TRAFFIC_TYPE_MIN                   0
#define QOS_TRAFFIC_TYPE_MAX                   1

#define QOS_SHORT_RETRY_LIMIT_MIN              1
#define QOS_SHORT_RETRY_LIMIT_MAX              255
#define QOS_SHORT_RETRY_LIMIT_DEF              10

#define QOS_SHORT_RETRY_LIMIT_BE_MIN            QOS_SHORT_RETRY_LIMIT_MIN
#define QOS_SHORT_RETRY_LIMIT_BE_MAX            QOS_SHORT_RETRY_LIMIT_MAX
#define QOS_SHORT_RETRY_LIMIT_BE_DEF            QOS_SHORT_RETRY_LIMIT_DEF

#define QOS_SHORT_RETRY_LIMIT_BK_MIN            QOS_SHORT_RETRY_LIMIT_MIN
#define QOS_SHORT_RETRY_LIMIT_BK_MAX            QOS_SHORT_RETRY_LIMIT_MAX
#define QOS_SHORT_RETRY_LIMIT_BK_DEF            QOS_SHORT_RETRY_LIMIT_DEF

#define QOS_SHORT_RETRY_LIMIT_VI_MIN            QOS_SHORT_RETRY_LIMIT_MIN
#define QOS_SHORT_RETRY_LIMIT_VI_MAX            QOS_SHORT_RETRY_LIMIT_MAX
#define QOS_SHORT_RETRY_LIMIT_VI_DEF            QOS_SHORT_RETRY_LIMIT_DEF

#define QOS_SHORT_RETRY_LIMIT_VO_MIN            QOS_SHORT_RETRY_LIMIT_MIN
#define QOS_SHORT_RETRY_LIMIT_VO_MAX            QOS_SHORT_RETRY_LIMIT_MAX
#define QOS_SHORT_RETRY_LIMIT_VO_DEF            4


#define QOS_LONG_RETRY_LIMIT_MIN               1
#define QOS_LONG_RETRY_LIMIT_MAX               255
#define QOS_LONG_RETRY_LIMIT_DEF               4

#define QOS_LONG_RETRY_LIMIT_BE_MIN             QOS_LONG_RETRY_LIMIT_MIN
#define QOS_LONG_RETRY_LIMIT_BE_MAX             QOS_LONG_RETRY_LIMIT_MAX
#define QOS_LONG_RETRY_LIMIT_BE_DEF             QOS_LONG_RETRY_LIMIT_DEF

#define QOS_LONG_RETRY_LIMIT_BK_MIN             QOS_LONG_RETRY_LIMIT_MIN
#define QOS_LONG_RETRY_LIMIT_BK_MAX             QOS_LONG_RETRY_LIMIT_MAX
#define QOS_LONG_RETRY_LIMIT_BK_DEF             QOS_LONG_RETRY_LIMIT_DEF

#define QOS_LONG_RETRY_LIMIT_VI_MIN             QOS_LONG_RETRY_LIMIT_MIN
#define QOS_LONG_RETRY_LIMIT_VI_MAX             QOS_LONG_RETRY_LIMIT_MAX
#define QOS_LONG_RETRY_LIMIT_VI_DEF             QOS_LONG_RETRY_LIMIT_DEF

#define QOS_LONG_RETRY_LIMIT_VO_MIN             QOS_LONG_RETRY_LIMIT_MIN
#define QOS_LONG_RETRY_LIMIT_VO_MAX             QOS_LONG_RETRY_LIMIT_MAX
#define QOS_LONG_RETRY_LIMIT_VO_DEF             QOS_LONG_RETRY_LIMIT_DEF

#define QOS_QUEUE_0_OVFLOW_POLICY_MIN           DROP_NEW_PACKET
#define QOS_QUEUE_0_OVFLOW_POLICY_MAX           DROP_OLD_PACKET
#define QOS_QUEUE_0_OVFLOW_POLICY_DEF           DROP_NEW_PACKET

#define QOS_QUEUE_1_OVFLOW_POLICY_MIN           DROP_NEW_PACKET
#define QOS_QUEUE_1_OVFLOW_POLICY_MAX           DROP_OLD_PACKET
#define QOS_QUEUE_1_OVFLOW_POLICY_DEF           DROP_NEW_PACKET

#define QOS_QUEUE_2_OVFLOW_POLICY_MIN           DROP_NEW_PACKET
#define QOS_QUEUE_2_OVFLOW_POLICY_MAX           DROP_OLD_PACKET
#define QOS_QUEUE_2_OVFLOW_POLICY_DEF           DROP_NEW_PACKET

#define QOS_QUEUE_3_OVFLOW_POLICY_MIN           DROP_NEW_PACKET
#define QOS_QUEUE_3_OVFLOW_POLICY_MAX           DROP_OLD_PACKET
#define QOS_QUEUE_3_OVFLOW_POLICY_DEF           DROP_NEW_PACKET

#define QOS_ACK_POLICY_BE_MIN                   ACK_POLICY_LEGACY
#define QOS_ACK_POLICY_BE_MAX                   MAX_ACK_POLICY
#define QOS_ACK_POLICY_BE_DEF                   ACK_POLICY_LEGACY

#define QOS_ACK_POLICY_BK_MIN                   ACK_POLICY_LEGACY
#define QOS_ACK_POLICY_BK_MAX                   MAX_ACK_POLICY
#define QOS_ACK_POLICY_BK_DEF                   ACK_POLICY_LEGACY

#define QOS_ACK_POLICY_VI_MIN                   ACK_POLICY_LEGACY
#define QOS_ACK_POLICY_VI_MAX                   MAX_ACK_POLICY
#define QOS_ACK_POLICY_VI_DEF                   ACK_POLICY_LEGACY

#define QOS_ACK_POLICY_VO_MIN                   ACK_POLICY_LEGACY
#define QOS_ACK_POLICY_VO_MAX                   MAX_ACK_POLICY
#define QOS_ACK_POLICY_VO_DEF                   ACK_POLICY_LEGACY


/* MAX_SP_LEN_VALUES
  00 - all buffered frames
  01 - 2
  10 - 4
  11 - 6
*/

#define QOS_MAX_SP_LEN_MIN                      0
#define QOS_MAX_SP_LEN_MAX                      3
/* Means maxSpLen = 2 (changed for SoftGemini requiremnet) */
#define QOS_MAX_SP_LEN_DEF                      1

/* CW setting from the ini */
#define QOS_CW_USER_ENABLE_MIN                  0
#define QOS_CW_USER_ENABLE_MAX                  1
#define QOS_CW_USER_ENABLE_DEF                  0

#define QOS_CW_CWMIN_MIN                        QOS_CWMIN_MIN
#define QOS_CW_CWMIN_MAX                        QOS_CWMIN_MAX
#define QOS_CW_CWMIN_DEF                        CW_MIN_DEF

#define QOS_CW_CWMAX_MIN                        QOS_CWMAX_MIN
#define QOS_CW_CWMAX_MAX                        QOS_CWMAX_MAX
#define QOS_CW_CWMAX_DEF                        CW_MAX_DEF

/*
 *  FW Logger setting
*/
#define FW_LOGGER_ENABLE_MIN        0
#define FW_LOGGER_ENABLE_MAX        1
#define FW_LOGGER_ENABLE_DEF        0

#define FW_LOGGER_LOGMOD_MIN        0
#define FW_LOGGER_LOGMOD_MAX        1
#define FW_LOGGER_LOGMOD_DEF        0

#define FW_LOGGER_BUFSIZE_MIN       0
#define FW_LOGGER_BUFSIZE_MAX       3
#define FW_LOGGER_BUFSIZE_DEF       2

#define FW_LOGGER_SEVERITY_MIN      0
#define FW_LOGGER_SEVERITY_MAX      7
#define FW_LOGGER_SEVERITY_DEF      0

#define FW_LOGGER_TIMSTMP_MIN       0
#define FW_LOGGER_TIMSTMP_MAX       1
#define FW_LOGGER_TIMSTMP_DEF       0

#define FW_LOGGER_MSGOUTPUT_MIN     0
#define FW_LOGGER_MSGOUTPUT_MAX     2
#define FW_LOGGER_MSGOUTPUT_DEF     1

#define FW_LOGGER_THRESHOLD_MIN     0
#define FW_LOGGER_THRESHOLD_MAX     50
#define FW_LOGGER_THRESHOLD_DEF     5

#define FW_MEM_DUMP_ENABLED_MIN     FALSE
#define FW_MEM_DUMP_ENABLED_MAX     TRUE
#define FW_MEM_DUMP_ENABLED_DEF     FALSE


/*
 * 802.11n HT settion
 */
#define  HT_11N_ENABLED_MIN                         FALSE
#define  HT_11N_ENABLED_MAX                         TRUE
#define  HT_11N_ENABLED_DEF                         TRUE

/* policies: 0 - disable, 1 - initiator, 2 - receiver, 3 -  initiator& receiver. */
#define  HT_BA_POLICY_MIN                           0
#define  HT_BA_POLICY_MAX                           3
#define  HT_BA_POLICY_DEF                           0

/* In the 11n spec in order to set endless timeout the value is 0 */
#define  HT_BA_INACTIVITY_TIMEOUT_MIN               0
#define  HT_BA_INACTIVITY_TIMEOUT_MAX               0xffff
#define  HT_BA_INACTIVITY_TIMEOUT_DEF               10000

/*---------------------------
      ROAMING parameters
-----------------------------*/
#define ROAMING_MNGR_ENABLE_MIN             0
#define ROAMING_MNGR_ENABLE_MAX             1
#define ROAMING_MNGR_ENABLE_DEF             0

#define ROAMING_MNGR_ENABLE_PERIODIC_SCAN_MIN       0
#define ROAMING_MNGR_ENABLE_PERIODIC_SCAN_MAX       1
#define ROAMING_MNGR_ENABLE_PERIODIC_SCAN_DEF       0

#define ROAMING_MNGR_RSSI_GAP_MIN                   0
#define ROAMING_MNGR_RSSI_GAP_MAX                   50
#define ROAMING_MNGR_RSSI_GAP_DEF                   10

#define ROAMING_MNGR_PERIODIC_SCAN_TIEMOUT_MIN      1000
#define ROAMING_MNGR_PERIODIC_SCAN_TIEMOUT_MAX      10000
#define ROAMING_MNGR_PERIODIC_SCAN_TIEMOUT_DEF      3000

#define ROAMING_MNGR_PERIODIC_SCAN_MIN_CH_MIN       5
#define ROAMING_MNGR_PERIODIC_SCAN_MIN_CH_MAX       60
#define ROAMING_MNGR_PERIODIC_SCAN_MIN_CH_DEF       5

#define ROAMING_MNGR_PERIODIC_SCAN_MAX_CH_MIN       5
#define ROAMING_MNGR_PERIODIC_SCAN_MAX_CH_MAX       60
#define ROAMING_MNGR_PERIODIC_SCAN_MAX_CH_DEF       20

#define ROAMING_MNGR_PERIODIC_SCAN_ET_MODE_MIN      0
#define ROAMING_MNGR_PERIODIC_SCAN_ET_MODE_MAX      3
#define ROAMING_MNGR_PERIODIC_SCAN_ET_MODE_DEF      3

#define ROAMING_MNGR_PERIODIC_SCAN_MAX_NUM_FRAMES_MIN       1
#define ROAMING_MNGR_PERIODIC_SCAN_MAX_NUM_FRAMES_MAX       30
#define ROAMING_MNGR_PERIODIC_SCAN_MAX_NUM_FRAMES_DEF       1

#define ROAMING_MNGR_PERIODIC_SCAN_NUM_PROBE_REQ_MIN        1
#define ROAMING_MNGR_PERIODIC_SCAN_NUM_PROBE_REQ_MAX        10
#define ROAMING_MNGR_PERIODIC_SCAN_NUM_PROBE_REQ_DEF        2

#define ROAMING_MNGR_OPERATIONAL_MODE_MIN       0 /* 0 - manual , 1 - auto*/
#define ROAMING_MNGR_OPERATIONAL_MODE_MAX       1
#define ROAMING_MNGR_OPERATIONAL_MODE_DEF       1


#define ROAMING_MNGR_SEND_TSPEC_IN_REASSO_PKT_MIN       0 /* 0 - do not send , 1 - send */
#define ROAMING_MNGR_SEND_TSPEC_IN_REASSO_PKT_MAX       1
#define ROAMING_MNGR_SEND_TSPEC_IN_REASSO_PKT_DEF       0


/*---------------------------
    Measurement parameters
-----------------------------*/

/* In ms */
#define MEASUREMENT_MAX_DUR_NON_SRV_CHANNEL_MIN 1
#define MEASUREMENT_MAX_DUR_NON_SRV_CHANNEL_MAX             1000
#define MEASUREMENT_MAX_DUR_NON_SRV_CHANNEL_DEF             300

/* In ms */
#define MEASUREMENT_MIN_TIME_BET_REQ_MIN                    0
#define MEASUREMENT_MIN_TIME_BET_REQ_MAX                    0xFFFF
#define MEASUREMENT_MIN_TIME_BET_REQ_DEF                    0

#define MEASUREMENT_XCC_ENABLE_MIN                          XCC_MNGR_ENABLE_MIN
#define MEASUREMENT_XCC_ENABLE_MAX                          XCC_MNGR_ENABLE_MAX
#define MEASUREMENT_XCC_ENABLE_DEF                          XCC_MNGR_ENABLE_DEF

#define MEASUREMENT_ONLY_SERVING_CHANNEL_MIN                0
#define MEASUREMENT_ONLY_SERVING_CHANNEL_MAX                1
#define MEASUREMENT_ONLY_SERVING_CHANNEL_DEF                0

/*---------------------------
      XCC Manager parameters
-----------------------------*/
#define XCC_MNGR_ENABLE_MIN             XCC_MODE_DISABLED
#define XCC_MNGR_ENABLE_MAX             XCC_MODE_STANDBY
#define XCC_MNGR_ENABLE_DEF             XCC_MODE_ENABLED

#define XCC_TEST_IGNORE_DEAUTH_0_DEF            1
#define XCC_TEST_IGNORE_DEAUTH_0_MIN            0
#define XCC_TEST_IGNORE_DEAUTH_0_MAX            1


/* 1 seconds */
#define CONN_SELF_TIMEOUT_MIN                   (1 * 1000)
/* 1 day */
#define CONN_SELF_TIMEOUT_MAX                   (60*60*24*1000)
/* 10 seconds */
#define CONN_SELF_TIMEOUT_DEF                   (10 * 1000)

#define AUTH_RESPONSE_TIMEOUT_MIN               100
#define AUTH_RESPONSE_TIMEOUT_MAX               5000
#define AUTH_RESPONSE_TIMEOUT_DEF               500

#define AUTH_MAX_RETRY_COUNT_MIN                1
#define AUTH_MAX_RETRY_COUNT_MAX                5
#define AUTH_MAX_RETRY_COUNT_DEF                5

#define ASSOC_RESPONSE_TIMEOUT_MIN              1000
#define ASSOC_RESPONSE_TIMEOUT_MAX              5000
#define ASSOC_RESPONSE_TIMEOUT_DEF              2000

#define ASSOC_MAX_RETRY_COUNT_MIN               1
#define ASSOC_MAX_RETRY_COUNT_MAX               5
#define ASSOC_MAX_RETRY_COUNT_DEF               5

#define RX_DATA_FILTERS_ENABLED_MIN             FALSE
#define RX_DATA_FILTERS_ENABLED_MAX             TRUE
#define RX_DATA_FILTERS_ENABLED_DEF             FALSE

#define RX_DATA_FILTERS_DEFAULT_ACTION_MIN      FILTER_DROP
#define RX_DATA_FILTERS_DEFAULT_ACTION_MAX      FILTER_FW_HANDLE
#define RX_DATA_FILTERS_DEFAULT_ACTION_DEF      FILTER_DROP

#define RX_DATA_FILTERS_FILTER_OFFSET_DEF       0
#define RX_DATA_FILTERS_FILTER_OFFSET_MIN       0
#define RX_DATA_FILTERS_FILTER_OFFSET_MAX       255

#define RX_DATA_FILTERS_FILTER_MASK_DEF         ""
#define RX_DATA_FILTERS_FILTER_MASK_LEN_DEF     0

#define RX_DATA_FILTERS_FILTER_PATTERN_DEF      ""
#define RX_DATA_FILTERS_FILTER_PATTERN_LEN_DEF  0

#define TX_DATA_CREDIT_CALC_TIMOEUT_DEF         100
#define TX_DATA_CREDIT_CALC_TIMOEUT_MIN         20
#define TX_DATA_CREDIT_CALC_TIMOEUT_MAX         1000

#define TRAFFIC_ADM_CONTROL_TIMEOUT_MIN         10
#define TRAFFIC_ADM_CONTROL_TIMEOUT_MAX         10000
#define TRAFFIC_ADM_CONTROL_TIMEOUT_DEF         5000

#define RATE_ADAPTATION_TIMEOUT_MIN             1
#define RATE_ADAPTATION_TIMEOUT_MAX             3600
#define RATE_ADAPTATION_TIMEOUT_DEF             300

#define RATE_ADAPT_HIGH_TRSH_AC_VO_MIN          0
#define RATE_ADAPT_HIGH_TRSH_AC_VO_MAX          54
#define RATE_ADAPT_HIGH_TRSH_AC_VO_DEF          0

#define RATE_ADAPT_HIGH_TRSH_AC_VI_MIN          0
#define RATE_ADAPT_HIGH_TRSH_AC_VI_MAX          54
#define RATE_ADAPT_HIGH_TRSH_AC_VI_DEF          0

#define RATE_ADAPT_HIGH_TRSH_AC_BE_MIN          0
#define RATE_ADAPT_HIGH_TRSH_AC_BE_MAX          54
#define RATE_ADAPT_HIGH_TRSH_AC_BE_DEF          0

#define RATE_ADAPT_HIGH_TRSH_AC_BK_MIN          0
#define RATE_ADAPT_HIGH_TRSH_AC_BK_MAX          54
#define RATE_ADAPT_HIGH_TRSH_AC_BK_DEF          0

#define RATE_ADAPT_LOW_TRSH_AC_VO_MIN           0
#define RATE_ADAPT_LOW_TRSH_AC_VO_MAX           54
#define RATE_ADAPT_LOW_TRSH_AC_VO_DEF           0

#define RATE_ADAPT_LOW_TRSH_AC_VI_MIN           0
#define RATE_ADAPT_LOW_TRSH_AC_VI_MAX           54
#define RATE_ADAPT_LOW_TRSH_AC_VI_DEF           0

#define RATE_ADAPT_LOW_TRSH_AC_BE_MIN           0
#define RATE_ADAPT_LOW_TRSH_AC_BE_MAX           54
#define RATE_ADAPT_LOW_TRSH_AC_BE_DEF           0

#define RATE_ADAPT_LOW_TRSH_AC_BK_MIN           0
#define RATE_ADAPT_LOW_TRSH_AC_BK_MAX           54
#define RATE_ADAPT_LOW_TRSH_AC_BK_DEF           0

#define RATE_POLICY_USER_SHORT_RETRY_LIMIT_MIN      1
#define RATE_POLICY_USER_SHORT_RETRY_LIMIT_MAX      255
#define RATE_POLICY_USER_SHORT_RETRY_LIMIT_DEF      10           /* in case packet size is under RTS threshold */

#define RATE_POLICY_USER_LONG_RETRY_LIMIT_MIN       1
#define RATE_POLICY_USER_LONG_RETRY_LIMIT_MAX       255
#define RATE_POLICY_USER_LONG_RETRY_LIMIT_DEF       10           /* in case packet size is over RTS threshold */

#define RATE_POLICY_USER_EN_DIS_MASK_MIN            0
#define RATE_POLICY_USER_EN_DIS_MASK_MAX            0x001FFFFF

#define RATE_POLICY_USER_BITMASK_AC_BK          RATE_POLICY_USER_EN_DIS_MASK_MAX
#define RATE_POLICY_USER_BITMASK_AC_BE          RATE_POLICY_USER_EN_DIS_MASK_MAX
#define RATE_POLICY_USER_BITMASK_AC_VI          RATE_POLICY_USER_EN_DIS_MASK_MAX
#define RATE_POLICY_USER_BITMASK_AC_VO          RATE_POLICY_USER_EN_DIS_MASK_MAX
#define RATE_POLICY_USER_BITMASK_MGMT           0x27 /* rates 1, 2, 5.5, 6 */

#define REPORT_SEVERITY_VALUE_MIN               0
#define REPORT_SEVERITY_VALUE_MAX               0xFF
/* WLAN_SEVERITY_WARNING | WLAN_SEVERITY_ERROR | WLAN_SEVERITY_FATAL_ERROR | WLAN_SEVERITY_CONSOLE */
#define REPORT_SEVERITY_VALUE_DEF               0xB8

#define RSN_AUTH_SUITE_MIN                      RSN_AUTH_OPEN
#define RSN_AUTH_SUITE_MAX                      RSN_AUTH_NONE
#define RSN_AUTH_SUITE_DEF                      RSN_AUTH_OPEN

/* 1 sec */
#define RSN_PMKSA_LIFETIME_MIN                  1
/* 49 days in sec */
#define RSN_PMKSA_LIFETIME_MAX                  4233600
/* 1 day in sec */
#define RSN_PMKSA_LIFETIME_DEF                  86400

#define RSN_WEP_STATUS_MIN                      0
#define RSN_WEP_STATUS_MAX                      1
#define RSN_WEP_STATUS_DEF                      0

#define RSN_WEPMIXEDMODE_ENABLED_MIN                    0
#define RSN_WEPMIXEDMODE_ENABLED_MAX                    1
#define RSN_WEPMIXEDMODE_ENABLED_DEF                    0

#define RSN_WPAMIXEDMODE_ENABLE_MIN             0
#define RSN_WPAMIXEDMODE_ENABLE_MAX             1
#define RSN_WPAMIXEDMODE_ENABLE_DEF             1

/* In mSec units */
#define RSN_PREAUTH_TIMEOUT_MIN                  500
#define RSN_PREAUTH_TIMEOUT_MAX                  60000
#define RSN_PREAUTH_TIMEOUT_DEF                 2000

#define PAIRWISE_MIC_FAIL_FILTER_MIN            0
#define PAIRWISE_MIC_FAIL_FILTER_MAX            1
#define PAIRWISE_MIC_FAIL_FILTER_DEF            1

#define  RSN_PMKIDCANDLIST_DELAY_MIN            3000
#define  RSN_PMKIDCANDLIST_DELAY_MAX            9000
#define  RSN_PMKIDCANDLIST_DELAY_DEF            4000

#define RSN_EXTERNAL_MODE_ENABLE_MIN            0
#define RSN_EXTERNAL_MODE_ENABLE_MAX            1
#define RSN_EXTERNAL_MODE_ENABLE_DEF            0


#define ETHER_MAX_PAYLOAD_SIZE            1500

/* SME Values */
#define SME_SCAN_RSSI_THRESHOLD_MIN             -100
#define SME_SCAN_RSSI_THRESHOLD_MAX             0
#define SME_SCAN_RSSI_THRESHOLD_DEF             "-90"
#define SME_SCAN_RSSI_THRESHOLD_DEF_NUM         -90

#define SME_SCAN_SNR_THRESHOLD_MIN              -5
#define SME_SCAN_SNR_THRESHOLD_MAX              20
#define SME_SCAN_SNR_THRESHOLD_DEF              "0"
#define SME_SCAN_SNR_THRESHOLD_DEF_NUM          0

#define SME_SCAN_CYCLES_MIN                     0
#define SME_SCAN_CYCLES_MAX                     100
#define SME_SCAN_CYCLES_DEF                     50

#define SME_SCAN_MAX_DWELL_MIN                  5     /* in milli-seconds */
#define SME_SCAN_MAX_DWELL_MAX                  500
#define SME_SCAN_MAX_DWELL_DEF                  60

#define SME_SCAN_MIN_DWELL_MIN                  5     /* in milli-seconds */
#define SME_SCAN_MIN_DWELL_MAX                  500
#define SME_SCAN_MIN_DWELL_DEF                  30

#define SME_SCAN_PROBE_REQ_MIN                  1
#define SME_SCAN_PROBE_REQ_MAX                  10
#define SME_SCAN_PROBE_REQ_DEF                  2

#define SME_SCAN_INTERVALS_LIST_VAL_DEF         "0,1000,2000,3000,4000,8000,16000,32000,64000,128000,256000,512000,512000,512000,512000,512000"
#define SME_SCAN_INTERVALS_LIST_STRING_MAX_SIZE 255

#define SME_SCAN_CHANNELS_LIST_G_VAL_DEF        "1,2,3,4,5,6,7,8,9,10,11,12,13,14"
#define SME_SCAN_CHANNELS_LIST_G_STRING_MAX_SIZE 255

#define SME_SCAN_CHANNELS_LIST_A_VAL_DEF        "36,40,44,48,52,56,60,64"
#define SME_SCAN_CHANNELS_LIST_A_STRING_MAX_SIZE 255


/*
  EEPROM-less support
*/
#define REG_MAC_ADDR_STR_LEN                    17
#define REG_ARP_IP_ADDR_STR_LEN                 11
#define REG_MAC_ADDR_PREAMBLE_STR_LEN           9

#define TWD_EEPROMLESS_ENABLE_DEF               1
#define TWD_EEPROMLESS_ENABLE_MIN               0
#define TWD_EEPROMLESS_ENABLE_MAX               1

/* Scanning Channel Values */
#define MAX_CHAN_BITMAP_BYTES                   26

#define MIN_CHANNEL_IN_BAND_2_4                  1
#define MAX_CHANNEL_IN_BAND_2_4                 14

#define SCAN_CONTROL_TABLE_ENTRY_MIN            0x00
#define SCAN_CONTROL_TABLE_ENTRY_MAX            0xff
#define SCAN_CONTROL_TABLE_ENTRY_DEF            0xff

/* country code reset time out */
/* 1 sec   */
#define REGULATORY_DOMAIN_COUNTRY_TIME_RESET_MIN     1000
/* 1 day */
#define REGULATORY_DOMAIN_COUNTRY_TIME_RESET_MAX     86400000
/* 1 minutes  */
#define REGULATORY_DOMAIN_COUNTRY_TIME_RESET_DEF     60000

/* d/h Enabling */

/* Passive scan for Japan channels*/
#define JAPAN_CHANNELS_ENABLED_MIN         FALSE
#define JAPAN_CHANNELS_ENABLED_MAX         TRUE
#define JAPAN_CHANNELS_ENABLED_DEF         TRUE

/* Tx Power table (Power level to Dbm)*/
#define TX_POWER_LEVEL_TABLE_24                 "21,13,10,7"
#define TX_POWER_LEVEL_TABLE_5                  "20,12,9,6"

#define SCAN_CNCN_REGULATORY_DOMAIN_PASSIVE_DWELL_TIME_DEF    150

#define SCAN_CNCN_DFS_PASSIVE_DWELL_TIME_DEF    150
#define SCAN_CNCN_DFS_PASSIVE_DWELL_TIME_MIN    10
#define SCAN_CNCN_DFS_PASSIVE_DWELL_TIME_MAX    500

#define SCAN_CNCN_APP_PUSH_MODE_DEF             FALSE
#define SCAN_CNCN_APP_PUSH_MODE_MIN             FALSE
#define SCAN_CNCN_APP_PUSH_MODE_MAX             TRUE

#define SCAN_CNCN_APP_SRA_DEF                   60
#define SCAN_CNCN_APP_SRA_MIN                   0
#define SCAN_CNCN_APP_SRA_MAX                   1000

#define SCAN_CNCN_RSSI_DEF                      (-100)
#define SCAN_CNCN_RSSI_MIN                      (-100)
#define SCAN_CNCN_RSSI_MAX                      0


#define SCAN_OID_DEFAULT_MAX_DWELL_TIME_PASSIVE_G                   110
#define SCAN_OID_DEFAULT_MAX_DWELL_TIME_PASSIVE_A                   110
#define SCAN_OID_DEFAULT_MIN_DWELL_TIME_PASSIVE_G                   110
#define SCAN_OID_DEFAULT_MIN_DWELL_TIME_PASSIVE_A                   110
#define SCAN_OID_DEFAULT_MAX_DWELL_TIME_ACTIVE_G                    50
#define SCAN_OID_DEFAULT_MAX_DWELL_TIME_ACTIVE_A                    50
#define SCAN_OID_DEFAULT_MIN_DWELL_TIME_ACTIVE_G                    25
#define SCAN_OID_DEFAULT_MIN_DWELL_TIME_ACTIVE_A                    25

/* Current BSS init paramaters - keep alive default interval */
#define NULL_KL_PERIOD_DEF      10
#define NULL_KL_PERIOD_MIN      0
#define NULL_KL_PERIOD_MAX      3600

/* WSC */
#define WSC_PARSE_IN_BEACON_DEF 1
#define WSC_PARSE_IN_BEACON_MIN 0
#define WSC_PARSE_IN_BEACON_MAX 1

#define WSC_INCLUDE_IN_BEACON_DEF 1
#define WSC_INCLUDE_IN_BEACON_MIN 0
#define WSC_INCLUDE_IN_BEACON_MAX 1


/* Packet Filtering Define */
#define MIN_NUM_OF_BEACONS_IN_BUFFER 1
#define DEF_NUM_OF_BEACONS_IN_BUFFER 5
#define MAX_NUM_OF_BEACONS_IN_BUFFER 10

/* Soft Gemini Enabling */
#define SG_ENABLE TRUE
#define SG_DISABLE FALSE

#define SOFT_GEMINI_ENABLED_MIN                 SG_DISABLE
#define SOFT_GEMINI_ENABLED_MAX                 SG_ENABLE
#define SOFT_GEMINI_ENABLED_DEF                 SG_ENABLE

#define SOFT_GEMINI_PARAMS_INDEX_MIN            0
#define SOFT_GEMINI_PARAMS_INDEX_MAX            (SOFT_GEMINI_PARAMS_MAX-1)
#define SOFT_GEMINI_PARAMS_INDEX_DEF            0

#define SOFT_GEMINI_PARAMS_VALUE_MIN            0
#define SOFT_GEMINI_PARAMS_VALUE_MAX            10000000
#define SOFT_GEMINI_PARAMS_VALUE_DEF            0

/****************************************New Coex params**************************************/

#define SOFT_GEMINI_UNUSED_VALUE                        0

#define SOFT_GEMINI_CONSECUTIVE_CTS_THERSHOLD_MIN       0
#define SOFT_GEMINI_CONSECUTIVE_CTS_THERSHOLD_MAX       50
#define SOFT_GEMINI_CONSECUTIVE_CTS_THERSHOLD_DEF       2

#define SOFT_GEMINI_STA_CONNECTION_PROTECTION_TIME_MIN       0
#define SOFT_GEMINI_STA_CONNECTION_PROTECTION_TIME_MAX       5000
#define SOFT_GEMINI_STA_CONNECTION_PROTECTION_TIME_DEF       30

#define SOFT_GEMINI_AP_BEACON_MISS_TX_MIN       0
#define SOFT_GEMINI_AP_BEACON_MISS_TX_MAX       255
#define SOFT_GEMINI_AP_BEACON_MISS_TX_DEF       3

#define SOFT_GEMINI_AP_CONNECTION_PROTECTION_TIME_MIN       0
#define SOFT_GEMINI_AP_CONNECTION_PROTECTION_TIME_MAX       5000
#define SOFT_GEMINI_AP_CONNECTION_PROTECTION_TIME_DEF       0

#define SOFT_GEMINI_AP_BEACON_WINDOW_INTERVAL_DURING_PAGE_INQUIRY_MIN       0
#define SOFT_GEMINI_AP_BEACON_WINDOW_INTERVAL_DURING_PAGE_INQUIRY_MAX       255
#define SOFT_GEMINI_AP_BEACON_WINDOW_INTERVAL_DURING_PAGE_INQUIRY_DEF       2



#define SOFT_GEMINI_AUTO_SCAN_PROBE_REQ_MIN             0
#define SOFT_GEMINI_AUTO_SCAN_PROBE_REQ_MAX             255
#define SOFT_GEMINI_AUTO_SCAN_PROBE_REQ_DEF             170

#define SOFT_GEMINI_ACTIVE_SCAN_DURATION_FACTOR_HV3_MIN     0
#define SOFT_GEMINI_ACTIVE_SCAN_DURATION_FACTOR_HV3_MAX     255
#define SOFT_GEMINI_ACTIVE_SCAN_DURATION_FACTOR_HV3_DEF     50

#define SOFT_GEMINI_PASSIVE_SCAN_DURATION_FACTOR_HV3_MIN        0
#define SOFT_GEMINI_PASSIVE_SCAN_DURATION_FACTOR_HV3_MAX        1000
#define SOFT_GEMINI_PASSIVE_SCAN_DURATION_FACTOR_HV3_DEF        200

#define SOFT_GEMINI_CONSECUTIVE_HV3_IN_PASSIVE_SCAN_MIN         0
#define SOFT_GEMINI_CONSECUTIVE_HV3_IN_PASSIVE_SCAN_MAX         255
#define SOFT_GEMINI_CONSECUTIVE_HV3_IN_PASSIVE_SCAN_DEF         0

#define SOFT_GEMINI_BEACON_HV3_COLLISION_THRESHOLD_IN_PASSIVE_SCAN_MIN  0
#define SOFT_GEMINI_BEACON_HV3_COLLISION_THRESHOLD_IN_PASSIVE_SCAN_MAX  1000
#define SOFT_GEMINI_BEACON_HV3_COLLISION_THRESHOLD_IN_PASSIVE_SCAN_DEF  0

#define SOFT_GEMINI_TX_RX_PROTECTION_BANDWITH_IN_PASSIVE_SCAN_MIN        0
#define SOFT_GEMINI_TX_RX_PROTECTION_BANDWITH_IN_PASSIVE_SCAN_MAX        79
#define SOFT_GEMINI_TX_RX_PROTECTION_BANDWITH_IN_PASSIVE_SCAN_DEF        0

#define SOFT_GEMINI_STA_FORCE_PS_IN_BT_SCO_MIN                                     0
#define SOFT_GEMINI_STA_FORCE_PS_IN_BT_SCO_MAX                                     1
#define SOFT_GEMINI_STA_FORCE_PS_IN_BT_SCO_DEF                                     1

#define SOFT_GEMINI_ANTENNA_CONFIGURATION_MIN                            0
#define SOFT_GEMINI_ANTENNA_CONFIGURATION_MAX                            1
#define SOFT_GEMINI_ANTENNA_CONFIGURATION_DEF                            0

#define SOFT_GEMINI_BEACON_MISS_PERCENT_MIN                              0
#define SOFT_GEMINI_BEACON_MISS_PERCENT_MAX                              100
#define SOFT_GEMINI_BEACON_MISS_PERCENT_DEF                              60

#define SOFT_GEMINI_RXT_MIN                                              0
#define SOFT_GEMINI_RXT_MAX                                              100000
#define SOFT_GEMINI_RXT_DEF                                              1200

#define SOFT_GEMINI_ADAPTIVE_RXT_TXT_MIN                                 0
#define SOFT_GEMINI_ADAPTIVE_RXT_TXT_MAX                                 1
#define SOFT_GEMINI_ADAPTIVE_RXT_TXT_DEF                                 1

#define SOFT_GEMINI_GENERAL_USAGE_BITMAP_MIN                             0
#define SOFT_GEMINI_GENERAL_USAGE_BITMAP_MAX                             255
#define SOFT_GEMINI_GENERAL_USAGE_BITMAP_DEF                             3

#define SOFT_GEMINI_HV3_MAX_SERVED_MIN                                   0
#define SOFT_GEMINI_HV3_MAX_SERVED_MAX                                   100
#define SOFT_GEMINI_HV3_MAX_SERVED_DEF                                   6

#define SOFT_GEMINI_CTS_DILUTED_BAD_RX_PACKETS_TH_MIN                    0
#define SOFT_GEMINI_CTS_DILUTED_BAD_RX_PACKETS_TH_MAX                    96
#define SOFT_GEMINI_CTS_DILUTED_BAD_RX_PACKETS_TH_DEF                    0

#define SOFT_GEMINI_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER_MIN                  0
#define SOFT_GEMINI_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER_MAX                  1000
#define SOFT_GEMINI_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER_DEF                  0

#define SOFT_GEMINI_ZIGBEE_COEX_MIN                                      0
#define SOFT_GEMINI_ZIGBEE_COEX_MAX                                      1
#define SOFT_GEMINI_ZIGBEE_COEX_DEF                                      0

#define SOFT_GEMINI_TEMP_PARAM_2_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_2_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_2_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_3_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_3_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_3_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_4_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_4_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_4_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_5_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_5_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_5_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_6_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_6_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_6_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_7_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_7_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_7_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_8_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_8_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_8_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_9_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_9_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_9_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_10_MIN                                     0
#define SOFT_GEMINI_TEMP_PARAM_10_MAX                                     100000
#define SOFT_GEMINI_TEMP_PARAM_10_DEF                                     0

#define SOFT_GEMINI_TEMP_PARAM_MIN      0
#define SOFT_GEMINI_TEMP_PARAM_MAX      0xFFFFFFFF
#define SOFT_GEMINI_TEMP_PARAM_DEF      0

#define SOFT_GEMINI_TEMP6_PARAM_DEF     1

/*****************************************************************************************/

/* FM Coexistence */
#define FM_COEX_ENABLE_DEF                             TRUE
#define FM_COEX_ENABLE_MIN                             FALSE
#define FM_COEX_ENABLE_MAX                             TRUE

#define FM_COEX_SWALLOW_PERIOD_DEF                     5
#define FM_COEX_SWALLOW_PERIOD_MIN                     0
#define FM_COEX_SWALLOW_PERIOD_MAX                     0xFF

#define FM_COEX_N_DIVIDER_FREF_SET1_DEF                0xFF
#define FM_COEX_N_DIVIDER_FREF_SET1_MIN                0
#define FM_COEX_N_DIVIDER_FREF_SET1_MAX                0xFF

#define FM_COEX_N_DIVIDER_FREF_SET2_DEF                12
#define FM_COEX_N_DIVIDER_FREF_SET2_MIN                0
#define FM_COEX_N_DIVIDER_FREF_SET2_MAX                0xFF

#define FM_COEX_M_DIVIDER_FREF_SET1_DEF                148
#define FM_COEX_M_DIVIDER_FREF_SET1_MIN                0
#define FM_COEX_M_DIVIDER_FREF_SET1_MAX                0xFFFF

#define FM_COEX_M_DIVIDER_FREF_SET2_DEF                0xFFFF
#define FM_COEX_M_DIVIDER_FREF_SET2_MIN                0
#define FM_COEX_M_DIVIDER_FREF_SET2_MAX                0xFFFF

#define FM_COEX_PLL_STABILIZATION_TIME_DEF             0xFFFFFFFF
#define FM_COEX_PLL_STABILIZATION_TIME_MIN             0
#define FM_COEX_PLL_STABILIZATION_TIME_MAX             0xFFFFFFFF

#define FM_COEX_LDO_STABILIZATION_TIME_DEF             0xFFFF
#define FM_COEX_LDO_STABILIZATION_TIME_MIN             0
#define FM_COEX_LDO_STABILIZATION_TIME_MAX             0xFFFF

#define FM_COEX_DISTURBED_BAND_MARGIN_DEF              0xFF
#define FM_COEX_DISTURBED_BAND_MARGIN_MIN              0
#define FM_COEX_DISTURBED_BAND_MARGIN_MAX              0xFF

#define FM_COEX_SWALLOW_CLK_DIF_DEF                    0xFF
#define FM_COEX_SWALLOW_CLK_DIF_MIN                    0
#define FM_COEX_SWALLOW_CLK_DIF_MAX                    0xFF


#define STA_CAPABILITY_RRM_ENABLED_DEF       1
#define STA_CAPABILITY_RRM_ENABLED_MIN       0
#define STA_CAPABILITY_RRM_ENABLED_MAX       1

/* 40MHz support */
#define STA_CAPABILITY_40MHZ_ENABLED_DEF     1
#define STA_CAPABILITY_40MHZ_ENABLED_MIN     0
#define STA_CAPABILITY_40MHZ_ENABLED_MAX     1

/* MIMO support */
#define STA_CAPABILITY_MIMO_ENABLED_DEF     0
#define STA_CAPABILITY_MIMO_ENABLED_MIN     0
#define STA_CAPABILITY_MIMO_ENABLED_MAX     1

#define ROLE_AP_BEACON_TX_TIMEOUT_DEF       20
#define ROLE_AP_BEACON_TX_TIMEOUT_MIN       0
#define ROLE_AP_BEACON_TX_TIMEOUT_MAX       255

#define ROLE_AP_CAC_TIME_DEF                60  /* 1 minute in seconds */
#define ROLE_AP_CAC_TIME_MIN                0
#define ROLE_AP_CAC_TIME_MAX                0xFFFF

#define ROLE_AP_NOP_TIME_DEF                1800 /* 30 minutes in seconds */
#define ROLE_AP_NOP_TIME_MIN                0
#define ROLE_AP_NOP_TIME_MAX                0xFFFF



/* Configurable Scan Rate */
#define SCAN_RATE_MODE_B_MIN                    DRV_RATE_1M
#define SCAN_RATE_MODE_B_MAX                    DRV_RATE_11M
#define SCAN_RATE_MODE_B_DEF                    DRV_RATE_2M

#define SCAN_RATE_MODE_G_MIN                    DRV_RATE_1M
#define SCAN_RATE_MODE_G_MAX                    DRV_RATE_54M
#define SCAN_RATE_MODE_G_DEF                    DRV_RATE_2M

#define SCAN_RATE_MODE_A_MIN                    DRV_RATE_6M
#define SCAN_RATE_MODE_A_MAX                    DRV_RATE_54M
#define SCAN_RATE_MODE_A_DEF                    DRV_RATE_6M

/* Probe request number during scan */
#define SCAN_PROBE_REQ_NUMBER_MIN   1
#define SCAN_PROBE_REQ_NUMBER_MAX   7
#define SCAN_PROBE_REQ_NUMBER_DEF   3


#define ACX_64BITS_WEP_KEY_LENGTH_BYTES         5
#define ACX_128BITS_WEP_KEY_LENGTH_BYTES        13
#define ACX_256BITS_WEP_KEY_LENGTH_BYTES        29
#define ACX_MAX_WEP_KEY_LENGTH_BYTES            29


/*
 * Driver-Main parameters values
 */
/* Set WLAN driver thread priority - Note that this is an OS dependent parameter! */
#define WLAN_DRV_THREAD_PRIORITY_MIN                        0
#define WLAN_DRV_THREAD_PRIORITY_MAX                        255
#define WLAN_DRV_THREAD_PRIORITY_DEF                        251

/* Set bus driver thread priority - Note that this is an OS dependent parameter! */
#define BUS_DRV_THREAD_PRIORITY_MIN                         0
#define BUS_DRV_THREAD_PRIORITY_MAX                         255
#define BUS_DRV_THREAD_PRIORITY_DEF                         251

/* In SDIO block-mode:  BlkSize = 1 << BlkSizeShift    (current block size is: 1<<8 = 256 bytes) */
#define SDIO_BLK_SIZE_SHIFT_MIN                             0
#define SDIO_BLK_SIZE_SHIFT_MAX                             16
#define SDIO_BLK_SIZE_SHIFT_DEF                             8


/* Health monitor recovery enable/disable */
#define HEALTH_RECOVERY_ENABLE_MIN         FALSE
#define HEALTH_RECOVERY_ENABLE_MAX         TRUE
#define HEALTH_RECOVERY_ENABLE_DEF         TRUE

/* RTS Threshold */
#define RTS_THRESHOLD_MIN           0
#define RTS_THRESHOLD_MAX           4096
#define RTS_THRESHOLD_DEF           4096

#define LISTEN_INTERVAL_MIN         1
#define LISTEN_INTERVAL_MAX         10
#define LISTEN_INTERVAL_DEF         3

#define RSSI_BEACON_WEIGHT_MIN       0
#define RSSI_BEACON_WEIGHT_MAX     100
#define RSSI_BEACON_WEIGHT_DEF      20

#define RSSI_PACKET_WEIGHT_MIN       0
#define RSSI_PACKET_WEIGHT_MAX     100
#define RSSI_PACKET_WEIGHT_DEF      10

#define SNR_BEACON_WEIGHT_MIN        0
#define SNR_BEACON_WEIGHT_MAX      100
#define SNR_BEACON_WEIGHT_DEF       20

#define SNR_PACKET_WEIGHT_MIN        0
#define SNR_PACKET_WEIGHT_MAX      100
#define SNR_PACKET_WEIGHT_DEF       10

/*****************************************************************************
 **         POWER MANAGER MODULE REGISTRY DEFINITIONS                       **
 *****************************************************************************/

typedef enum
{
  POWER_SAVE_SHORT_DOZE,  /**< In this mode the system is going to ELP state and awakes (by the
                             * FW) every beacon. The F/W wakes up the host on every Beacon passes
                             * the Beacon to the driver and returns to ELP Doze as soon as possible.
                             */

  POWER_SAVE_LONG_DOZE,    /**< In this mode the system is going to ELP state and awakes (by the
                             * FW) every DTIM or listen interval. This mode consumes low power,
                             * while still waking-up for Beacons once in a while. The system spends
                             * a lot of time in ELP-Doze, and the F/W rarely wakes up the host.
                             */
  POWER_SAVE_MAX
}PowerMgr_PowerSaveDozeMode_e;


enum PowerMgr_registryDefinitions
{
    POWER_MODE_MIN_VALUE = STATION_AUTO_PS_MODE,
    POWER_MODE_MAX_VALUE = STATION_POWER_SAVE_MODE,
    POWER_MODE_DEF_VALUE = STATION_AUTO_PS_MODE,

    POWER_SAVE_DOZE_MODE_MIN_VALUE = POWER_SAVE_SHORT_DOZE,
    POWER_SAVE_DOZE_MODE_MAX_VALUE = POWER_SAVE_LONG_DOZE,
    POWER_SAVE_DOZE_MODE_DEF_VALUE = POWER_SAVE_SHORT_DOZE,

    DPS_TIMEOUT_MIN_VALUE = 0,
    DPS_TIMEOUT_MAX_VALUE = 1500,
    DPS_TIMEOUT_DEF_VALUE = 1500,

    BEACON_RECEIVE_TIME_MIN_VALUE = 10,
    BEACON_RECEIVE_TIME_MAX_VALUE = 1000,
    BEACON_RECEIVE_TIME_DEF_VALUE = 50,

    BASE_BAND_WAKE_UP_TIME_MIN_VALUE = 100,      /* in micro seconds */
    BASE_BAND_WAKE_UP_TIME_MAX_VALUE = 10000,
    BASE_BAND_WAKE_UP_TIME_DEF_VALUE = 2000,

    PLL_LOCK_TIME_MIN_VALUE = 500,
    PLL_LOCK_TIME_MAX_VALUE = 20000,
    PLL_LOCK_TIME_DEF_VALUE = 4000,

    BEACON_LISTEN_INTERVAL_MIN_VALUE = 1,
    BEACON_LISTEN_INTERVAL_MAX_VALUE = 50,
    BEACON_LISTEN_INTERVAL_DEF_VALUE = 1,

    DTIM_LISTEN_INTERVAL_MIN_VALUE = 1,
    DTIM_LISTEN_INTERVAL_MAX_VALUE = 50,
    DTIM_LISTEN_INTERVAL_DEF_VALUE = 1,

    BEACON_FILTERING_MIN_VALUE = 0,
    BEACON_FILTERING_MAX_VALUE = 30,
    BEACON_FILTERING_DEF_VALUE = 10,

    N_CONSECUTIVE_BEACONS_MISSED_MIN_VALUE = 0,
    N_CONSECUTIVE_BEACONS_MISSED_MAX_VALUE = 50,
    N_CONSECUTIVE_BEACONS_MISSED_DEF_VALUE = 1,

    DCO_ITRIM_ENABLE_MIN = FALSE,
    DCO_ITRIM_ENABLE_MAX = TRUE,
    DCO_ITRIM_ENABLE_DEF = FALSE,

    DCO_ITRIM_MODERATION_TIMEOUT_MIN = 10000,
    DCO_ITRIM_MODERATION_TIMEOUT_MAX = 1000000,
    DCO_ITRIM_MODERATION_TIMEOUT_DEF = 50000,

    POWER_MGMNT_MODE_DEF_VALUE = 1,
    POWER_MGMNT_MODE_MIN_VALUE = 0,
    POWER_MGMNT_MODE_MAX_VALUE = 1,

    POWER_MGMNT_NEED_TO_SEND_NULL_PACKET_DEF_VALUE = 1,
    POWER_MGMNT_NEED_TO_SEND_NULL_PACKET_MIN_VALUE = 0,
    POWER_MGMNT_NEED_TO_SEND_NULL_PACKET_MAX_VALUE = 1,

    /*
     bit14 - "1" send Prob Request in PBCC
     bit15 - "1" short preamble, "0" long preammle
     bit0:bit12  Rates
     */
    POWER_MGMNT_NULL_PACKET_RATE_MOD_DEF_VALUE =  ((DRV_RATE_MASK_1_BARKER) | (DRV_RATE_MASK_2_BARKER)),
    POWER_MGMNT_NULL_PACKET_RATE_MOD_MIN_VALUE = 0,
    POWER_MGMNT_NULL_PACKET_RATE_MOD_MAX_VALUE = 255 ,

    POWER_MGMNT_NUM_NULL_PACKET_ENTER_RETRY_DEF_VALUE = 8,
    POWER_MGMNT_NUM_NULL_PACKET_ENTER_RETRY_MIN_VALUE = 1,
    POWER_MGMNT_NUM_NULL_PACKET_ENTER_RETRY_MAX_VALUE = 255,

    POWER_MGMNT_NUM_NULL_PACKET_EXIT_RETRY_DEF_VALUE = 16,
    POWER_MGMNT_NUM_NULL_PACKET_EXIT_RETRY_MIN_VALUE = 1,
    POWER_MGMNT_NUM_NULL_PACKET_EXIT_RETRY_MAX_VALUE = 255,

    HANGOVER_PERIOD_MIN_VALUE = 1,
    HANGOVER_PERIOD_MAX_VALUE = 128,
    HANGOVER_PERIOD_DEF_VALUE = 20,

    DYNAMIC_HANGOVER_MODE_MIN_VALUE = 0,
    DYNAMIC_HANGOVER_MODE_MAX_VALUE = 1,
    DYNAMIC_HANGOVER_MODE_DEF_VALUE = 1,

    EARLY_TERMINATION_MODE_MIN_VALUE = 0,
    EARLY_TERMINATION_MODE_MAX_VALUE = 1,
    EARLY_TERMINATION_MODE_DEF_VALUE = 1,

    PS_RECOVER_TIME_MIN_VALUE = 0,
    PS_RECOVER_TIME_MAX_VALUE = 120000,
    PS_RECOVER_TIME_DEF_VALUE = 0,

    PS_MAX_HANG_OVER_PERIOD_MIN_VALUE = 1,
    PS_MAX_HANG_OVER_PERIOD_MAX_VALUE = 128,
    PS_MAX_HANG_OVER_PERIOD_DEF_VALUE = 20,

    PS_MIN_HANG_OVER_PERIOD_MIN_VALUE = 1,
    PS_MIN_HANG_OVER_PERIOD_MAX_VALUE = 128,
    PS_MIN_HANG_OVER_PERIOD_DEF_VALUE = 1,

    PS_INCR_DELTA_TIME_FROM_HANG_OVER_MIN_VALUE = 1,
    PS_INCR_DELTA_TIME_FROM_HANG_OVER_MAX_VALUE = 128,
    PS_INCR_DELTA_TIME_FROM_HANG_OVER_DEF_VALUE = 1,

    PS_DECR_DELTA_TIME_FROM_HANG_OVER_MIN_VALUE = 2,
    PS_DECR_DELTA_TIME_FROM_HANG_OVER_MAX_VALUE = 128,
    PS_DECR_DELTA_TIME_FROM_HANG_OVER_DEF_VALUE = 2,

    PS_QUIET_TIME_FOR_EARLY_TERMINATION_MIN_VALUE = 1,
    PS_QUIET_TIME_FOR_EARLY_TERMINATION_MAX_VALUE = 128,
    PS_QUIET_TIME_FOR_EARLY_TERMINATION_DEF_VALUE = 4,

    PS_INCREASE_HANG_OVER_TIME_MIN_VALUE = 1,
    PS_INCREASE_HANG_OVER_TIME_MAX_VALUE = 128,
    PS_INCREASE_HANG_OVER_TIME_DEF_VALUE = 0,

    PS_SLIDING_WINDOW_SIZE_MIN_VALUE = 1,
    PS_SLIDING_WINDOW_SIZE_MAX_VALUE = 128,
    PS_SLIDING_WINDOW_SIZE_DEF_VALUE = 0,

    POWER_MGMNT_RE_AUTH_ACTIVE_PRIO_DEF_VALUE = 1,
    POWER_MGMNT_RE_AUTH_ACTIVE_PRIO_MIN_VALUE = 0,
    POWER_MGMNT_RE_AUTH_ACTIVE_PRIO_MAX_VALUE = 1,

    /*BET*/
    POWER_MGMNT_BET_ENABLE_MIN = 0,
    POWER_MGMNT_BET_ENABLE_MAX = 1,
    POWER_MGMNT_BET_ENABLE_DEF = 1,
    POWER_MGMNT_BET_MAX_CONSC_MIN = 1,
    POWER_MGMNT_BET_MAX_CONSC_MAX = 50,
    POWER_MGMNT_BET_MAX_CONSC_DEF = 8,

/*--------------- Maximal time between full beacon reception ------------------*/
    POWER_MGMNT_MAX_FULL_BEACON_MIN = 0,
    POWER_MGMNT_MAX_FULL_BEACON_MAX = 10000,
    POWER_MGMNT_MAX_FULL_BEACON_DEF = 5000,

    HOST_CLK_SETTLE_TIME_USEC_MIN = 0,
    HOST_CLK_SETTLE_TIME_USEC_MAX = 30000,
    HOST_CLK_SETTLE_TIME_USEC_DEF = 5000,

    HOST_FAST_WAKE_SUPPORT_MIN = 0,
    HOST_FAST_WAKE_SUPPORT_MAX = 1,
    HOST_FAST_WAKE_SUPPORT_DEF = 0
};



#endif /* _CORE_DEFAULT_PARAMS_H */


