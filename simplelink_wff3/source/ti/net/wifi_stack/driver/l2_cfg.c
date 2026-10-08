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
/*-----------------------------------------------------------------------------

  FILENAME:       le_cfg.h

  DESCRIPTION:    L2 configuration module, contains configurable L2 parameters.
                  The module is responsible for setting default values based on
                  static, hard coded values as well as ini files when available.
                  It is also responsible for updating configuration dynamically
                  during WLAN connection, based on peer capabilities.

  HISTORY:
                 09/15 - Creation

  ----------------------------------------------------------------------------- */

#include "l2_cfg.h"

#include "common.h"
#include "cc3xxx_public_commands.h"
#include "errors.h"
#include "cme_defs.h"

// ============================================================================
//		Modules private definitions
// ============================================================================

#define QOS_PACKET_BURST_TXOP_LIMIT_DEF   (93)
#define QOS_RX_TIMEOUT_PS_POLL_DEF        (15)
#define QOS_RX_TIMEOUT_UPSD_DEF           (15)
#define QOS_MAX_SP_LEN_DEF                 (1)

// for more information see PSScheme_e
#define PS_SCHEME_DEF                       (0) /* Regular PS: simple sending of packets*/
// for more information see AckPolicy_e
#define ACK_POLICY_DEF                      (0)   /* ACK immediate policy*/


#define AIFS_DEF                           (2)
#define CW_MIN_DEF                         (4)
#define CW_MAX_DEF                        (10)


#define  HT_BA_DISABLE                     (0)
#define  HT_BA_INITIATOR                   (1)
#define  HT_BA_RECEIVER                    (2)
#define  HT_BA_POLICY_INIT_RECEIVER        (3)
#define  HT_BA_DEF             (HT_BA_DISABLE)

#define  HT_BA_INACTIVITY_TIMEOUT_DEF  (10000)

#define RTS_THRESHOLD_DEF               (4096)

#define DOT_11_MODE_DEF          (DOT11_G_MODE)

#define CONSECUTIVE_PS_POLL_FAILURE_DEF    (4)

// BIT0: Tx MCS Set Defined
// BIT1: Tx Rx MCS Set Not Equal
// BIT2: Tx Maximum Number Spatial Streams Supported
// BIT3: Tx Unequal Modulation Supported
#define TX_MCS_SETTINGS_BM          (1)     // TX MCS set is defined & equals the RX set

#define        PHY_CFG_WIFI_PROTOCOL_AUTO    (0) // WiFi 1 to 6
#define        PHY_CFG_WIFI_PROTOCOL_LEGACY  (1) // WiFi 1 to 4

// ============================================================================
//		Modules data base
// ============================================================================
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991			0x00000001
#define IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT	23

// default configurations
l2CfgCommon_t gL2CommonCfg =
{
    .deviceSupportedBandsBM = BIT_x(RADIO_BAND_2_4GHZ)| BIT_x(RADIO_BAND_5GHZ),
    .iniIs5GHzEnabled = TRUE,
    .band40MHzEnabled = FALSE,                          // No 40MHz support
    .dot11nEnabled = TRUE,                              // All roles support 11n features
    .mimoEnabled = FALSE,                               // No MIMO support, MCS 8-15 are not supported
    .channelWidth40MHzEnabled = FALSE,                  // Support only 20MHz channles
    .fragThreshold = FRAG_THRESHOLD_DEFUALT,            // default fragmentation threshold
#ifndef DISABLE_WIFI6
    .heSupport     = TRUE,                              // default He support
#else
    .heSupport     = FALSE,
#endif 
    .heParams.tXMode                      = 2,
    .heParams.txFrag                      = 0,
    .heParams.mngInAggregation            = 0,
    .heParams.qosNullInAggr               = 0,
    .heParams.moreDataBit                 = 0,
    .heParams.heHeaderInHtSupp            = 1,
    .heParams.reserved                    = 0,

    .htCapabilities.ampduCfg.maxPackSize = MAX_MPDU_8191_OCTETS,   //8k bytes
    .htCapabilities.ampduCfg.spacing = AMPDU_SPC_16_MICROSECONDS,
    .htCapabilities.suppMcsSet.rxMscBitmask[0] = 0xff, // 0xff - in order to support MCS0-7, 0 - to avoid those rates
    .htCapabilities.suppMcsSet.rxMscBitmask[1] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[2] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[3] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[4] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[5] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[6] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[7] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[8] = 0,
    .htCapabilities.suppMcsSet.rxMscBitmask[9] = 0,
    .htCapabilities.suppMcsSet.highestSupportedDataRate = 72,           // MCS7 with short GI
    .htCapabilities.suppMcsSet.txSettingBM = TX_MCS_SETTINGS_BM,
    .htCapabilities.aselCapabilities = 0,
    .htCapabilities.extCapabilities = 0,
    .htCapabilities.txBfCapabilities = 0,
    .htCapabilities.htCapabBM =
                                // bit 0   -  Indicates support for receiving LDPC coded packets
                                // bit 1   -  0 - only 20 MHz operation is supported.
                                //            1 - both 20 MHz and 40 MHz operation is supported.
                                // bit 2|3 -  Indicates the spatial multiplexing power save mode.
                                //            0 - static SM power save mode.
                                //            1 - dynamic SM power save mode.
                                //            3 - SM Power Save disabled.
                                // bit 4   -  Indicates support for the reception of PPDUs with HT-greenfield format.
                   (BIT_x(5) | BIT_x(2)| BIT_x(3) | BIT(11)),    // bit 5   -  Indicates short GI support for the reception of packets with BW of 20Mhz.
                                // bit 6   -  Indicates short GI support for the reception of packets with BW of 40Mhz.
                                // bit 7   -  Indicates support for the transmission of PPDUs using STBC.
                                // bit 8|9 -  Indicate support for the reception of PPDUs using STBC
                                //            0 - no support.
                                //            1 - support of one spatial stream.
                                //            2 - support of one and two spatial streams.
                                //            3 - support of one, two and three spatial streams.
                                // bit 10  -  Indicates support for HTdelayed Block Ack operation.
                                // bit 11  -  Indicates maximum AMSDU length.
                                //            0 - 3839 octets
                                //            1 - 7935 octets
                                // bit 12  -  Indicates use of DSSS/CCK mode in a 20/40 MHz BSS.
                                //            In Beacon and Probe Response frames:
                                //              0 - if the BSS does not allow use of DSSS/CCK in 40 MHz.
                                //              1 - if the BSS does allow use of DSSS/CCK in 40 MHz.
                                //            Otherwise:
                                //              0 - if the STA does not use DSSS/CCK in 40 MHz.
                                //              1 - if the STA uses DSSS/CCK in 40 MHz.
                                // bit 13  - Indicates support for PSMP mechanism.
                                // bit 14  - Indicates whether APs receiving this information or reports of this
                                //           information are required to prohibit 40 MHz transmissions.
                                // bit 15  - Indicates support for the LSIG TXOP protection mechanism.


    /*HE Support Ver1- FPGA 0.45 minimum support (first day of bring up), what we think is must for establishing a connection*/

    //Mac cap
    .heCapabilities.heMacCapabilities.HTC_HE_Support                    = 1,
    .heCapabilities.heMacCapabilities.twtRequesterSupport               = 1,
    .heCapabilities.heMacCapabilities.twtResponderSupport               = 0,
    .heCapabilities.heMacCapabilities.DynamicFragSupport                = 0,
    .heCapabilities.heMacCapabilities.maxFragMsduAmsduExp               = 0,
    .heCapabilities.heMacCapabilities.minFragSize                       = 0,
    .heCapabilities.heMacCapabilities.triggerFrameMACPaddingDuration    = 2,
    .heCapabilities.heMacCapabilities.multiTIDAggregationRxSupport      = 7,
    .heCapabilities.heMacCapabilities.heLinkAdaptationSupport           = 0,
    .heCapabilities.heMacCapabilities.allAckSupport                     = 1,
    .heCapabilities.heMacCapabilities.trsSupport                        = 1,
    .heCapabilities.heMacCapabilities.bsrSupport                        = 1,
    .heCapabilities.heMacCapabilities.broadcastTWTSupport               = 0,
    .heCapabilities.heMacCapabilities.bitmap32bitBASupport              = 1,
    .heCapabilities.heMacCapabilities.muCascadingSupport                = 0,
    .heCapabilities.heMacCapabilities.ackEnabledAggregationSupport      = 1,
    .heCapabilities.heMacCapabilities.reserved                          = 0,
    .heCapabilities.heMacCapabilities.omControlSupport                  = 1,
    .heCapabilities.heMacCapabilities.ofdmaRASupport                    = 0,
    .heCapabilities.heMacCapabilities.maximumAMPDUlenExpExt             = 0,
    .heCapabilities.heMacCapabilities.amsduFragmentationSupport         = 0,
    .heCapabilities.heMacCapabilities.flexibleTWTScheduleSupport        = 0,
    .heCapabilities.heMacCapabilities.rxControlFrametoMultiBSS          = 1,
    .heCapabilities.heMacCapabilities.bsrpBqrpAmpduAggregation          = 0,
    .heCapabilities.heMacCapabilities.qtpSupport                        = 0,
    .heCapabilities.heMacCapabilities.bqrSupport                        = 0,
    .heCapabilities.heMacCapabilities.srpResponder                      = 0,
    .heCapabilities.heMacCapabilities.ndpFeedbackReportSupport          = 1,
    .heCapabilities.heMacCapabilities.opsSupport                        = 0,
    .heCapabilities.heMacCapabilities.amsduInAckEnabledAmpduSupport     = 1,
    .heCapabilities.heMacCapabilities.multiTidAggregationTxSupport      = 1,
    .heCapabilities.heMacCapabilities.ul2x996ToneRUSupport              = 0,
    .heCapabilities.heMacCapabilities.heDynamicSmPowerSave              = 0,
    .heCapabilities.heMacCapabilities.omControlULMUDataDisableRXSupport = 0,
    .heCapabilities.heMacCapabilities.puncturedSoundingSupport          = 0,
    .heCapabilities.heMacCapabilities.htAndVhtTriggerFrameRxSupport     = 1,

    //***** Phy Cap ****//
    .heCapabilities.hePhyCapabilities.reserved1                                         = 0,
    .heCapabilities.hePhyCapabilities.channelWidthSet                                   = 0,
    .heCapabilities.hePhyCapabilities.puncturedPreambleRx                               = 0,
    .heCapabilities.hePhyCapabilities.deviceClass                                       = 1,
    .heCapabilities.hePhyCapabilities.ldpcCodingInPayload                               = 0,
    .heCapabilities.hePhyCapabilities.heSuPPDUWith1xHeLTFand08usGI                      = 1,
    .heCapabilities.hePhyCapabilities.midambleTxRxMaxNSTS                               = 0,
    .heCapabilities.hePhyCapabilities.ndpWith4xHeLTFand32msGI                           = 1,
    .heCapabilities.hePhyCapabilities.stbcTxSmallerEqu80MHz                             = 0,
    .heCapabilities.hePhyCapabilities.stbcRxSmallerEqu80MHz                             = 0,
    .heCapabilities.hePhyCapabilities.dopplerTx                                         = 0,
    .heCapabilities.hePhyCapabilities.dopplerRx                                         = 0,
    .heCapabilities.hePhyCapabilities.fullBandwidthULmuMIMO                             = 1,
    .heCapabilities.hePhyCapabilities.partialBandwidthULmuMIMO                          = 0,
    .heCapabilities.hePhyCapabilities.dcmMaxConstellationTx                             = 0,
    .heCapabilities.hePhyCapabilities.dcmMaxNSStx                                       = 0,
    .heCapabilities.hePhyCapabilities.dcmMaxConstellationRx                             = 3,
    .heCapabilities.hePhyCapabilities.dcmMaxNSSrx                                       = 0,
    .heCapabilities.hePhyCapabilities.rxHEmuPPDUfromNonAPsta                            = 0,
    .heCapabilities.hePhyCapabilities.suBeamformer                                      = 0,
    .heCapabilities.hePhyCapabilities.suBeamformee                                      = 1,
    .heCapabilities.hePhyCapabilities.muBeamformer                                      = 0,
    .heCapabilities.hePhyCapabilities.beamformeeSTSsmallEqu80mHz                        = 3,
    .heCapabilities.hePhyCapabilities.beamformeeSTSbigger80mHz                          = 0,
    .heCapabilities.hePhyCapabilities.numberOfSoundingDimensionsSmallEqu80mHz           = 0,
    .heCapabilities.hePhyCapabilities.numberOfSoundingDimensionsBigger80mHz             = 0,
    .heCapabilities.hePhyCapabilities.ng16SUfeedback                                    = 1,
    .heCapabilities.hePhyCapabilities.ng16MUfeedback                                    = 1,
    .heCapabilities.hePhyCapabilities.codebookSize42SUfeedback                          = 1,
    .heCapabilities.hePhyCapabilities.codebookSize75mufeedback                          = 1,
    .heCapabilities.hePhyCapabilities.triggeredSUbeamformingfeedback                    = 1,
    .heCapabilities.hePhyCapabilities.triggeredMUbeamformingPartialBWfeedback           = 1,
    .heCapabilities.hePhyCapabilities.triggeredCQIFeedback                              = 1,
    .heCapabilities.hePhyCapabilities.partialBandwidthExtendedRange                     = 1,
    .heCapabilities.hePhyCapabilities.partialBandwidthDLmuMIMO                          = 0,
    .heCapabilities.hePhyCapabilities.ppeThresholdPresent                               = 0,
    .heCapabilities.hePhyCapabilities.srpBasedSRsupport                                 = 0,
    .heCapabilities.hePhyCapabilities.powerBoostFactorSupport                           = 0,
    .heCapabilities.hePhyCapabilities.heSUppduAndHEmuPPDUwith4xHEltfAnd08GI             = 1,
    .heCapabilities.hePhyCapabilities.maxNc                                             = 0,
    .heCapabilities.hePhyCapabilities.stbcTxBigger80MHz                                 = 0,
    .heCapabilities.hePhyCapabilities.stbcRxBigger80MHz                                 = 0,
    .heCapabilities.hePhyCapabilities.heERsuPPDUwith4xHEltfAnd08GI                      = 1,
    .heCapabilities.hePhyCapabilities.mHz20in40mHzHEppduIn24gHzBand                     = 1,
    .heCapabilities.hePhyCapabilities.mHz20in160or80plus80mHzHEppdu                     = 0,
    .heCapabilities.hePhyCapabilities.mHz80in160or80plus80mHzHEppdu                     = 0,
    .heCapabilities.hePhyCapabilities.heERsuPPDUwith1xHEltfAnd08GI                      = 1,
    .heCapabilities.hePhyCapabilities.midambleTxOrRx2xand1xHEltf                        = 0,
    .heCapabilities.hePhyCapabilities.dcmMaxBW                                          = 0,
    .heCapabilities.hePhyCapabilities.longerThan16heSIGbOFDMsymbolsSupport              = 0,
    .heCapabilities.hePhyCapabilities.nonTriggeredCQIfeedback                           = 1,
    .heCapabilities.hePhyCapabilities.tx1024QAM242toneRUsupport                         = 0,
    .heCapabilities.hePhyCapabilities.rx1024QAM242toneRUSupport                         = 0,
    .heCapabilities.hePhyCapabilities.rxFullBWsuUsingHEmuPPDUwithCompressedSIGB         = 1,
    .heCapabilities.hePhyCapabilities.rxFullBWsuUsingHEmuPPDUWithNonCompressedSIGB      = 1,
    .heCapabilities.hePhyCapabilities.nominalPacketPadding                              = 2,
    .heCapabilities.hePhyCapabilities.reserved2                                         = 0,
    .vhtCapabilities.cap                                                                =  
                                                                    (IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 | (1 << 
                                                                            IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT)),
    .vhtCapabilities.vht_mcs = {
			.rx_mcs_map = (0xfffc),
			.rx_highest = 7,
			.tx_mcs_map = (0xfffc),
			.tx_highest = 7,
	},
    .iniMixedModeEnabled = TRUE,
};

l2CfgCommon_t *gpL2CommonCfg  ;

Bool32 gL2SupportHe = FALSE;

uint8_t gCfgApSaeAntiCloggingThreshold = SAE_ANTI_CLOGGING_DEFAULT;

const cfgSta_t gL2StaBasedCfg =
{
    .shortPreamble = TRUE,
    .shortSlot = TRUE,
    .basicRatesBM = ANY_RATE,
    .supportedRatesBM = ANY_RATE,           // STA supports all 11b, 11g rates + MCS0-7
    .rtsThreshold = RTS_THRESHOLD_DEF,
    .dot11Mode = DOT11_DUAL_MODE,//DOT_11_MODE_DEF,
    .consecutivePsPollDeliveryFailureThreshold = CONSECUTIVE_PS_POLL_FAILURE_DEF,
    .maxTxRetriesThreshold = MAX_TX_RETRIES_THRESHOLD_DEFAULT_STA,  // Default max TX retries threshold
    .secondChanceTxTimePeriod = SECOND_CHANCE_TX_TIMER_PERIOD_STA_USEC, //Default second chance tx time period
    .sched_scan_default_plan = "10",              //Scan plans for scheduled scan,
                                                  //format: <interval:iterations> <interval2:iterations2> ... <interval>
                                                  //(see config.h)
                                                  //Changed to longer intervals after adding 5Ghz scan to plan.
                                                  //Sched scan starts after 3 retries (internal to the supplicant) of normal scan
    .pmf  = TRUE,                                 //pmf is set to capable always
    .pbac = FALSE                                 //when enabled, applies only if the connection is pmf and peer supports pbac as well
};

const qosCfgSta_t gL2StaQosCfg =
{
    .wmeEnable = TRUE,
    .trafficAdmCtrlEnable = FALSE,
    .packetBurstEnable = FALSE,
    .psPollTimeoutMS = QOS_RX_TIMEOUT_PS_POLL_DEF,
    .upsdTimeoutMS = QOS_RX_TIMEOUT_UPSD_DEF,
    .ackPolicy[AC_BE] = ACK_POLICY_DEF,
    .ackPolicy[AC_BK] = ACK_POLICY_DEF,
    .ackPolicy[AC_VO] = ACK_POLICY_DEF,
    .ackPolicy[AC_VI] = ACK_POLICY_DEF,
                    //+-----------------+----------------+----------------+---------------+----------------+---------------+
                    //|   AIFSN         |  CWmin         |  CWmax         | TXop limit    |   acm
                    //+-----------------+----------------+----------------+---------------+----------------+---------------+
    .acCfg[AC_BE] = {    AIFSN_BE       , CWMIN_BE       , CWMAX_BE       , TXOP_BE       , FALSE },
    .acCfg[AC_BK] = {    AIFSN_BK       , CWMIN_BK       , CWMAX_BK       , TXOP_BK       , FALSE },
    .acCfg[AC_VI] = {    AIFSN_VI       , CWMIN_VI       , CWMAX_VI       , TXOP_VI       , FALSE },
    .acCfg[AC_VO] = {    AIFSN_VO       , CWMIN_VO       , CWMAX_VO       , TXOP_VO       , FALSE },
    
    .burstModeEnabled = FALSE,
    .baPolicy = HT_BA_POLICY_INIT_RECEIVER | (HT_BA_DEF << 2) |
                (HT_BA_DEF << 4)  | (HT_BA_DEF << 6) |
                (HT_BA_DEF << 8)  |(HT_BA_DEF << 10) |
                (HT_BA_DEF << 12) | (HT_BA_DEF << 14),
    .baInactivityTimeout = HT_BA_INACTIVITY_TIMEOUT_DEF
};



const cfgAp_t gL2ApCfg =
{
    .maxTxRetriesThreshold = MAX_TX_RETRIES_THRESHOLD_DEFAULT_AP,  // Default max TX retries threshold
    .secondChanceTxTimePeriod = SECOND_CHANCE_TX_TIMER_PERIOD_AP_USEC, //Default second chance tx time period
    .dtimInterval = 2,
    .beaconIntervalTU = 100,

    .basicRateSetBM = BIT_x(RATE_INDEX_6MBPS) | BIT_x(RATE_INDEX_12MBPS) | BIT_x(RATE_INDEX_24MBPS),

    // Allow all BG rates; if HT is supported MCS rates are added in run time.
    .supportedRatesBM =   (ANY_B_RATE | ANY_AG_OFDM_RATE),

    .pmf = FALSE
//

};

l2cfgSta_t  gCfgSta           ;
l2cfgSta_t* gpL2StaBasedCfg   ;

l2cfgAp_t   gCfgAp            ;
l2cfgAp_t*  gpL2ApBasedCfg    ;

// This structure contains the parameters for L2 cfg that can be configured by the host or for testing / debug
l2DynamicCfg_t gL2DynamicCfg     =
{
        // Configurations per AC
        .acPsMode.wmeAcPsMode[AC_BE] = PS_SCHEME_DEF,
        .acPsMode.wmeAcPsMode[AC_BK] = PS_SCHEME_DEF,
        .acPsMode.wmeAcPsMode[AC_VO] = PS_SCHEME_DEF,
        .acPsMode.wmeAcPsMode[AC_VI] = PS_SCHEME_DEF,
//        .psMode = PS_SCHEME_LEGACY, // PS_SCHEME_UPSD_TRIGGER //TODO: for AP?
        .maxSpLen         = QOS_MAX_SP_LEN_DEF,
        .ApMaxNumStations = AP_DEFAULT_MAX_NUM_OF_STATIONS,
        .selectedBand     =  L2_CFG_BAND_BOTH,
#ifndef DISABLE_WIFI6
        .wirelessProtocol = PHY_CFG_WIFI_PROTOCOL_AUTO
#else
        .wirelessProtocol = PHY_CFG_WIFI_PROTOCOL_LEGACY
#endif
};


wpsParameters_t gWpsParameters = 
{
    .uuid = { 0 },
    .device_name = NULL,
    .manufacturer = NULL,
    .model_name = NULL,
    .model_number = NULL,
    .serial_number = NULL,
    .device_type = { 0 },
    .os_version = { 0 },
    .config_methods = NULL
};

SupplicantCfg_t gSupplicantCfg = 
{
    .wpsParams = NULL,
    .wpsDisabled = 1
};

P2pParameters_t gP2pParameters = 
{
    .p2pListenRegClass = 0,
    .p2pListenChannel = 0,
    .p2pOperRegClass = 0,
    .p2pOperChannel = 0,
    .p2pGoIntent = 0,
    .p2pPersistent = 0,
    .p2pSsidPostfix = NULL,
    .reserved = 0
};

P2pSupplicantCfg_t gP2pSupplicantCfg = 
{
    .p2pParams = NULL,
    .p2pDisabled = 1
};

wpsParameters_t *gpWpsParameters = NULL;
SupplicantCfg_t *gpSupplicantCfg = NULL;
P2pSupplicantCfg_t *gpP2pSupplicantCfg = NULL;


// ============================================================================
//		Local Functions declarations
// ============================================================================

// ============================================================================
//		Exported Functions
// ============================================================================

void l2_cfg_Init()
{
    // Use default configurations - globals point to hard coded configurations.
    // If dynamic configuration is needed, globals can be updated.
    gCfgSta.pStaCfg     = &gL2StaBasedCfg;
    gCfgSta.pQosCfg     = &gL2StaQosCfg;
    gCfgSta.pCommonCfg  = &gL2CommonCfg;

    gCfgAp.pCommonCfg   = &gL2CommonCfg;
    gCfgAp.pQosCfg      = &gL2StaQosCfg; // use the same CFG for AP & STA role, at least for the meantime
    gCfgAp.pApCfg       = &gL2ApCfg;


    gpL2StaBasedCfg     = &gCfgSta;
    gpL2CommonCfg       = (l2CfgCommon_t *) &gL2CommonCfg;

    gpL2ApBasedCfg      = &gCfgAp;

    gpSupplicantCfg     = &gSupplicantCfg;
    gpSupplicantCfg->wpsParams = &gWpsParameters;

    gpP2pSupplicantCfg = &gP2pSupplicantCfg;
    gpP2pSupplicantCfg->p2pParams = &gP2pParameters;

}

void l2_cfg_Dynamic_set(l2DynamicCfgParamId_e paramIndex, uint8_t *paramValue)
{
    // GTRACE(GRP_DRIVER_CC33, "l2_cfg_Dynamic. Params name: ENUM(l2DynamicCfgParamId_e,%d), parameter value: 0x%x",
    //        paramIndex,
    //        (uint32_t)paramValue);

    switch (paramIndex)
    {
        case (L2_AC_PS_MODE):
                //Note: PSScheme_e size is uint8_t so it is safe to cast (AcPsMode_t *) from the SL_device_set command
                gL2DynamicCfg.acPsMode.wmeAcPsMode[0] = ((AcPsMode_t *)paramValue)->wmeAcPsMode[0];
                gL2DynamicCfg.acPsMode.wmeAcPsMode[1] = ((AcPsMode_t *)paramValue)->wmeAcPsMode[1];
                gL2DynamicCfg.acPsMode.wmeAcPsMode[2] = ((AcPsMode_t *)paramValue)->wmeAcPsMode[2];
                gL2DynamicCfg.acPsMode.wmeAcPsMode[3] = ((AcPsMode_t *)paramValue)->wmeAcPsMode[3];
                break;
//        case (L2_PS_MODE):
//                gL2DynamicCfg.psMode = (PSScheme_e)*paramValue;
//                break;
        case (L2_MAX_SP_LEN):
                gL2DynamicCfg.maxSpLen = *paramValue;
                break;
    }
}


int l2_cfg_GetStaHeSupport()
{
    int ret_status = 0;
    uint8 iniHeEnabled = gpL2CommonCfg->heSupport;
    uint8 fuseHeDisabled;
    DeviceSystemInfo_t deviceSystemInfoParams;
    deviceSystemInfoParams.systemInfoIdx = SYSTEM_INFO_WIFI6_DISABLE_IDX;
    
    ret_status = Wlan_Get(WLAN_GET_SYSINFO, (void *)&deviceSystemInfoParams);
    
    if (ret_status < 0)
    {
        Report("\n\rl2_cfg.c, l2_cfg_isStaHeEnabled return status failed!");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH,
                         WLAN_ERROR_MODULE__FW_RESPONSE,
                         WLAN_ERROR_TYPE__CMD_GENERAL);
    }
    
    fuseHeDisabled = deviceSystemInfoParams.deviceSystemInfoValue;
    
    if ((fuseHeDisabled == 0) && (iniHeEnabled == 1))
    {
        gL2SupportHe = TRUE;
    }
    else
    {
        gL2SupportHe = FALSE;
    }

    return 0;
}

/* ----------------------------------------------------------------------------
 l2_cfg_isStaHeEnabled
      This function checks whether HE is enabled for STA based roles.

 Parameters:
     none

 return: TRUE - HE enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 l2_cfg_isStaHeEnabled(void)
{
#ifndef DISABLE_WIFI6
    return gL2SupportHe;
#else
    return FALSE;
#endif
}


/* ----------------------------------------------------------------------------
 cfgIsStaWmeEnabled
 This function checks whether WME is enabled for STA based roles.
 (For AP based roles, WME support is defined by supplicant configuration.

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 l2_cfgIsStaWmeEnabled()
{
    return gpL2StaBasedCfg->pQosCfg->wmeEnable;
}


/* ----------------------------------------------------------------------------
 l2_cfg_certificate
      This function is used for debug configuration for certification

 Parameters:


 return: none
---------------------------------------------------------------------------- */
void  l2_cfg_certificate(void)
{

}


/* ----------------------------------------------------------------------------
    l2Cfg_InitDevice

 Parameters:    none
 Return code:   none

 ---------------------------------------------------------------------------- */
#ifdef COMPILE_DEAD_FUNC
void l2Cfg_InitCommon()
{

}
#endif
// ----------------------------------------------------------------------------
void cfgGetRates(RoleType_e aRoleType, uint32_t *apBasicRatesBM, uint32_t *apSupportedRatesBM)
{
    if (ROLE_IS_TYPE_STA_BASED(aRoleType))
    {
        *apBasicRatesBM = gpL2StaBasedCfg->pStaCfg->basicRatesBM;
        *apSupportedRatesBM = gpL2StaBasedCfg->pStaCfg->supportedRatesBM;
        if (gpL2StaBasedCfg->pCommonCfg->dot11nEnabled)
        {
            // Set the supported mcs rates, into the proper place in the bitmap
            *apSupportedRatesBM |=  (gpL2StaBasedCfg->pCommonCfg->htCapabilities.suppMcsSet.rxMscBitmask[0]) << RATE_INDEX_MCS0;
            //if (*apSupportedRatesBM & BIT_x(RATE_INDEX_MCS7))
            //{
            //    *apSupportedRatesBM |= BIT_x(RATE_INDEX_MCS7_SGI);
            //}
        }
    }
    else if (ROLE_IS_TYPE_DEVICE(aRoleType))
    {
        *apBasicRatesBM = gpL2StaBasedCfg->pStaCfg->basicRatesBM;
        *apSupportedRatesBM = gpL2StaBasedCfg->pStaCfg->supportedRatesBM;
        if (gpP2pSupplicantCfg->p2pDisabled == FALSE)
        {
            //In p2p device mgmt frame 11b rate are deprecated 
            //so we omit these rate for p2p device role only
            *apSupportedRatesBM &= ~ ANY_B_RATE;
        }
        if (gpL2StaBasedCfg->pCommonCfg->dot11nEnabled)
        {
            // Set the supported mcs rates, into the proper place in the bitmap
            *apSupportedRatesBM |=  (gpL2StaBasedCfg->pCommonCfg->htCapabilities.suppMcsSet.rxMscBitmask[0]) << RATE_INDEX_MCS0;
            //if (*apSupportedRatesBM & BIT_x(RATE_INDEX_MCS7))
            //{
            //    *apSupportedRatesBM |= BIT_x(RATE_INDEX_MCS7_SGI);
            //}
        }
    }
    else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        *apBasicRatesBM = gpL2ApBasedCfg->pApCfg->basicRateSetBM;
        *apSupportedRatesBM = gpL2ApBasedCfg->pApCfg->supportedRatesBM;

        if (gpL2ApBasedCfg->pCommonCfg->dot11nEnabled)
        {
            // Set the supported mcs rates, into the proper place in the bitmap
            *apSupportedRatesBM |=  (gpL2ApBasedCfg->pCommonCfg->htCapabilities.suppMcsSet.rxMscBitmask[0]) << RATE_INDEX_MCS0;
            //if (*apSupportedRatesBM & BIT_x(RATE_INDEX_MCS7))
            //{
            //    *apSupportedRatesBM |= BIT_x(RATE_INDEX_MCS7_SGI);
            //}
        }
    }
}


//---------------------------------------------------------------
Bool32 cfgGetWmmParameters(const AcCfg_t **pAcCfg)
{
    if (FALSE == gpL2CommonCfg)
    {
        return FALSE;
    }

    *pAcCfg = (const AcCfg_t *)&(gpL2ApBasedCfg->pQosCfg->acCfg);

    return TRUE;

}
// ----------------------------------------------------------------------------
Bool32 l2_cfgGetHtCapabilities(const htCapabilities_t **apHtCapabilities)
{
    if (FALSE == gpL2CommonCfg->dot11nEnabled)
    {
        // GTRACE(GRP_DRIVER_CC33, "Device doesn't support 11n");
        return FALSE;
    }

    // Currently as no MIMO nor 40 MHz are required they are not handled here.
    // If in the futue they're supported, some code should be imported from MCP.

    *apHtCapabilities = &gpL2CommonCfg->htCapabilities;
    return TRUE;
}


// ----------------------------------------------------------------------------
uint8_t cfgGetMaxTxRetriesThreshold (RoleType_e aRoleType)
{
    if (ROLE_IS_TYPE_STA_BASED(aRoleType))
    {
        return gpL2StaBasedCfg->pStaCfg->maxTxRetriesThreshold;
    }
    else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        return gpL2ApBasedCfg->pApCfg->maxTxRetriesThreshold;
    }
    else
    {
        return 0;
    }
}


// ----------------------------------------------------------------------------
uint32_t cfgGetsecondChanceTxTimePeriod (RoleType_e aRoleType)
{
    if (ROLE_IS_TYPE_STA_BASED(aRoleType))
    {
        return gpL2StaBasedCfg->pStaCfg->secondChanceTxTimePeriod;
    }
    else if (ROLE_IS_TYPE_AP_BASED(aRoleType))
    {
        return gpL2ApBasedCfg->pApCfg->secondChanceTxTimePeriod;
    }
    else
    {
        return 0;
    }
}

#ifndef DISABLE_WIFI6
// ----------------------------------------------------------------------------
uint32_t l2_cfgBuildHeCapabilitiesIe(uint32_t aRoleId, uint8_t *apHeCapsIE)
{
    uint8 *pNextPos;
    heMcsCapabilities * mcsCap;
    //hePhyCapabilities_t *phyCap;

    /* build IE */
    apHeCapsIE[0] = EID_EXTENSION;
    apHeCapsIE[1] = DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN; //22 Bytes
    apHeCapsIE[2] = HE_CAPABILITIES_IE_ID;

    os_memcpy(&apHeCapsIE[3], gpL2CommonCfg->heCapabilities.heMacCapabilities._w32, HE_MAC_CAP_LEN_IN_BYTES);
    pNextPos = &apHeCapsIE[3]+ HE_MAC_CAP_LEN_IN_BYTES;

    os_memcpy(pNextPos, gpL2CommonCfg->heCapabilities.hePhyCapabilities._w32, HE_PHY_CAP_LEN_IN_BYTES);
    pNextPos = pNextPos + HE_PHY_CAP_LEN_IN_BYTES;

/*

    os_memset(&phyCap, 0, HE_PHY_CAP_LEN_IN_BYTES);

    phyCap-> deviceClass = 1;
    phyCap-> heSUppduAndHEmuPPDUwith4xHEltfAnd08GI = 1;
    phyCap-> dcmMaxConstellationTx = 2;
    phyCap-> dcmMaxConstellationRx = 3;
    phyCap-> ng16SUfeedback = 1;
    phyCap-> mHz20in40mHzHEppduIn24gHzBand = 1;
    phyCap-> heERsuPPDUwith1xHEltfAnd08GI =1;
    phyCap-> rxFullBWsuUsingHEmuPPDUWithNonCompressedSIGB =1;

    phyCap->channelWidthSet                       =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.channelWidthSet;
    phyCap->ldpcCodingInPayload                   =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.ldpcCodingInPayload;
    phyCap->midambleTxRxMaxNSTS                   =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.midambleTxRxMaxNSTS;
    phyCap->stbcTxSmallerEqu80MHz                 =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.stbcTxSmallerEqu80MHz;
    phyCap->stbcRxSmallerEqu80MHz                 =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.stbcRxSmallerEqu80MHz;
    phyCap->dopplerTx                             =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.dopplerTx;
    phyCap->dopplerRx                             =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.dopplerRx;
    phyCap->dcmMaxNSStx                           =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.dcmMaxNSStx;
    phyCap->dcmMaxNSSrx                           =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.dcmMaxNSSrx;
    phyCap->rxHEmuPPDUfromNonAPsta                =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.rxHEmuPPDUfromNonAPsta;
    phyCap->suBeamformer                          =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.suBeamformer;
    phyCap->muBeamformer                          =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.muBeamformer;
    phyCap->beamformeeSTSbigger80mHz              =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.beamformeeSTSbigger80mHz;
    phyCap->numberOfSoundingDimensionsBigger80mHz =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.numberOfSoundingDimensionsBigger80mHz;
    phyCap->maxNc                                 =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.maxNc;
    phyCap->stbcTxBigger80MHz                     =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.stbcTxBigger80MHz;
    phyCap->stbcRxBigger80MHz                     =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.stbcRxBigger80MHz;
    phyCap->midambleTxOrRx2xand1xHEltf            =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.midambleTxOrRx2xand1xHEltf;
    phyCap->rx1024QAM242toneRUSupport             =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.tx1024QAM242toneRUsupport;
    phyCap->rx1024QAM242toneRUSupport             =  gpL2CommonCfg-> heCapabilities.hePhyCfgCapabilities.rx1024QAM242toneRUSupport;
     */

    mcsCap = (heMcsCapabilities *)pNextPos;

    mcsCap->rxHeMcsMap80MHz  =  host_to_le16(HE_MSC_CAP_MCS_0_TO_7);
    mcsCap->txHeMcsMap80MHz  =  host_to_le16(HE_MSC_CAP_MCS_0_TO_7);

    return (DOT11_HE_CAPABILITIES_MIN_TOTAL_LEN + sizeof(dot11_eleHdr_t));
}
#endif

void l2_StoreWirelessProto(uint8_t proto)
{
    /*
        DOT11_PROTOCOL_AUTO = 0
        DOT11_PROTOCOL_LEGACY = 1
    */
#ifndef DISABLE_WIFI6
    gL2DynamicCfg.wirelessProtocol = proto;
#else
    gL2DynamicCfg.wirelessProtocol = PHY_CFG_WIFI_PROTOCOL_LEGACY;
#endif 
}

uint8_t l2_GetWirelessProto()
{
    /*
        DOT11_PROTOCOL_AUTO = 0
        DOT11_PROTOCOL_LEGACY = 1
    */
#ifndef DISABLE_WIFI6
    return gL2DynamicCfg.wirelessProtocol;
#else
    return PHY_CFG_WIFI_PROTOCOL_LEGACY;
#endif
}

void l2_StorePhyConfig(uint8_t band_cfg)
{
    /*
        DOT11_BAND_ONLY_2_4GHZ = 0
        DOT11_BAND_ONLY_5GHZ = 1 
        DOT11_BAND_BOTH = 2
    */

    gL2DynamicCfg.selectedBand = band_cfg;
}

uint8_t l2_GetPhyConfig()
{
    /*
        DOT11_BAND_ONLY_2_4GHZ = 0
        DOT11_BAND_ONLY_5GHZ = 1 
        DOT11_BAND_BOTH = 2
    */

    return gL2DynamicCfg.selectedBand;
}

uint32_t l2_cfgBuildOperatingModeNotifcationIe(uint32_t aRoleId, uint8_t *operatingModeNotifIE)
{
    uint8 opmode_notif = 0; 
	uint8 rx_nss = 0; 
	uint8 rx_nss_type = 0;

    /* dot11_eleHdr_t */
    operatingModeNotifIE[0] = OPMODE_NOTIF_IE_ID;
    operatingModeNotifIE[1] = DOT11_OPERATING_MOD_NOTIF_ELE_LEN;

    //for 20mhz only defines
#define IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ	(0)
 #define IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT	 (4)

	/*  Operating Mode Notification element */
	rx_nss = 0;
	rx_nss_type= 0;
	opmode_notif |= IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ; 
	rx_nss <<= IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
	rx_nss_type <<= (IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT + 3);
	opmode_notif |= rx_nss;
	opmode_notif |= rx_nss_type;
	
    operatingModeNotifIE[2] = opmode_notif;//0 for 20mhz


    return (DOT11_OPERATING_MOD_NOTIF_ELE_LEN + sizeof(dot11_eleHdr_t)); 
}

#ifndef DISABLE_WIFI6
uint32_t l2_cfgBuildVhtCapabilitiesIe(uint32_t aRoleId, uint8_t *apVhtCapsIE)
{
    uint16  tNextWord;

    /* dot11_eleHdr_t */
    apVhtCapsIE[0] = VHT_CAPABILITY_IE_ID;
    apVhtCapsIE[1] = DOT11_VHT_CAPABILITIES_ELE_LEN;

    tNextWord = host_to_le32(gpL2CommonCfg->vhtCapabilities.cap);

    os_memcpy(&apVhtCapsIE[2],&tNextWord, sizeof(tNextWord));

    os_memcpy(&apVhtCapsIE[6], &(gpL2CommonCfg->vhtCapabilities.vht_mcs), sizeof(uint16) * 4);


    return (DOT11_VHT_CAPABILITIES_ELE_LEN + sizeof(dot11_eleHdr_t)); 
}
#endif

// ----------------------------------------------------------------------------
uint32_t l2_cfgBuildHtCapabilitiesIe(uint32_t aRoleId, uint8_t *apHtCapsIE)
{
    uint16  tNextWord;
    uint32  tNexLong;

    if (FALSE == gpL2CommonCfg->dot11nEnabled)
    {
        // GTRACE(GRP_DRIVER_CC33, "Device doesn't support 11n, no HT capabilities IE");
        return 0;
    }

    /* dot11_eleHdr_t */
    apHtCapsIE[0] = HT_CAPABILITIES_IE_ID;
    apHtCapsIE[1] = DOT11_HT_CAPABILITIES_ELE_LEN;

    tNextWord = host_to_le16(gpL2CommonCfg->htCapabilities.htCapabBM);
    os_memcpy(&apHtCapsIE[2],&tNextWord, sizeof(tNextWord));


    apHtCapsIE[4] = *((uint8_t *)&gpL2CommonCfg->htCapabilities.ampduCfg);


    os_memcpy(&apHtCapsIE[5], gpL2CommonCfg->htCapabilities.suppMcsSet.rxMscBitmask, RX_MCS_BITMASK_SIZE);

    tNextWord = host_to_le16(gpL2CommonCfg->htCapabilities.suppMcsSet.highestSupportedDataRate);
    os_memcpy(&apHtCapsIE[15],&tNextWord, sizeof(tNextWord));


    apHtCapsIE[17] = gpL2CommonCfg->htCapabilities.suppMcsSet.txSettingBM;

    /* clear the reserved bytes */
    os_memset(&apHtCapsIE[18], 0, 3);

    tNextWord = host_to_le16(gpL2CommonCfg->htCapabilities.extCapabilities);
    os_memcpy(&apHtCapsIE[21],&tNextWord, sizeof(tNextWord));


    tNexLong = host_to_le32(gpL2CommonCfg->htCapabilities.txBfCapabilities);
    os_memcpy(&apHtCapsIE[23],&tNexLong, sizeof(tNexLong));

    apHtCapsIE[27] = gpL2CommonCfg->htCapabilities.aselCapabilities;

    return (DOT11_HT_CAPABILITIES_ELE_LEN + sizeof(dot11_eleHdr_t));
}

// ----------------------------------------------------------------------------
uint8_t cfgGetApMaxNumStations (void)
{
    return gL2DynamicCfg.ApMaxNumStations;
}

// ----------------------------------------------------------------------------
void cfgSetApMaxNumStations(uint8_t apMaxNumStations)
{
    gL2DynamicCfg.ApMaxNumStations = apMaxNumStations;
}

// ----------------------------------------------------------------------------
uint8_t cfgGetApMaxNumStationsFromConfIni (void)
{
    return gL2DynamicCfg.ApMaxNumStationsFromConfIni;
}

// ----------------------------------------------------------------------------
void cfgSetApMaxNumStationsFromConfIni(uint8_t apMaxNumStationsFromConfIni)
{
    gL2DynamicCfg.ApMaxNumStationsFromConfIni = apMaxNumStationsFromConfIni;
}

/* ----------------------------------------------------------------------------
 cfgGetFragThreshold
 This function retrieves the Fragmentation Threshold

 Parameters:
 none

 return: number of bytes of Fragmentation Threshold
 ---------------------------------------------------------------------------- */
uint16_t cfgGetFragThreshold()
{
    return gpL2CommonCfg->fragThreshold;
}

// ----------------------------------------------------------------------------
Bool32 l2_cfg_is5GhzSupported(void)
{
    return cfgGetDeviceSupportedBandsBM() & BIT(RADIO_BAND_5GHZ);
}

// ----------------------------------------------------------------------------
int8_t l2_cfg_setDevice5GhzSupport()
{
    int8_t ret = 0;
    DeviceSystemInfo_t deviceSystemInfoParams;
    Bool32 fuse5GhzSupport, ini5GHzSupport;

    deviceSystemInfoParams.systemInfoIdx = SYSTEM_INFO_PAPER_SPIN_DISABLE_5GHZ_IDX;
    ret = Wlan_Get(WLAN_GET_SYSINFO, (void *)&deviceSystemInfoParams);
    if (ret != 0)
    {
        return WlanError(WLAN_ERROR_SEVERITY__HIGH,
                         WLAN_ERROR_MODULE__FW_RESPONSE,
                         WLAN_ERROR_TYPE__CMD_GENERAL);
    }

    /* Device system info value indicates whether 5 GHz is disabled */
    fuse5GhzSupport = deviceSystemInfoParams.deviceSystemInfoValue == TRUE ?
                      FALSE :
                      TRUE;

    ini5GHzSupport = gpL2CommonCfg->iniIs5GHzEnabled;

    if (fuse5GhzSupport && ini5GHzSupport)
    {
        cfgSetDeviceSupportedBandsBM(cfgGetDeviceSupportedBandsBM() | BIT(RADIO_BAND_5GHZ));
        CME_PRINT_REPORT("\n\rDevice support 5GHz band operations\n\r");
    }
    else
    {
        cfgSetDeviceSupportedBandsBM(cfgGetDeviceSupportedBandsBM() & (~BIT(RADIO_BAND_5GHZ)));
        CME_PRINT_REPORT("\n\rDevice doesn't support 5GHz band operations (INI: %s, FUSE: %s)\n\r",
                         ini5GHzSupport ? "SUPPORTED" : "NOT SUPPORTED",
                         fuse5GhzSupport ? "SUPPORTED" : "NOT SUPPORTED");
    }

    return 0;
}

// ----------------------------------------------------------------------------
Bool32 l2_cfg_isMixedModeSupported(void)
{
    return gpL2CommonCfg->iniMixedModeEnabled;
}

// ----------------------------------------------------------------------------
void cfgSetApSaeAntiCloggingThreshold(uint8_t apSaeAntiCloggingThreshold)
{

    if ((apSaeAntiCloggingThreshold == SAE_ANTI_CLOGGING_ALWAYS) ||
        (apSaeAntiCloggingThreshold == SAE_ANTI_CLOGGING_LOW) || 
        (apSaeAntiCloggingThreshold == SAE_ANTI_CLOGGING_DEFAULT))
    {
        gCfgApSaeAntiCloggingThreshold = apSaeAntiCloggingThreshold;
    }
       
}

// ----------------------------------------------------------------------------
uint8_t cfgGetApSaeAntiCloggingThreshold(void)
{
    return gCfgApSaeAntiCloggingThreshold;
}

// ============================================================================
//      The APIs below are used for fetching STA based configurations
// ============================================================================

/* ----------------------------------------------------------------------------
 cfgIsStaWmeEnabled
 This function checks whether WME is enabled for STA based roles.
 (For AP based roles, WME support is defined by supplicant configuration.

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsStaWmeEnabled()
{
    return gpL2StaBasedCfg->pQosCfg->wmeEnable;
}

/* ----------------------------------------------------------------------------
 cfgIsApWmeEnabled
 This function checks whether WME is enabled for AP based roles.
 (For AP based roles, WME support is defined by supplicant configuration.

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsApWmeEnabled()
{
    return gpL2ApBasedCfg->pQosCfg->wmeEnable;
}

/* ----------------------------------------------------------------------------
 cfgIsApMfpEnabled
 This function checks whether PMF is enabled for AP based roles.

 Parameters:
 none

 return: TRUE - PMF enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsApPmfEnabled()
{
    return gpL2ApBasedCfg->pApCfg->pmf;
}

/* ----------------------------------------------------------------------------
 cfgIsStaPmfEnabled
 This function checks whether PMF is enabled for STA based roles.

 Parameters:
 none

 return: TRUE - PMF enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsStaPmfEnabled()
{
    return gpL2StaBasedCfg->pStaCfg->pmf;
}

/* ----------------------------------------------------------------------------
 cfgIsStaPbacEnabled
 This function checks whether PBAC is enabled for STA based roles.

 Parameters:
 none

 return: TRUE - Pbac enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsStaPbacEnabled()
{
    return gpL2StaBasedCfg->pStaCfg->pbac;
}

/* ----------------------------------------------------------------------------
 cfgGetCwMin/cfgGetCwMax
 These functions return the default values for QOS parameters

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
const AcCfg_t* cfgGetDefaultAcCfg(uint8_t ac)
{
    return &(gpL2StaBasedCfg->pQosCfg->acCfg[ac]);
}

/* ----------------------------------------------------------------------------
 cfgGetStaDefaultSchedScanPlans
 This function returns the default scan plans for scheduled scan.

 Parameters:
 none

 return: default sched scan plans
 ---------------------------------------------------------------------------- */
const char* cfgGetStaDefaultSchedScanPlans()
{
    return gpL2StaBasedCfg->pStaCfg->sched_scan_default_plan;
}

/* ----------------------------------------------------------------------------
 cfgIsStaShortPreambleEnabled
 This function checks whether short preamble is enabled for B rates for
 STA based roles.
 If default preamble is short and peer requires long peramble, it is updated
 on role's DB. TODO - verify where exactly.
 (For AP based roles, preamble type is defined by supplicant configuration).

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsStaShortPreambleEnabled()
{
    return gpL2StaBasedCfg->pStaCfg->shortPreamble;
}

/* ----------------------------------------------------------------------------
 cfgGetStadot11Mode
 This function returns the 802.11 supported mode/modes for STA based role

 Parameters:
 none

 return: STA supported modes
 ---------------------------------------------------------------------------- */
dot11Mode_e cfgGetStadot11Mode()
{
    return gpL2StaBasedCfg->pStaCfg->dot11Mode;
}

/* ----------------------------------------------------------------------------
 cfgIsStaShortSlotEnabled
 This function checks whether short slot is enabled for STA based roles.
 If default slot is short and peer requires long slot, it is updated
 on role's DB. TODO - verify where exactly.
 (For AP based roles, slot type is defined by supplicant configuration).

 Parameters:
 none

 return: TRUE - WME enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIsStaShortSlotEnabled()
{
    return gpL2StaBasedCfg->pStaCfg->shortSlot;
}
// ============================================================================
//      The APIs below are used for fetching AP based configurations
// ============================================================================

/* ----------------------------------------------------------------------------
 cfgGetApCfg
 This function retruns AP configuration

 Parameters:
 apCfg - OUT pointer to AP configuration

 return:
 ---------------------------------------------------------------------------- */
const cfgAp_t* cfgGetApCfg()
{
    return gpL2ApBasedCfg->pApCfg;
}

/* ----------------------------------------------------------------------------
 cfgIs11nEnabled
 This function checks whether HT is enabled

 Parameters:
 none

 return: TRUE - HT enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIs11nEnabled()
{
    return gpL2CommonCfg->dot11nEnabled;
}

/* ----------------------------------------------------------------------------
 cfgIs40MHzEnabled
 This function checks whether 40MHz channel is enabled

 Parameters:
 none

 return: TRUE - 40MHz channel enabled, FALSE not enabled
 ---------------------------------------------------------------------------- */
Bool32 cfgIs40MHzEnabled()
{
    return gpL2CommonCfg->band40MHzEnabled;
}

/* ----------------------------------------------------------------------------
 cfgIsMimoEnabled
      This function checks whether HT is enabled

 Parameters:
     none

 return: TRUE - HT enabled, FALSE not enabled
---------------------------------------------------------------------------- */
Bool32 cfgIsMimoEnabled()
{
    return gpL2CommonCfg->mimoEnabled;
}


// ----------------------------------------------------------------------------
// TODO - check if this is OK, default values are not supposed to be over-written
//void cfgSetFragThreshold(uint16_t  aFragThreshold)
//{
//    gpL2CommonCfg->fragThreshold = aFragThreshold;
//}


/* ----------------------------------------------------------------------------
 cfgGetWpsParameters
      This function returns a pointer to the default WPS parameters

 Parameters:
     OUT wpsParameters_t **pWpsParameters - Pointer to callers' wps parameters

 return: TRUE - WPS parameters are valid, FALSE parameters not available
---------------------------------------------------------------------------- */
Bool32 cfgGetWpsParameters(wpsParameters_t **pWpsParameters)
{
    if (gpSupplicantCfg->wpsParams)
    {
        *pWpsParameters = gpSupplicantCfg->wpsParams;
        return TRUE;
    }
    else
    {
        *pWpsParameters = NULL;
        return FALSE;
    }
}

/* ----------------------------------------------------------------------------
 cfgSetWpsParameters
      Set WPA Supplicant WPS configurations

 Parameters:
     params - WPS parameters

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsParameters(const WpsParams_t *params)
{
    cfgSetWpsParametersCleanUp();

    wpsParameters_t *setParams = gpSupplicantCfg->wpsParams;
    if (params->uuid)
    {
        os_memcpy(setParams->uuid, params->uuid, WPS_UUID_LEN);
    }
    
    if (params->deviceName && (os_strlen(params->deviceName) <= WPS_DEV_NAME_MAX_LEN))
    {
        setParams->device_name = os_strdup(params->deviceName);
    }
    
    if (params->manufacturer && (os_strlen(params->manufacturer) <= WPS_MANUFACTURER_MAX_LEN))
    {
        setParams->manufacturer = os_strdup(params->manufacturer);
    }

    if (params->modelName && (os_strlen(params->modelName) <= WPS_MODEL_NAME_MAX_LEN))
    {
        setParams->model_name = os_strdup(params->modelName);
    }

    if (params->modelNumber && (os_strlen(params->modelNumber) <= WPS_MODEL_NUMBER_MAX_LEN))
    {
        setParams->model_number = os_strdup(params->modelNumber);
    }

    if (params->serialNumber && (os_strlen(params->serialNumber) <= WPS_SERIAL_NUMBER_MAX_LEN))
    {
        setParams->serial_number = os_strdup(params->serialNumber);
    }

    if (params->deviceType)
    {
        os_memcpy(setParams->device_type, params->deviceType, WPS_DEV_TYPE_LEN);
    }

    if (params->osVersion)
    {
        os_memcpy(setParams->os_version, params->osVersion, WPS_OS_VERSION_LEN);
    }
    
    if (params->configMethods)
    {
        setParams->config_methods = os_strdup(params->configMethods);
    }
}

/* ----------------------------------------------------------------------------
 cfgSetWpsParametersCleanUp
      Cleans up the previopusly set WPS params

 Parameters:
     none

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsParametersCleanUp()
{
    wpsParameters_t *pWpsParameters;

    if (cfgGetWpsParameters(&pWpsParameters))
    {
		if (pWpsParameters->device_name)
		{
			os_free(pWpsParameters->device_name);
			pWpsParameters->device_name = NULL;
		}

		if (pWpsParameters->manufacturer)
		{
			os_free(pWpsParameters->manufacturer);
			pWpsParameters->manufacturer = NULL;
		}

		if (pWpsParameters->model_name)
		{
			os_free(pWpsParameters->model_name);
			pWpsParameters->model_name = NULL;
		}

		if (pWpsParameters->model_number)
		{
			os_free(pWpsParameters->model_number);
			pWpsParameters->model_number = NULL;
		}

		if (pWpsParameters->serial_number)
		{
			os_free(pWpsParameters->serial_number);
			pWpsParameters->serial_number = NULL;
		}

		if (pWpsParameters->config_methods)
		{
			os_free(pWpsParameters->config_methods);
			pWpsParameters->config_methods = NULL;
		}
	}
}

/* ----------------------------------------------------------------------------
 cfgSetWpsMode
      Set WPS mode

 Parameters:
     wpsDisabled - False for WPS support, True otherwise

 return: none
---------------------------------------------------------------------------- */
void cfgSetWpsMode(Bool_e wpsDisabled)
{
    gpSupplicantCfg->wpsDisabled = wpsDisabled;
}

/* ----------------------------------------------------------------------------
 cfgGetWpsMode
      Get WPS mode

 Parameters: none

 return: True if enabled, false if disabled
---------------------------------------------------------------------------- */
Bool_e cfgGetWpsMode()
{
    if (gpSupplicantCfg->wpsDisabled)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/* ----------------------------------------------------------------------------
 cfgGetP2pParameters
      This function returns a pointer to the default P2P parameters

 Parameters:
     OUT P2pParameters_t **pP2pParameters - Pointer to callers' p2p parameters

 return: TRUE - P2p parameters are valid, FALSE parameters not available
---------------------------------------------------------------------------- */
Bool32 cfgGetP2pParameters(const P2pParameters_t **pP2pParameters)
{
    if (gpP2pSupplicantCfg->p2pParams)
    {
        *pP2pParameters = gpP2pSupplicantCfg->p2pParams;
        return TRUE;
    }
    else
    {
        *pP2pParameters = NULL;
        return FALSE;
    }
}

/* ----------------------------------------------------------------------------
 cfgSetP2pParameters
    Set WPA Supplicant P2P configurations

 Parameters:
    params - P2P parameters

 return: none
---------------------------------------------------------------------------- */
void cfgSetP2pParameters(const P2pParams_t *params)
{
    P2pParameters_t *setParams = gpP2pSupplicantCfg->p2pParams;
    
    //set p2p listen channen & reg class
    setParams->p2pListenRegClass = params->listenReg;
    setParams->p2pListenChannel = params->listenChannel;
    
    //set p2p operational channen & reg class
    setParams->p2pOperRegClass = params->operReg;
    setParams->p2pOperChannel = params->operChannel;
    
    //set go intent value
    setParams->p2pGoIntent = params->goIntent;
}
/* ----------------------------------------------------------------------------
 cfgSetP2pDevice
    Set P2P Device 

 Parameters:
    p2pDevDisable - False for p2p device support, True otherwise

 return: none
---------------------------------------------------------------------------- */
void cfgSetP2pDevice(Bool_e p2pDevDisable)
{
    gpP2pSupplicantCfg->p2pDisabled = p2pDevDisable;
}

/* ----------------------------------------------------------------------------
 cfgGetP2pDeviceEnable
      Get P2P device enable/disabled

 Parameters: none

 return: True if enabled, false if disabled
---------------------------------------------------------------------------- */
Bool_e cfgGetP2pDeviceEnable()
{
    return gpP2pSupplicantCfg->p2pDisabled ? FALSE : TRUE; 
}
/* ----------------------------------------------------------------------------
 cfgGetP2pOperChannel
      Gets a P2P operational channel from config

 Parameters: none

Return: oper channel
---------------------------------------------------------------------------- */
uint8_t cfgGetP2pOperChannel()
{
    return gpP2pSupplicantCfg->p2pParams->p2pOperChannel;
}

/* ----------------------------------------------------------------------------
 cfgGetP2pOperRegClass
      Gets a P2P operational class from config

 Parameters: none

Return: oper channel
---------------------------------------------------------------------------- */
uint8_t cfgGetP2pOperRegClass()
{
    return gpP2pSupplicantCfg->p2pParams->p2pOperRegClass;
}

/* ----------------------------------------------------------------------------
 cfgGetDeviceSupportedBandsBM
      Get the bitmask of the user-config (INI) and device fuses bands support

 Parameters: none

Return: supported bands bitmask (based on RadioBand_e enum)
---------------------------------------------------------------------------- */
uint32_t cfgGetDeviceSupportedBandsBM()
{
    return gpL2CommonCfg->deviceSupportedBandsBM;
}

/* ----------------------------------------------------------------------------
 cfgSetDeviceSupportedBandsBM
      Set the bitmask of the user-config (INI) and device fuses bands support

 Parameters: supported bands bitmask (based on RadioBand_e enum)

Return: none
---------------------------------------------------------------------------- */
void cfgSetDeviceSupportedBandsBM(uint32_t supportedBandsBM)
{
    gpL2CommonCfg->deviceSupportedBandsBM = supportedBandsBM;
}



#if 0

// On RX association response OK:
// ConnIfra.c MlmeWait_to_RocWait

//TI_STATUS roleSta_configSystemForBss(TI_HANDLE hRoleSta)
//udata_SetRxState(pConn->hUdata, uApLinkId, LINK_STATE_EAPOL);
//configureApBeforeRoc

static void setCurrentProtectionStatus(RoleContext_t *apRole, Bool_e aProtectionEnabled)
{
    if (apRole->config.sta_based.erpProtection != aProtectionEnabled)
    {
        ACXCtsProtection_t ctsToSelf;

        apRole->config.sta_based.erpProtection = aProtectionEnabled;

        // TODO - activate ACX_CTS_PROTECTION & ACX_FRAG_CFG API

//        ctsToSelf.RoleID = uRoleId;
//        ctsToSelf.ctsProtectMode = (TRUE == papRole->protectionEnabled) ? CTS_TO_SELF_ENABLE : CTS_TO_SELF_DISABLE;
//        TWD_SendInfoEle(pRoleSta->hTwd, ACX_CTS_PROTECTION, (void*)&tCtsToSelf, sizeof(tCtsToSelf), NULL, NULL);

        /* In case of using protection fragmentation should be disabled */
//        if (TRUE == aProtectionEnabled)
//        {
//            /* save last non-protection mode fragmentation threshold */
//            TWD_GetParam(pRoleSta->hTwd,&param);
//            pRoleSta->uLastFragmentThreshold = param.content.halCtrlFragThreshold;
//            /* set fragmentation threshold to max (disable) */
//            param.content.halCtrlFragThreshold = TWD_FRAG_THRESHOLD_MAX;
//        }
//        else
//            param.content.halCtrlFragThreshold = pRoleSta->uLastFragmentThreshold;
//
//        {
//            ACXFRAGThreshold_t tFragThresh;
//
//            tFragThresh.fragThreshold = ENDIAN_HANDLE_WORD(pParamInfo->content.halCtrlFragThreshold);
//            TWD_SendInfoEle(hTWD, ACX_FRAG_CFG, &tFragThresh, sizeof(tFragThresh), NULL, NULL);
//        }
    }
}


#if 0
static int32_t configureConnectionParams(uint32_t aRoleId)
{
//    RssiSnrTriggerCfg_t             tTriggerCfg;
//    ACXBeaconFilterOptions_t        tBeaconFilterOptions;
//    ACXBeaconFilterIETable_t        tBeaconFilterTable;
//    dot11MulticastGroupAddrStart_t  tGrpCfg;
//    ACXBeaconAndBroadcastOptions_t  tBeaconOptions;
//    ACXRssiSnrAverageWeights_t      tAvWeights;
//    dot11RTSThreshold_t             tRtsThresh;

    // Set beacon filter table
//    tBeaconFilterTable.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tBeaconFilterTable.NumberOfIEs = pRoleSta->tInitParams.tBeaconFilterInitParams.numOfElements;
//    os_memoryZero(pRoleSta->hOs, (void *)tBeaconFilterTable.IETable, BEACON_FILTER_TABLE_MAX_SIZE);
//    os_memoryCopy(pRoleSta->hOs,
//                  (void *)tBeaconFilterTable.IETable,
//                  (void *)pRoleSta->tInitParams.tBeaconFilterInitParams.IETable,
//                  pRoleSta->tInitParams.tBeaconFilterInitParams.IETableSize);
//    TWD_SendInfoEle(pRoleSta->hTwd, ACX_BEACON_FILTER_TABLE, (void*)&tBeaconFilterTable, sizeof(tBeaconFilterTable), NULL, NULL);

    /*  At start-up Set the Beacon Filter state as the User required */
//    tBeaconFilterOptions.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tBeaconFilterOptions.enable = pRoleSta->tInitParams.tBeaconFilterInitParams.desiredState;
//    tBeaconFilterOptions.maxNumOfBeaconsStored = pRoleSta->tInitParams.tBeaconFilterInitParams.numOfStored;
//    TWD_SendInfoEle(pRoleSta->hTwd, ACX_BEACON_FILTER_OPT, (void*)&tBeaconFilterOptions, sizeof(tBeaconFilterOptions), NULL, NULL);

    /* Group Address Table */
//    tGrpCfg.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tGrpCfg.numOfGroups = pRoleSta->tInitParams.tMacAddrFilter.numOfMacAddresses;
//    tGrpCfg.fltrState = pRoleSta->tInitParams.tMacAddrFilter.isFilterEnabled;
//    os_memoryCopy(pRoleSta->hOs, tGrpCfg.dataLocation, pRoleSta->tInitParams.tMacAddrFilter.macAddrTable, ADDRESS_GROUP_MAX_LEN);
//    TWD_SendInfoEle(pRoleSta->hTwd, DOT11_GROUP_ADDRESS_TBL, (void*)&tGrpCfg, sizeof(tGrpCfg), NULL, NULL);

    // ------------------------------------------------------------------------
    /* RTS Threshold */
    // not needed, was already initialized directly on gL2StaBasedCfg

//    tRtsThresh.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tRtsThresh.RTSThreshold = ENDIAN_HANDLE_WORD(pRoleStaInitParams->uRtsThreshold);
//    TWD_SendInfoEle(pRoleSta->hTwd, DOT11_RTS_THRESHOLD, (void*)&tRtsThresh, sizeof(tRtsThresh), NULL, NULL);
    // ------------------------------------------------------------------------

    /* Beacon broadcast options */
//    tBeaconOptions.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tBeaconOptions.beaconRxTimeOut = pRoleStaInitParams->tBcnBrcOptions.BeaconRxTimeout;
//    tBeaconOptions.broadcastTimeOut = pRoleStaInitParams->tBcnBrcOptions.BroadcastRxTimeout;
//    tBeaconOptions.rxBroadcastInPS = pRoleStaInitParams->tBcnBrcOptions.RxBroadcastInPs;
//    tBeaconOptions.consecutivePsPollDeliveryFailureThr = pRoleStaInitParams->uConsecutivePsPollDeliveryFailureThreshold;
//    TWD_SendInfoEle(pRoleSta->hTwd, ACX_BCN_DTIM_OPTIONS, (void*)&tBeaconOptions, sizeof(tBeaconOptions), NULL, NULL);

    /* RSSI SNR Weights */
    // TODO - how do we handle bad connection ==================================
//    tAvWeights.RoleID = pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tAvWeights.param.rssiBeaconAverageWeight = pRoleStaInitParams->tWeightsParam.rssiBeaconAverageWeight;
//    tAvWeights.param.rssiPacketAverageWeight = pRoleStaInitParams->tWeightsParam.rssiPacketAverageWeight;
//    tAvWeights.param.snrBeaconAverageWeight = pRoleStaInitParams->tWeightsParam.snrBeaconAverageWeight;
//    tAvWeights.param.snrPacketAverageWeight = pRoleStaInitParams->tWeightsParam.snrPacketAverageWeight;
//    TWD_SendInfoEle(pRoleSta->hTwd, ACX_RSSI_SNR_WEIGHTS, (void*)&tAvWeights, sizeof(tAvWeights), NULL, NULL);

    /* Register the RSSI Trigger events at the currBss RSSI/SNR static table*/
    // TODO - how do we handle bad connection ==================================
//    tTriggerCfg.threshold = (0 - pRoleSta->tInitParams.iTxPowerRssiThresh);
//    tTriggerCfg.pacing    = TRIGGER_HIGH_TX_PW_PACING;
//    tTriggerCfg.metric    = METRIC_EVENT_RSSI_DATA;
//    tTriggerCfg.type      = RX_QUALITY_EVENT_EDGE;
//    tTriggerCfg.direction = RSSI_EVENT_DIR_HIGH;
//    tTriggerCfg.hystersis = TRIGGER_HIGH_TX_PW_HYSTERESIS;
//    tTriggerCfg.enable     = TI_TRUE;
//    rssiTriggers_Register (pRoleSta->hRssiTriggers,
//                           (TI_UINT8)(pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX]),
//                           &tTriggerCfg,
//                           (void*)txPowerHighThreshold,
//                           (TI_HANDLE)pRoleSta);


//    pRoleSta->uHighTxPowerEventTriggerIdx = tTriggerCfg.index;
//    tTriggerCfg.threshold = (0 - pRoleSta->tInitParams.iTxPowerRssiRestoreThresh);
//    tTriggerCfg.pacing    = TRIGGER_LOW_TX_PW_PACING;
//    tTriggerCfg.metric    = METRIC_EVENT_RSSI_DATA;
//    tTriggerCfg.type      = RX_QUALITY_EVENT_EDGE;
//    tTriggerCfg.direction = RSSI_EVENT_DIR_LOW;
//    tTriggerCfg.hystersis = TRIGGER_LOW_TX_PW_HYSTERESIS;
//    tTriggerCfg.enable    = TI_TRUE;
//    rssiTriggers_Register (pRoleSta->hRssiTriggers,
//                           (TI_UINT8)(pRoleSta->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX]),
//                           &tTriggerCfg,
//                           (void*)txPowerLowThreshold,
//                           (TI_HANDLE)pRoleSta);
//    pRoleSta->uLowTxPowerEventTriggerIdx = tTriggerCfg.index;

    return 0;
}
#endif


static TI_STATUS configureApBeforeRoc(connInfra_t *pConn)
{
    uint32_t       linkId;
    uint32_t       aid;
    TI_BOOL                         b11nEnable;
    TI_BOOL                         bWmeEnable;
    dot11HtCapabilitiesUnparse_t     *pHtCapabilities    = NULL;
    dot11HtInformationUnparse_t      *pHtInformation     = NULL;
    TI_UINT8                        uAmpduParam         = 0;
    TI_UINT16                       uHtCapabilitesField = 0;
    TI_BOOL                         bHtInfoUpdate       = TI_FALSE;
    PktTemplate_t           tTemplateCfg;
    ArpRspTemplate_t        tArpRspTemplate;
    ACXConfigureIP_t        tArpIpFilter;
    TI_UINT16               uTemplateLen = 0;
    TMacAddr                tBssid;
    EQosProtocol            eQosProtocol;
    TRateSets               tLinkRates;
    ACXAid_t                        tAidParams;
    AcxBurstMode                    tBurstModeParams;
    ACXpeerCap_t                    tPeerCapParams;
    HTBssCfg_t                      tHTInfoParamas;
    TI_UINT32               uHwSuppRate = 0;

    uApLinkId = roleSta_GetApLinkId(pConn->pRoleDesc->hRoleHandle);

    /****** Now, send required templates to the FW ******/
//    os_memoryZero(pConn->hOs, (void*)&tTemplateCfg, sizeof(tTemplateCfg));
//    tTemplateCfg.RoleID = pConn->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
//    tTemplateCfg.templateType = TEMPLATE_ARP_RSP;
//    tTemplateCfg.templateTxAttribute.enabledRates = RATE_MASK_UNSPECIFIED;
//    tTemplateCfg.templateTxAttribute.shortRetryLimit = 10;
//    tTemplateCfg.templateTxAttribute.longRetryLimit  = 10;
//
//    tArpIpFilter = roleSta_getArpFilterParams(pConn->pRoleDesc->hRoleHandle);
//    qosMngr_GetActiveProtocol(pConn->hQosMngr, &eQosProtocol);
//    buildArpRspTemplate(pConn->hOs, &tArpRspTemplate, tArpIpFilter.address,
//                        &pConn->pRoleDesc->tMacAddr, &tBssid, eQosProtocol,
//                        wlanLinks_GetLinkDataEncryption(pConn->hWlanLinks, uApLinkId), &uTemplateLen);
//    os_memoryCopy(pConn->hOs, (void *)tTemplateCfg.templateStart, (void *)&tArpRspTemplate, uTemplateLen);
//    tTemplateCfg.len = ENDIAN_HANDLE_WORD(uTemplateLen);
//    TWD_SendCmd(pConn->hTWD, CMD_SET_TEMPLATE, (void *)&tTemplateCfg, sizeof(tTemplateCfg), NULL, NULL);
//
//    /* Send the ARP Filter command */
//    TWD_SendInfoEle(pConn->hTWD, ACX_ARP_IP_FILTER, (void*)&tArpIpFilter, sizeof(ACXConfigureIP_t), NULL, NULL);
    /**************************************************************************/

    /* configure AID */
    wlanLinks_GetLinkAid(pConn->hWlanLinks, &uAid, uApLinkId);

    tAidParams.RoleID = pConn->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
    tAidParams.Aid = uAid;

    TWD_SendInfoEle(pConn->hTWD, ACX_AID, &tAidParams, sizeof(tAidParams), NULL, NULL);

    /* Configure the burst mode to the FW */
    tBurstModeParams.RoleID = (TI_UINT8)pConn->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
    tBurstModeParams.enable = qosMngr_GetBurstModeEnabled(pConn->hQosMngr);

    TWD_SendInfoEle(pConn->hTWD, ACX_BURST_MODE, &tBurstModeParams, sizeof(tBurstModeParams), NULL, NULL);

    rsn_SetKeys(pConn->hRsn);

    /* Configure AP's HT information to FW */
    TWD_DevCap_IsHtEnable (pConn->hTWD, &b11nEnable);
    qosMngr_GetWmeEnableFlag (pConn->hQosMngr, &bWmeEnable);
    roleSta_GetPeerHtCap(pConn->pRoleDesc->hRoleHandle, &pHtCapabilities);
    roleSta_GetPeerHtInfo(pConn->pRoleDesc->hRoleHandle, &bHtInfoUpdate, &pHtInformation);
    wlanLinks_GetLinkRates(pConn->hWlanLinks, &tLinkRates, uApLinkId);

    /* Set the default HT capabilities parameters */
    tPeerCapParams.hlid = uApLinkId;
    rate_DrvBitmapToHwBitmap(tLinkRates.uSuppRatesBitMap, &uHwSuppRate);
    tPeerCapParams.supportedRates = uHwSuppRate;
    tPeerCapParams.uAmpduMaxLength = 0;
    tPeerCapParams.uAmpduMinSpacing = 0;
    tPeerCapParams.uHtCapabilites = 0;

    if ((b11nEnable != TI_FALSE) &&
        (bWmeEnable != TI_FALSE) &&
         pHtCapabilities &&
         pHtInformation  &&
        (pHtCapabilities->tHdr[0] != TI_FALSE) &&
        (pHtInformation->tHdr[0]  != TI_FALSE))
    {
        /* get date from HT capabilities field (and handle endian) */
        COPY_WLAN_WORD(&uHtCapabilitesField, pHtCapabilities->aHtCapabilitiesIe);

        /* get date from A-MPDU parameters field */
        uAmpduParam = pHtCapabilities->aHtCapabilitiesIe[HT_CAP_AMPDU_PARAMETERS_FIELD_OFFSET];

        /* set the ht cap params*/
        tPeerCapParams.uAmpduMaxLength = (uAmpduParam & HT_CAP_AMPDU_MAX_SIZE_BITMASK);
        tPeerCapParams.uAmpduMinSpacing = ((uAmpduParam & HT_CAP_AMPDU_SPACING_BITMASK) >> HT_CAP_AMPDU_SPACING_OFFSET);
        tPeerCapParams.uHtCapabilites = uHtCapabilitesField;
        tPeerCapParams.uHtCapabilites |= uHtCapabilitesField ? HT_CAP_HT_OPERRATION : 0;

        /* Send the IE */
        TWD_SendInfoEle(pConn->hTWD, ACX_PEER_CAP, &tPeerCapParams, sizeof(tPeerCapParams), NULL, NULL);

        /* Set the HT Information parameters */
        tHTInfoParamas.RoleID = pConn->pRoleDesc->aFwRoleIds[ROLE_STA_STATION_FW_ROLE_ID_IDX];
        tHTInfoParamas.uRifsMode = HT_RIFS_MODE(pHtInformation);
        tHTInfoParamas.uHtProtection = HT_PROT(pHtInformation);
        tHTInfoParamas.uGfProtection = HT_GF_PROT(pHtInformation);
        tHTInfoParamas.uHtTxBurstLimit = 0; /* not in use */
        tHTInfoParamas.uDualCtsProtection = HT_DUAL_CTS_PROT(pHtInformation);

        /* Send the IE */
        TWD_SendInfoEle(pConn->hTWD, ACX_HT_BSS_OPERATION, &tHTInfoParamas, sizeof(tHTInfoParamas), NULL, NULL);
    }
    else
    {
        /* Send the IE */
        TWD_SendInfoEle(pConn->hTWD, ACX_PEER_CAP, &tPeerCapParams, sizeof(tPeerCapParams), NULL, NULL);
    }

    return TI_OK;
}


void determineLinkRates()
{
   TI_UINT32  uPeerBasicRateMask = 0, uPeerSuppRateMask = 0;
   TI_UINT32  uStaTotalRates;

   uStaTotalRates = pStaDesiredRates->uBasicRatesBitMap | pStaDesiredRates->uSuppRatesBitMap;

   roleSta_GetPeerRateMasks(pRoleSta, &uPeerBasicRateMask, &uPeerSuppRateMask);
   pLinkRates->uSuppRatesBitMap = uStaTotalRates & uPeerSuppRateMask;
}



void updateApsd()
{
    TI_BOOL bApsdSupport;
    /* If WME-Params IE is not included in the beacon, set the APSD-Support flag
         only by the beacons capabilities bit map. */
    if (pFrameInfo->WMEParams.hdr[1] == 0)
        bApsdSupport = (((pFrameInfo->capabilities >> CAP_APSD_SHIFT) & CAP_APSD_MASK) ? TI_TRUE : TI_FALSE);

    /* Else, set the APSD-Support flag if either the capabilities APSD bit or the
         WME-Params APSD bit indicate so. */
    else
        bApsdSupport = ((((pFrameInfo->capabilities >> CAP_APSD_SHIFT) & CAP_APSD_MASK) ? TI_TRUE : TI_FALSE) ||
        (((pFrameInfo->WMEParams.ACInfoField >> AP_QOS_INFO_UAPSD_SHIFT) & AP_QOS_INFO_UAPSD_MASK) ? TI_TRUE : TI_FALSE));

    roleSta_SetPeerApsd(pRoleSta, bApsdSupport);
}





// After connection completes - set all peer parameters
static TI_STATUS configureFwAfterRsn(connInfra_t *pConn, TI_BOOL bRecovery)
{
    TRoleSta *pRoleSta = (TRoleSta *)pConn->pRoleDesc->hRoleHandle;
    SetPeerState_t tPeerStateParams;
    TI_STATUS status;
    TI_UINT32 uHlid;
    TI_BOOL   bWme;
    dot11_ACParameters_t *pWmeAcParam = NULL;

    status = qosMngr_connect(pConn->hQosMngr, bRecovery);
    if (status != TI_OK)
    {
         TRACE(pConn->hReport, REPORT_SEVERITY_ERROR, "Infra Conn status=%d, have to return (%d)\n",status,__LINE__);
         return status;
    }


    uHlid = roleSta_GetApLinkId(pConn->pRoleDesc->hRoleHandle);

    roleSta_GetPeerWmeParams(pRoleSta, &bWme, &pWmeAcParam);

    /* Send peer state command */
    tPeerStateParams.HLID = (TI_UINT8)uHlid;
    tPeerStateParams.WMM = bWme;
    tPeerStateParams.peerState = STA_STATE_CONNECTED;

    TWD_SendCmd(pConn->hTWD,
                CMD_SET_PEER_STATE,
                &tPeerStateParams,
                sizeof(tPeerStateParams),
                (void *)conn_ConfigHwFinishCb,
                pConn);

    return TI_OK;
}





#endif
