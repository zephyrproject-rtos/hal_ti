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
/*
 * cme_common.h
 *
 *  Created on: Jan 31, 2021
 *      Author: a0387677
 */

#ifndef CME_CME_COMMON_H_
#define CME_CME_COMMON_H_

#include "wlan_if.h"
#include "cme_defs.h"

typedef struct
{
    uint8_t     SsidLen;
    uint8_t     SsidName[32];
    uint8_t     Bssid[6];
    uint8_t     ReasonCode;
} CMEWlanEventDisconnect_t;


typedef struct{
    uint16_t    SecType;
    uint8_t     SsidLen;
    uint8_t     Priority;
    uint32_t    Hidden; //scan_ssid, (u32 - to be aligned)
    uint8_t     Bssid[6];
    uint8_t     PasswordLen;
    uint8_t     WepKeyId;
    uint8_t     FastTransition;
} CMEWlanAddGetProfile_t;

typedef struct{
    uint8_t     UserLen;
    uint8_t     AnonUserLen;
    uint8_t     CertIndex;
    uint8_t     padding;
    uint32_t    EapBitmask;
    CMEWlanAddGetProfile_t  CommonAddProf;
} CMEWlanAddGetEapProfile_t;


typedef struct{
    uint8_t SecType;
    uint8_t SsidLen;
    uint8_t Bssid[6];
    uint8_t PasswordLen;
    uint8_t FastTransition;
    uint16_t Flags;
} CMEWlanConnectCommon_t;


typedef enum
{
    TLS,
    TTLS,
    PEAP0,
    PEAP1,
    PEAP2,
    FAST
}eap_phase1_val_t;

//eapol param
typedef enum
{
    MSCHAPV2_TYPE,
    TLS_TYPE,
    PSK_TYPE,
    GTC_TYPE
}eap_phase2_val_t;

typedef struct
{
    eap_phase1_val_t  eap_phase1_val;
    eap_phase2_val_t  eap_phase2_val;

    const uint8_t*    pEap_client_cert;
    uint32_t    eap_client_cert_len;

    const uint8_t*    pEap_ca_cert;
    uint32_t    eap_ca_cert_len;

    const uint8_t*    pEap_private_key;
    uint32_t    eap_private_key_len;

    uint8_t  eapIdentity[MAX_USER_LEN + 1];
    uint32_t eapIdentityLen;
    uint8_t  eapAnonymous[MAX_ANON_LEN + 1];
    uint32_t eapAnonUserLen;
    uint32_t TLSKeyLength;
    CMEWlanConnectCommon_t EapCommonConnect;//CMEWlanConnectCommon_t must be located at the need of the structure!!!
}CMEEapWlanConnect_t;



#define CME_MAX_SCAN_SSID                  5
#define CME_SSID_MAX_LENGTH               (32)

typedef struct
{
    uint8_t  ssidLen;
    uint8_t  pSsid[CME_SSID_MAX_LENGTH];
    uint8_t  mHidden;// 1 = SSID_TYPE_HIDDEN, 0 = SSID_TYPE_PUBLIC
    uint8_t  padding[2];
}CMEWlanSsid_t;

typedef struct
{
    CMEWlanSsid_t CMEWlanSsid[CME_MAX_SCAN_SSID];
    WlanBandCfg_e Band;//0  - 2.4, 1 = 5G , 2 = Both
    uint8_t extWpsMode;
    WlanRole_e roleType;
}CMEWlanScanCommon_t;


#define SSID_STRING(conCommon)       ((int8_t *)((CMEWlanConnectCommon_t *)(conCommon) + 1))
#define PASSWORD_STRING(conCommon)   (SSID_STRING(conCommon) + ((CMEWlanConnectCommon_t *)(conCommon))->SsidLen)


#define PROFILE_SSID_STRING(addProfCmd)           ((int8_t *)((CMEWlanAddGetProfile_t *)(addProfCmd) + 1))
#define PROFILE_PASSWORD_STRING(addProfCmd)       (PROFILE_SSID_STRING(addProfCmd) + ((CMEWlanAddGetProfile_t *)(addProfCmd))->SsidLen)


#define EAP_PROFILE_SSID_STRING(pCmd)       (int8_t *)((CMEWlanAddGetEapProfile_t *)(pCmd) + 1)
#define EAP_PROFILE_PASSWORD_STRING(pCmd)   (EAP_PROFILE_SSID_STRING(pCmd) + ((CMEWlanAddGetEapProfile_t *)(pCmd))->Common.SsidLen)

#define EAP_PROFILE_USER_STRING(pCmd)       (EAP_PROFILE_PASSWORD_STRING(pCmd) + ((CMEWlanAddGetEapProfile_t *)(pCmd))->Common.PasswordLen)
#define EAP_PROFILE_ANON_USER_STRING(pCmd)  (EAP_PROFILE_USER_STRING(pCmd) + ((CMEWlanAddGetEapProfile_t *)(pCmd))->UserLen)

#define EAP_SSID_STRING(pEapCmd)             ((int8_t*)(((CMEEapWlanConnect_t*)pEapCmd) +1))
#define EAP_PASSWORD_STRING(pEapCmd)           (EAP_SSID_STRING(pEapCmd) + ((CMEEapWlanConnect_t *)(pEapCmd))->EapCommonConnect.SsidLen)




typedef enum
{
    CME_SEC_TYPE_OPEN,
    CME_SEC_TYPE_WEP,
    CME_SEC_TYPE_WPA_WPA2,
    CME_SEC_TYPE_WPS_PBC,
    CME_SEC_TYPE_WPS_PIN,
    CME_SEC_TYPE_WPA2_PLUS  = 11,
    CME_SEC_TYPE_WPA3       = 12,
    CME_SEC_TYPE_WPA2_AES_ONLY_PMF = 13,
    CME_SEC_TYPE_WPA2_AES_ONLY_NO_PMF = 14,
    CME_SEC_TYPE_WPA2_WPA3 = 16,
    CME_SEC_TYPE_WPA_ENT = 17,
    CME_SEC_TYPE_WPA = 18,
    CME_SEC_TYPE_WEP_SHARED   = 19,
    CME_SEC_TYPE_WPA2_FT      = 20,
    CME_SEC_TYPE_WPA2_PLUS_FT = 21,
    CME_SEC_TYPE_WPA3_FT      = 22,
    CME_SEC_TYPE_WPA2_WPA3_FT = 23,

} CMESecType_e;

typedef struct
{
    uint8_t   MacAddress[6];
    uint16_t  Reserved;
} CMEWlanApRemovePeer_t;



#endif /* CME_CME_COMMON_H_ */
