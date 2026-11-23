/* psatest_aead.c
 *
 * Description: cipher
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

#include "psatest_internal.h"

/* Test vectors. */
#ifdef PSATEST_SYM_ALGO_AES_CCM
#include "testvectors_aes_ccm.h"
#endif
#ifdef PSATEST_SYM_ALGO_ARIA_GCM
#include "testvectors_aes_gcm.h"
#endif
#ifdef PSATEST_SYM_ALGO_ARIA_CCM
#include "testvectors_aria_ccm.h"
#endif
#ifdef PSATEST_SYM_ALGO_ARIA_GCM
#include "testvectors_aria_gcm.h"
#endif
#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
#include "testvectors_chacha20_poly1305_aead.h"
#endif

#define PSA_AEAD_STATE_INIT         0U
#define PSA_AEAD_STATE_SETUP        1U
#define PSA_AEAD_STATE_SET_LENGTH   2U
#define PSA_AEAD_STATE_SET_NONCE    3U
#define PSA_AEAD_STATE_UPDATE       4U
#define PSA_AEAD_STATE_IV           5U

#define PSA_SYM_ALGO_AES_BLOCK_SIZE 16U

typedef struct
{
    const uint8_t * Pt_p;
    const uint8_t * Aad_p;
    const uint8_t * Ct_p;
    const uint8_t * Nonce_p;
    const uint8_t * key_p;
    const uint8_t * Tag_p;
    uint32_t PtLen;
    uint32_t AadLen;
    uint32_t CtLen;
    uint32_t NonceLen;
    uint32_t KeyLen;
    uint32_t TagLen;
} SymaeadCryptTV_t;


#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM) || \
    (defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305))
static void
setupaeadTVctx(SymaeadCryptTV_t *TVctx,
               const uint8_t *Pt_p,
               uint32_t PtLen,
               const uint8_t * Aad_p,
               uint32_t AadLen,
               const uint8_t *Ct_p,
               uint32_t CtLen,
               const uint8_t * Nonce_p,
               uint32_t NonceLen,
               const uint8_t *Key_p,
               uint32_t KeyLen,
               const uint8_t * Tag_p,
               uint32_t TagLen)
{
    TVctx->Pt_p = Pt_p;
    TVctx->PtLen = PtLen;
    TVctx->Aad_p = Aad_p;
    TVctx->AadLen = AadLen;
    TVctx->Ct_p = Ct_p;
    TVctx->CtLen = CtLen;
    TVctx->Nonce_p = Nonce_p;
    TVctx->NonceLen = NonceLen;
    TVctx->key_p = Key_p;
    TVctx->KeyLen = KeyLen;
    TVctx->Tag_p = Tag_p;
    TVctx->TagLen = TagLen;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM) || \
    (defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305))
/*----------------------------------------------------------------------------
 * setupaeadkey
 *
 * Helper function to setup key.
 */
static psa_status_t
setupaeadkey(psa_key_id_t * key,
             psa_algorithm_t Mode,
             psa_key_usage_t usage_flag,
             psa_key_type_t key_type,
             psa_key_lifetime_t lifetime,
             psa_key_id_t uid,
             SymaeadCryptTV_t * Vector_p)
{
    psa_key_attributes_t attributes = { 0 };
    size_t bits = (Vector_p->KeyLen) * 8U;
    psa_status_t Status;

    if (0U == Vector_p->KeyLen)
    {
        Status = PSA_ERROR_INSUFFICIENT_DATA;
    }
    else
    {
        psa_set_key_type(&attributes, key_type);
        psa_set_key_algorithm(&attributes, Mode);
        psa_set_key_usage_flags(&attributes, usage_flag);
        psa_set_key_bits(&attributes, bits);
        psa_set_key_lifetime(&attributes, lifetime);
        if (uid != 0U)
        {
            psa_set_key_id(&attributes, uid);
        }
        Status = psa_import_key(&attributes, Vector_p->key_p, Vector_p->KeyLen, key);
    }

    return Status;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_GCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_GCM)
/*----------------------------------------------------------------------------
 * do_aead_gcm_test
 *
 * Helper function that runs a single GCM AEAD test.
 */
static int
do_aead_gcm_test(uint32_t VectorIndex,
                 psa_key_id_t key,
                 psa_key_id_t key_ver,
                 psa_algorithm_t alg,
                 SymaeadCryptTV_t * Vector_p)

{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t *ciphertext = NULL;
    size_t ciphertext_size = Vector_p->CtLen;
    uint8_t *plaintext = NULL;
    size_t ciphertext_length = 0U;
    size_t plaintext_length = 0U;
    uint8_t *input = NULL;
    size_t input_length = 0U;
    uint8_t nonce[16];
    size_t nonce_length = 0U;

    ciphertext = (uint8_t *)SFZUTF_MALLOC(((Vector_p->CtLen) + (Vector_p->TagLen)));
    fail_if(ciphertext == NULL, "Allocation ", (int)((Vector_p->CtLen) + (Vector_p->TagLen)));
    (void)memset(ciphertext, 0, (Vector_p->CtLen) + (Vector_p->TagLen));
    plaintext = (uint8_t *)SFZUTF_MALLOC(Vector_p->PtLen + 4);
    fail_if(plaintext == NULL, "Allocation ", (int)(Vector_p->PtLen));
    (void)memset(plaintext, 0, Vector_p->PtLen + 4);
    input = (uint8_t *)SFZUTF_MALLOC(((Vector_p->CtLen) + (Vector_p->TagLen) + 4));
    fail_if(input == NULL, "Allocation ", (int)((Vector_p->CtLen) + (Vector_p->TagLen)));
    (void)memset(input, 0, ((Vector_p->CtLen) + (Vector_p->TagLen) + 4));

    memcpy(nonce, Vector_p->Nonce_p, Vector_p->NonceLen);
    nonce_length = Vector_p->NonceLen;
    ciphertext_size += Vector_p->TagLen;
    if (nonce_length == 12)
    {
        memcpy(&nonce[nonce_length], "\x00\x00\x00\x01", 4);
        nonce_length = 16;
    }

    memcpy(input, Vector_p->Ct_p, Vector_p->CtLen);
    memcpy(&input[Vector_p->CtLen], Vector_p->Tag_p, Vector_p->TagLen);
    input_length = ((Vector_p->CtLen) + (Vector_p->TagLen));
    Status = psa_aead_decrypt(key_ver, alg, nonce, nonce_length,
                              Vector_p->Aad_p, Vector_p->AadLen, input,
                              input_length, plaintext, Vector_p->PtLen, &plaintext_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_decrypt()", Status);
    fail_if(Vector_p->PtLen != plaintext_length, "Length mismatch ", (int)plaintext_length);
    fail_if(memcmp(Vector_p->Pt_p, plaintext, Vector_p->PtLen) != 0, "", VectorIndex);

    SFZUTF_FREE(input);
    SFZUTF_FREE(plaintext);

    Status = psa_aead_encrypt(key, alg, nonce, nonce_length,
                              Vector_p->Aad_p, Vector_p->AadLen, Vector_p->Pt_p,
                              Vector_p->PtLen, ciphertext, ciphertext_size, &ciphertext_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_encrypt()", Status);
    fail_if(((Vector_p->CtLen) + Vector_p->TagLen) != ciphertext_length, "Length mismatch ", (int)ciphertext_length);

    uint8_t *decrypt_output = (uint8_t *)SFZUTF_MALLOC(Vector_p->PtLen + 4);
    fail_if(decrypt_output == NULL, "Allocation ", (int)(Vector_p->PtLen));
    (void)memset(decrypt_output, 0, Vector_p->PtLen + 4);
    plaintext_length = 0;
    input_length = ((Vector_p->CtLen) + (Vector_p->TagLen));
    Status = psa_aead_decrypt(key_ver, alg, nonce, nonce_length,
                            Vector_p->Aad_p, Vector_p->AadLen, ciphertext,
                            input_length, decrypt_output, Vector_p->PtLen, &plaintext_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_decrypt()", Status);
    fail_if(Vector_p->PtLen != plaintext_length, "Length mismatch ", (int)plaintext_length);
    fail_if(memcmp(Vector_p->Pt_p, decrypt_output, Vector_p->PtLen) != 0, "", VectorIndex);

    SFZUTF_FREE(ciphertext);
    SFZUTF_FREE(decrypt_output);

    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM)
/*----------------------------------------------------------------------------
 * do_aead_ccm_test
 *
 * Helper function that runs a single CCM AEAD test.
 */
static int
do_aead_ccm_test(uint32_t VectorIndex,
                 psa_key_id_t key,
                 psa_key_id_t key_ver,
                 psa_algorithm_t alg,
                 bool fencrypt,
                 SymaeadCryptTV_t * Vector_p)

{
    psa_status_t Status;
    uint8_t *ciphertext = NULL;
    uint8_t *plaintext = NULL;
    size_t ciphertext_length = 0;
    size_t plaintext_length = 0;

    ciphertext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen + 16));
    fail_if(ciphertext == NULL, "Allocation ", (int)(Vector_p->PtLen));
    (void)memset(ciphertext, 0, (Vector_p->PtLen + 16));
    if (Vector_p->PtLen != 0)
    {
        plaintext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen));
        fail_if(plaintext == NULL, "Allocation ", (int)(Vector_p->PtLen));
        (void)memset(plaintext, 0, Vector_p->PtLen);
    }

    if (fencrypt)
    {
        Status = psa_aead_encrypt(key, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                                  Vector_p->Aad_p, Vector_p->AadLen, Vector_p->Pt_p,
                                  Vector_p->PtLen, ciphertext, Vector_p->CtLen, &ciphertext_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_encrypt()", Status);
        fail_if(Vector_p->CtLen != ciphertext_length, "Length mismatch ", (int)ciphertext_length);
        fail_if(memcmp(Vector_p->Ct_p, ciphertext, Vector_p->CtLen) != 0, "enc data mismatch", VectorIndex);
    }
    else
    {
        Status = psa_aead_decrypt(key_ver, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                                Vector_p->Aad_p, Vector_p->AadLen, Vector_p->Ct_p,
                                Vector_p->CtLen, plaintext, Vector_p->PtLen, &plaintext_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_decrypt()", Status);
        fail_if(Vector_p->PtLen != plaintext_length, "Length mismatch ", (int)plaintext_length);
        fail_if(memcmp(Vector_p->Pt_p, plaintext, Vector_p->PtLen) != 0, "", VectorIndex);
    }

    SFZUTF_FREE(ciphertext);
    if (plaintext != NULL)
    {
        SFZUTF_FREE(plaintext);
    }
    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM)
/*----------------------------------------------------------------------------
 * do_aead_ccm_test_unpadded
 *
 * Helper function that runs a single CCM AEAD test with unpadded input.
 */
static int
do_aead_ccm_test_unpadded(uint32_t VectorIndex,
                          psa_key_id_t key,
                          psa_key_id_t key_ver,
                          psa_algorithm_t alg,
                          SymaeadCryptTV_t * Vector_p)

{
    psa_status_t Status;
    uint8_t *ciphertext = NULL;
    uint8_t *plaintext = NULL;
    uint8_t *decrypt_output = NULL;
    size_t plaintext_size = 0U;
    size_t ciphertext_size = 0U;
    size_t ciphertext_length = 0U;
    size_t plaintext_length = 0U;


    if (Vector_p->PtLen != 0)
    {
        plaintext_size = Vector_p->PtLen - 1; //Remove one byte for unpadded data
        plaintext = (uint8_t *)SFZUTF_MALLOC(plaintext_size);
        fail_if(plaintext == NULL, "Allocation ", (int)plaintext_size);
        (void)memcpy(plaintext, Vector_p->Pt_p, plaintext_size);
    }
    ciphertext = (uint8_t *)SFZUTF_MALLOC(plaintext_size + 16); // +16 for tag
    fail_if(ciphertext == NULL, "Allocation ", (int)(plaintext_size + 16));
    (void)memset(ciphertext, 0, (plaintext_size + 16));
    ciphertext_size = plaintext_size + 16;

    Status = psa_aead_encrypt(key, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                            Vector_p->Aad_p, Vector_p->AadLen, plaintext,
                            plaintext_size, ciphertext, ciphertext_size, &ciphertext_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_encrypt()", Status);
    fail_if(ciphertext_size != ciphertext_length, "Length mismatch ", (int)ciphertext_length);

    if (Vector_p->PtLen != 0)
    {
        decrypt_output = (uint8_t *)SFZUTF_MALLOC(plaintext_size);
        fail_if(decrypt_output == NULL, "Allocation ", (int)plaintext_size);
        (void)memset(decrypt_output, 0, plaintext_size);
    }
    Status = psa_aead_decrypt(key_ver, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                            Vector_p->Aad_p, Vector_p->AadLen, ciphertext,
                            ciphertext_size, decrypt_output, plaintext_size, &plaintext_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_decrypt()", Status);
    fail_if(plaintext_size != plaintext_length, "Length mismatch ", (int)plaintext_length);
    fail_if(memcmp(Vector_p->Pt_p, plaintext, plaintext_size) != 0, "", VectorIndex);


    SFZUTF_FREE(ciphertext);
    if (plaintext != NULL)
    {
        SFZUTF_FREE(plaintext);
    }
    if (decrypt_output != NULL)
    {
        SFZUTF_FREE(decrypt_output);
    }

    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
/*----------------------------------------------------------------------------
 * do_aead_cha20_poly_test
 *
 * Helper function that runs a single CHACHA20_POLY1350 AEAD test.
 */
static int
do_aead_cha20_poly_test(uint32_t VectorIndex,
                        psa_key_id_t key,
                        psa_key_id_t key_ver,
                        psa_algorithm_t alg,
                        bool fencrypt,
                        SymaeadCryptTV_t * Vector_p)

{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t *ciphertext = NULL;
    uint8_t *plaintext = NULL;
    uint8_t *input = NULL;
    size_t ciphertext_length = 0U;
    size_t plaintext_length = 0U;

    ciphertext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen + 16 + 15)); //tag
    fail_if(ciphertext == NULL, "Allocation ", (int)(Vector_p->PtLen + 15 + 16));
    (void)memset(ciphertext, 0, (Vector_p->PtLen + 16 + 15));
    plaintext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen));
    fail_if(plaintext == NULL, "Allocation ", (int)(Vector_p->PtLen));
    (void)memset(plaintext, 0, Vector_p->PtLen);
    input = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen + 16)); // tag
    fail_if(input == NULL, "Allocation ", (int)(Vector_p->PtLen + 16));
    (void)memset(input, 0, (Vector_p->PtLen + 16));

    if (fencrypt)
    {
        Status = psa_aead_encrypt(key, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                                Vector_p->Aad_p, Vector_p->AadLen, Vector_p->Pt_p,
                                Vector_p->PtLen, ciphertext, (Vector_p->CtLen) + 16, &ciphertext_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_encrypt()", Status);
        fail_if(Vector_p->CtLen != (ciphertext_length -16 ), "Length mismatch ", (int)ciphertext_length);
        fail_if(memcmp(Vector_p->Ct_p, ciphertext, Vector_p->CtLen) != 0, "enc data mismatch", VectorIndex);
        fail_if(memcmp(Vector_p->Tag_p, ciphertext+(Vector_p->CtLen), 16) != 0, "enc tag mismatch", VectorIndex);
    }
    else
    {
        memcpy(input, Vector_p->Ct_p, Vector_p->CtLen);
        memcpy(input+(Vector_p->CtLen), Vector_p->Tag_p, Vector_p->TagLen);
        Status = psa_aead_decrypt(key_ver, alg, Vector_p->Nonce_p, Vector_p->NonceLen,
                                Vector_p->Aad_p, Vector_p->AadLen, input,
                                ((Vector_p->CtLen)+16), plaintext, Vector_p->PtLen, &plaintext_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_decrypt()", Status);
        fail_if(Vector_p->PtLen != plaintext_length, "Length mismatch ", (int)plaintext_length);
        fail_if(memcmp(Vector_p->Pt_p, plaintext, Vector_p->PtLen) != 0, "", VectorIndex);
    }

    SFZUTF_FREE(ciphertext);
    SFZUTF_FREE(plaintext);
    SFZUTF_FREE(input);
    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM)
/*----------------------------------------------------------------------------
 * do_AEAD_update_AAD
 *
 * Helper function that runs AEAD update for AAD.
 */
static int
do_AEAD_update_AAD(psa_aead_operation_t *SymContext_p,
                   SymaeadCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;

    Status = psa_aead_update_ad(SymContext_p, Vector_p->Aad_p, Vector_p->AadLen);
    fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);

    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM)
/*----------------------------------------------------------------------------
 * do_AEAD_update
 *
 * Helper function that runs AEAD update.
 */
static int
do_AEAD_update(uint32_t VectorIndex,
               psa_aead_operation_t *SymContext_p,
               bool fencrypt,
               uint8_t *output_ret,
               size_t *output_length,
               SymaeadCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;

    if (fencrypt)
    {
        Status = psa_aead_update(SymContext_p, Vector_p->Pt_p,
                                  Vector_p->PtLen, output_ret, Vector_p->PtLen, output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        if (*output_length != 0)
        {
            fail_if(memcmp(Vector_p->Ct_p, output_ret, *output_length), "enc update data mismatch ", VectorIndex);
        }
    }
    else
    {
        uint8_t *input = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen) + 4);
        fail_if(input == NULL, "Allocation ", (int)(Vector_p->PtLen) + 4);
        (void)memcpy(input, Vector_p->Ct_p, Vector_p->PtLen);
        Status = psa_aead_update(SymContext_p, input,
                                 Vector_p->PtLen, output_ret, Vector_p->PtLen + 4, output_length);
        SFZUTF_FREE(input);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        if (*output_length != 0)
        {
            fail_if(memcmp(Vector_p->Pt_p, output_ret, *output_length), "dec update data mismatch ", VectorIndex);
        }
    }

    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM)
/*----------------------------------------------------------------------------
 * do_AEAD_finish
 *
 * Helper function that runs AEAD finish.
 */
static int
do_AEAD_finish(uint32_t VectorIndex,
               psa_aead_operation_t *SymContext_p,
               uint8_t *ciphertext,
               size_t *output_length,
               SymaeadCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t ciphertext_length = 0U;
    size_t tag_length = 0U;
    uint8_t *tag = NULL;
    size_t tag_size = 0U;

    if (Vector_p->TagLen != 0)
    {
        tag = (uint8_t *)SFZUTF_MALLOC((Vector_p->TagLen));
        fail_if(tag == NULL, "Allocation ", (int)(Vector_p->TagLen));
        tag_size = Vector_p->TagLen;
        (void)memset(tag, 0, Vector_p->TagLen);
    }
    else
    {
        tag = (uint8_t *)SFZUTF_MALLOC(16);
        fail_if(tag == NULL, "Allocation ", (int)(16));
        tag_size = 16;
        (void)memset(tag, 0, 16);
    }

    Status = psa_aead_finish(SymContext_p, &ciphertext[*output_length], Vector_p->CtLen,
                             &ciphertext_length, tag, tag_size,
                             &tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_finish ()", Status);
    fail_if((Vector_p->CtLen - tag_size - *output_length) != ciphertext_length, "final Length mismatch ", (int)ciphertext_length);
    fail_if(memcmp(Vector_p->Ct_p, ciphertext, ciphertext_length + *output_length) != 0, "Final data mismatch", VectorIndex);
    if (Vector_p->TagLen != 0)
    {
        fail_if(Vector_p->TagLen != tag_length, "tag Length mismatch ", (int)tag_length);
        fail_if(memcmp(Vector_p->Tag_p, tag, Vector_p->TagLen) != 0, "tag data mismatch", VectorIndex);
    }
    else
    {
        fail_if(16 != tag_length, "tag Length mismatch ", (int)tag_length);
        fail_if(memcmp(Vector_p->Ct_p+ciphertext_length+*output_length, tag, tag_length) != 0, "tag data mismatch", VectorIndex);
    }
    SFZUTF_FREE(tag);


    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM)
/*----------------------------------------------------------------------------
 * do_aead_verify
 *
 * Helper function that runs AEAD finish verify.
 */
static int
do_aead_verify(uint32_t VectorIndex,
               psa_aead_operation_t *SymContext_p,
               uint8_t *plaintext,
               size_t * output_length,
               SymaeadCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t plaintext_length = 0U;
    size_t tag_length = 0U;
    uint8_t *tag = NULL;

    if (Vector_p->TagLen != 0)
    {
        tag = (uint8_t *)SFZUTF_MALLOC((Vector_p->TagLen));
        fail_if(tag == NULL, "Allocation ", (int)(Vector_p->TagLen));
        (void)memcpy(tag, Vector_p->Tag_p, Vector_p->TagLen);
        tag_length = Vector_p->TagLen;
    }
    else
    {
        tag = (uint8_t *)SFZUTF_MALLOC(16);
        fail_if(tag == NULL, "Allocation ", (int)(16));
        (void)memcpy(tag, &Vector_p->Ct_p[Vector_p->CtLen-16], 16);
        tag_length = 16;
    }

    Status = psa_aead_verify(SymContext_p, &plaintext[*output_length], Vector_p->CtLen,
                              &plaintext_length, tag, tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if((Vector_p->PtLen - *output_length) != plaintext_length, "final Length mismatch ", (int)plaintext_length);
    fail_if(memcmp(Vector_p->Pt_p, plaintext, plaintext_length + *output_length) != 0, "Final data mismatch", VectorIndex);
    SFZUTF_FREE(tag);

    return END_TEST_SUCCES;
}
#endif

#if defined(PSATEST_SYM_ALGO_AES_GCM)
/*----------------------------------------------------------------------------
 * do_AEAD_update_finish_gcm
 *
 * Helper function that runs AEAD GCM update finish/verify.
 */
static int
do_AEAD_update_finish_gcm(uint32_t VectorIndex,
                          psa_aead_operation_t *SymContext_p,
                          psa_aead_operation_t *SymContext_ver_p,
                          SymaeadCryptTV_t * Vector_p)
{
    psa_status_t Status = PSA_ERROR_CORRUPTION_DETECTED;
    uint8_t *ciphertext = NULL;
    size_t ciphertext_size = 0U;
    uint8_t *plaintext = NULL;
    size_t plaintext_size = 0U;
    uint8_t *tag = NULL;
    size_t output_length = 0U;
    size_t ciphertext_length = 0U;
    size_t plaintext_length = 0U;
    size_t tag_length = 0U;

    ciphertext_size = Vector_p->CtLen;
    plaintext_size = Vector_p->PtLen;
    if ((ciphertext_size % 16) != 0)
    {
        ciphertext_size = ciphertext_size + 16 - (Vector_p->CtLen % 16);
        plaintext_size = plaintext_size + 16 - (Vector_p->PtLen % 16);
    }
    ciphertext = (uint8_t *)SFZUTF_MALLOC((Vector_p->CtLen) + 4);
    fail_if(ciphertext == NULL, "Allocation ", (int)(Vector_p->CtLen) + 4);
    (void)memset(ciphertext, 0, Vector_p->CtLen + 4);
    plaintext = (uint8_t *)SFZUTF_MALLOC((Vector_p->PtLen) + 4);
    fail_if(plaintext == NULL, "Allocation ", (int)(Vector_p->PtLen) + 4);
    (void)memset(plaintext, 0, Vector_p->PtLen + 4);
    tag = (uint8_t *)SFZUTF_MALLOC(16);
    fail_if(tag == NULL, "Allocation ", (int)16);
    (void)memset(tag, 0, 16);

    if (Vector_p->AadLen != 0)
    {
        Status = psa_aead_update_ad(SymContext_p, Vector_p->Aad_p, Vector_p->AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    if (Vector_p->PtLen != 0)
    {
        Status = psa_aead_update(SymContext_p, Vector_p->Pt_p,
                                 Vector_p->PtLen, ciphertext, ciphertext_size, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update ()", Status);
        if (output_length != 0)
        {
            fail_if(memcmp(Vector_p->Ct_p, ciphertext, output_length) != 0, "", VectorIndex);
        }
    }
    Status = psa_aead_finish(SymContext_p, &ciphertext[output_length], ciphertext_size,
                      &ciphertext_length, tag, 16,
                      &tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_finish ()", Status);
    fail_if(Vector_p->CtLen != (ciphertext_length + output_length), "Length mismatch ", (int)(ciphertext_length+output_length));

    output_length = 0;
    if (Vector_p->AadLen != 0)
    {
        Status = psa_aead_update_ad(SymContext_ver_p, Vector_p->Aad_p, Vector_p->AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    if (Vector_p->CtLen != 0)
    {
        Status = psa_aead_update(SymContext_ver_p, ciphertext,
                                Vector_p->CtLen, plaintext, plaintext_size, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update ()", Status);
    }
    Status = psa_aead_verify(SymContext_ver_p, &plaintext[output_length], plaintext_size,
                             &plaintext_length, tag, tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if(Vector_p->PtLen != (plaintext_length + output_length), "Length mismatch ", (int)(plaintext_length+output_length));
    fail_if(memcmp(Vector_p->Pt_p, plaintext, Vector_p->PtLen) != 0, "", VectorIndex);

    SFZUTF_FREE(ciphertext);
    SFZUTF_FREE(plaintext);
    SFZUTF_FREE(tag);
    return END_TEST_SUCCES;
}
#endif

#ifdef PSATEST_SYM_ALGO_AES_CCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_ccm
 *
 * Test with aes CCM test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes_ccm)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_CCM;
        TestVector_AES_CCM_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        bool fencrypt;
        psa_key_lifetime_t lifetime;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;

        tv_p = test_vectors_aes_ccm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        uid = 0;
        uid_ver = 0;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else
        {
            /* Default/_i == 0 */
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        fencrypt = true;
        if (do_aead_ccm_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);

        fencrypt = false;
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, uid_ver, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        if (do_aead_ccm_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key_ver);

        test_vectors_aes_ccm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_AES_CCM
START_TEST(test_sym_crypto_aes_ccm_padding)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_CCM;
        TestVector_AES_CCM_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_ccm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        if (do_aead_ccm_test_unpadded(ndx, key, key_ver, Mode, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);

        test_vectors_aes_ccm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_ARIA_CCM
START_TEST(test_sym_crypto_aria_ccm)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_CCM;
        TestVector_ARIA_CCM_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        bool fencrypt;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_ccm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);
        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        fencrypt = true;
        if (do_aead_ccm_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);

        fencrypt = false;
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        if (do_aead_ccm_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key_ver);

        test_vectors_aria_ccm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_AES_CCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_ccm_multipart
 *
 * Test with aes CCM continuation test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes_ccm_multipart)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_CCM_t tv_p;
        psa_algorithm_t Mode = PSA_ALG_CCM;
        psa_aead_operation_t SymContext;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        bool fencrypt;
        psa_key_lifetime_t lifetime;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;

        tv_p = test_vectors_aes_ccm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        uid = 0U;
        uid_ver = 0U;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);

        fencrypt = true;
        memset(&SymContext, 0, sizeof(SymContext));
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

        Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

        Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

        Status = psa_aead_set_nonce(&SymContext, tv_cipher.Nonce_p, tv_cipher.NonceLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

        if (tv_cipher.AadLen != 0)
        {
            if(do_AEAD_update_AAD(&SymContext, &tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        uint8_t *output_enc = (uint8_t *)SFZUTF_MALLOC(tv_cipher.CtLen);
        (void)memset(output_enc, 0, tv_cipher.CtLen);
        size_t output_length = 0;
        if (tv_cipher.PtLen != 0)
        {
            if(do_AEAD_update(ndx, &SymContext, fencrypt, output_enc, &output_length, &tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        if (do_AEAD_finish(ndx, &SymContext, output_enc, &output_length, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        SFZUTF_FREE(output_enc);
        (void)psa_destroy_key(key);

        memset(&SymContext, 0, sizeof(SymContext));
        fencrypt = false;

        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, uid_ver, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

        Status = psa_aead_decrypt_setup(&SymContext, key_ver, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_aead_decrypt_setup()=", Status);

        Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

        Status = psa_aead_set_nonce(&SymContext, tv_cipher.Nonce_p, tv_cipher.NonceLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

        if (tv_cipher.AadLen != 0)
        {
            if(do_AEAD_update_AAD(&SymContext, &tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        uint8_t *output_ver = (uint8_t *)SFZUTF_MALLOC((tv_cipher.CtLen));
        (void)memset(output_ver, 0, tv_cipher.CtLen);
        output_length = 0;
        if (tv_cipher.PtLen != 0)
        {
            if(do_AEAD_update(ndx, &SymContext, fencrypt, output_ver, &output_length ,&tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
            }
            else
            {
                Success++;
            }
        }

        if (do_aead_verify(ndx, &SymContext, output_ver, &output_length,&tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        SFZUTF_FREE(output_ver);
        (void)psa_destroy_key(key_ver);

        test_vectors_aes_ccm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_AES_CCM
START_TEST(test_sym_crypto_aes_ccm_Gen_nonce)
{
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;
    TestVector_AES_CCM_t tv_p;
    psa_algorithm_t Mode = PSA_ALG_CCM;
    psa_aead_operation_t SymContext;
    psa_aead_operation_t SymContext_ver;
    SymaeadCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    psa_key_lifetime_t lifetime;
    uint8_t Nonce[16] = {0};
    size_t nonce_size = 16;
    size_t nonce_length = 0;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    tv_p = test_vectors_aes_ccm_get(2);
    fail_if(tv_p == NULL, "No vector found", 2);

    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&SymContext_ver, 0, sizeof(SymContext_ver));

    Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

    Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_generate_nonce(&SymContext, Nonce, nonce_size, &nonce_length);
    fail_if(Status != PSA_SUCCESS, "psa_aead_generate_nonce()=", Status);
    fail_if(nonce_length != 13, "final Length mismatch ", (int)nonce_length);

    if (tv_cipher.AadLen != 0)
    {
        Status = psa_aead_update_ad(&SymContext, tv_cipher.Aad_p, tv_cipher.AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    uint8_t *output_enc = (uint8_t *)SFZUTF_MALLOC(tv_cipher.CtLen);
    fail_if(output_enc == NULL, "Allocation ", (int)(tv_cipher.CtLen));
    (void)memset(output_enc, 0, tv_cipher.CtLen);
    uint8_t *output_dec = (uint8_t *)SFZUTF_MALLOC(tv_cipher.CtLen);
    fail_if(output_dec == NULL, "Allocation ", (int)(tv_cipher.CtLen));
    (void)memset(output_dec, 0, tv_cipher.CtLen);
    size_t output_length = 0;
    size_t ciphertext_length = 0;
    uint8_t *tag = (uint8_t *)SFZUTF_MALLOC(16);
    fail_if(tag == NULL, "Allocation ", (int)(16));
    size_t tag_size = 16;
    size_t tag_length = 0;
    (void)memset(tag, 0, 16);

    // start encrypt
    if (tv_cipher.PtLen != 0)
    {
        Status = psa_aead_update(&SymContext, tv_cipher.Pt_p,
                                 tv_cipher.PtLen, output_enc, tv_cipher.CtLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
    }

    Status = psa_aead_finish(&SymContext, &output_enc[output_length], tv_cipher.CtLen,
                             &ciphertext_length, tag, tag_size,
                             &tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_finish ()", Status);

    // start decrypt
    Status = psa_aead_decrypt_setup(&SymContext_ver, key_ver, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext_ver, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_set_nonce(&SymContext_ver, Nonce, nonce_length);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

    if (tv_cipher.AadLen != 0)
    {
        Status = psa_aead_update_ad(&SymContext_ver, tv_cipher.Aad_p, tv_cipher.AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    output_length = 0;
    if (tv_cipher.PtLen != 0)
    {
        Status = psa_aead_update(&SymContext_ver, output_enc, tv_cipher.PtLen,
                                 output_dec, tv_cipher.CtLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
    }

    Status = psa_aead_verify(&SymContext_ver, &output_dec[output_length], tv_cipher.CtLen,
                             &ciphertext_length, tag, tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if(tv_cipher.PtLen != (ciphertext_length + output_length), "final Length mismatch ", (int)(ciphertext_length + output_length));
    if (memcmp(tv_cipher.Pt_p, output_dec, tv_cipher.PtLen) != 0)
    {
        LOG_CRIT("Final data mismatch\n");
        Failed++;
    }
    else
    {
        Success++;
    }

    SFZUTF_FREE(output_enc);
    SFZUTF_FREE(output_dec);
    SFZUTF_FREE(tag);
    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);

    test_vectors_aes_ccm_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif

#ifdef PSATEST_SYM_ALGO_AES_GCM
START_TEST(test_sym_crypto_aes_gcm_Gen_nonce)
{
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;
    TestVector_AES_GCM_t tv_p;
    psa_algorithm_t Mode = PSA_ALG_GCM;
    psa_aead_operation_t SymContext;
    psa_aead_operation_t SymContext_ver;
    SymaeadCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    psa_key_lifetime_t lifetime;
    uint8_t Nonce[16] = {0};
    size_t nonce_size = 16;
    size_t nonce_length = 0;
    const uint8_t *input;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    tv_p = test_vectors_aes_gcm_get(2);
    fail_if(tv_p == NULL, "No vector found", 2);

    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->IV_p, tv_p->IVLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, tv_p->TagLen);

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&SymContext_ver, 0, sizeof(SymContext_ver));

    Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

    Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_generate_nonce(&SymContext, Nonce, nonce_size, &nonce_length);
    fail_if(Status != PSA_SUCCESS, "psa_aead_generate_nonce()=", Status);
    fail_if(nonce_length != 16, "final Length mismatch ", (int)nonce_length);

    if (tv_cipher.AadLen != 0)
    {
        Status = psa_aead_update_ad(&SymContext, tv_cipher.Aad_p, tv_cipher.AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad enc()", Status);
    }

    uint8_t *output_enc = (uint8_t *)SFZUTF_MALLOC(tv_cipher.CtLen + 4);
    fail_if(output_enc == NULL, "Allocation ", (int)(tv_cipher.CtLen + 4));
    (void)memset(output_enc, 0, tv_cipher.CtLen + 4);
    uint8_t *output_dec = (uint8_t *)SFZUTF_MALLOC(tv_cipher.CtLen + 4);
    fail_if(output_dec == NULL, "Allocation ", (int)(tv_cipher.CtLen + 4));
    (void)memset(output_dec, 0, tv_cipher.CtLen + 4);
    size_t output_length = 0;
    size_t ciphertext_length = 0;
    uint8_t *tag = (uint8_t *)SFZUTF_MALLOC(16);
    fail_if(tag == NULL, "Allocation ", (int)(16));
    size_t tag_size = 16;
    size_t tag_length = 0;
    (void)memset(tag, 0, 16);
    size_t Total_output_len = 0;

    // start encrypt
    if (tv_cipher.PtLen != 0)
    {
        input = tv_cipher.Pt_p;
        Status = psa_aead_update(&SymContext, input, 17,
                                 output_enc, tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[17], 17,
                                 &output_enc[Total_output_len], tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[34], 26,
                                 &output_enc[Total_output_len], tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;

    }

    Status = psa_aead_finish(&SymContext, &output_enc[Total_output_len], tv_cipher.CtLen + 4,
                             &ciphertext_length, tag, tag_size,
                             &tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_finish ()", Status);

    // start decrypt
    Status = psa_aead_decrypt_setup(&SymContext_ver, key_ver, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext_ver, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_set_nonce(&SymContext_ver, Nonce, nonce_length);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

    if (tv_cipher.AadLen != 0)
    {
        Status = psa_aead_update_ad(&SymContext_ver, tv_cipher.Aad_p, tv_cipher.AadLen);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad dec()", Status);
    }

    output_length = 0;
    Total_output_len = 0;
    ciphertext_length = 0;
    if (tv_cipher.PtLen != 0)
    {
        input = output_enc;
        Status = psa_aead_update(&SymContext_ver, input, 18,
                                 output_dec, tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext_ver, &input[18], 17,
                                 &output_dec[Total_output_len], tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext_ver, &input[35], 25,
                                 &output_dec[Total_output_len], tv_cipher.CtLen + 4, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;
    }

    Status = psa_aead_verify(&SymContext_ver, &output_dec[Total_output_len], tv_cipher.CtLen + 4,
                             &ciphertext_length, tag, tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if(tv_cipher.PtLen != (ciphertext_length + Total_output_len), "final Length mismatch ", (int)(ciphertext_length + Total_output_len));
    if (memcmp(tv_cipher.Pt_p, output_dec, tv_cipher.PtLen) != 0)
    {
        Failed++;
        LOG_CRIT("Final data mismatch\n");
    }
    else
    {
        Success++;
    }

    SFZUTF_FREE(output_enc);
    SFZUTF_FREE(output_dec);
    SFZUTF_FREE(tag);
    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);

    test_vectors_aes_gcm_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif

#ifdef PSATEST_SYM_ALGO_AES_CCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_ccm_mul_padding
 *
 * Test with aes CCM continuation with chunk inputs that is not block aligned test.
 */
START_TEST(test_sym_crypto_aes_ccm_mul_padding)
{
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;
    TestVector_AES_CCM_t tv_p;
    psa_algorithm_t Mode = PSA_ALG_CCM;
    psa_aead_operation_t SymContext;
    psa_aead_operation_t SymContext_ver;
    SymaeadCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_id_t key_ver;
    psa_key_lifetime_t lifetime;
    const uint8_t *input;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    tv_p = test_vectors_aes_ccm_get(4);
    fail_if(tv_p == NULL, "No vector found", 4);

    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);

    memset(&SymContext, 0, sizeof(SymContext));
    memset(&SymContext_ver, 0, sizeof(SymContext_ver));

    Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

    Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen - 1);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_set_nonce(&SymContext, tv_cipher.Nonce_p, tv_cipher.NonceLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

    if (tv_cipher.AadLen != 0)
    {
        input = tv_cipher.Aad_p;
        Status = psa_aead_update_ad(&SymContext, input, 16);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);

        Status = psa_aead_update_ad(&SymContext, &input[16], 8);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);

        Status = psa_aead_update_ad(&SymContext, &input[24], 8);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    uint8_t *output_enc = (uint8_t *)SFZUTF_MALLOC(tv_cipher.PtLen - 1);
    fail_if(output_enc == NULL, "Allocation ", (int)(tv_cipher.PtLen - 1));
    (void)memset(output_enc, 0, tv_cipher.PtLen - 1);
    uint8_t *output_dec = (uint8_t *)SFZUTF_MALLOC(tv_cipher.PtLen - 1);
    fail_if(output_dec == NULL, "Allocation ", (int)(tv_cipher.PtLen - 1));
    (void)memset(output_dec, 0, tv_cipher.PtLen - 1);
    size_t output_length = 0;
    size_t ciphertext_length = 0;
    uint8_t *tag = (uint8_t *)SFZUTF_MALLOC(16);
    fail_if(tag == NULL, "Allocation ", (int)(16));
    size_t tag_size = 16;
    size_t tag_length = 0;
    (void)memset(tag, 0, 16);
    size_t Total_output_len = 0;

    // start encrypt
    if (tv_cipher.PtLen != 0)
    {
        input = tv_cipher.Pt_p;
        Status = psa_aead_update(&SymContext, input, 16,
                                 output_enc, tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[16], 8,
                                 &output_enc[Total_output_len], tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[24], 7,
                                 &output_enc[Total_output_len], tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update enc()", Status);
        Total_output_len = Total_output_len + output_length;
    }

    Status = psa_aead_finish(&SymContext, &output_enc[Total_output_len], tv_cipher.PtLen - 1,
                             &ciphertext_length, tag, tag_size,
                             &tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_finish ()", Status);
    fail_if(tv_cipher.PtLen - 1 != (ciphertext_length + Total_output_len), "final Length mismatch ", (int)(ciphertext_length + Total_output_len));

    // start decrypt
    Status = psa_aead_decrypt_setup(&SymContext_ver, key_ver, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_decrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext_ver, tv_cipher.AadLen, tv_cipher.PtLen - 1);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    Status = psa_aead_set_nonce(&SymContext_ver, tv_cipher.Nonce_p, tv_cipher.NonceLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

    if (tv_cipher.AadLen != 0)
    {
        input = tv_cipher.Aad_p;
        Status = psa_aead_update_ad(&SymContext_ver, input, 16);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
        Status = psa_aead_update_ad(&SymContext_ver, &input[16], 8);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
        Status = psa_aead_update_ad(&SymContext_ver, &input[24], 8);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update_ad()", Status);
    }

    output_length = 0;
    Total_output_len = 0;
    ciphertext_length = 0;
    if (tv_cipher.PtLen != 0)
    {
        input = output_enc;
        Status = psa_aead_update(&SymContext_ver, input, 16,
                                 output_dec, tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext_ver, &input[16], 8,
                                 &output_dec[Total_output_len], tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext_ver, &input[24], 7,
                                 &output_dec[Total_output_len], tv_cipher.PtLen - 1, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;
    }

    Status = psa_aead_verify(&SymContext_ver, &output_dec[Total_output_len], tv_cipher.PtLen - 1,
                             &ciphertext_length, tag, tag_length);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if(tv_cipher.PtLen - 1 != (ciphertext_length + Total_output_len), "final Length mismatch ", (int)(ciphertext_length + Total_output_len));
    if (memcmp(tv_cipher.Pt_p, output_dec, tv_cipher.PtLen - 1) != 0)
    {
        Failed++;
        LOG_CRIT("Final data mismatch\n");
    }
    else
    {
        Success++;
    }

    SFZUTF_FREE(output_enc);
    SFZUTF_FREE(output_dec);
    SFZUTF_FREE(tag);
    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);

    test_vectors_aes_ccm_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif

#ifdef PSATEST_SYM_ALGO_AES_GCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_gcm
 *
 * Test with aes CCM test vectors. Intended to be called 5 times.
 * _i = 0 -> PSA Key Store in RAM in cleartext.
 * _i = 1 -> PSA Key Store in NVM in cleartext.
 * _i = 2 -> HSM Asset Store in Asset store in cleartext.
 * _i = 3 -> HSM Asset Store in RAM in wrapped format.
 * _i = 4 -> HSM Asset Store in NVM in wrapped format.
 */
START_TEST(test_sym_crypto_aes_gcm)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_GCM;
        TestVector_AES_GCM_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;
        psa_key_id_t uid;
        psa_key_id_t uid_ver;

        tv_p = test_vectors_aes_gcm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->IVLen < 12) || (tv_p->IVLen > 16))
        {
            LOG_WARN("GCM IV Length is not support%d\n",tv_p.IVLen);
            test_vectors_aes_gcm_release(tv_p);
            continue;
        }

        uid = 0U;
        uid_ver = 0U;
        if (_i == 1)
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else if (_i == 2)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_HSM_ASSET_STORE;
        }
        else if (_i == 3)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }
        else if (_i == 4)
        {
            lifetime = (PSA_KEY_LOCATION_PRIMARY_SECURE_ELEMENT << 8) | PSA_KEY_PERSISTENCE_DEFAULT;
            uid = 1U;
            uid_ver = 2U;
        }
        else
        {
            lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        }

        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->IV_p, tv_p->IVLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, tv_p->TagLen);
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, uid, &tv_cipher);
        unsupported_if((PSA_ERROR_HARDWARE_FAILURE == Status), "No Root key");
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, uid_ver, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        if (do_aead_gcm_test(ndx, key, key_ver, Mode, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aes_gcm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_ARIA_GCM
START_TEST(test_sym_crypto_aria_gcm)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_GCM;
        TestVector_ARIA_GCM_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aria_gcm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->IVLen < 12) || (tv_p->IVLen > 16))
        {
            LOG_WARN("GCM IV Length is not support%d\n",tv_p.IVLen);
            test_vectors_aria_gcm_release(tv_p);
            continue;
        }

        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->IV_p, tv_p->IVLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, tv_p->TagLen);
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        if (do_aead_gcm_test(ndx, key, key_ver, Mode, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aria_gcm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_AES_GCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_gcm_multipart
 */
START_TEST(test_sym_crypto_aes_gcm_multipart)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ; ndx++)
    {
        TestVector_AES_GCM_t tv_p;
        psa_algorithm_t Mode = PSA_ALG_GCM;
        psa_aead_operation_t SymContext;
        psa_aead_operation_t SymContext_ver;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        bool fencrypt;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_aes_gcm_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }
        if ((tv_p->IVLen < 12) || (tv_p->IVLen > 16))
        {
            LOG_WARN("GCM IV Length is not support%d\n",tv_p.IVLen);
            test_vectors_aes_gcm_release(tv_p);
            continue;
        }

        memset(&tv_cipher, 0, sizeof(tv_cipher));
        lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
        setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->IV_p, tv_p->IVLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, tv_p->TagLen);

        memset(&SymContext, 0, sizeof(SymContext));
        fencrypt = false;

        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

        Status = psa_aead_decrypt_setup(&SymContext, key_ver, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_aead_decrypt_setup()=", Status);

        Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

        uint8_t * nonce = (uint8_t *)SFZUTF_MALLOC(16);
        size_t nonce_length = tv_cipher.NonceLen;
        (void)memcpy(nonce, tv_cipher.Nonce_p, tv_cipher.NonceLen);
        if (tv_cipher.NonceLen == 12)
        {
            memcpy(&nonce[tv_cipher.NonceLen], "\x00\x00\x00\x01", 4);
            nonce_length = 16;
        }
        Status = psa_aead_set_nonce(&SymContext, nonce, nonce_length);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

        if (tv_cipher.AadLen != 0)
        {
            if(do_AEAD_update_AAD(&SymContext, &tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
                SFZUTF_FREE(nonce);
            }
            else
            {
                Success++;
            }
        }

        uint8_t *output_ver = (uint8_t *)SFZUTF_MALLOC((tv_cipher.PtLen) + 4);
        size_t output_length = 0;
        (void)memset(output_ver, 0, tv_cipher.PtLen + 4);
        if (tv_cipher.PtLen != 0)
        {
            if(do_AEAD_update(ndx, &SymContext, fencrypt, output_ver, &output_length, &tv_cipher) != END_TEST_SUCCES)
            {
                LOG_CRIT("Processed vector %d\n", ndx);
                Failed++;
                SFZUTF_FREE(nonce);
                SFZUTF_FREE(output_ver);
            }
            else
            {
                Success++;
            }
        }

        if (do_aead_verify(ndx, &SymContext, output_ver, &output_length, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
            SFZUTF_FREE(output_ver);
            SFZUTF_FREE(nonce);
        }
        else
        {
            Success++;
            SFZUTF_FREE(output_ver);
            SFZUTF_FREE(nonce);
        }
        (void)psa_destroy_key(key_ver);

        memset(&SymContext, 0, sizeof(SymContext));
        memset(&SymContext_ver, 0, sizeof(SymContext_ver));

        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);

        Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

        Status = psa_aead_decrypt_setup(&SymContext_ver, key_ver, Mode);
        fail_if(Status != PSA_SUCCESS, "psa_aead_decrypt_setup()=", Status);

        Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

        Status = psa_aead_set_lengths(&SymContext_ver, tv_cipher.AadLen, tv_cipher.CtLen);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

        uint8_t * nonce_enc = (uint8_t *)SFZUTF_MALLOC(16);
        size_t nonce_len = tv_cipher.NonceLen;
        (void)memcpy(nonce_enc, tv_cipher.Nonce_p, tv_cipher.NonceLen);
        if (tv_cipher.NonceLen == 12)
        {
            memcpy(&nonce_enc[tv_cipher.NonceLen], "\x00\x00\x00\x01", 4);
            nonce_len = 16;
        }
        Status = psa_aead_set_nonce(&SymContext, nonce_enc, nonce_len);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

        Status = psa_aead_set_nonce(&SymContext_ver, nonce_enc, nonce_len);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

        if (do_AEAD_update_finish_gcm(ndx, &SymContext, &SymContext_ver, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            SFZUTF_FREE(nonce_enc);
            Failed++;
        }
        else
        {
            SFZUTF_FREE(nonce_enc);
            Success++;
        }

        Status = psa_aead_abort(&SymContext);
        fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);
        fail_if(SymContext.Mode != PSA_ALG_NONE, "psa_aead_abort()=", SymContext.Mode);
        (void)psa_destroy_key(key);
        (void)psa_destroy_key(key_ver);
        test_vectors_aes_gcm_release(tv_p);
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

#ifdef PSATEST_SYM_ALGO_AES_GCM
/*----------------------------------------------------------------------------
 * test_sym_crypto_aes_gcm_multipart
 */
START_TEST(test_sym_crypto_aes_gcm_multipart_chunks)
{
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;
    TestVector_AES_GCM_t tv_p;
    psa_algorithm_t Mode = PSA_ALG_GCM;
    psa_aead_operation_t SymContext;
    SymaeadCryptTV_t tv_cipher;
    psa_key_id_t key;
    psa_key_lifetime_t lifetime;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    tv_p = test_vectors_aes_gcm_get(1); // AESGCM_128_tv1_P 64 byte input
    fail_if(tv_p == NULL, "No vector found", 0);
    fail_if(((tv_p->IVLen < 12) || (tv_p->IVLen > 16)), "GCM IV Length is not suppor", tv_p->IVLen);

    memset(&tv_cipher, 0, sizeof(tv_cipher));
    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;
    setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->IV_p, tv_p->IVLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, tv_p->TagLen);

    memset(&SymContext, 0, sizeof(SymContext));

    Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);

    Status = psa_aead_decrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_decrypt_setup()=", Status);

    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);

    uint8_t * nonce = (uint8_t *)SFZUTF_MALLOC(16);
    size_t nonce_length = tv_cipher.NonceLen;
    (void)memcpy(nonce, tv_cipher.Nonce_p, tv_cipher.NonceLen);
    if (tv_cipher.NonceLen == 12)
    {
        memcpy(&nonce[tv_cipher.NonceLen], "\x00\x00\x00\x01", 4);
        nonce_length = 16;
    }
    Status = psa_aead_set_nonce(&SymContext, nonce, nonce_length);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_nonce()=", Status);

    if (tv_cipher.AadLen != 0)
    {
        if(do_AEAD_update_AAD(&SymContext, &tv_cipher) != END_TEST_SUCCES)
        {
            Failed++;
            SFZUTF_FREE(nonce);
        }
        else
        {
            Success++;
        }
    }

    uint8_t *output_ver = (uint8_t *)SFZUTF_MALLOC(tv_cipher.PtLen);
    fail_if(output_ver == NULL, "Allocation ", (int)(tv_cipher.PtLen));
    (void)memset(output_ver, 0, tv_cipher.PtLen);
    size_t output_length = 0;
    size_t plaintext_length = 0;
    const uint8_t *input;
    size_t Total_output_len = 0;
    if (tv_cipher.PtLen != 0)
    {
        input = tv_cipher.Ct_p;
        Status = psa_aead_update(&SymContext, input, 16,
                                 output_ver, tv_cipher.PtLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[16], 17,
                                 output_ver, tv_cipher.PtLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;

        Status = psa_aead_update(&SymContext, &input[33], 31,
                                 &output_ver[Total_output_len], tv_cipher.PtLen, &output_length);
        fail_if(PSA_SUCCESS != Status, "psa_aead_update dec()", Status);
        Total_output_len = Total_output_len + output_length;
    }

    Status = psa_aead_verify(&SymContext, &output_ver[Total_output_len], tv_cipher.PtLen,
                              &plaintext_length, tv_cipher.Tag_p, tv_cipher.TagLen);
    fail_if(PSA_SUCCESS != Status, "psa_aead_verify ()", Status);
    fail_if(tv_cipher.PtLen != (Total_output_len + output_length), "final Length mismatch ", (int)(Total_output_len + output_length));
    if (memcmp(tv_cipher.Pt_p, output_ver, tv_cipher.PtLen) != 0)
    {
        Failed++;
    }
    else
    {
        Success++;
    }

    (void)psa_destroy_key(key);
    SFZUTF_FREE(output_ver);
    SFZUTF_FREE(nonce);
    test_vectors_aes_gcm_release(tv_p);

    if ((Failed > 0) || (Success == 0))
    {
        LOG_CRIT("%d:%s:%d> FAILED: #wrong tests %d of %d\n",
                 SFZUTF_GETPID(), __func__, __LINE__, Failed, (Success + Failed));
        return END_TEST_FAIL;
    }
}
END_TEST
#endif

#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
START_TEST(test_sym_crypto_chacha20_poly1305)
{
    uint32_t ndx;
    int Failed = 0;
    int Success = 0;
    psa_status_t Status;

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    for (ndx = 0U; ndx < 1; ndx++)
    {
        psa_algorithm_t Mode = PSA_ALG_CHACHA20_POLY1305;
        TestVector_ChaCha20_Poly1305_t tv_p;
        SymaeadCryptTV_t tv_cipher;
        psa_key_id_t key;
        psa_key_id_t key_ver;
        bool fencrypt;
        psa_key_lifetime_t lifetime;

        tv_p = test_vectors_chacha20_poly1305_get(ndx);
        if (tv_p == NULL)
        {
            break;
        }

        setupaeadTVctx(&tv_cipher, tv_p->PlainData_p, tv_p->DataLen, tv_p->Aad_p, tv_p->AadLen, tv_p->CipherData_p, tv_p->DataLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, tv_p->Tag_p, 16U);
        lifetime = PSA_KEY_LOCATION_LOCAL_STORAGE | PSA_KEY_PERSISTENCE_VOLATILE;
        Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_CHACHA20, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
        fencrypt = true;
        if (do_aead_cha20_poly_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key);
        fencrypt = false;
        Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_CHACHA20, lifetime, 0, &tv_cipher);
        fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
        if (do_aead_cha20_poly_test(ndx, key, key_ver, Mode, fencrypt, &tv_cipher) != END_TEST_SUCCES)
        {
            LOG_CRIT("Processed vector %d\n", ndx);
            Failed++;
        }
        else
        {
            Success++;
        }
        (void)psa_destroy_key(key_ver);
        test_vectors_chacha20_poly1305_release(tv_p);
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

#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM) || \
    (defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305))
START_TEST(test_aead_invalid_arguments)
{
    uint32_t ndx = 2;
    psa_status_t Status;
    psa_algorithm_t Mode = PSA_ALG_CCM;
    TestVector_AES_CCM_t tv_p;
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    TestVector_ARIA_CCM_t tv_p_aria;
#endif
    SymaeadCryptTV_t tv_cipher;
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    SymaeadCryptTV_t tv_cipher_aria;
#endif
    psa_aead_operation_t SymContext = { 0 };
    psa_key_id_t key = PSA_KEY_ID_NULL;
    psa_key_id_t key_ver = PSA_KEY_ID_NULL;
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    psa_key_id_t key_aria = PSA_KEY_ID_NULL;
    psa_key_id_t key_aria_ver = PSA_KEY_ID_NULL;
#endif
    psa_key_lifetime_t lifetime;
    size_t ciphertext_length = 0;
    size_t nonce_length = 0;
    size_t output_length = 0;
    size_t tag_length = 0;
    uint8_t ciphertext[128] = { 0 };
    uint8_t Nonce[16] = { 0 };
    uint8_t output[16] = { 0 };
    uint8_t tag[16] = { 0 };

    Status = psa_crypto_init();
    fail_if(PSA_SUCCESS != Status, "psa_crypto_init()", Status);

    tv_p = test_vectors_aes_ccm_get(ndx);
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    tv_p_aria = test_vectors_aria_ccm_get(ndx);
#endif
    lifetime = (PSA_KEY_LOCATION_LOCAL_STORAGE << 8) | PSA_KEY_PERSISTENCE_VOLATILE;

    setupaeadTVctx(&tv_cipher, tv_p->Pt_p, tv_p->PtLen, tv_p->Aad_p, tv_p->AadLen, tv_p->Ct_p, tv_p->CtLen, tv_p->Nonce_p, tv_p->NonceLen, tv_p->Key_p, tv_p->KeyLen, NULL, 0U);
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    setupaeadTVctx(&tv_cipher_aria, tv_p_aria->Pt_p, tv_p_aria->PtLen, tv_p_aria->Aad_p, tv_p_aria->AadLen, tv_p_aria->Ct_p,
                   tv_p_aria->CtLen, tv_p_aria->Nonce_p, tv_p_aria->NonceLen, tv_p_aria->Key_p, tv_p_aria->KeyLen, NULL, 0U);
#endif
    Status = setupaeadkey(&key, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey enc()", Status);
    Status = setupaeadkey(&key_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_AES, lifetime, 0U, &tv_cipher);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey dec()", Status);
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    Status = setupaeadkey(&key_aria, Mode, PSA_KEY_USAGE_ENCRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher_aria);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey aria()", Status);
    Status = setupaeadkey(&key_aria_ver, Mode, PSA_KEY_USAGE_DECRYPT, PSA_KEY_TYPE_ARIA, lifetime, 0U, &tv_cipher_aria);
    fail_if(PSA_SUCCESS != Status, "setupaeadkey aria()", Status);
#endif

    // key not created
    (void)psa_destroy_key(5); // make sure key is not used
    Status = psa_aead_encrypt(5, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_aead_encrypt()=", Status);
    // invalid key usage flag
    Status = psa_aead_encrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_aead_encrypt()=", Status);
    // invalid alg
    Status = psa_aead_encrypt(key, PSA_ALG_SHA_224, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // NULL additional data with AAD size
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              NULL, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // NULL plaintext with ptext size
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, NULL,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // NULL ciphertext buffer
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, NULL, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // ciphertext size 0
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, 0, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // NULL ciphertext length
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // ciphertext buffer size is small
    Status = psa_aead_encrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_aead_encrypt()=", Status);
    // NULL nonce
    Status = psa_aead_encrypt(key, Mode, NULL, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
    // wrong Nonce size for GCM
    Status = psa_aead_encrypt(key, PSA_ALG_GCM, tv_cipher.Nonce_p, 12,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
    // wrong Nonce size for CHACHA20POLY1305
    Status = psa_aead_encrypt(key, PSA_ALG_CHACHA20_POLY1305, tv_cipher.Nonce_p, 16,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, (tv_cipher.CtLen) + 16, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt()=", Status);
#endif
    // key not created
    Status = psa_aead_decrypt(5, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_aead_decrypt()=", Status);
    // invalid key usage flag
    Status = psa_aead_decrypt(key, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_aead_decrypt()=", Status);
    // invalid alg
    Status = psa_aead_decrypt(key_ver, PSA_ALG_SHA_224, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // NULL additional data with AAD size
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              NULL, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // NULL plaintext with ptext size
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, NULL, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // NULL ciphertext buffer
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, NULL,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // ciphertext length 0
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              0, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // NULL plaintext length
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // plaintext buffer size is small
    Status = psa_aead_decrypt(key_ver, Mode, tv_cipher.Nonce_p, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, 15, &ciphertext_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_aead_decrypt()=", Status);
    // ciphertext size smaller than plaintext size
    Status = psa_aead_decrypt(key_ver, Mode, NULL, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.PtLen, ciphertext, tv_cipher.CtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // NULL nonce
    Status = psa_aead_decrypt(key_ver, Mode, NULL, tv_cipher.NonceLen,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
    // wrong Nonce size for GCM
    Status = psa_aead_decrypt(key_ver, PSA_ALG_GCM, tv_cipher.Nonce_p, 12,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
    // wrong Nonce size for CHACHA20POLY1305
    Status = psa_aead_decrypt(key_ver, PSA_ALG_CHACHA20_POLY1305, tv_cipher.Nonce_p, 16,
                              tv_cipher.Aad_p, tv_cipher.AadLen, tv_cipher.Pt_p,
                              tv_cipher.CtLen, ciphertext, tv_cipher.PtLen, &ciphertext_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt()=", Status);
#endif
    // key not created
    Status = psa_aead_encrypt_setup(&SymContext, 5, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_aead_encrypt_setup()=", Status);
    // invalid key usage flag
    Status = psa_aead_encrypt_setup(&SymContext, key_ver, Mode);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_aead_encrypt_setup()=", Status);
    // NULL operation
    Status = psa_aead_encrypt_setup(NULL, key, Mode);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt_setup()=", Status);
    // invalid alg
    Status = psa_aead_encrypt_setup(&SymContext, key, PSA_ALG_SHA_224);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt_setup()=", Status);
    // wrong state
    SymContext.aead_state = PSA_AEAD_STATE_SETUP;
    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_encrypt_setup()=", Status);
    // wrong key type
    SymContext.aead_state = PSA_AEAD_STATE_INIT;
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    Status = psa_aead_encrypt_setup(&SymContext, key_aria, Mode);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_aead_encrypt_setup()=", Status);
#endif
#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
    // Do not support CHACHA20POLY1305 continuation
    Status = psa_aead_encrypt_setup(&SymContext, key, PSA_ALG_CHACHA20_POLY1305);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_encrypt_setup()=", Status);
#endif
    // key not created
    Status = psa_aead_decrypt_setup(&SymContext, 5, Mode);
    fail_if(Status != PSA_ERROR_INVALID_HANDLE, "psa_aead_decrypt_setup()=", Status);
    // invalid key usage flag
    Status = psa_aead_decrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_ERROR_NOT_PERMITTED, "psa_aead_decrypt_setup()=", Status);
    // NULL operation
    Status = psa_aead_decrypt_setup(NULL, key_ver, Mode);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt_setup()=", Status);
    // invalid alg
    Status = psa_aead_decrypt_setup(&SymContext, key_ver, PSA_ALG_SHA_224);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt_setup()=", Status);
    // wrong state
    SymContext.aead_state = PSA_AEAD_STATE_SETUP;
    Status = psa_aead_decrypt_setup(&SymContext, key_ver, Mode);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_decrypt_setup()=", Status);
    // wrong key type
    SymContext.aead_state = PSA_AEAD_STATE_INIT;
    Status = psa_aead_decrypt_setup(&SymContext, key_aria_ver, Mode);
    fail_if(Status != PSA_ERROR_NOT_SUPPORTED, "psa_aead_decrypt_setup()=", Status);
#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
    // Do not support CHACHA20POLY1305 continuation
    Status = psa_aead_decrypt_setup(&SymContext, key_ver, PSA_ALG_CHACHA20_POLY1305);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_decrypt_setup()=", Status);
#endif
    //NULL operation
    Status = psa_aead_set_lengths(NULL, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_lengths()=", Status);
    // aad size and ptext size are zero
    Status = psa_aead_set_lengths(&SymContext, 0, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_lengths()=", Status);
    // bad state not setup
    SymContext.aead_state = PSA_AEAD_STATE_INIT;
    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_set_lengths()=", Status);

    // NULL operation
    Status = psa_aead_generate_nonce(NULL, Nonce, 16, &nonce_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_generate_nonce()=", Status);
    // NULL Nonce buffer
    Status = psa_aead_generate_nonce(&SymContext, NULL, 16, &nonce_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_generate_nonce()=", Status);
    // nonce size is 0
    Status = psa_aead_generate_nonce(&SymContext, Nonce, 0, &nonce_length);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_generate_nonce()=", Status);
    // NULL nonce length
    Status = psa_aead_generate_nonce(&SymContext, Nonce, 16, NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_generate_nonce()=", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_INIT;
    Status = psa_aead_generate_nonce(&SymContext, Nonce, 16, &nonce_length);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_generate_nonce()=", Status);
    // Create context for encrypt
    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);
    // set length for encrypt
    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);
    // nonce buffer size small
    Status = psa_aead_generate_nonce(&SymContext, Nonce, 11, &nonce_length);
    fail_if(Status != PSA_ERROR_BUFFER_TOO_SMALL, "psa_aead_generate_nonce()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_aead_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_aead_abort()=", Status);

    //NULL operation
    Status = psa_aead_set_nonce(NULL, Nonce, 16);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_nonce()=", Status);
    // NULL Nonce buffer
    Status = psa_aead_set_nonce(&SymContext, NULL, 16);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_nonce()=", Status);
    // nonce size is 0
    Status = psa_aead_set_nonce(&SymContext, Nonce, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_nonce()=", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_INIT;
    Status = psa_aead_set_nonce(&SymContext, Nonce, 16);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_set_nonce()=", Status);

    // Create context for encrypt
    Status = psa_aead_encrypt_setup(&SymContext, key, Mode);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);
    // set length for encrypt
    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);
    // wrong nonce size
    Status = psa_aead_set_nonce(&SymContext, Nonce, 6);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_nonce()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_aead_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_aead_abort()=", Status);

    // Create context for encrypt
    Status = psa_aead_encrypt_setup(&SymContext, key, PSA_ALG_GCM);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);
    // set length for encrypt
    Status = psa_aead_set_lengths(&SymContext, tv_cipher.AadLen, tv_cipher.PtLen);
    fail_if(Status != PSA_SUCCESS, "psa_aead_set_lengths()=", Status);
    // wrong nonce size
    Status = psa_aead_set_nonce(&SymContext, Nonce, 12);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_set_nonce()=", Status);
    /* Make sure to clear key in use counter incremented in the successful setup*/
    Status = psa_aead_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_aead_abort()=", Status);

    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    // NULL operation
    Status = psa_aead_update_ad(NULL, tv_cipher.Aad_p, tv_cipher.AadLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_update_ad()=", Status);
    //NULL input
    Status = psa_aead_update_ad(&SymContext, NULL, tv_cipher.AadLen);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_update_ad()=", Status);
    // input length is 0
    Status = psa_aead_update_ad(&SymContext, tv_cipher.Aad_p, 0);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_update_ad()=", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_SETUP;
    Status = psa_aead_update_ad(&SymContext, tv_cipher.Aad_p, tv_cipher.AadLen);
    fail_if(Status != PSA_ERROR_BAD_STATE, "psa_aead_update_ad()=", Status);
    // input length bigger than length in context
    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    SymContext.ad_length = 12;
    Status = psa_aead_update_ad(&SymContext, tv_cipher.Aad_p, 13);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_update_ad()=", Status);

    // NULL operation
    Status = psa_aead_update(NULL, tv_cipher.Pt_p, tv_cipher.PtLen,
                             output, 16, &output_length);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // NULL input buffer
    Status = psa_aead_update(&SymContext, NULL, tv_cipher.PtLen,
                             output, 16, &output_length);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // input length is 0
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, 0,
                             output, 16, &output_length);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // NULL output buffer
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, tv_cipher.PtLen,
                             NULL, 16, &output_length);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // output size is 0
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, tv_cipher.PtLen,
                             output, 0, &output_length);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // NULL output length
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, tv_cipher.PtLen,
                             output, 16, NULL);
    fail_if(PSA_ERROR_DATA_INVALID != Status, "psa_aead_update ()", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_SETUP;
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, tv_cipher.PtLen,
                             output, 16, &output_length);
    fail_if(PSA_ERROR_BAD_STATE != Status, "psa_aead_update ()", Status);
    // input length is bigger than length saved in the context
    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    SymContext.plaintext_length = 16;
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, 17,
                             output, 16, &output_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_update ()", Status);
    // output buffer size is small
    Status = psa_aead_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_aead_abort()=", Status);

    Status = psa_aead_encrypt_setup(&SymContext, key, PSA_ALG_GCM);
    fail_if(Status != PSA_SUCCESS, "psa_aead_encrypt_setup()=", Status);

    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    SymContext.plaintext_length = 16;
    SymContext.ad_length  = 0;
    SymContext.TotalAADLength = 0;
    Status = psa_aead_update(&SymContext, tv_cipher.Pt_p, 16,
                             output, 15, &output_length);
    fail_if(PSA_ERROR_BUFFER_TOO_SMALL != Status, "psa_aead_update ()", Status);

    // NULL operation
    Status = psa_aead_finish(NULL, ciphertext, 16,
                             &ciphertext_length, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // NULL ciphertext with ciphertext size
    Status = psa_aead_finish(&SymContext, NULL, 16,
                             &ciphertext_length, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    //NULL ciphertext length
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             NULL, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // NULL tag buffer
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, NULL, 16,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // tag size is 0
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 0,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // NULL tag length
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 16,
                             NULL);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_BAD_STATE != Status, "psa_aead_finish ()", Status);
    // output buffer size is small
    SymContext.aead_state = PSA_AEAD_STATE_UPDATE;
    SymContext.leftover_nbytes_data = 16;
    Status = psa_aead_finish(&SymContext, ciphertext, 10,
                             &ciphertext_length, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_BUFFER_TOO_SMALL != Status, "psa_aead_finish ()", Status);
    // tag buffer size is small
    SymContext.aead_state = PSA_AEAD_STATE_UPDATE;
    SymContext.leftover_nbytes_data = 0;
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 5,
                             &tag_length);
    fail_if(PSA_ERROR_BUFFER_TOO_SMALL != Status, "psa_aead_finish ()", Status);
    // plain textsize saved in context not equal to total data length
    SymContext.plaintext_length = 16;
    SymContext.TotalDataLength = 17;
    Status = psa_aead_finish(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 16,
                             &tag_length);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_finish ()", Status);
    // NULL operation
    SymContext.fEncrypt = 0U;
    Status = psa_aead_verify(NULL, ciphertext, 16,
                             &ciphertext_length, tag, 16);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);
    // NULL plaintext with size provided
    Status = psa_aead_verify(&SymContext, NULL, 16,
                             &ciphertext_length, tag, 16);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);
    // NULL ptext length
    Status = psa_aead_verify(&SymContext, ciphertext, 16,
                             NULL, tag, 16);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);
    // NULL tag
    Status = psa_aead_verify(&SymContext, ciphertext, 16,
                             &ciphertext_length, NULL, 16);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);
    // tag size is 0
    Status = psa_aead_verify(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 0);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);
    // bad state
    SymContext.aead_state = PSA_AEAD_STATE_SET_NONCE;
    Status = psa_aead_verify(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 16);
    fail_if(PSA_ERROR_BAD_STATE != Status, "psa_aead_verify ()", Status);
    // plaintext buffer size is small
    SymContext.aead_state = PSA_AEAD_STATE_UPDATE;
    SymContext.leftover_nbytes_data = 16;
    Status = psa_aead_verify(&SymContext, ciphertext, 5,
                             &ciphertext_length, tag, 16);
    fail_if(PSA_ERROR_BUFFER_TOO_SMALL != Status, "psa_aead_verify ()", Status);

    // plain textsize saved in context not equal to total data length
    SymContext.plaintext_length = 16;
    SymContext.TotalDataLength = 17;
    Status = psa_aead_verify(&SymContext, ciphertext, 16,
                             &ciphertext_length, tag, 16);
    fail_if(PSA_ERROR_INVALID_ARGUMENT != Status, "psa_aead_verify ()", Status);

    Status = psa_aead_abort(NULL);
    fail_if(Status != PSA_ERROR_INVALID_ARGUMENT, "psa_aead_abort()=", Status);

    Status = psa_aead_abort(&SymContext);
    fail_if(Status != PSA_SUCCESS, "psa_aead_abort()=", Status);

    (void)psa_destroy_key(key);
    (void)psa_destroy_key(key_ver);
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    (void)psa_destroy_key(key_aria);
    (void)psa_destroy_key(key_aria_ver);
#endif

    test_vectors_aes_ccm_release(tv_p);
#if defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM)
    test_vectors_aria_ccm_release(tv_p_aria);
#endif
}
END_TEST
#endif

#undef PSA_AEAD_STATE_INIT
#undef PSA_AEAD_STATE_SETUP
#undef PSA_AEAD_STATE_SET_LENGTH
#undef PSA_AEAD_STATE_SET_NONCE
#undef PSA_AEAD_STATE_UPDATE
#undef PSA_AEAD_STATE_IV
#undef PSA_SYM_ALGO_AES_BLOCK_SIZE


int
suite_add_test_aead(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "SymCrypto_aead_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

#ifdef PSATEST_SYM_ALGO_AES_CCM
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_ccm, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_ccm_padding) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_ccm_Gen_nonce) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_ccm_multipart, 5) != 0) goto FuncErrorReturn;
#endif
#ifdef PSATEST_SYM_ALGO_AES_GCM
        if (sfzutf_test_add_loop(TestCase_p, test_sym_crypto_aes_gcm, 5) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_gcm_Gen_nonce) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_gcm_multipart) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_ccm_mul_padding) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aes_gcm_multipart_chunks) != 0) goto FuncErrorReturn;
#endif

#ifdef PSATEST_SYM_ALGO_ARIA_CCM
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aria_ccm) != 0) goto FuncErrorReturn;
#endif
#ifdef PSATEST_SYM_ALGO_ARIA_GCM
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_aria_gcm) != 0) goto FuncErrorReturn;
#endif

#if defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305)
        if (sfzutf_test_add(TestCase_p, test_sym_crypto_chacha20_poly1305) != 0) goto FuncErrorReturn;
#endif
#if defined(PSATEST_SYM_ALGO_AES_CCM) || defined(PSATEST_SYM_ALGO_AES_GCM) || \
    defined(PSATEST_SYM_ALGO_ARIA_CCM) || defined(PSATEST_SYM_ALGO_ARIA_GCM) || \
    (defined(PSATEST_SYM_ALGO_CHACHA20) && defined(PSATEST_SYM_ALGO_POLY1305))
        if (sfzutf_test_add(TestCase_p, test_aead_invalid_arguments) != 0) goto FuncErrorReturn;
#endif

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_cipher.c */
