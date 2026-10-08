/* adapter_vex_asym.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the main entry for asymmetric crypto services.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_intern_asym.h>   // API implementation


/*----------------------------------------------------------------------------
 * vex_Asym
 */
VexStatus_t
vex_Asym(
        const VexTokenCmd_Generic_t * const CommandToken_p,
        VexTokenRslt_Generic_t * const ResultToken_p)
{
    VexStatus_t funcres = VEX_UNSUPPORTED;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_PK_NOASSETS:
        {
            switch (((VexTokenCmd_PkOperation_t *)CommandToken_p)->Operation)
            {
            case VEXTOKEN_PK_OP_NUMLOAD:
                funcres = vex_Asym_PkaNumLoad((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                              ResultToken_p);
                break;

            case VEXTOKEN_PK_OP_NUMSETN:
                funcres = vex_Asym_PkaNumSet((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                             ResultToken_p);
                break;

            case VEXTOKEN_PK_OP_MODEXPE:
            case VEXTOKEN_PK_OP_MODEXPD:
            case VEXTOKEN_PK_OP_MODEXPCRT:
            case VEXTOKEN_PK_OP_ECMONTMUL:
            case VEXTOKEN_PK_OP_ECCMUL:
            case VEXTOKEN_PK_OP_ECCADD:
            case VEXTOKEN_PK_OP_ECDSASIGN:
            case VEXTOKEN_PK_OP_ECDSAVERIFY:
                funcres = vex_Asym_PkaOperation((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                                ResultToken_p);
                break;

            default:
                /* MISRA - Intentially empty */
                break;
            }
        }
        break;

    case VEXTOKEN_SUBCODE_PK_WITHASSETS:
        {
            switch (((VexTokenCmd_PkAssetKeyCheck_t *)CommandToken_p)->Method)
            {
            case VEXTOKEN_PKAS_ECDH_ECDSA_KEYCHK:
            case VEXTOKEN_PKAS_DH_DSA_KEYCHK:
                funcres = vex_Asym_AssetKeyCheck((VexTokenCmd_PkAssetKeyCheck_t *)CommandToken_p,
                                                 ResultToken_p);
                break;

            case VEXTOKEN_PKAS_ECDSA_SIGN:
            case VEXTOKEN_PKAS_SM2DSA_SIGN:
            case VEXTOKEN_PKAS_RSA_PKCS1V1_5_SIGN:
            case VEXTOKEN_PKAS_RSA_PSS_SIGN:
            case VEXTOKEN_PKAS_EDDSA_SIGN_INITIAL:
            case VEXTOKEN_PKAS_EDDSA_SIGN_UPDATE:
            case VEXTOKEN_PKAS_EDDSA_SIGN_FINAL:
                funcres = vex_Asym_AssetSign((VexTokenCmd_PkAssetSignVerify_t *)CommandToken_p,
                                             (VexTokenRslt_PkAssetSignVerify_t *)ResultToken_p);
                break;

            case VEXTOKEN_PKAS_ECDSA_VERIFY:
            case VEXTOKEN_PKAS_SM2DSA_VERIFY:
            case VEXTOKEN_PKAS_RSA_PKCS1V1_5_VERIFY:
            case VEXTOKEN_PKAS_RSA_PSS_VERIFY:
            case VEXTOKEN_PKAS_EDDSA_VERIFY_INITIAL:
            case VEXTOKEN_PKAS_EDDSA_VERIFY_FINAL:
                funcres = vex_Asym_AssetVerify((VexTokenCmd_PkAssetSignVerify_t *)CommandToken_p,
                                               (VexTokenRslt_PkAssetSignVerify_t *)ResultToken_p);
                break;

            case VEXTOKEN_PKAS_DH_GEN_PUBKEY:
            case VEXTOKEN_PKAS_ECDH_ECDSA_GEN_PUBKEY:
            case VEXTOKEN_PKAS_CURVE25519_GEN_PUBKEY:
            case VEXTOKEN_PKAS_EDDSA_GEN_PUBKEY:
                funcres = vex_Asym_AssetGenKeyPublic((VexTokenCmd_PkAssetGenKey_t *)CommandToken_p,
                                                     ResultToken_p);
                break;

            case VEXTOKEN_PKAS_DH_GEN_KEYPAIR:
            case VEXTOKEN_PKAS_ECDH_ECDSA_GEN_KEYPAIR:
            case VEXTOKEN_PKAS_CURVE25519_GEN_KEYPAIR:
            case VEXTOKEN_PKAS_EDDSA_GEN_KEYPAIR:
                funcres = vex_Asym_AssetGenKeyPair((VexTokenCmd_PkAssetGenKey_t *)CommandToken_p,
                                                   ResultToken_p);
                break;

            case VEXTOKEN_PKAS_DH_GEN_SKEYPAIR_SHARED_SECRET:
            case VEXTOKEN_PKAS_DH_GEN_DKEYPAIR_SHARED_SECRET:
            case VEXTOKEN_PKAS_ECDH_GEN_SKEYPAIR_SHARED_SECRET:
            case VEXTOKEN_PKAS_ECDH_GEN_DKEYPAIR_SHARED_SECRET:
            case VEXTOKEN_PKAS_CURVE25519_GEN_SHARED_SECRET:
            case VEXTOKEN_PKAS_SM2KEX_GEN_SHARED_SECRET:
                funcres = vex_Asym_AssetGenSharedSecret((VexTokenCmd_PkAssetGenSharedSecret_t *)CommandToken_p,
                                                        ResultToken_p);
                break;

            case VEXTOKEN_PKAS_RSA_OAEP_WRAP_STRING:
            case VEXTOKEN_PKAS_RSA_OAEP_WRAP_HASH:
            case VEXTOKEN_PKAS_RSA_OAEP_UNWRAP_STRING:
            case VEXTOKEN_PKAS_RSA_OAEP_UNWRAP_HASH:
            case VEXTOKEN_PKAS_RSA_PKCS1V15_WRAP:
            case VEXTOKEN_PKAS_RSA_PKCS1V15_UNWRAP:
            case VEXTOKEN_PKAS_SM2ENC_WRAP:
            case VEXTOKEN_PKAS_SM2ENC_UNWRAP:
                funcres = vex_Asym_AssetKeyWrap((VexTokenCmd_PkAssetWrap_t *)CommandToken_p,
                                                ResultToken_p);
                break;

#ifdef VEX_ENABLE_ASYM_ECIES
            case VEXTOKEN_PKAS_ECIESWRAP:
            case VEXTOKEN_PKAS_ECIESUNWRAP:
                funcres = vex_Asym_AssetEcies((VexTokenCmd_PkEcies_t *)CommandToken_p,
                                              ResultToken_p);
                break;
#endif

            case VEXTOKEN_PKAS_INSTALL_ECCURVE:
                funcres = vex_Asym_AssetInstallECCurve((VexTokenCmd_PkAssetInstallCurve_t *)CommandToken_p,
                                                       (VexTokenRslt_AssetCreate_t *)ResultToken_p);
                break;

            default:
                /* MISRA - Intentially empty */
                break;
            }
        }
        break;

    default:
        /* MISRA - Intentially empty */
        break;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * vex_Asym_PostProcessing
 */
VexStatus_t
vex_Asym_PostProcessing(const VexTokenCmd_Generic_t * const CommandToken_p,
                        VexTokenRslt_Generic_t * const ResultToken_p,
                        const Eip130Token_Result_t * const ResultTokenP_p)
{
    VexStatus_t funcres = VEX_UNSUPPORTED;

    switch (CommandToken_p->SubCode)
    {
    case VEXTOKEN_SUBCODE_PK_NOASSETS:
        {
            switch (((VexTokenCmd_PkOperation_t *)CommandToken_p)->Operation)
            {
            case VEXTOKEN_PK_OP_NUMLOAD:
                funcres = vex_Asym_PkaNumLoad_Post((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                              ResultToken_p,
                                              ResultTokenP_p);
                break;

            case VEXTOKEN_PK_OP_NUMSETN:
                funcres = vex_Asym_PkaNumSet_Post((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                             ResultToken_p,
                                             ResultTokenP_p);
                break;

            case VEXTOKEN_PK_OP_MODEXPE:
            case VEXTOKEN_PK_OP_MODEXPD:
            case VEXTOKEN_PK_OP_MODEXPCRT:
            case VEXTOKEN_PK_OP_ECMONTMUL:
            case VEXTOKEN_PK_OP_ECCMUL:
            case VEXTOKEN_PK_OP_ECCADD:
            case VEXTOKEN_PK_OP_ECDSASIGN:
            case VEXTOKEN_PK_OP_ECDSAVERIFY:
                funcres = vex_Asym_PkaOperation_Post((VexTokenCmd_PkOperation_t *)CommandToken_p,
                                                ResultToken_p,
                                                ResultTokenP_p);
                break;

            default:
                /* MISRA - Intentially empty */
                break;
            }
        }
        break;
    default:
        /* MISRA - Intentially empty */
        break;
    }

    return funcres;
}


/* end of file adapter_vex_asym.c */
