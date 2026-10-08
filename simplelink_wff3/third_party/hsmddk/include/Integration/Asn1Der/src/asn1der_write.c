/**
 * @file asn1der_write.c
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


static inline uint8_t
Asn1DerLocal_Byte0(uint32_t x)
{
    return (uint8_t)(x);
}

static inline uint8_t
Asn1DerLocal_Byte1(uint32_t x)
{
    return (uint8_t)((x) >> 8);
}

static inline uint8_t
Asn1DerLocal_Byte2(uint32_t x)
{
    return (uint8_t)((x) >> 16);
}

static inline uint8_t
Asn1DerLocal_Byte3(uint32_t x)
{
    return (uint8_t)((x) >> 24);
}

#if !defined(ASN1DER_REMOVE_WRITEBOOLEAN) || \
    !defined(ASN1DER_REMOVE_WRITEINTEGER)  || \
    !defined(ASN1DER_REMOVE_WRITEENUM)
static int32_t
Asn1DerLocal_WriteTaggedInt(uint8_t ** ppBufferInsert,
                            const uint8_t * pBufferStart,
                            int32_t Value,
                            uint8_t Tag)
{
    size_t length = 0U;
    int32_t LocalValue = Value;
    int32_t rc = 0;

    do
    {
        if ((*ppBufferInsert - pBufferStart) < 1)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
            LocalValue = 0;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)LocalValue);
            LocalValue >>= 8U;
            length++;
        }
    } while (LocalValue > 0);

    if (rc >= 0)
    {
        if ((**ppBufferInsert & 0x80U) != 0U)
        {
            if ((*ppBufferInsert - pBufferStart) < 1)
            {
                rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                (*ppBufferInsert)--;
                **ppBufferInsert = 0x00U;
                length++;
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
        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, Tag);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}
#endif


int32_t
Asn1Der_WriteLength(uint8_t ** ppBufferInsert,
                    const uint8_t * pBufferStart,
                    size_t Length)
{
    int32_t rc;

    if (Length < 0x80U)
    {
        if ((*ppBufferInsert - pBufferStart) < 1)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)Length);
            rc = 1;
        }
    }
    else if (Length < 0x100U)
    {
        if ((*ppBufferInsert - pBufferStart) < 2)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = 0x81U;
            rc = 2;
        }
    }
    else if (Length < 0x10000U)
    {
        if ((*ppBufferInsert - pBufferStart) < 3)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte1((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = 0x82U;
            rc = 3;
        }
    }
    else if (Length < 0x1000000U)
    {
        if ((*ppBufferInsert - pBufferStart) < 4)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte1((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte2((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = 0x83U;
            rc = 4;
        }
    }
    else
    {
        /* (Length <= (size_t)0xFFFFFFFFU) */

        if ((*ppBufferInsert - pBufferStart) < 5)
        {
            rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
        }
        else
        {
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte0((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte1((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte2((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = Asn1DerLocal_Byte3((uint32_t)Length);
            (*ppBufferInsert)--;
            **ppBufferInsert = 0x84U;
            rc = 5;
        }
    }

    return rc;
}


int32_t
Asn1Der_WriteTag(uint8_t ** ppBufferInsert,
                 const uint8_t * pBufferStart,
                 uint8_t Tag)
{
    int32_t rc;

    if ((*ppBufferInsert - pBufferStart) < 1)
    {
        rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        (*ppBufferInsert)--;
        **ppBufferInsert = Tag;
        rc = 1;
    }

    return rc;
}


#if !defined(ASN1DER_REMOVE_WRITERAWDATA)      || \
    !defined(ASN1DER_REMOVE_WRITEOBJECTID)     || \
    !defined(ASN1DER_REMOVE_WRITEBIGNUMBERINT) || \
    !defined(ASN1DER_REMOVE_WRITEALGORITHMID)
int32_t
Asn1Der_WriteRawData(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     const uint8_t * pData,
                     size_t Size)
{
    int32_t rc;

    if ((*ppBufferInsert < pBufferStart) ||
        ((*ppBufferInsert - pBufferStart) < (int32_t)Size))
    {
        rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        *ppBufferInsert -= Size;
        (void)memcpy(*ppBufferInsert, pData, Size);
        rc = (int32_t)Size;
    }

    return rc;
}
#endif


#ifndef ASN1DER_REMOVE_WRITEBIGNUMBERINT
int32_t
Asn1Der_WriteBigNumberInteger(uint8_t ** ppBufferInsert,
                              const uint8_t * pBufferStart,
                              const Asn1Der_BigNumber * pNumber)
{
    size_t length = 0U;
    int32_t rc;

    /* Write the big number */
    rc = Asn1Der_WriteRawData(ppBufferInsert, pBufferStart,
                              pNumber->pData, pNumber->Length);
    if (rc >= 0)
    {
        length += (size_t)rc;

        /* DER format assumes 2s complement for numbers, so the leftmost bit
         * should be 0 for positive numbers and 1 for negative numbers. */
        if ((pNumber->Sign > 0U) && ((**ppBufferInsert & 0x80U) != 0U))
        {
            if ((*ppBufferInsert - pBufferStart) < 1)
            {
                rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
            }
            else
            {
                (*ppBufferInsert)--;
                **ppBufferInsert = 0x00U;
                length++;
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
        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, ASN1DER_TAG_INTEGER);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}
#endif


#if !defined(ASN1DER_REMOVE_WRITENULL) || \
    !defined(ASN1DER_REMOVE_WRITEALGORITHMID)
int32_t
Asn1Der_WriteNull(uint8_t ** ppBufferInsert,
                  const uint8_t * pBufferStart)
{
    size_t length = 0U;
    int32_t rc;

    rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
    if (rc >= 0)
    {
        length += (size_t)rc;

        rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, ASN1DER_TAG_NULL);
        if (rc >= 0)
        {
            length += (size_t)rc;
            rc = (int32_t)length;
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
#endif


#if !defined(ASN1DER_REMOVE_WRITEOBJECTID) || \
    !defined(ASN1DER_REMOVE_WRITEALGORITHMID)
int32_t
Asn1Der_WriteObjectId(uint8_t ** ppBufferInsert,
                      const uint8_t * pBufferStart,
                      const char * pObjectId,
                      size_t ObjectIdLength)
{
    const uint8_t * ptr = (const uint8_t *)pObjectId;
    size_t length = 0U;
    int32_t rc;

    rc = Asn1Der_WriteRawData(ppBufferInsert, pBufferStart,
                              ptr, ObjectIdLength);
    if (rc >= 0)
    {
        length += (size_t)rc;

        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, ASN1DER_TAG_OID);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}
#endif


#ifndef ASN1DER_REMOVE_WRITEALGORITHMID
int32_t
Asn1Der_WriteAlgorithmIdentifier(uint8_t ** ppBufferInsert,
                                 const uint8_t * pBufferStart,
                                 const char * pObjectId,
                                 size_t ObjectIdLength,
                                 size_t IdentifierLength)
{
    size_t length = 0U;
    int32_t rc = 0;

    if (IdentifierLength == 0U)
    {
        rc = Asn1Der_WriteNull(ppBufferInsert, pBufferStart);
        if (rc >= 0)
        {
            length += (size_t)rc;
        }
        else
        {
            /* MISRA - Intentially empty */
        }
    }
    else
    {
        length += IdentifierLength;
    }

    if (rc >= 0)
    {
        rc = Asn1Der_WriteObjectId(ppBufferInsert, pBufferStart,
                                   pObjectId, ObjectIdLength);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
            if (rc >= 0)
            {
                length += (size_t)rc;

                rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart,
                                      (ASN1DER_TAG_CONSTRUCTED | ASN1DER_TAG_SEQUENCE));
                if (rc >= 0)
                {
                    length += (size_t)rc;
                    rc = (int32_t)length;
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

    return rc;
}
#endif


#ifndef ASN1DER_REMOVE_WRITEBOOLEAN
int32_t
Asn1Der_WriteBoolean(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     uint8_t fBoolean)
{
    int32_t Value;

    if (fBoolean != 0U)
    {
        Value = 255;
    }
    else
    {
        Value = 0;
    }

    return Asn1DerLocal_WriteTaggedInt(ppBufferInsert, pBufferStart,
                                       Value, ASN1DER_TAG_BOOLEAN);
}
#endif


#ifndef ASN1DER_REMOVE_WRITEINTEGER
int32_t
Asn1Der_WriteInteger(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     int32_t Value)
{
    return Asn1DerLocal_WriteTaggedInt(ppBufferInsert, pBufferStart,
                                       Value, ASN1DER_TAG_INTEGER);
}
#endif


#ifndef ASN1DER_REMOVE_WRITEENUM
int32_t
Asn1Der_WriteEnum(uint8_t ** ppBufferInsert,
                  const uint8_t * pBufferStart,
                  int32_t Value)
{
    return Asn1DerLocal_WriteTaggedInt(ppBufferInsert, pBufferStart,
                                       Value, ASN1DER_TAG_ENUMERATED);
}
#endif

#if !defined(ASN1DER_REMOVE_WRITETAGGEDSTR) || \
    !defined(ASN1DER_REMOVE_WRITEOCTETSTR)  || \
    !defined(ASN1DER_REMOVE_WRITEUTF8STR)   || \
    !defined(ASN1DER_REMOVE_WRITEIA5STR)    || \
    !defined(ASN1DER_REMOVE_WRITEPRINTSTR)
int32_t
Asn1Der_WriteTaggedString(uint8_t ** ppBufferInsert,
                          const uint8_t * pBufferStart,
                          uint8_t Tag,
                          const uint8_t * pString,
                          size_t StringLength)
{
    size_t length = 0U;
    int32_t rc = 0;

    rc = Asn1Der_WriteRawData(ppBufferInsert, pBufferStart,
                              pString, StringLength);
    if (rc >= 0)
    {
        length += (size_t)rc;

        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, Tag);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}
#endif


#ifndef ASN1DER_REMOVE_WRITEOCTETSTR
int32_t
Asn1Der_WriteOctetString(uint8_t ** ppBufferInsert,
                         const uint8_t * pBufferStart,
                         const uint8_t * pString,
                         size_t StringLength)
{
    return Asn1Der_WriteTaggedString(ppBufferInsert, pBufferStart,
                                     ASN1DER_TAG_OCTET_STRING,
                                     pString, StringLength);
}
#endif


#ifndef ASN1DER_REMOVE_WRITEUTF8STR
int32_t
Asn1Der_WriteUtf8String(uint8_t ** ppBufferInsert,
                        const uint8_t * pBufferStart,
                        const char * pString,
                        size_t StringLength)
{
    return Asn1Der_WriteTaggedString(ppBufferInsert, pBufferStart,
                                     ASN1DER_TAG_UTF8_STRING,
                                     (const uint8_t *)pString, StringLength);
}
#endif


#ifndef ASN1DER_REMOVE_WRITEPRINTSTR
int32_t
Asn1Der_WritePrintableString(uint8_t ** ppBufferInsert,
                             const uint8_t * pBufferStart,
                             const char * pString,
                             size_t StringLength)
{
    return Asn1Der_WriteTaggedString(ppBufferInsert, pBufferStart,
                                     ASN1DER_TAG_PRINTABLE_STRING,
                                     (const uint8_t *)pString, StringLength);
}
#endif


#ifndef ASN1DER_REMOVE_WRITEIA5STR
int32_t
Asn1Der_WriteIa5String(uint8_t ** ppBufferInsert,
                       const uint8_t * pBufferStart,
                       const char * pString,
                       size_t StringLength)
{
    return Asn1Der_WriteTaggedString(ppBufferInsert, pBufferStart,
                                     ASN1DER_TAG_IA5_STRING,
                                     (const uint8_t *)pString, StringLength);
}
#endif


int32_t
Asn1Der_WriteBitStringHeaderOnly(uint8_t ** ppBufferInsert,
                                 const uint8_t * pBufferStart,
                                 size_t Bits)
{
    size_t byte_length;
    size_t unused_bits;
    size_t length = 0U;
    int32_t rc = 0;

    byte_length = (Bits + 7U) / 8U;
    unused_bits = (byte_length * 8U) - Bits;

    if ((*ppBufferInsert < pBufferStart) ||
        ((*ppBufferInsert - pBufferStart) < 1))
    {
        rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        length = byte_length + 1U;

        /* Write unused bits */
        (*ppBufferInsert)--;
        **ppBufferInsert = (uint8_t)unused_bits;
    }

    if (rc >= 0)
    {
        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, ASN1DER_TAG_BIT_STRING);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}


#if !defined(ASN1DER_REMOVE_WRITEBITSTR) || \
    !defined(ASN1DER_REMOVE_WRITENAMEDBITSTR)
int32_t
Asn1Der_WriteBitString(uint8_t ** ppBufferInsert,
                       const uint8_t * pBufferStart,
                       const uint8_t * pBits,
                       size_t Bits)
{
    size_t byte_length;
    size_t unused_bits;
    size_t length = 0U;
    int32_t rc = 0;

    byte_length = (Bits + 7U) / 8U;
    unused_bits = (byte_length * 8U) - Bits;

    if ((*ppBufferInsert < pBufferStart) ||
        ((int32_t)(*ppBufferInsert - pBufferStart) < (int32_t)(uintptr_t)(byte_length + 1U)))
    {
        rc = ASN1DER_ERROR_BUFFER_TOO_SMALL;
    }
    else
    {
        length = byte_length + 1U;

        /* Write the bitstring. Ensure the unused bits are zeroized */
        if (byte_length > 0U)
        {
            byte_length--;
            (*ppBufferInsert)--;
            **ppBufferInsert = (uint8_t)(pBits[byte_length] & ~((0x1U << unused_bits) - 1U));
            *ppBufferInsert -= byte_length;
            (void)memcpy(*ppBufferInsert, pBits, byte_length);
        }
        else
        {
            /* MISRA - Intentially empty */
        }

        /* Write unused bits */
        (*ppBufferInsert)--;
        **ppBufferInsert = (uint8_t)unused_bits;
    }

    if (rc >= 0)
    {
        rc = Asn1Der_WriteLength(ppBufferInsert, pBufferStart, length);
        if (rc >= 0)
        {
            length += (size_t)rc;

            rc = Asn1Der_WriteTag(ppBufferInsert, pBufferStart, ASN1DER_TAG_BIT_STRING);
            if (rc >= 0)
            {
                length += (size_t)rc;
                rc = (int32_t)length;
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

    return rc;
}
#endif


#ifndef ASN1DER_REMOVE_WRITENAMEDBITSTR
int32_t
Asn1Der_WriteNamedBitString(uint8_t ** ppBufferInsert,
                            const uint8_t * pBufferStart,
                            const uint8_t * pBits,
                            size_t Bits)
{
    size_t lBits = Bits;

    /* Named bitstrings require that trailing 0s are excluded in the encoding
     * of the bitstring. Trailing 0s are considered part of the 'unused' bits
     * when encoding this value in the first content octet */
    if  (lBits != 0U)
    {
        size_t unused_bits;
        size_t byte_length = (lBits + 7U) / 8U;
        const uint8_t * cur_byte;
        uint8_t cur_byte_shifted;

        unused_bits = (byte_length * 8) - lBits;

        cur_byte = &pBits[byte_length - 1];
        cur_byte_shifted = (uint8_t)(*cur_byte >> unused_bits);

        while ((cur_byte_shifted & 0x1U) == 0U)
        {
            lBits--;
            if (lBits == 0U)
            {
                break;
            }
            else if ((lBits % 8U) == 0U)
            {
                cur_byte--;
                cur_byte_shifted = *cur_byte;
            }
            else
            {
                cur_byte_shifted >>= 1;
            }
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return Asn1Der_WriteBitString(ppBufferInsert, pBufferStart, pBits, lBits);
}
#endif


#ifndef ASN1DER_REMOVE_NAMEDDATA
Asn1Der_NamedData *
Asn1Der_FindNamedData(Asn1Der_NamedData * pList,
                      const uint8_t * pObjectId,
                      size_t ObjectIdLength)
{
    while (pList != NULL)
    {
        if ((pList->ObjectId.Length == ObjectIdLength) &&
            (memcmp(pList->ObjectId.pData, pObjectId, ObjectIdLength) == 0))
        {
            break;
        }
        else
        {
            pList = pList->pNext;
        }
    }

    return pList;
}


Asn1Der_NamedData *
Asn1Der_StoreNamedData(Asn1Der_NamedData ** ppHead,
                       const uint8_t * pObjectId,
                       size_t ObjectIdLength,
                       const uint8_t * pValue,
                       size_t ValueLength)
{
    Asn1Der_NamedData *pCurrent = Asn1Der_FindNamedData(*ppHead, pObjectId, ObjectIdLength);
    if (pCurrent == NULL)
    {
        /* Add new entry */
        pCurrent = (Asn1Der_NamedData *)Adapter_Alloc((uint32_t)sizeof(Asn1Der_NamedData));
        if (pCurrent != NULL)
        {
            pCurrent->ObjectId.pData = (uint8_t *)Adapter_Alloc((uint32_t)ObjectIdLength);
            if (pCurrent->ObjectId.pData == NULL)
            {
                Adapter_Free(pCurrent);
                pCurrent = NULL;
            }
            else
            {
                pCurrent->ObjectId.Length = ObjectIdLength;
                (void)memcpy(pCurrent->ObjectId.pData, pObjectId, ObjectIdLength);

                pCurrent->Value.Length = ValueLength;
                if (ValueLength != 0)
                {
                    pCurrent->Value.pData = (uint8_t *)Adapter_Alloc((uint32_t)ValueLength);
                    if (pCurrent->Value.pData == NULL)
                    {
                        Adapter_Free(pCurrent->ObjectId.pData);
                        Adapter_Free(pCurrent);
                        pCurrent = NULL;
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

            if (pCurrent != NULL)
            {
                pCurrent->pNext = *ppHead;
                *ppHead = pCurrent;
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
    else if (ValueLength == 0)
    {
        /* Clear value buffer */
        Adapter_Free(pCurrent->Value.pData);
        pCurrent->Value.pData = NULL;
    }
    else if (pCurrent->Value.Length != ValueLength)
    {
        /* Enlarge existing value buffer if needed
         * Preserve old data until the allocation succeeded, to leave list in
         * a consistent state in case allocation fails. */
        void *pTemp = (uint8_t *)Adapter_Alloc((uint32_t)ValueLength);
        if (pTemp == NULL)
        {
            /* Value can not be updated */
            pCurrent = NULL;
        }
        else
        {
            Adapter_Free(pCurrent->Value.pData);
            pCurrent->Value.pData = pTemp;
            pCurrent->Value.Length = ValueLength;
        }
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    if ((pCurrent != NULL) && (pValue != NULL) && (ValueLength != 0U))
    {
        /* Copy value to value buffer */
        (void)memcpy(pCurrent->Value.pData, pValue, ValueLength);
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    return pCurrent;
}
#endif


/* end of file asn1der_write.c */
