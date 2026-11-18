/* testvectors_aes_f8_data.h
 *
 * Description: AES-f8 test vector data, automatically generated from
 *              stdvect.aes.aes_f8_rfc3711.py
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

#ifndef INCLUDE_GUARD_TEST_VECTORS_AES_F8_DATA_H
#define INCLUDE_GUARD_TEST_VECTORS_AES_F8_DATA_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

static const uint8_t
RFC3711_B_1_key [] = {
    0x23, 0x48, 0x29, 0x00, 0x84, 0x67, 0xbe, 0x18, 0x6c, 0x3d, 0xe1, 0x4a,
    0xae, 0x72, 0xd6, 0x2c
};

static const uint8_t
RFC3711_B_1_saltkey [] = {
    0x32, 0xf2, 0x87, 0x0d
};

static const uint8_t
RFC3711_B_1_iv [] = {
    0x00, 0x6e, 0x5c, 0xba, 0x50, 0x68, 0x1d, 0xe5, 0x5c, 0x62, 0x15, 0x99,
    0xd4, 0x62, 0x56, 0x4a
};

static const uint8_t
RFC3711_B_1_ptx [] = {
    0x70, 0x73, 0x65, 0x75, 0x64, 0x6f, 0x72, 0x61, 0x6e, 0x64, 0x6f, 0x6d,
    0x6e, 0x65, 0x73, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x65, 0x20,
    0x6e, 0x65, 0x78, 0x74, 0x20, 0x62, 0x65, 0x73, 0x74, 0x20, 0x74, 0x68,
    0x69, 0x6e, 0x67
};

static const uint8_t
RFC3711_B_1_ctx [] = {
    0x01, 0x9c, 0xe7, 0xa2, 0x6e, 0x78, 0x54, 0x01, 0x4a, 0x63, 0x66, 0xaa,
    0x95, 0xd4, 0xee, 0xfd, 0x1a, 0xd4, 0x17, 0x2a, 0x14, 0xf9, 0xfa, 0xf4,
    0x55, 0xb7, 0xf1, 0xd4, 0xb6, 0x2b, 0xd0, 0x8f, 0x56, 0x2c, 0x0e, 0xef,
    0x7c, 0x48, 0x02
};


static const uint8_t
TC2_key [] = {
    0xee, 0x34, 0x6c, 0x62, 0x1e, 0xc9, 0x7c, 0x1f, 0x67, 0xce, 0x37, 0x11,
    0x85, 0x51, 0x4a, 0x8a
};

static const uint8_t
TC2_saltkey [] = {
    0xf2, 0xbd
};

static const uint8_t
TC2_iv [] = {
    0xf1, 0x84, 0x44, 0x08, 0xab, 0xae, 0xa5, 0xb8, 0xfc, 0xba, 0x33, 0x2e,
    0x78, 0xc4, 0x85, 0x98
};

static const uint8_t
TC2_ptx [] = {
    0x04, 0xe5, 0x1c, 0xf0, 0x20, 0x2d, 0x4c, 0x59, 0x0f, 0xd2, 0xe1, 0x28,
    0xa5, 0x7c, 0x50, 0x30
};

static const uint8_t
TC2_ctx [] = {
    0x34, 0x67, 0x42, 0x55, 0xf9, 0x13, 0xc8, 0x37, 0x19, 0x4e, 0x71, 0x88,
    0x80, 0xda, 0xcc, 0x08
};


#endif /* INCLUDE_GUARD_TEST_VECTORS_AES_F8_DATA_H */

/* end of file testvectors_aes_f8_data.h */
