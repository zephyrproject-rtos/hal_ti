/** @file asn1der.h
 *
 * @brief ASN1 implementation intended for DER encoding
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

#ifndef INCLUDE_GUARD_ASN1DER_H
#define INCLUDE_GUARD_ASN1DER_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>                 // uint8_t, uint32_t, int32_t
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                       // size_t
#include <third_party/hsmddk/include/Config/cs_asn1der.h>

/* ASN1 Error codes */
/* - Successful. */
#define ASN1DER_SUCCESS                     ( 0)
/* - Out of data when parsing an ASN1 data structure. */
#define ASN1DER_ERROR_OUT_OF_DATA           (-1)
/* - ASN1 tag was of an unexpected value. */
#define ASN1DER_ERROR_UNEXPECTED_TAG        (-2)
/* - Error when trying to determine the length or invalid length. */
#define ASN1DER_ERROR_INVALID_LENGTH        (-3)
/* - Actual length differs from expected length. */
#define ASN1DER_ERROR_LENGTH_MISMATCH       (-4)
/* - Data is invalid. */
#define ASN1DER_ERROR_INVALID_DATA          (-5)
/* - Memory allocation failed */
#define ASN1DER_ERROR_ALLOC_FAILED          (-6)
/* - Buffer too small when writing ASN.1 data structure. */
#define ASN1DER_ERROR_BUFFER_TOO_SMALL      (-7)

/* DER constants
 * These constants comply with the DER encoded ASN.1 type tags.
 * DER encoding uses hexadecimal representation.
 * An example DER sequence is:\n
 * - 0x02 -- tag indicating INTEGER
 * - 0x01 -- length in octets
 * - 0x05 -- value */
#define ASN1DER_TAG_BOOLEAN                 0x01U
#define ASN1DER_TAG_INTEGER                 0x02U
#define ASN1DER_TAG_BIT_STRING              0x03U
#define ASN1DER_TAG_OCTET_STRING            0x04U
#define ASN1DER_TAG_NULL                    0x05U
#define ASN1DER_TAG_OID                     0x06U
#define ASN1DER_TAG_ENUMERATED              0x0AU
#define ASN1DER_TAG_UTF8_STRING             0x0CU
#define ASN1DER_TAG_SEQUENCE                0x10U
#define ASN1DER_TAG_SET                     0x11U
#define ASN1DER_TAG_PRINTABLE_STRING        0x13U
#define ASN1DER_TAG_T61_STRING              0x14U
#define ASN1DER_TAG_IA5_STRING              0x16U
#define ASN1DER_TAG_UTC_TIME                0x17U
#define ASN1DER_TAG_GENERALIZED_TIME        0x18U
#define ASN1DER_TAG_UNIVERSAL_STRING        0x1CU
#define ASN1DER_TAG_BMP_STRING              0x1EU
#define ASN1DER_TAG_PRIMITIVE               0x00U
#define ASN1DER_TAG_CONSTRUCTED             0x20U
#define ASN1DER_TAG_CONTEXT_SPECIFIC        0x80U

/* Bit masks for each of the components of an ASN.1 tag as specified in
 * ITU X.690 (08/2015), section 8.1 "General rules for encoding",
 * paragraph 8.1.2.2:
 *
 * Bit  8     7   6   5          1
 *     +-------+-----+------------+
 *     | Class | P/C | Tag number |
 *     +-------+-----+------------+
 */
#define ASN1DER_TAG_CLASS_MASK          0xC0U
#define ASN1DER_TAG_PC_MASK             0x20U
#define ASN1DER_TAG_VALUE_MASK          0x1FU

/* Type-length-value structure that allows for ASN1 using DER. */
typedef struct
{
    uint8_t * pData;                /* Raw ASN.1 data for the big number. */
    size_t Length;                  /* ASN1 length, in octets. */
    uint8_t Sign;                   /* Sign: !0 if the big number is negative, 0 otherwise */
} Asn1Der_BigNumber;

/* Type-length-value structure that allows for ASN1 using DER. */
typedef struct
{
    uint8_t * pData;                /* ASN1 data, e.g. in ASCII. */
    size_t Length;                  /* ASN1 length, in octets. */
    uint8_t Tag;                    /* ASN1 type, e.g. ASN1DER_TAG_BIT_STRING. */
} Asn1Der_Buffer;

/* Container for ASN1 bit strings. */
typedef struct
{
    uint8_t * pData;                /* Raw ASN1 data for the bit string */
    size_t Length;                  /* ASN1 length, in octets. */
    uint8_t UnusedBits;             /* Number of unused bits at the end of the string */
} Asn1Der_BitString;

#ifndef ASN1DER_REMOVE_TRAVERSESEQUENCE
/* Container for a sequence of ASN.1 items */
typedef struct Asn1Der_Sequence
{
    struct Asn1Der_Sequence * pNext;    /* The next entry in the sequence */

    Asn1Der_Buffer Buffer;              /* Buffer containing the given ASN.1 item. */
} Asn1Der_Sequence;
#endif

#ifndef ASN1DER_REMOVE_NAMEDDATA
/* Container for a sequence or list of 'named' ASN.1 data items */
typedef struct Asn1Der_NamedData
{
    struct Asn1Der_NamedData * pNext;  /* The next entry in the sequence */

    Asn1Der_Buffer ObjectId;           /* The object identifier. */
    Asn1Der_Buffer Value;              /* The named value. */
} Asn1Der_NamedData;
#endif


/*-----------------------------------------------------------------------------
 * Asn1Der_GetLength
 *
 * Get the length of an ASN.1 element. Updates the pointer to immediately
 * behind the length.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the first byte of the length,
 *      i.e. immediately after the tag.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pLength
 *      On successful completion, *pLength contains the length read from the
 *      ASN.1 input.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetLength(uint8_t ** ppBufferCurrent,
                  const uint8_t * pBufferEnd,
                  size_t * pLength);

/*-----------------------------------------------------------------------------
 * Asn1Der_GetTag
 *
 * Get the tag and length of the element.
 * Check for the requested tag.
 * Updates the pointer to immediately behind the tag and length.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pLength
 *      On successful completion, *pLength contains the length read from the
 *      ASN.1 input.
 *
 * @param [in] Tag
 *      The expected tag.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetTag(uint8_t ** ppBufferCurrent,
               const uint8_t * pBufferEnd,
               size_t * pLength,
               uint8_t Tag);

#ifndef ASN1DER_REMOVE_GETBOOLEAN
/*-----------------------------------------------------------------------------
 * Asn1Der_GetBoolean
 *
 * Retrieve a boolean ASN.1 tag and its value.
 * Updates the pointer to immediately behind the full tag.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pValue
 *      On success, the parsed value (0 or 1).
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetBoolean(uint8_t ** ppBufferCurrent,
                   const uint8_t * pBufferEnd,
                   uint8_t * pValue);
#endif

/*-----------------------------------------------------------------------------
 * Asn1Der_GetInteger
 *
 * Retrieve an integer ASN.1 tag and its value.
 * Updates the pointer to immediately behind the full tag.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pValue
 *      On success, the parsed value.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetInteger(uint8_t ** ppBufferCurrent,
                   const uint8_t * pBufferEnd,
                   int32_t * pValue);

#ifndef ASN1DER_REMOVE_GETENUM
/*-----------------------------------------------------------------------------
 * Asn1Der_GetEnum
 *
 * Retrieve an enumerated ASN.1 tag and its value.
 * Updates the pointer to immediately behind the full tag.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pValue
 *      On success, the parsed value.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetEnum(uint8_t ** ppBufferCurrent,
                const uint8_t * pBufferEnd,
                int32_t * pValue);
#endif

/*-----------------------------------------------------------------------------
 * Asn1Der_GetBigNumberInteger
 *
 * Retrieve an big number integer ASN.1 tag and its value.
 * Updates the pointer to immediately behind the full tag.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pNumber
 *      On success, the parsed big number value.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_GetBigNumberInteger(uint8_t ** ppBufferCurrent,
                            const uint8_t * pBufferEnd,
                            Asn1Der_BigNumber * pNumber);

/*-----------------------------------------------------------------------------
 * Asn1Der_GetBitString
 *
 * Retrieve a bitstring ASN.1 tag and its value.
 * Updates the pointer to immediately behind the full tag.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pBitString
 *      On success, the Asn1Der_BitString information about the parsed value.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 */
int32_t
Asn1Der_GetBitString(uint8_t ** ppBufferCurrent,
                     const uint8_t * pBufferEnd,
                     Asn1Der_BitString * pBitString);

/*-----------------------------------------------------------------------------
 * Asn1Der_GetBitStringNull
 *
 * Retrieve a bitstring ASN.1 tag without unused bits and its value.
 * Updates the pointer to the beginning of the bit/octet string.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pLength
 *      On successful completion, *pLength contains the the content in bytes.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 *              ASN1DER_ERROR_INVALID_DATA
 */
int32_t
Asn1Der_GetBitStringNull(uint8_t ** ppBufferCurrent,
                         const uint8_t * pBufferEnd,
                         size_t * pLength);

/*-----------------------------------------------------------------------------
 * Asn1Der_GetAlgorithm
 *
 * Retrieve an AlgorithmIdentifier ASN.1 sequence.
 * Updates the pointer to immediately behind the full AlgorithmIdentifier.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pAlgorithm
 *      The buffer to receive the OID.
 *
 * @param [out] pParams
 *      The buffer to receive the parameters.
 *      This is zeroized if there are no parameters.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 */
int32_t
Asn1Der_GetAlgorithm(uint8_t ** ppBufferCurrent,
                     const uint8_t * pBufferEnd,
                     Asn1Der_Buffer * pAlgorithm,
                     Asn1Der_Buffer * pParams);

/*-----------------------------------------------------------------------------
 * Asn1Der_GetAlgorithmNull
 *
 * Retrieve an AlgorithmIdentifier ASN.1 sequence with NULL or no params.
 * Updates the pointer to immediately behind the full AlgorithmIdentifier.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pAlgorithm
 *      The buffer to receive the OID.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 *              ASN1DER_ERROR_INVALID_DATA
 */
int32_t
Asn1Der_GetAlgorithmNull(uint8_t ** ppBufferCurrent,
                         const uint8_t * pBufferEnd,
                         Asn1Der_Buffer * pAlgorithm);

#ifndef ASN1DER_REMOVE_TRAVERSESEQUENCE
/*-----------------------------------------------------------------------------
 * Asn1Der_GetSequenceOf
 *
 * Parses and splits an ASN.1 "SEQUENCE OF <tag>".
 * Updates the pointer to immediately behind the full sequence tag.
 *
 * This function allocates memory for the sequence elements. You can free
 * the allocated memory with Asn1Der_SequenceFree().
 *
 * Notes:
 * - On error, this function may return a partial list in pSequence.
 *   You must set `pSequence->pNext = NULL` before calling this function!
 *   Otherwise it is impossible to distinguish a previously non-null pointer
 *   from a pointer to an object allocated by this function.
 *
 * - If the sequence is empty, this function does not modify pSequence.
 *   If the sequence is valid and non-empty, this function sets
 *   pSequence->Buffer.Tag to Tag. This allows callers to distinguish between
 *   an empty sequence and a one-element sequence.
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the first byte
 *      after the length, i.e. the first byte of the content.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of data.
 *
 * @param [out] pSequence
 *      A Asn1Der_Sequence which this function fills. When this function
 *      returns, *pSequence is the head of a linked list. Each node in this
 *      list is allocated with Adapter_Alloc() apart from pSequence itself, and
 *      should therefore be freed with Adapter_Free().
 *      The list describes the content of the sequence. The head of the list
 *      (i.e. *pSequence itself) describes the first element, *pSequence->next
 *      describes the second element, etc. For each element, Buffer.Tag == Tag,
 *      Buffer.Length is the length of the content of the content of the
 *      element, and Buffer.pData points to the first byte of the content
 *      (i.e. immediately past the length of the element). Note that list
 *      elements may be allocated even on error.
 *
 * @param [in] Tag
 *      Each element of the sequence must have this tag.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 *              ASN1DER_ERROR_ALLOC_FAILED
 */
int32_t
Asn1Der_GetSequenceOf(uint8_t ** ppBufferCurrent,
                      const uint8_t * pEnd,
                      Asn1Der_Sequence * pSequence,
                      uint8_t Tag);

/*-----------------------------------------------------------------------------
 * Asn1Der_SequenceFree
 *
 * Free a heap-allocated linked list presentation of an ASN.1 sequence,
 * including the first element.
 *
 * There are two common ways to manage the memory used for the representation
 * of a parsed ASN.1 sequence:
 * - Allocate a head node `Asn1Der_Sequence * phead` with Adapter_alloc().
 *   Pass this node as the `pSequence` argument to Asn1Der_GetSequenceOf().
 *   If you have finished processing the sequence, call Asn1Der_SequenceFree()
 *   on `phead`.
 * - Allocate a head node `Asn1Der_Sequence * phead` in any manner, for example
 *   on the stack. Make sure that `phead->pNext == NULL`.
 *   Pass `phead` as the `pSequence` argument to Asn1Der_GetSequenceOf().
 *   When you have finished processing the sequence, call Asn1Der_SequenceFree()
 *   on `phead->pSequence`, then free `phead` itself in the appropriate manner.
 *
 * @param [in] pSequence
 *      The address of the first sequence component. This may be
 *      NULL, in which case this functions returns immediately.
 */
void
Asn1Der_SequenceFree(Asn1Der_Sequence * pSequence);

/*-----------------------------------------------------------------------------
 * Asn1Der_TraverseSequenceOf
 *
 * Traverse an ASN.1 SEQUENCE container and call a callback for each entry.
 *
 * This function checks that the input is a SEQUENCE of elements that
 * each have a "must" tag, and calls a callback function on the elements
 * that have a "may" tag.
 *
 * The callback is called on the elements with a "may" tag from left to
 * right. If the input is not a valid SEQUENCE of elements with a "must" tag,
 * the callback is called on the elements up to the leftmost point where
 * the input is invalid.
 *
 * For example, to validate that the input is a SEQUENCE of tag1 and call
 * the callback function on each element, use:
 *    Asn1Der_TraverseSequenceOf(&pBufferCurrent, pBufferEnd,
 *                               0xff, tag1, 0, 0,
 *                               pCbFunc, pContext);
 *
 * To validate that the input is a SEQUENCE of ANY and call the callback
 * function on each element, use:
 *    Asn1Der_TraverseSequenceOf(&pBufferCurrent, pBufferEnd,
 *                               0, 0, 0, 0,
 *                               pCbFunc, pContext);
 *
 * To validate that the input is a SEQUENCE of CHOICE {NULL, OCTET STRING}
 * and call the callback function on each element that is an OCTET STRING,
 * use:
 *    Asn1Der_TraverseSequenceOf(&pBufferCurrent, pBufferEnd,
 *                               0xfe, 0x04, 0xff, 0x04,
 *                               pCbFunc, pContext);
 *
 * @param [in/out] ppBufferCurrent
 *      On entry, *ppBufferCurrent points to the start of the ASN.1 element.
 *      On successful completion, *ppBufferCurrent points to the end of the
 *      ASN.1 SEQUENCE container.
 *      On error, the value of *ppBufferCurrent is undefined.
 *
 * @param [in] pBufferEnd
 *      End of the ASN.1 SEQUENCE container.
 *
 * @param [in] TagMustMask
 *      A mask to be applied to the ASN.1 tags found within the SEQUENCE
 *      before comparing to TagMustValue.
 *
 * @param [in] TagMustValue
 *      The required value of each ASN.1 tag found in the SEQUENCE, after
 *      masking with \p tag_must_mask. Mismatching tags lead to an error.
 *      For example, a value of 0 for both TagMustMask and TagMustValue
 *      means that every tag is allowed, while a value of 0xFF for
 *      TagMustMask means that TagMustValue is the only allowed tag.
 *
 * @param [in] TagMayMask
 *      A mask to be applied to the ASN.1 tags found within the SEQUENCE
 *      before comparing to TagMayValue.
 *
 * @param [in] TagMayValue
 *      The desired value of each ASN.1 tag found in the SEQUENCE, after
 *      masking with TagMayMask. Mismatching tags will be silently ignored.
 *      For example, a value of 0 for TagMayMask and TagMayValue means that
 *      any tag will be considered, while a value of 0xFF for TagMayMask means
 *      that all tags with value different from TagMayValue will be ignored.
 *
 * @param [in] pCb
 *      The callback function to trigger for each component in the ASN.1
 *      SEQUENCE that matches TagMayValue.
 *      The callback function is called with the following parameters:
 *      - The callback context (pContext)
 *      - The tag of the current element.
 *      - A pointer to the start of the current element's content inside
 *        the input.
 *      - The length of the content of the current element.
 *      If the callback returns a non-zero value, the function stops
 *      immediately, forwarding the callback's return value.
 *
 * @param [in] pContext
 *      The context to be passed to the callback \p cb.
 *
 * @return
 * On success   ASN1DER_SUCCESS
 * On failure   A negative code:
 *              ASN1DER_ERROR_OUT_OF_DATA
 *              ASN1DER_ERROR_UNEXPECTED_TAG
 *              ASN1DER_ERROR_INVALID_LENGTH
 *              ASN1DER_ERROR_LENGTH_MISMATCH
 */
int32_t
Asn1Der_TraverseSequenceOf(uint8_t ** ppBufferCurrent,
                           const uint8_t * pBufferEnd,
                           uint8_t TagMustMask,
                           uint8_t TagMustValue,
                           uint8_t TagMayMask,
                           uint8_t TagMayValue,
                           int32_t (* pCb)(void * pCtx, uint8_t Tag, uint8_t * pStart, size_t Length),
                           void * pContext);
#endif

/*-----------------------------------------------------------------------------
 * Asn1Der_WriteLength
 *
 * Write a length field in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Length
 *      The length value to write.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteLength(uint8_t ** ppBufferInsert,
                    const uint8_t * pBufferStart,
                    size_t Length);

/*-----------------------------------------------------------------------------
 * Asn1Der_WriteTag
 *
 * Write an ASN.1 tag in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Tag
 *      The tag to write.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 */
int32_t
Asn1Der_WriteTag(uint8_t ** ppBufferInsert,
                 const uint8_t * pBufferStart,
                 uint8_t Tag);

#if !defined(ASN1DER_REMOVE_WRITERAWDATA)      || \
    !defined(ASN1DER_REMOVE_WRITEOBJECTID)     || \
    !defined(ASN1DER_REMOVE_WRITEBIGNUMBERINT) || \
    !defined(ASN1DER_REMOVE_WRITEALGORITHMID)
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteRawData
 *
 * Write raw buffer data.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pData
 *      The data buffer to write.
 *
 * @param [in] Size
 *      The length of the data buffer.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 */
int32_t
Asn1Der_WriteRawData(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     const uint8_t * pData,
                     size_t Size);
#endif

#if !defined(ASN1DER_REMOVE_WRITENULL) || \
    !defined(ASN1DER_REMOVE_WRITEALGORITHMID)
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteNull
 *
 * Write a NULL ASN.1 tag with zero data in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteNull(uint8_t ** ppBufferInsert,
                  const uint8_t * pBufferStart);
#endif

/*-----------------------------------------------------------------------------
 * Asn1Der_WriteObjectId
 *
 * Write an OID ASN.1 tag and data in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pObjectId
 *      The Object Identifier (OID) to write.
 *
 * @param [in] ObjectIdLength
 *      The length of the Object Identifier (OID).
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteObjectId(uint8_t ** ppBufferInsert,
                      const uint8_t * pBufferStart,
                      const char * pObjectId,
                      size_t ObjectIdLength);

#ifndef ASN1DER_REMOVE_WRITEALGORITHMID
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteAlgorithmIdentifier
 *
 * Write an AlgorithmIdentifier sequence in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pObjectId
 *      The algorithm's Object Identifier (OID) to write.
 *
 * @param [in] ObjectIdLength
 *      The length of the algorithm's Object Identifier (OID).
 *
 * @param [in] IdentifierLength
 *      The length of the parameters that must be already written.
 *      If 0, NULL parameters are added.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteAlgorithmIdentifier(uint8_t ** ppBufferInsert,
                                 const uint8_t * pBufferStart,
                                 const char * pObjectId,
                                 size_t ObjectIdLength,
                                 size_t IdentifierLength);
#endif

#ifndef ASN1DER_REMOVE_WRITEBOOLEAN
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteBoolean
 *
 * Write a boolean ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] fBoolean
 *      The boolean value to write, either 0 or 1.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteBoolean(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     uint8_t fBoolean);
#endif

#ifndef ASN1DER_REMOVE_WRITEINTEGER
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteInteger
 *
 * Write an integer ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Value
 *      The integer value to write and must be non-negative.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteInteger(uint8_t ** ppBufferInsert,
                     const uint8_t * pBufferStart,
                     int32_t Value);
#endif

#ifndef ASN1DER_REMOVE_WRITEBIGNUMBERINT
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteBigNumberInteger
 *
 * Write an integer ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pNumber
 *      The big number integer value to write.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteBigNumberInteger(uint8_t ** ppBufferInsert,
                              const uint8_t * pBufferStart,
                              const Asn1Der_BigNumber * pNumber);
#endif

#ifndef ASN1DER_REMOVE_WRITEENUM
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteEnum
 *
 * Write an enum ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Value
 *      The integer value to write and must be non-negative.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteEnum(uint8_t ** ppBufferInsert,
                  const uint8_t * pBufferStart,
                  int32_t Value);
#endif

#if !defined(ASN1DER_REMOVE_WRITETAGGEDSTR) || \
    !defined(ASN1DER_REMOVE_WRITEOCTETSTR)  || \
    !defined(ASN1DER_REMOVE_WRITEUTF8STR)   || \
    !defined(ASN1DER_REMOVE_WRITEIA5STR)    || \
    !defined(ASN1DER_REMOVE_WRITEPRINTSTR)
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteTaggedString
 *
 * Write a string in ASN.1 format using a specific string encoding tag.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Tag
 *      The string encoding tag to write, e.g. ASN1DER_TAG_UTF8_STRING.
 *
 * @param [in] pString
 *      The string/text to write.
 *
 * @param [in] StringLength
 *      The length of the string/text in bytes.
 *      Note it might be strictly larger than the number of characters.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteTaggedString(uint8_t ** ppBufferInsert,
                          const uint8_t * pBufferStart,
                          uint8_t Tag,
                          const uint8_t * pString,
                          size_t StringLength);
#endif

#ifndef ASN1DER_REMOVE_WRITEPRINTSTR
/*-----------------------------------------------------------------------------
 * Asn1Der_WritePrintableString
 *
 * Write a string in ASN.1 format using the PrintableString string encoding
 * tag.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pString
 *      The string/text to write.
 *
 * @param [in] StringLength
 *      The length of the string/text in bytes.
 *      Note it might be strictly larger than the number of characters.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WritePrintableString(uint8_t ** ppBufferInsert,
                             const uint8_t * pBufferStart,
                             const char * pString,
                             size_t StringLength);
#endif

#ifndef ASN1DER_REMOVE_WRITEUTF8STR
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteUtf8String
 *
 * Write a UTF8 string in ASN.1 format using the UTF8String string encoding
 * tag.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pString
 *      The string/text to write.
 *
 * @param [in] StringLength
 *      The length of the string/text in bytes.
 *      Note it might be strictly larger than the number of characters.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteUtf8String(uint8_t ** ppBufferInsert,
                        const uint8_t * pBufferStart,
                        const char * pString,
                        size_t StringLength);
#endif

#ifndef ASN1DER_REMOVE_WRITEIA5STR
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteIa5String
 *
 * Write a string in ASN.1 format using the IA5String string encoding tag.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pString
 *      The string/text to write.
 *
 * @param [in] StringLength
 *      The length of the string/text in bytes.
 *      Note it might be strictly larger than the number of characters.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteIa5String(uint8_t ** ppBufferInsert,
                       const uint8_t * pBufferStart,
                       const char * pString,
                       size_t StringLength);
#endif

#if !defined(ASN1DER_REMOVE_WRITEBITSTR) || \
    !defined(ASN1DER_REMOVE_WRITENAMEDBITSTR)
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteBitString
 *
 * Write a bitstring ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pBits
 *      The bitstring to write.
 *
 * @param [in] Bits
 *      The total number of bits in the bitstring.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteBitString(uint8_t ** ppBufferInsert,
                       const uint8_t * pBufferStart,
                       const uint8_t * pBits,
                       size_t Bits);
#endif

/*-----------------------------------------------------------------------------
 * Asn1Der_WriteBitStringHeaderOnly
 *
 * Write a bitstring ASN.1 tag, length and unused bits information in ASN.1
 * format.
 * Note: Make sure that the unused bits of the value are zeroized.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] Bits
 *      The total number of bits in the bitstring.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */

int32_t
Asn1Der_WriteBitStringHeaderOnly(uint8_t ** ppBufferInsert,
                                 const uint8_t * pBufferStart,
                                 size_t Bits);

#ifndef ASN1DER_REMOVE_WRITENAMEDBITSTR
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteNamedBitString
 *
 * This function writes a named bitstring ASN.1 tag and value in ASN.1 format.
 *
 * As stated in RFC 5280 Appendix B, trailing zeroes are omitted when encoding
 * named bitstrings in DER.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pBits
 *      The bitstring to write.
 *
 * @param [in] Bits
 *      The total number of bits in the bitstring.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteNamedBitString(uint8_t ** ppBufferInsert,
                            const uint8_t * pBufferStart,
                            const uint8_t * pBits,
                            size_t Bits);
#endif

#ifndef ASN1DER_REMOVE_WRITEOCTETSTR
/*-----------------------------------------------------------------------------
 * Asn1Der_WriteOctetString
 *
 * Write an octet string ASN.1 tag and value in ASN.1 format.
 * Note: This function works backwards in data buffer.
 *
 * @param [in/out] ppBufferInsert
 *      The reference to the current insert position pointer.
 *
 * @param [in] pBufferStart
 *      The start of the buffer, for boundary-checking.
 *
 * @param [in] pString
 *      The buffer containing the string data to write.
 *
 * @param [in] StringLength
 *      The length of the string/data buffer.
 *
 * @return
 * On success   The number of bytes written to ppBufferInsert.
 * On failure   A negative code:
 *              ASN1DER_ERROR_BUFFER_TOO_SMALL
 *              ASN1DER_ERROR_INVALID_LENGTH
 */
int32_t
Asn1Der_WriteOctetString(uint8_t ** ppBufferInsert,
                         const uint8_t * pBufferStart,
                         const uint8_t * pString,
                         size_t StringLength);
#endif

#ifndef ASN1DER_REMOVE_NAMEDDATA
/*-----------------------------------------------------------------------------
 * Asn1Der_FindNamedData
 *
 * Find a specific named_data entry in a sequence or list based on the Object
 * Identifier (OID).
 *
 * @param [in] pList
 *      The reference to the list to search.
 *
 * @param [in] pObjectId
 *      The Object Identifier (OID) to find.
 *
 * @param [in] ObjectIdLength
 *      Size of the Object Identifier (OID).
 *
 * @return
 * When found   The pointer to the entry.
 * Otherwise    NULL
 */
Asn1Der_NamedData *
Asn1Der_FindNamedData(Asn1Der_NamedData * pList,
                      const uint8_t * pObjectId,
                      size_t ObjectIdLength);

/*-----------------------------------------------------------------------------
 * Asn1Der_StoreNamedData
 *
 * Create or find a specific named_data entry for writing in a sequence or
 * list based on the OID. If not already in there, a new entry is added to the
 * head of the list.
 * Warning: Destructive behaviour for the pValue data!
 *
 * @param [in/out] ppHead
 *      The pointer to the head (root) of the list and can be updated in case
 *      of a new entry.
 *
 * @param [in] pObjectId
 *      The Object Identifier (OID) to find.
 *
 * @param [in] ObjectIdLength
 *      Size of the Object Identifier (OID).
 *
 * @param [in] pValue
 *      The associated data to store. If this is NULL, no data is copied to
 *      the new or existing entry.
 *
 * @param [in] ValueLength
 *      The minimum length of the data buffer needed. If this is 0, do not
 *      allocate a buffer for the associated data.
 *      If the OID was already present, the existing buffer is enlarged,
 *      shrinked or freed to fit the associated data.
 *
 * @return
 * On success   A pointer to the new / existing entry.
 * On failure   NULL if there was a memory allocation error.
 */
Asn1Der_NamedData *
Asn1Der_StoreNamedData(Asn1Der_NamedData ** ppHead,
                       const uint8_t * pObjectId,
                       size_t ObjectIdLength,
                       const uint8_t * pValue,
                       size_t ValueLength);

/*-----------------------------------------------------------------------------
 * Asn1Der_FreeNamedData
 *
 * Free an Asn1Der_NamedData entry
 *
 * @param [in] pData
 *      The named data entry to free.
 *      This function calls Adapter_Free() on pData->ObjectId.pData and
 *      pData->Value.pData.
 */
void
Asn1Der_FreeNamedData(Asn1Der_NamedData * pData);

/*-----------------------------------------------------------------------------
 * Asn1Der_FreeNamedDataList
 *
 * Free all entries in an Asn1Der_NamedData list.
 *
 * @param [in] ppHead
 *      Pointer to the head of the list of named data entries to free.
 *      This function calls Asn1Der_FreeNamedData() and Adapter_Free() on
 *      each list element and sets *ppHead to NULL.
 */
void
Asn1Der_FreeNamedDataList(Asn1Der_NamedData ** ppHead);
#endif


#endif /* INCLUDE_GUARD_ASN1DER_H */

/* end of file asn1der.h */
