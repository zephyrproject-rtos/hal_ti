/* valtest_asym_sm2.c
 *
 * Description: SM2 tests
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
#include "valtest_asym_ecc_common.h"

/* Test vectors. */
#include "testvectors_ecdsa.h"


#ifdef VALTEST_ASYM_SM2
static int
test_AsymSm2LoadDomain(
    TestVector_ECC_Curve_t Curve_p,
    ValAssetId_t * DomainAssetId_p,
    ValAsymECDomainParam_t * Domain_p)
{
    ValStatus_t Status;
    ValAsymECDomainParam_t LocalDomain;
    ValAsymECDomainParam_t * LocalDomain_p = NULL;

    if ((DomainAssetId_p == NULL) && (Domain_p == NULL))
    {
        return END_TEST_FAIL;
    }

    if (DomainAssetId_p != NULL)
    {
        /* Load curve parameters into Asset Store */
        LocalDomain_p = &LocalDomain;
        Status = val_AsymEccAllocDomainAsset(Curve_p->CurveBits, DomainAssetId_p);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccAllocDomainAsset()=", Status);
    }

    if (Domain_p != NULL)
    {
        /* Load curve parameters into ValAsymECDomainParam_t struct */
        LocalDomain_p = Domain_p;
    }

    /* Common part - prepare domain parameters */
    LocalDomain_p->Family = (ValAsymECCurveFamily_t)Curve_p->Family;
    LocalDomain_p->ModulusSizeBits = Curve_p->CurveBits;
    LocalDomain_p->Modulus.Data_p = sfzutf_discard_const(Curve_p->P_p);
    LocalDomain_p->Modulus.ByteDataSize = Curve_p->PLen;
    LocalDomain_p->a.Data_p = sfzutf_discard_const(Curve_p->A_p);
    LocalDomain_p->a.ByteDataSize = Curve_p->ALen;
    LocalDomain_p->b.Data_p = sfzutf_discard_const(Curve_p->B_p);
    LocalDomain_p->b.ByteDataSize = Curve_p->BLen;
    LocalDomain_p->Order.Data_p = sfzutf_discard_const(Curve_p->Order_p);
    LocalDomain_p->Order.ByteDataSize = Curve_p->OrderLen;
    LocalDomain_p->BasePoint.x.Data_p = sfzutf_discard_const(Curve_p->ECPointX_p);
    LocalDomain_p->BasePoint.x.ByteDataSize = Curve_p->ECPointXLen;
    LocalDomain_p->BasePoint.y.Data_p = sfzutf_discard_const(Curve_p->ECPointY_p);
    LocalDomain_p->BasePoint.y.ByteDataSize = Curve_p->ECPointYLen;
    LocalDomain_p->CoFactor = Curve_p->Cofactor;

    if (DomainAssetId_p != NULL)
    {
        Status = val_AsymEccLoadDomainAssetPlaintext(LocalDomain_p,
                                                     *DomainAssetId_p,
                                                     VAL_ASSETID_INVALID,
                                                     NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymEccLoadDomainAssetPlaintext()=", Status);
    }

    return END_TEST_SUCCES;
}


static int
test_AsymSm2LoadPrivateKey(
    /* input */
    ValAssetId_t DomainAssetId,
    ValAsymECCurveFamily_t Family,
    const uint8_t * PrivateKey_p,
    uint32_t PrivateKeyLen,
    ValSymAlgo_t HashAlgo,
    /* output */
    ValAsymKey_t * PrivateKeyOut_p,
    ValAsymBigInt_t * PrivateKeyData_p)
{
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAsymBigInt_t LocalBigInt;
    ValAsymBigInt_t * LocalBigInt_p = &LocalBigInt;
    ValStatus_t Status;

    if (PrivateKeyData_p != NULL)
    {
        /* Use external structure */
        LocalBigInt_p = PrivateKeyData_p;
    }

    LocalBigInt_p->Data_p = sfzutf_discard_const(PrivateKey_p);
    LocalBigInt_p->ByteDataSize = PrivateKeyLen;

    if (PrivateKeyOut_p != NULL)
    {
        /* Allocate private key asset */
        Status = val_AsymSm2dsaAllocPrivateKeyAsset(256, false, false,
                                                    &PrivateKeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymSm2dsaAllocPrivateKeyAsset()=", Status);

        /* Initialize private key structure */
        Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                                 256, HashAlgo, PrivateKeyOut_p);
        fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

        /* Initialize the private key asset */
        Status = val_AsymEccLoadPrivateKeyAssetPlaintext(LocalBigInt_p,
                                                         Family, 256,
                                                         PrivateKeyAssetId,
                                                         VAL_ASSETID_INVALID,
                                                         NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);
    }

    return END_TEST_SUCCES;
}


static int
test_AsymSm2LoadPublicKey(
    /* input */
    ValAssetId_t DomainAssetId,
    ValAsymECCurveFamily_t Family,
    const uint8_t * PublicKeyX_p,
    uint32_t PublicKeyXLen,
    const uint8_t * PublicKeyY_p,
    uint32_t PublicKeyYLen,
    ValSymAlgo_t HashAlgo,
    /* output */
    ValAsymKey_t * PublicKeyOut_p,
    ValAsymECCPoint_t * PublicKeyData_p)
{
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValAsymECCPoint_t LocalECCPoint;
    ValAsymECCPoint_t * LocalECCPoint_p = &LocalECCPoint;
    ValStatus_t Status;

    if (PublicKeyData_p != NULL)
    {
        /* Use external structure */
        LocalECCPoint_p = PublicKeyData_p;
    }

    LocalECCPoint_p->x.Data_p = sfzutf_discard_const(PublicKeyX_p);
    LocalECCPoint_p->x.ByteDataSize = PublicKeyXLen;
    LocalECCPoint_p->y.Data_p = sfzutf_discard_const(PublicKeyY_p);
    LocalECCPoint_p->y.ByteDataSize = PublicKeyYLen;

    if (PublicKeyOut_p != NULL)
    {
        /* Allocate public key asset */
        Status = val_AsymSm2dsaAllocPublicKeyAsset(256, false, false,
                                                   &PublicKeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymSm2dsaAllocPublicKeyAsset()=", Status);

        /* Initialize public key structure */
        Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                                 256, HashAlgo, PublicKeyOut_p);
        fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

        /* Initialize the public key asset */
        Status = val_AsymEccLoadPublicKeyAssetPlaintext(LocalECCPoint_p,
                                                        Family, 256,
                                                        PublicKeyAssetId,
                                                        VAL_ASSETID_INVALID,
                                                        NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);
    }

    return END_TEST_SUCCES;
}


#ifdef EIP130_ENABLE_EXPLICITDIGEST
static int
test_CreateExplicitDigest(const uint8_t * Message_p,
                          ValSize_t MessageLen,
                          uint8_t * ZA_p,
                          ValSize_t ZASize,
                          uint8_t * Digest_p,
                          ValSize_t * DigestLen_p)
{
    ValStatus_t Status = 0;
    ValSymContextPtr_t HashContext_p = NULL;
    ValSize_t HashDataSize = 0;
    uint8_t * MessageData_p = NULL;

    if (MessageLen > (VAL_SIZE_MAX_DMA - (4 * VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE)))
    {
        HashDataSize = (VAL_SIZE_MAX_DMA - (4 * VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE));
    }
    else if (MessageLen > VAL_SYM_ALGO_HASH_BLOCK_SIZE)
    {
        HashDataSize = MessageLen;
    }
    else
    {
        HashDataSize = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
    }

    /* Allocate hash context */
    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SM3,
                          VAL_SYM_MODE_NONE, false,
                          &HashContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    /* Create temporary buffer for ZA + message */
    MessageData_p = SFZUTF_MALLOC(HashDataSize);
    fail_if(MessageData_p == NULL, "SFZUTF_MALLOC()=", Status);

    /* Copy ZA to temporary buffer */
    memcpy(MessageData_p, ZA_p, ZASize);

    HashDataSize = MessageLen + ZASize;

    if (HashDataSize > VAL_SYM_ALGO_HASH_BLOCK_SIZE)
    {
        /* Copy first part of HashMessage into temporary buffer */
        memcpy(&MessageData_p[ZASize], Message_p,
                (VAL_SYM_ALGO_HASH_BLOCK_SIZE - ZASize));

        /* Do HashUpdate operation for the first block */
        Status = val_SymHashUpdate(HashContext_p,
                                   MessageData_p, VAL_SYM_ALGO_HASH_BLOCK_SIZE);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate(1)=", Status);

        Message_p   += (VAL_SYM_ALGO_HASH_BLOCK_SIZE - ZASize);
        HashDataSize -= VAL_SYM_ALGO_HASH_BLOCK_SIZE;

        /* Hash the rest of the data in blocks of 64 bytes */
        while (HashDataSize > VAL_SYM_ALGO_HASH_BLOCK_SIZE)
        {
            ValSize_t Size = HashDataSize;
            if (HashDataSize > VAL_SYM_ALGO_HASH_BLOCK_SIZE)
            {
                /* Limit the size to maximum block size */
                Size = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
            }

            /* Prevent possible memory alignment issue */
            memcpy(MessageData_p, Message_p, Size);

            Status = val_SymHashUpdate(HashContext_p,
                                       MessageData_p, Size);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate(2)=", Status);

            /* Adjust references */
            Message_p    += Size;
            HashDataSize -= Size;
        }
        /* Copy last part of message to temporary buffer for final hash */
        memcpy(MessageData_p, Message_p, HashDataSize);
    }
    else
    {
        /* Append rest of message to temporary buffer with ZA */
        memcpy(&MessageData_p[ZASize], Message_p, MessageLen);
    }

    Status = val_SymHashFinal(HashContext_p,
                              MessageData_p, HashDataSize,
                              Digest_p, DigestLen_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal()=", Status);

    SFZUTF_FREE(MessageData_p);

    (void)val_SymRelease(HashContext_p);

    return END_TEST_SUCCES;
}
#endif


START_TEST (test_AsymSm2dsaSignVerifyVectors)
{
    uint32_t ndx;
    int Failed = 0;
    int rc;
    ValStatus_t Status;
    ValAsymECDomainParam_t Domain;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymECCPoint_t PublicKeyData;
    ValAsymSign_t Signature;
    uint8_t * Data_p = NULL;
    ValSize_t DataLen;
    uint8_t * ZA_p;
    ValSize_t ZA_Size;
    bool fExplicitDigest = false;
#ifdef EIP130_ENABLE_EXPLICITDIGEST
    fExplicitDigest = ((_i & 1) != 0);
#endif

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");
    unsupported_unless(valtest_IsSM3Supported(), "SM3 not supported");

    for (ndx = 0U; ; ndx++)
    {
        TestVector_SM2DSA_t tv_p = test_vectors_sm2dsa_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        /* Load domain parameters */
        rc = test_AsymSm2LoadDomain(tv_p->Curve_p, &DomainAssetId, &Domain);
        fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadDomain()=", rc);

        /* Load private key, only in asset store */
        rc = test_AsymSm2LoadPrivateKey(DomainAssetId,
                                        (ValAsymECCurveFamily_t)tv_p->Curve_p->Family,
                                        tv_p->PrivateKey_p,
                                        tv_p->PrivateKeyLen,
                                        VAL_SYM_ALGO_HASH_SM3,
                                        &PrivateKey, NULL);
        fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadPrivateKey()=", rc);

        /* Load public key, both in asset store and ECCPoint structure */
        rc = test_AsymSm2LoadPublicKey(DomainAssetId,
                                       (ValAsymECCurveFamily_t)tv_p->Curve_p->Family,
                                       tv_p->PublicKeyX_p,
                                       tv_p->PublicKeyXLen,
                                       tv_p->PublicKeyY_p,
                                       tv_p->PublicKeyYLen,
                                       VAL_SYM_ALGO_HASH_SM3,
                                       &PublicKey, &PublicKeyData);
        fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadPublicKey()=", rc);

        /* Prepare Message that needs to be signed */
        DataLen = tv_p->MessageLen;
        Data_p = (uint8_t *)SFZUTF_MALLOC(DataLen);
        fail_if(Data_p == NULL, "Allocation ", (int)DataLen);
        memcpy(Data_p, tv_p->Message_p, DataLen);

        /* Allocate space for Signature */
        Signature.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);
        Signature.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);
        Signature.r.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.r.ByteDataSize);
        Signature.s.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.s.ByteDataSize);
        fail_if(Signature.r.Data_p == NULL, "Allocation ", Signature.r.ByteDataSize);
        fail_if(Signature.s.Data_p == NULL, "Allocation ", Signature.s.ByteDataSize);

        /* Calculate ZA */
        ZA_Size = 32;
        ZA_p = (uint8_t *)SFZUTF_MALLOC(ZA_Size);
        fail_if(ZA_p == NULL, "Allocation ", (int)ZA_Size);

        Status = val_AsymSm2dsaCalculateZA(tv_p->UserIdentity_p,
                                           tv_p->UserIdentityLen,
                                           &Domain,
                                           &PublicKeyData,
                                           ZA_p, &ZA_Size);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaCalculateZA()=", Status);

#ifdef EIP130_ENABLE_EXPLICITDIGEST
        if (fExplicitDigest)
        {
            /* Resize reserved memory for Digest if necessary */
            DataLen = (tv_p->HashBits/8);
            Data_p = SFZUTF_REALLOC(Data_p, DataLen);
            rc = test_CreateExplicitDigest(tv_p->Message_p,
                                           tv_p->MessageLen,
                                           ZA_p, ZA_Size,
                                           Data_p, &DataLen);
            fail_if(rc != END_TEST_SUCCES, "test_CreateExplicitDigest()=", rc);
        }
#endif

        /* First test 'verify' operation with reference
           public key and signature */
        memcpy(Signature.r.Data_p, tv_p->SignatureR_p, Signature.r.ByteDataSize);
        memcpy(Signature.s.Data_p, tv_p->SignatureS_p, Signature.s.ByteDataSize);
        Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaVerify()=", Status);

        /* Test 'sign' + 'verify' operations */
        memset(Signature.r.Data_p, 0, Signature.r.ByteDataSize);
        memset(Signature.s.Data_p, 0, Signature.s.ByteDataSize);

        /* Sign the message */
        Status = val_AsymSm2dsaSign(&PrivateKey, &Signature,
                                    ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaSign()=", Status);

        /* Check signature size */
        fail_if(Signature.r.ByteDataSize != tv_p->SignatureRLen,
                "Signature.R size mismatch ", Signature.r.ByteDataSize);
        fail_if(Signature.s.ByteDataSize != tv_p->SignatureSLen,
                "Signature.S size mismatch ", Signature.s.ByteDataSize);

        /* Verify signature with public key */
        Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaVerify()=", Status);

        /************* NEGATIVE TESTS **************/
        /* Sign operation with public key */
        Status = val_AsymSm2dsaSign(&PublicKey, &Signature,
                                    ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET,
                "val_AsymSm2dsaSign(wrong key)=", Status);

        /* Verify operation with private key */
        Status = val_AsymSm2dsaVerify(&PrivateKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET,
                "val_AsymSm2dsaVerify(wrong key)=", Status);

        /* Verify operation with wrong signature */
        Signature.r.Data_p[3] ^= 0xA5;
        Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR,
                "val_AsymSm2dsaVerify(wrong signature)=", Status);
        Signature.r.Data_p[3] ^= 0xA5;

        /* Verify operation with wrong message */
        Data_p[0] ^= 0xA5;
        Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
        fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR,
                "val_AsymSm2dsaVerify(wrong message)=", Status);
        Data_p[0] ^= 0xA5;

        /* Verify operation with wrong message length */
        DataLen -= 1;
        Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                      ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
#ifdef EIP130_ENABLE_EXPLICITDIGEST
        if (fExplicitDigest)
        {
            fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_LENGTH,
                    "val_AsymSm2dsaVerify(wrong msg len)=", Status);
        }
        else
        {
            fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR,
                    "val_AsymSm2dsaVerify(wrong msg len)=", Status);
        }
#else
        fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR,
                "val_AsymSm2dsaVerify(wrong msg len)=", Status);
#endif
        DataLen += 1;

        /* Verify operation with wrong ZA (or Identity) */
        if (!fExplicitDigest)
        {
            ZA_p[5] ^= 0xA5;
            Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                          ZA_p, Data_p, DataLen, NULL, fExplicitDigest);
            fail_if(val_CheckFunctionResult(Status) != VAL_VERIFY_ERROR,
                    "val_AsymSm2dsaVerify(wrong ZA)=", Status);
            ZA_p[5] ^= 0xA5;
        }

        /* Clean-up */
        SFZUTF_FREE(Signature.r.Data_p);
        SFZUTF_FREE(Signature.s.Data_p);
        SFZUTF_FREE(ZA_p);
        SFZUTF_FREE(Data_p);

        Status = val_AssetFree(PrivateKey.KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
        Status = val_AssetFree(PublicKey.KeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
        Status = val_AssetFree(DomainAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

        test_vectors_sm2dsa_release(tv_p);
    }

    fail_if(Failed, "#wrong tests", Failed);
}
END_TEST


static int
test_AsymSm2PrecalculateHash(uint8_t *ZA_p,
                             uint8_t *Message_p,
                             uint32_t MessageLen,
                             bool FinalHash,
                             uint8_t **DigestOrLastBlock_p,
                             uint32_t *DigestOrLastBlockSize_p,
                             ValSymContextPtr_t *HashContext_pp)
{
    ValStatus_t Status;
    uint8_t * Data_p;
    ValSize_t DataLen;
    uint8_t * TempBuff_p = NULL;

    if ((DigestOrLastBlock_p == NULL) ||
        (DigestOrLastBlockSize_p == NULL) ||
        (HashContext_pp == NULL))
    {
        return END_TEST_FAIL;
    }

    if (MessageLen > (VAL_SIZE_MAX_DMA - (4 * VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE)))
    {
        DataLen = (VAL_SIZE_MAX_DMA - (4 * VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE));
    }
    else
    {
        if (MessageLen < 32)
        {
            return END_TEST_FAIL;
        }
        if (MessageLen > VAL_SYM_ALGO_HASH_BLOCK_SIZE)
        {
            DataLen = MessageLen;
        }
        else
        {
            DataLen = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
        }
    }
    TempBuff_p = (uint8_t *)SFZUTF_MALLOC(DataLen);
    fail_if(TempBuff_p == NULL, "Allocation ", DataLen);

    /* Copy ZA_p array and first part of Message_p */
    memcpy(TempBuff_p, ZA_p, 32);
    memcpy(&TempBuff_p[32], Message_p, 32);
    Data_p = &Message_p[32];
    DataLen = MessageLen - 32;

    /* Allocate hash context */
    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SM3, VAL_SYM_MODE_NONE, false, HashContext_pp);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    /* Do HashUpdate operation for the first block */
    Status = val_SymHashUpdate(*HashContext_pp, TempBuff_p, VAL_SYM_ALGO_HASH_BLOCK_SIZE);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate()=", Status);

    /* Perform a partial hash operation as long as the remaining size
     * is bigger than compleate Hash block size */
    while (DataLen > 64)
    {
        ValSize_t PacketSize;

        /* Reduce number of hash update operations */
        if (DataLen > 4096)
        {
            PacketSize = 4096;
        }
        else if (DataLen > 512)
        {
            PacketSize = 512;
        }
        else
        {
            PacketSize = 64;
        }

        // Prevent possible memory alignment issue
        memcpy(TempBuff_p, Data_p, PacketSize);

        Status = val_SymHashUpdate(*HashContext_pp, TempBuff_p, PacketSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate()=", Status);

        /* Adjust references */
        Data_p += PacketSize;
        DataLen -= PacketSize;
    }

    if (FinalHash)
    {
        uint8_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
        ValSize_t DigestSize = VAL_SYM_ALGO_MAX_DIGEST_SIZE;

        // Prevent possible memory alignment issue
        memcpy(TempBuff_p, Data_p, DataLen);

        Status = val_SymHashFinal(*HashContext_pp, TempBuff_p, DataLen, Digest, &DigestSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal()=", Status);

        memcpy(*DigestOrLastBlock_p, Digest, DigestSize);

        (void)val_SymRelease(*HashContext_pp);
        *HashContext_pp = NULL;
    }
    else
    {
        *DigestOrLastBlock_p = Data_p;
    }
    *DigestOrLastBlockSize_p = (uint32_t)DataLen;

    SFZUTF_FREE(TempBuff_p);

    return END_TEST_SUCCES;
}


START_TEST (test_AsymSm2dsaSignVerifyLongMessage)
{
    TestVector_SM2DSA_t tv_p;
    ValAsymECDomainParam_t Domain;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    ValAsymECCPoint_t PublicKeyData;
    ValAsymSign_t Signature;
    ValStatus_t Status;
    uint32_t MessageLen = 20 * 1024;
    uint8_t * Message_p;
    ValSize_t ZA_Size = 32;
    uint8_t * ZA_p;
    int rc;
    ValSymContextPtr_t HashContext_p = NULL;
    uint8_t * HashBuff_p;
    uint32_t HashSize;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");
    unsupported_unless(valtest_IsSM3Supported(), "SM3 not supported");

    tv_p = test_vectors_sm2dsa_get(0U);

    /* Allocate space for a message longer than 4096B */
    Message_p = (uint8_t *)SFZUTF_MALLOC(MessageLen);
    fail_if(Message_p == NULL, "Allocation ", MessageLen);
    memset(Message_p, 'a', MessageLen);

    /* Load domain */
    rc = test_AsymSm2LoadDomain(tv_p->Curve_p, &DomainAssetId, &Domain);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadDomain()=", rc);

    /* Load private key, only in asset store */
    rc = test_AsymSm2LoadPrivateKey(DomainAssetId,
                                    (ValAsymECCurveFamily_t)tv_p->Curve_p->Family,
                                    tv_p->PrivateKey_p,
                                    tv_p->PrivateKeyLen,
                                    VAL_SYM_ALGO_HASH_SM3,
                                    &PrivateKey, NULL);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadPrivateKey()=", rc);

    /* Load public key, both in asset store and ECCPoint structure */
    rc = test_AsymSm2LoadPublicKey(DomainAssetId,
                                   (ValAsymECCurveFamily_t)tv_p->Curve_p->Family,
                                   tv_p->PublicKeyX_p,
                                   tv_p->PublicKeyXLen,
                                   tv_p->PublicKeyY_p,
                                   tv_p->PublicKeyYLen,
                                   VAL_SYM_ALGO_HASH_SM3,
                                   &PublicKey, &PublicKeyData);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadPublicKey()=", rc);

    /* Allocate space for ZA, and calculate its value */
    ZA_p = (uint8_t *)SFZUTF_MALLOC(ZA_Size);
    fail_if(ZA_p == NULL, "Allocation ", (uint32_t)ZA_Size);
    Status = val_AsymSm2dsaCalculateZA(tv_p->UserIdentity_p,
                                       tv_p->UserIdentityLen,
                                       &Domain,
                                       &PublicKeyData,
                                       ZA_p, &ZA_Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaCalculateZA()=", Status);

    /* Allocate space for Signature */
    Signature.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);
    Signature.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);
    Signature.r.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.r.ByteDataSize);
    Signature.s.Data_p = (uint8_t *)SFZUTF_MALLOC(Signature.s.ByteDataSize);
    fail_if(Signature.r.Data_p == NULL, "Allocation ", Signature.r.ByteDataSize);
    fail_if(Signature.s.Data_p == NULL, "Allocation ", Signature.s.ByteDataSize);

    /* Sign the message */
    Status = val_AsymSm2dsaSign(&PrivateKey, &Signature,
                                ZA_p, Message_p, MessageLen, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaSign()=", Status);

    /* Verify signature with public key */
    Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                  ZA_p, Message_p, MessageLen, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaVerify()=", Status);

    /******************************************************
     * Precalculated e = SM3(ZA || Msg) tests             *
     * Used in two different ways:                        *
     * 1. Intermediate hash value, HashContext provided   *
     *    together with final block data pointer and size *
     * 2. Final hash value calculated and passed into the *
     *    sign and verify functions, HashContext is NULL  *
     ******************************************************/

    /* Sign the message, 'e' precalc, non-final */
    rc = test_AsymSm2PrecalculateHash(ZA_p, Message_p, MessageLen,
                                      false,
                                      &HashBuff_p, &HashSize,
                                      &HashContext_p);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2PrecalculateHash()=", rc);

    Status = val_AsymSm2dsaSign(&PrivateKey, &Signature,
                                NULL, HashBuff_p, HashSize, HashContext_p, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaSign()=", Status);

    if (HashContext_p != NULL)
    {
        (void)val_SymRelease(HashContext_p);
        HashContext_p = NULL;
    }

    /* Verify signature, 'e' precalc, non-final */
    rc = test_AsymSm2PrecalculateHash(ZA_p, Message_p, MessageLen,
                                      false,
                                      &HashBuff_p, &HashSize,
                                      &HashContext_p);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2PrecalculateHash()=", rc);

    Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                  NULL, HashBuff_p, HashSize, HashContext_p, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaVerify()=", Status);

    if (HashContext_p != NULL)
    {
        (void)val_SymRelease(HashContext_p);
        HashContext_p = NULL;
    }

    /* Sign the message, 'e' precalc, final hash */
    HashBuff_p = (uint8_t *)SFZUTF_MALLOC(32);
    rc = test_AsymSm2PrecalculateHash(ZA_p, Message_p, MessageLen,
                                      true,
                                      &HashBuff_p, &HashSize,
                                      &HashContext_p);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2PrecalculateHash()=", rc);

    Status = val_AsymSm2dsaSign(&PrivateKey, &Signature,
                                NULL, HashBuff_p, HashSize, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaSign()=", Status);

    if (HashContext_p != NULL)
    {
        (void)val_SymRelease(HashContext_p);
        HashContext_p = NULL;
    }

    /* Verify signature, 'e' precalc, final hash */
    rc = test_AsymSm2PrecalculateHash(ZA_p, Message_p, MessageLen,
                                      true,
                                      &HashBuff_p, &HashSize,
                                      &HashContext_p);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2PrecalculateHash()=", rc);

    Status = val_AsymSm2dsaVerify(&PublicKey, &Signature,
                                  NULL, HashBuff_p, HashSize, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2dsaVerify()=", Status);

    if (HashContext_p != NULL)
    {
        (void)val_SymRelease(HashContext_p);
        HashContext_p = NULL;
    }

    /* Clean-up */
    SFZUTF_FREE(HashBuff_p);
    SFZUTF_FREE(Message_p);
    SFZUTF_FREE(ZA_p);
    SFZUTF_FREE(Signature.r.Data_p);
    SFZUTF_FREE(Signature.s.Data_p);

    Status = val_AssetFree(PrivateKey.KeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
    Status = val_AssetFree(PublicKey.KeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);
    Status = val_AssetFree(DomainAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree()=", Status);

    test_vectors_sm2dsa_release(tv_p);
}
END_TEST


typedef struct test_sm2_keypair {
    ValAssetId_t DomainAssetId;
    ValAsymKey_t PubKey;
    ValAsymKey_t PrivKey;
    ValAsymECCPoint_t PubPoint; /* data lives in PubPointData */
    ValOctetsInOut_t PrivKeyBlob[64];
    ValSize_t PrivKeyBlobSize;
    ValOctetsInOut_t PubPointData[64];
    ValSize_t PubPointDataSize;
} Sm2KeyPair;


static int
test_AsymSm2KexLoadPrivateKey(ValAssetId_t DomainAssetId,
                              ValAsymECCurveFamily_t Family,
                              const uint8_t * PrivateKey_p,
                              uint32_t PrivateKeyLen,
                              ValSymAlgo_t HashAlgo,
                              ValAsymKey_t * PrivateKeyOut_p,
                              ValAsymBigInt_t * PrivateKeyData_p,
                              const bool fAllowAny)
{
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAsymBigInt_t LocalBigInt;
    ValAsymBigInt_t * LocalBigInt_p = &LocalBigInt;
    ValStatus_t Status;

    if (PrivateKeyData_p != NULL)
    {
        /* Use external structure */
        LocalBigInt_p = PrivateKeyData_p;
    }

    LocalBigInt_p->Data_p = sfzutf_discard_const(PrivateKey_p);
    LocalBigInt_p->ByteDataSize = PrivateKeyLen;

    if (PrivateKeyOut_p != NULL)
    {
        /* Allocate private key asset */
        Status = val_AsymSm2kexAllocPrivateKeyAsset(256, false, true, fAllowAny,
                                                    &PrivateKeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymSm2dsaAllocPrivateKeyAsset()=", Status);

        /* Initialize private key structure */
        Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                                 256, HashAlgo, PrivateKeyOut_p);
        fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

        /* Initialize the private key asset */
        Status = val_AsymEccLoadPrivateKeyAssetPlaintext(LocalBigInt_p,
                                                         Family, 256,
                                                         PrivateKeyAssetId,
                                                         VAL_ASSETID_INVALID,
                                                         NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymEccLoadPrivateKeyAssetPlaintext()=", Status);
    }

    return END_TEST_SUCCES;
}


static int
test_AsymSm2KexLoadPublicKey(ValAssetId_t DomainAssetId,
                             ValAsymECCurveFamily_t Family,
                             const uint8_t * PublicKeyX_p,
                             uint32_t PublicKeyXLen,
                             const uint8_t * PublicKeyY_p,
                             uint32_t PublicKeyYLen,
                             ValSymAlgo_t HashAlgo,
                             ValAsymKey_t * PublicKeyOut_p,
                             ValAsymECCPoint_t * PublicKeyData_p)
{
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValAsymECCPoint_t LocalECCPoint;
    ValAsymECCPoint_t * LocalECCPoint_p = &LocalECCPoint;
    ValStatus_t Status;

    if (PublicKeyData_p != NULL)
    {
        /* Use external structure */
        LocalECCPoint_p = PublicKeyData_p;
    }

    LocalECCPoint_p->x.Data_p = sfzutf_discard_const(PublicKeyX_p);
    LocalECCPoint_p->x.ByteDataSize = PublicKeyXLen;
    LocalECCPoint_p->y.Data_p = sfzutf_discard_const(PublicKeyY_p);
    LocalECCPoint_p->y.ByteDataSize = PublicKeyYLen;

    if (PublicKeyOut_p != NULL)
    {
        /* Allocate public key asset */
        Status = val_AsymSm2kexAllocPublicKeyAsset(256, false, true,
                                                   &PublicKeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymSm2dsaAllocPublicKeyAsset()=", Status);

        /* Initialize public key structure */
        Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                                 256, HashAlgo, PublicKeyOut_p);
        fail_if(Status != VAL_SUCCESS,
                "val_AsymInitKey()=", Status);

        /* Initialize the public key asset */
        Status = val_AsymEccLoadPublicKeyAssetPlaintext(LocalECCPoint_p,
                                                        Family, 256,
                                                        PublicKeyAssetId,
                                                        VAL_ASSETID_INVALID,
                                                        NULL, 0, NULL, NULL);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS,
                "val_AsymEccLoadPublicKeyAssetPlaintext()=", Status);
    }

    return END_TEST_SUCCES;
}


static int
test_AsymSm2AllocGenerateKeyPair(ValAssetId_t DomainAssetId,
                                 ValAsymKey_t * PrivateKey_p,
                                 ValAsymKey_t * PublicKey_p,
                                 ValAsymECCPoint_t * PublicPoint_p,
                                 ValSize_t ModulusBits,
                                 const bool fAllowAny)
{
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValStatus_t Status;
    ValSymAlgo_t HashAlgorithm = VAL_SYM_ALGO_NONE;

    Status = val_AsymSm2kexAllocPrivateKeyAsset(ModulusBits, false, false, fAllowAny, &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId, ModulusBits, HashAlgorithm, PrivateKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    Status = val_AsymSm2kexAllocPublicKeyAsset(ModulusBits, false, false, &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId, ModulusBits, HashAlgorithm, PublicKey_p);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    /* Generate a key pair */
    Status = val_AsymEccGenKeyPair(PublicKey_p, PrivateKey_p,
                                   VAL_ASSETID_INVALID, NULL, 0,
                                   PublicPoint_p, NULL, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenKeyPair()=", Status);

    Status = val_AsymEccKeyCheck(PublicKey_p, PrivateKey_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);

    return END_TEST_SUCCES;
}


typedef struct AsymKeyPair {
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
} AsymKeyPair_t;

typedef struct Sm2Peer {
    AsymKeyPair_t StaticKeyPair;
    AsymKeyPair_t EphemeralKeyPair;
    ValAsymECCPoint_t StaticPoint;
    ValAsymECCPoint_t EphemeralPoint;
    uint8_t Identity[64];               /* this party's identifier */
    ValSize_t IdentitySize;
    uint8_t Z[64];                      /* calculated Z */
    ValSize_t ZSize;                    /* length of Z */
    uint8_t _PointStorage[4*((VAL_ASYM_ECP_MAX_BITS+7)/8)]; /* public key data (static, ephemeral) */
} Sm2Peer_t;


static void
test_Sm2PeerFree(Sm2Peer_t * pPeer)
{
    if (pPeer != NULL)
    {
        if (pPeer->EphemeralKeyPair.PublicKey.KeyAssetId)
        {
            (void)val_AssetFree(pPeer->EphemeralKeyPair.PublicKey.KeyAssetId);
        }
        if (pPeer->EphemeralKeyPair.PrivateKey.KeyAssetId)
        {
            (void)val_AssetFree(pPeer->EphemeralKeyPair.PrivateKey.KeyAssetId);
        }
        if (pPeer->StaticKeyPair.PublicKey.KeyAssetId)
        {
            (void)val_AssetFree(pPeer->StaticKeyPair.PublicKey.KeyAssetId);
        }
        if (pPeer->StaticKeyPair.PrivateKey.KeyAssetId)
        {
            (void)val_AssetFree(pPeer->StaticKeyPair.PrivateKey.KeyAssetId);
        }

        SFZUTF_FREE(pPeer);
    }
}


static void
test_Sm2PeerInit(Sm2Peer_t ** pPeer,
                 ValSize_t ModulusSizeBits)
{
    Sm2Peer_t * pNewPeer;

    pNewPeer = (Sm2Peer_t *)SFZUTF_MALLOC(sizeof(Sm2Peer_t));
    if (pNewPeer != NULL)
    {
        uint32_t KeySize = (uint32_t)((ModulusSizeBits + 7) / 8);

        *pPeer = pNewPeer;
        memset(pNewPeer, 0, sizeof(Sm2Peer_t));

        pNewPeer->EphemeralPoint.x.Data_p = &pNewPeer->_PointStorage[0 * KeySize];
        pNewPeer->EphemeralPoint.x.ByteDataSize = KeySize;
        pNewPeer->EphemeralPoint.y.Data_p = &pNewPeer->_PointStorage[1 * KeySize];
        pNewPeer->EphemeralPoint.y.ByteDataSize = KeySize;
        pNewPeer->StaticPoint.x.Data_p = &pNewPeer->_PointStorage[2 * KeySize];
        pNewPeer->StaticPoint.x.ByteDataSize = KeySize;
        pNewPeer->StaticPoint.y.Data_p = &pNewPeer->_PointStorage[3 * KeySize];
        pNewPeer->StaticPoint.y.ByteDataSize = KeySize;
        pNewPeer->ZSize = 32;           // This is alwayws 32, not KeySize;
    }
    else
    {
        *pPeer = NULL;
    }
}


static int
test_Sm2PeerCreateRandom(Sm2Peer_t * pPeer,
                         const uint8_t * pIdentity,
                         ValSize_t IdentitySize,
                         ValAssetId_t DomainAssetId,
                         ValAsymECDomainParam_t const * pDomain,
                         const bool fAllowAny)
{
    ValStatus_t rc;

    rc = test_AsymSm2AllocGenerateKeyPair(DomainAssetId,
                                          &pPeer->StaticKeyPair.PrivateKey,
                                          &pPeer->StaticKeyPair.PublicKey,
                                          &pPeer->StaticPoint,
                                          pDomain->ModulusSizeBits,
                                          fAllowAny);
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = test_AsymSm2AllocGenerateKeyPair(DomainAssetId,
                                              &pPeer->EphemeralKeyPair.PrivateKey,
                                              &pPeer->EphemeralKeyPair.PublicKey,
                                              &pPeer->EphemeralPoint,
                                              pDomain->ModulusSizeBits,
                                              fAllowAny);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymEccKeyCheck(&pPeer->StaticKeyPair.PublicKey,
                                 &pPeer->StaticKeyPair.PrivateKey);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymEccKeyCheck(&pPeer->EphemeralKeyPair.PublicKey,
                                 &pPeer->EphemeralKeyPair.PrivateKey);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymSm2dsaCalculateZA(pIdentity, (uint32_t)IdentitySize,
                                       pDomain, &pPeer->StaticPoint,
                                       pPeer->Z, &pPeer->ZSize);
    }
    return rc;
}


static void
copyin(struct TestVector_SM2KEX_KeyPair const * p,
       size_t n,
       uint8_t * priv,
       uint8_t * pubx,
       uint8_t * puby)
{
    memcpy(priv, p->PrivateKey_p, n);
    memcpy(pubx, p->PublicKeyX_p, n);
    memcpy(puby, p->PublicKeyY_p, n);
}


static int
test_Sm2PeerLoad(Sm2Peer_t * pPeer,
                 struct TestVector_SM2KEX_Peer const * pInfo,
                 ValAssetId_t DomainAssetId,
                 ValAsymECDomainParam_t const * pDomain,
                 const bool fAllowAny)
{
    uint8_t PrivateKey[((VAL_ASYM_ECP_MAX_BITS+7)/8)];
    uint8_t PublicKeyX[((VAL_ASYM_ECP_MAX_BITS+7)/8)];
    uint8_t PublicKeyY[((VAL_ASYM_ECP_MAX_BITS+7)/8)];
    uint32_t n = (uint32_t)((pDomain->ModulusSizeBits + 7) / 8);
    ValStatus_t rc;

    memcpy(pPeer->Identity, pInfo->UserIdentity_p, pInfo->UserIdentityLen);
    pPeer->IdentitySize = pInfo->UserIdentityLen;

    /* Values must be little-endian. */
    copyin(&pInfo->StaticKeyPair, n, PrivateKey, PublicKeyX, PublicKeyY);
    rc = test_AsymSm2KexLoadPrivateKey(DomainAssetId, pDomain->Family,
                                       PrivateKey, n,
                                       VAL_SYM_ALGO_HASH_SM3,
                                       &pPeer->StaticKeyPair.PrivateKey,
                                       NULL,
                                       fAllowAny);
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        /* Passing the last argument will return a pointer with the data
           set to point to the stack variables above.  Copy the data
           manually to retain storage. */
        rc = test_AsymSm2KexLoadPublicKey(DomainAssetId, pDomain->Family,
                                          PublicKeyX, n,
                                          PublicKeyY, n,
                                          VAL_SYM_ALGO_HASH_SM3,
                                          &pPeer->StaticKeyPair.PublicKey,
                                          NULL);

        memcpy(pPeer->StaticPoint.x.Data_p, PublicKeyX, n);
        memcpy(pPeer->StaticPoint.y.Data_p, PublicKeyY, n);
        pPeer->StaticPoint.x.ByteDataSize = n;
        pPeer->StaticPoint.y.ByteDataSize = n;
    }

    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        copyin(&pInfo->EphemeralKeyPair, n, PrivateKey, PublicKeyX, PublicKeyY);
        rc = test_AsymSm2KexLoadPrivateKey(DomainAssetId, pDomain->Family,
                                           PrivateKey, n,
                                           VAL_SYM_ALGO_HASH_SM3,
                                           &pPeer->EphemeralKeyPair.PrivateKey,
                                           NULL,
                                           fAllowAny);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = test_AsymSm2KexLoadPublicKey(DomainAssetId, pDomain->Family,
                                          PublicKeyX, n,
                                          PublicKeyY, n,
                                          VAL_SYM_ALGO_NONE,
                                          &pPeer->EphemeralKeyPair.PublicKey,
                                          NULL);

        memcpy(pPeer->EphemeralPoint.x.Data_p, PublicKeyX, n);
        memcpy(pPeer->EphemeralPoint.y.Data_p, PublicKeyY, n);
        pPeer->EphemeralPoint.x.ByteDataSize = n;
        pPeer->EphemeralPoint.y.ByteDataSize = n;
    }

    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymEccKeyCheck(&pPeer->StaticKeyPair.PublicKey,
                                 &pPeer->StaticKeyPair.PrivateKey);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymEccKeyCheck(&pPeer->EphemeralKeyPair.PublicKey,
                                 &pPeer->EphemeralKeyPair.PrivateKey);
    }
    if (val_CheckFunctionResult(rc) == VAL_SUCCESS)
    {
        rc = val_AsymSm2dsaCalculateZA(pPeer->Identity,
                                       (uint32_t)pPeer->IdentitySize,
                                       pDomain, &pPeer->StaticPoint,
                                       pPeer->Z, &pPeer->ZSize);
    }
    return rc;
}


static int
test_AsymSm2kexGenerate(uint32_t ndx,
                        bool fRandomKeys,
                        bool fSaveSharedSecret,
                        bool fDeriveAssets,
                        bool fAllowAny)
{
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAsymECDomainParam_t Domain;
    Sm2Peer_t * pAlice = NULL;
    Sm2Peer_t * pBob = NULL;

    ValStatus_t Status;
    TestVector_SM2KEX_t tv_p;
    int rc;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");
    unsupported_unless(valtest_IsSM3Supported(), "SM3 not supported");

    /* Get test vector */
    tv_p = test_vectors_sm2kex_get(ndx);

    /* Load domain parameters */
    rc = test_AsymSm2LoadDomain(tv_p->Curve_p, &DomainAssetId, &Domain);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadDomain()=", rc);

    /* Initialize the peers */
    test_Sm2PeerInit(&pAlice, tv_p->Curve_p->CurveBits);
    test_Sm2PeerInit(&pBob, tv_p->Curve_p->CurveBits);
    if ((pAlice == NULL) || (pBob == NULL))
    {
        if (DomainAssetId != VAL_ASSETID_INVALID)
        {
            (void)val_AssetFree(DomainAssetId);
        }
        test_Sm2PeerFree(pAlice);
        test_Sm2PeerFree(pBob);

        LOG_CRIT("Memory allocation error\n");
        return END_TEST_FAIL;
    }
    if (fRandomKeys)
    {
        rc = test_Sm2PeerCreateRandom(pAlice, (const uint8_t *)"ALICE", 5,
                                      DomainAssetId, &Domain, fAllowAny);
        fail_if(val_CheckFunctionResult(rc) != VAL_SUCCESS, "AliceKeys(Random)", rc);

        rc = test_Sm2PeerCreateRandom(pBob, (const uint8_t *)"BOB", 3,
                                      DomainAssetId, &Domain, fAllowAny);
        fail_if(val_CheckFunctionResult(rc) != VAL_SUCCESS, "BobKeys(Random)", rc);
    }
    else
    {
        rc = test_Sm2PeerLoad(pAlice, &tv_p->Peers[0], DomainAssetId, &Domain, fAllowAny);
        fail_if(val_CheckFunctionResult(rc) != VAL_SUCCESS, "AliceKeys(Vector)", rc);
        //Log_HexDump("pAlice->Z", 0, (uint8_t *)pAlice->Z, 32);
        if (tv_p->Peers[0].ZA != NULL)
        {
            fail_if(memcmp(pAlice->Z, tv_p->Peers[0].ZA, 32) != 0, "ZA wrong", 0);
        }

        rc = test_Sm2PeerLoad(pBob, &tv_p->Peers[1], DomainAssetId, &Domain, fAllowAny);
        fail_if(val_CheckFunctionResult(rc) != VAL_SUCCESS, "BobKeys(Vector)", rc);
        //Log_HexDump("pBob->Z", 0, (uint8_t *)pBob->Z, 32);
        if (tv_p->Peers[1].ZA != NULL)
        {
            fail_if(memcmp(pBob->Z, tv_p->Peers[1].ZA, 32) != 0, "ZB wrong", 0);
        }
    }

    if (fSaveSharedSecret)
    {
        uint8_t SharedSecret[2][2 * ((VAL_ASYM_ECP_MAX_BITS+7)/8)];
        ValSize_t SharedSecretSize = 2 * ((tv_p->Curve_p->CurveBits + 7) / 8);
        ValAssetId_t AssetList[2];
        ValPolicyMask_t AssetPolicy;

        /* Allocate public data assets for Shared Secret */
        AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE | EIP130_ASSET_POLICY_NODOMAIN |
                      EIP130_ASSET_POLICY_GENERICDATA | EIP130_ASSET_POLICY_PUBLICDATA;
        if (!val_IsAccessSecure())
        {
            AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicy, SharedSecretSize,
                                VAL_ASSET_LIFETIME_INFINITE, true, false, 0,
                                &AssetList[0]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(PubDataAlice)", Status);
        Status = val_AssetAlloc(AssetPolicy, SharedSecretSize,
                                VAL_ASSET_LIFETIME_INFINITE, true, false, 0,
                                &AssetList[1]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(PubDataBob)", Status);

        /* Test the shared secrets directly via public data assets */
        Status = val_AsymSm2kexGenSharedSecret(&pBob->EphemeralKeyPair.PublicKey,
                                               &pAlice->EphemeralKeyPair.PrivateKey,
                                               &pBob->StaticKeyPair.PublicKey,
                                               &pAlice->StaticKeyPair.PrivateKey,
                                               &pAlice->EphemeralPoint,
                                               true, NULL, 0,
                                               &AssetList[0], 1);
        if (fAllowAny)
        {
            /* shared secret is only allowed to be placed in a public data asset if
               the private key's ST_ANY policy bit is set (fAllowAny) */
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexGenSharedSecret(Alice1)=", Status);

            Status = val_AsymSm2kexGenSharedSecret(&pAlice->EphemeralKeyPair.PublicKey,
                                                   &pBob->EphemeralKeyPair.PrivateKey,
                                                   &pAlice->StaticKeyPair.PublicKey,
                                                   &pBob->StaticKeyPair.PrivateKey,
                                                   &pBob->EphemeralPoint,
                                                   true, NULL, 0,
                                                   &AssetList[1], 1);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexGenSharedSecret(Bob1)=", Status);

            memset(SharedSecret, 0, sizeof(SharedSecret));
            Status = val_PublicDataRead(AssetList[0], SharedSecret[0], SharedSecretSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "Asset data read", Status);
            Status = val_PublicDataRead(AssetList[1], SharedSecret[1], SharedSecretSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "Asset data read", Status);

            //Log_HexDump("SharedSecret[Alice]", 0, (uint8_t *)SharedSecret[0], SharedSecretSize);
            //Log_HexDump("SharedSecret[Bob]", 0, (uint8_t *)SharedSecret[1], SharedSecretSize);
            fail_if(memcmp(SharedSecret[0], SharedSecret[1], SharedSecretSize) != 0, "Compare shared secret", 0);
            if ((tv_p->Vx != NULL) && (tv_p->Vy != NULL))
            {
                fail_if(memcmp(SharedSecret[0], tv_p->Vx, (SharedSecretSize / 2)) != 0,
                        "Shared point x mismatch", 0);
                fail_if(memcmp(SharedSecret[0] + (SharedSecretSize / 2), tv_p->Vy, (SharedSecretSize / 2)) != 0,
                        "Shared point y mismatch", 0);
            }
        }
        else
        {
            fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ASSET, "val_AsymSm2kexGenSharedSecret(Alice1)=", Status);
        }

        (void)val_AssetFree(AssetList[0]);
        (void)val_AssetFree(AssetList[1]);

        /* no need to test code below twice */
        if (!fAllowAny)
        {
            test_Sm2PeerFree(pAlice);
            test_Sm2PeerFree(pBob);
            return END_TEST_SUCCES;
        }
    }

    if (fDeriveAssets)
    {
        static char Message[] = "Some data that is used to check.";
        ValSymContextPtr_t AliceSymContext_p = NULL;
        ValSymContextPtr_t BobSymContext_p = NULL;
        ValOctetsOut_t AliceMac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
        ValOctetsOut_t BobMac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
        ValAssetId_t AssetList[4];
        ValPolicyMask_t AssetPolicySM4;
        ValPolicyMask_t AssetPolicySM3;
        ValSize_t DataSize = sizeof(Message) - 1;
        ValSize_t AliceSize;
        ValSize_t BobSize;
        ValSize_t ZAZB_Size = 64;
        uint8_t * ZAZB_p = NULL;
        uint8_t * Data_p = NULL;
        uint8_t * OutputAlice_p = NULL;
        uint8_t * OutputBob_p = NULL;

        /* Allocate assets for SM4-CBC key and SM3 HMAC key */
        AssetPolicySM4 = EIP130_ASSET_POLICY_SYM_CIPHERBULK | EIP130_ASSET_POLICY_SCACSM4 |
                         EIP130_ASSET_POLICY_SCMCBCBC | EIP130_ASSET_POLICY_SCDIRENCGEN;
        AssetPolicySM3 = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_SCAHSM3 |
                         EIP130_ASSET_POLICY_SCDIRENCGEN;
        if (!val_IsAccessSecure())
        {
            AssetPolicySM4 |= EIP130_ASSET_POLICY_SOURCENONSECURE;
            AssetPolicySM3 |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }
        Status = val_AssetAlloc(AssetPolicySM4, 16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetList[0]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(SM4KeyAlice)=", Status);
        Status = val_AssetAlloc(AssetPolicySM3, 16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetList[1]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(SM3KeyAlice)=", Status);
        Status = val_AssetAlloc(AssetPolicySM4, 16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetList[2]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(SM4KeyBob)=", Status);
        Status = val_AssetAlloc(AssetPolicySM3, 16,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                &AssetList[3]);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(SM3KeyBob)=", Status);

        /* Generate ZA || ZB that is used in the KDF. Use the key parameters
         * for the static keys, initiator first.  These MUST be set to zero
         * when using the SvShrdScrt flag.  We can calculate them nevertheless.
         * The public data must match the keys we created above (should use the
         * vector-supplied data instead.) */
        ZAZB_p = (uint8_t *)SFZUTF_MALLOC(ZAZB_Size);
        fail_if(ZAZB_p == NULL, "Memory allocation", 0);
        memset(ZAZB_p, 0, ZAZB_Size);
        memcpy(ZAZB_p, pAlice->Z, pAlice->ZSize);
        memcpy(ZAZB_p + pAlice->ZSize, pBob->Z, pBob->ZSize);
        //Log_HexDump("ZAZB_p", 0, ZAZB_p, ZAZB_Size);

        /* Test derived assets from the shared secrets */
        Status = val_AsymSm2kexGenSharedSecret(&pBob->EphemeralKeyPair.PublicKey,
                                               &pAlice->EphemeralKeyPair.PrivateKey,
                                               &pBob->StaticKeyPair.PublicKey,
                                               &pAlice->StaticKeyPair.PrivateKey,
                                               &pAlice->EphemeralPoint,
                                               false, ZAZB_p, ZAZB_Size,
                                               &AssetList[0], 2);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexGenSharedSecret(Alice2)=", Status);

        Status = val_AsymSm2kexGenSharedSecret(&pAlice->EphemeralKeyPair.PublicKey,
                                               &pBob->EphemeralKeyPair.PrivateKey,
                                               &pAlice->StaticKeyPair.PublicKey,
                                               &pBob->StaticKeyPair.PrivateKey,
                                               &pBob->EphemeralPoint,
                                               false, ZAZB_p, ZAZB_Size,
                                               &AssetList[2], 2);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2kexGenSharedSecret(Bob2)=", Status);

        Data_p = (uint8_t *)SFZUTF_MALLOC(DataSize);
        fail_if(Data_p == NULL, "Allocation ", (int)DataSize);
        OutputAlice_p = (uint8_t *)SFZUTF_MALLOC(DataSize);
        fail_if(OutputAlice_p == NULL, "Allocation ", (int)DataSize);
        OutputBob_p = (uint8_t *)SFZUTF_MALLOC(DataSize);
        fail_if(OutputBob_p == NULL, "Allocation ", (int)DataSize);
        memcpy(Data_p, Message, DataSize);
        memset(OutputAlice_p, 0, DataSize);
        memset(OutputBob_p, 0, DataSize);

        /* Check the generated SM4 keys */
        Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_SM4, VAL_SYM_MODE_CIPHER_CBC, false, &AliceSymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc(Alice2C)=", Status);
        Status = val_SymAlloc(VAL_SYM_ALGO_CIPHER_SM4, VAL_SYM_MODE_CIPHER_CBC, false, &BobSymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc(Bob2C)=", Status);

        Status = val_SymInitKey(AliceSymContext_p, AssetList[0], NULL, 16);
        fail_if(Status != VAL_SUCCESS, "val_SymInitKey(Alice2C)=", Status);
        Status = val_SymCipherInitEncrypt(AliceSymContext_p);

        Status = val_SymInitKey(BobSymContext_p, AssetList[2], NULL, 16);
        fail_if(Status != VAL_SUCCESS, "val_SymInitKey(Bob2C)=", Status);
        Status = val_SymCipherInitEncrypt(BobSymContext_p);

        AliceSize = DataSize;
        Status = val_SymCipherFinal(AliceSymContext_p, Data_p, DataSize, OutputAlice_p, &AliceSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherFinal(Alice2C)=", Status);
        fail_if(AliceSize != DataSize, "", 0);

        BobSize = DataSize;
        Status = val_SymCipherFinal(BobSymContext_p, Data_p, DataSize, OutputBob_p, &BobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymCipherFinal(Bob2C)=", Status);
        fail_if(BobSize != DataSize, "", 0);
        //Log_HexDump("OutputAlice_p", 0, OutputAlice_p, AliceSize);
        //Log_HexDump("OutputBob_p", 0, OutputBob_p, BobSize);
        fail_if(memcmp(OutputAlice_p, OutputBob_p, DataSize) != 0, "", 0);

        (void)val_SymRelease(AliceSymContext_p);
        (void)val_SymRelease(BobSymContext_p);

        /* Check the generated SM3 keys */
        Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SM3, VAL_SYM_MODE_NONE, false, &AliceSymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc(Alice2H)=", Status);
        Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SM3, VAL_SYM_MODE_NONE, false, &BobSymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc(Bob2H)=", Status);

        Status = val_SymInitKey(AliceSymContext_p, AssetList[1], NULL, 16);
        fail_if(Status != VAL_SUCCESS, "val_SymInitKey(Alice2H)=", Status);

        Status = val_SymInitKey(BobSymContext_p, AssetList[3], NULL, 16);
        fail_if(Status != VAL_SUCCESS, "val_SymInitKey(Bob2H)=", Status);

        AliceSize = sizeof(AliceMac);
        Status = val_SymMacGenerate(AliceSymContext_p, Data_p, DataSize, AliceMac, &AliceSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacGenerate(Alice2H)=", Status);

        BobSize = sizeof(BobMac);
        Status = val_SymMacGenerate(BobSymContext_p, Data_p, DataSize, BobMac, &BobSize);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacGenerate(Bob2H)=", Status);

        (void)val_SymRelease(AliceSymContext_p);
        (void)val_SymRelease(BobSymContext_p);

        fail_if(AliceSize != BobSize, "", 0);
        //Log_HexDump("AliceMac", 0, (uint8_t *)AliceMac, AliceSize);
        //Log_HexDump("BobMac", 0, (uint8_t *)BobMac, BobSize);
        fail_if(memcmp(AliceMac, BobMac, AliceSize) != 0, "", 0);

        SFZUTF_FREE(OutputBob_p);
        SFZUTF_FREE(OutputAlice_p);
        SFZUTF_FREE(Data_p);
        SFZUTF_FREE(ZAZB_p);

        (void)val_AssetFree(AssetList[0]);
        (void)val_AssetFree(AssetList[1]);
        (void)val_AssetFree(AssetList[2]);
        (void)val_AssetFree(AssetList[3]);
    }

    /* Clean-up */
    if (DomainAssetId != VAL_ASSETID_INVALID)
    {
        (void)val_AssetFree(DomainAssetId);
    }
    test_Sm2PeerFree(pAlice);
    test_Sm2PeerFree(pBob);

    test_vectors_sm2kex_release(tv_p);

    return END_TEST_SUCCES;
}


static int
test_AsymSm2encWrapUnwrap(uint32_t ndx,
                          bool fAllowAny)
{
    int rc = 0;
    ValStatus_t Status;
    ValAssetId_t DomainAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PrivateKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t PublicKeyAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t WrapAssetId = VAL_ASSETID_INVALID;
    ValAssetId_t UnwrapAssetId = VAL_ASSETID_INVALID;
    ValSymAlgo_t HashAlgorithm = VAL_SYM_ALGO_HASH_SM3;
    ValAsymECDomainParam_t Domain;
    ValAsymKey_t PrivateKey;
    ValAsymKey_t PublicKey;
    uint8_t * WrappedData_p = NULL;
    ValSize_t WrappedDataSize;
    ValPolicyMask_t AssetPolicy;
    TestVector_SM2KEX_t tv_p;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");
    unsupported_unless(valtest_IsSM3Supported(), "SM3 not supported");

    tv_p = test_vectors_sm2kex_get(ndx);

    /* load Domain params */
    rc = test_AsymSm2LoadDomain(tv_p->Curve_p, &DomainAssetId, &Domain);
    fail_if(rc != END_TEST_SUCCES, "test_AsymSm2LoadDomain()=", rc);

    /* Create keys, test_AsymSm2AllocGenerateKeyPair cannot be used for this! */
    Status = val_AsymSm2encAllocPrivateKeyAsset(tv_p->Curve_p->CurveBits,
                                                false, false, fAllowAny,
                                                &PrivateKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2encAllocPrivateKeyAsset()=", Status);

    Status = val_AsymInitKey(PrivateKeyAssetId, DomainAssetId,
                             tv_p->Curve_p->CurveBits, HashAlgorithm,
                             &PrivateKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    Status = val_AsymSm2encAllocPublicKeyAsset(tv_p->Curve_p->CurveBits,
                                               false, false, &PublicKeyAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2encAllocPublicKeyAsset()=", Status);

    Status = val_AsymInitKey(PublicKeyAssetId, DomainAssetId,
                             tv_p->Curve_p->CurveBits, HashAlgorithm,
                             &PublicKey);
    fail_if(Status != VAL_SUCCESS, "val_AsymInitKey()=", Status);

    Status = val_AsymEccGenKeyPair(&PublicKey, &PrivateKey,
                                   VAL_ASSETID_INVALID, NULL, 0,
                                   NULL, NULL, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccGenKeyPair()=", Status);

    Status = val_AsymEccKeyCheck(&PublicKey, &PrivateKey);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymEccKeyCheck()=", Status);

    /* create asset to wrap */
    AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_NODOMAIN |
                  EIP130_ASSET_POLICY_SCDIRENCGEN | EIP130_ASSET_POLICY_SCAHSHA512 |
                  EIP130_ASSET_POLICY_EXPORTABLE;
    Status = val_AssetAlloc(AssetPolicy, (256/8),
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &WrapAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc=(sm2WrapAssetId)", Status);

    Status = val_AssetLoadRandom(WrapAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadRandom=(sm2WrapAssetId)", Status);

    /* allocate memory for cryptogram */
    /* cryptogram = x&y points len + tag + datalen */
    WrappedDataSize = (2 * VAL_ASYM_DATA_SIZE_B2B(tv_p->Curve_p->CurveBits)) + 32 + (256/8);
    WrappedData_p = (uint8_t *)SFZUTF_MALLOC(WrappedDataSize+4); // + 4 for writetokenID
    fail_if(WrappedData_p == NULL, "Allocation ", (int)WrappedDataSize);

    /* sm2enc wrap */
    Status = val_AsymSm2EncWrap(&PublicKey, WrapAssetId, WrappedData_p, WrappedDataSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2EncWrap()=", Status);

    /* create asset for unwrap */
    if (fAllowAny)
    {
        /* create public data asset */
        AssetPolicy = EIP130_ASSET_POLICY_NONMODIFIABLE | EIP130_ASSET_POLICY_NODOMAIN |
                      EIP130_ASSET_POLICY_GENERICDATA | EIP130_ASSET_POLICY_PUBLICDATA;
    }
    else
    {
        AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH | EIP130_ASSET_POLICY_NODOMAIN |
                      EIP130_ASSET_POLICY_SCDIRENCDEC | EIP130_ASSET_POLICY_SCAHSHA512;
    }

    Status = val_AssetAlloc(AssetPolicy, (256/8),
                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                            &UnwrapAssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc=(sm2UnwrapAssetId)", Status);

    /* sm2enc unwrap */
    Status = val_AsymSm2EncUnwrap(&PrivateKey, UnwrapAssetId, WrappedData_p, WrappedDataSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymSm2EncUnwrap()=", Status);

    /* free assets and allocated memory*/
    SFZUTF_FREE(WrappedData_p);
    (void)val_AssetFree(WrapAssetId);
    (void)val_AssetFree(UnwrapAssetId);
    (void)val_AssetFree(PrivateKeyAssetId);
    (void)val_AssetFree(PublicKeyAssetId);

    test_vectors_sm2kex_release(tv_p);

    return END_TEST_SUCCES;
}

START_TEST (test_AsymSm2kexGenerateSharedSecret)
{
    int rc = test_AsymSm2kexGenerate(0, false, true, true, true);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST (test_AsymSm2kexGenerateSharedSecret_PublicData)
{
    int rc = test_AsymSm2kexGenerate(0, false, true, true, false);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST (test_AsymSm2kexFp192RandomKeys)
{
    int rc = test_AsymSm2kexGenerate(1, true, true, true, true);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST (test_AsymSm2enc)
{
    int rc = test_AsymSm2encWrapUnwrap(0, true);
    if (rc != END_TEST_SUCCES)
    {
        return rc;
    }
}
END_TEST


START_TEST (test_AsymSm2dsaArguments)
{
    ValStatus_t Status;
    ValAssetId_t AssetId = 0x5001;
    uint8_t Buffer[32] = { 0 };
    ValSize_t Size = 32;
    uint8_t * ZA = Buffer;
    uint8_t * Msg = Buffer;
    ValAsymKey_t Key;
    ValAsymSign_t Sign;
    ValSymContextPtr_t HashContext_p = NULL;

    /* ECC part */
    if (test_AsymEccArguments() != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }

    /* SM2DSA part */
    /* val_AsymSm2dsaAllocPrivateKeyAsset() */
    /* ModulusSizeBits below supported value */
    Status = val_AsymSm2dsaAllocPrivateKeyAsset(VAL_ASYM_ECP_MIN_BITS - 1,
                                                false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPrivateKeyAsset(low modulus size)=", Status);

    /* ModulusSizeBits above supported value */
    Status = val_AsymSm2dsaAllocPrivateKeyAsset(VAL_ASYM_ECP_MAX_BITS + 1,
                                                false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPrivateKeyAsset(high modulus size)=", Status);

    /* AssetId_p is NULL */
    Status = val_AsymSm2dsaAllocPrivateKeyAsset(256, false, false, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPrivateKeyAsset(null asset id ptr)=", Status);

    /* val_AsymSm2dsaAllocPublicKeyAsset() */
    /* ModulusSizeBits below supported value */
    Status = val_AsymSm2dsaAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS - 1,
                                               false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPublicKeyAsset(low modulus size)=", Status);

    /* ModulusSizeBits above supported value */
    Status = val_AsymSm2dsaAllocPublicKeyAsset(VAL_ASYM_ECP_MAX_BITS + 1,
                                               false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPublicKeyAsset(high modulus size)=", Status);

    /* AssetId_p is NULL */
    Status = val_AsymSm2dsaAllocPublicKeyAsset(256, false, false, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaAllocPublicKeyAsset(null asset id ptr)=", Status);

    /* val_AsymSm2dsaSign(), val_AsymSm2dsaVerify() */
    Sign.r.Data_p = Buffer;
    Sign.r.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);
    Sign.s.Data_p = Buffer;
    Sign.s.ByteDataSize = (uint32_t)VAL_ASYM_DATA_SIZE_B2B(256);

    /* KeyContext_p = NULL */
    Status = val_AsymSm2dsaSign(NULL, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AsymSm2dsaSign(null key ctx)=", Status);
    Status = val_AsymSm2dsaVerify(NULL, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_AsymSm2dsaVerify(null key ctx)=", Status);

    Key.KeyAssetId = VAL_ASSETID_INVALID;
    Key.DomainAssetId = AssetId;
    Key.ModulusSizeBits = 256;
    Key.HashAlgorithm = VAL_SYM_ALGO_HASH_SM3;

    /* Invalid KeyAssetId */
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(invalid key asset)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(invalid key asset)=", Status);
    Key.KeyAssetId = AssetId;

    /* Invalid DomainAssetId */
    Key.DomainAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(invalid domain asset)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(invalid domain asset)=", Status);
    Key.DomainAssetId = AssetId;

    /* ModulusSizeBits below supported value */
    Key.ModulusSizeBits = VAL_ASYM_ECP_MIN_BITS - 1;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(low key modulus size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(low key modulus size)=", Status);

    /* ModulusSizeBits above supported value */
    Key.ModulusSizeBits = VAL_ASYM_ECP_MAX_BITS + 1;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(high key modulus size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(high key modulus size)=", Status);
    Key.ModulusSizeBits = 256;

    /* Signature_p = NULL */
    Status = val_AsymSm2dsaSign(&Key, NULL, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(null signature)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, NULL, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(null signature)=", Status);

    /* Empty R sign array */
    Sign.r.Data_p = NULL;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(empty R)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(empty R)=", Status);
    Sign.r.Data_p = Buffer;

    /* Empty S sign array */
    Sign.s.Data_p = NULL;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(empty S)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(empty S)=", Status);
    Sign.s.Data_p = Buffer;

    /* R sign. part size less than expected */
    Sign.r.ByteDataSize -= 1;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(low R size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(low R size)=", Status);
    Sign.r.ByteDataSize += 1;

    /* S sign. part size less than expected */
    Sign.s.ByteDataSize -= 1;
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(low S size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(low S size)=", Status);
    Sign.s.ByteDataSize += 1;

    /* HashMessage_p = NULL */
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, NULL, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(null hash message)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, NULL, Size, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(null hash message)=", Status);

    /* HashMessageSize = 0 */
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, 0, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(zero hash msg size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, 0, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(zero hash msg size)=", Status);

    /* Both ZA_p and HashContext_p equal to NULL and Size != 32 */
    Status = val_AsymSm2dsaSign(&Key, &Sign, NULL, Msg, 100, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign('e' precalc, wrong msg size)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, NULL, Msg, 100, NULL, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify('e' precalc, wrong msg size)=", Status);

    /* Both ZA_p and HashContext_p NOT equal to NULL */
    HashContext_p = (ValSymContextPtr_t)SFZUTF_MALLOC(16);
    fail_if(HashContext_p == NULL, "SFZUTF_MALLOC()=", 0);
    Status = val_AsymSm2dsaSign(&Key, &Sign, ZA, Msg, Size, HashContext_p, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaSign(both ZA and HashCtx are defined)=", Status);
    Status = val_AsymSm2dsaVerify(&Key, &Sign, ZA, Msg, Size, HashContext_p, false);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2dsaVerify(both ZA and HashCtx are defined)=", Status);
    SFZUTF_FREE(HashContext_p);
}
END_TEST


START_TEST (test_AsymSm2kexArguments)
{
    ValStatus_t Status;
    ValAssetId_t AssetId = 0x5001;

    /* SM2KEX part */
    /* val_AsymSm2kexAllocPrivateKeyAsset() */
    /* ModulusSizeBits below supported value */
    Status = val_AsymSm2kexAllocPrivateKeyAsset(VAL_ASYM_ECP_MIN_BITS - 1,
                                                false, false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPrivateKeyAsset(low modulus size)=", Status);

    /* ModulusSizeBits above supported value */
    Status = val_AsymSm2kexAllocPrivateKeyAsset(VAL_ASYM_ECP_MAX_BITS + 1,
                                                false, false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPrivateKeyAsset(high modulus size)=", Status);

    /* AssetId_p is NULL */
    Status = val_AsymSm2kexAllocPrivateKeyAsset(256, false, false, false, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPrivateKeyAsset(null asset id ptr)=", Status);

    /* val_AsymSm2kexAllocPublicKeyAsset() */
    /* ModulusSizeBits below supported value */
    Status = val_AsymSm2kexAllocPublicKeyAsset(VAL_ASYM_ECP_MIN_BITS - 1,
                                               false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPublicKeyAsset(low modulus size)=", Status);

    /* ModulusSizeBits above supported value */
    Status = val_AsymSm2kexAllocPublicKeyAsset(VAL_ASYM_ECP_MAX_BITS + 1,
                                               false, false, &AssetId);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPublicKeyAsset(high modulus size)=", Status);

    /* AssetId_p is NULL */
    Status = val_AsymSm2kexAllocPublicKeyAsset(256, false, false, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2kexAllocPublicKeyAsset(null asset id ptr)=", Status);
}
END_TEST


START_TEST (test_AsymSm2encArguments)
{
    ValStatus_t Status;
    ValAssetId_t AssetId = 0x5001;
    ValAsymKey_t Key;
    uint8_t Buffer[32] = { 0 };
    ValSize_t Size = 32;
    Key.KeyAssetId = 0x5002;
    Key.DomainAssetId = 0x5003;
    Key.ModulusSizeBits = 256;

    Status = val_AsymSm2EncWrap(NULL, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(keyContext NULL)=", Status);

    Status = val_AsymSm2EncWrap(&Key, VAL_ASSETID_INVALID, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(invalid asset ID)=", Status);

    Status = val_AsymSm2EncWrap(&Key, AssetId, NULL, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(output buffer NULL)=", Status);

    Size = 0;
    Status = val_AsymSm2EncWrap(&Key, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(buffer size 0)=", Status);

    /* invalid key parameters */
    Size = 32;
    Key.KeyAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymSm2EncWrap(&Key, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(KeyAssetId invalid)=", Status);

    Key.KeyAssetId = 0x5002;
    Key.DomainAssetId = VAL_ASSETID_INVALID;
    Status = val_AsymSm2EncWrap(&Key, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(DomainAssetId invalid)=", Status);

    Key.KeyAssetId = 0x5002;
    Key.DomainAssetId = 0x5003;
    Key.ModulusSizeBits = 0;
    Status = val_AsymSm2EncWrap(&Key, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(ModulusSizeBits 0)=", Status);

    Key.ModulusSizeBits = 522;
    Status = val_AsymSm2EncWrap(&Key, AssetId, Buffer, Size);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT,
            "val_AsymSm2EncWrap(ModulusSizeBits > 521)=", Status);

    /* no need to test unwrap since it uses the same base function as wrap */
}
END_TEST
#endif


int
suite_add_test_AsymSm2(struct TestSuite * TestSuite_p)
{
#ifdef VALTEST_ASYM_SM2
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_SM2_Vectors");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
            goto FuncErrorReturn;
        }

#ifdef EIP130_ENABLE_EXPLICITDIGEST
        if (sfzutf_test_add_loop(TestCase_p, test_AsymSm2dsaSignVerifyVectors, 2)) goto FuncErrorReturn;
#else
        if (sfzutf_test_add(TestCase_p, test_AsymSm2dsaSignVerifyVectors)) goto FuncErrorReturn;
#endif
        if (sfzutf_test_add(TestCase_p, test_AsymSm2dsaSignVerifyLongMessage)) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymSm2kexGenerateSharedSecret)) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymSm2kexGenerateSharedSecret_PublicData)) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymSm2kexFp192RandomKeys)) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymSm2enc)) goto FuncErrorReturn;

        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_AsymSm2dsaArguments)) goto FuncErrorReturn;
            if (sfzutf_test_add(TestCase_p, test_AsymSm2kexArguments)) goto FuncErrorReturn;
            if (sfzutf_test_add(TestCase_p, test_AsymSm2encArguments)) goto FuncErrorReturn;
        }
        return 0;
    }
FuncErrorReturn:
    return -1;
#else
    IDENTIFIER_NOT_USED(TestSuite_p);
    return 0;
#endif
}

/* end of file valtest_asym_sm2.c */
