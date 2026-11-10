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
 FILENAME:       drv_ti_utils.c

 DESCRIPTION:  This files contains utilities used by driver_cc33 layer
 ----------------------------------------------------------------------------- */

#include "drv_ti_internal.h"
#include "cme_supplicant_api.h"
#include "cme_fw_api.h"
#include "gtrace.h"
#include "ieee802_11_defs.h"
#include "rates.h"
#include "hostapd.h"
#include "mpdu.h"
#include "l2_cfg.h"
#include "udata_net_api.h"

extern uint32_t wlanLinks_LinkMacFind(uint8 uNetIf, uint8 *pMacAddr);

extern ti_driver_ifData_t *gpDriverIfDataSta; //TIWLAN_DEV_NAME_STA
extern ti_driver_ifData_t *gpDriverIfDataAp;   //TIWLAN_DEV_NAME_SAP
extern ti_driver_ifData_t *gpDriverIfDataDev; //TIWLAN_DEV_NAME_P2PDEV

extern TUdata *gUdataCB;

extern p2pGroupRole_e gP2pGroupRole;

// ============================================================================
//      Modules private definitions
// ============================================================================


// Macros used for constructing rates IEs
#define DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET   (3)
#define DOT11_HT_INFORMATION_MCS_RATE_OFFSET    (6)

// ----------------------------------------------------------------------------
RoleType_e drv_getDrvRoleType(ti_driver_ifData_t *apDrv)
{
    HOOK(HOOK_DRV_TI_UTILS);

    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_STA)))
        return ROLE_STA;

    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_SAP)))
        return ROLE_AP;

    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV)))
        return ROLE_DEVICE;

    // Note: this function serves for getting interface type, as set when
    // interface is started. P2P CL/GO are not valid at this stage hence
    // this function won't return these types..
    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2P_GO)))
        return ROLE_P2P_GO;

    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2P_CL)))
        return ROLE_P2P_CL;

    if (!os_strcmp(apDrv->iface, NETIF_NAME(TIWLAN_DEV_NAME_P2P)))
    {
        if (gP2pGroupRole == P2P_GROUP_ROLE_GO)
            return ROLE_P2P_GO;
        else
            return ROLE_P2P_CL;
    }

    return ROLE_TYPE_NONE;
}

ti_driver_ifData_t * drv_getDriverData(const char *ifname)
{
    HOOK(HOOK_DRV_TI_UTILS);

    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_STA)))
        return (gpDriverIfDataSta);

    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_SAP)))
        return (gpDriverIfDataAp);

    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2PDEV)))
        return (gpDriverIfDataDev);

    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_GO)))
        return (gpDriverIfDataAp);

    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P_CL)))
        return (gpDriverIfDataSta);
        
    if (0 == os_strcmp(ifname, NETIF_NAME(TIWLAN_DEV_NAME_P2P)))
    {
        if(gP2pGroupRole == P2P_GROUP_ROLE_GO)
            return (gpDriverIfDataAp);
        else
            return (gpDriverIfDataSta);
    }

    return NULL;
}


uint32_t drv_getDriverLink(uint32_t uNetIfId, uint8_t* dst)
{
    TUdata           *pUdata = gUdataCB ;
    tiwdrv_if_mode_e  eIfMode = pUdata->aNetidToMode[uNetIfId];
    uint32_t uHlid;

    if ((TIWDRV_IF_MODE_SAP == eIfMode) || (TIWDRV_IF_MODE_P2PGO == eIfMode))
    {
        uHlid = wlanLinks_LinkMacFind(uNetIfId, dst);
    }
    /* For STA or P2P-CL, the broadcast and unicast links are the same */
    else
    {
        uHlid = pUdata->aBcastHlid[uNetIfId];
    }
    return uHlid;
}
// ------------------------------------------------------------------------
void utilsDumpHex(const uint8_t *apBuff,
                  uint32_t aLen)
{
    uint32_t i, lines;

    if (NULL == apBuff)
    {
        GTRACE(GRP_DRIVER_CC33_DUMP, "ERROR: NULL buffer");
    }

    lines = aLen / 8;
    for (i = 0; i < lines; ++i)
    {
        GTRACE(GRP_DRIVER_CC33_DUMP,
               "%02x %02x %02x %02x %02x %02x %02x %02x",
               apBuff[i * 8],
               apBuff[1 + i * 8],
               apBuff[+2 + i * 8],
               apBuff[3 + i * 8],
               apBuff[4 + i * 8],
               apBuff[5 + i * 8],
               apBuff[6 + i * 8],
               apBuff[7 + i * 8]);
    }

    for (i = 0; i < (aLen - lines * 8); ++i)
    {
        GTRACE(GRP_DRIVER_CC33_DUMP, "%02x", apBuff[i + 8 * lines]);
    }
}

// ------------------------------------------------------------------------
void utilsDumpScanResult(struct wpa_scan_res *apResult)
{
#if GRP_DRIVER_CC33_DUMP

    uint8_t*  pIe;
    uint8_t*  pIeEnd;
    uint8_t   i;
    char    ssid[SSID_MAX_LEN];
    char    macStr[MAC_STR_LEN];

    GET_MAC_STR(apResult->bssid, macStr);
    GTRACE(GRP_DRIVER_CC33, "bssid %s", macStr);
    GTRACE(GRP_DRIVER_CC33_DUMP,
           "Beacon interval %d, beacon IE len %d",
           apResult->beacon_int,
           apResult->beacon_ie_len);
    GTRACE(GRP_DRIVER_CC33_DUMP,
           "Capabilities 0x%x, frequency %d",
           apResult->caps,
           apResult->freq);


    pIe = (uint8_t *) (apResult + 1);
    pIeEnd = pIe + apResult->ie_len - 1;

    utilsDumpHex(pIe, apResult->ie_len);

    // continue to next IE's
    while (pIe < pIeEnd)
    {
        switch (pIe[0])
        {
            case    SSID_IE_ID:
                memset(ssid, 0, SSID_MAX_LEN);
                memcpy(ssid, &pIe[2], pIe[1]);
                GTRACE(GRP_DRIVER_CC33_DUMP, "ssid %s, ssid len %d", ssid, pIe[1]);
                break;

            case    SUPPORTED_RATES_IE_ID:
                i = 0;
                for (i = 0 ; i < pIe[1] ; i+=4)
                {
                    GTRACE(GRP_DRIVER_CC33_DUMP,
                           "Rates IE len %d, rates 0x%8.8x",
                           pIe[1],
                           *(uint32_t*)&(pIe[2+i]));
                }
                break;

            case    ERP_IE_ID:
                GTRACE(GRP_DRIVER_CC33_DUMP,
                       "ERP IE len %d flags 0x%x",
                       pIe[1],
                       pIe[2]);
                break;

            case    HT_CAPABILITIES_IE_ID:
                GTRACE(GRP_DRIVER_CC33_DUMP, "HT capabilities IE len %d", pIe[1]);
                break;

            case    EXT_SUPPORTED_RATES_IE_ID:
                i = 0;
                for (i = 0 ; i < pIe[1] ; i+=4)
                {
                    GTRACE(GRP_DRIVER_CC33_DUMP,
                           "Ext rates IE len %d, rates 0x%8.8x",
                           pIe[1],
                           *(uint32_t*)&(pIe[2+i]));
                }
                break;

            case    HT_INFORMATION_IE_ID:
                GTRACE(GRP_DRIVER_CC33_DUMP, "HT information IE len %d", pIe[1]);
                break;

            case    RSN_IE_ID:
                GTRACE(GRP_DRIVER_CC33_DUMP, "RSN IE len %d", pIe[1]);
                break;
        }

        pIe += pIe[1] + 2;
    }
#endif
}

// ----------------------------------------------------------------------------
int32_t convertRatesToBitmap(struct hostapd_rate_data *apSupportedRates,
                           int *apBasicRates,
                           apRatesSets_t *apRateParams)
{
    int32_t rate;
    uint32_t i = 0;
    uint32_t ratesBM = 0;

    HOOK(HOOK_DRV_TI_UTILS);

    if ((NULL == apSupportedRates) && (NULL == apBasicRates))
    {
        CME_PRINT_REPORT_ERROR("\n\r ERROR !  convertRatesToBitmap failed");
        return -1;
    }

    // Start with empty rates BM & 0 basic/supported rates
    memset(apRateParams, 0, sizeof(apRatesSets_t));

    if (NULL != apSupportedRates)
    {
        for (i = 0; i < MAX_NUM_BG_RATES; ++i)
        {
            rate = apSupportedRates[i].rate;
            if (rate < 0)
                break;

            switch (rate / 10)
            {
                case 1:
                    ratesBM = BIT_x(RATE_INDEX_1MBPS);
                    break;
                case 2:
                    ratesBM = BIT_x(RATE_INDEX_2MBPS);
                    break;
                case 5:
                    ratesBM = BIT_x(RATE_INDEX_5_5MBPS);
                    break;
                case 6:
                    ratesBM = BIT_x(RATE_INDEX_6MBPS);
                    break;
                case 9:
                    ratesBM = BIT_x(RATE_INDEX_9MBPS);
                    break;
                case 11:
                    ratesBM = BIT_x(RATE_INDEX_11MBPS);
                    break;
                case 12:
                    ratesBM = BIT_x(RATE_INDEX_12MBPS);
                    break;
                case 18:
                    ratesBM = BIT_x(RATE_INDEX_18MBPS);
                    break;
                case 24:
                    ratesBM = BIT_x(RATE_INDEX_24MBPS);
                    break;
                case 36:
                    ratesBM = BIT_x(RATE_INDEX_36MBPS);
                    break;
                case 48:
                    ratesBM = BIT_x(RATE_INDEX_48MBPS);
                    break;
                case 54:
                    ratesBM = BIT_x(RATE_INDEX_54MBPS);
                    break;

                    // Note that 22Mbps isn't supported
                default:
                    ratesBM = 0;
                    break;
            }
            apRateParams->supportedRatesBM |= ratesBM;
        }
        apRateParams->suppRateNum = i;
        GTRACE(GRP_DRIVER_CC33,
               "Supported rates: number %d rates 0x%x",
               apRateParams->suppRateNum,
               apRateParams->supportedRatesBM);
    }

    if (NULL != apBasicRates)
    {
        for (i = 0; i < MAX_NUM_BG_RATES && 0 < apBasicRates[i]; ++i)
        {
            switch (apBasicRates[i] / 10)
            {
                case 1:
                    ratesBM = BIT_x(RATE_INDEX_1MBPS);
                    break;
                case 2:
                    ratesBM = BIT_x(RATE_INDEX_2MBPS);
                    break;
                case 5:
                    ratesBM = BIT_x(RATE_INDEX_5_5MBPS);
                    break;
                case 6:
                    ratesBM = BIT_x(RATE_INDEX_6MBPS);
                    break;
                case 9:
                    ratesBM = BIT_x(RATE_INDEX_9MBPS);
                    break;
                case 11:
                    ratesBM = BIT_x(RATE_INDEX_11MBPS);
                    break;
                case 12:
                    ratesBM = BIT_x(RATE_INDEX_12MBPS);
                    break;
                case 18:
                    ratesBM = BIT_x(RATE_INDEX_18MBPS);
                    break;
                case 24:
                    ratesBM = BIT_x(RATE_INDEX_24MBPS);
                    break;
                case 36:
                    ratesBM = BIT_x(RATE_INDEX_36MBPS);
                    break;
                case 48:
                    ratesBM = BIT_x(RATE_INDEX_48MBPS);
                    break;
                case 54:
                    ratesBM = BIT_x(RATE_INDEX_54MBPS);
                    break;

                    // Note that 22Mbps isn't supported
                default:
                    ratesBM = 0;
                    break;
            }
            apRateParams->basicRatesBM |= ratesBM;
        }
        apRateParams->basicRateNum = i;
        GTRACE(GRP_DRIVER_CC33,
               "Basic rates: number %d rates 0x%x",
               apRateParams->basicRateNum,
               apRateParams->basicRatesBM);
    }

    return 0;
}

// ----------------------------------------------------------------------------

uint32_t convertBitmapToRatesIe(uint32_t aSupportedRatesBM,
                              uint32_t aBasicRatesBM,
                              uint8_t *apRatesBuff)

{
    uint32_t numRates = 0;
    uint32_t i;

    ASSERT_GENERAL(NULL != apRatesBuff);

    // Handle basic rates IE
    if (aSupportedRatesBM & ANY_B_RATE)
    {
        if (aSupportedRatesBM & (1 << RATE_INDEX_1MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_1MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_1M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_1M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_2MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_2MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_2M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_2M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_5_5MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_5_5MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_5_5M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_5_5M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_11MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_11MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_11M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_11M;
            }
        }
    }

    // Handle extended rates IE
    if (aSupportedRatesBM & ANY_AG_OFDM_RATE)
    {
        if (aSupportedRatesBM & (1 << RATE_INDEX_6MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_6MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_6M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_6M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_9MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_9MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_9M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_9M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_12MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_12MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_12M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_12M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_18MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_18MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_18M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_18M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_24MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_24MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_24M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_24M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_36MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_36MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_36M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_36M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_48MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_48MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_48M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_48M;
            }
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_54MBPS))
        {
            if (aBasicRatesBM & (1 << RATE_INDEX_54MBPS))
            {
                apRatesBuff[numRates++] = NET_RATE_54M_BASIC;
            }
            else
            {
                apRatesBuff[numRates++] = NET_RATE_54M;
            }
        }
    }

    //CME_CC3XX_PORT_PRINT("\r\nRates:");
    for (i = 0; i < numRates; ++i)
    {
        //CME_CC3XX_PORT_PRINT("0x%x," ,apRatesBuff[i]);
        GTRACE(GRP_DRIVER_CC33_DUMP, "[%i] rate 0x%x", i, apRatesBuff[i]);
    }
    //CME_CC3XX_PORT_PRINT("\r\n");

    return numRates;
}

// ----------------------------------------------------------------------------
uint32_t convertBitmapToSupplicantRates(uint32_t aSupportedRatesBM,
                                      int   *apRatesBuff)
{
    uint32_t numRates = 0;
    uint32_t i;

    ASSERT_GENERAL(NULL != apRatesBuff);

    // Handle basic rates IE
    if (aSupportedRatesBM & ANY_B_RATE)
    {
        if (aSupportedRatesBM & (1 << RATE_INDEX_1MBPS))
        {
            apRatesBuff[numRates++] = 10;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_2MBPS))
        {
            apRatesBuff[numRates++] = 20;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_5_5MBPS))
        {
            apRatesBuff[numRates++] = 55;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_11MBPS))
        {
            apRatesBuff[numRates++] = 110;
        }
    }

    // Handle extended rates IE
    if (aSupportedRatesBM & ANY_AG_OFDM_RATE)
    {
        if (aSupportedRatesBM & (1 << RATE_INDEX_6MBPS))
        {
            apRatesBuff[numRates++] = 60;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_9MBPS))
        {
            apRatesBuff[numRates++] = 90;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_12MBPS))
        {
            apRatesBuff[numRates++] = 120;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_18MBPS))
        {
            apRatesBuff[numRates++] = 180;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_24MBPS))
        {
            apRatesBuff[numRates++] = 240;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_36MBPS))
        {
            apRatesBuff[numRates++] = 360;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_48MBPS))
        {
            apRatesBuff[numRates++] = 480;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_54MBPS))
        {
            apRatesBuff[numRates++] = 540;
        }
    }

    // Handle extended rates IE
    if (aSupportedRatesBM & ANY_N_RATE)
    {
        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS0))
        {
            apRatesBuff[numRates++] = 65;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS1))
        {
            apRatesBuff[numRates++] = 130;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS2))
        {
            apRatesBuff[numRates++] = 195;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS3))
        {
            apRatesBuff[numRates++] = 260;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS4))
        {
            apRatesBuff[numRates++] = 390;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS5))
        {
            apRatesBuff[numRates++] = 520;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS6))
        {
            apRatesBuff[numRates++] = 585;
        }

        if (aSupportedRatesBM & (1 << RATE_INDEX_MCS7))
        {
            apRatesBuff[numRates++] = 650;
        }
    }

    for (i = 0; i < numRates; ++i)
        GTRACE(GRP_DRIVER_CC33_DUMP, "[%i] rate %d", i, apRatesBuff[i]);

    return numRates;
}

// ------------------------------------------------------------------------
uint32_t convertNetRatesToBitmap(const uint8_t *apRatesIe,
                               uint32_t aNumRates)
{
    uint32_t i, ratesBM = 0;

    for (i = 0; i < aNumRates; ++i)
    {
        switch (apRatesIe[i])
        {
            case NET_RATE_1M:
            case NET_RATE_1M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_1MBPS);
                break;

            case NET_RATE_2M:
            case NET_RATE_2M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_2MBPS);
                break;

            case NET_RATE_5_5M:
            case NET_RATE_5_5M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_5_5MBPS);
                break;

            case NET_RATE_11M:
            case NET_RATE_11M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_11MBPS);
                break;

            case NET_RATE_6M:
            case NET_RATE_6M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_6MBPS);
                break;

            case NET_RATE_9M:
            case NET_RATE_9M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_9MBPS);
                break;

            case NET_RATE_12M:
            case NET_RATE_12M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_12MBPS);
                break;

            case NET_RATE_18M:
            case NET_RATE_18M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_18MBPS);
                break;

            case NET_RATE_24M:
            case NET_RATE_24M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_24MBPS);
                break;

            case NET_RATE_36M:
            case NET_RATE_36M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_36MBPS);
                break;

            case NET_RATE_48M:
            case NET_RATE_48M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_48MBPS);
                break;

            case NET_RATE_54M:
            case NET_RATE_54M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_54MBPS);
                break;

            default:
                break;
        }
    }

    return ratesBM;
}

// ------------------------------------------------------------------------
uint32_t convertBasicRatesIeToBitmap(dot11_eleHdr_t *apRatesEleHdr)
{
    uint32_t i, ratesBM = 0;
    uint8_t *pRatesIe = (uint8_t *) apRatesEleHdr + sizeof(dot11_eleHdr_t);

    for (i = 0; i < apRatesEleHdr->eleLen; ++i)
    {
        switch (pRatesIe[i])
        {
            case NET_RATE_1M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_1MBPS);
                break;

            case NET_RATE_2M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_2MBPS);
                break;

            case NET_RATE_5_5M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_5_5MBPS);
                break;

            case NET_RATE_11M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_11MBPS);
                break;

            case NET_RATE_6M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_6MBPS);
                break;

            case NET_RATE_9M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_9MBPS);
                break;

            case NET_RATE_12M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_12MBPS);
                break;

            case NET_RATE_18M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_18MBPS);
                break;

            case NET_RATE_24M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_24MBPS);
                break;

            case NET_RATE_36M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_36MBPS);
                break;

            case NET_RATE_48M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_48MBPS);
                break;

            case NET_RATE_54M_BASIC:
                ratesBM |= BIT_x(RATE_INDEX_54MBPS);
                break;

            default:
                break;
        }
    }

    return ratesBM;
}

// ------------------------------------------------------------------------
uint32_t convertMcsNetToBitmap(uint8_t *apMcsNetMask)
{
    uint32_t mcsRatesBM;

    mcsRatesBM = apMcsNetMask[0] + (((uint32_t) apMcsNetMask[1]) << 8);
    mcsRatesBM = mcsRatesBM << (RATE_INDEX_MCS0);

    return mcsRatesBM;
}

// ------------------------------------------------------------------------
void validateRateVsBand(RadioBand_e aBand,
                        uint32_t *aSupportedRatesBM,
                        uint32_t *aBasicRatesBM)
{
    if (RADIO_BAND_5GHZ == aBand)
    {
        *aSupportedRatesBM &= ~ANY_B_RATE;
    }

    *aBasicRatesBM &= *aSupportedRatesBM;

    if (*aBasicRatesBM == 0)
    {
        if (RADIO_BAND_5GHZ == aBand)
        {
            *aBasicRatesBM =
                    BIT_x(RATE_INDEX_6MBPS) | BIT_x(RATE_INDEX_12MBPS) | BIT_x(RATE_INDEX_24MBPS);
        }
        else
        {
            *aBasicRatesBM = BIT_x(RATE_INDEX_1MBPS) | BIT_x(RATE_INDEX_2MBPS);
        }
    }
}

// ------------------------------------------------------------------------
void determineLinkRates(rateSets_t *apPeerRates,
                        rateSets_t *apLinkRates)
{
    uint32_t staTotalRatesBM;
    uint32_t basicRatesBM, supportedRatesBM;

    cfgGetRates(ROLE_STA, &basicRatesBM, &supportedRatesBM);

    // Aggregate all supported rates
    staTotalRatesBM = basicRatesBM | supportedRatesBM;

    apLinkRates->basicRatesBM = staTotalRatesBM & apPeerRates->basicRatesBM;
    apLinkRates->supportedRatesBM = staTotalRatesBM & apPeerRates->supportedRatesBM;

    if (0 == apLinkRates->basicRatesBM)
    {
        apLinkRates->basicRatesBM = basicRatesBM;
    }

}

// ------------------------------------------------------------------------
void getPeerRates(cmeScanCandidateDesc_t *apCandidateDesc,
                  rateSets_t *apLinkRates)
{
    uint8_t *pNextIe;
    uint8_t *pHtCaps = NULL, *pHtInfo = NULL;
    uint32_t numReadIes = 0;
    uint32_t mcsRateBM, extSuppBM;
    uint32_t basicRateBM, supportedRateBM;
    uint8_t *pRatesIe;
    rateSets_t peerRates;
    dot11_eleHdr_t *pEleHdr;
    dot11_eleHdr_t *pRatesEleHdr = NULL, *pExtRatesEleHdr = NULL;

    // Find IEs
//    pNextIe = (uint8_t *)apCandidateDesc->mpScanResult + sizeof(struct wpa_scan_res);
    pNextIe = (uint8_t *) apCandidateDesc->mInfoElements;
    while (numReadIes < apCandidateDesc->mScanResult.ie_len)
    {
        pEleHdr = (dot11_eleHdr_t *) pNextIe;

        switch (pEleHdr->eleId)
        {
            case WLAN_EID_SUPP_RATES:
                pRatesEleHdr = pEleHdr;
                break;

            case WLAN_EID_EXT_SUPP_RATES:
                pExtRatesEleHdr = pEleHdr;
                break;

            case WLAN_EID_HT_CAP:
                pHtCaps = pNextIe + sizeof(dot11_eleHdr_t);
                break;

            case WLAN_EID_HT_OPERATION:
                pHtInfo = pNextIe + sizeof(dot11_eleHdr_t);
                break;

            default:
                break;
        }
        numReadIes += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
        pNextIe += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
    }

    if (NULL == pRatesEleHdr)
    {
        GTRACE(GRP_GENERAL_ERROR, "ERROR: peer rates IE is missing");

        apLinkRates->basicRatesBM = 0;
        apLinkRates->supportedRatesBM = 0;
    }

    // Rates bit map
    basicRateBM = convertBasicRatesIeToBitmap(pRatesEleHdr);

    pRatesIe = (uint8_t *) pRatesEleHdr + sizeof(dot11_eleHdr_t);
    supportedRateBM = convertNetRatesToBitmap(pRatesIe, pRatesEleHdr->eleLen);

    // Extended rates bit map
    if (NULL != pExtRatesEleHdr)
    {
        extSuppBM = convertBasicRatesIeToBitmap(pExtRatesEleHdr);
        basicRateBM |= extSuppBM;

        pRatesIe = (uint8_t *) pExtRatesEleHdr + sizeof(dot11_eleHdr_t);
        extSuppBM = convertNetRatesToBitmap(pRatesIe, pExtRatesEleHdr->eleLen);
        supportedRateBM |= extSuppBM;
    }


    // MCS rates bit map
    if (NULL != pHtCaps)
    {
        mcsRateBM = convertMcsNetToBitmap(pHtCaps
                + DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET);
        supportedRateBM |= mcsRateBM;

    }

    // MCS rates bit map
    if (NULL != pHtInfo)
    {
        mcsRateBM = convertMcsNetToBitmap(pHtInfo
                + DOT11_HT_INFORMATION_MCS_RATE_OFFSET);
        basicRateBM |= mcsRateBM;
    }


    peerRates.basicRatesBM = basicRateBM;
    peerRates.supportedRatesBM = supportedRateBM;
    determineLinkRates(&peerRates, apLinkRates);
}

// ------------------------------------------------------------------------
void getPeerIes(cmeScanCandidateDesc_t *apCandidateDesc,
                ti_driver_parsedIes_t *apPeerIes)
{
    uint8_t *pNextIe;
    uint32_t numReadBytes = 0;
    dot11_eleHdr_t *pEleHdr;

    // All pointers are set to NULL, this indicates IE wasn't found.
    // Pointer to detected IE is updated below.
    memset(apPeerIes, 0, sizeof(ti_driver_parsedIes_t));

    // Find IEs and set their pointers in caller stucture
    pNextIe = (uint8_t *) apCandidateDesc->mInfoElements;
    while (numReadBytes < apCandidateDesc->mScanResult.ie_len)
    {
        pEleHdr = (dot11_eleHdr_t *) pNextIe;

        switch (pEleHdr->eleId)
        {
            case WLAN_EID_SUPP_RATES:
                apPeerIes->pRatesIe = pEleHdr;
                GTRACE(GRP_DRIVER_CC33, "Found rates IE at 0x%x", pEleHdr);
                ;
                break;

            case WLAN_EID_EXT_SUPP_RATES:
                apPeerIes->pExtRatesIe = pEleHdr;
                GTRACE(GRP_DRIVER_CC33,
                       "Found extended rates IE at 0x%x",
                       pEleHdr)
                ;
                break;

            case WLAN_EID_HT_CAP:
                apPeerIes->pHtCapsIe = pEleHdr;
                GTRACE(GRP_DRIVER_CC33,
                       "Found HT capabilities IE at 0x%x",
                       pEleHdr)
                ;
                break;

            case WLAN_EID_HT_OPERATION:
                apPeerIes->pHtInfoIe = pEleHdr;
                GTRACE(GRP_DRIVER_CC33, "Found HT info IE at 0x%x", pEleHdr);
                break;

            default:
                break;
        }
        numReadBytes += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
        pNextIe += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
    }
}



// ------------------------------------------------------------------------
// TODO: need to implemet
#if 0
int32_t cc33drv_AllocAndConfigTXDataPack(uint32_t aRoleId,
                                       const uint8_t  *apPayload,
                                       uint32_t aPayloadSize,
                                       ltxpSendFrameRequest_t *apSendReq)
{
    CC33_FrameTxDesc_t *pDesc;
    uint8_t  descId;
    uint32_t allocSize;
    uint32_t  rc = 0;

    // ------------------------------------------------------------------------
    // Handle packet allocation:
    //  o Calculate packet size
    //  o Allocate a packet from MMU
    // ------------------------------------------------------------------------
    allocSize = CC33_DRV_DATA_PACKET_MIN_SIZE + aPayloadSize;
    rc = TxcAllocateNoWaitRequest(CC33_DRIVER_MMU_ALLOC_MASTER_TYPE, // [in ] CC33xx master ID
                                  allocSize,                         // [in ] Allocation size, in bytes, for the entire thing
                                  MMU_ALLOC_OPCODE_ALLOCATE,         // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
                                  MMU_POOL_TYPE_MNGMT, //MMU_POOL_TYPE_TX, // [in ] Pool ID from which to allocate (TX/RX/MNG) (although EAPOL is a data frame, its priority is as a management frame so the pool used is MNG)
                                  &descId,                           // [out] -> CC33xx virtual descriptor index
                                  0);                                // [in ] Reallocated descriptor index - irrelevant for ALLOCATE

    // If allocation failed, return with error indication
    if (rc != TXC_RETURN_CODE_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR,
               "ERROR: failed to allocate %d bytes for data packet",
               allocSize);

        return -1;
    }

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set payload address on the descriptor
    //  o Copy payload to allocated memory
    //  o Set packet information on send request
    //    Calling function may override any parameter in case shared configuration
    //    doesn't fit the specific packet.
    // ------------------------------------------------------------------------
    pDesc = (struct CC33_FrameTxDesc_s *) MMU_GET_VIRTUAL_ADDR_FROM_DESC(descId);

    pDesc->address = (uint32_t) ((uint8_t *) pDesc + CC33_DRV_PAYLOAD_START_OFFSET);
    os_memcpy((uint8_t *)pDesc->address, apPayload, aPayloadSize);

    apSendReq->address = pDesc->address;
    apSendReq->callback = NULL;
    apSendReq->callback_msi = 0;
    apSendReq->expiry_duration_us = TX_NO_EXPIRY;
    apSendReq->frame = pDesc;
    apSendReq->frame_type = FRAME_TYPE_QOS_DATA;  // LTXP verifies the specific link supports QOS data.
                                                  // In case it isn't, type is changed to DATA
    apSendReq->payload_length = aPayloadSize;
    apSendReq->release_frame = TRUE;
    apSendReq->etherType = ETHER_TYPE_INVALID;
    apSendReq->role_id = aRoleId;
    apSendReq->retriesLimit    = LTXP_TX_RETRIES_DEFAULT_LIMIT;
    apSendReq->rate_ovr = RATE_OVR_DISABLED;

    return 0;
}
#endif
#if 0
// The below serves just for debugging TX.
// If a CB is required, this can serve for logging TX result and releasing the TX packet.
void cc33_driver_tx_result(const uint8_t aDescId)
{
    struct CC33_FrameTxDesc_s *pDesc = (struct CC33_FrameTxDesc_s *) MMU_GET_VIRTUAL_ADDR_FROM_DESC(aDescId);

    GTRACE(GRP_DRIVER_CC33, "TX done: desc ID 0x%x status ENUM(TX_status_e, %d) retries %d",
                              aDescId, pDesc->tx_status, pDesc->ack_failure_count);

    if (TRUE == pDesc->tx_exchange.sw_no_release_request)
    {
        TxcReleaseDeAllocRequestPush(aDescId);
    }
}
#endif

// ------------------------------------------------------------------------
// TODO: need to implemet
#if 0
int32_t cc33drv_AllocAndConfigMngPack(uint32_t aRoleId,
                                    uint32_t aPayloadSize,
                                    uint32_t aType,
                                    Bool32 aKeepAfterTx,
                                    uint8_t *apDescId,
                                    struct ieee80211_mgmt **apMngPack,
                                    CC33_FrameTxDesc_t **apDescriptor,
                                    ltxpSendFrameRequest_t *apSendReq)
{
    CC33_FrameTxDesc_t *pDesc;
    uint32_t allocSize;
    int32_t rc = 0;

    // ------------------------------------------------------------------------
    // Handle packet allocation:
    //  o Calculate packet size
    //  o Allocate a packet from MMU
    // ------------------------------------------------------------------------
    allocSize = CC33_DRV_MNG_PACKET_MIN_SIZE + aPayloadSize;
    rc = TxcAllocateNoWaitRequest(CC33_DRIVER_MMU_ALLOC_MASTER_TYPE, // [in ] CC33xx master ID
                                  allocSize,                         // [in ] Allocation size, in bytes, for the entire thing
                                  MMU_ALLOC_OPCODE_ALLOCATE,         // [in ] Opcode = ALLOC (as opposed to REALLOC or DEALLOC)
                                  MMU_POOL_TYPE_MNGMT,               // [in ] Pool ID from which to allocate (TX/RX/MNG)
                                  apDescId,                          // [out] -> CC33xx virtual descriptor index
                                  0);                                // [in ] Reallocated descriptor index - irrelevant for ALLOCATE

    // If allocation failed, return with error indication
    if (rc != TXC_RETURN_CODE_SUCCESS)
    {
        GTRACE(GRP_GENERAL_ERROR,
               "ERROR: failed to allocate %d bytes for management packet",
               allocSize);
        return -1;
    }

    // ------------------------------------------------------------------------
    // Allocation succeeded
    //  o Set packet information on descriptor
    //  o Construct payload
    // ------------------------------------------------------------------------
    pDesc = (CC33_FrameTxDesc_t *) MMU_GET_VIRTUAL_ADDR_FROM_DESC(*apDescId);

    apSendReq->address = (uint32_t) ((uint8_t *) pDesc + CC33_DRV_PAYLOAD_START_OFFSET);
    apSendReq->frame = pDesc;
    apSendReq->frame_type = aType;
    apSendReq->payload_length = aPayloadSize;
    apSendReq->release_frame = !aKeepAfterTx;
    apSendReq->role_id = aRoleId;
    apSendReq->callback = NULL;
    apSendReq->callback_msi = 0;
    apSendReq->etherType = ETHER_TYPE_INVALID;
    apSendReq->expiry_duration_us = TX_NO_EXPIRY;  // may be overriden by the caller
    apSendReq->retriesLimit    = LTXP_TX_RETRIES_DEFAULT_LIMIT;
    apSendReq->rate_ovr = RATE_OVR_DISABLED;

    *apMngPack = (struct ieee80211_mgmt *) ((uint8_t *) (apSendReq->address - WLAN_HDR_LEN));

    GTRACE(GRP_DRIVER_CC33,
           "Allocated payload size %d type 0x%x desc ID 0x%x set address to 0x%x apMngPack to 0x%x",
           aPayloadSize,
           aType,
           *apDescId,
           apSendReq->address,
           *apMngPack);

    *apDescriptor = pDesc;
    return 0;
}
#endif
//TODO - When session ID in tx and rx will share the same fields - implement the check session validity in one function for TX and RX
//-------------------------------------------------------------------
// TODO: need to implemet
#if 0
Bool_e cc33_RxFrame_CheckSessionIsValid(CC33_FrameRxDesc_t *pDesc)
{


    Bool_e retVal = FALSE;
    uint8_t linkSessionId;

    if (pDesc->link_role.link_id != INVALID_LINK)
    {
        if ( Links_GetConnectionState(pDesc->link_role.link_id)!= LINK_CONNECTION_STATE_DISCONNECTED ){
            linkSessionId = Links_GetLinkSessionId(pDesc->link_role.link_id);
            if (linkSessionId != 0xff)
            {
                if (linkSessionId ==  (uint8_t) ((pDesc->sw_tagging._w32 >> 16) & 0x00ff))
                {
                       retVal = TRUE;
                }
            }
        }
    }
    return (retVal);
}
#endif
//--------------------------------------------------------------------
// TODO: need to implement
#if 0
Bool_e cc33_TxResult_CheckSessionIsValid(CC33_FrameTxDesc_t *pDesc)
{

    Bool_e retVal = FALSE;
    uint8_t linkSessionId;

    if (pDesc->link_role_queue.link_id != INVALID_LINK)
    {
        if ( Links_GetConnectionState(pDesc->link_role_queue.link_id)!= LINK_CONNECTION_STATE_DISCONNECTED ){
            linkSessionId = Links_GetLinkSessionId(pDesc->link_role_queue.link_id);
            if (linkSessionId != 0xff)
            {
                if (linkSessionId ==  (uint8_t) (((SL_BSD_SocketLabel_u)(pDesc->socket_label._w32)).hdi_ll_instance_id))
                {
                       retVal = TRUE;
                }
            }
        }
    }
    return (retVal);
}
#endif
//--------------------------------------------------------------------
