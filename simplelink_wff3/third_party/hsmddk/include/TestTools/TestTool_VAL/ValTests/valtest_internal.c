/* valtest_internal.c
 *
 * Description: VAL Test Suite internal helper functions.
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#include "valtest_internal.h"

/*----------------------------------------------------------------------------
 * valtest_StrictArgsCheck
 *
 * This function checks once if the VAL API is with restirct arguments
 * checking enabled.
 */
bool
valtest_StrictArgsCheck(void)
{
    static ValStatus_t gl_StrictArgs = VAL_SUCCESS;

    if (gl_StrictArgs == VAL_SUCCESS)
    {
        uint8_t * buffer_p;
        ValSize_t outDataSize = 32;

        buffer_p = SFZUTF_MALLOC(outDataSize);
        if (buffer_p != NULL)
        {
            ValSymContextPtr_t SymContext_p = NULL;
            ValStatus_t Status;

            Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_AES,
                                  VAL_SYM_MODE_CIPHER_ECB,
                                  false,
                                  &SymContext_p);
            if (Status == VAL_SUCCESS)
            {
                gl_StrictArgs = val_SymCipherUpdate(SymContext_p,
                                                    NULL, 0,
                                                    buffer_p, &outDataSize);
                (void)val_SymRelease(SymContext_p);
            }

            SFZUTF_FREE(buffer_p);
        }
        else
        {
            // Assume no strict argument checking
        }
    }

    // Return true only in case of VAL_BAD_ARGUMENT, otherwise assume no
    // strict argument checking
    return (gl_StrictArgs == VAL_BAD_ARGUMENT);
}


/*----------------------------------------------------------------------------
 * valtest_DefaultTrngConfig
 *
 * This function set the default TRNG configuartion and actives the TRNG.
 */
ValStatus_t
valtest_DefaultTrngConfig(void)
{
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    return val_TrngConfig(0, g_ValTestTrngSampleCycles, 1, 8, 0, 31, 56, 325, true);
}


/*----------------------------------------------------------------------------
 * valtest_IsTrngActive
 *
 * This function checks if TRNG has been activated and on request it tries
 * to activate the TRNG if it was not activated.
 */
bool
valtest_IsTrngActive(
        const bool fActivate)
{
    ValStatus_t Status = VAL_NO_MEMORY;
    uint8_t * buffer_p;

    buffer_p = SFZUTF_MALLOC(20);
    if (buffer_p != NULL)
    {
        // Get a random number
        Status = val_RandomData(16, buffer_p);
        SFZUTF_FREE(buffer_p);

        if ((val_CheckFunctionResult(Status) != VAL_SUCCESS) &&
            fActivate && val_IsAccessSecure() && valtest_IsCOIDAvailable())
        {
            Status = valtest_DefaultTrngConfig();
        }
    }
    else
    {
        // Assume TRNG is not active
    }

    return (val_CheckFunctionResult(Status) == VAL_SUCCESS);
}


/*----------------------------------------------------------------------------
 * valtest_IsCOIDAvailable
 *
 * This function checks if the Crypto Officer ID (COID) is available.
 */
bool
valtest_IsCOIDAvailable(void)
{
    ValStatus_t FuncRes;
    uint8_t CryptoOfficer = 0;

    FuncRes = val_SystemGetState(NULL, NULL, NULL, NULL,
                                 &CryptoOfficer,
                                 NULL, NULL, NULL);
    if((val_CheckFunctionResult(FuncRes) == VAL_SUCCESS) && CryptoOfficer)
    {
        // COID available
        return true;
    }

    // COID not available
    return false;
}


/*----------------------------------------------------------------------------
 * asn1get
 *
 * Simple ASN.1 decoder. Reads the next item (Tag-Length-Value triplet) from
 * 'octets_p'. The actual Tag must match 'tag'. Length must be in 1..0xFFFF.
 * Returns a pointer to the item's Value.
 * Integer values may start with 0x00 to avoid being interpreted as a negative
 * value, but that interpretation is up to the caller.
 */
#if (TEST_VAL_NOT_USED)
uint8_t *
asn1get(
        const uint8_t * octets_p,
        size_t * itemlen_p,
        uint8_t tag)
{
    size_t len = octets_p[1];

    if(tag != octets_p[0])
    {
        LOG_CRIT("%s: tag mismatch (actual %d != %d)\n",
                 __func__, octets_p[0], tag);
        return NULL;
    }
    if(len == 0 || len == 0x80 || len > 0x82)
    {
        LOG_CRIT("%s: bad len[size] (%u)\n",
                 __func__, (unsigned int)len);
        return NULL;
    }

    if (len < 0x80)
    {
        *itemlen_p = len;
        return (uint8_t *)octets_p + 2;
    }

    if (len == 0x81)
    {
        *itemlen_p = octets_p[2];
        return (uint8_t *)octets_p + 3;
    }

    *itemlen_p = (octets_p[2] << 8) + octets_p[3];
    return (uint8_t *)octets_p + 4;
}
#endif


/*----------------------------------------------------------------------------
 * asn1put
 *
 * Simple ASN.1 encoder. Stores the next item (Tag-Length-Value triplet) at
 * 'octets_p'.  Tag must be 0x30 (Sequence) or 0x02 (Integer). Length must be
 * in 0..0xFFFF. Uses 'memmove' to copy the item, unless item_p is NULL, e.g
 * for a Sequence.
 * Returns a pointer to the location right after the stored item ('item_p != NULL)
 * or to the start of the Value ('item_p' == NULL).
 */
#if (TEST_VAL_NOT_USED)
uint8_t *
asn1put(
        uint8_t * octets_p,
        uint8_t * item_p,
        size_t itemlen,
        uint8_t tag)
{
    uint8_t * u8_p = octets_p + 2;

    if(tag != 0x30 && tag != 0x02)
    {
        LOG_CRIT("%s: bad tag (%d)\n",
                 __func__, tag);
        return NULL;
    }
    if(itemlen > 0xFFFF)
    {
        LOG_CRIT("%s: bad length (%u)\n",
                 __func__, (unsigned int)itemlen);
        return NULL;
    }

    octets_p[0] = tag;
    if (itemlen < 0x80)
    {
        octets_p[1] = (uint8_t)itemlen;
    }
    else if (itemlen < 0x100)
    {
        octets_p[1] = 0x81;
        octets_p[2] = (uint8_t)itemlen;
        u8_p += 1;
    }
    else
    {
        octets_p[1] = 0x82;
        octets_p[2] = (uint8_t)(itemlen >> 8);
        octets_p[3] = (uint8_t)(itemlen & 0xFF);
        u8_p += 2;
    }

    if (item_p != NULL)
    {
        memmove(u8_p, item_p, itemlen);
        return u8_p + itemlen;
    }

    return u8_p;
}
#endif

/* end of file valtest_internal.c */
