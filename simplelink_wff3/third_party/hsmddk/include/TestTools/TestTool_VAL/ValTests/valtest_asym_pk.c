/* valtest_asym_pk.c
 *
 * Description: PK operations with assets tests
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

static bool
LoadVector(
        const uint8_t * const VectorData_p,
        const uint32_t VectorDataSize,
        uint8_t * const Vector_p,
        const uint32_t VectorSize,
        bool fBigEndian)
{
    if (VectorDataSize > VectorSize)
    {
        return false;
    }
    if (fBigEndian)
    {
        uint32_t i, j;

        for (i = 0, j = (VectorDataSize - 1); i < VectorDataSize; i++, j--)
        {
            Vector_p[i] = VectorData_p[j];
        }
    }
    else
    {
        memcpy(Vector_p, VectorData_p, VectorDataSize);
    }
    if (VectorSize > VectorDataSize)
    {
        memset(&Vector_p[VectorDataSize], 0, (VectorSize - VectorDataSize));
    }
    return true;
}


static uint8_t *
AllocAndInitializeVector(
        const uint8_t * const VectorData_p,
        const uint32_t VectorDataSize,
        const uint32_t VectorSize,
        bool fBigEndian)
{
    uint8_t * Vector_p = NULL;

    if (VectorSize >= VectorDataSize)
    {
        Vector_p = SFZUTF_MALLOC(VectorSize);
        if (Vector_p != NULL)
        {
            (void)LoadVector(VectorData_p, VectorDataSize,
                             Vector_p, VectorSize,
                             fBigEndian);
        }
    }
    return Vector_p;
}


static bool
CheckResultVector(
        const uint8_t * const Vector_p,
        const uint32_t VectorSize,
        const uint8_t * const Result_p,
        const uint32_t ResultSize,
        bool fBigEndian)
{
    if ((VectorSize < ResultSize) ||
        (Vector_p == NULL) ||
        (Result_p == NULL))
    {
        return false;
    }

    if (fBigEndian)
    {
        uint32_t i, j;

        for (i = 0, j = (ResultSize - 1); i < ResultSize; i++, j--)
        {
            if (Vector_p[i] != Result_p[j])
            {
                return false;
            }
        }

    }
    else
    {
        if (memcmp(Vector_p, Result_p, ResultSize) != 0)
        {
            return false;
        }
    }

    if (VectorSize > ResultSize)
    {
        uint32_t i;

        for (i = ResultSize; i < VectorSize; i++)
        {
            if (Vector_p[i] != 0)
            {
                return false;
            }
        }
    }

    return true;
}

START_TEST(test_AsymPkModExpE)
{
    static const uint8_t Mod[] = { 0xE0, 0x08, 0xE0, 0x07, 0xE0, 0x06, 0xE0, 0x05, 0xE0, 0x04, 0xE0, 0x03, 0xE0, 0x02, 0xE0, 0x01 };
    static const uint8_t Msg[] = { 0xDA, 0x7A, 0x00, 0x04, 0xDA, 0x7A, 0x00, 0x03, 0xDA, 0x7A, 0x00, 0x02, 0xDA, 0x7A, 0x00, 0x01 };
    static const uint8_t Result[] = { 0xBA, 0x40, 0xCC, 0x16, 0x46, 0x36, 0x9E, 0xB0, 0x58, 0x35, 0xB5, 0x58, 0x4E, 0x83, 0x0F, 0x02 };
    static const uint32_t Exponent = 0x12345678;
    //static const uint8_t Mod[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD };
    //static const uint8_t Msg[] = { 0xDA, 0x7A, 0x00, 0x02, 0xDA, 0x7A, 0x00, 0x01 };
    //static const uint8_t Result[] = { 0x2D, 0x6C, 0x37, 0xF5, 0xF0, 0x52, 0x01, 0xC8 };
    //static const uint32_t Exponent = 0x10001;
    ValStatus_t Status;
    ValSize_t ResultSize;
    ValSize_t VectorSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(Mod) + 3) & (ValSize_t)~3;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    // Next function is only intended for function coverage
    Status = val_ClaimOverrule();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_ClaimOverrule()=", Status);

    Vector_p = AllocAndInitializeVector(Mod, sizeof(Mod), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(Mod)=", Status);

    Vector_p = AllocAndInitializeVector(Msg, sizeof(Msg), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    ResultSize = VectorSize;
    Result_p = SFZUTF_MALLOC(VectorSize);
    fail_if(Result_p == NULL, "Allocation ", (int)VectorSize);
    memset(Result_p, 0, VectorSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_MODEXPE, Exponent,
                                         Vector_p, VectorSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, Result, sizeof(Result), true) == false, "", Status);

    SFZUTF_FREE(Result_p);
    SFZUTF_FREE(Vector_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkModExpD)
{
    static const uint8_t Msg[] = { 0xDA, 0x7A, 0x00, 0x04, 0xDA, 0x7A, 0x00, 0x03, 0xDA, 0x7A, 0x00, 0x02, 0xDA, 0x7A, 0x00, 0x01 };
    static const uint8_t Mod[] = { 0xE0, 0x08, 0xE0, 0x07, 0xE0, 0x06, 0xE0, 0x05, 0xE0, 0x04, 0xE0, 0x03, 0xE0, 0x02, 0xE0, 0x01 };
    static const uint8_t Exp[] = { 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78 };
    static const uint8_t Result[] = { 0xCC, 0x91, 0xB1, 0xFB, 0x61, 0xDC, 0x6B, 0xF9, 0xA2, 0x29, 0x60, 0x65, 0x2C, 0x78, 0x84, 0x31 };
    ValStatus_t Status;
    ValSize_t ResultSize;
    ValSize_t VectorSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(Mod) + 3) & (ValSize_t)~3;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(Mod, sizeof(Mod), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(Mod)=", Status);

    Vector_p = AllocAndInitializeVector(Exp, sizeof(Exp), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(Exp)=", Status);

    Vector_p = AllocAndInitializeVector(Msg, sizeof(Msg), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    ResultSize = VectorSize;
    Result_p = SFZUTF_MALLOC(VectorSize);
    fail_if(Result_p == NULL, "Allocation ", (int)VectorSize);
    memset(Result_p, 0, VectorSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_MODEXPD, 0,
                                         Vector_p, VectorSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, Result, sizeof(Result), true) == false, "", Status);

    SFZUTF_FREE(Result_p);
    SFZUTF_FREE(Vector_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkModExpCRT)
{
    static const uint8_t Msg[] = {
        0x22, 0x5E, 0xDA, 0x31, 0x4F, 0x01, 0x96, 0x0B, 0x93, 0x8E, 0xA8, 0x77, 0xA2, 0x40, 0x82, 0xDA,
        0xBA, 0x1D, 0x7F, 0xE2, 0x0D, 0xB5, 0x9D, 0xDB, 0x72, 0xF5, 0xA9, 0x4A, 0x28, 0x8C, 0x9C, 0x56,
        0x8A, 0xA5, 0xDA, 0x2C, 0x4A, 0xC4, 0x32, 0x8E, 0xBD, 0x36, 0x7D, 0x95, 0xEC, 0x12, 0x8A, 0x3A,
        0xC6, 0x45, 0x08, 0x9B, 0xC4, 0x5C, 0x58, 0x46, 0x24, 0x37, 0x24, 0xB4, 0x89, 0x0C, 0x05, 0x13
    };
    static const uint8_t ModP[] = {
        0xAC, 0x06, 0x6F, 0x76, 0x97, 0xE5, 0xB2, 0xEF, 0xF9, 0x23, 0x1C, 0x91, 0xFD, 0x1C, 0xC5, 0x64,
        0x31, 0xE9, 0x97, 0x13, 0x47, 0x96, 0x68, 0xCC, 0x7E, 0x03, 0x50, 0x9B, 0xB0, 0x9E, 0x2F, 0xD7
    };
    static const uint8_t ModQ[] = {
        0xA8, 0x26, 0x2F, 0xC3, 0x2F, 0x50, 0x9D, 0x4B, 0xD8, 0x40, 0x58, 0xE3, 0x70, 0xC6, 0x43, 0x4F,
        0x37, 0x23, 0x8F, 0x48, 0x38, 0x0C, 0x6F, 0xF2, 0x0F, 0x62, 0xA7, 0xE4, 0xDF, 0xD2, 0x9C, 0x23
    };
    static const uint8_t ExpP[] = {
        0x02, 0x8B, 0xF7, 0x89, 0xB7, 0xEA, 0xB8, 0x72, 0xAA, 0xE8, 0xB3, 0x73, 0x23, 0x49, 0x4B, 0x24,
        0x40, 0x49, 0xB3, 0x66, 0x2A, 0x89, 0x63, 0x30, 0xBE, 0xCA, 0x36, 0x29, 0x34, 0xA5, 0x20, 0xBC
    };
    static const uint8_t ExpQ[] = {
        0x01, 0x38, 0x93, 0x3B, 0x74, 0x0A, 0x88, 0x37, 0x00, 0x38, 0x81, 0x1B, 0xD0, 0x7A, 0xBE, 0x59,
        0x28, 0xE3, 0xBB, 0x0A, 0x70, 0x77, 0x9C, 0xFF, 0xD9, 0x62, 0x68, 0x76, 0xF7, 0x01, 0xE5, 0x6A
    };
    static const uint8_t QInv[] = {
        0x28, 0x0C, 0xC3, 0x78, 0x17, 0x54, 0xBE, 0xDD, 0x4B, 0xB7, 0x9E, 0x72, 0x38, 0x5B, 0x79, 0xB3,
        0xDD, 0x1E, 0x92, 0xD2, 0x1F, 0xFC, 0xC9, 0x3D, 0x53, 0x7E, 0x67, 0x21, 0x97, 0x23, 0xDA, 0x58
    };
    static const uint8_t Result[] = {
        0x11, 0x3E, 0xC4, 0x73, 0x3B, 0x87, 0x57, 0x47, 0x2B, 0x63, 0x2E, 0xEB, 0xFB, 0xFC, 0x04, 0xB3,
        0xBA, 0x5A, 0x4D, 0x5A, 0xD0, 0x34, 0x3E, 0xB4, 0x4B, 0x98, 0xBB, 0x02, 0xA0, 0xD8, 0x8F, 0x6A,
        0x22, 0x1D, 0xB7, 0xFE, 0xCE, 0xDA, 0xC7, 0xA1, 0x72, 0x4D, 0x1C, 0x7A, 0xEA, 0x0E, 0xAD, 0x38,
        0xD0, 0xBD, 0xA7, 0x0B, 0x54, 0xC4, 0xAF, 0x49, 0x3C, 0x2B, 0xD2, 0x78, 0xDD, 0x4A, 0x0B, 0x14
    };
    ValStatus_t Status;
    ValSize_t ResultSize;
    ValSize_t VectorSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(ModP) + 3) & (ValSize_t)~3; // Or sizeof(ModQ) if this one is bigger

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(ModP, sizeof(ModP), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ModP)=", Status);

    Vector_p = AllocAndInitializeVector(ModQ, sizeof(ModQ), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ModQ)=", Status);

    Vector_p = AllocAndInitializeVector(ExpP, sizeof(ExpP), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ExpP)=", Status);

    Vector_p = AllocAndInitializeVector(ExpQ, sizeof(ExpQ), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ExpQ)=", Status);

    Vector_p = AllocAndInitializeVector(QInv, sizeof(QInv), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(4, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(QInv)=", Status);

    VectorSize = 2 * VectorSize;           // 2 x VectorSize
    Vector_p = AllocAndInitializeVector(Msg, sizeof(Msg), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    ResultSize = VectorSize;
    Result_p = SFZUTF_MALLOC(VectorSize);
    fail_if(Result_p == NULL, "Allocation ", (int)VectorSize);
    memset(Result_p, 0, VectorSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_MODEXPCRT, 0,
                                         Vector_p, VectorSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, Result, sizeof(Result), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkEcMontMul)
{
    static const uint8_t p[]  = {
        0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xED
    };
    static const uint8_t a[]  = { 0x07, 0x6D, 0x06 };
    static const uint8_t b[]  = { 0x01 };
    static const uint8_t k[]  = {
        0x6A, 0x2C, 0xB9, 0x1D, 0xA5, 0xFB, 0x77, 0xB1, 0x2A, 0x99, 0xC0, 0xEB, 0x87, 0x2F, 0x4C, 0xDF,
        0x45, 0x66, 0xB2, 0x51, 0x72, 0xC1, 0x16, 0x3C, 0x7D, 0xA5, 0x18, 0x73, 0x0A, 0x6D, 0x07, 0x70
    };
    static const uint8_t xi[] = { 0x09 };
    static const uint8_t xo[] = {
        0x6A, 0x4E, 0x9B, 0xAA, 0x8E, 0xA9, 0xA4, 0xEB, 0xF4, 0x1A, 0x38, 0x26, 0x0D, 0x3A, 0xBF, 0x0D,
        0x5A, 0xF7, 0x3E, 0xB4, 0xDC, 0x7D, 0x8B, 0x74, 0x54, 0xA7, 0x30, 0x89, 0x09, 0xF0, 0x20, 0x85
    };
    ValStatus_t Status;
    ValSize_t VectorSize;
    ValSize_t ResultSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(p) + 3) & (ValSize_t)~3;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(p, sizeof(p), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(p)=", Status);

    Vector_p = AllocAndInitializeVector(a, sizeof(a), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(a)=", Status);

    Vector_p = AllocAndInitializeVector(b, sizeof(b), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(b)=", Status);

    Vector_p = AllocAndInitializeVector(k, sizeof(k), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(k)=", Status);

    Vector_p = AllocAndInitializeVector(xi, sizeof(xi), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Result_p = SFZUTF_MALLOC(VectorSize);
    fail_if(Result_p == NULL, "Allocation ", (int)VectorSize);
    memset(Result_p, 0, VectorSize);
    ResultSize = VectorSize;

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECMONTMUL, 0,
                                         Vector_p, VectorSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, xo, sizeof(xo), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkEccAddA)
{
    static const uint8_t p[]    = { 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    static const uint8_t a[]    = { 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC };
    static const uint8_t b[]    = { 0xE8, 0x75, 0x79, 0xC1, 0x10, 0x79, 0xF4, 0x3D, 0xD8, 0x24, 0x99, 0x3C, 0x2C, 0xEE, 0x5E, 0xD3 };
    // Add
    static const uint8_t axi[]  = { 0xA1, 0x07, 0xB3, 0x80, 0xD3, 0x9A, 0x85, 0xDF, 0xCA, 0x28, 0xBF, 0xA6, 0xB1, 0x37, 0x05, 0xC2 };
    static const uint8_t ayi[]  = { 0xF7, 0x3B, 0x60, 0x7B, 0xC8, 0xA3, 0x05, 0xAB, 0x06, 0xDD, 0xF9, 0x9B, 0x2D, 0x5A, 0xDB, 0xA6 };
    static const uint8_t axi1[] = { 0xB0, 0x3E, 0x33, 0x18, 0x6A, 0x8B, 0x90, 0x14, 0x67, 0x01, 0xDF, 0x02, 0x47, 0xC6, 0xC7, 0xE9 };
    static const uint8_t ayi1[] = { 0xD1, 0x6D, 0x85, 0xEF, 0x6B, 0xB7, 0x3C, 0xF9, 0x75, 0xFE, 0x9F, 0x9F, 0x3B, 0xFF, 0x99, 0xD8 };
    static const uint8_t axo[]  = { 0xE8, 0x3A, 0x43, 0x7F, 0x6B, 0x06, 0xF5, 0x6A, 0xC6, 0x63, 0xEF, 0x5E, 0x82, 0x58, 0x6F, 0x05 };
    static const uint8_t ayo[]  = { 0xC2, 0x86, 0x53, 0xD9, 0x76, 0x61, 0x21, 0xEC, 0x11, 0x40, 0x0D, 0xEC, 0xAF, 0x8A, 0xA7, 0x39 };
    // Double
    static const uint8_t dxi[]  = { 0xE9, 0x73, 0x96, 0xF3, 0x8E, 0xD9, 0x12, 0x66, 0x05, 0x4D, 0x9A, 0x1F, 0xAC, 0x6F, 0x99, 0x00 };
    static const uint8_t dyi[]  = { 0x5F, 0xDA, 0x36, 0x13, 0x7C, 0xE6, 0xCE, 0x0A, 0xF0, 0xB6, 0xE3, 0xAC, 0xDD, 0x38, 0x4F, 0x57 };
    static const uint8_t dxo[]  = { 0xBA, 0xD9, 0xA6, 0xE7, 0x6D, 0x6F, 0x2A, 0x5C, 0x53, 0x07, 0x14, 0xAA, 0x59, 0xEA, 0x04, 0x36 };
    static const uint8_t dyo[]  = { 0x12, 0x79, 0xBF, 0x83, 0x9A, 0xD4, 0x38, 0xF3, 0x5F, 0x1B, 0xCD, 0x11, 0x0D, 0xA2, 0x0E, 0x8F };
    ValStatus_t Status;
    ValSize_t VectorSize;
    ValSize_t BufferWordsSize;
    ValSize_t ResultSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(p) + 3) & (ValSize_t)~3;
    BufferWordsSize = (2 + ((VectorSize / 4) & 1)) * 4;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    // Add
    Vector_p = AllocAndInitializeVector(p, sizeof(p), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(p)=", Status);

    Vector_p = AllocAndInitializeVector(a, sizeof(a), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(a)=", Status);

    Vector_p = AllocAndInitializeVector(b, sizeof(b), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(b)=", Status);

    Vector_p = AllocAndInitializeVector(axi1, sizeof(axi1), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(axi1)=", Status);

    Vector_p = AllocAndInitializeVector(ayi1, sizeof(ayi1), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(4, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ayi1)=", Status);

    ResultSize = (2 * VectorSize) + BufferWordsSize;
    Vector_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Vector_p == NULL, "Allocation ", (int)ResultSize);
    (void)LoadVector(axi, sizeof(axi), Vector_p, (uint32_t)VectorSize, true);
    (void)LoadVector(ayi, sizeof(ayi), &Vector_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, true);
    Result_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultSize);
    memset(Result_p, 0, ResultSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECCADD, 0,
                                         Vector_p, ResultSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, axo, sizeof(axo), true) == false, "", Status);
    fail_if(CheckResultVector(&Result_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, ayo, sizeof(ayo), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    // Double
    Vector_p = AllocAndInitializeVector(dxi, sizeof(dxi), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(dxi1)=", Status);

    Vector_p = AllocAndInitializeVector(dyi, sizeof(dyi), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(4, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(dyi1)=", Status);

    ResultSize = (2 * VectorSize) + BufferWordsSize;
    Vector_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Vector_p == NULL, "Allocation ", (int)ResultSize);
    (void)LoadVector(dxi, sizeof(dxi), Vector_p, (uint32_t)VectorSize, true);
    (void)LoadVector(dyi, sizeof(dyi), &Vector_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, true);
    Result_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultSize);
    memset(Result_p, 0, ResultSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECCADD, 0,
                                         Vector_p, ResultSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, dxo, sizeof(dxo), true) == false, "", Status);
    fail_if(CheckResultVector(&Result_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, dyo, sizeof(dyo), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkEccMulA)
{
    static const uint8_t p[]  = { 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    static const uint8_t a[]  = { 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC };
    static const uint8_t b[]  = { 0xE8, 0x75, 0x79, 0xC1, 0x10, 0x79, 0xF4, 0x3D, 0xD8, 0x24, 0x99, 0x3C, 0x2C, 0xEE, 0x5E, 0xD3 };
    static const uint8_t k[]  = { 0xED, 0x63, 0xD5, 0xFF, 0x2F, 0x92, 0x21, 0x13, 0x84, 0x26, 0xF1, 0x56, 0x0F, 0x16, 0x6B, 0xBB };
    static const uint8_t xi[] = { 0x16, 0x1F, 0xF7, 0x52, 0x8B, 0x89, 0x9B, 0x2D, 0x0C, 0x28, 0x60, 0x7C, 0xA5, 0x2C, 0x5B, 0x86 };
    static const uint8_t yi[] = { 0xCF, 0x5A, 0xC8, 0x39, 0x5B, 0xAF, 0xEB, 0x13, 0xC0, 0x2D, 0xA2, 0x92, 0xDD, 0xED, 0x7A, 0x83 };
    static const uint8_t xo[] = { 0xC4, 0x64, 0x27, 0x8D, 0x03, 0x20, 0x12, 0xAA, 0xF9, 0xC6, 0x6F, 0xFA, 0x40, 0x6F, 0x72, 0x4D };
    static const uint8_t yo[] = { 0x93, 0x87, 0xE3, 0xF9, 0x27, 0x4C, 0xD4, 0xAF, 0x3C, 0x10, 0x60, 0xA0, 0x02, 0x2C, 0x27, 0x08 };
    ValStatus_t Status;
    ValSize_t VectorSize;
    ValSize_t BufferWordsSize;
    ValSize_t ResultSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(p) + 3) & (ValSize_t)~3;
    BufferWordsSize = (2 + ((VectorSize / 4) & 1)) * 4;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(p, sizeof(p), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(p)=", Status);

    Vector_p = AllocAndInitializeVector(a, sizeof(a), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(a)=", Status);

    Vector_p = AllocAndInitializeVector(b, sizeof(b), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(b)=", Status);

    Vector_p = AllocAndInitializeVector(k, sizeof(k), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(k)=", Status);

    ResultSize = (2 * VectorSize) + BufferWordsSize;
    Vector_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Vector_p == NULL, "Allocation ", (int)ResultSize);
    (void)LoadVector(xi, sizeof(xi), Vector_p, (uint32_t)VectorSize, true);
    (void)LoadVector(yi, sizeof(yi), &Vector_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, true);
    Result_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultSize);
    memset(Result_p, 0, ResultSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECCMUL, 0,
                                         Vector_p, ResultSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, xo, sizeof(xo), true) == false, "", Status);
    fail_if(CheckResultVector(&Result_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, yo, sizeof(yo), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkEcdsaSign)
{
    static const uint8_t p[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    static const uint8_t a[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC
    };
    static const uint8_t b[]  = {
        0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F, 0xA7, 0xE9, 0xAB, 0x72, 0x24, 0x30, 0x49,
        0xFE, 0xB8, 0xDE, 0xEC, 0xC1, 0x46, 0xB9, 0xB1
    };
    static const uint8_t n[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xDE, 0xF8, 0x36,
        0x14, 0x6B, 0xC9, 0xB1, 0xB4, 0xD2, 0x28, 0x31
    };
    static const uint8_t gx[]  = {
        0x18, 0x8D, 0xA8, 0x0E, 0xB0, 0x30, 0x90, 0xF6, 0x7C, 0xBF, 0x20, 0xEB, 0x43, 0xA1, 0x88, 0x00,
        0xF4, 0xFF, 0x0A, 0xFD, 0x82, 0xFF, 0x10, 0x12
    };
    static const uint8_t gy[]  = {
        0x07, 0x19, 0x2B, 0x95, 0xFF, 0xC8, 0xDA, 0x78, 0x63, 0x10, 0x11, 0xED, 0x6B, 0x24, 0xCD, 0xD5,
        0x73, 0xF9, 0x77, 0xA1, 0x1E, 0x79, 0x48, 0x11
    };
    static const uint8_t grz[] = {
        0x00, 0x00, 0x00, 0x00, 0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F, 0xA7, 0xE9, 0xAB,
        0x72, 0x24, 0x30, 0x49, 0x00, 0x00, 0x00, 0x01
    };
    static const uint8_t h[] = {
        0x00, 0x00, 0x00, 0x00, 0x2D, 0xC0, 0x45, 0x2E, 0xAC, 0x88, 0xE3, 0x8A, 0xC8, 0xAC, 0x3D, 0x41,
        0xF9, 0x8E, 0x8C, 0xB6, 0xB6, 0xD7, 0xAA, 0x7F
    };
    static const uint8_t k[] = {
        0xE6, 0x01, 0xA9, 0x45, 0x79, 0x38, 0x50, 0xA2, 0x32, 0xEB, 0xBA, 0x2A, 0x4C, 0x85, 0xAE, 0x1C,
        0xE0, 0x0C, 0x8F, 0x43, 0x0B, 0x03, 0x31, 0x42
    };
    static const uint8_t y[] = {
        0x7F, 0x43, 0x54, 0xE3, 0xF6, 0xB6, 0x8B, 0x41, 0x9D, 0x2A, 0x09, 0x52, 0xC6, 0xFA, 0xC4, 0xEA,
        0xCD, 0x25, 0x52, 0x4A, 0x79, 0xA0, 0x22, 0xEA
    };
    static const uint8_t ro[] = {
        0x87, 0xFE, 0x31, 0x74, 0xB6, 0x15, 0xF5, 0x52, 0x46, 0x96, 0x9E, 0x12, 0x44, 0x17, 0x14, 0xAB,
        0xEF, 0xF1, 0x74, 0x24, 0xAB, 0x18, 0x7F, 0x11
    };
    static const uint8_t so[] = {
        0xB3, 0x36, 0x85, 0xD6, 0x69, 0xCF, 0x0E, 0x70, 0xF7, 0x70, 0x50, 0x76, 0xC0, 0x21, 0xB1, 0x1E,
        0x40, 0xC9, 0x5B, 0x5D, 0x98, 0xBA, 0x5D, 0xCD
    };
    ValStatus_t Status;
    ValSize_t VectorSize;
    ValSize_t BufferWordsSize;
    ValSize_t ResultSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(p) + 3) & (ValSize_t)~3;
    BufferWordsSize = (2 + ((VectorSize / 4) & 1)) * 4;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(p, sizeof(p), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(p)=", Status);

    Vector_p = AllocAndInitializeVector(a, sizeof(a), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(a)=", Status);

    Vector_p = AllocAndInitializeVector(b, sizeof(b), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(b)=", Status);

    Vector_p = AllocAndInitializeVector(n, sizeof(n), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(n)=", Status);

    Vector_p = AllocAndInitializeVector(gx, sizeof(gx), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(4, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(gx)=", Status);

    Vector_p = AllocAndInitializeVector(gy, sizeof(gy), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(5, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(gy)=", Status);

    Vector_p = AllocAndInitializeVector(grz, sizeof(grz), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(6, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(grz)=", Status);

    Vector_p = AllocAndInitializeVector(h, sizeof(h), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(7, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(h)=", Status);

    Vector_p = AllocAndInitializeVector(k, sizeof(k), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(8, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(k)=", Status);

    Vector_p = AllocAndInitializeVector(y, sizeof(y), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);

    ResultSize = (2 * VectorSize) + BufferWordsSize;
    Result_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultSize);
    memset(Result_p, 0, ResultSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECDSASIGN, 0,
                                         Vector_p, VectorSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, ro, sizeof(ro), true) == false, "", Status);
    fail_if(CheckResultVector(&Result_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, so, sizeof(so), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

START_TEST(test_AsymPkEcdsaVerify)
{
    static const uint8_t p[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    static const uint8_t a[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC
    };
    static const uint8_t b[]  = {
        0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F, 0xA7, 0xE9, 0xAB, 0x72, 0x24, 0x30, 0x49,
        0xFE, 0xB8, 0xDE, 0xEC, 0xC1, 0x46, 0xB9, 0xB1
    };
    static const uint8_t n[]  = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xDE, 0xF8, 0x36,
        0x14, 0x6B, 0xC9, 0xB1, 0xB4, 0xD2, 0x28, 0x31
    };
    static const uint8_t gx[]  = {
        0x18, 0x8D, 0xA8, 0x0E, 0xB0, 0x30, 0x90, 0xF6, 0x7C, 0xBF, 0x20, 0xEB, 0x43, 0xA1, 0x88, 0x00,
        0xF4, 0xFF, 0x0A, 0xFD, 0x82, 0xFF, 0x10, 0x12
    };
    static const uint8_t gy[]  = {
        0x07, 0x19, 0x2B, 0x95, 0xFF, 0xC8, 0xDA, 0x78, 0x63, 0x10, 0x11, 0xED, 0x6B, 0x24, 0xCD, 0xD5,
        0x73, 0xF9, 0x77, 0xA1, 0x1E, 0x79, 0x48, 0x11
    };
    static const uint8_t grz[] = {
        0x00, 0x00, 0x00, 0x00, 0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F, 0xA7, 0xE9, 0xAB,
        0x72, 0x24, 0x30, 0x49, 0x00, 0x00, 0x00, 0x01
    };
    static const uint8_t h[] = {
        0x00, 0x00, 0x00, 0x00, 0x2D, 0xC0, 0x45, 0x2E, 0xAC, 0x88, 0xE3, 0x8A, 0xC8, 0xAC, 0x3D, 0x41,
        0xF9, 0x8E, 0x8C, 0xB6, 0xB6, 0xD7, 0xAA, 0x7F
    };
    static const uint8_t pkx[] = {
        0xD1, 0xFB, 0x5B, 0xFB, 0xAB, 0xB9, 0x8B, 0xB7, 0x9C, 0x8B, 0xEC, 0x0F, 0xB7, 0x3D, 0x1D, 0x54,
        0xEF, 0xB4, 0xF2, 0xDF, 0x3D, 0x58, 0x9A, 0xBF
    };
    static const uint8_t pky[] = {
        0xDB, 0x5D, 0x79, 0x4A, 0xCC, 0x1F, 0xB4, 0x04, 0x41, 0x3A, 0x30, 0x71, 0xE4, 0x7B, 0x1A, 0x9C,
        0x5A, 0xE5, 0xCD, 0x5F, 0x17, 0xFE, 0xC0, 0x0D
    };
    static const uint8_t pkrz[] = {
        0xAB, 0xB9, 0x8B, 0xB7, 0x9C, 0x8B, 0xEC, 0x0F, 0xB7, 0x3D, 0x1D, 0x54, 0xEF, 0xB4, 0xF2, 0xDF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
    };
    static const uint8_t ri[] = {
        0x87, 0xFE, 0x31, 0x74, 0xB6, 0x15, 0xF5, 0x52, 0x46, 0x96, 0x9E, 0x12, 0x44, 0x17, 0x14, 0xAB,
        0xEF, 0xF1, 0x74, 0x24, 0xAB, 0x18, 0x7F, 0x11
    };
    static const uint8_t si[] = {
        0xB3, 0x36, 0x85, 0xD6, 0x69, 0xCF, 0x0E, 0x70, 0xF7, 0x70, 0x50, 0x76, 0xC0, 0x21, 0xB1, 0x1E,
        0x40, 0xC9, 0x5B, 0x5D, 0x98, 0xBA, 0x5D, 0xCD
    };
    ValStatus_t Status;
    ValSize_t VectorSize;
    ValSize_t PointSize;
    ValSize_t ResultSize;
    ValSize_t BufferWordsSize;
    uint8_t * Vector_p;
    uint8_t * Result_p;

    VectorSize = (sizeof(p) + 3) & (ValSize_t)~3;
    BufferWordsSize = (2 + ((VectorSize / 4) & 1)) * 4;

    Status = val_AsymPkaClaim((uint8_t)(VectorSize / 4), 0, 0);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaim()=", Status);

    Vector_p = AllocAndInitializeVector(p, sizeof(p), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(0, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(p)=", Status);

    Vector_p = AllocAndInitializeVector(a, sizeof(a), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(1, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(a)=", Status);

    Vector_p = AllocAndInitializeVector(b, sizeof(b), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(2, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(b)=", Status);

    Vector_p = AllocAndInitializeVector(n, sizeof(n), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(3, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(n)=", Status);

    Vector_p = AllocAndInitializeVector(gx, sizeof(gx), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(4, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(gx)=", Status);

    Vector_p = AllocAndInitializeVector(gy, sizeof(gy), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(5, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(gy)=", Status);

    Vector_p = AllocAndInitializeVector(grz, sizeof(grz), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(6, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(grz)=", Status);

    Vector_p = AllocAndInitializeVector(h, sizeof(h), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(7, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(h)=", Status);

    Vector_p = AllocAndInitializeVector(ri, sizeof(ri), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(8, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(ri)=", Status);

    Vector_p = AllocAndInitializeVector(si, sizeof(si), (uint32_t)VectorSize, true);
    fail_if(Vector_p == NULL, "Allocation ", (int)VectorSize);
    Status = val_AsymPkaLoadVector(9, Vector_p, VectorSize);
    SFZUTF_FREE(Vector_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaLoadVector(si)=", Status);

    PointSize = (3 * VectorSize) + (2 * BufferWordsSize);
    Vector_p = SFZUTF_MALLOC(PointSize);
    fail_if(Vector_p == NULL, "Allocation ", (int)PointSize);
    (void)LoadVector(pkx, sizeof(pkx), Vector_p, (uint32_t)VectorSize, true);
    (void)LoadVector(pky, sizeof(pky), &Vector_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, true);
    (void)LoadVector(pkrz, sizeof(pkrz), &Vector_p[2 * (VectorSize + BufferWordsSize)], (uint32_t)VectorSize, true);

    ResultSize = (2 * VectorSize) + BufferWordsSize;
    Result_p = SFZUTF_MALLOC(ResultSize);
    fail_if(Result_p == NULL, "Allocation ", (int)ResultSize);
    memset(Result_p, 0, ResultSize);

    Status = val_AsymPkaExecuteOperation(VAL_ASYM_PKA_OP_ECDSAVERIFY, 0,
                                         Vector_p, PointSize,
                                         Result_p, &ResultSize);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaExecuteOperation()=", Status);
    fail_if(CheckResultVector(Result_p, (uint32_t)VectorSize, ri, sizeof(ri), true) == false, "", Status);
    fail_if(CheckResultVector(&Result_p[VectorSize + BufferWordsSize], (uint32_t)VectorSize, ri, sizeof(ri), true) == false, "", Status);

    SFZUTF_FREE(Vector_p);
    SFZUTF_FREE(Result_p);

    Status = val_AsymPkaClaimRelease();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_AsymPkaClaimRelease()=", Status);
}
END_TEST

int
suite_add_test_AsymPk(
    struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "AsymCrypto_PkWithoutAssets");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
            goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_AsymPkModExpE) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkModExpD) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkModExpCRT) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkEcMontMul) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkEccAddA) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkEccMulA) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkEcdsaSign) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_AsymPkEcdsaVerify) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_asym_pk.c */
