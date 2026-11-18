/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
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
#include <stdint.h>
#include <string.h>

#include <ti/drivers/cryptoutils/hsm/HSMXXF3Utility.h>

/* Forward declarations for helper functions */
static void HSMXXF3_asymBigIntToHw(const uint8_t *const data,
                                   const size_t modulusSizeBits,
                                   const uint8_t beginItem,
                                   const uint8_t items,
                                   uint8_t *out);
static void HSMXXF3_asymRsaSignatureFromHw(const uint8_t *const in, const size_t modulusSizeBits, uint8_t *out);

/*
 *  ======== HSMXXF3_reverseMemCpy ========
 */
void *HSMXXF3_reverseMemCpy(void *dest, const void *src, size_t size)
{
    uint8_t *dp       = (uint8_t *)dest;
    const uint8_t *sp = (const uint8_t *)src;
    size_t tempSize   = size;

    sp = &sp[(tempSize - 1U)];
    while (tempSize > 0U)
    {
        *dp = *sp;
        dp++;
        sp--;
        tempSize--;
    }

    return dest;
}

/*
 *  ======== HSMXXF3_asymRsaSignatureFromHw ========
 */
static void HSMXXF3_asymRsaSignatureFromHw(const uint8_t *const in, const size_t modulusSizeBits, uint8_t *out)
{
    uint32_t Size = (uint32_t)BITS_TO_BYTES(modulusSizeBits);

    /* Convert big integer from HW to application format */
    HSMXXF3_reverseMemCpy(out, &in[HSM_ASYM_DATA_VHEADER], Size);
}

/*
 *  ======== HSMXXF3_asymBigIntToHw ========
 */
static void HSMXXF3_asymBigIntToHw(const uint8_t *const data,
                                   const size_t modulusSizeBits,
                                   const uint8_t beginItem,
                                   const uint8_t items,
                                   uint8_t *out)
{
    uint8_t *ptr             = out;
    uint32_t RemainingLength = HSM_ASYM_DATA_SIZE_B2WB((uint32_t)modulusSizeBits);
    uint32_t CopySize        = (uint32_t)BITS_TO_BYTES(modulusSizeBits);

    /* Convert big integer from application to HW format */
    /* - Initialize header */
    *ptr = (uint8_t)(modulusSizeBits);
    ptr++;
    *ptr = (uint8_t)(modulusSizeBits >> 8);
    ptr++;
    *ptr = (uint8_t)(beginItem);
    ptr++;
    *ptr = (uint8_t)(items);
    ptr++;
    /* - Copy data reversed */
    if (CopySize > RemainingLength)
    {
        /* Prevent buffer overrun */
        CopySize = RemainingLength;
    }
    else
    {
        /* MISRA - Intentially empty */
    }

    HSMXXF3_reverseMemCpy(ptr, data, CopySize);
    /* - Zeroize remaining part if needed */
    RemainingLength -= CopySize;
    if (RemainingLength != 0U)
    {
        (void)memset(&ptr[CopySize], 0, RemainingLength);
    }
    else
    {
        /* MISRA - Intentially empty */
    }
}

/*
 *  ======== HSMXXF3_asymVectorHeaderFormat ========
 */
void HSMXXF3_asymVectorHeaderFormat(const size_t modulusSizeBits,
                                    const uint8_t itemsLength,
                                    const uint8_t itemIdx,
                                    const uint8_t domainId,
                                    uint32_t *blob)
{
    *blob = ((domainId << 28) | (itemsLength << 24) | (itemIdx << 16) | (modulusSizeBits));
}

/*
 *  ================ Helper APIs to handle DH related operation ================
 */

/*
 *  ======== HSMXXF3_asymBEDHPriKeyToHW ========
 */
static void HSMXXF3_asymBEDHPriKeyToHW(uint8_t *in, const size_t modulusSizeBits, const uint8_t domainId, uint8_t *blob)
{
    HSMXXF3_asymVectorHeaderFormat(modulusSizeBits, 1, 0, domainId, (uint32_t *)blob);

    HSMXXF3_reverseMemCpy(&blob[HSM_ASYM_DATA_VHEADER], &in[0], BITS_TO_BYTES(modulusSizeBits));
}

/*
 *  ======== HSMXXF3_asymLEDHPriKeyToHW ========
 */
static void HSMXXF3_asymLEDHPriKeyToHW(uint8_t *in, const size_t modulusSizeBits, const uint8_t domainId, uint8_t *blob)
{
    HSMXXF3_asymVectorHeaderFormat(modulusSizeBits, 1, 0, domainId, (uint32_t *)blob);

    memcpy(&blob[HSM_ASYM_DATA_VHEADER], &in[0], BITS_TO_BYTES(modulusSizeBits));
}

void HSMXXF3_asymDHPriKeyToHW(uint8_t *in,
                              const size_t modulusSizeBits,
                              const uint8_t domainId,
                              HSMXXF3_KeyMaterialEndianness endianness,
                              uint8_t *blob)
{
    if (endianness == HSMXXF3_BIG_ENDIAN_KEY)
    {
        HSMXXF3_asymBEDHPriKeyToHW(in, modulusSizeBits, domainId, blob);
    }
    else
    {
        HSMXXF3_asymLEDHPriKeyToHW(in, modulusSizeBits, domainId, blob);
    }
}

/*
 *  ======== HSMXXF3_asymBEDHPubKeyToHW ========
 */
static void HSMXXF3_asymBEDHPubKeyToHW(uint8_t *in,
                                       const size_t modulusSizeBits,
                                       const uint8_t itemsLength,
                                       const uint8_t domainId,
                                       uint8_t *blob)
{
    HSMXXF3_asymVectorHeaderFormat(modulusSizeBits, itemsLength, 0, domainId, (uint32_t *)blob);

    HSMXXF3_reverseMemCpy(&blob[HSM_ASYM_DATA_VHEADER], &in[0], BITS_TO_BYTES(modulusSizeBits));

    /* In the case of public key, curve25519 based public keys only offer one component pubkey.u.
     * All other curves have two components pubkey.x and pubkey.y.
     */
    if (itemsLength == HSM_ASYM_ECC_PUB_KEY_VCOUNT)
    {
        HSMXXF3_asymVectorHeaderFormat(modulusSizeBits,
                                       itemsLength,
                                       1,
                                       0,
                                       (uint32_t *)&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)]);

        HSMXXF3_reverseMemCpy(&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits) + HSM_ASYM_DATA_VHEADER],
                              &in[BITS_TO_BYTES(modulusSizeBits)],
                              BITS_TO_BYTES(modulusSizeBits));
    }
}

/*
 *  ======== HSMXXF3_asymLEDHPubKeyToHW ========
 */
static void HSMXXF3_asymLEDHPubKeyToHW(uint8_t *in,
                                       const size_t modulusSizeBits,
                                       const uint8_t itemsLength,
                                       const uint8_t domainId,
                                       uint8_t *blob)
{
    HSMXXF3_asymVectorHeaderFormat(modulusSizeBits, itemsLength, 0, domainId, (uint32_t *)blob);

    memcpy(&blob[HSM_ASYM_DATA_VHEADER], &in[0], BITS_TO_BYTES(modulusSizeBits));

    /* In the case of public key, curve25519 based public keys only offer one component pubkey.u.
     * All other curves have two components pubkey.x and pubkey.y.
     */
    if (itemsLength == HSM_ASYM_ECC_PUB_KEY_VCOUNT)
    {
        HSMXXF3_asymVectorHeaderFormat(modulusSizeBits,
                                       itemsLength,
                                       1,
                                       0,
                                       (uint32_t *)&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)]);

        memcpy(&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits) + HSM_ASYM_DATA_VHEADER],
               &in[BITS_TO_BYTES(modulusSizeBits)],
               BITS_TO_BYTES(modulusSizeBits));
    }
}

/*
 *  ======== HSMXXF3_asymDHPubKeyToHW ========
 */
void HSMXXF3_asymDHPubKeyToHW(uint8_t *in,
                              const size_t modulusSizeBits,
                              const uint8_t itemsLength,
                              const uint8_t domainId,
                              HSMXXF3_KeyMaterialEndianness endianness,
                              uint8_t *blob)
{
    uint8_t *key_p = in;

    if (endianness == HSMXXF3_BIG_ENDIAN_KEY)
    {
        /* Skip the octet string formatting (first byte) */
        key_p = key_p + HSM_ASYM_ECC_PUB_KEY_UNCOMP_ENC_LENG;

        HSMXXF3_asymBEDHPubKeyToHW(key_p, modulusSizeBits, itemsLength, domainId, blob);
    }
    else
    {
        HSMXXF3_asymLEDHPubKeyToHW(key_p, modulusSizeBits, itemsLength, domainId, blob);
    }
}

/*
 *  ======== HSMXXF3_asymBEDHPubKeyFromHW ========
 */
static void HSMXXF3_asymBEDHPubKeyFromHW(const uint8_t *const in,
                                         const size_t modulusSizeBits,
                                         const uint8_t itemsLength,
                                         uint8_t *out_pubKey)
{
    HSMXXF3_asymRsaSignatureFromHw(in, modulusSizeBits, out_pubKey);

    /* In the case of public key, curve25519 based public keys only offer one component pubkey.u.
     * All other curves have two components pubkey.x and pubkey.y.
     */
    if (itemsLength == HSM_ASYM_ECC_PUB_KEY_VCOUNT)
    {
        HSMXXF3_asymRsaSignatureFromHw(&in[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)],
                                       modulusSizeBits,
                                       &out_pubKey[BITS_TO_BYTES(modulusSizeBits)]);
    }
}

/*
 *  ======== HSMXXF3_asymLEDHPubKeyFromHW ========
 */
static void HSMXXF3_asymLEDHPubKeyFromHW(const uint8_t *const in,
                                         const size_t modulusSizeBits,
                                         const uint8_t itemsLength,
                                         uint8_t *out_pubKey)
{
    memcpy(&out_pubKey[0], &in[HSM_ASYM_DATA_VHEADER], HSM_ASYM_DATA_SIZE_B2WB(modulusSizeBits));

    /* In the case of public key, curve25519 based public keys only offer one component pubkey.u.
     * All other curves have two components pubkey.x and pubkey.y.
     */
    if (itemsLength == HSM_ASYM_ECC_PUB_KEY_VCOUNT)
    {
        memcpy(&out_pubKey[HSM_ASYM_DATA_SIZE_B2WB(modulusSizeBits)],
               &in[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits) + HSM_ASYM_DATA_VHEADER],
               HSM_ASYM_DATA_SIZE_B2WB(modulusSizeBits));
    }
}

/*
 *  ======== HSMXXF3_asymDHPubKeyFromHW ========
 */
void HSMXXF3_asymDHPubKeyFromHW(const uint8_t *const in,
                                const size_t modulusSizeBits,
                                const uint8_t itemsLength,
                                HSMXXF3_KeyMaterialEndianness endianness,
                                uint8_t *out_pubKey)
{
    uint8_t *key_p = out_pubKey;

    if (endianness == HSMXXF3_BIG_ENDIAN_KEY)
    {
        *key_p = HSM_ASYM_ECC_UNCOMP_ENC_VALUE;
        key_p  = key_p + HSM_ASYM_ECC_PUB_KEY_UNCOMP_ENC_LENG;

        HSMXXF3_asymBEDHPubKeyFromHW(in, modulusSizeBits, itemsLength, key_p);
    }
    else
    {
        HSMXXF3_asymLEDHPubKeyFromHW(in, modulusSizeBits, itemsLength, key_p);
    }
}

/*
 *  ================ Helper APIs to handle DSA related operation ================
 */

/*
 *  ======== HSMXXF3_asymDsaSignatureFromHW ========
 */
void HSMXXF3_asymDsaSignatureFromHW(const uint8_t *const in,
                                    const size_t modulusSizeBits,
                                    HSMXXF3_KeyMaterialEndianness endianness,
                                    uint8_t *out_r,
                                    uint8_t *out_s)
{
    if (endianness == HSMXXF3_BIG_ENDIAN_KEY)
    {
        /* Convert Signature from HW to application format */
        HSMXXF3_asymRsaSignatureFromHw(in, modulusSizeBits, out_r);
        HSMXXF3_asymRsaSignatureFromHw(&in[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)], modulusSizeBits, out_s);
    }
    else
    {
        uint32_t sizeInBytes = (uint32_t)BITS_TO_BYTES(modulusSizeBits);

        memcpy(out_r, &in[HSM_ASYM_DATA_VHEADER], sizeInBytes);
        memcpy(out_s, &in[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits) + HSM_ASYM_DATA_VHEADER], sizeInBytes);
    }
}

/*
 *  ======== HSMXXF3_asymDsaSignatureToHW ========
 */
void HSMXXF3_asymDsaSignatureToHW(const uint8_t *const signature_r,
                                  const uint8_t *const signature_s,
                                  HSMXXF3_KeyMaterialEndianness endianness,
                                  const size_t modulusSizeBits,
                                  uint8_t *const blob)
{
    /* Endianness determines how to copy the signature to the hardware.
     * The end result should be in little endian format.
     * For big endian, the signature is copied in reverse order.
     *  - #HSMXXF3_asymBigIntToHw() is used to convert the signature to HW format as well as create the header.
     * For little endian, the signature is copied as is.
     *  - #HSMXXF3_asymVectorHeaderFormat() is used to create the header.
     *  - The signature is copied as is.
     */
    if (endianness == HSMXXF3_BIG_ENDIAN_KEY)
    {
        /* Convert Signature from application to HW format */
        /* - Signature.r */
        HSMXXF3_asymBigIntToHw(signature_r, modulusSizeBits, 0, 2, blob);
        /* - Signature.s */
        HSMXXF3_asymBigIntToHw(signature_s, modulusSizeBits, 1, 2, &blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)]);
    }
    else
    {
        HSMXXF3_asymVectorHeaderFormat(modulusSizeBits, 2, 0, 0U, (uint32_t *)blob);

        memcpy(&blob[HSM_ASYM_DATA_VHEADER], &signature_r[0], BITS_TO_BYTES(modulusSizeBits));

        HSMXXF3_asymVectorHeaderFormat(modulusSizeBits,
                                       2,
                                       1,
                                       0U,
                                       (uint32_t *)&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)]);

        memcpy(&blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits) + HSM_ASYM_DATA_VHEADER],
               &signature_s[0],
               BITS_TO_BYTES(modulusSizeBits));
    }
}

/*
 *  ======== HSMXXF3_asymDsaPubKeyToHW ========
 */
void HSMXXF3_asymDsaPubKeyToHW(const uint8_t *const pubKey,
                               const size_t modulusSizeBits,
                               const uint8_t domainId,
                               uint8_t *const blob)
{
    uint8_t lastByte = 2 | (domainId << 4);

    /* Convert Public Key from OS format to HW format */
    /* - publicKey.x */
    HSMXXF3_asymBigIntToHw(pubKey, modulusSizeBits, 0, lastByte, blob);
    /* - publicKey.y */
    HSMXXF3_asymBigIntToHw(pubKey + BITS_TO_BYTES(modulusSizeBits),
                           modulusSizeBits,
                           1,
                           lastByte,
                           &blob[HSM_ASYM_DATA_SIZE_VWB(modulusSizeBits)]);
}

/*
 *  ======== HSMXXF3_asymDsaPriKeyToHW ========
 */
void HSMXXF3_asymDsaPriKeyToHW(const uint8_t *const priKey,
                               const size_t modulusSizeBits,
                               const uint8_t domainId,
                               uint8_t *const blob)
{
    uint8_t lastByte = 1 | (domainId << 4);

    /* Convert Private Key from OS format to HW format */
    HSMXXF3_asymBigIntToHw(priKey, modulusSizeBits, 0, lastByte, blob);
}