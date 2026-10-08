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
/** \file  TWDriver.h
 *  \brief TWDriver APIs
 *
 *  \see
 */

/** @defgroup Control Control group
 * \brief The Control group includes the list of functions which perform TWD Control
 */
/** @defgroup Measurement Measurement group
 * \brief The Measurement group includes the list of functions which gets measurements from FW / TWD
 */
/** @defgroup Data_Path Data Path group
 * \brief The Data Path group includes the list of functions which perform the TWD Data Path
 */
/** @defgroup Power_Management Power Management group
 * \brief The Power Management group includes the list of functions which set the power management mode
 */
/** @defgroup QoS Quality  Of Service group
 * \brief The Quality of Service group includes the list of functions which perform the TWD QoS
 */
/** @defgroup Radio Radio (PHY) group
 * \brief The Radio group includes the list of functions which handle the Radio
 */
/** @defgroup BSS BSS group
 * \brief The BSS group includes the list of functions which handle the Basic Service Set
 */
/** @defgroup Misc Miscellaneous group
 * \brief The Miscellaneous group includes the list of functions which handle miscellaneous issues
 */
#ifdef TI_DBG
/** @defgroup Test Debug Test group
 * \brief The Debug Test group includes the list of functions which Test the TWD and FW
 */
#endif

#ifndef TWDRIVER_H
#define TWDRIVER_H

//#include "osi.h"
#include "txn_defs.h"
#include <trnspt_thread.h>
#include "public_types.h"
#include "public_share.h"
#include "timer.h"
#include "802_11defs.h"
#include "ti_qos_types.h"
#include "txn_bus_drv.h"
#include "cc3xxx_public_types.h"


/* new */
/*TI Wilnk Driver network interface indices*/


/*TI Wilnk Driver possible role types (modes)*/
typedef enum
{
	TIWDRV_IF_MODE_SYS,
	TIWDRV_IF_MODE_STA,
    TIWDRV_IF_MODE_SAP,
    TIWDRV_IF_MODE_P2PDEV,
    TIWDRV_IF_MODE_P2PCL,
    TIWDRV_IF_MODE_P2PGO,
    TIWDRV_IF_MODE_IBSS,
    TIWDRV_IF_MODE_NETMON,
	TIWDRV_IF_MODE_MAX,
	TIWDRV_IF_MODE_UNKNOWN
} tiwdrv_if_mode_e;

/** \struct TIWLN_TX_STATISTICS
 * \brief TI WLAN TX Statistics
 *
 * \par Description
 * All Tx statistics of all Tx Queues Tx-queue
 *
 * \sa
 */
typedef struct
{
    Bool_e         validLink;
    linkType_e     linkType;
    TMacAddr       aMacAddr;
    uint32_t       recvPktsFromWlan;
    uint32_t       recvBytesFromWlan;
    uint32_t       sentPkts;
    uint32_t       sentBytes;
    uint32_t       sentPktsError;
} TLinkDataCounters;

/** \enum ERate
 * \brief Rate Types
 *
 * \par Description
 * Driver's TX Control Frame Rate Format Type
 *
 * \sa
 */
typedef enum
{
    TIW_DRV_RATE_AUTO        = 0,                   /**< Auto                           */
    TIW_DRV_RATE_1M          = 1,                   /**< 1M                             */
    TIW_DRV_RATE_2M          = 2,                   /**< 2M                             */
    TIW_DRV_RATE_5_5M        = 3,                   /**< 5.5M                           */
    TIW_DRV_RATE_11M         = 4,                   /**< 11M                            */
    TIW_DRV_RATE_22M         = 5,                   /**< 22M                            */
    TIW_DRV_RATE_6M          = 6,                   /**< 6M                             */
    TIW_DRV_RATE_9M          = 7,                   /**< 9M                             */
    TIW_DRV_RATE_12M         = 8,                   /**< 12M                            */
    TIW_DRV_RATE_18M         = 9,                   /**< 18M                            */
    TIW_DRV_RATE_24M         = 10,                  /**< 24M                            */
    TIW_DRV_RATE_36M         = 11,                  /**< 36M                            */
    TIW_DRV_RATE_48M         = 12,                  /**< 48M                            */
    TIW_DRV_RATE_54M         = 13,                  /**< 54M                            */
    TIW_DRV_RATE_MCS_0       = 14,                  /**< 6.5M   or 7.2                  */
    TIW_DRV_RATE_MCS_1       = 15,                  /**< 13.0M  or 14.4                 */
    TIW_DRV_RATE_MCS_2       = 16,                  /**< 19.5M  or 21.7                 */
    TIW_DRV_RATE_MCS_3       = 17,                  /**< 26.0M  or 28.9                 */
    TIW_DRV_RATE_MCS_4       = 18,                  /**< 39.0M  or 43.3                 */
    TIW_DRV_RATE_MCS_5       = 19,                  /**< 52.0M  or 57.8                 */
    TIW_DRV_RATE_MCS_6       = 20,                  /**< 58.5M  or 65.0                 */
    TIW_DRV_RATE_MCS_7       = 21,                  /**< 65.0M  or 72.2                 */
    TIW_DRV_RATE_MCS_8       = 22,                  /**< 13.0M  or 14.4                 */
    TIW_DRV_RATE_MCS_9       = 23,                  /**< 26.0M  or 28.9                 */
    TIW_DRV_RATE_MCS_10      = 24,                  /**< 39.0M  or 43.3                 */
    TIW_DRV_RATE_MCS_11      = 25,                  /**< 52.0M  or 57.8                 */
    TIW_DRV_RATE_MCS_12      = 26,                  /**< 78.0M  or 86.7                 */
    TIW_DRV_RATE_MCS_13      = 27,                  /**< 104.0M or 115.6                */
    TIW_DRV_RATE_MCS_14      = 28,                  /**< 117.0M or 130                  */
    TIW_DRV_RATE_MCS_15      = 29,                  /**< 130.0M or 144.4                */
    TIW_DRV_RATE_40MHZ_RATES = 32,
    TIW_DRV_RATE_MAX         = TIW_DRV_RATE_MCS_15, /**< Maximum Driver's Rate Type     */
    TIW_DRV_RATE_INVALID     = 0xFF                 /**< Invalid Driver's Rate Type     */
} tiwdrv_rate_e;

#define RATE_TO_MASK(R)  (1 << ((R) - 1))

#define __FW_STA_ROLE_ID__     0
#define __FW_AP_ROLE_ID__      1

/** \enum ERateMask
 * \brief Driver rate mask
 *
 * \par Description
 *
 * \sa
 */
typedef enum
{
    DRV_RATE_MASK_AUTO          = TIW_DRV_RATE_AUTO,                        /**< 0x00000000 */
    DRV_RATE_MASK_1_BARKER      = RATE_TO_MASK(TIW_DRV_RATE_1M),            /**< 0x00000001 */
    DRV_RATE_MASK_2_BARKER      = RATE_TO_MASK(TIW_DRV_RATE_2M),            /**< 0x00000002 */
    DRV_RATE_MASK_5_5_CCK       = RATE_TO_MASK(TIW_DRV_RATE_5_5M),          /**< 0x00000004 */
    DRV_RATE_MASK_11_CCK        = RATE_TO_MASK(TIW_DRV_RATE_11M),           /**< 0x00000008 */
    DRV_RATE_MASK_22_PBCC       = RATE_TO_MASK(TIW_DRV_RATE_22M),           /**< 0x00000010 */
    DRV_RATE_MASK_6_OFDM        = RATE_TO_MASK(TIW_DRV_RATE_6M),            /**< 0x00000020 */
    DRV_RATE_MASK_9_OFDM        = RATE_TO_MASK(TIW_DRV_RATE_9M),            /**< 0x00000040 */
    DRV_RATE_MASK_12_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_12M),           /**< 0x00000080 */
    DRV_RATE_MASK_18_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_18M),           /**< 0x00000100 */
    DRV_RATE_MASK_24_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_24M),           /**< 0x00000200 */
    DRV_RATE_MASK_36_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_36M),           /**< 0x00000400 */
    DRV_RATE_MASK_48_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_48M),           /**< 0x00000800 */
    DRV_RATE_MASK_54_OFDM       = RATE_TO_MASK(TIW_DRV_RATE_54M),           /**< 0x00001000 */
    DRV_RATE_MASK_MCS_0_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_0),         /**< 0x00002000 */
    DRV_RATE_MASK_MCS_1_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_1),         /**< 0x00004000 */
    DRV_RATE_MASK_MCS_2_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_2),         /**< 0x00008000 */
    DRV_RATE_MASK_MCS_3_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_3),         /**< 0x00010000 */
    DRV_RATE_MASK_MCS_4_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_4),         /**< 0x00020000 */
    DRV_RATE_MASK_MCS_5_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_5),         /**< 0x00040000 */
    DRV_RATE_MASK_MCS_6_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_6),         /**< 0x00080000 */
    DRV_RATE_MASK_MCS_7_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_7),         /**< 0x00100000 */
    DRV_RATE_MASK_MCS_8_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_8),         /**< 0x00200000 */
    DRV_RATE_MASK_MCS_9_OFDM    = RATE_TO_MASK(TIW_DRV_RATE_MCS_9),         /**< 0x00400000 */
    DRV_RATE_MASK_MCS_10_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_10),        /**< 0x00800000 */
    DRV_RATE_MASK_MCS_11_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_11),        /**< 0x01000000 */
    DRV_RATE_MASK_MCS_12_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_12),        /**< 0x02000000 */
    DRV_RATE_MASK_MCS_13_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_13),        /**< 0x04000000 */
    DRV_RATE_MASK_MCS_14_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_14),        /**< 0x08000000 */
    DRV_RATE_MASK_MCS_15_OFDM   = RATE_TO_MASK(TIW_DRV_RATE_MCS_15),        /**< 0x10000000 */
    DRV_RATE_MASK_40MHZ_RATES   = RATE_TO_MASK(TIW_DRV_RATE_40MHZ_RATES)    /**< 0x80000000 */

} ERateMask;

#ifndef TI_FIELD_OFFSET
/**
 * \def TI_FIELD_OFFSET
 * \brief Macro which returns a field offset from structure begine
 */
#define TI_FIELD_OFFSET(type,field)    ((uint32_t)(&(((type*)0)->field)))
#endif         
                        
#ifndef TI_BIT
#define TI_BIT(x)                   (1 << (x))
#endif

#ifndef IS_BIT_SET
#define IS_BIT_SET(bitmap, idx)  (((bitmap) & TI_BIT(idx)) > 0)
#endif

#ifndef SET_BIT_BY_IDX
#define SET_BIT_BY_IDX(bitmap, idx) ((bitmap) |= TI_BIT(idx))
#endif

#ifndef CLEAR_BIT_BY_IDX
#define CLEAR_BIT_BY_IDX(bitmap, idx) ((bitmap) &= ~TI_BIT(idx))
#endif


/*
 * --------------------------------------------------------------
 *  Definitions
 * --------------------------------------------------------------
 */

/* Add hlid: process_id_tag field moved into status fileds bits [5..3] */
#define    RX_DESC_STATUS_PROC_ID_TAG_MASK  0x7
#define    RX_DESC_STATUS_PROC_ID_TAG_SHFT  3


#ifndef CC33xx
#ifndef RADIO_BAND_2_4GHZ
#define RADIO_BAND_2_4GHZ RADIO_BAND_2_4_GHZ
#endif

#ifndef RADIO_BAND_5GHZ
#define RADIO_BAND_5GHZ RADIO_BAND_5_0_GHZ
#endif
#endif // cc33xx

#define RXFLAGS_TO_BAND(flags)      (((flags & RX_DESC_BAND_MASK) == RX_DESC_BAND_BG) ? RADIO_BAND_2_4GHZ : RADIO_BAND_5GHZ)
#define RXSTATUS_TO_SCANTAG(status) ((status >> RX_DESC_STATUS_PROC_ID_TAG_SHFT ) & RX_DESC_STATUS_PROC_ID_TAG_MASK)

#define RX_QUEUE_DEFAULT_WIN_SIZE           32

/* Tx aggregation packets number limit (max packets in one aggregation) */
#define TWD_TX_AGGREG_PKTS_LIMIT_MIN    0
#define TWD_TX_AGGREG_PKTS_LIMIT_DEF    1 //1 = no aggragation
#define TWD_TX_AGGREG_PKTS_LIMIT_MAX    (TWD_TX_AGGREG_PKTS_LIMIT_DEF*2346) //max frame length mutiple num of frames

/* PALAU Group Address Default Values */
#define NUM_GROUP_ADDRESS_VALUE_DEF     0
#define NUM_GROUP_ADDRESS_VALUE_MIN     0
#define NUM_GROUP_ADDRESS_VALUE_MAX     8


/* ARP IP Filter Default Values */
#define MIN_FILTER_ENABLE_VALUE         0
#define MAX_FILTER_ENABLE_VALUE         3
#define DEF_FILTER_ENABLE_VALUE         0
#define FILTER_ENABLE_FLAG_LEN          1

/* Beacon filter Deafult Values */
#define DEF_BEACON_FILTER_ENABLE_VALUE  1
#define MIN_BEACON_FILTER_ENABLE_VALUE  0
#define MAX_BEACON_FILTER_ENABLE_VALUE  1
#define BEACON_FILTER_IE_TABLE_DEF_SIZE 36
#define BEACON_FILTER_IE_TABLE_MAX_SIZE 6*15
#define BEACON_FILTER_IE_TABLE_MIN_SIZE 0
#define DEF_BEACON_FILTER_IE_TABLE_NUM  15
#define BEACON_FILTER_IE_TABLE_MAX_NUM  15
#define BEACON_FILTER_IE_TABLE_MIN_NUM  0

#define DEF_NUM_STORED_FILTERS          1
#define MIN_NUM_STORED_FILTERS          1
#define MAX_NUM_STORED_FILTERS          8

/** \enum TxDelayRanges_e
 * \brief TX Delay Ranges
 *
 * \par Description
 * The Tx path delay histogram (host + MAC)ranges in msec
 * Used as indexes in tx Delay Histogram Ranges (including Start & End of ranges) Table
 *
 * \sa
 */
typedef enum
{
    TX_DELAY_RANGE_MIN        = 0,		/**< */

    TX_DELAY_RANGE_0_TO_1     = 0,		/**< */
    TX_DELAY_RANGE_1_TO_10    = 1,		/**< */
    TX_DELAY_RANGE_10_TO_20   = 2,		/**< */
    TX_DELAY_RANGE_20_TO_40   = 3,		/**< */
    TX_DELAY_RANGE_40_TO_60   = 4,		/**< */
    TX_DELAY_RANGE_60_TO_80   = 5,		/**< */
    TX_DELAY_RANGE_80_TO_100  = 6,		/**< */
    TX_DELAY_RANGE_100_TO_200 = 7,		/**< */
    TX_DELAY_RANGE_ABOVE_200  = 8,		/**< */

    TX_DELAY_RANGE_MAX        = 8,		/**< */
    TX_DELAY_RANGES_NUM       = 9		/**< */
} TxDelayRanges_e;

#define NUM_EXTRA_BLKS_DEFAULT_SECURITY 1  /* If no link uses TKIP or GEM, only one extra mem-block is needed per Tx packet */
#define NUM_EXTRA_BLKS_TKIP_OR_GEM 2

/*
 * Host I/f configuration
 */
#define TWD_HOST_IF_CFG_BITMAP_MIN      0x80000000  /* Lowest 32bit signed value */
#define TWD_HOST_IF_CFG_BITMAP_MAX      0x7fffffff  /* Highest 32bit signed value */

#define TWD_HOST_IF_CFG_BITMAP_DEF      1



/* Rx aggregation packets number limit (max packets in one aggregation) */
#define TWD_RX_AGGREG_PKTS_LIMIT_DEF    8//1//MAX_XFER_BUFS



#define MAX_NUM_OF_AC                   4
#define WLANLINKS_MAX_LINKS             MAX_NUM_LINKS  /* defined in the FW API (public_define.h) */
//#define WLANLINKS_MAX_LINKS             19
/************************************/
/*      Rates values                */
/************************************/

/* Tx packet Control-Block flags bit-mask. */
#define TX_CTRL_FLAG_SENT_TO_FW            0x0001  /* Set after the packet is allowed (by TxHwQueue) to be sent to FW */
#define TX_CTRL_FLAG_PKT_IN_RAW_BUF        0x0002  /* The input packet is in a raw buffer (as opposed to OS packet) */
#define TX_CTRL_FLAG_MULTICAST             0x0004  /* A multicast ethernet packet */
#define TX_CTRL_FLAG_BROADCAST             0x0008  /* A broadcast ethernet packet */
#define TX_CTRL_FLAG_HDR_BUILD             0x0010  /* Set after the packet header is build */


#define IS_PKT_TYPE_IF_ROLE_AP(pPktCtrlBlk)      ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_AP)
#define IS_PKT_TYPE_IF_ROLE_P2PGO(pPktCtrlBlk)   ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_P2P_GO)
#define IS_PKT_TYPE_IF_ROLE_STA(pPktCtrlBlk)     ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_STA)
#define IS_PKT_TYPE_IF_ROLE_P2PCL(pPktCtrlBlk)   ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_P2P_CL)
#define IS_PKT_TYPE_IF_ROLE_DEV(pPktCtrlBlk)     ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_DEVICE)
#define IS_PKT_TYPE_IF_ROLE_IBSS(pPktCtrlBlk)    ((pPktCtrlBlk)->tTxPktParams.uRoleType == ROLE_IBSS)
#define SET_PKT_TYPE_IF_ROLE_AP(pPktCtrlBlk)     (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_AP)
#define SET_PKT_TYPE_IF_ROLE_P2PGO(pPktCtrlBlk)  (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_P2P_GO)
#define SET_PKT_TYPE_IF_ROLE_STA(pPktCtrlBlk)    (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_STA)
#define SET_PKT_TYPE_IF_ROLE_P2PCL(pPktCtrlBlk)  (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_P2P_CL)
#define SET_PKT_TYPE_IF_ROLE_DEV(pPktCtrlBlk)    (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_DEVICE)
#define SET_PKT_TYPE_IF_ROLE_IBSS(pPktCtrlBlk)   (((pPktCtrlBlk)->tTxPktParams.uRoleType) = ROLE_IBSS)

#define SET_PKT_RATE_POLICY(pPktCtrlBlk, uRatePolicyId) (((pPktCtrlBlk)->tTxPktParams.uRatePolicyIndex) = uRatePolicyId)
#define GET_PKT_RATE_POLICY(pPktCtrlBlk) ((pPktCtrlBlk)->tTxPktParams.uRatePolicyIndex)

/* TxData resources flags */
#define TX_CTRL_FLAG_RSRC_ALLOCATED        0x0200 /* Tx data resources already checked and allocated */
#define IS_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk)  (((pPktCtrlBlk)->tTxPktParams.uFlags & TX_CTRL_FLAG_RSRC_ALLOCATED) == TX_CTRL_FLAG_RSRC_ALLOCATED)
#define SET_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk) (((pPktCtrlBlk)->tTxPktParams.uFlags) |= TX_CTRL_FLAG_RSRC_ALLOCATED)
#define CLEAR_TX_CTRL_FLAG_RSRC_ALLOCATED(pPktCtrlBlk) (((pPktCtrlBlk)->tTxPktParams.uFlags) &= ~TX_CTRL_FLAG_RSRC_ALLOCATED)

#define TX_CTRL_FLAG_RSRC_AC_MASK          0x0C00 /* 2 bits for original AC used in enqueue */
#define TX_CTRL_FLAG_RSRC_AC_SHIFT         10
#define SET_TX_CTRL_FLAG_RSRC_AC(pPktCtrlBlk, ac) (((pPktCtrlBlk)->tTxPktParams.uFlags) |= (((ac) << TX_CTRL_FLAG_RSRC_AC_SHIFT) & TX_CTRL_FLAG_RSRC_AC_MASK))
#define GET_TX_CTRL_FLAG_RSRC_AC(pPktCtrlBlk)     ((((pPktCtrlBlk)->tTxPktParams.uFlags) >> TX_CTRL_FLAG_RSRC_AC_SHIFT) & 0x3)

#define TX_PKT_TYPE_MGMT                   1   /* Management Packet                       */
#define TX_PKT_TYPE_EAPOL                  2   /* EAPOL packet (Ethernet)                 */
#define TX_PKT_TYPE_ETHER                  3   /* Data packet from the Network interface  */
#define TX_PKT_TYPE_WLAN_DATA              4   /* Driver generated WLAN Data Packet
                                                * (currently used for IAPP packet)        */
#define TX_PKT_TYPE_DUMMY_BLKS             5   /* Dummy Blocks Packet (for Dynamic Memory
                                                * management). Sent in response to Dummy
                                                * Packet Request FW event. Used by FW to
                                                * move memory blocks from TX to RX.       */


#define ALIGN_4BYTE_MASK                   0x3 /* Masked LS bits for 4-bytes aligned addresses or lengths. */
#define SHIFT_BETWEEN_TU_AND_USEC          10  /* Shift factor to convert between TU (1024 uSec) and uSec. */

/* Packet header + extensions structure ranges between 24 and 36 bytes as follows:
 * ------------------------------------------------------------------------------
 * Alignment Padding:   0/2 bytes,      added for 4 bytes alignment of this structure.
 * dot11 header:        24 bytes,       802.11 basic header.
 * Qos header:          0/2 bytes,      for QoS-data or QoS-Null the two QoS bytes are added.
 * extra                4 bytes
 * RSN header           0/8
 * LLC/SNAP:            8 bytes,         added only for data packets.
 */
#define MAX_HEADER_SIZE                 52 //TODO AK: change to 40 when FW removes security padding !!!!!!!

/* Data body max length */
#define MAX_DATA_BODY_LENGTH            4096

#define CTRL_BLK_ENTRIES_NUM                             120// was 120 but memory reduction for MX is required
#define CTRL_BLK_ENTRIES_FOR_DATA_NUM                    (CTRL_BLK_ENTRIES_NUM-16) //means kept for mgmt


/*the max table sized is : ( number of 221 * 8 bytes ) + ( non-221 * 2 bytes )
  Must be synchronized with the size of ACX defined in public_infoele.h interface
  with the FW
*/
#define ROLE_NONE                               0

#define MEM_BLOCK_SIZE                          256


/* Build the buffers descriptor of a typical two buffers (header & data) Tx packet */
#define BUILD_TX_TWO_BUF_PKT_BDL(pPktCtrlBlk,pHdrStart, uNabHdrLen,uDescrLen, uHdrLen, pDataBuf, uDataLenAlign,uDataLen) \
    pPktCtrlBlk->tTxnStruct.aBuf[0]   = (uint8_t *) (pHdrStart);    \
    pPktCtrlBlk->tTxnStruct.aLen[0]   = (uint16_t ) (uNabHdrLen+uDescrLen+uHdrLen);    \
    pPktCtrlBlk->tTxnStruct.aBuf[1]   = (uint8_t *) (pDataBuf);   \
    pPktCtrlBlk->tTxnStruct.aLen[1]   = (uint16_t ) (uDataLenAlign);   \
    pPktCtrlBlk->tTxnStruct.aLen[2]   = 0;                         \
    pPktCtrlBlk->tTxDescriptor.length = (uint16_t)((uHdrLen) + (uDescrLen) + (uDataLen));


#define TX_BUF_HDR_OFFSET 0


/*
 * --------------------------------------------------------------
 *  Enumerations
 * --------------------------------------------------------------
*/

/** \enum ETwdCallbackOwner
 * \brief TWD Callback Module owner ID
 *
 * \par Description
 * The Owner ID defines a specific TWD Module
 *
 * \sa ETwdEventId, TWD_RegisterCb
 */
typedef enum
{
    TWD_OWNER_DRIVER_TX_XFER            = 0x0100,   /**<    TX Xfer Owner ID        */
    TWD_OWNER_RX_XFER                   = 0x0200,   /**<    RX Xfer Owner ID        */
    TWD_OWNER_SELF                      = 0x0300,   /**<    Self Owner ID           */
    TWD_OWNER_MAC_SERVICES              = 0x0400,   /**<    MAC Services Owner ID   */
    TWD_OWNER_TX_RESULT                 = 0x0500,   /**<    TX Result Owner ID      */
    TWD_OWNER_SELF_CONFIG               = 0x0600,   /**<    Self configuration of Owner ID      */
    TWD_OWNER_RX_QUEUE                  = 0x0700,   /**<    RX Queue Owner ID       */
    TWD_OWNER_TX_HW_QUEUE               = 0x0800,   /**<    TX HW Queue Owner ID    */
    TWD_OWNER_FWLOGGER_CONTINUOUS       = 0x0900,   /**<    RX FwLogger_CONTINUOUS Queue Owner ID */
    TWD_OWNER_FWLOGGER_ON_DEMAND        = 0x1000    /**<    RX FwLogger_ON_DEMAND Queue Owner ID */
} ETwdCallbackOwner;

/** \enum ETwdIntCallbackId
 * \brief TWD Internal Callbacks ID
 *
 * \par Description
 * The Owner ID defines a specific TWD Internal CB
 *
 * \sa ETwdEventId
 */
typedef enum
{
    TWD_INT_SEND_PACKET_COMPLETE        =  0x00 ,   /**<    Tx Data Path Complete Callback  */
    TWD_INT_UPDATE_BUSY_MAP                     ,   /**<    Tx Data Path Update-Busy-Map Callback   */

    /* Rx Data Path Callbacks */
    TWD_INT_RECEIVE_PACKET              =  0x10 ,   /**<    Rx Data Path Receive Packet Callback        */
    TWD_INT_REQUEST_FOR_BUFFER                  ,   /**<    Rx Data Path Request for buffer Callback    */
    TWD_INT_RECEIVE_FWLOGGER_PACKET             ,   /**<    Rx Data Path Receive FwLogger Packet Callback       */

    /* TWD Callbacks */
    TWD_INT_EVENT_FAILURE               =  0x20 ,   /**<    TWD internal Event Failure handle Callback  */

} ETwdIntCallbackId;


/** \enum ETwdEventId
 * \brief TNETW Driver Event ID
 *
 * \par Description
 * The TWD Event ID is used by user for registering a TWD Internal CB
 * which will handle a TWD Event.
 * Each field in this enum is an ID of TWD Event, and is combined of two IDs:
 * TWD CB Owner (Module) ID and TWD Internal CB ID. Therefore, the CB is registered accordeing to
 * Module (Owner) and Internal CB Id.
 *
 * \sa TWD_RegisterCb, ETwdCallbackOwner, ETwdIntCallbackId
 */
typedef enum
{
    /* Internal Failure Event Callbacks */
    TWD_EVENT_FAILURE                       =  TWD_OWNER_SELF | TWD_INT_EVENT_FAILURE,                  /**<    Failure Internal Event ID           */

    /* Tx Data Path Callbacks */
    TWD_EVENT_TX_RESULT_SEND_PKT_COMPLETE   =  TWD_OWNER_TX_RESULT | TWD_INT_SEND_PACKET_COMPLETE,      /**<    TX Data Path Send Packet Complete Event ID  */
    TWD_EVENT_TX_HW_QUEUE_UPDATE_BUSY_MAP   =  TWD_OWNER_TX_HW_QUEUE | TWD_INT_UPDATE_BUSY_MAP,         /**<    TX Data Path Update-Busy-Map Event ID   */

    /* Rx Data Path Callbacks */
    TWD_EVENT_RX_REQUEST_FOR_BUFFER         =  TWD_OWNER_RX_XFER | TWD_INT_REQUEST_FOR_BUFFER,          /**<    RX Data Path Request for Buffer Internal Event ID   */
    TWD_EVENT_RX_RECEIVE_PACKET             =  TWD_OWNER_RX_XFER | TWD_INT_RECEIVE_PACKET,              /**<    RX Data Path Receive Packet Internal Event ID   */
    TWD_EVENT_RX_RECEIVE_FWLOGGER_CONTINUOUS_PACKET        =  TWD_OWNER_FWLOGGER_CONTINUOUS | TWD_INT_RECEIVE_FWLOGGER_PACKET,                  /**<    RX Data Path Receive FwLogger Packet Internal Event ID  */
    TWD_EVENT_RX_RECEIVE_FWLOGGER_ON_DEMAND_PACKET      =    TWD_OWNER_FWLOGGER_ON_DEMAND | TWD_INT_RECEIVE_FWLOGGER_PACKET
} ETwdEventId;

#ifdef TI_DBG
/** \enum ETwdPrintInfoType
 * \brief TWD print functions codes
 *
 * \par Description
 * Used for Debug - determines which Tx Info to print
 *
 * \sa TWD_PrintTxInfo
 */
typedef enum
{
/*  0   */  TWD_PRINT_TX_CTRL_BLK_TBL = 0,  /**<    Print TX Control Block Information  */
/*  1   */  TWD_PRINT_TX_HW_QUEUE_INFO,     /**<    Print TX HW Queue Information       */
/*  2   */  TWD_PRINT_TX_XFER_INFO,         /**<    Print TX XFER Information           */
/*  3   */  TWD_PRINT_TX_RESULT_INFO,       /**<    Print TX Result Information         */
/*  4   */  TWD_CLEAR_TX_RESULT_INFO,       /**<    Clear TX Result Information         */
/*  5   */  TWD_CLEAR_TX_XFER_INFO          /**<    Clear TX Xfer Information           */

} ETwdPrintInfoType;
#endif



/** \enum EKeyType
 * \brief Key Type
 *
 * \par Description
 * Security Key Type
 *
 * \sa TSecurityKeys
 */
typedef enum
{
	KEY_NULL,
	KEY_WEP,
	KEY_TKIP,
	KEY_AES,
	KEY_BIP_CMAC_128,
	KEY_GCMP,
	KEY_SMS4,
	KEY_KRK,
	KEY_GCMP_256,
	KEY_CCMP_256,
	KEY_BIP_GMAC_128,
	KEY_BIP_GMAC_256,
	KEY_BIP_CMAC_256

#ifdef GEM_SUPPORTED
    /*  5   */  KEY_GEM
#endif

} EKeyType;

/** \enum EFailureEvent
 * \brief Failure Event
 *
 * \par Description
 * Used as a parameter for Failure Event CB -
 * Inicates Failure Event ID, according which the Failure
 * Event's data is driven
 *
 * \sa TWD_RegisterOwnCb, TFailureEventCb
 */
typedef enum
{
/* -1 */ NO_FAILURE = -1,               /**< No Failure Event                   */
/*  0 */ NO_SCAN_COMPLETE_FAILURE = 0,  /**< No Scan Complete Failure Event     */
/*  1 */ MBOX_FAILURE,                  /**< Mail Box Failure Event             */
/*  2 */ HW_AWAKE_FAILURE,              /**< HW Awake Failure Event             */
/*  3 */ TX_STUCK,                      /**< TX STUCK Failure Event             */
/*  4 */ DISCONNECT_TIMEOUT,            /**< Disconnect Timeout Failure Event   */
/*  5 */ MEASUREMENT_FAILURE,           /**< Measurement Failure Event */
/*  6 */ BUS_FAILURE,                   /**< Bus Failure Event */
/*  7 */ HW_WD_EXPIRE,                  /**< HW Watchdog Expire Event */
/*  8 */ SW_WD_EXPIRE,                  /**< SW Watchdog Event  - FW ASSERT_GENERAL*/
/*  9 */ RX_XFER_FAILURE,               /**< Rx pkt xfer failure */
/* 10*/  ROC_TIMEOUT,                   /**< Remain on channel timeout Event */
/* 11 */ REG_DOMAIN_TIMEOUT,            /**< Reg domain configuration timeout Event */
/* must be last!!! */
/* 12 */  MAX_FAILURE_EVENTS            /**< Maximum number of Failure Events */
} EFailureEvent;


typedef enum
{
    KEY_WEP_DEFAULT       = 0,
    KEY_WEP_ADDR          = 1,
    KEY_AES_GROUP         = 4,
    KEY_AES_PAIRWISE      = 5,
    KEY_WEP_GROUP         = 6,
    KEY_TKIP_MIC_GROUP    = 10,
    KEY_TKIP_MIC_PAIRWISE = 11
} KeyType_enum;


/** \enum ETxHwQueStatus
 * \brief Status returned by txHwQueue_AllocResources
 *
 * \par Description
 *
 * \sa
 */
typedef enum
{
    TX_HW_QUE_STATUS_SUCCESS       = 0x0,  /* Resources available on current queue and current link*/
    TX_HW_QUE_STATUS_XMIT_BUSY     = 0x1,  /* No resources, stop current queue and requeue the packet */

} ETxHwQueStatus;

#define TX_HW_CURRENT_AC_STOP      0x1
#define TX_HW_CURRENT_LINK_STOP    0x2
#define TX_HW_CURRENT_LINK_HIGH    0x8

/** \enum ERxBufferStatus
 * \brief Status returned by TRequestForBufferCb
 *
 * \par Description
 *
 * \sa
 */
typedef enum
{
    RX_BUF_ALLOC_PENDING,
    RX_BUF_ALLOC_COMPLETE,
    RX_BUF_ALLOC_OUT_OF_MEM

}ERxBufferStatus;

/*
 * --------------------------------------------------------------
 *  Structures
 * --------------------------------------------------------------
 */

/** \struct TDmaParams
 * \brief DMA Parameters
 *
 * \par Description
 * Struct which holds DMA Rx/Tx Queues and Bufffers params
 *
 * \sa
 */
typedef struct
{
    uint32_t               NumTxBlocks;                /**< Allocated TX memory blocks number      */
    uint32_t               PacketMemoryPoolStart;      /**< RX Memory block offset */
    uint32_t               uHostTxDescriptors;            /**< Num of Tx descriptors in FW */
    uint8_t                FwLogBufferSize;            /**< number  of mem blks for FwLogger use*/
} TDmaParams;


/** \struct TTxDataCounters
 * \brief TX Data Counters
 *
 * \par Description
 * Tx statistics per Tx-queue
 *
 * \sa
 */
typedef struct
{
    uint32_t  XmitOk;                 /**< The number of frames that were transferred to TNET without errors                        */
    uint32_t  DirectedBytesXmit;      /**< The number of bytes in directed packets that are transmitted without errors          */
    uint32_t  DirectedFramesXmit;     /**< The number of directed packets that are transmitted without errors                       */
    uint32_t  MulticastBytesXmit;     /**< The number of bytes in multicast/functional packets that are transmitted without errors */
    uint32_t  MulticastFramesXmit;    /**< The number of multicast/functional packets that are transmitted without errors           */
    uint32_t  BroadcastBytesXmit;     /**< The number of bytes in broadcast packets that are transmitted without errors             */
    uint32_t  BroadcastFramesXmit;    /**< The number of broadcast packets that are transmitted without errors                  */
    uint32_t  FailCounter;            /**< Number of packets that failed transmission                                           */
} TTxDataCounters;

typedef struct
{
    TTxDataCounters *pTxDataCounters;
    uint8_t          acID;
}	reportTsStatisticsReq_t;

/** \struct TxPktParams_t
 * \brief TX Packet Parameters
 *
 * \par Description
 * Tx Control-Block Packet parameters that are not included in the Tx-descriptor
 *
 * \sa
 */
typedef struct
{
    void       *pInputDesc;       /**< The input packet descriptor used for Mgmt packets, of type TMgmtPktDesc  */
    void       *pInputPkt;        /**< The input packet to the Tx path, either OS packet or raw buffer (see RAW_BUF_PKT flag) */
    uint32_t    uInputPktLen;     /**< The input packet length in bytes (for freeing it in case of raw buffer)  */
    uint32_t    uDriverDelay;     /**< The time in uSec the pkt was delayed in the driver until Xfer            */
    uint8_t     uPktType;         /**< See TX_PKT_TYPE_xxxx above                                               */
    uint8_t     uHeadroomSize;    /**< Only for WHA - headroom in bytes before the payload in the packet buffer */
    uint16_t    uFlags;           /**< See TX_CTRL_FLAG__xxxx above                                             */
    uint8_t     uRoleType;        /**< The Role Type                                                            */
    uint8_t     uFwRoleId;        /**< The FW Role Id                                                           */
    uint8_t     uRatePolicyIndex; /**< The Rate Policy Index                                                    */
    uint8_t     uDelBaTidParam;   /**< TID of DELBA packet - used closing BA session upon Tx complete           */
    void       *fCb;              /**< The callback function for the packet - should be of type TMgmtPacketCb   */
    void       *hCb;              /**< The context for the callback                                             */
    uint8_t     uAcCounteDone;       /**< The packet was dequeue and allocated for tX and AC counted                                  */
    uint32_t    uAcPendTXDataDone;        /**<frame was enqueued and it is pending TX >**/
    uint8_t     extraSpareKeyCount;/* number of keys requiring extra spare mem-blocks                           */ 
    Bool_e      isNullDataFrame;  /**< Indicates whether the frame is a data frame with no payload              */
} TTxPktParams;


/** \struct TTxCtrlBlk
 * \brief TX Control Block Entry
 *
 * \par Description
 * Contains the Tx packet parameters required for the Tx process, including
 * the Tx descriptor and the attributes required for HW-queue calculations.
 * TX Control Block Entry is allocated for each packet sent from the upper
 * driver and freed upon Tx-complete.
 * The entry index is the descriptor-ID. It is written in the descriptor and
 * copied back into the tx-complete results
 *
 * \sa  SendPacketTranferCB_t, SendPacketDebugCB_t, TWD_txCtrlBlk_alloc, TWD_txCtrlBlk_free, TWD_txCtrlBlk_GetPointer, TWD_txXfer_SendPacket
 */

//---------------------------------------------------------------------------------------------//
// Structure name: CC33_FrameTxDesc_t                                                          //
// Size:  116 bytes (0x74)                                                                     //
// Field description                                                                           //
//---------------------------------------------------------------------------------------------//
//   *None*                                                                                    //
//
//---------------------------------------------------------------------------------------------//

//This struct should be kept 4 aligned
typedef struct _TTxCtrlBlk
{
    TTxnStruct           tTxnStruct;               /**< The transaction structure for packet queueing and transaction via the bus driver */
    NAB_tx_header_t      aPktNabHdr;               /**< The packet header + extensions (see description of MAX_HEADER_SIZE above) */
    TxIfDescriptor_t     tTxDescriptor;            /**< The packet descriptor copied to the FW  */
    uint8_t              aPktHdr[MAX_HEADER_SIZE]; /**< The packet header + extensions (see description of MAX_HEADER_SIZE above) */
    TTxPktParams         tTxPktParams;             /**< Per packet parameters not included in the descriptor */
    struct _TTxCtrlBlk  *pNextFreeEntry;           /**< Pointer to the next free entry */
    struct _TTxCtrlBlk  *pNextAggregEntry;         /**< Pointer to the next aggregated packet entry */

} TTxCtrlBlk;


/** \struct TTxHwBackpressure
 * \brief TxHwQueue ACs and Links queues busy and priority info
 *
 * \par Description
 *
 *      Update Tx upper layers about the FW queues status, including per link and per
 *          AC busy and priority state.
 * \sa
 */
typedef struct
{
    uint32_t   uAcBusyBitmap;        /* bitmap to indicate which AC is busy (1=stopped) */
    uint32_t   uLinkBusyBitmap;      /* bitmap to indicate which LINK is busy (1=stopped) */
    uint32_t   uLinkPriorityBitmap;  /* bitmap to indicate each LINK's priority (1=high) */
    uint8_t    aAcQueueLen[MAX_NUM_OF_AC];  /* bitmap to indicate each LINK's priority (1=high) */
    uint32_t   TransmitQOnTxComplete       ; /* Flag to indicate if run schedualer after TX Complete */
} TTxHwBackpressure;

#if 0
/******************************************************************************

    Ethernet

******************************************************************************/

#define ETHERTYPE_802_1D                        0x8100
#define ETHERTYPE_EAPOL                         0x888e
#define ETHERTYPE_PREAUTH_EAPOL                 0x88c7
#define ETHERTYPE_IP                            0x0800
#define ETHERTYPE_APPLE_AARP                    0x80f3
#define ETHERTYPE_DIX_II_IPX                    0x8137
#define ETHERTYPE_ARP                           0x0806

typedef struct
{
    TMacAddr    dst;
    TMacAddr    src;
    uint16_t    type;

} TEthernetHeader;
#endif

/******************************************************************************

    Core Default Params

******************************************************************************/
/* 0 - Dtag, 1 - DSCP, 2 - Port, 3 - IP & port */ 
//#define CLSFR_TYPE_MIN                      0
#define CLSFR_TYPE_DEF                      1
#define CLSFR_TYPE_MAX                      3

/* general values of D-tags */
//#define CLASSIFIER_DTAG_MIN                 0 
#define CLASSIFIER_DTAG_MAX                 7
//#define CLASSIFIER_DTAG_DEF                 0 

/* general values of code points in 
the DSCP classification table*/
//#define CLASSIFIER_CODE_POINT_MIN           0 
#define CLASSIFIER_CODE_POINT_MAX          63
//#define CLASSIFIER_CODE_POINT_DEF           0

/* General values of IP addresses */
/* TBD according to spec!*/
#define CLASSIFIER_IPADDRESS_MIN          0x0
/* MY IP ... TBD according to spec!*/
//#define CLASSIFIER_IPADDRESS_DEF   0x0A030DC4
/* TBD according to spec!*/
#define CLASSIFIER_IPADDRESS_MAX   0xFFFFFFFF


/* general values of port numbers */
#define CLASSIFIER_PORT_MIN                 1 
#define CLASSIFIER_PORT_MAX             65535
#define CLASSIFIER_PORT_DEF              1024 

#define PARAM_VALUE_NOT_VALID               3


/* In SDIO block-mode:  BlkSize = 1 << BlkSizeShift    (current block size is: 1<<8 = 256 bytes) */
#define SDIO_BLK_SIZE_SHIFT_MIN                             0
#define SDIO_BLK_SIZE_SHIFT_MAX                             16
#define SDIO_BLK_SIZE_SHIFT_DEF                             8






/******************************************************************************

    tiwDrvExternalIf

******************************************************************************/
#define TIW_DRV_MAC_ADDR          6


typedef enum
{
//    TIWDRV_NETIF_ID_DRV,
    TIWDRV_NETIF_ID_STA,
    TIWDRV_NETIF_ID_SAP,
    TIWDRV_NETIF_ID_P2PDEV,
    TIWDRV_NETIF_ID_P2PGROUP,
//    TIWDRV_NETIF_ID_IBSS,
    TIWDRV_NETIF_NUM,/*Total number of network interfaces*/
    TIWDRV_NETIF_ID_NONE = 0xFF
} tiwdrv_netif_id_e;


#define TI_UNLIKELY(statement) (statement)

/*
 * --------------------------------------------------------------
 *  APIs
 * --------------------------------------------------------------
 */
/** @ingroup Control
 * \brief Send Packet Debug CB
 *
 * \param  CBObj        - object handle
 * \param  pPktCtrlBlk  - Pointer to Input Packet Control Block
 * uDebugInfo           - Debug Information
 * \return void
 *
 * \par Description
 *
 * \sa  TWD_RegisterCb
 */
typedef uint8_t (*TRequestForBufferCb) (void **pRxBuffer, uint16_t aLength, uint32_t uEncryptionFlag, PacketClassTag_e ePacketClassTag);
/** @ingroup Control
 * \brief Send Packet Debug CB
 *
 * \param  hObj         - object handle
 * \param  pBuffer      - Pointer to Received buffer frame
 * \return void
 *
 * \par Description
 * This function CB will be called when Received packet from RX Queue
 * User registers the CB for RX Buffer Request
 *
 * \sa  TWD_RegisterCb
 */
typedef void (*TPacketReceiveCb) (const void *pBuffer);
/** @ingroup Control
 * \brief Failure Event CB
 *
 * \param  handle           - object handle
 * \param  eFailureEvent    - Failure Event Type
 * \return void
 *
 * \par Description
 * Callback clled for Failure event
 * User registers the CB for Health-Moitoring
 *
 * \sa  TWD_RegisterCb
 */
typedef void (*TFailureEventCb)  (void*  handle, EFailureEvent eFailureEvent);


/** \struct TTxResultInfo
 * \brief Tx result info
 *
 * \par Description
 * The Tx result info retrieved from FW upon packet TX completion.
 */
typedef struct
{
    uint8_t    uDescId;     /* Packet Identifier - same value used in the Tx descriptor.*/
    uint32_t   eStatus;     /* 1 if successful, 0 if failed */
} TTxResultInfo;

/*
 * Sends a CMD_CONFIGURE command to FW
 * Non-blocking, and the callback is called in a different "context" (if provided)
 *
 * @hTWD                module object
 * @eIeId               ID of Info-Element to send
 * @pIeBuf              buffer for input/output
 * @uCmdLen             bytes in @pIeBuf
 * @fCb                 a callback to invoke when the command completes transfer (set NULL if not needed)
 * @hCb                 an argument to pass when invoking @fCb (set NULL if CB not needed)
 *
 * @return              OK / NOK
 */
//uint32_t TWD_SendInfoEle(void *hTWD, InfoElement_enum eIeId, void *pIeBuf, uint32_t uIeLen, void *fCb, void *hCb);

/*
 * Sends a CMD_INTERROGATE command to retreive an Info-Element from FW
 * Non-blocking, and the callback is called in a different "context" (if provided)
 *
 * @hTWD                module object
 * @eIeId               ID of Info-Element to get
 * @pIeBuf              buffer for input/output
 * @uCmdLen             bytes in @pIeBuf
 * @fCb                 a callback to invoke when the command completes transfer (set NULL if not needed)
 * @hCb                 an argument to pass when invoking @fCb (set NULL if CB not needed)
 *
 * @return              OK / NOK
 */
//uint32_t TWD_GetInfoEle(void *hTWD, InfoElement_enum eIeId, void *pIeBuf, uint32_t uIeLen, void *fCb, void *hCb);


#ifdef TI_DBG

/** @ingroup Test
 * \brief Prints Tx Info
 *
 * \param  hTWD         - TWD module object handle
 * \param  ePrintInfo   - Information type
 * \return OK on success or NOK on failure
 *
 * \par Description
 * Call the requested print function - used for Debug Test
 *
 * \sa
 */
uint32_t TWD_PrintTxInfo (ETwdPrintInfoType ePrintInfo);
#endif


/*---------*/
/* Command */
/*---------*/

/*
 * --------------------------------------------------------------
 *  TNETW-Driver  Tx  API  Functions
 * --------------------------------------------------------------
 */

/** @ingroup Data_Path
 * \brief  TWD TX Control Block Allocation
 *
 * \param  hTWD     - TWD module object handle
 * \return Pointer to Control Block Entry on success or NULL on failure
 *
 * \par Description
 * Use this function for Allocate a Control-Block for the packet Tx parameters and descriptor
 *
 * \sa
 */
TTxCtrlBlk *TWD_txCtrlBlk_Alloc (uint8_t isMgmt);
/** @ingroup Data_Path
 * \brief  TWD TX Control Block Free
 *
 * \param  hTWD             - TWD module object handle
 * \param  pCurrentEntry    - Pointer to TX Control Block Entry to Free
 * \return void
 *
 * \par Description
 * Use this function for Free a Control-Block of packet Tx parameters and descriptor
 *
 * \sa
 */
void TWD_txCtrlBlk_Free (TTxCtrlBlk *pCurrentEntry);

/** @ingroup Data_Path
 * \brief  TWD TX Control Get Pointer
 *
 * \param  hTWD     - TWD module object handle
 * \param  uIndex   - Index of TX Control Block in the table
 * \return Pointer to Control Block Entry on success or NULL on failure
 *
 * \par Description
 * Use this function for Get a Pointer to a Control-Block of packet Tx parameters and descriptor
 *
 * \sa
 */
TTxCtrlBlk *TWD_txCtrlBlk_GetPointer(uint32_t uIndex);

/** @ingroup Data_Path
 * \brief  Allocate Resources for TX HW Queue
 *
 * \param  hTWD             - TWD module object handle
 * \param  pTxCtrlBlk       - The Tx packet control block
 * \return see - ETxHwQueStatus
 *
 * \par Description
 * Allocates Resources (HW-blocks number required) for TX HW Queue
 *
 * \sa
 */

ETxHwQueStatus TWD_txHwQueue_AllocResources (TTxCtrlBlk *pTxCtrlBlk, uint8_t *pBackpressureMap);

/** @ingroup Data_Path
 * \brief  TX Xfer Send Packet
 *
 * \param  hTWD             - TWD module object handle
 * \param  pPktCtrlBlk      - Pointer to TX Control Block Entry to Free
 * \return see ETxnStatus
 *
 * \par Description
 * Send Packet via TX Xfer
 *
 * \sa
 */
ETxnStatus TWD_txXfer_SendPacket (TTxCtrlBlk *pPktCtrlBlk);


/** @ingroup Data_Path
 * \brief  TX Xfer Send Packet
 *
 * \param  hTWD             - TWD module object handle
 * \param  pPktCtrlBlk      - Pointer to TX Control Block Entry to Free
 * \return see ETxnStatus
 *
 * \par Description
 * Send Packet via TX Xfer , aggregation of  packet
 *
 * \sa
 */
ETxnStatus TWD_txXferAggr_SendPacket (TTxCtrlBlk *pPktCtrlBlk);

/** @ingroup Data_Path
 * \brief  Indicates that current packets burst stopped
 *
 * \param  hTWD             - TWD module object handle
 * \return void
 *
 * \par Description
 * Indicates that current packets burst stopped, so the TxXfer will send its aggregated packets to FW.
 *
 * \sa
 */
void TWD_txXferAggr_EndOfBurst (void);
#endif  /* TWDRIVER_H */
