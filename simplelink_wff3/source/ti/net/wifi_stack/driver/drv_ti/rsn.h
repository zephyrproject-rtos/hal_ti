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
  FILENAME:       rsn.c

  DESCRIPTION:    This file handles STA RSN (Robust Security Network) keys.
                  It is based on WL8 MCP rsn.c code.

  HISTORY:
                  07/15 Creation
  ----------------------------------------------------------------------------- */

#ifndef RSN_H_
#define RSN_H_

#include <public_types.h>
#include "802_11defs.h"
#include "common.h"                 // needed for including defs.h
#include "defs.h"
#include "osi_kernel.h"                    // For OS timer handle


// ============================================================================
//  Type definitions
// ============================================================================

#define KEY_RSC_LEN      (6)
#define MIN_KEY_LEN      (5)
#define MAX_KEY_LEN     (32)

#define TKIP_MIC_LEN     (8)


//#define DRV_LOG_REPORT
#ifdef DRV_LOG_REPORT
#define DRV_PRINT_REPORT Report
#define DRV_PRINT_REPORT_ERROR Report
#else
#define DRV_PRINT_REPORT(...)
#define DRV_PRINT_REPORT_ERROR Report
#endif

#ifdef CONFIG_IEEE80211W
#define MAX_KEYS_NUM     (6)
#else /* CONFIG_IEEE80211W */
#define MAX_KEYS_NUM     (4)
#endif /* CONFIG_IEEE80211W */


#define RSN_MAX_NUMBER_OF_BANNED_SITES        (16)
#define RSN_MIC_FAILURE_REPORT_TIMEOUT_MS    (500)
#define RSN_MIC_FAILURE_RE_KEY_TIMEOUT_MS   (3000)
#define RSN_AUTH_FAILURE_TIMEOUT_MS        (30000)
#define RSN_MIC_FAILURE_TIMEOUT_MS         (60000 + RSN_MIC_FAILURE_REPORT_TIMEOUT_MS)
#define RSN_MAIN_KEYS_SESSION_TIMEOUT_MS   (RSN_AUTH_FAILURE_TIMEOUT_MS)



#define RSN_WEP_KEY_TRANSMIT_MASK  (0x80000000)      // bit 31 of key index field
#define MIN_DEFAULT_KEY_ID                  (0)
#define MAX_DEFAULT_KEY_ID                  (3)

/* Scan results security information */

#define RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK              0x3f
#define RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION          8
/* Bits 8-13: Security type (6 bits) */
/* Note: Bit 13 was previously used for hidden SSID but is now part of security type */

#define RSN_WLAN_SCAN_RESULT_GROUP_CIPHER_MASK          0xf
#define RSN_WLAN_SCAN_RESULT_GROUP_CIPHER_POSITION      0

#define RSN_WLAN_SCAN_RESULT_UNICAST_CIPHER_MASK        0xf
#define RSN_WLAN_SCAN_RESULT_UNICAST_CIPHER_POSITION    4

#define RSN_WLAN_SCAN_RESULT_KEY_MGMT_MASK              0x7
#define RSN_WLAN_SCAN_RESULT_KEY_MGMT_POSITION          14

#define RSN_WLAN_SCAN_RESULT_GROUP_CIPHER(SecurityInfo)              (SecurityInfo & 0xF)   /* Possible values: NONE,RSN_WLAN_CIPHER_BITMAP_TKIP,RSN_WLAN_CIPHER_BITMAP_CCMP */
#define RSN_WLAN_SCAN_RESULT_UNICAST_CIPHER_BITMAP(SecurityInfo)     ((SecurityInfo & 0xF0) >> 4 ) /* Possible values: NONE,RSN_WLAN_CIPHER_BITMAP_WEP40,RSN_WLAN_CIPHER_BITMAP_WEP104,RSN_WLAN_CIPHER_BITMAP_TKIP,RSN_WLAN_CIPHER_BITMAP_CCMP*/
#define RSN_WLAN_SCAN_RESULT_KEY_MGMT_SUITES_BITMAP(SecurityInfo)    ((SecurityInfo & (RSN_WLAN_SCAN_RESULT_KEY_MGMT_MASK << RSN_WLAN_SCAN_RESULT_KEY_MGMT_POSITION)) >> RSN_WLAN_SCAN_RESULT_KEY_MGMT_POSITION)  /* bits 14-16; Possible values: RSN_WLAN_KEY_MGMT_SUITE_802_1_X, RSN_WLAN_KEY_MGMT_SUITE_PSK, RSN_WLAN_KEY_MGMT_SUITE_SAE */
#define RSN_WLAN_SCAN_RESULT_SEC_TYPE_BITMAP(SecurityInfo)           ((SecurityInfo & (RSN_WLAN_SCAN_RESULT_SEC_TYPE_MASK << RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION)) >> RSN_WLAN_SCAN_RESULT_SEC_TYPE_POSITION)  /* Possible values: RSN_WLAN_SECURITY_TYPE_BITMAP_OPEN, RSN_WLAN_SECURITY_TYPE_BITMAP_WEP, RSN_WLAN_SECURITY_TYPE_BITMAP_WPA, RSN_WLAN_SECURITY_TYPE_BITMAP_WPA2, 0x6 (mix mode) RSN_WLAN_SECURITY_TYPE_BITMAP_WPA | RSN_WLAN_SECURITY_TYPE_BITMAP_WPA2 */
#define RSN_WLAN_SCAN_RESULT_PMF_CAPABLE(SecurityInfo)               (RSN_WLAN_SCAN_RESULT_SEC_TYPE_BITMAP(SecurityInfo) & RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_CAPABLE)
#define RSN_WLAN_SCAN_RESULT_PMF_REQUIRED(SecurityInfo)              (RSN_WLAN_SCAN_RESULT_SEC_TYPE_BITMAP(SecurityInfo) & RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_REQUIRED)

#define RSN_WLAN_SECURITY_TYPE_BITMAP_OPEN            (0)  
#define RSN_WLAN_SECURITY_TYPE_BITMAP_WEP             (1 << 0)  
#define RSN_WLAN_SECURITY_TYPE_BITMAP_WPA             (1 << 1)  
#define RSN_WLAN_SECURITY_TYPE_BITMAP_WPA2            (1 << 2)  
#define RSN_WLAN_SECURITY_TYPE_BITMAP_WPA3            (1 << 3) 
#define RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_CAPABLE     (1 << 4)  
#define RSN_WLAN_SECURITY_TYPE_BITMAP_PMF_REQUIRED    (1 << 5) 


#define RSN_WLAN_CIPHER_BITMAP_WEP40                  0x1
#define RSN_WLAN_CIPHER_BITMAP_WEP104                 0x2
#define RSN_WLAN_CIPHER_BITMAP_TKIP                   0x4
#define RSN_WLAN_CIPHER_BITMAP_CCMP                   0x8

#define RSN_WLAN_KEY_MGMT_SUITE_802_1_X               1
#define RSN_WLAN_KEY_MGMT_SUITE_PSK                   2
#define RSN_WLAN_KEY_MGMT_SUITE_SAE                   4    // WPA3-Personal (SAE key exchange)

/* Available legacy authentication modes */
typedef enum
{
    AUTH_LEGACY_OPEN_SYSTEM     = 0,
    AUTH_LEGACY_SHARED_KEY      = 1,
    AUTH_LEGACY_FT              = 2,
    AUTH_LEGACY_AUTO_SWITCH     = 3,
    AUTH_LEGACY_RESERVED1       = 128,
    AUTH_LEGACY_NONE            = 255
} legacyAuthType_e;

/* Available External authentication modes */
typedef enum
{
    RSN_EXT_AUTH_MODE_OPEN,                  // Legacy Open authentication suite
    RSN_EXT_AUTH_MODE_SHARED_KEY,            // Legacy Shared Key authentication suite
    RSN_EXT_AUTH_MODE_AUTO_SWITCH,           // Automatic authentication suite
    RSN_EXT_AUTH_MODE_WPA,
    RSN_EXT_AUTH_MODE_WPAPSK,
    RSN_EXT_AUTH_MODE_WPANONE,
    RSN_EXT_AUTH_MODE_WPA2,
    RSN_EXT_AUTH_MODE_WPA2PSK,
    /* Not a real mode, defined as upper bound */
    RSN_EXT_AUTH_MODEMAX

} externalAuthMode_e;


// Used for Get/Set RSN/WPA/WPS IE
#define RSN_GENERIC_IE_MAX_LEN  (255)

typedef struct
{
    uint8_t  length;                          // IE buffer length
    uint8_t  data[RSN_GENERIC_IE_MAX_LEN];    // IE buffer
} rsnGenericIE_t;

// Security keys, to be filled by driver_cc33
typedef struct
{
    uint8_t              lid;                       /**< Link ID                            */
    uint8_t/*LidKeyType_e*/ lidKeyType;                /**< Link Key of type ELidKeyType       */
    enum wpa_alg       keyType;                   /**< Security Key Type (WEP, TKIP etc.) */
    uint32_t             encLen;                    /**< Security Key length in bytes       */
    uint8_t              encKey[MAX_KEY_LEN];       /**< Security Key Encoding              */
    uint8_t              micRxKey[MAX_KEY_LEN];     /**< MIC RX Security Key                */
    uint8_t              micTxKey[MAX_KEY_LEN];     /**< MIC TX Security Key                */
    uint32_t             keyIndex;                  /**< Security Key Index                 */
    uint8_t              macAddress[MAC_ADDR_LEN];  /**< Security Key MAC Address           */
    uint8_t              keyRsc[KEY_RSC_LEN];       /**< Security Key RSC                   */

} securityKeys_t;

// RSN DB
typedef struct
{
    uint32_t     roleId;
//    Bool_e     groupKeyUpdate;
//    Bool_e     pairwiseKeyUpdate;
//    OsiTimer_t micFailureReportWaitTimer;
//    OsiTimer_t micFailureGroupReKeyTimer;
//    OsiTimer_t micFailurePairwiseReKeyTimer;

//    Bool_e     pairwiseMicFailureFilter;
//
//    rsn_siteBanEntry_t     bannedSites[RSN_MAX_NUMBER_OF_BANNED_SITES];
//    uint8_t                    numOfBannedSites;
    rsnGenericIE_t             genericIE;
//
    Bool_e                     portStatus;        // 1 - auth completed
//    Bool_e                   waitRsnSuccess;
//    Bool_e                   mixedMode;
    uint8_t /*CipherSuite_e*/  unicastSuite;
    uint8_t /*CipherSuite_e*/  broadcastSuite;
    externalAuthMode_e         externalAuthMode;
//    uint32_t                   preAuthTimeout;
//    preAuthCache_t          preAuthCache;// ----------------------------------------------------------------------------
//    uint8_t                    numberOfPreAuthCandidates;
//    OsiTimer_t               preAuthTimerWpa2;

// No need to save the keys in cc3xxx (save ull memory), in Wilink they were probably saved for recovery
//    securityKeys_t           keys[MAX_KEYS_NUM];
} rsnCB_t;


/* ----------------------------------------------------------------------------
 rsn_init
      Init RSN DB

 Parameters:    none
 Return code:   none
---------------------------------------------------------------------------- */
void rsn_init();

/* ----------------------------------------------------------------------------
 rsn_SetDefaults
      Set RSN parameters when a STA role is started

 Parameters:    aRoleId
                aPrivacyOn - if TRUE, default suites are WEP
                             if FALSE, default suites are no cipher suite
                             for WL8 MCP the default is hard coded FALSE
 Return code:   none
---------------------------------------------------------------------------- */
int32_t rsn_SetDefaults(uint32_t aRoleID, Bool32 aPrivacyOn);

/* ----------------------------------------------------------------------------
 rsn_setCryptoParams
      Set unicast and broadcast cipher suites, suites are taken from association
      request command (as received from supplicant)

 Parameters:    aRoleId
 Return code:   none
---------------------------------------------------------------------------- */
void rsn_setCryptoParams(uint32_t aRoleId, uint32_t aPairwiseSuite, uint32_t aGroupSuite);

/* ----------------------------------------------------------------------------
 rsn_addKey
      Handle a new RSN key
      Code is based on rsn_setParam, case TI_PARAM_ADD_KEY

 Parameters:    Pointer to new key parameters

 Return code:   none
---------------------------------------------------------------------------- */
void rsn_addKey(securityKeys_t *apSecurityKey,const char *ifname);

/* ----------------------------------------------------------------------------
 rsn_getGenericIe
      Returns the generic IE for building (re)association request packet

 Parameters:    Role ID
                Pointer to generic IE, to be filled here
 Return code:   IE length
---------------------------------------------------------------------------- */
uint32_t rsn_getGenericIe(uint32_t aRoleId, uint8_t *apGenericIE);

/* ----------------------------------------------------------------------------
 rsn_setAuthParams
      1. Set the WPA generic key, to be used for building (re)association request packet.
         Code is based on MCP code - rsn_setParam, case TI_PARAM_WPA_IE
      2. Set authentication mode

 Parameters:    Role ID
                Auth algorithm, set by supplicant
                Key suite type (none, wpa, wps ,,,)
                Pointer to WPA IE
                WPA IE length in bytes
 Return code:   authentication type
---------------------------------------------------------------------------- */
legacyAuthType_e rsn_setAuthParams(uint32_t aRoleId,
                                   int32_t  AuthAlg,
                                   uint32_t aKeySuite,
                                   const uint8_t *apWpaIe,
                                   uint32_t      aWpaIeLen);

/* ----------------------------------------------------------------------------
 rsn_removeKey
      remove a key
      Code is based on rsn_removeKey

 Parameters:    Pointer to key parameters

 Return code:   none
---------------------------------------------------------------------------- */
void rsn_removeKey(securityKeys_t *apSecurityKey, const char *ifname);

/* ----------------------------------------------------------------------------
 rsn_setKey
      set a key

 Parameters:    Pointer to key parameters
 Return code:   none
---------------------------------------------------------------------------- */
void rsn_setKey(securityKeys_t *apSecurityKey, const char *ifname);

/* ----------------------------------------------------------------------------
 rsn_setPortStatus
      Notify RSN module in case of a change in authentication state

 Parameters:    Role ID
                aConnected - indication on RSN state
                             TRUE - sequence was successfully completed
                             FALSE - RSN session close
 Return code:   none
---------------------------------------------------------------------------- */
void rsn_setPortStatus(uint32_t aRoleId, int32_t aConnected);

/* ----------------------------------------------------------------------------
 rsn_getPairwiseSuite
      Return the pairwise cipher suite

 Parameters:
 Return code:   pairwise cipher suite
---------------------------------------------------------------------------- */
CipherSuite_e rsn_getPairwiseSuite();


/* ----------------------------------------------------------------------------
 * rsn_rsnWpaIe2SecurityInfo
 *
 * Parse and translate the rsnIE and return it in security information format, as described in wlan.h
 * (for survey scan results security information)
 *
 * Params: dot11_RSN_t *rsnIe - pointer to the rsn ie
 *         uint8_t rsnIeLen - rsnIE len
 *         uint16_t *securityType [out] - returned security type
 *
 * Return - 0 on success, negative on error*
 *
 * ---------------------------------------------------------------------------- */
int rsn_rsnWpaIe2SecurityInfo(dot11_RSN_t *rsnIe, uint8_t rsnIeLen, uint32_t *securityType);



void rsn_findSecurityIEs(uint8_t * payload, uint16_t payloadLen, dot11_RSN_t **pDotRsn, dot11_RSN_t **pDotWpa, dot11_RSN_t **pDotRsnOverride, dot11_RSN_t **pDotRsnOverride2);
/*
 * Parse the payload for RSN ie and WPA IE and return the security type (SL_SEC_TYPE_OPEN / SL_SEC_TYPE_WEP / SL_SEC_TYPE_WPA_WPA2 / CME_SEC_TYPE_WPA_ENT)
 *
 *
 * Params: uint16_t dot11CapabilityInfo
 *         uint8_t * payload - Beacon or probe response payload
 *         uint8_t payloadLen
 *         uint8_t *securityType [out] - returned security type from WPA/RSN IE
 *         uint8_t *securityTypeOverride [out] - returned security type from RSN Override IE
 *         uint8_t *securityTypeOverride2 [out] - returned security type from RSN Override 2 IE
 *
 * Return - 0 on success, negative on error
 *
 */
int rsn_getSecurityTypes(uint16_t dot11CapabilityInfo, dot11_RSN_t *pDotRsn, dot11_RSN_t *pDotWpa, dot11_RSN_t *pDotRsnOverride, dot11_RSN_t *pDotRsnOverride2, uint8_t *securityType, uint8_t *securityTypeOverride, uint8_t *securityTypeOverride2);

#endif /* RSN_H_ */

