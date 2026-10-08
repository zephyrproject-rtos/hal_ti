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
#ifndef RATES_H
#define RATES_H

#include "public_types.h"
#include "macro_utils.h"        // for BITMASK_x_y

// The enumeration below can be used in 2 ways:
//      o when setting specific rate - enumeration value is used
//      o when settting a bit mask of supported rates - enumeration value defines the equivalent bit
typedef enum
{
    RATE_INDEX_1MBPS            =  1,
    RATE_INDEX_2MBPS            =  2,
    RATE_INDEX_5_5MBPS          =  3,
    RATE_INDEX_11MBPS           =  4,
    RATE_INDEX_6MBPS            =  5,
    RATE_INDEX_9MBPS            =  6,
    RATE_INDEX_12MBPS           =  7,
    RATE_INDEX_18MBPS           =  8,
    RATE_INDEX_24MBPS           =  9,
    RATE_INDEX_36MBPS           =  10,
    RATE_INDEX_48MBPS           =  11,
    RATE_INDEX_54MBPS           =  12,
    RATE_INDEX_MCS0             =  13, //6.5Mbps
    RATE_INDEX_MCS1             =  14, //13Mbps
    RATE_INDEX_MCS2             =  15, //19.5Mbps
    RATE_INDEX_MCS3             =  16, //26Mbps
    RATE_INDEX_MCS4             =  17, //39Mbps
    RATE_INDEX_MCS5             =  18, //52Mbps
    RATE_INDEX_MCS6             =  19, //58.5Mbps
    RATE_INDEX_MCS7             =  20, //65Mbps


    RATE_INDEX_MAX_INDEXES,

    INVALID_RATE_INDEX = RATE_INDEX_MAX_INDEXES,

    RATE_INDEX_ENUM_MAX_SIZE = 0x7F
} RateIndex_e;


// ----------------------------------------------------------------------------
// Static information stored per recommended rate for fragmentation
// ----------------------------------------------------------------------------
typedef struct
{
    uint8_t/*RateIndex_e*/ nonHTRate;
    uint32_t      lowerRatesBM;

} RateRecommendationFrag_t;


// factor that the gRateLengthFactors is multiply with
#define RATE_LENGTH_FACTOR  2

#define ANY_B_RATE          ( BITMASK_x_y(RATE_INDEX_11MBPS, RATE_INDEX_1MBPS) )
#define ANY_AG_OFDM_RATE    ( BITMASK_x_y(RATE_INDEX_54MBPS, RATE_INDEX_6MBPS) )

#define ANY_N_RATE          ( BITMASK_x_y(RATE_INDEX_MCS7, RATE_INDEX_MCS0) )

#define ANY_RATE            ( ANY_B_RATE | ANY_AG_OFDM_RATE | ANY_N_RATE )

#define RX_MCS_BM_0_TO_7    0xFF

#define IS_MCS_RATE(rate)   ((BIT_x(rate) & ANY_N_RATE) != 0)
#define IS_B_RATE(rate)     ((BIT_x(rate) & ANY_B_RATE) != 0)
#define IS_AG_RATE(rate)    ((BIT_x(rate) & ANY_AG_OFDM_RATE) != 0)
#define BASIC_RATE_SET      ( BITMASK_x_y(RATE_INDEX_11MBPS, RATE_INDEX_1MBPS) )


#define SUPPORTED_RATE_SET  ( BITMASK_x_y(RATE_INDEX_11MBPS, RATE_INDEX_1MBPS) )

#define EXCLUDE_MCS_RATES(rateBitmap)   (rateBitmap &= ~(BITMASK_x_y(RATE_INDEX_MCS7, RATE_INDEX_MCS0)))

#define MAX_NUM_BG_RATES    (12)
#define MAX_NUM_MCS_RATES   (16)

#define CONVERT_RATE_INDEX_TO_RATESET_BIT(rateIndex) (1 << rateIndex)
#define TEST_OFDM_RATE(rateIndex) ((CONVERT_RATE_INDEX_TO_RATESET_BIT(rateIndex) & ANY_OFDM_RATESET) ? TRUE : FALSE)

// RATE POLICIES registers- these registers indexes store bitmaps that are used by the rate management HW module.
// First 4 registers indexes, contains hard coded rate policies bitmaps in HW and cannot be changed
#define RATE_POLICY_ANY_RATE                           0 // ANY_RATE
#define RATE_POLICY_ANY_OFDM_RATE                      1 // ANY_AG_OFDM_RATE | ANY_N_RATE
#define RATE_POLICY_ANY_B_RATE                         2 // ANY_B_RATE
#define RATE_POLICY_11BG_RATE                          3 // ANY_B_RATE | ANY_AG_OFDM_RATE
// These 4 registers indexes, contains configurable rate policies through the registers PMAC_TX_2__TX_RM_RATE_POLICY_4 - PMAC_TX_2__TX_RM_RATE_POLICY_7
#define RATE_POLICY_LOW_RATES_BASIC_SHORT_FRAMES       4 // LOW RATES Basic or LOW B RATES Basic if ERP Protection on
#define RATE_POLICY_LOW_RATES_SUPPORTED_SHORT_FRAMES   5 // LOW RATES Supported or LOW B RATES Supported if ERP Protection is on
#define RATE_POLICY_MEDIUM_RATES                       6 // Medium rates
#define RATE_POLICY_LOW_RATES_SUPPORTED                7 // LOW RATES Supported

//Rate policy use - used to calculate the polices
#define LOW_RATES       ( BITMASK_x_y(RATE_INDEX_5_5MBPS, RATE_INDEX_1MBPS) | BIT_x(RATE_INDEX_6MBPS) )//(1,2,5.5,6)
#define MEDIUM_RATES    ( BITMASK_x_y(RATE_INDEX_24MBPS, RATE_INDEX_1MBPS) )  //(1,2,5.5,11,6,9,12,18,24)

//Rate policy use - used for frames overwrite rate policy
#define BROADCAST_RATE_2_4                   RATE_INDEX_1MBPS
#define PROBES_RATE_2_4                      RATE_INDEX_2MBPS
#define BROADCAST_RATE_5                     RATE_INDEX_6MBPS
#define PROBES_RATE_5                        RATE_INDEX_6MBPS

// The types are used for building rates IEs for management packets
// (beacon, probe response, association request/response)
#define NET_BASIC_MASK  0x80

typedef enum
{
    NET_RATE_1M         = 0x02,
    NET_RATE_2M         = 0x04,
    NET_RATE_5_5M       = 0x0B,
    NET_RATE_11M        = 0x16,
    NET_RATE_22M        = 0x2C,
    NET_RATE_6M         = 0x0C,
    NET_RATE_9M         = 0x12,
    NET_RATE_12M        = 0x18,
    NET_RATE_18M        = 0x24,
    NET_RATE_24M        = 0x30,
    NET_RATE_36M        = 0x48,
    NET_RATE_48M        = 0x60,
    NET_RATE_54M        = 0x6C
} NetRate_e;

typedef enum
{
    NET_RATE_1M_BASIC   = (NET_RATE_1M   | NET_BASIC_MASK),
    NET_RATE_2M_BASIC   = (NET_RATE_2M   | NET_BASIC_MASK),
    NET_RATE_5_5M_BASIC = (NET_RATE_5_5M | NET_BASIC_MASK),
    NET_RATE_11M_BASIC  = (NET_RATE_11M  | NET_BASIC_MASK),
    NET_RATE_22M_BASIC  = (NET_RATE_22M  | NET_BASIC_MASK),
    NET_RATE_6M_BASIC   = (NET_RATE_6M   | NET_BASIC_MASK),
    NET_RATE_9M_BASIC   = (NET_RATE_9M   | NET_BASIC_MASK),
    NET_RATE_12M_BASIC  = (NET_RATE_12M  | NET_BASIC_MASK),
    NET_RATE_18M_BASIC  = (NET_RATE_18M  | NET_BASIC_MASK),
    NET_RATE_24M_BASIC  = (NET_RATE_24M  | NET_BASIC_MASK),
    NET_RATE_36M_BASIC  = (NET_RATE_36M  | NET_BASIC_MASK),
    NET_RATE_48M_BASIC  = (NET_RATE_48M  | NET_BASIC_MASK),
    NET_RATE_54M_BASIC  = (NET_RATE_54M  | NET_BASIC_MASK)
} NetRateBasic_e;


typedef struct
{
    uint32_t basicRatesBM;
    uint32_t supportedRatesBM;
} rateSets_t;

/********************************************************************************/
// Rate adaptation enumeration
// Note that this enumeration is used inside the rate management module only !!!!
// Used in the SW for rate management configuration only
typedef enum
{
    RATE_ADAPT_1MBPS            =  0x0,
    RATE_ADAPT_2MBPS            =  0x1,
    RATE_ADAPT_5_5MBPS          =  0x2,
    RATE_ADAPT_MCS0             =  0x3,//6.5Mbps
    RATE_ADAPT_9MBPS            =  0x4,
    RATE_ADAPT_11MBPS           =  0x5,
    RATE_ADAPT_MCS1             =  0x6,//13Mbps
    RATE_ADAPT_MCS2             =  0x7,//19.5Mbps
    RATE_ADAPT_MCS3             =  0x8,//26Mbps
    RATE_ADAPT_MCS4             =  0x9,//39Mbps
    RATE_ADAPT_MCS5             =  0xa,//52Mbps
    RATE_ADAPT_MCS6             =  0xb,//58.5Mbps
    RATE_ADAPT_MCS7             =  0xc,//65Mbps
#ifndef PMAC_AX
    RATE_ADAPT_MCS7_SGI         =  0xd//65Mbps+10%
#endif
} rateAdapt_e;
/********************************************************************************/
#endif
