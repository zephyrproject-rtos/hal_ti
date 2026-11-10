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
#ifndef IE_PARSER_UTIL_H
#define IE_PARSER_UTIL_H

#include "public_types.h"
#include <string.h>


/*=============================================================================
    Export Functions
=============================================================================*/



/******************************************************************************
   IEParser_AdvanceToNextIe

   DESCRIPTION:  get pointer to info element and advance to next info element.

   PARAMETERS:   iePtr - pointer to info element located inside the frame

   RETURNS:      iePtr - pointer to next info element located inside the frame
******************************************************************************/
void IEParser_AdvanceToNextIe(uint8_t** iePtr);


/******************************************************************************
   IEParser_FindIe

   DESCRIPTION:  Parses info elements.
                 get desired info element ID + Length + pointer to the begining of the
                 info elements location.

   PARAMETERS:   payloadStart   -  pointer to payload start, which is the beginning of the IE.
                 payloadLength  - length of the frame payload
                 ieId           - info element ID to look for

   OUTPUT:       pIe - pointer to info element location

   RETURN:       TRUE - if info element found, else FALSE
******************************************************************************/
Bool32 IEParser_FindIe(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t  ieId, uint8_t**   pIe);


/******************************************************************************
   IEParser_FindIe_forBeaconProbeRsp

   DESCRIPTION:  parse info element inside Beacon or Probe Response.
                 get info element ID + Length + pointer to for the info element location

   PARAMETERS:   payloadStart   - pointer to Beacon / Probe Response payload start,
                                  which is the beginning of the IE
                 payloadLength  - length of the frame payload
                 ieId           - info element ID to look for

   OUTPUT:       pIe - pointer to info element location

   RETURN:       TRUE - if info element found, else FALSE
******************************************************************************/
Bool32 IEParser_FindIe_forBeaconProbeRsp(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t  ieId, uint8_t**   pIe);


/******************************************************************************
   IEParser_FindVendorSpecificIe

   DESCRIPTION:  parse frame and check if vendor specific IE (VENDOR_SPECIFIC_IE_ID) with
                 specific oui type (i.e.  WPA_OUI_TYPE or DOT11_WPS_OUI) is found inside the frame

   PARAMETERS:   payloadStart  -  pointer to payload start, which is the beginning of the IE
                 payloadLength - length of the frame payload
                 uint8_t* pInputOui   - pointer to oui to search

   OUTPUT:       pIe       - pointer to info element location

   RETURN:       TRUE - if info element found, else FALSE
******************************************************************************/
Bool_e  IEParser_FindVendorSpecificIe(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t* pInputOui, uint8_t**   pIe);


/******************************************************************************
   IEParser_FindVendorSpecificIe_forBeaconProbeRsp

   DESCRIPTION:  parse Beacon / Probe Response frame and check if vendor specific IE (VENDOR_SPECIFIC_IE_ID) with
                 specific oui type (i.e.  WPA_OUI_TYPE or DOT11_WPS_OUI) is found inside the frame.

   PARAMETERS:   payloadStart  -  pointer to Beacon / Probe Response payload start
                 payloadLength -  length of the frame payload start,
                                  which is the beginning of the IE
                 uint8_t* pInputOui   - pointer to oui to search

   OUTPUT:       pIe       - pointer to info element location

   RETURN:       TRUE - if info element found, else FALSE
******************************************************************************/
Bool_e  IEParser_FindVendorSpecificIe_forBeaconProbeRsp(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t* pInputOui, uint8_t**   pIe);

/******************************************************************************
   IEParser_MergeIeBuffers

   DESCRIPTION:  Merge two info element buffers. If an IE exsists in both buffers,
                  it is taken only from the primary buffer.

   PARAMETERS:   PrimePayloadStart  -  Pointer to primary buffer
                 PrimePayloadLength -  Length of the primary buffer
                 SecondPayloadStart -  Pointer to secondary buffer
                 PrimePayloadLength -  Length of the secondary buffer
                 MergedPayload      -  Merged output will be written here
                 MergedPayloadLength-  Size of the merge buffer on input, size of the 
                  merge result on output


   OUTPUT:       MergedPayloadLength- Size of the merged result

   RETURN:       TRUE if merge was successfully completed, FALSE otherwise. 
******************************************************************************/
Bool_e  IEParser_MergeIeBuffers( uint8_t* PrimePayloadStart, uint16_t  PrimePayloadLength,
                                 uint8_t* SecondPayloadStart, uint16_t  SecondPayloadLength,
                                 uint8_t* MergedPayload, uint16_t* MergedPayloadLength);


#endif //IE_PARSER_UTIL_H
