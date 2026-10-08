/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

#ifndef INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_PREFIX_H
#define INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_PREFIX_H

/** \addtogroup crypto_prefix
 * @{
*/
#define KEYMGMT_FUNCTION_NAME(x) KeyMgmt_##x

#define psa_crypto_init \
        KEYMGMT_FUNCTION_NAME(psa_crypto_init)
#define psa_raw_key_agreement \
        KEYMGMT_FUNCTION_NAME(psa_raw_key_agreement)
#define psa_generate_random \
        KEYMGMT_FUNCTION_NAME(psa_generate_random)
#define psa_aead_encrypt \
        KEYMGMT_FUNCTION_NAME(psa_aead_encrypt)
#define psa_aead_decrypt \
        KEYMGMT_FUNCTION_NAME(psa_aead_decrypt)
#define psa_aead_encrypt_setup \
        KEYMGMT_FUNCTION_NAME(psa_aead_encrypt_setup)
#define psa_aead_decrypt_setup \
        KEYMGMT_FUNCTION_NAME(psa_aead_decrypt_setup)
#define psa_aead_generate_nonce \
        KEYMGMT_FUNCTION_NAME(psa_aead_generate_nonce)
#define psa_aead_set_nonce \
        KEYMGMT_FUNCTION_NAME(psa_aead_set_nonce)
#define psa_aead_set_lengths \
        KEYMGMT_FUNCTION_NAME(psa_aead_set_lengths)
#define psa_aead_update_ad \
        KEYMGMT_FUNCTION_NAME(psa_aead_update_ad)
#define psa_aead_update \
        KEYMGMT_FUNCTION_NAME(psa_aead_update)
#define psa_aead_finish \
        KEYMGMT_FUNCTION_NAME(psa_aead_finish)
#define psa_aead_verify \
        KEYMGMT_FUNCTION_NAME(psa_aead_verify)
#define psa_aead_abort \
        KEYMGMT_FUNCTION_NAME(psa_aead_abort)
#define psa_open_key \
        KEYMGMT_FUNCTION_NAME(psa_open_key)
#define psa_close_key \
        KEYMGMT_FUNCTION_NAME(psa_close_key)
#define psa_import_key \
        KEYMGMT_FUNCTION_NAME(psa_import_key)
#define psa_destroy_key \
        KEYMGMT_FUNCTION_NAME(psa_destroy_key)
#define psa_get_key_attributes \
        KEYMGMT_FUNCTION_NAME(psa_get_key_attributes)
#define psa_reset_key_attributes \
        KEYMGMT_FUNCTION_NAME(psa_reset_key_attributes)
#define psa_export_key \
        KEYMGMT_FUNCTION_NAME(psa_export_key)
#define psa_export_public_key \
        KEYMGMT_FUNCTION_NAME(psa_export_public_key)
#define psa_purge_key \
        KEYMGMT_FUNCTION_NAME(psa_purge_key)
#define psa_copy_key \
        KEYMGMT_FUNCTION_NAME(psa_copy_key)
#define psa_cipher_operation_init \
        KEYMGMT_FUNCTION_NAME(psa_cipher_operation_init)
#define psa_cipher_generate_iv \
        KEYMGMT_FUNCTION_NAME(psa_cipher_generate_iv)
#define psa_cipher_set_iv \
        KEYMGMT_FUNCTION_NAME(psa_cipher_set_iv)
#define psa_cipher_encrypt_setup \
        KEYMGMT_FUNCTION_NAME(psa_cipher_encrypt_setup)
#define psa_cipher_decrypt_setup \
        KEYMGMT_FUNCTION_NAME(psa_cipher_decrypt_setup)
#define psa_cipher_update \
        KEYMGMT_FUNCTION_NAME(psa_cipher_update)
#define psa_cipher_encrypt \
        KEYMGMT_FUNCTION_NAME(psa_cipher_encrypt)
#define psa_cipher_decrypt \
        KEYMGMT_FUNCTION_NAME(psa_cipher_decrypt)
#define psa_cipher_finish \
        KEYMGMT_FUNCTION_NAME(psa_cipher_finish)
#define psa_cipher_abort \
        KEYMGMT_FUNCTION_NAME(psa_cipher_abort)
#define psa_hash_operation_init \
        KEYMGMT_FUNCTION_NAME(psa_hash_operation_init)
#define psa_hash_setup \
        KEYMGMT_FUNCTION_NAME(psa_hash_setup)
#define psa_hash_update \
        KEYMGMT_FUNCTION_NAME(psa_hash_update)
#define psa_hash_finish \
        KEYMGMT_FUNCTION_NAME(psa_hash_finish)
#define psa_hash_verify \
        KEYMGMT_FUNCTION_NAME(psa_hash_verify)
#define psa_hash_abort \
        KEYMGMT_FUNCTION_NAME(psa_hash_abort)
#define psa_hash_clone \
        KEYMGMT_FUNCTION_NAME(psa_hash_clone)
#define psa_hash_compute \
        KEYMGMT_FUNCTION_NAME(psa_hash_compute)
#define psa_hash_compare \
        KEYMGMT_FUNCTION_NAME(psa_hash_compare)
#define psa_mac_operation_init \
        KEYMGMT_FUNCTION_NAME(psa_mac_operation_init)
#define psa_mac_sign_setup \
        KEYMGMT_FUNCTION_NAME(psa_mac_sign_setup)
#define psa_mac_verify_setup \
        KEYMGMT_FUNCTION_NAME(psa_mac_verify_setup)
#define psa_mac_update \
        KEYMGMT_FUNCTION_NAME(psa_mac_update)
#define psa_mac_sign_finish \
        KEYMGMT_FUNCTION_NAME(psa_mac_sign_finish)
#define psa_mac_verify_finish \
        KEYMGMT_FUNCTION_NAME(psa_mac_verify_finish)
#define psa_mac_compute \
        KEYMGMT_FUNCTION_NAME(psa_mac_compute)
#define psa_mac_verify \
        KEYMGMT_FUNCTION_NAME(psa_mac_verify)
#define psa_mac_abort \
        KEYMGMT_FUNCTION_NAME(psa_mac_abort)
#define psa_sign_message \
        KEYMGMT_FUNCTION_NAME(psa_sign_message)
#define psa_verify_message \
        KEYMGMT_FUNCTION_NAME(psa_verify_message)
#define psa_sign_hash \
        KEYMGMT_FUNCTION_NAME(psa_sign_hash)
#define psa_verify_hash \
        KEYMGMT_FUNCTION_NAME(psa_verify_hash)
#define psa_asymmetric_encrypt \
        KEYMGMT_FUNCTION_NAME(psa_asymmetric_encrypt)
#define psa_asymmetric_decrypt \
        KEYMGMT_FUNCTION_NAME(psa_asymmetric_decrypt)
#define psa_generate_key \
        KEYMGMT_FUNCTION_NAME(psa_generate_key)
#define psa_set_key_domain_parameters \
        KEYMGMT_FUNCTION_NAME(psa_set_key_domain_parameters)
/**@}*/

#endif /* INCLUDE_GUARD_ADAPTER_PSA_KEY_MANAGEMENT_PREFIX_H */