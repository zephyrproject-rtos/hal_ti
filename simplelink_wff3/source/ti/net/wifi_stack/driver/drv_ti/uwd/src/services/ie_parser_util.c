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
#include "public_types.h"
#include <string.h>
#include "mpdu.h"
#include "802_11defs.h"


/*=============================================================================
    Internal Defines And Macros
=============================================================================*/






/*=============================================================================
    Internal Type Definitions
=============================================================================*/

/*=============================================================================
    Internal Variables
=============================================================================*/




/*=============================================================================
    Global Variables
=============================================================================*/


/*=============================================================================
    Internal Functions Implementation
=============================================================================*/






/*=============================================================================
    Export Functions Implementation
=============================================================================*/




/******************************************************************************
   IEParser_AdvanceToNextIe

   DESCRIPTION:  get pointer to info element and advance to next info element.

   PARAMETERS:   iePtr - pointer to info element located inside the frame

   RETURNS:      iePtr - pointer to next info element located inside the frame
******************************************************************************/
void IEParser_AdvanceToNextIe(uint8_t** iePtr)
{
    uint8_t*              pCurrentIe;
    uint8_t               ieLength;

    pCurrentIe = *iePtr;

    /* +--------------------------------------+
     * | Info Element structure:              |
     * +--------------------------------------+
     * |  ID      - 1 Byte                    |
     * |  Length  - 1 Byte                    |
     * |  Data    - acourding to the length   |
     * +- ------------------------------------+
     */


    ++pCurrentIe;               //advance to Length
    ieLength = *pCurrentIe;     //get the length
    ++pCurrentIe;               //advance to data
    pCurrentIe += ieLength;

    *iePtr = pCurrentIe;
}


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
Bool32 IEParser_FindIe(uint8_t* payloadStart, uint16_t payloadLength,uint8_t ieId, uint8_t** pIe)
{
    dot11_eleHdr_t*     pCurrentIe;
    uint8_t*              ptrPayloadEnd;
    Bool32              retVal = FALSE;

    pCurrentIe   = (dot11_eleHdr_t*)payloadStart;

    ptrPayloadEnd =     (uint8_t*)payloadStart
                      + (payloadLength - 1);

    /* +--------------------------------------+
     * | Info Element structure:              |
     * +--------------------------------------+
     * |  ID      - 1 Byte                    |
     * |  Length  - 1 Byte                    |
     * |  Data    - acourding to the length   |
     * +- ------------------------------------+
     */

    do
    {
        if (pCurrentIe->eleId == ieId)
        {
            //we found the IE !!!

            *pIe      = (uint8_t*)pCurrentIe;

            retVal = TRUE;
            break;
        }

        //advance to next IE
        IEParser_AdvanceToNextIe((uint8_t**) &pCurrentIe);

    } while ((uint8_t*)pCurrentIe < ptrPayloadEnd);

    return retVal;
}


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
Bool32 IEParser_FindIe_forBeaconProbeRsp(uint8_t* payloadStart, uint16_t payloadLength,uint8_t ieId, uint8_t** pIe)
{
    return IEParser_FindIe(payloadStart + BEACON_PROBRESP_FIXED_LENGTH_FIELDS,
                            payloadLength - BEACON_PROBRESP_FIXED_LENGTH_FIELDS, ieId, pIe);
}

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
Bool_e  IEParser_FindVendorSpecificIe(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t* pInputOui, uint8_t**   pIe)
{
    dot11_eleHdr_t*     pCurrentIe;
    uint8_t*              ptrPayloadEnd;
    uint8_t*              pOui ;
    Bool32              retVal = FALSE;

    pCurrentIe   = (dot11_eleHdr_t*)payloadStart;

    ptrPayloadEnd =     (uint8_t*)payloadStart
                      + (payloadLength - 1);

    /* +--------------------------------------+
     * | Info Element structure:              |
     * +--------------------------------------+
     * |  ID      - 1 Byte                    |
     * |  Length  - 1 Byte                    |
     * |  Data    - according to the length   |
     * +- ------------------------------------+
     */

    do
    {
        if ((pCurrentIe->eleId == VENDOR_SPECIFIC_IE_ID) &&
            (pCurrentIe->eleLen >= DOT11_OUI_LEN))
        {
             pOui = (uint8_t*)pCurrentIe + 2;   //ID + Length

             //now check if there is a match with the requested oui
             if (    (pOui[0] == pInputOui[0])
                  && (pOui[1] == pInputOui[1])
                  && (pOui[2] == pInputOui[2])
                  && (pOui[3] == pInputOui[3])
                )
             {
                 *pIe  = (uint8_t*)pCurrentIe;

                 retVal = TRUE;
                 break;
             }
        }

        //advance to next IE
        IEParser_AdvanceToNextIe((uint8_t**) &pCurrentIe);

    } while ((uint8_t*)pCurrentIe < ptrPayloadEnd);

    return retVal;
}

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
Bool_e  IEParser_FindVendorSpecificIe_forBeaconProbeRsp(uint8_t* payloadStart, uint16_t  payloadLength, uint8_t* pInputOui, uint8_t**   pIe)
{
    return IEParser_FindVendorSpecificIe(payloadStart + BEACON_PROBRESP_FIXED_LENGTH_FIELDS,
                                        payloadLength - BEACON_PROBRESP_FIXED_LENGTH_FIELDS, pInputOui, pIe);

}
Bool_e IEParser_MergeIeBuffers(uint8_t* PrimePayloadStart, uint16_t PrimePayloadLength,
                               uint8_t* SecondPayloadStart, uint16_t SecondPayloadLength,
                               uint8_t* MergedPayload, uint16_t* MergedPayloadLength)
{
    uint8_t *MergedPayloadPtr = MergedPayload;
    uint16_t MergedLength = 0;
    uint8_t *CurrentIePtr, *Dummy;
    uint8_t CurrentIeLength;
    const uint8_t *SecondPayloadEnd = SecondPayloadStart + SecondPayloadLength;
    if (PrimePayloadLength > *MergedPayloadLength)
    {
        return FALSE;
    }
    memcpy(MergedPayloadPtr, PrimePayloadStart, PrimePayloadLength);
    MergedPayloadPtr += PrimePayloadLength;
    MergedLength += PrimePayloadLength;
    CurrentIePtr = SecondPayloadStart;
    while (CurrentIePtr < (SecondPayloadEnd-1))
    {
        CurrentIeLength = *(CurrentIePtr + 1) + 2; // IE length field + 2 bytes for ID and length
        if (FALSE == IEParser_FindIe(PrimePayloadStart, PrimePayloadLength, *CurrentIePtr, &Dummy))
        {
            if (MergedLength + CurrentIeLength > *MergedPayloadLength) 
            {
                return FALSE;
            }
            if (CurrentIePtr + CurrentIeLength > SecondPayloadEnd) 
            {
                return FALSE; 
            }
            memcpy(MergedPayloadPtr, CurrentIePtr, CurrentIeLength);
            MergedPayloadPtr += CurrentIeLength;
            MergedLength += CurrentIeLength;
        }
        CurrentIePtr += CurrentIeLength;
    }
    *MergedPayloadLength = MergedLength;
    return TRUE;
}