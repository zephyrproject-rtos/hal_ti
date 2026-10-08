/**
 * \file psa/crypto_config.h
 * \brief PSA crypto configuration options (set of defines)
 *
 */
#if defined(MBEDTLS_PSA_CRYPTO_CONFIG)
/**
 * When #MBEDTLS_PSA_CRYPTO_CONFIG is enabled in mbedtls_config.h,
 * this file determines which cryptographic mechanisms are enabled
 * through the PSA Cryptography API (\c psa_xxx() functions).
 *
 * To enable a cryptographic mechanism, uncomment the definition of
 * the corresponding \c PSA_WANT_xxx preprocessor symbol.
 * To disable a cryptographic mechanism, comment out the definition of
 * the corresponding \c PSA_WANT_xxx preprocessor symbol.
 * The names of cryptographic mechanisms correspond to values
 * defined in psa/crypto_values.h, with the prefix \c PSA_WANT_ instead
 * of \c PSA_.
 *
 * Note that many cryptographic mechanisms involve two symbols: one for
 * the key type (\c PSA_WANT_KEY_TYPE_xxx) and one for the algorithm
 * (\c PSA_WANT_ALG_xxx). Mechanisms with additional parameters may involve
 * additional symbols.
 */
#else
/**
 * When \c MBEDTLS_PSA_CRYPTO_CONFIG is disabled in mbedtls_config.h,
 * this file is not used, and cryptographic mechanisms are supported
 * through the PSA API if and only if they are supported through the
 * mbedtls_xxx API.
 */
#endif
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef PSA_CRYPTO_CONFIG_H
#define PSA_CRYPTO_CONFIG_H

/*
 * CBC-MAC is not yet supported via the PSA API in Mbed TLS.
 */
#define PSA_WANT_ALG_CBC_MAC                    1
#define PSA_WANT_ALG_CBC_NO_PADDING             1
// #define PSA_WANT_ALG_CBC_PKCS7                  1
#define PSA_WANT_ALG_CCM                        1
#define PSA_WANT_ALG_CCM_STAR_NO_TAG            1
#define PSA_WANT_ALG_CMAC                       1
// #define PSA_WANT_ALG_CFB                        1
#define PSA_WANT_ALG_CHACHA20_POLY1305          1
#define PSA_WANT_ALG_CTR                        1
#define PSA_WANT_ALG_DETERMINISTIC_ECDSA        1
#define PSA_WANT_ALG_ECB_NO_PADDING             1
#define PSA_WANT_ALG_ECDH                       1
#define PSA_WANT_ALG_FFDH                       1
#define PSA_WANT_ALG_ECDSA                      1
// #define PSA_WANT_ALG_JPAKE                      1
#define PSA_WANT_ALG_GCM                        1
#define PSA_WANT_ALG_HKDF                       1
#define PSA_WANT_ALG_HKDF_EXTRACT               1
#define PSA_WANT_ALG_HKDF_EXPAND                1
#define PSA_WANT_ALG_HMAC                       1
#define PSA_WANT_ALG_MD5                        1
// #define PSA_WANT_ALG_OFB                        1
// #define PSA_WANT_ALG_PBKDF2_HMAC                1
// #define PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128    1
// #define PSA_WANT_ALG_RIPEMD160                  1
#define PSA_WANT_ALG_RSA_OAEP                   1
#define PSA_WANT_ALG_RSA_PKCS1V15_CRYPT         1
#define PSA_WANT_ALG_RSA_PKCS1V15_SIGN          1
#define PSA_WANT_ALG_RSA_PSS                    1
#define PSA_WANT_ALG_SHA_1                      1
#define PSA_WANT_ALG_SHA_224                    1
#define PSA_WANT_ALG_SHA_256                    1
#define PSA_WANT_ALG_SHA_384                    1
#define PSA_WANT_ALG_SHA_512                    1
#define PSA_WANT_ALG_SHA3_224                   1
#define PSA_WANT_ALG_SHA3_256                   1
#define PSA_WANT_ALG_SHA3_384                   1
#define PSA_WANT_ALG_SHA3_512                   1
// #define PSA_WANT_ALG_STREAM_CIPHER              1
// #define PSA_WANT_ALG_TLS12_PRF                  1
// #define PSA_WANT_ALG_TLS12_PSK_TO_MS            1
// #define PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS       1

#define PSA_WANT_ECC_BRAINPOOL_P_R1_256         1
#define PSA_WANT_ECC_BRAINPOOL_P_R1_384         1
#define PSA_WANT_ECC_BRAINPOOL_P_R1_512         1
#define PSA_WANT_ECC_MONTGOMERY_255             1
// #define PSA_WANT_ECC_MONTGOMERY_448             1
// #define PSA_WANT_ECC_SECP_K1_192                1
// #define PSA_WANT_ECC_SECP_K1_256                1
// #define PSA_WANT_ECC_SECP_R1_192                1
#define PSA_WANT_ECC_SECP_R1_224                1
/* For secp256r1, consider enabling #MBEDTLS_PSA_P256M_DRIVER_ENABLED
 * (see the description in mbedtls/mbedtls_config.h for details). */
#define PSA_WANT_ECC_SECP_R1_256                1
#define PSA_WANT_ECC_SECP_R1_384                1
#define PSA_WANT_ECC_SECP_R1_521                1

#define PSA_WANT_DH_RFC7919_2048                1
#define PSA_WANT_DH_RFC7919_3072                1
// #define PSA_WANT_DH_RFC7919_4096                1
// #define PSA_WANT_DH_RFC7919_6144                1
// #define PSA_WANT_DH_RFC7919_8192                1

#define PSA_WANT_KEY_TYPE_DERIVE                1
#define PSA_WANT_KEY_TYPE_PASSWORD              1
#define PSA_WANT_KEY_TYPE_PASSWORD_HASH         1
#define PSA_WANT_KEY_TYPE_HMAC                  1
#define PSA_WANT_KEY_TYPE_AES                   1
// #define PSA_WANT_KEY_TYPE_ARIA                  1
// #define PSA_WANT_KEY_TYPE_CAMELLIA              1
#define PSA_WANT_KEY_TYPE_CHACHA20              1
// #define PSA_WANT_KEY_TYPE_DES                   1
//#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR          1 /* Deprecated */
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY        1
#define PSA_WANT_KEY_TYPE_DH_PUBLIC_KEY         1
#define PSA_WANT_KEY_TYPE_RAW_DATA              1
//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR          1 /* Deprecated */
#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY        1

/*
 * The following symbols extend and deprecate the legacy
 * PSA_WANT_KEY_TYPE_xxx_KEY_PAIR ones. They include the usage of that key in
 * the name's suffix. "_USE" is the most generic and it can be used to describe
 * a generic suport, whereas other ones add more features on top of that and
 * they are more specific.
 */
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC      1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT   1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT   1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE 1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE   1

#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC      1
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT   1
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT   1
#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE 1
//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_DERIVE   1 /* Not supported */

#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC       1
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT    1
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT    1
#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_GENERATE  1
//#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_DERIVE    1 /* Not supported */

/* We must define BUILTIN_HMAC ourselves. It is usually only defined
 * when we PSA_WANT_ALG_HMAC, but we don't MBEDTLS_PSA_ACCEL that alg.
 * We do accelerate HMAC, but in the context of HKDF, we use the builtin
 * implementation of HMAC. So, we must define this to compile in SW HMAC.
 */
#define MBEDTLS_PSA_BUILTIN_ALG_HMAC
/* Add MBEDTLS_PSA_ACCEL_ALG_XXX macros to indicate that these crypto algorithms
 * can be provided by our PSA 'driver', as mbedTLS calls it, though really we will
 * just link the mbedTLS build to our own PSA implementation (which is not in the
 * 'driver' format that mbedTLS speaks of)
 */
#define MBEDTLS_PSA_ACCEL_ALG_ECDSA
#define MBEDTLS_PSA_ACCEL_ALG_ECDH
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_PUBLIC_KEY
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_BASIC
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_IMPORT
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_EXPORT
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_GENERATE
#define MBEDTLS_PSA_ACCEL_ECC_BRAINPOOL_P_R1_256
#define MBEDTLS_PSA_ACCEL_ECC_BRAINPOOL_P_R1_384
#define MBEDTLS_PSA_ACCEL_ECC_BRAINPOOL_P_R1_512
// #define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_192
#define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_224
#define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_256
#define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_384
#define MBEDTLS_PSA_ACCEL_ECC_SECP_R1_521
// #define MBEDTLS_PSA_ACCEL_ECC_SECP_K1_192
// #define MBEDTLS_PSA_ACCEL_ECC_SECP_K1_224
// #define MBEDTLS_PSA_ACCEL_ECC_SECP_K1_256
#define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_255
// #define MBEDTLS_PSA_ACCEL_ECC_MONTGOMERY_448
#define MBEDTLS_PSA_ACCEL_ALG_DETERMINISTIC_ECDSA
// #define MBEDTLS_PSA_ACCEL_ALG_JPAKE
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR_DERIVE
// #define MBEDTLS_PSA_ACCEL_DH_RFC7919_2048
// #define MBEDTLS_PSA_ACCEL_DH_RFC7919_3072
// #define MBEDTLS_PSA_ACCEL_DH_RFC7919_4096
// #define MBEDTLS_PSA_ACCEL_DH_RFC7919_6144
// #define MBEDTLS_PSA_ACCEL_DH_RFC7919_8192
// #define MBEDTLS_PSA_ACCEL_ALG_FFDH
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DH_PUBLIC_KEY
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DH_KEY_PAIR_BASIC
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DH_KEY_PAIR_IMPORT
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DH_KEY_PAIR_EXPORT
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DH_KEY_PAIR_GENERATE
// #define MBEDTLS_PSA_ACCEL_ALG_HKDF
// #define MBEDTLS_PSA_ACCEL_ALG_HKDF_EXTRACT
// #define MBEDTLS_PSA_ACCEL_ALG_HKDF_EXPAND
#define MBEDTLS_PSA_ACCEL_ALG_HMAC
// #define MBEDTLS_PSA_ACCEL_ALG_MD5
// #define MBEDTLS_PSA_ACCEL_ALG_RIPEMD160
// #define MBEDTLS_PSA_ACCEL_ALG_RSA_OAEP
// #define MBEDTLS_PSA_ACCEL_ALG_RSA_PKCS1V15_CRYPT
// #define MBEDTLS_PSA_ACCEL_ALG_RSA_PKCS1V15_SIGN
// #define MBEDTLS_PSA_ACCEL_ALG_RSA_PSS
// #define MBEDTLS_PSA_ACCEL_ALG_SHA_1
#define MBEDTLS_PSA_ACCEL_ALG_SHA_224
#define MBEDTLS_PSA_ACCEL_ALG_SHA_256
#define MBEDTLS_PSA_ACCEL_ALG_SHA_384
#define MBEDTLS_PSA_ACCEL_ALG_SHA_512
#define MBEDTLS_PSA_ACCEL_ALG_SHA3_224
#define MBEDTLS_PSA_ACCEL_ALG_SHA3_256
#define MBEDTLS_PSA_ACCEL_ALG_SHA3_384
#define MBEDTLS_PSA_ACCEL_ALG_SHA3_512
// #define MBEDTLS_PSA_ACCEL_ALG_PBKDF2_HMAC
// #define MBEDTLS_PSA_ACCEL_ALG_TLS12_PRF
// #define MBEDTLS_PSA_ACCEL_ALG_TLS12_PSK_TO_MS
// #define MBEDTLS_PSA_ACCEL_ALG_TLS12_ECJPAKE_TO_PMS
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_IMPORT
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_EXPORT
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_GENERATE
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR_BASIC
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_PUBLIC_KEY
#define MBEDTLS_PSA_ACCEL_ALG_CTR
// #define MBEDTLS_PSA_ACCEL_ALG_CFB
// #define MBEDTLS_PSA_ACCEL_ALG_OFB
#define MBEDTLS_PSA_ACCEL_ALG_ECB_NO_PADDING
#define MBEDTLS_PSA_ACCEL_ALG_CBC_NO_PADDING
// #define MBEDTLS_PSA_ACCEL_ALG_CBC_PKCS7
#define MBEDTLS_PSA_ACCEL_ALG_CCM
#define MBEDTLS_PSA_ACCEL_ALG_CCM_STAR_NO_TAG
#define MBEDTLS_PSA_ACCEL_ALG_GCM

// #define MBEDTLS_PSA_ACCEL_ALG_CHACHA20_POLY1305
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_AES
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_ARIA
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_CAMELLIA
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_DES
#define MBEDTLS_PSA_ACCEL_ALG_STREAM_CIPHER
// #define MBEDTLS_PSA_ACCEL_KEY_TYPE_CHACHA20
#define MBEDTLS_PSA_ACCEL_ALG_CBC_MAC
#define MBEDTLS_PSA_ACCEL_ALG_CMAC
#define MBEDTLS_PSA_ACCEL_ALG_PBKDF2_AES_CMAC_PRF_128

#endif /* PSA_CRYPTO_CONFIG_H */