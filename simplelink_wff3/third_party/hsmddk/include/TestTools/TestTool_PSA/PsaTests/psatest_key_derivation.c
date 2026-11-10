/* psatest_key_derivation.c
 *
 * Description: tests for key derivation functions.
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


/*----------------------------------------------------------------------------
 * test_call_key_derive_func
 */
START_TEST(test_call_key_derive_func)
{
    psa_key_derivation_operation_t Operation = { 0 };
    psa_key_attributes_t Attributes = { 0 };
    psa_key_derivation_step_t Step;
    psa_key_id_t Key;
    uint64_t Value;
    psa_status_t Status;
    size_t Capacity;
    uint8_t DataBuffer[4];

    Status = psa_key_derivation_setup(&Operation,
                                      PSA_KEY_DERIVATION_INPUT_SECRET);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_setup()=", Status);

    Capacity = 128;
    Status = psa_key_derivation_get_capacity(&Operation, &Capacity);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_get_capacity()=", Status);

    Status = psa_key_derivation_set_capacity(&Operation, Capacity);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_set_capacity()=", Status);

    Step = 1;
    Status = psa_key_derivation_input_bytes(&Operation, Step,
                                            DataBuffer, sizeof(DataBuffer));
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_input_bytes()=", Status);

    Value = 10U;
    Status = psa_key_derivation_input_integer(&Operation, Step, Value);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_input_integer()=", Status);

    Key = 10U;
    Status = psa_key_derivation_input_key(&Operation, Step, Key);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_input_key()=", Status);

    Status = psa_key_derivation_output_bytes(&Operation, DataBuffer, sizeof(DataBuffer));
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_output_bytes()=", Status);

    Status = psa_key_derivation_output_key(&Attributes, &Operation, &Key);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_output_key()=", Status);

    Status = psa_key_derivation_verify_bytes(&Operation,
                                             DataBuffer, sizeof(DataBuffer));
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_verify_bytes()=", Status);

    Status = psa_key_derivation_verify_key(&Operation, Key);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_verify_key()=", Status);

    Status = psa_key_derivation_abort(&Operation);
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_abort()=", Status);

    Status = psa_key_derivation_key_agreement(&Operation, Step, Key,
                                              DataBuffer, sizeof(DataBuffer));
    fail_if(PSA_ERROR_NOT_SUPPORTED != Status, "psa_key_derivation_key_agreement()=", Status);
}
END_TEST


int
suite_add_test_key_derivation(struct TestSuite * TestSuite_p)
{
    struct TestCase * TestCase_p;

    TestCase_p = sfzutf_tcase_create(TestSuite_p, "KeyDerivation_Tests");
    if (TestCase_p != NULL)
    {
        if (sfzutf_tcase_add_fixture(TestCase_p, psatest_initialize, psatest_terminate) != 0)
        {
             goto FuncErrorReturn;
        }

        if (sfzutf_test_add(TestCase_p, test_call_key_derive_func) != 0) goto FuncErrorReturn;

        return 0;
    }

FuncErrorReturn:
    return -1;
}

/* end of file psatest_key_derivation.c */
