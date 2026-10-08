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

#include "fw_utils.h"
#include "gtrace.h"
#include "osi_kernel.h"
// ============================================================================
//      Modules private definitions
// ============================================================================

// Macros used for constructing rates IEs
#define DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET   (3)
#define DOT11_HT_INFORMATION_MCS_RATE_OFFSET    (6)

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

    for (i = 0; i < numRates; ++i)
    {
        CME_CC3XX_PORT_PRINT("\r\n [%i] rate 0x%x\n" ,i, apRatesBuff[i]);
        GTRACE(GRP_DRIVER_CC33_DUMP, "[%i] rate 0x%x", i, apRatesBuff[i]);
    }

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
#if 0
// ------------------------------------------------------------------------
void determineLinkRates(rateSets_t *apPeerRates,
                        rateSets_t *apLinkRates)
{
    uint32_t staTotalRatesBM;
    uint32_t basicRatesBM =0, supportedRatesBM = 0;

    //cfgGetRates(ROLE_STA, &basicRatesBM, &supportedRatesBM); //TODO


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

#ifndef PMAC_AX
    // michal temp. check SGI support
    if (supportedRateBM & BIT_x(RATE_INDEX_MCS7))
    {
        supportedRateBM |=  BIT_x(RATE_INDEX_MCS7_SGI);
    }
    GTRACE(GRP_DRIVER_CC33, "michal: pHtInfo: 0x%x, pHtCaps: 0x%x, DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET 0x%x,  mcsRateBM 0x%x", (uint32_t)pHtInfo, (uint32_t)pHtCaps, (uint32_t)DOT11_HT_CAPABILITIES_MCS_RATE_OFFSET, (uint32_t)mcsRateBM);
#endif


    peerRates.basicRatesBM = basicRateBM;
    peerRates.supportedRatesBM = supportedRateBM;
    determineLinkRates(&peerRates, apLinkRates);
}
#endif

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
                ;
                break;

            default:
                break;
        }
        numReadBytes += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
        pNextIe += pEleHdr->eleLen + sizeof(dot11_eleHdr_t);
    }
}
