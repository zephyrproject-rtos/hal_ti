/* adapter_psa_asym_parse.c
 *
 * This file implements the Asymmetric key data parsing, which is based on ASN1
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
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asym_parse.h>     // the API to implement
#include <third_party/hsmddk/include/Integration/Asn1Der/incl/asn1der.h>                    // ASN1 / DER defines and functions
#include <third_party/hsmddk/include/Integration/Asn1Der/incl/oid.h>                        // Object Identifiers
#include <third_party/hsmddk/include/Kit/EIP130/DomainHelper/incl/eip130_domain_ecc_curves.h>   // EIP130DOMAIN_ECC_FAMILY_*


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Local defines for asymmetric algorithms */
#define PSA_ASYM_PARSE_ALG_UNKNOWN      (0)
#define PSA_ASYM_PARSE_ALG_EC_GENERIC   (1)
#define PSA_ASYM_PARSE_ALG_EC_DH        (2)
#define PSA_ASYM_PARSE_ALG_EC_X25519    (3)
#define PSA_ASYM_PARSE_ALG_EC_ED25519   (4)
#define PSA_ASYM_PARSE_ALG_RSA_PKCS1    (5)
#define PSA_ASYM_PARSE_ALG_RSA_PSS      (6)


/*----------------------------------------------------------------------------
 * local_ParseConvertError
 */
static psa_status_t
local_ParseConvertError(int32_t ErrorCode)
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
 * local_GetAlgorithm
 */
static int32_t
local_GetAlgorithm(const Asn1Der_Buffer * pAlgorithm)
{
    int32_t rc;

    if (0 == memcmp((const void *)(OID_EC_ALG_UNRESTRICTED),
                    (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_EC_GENERIC;
    }
    else if (0 == memcmp((const void *)(OID_EC_ALG_ECDH),
                         (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_EC_DH;
    }
    else if (0 == memcmp((const void *)(OID_PKCS1_RSA),
                         (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_RSA_PKCS1;
    }
    else if (0 == memcmp((const void *)(OID_RSASSA_PSS),
                         (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_RSA_PSS;
    }
    else if (0 == memcmp((const void *)(OID_ID_X25519),
                         (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_EC_X25519;
    }
    else if (0 == memcmp((const void *)(OID_ID_ED25519),
                         (const void *)pAlgorithm->pData, pAlgorithm->Length))
    {
        rc = PSA_ASYM_PARSE_ALG_EC_ED25519;
    }
    else
    {
        rc = PSA_ASYM_PARSE_ALG_UNKNOWN;
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * local_GetCurveInfo
 */
static int32_t
local_GetCurveInfo(const Asn1Der_Buffer * pParams,
                   uint8_t * pCurveFamily,
                   size_t * pCurveBits)
{
    int32_t rc = ASN1DER_SUCCESS;

    if (0 == memcmp((const void *)(OID_EC_GRP_SECP224R1),
                    (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        *pCurveBits = 224U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_SECP256R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        *pCurveBits = 256U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_SECP384R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        *pCurveBits = 384U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_SECP521R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NIST_P;
        *pCurveBits = 521U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_BP224R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        *pCurveBits = 224U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_BP256R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        *pCurveBits = 256U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_BP384R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        *pCurveBits = 384U;
    }
    else if (0 == memcmp((const void *)(OID_EC_GRP_BP512R1),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1;
        *pCurveBits = 512U;
    }
    else if (0 == memcmp((const void *)(OID_ID_X25519),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
        *pCurveBits = 255U;
    }
    else if (0 == memcmp((const void *)(OID_ID_ED25519),
                         (const void *)pParams->pData, pParams->Length))
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS;
        *pCurveBits = 255U;
    }
    else
    {
        *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_NONE;
        rc = ASN1DER_ERROR_INVALID_DATA;
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * local_GetECCurve
 *
 * Parses the ECparameters and returns its family and size
 *
 * ECParameters ::= CHOICE {
 *   namedCurve         OBJECT IDENTIFIER
 *   specifiedCurve     SpecifiedECDomain -- = SEQUENCE { ... }
 *   -- implicitCurve   NULL
 * }
 */
static int32_t
local_GetECCurve(uint8_t ** ppBufferCurrent,
                 const uint8_t * pBufferEnd,
                 uint8_t * pCurveFamily,
                 size_t * pCurveBits)
{
    Asn1Der_Buffer params = { 0 };
    int32_t rc = ASN1DER_SUCCESS;

    if ((pBufferEnd - *ppBufferCurrent) < 1)
    {
        rc = ASN1DER_ERROR_OUT_OF_DATA;
    }
    else
    {
        /* Tag may be either OID or SEQUENCE */
        params.Tag = **ppBufferCurrent;
        if (ASN1DER_TAG_OID != params.Tag)
        {
            rc = ASN1DER_ERROR_UNEXPECTED_TAG;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (ASN1DER_SUCCESS == rc)
        {
            rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd,
                                &params.Length, params.Tag);
        }
        else
        {
            /* MISRA - Intentially empty */
        }
        if (ASN1DER_SUCCESS == rc)
        {
            params.pData = *ppBufferCurrent;
            *ppBufferCurrent = &(*ppBufferCurrent)[params.Length];

            if (*ppBufferCurrent != pBufferEnd)
            {
                rc = ASN1DER_ERROR_LENGTH_MISMATCH;
            }
            else
            {
                rc = local_GetCurveInfo(&params, pCurveFamily, pCurveBits);
            }
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_EC_SEC1
 *
 * Parse a SEC1 encoded EC private key according RFC 5915, or SEC1 Appendix C.4.
 *
 * ECPrivateKey ::= SEQUENCE {
 *      version        INTEGER { ecPrivkeyVer1(1) } (ecPrivkeyVer1),
 *      privateKey     OCTET STRING,
 *      parameters [0] ECParameters {{ NamedCurve }} OPTIONAL,
 *      publicKey  [1] BIT STRING OPTIONAL
 *    }
 */
psa_status_t
PSAInt_AsymParse_EC_SEC1(const uint8_t * pData,
                         size_t DataLen,
                         Asn1Der_BigNumber * pPrvKey,
                         uint8_t * pCurveFamily,
                         size_t * pCurveBits,
                         Asn1Der_BigNumber * pPubKey)
{
    uint8_t * begin = psaInt_discard_const(pData);
    uint8_t * end = &begin[DataLen];
    const uint8_t * end2;
    size_t len;
    int32_t rc;

    /* Initialize optional output */
    *pCurveFamily = 0U;
    *pCurveBits = 0U;
    if (NULL != pPubKey)
    {
        pPubKey->Sign = 0U;
        pPubKey->pData = NULL;
        pPubKey->Length = 0U;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        int32_t version;

        end = &begin[len];

        rc = Asn1Der_GetInteger(&begin, end, &version);
        if ((ASN1DER_SUCCESS == rc) && (1 != version))
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
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
        rc = Asn1Der_GetTag(&begin, end, &len, ASN1DER_TAG_OCTET_STRING);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read private key */
        pPrvKey->Sign = 0U;
        pPrvKey->pData = begin;
        pPrvKey->Length = len;
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        begin = &begin[len];
        if (begin != end)
        {
            /* Curve present? */
            rc = Asn1Der_GetTag(&begin, end, &len,
                                (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_CONTEXT_SPECIFIC));
            if (ASN1DER_SUCCESS == rc)
            {
                end2 = &begin[len];

                /* Validate and get curve information */
                rc = local_GetECCurve(&begin, end2,
                                      pCurveFamily, pCurveBits);
            }
            else
            {
                if (ASN1DER_ERROR_UNEXPECTED_TAG == rc)
                {
                    /* Optional, so assume not available */
                    begin = end;
                    rc = ASN1DER_SUCCESS;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
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
        if ((NULL != pPubKey) && (begin != end))
        {
            /* Public key present? */
            rc = Asn1Der_GetTag(&begin, end, &len,
                                (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_CONTEXT_SPECIFIC|
                                 ASN1DER_TAG_BOOLEAN));
            if (ASN1DER_SUCCESS == rc)
            {
                end2 = &begin[len];

                rc = Asn1Der_GetBitStringNull(&begin, end2, &len);
                if (ASN1DER_SUCCESS == rc)
                {
                    if ((&begin[len] != end2) || (1U > len))
                    {
                        rc = ASN1DER_ERROR_LENGTH_MISMATCH;
                    }
                    else
                    {
                        /* Read public key */
                        switch (*pCurveFamily)
                        {
                        case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                        case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                            if (*begin == 0x04U)
                            {
                                /* Uncompressed form */
                                pPubKey->Sign = 0U;
                                pPubKey->pData = &begin[1];
                                pPubKey->Length = (len - 1U);
                            }
                            else
                            {
                                /* Not supported form:
                                 * Compressed (0x2 or 0x03) or unknown */
                                rc = ASN1DER_ERROR_INVALID_DATA;
                                break;
                            }
                            break;
                        default:
                            rc = ASN1DER_ERROR_INVALID_DATA;
                            break;
                        }
                    }
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
            else
            {
                if (ASN1DER_ERROR_UNEXPECTED_TAG == rc)
                {
                    /* Optional, so assume not available */
                    begin = end;
                    rc = ASN1DER_SUCCESS;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
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

    return local_ParseConvertError(rc);
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_EC_EdX
 *
 * Parse Ed25519 and X25519 encoded private key according RFC 8410 and
 * RFC 5958.
 *
 * OneAsymmetricKey ::= SEQUENCE {
 *       version Version,
 *       privateKeyAlgorithm PrivateKeyAlgorithmIdentifier,
 *       privateKey PrivateKey,
 *       attributes [0] IMPLICIT Attributes OPTIONAL,
 *       ...,
 *       [[2: publicKey [1] IMPLICIT PublicKey OPTIONAL ]],
 *       ...
 *    }
 */
psa_status_t
PSAInt_AsymParse_EC_EdX(const uint8_t * pData,
                        size_t DataLen,
                        Asn1Der_BigNumber * pPrvKey,
                        uint8_t * pCurveFamily,
                        size_t * pCurveBits,
                        Asn1Der_BigNumber * pPubKey)
{
    uint8_t * begin = psaInt_discard_const(pData);
    const uint8_t * end = &begin[DataLen];
    const uint8_t * end2;
    size_t len;
    int32_t rc;
    bool fPublicKey = false;

    /* Initialize optional output */
    *pCurveFamily = 0U;
    *pCurveBits = 0U;
    if (NULL != pPubKey)
    {
        pPubKey->Sign = 0U;
        pPubKey->pData = NULL;
        pPubKey->Length = 0U;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        int32_t version;

        end = &begin[len];

        rc = Asn1Der_GetInteger(&begin, end, &version);
        if (ASN1DER_SUCCESS == rc)
        {
            if (0 == version)
            {
                /* Only private key is listed */
            }
            else if (1 == version)
            {
                /* Private and public key are listed */
                fPublicKey = true;
            }
            else
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
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
        if (begin != end)
        {
            /* Read curve parameters */
            rc = Asn1Der_GetTag(&begin, end, &len,
                                (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
            if (ASN1DER_SUCCESS == rc)
            {
                end2 = &begin[len];

                /* Validate and get curve information */
                rc = local_GetECCurve(&begin, end2,
                                      pCurveFamily, pCurveBits);
            }
            else
            {
                /* MISRA - Intentially empty */
            }
        }
        else
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        rc = Asn1Der_GetTag(&begin, end, &len, ASN1DER_TAG_OCTET_STRING);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        end2 = &begin[len];

        if (ASN1DER_SUCCESS == rc)
        {
            rc = Asn1Der_GetTag(&begin, end2, &len, ASN1DER_TAG_OCTET_STRING);
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
        /* Read private key */
        pPrvKey->Sign = 0U;
        pPrvKey->pData = begin;
        pPrvKey->Length = len;

        if ((true == fPublicKey) && (NULL != pPubKey) && (begin != end))
        {
            /* Public key present */
            rc = Asn1Der_GetTag(&begin, end, &len,
                                (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_CONTEXT_SPECIFIC|
                                 ASN1DER_TAG_BOOLEAN));
            if (ASN1DER_SUCCESS == rc)
            {
                end2 = &begin[len];

                rc = Asn1Der_GetBitStringNull(&begin, end2, &len);
                if (ASN1DER_SUCCESS == rc)
                {
                    if ((&begin[len] != end2) || (1U > len))
                    {
                        rc = ASN1DER_ERROR_LENGTH_MISMATCH;
                    }
                    else
                    {
                        /* Read public key */
                        switch (*pCurveFamily)
                        {
                        case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
                        case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
                            pPubKey->Sign = 0U;
                            pPubKey->pData = begin;
                            pPubKey->Length = len;
                            break;
                        default:
                            rc = ASN1DER_ERROR_INVALID_DATA;
                            break;
                        }
                    }
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

    return local_ParseConvertError(rc);
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_EC_PubKey
 */
/* Parse a DER encoded EC public key according RFC 5480.
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
PSAInt_AsymParse_EC_PubKey(const uint8_t * pData,
                           size_t DataLen,
                           uint8_t * pCurveFamily,
                           size_t * pCurveBits,
                           Asn1Der_BigNumber * pPubKey,
                           uint8_t * pfECDH)
{
    Asn1Der_Buffer algorithm = { 0 };
    Asn1Der_Buffer params = { 0 };
    uint8_t * begin = psaInt_discard_const(pData);
    const uint8_t * end = &begin[DataLen];
    size_t len;
    int32_t rc;

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        end = &begin[len];

        rc = Asn1Der_GetAlgorithm(&begin, end, &algorithm, &params);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Process Algorithm & Validate and get curve information */
        rc = local_GetAlgorithm(&algorithm);
        switch (rc)
        {
        case PSA_ASYM_PARSE_ALG_EC_GENERIC:
        case PSA_ASYM_PARSE_ALG_EC_DH:
            if (PSA_ASYM_PARSE_ALG_EC_DH == rc)
            {
                *pfECDH = 255U;
            }
            else
            {
                *pfECDH = 0U;
            }
            rc = local_GetCurveInfo(&params, pCurveFamily, pCurveBits);
            break;
        case PSA_ASYM_PARSE_ALG_EC_X25519:
            *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_MONTGOMERY;
            *pCurveBits = 255U;
            *pfECDH = 255U;
            rc = ASN1DER_SUCCESS;
            break;
        case PSA_ASYM_PARSE_ALG_EC_ED25519:
            *pCurveFamily = EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS;
            *pCurveBits = 255U;
            *pfECDH = 0U;
            rc = ASN1DER_SUCCESS;
            break;
        default:
            rc = ASN1DER_ERROR_UNEXPECTED_TAG;
            break;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        rc = Asn1Der_GetBitStringNull(&begin, end, &len);
        if (ASN1DER_SUCCESS == rc)
        {
            if ((&begin[len] != end) || (1U > len))
            {
                rc = ASN1DER_ERROR_LENGTH_MISMATCH;
            }
            else
            {
                /* Read public key */
                switch (*pCurveFamily)
                {
                case EIP130DOMAIN_ECC_FAMILY_NIST_P:
                case EIP130DOMAIN_ECC_FAMILY_BRAINPOOL_R1:
                    if (*begin == 0x04U)
                    {
                        /* Uncompressed form */
                        pPubKey->Sign = 0U;
                        pPubKey->pData = &begin[1];
                        pPubKey->Length = (len - 1U);
                    }
                    else
                    {
                        /* Not supported form:
                         * Compressed (0x2 or 0x03) or unknown */
                        rc = ASN1DER_ERROR_INVALID_DATA;
                        break;
                    }
                    break;
                case EIP130DOMAIN_ECC_FAMILY_MONTGOMERY:
                case EIP130DOMAIN_ECC_FAMILY_TWISTED_EDWARDS:
                    pPubKey->Sign = 0U;
                    pPubKey->pData = begin;
                    pPubKey->Length = len;
                    break;
                default:
                    rc = ASN1DER_ERROR_INVALID_DATA;
                    break;
                }
            }
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

    return local_ParseConvertError(rc);
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_RSA_PKCS1
 *
 * Parse a RSA-PKCS#1 private key.
 *
 *  RSAPrivateKey ::= SEQUENCE {
 *      version           INTEGER,  Version = 0
 *      modulus           INTEGER,  -- n
 *      publicExponent    INTEGER,  -- e
 *      privateExponent   INTEGER,  -- d
 *      prime1            INTEGER,  -- p
 *      prime2            INTEGER,  -- q
 *      exponent1         INTEGER,  -- d mod (p-1)
 *      exponent2         INTEGER,  -- d mod (q-1)
 *      coefficient       INTEGER,  -- (inverse of q) mod p
 *      otherPrimeInfos   OtherPrimeInfos OPTIONAL
 *  }
 */
psa_status_t
PSAInt_AsymParse_RSA_PKCS1(const uint8_t * pData,
                           size_t DataLen,
                           Asn1Der_BigNumber * pModulus,
                           Asn1Der_BigNumber * pPrivateExponent,
                           Asn1Der_BigNumber * pPublicExponent)
{
    uint8_t * begin = psaInt_discard_const(pData);
    const uint8_t * end = &begin[DataLen];
    size_t len;
    int32_t rc;

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        int32_t version;

        end = &begin[len];

        rc = Asn1Der_GetInteger(&begin, end, &version);
        if ((ASN1DER_SUCCESS == rc) && (0 != version))
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
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
        /* Read modulus */
        rc = Asn1Der_GetBigNumberInteger(&begin, end, pModulus);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read public exponent */
        rc = Asn1Der_GetBigNumberInteger(&begin, end, pPublicExponent);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read private exponent */
        rc = Asn1Der_GetBigNumberInteger(&begin, end, pPrivateExponent);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    /* The remaining part is ignored for now */

    return local_ParseConvertError(rc);
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_RSA_PSS
 *
 * Parse a RSASSA-PSS private key according RFC 5915, or SEC1 Appendix C.4.
 *
 * RSAPSSPrivateKey ::= SEQUENCE {
 *     version  INTEGER,  version = 0
 *     RSASSA-AlgorithmIdentifier SEQUENCE ::= {
 *         algorithm   id-RSASSA-PSS,
 *         parameters  RSASSA-PSS-params : { Optional (ignored in our case)
 *             hashAlgorithm       sha1,
 *             maskGenAlgorithm    mgf1SHA1,
 *             saltLength          20,
 *             trailerField        trailerFieldBC
 *         }
 *     }
 *     OCTET STRING {
 *         RSAPrivateKey ::= SEQUENCE {
 *             version           INTEGER,  version = 0
 *             modulus           INTEGER,  -- n
 *             publicExponent    INTEGER,  -- e
 *             privateExponent   INTEGER,  -- d
 *             prime1            INTEGER,  -- p
 *             prime2            INTEGER,  -- q
 *             exponent1         INTEGER,  -- d mod (p-1)
 *             exponent2         INTEGER,  -- d mod (q-1)
 *             coefficient       INTEGER,  -- (inverse of q) mod p
 *             otherPrimeInfos   OtherPrimeInfos OPTIONAL
 *         }
 *     }
 * }
 */
psa_status_t
PSAInt_AsymParse_RSA_PSS(const uint8_t * pData,
                         size_t DataLen,
                         Asn1Der_BigNumber * pModulus,
                         Asn1Der_BigNumber * pPrivateExponent,
                         Asn1Der_BigNumber * pPublicExponent)
{
    Asn1Der_Buffer algorithm = { 0 };
    Asn1Der_Buffer params = { 0 };
    uint8_t * begin = psaInt_discard_const(pData);
    const uint8_t * end = &begin[DataLen];
    size_t len;
    int32_t rc;

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        int32_t version;

        end = &begin[len];

        rc = Asn1Der_GetInteger(&begin, end, &version);
        if ((ASN1DER_SUCCESS == rc) && (0 != version))
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
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
        rc = Asn1Der_GetAlgorithm(&begin, end, &algorithm, &params);
        if (ASN1DER_SUCCESS == rc)
        {
            rc = local_GetAlgorithm(&algorithm);
            if (PSA_ASYM_PARSE_ALG_RSA_PSS == rc)
            {
                rc = ASN1DER_SUCCESS;
            }
            else
            {
                rc = ASN1DER_ERROR_INVALID_DATA;
            }
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
        rc = Asn1Der_GetTag(&begin, end, &len, ASN1DER_TAG_OCTET_STRING);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read private key components */
        rc = PSAInt_AsymParse_RSA_PKCS1(begin, len, pModulus,
                                        pPrivateExponent, pPublicExponent);
    }
    else
    {
        rc = local_ParseConvertError(rc);
    }

    return rc;
}


/*----------------------------------------------------------------------------
 * PSAInt_AsymParse_RSA_PubKey
 *
 * Parse a DER encoded RSA public key.
 *
 * PublicKeyInfo ::= SEQUENCE  {
 *     algorithm ::= SEQUENCE  {
 *         algorithm   OBJECT IDENTIFIER,
 *         parameters  NULL
 *     }
 *     PublicKey  BIT STRING {
 *         RSAPublicKey ::= SEQUENCE {
 *             modulus         INTEGER,  -- n
 *             publicExponent  INTEGER   -- e
 *         }
 *     }
 * }
 */
psa_status_t
PSAInt_AsymParse_RSA_PubKey(const uint8_t * pData,
                            size_t DataLen,
                            Asn1Der_BigNumber * pModulus,
                            Asn1Der_BigNumber * pExponent,
                            uint8_t * pfPSS)
{
    Asn1Der_Buffer Algorithm = { 0 };
    Asn1Der_BitString KeyInfo = { 0 };
    uint8_t * begin = psaInt_discard_const(pData);
    const uint8_t * end = &begin[DataLen];
    size_t len;
    int32_t rc;

    /* Parse provide data */
    rc = Asn1Der_GetTag(&begin, end, &len,
                        (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
    if (ASN1DER_SUCCESS == rc)
    {
        end = &begin[len];

        rc = Asn1Der_GetAlgorithmNull(&begin, end, &Algorithm);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        rc = local_GetAlgorithm(&Algorithm);
        if ((PSA_ASYM_PARSE_ALG_RSA_PKCS1 == rc) ||
            (PSA_ASYM_PARSE_ALG_RSA_PSS == rc))
        {
            /* Looks valid RSA key */
            if (PSA_ASYM_PARSE_ALG_RSA_PSS == rc)
            {
                *pfPSS = 255U;
            }
            else
            {
                *pfPSS = 0U;
            }
            rc = ASN1DER_SUCCESS;
        }
        else
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if (ASN1DER_SUCCESS == rc)
    {
        rc = Asn1Der_GetBitString(&begin, end, &KeyInfo);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        if ((0U == KeyInfo.UnusedBits) &&
            (NULL != KeyInfo.pData))
        {
            begin = KeyInfo.pData;
            end   = &begin[KeyInfo.Length];

            rc = Asn1Der_GetTag(&begin, end, &len,
                                (ASN1DER_TAG_CONSTRUCTED|ASN1DER_TAG_SEQUENCE));
        }
        else
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read Modulus */
        rc = Asn1Der_GetBigNumberInteger(&begin, end, pModulus);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
    if (ASN1DER_SUCCESS == rc)
    {
        /* Read Exponent */
        rc = Asn1Der_GetBigNumberInteger(&begin, end, pExponent);
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return local_ParseConvertError(rc);
}


/* end of file adapter_psa_asym_parse.c */
