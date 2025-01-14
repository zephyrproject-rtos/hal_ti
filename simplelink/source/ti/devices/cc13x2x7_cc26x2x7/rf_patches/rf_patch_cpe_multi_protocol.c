/******************************************************************************
*  Filename:       rf_patch_cpe_multi_protocol.c
*
*  Description: RF core patch for multi-protocol support (all available API command sets) in CC13x2 and CC26x2
*
*  Copyright (c) 2015-2022, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/
//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#include "rf_patch_cpe_multi_protocol.h"

#ifndef CPE_PATCH_TYPE
#define CPE_PATCH_TYPE static const uint32_t
#endif

#ifndef SYS_PATCH_TYPE
#define SYS_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC static
#endif

#ifndef _APPLY_PATCH_TAB
#define _APPLY_PATCH_TAB
#endif


CPE_PATCH_TYPE patchImageMultiProtocol[] = {
   0x210044e1,
   0x21004099,
   0x210040b5,
   0x2100411f,
   0x210040e1,
   0x21004555,
   0x21004591,
   0x21004151,
   0x2100415d,
   0x21004169,
   0x21004185,
   0x2100463b,
   0x210041cd,
   0x210041e5,
   0x210041fd,
   0x21004239,
   0x2100466f,
   0x210046df,
   0x210047eb,
   0xd00507db,
   0xf803f000,
   0x70084902,
   0xb570bd70,
   0x47284d01,
   0x210004e0,
   0x0002241d,
   0x79654c07,
   0xf809f000,
   0x40697961,
   0xd5030749,
   0x4a042101,
   0x60110389,
   0xb570bd70,
   0x47084902,
   0x21000380,
   0x40041108,
   0x0000592d,
   0xf819f000,
   0x296cb2e1,
   0x2804d00b,
   0x2806d001,
   0x4910d107,
   0x07c97809,
   0x7821d103,
   0xd4000709,
   0x490d2002,
   0x210c780a,
   0xd0024211,
   0x2280490b,
   0xb003600a,
   0xb5f0bdf0,
   0x4909b083,
   0x20004708,
   0x47884908,
   0x78014804,
   0x43912240,
   0x48067001,
   0x00004700,
   0x210000c8,
   0x21000133,
   0xe000e200,
   0x00031641,
   0x000063f7,
   0x00031b23,
   0x4700b570,
   0xfa46f000,
   0x47004800,
   0x00007f57,
   0xfa46f000,
   0x47004800,
   0x0000881b,
   0x0a889905,
   0xd1052880,
   0x78884913,
   0x0f800780,
   0xfa50f000,
   0x47004800,
   0x00006ed9,
   0x480fb40f,
   0x290088c1,
   0x4610d002,
   0xfa44f000,
   0x0a9b9b07,
   0x2b834d08,
   0x4c08d108,
   0x069b8923,
   0xf000d504,
   0x2800f805,
   0x3542d000,
   0x4728bc0f,
   0x4804b570,
   0x00004700,
   0x00020b1f,
   0x21000160,
   0x21000380,
   0x000209eb,
   0x781a4b09,
   0x43a22408,
   0xd0002800,
   0x701a4322,
   0x47104a00,
   0x00008e83,
   0x78084903,
   0xd4010700,
   0x47004802,
   0x00004770,
   0x21000380,
   0x00007e5f,
   0x4a094808,
   0x429a6803,
   0x4808d10a,
   0x4b088902,
   0xd0011ad2,
   0xd1032a01,
   0x49066e40,
   0x99034788,
   0x47184b05,
   0x210002a8,
   0x000203bd,
   0x21000160,
   0x00001821,
   0x000035f1,
   0x000006bd,
   0x20284a04,
   0x48044790,
   0x60412101,
   0x4a044803,
   0x47106041,
   0x0000424f,
   0x40045000,
   0x40046000,
   0x00004285,
   0x4901b5f8,
   0x00004708,
   0x0000640d,
   0x4d1fb570,
   0xb2c47828,
   0x4780481e,
   0x28037828,
   0x2c03d134,
   0x481cd032,
   0x0d406880,
   0x481a07c2,
   0x31604601,
   0x2a003080,
   0x241fd003,
   0x8845570c,
   0x241ee002,
   0x8805570c,
   0xd01f2c00,
   0x4a154813,
   0x79006941,
   0x10484341,
   0x69494911,
   0x49101840,
   0x7f493940,
   0x05404790,
   0x42691540,
   0xdb0d4288,
   0xdc0b42a8,
   0x69994b0c,
   0x4602b288,
   0x43620c09,
   0x12520409,
   0xb2801880,
   0x61984308,
   0x0000bd70,
   0x210002e4,
   0x00004179,
   0x21000028,
   0x21000380,
   0x21000300,
   0x000081cb,
   0x40044040,
   0x4c86b510,
   0x31404621,
   0x28017d08,
   0x4884d134,
   0x08407dc0,
   0xd02f07c0,
   0x30604620,
   0x08527942,
   0xd02907d2,
   0x0b808940,
   0xd1252801,
   0x09417e08,
   0xd00c07c9,
   0x07006fa1,
   0x0fc08809,
   0x04090240,
   0x66604308,
   0x1c806fa0,
   0xfa76f000,
   0x4874e013,
   0x69803020,
   0x28006840,
   0x4a72d00e,
   0x78012300,
   0x1a5956d3,
   0x00c9d408,
   0x78411808,
   0xd00307c9,
   0x66616801,
   0x66a06840,
   0x4780486b,
   0xb5f8bd10,
   0x496a4c66,
   0x36204626,
   0x46257b70,
   0x90003540,
   0x00b8792f,
   0x68801840,
   0x28004780,
   0x4960d128,
   0x09097dc9,
   0xd02307c9,
   0x32644622,
   0xd0202f15,
   0x23007e29,
   0x07ff094f,
   0x7d6dd003,
   0xd0002d00,
   0x9f002301,
   0x43bb6fa5,
   0x7b73d012,
   0xd00f2b00,
   0x065b7d23,
   0x88d2d50c,
   0x2a010b92,
   0x08c9d108,
   0xd00507c9,
   0x0b8988a9,
   0xd1012901,
   0x73712100,
   0x7eabbdf8,
   0x2b017de9,
   0x2300d0e3,
   0xb570e7e1,
   0x46254c46,
   0x35806a60,
   0xd11d2800,
   0x5d002054,
   0x28002200,
   0x2064d017,
   0x08805d00,
   0xd01207c0,
   0x888868a9,
   0x28010b80,
   0x483dd10d,
   0x08407dc0,
   0xd00807c0,
   0x3020483a,
   0x68006980,
   0xd0022800,
   0x60a86229,
   0x622ae000,
   0x47804839,
   0x29006a61,
   0x6a29d103,
   0xd0002900,
   0xbd7060a9,
   0x4c2fb5f8,
   0x46204934,
   0x7d023040,
   0xd02f2a00,
   0x46257e80,
   0x28033580,
   0x2804d002,
   0xe027d003,
   0x75e82001,
   0x2064e024,
   0x08805d00,
   0xd01f07c0,
   0x888068a8,
   0x28010b80,
   0x4822d11a,
   0x7dc07dea,
   0xd0132a00,
   0x07c008c0,
   0x4626d012,
   0x7b773620,
   0x46014788,
   0xd1084339,
   0x06097d21,
   0x8869d505,
   0x29010b89,
   0x2100d101,
   0xbdf87371,
   0xe7ea0880,
   0xbdf84788,
   0x30804812,
   0x75c12100,
   0x47004817,
   0x3140490f,
   0x28267108,
   0xdc06d014,
   0xd0132815,
   0xd00b281b,
   0xd104281f,
   0x283de00a,
   0x2847d00e,
   0x490bd00a,
   0x18400080,
   0x47706880,
   0x4770480c,
   0x4770480c,
   0x4770480c,
   0x4770480c,
   0x4770480c,
   0x21000160,
   0x210000c8,
   0x210004e0,
   0x00024959,
   0x00025500,
   0x00023d8f,
   0x00023075,
   0x00022a15,
   0x210044d5,
   0x21004461,
   0x21004403,
   0x21004383,
   0x21004305,
   0x490cb510,
   0x4a0c4788,
   0x5e512106,
   0xd0072900,
   0xd0052902,
   0xd0032909,
   0xd0012910,
   0xd1072911,
   0x43c92177,
   0xdd014288,
   0xdd012800,
   0x43c0207f,
   0x0000bd10,
   0x000065a9,
   0x21000380,
   0x4810b510,
   0x481088c1,
   0xd0182905,
   0x68214c0f,
   0x0052084a,
   0x6ba26022,
   0x00520852,
   0x602163a2,
   0xfdccf7ff,
   0x07006ba0,
   0x2001d408,
   0x60606020,
   0x1c402000,
   0xdbfc280c,
   0x62202014,
   0xf7ffbd10,
   0xbd10fdbd,
   0x21000380,
   0x00005b3f,
   0x40046000,
   0x490c6b80,
   0x0f000700,
   0x47707148,
   0x490a4a09,
   0x79502318,
   0x7e4956cb,
   0x428118c0,
   0x4608dd01,
   0x280fe002,
   0x200fdd00,
   0x090989d1,
   0x43010109,
   0x477081d1,
   0x210002e0,
   0x21000088,
   0x79c94908,
   0x07d208ca,
   0x40c1d008,
   0x07c94806,
   0x4906d001,
   0x4906e000,
   0x60c11c49,
   0x20004770,
   0x00004770,
   0x210000e8,
   0x21000028,
   0x00000188,
   0x00000150,
   0x4833b510,
   0x47804c31,
   0xd0072801,
   0x7d213420,
   0xd1032900,
   0x4a2f2101,
   0x60910509,
   0x2807bd10,
   0x4a2dd001,
   0x4a2d4710,
   0x72c8604a,
   0x22014770,
   0x21024b2c,
   0x4718482a,
   0xb5104827,
   0x478030f8,
   0x6a404829,
   0xd10d2800,
   0x200a4928,
   0x28005608,
   0x1c40da09,
   0x4608d007,
   0x6a403820,
   0x42884924,
   0x4780d100,
   0xf7ffbd10,
   0xbd10ffe2,
   0x4b222100,
   0x46084a20,
   0x20014718,
   0x02404920,
   0x48206008,
   0x780122fb,
   0x70014011,
   0x300c4813,
   0xb5104700,
   0x4788491c,
   0x39204915,
   0xd0072801,
   0xd5040402,
   0x85082000,
   0x62484818,
   0xbd102001,
   0x4b0a6a4a,
   0x429a330c,
   0x4a15d101,
   0x490be005,
   0x4b146a4a,
   0xd1f2429a,
   0x624a4a13,
   0x0000bd10,
   0x21000160,
   0x0002a675,
   0x40041100,
   0x000291a9,
   0x21004651,
   0x00000806,
   0x0000069f,
   0x21000108,
   0x21000154,
   0x00029263,
   0x21004689,
   0x0002b4b5,
   0xe000e180,
   0x21000380,
   0x000296f7,
   0x2100467f,
   0x210046c7,
   0x00029569,
   0x210046bd,
   0x4601b510,
   0x482c4b2b,
   0xbf20e000,
   0x07926942,
   0x4829d1fb,
   0x30407ada,
   0x2a0b6800,
   0xf000d101,
   0xbd10f843,
   0x1a522220,
   0x4a244090,
   0x6993ba00,
   0x48214043,
   0xbf20e000,
   0x07926942,
   0x0088d4fb,
   0x1840491f,
   0x481c63c3,
   0x60033040,
   0xb5104770,
   0xe0004819,
   0x6942bf20,
   0xd4fb0792,
   0x4b176b42,
   0x40506998,
   0x07d48a5a,
   0x2401d001,
   0x08524060,
   0x2220825a,
   0x40881a51,
   0xba00490f,
   0x60083140,
   0xb510bd10,
   0xf7ff4604,
   0x490cfd35,
   0x09897c09,
   0xd00807c8,
   0x07e1480b,
   0x490bd001,
   0x490be000,
   0x490b6201,
   0xbd106241,
   0x1a512220,
   0xba004088,
   0x00004770,
   0x21000160,
   0x40042000,
   0x21000028,
   0x400421c0,
   0x21000380,
   0x210047b7,
   0x2100478d,
   0x21004769,
   0x07810882,
   0x0ec90092,
   0x78c0ca0c,
   0x424940ca,
   0x408b3120,
   0x0211431a,
   0x06000a09,
   0x47704308,
};
#define _NWORD_PATCHIMAGE_MULTI_PROTOCOL 516

CPE_PATCH_TYPE patchCpeHd[] = {
   0x00000000,
};
#define _NWORD_PATCHCPEHD_MULTI_PROTOCOL 1

#define _NWORD_PATCHSYS_MULTI_PROTOCOL 0

#define _IRQ_PATCH_0 0x21004269


#ifndef _MULTI_PROTOCOL_SYSRAM_START
#define _MULTI_PROTOCOL_SYSRAM_START 0x20000000
#endif

#ifndef _MULTI_PROTOCOL_CPERAM_START
#define _MULTI_PROTOCOL_CPERAM_START 0x21000000
#endif

#define _MULTI_PROTOCOL_SYS_PATCH_FIXED_ADDR 0x20000000

#define _MULTI_PROTOCOL_PATCH_VEC_ADDR_OFFSET 0x03D0
#define _MULTI_PROTOCOL_PATCH_TAB_OFFSET 0x03D4
#define _MULTI_PROTOCOL_IRQPATCH_OFFSET 0x0480
#define _MULTI_PROTOCOL_PATCH_VEC_OFFSET 0x404C

#define _MULTI_PROTOCOL_PATCH_CPEHD_OFFSET 0x04E0

#ifndef _MULTI_PROTOCOL_NO_PROG_STATE_VAR
static uint8_t bMultiProtocolPatchEntered = 0;
#endif

PATCH_FUN_SPEC void enterMultiProtocolCpePatch(void)
{
#if (_NWORD_PATCHIMAGE_MULTI_PROTOCOL > 0)
   uint32_t *pPatchVec = (uint32_t *) (_MULTI_PROTOCOL_CPERAM_START + _MULTI_PROTOCOL_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageMultiProtocol, sizeof(patchImageMultiProtocol));
#endif
}

PATCH_FUN_SPEC void enterMultiProtocolCpeHdPatch(void)
{
#if (_NWORD_PATCHCPEHD_MULTI_PROTOCOL > 0)
   uint32_t *pPatchCpeHd = (uint32_t *) (_MULTI_PROTOCOL_CPERAM_START + _MULTI_PROTOCOL_PATCH_CPEHD_OFFSET);

   memcpy(pPatchCpeHd, patchCpeHd, sizeof(patchCpeHd));
#endif
}

PATCH_FUN_SPEC void enterMultiProtocolSysPatch(void)
{
}

PATCH_FUN_SPEC void configureMultiProtocolPatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) (_MULTI_PROTOCOL_CPERAM_START + _MULTI_PROTOCOL_PATCH_TAB_OFFSET);
   uint32_t *pIrqPatch = (uint32_t *) (_MULTI_PROTOCOL_CPERAM_START + _MULTI_PROTOCOL_IRQPATCH_OFFSET);


   pPatchTab[1] = 0;
   pPatchTab[21] = 1;
   pPatchTab[76] = 2;
   pPatchTab[62] = 3;
   pPatchTab[64] = 4;
   pPatchTab[91] = 5;
   pPatchTab[79] = 6;
   pPatchTab[140] = 7;
   pPatchTab[150] = 8;
   pPatchTab[107] = 9;
   pPatchTab[13] = 10;
   pPatchTab[31] = 11;
   pPatchTab[152] = 12;
   pPatchTab[151] = 13;
   pPatchTab[40] = 14;
   pPatchTab[73] = 15;
   pPatchTab[7] = 16;
   pPatchTab[164] = 17;
   pPatchTab[85] = 18;

   pIrqPatch[1] = _IRQ_PATCH_0;
}

PATCH_FUN_SPEC void applyMultiProtocolPatch(void)
{
#ifdef _MULTI_PROTOCOL_NO_PROG_STATE_VAR
   enterMultiProtocolSysPatch();
   enterMultiProtocolCpePatch();
#else
   if (!bMultiProtocolPatchEntered)
   {
      enterMultiProtocolSysPatch();
      enterMultiProtocolCpePatch();
      bMultiProtocolPatchEntered = 1;
   }
#endif
   enterMultiProtocolCpeHdPatch();
   configureMultiProtocolPatch();
}

void refreshMultiProtocolPatch(void)
{
   enterMultiProtocolCpeHdPatch();
   configureMultiProtocolPatch();
}

void cleanMultiProtocolPatch(void)
{
#ifndef _MULTI_PROTOCOL_NO_PROG_STATE_VAR
   bMultiProtocolPatchEntered = 0;
#endif
}

void rf_patch_cpe_multi_protocol(void)
{
   applyMultiProtocolPatch();
}

#undef _IRQ_PATCH_0

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif


