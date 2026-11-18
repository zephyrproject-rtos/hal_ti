/* eip130_token_sf_milenage.h
 *
 * Security Module Token helper functions
 * - Special Functions tokens related functions and definitions for Milenage
 *
 * This module can convert a set of parameters into a Security Module Command
 * token, or parses a set of parameters from a Security Module Result token.
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

#ifndef INCLUDE_GUARD_EIP130TOKEN_SF_MILENAGE_H
#define INCLUDE_GUARD_EIP130TOKEN_SF_MILENAGE_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

#ifdef EIP130_ENABLE_SF_MILENAGE
/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageSqnAdminCreate
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage SQN administration creation.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetNumber
 *      Asset number of the Static Asset with the K and OPc.
 *
 * fAMF_SBtest
 *     Indication to enable the AMF Separation Bit test.
 */
static inline void
Eip130Token_Command_SF_MilenageSqnAdminCreate(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t AssetNumber,
        const bool fAMF_SBtest)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 0U;          /* SQN Administration create */
    CommandToken_p->W[2] |= ((Eip130TokenWord_t)AssetNumber & MASK_6_BITS) << 16;
    if (fAMF_SBtest)
    {
        CommandToken_p->W[2] |= BIT_31; /* Enable AMF Separation Bit test */
    }
    CommandToken_p->W[3] = 0U;          /* Force AssetId to zero */
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageSqnAdminCreate
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * AssetId_p
 *      Pointer to the variable in which the AssetId must be returned.
 */
static inline void
Eip130Token_Result_SF_MilenageSqnAdminCreate(
        const Eip130Token_Result_t * const ResultToken_p,
        Eip130TokenAssetId_t * const AssetId_p)
{
    *AssetId_p = ResultToken_p->W[1];
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageSqnAdminReset
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage SQN administration reset.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to reset.
 */
static inline void
Eip130Token_Command_SF_MilenageSqnAdminReset(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 0U;          /* SQN Administration reset */
    CommandToken_p->W[3] = (Eip130TokenWord_t)AssetId;
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageSqnAdminReset
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage SQN administration export.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the Asset to export.
 *
 * KekAssetId
 *      Asset ID of the Key Encryption Key Asset to use.
 *
 * DataBlobAddress
 *      Data Blob buffer address.
 *
 * DataBlobLengthInBytes
 *      Data Blob buffer length.
 *
 * AssociatedData_p
 *      Associated Data address.
 *
 * AssociatedDataSizeInBytes
 *      Associated Data length.
 */
static inline void
Eip130Token_Command_SF_MilenageSqnAdminExport(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const Eip130TokenAssetId_t KekAssetId,
        const Eip130TokenDmaAddress_t DataBlobAddress,
        const Eip130TokenDmaSize_t DataBlobLengthInBytes,
        const uint8_t * const AssociatedData_p,
        const uint32_t AssociatedDataSizeInBytes)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 3U;          /* SQN Administration export  */
    CommandToken_p->W[3] = (Eip130TokenWord_t)AssetId; /* Asset to export  */
    CommandToken_p->W[4] = (((Eip130TokenWord_t)AssociatedDataSizeInBytes & MASK_8_BITS) << 16) |
                           ((Eip130TokenWord_t)DataBlobLengthInBytes & MASK_10_BITS);
    CommandToken_p->W[5] = (Eip130TokenWord_t)(DataBlobAddress);
    CommandToken_p->W[6] = (Eip130TokenWord_t)(DataBlobAddress >> 32);
    CommandToken_p->W[7] = (Eip130TokenWord_t)KekAssetId; /* AES-SIV Key Encryption Key */

    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U,
                                       AssociatedData_p,
                                       AssociatedDataSizeInBytes);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageSqnAdminExport
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * DataBlobLengthInBytes_p
 *      Pointer to the variable in which the Data Blob size must be returned.
 */
static inline void
Eip130Token_Result_SF_MilenageSqnAdminExport(
        const Eip130Token_Result_t * const ResultToken_p,
        uint32_t * const DataBlobLengthInBytes_p)
{
    *DataBlobLengthInBytes_p = (ResultToken_p->W[1] & MASK_10_BITS);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageAutnVerificationSqn
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage AUTN Verification using the SQN Administration to do Sequence
 * Number checking.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetId
 *      Asset ID of the SQN Administration Asset.
 *
 * RAND_p
 *      RAND data address. Note: 16 bytes data size is assumed.
 *
 * AUTN_p
 *      AUTN data address. Note: 16 bytes data size is assumed.
 */
static inline void
Eip130Token_Command_SF_MilenageAutnVerificationSqn(
        Eip130Token_Command_t * const CommandToken_p,
        const Eip130TokenAssetId_t AssetId,
        const uint8_t * const RAND_p,
        const uint8_t * const AUTN_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 1U;          /* AUTN Verification */
    CommandToken_p->W[3] = (Eip130TokenWord_t)AssetId; /* using SQN Administration */

    Eip130Token_Command_WriteByteArray(CommandToken_p, 4U, RAND_p, 16U);
    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U, AUTN_p, 16U);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageAutnVerification
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage AUTN Verification (no Sequence Number checking).
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetNumber
 *      Asset number of the Static Asset with the K and OPc.
 *
 * RAND_p
 *      RAND data address. Note: 16 bytes data size is assumed.
 *
 * AUTN_p
 *      AUTN data address. Note: 16 bytes data size is assumed.
 */
static inline void
Eip130Token_Command_SF_MilenageAutnVerification(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t AssetNumber,
        const uint8_t * const RAND_p,
        const uint8_t * const AUTN_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 1U;          /* AUTN Verification */
    CommandToken_p->W[2] |= ((Eip130TokenWord_t)AssetNumber & MASK_6_BITS) << 16;
    CommandToken_p->W[3] = 0U;          /* Force AssetId to zero */

    Eip130Token_Command_WriteByteArray(CommandToken_p, 4U, RAND_p, 16U);
    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U, AUTN_p, 16U);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageAutnVerificationEMMCause
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * EMMCause_p
 *      Pointer to the variable in which the EMM Cause must be returned.
 */
static inline void
Eip130Token_Result_SF_MilenageAutnVerificationEMMCause(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const EMMCause_p)
{
    *EMMCause_p = (uint8_t)ResultToken_p->W[1];
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageAutnVerification
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * RES_p
 *      RES data address. Note: 8 bytes data size is assumed.
 *
 * CK_p
 *      CK data address. Note: 16 bytes data size is assumed.
 *
 * IK_p
 *      IK data address. Note: 16 bytes data size is assumed.
 */
static inline void
Eip130Token_Result_SF_MilenageAutnVerification(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const RES_p,
        uint8_t * const CK_p,
        uint8_t * const IK_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U,  8U, RES_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 4U, 16U, CK_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 8U, 16U, IK_p);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageAutnVerificationSQNAMF
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * SQN_AMF_p
 *      SQN and AMF data address. Note: 8 bytes data size is assumed.
 */
static inline void
Eip130Token_Result_SF_MilenageAutnVerificationSQNAMF(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const SQN_AMF_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 12U, 8U, SQN_AMF_p);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageAutsGeneration
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage AUTS Generation.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * AssetNumber
 *      Asset number of the Static Asset with the K and OPc.
 *
 * RAND_p
 *      RAND data address. Note: 16 bytes data size is assumed.
 *
 * SQNms_AMF_p
 *      SQNms_AMF_p data address. Note: 8 bytes data size is assumed.
 */
static inline void
Eip130Token_Command_SF_MilenageAutsGeneration(
        Eip130Token_Command_t * const CommandToken_p,
        const uint16_t AssetNumber,
        const uint8_t * const RAND_p,
        const uint8_t * const SQNms_AMF_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 2U;          /* AUTS Generation */
    CommandToken_p->W[2] |= ((Eip130TokenWord_t)AssetNumber & MASK_6_BITS) << 16;

    Eip130Token_Command_WriteByteArray(CommandToken_p, 4U, RAND_p, 16U);
    /* Note: AMF[2] is directly after SQN[6], so next line can take the 8 bytes copy */
    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U, SQNms_AMF_p, 8U);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageAuts
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * AUTS_p
 *      AUTS data address. Note: 12 bytes data size is assumed.
 */
static inline void
Eip130Token_Result_SF_MilenageAuts(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const AUTS_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p, 2U, 14U, AUTS_p);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SF_MilenageConformance
 *
 * This function is used to intialize the token for the Special Functions
 * Milenage conformance check.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 *
 * RAND_p
 *      RAND data address. Note: 16 bytes data size is assumed.
 *
 * SQN_AMF_p
 *      SQN_AMF data address. Note: 8 bytes data size is assumed.
 *
 * K_p
 *      K data address. Note: 16 bytes data size is assumed.
 *
 * OP_p
 *      OP data address. Note: 16 bytes data size is assumed.
 */
static inline void
Eip130Token_Command_SF_MilenageConformance(
        Eip130Token_Command_t * const CommandToken_p,
        const uint8_t * const RAND_p,
        const uint8_t * const SQN_AMF_p,
        const uint8_t * const K_p,
        const uint8_t * const OP_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SPECIALFUNCTIONS |
                            EIP130TOKEN_SUBCODE_SF_MILENAGE);
    CommandToken_p->W[2] = 4U;          /* Conformance check */

    Eip130Token_Command_WriteByteArray(CommandToken_p, 4U, RAND_p, 16U);
    Eip130Token_Command_WriteByteArray(CommandToken_p, 8U, SQN_AMF_p, 8U);
    Eip130Token_Command_WriteByteArray(CommandToken_p, 10U, K_p, 16U);
    Eip130Token_Command_WriteByteArray(CommandToken_p, 14U, OP_p, 16U);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SF_MilenageConformance
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * RES_p
 *      RES data address. Note: 8 bytes data size is assumed.
 *
 * CK_p
 *      CK data address. Note: 16 bytes data size is assumed.
 *
 * IK_p
 *      IK data address. Note: 16 bytes data size is assumed.
 *
 * MACA_p
 *      RES data address. Note: 8 bytes data size is assumed.
 *
 * MACS_p
 *      CK data address. Note: 8 bytes data size is assumed.
 *
 * AK_p
 *      AK data address. Note: 6 bytes data size is assumed.
 *
 * AKstar_p
 *      AKstar data address. Note: 6 bytes data size is assumed.
 *
 * OPc_p
 *      OPc data address. Note: 16 bytes data size is assumed.
 */
static inline void
Eip130Token_Result_SF_MilenageConformance(
        const Eip130Token_Result_t * const ResultToken_p,
        uint8_t * const RES_p,
        uint8_t * const CK_p,
        uint8_t * const IK_p,
        uint8_t * const MACA_p,
        uint8_t * const MACS_p,
        uint8_t * const AK_p,
        uint8_t * const AKstar_p,
        uint8_t * const OPc_p)
{
    Eip130Token_Result_ReadByteArray(ResultToken_p,  2U,  8U, RES_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p,  4U, 16U, CK_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p,  8U, 16U, IK_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 12U,  8U, MACA_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 14U,  8U, MACS_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 16U,  6U, AK_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 18U,  6U, AKstar_p);
    Eip130Token_Result_ReadByteArray(ResultToken_p, 20U, 16U, OPc_p);
}
#endif


#endif /* INCLUDE_GUARD_EIP130TOKEN_SF_MILENAGE_H */

/* end of file eip130_token_sf_milenage.h */
