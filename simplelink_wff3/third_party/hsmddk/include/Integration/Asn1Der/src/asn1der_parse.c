/**
 * @file asn1der_parse.c
 *
 * @brief ASN.1 DER decoding routines
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

#include <third_party/hsmddk/include/Config/cs_asn1der.h>
#include <third_party/hsmddk/include/Integration/Asn1Der/incl/asn1der.h>
#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_alloc.h>


int32_t
Asn1Der_GetLength(uint8_t * *ppBufferCurrent,
                  const uint8_t * pBufferEnd,
                  size_t * pLength)
{
    int32_t rc = 0;

    if ((pBufferEnd - *ppBufferCurrent) < 1)
    {
        rc = ASN1DER_ERROR_OUT_OF_DATA;
    }
    else if ((**ppBufferCurrent & 0x80U) == 0U)
    {
        *pLength = **ppBufferCurrent;
        (*ppBufferCurrent)++;
    }
    else
    {
        switch (**ppBufferCurrent & 0x7FU)
        {
        case 1:
            if ((pBufferEnd - *ppBufferCurrent) < 2)
            {
                rc = ASN1DER_ERROR_OUT_OF_DATA;
            }
            else
            {
                *pLength = (size_t)(*ppBufferCurrent)[1];
                *ppBufferCurrent = &(*ppBufferCurrent)[2];
            }
            break;

        case 2:
            if ((pBufferEnd - *ppBufferCurrent) < 3)
            {
                rc = ASN1DER_ERROR_OUT_OF_DATA;
            }
            else
            {
                *pLength = ((size_t)(*ppBufferCurrent)[1] << 8) |
                           ((size_t)(*ppBufferCurrent)[2] << 0);
                *ppBufferCurrent = &(*ppBufferCurrent)[3];
            }
            break;

        case 3:
            if ((pBufferEnd - *ppBufferCurrent) < 4)
            {
                rc = ASN1DER_ERROR_OUT_OF_DATA;
            }
            else
            {
                *pLength = ((size_t)(*ppBufferCurrent)[1] << 16) |
                           ((size_t)(*ppBufferCurrent)[2] <<  8) |
                           ((size_t)(*ppBufferCurrent)[3] <<  0);
                *ppBufferCurrent = &(*ppBufferCurrent)[4];
            }
            break;

        case 4:
            if ((pBufferEnd - *ppBufferCurrent) < 5)
            {
                rc = ASN1DER_ERROR_OUT_OF_DATA;
            }
            else
            {
                *pLength = ((size_t)(*ppBufferCurrent)[1] << 24) |
                           ((size_t)(*ppBufferCurrent)[2] << 16) |
                           ((size_t)(*ppBufferCurrent)[3] <<  8) |
                           ((size_t)(*ppBufferCurrent)[4] <<  0);
                *ppBufferCurrent = &(*ppBufferCurrent)[5];
            }
            break;

        default:
            rc = ASN1DER_ERROR_INVALID_LENGTH;
            break;
        }
    }

    if ((rc == 0) &&
        ((int32_t)*pLength > (int32_t)(pBufferEnd - *ppBufferCurrent)))
    {
        rc = ASN1DER_ERROR_OUT_OF_DATA;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetTag(uint8_t ** ppBufferCurrent,
               const uint8_t * pBufferEnd,
               size_t * pLength,
               uint8_t Tag)
{
    int32_t rc;

    if ((pBufferEnd - *ppBufferCurrent) < 1)
    {
        rc = ASN1DER_ERROR_OUT_OF_DATA;
    }
    else
    {
        if (**ppBufferCurrent != Tag)
        {
            rc = ASN1DER_ERROR_UNEXPECTED_TAG;
        }
        else
        {
            (*ppBufferCurrent)++;
            rc = Asn1Der_GetLength(ppBufferCurrent, pBufferEnd, pLength);
        }
    }

    return rc;
}


#ifndef ASN1DER_REMOVE_GETBOOLEAN
int32_t
Asn1Der_GetBoolean(uint8_t ** ppBufferCurrent,
                   const uint8_t * pBufferEnd,
                   uint8_t * pValue)
{
    size_t Length = 0;
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length, ASN1DER_TAG_BOOLEAN);
    if (rc >= 0)
    {
        if (Length != 1)
        {
            rc = ASN1DER_ERROR_INVALID_LENGTH;
        }
        else
        {
            if (**ppBufferCurrent != 0)
            {
                *pValue = 1;
            }
            else
            {
                *pValue = 0;
            }
            (*ppBufferCurrent)++;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}
#endif /* ASN1DER_REMOVE_GETBOOLEAN */


static int32_t
Asn1Der_GetTaggedInteger(uint8_t ** ppBufferCurrent,
                         const uint8_t * pBufferEnd,
                         uint8_t Tag,
                         int32_t * pValue)
{
    size_t Length = 0;
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length, Tag);
    if (rc >= 0)
    {
        if (Length == 0U)
        {
            /* len==0 is an error because 0 must be represented as 020100 for
             * INTEGER, or 0A0100 for ENUMERATED tags */
            rc = ASN1DER_ERROR_INVALID_LENGTH;
        }
        else if ((**ppBufferCurrent & 0x80U) != 0U)
        {
            /* Reject negative integers. */
            rc = ASN1DER_ERROR_INVALID_LENGTH;
        }
        else
        {
            /* Skip leading zeros. */
            while ((Length > 0U) && (**ppBufferCurrent == 0U))
            {
                (*ppBufferCurrent)++;
                Length--;
            }

            /* Reject integers that don't fit in a 32-bit integer.
             * Code assumes that the integer type has no padding bit. */
            if (Length > sizeof(int32_t))
            {
                rc = ASN1DER_ERROR_INVALID_LENGTH;
            }
            else if ((Length == sizeof(int32_t)) && ((**ppBufferCurrent & 0x80U) != 0U))
            {
                rc = ASN1DER_ERROR_INVALID_LENGTH;
            }
            else
            {
                uint32_t Value = 0;
                while (Length > 0U)
                {
                    Value = ((Value << 8U) | (uint32_t)**ppBufferCurrent);
                    (*ppBufferCurrent)++;
                    Length--;
                }
                *pValue = (int32_t)Value;
            }
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetInteger(uint8_t ** ppBufferCurrent,
                   const uint8_t * pBufferEnd,
                   int32_t * pValue)
{
    return Asn1Der_GetTaggedInteger(ppBufferCurrent, pBufferEnd, ASN1DER_TAG_INTEGER, pValue);
}


#ifndef ASN1DER_REMOVE_GETENUM
int32_t
Asn1Der_GetEnum(uint8_t ** ppBufferCurrent,
                const uint8_t * pBufferEnd,
                int32_t * pValue)
{
    return Asn1Der_GetTaggedInteger(ppBufferCurrent, pBufferEnd, ASN1DER_TAG_ENUMERATED, pValue);
}
#endif


int32_t
Asn1Der_GetBigNumberInteger(uint8_t ** ppBufferCurrent,
                            const uint8_t * pBufferEnd,
                            Asn1Der_BigNumber * pNumber)
{
    size_t Length = 0;
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length, ASN1DER_TAG_INTEGER);
    if (rc >= 0)
    {
        pNumber->Sign = 0U;
        if (**ppBufferCurrent == 0U)
        {
            if ((pBufferEnd - *ppBufferCurrent) < 1)
            {
                rc = ASN1DER_ERROR_OUT_OF_DATA;
            }
            else
            {
                (*ppBufferCurrent)++;
                if ((**ppBufferCurrent & 0x80U) != 0U)
                {
                    pNumber->Sign = 1;
                    Length--;
                }
                else
                {
                    /* No sign indication, correct offset */
                    (*ppBufferCurrent)--;
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

    if (rc >= 0)
    {
        if ((pBufferEnd - *ppBufferCurrent) < (int32_t)Length)
        {
            rc = ASN1DER_ERROR_OUT_OF_DATA;
        }
        else
        {
            pNumber->pData = *ppBufferCurrent;
            pNumber->Length = Length;
            *ppBufferCurrent = &(*ppBufferCurrent)[Length];
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetBitString(uint8_t ** ppBufferCurrent,
                     const uint8_t * pBufferEnd,
                     Asn1Der_BitString * pBitString)
{
    size_t Length = 0;
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length, ASN1DER_TAG_BIT_STRING);
    if (rc >= 0)
    {
        if (Length == 0U)
        {
            /* Bit string length must be at least 1 */
            rc = ASN1DER_ERROR_OUT_OF_DATA;
        }
        else
        {
            /* Get number of unused bits, ensure unused bits <= 7 */
            pBitString->UnusedBits = **ppBufferCurrent;
            if (pBitString->UnusedBits > 7U)
            {
                rc = ASN1DER_ERROR_INVALID_LENGTH;
            }
            else
            {
                (*ppBufferCurrent)++;
                Length--;

                /* Get actual bitstring */
                pBitString->pData = *ppBufferCurrent;
                pBitString->Length = Length;

                *ppBufferCurrent = &(*ppBufferCurrent)[Length];
                if (*ppBufferCurrent != pBufferEnd)
                {
                    rc = ASN1DER_ERROR_LENGTH_MISMATCH;
                }
                else
                {
                    /* MISRA - Intentially empty */
                }
            }
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetBitStringNull(uint8_t ** ppBufferCurrent,
                         const uint8_t * pBufferEnd,
                         size_t * pLength)
{
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, pLength, ASN1DER_TAG_BIT_STRING);
    if (rc >= 0)
    {
        if ((*pLength == 0U) || (**ppBufferCurrent != 0U))
        {
            rc = ASN1DER_ERROR_INVALID_DATA;
        }
        else
        {
            ++(*ppBufferCurrent);
            --(*pLength);
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetAlgorithm(uint8_t ** ppBufferCurrent,
                     const uint8_t * pBufferEnd,
                     Asn1Der_Buffer * pAlgorithm,
                     Asn1Der_Buffer * pParams)
{
    size_t Length = 0;
    int32_t rc;

    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length,
                        (ASN1DER_TAG_CONSTRUCTED | ASN1DER_TAG_SEQUENCE));
    if (rc >= 0)
    {
        if ((pBufferEnd - *ppBufferCurrent) < 1)
        {
            rc = ASN1DER_ERROR_OUT_OF_DATA;
        }
        else
        {
            const uint8_t *end = &(*ppBufferCurrent)[Length];

            pAlgorithm->Tag = **ppBufferCurrent;

            rc = Asn1Der_GetTag(ppBufferCurrent, end, &pAlgorithm->Length, ASN1DER_TAG_OID);
            if (rc >= 0)
            {
                pAlgorithm->pData = *ppBufferCurrent;
                *ppBufferCurrent = &(*ppBufferCurrent)[pAlgorithm->Length];
                if (*ppBufferCurrent == end)
                {
                    (void)memset(pParams, 0, sizeof(Asn1Der_Buffer));
                    rc = 0;
                }
                else
                {
                    pParams->Tag = **ppBufferCurrent;
                    (*ppBufferCurrent)++;

                    rc = Asn1Der_GetLength(ppBufferCurrent, end,  &pParams->Length);
                    if (rc >= 0)
                    {
                        pParams->pData = *ppBufferCurrent;
                        *ppBufferCurrent = &(*ppBufferCurrent)[pParams->Length];

                        if (*ppBufferCurrent != end)
                        {
                            rc = ASN1DER_ERROR_LENGTH_MISMATCH;
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

    return rc;
}


int32_t
Asn1Der_GetAlgorithmNull(uint8_t ** ppBufferCurrent,
                         const uint8_t * pBufferEnd,
                         Asn1Der_Buffer * pAlgorithm)
{
    Asn1Der_Buffer params;
    int32_t rc;

    (void)memset(&params, 0, sizeof(Asn1Der_Buffer));

    rc = Asn1Der_GetAlgorithm(ppBufferCurrent, pBufferEnd, pAlgorithm, &params);
    if (rc >= 0)
    {
        if (((params.Tag != ASN1DER_TAG_NULL) && (params.Tag != 0U)) ||
            (params.Length != 0U))
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

    return rc;
}


#ifndef ASN1DER_REMOVE_TRAVERSESEQUENCE
int32_t
Asn1Der_TraverseSequenceOf(uint8_t ** ppBufferCurrent,
                           const uint8_t * pBufferEnd,
                           uint8_t TagMustMask,
                           uint8_t TagMustValue,
                           uint8_t TagMayMask,
                           uint8_t TagMayValue,
                           int32_t(*pCb)(void * pCtx, uint8_t Tag, uint8_t * pStart, size_t Length),
                           void * pContext)
{
    size_t Length;
    int32_t rc;

    /* Get main sequence tag */
    rc = Asn1Der_GetTag(ppBufferCurrent, pBufferEnd, &Length,
                        (ASN1DER_TAG_CONSTRUCTED | ASN1DER_TAG_SEQUENCE));
    if (rc == 0)
    {
        if (*ppBufferCurrent + Length != pBufferEnd)
        {
             rc = ASN1DER_ERROR_LENGTH_MISMATCH;
        }
        else
        {
            while (*ppBufferCurrent < pBufferEnd)
            {
                uint8_t const Tag = *(*ppBufferCurrent)++;

                if ((Tag & TagMustMask) != TagMustValue)
                {
                    rc = ASN1DER_ERROR_UNEXPECTED_TAG;
                }
                else
                {
                    rc = Asn1Der_GetLength(ppBufferCurrent, pBufferEnd, &Length);
                    if (rc == 0)
                    {
                        if ((Tag & TagMayMask) == TagMayValue)
                        {
                            if (pCb != NULL)
                            {
                                rc = pCb(pContext, Tag, *ppBufferCurrent, Length);
                            }
                        }
                    }
                }

                if (rc != 0)
                {
                    break;
                }
                else
                {
                    *ppBufferCurrent = &(*ppBufferCurrent)[Length];
                }
            }
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


typedef struct
{
    Asn1Der_Sequence * pSequence;
    uint8_t Tag;
} Asn1Der_Sequence_CbCtx_t;


static int32_t
Asn1Der_GetSequenceOfCb(void * pContext,
                        uint8_t Tag,
                        uint8_t * pStart,
                        size_t Length)
{
    Asn1Der_Sequence_CbCtx_t * pCbCtx = (Asn1Der_Sequence_CbCtx_t *)pContext;
    Asn1Der_Sequence * pSequence = pCbCtx->pSequence;
    int32_t rc = 0;

    if (pSequence->Buffer.pData != NULL)
    {
        pSequence->pNext = Adapter_Alloc(sizeof(Asn1Der_Sequence));
        if (pSequence->pNext == NULL)
        {
            rc = ASN1DER_ERROR_ALLOC_FAILED;
            pSequence = NULL;
        }
        else
        {
            pSequence = pSequence->pNext;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if (pSequence != NULL)
    {
        pSequence->Buffer.pData = pStart;
        pSequence->Buffer.Length = Length;
        pSequence->Buffer.Tag = Tag;

        pCbCtx->pSequence = pSequence;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return rc;
}


int32_t
Asn1Der_GetSequenceOf(uint8_t ** ppBufferCurrent,
                      const uint8_t * pEnd,
                      Asn1Der_Sequence * pSequence,
                      uint8_t Tag)
{
    Asn1Der_Sequence_CbCtx_t pCbCtx = { pSequence, Tag };

    (void)memset(pSequence, 0, sizeof(Asn1Der_Sequence));

    return Asn1Der_TraverseSequenceOf(ppBufferCurrent, pEnd,
                                      0xFF, Tag, 0, 0,
                                      Asn1Der_GetSequenceOfCb, &pCbCtx);
}


void
Asn1Der_SequenceFree(Asn1Der_Sequence * pSequence)
{
    while (pSequence != NULL)
    {
        Asn1Der_Sequence *pNext = pSequence->pNext;

        (void)memset(pSequence, 0, sizeof(Asn1Der_Sequence));
        Adapter_Free(pSequence);

        pSequence = pNext;
    }
}
#endif


#ifndef ASN1DER_REMOVE_NAMEDDATA
void
Asn1Der_FreeNamedData(Asn1Der_NamedData * pData)
{
    if (pData != NULL)
    {
        Adapter_Free(pData->ObjectId.pData);
        Adapter_Free(pData->Value.pData);

        (void)memset(pData, 0, sizeof(Asn1Der_NamedData));
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}


void
Asn1Der_FreeNamedDataList(Asn1Der_NamedData ** ppHead)
{
    if (ppHead != NULL)
    {
        while (*ppHead != NULL)
        {
            Asn1Der_NamedData * pData = *ppHead;

            *ppHead = pData->pNext;
            Asn1Der_FreeNamedData(pData);
            Adapter_Free(pData);
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}
#endif


/* end of file asn1der_parse.c */
