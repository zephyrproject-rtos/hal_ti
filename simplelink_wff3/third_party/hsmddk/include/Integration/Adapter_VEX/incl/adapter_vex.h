/* adapter_vex.h
 *
 * The VEX API.
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

#ifndef INCLUDE_GUARD_ADAPTER_VEX_H
#define INCLUDE_GUARD_ADAPTER_VEX_H

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             // uint32_t, inline, etc.

#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>
/*----------------------------------------------------------------------------
 * VexStatus_t
 */
typedef int32_t VexStatus_t;

/* Retuned Status codes */
#define VEX_SUCCESS                 (0)     /* Operation success */
#define VEX_UNSUPPORTED             (-1)    /* Not supported */
#define VEX_NOT_CONNECTED           (-2)    /* No connection with HW available */
#define VEX_POWER_STATE_ERROR       (-3)    /* Device writes (unexpectly) did not work */
#define VEX_OPERATION_NOT_ALLOWED   (-4)    /* The host is not allowed to do this operation */
#define VEX_OPERATION_FAILED        (-5)    /* Operation failed */
#define VEX_INVALID_OPCODE          (-6)    /* Invalid parameter */
#define VEX_INVALID_SUBCODE         (-7)    /* Invalid parameter */
#define VEX_INVALID_LENGTH          (-8)    /* Invalid length */
#define VEX_BAD_ARGUMENT            (-9)    /* Wrong use; not depending on configuration */
#define VEX_NO_MEMORY               (-10)   /* No memory */
#define VEX_NO_IDENTITY             (-11)   /* No identity */
#define VEX_NO_MAILBOX              (-12)   /* No mailbox */
#define VEX_MAILBOX_IN_USE          (-13)   /* Mailbox is in use */
#define VEX_RESPONSE_TIMEOUT        (-14)   /* Output token response timeout */
#define VEX_DATA_TIMEOUT            (-15)   /* Data ready check timeout */
#define VEX_DATA_MAPPING_ERROR      (-16)   /* Data mapping error */
#define VEX_LOCK_TIMEOUT            (-17)   /* Output token response timeout */
#define VEX_TOKEN_TIMEOUT           (-18)   /* Input token processing timeout */
#define VEX_INTERNAL_ERROR          (-19)   /* Internal error */


/*----------------------------------------------------------------------------
 * Token operation codes
 */
#define VEXTOKEN_OPCODE_NOP                 0U
#define VEXTOKEN_OPCODE_ENCRYPTION          1U
#define VEXTOKEN_OPCODE_HASH                2U
#define VEXTOKEN_OPCODE_MAC                 3U
#define VEXTOKEN_OPCODE_TRNG                4U
#define VEXTOKEN_OPCODE_SPECIALFUNCTIONS    5U
#define VEXTOKEN_OPCODE_SYMWRAP             6U
#define VEXTOKEN_OPCODE_ASSETMANAGEMENT     7U
#define VEXTOKEN_OPCODE_AUTH_UNLOCK         8U
#define VEXTOKEN_OPCODE_PUBLIC_KEY          9U
#define VEXTOKEN_OPCODE_RESERVED10          10U
#define VEXTOKEN_OPCODE_RESERVED11          11U
#define VEXTOKEN_OPCODE_RESERVED12          12U
#define VEXTOKEN_OPCODE_RESERVED13          13U
#define VEXTOKEN_OPCODE_SERVICE             14U
#define VEXTOKEN_OPCODE_SYSTEM              15U
#define VEXTOKEN_OPCODE_HARDWARE            16U
#define VEXTOKEN_OPCODE_CLAIMCONTROL        17U

/*----------------------------------------------------------------------------
 * Token sub codes
 */
// General operations
#define VEXTOKEN_SUBCODE_NOT_USED               0U

// Encryption operation
#define VEXTOKEN_SUBCODE_ENCRYPT                0U
#define VEXTOKEN_SUBCODE_AUTHENCRYPT            1U

// MAC operations
#define VEXTOKEN_SUBCODE_MACUPDATE              0U
#define VEXTOKEN_SUBCODE_MACGENERATE            1U
#define VEXTOKEN_SUBCODE_MACVERIFY              2U

// TRNG operations
#define VEXTOKEN_SUBCODE_RANDOMNUMBER           0U
#define VEXTOKEN_SUBCODE_TRNGCONFIG             1U
#define VEXTOKEN_SUBCODE_VERIFYDRBG             2U
#define VEXTOKEN_SUBCODE_VERIFYNRBG             3U
#define VEXTOKEN_SUBCODE_TRNGRAWDATA            4U

// Special functions operations
#define VEXTOKEN_SUBCODE_SF_MILENAGE            0U

// Asset Management operations
#define VEXTOKEN_SUBCODE_ASSETSEARCH            0U
#define VEXTOKEN_SUBCODE_ASSETCREATE            1U
#define VEXTOKEN_SUBCODE_ASSETLOAD              2U
#define VEXTOKEN_SUBCODE_ASSETDELETE            3U
#define VEXTOKEN_SUBCODE_PUBLICDATA             4U
#define VEXTOKEN_SUBCODE_MONOTONICREAD          5U
#define VEXTOKEN_SUBCODE_MONOTONICINCR          6U
#define VEXTOKEN_SUBCODE_OTPDATAWRITE           7U
#define VEXTOKEN_SUBCODE_SECURETIMER            8U
#define VEXTOKEN_SUBCODE_PROVISIONRANDOMHUK     9U
#define VEXTOKEN_SUBCODE_CPIF_EXPORT            10U
#define VEXTOKEN_SUBCODE_ASSETSTORERESET        15U

// KeyWrap and Encrypt vector operations
#define VEXTOKEN_SUBCODE_SYMKEYWRAP             0U

// Authenticated Unlock operations
#define VEXTOKEN_SUBCODE_AUNLOCKSTART           0U
#define VEXTOKEN_SUBCODE_AUNLOCKVERIFY          1U
#define VEXTOKEN_SUBCODE_SETSECUREDEBUG         2U

// Public key operations
#define VEXTOKEN_SUBCODE_PK_NOASSETS            0U
#define VEXTOKEN_SUBCODE_PK_WITHASSETS          1U

// Service operations
#define VEXTOKEN_SUBCODE_REGISTERREAD           0U
#define VEXTOKEN_SUBCODE_REGISTERWRITE          1U
#define VEXTOKEN_SUBCODE_CLOCKSWITCH            2U
#define VEXTOKEN_SUBCODE_ZEROOUTMAILBOX         3U
#define VEXTOKEN_SUBCODE_SELECTOTPZERO          4U
#define VEXTOKEN_SUBCODE_ZEROIZEOTP             5U
#define VEXTOKEN_SUBCODE_FIRMWARECHECK          6U
#define VEXTOKEN_SUBCODE_UPDATEROLLBACKID       7U

// System operations
#define VEXTOKEN_SUBCODE_SYSTEMINFO             0U
#define VEXTOKEN_SUBCODE_SELFTEST               1U
#define VEXTOKEN_SUBCODE_RESET                  2U
#define VEXTOKEN_SUBCODE_LOGIN                  3U
#define VEXTOKEN_SUBCODE_SLEEP                  4U
#define VEXTOKEN_SUBCODE_RESUMEFROMSLEEP        5U
#define VEXTOKEN_SUBCODE_SETTIME                8U

// Hardware related information
#define VEXTOKEN_SUBCODE_MODULESTATUS           0U
#define VEXTOKEN_SUBCODE_EIP_OPTIONS            1U
#define VEXTOKEN_SUBCODE_EIP_VERSION            2U

// Claim control
#define VEXTOKEN_SUBCODE_CLAIM_EXCL             0U
#define VEXTOKEN_SUBCODE_CLAIM_EXCL_OVERRULE    1U
#define VEXTOKEN_SUBCODE_CLAIM_RELEASE          2U

/*----------------------------------------------------------------------------
 * Hash algorithm codes
 */
#define VEXTOKEN_ALGO_HASH_SHA1         1U
#define VEXTOKEN_ALGO_HASH_SHA224       2U
#define VEXTOKEN_ALGO_HASH_SHA256       3U
#define VEXTOKEN_ALGO_HASH_SHA384       4U
#define VEXTOKEN_ALGO_HASH_SHA512       5U
#define VEXTOKEN_ALGO_HASH_SM3          6U
#define VEXTOKEN_ALGO_HASH_SHA3_224     7U
#define VEXTOKEN_ALGO_HASH_SHA3_256     8U
#define VEXTOKEN_ALGO_HASH_SHA3_384     9U
#define VEXTOKEN_ALGO_HASH_SHA3_512     10U

/*----------------------------------------------------------------------------
 * MAC algorithm codes
 */
#define VEXTOKEN_ALGO_MAC_HMAC_SHA1     1U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA224   2U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA256   3U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA384   4U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA512   5U
#define VEXTOKEN_ALGO_MAC_HMAC_SM3      6U
#define VEXTOKEN_ALGO_MAC_POLY1305      7U // not supported
#define VEXTOKEN_ALGO_MAC_AES_CMAC      8U
#define VEXTOKEN_ALGO_MAC_AES_CBC_MAC   9U
#define VEXTOKEN_ALGO_MAC_ARIA_CMAC     10U
#define VEXTOKEN_ALGO_MAC_ARIA_CBC_MAC  11U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA3_224 12U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA3_256 13U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA3_384 14U
#define VEXTOKEN_ALGO_MAC_HMAC_SHA3_512 15U

/*----------------------------------------------------------------------------
 *  Cipher algorithm codes
 */
#define VEXTOKEN_ALGO_CIPHER_AES        0U
#define VEXTOKEN_ALGO_CIPHER_DES        1U
#define VEXTOKEN_ALGO_CIPHER_3DES       2U
#define VEXTOKEN_ALGO_CIPHER_CHACHA20   7U
#define VEXTOKEN_ALGO_CIPHER_SM4        8U
#define VEXTOKEN_ALGO_CIPHER_ARIA       9U

/*----------------------------------------------------------------------------
 * Authenticated Encrypt mode codes
 */
#define VEXTOKEN_MODE_CIPHER_AE_INIT2FINAL          0U
#define VEXTOKEN_MODE_CIPHER_AE_CONT2FINAL          1U
#define VEXTOKEN_MODE_CIPHER_AE_INIT2CONT           2U
#define VEXTOKEN_MODE_CIPHER_AE_CONT2CONT           3U
#define VEXTOKEN_MODE_CIPHER_AE_AAD_INIT2CONT       4U
#define VEXTOKEN_MODE_CIPHER_AE_AAD_FINAL2INIT_DATA 5U

/*----------------------------------------------------------------------------
 * Hash and MAC mode codes
 */
#define VEXTOKEN_MODE_HASH_MAC_INIT2FINAL   0U
#define VEXTOKEN_MODE_HASH_MAC_CONT2FINAL   1U
#define VEXTOKEN_MODE_HASH_MAC_INIT2CONT    2U
#define VEXTOKEN_MODE_HASH_MAC_CONT2CONT    3U

/*----------------------------------------------------------------------------
 * Cipher mode codes
 */
#define VEXTOKEN_MODE_CIPHER_ECB            0U
#define VEXTOKEN_MODE_CIPHER_CBC            1U
#define VEXTOKEN_MODE_CIPHER_CTR            2U
#define VEXTOKEN_MODE_CIPHER_ICM            3U
#define VEXTOKEN_MODE_CIPHER_F8             4U
#define VEXTOKEN_MODE_CIPHER_CCM            5U
#define VEXTOKEN_MODE_CIPHER_XTS            6U
#define VEXTOKEN_MODE_CIPHER_GCM            7U
#define VEXTOKEN_MODE_CIPHER_CHACHA20_ENC   0U
#define VEXTOKEN_MODE_CIPHER_CHACHA20_AEAD  1U

/*----------------------------------------------------------------------------
 * Milenage operation codes
 */
#define VEXTOKEN_MILENAGE_OP_SQNADMINCREATE     0U
#define VEXTOKEN_MILENAGE_OP_AUTNVERIFICATION   1U
#define VEXTOKEN_MILENAGE_OP_AUTSGENERATION     2U
#define VEXTOKEN_MILENAGE_OP_SQNADMINEXPORT     3U
#define VEXTOKEN_MILENAGE_OP_CONFORMANCECHECK   4U

/*----------------------------------------------------------------------------
 * Asset Load codes
 */
#define VEXTOKEN_ASSETLOAD_IMPORT       0U
#define VEXTOKEN_ASSETLOAD_DERIVE       1U
#define VEXTOKEN_ASSETLOAD_PLAINTEXT    2U
#define VEXTOKEN_ASSETLOAD_RANDOM       3U
#define VEXTOKEN_ASSETLOAD_SYMUNWRAP    4U

/*----------------------------------------------------------------------------
 * PK with Assets operation codes
 */
#define VEXTOKEN_PKAS_ECDH_ECDSA_KEYCHK                 0x001U
#define VEXTOKEN_PKAS_DH_DSA_KEYCHK                     0x002U
#define VEXTOKEN_PKAS_ECDSA_SIGN                        0x006U
#define VEXTOKEN_PKAS_ECDSA_VERIFY                      0x007U
#define VEXTOKEN_PKAS_RSA_PKCS1V1_5_SIGN                0x008U
#define VEXTOKEN_PKAS_RSA_PKCS1V1_5_VERIFY              0x009U
#define VEXTOKEN_PKAS_RSA_PSS_SIGN                      0x00CU
#define VEXTOKEN_PKAS_RSA_PSS_VERIFY                    0x00DU
#define VEXTOKEN_PKAS_DH_GEN_PUBKEY                     0x010U
#define VEXTOKEN_PKAS_DH_GEN_KEYPAIR                    0x011U
#define VEXTOKEN_PKAS_DH_GEN_SKEYPAIR_SHARED_SECRET     0x012U
#define VEXTOKEN_PKAS_DH_GEN_DKEYPAIR_SHARED_SECRET     0x013U
#define VEXTOKEN_PKAS_ECDH_ECDSA_GEN_PUBKEY             0x014U
#define VEXTOKEN_PKAS_ECDH_ECDSA_GEN_KEYPAIR            0x015U
#define VEXTOKEN_PKAS_ECDH_GEN_SKEYPAIR_SHARED_SECRET   0x016U
#define VEXTOKEN_PKAS_ECDH_GEN_DKEYPAIR_SHARED_SECRET   0x017U
#define VEXTOKEN_PKAS_RSA_OAEP_WRAP_STRING              0x018U
#define VEXTOKEN_PKAS_RSA_OAEP_WRAP_HASH                0x019U
#define VEXTOKEN_PKAS_RSA_OAEP_UNWRAP_STRING            0x01AU
#define VEXTOKEN_PKAS_RSA_OAEP_UNWRAP_HASH              0x01BU
#define VEXTOKEN_PKAS_RSA_PKCS1V15_UNWRAP               0x021U
#define VEXTOKEN_PKAS_RSA_PKCS1V15_WRAP                 0x022U
#define VEXTOKEN_PKAS_CURVE25519_GEN_PUBKEY             0x028U
#define VEXTOKEN_PKAS_CURVE25519_GEN_KEYPAIR            0x029U
#define VEXTOKEN_PKAS_CURVE25519_GEN_SHARED_SECRET      0x02AU
#define VEXTOKEN_PKAS_EDDSA_GEN_PUBKEY                  0x02BU
#define VEXTOKEN_PKAS_EDDSA_GEN_KEYPAIR                 0x02CU
#define VEXTOKEN_PKAS_EDDSA_SIGN_INITIAL                0x02DU
#define VEXTOKEN_PKAS_EDDSA_SIGN_UPDATE                 0x02EU
#define VEXTOKEN_PKAS_EDDSA_SIGN_FINAL                  0x02FU
#define VEXTOKEN_PKAS_EDDSA_VERIFY_INITIAL              0x030U
#define VEXTOKEN_PKAS_EDDSA_VERIFY_FINAL                0x031U
#define VEXTOKEN_PKAS_SM2DSA_SIGN                       0x032U
#define VEXTOKEN_PKAS_SM2DSA_VERIFY                     0x033U
#define VEXTOKEN_PKAS_SM2ENC_WRAP                       0x034U
#define VEXTOKEN_PKAS_SM2ENC_UNWRAP                     0x035U
#define VEXTOKEN_PKAS_SM2KEX_GEN_SHARED_SECRET          0x036U
#define VEXTOKEN_PKAS_ECIESWRAP                         0x038U
#define VEXTOKEN_PKAS_ECIESUNWRAP                       0x039U
#define VEXTOKEN_PKAS_INSTALL_ECCURVE                   0x100U

/*----------------------------------------------------------------------------
 * PK without Assets operation codes
 */
#define VEXTOKEN_PK_OP_NUMLOAD      0x01U
#define VEXTOKEN_PK_OP_NUMSETN      0x03U
#define VEXTOKEN_PK_OP_MODEXPE      0x04U
#define VEXTOKEN_PK_OP_MODEXPD      0x05U
#define VEXTOKEN_PK_OP_MODEXPCRT    0x06U
#define VEXTOKEN_PK_OP_ECMONTMUL    0x0AU
#define VEXTOKEN_PK_OP_ECCMUL       0x0BU
#define VEXTOKEN_PK_OP_ECCADD       0x0CU
#define VEXTOKEN_PK_OP_ECDSASIGN    0x0FU
#define VEXTOKEN_PK_OP_ECDSAVERIFY  0x10U

/*----------------------------------------------------------------------------
 * Secure Timer operation codes
 */
#define VEXTOKEN_SECURETIMER_START  0U      // (Re)Start a timer
#define VEXTOKEN_SECURETIMER_STOP   1U      // Read elapsed time and stop the timer
#define VEXTOKEN_SECURETIMER_READ   2U     // Read elapsed time

/*----------------------------------------------------------------------------
 * Token/HW/Algorithm related limits
 */
#define VEXTOKEN_DMA_MAXLENGTH           0x001FFFFF  // 2 MB - 1 bytes
#define VEXTOKEN_DMA_TOKENID_SIZE        4           // bytes

/*----------------------------------------------------------------------------
 * DMA data block must be an integer multiple of a work block size (in bytes)
 */
#define VEXTOKEN_DMA_ALGO_BLOCKSIZE_HASH 64
#define VEXTOKEN_DMA_ALGO_BLOCKSIZE_AES  16
#define VEXTOKEN_DMA_ALGO_BLOCKSIZE_DES  8
#define VEXTOKEN_DMA_ALGO_BLOCKSIZE_ARC4 4
#define VEXTOKEN_DMA_ALGO_BLOCKSIZE_NOP  4

/*----------------------------------------------------------------------------
 * Protected Application related limits
 */
#define PROT_APP_MAX_DATA_SIZE   (256 - (3*4))  // Mailbox Size - 3 reserved words (word 0, Identity, Prot. App Data Size)

/*----------------------------------------------------------------------------
 * Maximums for items in VexTokenCmd_*_t
 */
#define VEXTOKEN_MAX_ASSOC_DATA_SZ  224U
#define VEXTOKEN_MAX_PK_NUM_ASSETS  24U

/*----------------------------------------------------------------------------
 * VexTokenCmd_*_t - Command Token structures
 */
/*----------------------------------------------------------------------------
 * VexTokenCmd_Generic_t - Generic command Token
 */
typedef struct
{
    uint32_t OpCode;                    // Service group
    uint32_t SubCode;                   // Specific service code in the group
    uint32_t fFromUserSpace;            // From User Space indication
} VexTokenCmd_Generic_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_Nop_t - NOP command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Size;
    const uint8_t * In_p;
    uint8_t * Out_p;
} VexTokenCmd_Nop_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_Cipher_t - Cipher command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Algorithm;
    const uint8_t * SrcData_p;
    uint8_t * DstData_p;
    uint32_t Mode;
    uint32_t KeyAssetId;
    uint32_t TempAssetId;
    uint32_t DataSize;
    uint32_t KeySize;
    uint8_t Key[64];            // AES-XTS requires 512bit (2 * 256bit)
    uint8_t IV[16];
    uint8_t Parameter[16];      // System parameter
    uint8_t f8_IV[16];          // IV for AES f8 mode
    uint8_t f8_SaltKey[16];     // Salt key for AES f8 mode
    uint8_t f8_SaltKeySize;     // Salt key size for AES f8 mode
    uint8_t NonceLength;        // Nonce length for ChaCha20
    uint8_t fEncrypt;
} VexTokenCmd_Cipher_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_CipherAE_t - Cipher Authenticated Encrypt command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Algorithm;
    const uint8_t * AAD_p;
    const uint8_t * SrcData_p;
    uint8_t * DstData_p;
    uint32_t Mode;
    uint32_t KeyAssetId;
    uint32_t TempAssetId;
    uint32_t AADSize;
    uint32_t TotalAADLength;
    uint32_t DataSize;
    uint32_t TotalDataLength;
    uint32_t KeySize;
    uint8_t Key[32];
    uint8_t NonceHashKey[16];
    uint8_t IV[16];
    uint8_t Tag[16];
    uint8_t fEncrypt;
    uint8_t fNoRandomIV;
    uint8_t NonceHashKeySize;  // Actual Nonce/HashKey size
    uint8_t GCMMode;           // GCMMode
    uint8_t OpMode;            // for continuation
    uint8_t TagSize;           // Tag size
} VexTokenCmd_CipherAE_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_Hash_t - Hash command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Algorithm;
    uint32_t TotalMessageLengthLo;
    uint32_t TotalMessageLengthHi;
    uint32_t Mode;
    uint32_t DataSize;
    const uint8_t * Data_p;
    uint32_t TempAssetId;
    uint8_t Digest[1600U/8U];           // Required to support SHA-3
} VexTokenCmd_Hash_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_Mac_t - MAC command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Algorithm;
    uint32_t TotalMessageLengthLo;
    uint32_t TotalMessageLengthHi;
    uint32_t Mode;
    uint32_t DataSize;
    const uint8_t * Data_p;
    uint32_t TempAssetId;
    uint32_t KeyAssetId;
    uint32_t MacAssetId;
    uint32_t MacSize;
    uint8_t Mac[64];
} VexTokenCmd_Mac_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_KeyWrap_t - KeyWrap command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t KeyAssetId;
    const uint8_t * SrcData_p;
    uint8_t * DstData_p;
    uint32_t SrcDataSize;
    uint32_t DstDataSize;
    uint32_t KeySize;
    uint8_t Key[32];
    uint8_t fWrap;
    uint8_t Algorithm;
} VexTokenCmd_KeyWrap_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_TrngConfig_t - TRNG configuration command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint16_t FroBlockKey;
    uint16_t SampleCycles;
    uint16_t AdaptProp512Cutoff;
    uint8_t NoiseBlocks;
    uint8_t SampleDiv;
    uint8_t AutoSeed;
    uint8_t Scale;
    uint8_t RepCntCutoff;
    uint8_t AdaptProp64Cutoff;
    uint8_t fLoadStart;
    uint8_t fReseed;
    uint8_t fAria;
    uint8_t fDRBGForceSeed;
    uint8_t Seed[48];
} VexTokenCmd_TrngConfig_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_Random_t - Random number command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint8_t * Data_p;
    uint16_t Size;
} VexTokenCmd_Random_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_DrbgPP_t - DRBG Post Processing command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t InputDataSize;
    const uint8_t * InputData_p;
    uint8_t * OutputData_p;
    uint32_t OutputDataSize;
    uint16_t Size;
    uint16_t Pattern;
    uint8_t Test;
} VexTokenCmd_DrbgPP_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_NrbgVerify_t - NRBG Verify command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    const uint8_t * InputData_p;
    uint16_t Size;
    uint16_t AdaptProp512Cutoff;
    uint16_t AdaptProp512Count;
    uint8_t AdaptProp512Data;
    uint8_t AdaptProp64Cutoff;
    uint8_t AdaptProp64Count;
    uint8_t AdaptProp64Data;
    uint8_t RepCntCutoff;
    uint8_t RepCntCount;
    uint8_t RepCntData;
} VexTokenCmd_NrbgVerify_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_SF_Milenage_t - Milenage command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Operation;
    uint32_t AssetId;
    uint16_t AssetNumber;
    uint8_t fAMF_SBtest;
    uint8_t RAND[16];
    uint8_t AUTN[16];
    uint8_t SQN[6];
    uint8_t AMF[2];
    uint8_t K[16];
    uint8_t OP[16];
} VexTokenCmd_SF_Milenage_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_SF_MilenageExport_t - Milenage export command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Operation;
    uint32_t AssetId;
    uint8_t * DataBlob_p;
    uint32_t KekAssetId;
    uint32_t DataBlobSize;
    uint32_t AssociatedDataSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_SF_MilenageExport_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetCreate_t - Asset create command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Size;
    uint32_t PolicyLo;
    uint32_t PolicyHi;
} VexTokenCmd_AssetCreate_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetDelete_t - Asset delete command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t AssetId;
} VexTokenCmd_AssetDelete_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetSearch_t - Asset search command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint16_t Number;
} VexTokenCmd_AssetSearch_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetLoadImport_t - Asset load import command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * KeyBlob_p;
    uint32_t AssetId;
    uint32_t KekAssetId;
    uint32_t KeyBlobSize;
    uint32_t AssociatedDataSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_AssetLoadImport_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetLoadDerive_t - Asset load derive command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * Salt_p;
    const uint8_t * IV_p;
    uint32_t AssetId;
    uint32_t KdkAssetId;
    uint32_t AssociatedDataSize;
    uint32_t SaltSize;
    uint32_t IVSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
    uint8_t fCounter;
    uint8_t fRFC5869;
    uint8_t AssetNumber;
} VexTokenCmd_AssetLoadDerive_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetLoadPlaintext_t - Asset load plaintext command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * Data_p;
    uint8_t * KeyBlob_p;
    uint32_t AssetId;
    uint32_t KekAssetId;
    uint32_t DataSize;
    uint32_t AssociatedDataSize;
    uint32_t KeyBlobSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_AssetLoadPlaintext_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetLoadRandom_t - Asset load random command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    uint8_t * KeyBlob_p;
    uint32_t AssetId;
    uint32_t KekAssetId;
    uint32_t AssociatedDataSize;
    uint32_t KeyBlobSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_AssetLoadRandom_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetLoadSymUnwrap_t - Asset load key unwrap command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * KeyBlob_p;
    uint32_t AssetId;
    uint32_t KekAssetId;
    uint32_t KeyBlobSize;
    uint8_t  Algorithm;
} VexTokenCmd_AssetLoadSymUnwrap_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AssetExportCPIF_t - Asset export to CPIF command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t AssetId;
    uint16_t Address;
    uint16_t CPxSelectionBits;
} VexTokenCmd_AssetExportCPIF_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_OTPDataWrite_t - OTP data write command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t KeyBlobSize;
    uint32_t PolicyLo;
    uint32_t PolicyHi;
    const uint8_t * KeyBlob_p;
    uint32_t AssociatedDataSize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_OTPDataWrite_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_ProvisionRandomHUK_t - Provision random HUK command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t KeyBlobSize;
    const uint8_t * KeyBlob_p;
    uint32_t Identity;
    uint32_t AssociatedDataSize;
    uint16_t SampleCycles;
    uint16_t AdaptProp512Cutoff;
    uint8_t NoiseBlocks;
    uint8_t SampleDiv;
    uint8_t AutoSeed;
    uint8_t Scale;
    uint8_t RepCntCutoff;
    uint8_t AdaptProp64Cutoff;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
    uint8_t f128bit;
    uint8_t fAria;
} VexTokenCmd_ProvisionRandomHUK_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_SecureTimer_t - Secure timer command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Operation;
    uint32_t AssetId;
    uint32_t fSecond;
} VexTokenCmd_SecureTimer_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PublicData_t - Public data command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t AssetId;
    const uint8_t * Data_p;
    uint32_t DataSize;
} VexTokenCmd_PublicData_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_MonotonicCounter_t - Monotonic read command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t AssetId;
    const uint8_t * Data_p;
    uint32_t DataSize;
} VexTokenCmd_MonotonicCounter_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetEncrypt_t - Public key encrypt command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    uint32_t CurveFamily;
    uint32_t CurveBits;
} VexTokenCmd_PkAssetInstallCurve_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetSignVerify_t - Public key sign/verify command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    uint32_t TotalMessageSizeLo;
    uint32_t TotalMessageSizeHi;
    const uint8_t * HashData_p;
    uint8_t * Sign_p;
    uint32_t ModulusSizeInBits;
    uint32_t DomainAssetId;
    uint32_t KeyAssetId;
    uint32_t DigestAssetId;
    uint32_t HashDataSize;
    uint32_t SaltSize;          // RSA-PSS only
    uint32_t SignSize;
    uint32_t ExplicitDigestSize;
    uint8_t ExplicitDigest[64];
} VexTokenCmd_PkAssetSignVerify_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetEncrypt_t - Public key encrypt command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * SrcData_p;
    const uint8_t * DstData_p;
    uint32_t ModulusSizeInBits;
    uint32_t DomainAssetId;
    uint32_t KeyAssetId;
    uint32_t SrcDataSize;
    uint32_t DstDataSize;
} VexTokenCmd_PkAssetEncrypt_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetGenKey_t - Public key generate key command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * KeyBlob_p;
    uint8_t * PubKey_p;
    uint32_t ModulusSizeInBits;
    uint32_t DivisorSizeInBits;
    uint32_t DomainAssetId;
    uint32_t PubKeyAssetId;
    uint32_t PrivKeyAssetId;
    uint32_t KekAssetId;
    uint32_t AssociatedDataSize;
    uint32_t KeyBlobSize;
    uint32_t PubKeySize;
    uint8_t AssociatedData[VEXTOKEN_MAX_ASSOC_DATA_SZ];
} VexTokenCmd_PkAssetGenKey_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetKeyCheck_t - Public key check key command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    uint32_t ModulusSizeInBits;
    uint32_t DivisorSizeInBits;
    uint32_t DomainAssetId;
    uint32_t PubKeyAssetId;
    uint32_t PrivKeyAssetId;
} VexTokenCmd_PkAssetKeyCheck_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetGenSharedSecret_t - Public key generate shared secret command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * OtherInfo_p;
    const uint8_t * LocalEphPubKey;
    uint32_t ModulusSizeInBits;
    uint32_t DivisorSizeInBits;
    uint32_t DomainAssetId;
    uint32_t PubKeyAssetId;
    uint32_t PrivKeyAssetId;
    uint32_t PubKey2AssetId;
    uint32_t PrivKey2AssetId;
    uint32_t OtherInfoSize;
    uint32_t LocalEphPubKeySize;
    uint32_t AssetIdListSize;
    uint32_t AssetIdList[VEXTOKEN_MAX_PK_NUM_ASSETS];
    uint8_t fSaveSharedSecret;
} VexTokenCmd_PkAssetGenSharedSecret_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkAssetWrap_t - Public key wrap command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * Data_p;
    uint32_t ModulusSizeInBits;
    uint32_t DomainAssetId;
    uint32_t KeyAssetId;
    uint32_t AssetId;
    uint32_t DataSize;
    uint32_t AdditionalInputSize;
    uint8_t AdditionalInput[208];
} VexTokenCmd_PkAssetWrap_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkEcies_t - Public key ECIES command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Method;
    const uint8_t * Data_p;
    const uint8_t * EphPubKey_p;
    const uint8_t * OtherInfo_p;
    uint32_t ModulusSizeInBits;
    uint32_t DataSize;
    uint32_t EphPubKeySize;
    uint32_t OtherInfoSize;
    uint32_t DomainAssetId;
    uint32_t KeyAssetId;
    uint32_t EphPubKeyAssetId;
    uint32_t AssetDataId;
} VexTokenCmd_PkEcies_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_PkOperation_t - Public key operation command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Operation;
    const uint8_t * InData_p;
    const uint8_t * OutData_p;
    uint32_t PublicExponent;
    uint32_t InDataSize;
    uint32_t OutDataSize;
    uint8_t Nwords;
    uint8_t Mwords;
    uint8_t Mmask;
    uint8_t Index;
} VexTokenCmd_PkOperation_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_AuthUnlock_t - Authenticate Unlock command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    const uint8_t * Sign_p;
    uint32_t AuthStateAssetId;
    uint32_t AuthKeyAssetId;
    uint32_t SignSize;
    uint8_t Nonce[16];
} VexTokenCmd_AuthUnlock_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_SecureDebug_t - Secure Debug command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t AuthStateAssetId;
    uint32_t fSet;
} VexTokenCmd_SecureDebug_t;


/*----------------------------------------------------------------------------
 * VexTokenCmd_Register_t - Register Read/Write command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Address;
    uint32_t Value;
} VexTokenCmd_Register_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_SystemSetTime_t - Set time command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint32_t Seconds;
} VexTokenCmd_SystemSetTime_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_ClockSwitch_t - Clockswitch command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint16_t On;
    uint16_t Off;
} VexTokenCmd_ClockSwitch_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_FirmwareCheck_t - Firmware check command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    const uint8_t * FirmwareImage_p;
    uint32_t FirmwareImageSize;
} VexTokenCmd_FirmwareCheck_t;

/*----------------------------------------------------------------------------
 * VexTokenCmd_UpdateRollbackID_t - Update rollback ID command Token
 */
typedef struct
{
    uint32_t OpCode;
    uint32_t SubCode;
    uint32_t fFromUserSpace;
    uint16_t RollbackID;
} VexTokenCmd_UpdateRollbackID_t;


/*----------------------------------------------------------------------------
 * Result token structures
 */
/*----------------------------------------------------------------------------
 * VexTokenRslt_Generic_t - Result token_Generic
 */
typedef struct
{
    int32_t Result;
} VexTokenRslt_Generic_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_Cipher_t; - Result token_Cipher
 */
typedef struct
{
    int32_t Result;
    uint8_t IV[16];
} VexTokenRslt_Cipher_t;

/*----------------------------------------------------------------------------
 * VexToken_CipherAE - Result token_CipherAE
 */
typedef struct
{
    int32_t Result;
    uint8_t IV[16];
    uint8_t Tag[16];
} VexTokenRslt_CipherAE_t;

/*----------------------------------------------------------------------------
 * VexToken_Hash - Result token_Hash
 */
typedef struct
{
    int32_t Result;
    uint8_t Digest[1600U/8U];           // Required to support SHA-3
} VexTokenRslt_Hash_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_Mac_t - Result token_Mac
 */
typedef struct
{
    int32_t Result;
    uint8_t Mac[64];
} VexTokenRslt_Mac_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_NrbgVerify_t - Result token_NrbgVerify
 */
typedef struct
{
    int32_t Result;
    uint16_t AdaptProp512Cutoff;
    uint16_t AdaptProp512Count;
    uint8_t AdaptProp512Data;
    uint8_t AdaptProp512Fail;
    uint8_t AdaptProp64Cutoff;
    uint8_t AdaptProp64Count;
    uint8_t AdaptProp64Data;
    uint8_t AdaptProp64Fail;
    uint8_t RepCntCutoff;
    uint8_t RepCntCount;
    uint8_t RepCntData;
} VexTokenRslt_NrbgVerify_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_SF_General_t - Result token_SF_General
 */
typedef struct
{
    int32_t Result;
    uint8_t Token[64];
} VexTokenRslt_SF_General_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_SF_Milenage_t - Result token_SF_Milenage
 */
typedef struct
{
    int32_t Result;
    uint32_t AssetId;
    uint8_t RES[8];
    uint8_t CK[16];
    uint8_t IK[16];
    uint8_t SQN[6];
    uint8_t AMF[2];
    uint8_t MACA[8];
    uint8_t MACS[8];
    uint8_t AUTS[14];
    uint8_t AK[6];
    uint8_t AKstar[6];
    uint8_t OPc[16];
    uint8_t EMMCause;
} VexTokenRslt_SF_Milenage_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_SF_MilenageExport_t - Result token_SF_MilenageExport
 */
typedef struct
{
    int32_t Result;
    uint32_t DataBlobSize;
} VexTokenRslt_SF_MilenageExport_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_KeyWrap_t - Result token_KeyWrap
 */
typedef struct
{
    int32_t Result;
    uint32_t Size;
} VexTokenRslt_KeyWrap_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_AssetCreate_t - Result token_AssetCreate
 */
typedef struct
{
    int32_t Result;
    uint32_t AssetId;
} VexTokenRslt_AssetCreate_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_AssetSearch_t - Result token_AssetSearch
 */
typedef struct
{
    int32_t Result;
    uint32_t AssetId;
    uint32_t Size;
} VexTokenRslt_AssetSearch_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_AssetLoad_t - Result token_AssetLoad
 */
typedef struct
{
    int32_t Result;
    uint32_t DataBlobSize;
} VexTokenRslt_AssetLoad_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_ProvisionRandomHUK_t - Result token_ProvisionRandomHUK
 */
typedef struct
{
    int32_t Result;
    uint32_t DataBlobSize;
} VexTokenRslt_ProvisionRandomHUK_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_SecureTimer_t - Result token_SecureTimer
 */
typedef struct
{
    int32_t Result;
    uint32_t AssetId;
    uint32_t ElapsedTime;
} VexTokenRslt_SecureTimer_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_PublicData_t - Result token_PublicData
 */
typedef struct
{
    int32_t Result;
    uint32_t DataSize;
} VexTokenRslt_PublicData_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_MonotonicCounter_t - Result token_MonotonicCounter
 */
typedef struct
{
    int32_t Result;
    uint32_t DataSize;
} VexTokenRslt_MonotonicCounter_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_PkAssetSignVerify_t - Result token_PkAssetSignVerify
 */
typedef struct
{
    int32_t Result;
    uint32_t StateAssetId;
} VexTokenRslt_PkAssetSignVerify_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_PkAssetWrap_t - Result token_PkAssetWrap
 */
typedef struct
{
    int32_t Result;
    uint32_t WrappedDataSize;
} VexTokenRslt_PkAssetWrap_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_AuthUnlock_t - Result token_AuthUnlock
 */
typedef struct
{
    int32_t Result;
    uint8_t Nonce[16];
} VexTokenRslt_AuthUnlock_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_Register_t - Result token_Register
 */
typedef struct
{
    int32_t Result;
    uint32_t Value;
} VexTokenRslt_Register_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_SystemInfo_t - Result token_SystemInfo
 */
typedef struct
{
    int32_t Result;
    struct
    {
        uint16_t MemorySizeInBytes;
        uint8_t Major;          // 0..9
        uint8_t Minor;          // 0..9
        uint8_t Patch;          // 0..9
    } Hardware;
    struct
    {
        uint8_t RollbackId;     // 0..32
        uint8_t Major;          // 0..9
        uint8_t Minor;          // 0..9
        uint8_t Patch;          // 0..9
    } Firmware;
    struct
    {
        uint32_t Identity;
        uint8_t HostID;         // 0..7
        uint8_t NonSecure;      // 0=Secure, !0=Non-Secure
        uint8_t CryptoOfficer;  // 0=Not available, !0=Available
        uint8_t Mode;           // 0=Active mode, 4..6=Error modes, 15=Active mode, with successful Login
        uint8_t ErrorTest;      // Self-test error (only valid when Fatal Error is caused by a self-test)
    } Self;
    struct
    {
        uint16_t ErrorLocation;
        uint8_t ErrorCode;
    } OTP;
} VexTokenRslt_SystemInfo_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_ModuleStatus_t - Result token_ModuleStatus
 */
typedef struct
{
    int32_t Result;
    uint8_t Bit0;
    uint8_t Bit1;
    uint8_t CRC24Ok;
    uint8_t CRC24Busy;
    uint8_t CRC24Error;
    uint8_t FwImageWritten;
    uint8_t FwImageCheckDone;
    uint8_t FwImageAccepted;
    uint8_t FatalError;
} VexTokenRslt_ModuleStatus_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_EipOptions_t - Result token_EipOptions
 */
typedef struct
{
    int32_t Result;
    uint16_t StandardEngines;
    uint16_t CustomEngines;
    uint16_t MailboxSize;
    uint8_t nMailboxes;
    uint8_t HostId;
    uint8_t SecureHostId;
    uint8_t MasterId;
    uint8_t MyHostId;
    uint8_t Protection;
    uint8_t ProtectionAvailable;
} VexTokenRslt_EipOptions_t;

/*----------------------------------------------------------------------------
 * VexTokenRslt_EipVersion_t - Result token_EipVersion
 */
typedef struct
{
    int32_t Result;
    uint8_t MajorVersion;
    uint8_t MinorVersion;
    uint8_t PatchLevel;
    uint8_t EipNumber;
} VexTokenRslt_EipVersion_t;


/*----------------------------------------------------------------------------
 * vex_LogicalToken
 *
 * This function handles the logical tokens coming from an external caller API level.
 *
 * CommandToken_p
 *     Pointer to the buffer with the service request (CommandToken).
 *
 * CommandTokenSize
 *     Size of the service request.
 *
 * ResultToken_p
 *     Pointer to the buffer in which the service result (ResultToken) needs
 *     to be returned.
 *
 * ResultTokenSize
 *     Size of the service result.
 *
 * Return Value:
 *     One of the VexStatus_t values.
 */
VexStatus_t
vex_LogicalToken(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p);

/*----------------------------------------------------------------------------
 * vex_Init
 *
 * This function initializes the VEX Adapter.
 *
*
 * Return Value:
 *     0 if successful, otherwise <0
 */
int32_t
vex_Init(void);


/*----------------------------------------------------------------------------
 * vex_UnInit
 *
 * This function un-initializes the VEX Adapter.
 *
 * Return Value:
 *     None
 */
void
vex_UnInit(void);


#endif /* INCLUDE_GUARD_ADAPTER_VEX_H */

/* end of file adapter_vex.h */
