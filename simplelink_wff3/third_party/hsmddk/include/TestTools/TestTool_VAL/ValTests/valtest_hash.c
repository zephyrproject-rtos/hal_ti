/* valtest_hash.c
 *
 * Description: hash tests for MD5, SHA-1, SHA-2
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

/* Test vectors. */
#include "testvectors_hash.h"
#include "testvectors_hmac.h"

/* Foreach macro, for iterating through arrays.
   When reading the next/last element, reading (just) outside the array
   is prevented. */
#define FOREACH(var, index, array)                                      \
    for(((index) = 0),(var) = (array)[0];                               \
        ((index) < sizeof((array))/sizeof((array)[0]));                 \
        (var) = (++(index) < sizeof((array))/sizeof((array)[0]))?       \
            (array)[(index)]: (var))

/* Context for iterating over data in fragments.
   If frags_p == NULL, handle data unfragmented.
   If frags_p[i] == 0, re-use last fragment size.
   If frags_p[i] < 0, cycle back to first fragment size.
   If frags_p[i] > 0, use frags_p[i] as next fragment size. */
typedef struct
{
    const uint8_t * msg_p;
    size_t nbytes_done;
    size_t nbytes_left;
    const int * frags_p;
    size_t frags_ndx;
    size_t frag_len;
} MsgIter_t;


typedef struct
{
    ValSymAlgo_t Algorithm;
    ValPolicyMask_t AssetPolicy;
    ValSize_t BlockSize;
    ValSize_t MacSize;
    ValSize_t IntermediateSize;
    const int * frags_p;
} HMacAlgoInfo_t;

/*----------------------------------------------------------------------------
 * msgiter_init
 *
 * Initialize '*msgiter_p' for iterating over the message defined by
 * 'Msg_p' and 'MsgLen', using fragments as defined by '*Fragments_p'
 * if non-NULL.
 */
static void
msgiter_init(MsgIter_t *const msgiter_p,
             const uint8_t * Msg_p,
             size_t MsgLen,
             const int * Fragments_p)
{
    msgiter_p->msg_p = Msg_p;
    msgiter_p->nbytes_left = MsgLen;
    msgiter_p->nbytes_done = 0;
    msgiter_p->frags_p = Fragments_p;
    if ((Fragments_p == NULL) || (Fragments_p[0] <= 0))
    {
        msgiter_p->frag_len = MsgLen;
        msgiter_p->frags_ndx = 0;
    }
    else
    {
        msgiter_p->frag_len = MIN(MsgLen, (size_t)Fragments_p[0]);
        msgiter_p->frags_ndx = 1;
    }
}


/*----------------------------------------------------------------------------
 * msgiter_next
 *
 * Update '*msgiter_p' for the next message fragment.
 * Return false if the previous fragment was the last.
 */
static bool
msgiter_next(MsgIter_t * const msgiter_p)
{
    size_t fraglen = msgiter_p->frag_len;
    int next_fraglen;

    msgiter_p->nbytes_done += fraglen;
    msgiter_p->nbytes_left -= fraglen;
    if ((msgiter_p->nbytes_left == 0) ||
        (msgiter_p->frags_p == NULL) ||
        (fraglen == 0))
    {
        msgiter_p->frag_len = 0;
        return false;
    }

    next_fraglen = msgiter_p->frags_p[msgiter_p->frags_ndx];
    if (next_fraglen < 0)
    {
        msgiter_p->frags_ndx = 0;
        next_fraglen = msgiter_p->frags_p[0];
    }
    else if (next_fraglen == 0)
    {
        next_fraglen = (int)fraglen;
        msgiter_p->frags_ndx--;
    }

    msgiter_p->frag_len = MIN(msgiter_p->nbytes_left, (size_t)next_fraglen);
    msgiter_p->frags_ndx++;
    return true;
}

/**
 * @brief Get the hmac info object
 *
 * @param testvectorAlgo
 * @param info
 * @return int, -1=Unsupported,0=OK,1=Invalid algorithm
 */
static int
get_hmac_info(const TestVectors_HashAlgo_t testvectorAlgo,
              HMacAlgoInfo_t * info)
{
    info->frags_p = NULL;
    info->AssetPolicy = EIP130_ASSET_POLICY_SYM_MACHASH;
    switch (testvectorAlgo)
    {
    case TESTVECTORS_HASH_SHA160:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA1;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA1;
        info->MacSize = (160 / 8);
        info->IntermediateSize = (160 / 8);
        info->BlockSize = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
        break;
    case TESTVECTORS_HASH_SHA224:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA224;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA224;
        info->BlockSize = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
        info->MacSize = (224 / 8);
        info->IntermediateSize = (256 / 8);
        break;
    case TESTVECTORS_HASH_SHA256:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA256;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA256;
        info->BlockSize = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
        info->MacSize = (256 / 8);
        info->IntermediateSize = (256 / 8);
        break;
    case TESTVECTORS_HASH_SHA384:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA384;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA384;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE;
        info->MacSize = (384 / 8);
        info->IntermediateSize = (512 / 8);
        break;
    case TESTVECTORS_HASH_SHA512:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA512;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA512;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA512_BLOCK_SIZE;
        info->MacSize = (512 / 8);
        info->IntermediateSize = (512 / 8);
        break;
#ifdef VALTEST_SYM_ALGO_SHA3
    case TESTVECTORS_HASH_SHA3_224:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA3_224;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_224;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA3_224_BLOCK_SIZE;
        info->MacSize = (224 / 8);
        info->IntermediateSize = (1600 / 8);
        break;
    case TESTVECTORS_HASH_SHA3_256:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA3_256;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_256;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA3_256_BLOCK_SIZE;
        info->MacSize = (256 / 8);
        info->IntermediateSize = (1600 / 8);
        break;
    case TESTVECTORS_HASH_SHA3_384:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA3_384;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_384;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA3_384_BLOCK_SIZE;
        info->MacSize = (384 / 8);
        info->IntermediateSize = (1600 / 8);
        break;
    case TESTVECTORS_HASH_SHA3_512:
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SHA3_512;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSHA3_512;
        info->BlockSize = VAL_SYM_ALGO_HASH_SHA3_512_BLOCK_SIZE;
        info->MacSize = (512 / 8);
        info->IntermediateSize = (1600 / 8);
        break;
#endif
#ifdef VALTEST_SYM_ALGO_SM3
    case TESTVECTORS_HASH_SM3:
        if (!valtest_IsSM3Supported())
        {
            return -1;
        }
        info->Algorithm = VAL_SYM_ALGO_MAC_HMAC_SM3;
        info->AssetPolicy |= EIP130_ASSET_POLICY_SCAHSM3;
        info->BlockSize = VAL_SYM_ALGO_HASH_BLOCK_SIZE;
        info->MacSize = (256 / 8);
        info->IntermediateSize = (256 / 8);
        break;
#endif
    default:
        info->AssetPolicy = 0;
        info->Algorithm = 0;
        info->BlockSize = 0;
        info->MacSize = 0;
        info->IntermediateSize = 0;
        return 1;
    }
    return 0;
}


/*----------------------------------------------------------------------------
 * do_hash_test
 *
 * Helper function that runs a single hash test.
 */
static int
do_hash_test(uint32_t VectorIndex,
             const bool fReadWriteTemp,
             ValSymContextPtr_t SymContext_p,
             TestVector_HASH_t Vector_p,
             const int *const frags_p)
{
    ValStatus_t Status;
    ValOctetsOut_t Digest[VAL_SYM_ALGO_HASH_STATE_SIZE];
    ValSize_t DigestSize = 0;
    MsgIter_t msgit;

    memset(Digest, 0, sizeof(Digest));

    msgiter_init(&msgit, Vector_p->Msg_p, Vector_p->MsgLen, frags_p);
    do
    {
        uint8_t * InCopy_p;

        if (msgit.frag_len > 0)
        {
            InCopy_p = (uint8_t *)SFZUTF_MALLOC(msgit.frag_len);
            fail_if(InCopy_p == NULL, "Allocation ", (int)msgit.frag_len);
            memcpy(InCopy_p, (const uint8_t *)(msgit.msg_p + msgit.nbytes_done), msgit.frag_len);
        }
        else
        {
            InCopy_p = NULL;
        }

        if (msgit.nbytes_left == msgit.frag_len)
        {
            DigestSize = sizeof(Digest);
            Status = val_SymHashFinal(SymContext_p,
                                      InCopy_p, msgit.frag_len,
                                      Digest, &DigestSize);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal()=", Status);
        }
        else
        {
            Status = val_SymHashUpdate(SymContext_p, InCopy_p, msgit.frag_len);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashUpdate()=", Status);

            if (fReadWriteTemp)
            {
                ValSize_t TotalMessageLength;

                DigestSize = sizeof(Digest);
                Status = val_SymReadTokenTemp(SymContext_p,
                                              Digest, &DigestSize,
                                              &TotalMessageLength);
                fail_if(Status != VAL_SUCCESS, "val_SymReadTokenTemp()=", Status);

                Status = val_SymWriteTokenTemp(SymContext_p,
                                               Digest, DigestSize,
                                               TotalMessageLength);
                fail_if(Status != VAL_SUCCESS, "val_SymWriteTokenTemp()=", Status);
            }
        }

        if (InCopy_p != NULL)
        {
            SFZUTF_FREE(InCopy_p);
        }
    }
    while (msgiter_next(&msgit));

    fail_if(Vector_p->DigestLen != DigestSize,
            "Length mismatch ", (int)DigestSize);
    fail_if(memcmp(Digest, Vector_p->Digest_p, Vector_p->DigestLen) != 0,
            "", VectorIndex);

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * do_hmac_key_hash
 *
 * Helper function that hashes the key if needed.
 */
static bool
do_hmac_key_hash_if_needed(ValSymAlgo_t Algorithm,
                           const uint8_t * Key_p,
                           uint32_t KeySize,
                           uint8_t * HashedKey_p,
                           ValSize_t * HashedKeySize_p)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValSymAlgo_t HashAlgorithm;
    ValStatus_t Status;

    switch (Algorithm)
    {
    case VAL_SYM_ALGO_MAC_HMAC_SHA1:
    case VAL_SYM_ALGO_MAC_HMAC_SHA224:
    case VAL_SYM_ALGO_MAC_HMAC_SHA256:
#ifdef VALTEST_SYM_ALGO_SM3
    case VAL_SYM_ALGO_MAC_HMAC_SM3:
#endif
        if (KeySize <= VAL_SYM_ALGO_MAX_SHA2_MAC_KEY_SIZE)
        {
            return false;
        }
        break;
#ifdef VALTEST_SYM_ALGO_SHA512
    case VAL_SYM_ALGO_MAC_HMAC_SHA384:
    case VAL_SYM_ALGO_MAC_HMAC_SHA512:
        if (KeySize <= VAL_SYM_ALGO_MAX_SHA512_MAC_KEY_SIZE)
        {
            return false;
        }
        break;
#endif
    default:
        break;
    }

    switch (Algorithm)
    {
    case VAL_SYM_ALGO_MAC_HMAC_SHA1:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA1;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA224:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA224;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA256:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA256;
        break;
#ifdef VALTEST_SYM_ALGO_SHA512
    case VAL_SYM_ALGO_MAC_HMAC_SHA384:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA384;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA512:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA512;
        break;
#endif
#ifdef VALTEST_SYM_ALGO_SHA3
    case VAL_SYM_ALGO_MAC_HMAC_SHA3_224:
        if (KeySize <= VAL_SYM_ALGO_HASH_SHA3_224_BLOCK_SIZE)
        {
            return false;
        }
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA3_224;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA3_256:
        if (KeySize <= VAL_SYM_ALGO_HASH_SHA3_256_BLOCK_SIZE)
        {
            return false;
        }
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA3_256;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA3_384:
        if (KeySize <= VAL_SYM_ALGO_HASH_SHA3_384_BLOCK_SIZE)
        {
            return false;
        }
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA3_384;
        break;
    case VAL_SYM_ALGO_MAC_HMAC_SHA3_512:
        if (KeySize <= VAL_SYM_ALGO_HASH_SHA3_512_BLOCK_SIZE)
        {
            return false;
        }
        HashAlgorithm = VAL_SYM_ALGO_HASH_SHA3_512;
        break;
#endif
#ifdef VALTEST_SYM_ALGO_SM3
    case VAL_SYM_ALGO_MAC_HMAC_SM3:
        HashAlgorithm = VAL_SYM_ALGO_HASH_SM3;
        break;
#endif
    default:
        return false;
    }

    Status = val_SymAlloc(HashAlgorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
    if  (Status == VAL_SUCCESS)
    {
#ifdef SFZUTF_USERMODE
        const uint8_t * KeyCopy_p = Key_p;
#else
        uint8_t * KeyCopy_p = (uint8_t *)SFZUTF_MALLOC(KeySize);
        fail_if(KeyCopy_p == NULL, "Allocation ", (int)KeySize);
        memcpy(KeyCopy_p, Key_p, KeySize);
#endif

        Status = val_SymHashFinal(SymContext_p, KeyCopy_p, KeySize,
                                  HashedKey_p, HashedKeySize_p);
#ifndef SFZUTF_USERMODE
        SFZUTF_FREE(KeyCopy_p);
#endif
        if  (val_CheckFunctionResult(Status) == VAL_SUCCESS)
        {
            return true;
        }

        (void)val_SymRelease(SymContext_p);
    }
    return false;
}


/**
 * @brief Create a hmac key (asset)
 *
 * @param tv_p testvector with key data
 * @param hmacInfo a filled hmac object, policy must be OK
 * @param SymContext_p context ptr
 * @return int
 */
static int
create_hmac_key_asset(TestVector_HMAC_t tv_p,
                      HMacAlgoInfo_t * hmacInfo_p,
                      ValSymContextPtr_t SymContext_p,
                      ValAssetId_t * pKeyAssetId)
{
    if (tv_p->KeyLen == 0)
    {
        *pKeyAssetId = VAL_ASSETID_INVALID;
    }
    else
    {
        uint8_t HashedKeyBuffer[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
        ValSize_t KeySize = VAL_SYM_ALGO_MAX_DIGEST_SIZE;
        ValOctetsIn_t * Key_p = NULL;
        int Status;

        if (do_hmac_key_hash_if_needed(hmacInfo_p->Algorithm,
                                       tv_p->Key_p, tv_p->KeyLen,
                                       HashedKeyBuffer, &KeySize))
        {
            Key_p = HashedKeyBuffer;
        }
        else
        {
            Key_p = tv_p->Key_p;
            KeySize = tv_p->KeyLen;
        }

        Status = val_AssetAlloc(hmacInfo_p->AssetPolicy, KeySize,
                                VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                pKeyAssetId);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(Key)=", Status);

        {
#ifdef SFZUTF_USERMODE
            const uint8_t * KeyCopy_p = Key_p;
#else
            uint8_t * KeyCopy_p = (uint8_t *)SFZUTF_MALLOC(KeySize);
            fail_if(KeyCopy_p == NULL, "Allocation ", (int)KeySize);
            memcpy(KeyCopy_p, Key_p, KeySize);
#endif
            Status = val_AssetLoadPlaintext(*pKeyAssetId, KeyCopy_p, KeySize);
#ifndef SFZUTF_USERMODE
            SFZUTF_FREE(KeyCopy_p);
#endif
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(Key)=", Status);
        }

        Status = val_SymInitKey(SymContext_p, *pKeyAssetId, NULL, KeySize);
        fail_if(Status != VAL_SUCCESS, "val_SymInitKey=", (int)KeySize);
    }

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * do_hmac_test
 * Helper function that runs a single HMAC test.
 */
static int
do_hmac_test(uint32_t VectorIndex,
             ValSymContextPtr_t SymContext_p,
             TestVector_HMAC_t Vector_p,
             const int *const frags_p,
             const bool fVerify,
             ValAssetId_t const MacAssetId)
{
    ValStatus_t Status;
    ValOctetsOut_t Mac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t MacSize = 0;
    MsgIter_t msgit;

    memset(Mac, 0, sizeof(Mac));

    msgiter_init(&msgit, Vector_p->Msg_p, Vector_p->MsgLen, frags_p);
    do
    {
        uint8_t * InCopy_p;

        if (msgit.frag_len > 0)
        {
            InCopy_p = (uint8_t *)SFZUTF_MALLOC(msgit.frag_len);
            fail_if(InCopy_p == NULL, "Allocation ", (int)msgit.frag_len);
            memcpy(InCopy_p, (const uint8_t *)(msgit.msg_p + msgit.nbytes_done), msgit.frag_len);
        }
        else
        {
            InCopy_p = NULL;
        }

        if (msgit.nbytes_left == msgit.frag_len)
        {
            if (fVerify)
            {
                if (MacAssetId == VAL_ASSETID_INVALID)
                {
                    MacSize = Vector_p->MacLen;
                    memcpy(Mac, Vector_p->Mac_p, MacSize);
                    Status = val_SymMacVerify(SymContext_p,
                                              InCopy_p, msgit.frag_len,
                                              VAL_ASSETID_INVALID,
                                              Mac, MacSize);
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacVerify(MACValue)=", Status);
                }
                else
                {
                    Status = val_SymMacVerify(SymContext_p,
                                              InCopy_p, msgit.frag_len,
                                              MacAssetId,
                                              NULL, 0);
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacVerify(MACAsset)=", Status);
                }
            }
            else
            {
                MacSize = sizeof(Mac);
                Status = val_SymMacGenerate(SymContext_p,
                                            InCopy_p, msgit.frag_len,
                                            Mac, &MacSize);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacGenerate()=", Status);
                fail_if(Vector_p->MacLen != MacSize, "Result mismatch on length", VectorIndex);
                fail_if(memcmp(Mac, Vector_p->Mac_p, Vector_p->MacLen) != 0, "", VectorIndex);
            }
        }
        else
        {
            Status = val_SymMacUpdate(SymContext_p, InCopy_p, msgit.frag_len);
            if (val_CheckFunctionResult(Status) == VAL_INVALID_ALGORITHM)
            {
                uint32_t * ptr = (uint32_t *)SymContext_p;
                LOG_CRIT("Strange: 0x%X, 0x%X\n", ptr[0], ptr[1]);
            }
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymMacUpdate()=", Status);
        }

        if (InCopy_p != NULL)
        {
            SFZUTF_FREE(InCopy_p);
        }
    }
    while (msgiter_next(&msgit));

    return END_TEST_SUCCES;
}


static int
do_test_hmac(const bool fVerify,
             const bool fMacFinalAsset)
{
    uint32_t ndx = (uint32_t)g_ValTestBeginVector;
    int Failed = 0;
    int Success = 0;

    while (true)
    {
        HMacAlgoInfo_t hmacInfo;
        TestVector_HMAC_t tv_p;
        ValSymContextPtr_t SymContext_p;
        ValAssetId_t KeyAssetId;
        ValAssetId_t MacAssetId;
        ValStatus_t Status;
        int res;

        SymContext_p = NULL;
        KeyAssetId = VAL_ASSETID_INVALID;
        MacAssetId = VAL_ASSETID_INVALID;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        res = get_hmac_info(tv_p->Algorithm, &hmacInfo);
        if (res != 0)
        {
            // Unknown or unsupported vector
            goto next_vector;
        }
        if (hmacInfo.MacSize != tv_p->MacLen)
        {
            // HMAC does not handle partial MAC compare yet
            goto next_vector;
        }

        if (fVerify)
        {
            hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
        }
        else
        {
            hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
        }
        if (!val_IsAccessSecure())
        {
            hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
        }

        Status = val_SymAlloc(hmacInfo.Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

        if (tv_p->KeyLen != 0)
        {
            if ((tv_p->KeyLen < (hmacInfo.MacSize/2)) ||
                (tv_p->MacLen != hmacInfo.MacSize))
            {
                // HMAC Asset require a minimum size
                goto next_vector;
            }

            Status = create_hmac_key_asset(tv_p, &hmacInfo, SymContext_p, &KeyAssetId);
            fail_if(Status != END_TEST_SUCCES, "Failed to init key", Status);
        }

        if (fVerify)
        {
            if (fMacFinalAsset)
            {
                hmacInfo.AssetPolicy = (hmacInfo.AssetPolicy - EIP130_ASSET_POLICY_NONMODIFIABLE) | EIP130_ASSET_POLICY_TEMPORARY;
                if (!val_IsAccessSecure())
                {
                    hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                }
                Status = val_AssetAlloc(hmacInfo.AssetPolicy, tv_p->MacLen,
                                        VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                        &MacAssetId);
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(MAC)=", Status);

                {
#ifdef SFZUTF_USERMODE
                    const uint8_t * MacCopy_p = tv_p->Mac_p;
#else
                    uint8_t * MacCopy_p = (uint8_t *)SFZUTF_MALLOC(tv_p->MacLen);
                    fail_if(MacCopy_p == NULL, "Allocation ", (int)tv_p->MacLen);
                    memcpy(MacCopy_p, tv_p->Mac_p, tv_p->MacLen);
#endif
                    Status = val_AssetLoadPlaintext(MacAssetId,
                                                    MacCopy_p, tv_p->MacLen);
#ifndef SFZUTF_USERMODE
                    SFZUTF_FREE(MacCopy_p);
#endif
                }
                fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(MAC)=", Status);
            }
        }

        if (do_hmac_test(ndx, SymContext_p, tv_p, NULL,
                         fVerify, MacAssetId) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d (%d)\n", ndx, hmacInfo.Algorithm);
            Failed++;

            if (!g_ValTestCleanUp)
            {
                break;
            }
        }
        else
        {
            Success++;
            SymContext_p = NULL;        // Internally released
        }

next_vector:
        if (SymContext_p != NULL)
        {
            Status = val_SymRelease(SymContext_p);
            fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
        }
        if (KeyAssetId != VAL_ASSETID_INVALID)
        {
            Status = val_AssetFree(KeyAssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Key)=", Status);
        }
        if (MacAssetId != VAL_ASSETID_INVALID)
        {
            Status = val_AssetFree(MacAssetId);
            fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(MAC)=", Status);
        }

        test_vectors_hmac_release(tv_p);

        if (!g_ValTestRepeatVector)
        {
            ndx++;
        }
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }

    return END_TEST_SUCCES;
}


static int
do_test_hmac_multipart(const bool fVerify)
{
    int MULTIPART_HMAC_TEST[2];
    uint32_t ndx;

    MULTIPART_HMAC_TEST[1] = 0;
    for (ndx = 0U; ; ndx++)
    {
        HMacAlgoInfo_t hmacInfo;
        TestVector_HMAC_t tv_p;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (get_hmac_info(tv_p->Algorithm, &hmacInfo) == 0)
        {
            // check if vector is used able
            if ((tv_p->MsgLen > hmacInfo.BlockSize)
                && (tv_p->KeyLen >= (112/8)))
            {
                ValStatus_t Status;
                int rc;
                ValSymContextPtr_t SymContext_p = NULL;
                ValAssetId_t MacAssetId = VAL_ASSETID_INVALID;
                ValAssetId_t KeyAssetId = VAL_ASSETID_INVALID;

                if (fVerify)
                {
                    hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
                }
                else
                {
                    hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
                }
                if (!val_IsAccessSecure())
                {
                    hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
                }

                MULTIPART_HMAC_TEST[0] = (int)hmacInfo.BlockSize;
                hmacInfo.frags_p = MULTIPART_HMAC_TEST;

                Status = val_SymAlloc(hmacInfo.Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

                /* create key asset */
                Status = create_hmac_key_asset(tv_p, &hmacInfo, SymContext_p, &KeyAssetId);
                fail_if(Status != END_TEST_SUCCES, "Failed to init key", Status);

                if (fVerify)
                {
                    /* Set MACverify indication */
                    Status = val_SymMacInitVerify(SymContext_p);
                    fail_if(Status != VAL_SUCCESS, "val_SymMacInitVerify()=", Status);

                    /* Create & Load Final MAC Asset */
                    hmacInfo.AssetPolicy = (hmacInfo.AssetPolicy & ~EIP130_ASSET_POLICY_NONMODIFIABLE) | EIP130_ASSET_POLICY_TEMPORARY;
                    Status = val_AssetAlloc(hmacInfo.AssetPolicy, tv_p->MacLen,
                                            VAL_ASSET_LIFETIME_INFINITE, false, false, 0,
                                            &MacAssetId);
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetAlloc(MAC)=", Status);

                    {
#ifdef SFZUTF_USERMODE
                        const uint8_t * MacCopy_p = tv_p->Mac_p;
#else
                        uint8_t * MacCopy_p = (uint8_t *)SFZUTF_MALLOC(tv_p->MacLen);
                        fail_if(MacCopy_p == NULL, "Allocation ", (int)tv_p->MacLen);
                        memcpy(MacCopy_p, tv_p->Mac_p, tv_p->MacLen);
#endif
                        Status = val_AssetLoadPlaintext(MacAssetId,
                                                        MacCopy_p, tv_p->MacLen);
#ifndef SFZUTF_USERMODE
                        SFZUTF_FREE(MacCopy_p);
#endif
                    }
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetLoadPlaintext(MAC)=", Status);
                }

                rc = do_hmac_test(ndx, SymContext_p, tv_p, hmacInfo.frags_p,
                                  fVerify, MacAssetId);

                if (KeyAssetId != VAL_ASSETID_INVALID)
                {
                    Status = val_AssetFree(KeyAssetId);
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(Key)=", Status);
                }
                if (MacAssetId != VAL_ASSETID_INVALID)
                {
                    Status = val_AssetFree(MacAssetId);
                    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AssetFree(MAC)=", Status);
                }
                Status = val_SymRelease(SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
                if (rc != 0)
                {
                    LOG_CRIT("Processed vector %d (%d)\n", ndx, hmacInfo.Algorithm);
                    return END_TEST_FAIL;
                }
            }
        }
        else
        {
            // Unknown or unsupported vector
        }

        test_vectors_hmac_release(tv_p);
    }

    return END_TEST_SUCCES;
}


/*----------------------------------------------------------------------------
 * valtest_IsSM3Supported
 *
 * This function checks if the SM3 is supported or not.
 */
#ifdef VALTEST_SYM_ALGO_SM3
bool
valtest_IsSM3Supported(void)
{
#define SM3_SUPPORTED_TAG   (0xA5)
#define SM3_UNSUPPORTED_TAG (0x5A)

    static uint8_t gl_SM3Supported = 0;
    TestVector_HASH_t tv_p;
    ValStatus_t Status;
    ValSymContextPtr_t SymContext_p;
    uint8_t * Message_p;
    ValOctetsOut_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t DigestSize = sizeof(Digest);

    if (gl_SM3Supported != 0)
    {
        return (gl_SM3Supported == SM3_SUPPORTED_TAG);
    }

    tv_p = test_vectors_first_sm3_get();
    if (tv_p == NULL)
    {
        goto sm3_unsupported;
    }

    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SM3, VAL_SYM_MODE_NONE,
                          false, &SymContext_p);
    if (Status != VAL_SUCCESS)
    {
        goto sm3_unsupported;
    }

    Message_p = (uint8_t *)SFZUTF_MALLOC(tv_p->MsgLen);
    if (Message_p == NULL)
    {
        (void)val_SymRelease(SymContext_p);
        goto sm3_unsupported;
    }
    memcpy(Message_p, tv_p->Msg_p, tv_p->MsgLen);

    Status = val_SymHashFinal(SymContext_p, Message_p, tv_p->MsgLen,
                              Digest, &DigestSize);

    SFZUTF_FREE(Message_p);

    (void)val_SymRelease(SymContext_p);

    if (val_CheckFunctionResult(Status) != VAL_SUCCESS)
    {
        goto sm3_unsupported;
    }

    if ((DigestSize == tv_p->DigestLen) &&
         !memcmp(Digest, tv_p->Digest_p, DigestSize))
    {
        gl_SM3Supported = SM3_SUPPORTED_TAG;
        return true;
    }

sm3_unsupported:
    gl_SM3Supported = SM3_UNSUPPORTED_TAG;
    return false;

#undef SM3_SUPPORTED_TAG
#undef SM3_UNSUPPORTED_TAG
}
#endif


START_TEST(test_hash)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        ValSymContextPtr_t SymContext_p = NULL;
        ValSymAlgo_t Algorithm = VAL_SYM_ALGO_NONE;
        TestVector_HASH_t tv_p;
        ValStatus_t Status;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        LOG_INFO("Processed vector %d\n", ndx);

        switch (tv_p->Algorithm)
        {
        case TESTVECTORS_HASH_SHA160:
            Algorithm = VAL_SYM_ALGO_HASH_SHA1;
            break;
        case TESTVECTORS_HASH_SHA224:
            Algorithm = VAL_SYM_ALGO_HASH_SHA224;
            break;
        case TESTVECTORS_HASH_SHA256:
            Algorithm = VAL_SYM_ALGO_HASH_SHA256;
            break;
#ifdef VALTEST_SYM_ALGO_SHA512
        case TESTVECTORS_HASH_SHA384:
            Algorithm = VAL_SYM_ALGO_HASH_SHA384;
            break;
        case TESTVECTORS_HASH_SHA512:
            Algorithm = VAL_SYM_ALGO_HASH_SHA512;
            break;
#endif
#ifdef VALTEST_SYM_ALGO_SHA3
        case TESTVECTORS_HASH_SHA3_224:
            Algorithm = VAL_SYM_ALGO_HASH_SHA3_224;
            break;
        case TESTVECTORS_HASH_SHA3_256:
            Algorithm = VAL_SYM_ALGO_HASH_SHA3_256;
            break;
        case TESTVECTORS_HASH_SHA3_384:
            Algorithm = VAL_SYM_ALGO_HASH_SHA3_384;
            break;
        case TESTVECTORS_HASH_SHA3_512:
            Algorithm = VAL_SYM_ALGO_HASH_SHA3_512;
            break;
#endif
#ifdef VALTEST_SYM_ALGO_SM3
        case TESTVECTORS_HASH_SM3:
            if (!valtest_IsSM3Supported())
            {
                test_vectors_hash_release(tv_p);
                continue;
            }
            Algorithm = VAL_SYM_ALGO_HASH_SM3;
            break;
#endif
        default:
            // Not (yet) supported
            test_vectors_hash_release(tv_p);
            continue;
        }

        Status = val_SymAlloc(Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

        if (do_hash_test(ndx, false, SymContext_p, tv_p, NULL) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }

        Status = val_SymRelease(SymContext_p);
        fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hash_multipart)
{
    static const int MULTIPART_HASH_TEST1[] = {128, 0};
    static const int MULTIPART_HASH_TEST2[] = {5*128, 11*128, 1*128, -1};
    static const int * MULTIPART_HASH_TESTS[] = {
        MULTIPART_HASH_TEST1,
        MULTIPART_HASH_TEST2
    };
    int Success = 0;
    int Failed = 0;
    uint32_t ndx;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if (tv_p->MsgLen > 1000)
        {
            ValSymAlgo_t Algorithm = VAL_SYM_ALGO_NONE;
            const int * frags_p;
            unsigned int ndx2;

            switch (tv_p->Algorithm)
            {
            case TESTVECTORS_HASH_SHA160:
                Algorithm = VAL_SYM_ALGO_HASH_SHA1;
                break;
            case TESTVECTORS_HASH_SHA224:
                Algorithm = VAL_SYM_ALGO_HASH_SHA224;
                break;
            case TESTVECTORS_HASH_SHA256:
                Algorithm = VAL_SYM_ALGO_HASH_SHA256;
                break;
#ifdef VALTEST_SYM_ALGO_SHA512
            case TESTVECTORS_HASH_SHA384:
                Algorithm = VAL_SYM_ALGO_HASH_SHA384;
                break;
            case TESTVECTORS_HASH_SHA512:
                Algorithm = VAL_SYM_ALGO_HASH_SHA512;
                break;
#endif
#ifdef VALTEST_SYM_ALGO_SHA3
            case TESTVECTORS_HASH_SHA3_224:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_224;
                break;
            case TESTVECTORS_HASH_SHA3_256:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_256;
                break;
            case TESTVECTORS_HASH_SHA3_384:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_384;
                break;
            case TESTVECTORS_HASH_SHA3_512:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_512;
                break;
#endif
#ifdef VALTEST_SYM_ALGO_SM3
            case TESTVECTORS_HASH_SM3:
                if (!valtest_IsSM3Supported())
                {
                    LOG_INFO("SKIPPED: vector %d\n", ndx);
                    test_vectors_hash_release(tv_p);
                    continue;
                }
                Algorithm = VAL_SYM_ALGO_HASH_SM3;
                break;
#endif
            default:
                // Not (yet) supported
                LOG_INFO("SKIPPED: vector %d\n", ndx);
                test_vectors_hash_release(tv_p);
                continue;
            }

            FOREACH(frags_p, ndx2, MULTIPART_HASH_TESTS)
            {
                ValSymContextPtr_t SymContext_p = NULL;
                ValStatus_t Status;

                Status = val_SymAlloc(Algorithm, VAL_SYM_MODE_NONE, ((_i & 1) != 0), &SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

                if (do_hash_test(ndx, ((_i & 1) != 0), SymContext_p, tv_p, frags_p) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Processed vector %d\n", ndx);
                    Failed++;
                }
                else
                {
                    Success++;
                }

                Status = val_SymRelease(SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
            }
        }

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST


#ifdef SFZUTF_USERMODE
START_TEST(test_hash_unaligned_buffer)
{
    static uint8_t Buffer[512];
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HASH_t tv_p;

        tv_p = test_vectors_hash_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if ((tv_p->MsgLen >= 16) && (tv_p->MsgLen < 500))
        {
            ValSymAlgo_t Algorithm = VAL_SYM_ALGO_NONE;
            int disalign;

            switch (tv_p->Algorithm)
            {
            case TESTVECTORS_HASH_SHA160:
                Algorithm = VAL_SYM_ALGO_HASH_SHA1;
                break;
            case TESTVECTORS_HASH_SHA224:
                Algorithm = VAL_SYM_ALGO_HASH_SHA224;
                break;
            case TESTVECTORS_HASH_SHA256:
                Algorithm = VAL_SYM_ALGO_HASH_SHA256;
                break;
#ifdef VALTEST_SYM_ALGO_SHA512
            case TESTVECTORS_HASH_SHA384:
                Algorithm = VAL_SYM_ALGO_HASH_SHA384;
                break;
            case TESTVECTORS_HASH_SHA512:
                Algorithm = VAL_SYM_ALGO_HASH_SHA512;
                break;
#endif
#ifdef VALTEST_SYM_ALGO_SHA3
            case TESTVECTORS_HASH_SHA3_224:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_224;
                break;
            case TESTVECTORS_HASH_SHA3_256:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_256;
                break;
            case TESTVECTORS_HASH_SHA3_384:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_384;
                break;
            case TESTVECTORS_HASH_SHA3_512:
                Algorithm = VAL_SYM_ALGO_HASH_SHA3_512;
                break;
#endif
#ifdef VALTEST_SYM_ALGO_SM3
            case TESTVECTORS_HASH_SM3:
                if (!valtest_IsSM3Supported())
                {
                    LOG_INFO("SKIPPED: vector %d\n", ndx);
                    test_vectors_hash_release(tv_p);
                    continue;
                }
                Algorithm = VAL_SYM_ALGO_HASH_SM3;
                break;
#endif
            default:
                // Not (yet) supported
                LOG_INFO("SKIPPED: vector %d\n", ndx);
                test_vectors_hash_release(tv_p);
                continue;
            }

            for (disalign = 1; disalign < 4; disalign++)
            {
                TestVector_HASH_Rec_t tvrec;
                ValSymContextPtr_t SymContext_p = NULL;
                ValStatus_t Status;

                Status = val_SymAlloc(Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

                tvrec = *tv_p; // copy structure
                tvrec.Msg_p = Buffer + disalign;
                memset(Buffer, 0xdc, sizeof(Buffer));
                memcpy(&Buffer[disalign], tv_p->Msg_p, tv_p->MsgLen);
                Status = do_hash_test(ndx, false, SymContext_p, &tvrec, NULL);
                if(Status != END_TEST_SUCCES)
                {
                    Failed++;
                    LOG_CRIT("Process vector %d Failed\n", ndx);
                }
                else
                {
                    Success++;
                }

                Status = val_SymRelease(SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
            }
        }

        test_vectors_hash_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif


START_TEST(test_hmac_generate_key_asset)
{
    if (do_test_hmac(false, false) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hmac_verify_key_asset)
{
    if (do_test_hmac(true, false) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hmac_verify_key_mac_asset)
{
    if (do_test_hmac(true, true) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hmac_multipart_generate)
{
    if (do_test_hmac_multipart(false) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST


START_TEST(test_hmac_multipart_verify)
{
    if (do_test_hmac_multipart(true) != END_TEST_SUCCES)
    {
        return END_TEST_FAIL;
    }
}
END_TEST


#ifdef SFZUTF_USERMODE
#ifdef NO_SKIP
START_TEST(test_hmac_unaligned_buffer)
{
    static uint8_t Buffer[512];
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;

    for (ndx = 0U; ; ndx++)
    {
        TestVector_HMAC_t tv_p;

        tv_p = test_vectors_hmac_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        if ((tv_p->MsgLen > 200) && (tv_p->MsgLen < 500))
        {
            HMacAlgoInfo_t hmacInfo;
            int disalign;

            if (get_hmac_info(tv_p->Algorithm, &hmacInfo) != 0)
            {
                // Algorithm is not supported
                continue;
            }

            LOG_INFO("Process vector %d\n", ndx);

            hmacInfo.AssetPolicy = VAL_POLICY_MAC_GENERATE;
            if (!val_IsAccessSecure())
            {
                hmacInfo.AssetPolicy |= EIP130_ASSET_POLICY_SOURCENONSECURE;
            }

            for (disalign = 1; disalign < 4; disalign++)
            {
                ValSymContextPtr_t SymContext_p;
                ValAssetId_t KeyAssetId;
                TestVector_HMAC_Rec_t tvrec;
                size_t offs;
                ValStatus_t Status;

                SymContext_p = NULL;
                KeyAssetId = VAL_ASSETID_INVALID;

                Status = val_SymAlloc(hmacInfo.Algorithm, VAL_SYM_MODE_NONE, false, &SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

                offs = (tv_p->KeyLen + 3U + 3U) & (size_t)~3UL;
                tvrec = *tv_p;          // copy structure
                tvrec.Key_p = Buffer + disalign;
                tvrec.Msg_p = Buffer + offs + (4 - disalign);
                memset(Buffer, 0xdc, sizeof(Buffer));
                memcpy((Buffer + disalign), tv_p->Key_p, tv_p->KeyLen);
                memcpy((Buffer + offs + (4 - disalign)), tv_p->Msg_p, tv_p->MsgLen);

                Status = create_hmac_key_asset((TestVector_HMAC_t)&tvrec, &hmacInfo, SymContext_p, &KeyAssetId);
                if (Status != END_TEST_SUCCES)
                {
                    LOG_CRIT("Process vector %d (Failed to init key)\n", ndx);
                    Failed++;
                    (void)val_SymRelease(SymContext_p);
                    break;
                }

                if (do_hmac_test(ndx, SymContext_p, &tvrec, NULL,
                                 false, KeyAssetId) != END_TEST_SUCCES)
                {
                    LOG_CRIT("Process vector %d (disalignment %d)\n", ndx, disalign);
                    Failed++;
                }
                else
                {
                    Success++;
                }


                if (KeyAssetId != VAL_ASSETID_INVALID)
                {
                    (void)val_AssetFree(KeyAssetId);
                }

                Status = val_SymRelease(SymContext_p);
                fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
            }
        }

        test_vectors_hmac_release(tv_p);
    }

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif
#endif


/*----------------------------------------------------------------------------
 * Some negative Hash tests
 *--------------------------------------------------------------------------*/
START_TEST(test_hash_invalid_algorithm)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValOctetsOut_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t DigestSize = sizeof(Digest);
    uint8_t hashData[128];
    ValStatus_t Status;

    memset(hashData, 'a', sizeof(hashData));

    Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymHashFinal(SymContext_p,
                              hashData,
                              sizeof(hashData),
                              Digest,
                              &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymHashFinal()=", Status);

    Status = val_SymHashUpdate(SymContext_p,
                               hashData,
                               sizeof(hashData));
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymHashUpdate()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST


START_TEST(test_hash_buffer_too_small)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValOctetsOut_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t DigestSize = sizeof(Digest);
    uint8_t hashData[128];
    ValStatus_t Status;

    memset(hashData, 'a', sizeof(hashData));

    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    DigestSize = (224/8);
    Status = val_SymHashFinal(SymContext_p,
                              hashData,
                              sizeof(hashData),
                              Digest,
                              &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_SymHashFinal()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST


START_TEST(test_hash_arguments)
{
    ValSymContextPtr_t SymContext_p = NULL;
    uint8_t * DataBuffer_p;
    ValOctetsOut_t Digest[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t DigestSize = sizeof(Digest);
    ValStatus_t Status;

    DataBuffer_p = (uint8_t *)SFZUTF_MALLOC(100);
    fail_if(DataBuffer_p == NULL, "Allocation ", 100);

    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymHashFinal(NULL, DataBuffer_p, 64, Digest, &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashFinal(BadArgument1)=", Status);

    Status = val_SymHashFinal(SymContext_p, NULL, 64, Digest, &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashFinal(BadArgument2)=", Status);

    Status = val_SymHashFinal(SymContext_p, DataBuffer_p, 64, NULL, &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashFinal(BadArgument4)=", Status);

    Status = val_SymHashFinal(SymContext_p, DataBuffer_p, 64, Digest, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashFinal(BadArgument5)=", Status);

    Status = val_SymHashUpdate(NULL, DataBuffer_p, 64);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashUpdate(BadArgument1)=", Status);

    Status = val_SymHashUpdate(SymContext_p, NULL, 64);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashUpdate(BadArgument2)=", Status);

    Status = val_SymHashUpdate(SymContext_p, DataBuffer_p, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashUpdate(BadArgument3L)=", Status);

    Status = val_SymHashUpdate(SymContext_p, DataBuffer_p, 32);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymHashUpdate(BadArgument3M)=", Status);

    Status = val_SymHashFinal(SymContext_p, NULL, 0, Digest, &DigestSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_SymHashFinal(NULL HASH)=", Status);

    (void)val_SymRelease(SymContext_p);

    SFZUTF_FREE(DataBuffer_p);
}
END_TEST


START_TEST(test_hmac_invalid_algorithm)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValOctetsOut_t Mac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t MacSize = sizeof(Mac);
    uint8_t macData[128];
    ValStatus_t Status;

    memset(macData, 'a', sizeof(macData));

    Status = val_SymAlloc(VAL_SYM_ALGO_HASH_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymMacGenerate(SymContext_p,
                                macData,
                                sizeof(macData),
                                Mac,
                                &MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymMacGenerate()=", Status);

    Status = val_SymMacVerify(SymContext_p,
                              macData,
                              sizeof(macData),
                              VAL_ASSETID_INVALID,
                              Mac,
                              MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymMacVerify()=", Status);

    Status = val_SymMacUpdate(SymContext_p,
                              macData,
                              sizeof(macData));
    fail_if(val_CheckFunctionResult(Status) != VAL_INVALID_ALGORITHM, "val_SymMacUpdate()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);
}
END_TEST


START_TEST(test_hmac_buffer_too_small)
{
    ValSymContextPtr_t SymContext_p = NULL;
    ValOctetsOut_t Mac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t MacSize = sizeof(Mac);
    uint8_t macData[128];
    ValStatus_t Status;

    memset(macData, 'a', sizeof(macData));

    Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    MacSize = (224/8);
    Status = val_SymMacGenerate(SymContext_p,
                                macData,
                                sizeof(macData),
                                Mac,
                                &MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BUFFER_TOO_SMALL, "val_SymMacGenerate()=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

}
END_TEST


START_TEST(test_hmac_arguments)
{
    ValSymContextPtr_t SymContext_p = NULL;
    uint8_t * DataBuffer_p;
    ValOctetsOut_t Mac[VAL_SYM_ALGO_MAX_DIGEST_SIZE];
    ValSize_t MacSize = sizeof(Mac);
    ValStatus_t Status;

    DataBuffer_p = (uint8_t *)SFZUTF_MALLOC(100);
    fail_if(DataBuffer_p == NULL, "Allocation ", 100);

    Status = val_SymAlloc(VAL_SYM_ALGO_MAC_HMAC_SHA256,
                          VAL_SYM_MODE_NONE,
                          false,
                          &SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymAlloc()=", Status);

    Status = val_SymMacGenerate(NULL, DataBuffer_p, 64, Mac, &MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacGenerate(BadArgument1)=", Status);

    Status = val_SymMacGenerate(SymContext_p, NULL, 64, Mac, &MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacGenerate(BadArgument2)=", Status);

    Status = val_SymMacGenerate(SymContext_p, DataBuffer_p, 64, NULL, &MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacGenerate(BadArgument4)=", Status);

    Status = val_SymMacGenerate(SymContext_p, DataBuffer_p, 64, Mac, NULL);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacGenerate(BadArgument5)=", Status);

    Status = val_SymMacVerify(NULL, DataBuffer_p, 64, VAL_ASSETID_INVALID, Mac, MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacVerify(BadArgument1)=", Status);

    Status = val_SymMacVerify(SymContext_p, NULL, 64, VAL_ASSETID_INVALID, Mac, MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacVerify(BadArgument2)=", Status);

    Status = val_SymMacVerify(SymContext_p, DataBuffer_p, 64, VAL_ASSETID_INVALID, NULL, MacSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacVerify(BadArgument5)=", Status);

    Status = val_SymMacUpdate(NULL, DataBuffer_p, 64);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacUpdate(BadArgument1)=", Status);

    Status = val_SymMacUpdate(SymContext_p, NULL, 64);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacUpdate(BadArgument2)=", Status);

    Status = val_SymMacUpdate(SymContext_p, DataBuffer_p, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacUpdate(BadArgument3L)=", Status);

    Status = val_SymMacUpdate(SymContext_p, DataBuffer_p, 32);
    fail_if(val_CheckFunctionResult(Status) != VAL_BAD_ARGUMENT, "val_SymMacUpdate(BadArgument3M)=", Status);

    Status = val_SymRelease(SymContext_p);
    fail_if(Status != VAL_SUCCESS, "val_SymRelease()=", Status);

    SFZUTF_FREE(DataBuffer_p);
}
END_TEST


int
suite_add_test_SymHashHMac(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_Hash_and_HMac_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_hash) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_hash_multipart, 2) != 0) goto FuncErrorReturn;
#ifdef SFZUTF_USERMODE
        if (sfzutf_test_add(TestCase_p, test_hash_unaligned_buffer) != 0) goto FuncErrorReturn;
#endif
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart_generate) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_multipart_verify) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_generate_key_asset) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_verify_key_asset) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_verify_key_mac_asset) != 0) goto FuncErrorReturn;

#ifdef SFZUTF_USERMODE
#ifdef NO_SKIP
        if (sfzutf_test_add(TestCase_p, test_hmac_unaligned_buffer) != 0) goto FuncErrorReturn;
#endif
#endif

        if (sfzutf_test_add(TestCase_p, test_hash_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hash_buffer_too_small) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_invalid_algorithm) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_hmac_buffer_too_small) != 0) goto FuncErrorReturn;

        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_hash_arguments) != 0) goto FuncErrorReturn;
            if (sfzutf_test_add(TestCase_p, test_hmac_arguments) != 0) goto FuncErrorReturn;
        }
        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_hash.c */
