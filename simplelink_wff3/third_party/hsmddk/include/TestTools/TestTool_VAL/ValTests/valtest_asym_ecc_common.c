/* valtest_asym_ecc_common.c
 *
 * Description: ECC Common test functions
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
#include "testvectors_ecc_curves.h"
#include "valtest_asym_ecc_common.h"    /* API to implement */


/*----------------------------------------------------------------------------
 * test_AsymEccArguments
 *
 * This test helper function checks the VAL API arguments of the common
 * (general) ECC functions.
 */
int
test_AsymEccArguments(void)
{
    uint8_t Buffer[4];
    ValSize_t Size = 100;
    ValAssetId_t AssetId = 0x5001;
    ValAsymECDomainParam_t Domain;
    ValAsymKey_t Key;
    ValAsymKey_t ErrorKey;
    ValAsymBigInt_t BigInt;
    ValAsymECCPoint_t Point;
    ValAsymECCPoint_t ErrorPoint;
    ValStatus_t Status;

    // General function
    // - val_AsymInitKey
    Status = val_AsymInitKey(VAL_ASSETID_INVALID, VAL_ASSETID_INVALID, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA256, &Key);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument1/2)=", Status);

    Status = val_AsymInitKey(AssetId, AssetId, 0, VAL_SYM_ALGO_HASH_SHA1, &Key);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument3)=", Status);

    Status = val_AsymInitKey(AssetId, AssetId, 128, VAL_SYM_ALGO_HASH_SHA1, &Key);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument4I)=", Status);

    Status = val_AsymInitKey(AssetId, AssetId, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA224, &Key);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument4I)=", Status);

    Status = val_AsymInitKey(AssetId, AssetId, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA256, &Key);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument4I)=", Status);

    Status = val_AsymInitKey(AssetId, AssetId, VAL_ASYM_ECP_MIN_BITS, VAL_SYM_ALGO_HASH_SHA256, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymInitKey(BadArgument5)=", Status);

    // ECC part
    // - val_AsymEccAllocDomainAsset
    Status = val_AsymEccAllocDomainAsset((VAL_ASYM_ECP_MIN_BITS - 1), &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccAllocDomainAsset(BadArgument1L)=", Status);

    Status = val_AsymEccAllocDomainAsset((VAL_ASYM_ECP_MAX_BITS + 1), &AssetId);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccAllocDomainAsset(BadArgument1H)=", Status);

    Status = val_AsymEccAllocDomainAsset(VAL_ASYM_ECP_MAX_BITS, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccAllocDomainAsset(BadArgument2)=", Status);

    // - val_AsymEccLoadDomainAssetPlaintext
    Status = val_AsymEccLoadDomainAssetPlaintext(NULL, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1)=", Status);

    Domain.Family = VAL_ECC_FAMILY_NIST_P;
    Domain.ModulusSizeBits = VAL_ASYM_ECP_MAX_BITS;
    Domain.Modulus.Data_p = Buffer;
    Domain.Modulus.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(Domain.ModulusSizeBits);
    Domain.a.Data_p = Buffer;
    Domain.a.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;
    Domain.b.Data_p = Buffer;
    Domain.b.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;
    Domain.Order.Data_p = Buffer;
    Domain.Order.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;
    Domain.BasePoint.x.Data_p = Buffer;
    Domain.BasePoint.x.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;
    Domain.BasePoint.y.Data_p = Buffer;
    Domain.BasePoint.y.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;
    Domain.CoFactor = 1;

    Domain.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS - 1;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);

    Domain.ModulusSizeBits = VAL_ASYM_ECP_MAX_BITS + 1;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.ModulusSizeBits = VAL_ASYM_ECP_MAX_BITS;

    Domain.Modulus.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.Modulus.Data_p = Buffer;

    Domain.Modulus.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(Domain.ModulusSizeBits)-1;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.Modulus.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(Domain.ModulusSizeBits);

    Domain.a.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.a.Data_p = Buffer;

    Domain.a.ByteDataSize = 0;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.a.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;

    Domain.b.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.b.Data_p = Buffer;

    Domain.b.ByteDataSize = 0;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.b.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;

    Domain.Order.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.Order.Data_p = Buffer;

    Domain.Order.ByteDataSize = 0;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.Order.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;

    Domain.BasePoint.x.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.BasePoint.x.Data_p = Buffer;

    Domain.BasePoint.x.ByteDataSize = 0;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.BasePoint.x.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;

    Domain.BasePoint.y.Data_p = NULL;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.BasePoint.y.Data_p = Buffer;

    Domain.BasePoint.y.ByteDataSize = 0;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument1I)=", Status);
    Domain.BasePoint.y.ByteDataSize = VAL_ASYM_ECP_MAX_BITS;

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, VAL_ASSETID_INVALID, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument2)=", Status);

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, NULL, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument4)=", Status);

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MIN_SIZE - 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument5L)=", Status);

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MAX_SIZE + 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument5H)=", Status);

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, NULL, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument6&7)=", Status);

    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument7)=", Status);

    Size = (128/8) - 1;
    Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadDomainAssetPlaintext(BadArgument7L)=", Status);
    Size = 100;

    // - val_AsymEccGenKeyPair
    Key.DomainAssetId = AssetId;
    Key.KeyAssetId = AssetId;
    Key.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS;
    Key.HashAlgorithm = VAL_SYM_ALGO_NONE;

    Point.x.Data_p = Buffer;
    Point.x.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);
    Point.y.Data_p = Buffer;
    Point.y.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEccGenKeyPair(NULL, &Key, AssetId, Buffer, Size, NULL, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument1)=", Status);

    Status = val_AsymEccGenKeyPair(&Key, NULL, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument2)=", Status);

    ErrorKey = Key;
    ErrorKey.DomainAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymEccGenKeyPair(&ErrorKey, &Key, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument1I)=", Status);
    Status = val_AsymEccGenKeyPair(&Key, &ErrorKey, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument2I)=", Status);
    ErrorKey.DomainAssetId = AssetId;

    ErrorKey.KeyAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymEccGenKeyPair(&ErrorKey, &Key, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument1I)=", Status);
    Status = val_AsymEccGenKeyPair(&Key, &ErrorKey, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument2I)=", Status);
    ErrorKey.KeyAssetId = AssetId;

    ErrorKey.ModulusSizeBits = (VAL_ASYM_ECP_MIN_BITS - 1);
    Status = val_AsymEccGenKeyPair(&ErrorKey, &Key, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument1I)=", Status);
    Status = val_AsymEccGenKeyPair(&Key, &ErrorKey, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument2I)=", Status);

    ErrorKey.ModulusSizeBits = (VAL_ASYM_ECP_MAX_BITS + 1);
    Status = val_AsymEccGenKeyPair(&ErrorKey, &Key, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument1I)=", Status);
    Status = val_AsymEccGenKeyPair(&Key, &ErrorKey, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument2I)=", Status);

    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, NULL, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument4)=", Status);

    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, (VAL_KEYBLOB_AAD_MIN_SIZE - 1), &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument5L)=", Status);

    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, (VAL_KEYBLOB_AAD_MAX_SIZE + 1), &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument5H)=", Status);

    ErrorPoint = Point;
    ErrorPoint.x.Data_p = NULL;
    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &ErrorPoint, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument6I)=", Status);
    ErrorPoint.x.Data_p = Buffer;

    ErrorPoint.x.ByteDataSize--;
    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &ErrorPoint, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument6I)=", Status);
    ErrorPoint.x.ByteDataSize++;

    ErrorPoint.y.Data_p = NULL;
    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &ErrorPoint, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument6I)=", Status);
    ErrorPoint.y.Data_p = Buffer;

    ErrorPoint.y.ByteDataSize--;
    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &ErrorPoint, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument6I)=", Status);
    ErrorPoint.y.ByteDataSize++;

    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &Point, Buffer, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument8)=", Status);

    Size = (128/8) - 1;
    Status = val_AsymEccGenKeyPair(&Key, &Key, AssetId, Buffer, Size, &Point, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument8L)=", Status);
    Size = 100;

    // - val_AsymEccGenPublicKey
    Status = val_AsymEccGenPublicKey(NULL, &Key, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument1)=", Status);

    Status = val_AsymEccGenPublicKey(&Key, NULL, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument2)=", Status);

    ErrorKey = Key;
    ErrorKey.DomainAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument1I)=", Status);
    Status = val_AsymEccGenPublicKey(&Key, &ErrorKey, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument2I)=", Status);
    ErrorKey.DomainAssetId = AssetId;

    ErrorKey.KeyAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument1I)=", Status);
    Status = val_AsymEccGenPublicKey(&Key, &ErrorKey, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument2I)=", Status);
    ErrorKey.KeyAssetId = AssetId;

    ErrorKey.ModulusSizeBits = (VAL_ASYM_ECP_MIN_BITS - 1);
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument1I)=", Status);
    Status = val_AsymEccGenPublicKey(&Key, &ErrorKey, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument2I)=", Status);

    ErrorKey.ModulusSizeBits = (VAL_ASYM_ECP_MAX_BITS + 1);
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument1I)=", Status);
    Status = val_AsymEccGenPublicKey(&Key, &ErrorKey, &Point);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenPublicKey(BadArgument2I)=", Status);

    ErrorPoint = Point;
    ErrorPoint.x.Data_p = NULL;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &ErrorPoint);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument3I)=", Status);
    ErrorPoint.x.Data_p = Buffer;

    ErrorPoint.x.ByteDataSize--;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &ErrorPoint);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument3I)=", Status);
    ErrorPoint.x.ByteDataSize++;

    ErrorPoint.y.Data_p = NULL;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &ErrorPoint);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument3I)=", Status);
    ErrorPoint.y.Data_p = Buffer;

    ErrorPoint.y.ByteDataSize--;
    Status = val_AsymEccGenPublicKey(&ErrorKey, &Key, &ErrorPoint);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccGenKeyPair(BadArgument3I)=", Status);
    ErrorPoint.y.ByteDataSize++;

    // - val_AsymEccLoadPrivateKeyAssetPlaintext
    BigInt.Data_p = Buffer;
    BigInt.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(NULL, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument1)=", Status);

    BigInt.Data_p = NULL;
    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument1I)=", Status);
    BigInt.Data_p = Buffer;

    BigInt.ByteDataSize = 0;
    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument1I)=", Status);
    BigInt.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, (VAL_ASYM_ECP_MIN_BITS - 1), AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument2L)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, (VAL_ASYM_ECP_MAX_BITS + 1), AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument2H)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_ASSETID_INVALID, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument3)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, NULL, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument5)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MIN_SIZE - 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument6L)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MAX_SIZE + 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument6H)=", Status);

    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument8)=", Status);

    Size = (128/8) - 1;
    Status = val_AsymEccLoadPrivateKeyAssetPlaintext(&BigInt, VAL_ECC_FAMILY_NIST_P, Size, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPrivateKeyAssetPlaintext(BadArgument8L)=", Status);
    Size = 100;

    // - val_AsymEccLoadPublicKeyAssetPlaintext
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(NULL, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument1)=", Status);

    ErrorPoint = Point;
    ErrorPoint.x.Data_p = NULL;
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ErrorPoint, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument1I)=", Status);
    ErrorPoint.x.Data_p = Buffer;

    ErrorPoint.x.ByteDataSize = 0;
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ErrorPoint, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument1I)=", Status);
    ErrorPoint.x.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    ErrorPoint.y.Data_p = NULL;
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ErrorPoint, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument1I)=", Status);
    ErrorPoint.y.Data_p = Buffer;

    ErrorPoint.y.ByteDataSize = 0;
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&ErrorPoint, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument1I)=", Status);
    ErrorPoint.y.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(VAL_ASYM_ECP_MIN_BITS);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, (VAL_ASYM_ECP_MIN_BITS - 1), AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument2L)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, (VAL_ASYM_ECP_MAX_BITS + 1), AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument2H)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, VAL_ASSETID_INVALID, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument3)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, NULL, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument5)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MIN_SIZE - 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument6L)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, (VAL_KEYBLOB_AAD_MAX_SIZE + 1), Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument6H)=", Status);

    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, VAL_ASYM_ECP_MIN_BITS, AssetId, AssetId, Buffer, Size, Buffer, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument8)=", Status);

    Size = (128/8) - 1;
    Status = val_AsymEccLoadPublicKeyAssetPlaintext(&Point, VAL_ECC_FAMILY_NIST_P, Size, AssetId, AssetId, Buffer, Size, Buffer, &Size);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_AsymEccLoadPublicKeyAssetPlaintext(BadArgument8L)=", Status);
    Size = 100;

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * test_AsymEccLoadDomain
 *
 * This test helper function load the ECC domain (curve) parameters.
 */
int
test_AsymEccLoadDomain(
        const TestVector_ECC_Curve_Rec_t * Curve_p,
        ValAssetId_t * DomainAssetId_p,
        bool ftestExport)
{
    uint8_t * AssociatedData_p;
    ValSize_t AssociatedDataSize = strlen(g_ValTestAssociatedData_p);
    ValStatus_t Status;
    ValAsymECDomainParam_t Domain;
    ValAssetId_t RootAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t KEKAssetId = VAL_ASSETID_INVALID;

    AssociatedData_p = (uint8_t *)SFZUTF_MALLOC(AssociatedDataSize);
    fail_if(AssociatedData_p == NULL, "Allocation ", (int)AssociatedDataSize);
    memcpy(AssociatedData_p, g_ValTestAssociatedData_p, AssociatedDataSize);

    if (ftestExport)
    {
        RootAssetId = val_AssetGetRootKey();
        if (RootAssetId != VAL_ASSETID_INVALID)
        {
            ValPolicyMask_t AssetPolicy;

            // Create and derive KEK Asset
            AssetPolicy = EIP130_ASSET_POLICY_SYM_WRAP | EIP130_ASSET_POLICY_SCAWAESSIV | EIP130_ASSET_POLICY_SCDIRENCDEC;
            if (!val_IsAccessSecure())
            {
                AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
            }
            Status = val_AssetAlloc(AssetPolicy, 64,
                                    VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                    &KEKAssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(KEK)=", Status);

            Status = val_AssetLoadDerive(KEKAssetId, RootAssetId,
                                         AssociatedData_p, AssociatedDataSize,
                                         false, false, NULL, 0, NULL, 0, 0);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadDerive(KEK)=", Status);
        }
    }

    /* Prepare domain parameters */
    Domain.Family                   = (ValAsymECCurveFamily_t)Curve_p->Family;
    Domain.ModulusSizeBits          = Curve_p->CurveBits;
    Domain.Modulus.Data_p           = sfzutf_discard_const(Curve_p->P_p);
    Domain.Modulus.ByteDataSize     = Curve_p->PLen;
    Domain.a.Data_p                 = sfzutf_discard_const(Curve_p->A_p);
    Domain.a.ByteDataSize           = Curve_p->ALen;
    Domain.b.Data_p                 = sfzutf_discard_const(Curve_p->B_p);
    Domain.b.ByteDataSize           = Curve_p->BLen;
    Domain.Order.Data_p             = sfzutf_discard_const(Curve_p->Order_p);
    Domain.Order.ByteDataSize       = Curve_p->OrderLen;
    Domain.BasePoint.x.Data_p       = sfzutf_discard_const(Curve_p->ECPointX_p);
    Domain.BasePoint.x.ByteDataSize = Curve_p->ECPointXLen;
    Domain.BasePoint.y.Data_p       = sfzutf_discard_const(Curve_p->ECPointY_p);
    Domain.BasePoint.y.ByteDataSize = Curve_p->ECPointYLen;
    Domain.CoFactor                 = Curve_p->Cofactor;

    /* Allocate and initialize the Domain paramter asset */
    Status = val_AsymEccAllocDomainAsset(Domain.ModulusSizeBits, DomainAssetId_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccAllocDomainAsset()=", Status);

    if (KEKAssetId != VAL_ASSETID_INVALID)
    {
        uint8_t * KeyBlob_p;
        ValSize_t KeyBlobSize = 0;

        Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, *DomainAssetId_p,
                                                     KEKAssetId,
                                                     AssociatedData_p, AssociatedDataSize,
                                                     AssociatedData_p, &KeyBlobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadDomainAssetPlaintext()=", Status);

        KeyBlobSize = 0;
        Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, *DomainAssetId_p,
                                                     KEKAssetId,
                                                     AssociatedData_p, AssociatedDataSize,
                                                     NULL, &KeyBlobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_AsymEccLoadDomainAssetPlaintext()=", Status);

        KeyBlob_p = (uint8_t *)SFZUTF_MALLOC(KeyBlobSize);
        fail_if(KeyBlob_p == NULL, "Allocation ", (int)KeyBlobSize);

        Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, *DomainAssetId_p,
                                                     KEKAssetId,
                                                     AssociatedData_p, AssociatedDataSize,
                                                     KeyBlob_p, &KeyBlobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadDomainAssetPlaintext()=", Status);

        SFZUTF_FREE(KeyBlob_p);

        // Release the involved Assets
        Status = val_AssetFree(KEKAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(KEK)=", Status);
    }
    else
    {
        Status = val_AsymEccLoadDomainAssetPlaintext(&Domain, *DomainAssetId_p,
                                                     VAL_ASSETID_INVALID,
                                                     NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccLoadDomainAssetPlaintext()=", Status);
    }

    SFZUTF_FREE(AssociatedData_p);

    return END_TEST_SUCCES;
}

/* end of file valtest_asym_ecc_common.c */
