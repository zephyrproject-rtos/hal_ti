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

  FILENAME:       drv_ti_internal.h

  DESCRIPTION:    This files defines the APIs between ti driver supplicant driver
  	  	  	  	  (driver_ti_wifi) and its service files.

  ----------------------------------------------------------------------------- */
#ifndef _FW_UTILS_H_
#define _FW_UTILS_H_
#ifndef CC33xx
#include "drv_ti_internal.h"

// ============================================================================
//	Type definitions
// ============================================================================

// -----------------------------------------
// Packet allocation related definitions
// -----------------------------------------



typedef struct
{
    dot11_eleHdr_t *pRatesIe;
    dot11_eleHdr_t *pExtRatesIe;
    dot11_eleHdr_t *pHtCapsIe;
    dot11_eleHdr_t *pHtInfoIe;
} cc33drv_parsedIes_t;


// ============================================================================
//  Driver cc33xx internal utilities
// ============================================================================
/* ----------------------------------------------------------------------------
 utilsDumpHex
    Utility for dumping TX/RX packets

 Parameters:    apBuff - pointer to buffer to be printed
                aLen - number of bytes to print
 Return code:   0 - success
---------------------------------------------------------------------------- */
void utilsDumpHex(const uint8_t *apBuff, uint32_t aLen);

/* ----------------------------------------------------------------------------
 utilsDumpScanResult
    Dump scan result fields

 Parameters:    apResult - pointer to scan result
 Return code:   none
---------------------------------------------------------------------------- */
void utilsDumpScanResult(struct wpa_scan_res *apResult);

/* ----------------------------------------------------------------------------
 convertRatesToBitmap
    This API converts rates array to rates bitmaps (defined in rates.h)

 Parameters:  IN  apSupportedRates - supplicant supported rates
              IN  apBasicRates - supplicant basic rates
              OUT apRateParams - conversion product in terms of rates bit masks

 Return code: 0 - OK, -1 - missing parameters
---------------------------------------------------------------------------- */
int32_t convertRatesToBitmap(struct hostapd_rate_data *apSupportedRates,
                           int           *apBasicRates,
                           apRatesSets_t *apRateParams);

/* ----------------------------------------------------------------------------
 convertBitmapToRatesIe
    This API creates rates IE from rates bitmask (defined in rates.h).
    Created IE includes element ID, length and an array of rates (in terms of
    500kbps).

 Parameters:  IN  aSupportedRatesBM - bitmap of supported rates
              IN  aBasicRatesBM - bitmap of basic rates
              OUT apRatesBuff - buffer for conversion result (size must be DOT11_MAX_SUPPORTED_RATES)

 Return code: number of bytes added to IE
---------------------------------------------------------------------------- */
uint32_t convertBitmapToRatesIe(uint32_t aSupportedRatesBM,
                              uint32_t aBasicRatesBM,
                              uint8_t *apRatesBuff);

/* ----------------------------------------------------------------------------
 convertBitmapToSupplicantRates
    This API translates rates bitmask (defined in rates.h) to an array of rates
    described in 100kbps terms.

 Parameters:  IN  aSupportedRatesBM - bitmap of supported rates
              OUT apRatesBuff - buffer for conversion result (size must be DOT11_MAX_SUPPORTED_RATES)

 Return code: total number of supported rates
---------------------------------------------------------------------------- */
uint32_t convertBitmapToSupplicantRates(uint32_t aSupportedRatesBM,
                                      int    *apRatesBuff);

/* ----------------------------------------------------------------------------
 convertNetRatesToBitmap
    This API converts network rates array to rates bit mask (nased on RateIndex_e)

 Parameters:  IN apRatesIe - pointer to rates array
              IN aNumRates - number of rates in array

 Return code: rates bit mask
---------------------------------------------------------------------------- */
uint32_t convertNetRatesToBitmap(const uint8_t *apRatesIe, uint32_t aNumRates);

/* ----------------------------------------------------------------------------
 validateRateVsBand
    This API verifies supported and based rates are correct:
       - For A band it removes B rates from supported rates BM
       - If basic rate set empty (no shared rates between us & peer) it sets
         a subset of basic rates.

 Parameters:  IN  aBand - peer's band
              OUT aSupportedRatesBM - supported rate BM
              OUT aBasicRatesBM - basic rate BM

 Return code: number of bytes added to IE
---------------------------------------------------------------------------- */
void validateRateVsBand (RadioBand_e aBand,
                         uint32_t *aSupportedRatesBM,
                         uint32_t *aBasicRatesBM);

/* ----------------------------------------------------------------------------
 getPeerRates
    This API supplies peer rates based on received rates IE, ext rates IE & HT IEs
    and on chip STA supported rates.

 Parameters:  IN  apCandidateDesc - scan result holding peer IEs
              OUT apLinkRates - peer basic & supported rates

 Return code: none
---------------------------------------------------------------------------- */
void getPeerRates(cmeScanCandidateDesc_t *apCandidateDesc, rateSets_t *apLinkRates);

/* ----------------------------------------------------------------------------
 getPeerIes
    This API parses received beacon/probe response and retruns a structure with
    pointers to rates IE, ext rates IE & HT IEs. These IEs are parsed when
    building start role parameters.

 Parameters:  IN  apCandidateDesc - scan result holding peer IEs
              IN/OUT apPeerIes - pointer to a stucture with required IEs pointers

 Return code: none
---------------------------------------------------------------------------- */
void getPeerIes(cmeScanCandidateDesc_t *apCandidateDesc, ti_driver_parsedIes_t *apPeerIes);
#endif // CC33xx

#endif