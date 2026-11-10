/* valtest_random.c
 *
 * Description: Tests with PRNG/TRNG.
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

static ValSize_t gl_RandomnessBuckets[256];
static ValSize_t gl_RandomnessTotal;

static inline void
randomness_reset(void)
{
    gl_RandomnessTotal = 0;

    memset(gl_RandomnessBuckets, 0, sizeof(gl_RandomnessBuckets));
}


static inline void
randomness_add(
        const uint8_t * rnd_bytes_p,
        ValSize_t nbytes)
{
    ValSize_t i;

    for (i = 0; i < nbytes; i++)
    {
        gl_RandomnessBuckets[rnd_bytes_p[i]]++;
    }
    gl_RandomnessTotal += nbytes;
}


/* check_randomness
 * return 0 if input looks random, -1 otherwise.
 */
static int
randomness_check(void)
{
    unsigned int i;
    int result = 0;
    int MinDelta = 0;
    int PosDelta = 0;
    ValSize_t ExpectedAverage = (gl_RandomnessTotal / 256);
    ValSize_t FaultThreshold = (gl_RandomnessTotal / 2);

    // for i in 0..255, check if bucket[i] ~ nbytes/256
    for (i = 0; i < 256; i++)
    {
        int Delta = (int)(gl_RandomnessBuckets[i] - ExpectedAverage);
        if (Delta < 0)
        {
            Delta = -Delta;
            MinDelta = MAX(Delta, MinDelta);
        }
        else
        {
            PosDelta = MAX(Delta, PosDelta);
        }
        if (Delta > (int)FaultThreshold)
        {
            result = -1;
        }
    }

    if (result)
    {
        LOG_CRIT("Randomness check: %u bytes -> Expected average %d (-%d, %d)\n",
                 (int)gl_RandomnessTotal, (int)ExpectedAverage, MinDelta, PosDelta);

        LOG_CRIT("Randomness buckets:\n");
        for(i = 0; i < 256; i += 8)
        {
            LOG_CRIT("  "
                     "[%02x]=%4u [%02x]=%4u [%02x]=%4u [%02x]=%4u "
                     "[%02x]=%4u [%02x]=%4u [%02x]=%4u [%02x]=%4u\n",
                     i + 0, (unsigned int)gl_RandomnessBuckets[i + 0],
                     i + 1, (unsigned int)gl_RandomnessBuckets[i + 1],
                     i + 2, (unsigned int)gl_RandomnessBuckets[i + 2],
                     i + 3, (unsigned int)gl_RandomnessBuckets[i + 3],
                     i + 4, (unsigned int)gl_RandomnessBuckets[i + 4],
                     i + 5, (unsigned int)gl_RandomnessBuckets[i + 5],
                     i + 6, (unsigned int)gl_RandomnessBuckets[i + 6],
                     i + 7, (unsigned int)gl_RandomnessBuckets[i + 7]);
        }
    }
    else
    {
        LOG_INFO("Randomness check: %u bytes -> Expected average %d (-%d, %d)\n",
                 (int)gl_RandomnessTotal, (int)ExpectedAverage, MinDelta, PosDelta);
    }

    return result;
}


START_TEST(test_rand_config)
{
    ValStatus_t Status;

    Status = valtest_DefaultTrngConfig();
    if (val_IsAccessSecure())
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_ACCESS_ERROR, "val_TrngConfig()=", Status);
    }
}
END_TEST

START_TEST(test_rand)
{
    ValStatus_t Status;
    uint8_t * RandNum_p;
    ValSize_t size;
    ValSize_t i;

    unsupported_unless(valtest_IsTrngActive(true), "TRNG not activated");

    randomness_reset();

    Status = val_RandomReseed();
    if (val_IsAccessSecure())
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_RandomReseed()=", Status);
    }
    else
    {
        fail_if(val_CheckFunctionResult(Status) != VAL_ACCESS_ERROR, "val_RandomReseed()=", Status);
    }

    RandNum_p = (uint8_t *)SFZUTF_MALLOC(1024+32);
    fail_if(RandNum_p == NULL, "Allocation ", (1024+32));

    /* Test to generate 128 bytes of random data */
    size = 128;
    memset(RandNum_p, 0xAA, (size + 32));

    Status = val_RandomData(size, RandNum_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_RandomData(128)=", Status);

    //for (i = 0; i < size; i++)
    //{
    //    L_TRACE(LF_TOTAL_PROGRESS, "%02X ", RandNumber[i]);
    //}

    // check the marker
    for (i = size; i < (size + 32); i++)
    {
        fail_if(RandNum_p[i] != 0xAA,
                "val_RandomData() wrote outside allowed range ", 1);
    }

    randomness_add(RandNum_p, size);

    /* Test to generate 4096 bytes of random data, which is the maximum */
    size = 1024;
    memset(RandNum_p, 0xAB, (size + 32));

    Status = val_RandomData(size, RandNum_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_RandomData(1024)=", Status);

    //for (i = 0; i < size; i++)
    //{
    //    L_TRACE(LF_TOTAL_PROGRESS, "%02X ", RandNumber[i]);
    //}

    // check the marker
    for (i = size; i < (size + 32); i++)
    {
        fail_if(RandNum_p[i] != 0xAB,
                "val_RandomData() wrote outside allowed range ", 2);
    }

    randomness_add(RandNum_p, size);

    // perform a statistical distribution check on the generated data
    // collect more random until we have enough
    size = 1024;
    while(gl_RandomnessTotal < (2*65536))
    {
        Status = val_RandomData(size, RandNum_p);
        fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_RandomData(1024)=", Status);

        randomness_add(RandNum_p, size);
    }

    // check if data looks random
    fail_if(0 != randomness_check(),
            "val_RandomData() returned non-random data ", 0);

    SFZUTF_FREE(RandNum_p);
}
END_TEST

START_TEST(test_rand_arguments)
{
    uint8_t * RandNum_p;
    ValStatus_t Status;

    RandNum_p = (uint8_t *)SFZUTF_MALLOC(100);
    fail_if(RandNum_p == NULL, "Allocation ", 100);

    Status = val_RandomData(0, RandNum_p);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_RandomData(BadArgument1L)=", Status);

    Status = val_RandomData(0xFFFF+1, RandNum_p);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_RandomData(BadArgument1H)=", Status);

    Status = val_RandomData(64, NULL);
    fail_if(Status != VAL_BAD_ARGUMENT, "val_RandomData(BadArgument2)=", Status);

    SFZUTF_FREE(RandNum_p);
}
END_TEST

#ifdef VALTEST_RANDOM_VERYLONG
START_TEST(test_rand_verylong)
{
    uint8_t * RandNum_p;
    int Size = 8096;
    int i = 0;

    unsupported_unless(valtest_IsTrngActive(false), "TRNG not activated");

    RandNum_p = (uint8_t *)SFZUTF_MALLOC(Size);
    fail_if(RandNum_p == NULL, "Allocation ", (int)size);

    for(i = 0; i < 10000 ; i++)
    {
       ValStatus_t Status = val_RandomData(Size, RandNum_p);
       fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_RandomData()=", Status);
    }

    SFZUTF_FREE(RandNum_p);
}
END_TEST
#endif /* VALTEST_RANDOM_VERYLONG */

START_TEST(test_TrngVerPP_CF_12bitRepeatPattern)
{
    static const uint8_t ResultData[] =
    {
        0xFB, 0xD4, 0x84, 0xB6, 0xCE, 0x85, 0x5F, 0x8C, 0xA7, 0xCA, 0xEC, 0x57, 0x72, 0x6E, 0xB4, 0x1E,
        0x03, 0x3B, 0x43, 0x4C, 0x0A, 0x06, 0xD9, 0xCB, 0x7E, 0x23, 0xC1, 0x44, 0xD6, 0x0E, 0x3D, 0x45,
        0x80, 0xE6, 0x0E, 0xFD, 0x60, 0x99, 0x95, 0x8A, 0x05, 0x41, 0xD5, 0xED, 0x7C, 0x6E, 0xE9, 0xF8
    };
    uint8_t * ResultData_p;
    ValStatus_t Status;

    unsupported_unless(val_IsAccessSecure(), "Requires a secure HW connection");

    /* Set special test TRNG configuration */
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    Status = val_TrngConfig(0, 3, 8, 2, 0, 31, 56, 325, true);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);

    ResultData_p = (uint8_t *)SFZUTF_MALLOC(200);
    fail_if(ResultData_p == NULL, "Allocation ", 200);
    memset(ResultData_p, 0, 200);

    Status = val_TrngDrbgPostProcessing(VAL_TRNG_DRBGPP_CF_12B_REPEAT_PATTERN,
                                        0xB16, 1,
                                        NULL, 0,
                                        ResultData_p, 200);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngDrbgPostProcessing()=", Status);
    //Log_HexDump("ResultData", 0, ResultData_p, sizeof(ResultData));
    fail_if(memcmp(ResultData_p, ResultData, sizeof(ResultData)) != 0, " ", -1);

    SFZUTF_FREE(ResultData_p);

    Status = valtest_DefaultTrngConfig();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig(default)=", Status);
}
END_TEST

START_TEST(test_TrngVerPP_CF_ExternalNoise)
{
    static const uint8_t InputData[] =
    {
        0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6B, 0x20, 0x62, 0x72, 0x6F, 0x77, 0x6E, 0x20,
        0x66, 0x6F, 0x78, 0x20, 0x6A, 0x75, 0x6D, 0x70, 0x73, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x20, 0x74,
        0x68, 0x65, 0x20, 0x6C, 0x61, 0x7A, 0x79, 0x20, 0x64, 0x6F, 0x67, 0x2C, 0x20, 0x77, 0x68, 0x6F,
        0x20, 0x77, 0x61, 0x73, 0x20, 0x73, 0x75, 0x72, 0x70, 0x72, 0x69, 0x7A, 0x65, 0x64, 0x2E, 0x20,
        0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6B, 0x20, 0x62, 0x72, 0x6F, 0x77, 0x6E, 0x20,
        0x66, 0x6F, 0x78, 0x20, 0x6A, 0x75, 0x6D, 0x70, 0x73, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x20, 0x74,
        0x68, 0x65, 0x20, 0x6C, 0x61, 0x7A, 0x79, 0x20, 0x64, 0x6F, 0x67, 0x2C, 0x20, 0x77, 0x68, 0x6F,
        0x20, 0x77, 0x61, 0x73, 0x20, 0x73, 0x75, 0x72, 0x70, 0x72, 0x69, 0x7A, 0x65, 0x64, 0x2E, 0x20,
        0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6B, 0x20, 0x62, 0x72, 0x6F, 0x77, 0x6E, 0x20,
        0x66, 0x6F, 0x78, 0x20, 0x6A, 0x75, 0x6D, 0x70, 0x73, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x20, 0x74,
        0x68, 0x65, 0x20, 0x6C, 0x61, 0x7A, 0x79, 0x20, 0x64, 0x6F, 0x67, 0x2C, 0x20, 0x77, 0x68, 0x6F,
        0x20, 0x77, 0x61, 0x73, 0x20, 0x73, 0x75, 0x72, 0x70, 0x72, 0x69, 0x7A, 0x65, 0x64, 0x2E, 0x20,
        0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6B, 0x20, 0x62, 0x72, 0x6F, 0x77, 0x6E, 0x20,
        0x66, 0x6F, 0x78, 0x20, 0x6A, 0x75, 0x6D, 0x70, 0x73, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x20, 0x74,
        0x68, 0x65, 0x20, 0x6C, 0x61, 0x7A, 0x79, 0x20, 0x64, 0x6F, 0x67, 0x2C, 0x20, 0x77, 0x68, 0x6F,
        0x20, 0x77, 0x61, 0x73, 0x20, 0x73, 0x75, 0x72, 0x70, 0x72, 0x69, 0x7A, 0x65, 0x64, 0x2E, 0x20
    };
    static const uint8_t ResultData[] =
    {
        0xDA, 0x12, 0x64, 0x0B, 0x27, 0x7C, 0xF8, 0x22, 0x94, 0x39, 0xEA, 0x7A, 0x1E, 0x02, 0x5A, 0x00,
        0xDB, 0x06, 0x8B, 0x8A, 0x16, 0xC7, 0x07, 0xF0, 0xF0, 0x07, 0xC5, 0x68, 0x00, 0xAA, 0xA7, 0x3F,
        0x8B, 0xD5, 0x16, 0x1E, 0x47, 0x6F, 0x90, 0x03, 0xD6, 0xD1, 0xC9, 0x9F, 0x6F, 0xDA, 0x87, 0xBD
    };
    uint8_t * InputData_p;
    uint8_t * ResultData_p;
    ValStatus_t Status;

    unsupported_unless(val_IsAccessSecure(), "Requires a secure HW connection");

    /* Set special test TRNG configuration */
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    Status = val_TrngConfig(0, 3, 8, 2, 0, 31, 56, 325, true);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);

    InputData_p = (uint8_t *)SFZUTF_MALLOC(sizeof(InputData));
    fail_if(InputData_p == NULL, "Allocation ", (int)sizeof(InputData));
    memcpy(InputData_p, InputData, sizeof(InputData));

    ResultData_p = (uint8_t *)SFZUTF_MALLOC(200);
    fail_if(ResultData_p == NULL, "Allocation ", 200);
    memset(ResultData_p, 0, 200);

    Status = val_TrngDrbgPostProcessing(VAL_TRNG_DRBGPP_CF_EXTERNAL_NOISE,
                                        0, 1,
                                        InputData_p, sizeof(InputData),
                                        ResultData_p, 200);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngDrbgPostProcessing()=", Status);
    //Log_HexDump("ResultData", 0, ResultData_p, sizeof(ResultData));
    fail_if(memcmp(ResultData_p, ResultData, sizeof(ResultData)) != 0, " ", -1);

    SFZUTF_FREE(InputData_p);
    SFZUTF_FREE(ResultData_p);

    Status = valtest_DefaultTrngConfig();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig(default)=", Status);
}
END_TEST

START_TEST(test_TrngVerPP_DRBG_KnownData)
{
    // CTR_DRBG: AES-256 no df, PredictionResistance=False,
    //           EntropyInputLen=384, NonceLen=128, PersonalizationStringLen=0,
    //           AdditionalInputLen=0, Count 0
    static const uint8_t InputData[] =
    {
        0x0D, 0x15, 0xAA, 0x80, 0xB1, 0x6C, 0x3A, 0x10, 0x90, 0x6C, 0xFE, 0xDB, 0x79, 0x5D, 0xAE, 0x0B,
        0x5B, 0x81, 0x04, 0x1C, 0x5C, 0x5B, 0xFA, 0xCB, 0x37, 0x3D, 0x44, 0x40, 0xD9, 0x12, 0x0F, 0x7E,
        0x3D, 0x6C, 0xF9, 0x09, 0x86, 0xCF, 0x52, 0xD8, 0x5D, 0x3E, 0x94, 0x7D, 0x8C, 0x06, 0x1F, 0x91,
        0x6E, 0xE7, 0x93, 0xA3, 0x39, 0x55, 0xD7, 0x2A, 0xD1, 0x2F, 0xD8, 0x0A, 0x8A, 0x3F, 0xCF, 0x95,
        0xED, 0x3B, 0x4D, 0xAC, 0x57, 0x95, 0xFE, 0x25, 0xCF, 0x86, 0x9F, 0x7C, 0x27, 0x57, 0x3B, 0xBC,
        0x56, 0xF1, 0xAC, 0xAE, 0x13, 0xA6, 0x50, 0x42, 0xB3, 0x40, 0x09, 0x3C, 0x46, 0x4A, 0x7A, 0x22
    };
    static const uint8_t ResultData[] =
    {
        0x28, 0xE0, 0xEB, 0xB8, 0x21, 0x01, 0x66, 0x50, 0x8C, 0x8F, 0x65, 0xF2, 0x20, 0x7B, 0xD0, 0xA3,
        0x94, 0x6F, 0x51, 0x82, 0xD5, 0x45, 0x10, 0xB9, 0x46, 0x12, 0x48, 0xF5, 0x71, 0xCA, 0x06, 0xC9
    };
    uint8_t * InputData_p;
    uint8_t * ResultData_p;
    ValStatus_t Status;

    unsupported_unless(val_IsAccessSecure(), "Requires a secure HW connection");

    /* Set special test TRNG configuration */
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    Status = val_TrngConfig(0, 3, 8, 2, 0, 31, 56, 325, true);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);

    InputData_p = (uint8_t *)SFZUTF_MALLOC(sizeof(InputData));
    fail_if(InputData_p == NULL, "Allocation ", (int)sizeof(InputData));
    memcpy(InputData_p, InputData, sizeof(InputData));

    ResultData_p = (uint8_t *)SFZUTF_MALLOC(sizeof(ResultData));
    fail_if(ResultData_p == NULL, "Allocation ", (int)sizeof(ResultData));
    memset(ResultData_p, 0, sizeof(ResultData));

    Status = val_TrngDrbgPostProcessing(VAL_TRNG_DRBGPP_KNOWN_ANSWER,
                                        0, 2,
                                        InputData_p, sizeof(InputData),
                                        ResultData_p, sizeof(ResultData));
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngDrbgPostProcessing()=", Status);
    //Log_HexDump("ResultData", 0, ResultData_p, sizeof(ResultData));
    fail_if(memcmp(ResultData_p, ResultData, sizeof(ResultData)) != 0, " ", -1);

    SFZUTF_FREE(InputData_p);
    SFZUTF_FREE(ResultData_p);

    Status = valtest_DefaultTrngConfig();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig(default)=", Status);
}
END_TEST

START_TEST(test_TrngVerHW_128BytesPattern)
{
    static const uint8_t InputData[] =
    {
        0x3C, 0x83, 0x91, 0x02, 0xD1, 0x2B, 0xF5, 0x9A, 0xCC, 0x75, 0x9F, 0xCC, 0x9F, 0xF7, 0xD1, 0x81,
        0xF5, 0xEE, 0xD3, 0x39, 0xDF, 0x32, 0xF0, 0x5E, 0xA7, 0xCD, 0x70, 0x07, 0x18, 0x9D, 0x85, 0xBA,
        0x61, 0xBC, 0xA7, 0x7C, 0xBC, 0xFD, 0x00, 0x56, 0x05, 0xA3, 0x28, 0xE4, 0x9A, 0xEF, 0x7B, 0x22,
        0xED, 0x15, 0xA1, 0x19, 0x69, 0x1B, 0x37, 0xDC, 0x61, 0x94, 0x26, 0xC5, 0x30, 0xE3, 0x2C, 0x35,
        0xD8, 0xC1, 0x83, 0x2D, 0xF2, 0x50, 0x39, 0x5F, 0x9F, 0x8D, 0x68, 0xC9, 0x14, 0xD9, 0xCB, 0xAF,
        0xFF, 0x53, 0xE7, 0x28, 0xE7, 0x2D, 0xCB, 0xB3, 0x7D, 0xB0, 0x43, 0xF9, 0x38, 0x2B, 0x96, 0xD5,
        0x4B, 0x32, 0xA0, 0xAB, 0x96, 0x71, 0x3A, 0x76, 0x45, 0x0D, 0x5C, 0x11, 0xD1, 0x25, 0x17, 0x64,
        0xED, 0x0B, 0x12, 0xF6, 0xBD, 0xC8, 0x26, 0x37, 0x32, 0xD8, 0x0A, 0xDE, 0x99, 0x6B, 0x3E, 0x5E
    };
    uint8_t * InputData_p;
    ValStatus_t Status;
    uint8_t RepCntCutoff = 0;
    uint8_t RepCntCount = 0;
    uint8_t RepCntData = 0;
    uint8_t AdaptProp64Cutoff = 0;
    uint8_t AdaptProp64Count = 0;
    uint8_t AdaptProp64Data = 0;
    uint8_t AdaptProp64Fail = 0;
    uint16_t AdaptProp512Cutoff = 0;
    uint16_t AdaptProp512Count = 0;
    uint8_t AdaptProp512Data = 0;
    uint8_t AdaptProp512Fail = 0;

    unsupported_unless(val_IsAccessSecure(), "Requires a secure HW connection");

    /* Set special test TRNG configuration */
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    Status = val_TrngConfig(0, 3, 8, 1, 0, 31, 56, 325, true);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);

    InputData_p = (uint8_t *)SFZUTF_MALLOC(sizeof(InputData));
    fail_if(InputData_p == NULL, "Allocation ", (int)sizeof(InputData));
    memcpy(InputData_p, InputData, sizeof(InputData));

    Status = val_TrngNrbgSelfTest(InputData_p, sizeof(InputData),
                                  &RepCntCutoff, &RepCntCount, &RepCntData,
                                  &AdaptProp64Cutoff, &AdaptProp64Count, &AdaptProp64Data,
                                  &AdaptProp512Cutoff, &AdaptProp512Count, &AdaptProp512Data,
                                  &AdaptProp64Fail, &AdaptProp512Fail);
    SFZUTF_FREE(InputData_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngNrbgSelfTest()=", Status);

    Status = valtest_DefaultTrngConfig();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig(default)=", Status);

    /*
    // Result depends on the implementation, so it is not checked
    fail_if(RepCntCutoff != 0x1F, " ", RepCntCutoff);
    fail_if(RepCntCount != 0x01, " ", RepCntCount);
    fail_if(RepCntData != 0x19, " ", RepCntData);
    fail_if(AdaptProp64Cutoff != 0x33, " ", AdaptProp64Cutoff);
    fail_if(AdaptProp64Count != 0x01, " ", AdaptProp64Count);
    fail_if(AdaptProp64Data != 0x2F, " ", AdaptProp64Data);
    fail_if(AdaptProp64Fail != 0, " ", AdaptProp64Fail);
    fail_if(AdaptProp512Cutoff != 0x8C0, " ", AdaptProp512Cutoff);
    fail_if(AdaptProp512Count != 0x000, " ", AdaptProp512Count);
    fail_if(AdaptProp512Data != 0x04D, " ", AdaptProp512Data);
    fail_if(AdaptProp512Fail != 0, " ", AdaptProp512Fail);
    */
}
END_TEST

START_TEST(test_TrngVerHW_8BytesPatternWithPropRep)
{
    static const uint8_t InputData[] =
    {
        0xD0, 0xCE, 0xCC, 0xCA, 0xC8, 0xC6, 0xC4, 0xC2
    };
    uint8_t * InputData_p;
    ValStatus_t Status;
    uint8_t RepCntCutoff = 0x1A;
    uint8_t RepCntCount = 0x3F;
    uint8_t RepCntData = 0xFF;
    uint8_t AdaptProp64Cutoff = 0x2E;
    uint8_t AdaptProp64Count = 0x3F;
    uint8_t AdaptProp64Data = 0xFF;
    uint8_t AdaptProp64Fail = 0;
    uint16_t AdaptProp512Cutoff = 0x81;
    uint16_t AdaptProp512Count = 0x1FF;
    uint8_t AdaptProp512Data = 0xFF;
    uint8_t AdaptProp512Fail = 0;

    unsupported_unless(val_IsAccessSecure(), "Requires a secure HW connection");

    /* Set special test TRNG configuration */
    /* IntegrationItem:
     * The TRNG configuration needs to be adapted to meet the customer
     * specific FROs timing/behavior. */
    Status = val_TrngConfig(0, 3, 8, 1, 0, 31, 56, 325, true);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig()=", Status);

    InputData_p = (uint8_t *)SFZUTF_MALLOC(sizeof(InputData));
    fail_if(InputData_p == NULL, "Allocation ", (int)sizeof(InputData));
    memcpy(InputData_p, InputData, sizeof(InputData));

    Status = val_TrngNrbgSelfTest(InputData_p, sizeof(InputData),
                                  &RepCntCutoff, &RepCntCount, &RepCntData,
                                  &AdaptProp64Cutoff, &AdaptProp64Count, &AdaptProp64Data,
                                  &AdaptProp512Cutoff, &AdaptProp512Count, &AdaptProp512Data,
                                  &AdaptProp64Fail, &AdaptProp512Fail);
    SFZUTF_FREE(InputData_p);
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngNrbgSelfTest()=", Status);

    Status = valtest_DefaultTrngConfig();
    fail_if(val_CheckFunctionResult(Status) != VAL_SUCCESS, "val_TrngConfig(default)=", Status);

    fail_if(RepCntCutoff != 0x1A, " ", (int)RepCntCutoff);
    fail_if(RepCntCount != 0x01, " ", (int)RepCntCount);
    fail_if(RepCntData != 0x68, " ", (int)RepCntData);
    fail_if(AdaptProp64Cutoff != 0x2E, " ", (int)AdaptProp64Cutoff);
    fail_if(AdaptProp64Count != 0x00, " ", (int)AdaptProp64Count);
    fail_if(AdaptProp64Data != 0x61, " ", (int)AdaptProp64Data);
    fail_if(AdaptProp64Fail != 0, " ", (int)AdaptProp64Fail);
    fail_if(AdaptProp512Cutoff != 0x81, " ", (int)AdaptProp512Cutoff);
    fail_if(AdaptProp512Count != 0x000, " ", (int)AdaptProp512Count);
    fail_if(AdaptProp512Data != 0x061, " ", (int)AdaptProp512Data);
    fail_if(AdaptProp512Fail != 0, " ", (int)AdaptProp512Fail);
}
END_TEST


int
suite_add_test_Random(
        struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "Random_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, valtest_initialize, valtest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_rand_config) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_rand) != 0) goto FuncErrorReturn;
#ifdef VALTEST_RANDOM_VERYLONG
        if (sfzutf_test_add(TestCase_p, test_rand_verylong) != 0) goto FuncErrorReturn;
#endif
        if (sfzutf_test_add(TestCase_p, test_TrngVerPP_CF_12bitRepeatPattern) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_TrngVerPP_CF_ExternalNoise) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_TrngVerPP_DRBG_KnownData) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_TrngVerHW_128BytesPattern) != 0) goto FuncErrorReturn;
        if (sfzutf_test_add(TestCase_p, test_TrngVerHW_8BytesPatternWithPropRep) != 0) goto FuncErrorReturn;

        if (valtest_StrictArgsCheck())
        {
            if (sfzutf_test_add(TestCase_p, test_rand_arguments) != 0) goto FuncErrorReturn;
        }

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file valtest_random.c */
