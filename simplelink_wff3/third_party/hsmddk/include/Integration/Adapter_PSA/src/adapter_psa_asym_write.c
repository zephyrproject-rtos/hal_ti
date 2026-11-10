/* adapter_psa_asym_write.c
 *
 * This file implements the Asymmetric key data write, which is based on ASN1
 * DER notation.
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

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>                 // the API to implement
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asym_write.h>     // the API to implement
#include <third_party/hsmddk/include/Integration/Asn1Der/incl/asn1der.h>                    // ASN1 / DER defines and functions
#include <third_party/hsmddk/include/Integration/Asn1Der/incl/oid.h>                        // Object Identifiers
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>   // EIP130DOMAIN_ECC_FAMILY_*

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * local_WriteConvertError
 */
static psa_status_t
local_WriteConvertError(int32_t ErrorCode)
{
    psa_status_t funcres;

    switch (ErrorCode)
    {
    case ASN1DER_SUCCESS:
        funcres = PSA_SUCCESS;
        break;
    case ASN1DER_ERROR_OUT_OF_DATA:
    case ASN1DER_ERROR_UNEXPECTED_TAG:
    case ASN1DER_ERROR_INVALID_LENGTH:
    case ASN1DER_ERROR_LENGTH_MISMATCH:
    case ASN1DER_ERROR_INVALID_DATA:
        funcres = PSA_ERROR_DATA_CORRUPT;
        break;
    case ASN1DER_ERROR_ALLOC_FAILED:
        funcres = PSA_ERROR_INSUFFICIENT_MEMORY;
        break;
    case ASN1DER_ERROR_BUFFER_TOO_SMALL:
        funcres = PSA_ERROR_BUFFER_TOO_SMALL;
        break;
    default:
        funcres = ErrorCode;
        break;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymWrite_EC_PubKey
 *
 * Write a DER encoded EC public key according RFC 5480.
 *
 * PublicKeyInfo ::= SEQUENCE  {
 *     algorithm ::= SEQUENCE  {
 *         algorithm   OBJECT IDENTIFIER,
 *         parameters  ANY DEFINED BY algorithm OPTIONAL
 *     }
 *     PublicKey  BIT STRING
 * }
 */
psa_status_t
PSAInt_AsymWrite_EC_PubKey(Asn1Der_BigNumber * const pPubKey,
                           uint8_t CurveFamily,
                           size_t CurveBits,
                           uint8_t fECDH,
                           size_t DataLen,
                           uint8_t * pData,
                           uint8_t ** ppActualBegin)
{
    uint8_t * insert;
    const uint8_t * start;
    const uint8_t * end;
    const uint8_t * offset;
    size_t bits;
    int32_t length;
    int32_t rc = ASN1DER_SUCCESS;

    if ((NULL == pPubKey) ||
        (NULL == pData) || (0U == DataLen) || (NULL == ppActualBegin))
    {
        rc = ASN1DER_ERROR_INVALID_DATA;
    }
    else
    {
        insert = &pData[DataLen];
        start = pData;
        end = insert;
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write public key */
        bits = 8U * ((CurveBits + 7U) / 8U);
        insert -= pPubKey->Length;
        switch (CurveFamily)
        {
        case EIP130DOMAIN_ECC_FAMILY_NIST_P:
        case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
            bits *= 2U;
            if (pPubKey->Length !=  (bits / 8U))
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
            else
            {
                (void)memcpy(insert, pPubKey->pData, pPubKey->Length);
                insert--;
                *insert = 0x04U;
            }
            break;
        case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
        case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
            if (pPubKey->Length != (bits / 8U))
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
            else
            {
                (void)memcpy(insert, pPubKey->pData, pPubKey->Length);
            }
            break;
        default:
            rc = ASN1DER_ERROR_INVALID_DATA;
            break;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        bits = (size_t)((end - insert) * 8);
        length = Asn1Der_WriteBitStringHeaderOnly(&insert, start, bits);
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write parameters (curve) information */
        offset = insert;
        if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_NIST_P)
        {
            if (224U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_SECP224R1,
                                               (sizeof(OID_EC_GRP_SECP224R1) - 1U));
            }
            else if (256U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_SECP256R1,
                                               (sizeof(OID_EC_GRP_SECP256R1) - 1U));
            }
            else if (384U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_SECP384R1,
                                               (sizeof(OID_EC_GRP_SECP384R1) - 1U));
            }
            else if (521U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_SECP521R1,
                                               (sizeof(OID_EC_GRP_SECP521R1) - 1U));
            }
            else
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
        }
        else if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1)
        {
            if (224U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_BP224R1,
                                               (sizeof(OID_EC_GRP_BP224R1) - 1U));
            }
            else if (256U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_BP256R1,
                                               (sizeof(OID_EC_GRP_BP256R1) - 1U));
            }
            else if (384U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_BP384R1,
                                               (sizeof(OID_EC_GRP_BP384R1) - 1U));
            }
            else if (512U == CurveBits)
            {
                length = Asn1Der_WriteObjectId(&insert, start,
                                               OID_EC_GRP_BP512R1,
                                               (sizeof(OID_EC_GRP_BP512R1) - 1U));
            }
            else
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
        }
        else
        {
            /* Nothing to do for MONTGOMERY and TWISTED_EDWARDS */
        }
        if ((ASN1DER_SUCCESS == rc) && (0 > length))
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        const char * pObjectId;
        size_t ObjectIdLength;

        /* Write algorithm information */
        if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_MONTGOMERY)
        {
            pObjectId = OID_ID_X25519;
            ObjectIdLength = sizeof(OID_ID_X25519) - 1U;
        }
        else if (CurveFamily == EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS)
        {
            pObjectId = OID_ID_ED25519;
            ObjectIdLength = sizeof(OID_ID_ED25519) - 1U;
        }
        else if (0U == fECDH)
        {
            pObjectId = OID_EC_ALG_UNRESTRICTED;
            ObjectIdLength = sizeof(OID_EC_ALG_UNRESTRICTED) - 1U;
        }
        else
        {
            pObjectId = OID_EC_ALG_ECDH;
            ObjectIdLength = sizeof(OID_EC_ALG_ECDH) - 1U;
        }
        length = Asn1Der_WriteObjectId(&insert, start, pObjectId, ObjectIdLength);
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write Sequence length for algorithm and parameter */
        length = Asn1Der_WriteLength(&insert, start, (size_t)(offset - insert));
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write Sequence tag for algorithm and parameter */
        length = Asn1Der_WriteTag(&insert, start,
                                  (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write overall Sequence length */
        length = Asn1Der_WriteLength(&insert, start, (size_t)(end - insert));
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Write overall Sequence tag */
        length = Asn1Der_WriteTag(&insert, start,
                                  (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
        if (0 > length)
        {
            rc = length;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if (ASN1DER_SUCCESS == rc)
    {
        *ppActualBegin = insert;
    }
    else
    {
        if (NULL != ppActualBegin)
        {
            *ppActualBegin = NULL;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return local_WriteConvertError(rc);
}


/* end of file adapter_psa_asym_write.c */
