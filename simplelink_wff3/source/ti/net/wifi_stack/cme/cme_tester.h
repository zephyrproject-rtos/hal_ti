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
  FILENAME:       cme_tester.h

  DESCRIPTION:    This file simulates CME events for testing CME & supplicant
                  integration.
                  This tester allows defining a sequence of simulated events,
                  including their timing.
                  A list of tests may run in a sequence.

  HISTORY:
                  07/15 Creation
  ----------------------------------------------------------------------------- */

#include "cme_scan_api.h"

// ============================================================================
//      Test configurations definitions
// ============================================================================

// ============================================================================
//      Test type definitions
// ============================================================================


typedef enum
{
    CME_TEST_RESP_OK,
    CME_TEST_RESP_GENERAL_ERR,
    CME_TEST_RESP_UNSUPPORTED_AUTH_ALG,
    CME_TEST_RESP_NONE
} cmeTesterConnectResp_e;



// ============================================================================
//      Test API
// ============================================================================

void cmeTestInit();

#ifndef CC33XX_NO_CME_TEST
void cmeTestBuildScanResult(cmeScanSharedInfo_t *apSharedInfo, EScanRequestType aType);
void   cmeClearFastTest();
Bool_e cmeIsFastTest();
#endif

#ifndef FPGA_PMAC_TX
cmeTesterConnectResp_e cmeTestConfigResponse(uint32_t aPackType);
#endif

