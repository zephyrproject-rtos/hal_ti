/******************************************************************************
*  Filename:       rf_patch_cpe_multi_protocol_hid.c
*
*  Description: RF core patch for multi-protocol support (all available API command sets) with HID components in CC13x2 and CC26x2
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

#include "rf_patch_cpe_multi_protocol_hid.h"

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


CPE_PATCH_TYPE patchImageMultiProtocolHid[] = {
   0x210044d9,
   0x2100409d,
   0x210040b9,
   0x21004123,
   0x210040e5,
   0x2100454d,
   0x21004589,
   0x21004155,
   0x21004161,
   0x2100416d,
   0x21004189,
   0x21004633,
   0x210041d1,
   0x210041e9,
   0x21004201,
   0x2100423d,
   0x21004667,
   0x210046d7,
   0x21005b27,
   0x21004b53,
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
   0xfa40f000,
   0x47004800,
   0x00007f57,
   0xfa40f000,
   0x47004800,
   0x0000881b,
   0x0a889905,
   0xd1052880,
   0x78884913,
   0x0f800780,
   0xfa4af000,
   0x47004800,
   0x00006ed9,
   0x480fb40f,
   0x290088c1,
   0x4610d002,
   0xfa3ef000,
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
   0xfcacf001,
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
   0x210044cd,
   0x21004459,
   0x210043fb,
   0x2100437b,
   0x210042fd,
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
   0xfdd2f7ff,
   0x07006ba0,
   0x2001d408,
   0x60606020,
   0x1c402000,
   0xdbfc280c,
   0x62202014,
   0xf7ffbd10,
   0xbd10fdc3,
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
   0x21004649,
   0x00000806,
   0x0000069f,
   0x21000108,
   0x21000154,
   0x00029263,
   0x21004681,
   0x0002b4b5,
   0xe000e180,
   0x21000380,
   0x000296f7,
   0x21004677,
   0x210046bf,
   0x00029569,
   0x210046b5,
   0x22ff0783,
   0x409a0edb,
   0x0e090789,
   0x28004099,
   0x0700da0b,
   0x38080f00,
   0x009b0883,
   0x181848ff,
   0x439369c3,
   0x61c3430b,
   0x08834770,
   0x009b48fc,
   0x68031818,
   0x430b4393,
   0x47706003,
   0x48f9b510,
   0x4cf94780,
   0x29006c61,
   0x7b21d019,
   0x07c90909,
   0x2200d114,
   0x31404621,
   0x73e2730a,
   0x64a26c62,
   0x764a7812,
   0x78526ca2,
   0x6ca2704a,
   0x760a78d2,
   0x89126ca2,
   0x6ca1834a,
   0x63616849,
   0x2081bd10,
   0xfa6ef001,
   0x02c0200b,
   0x20028120,
   0xbd1072a0,
   0x4ae5b570,
   0x46144601,
   0x34202000,
   0xd0012900,
   0xe0002106,
   0x7be37a21,
   0x07ed089d,
   0x7b15d004,
   0x07ed092d,
   0x1c49d000,
   0x07ed08dd,
   0x1c89d000,
   0x07ed091d,
   0x4dd9d004,
   0x1ded7c6d,
   0x186908ed,
   0x07ed095d,
   0x1c49d000,
   0x07ed099d,
   0x1c49d000,
   0xd00009db,
   0x6b131d09,
   0x2b002500,
   0x4618d00b,
   0x321c4bcf,
   0x21234798,
   0xd0024208,
   0x72e12101,
   0x72e5e002,
   0x61d5e000,
   0xd5030741,
   0x4ac92101,
   0x609105c9,
   0xb5f8bd70,
   0x48c74606,
   0x21004cc2,
   0x7c616001,
   0x1e4a4fc4,
   0x63fa3f40,
   0x07806840,
   0x6b78d554,
   0x69ea4dc1,
   0x6a694790,
   0x47887c60,
   0x46204605,
   0x2e003020,
   0x0569da09,
   0x72010e09,
   0x5d122241,
   0xd9034291,
   0x43c02001,
   0x7206bdf8,
   0x7ca17a02,
   0x00d04606,
   0x62381808,
   0x210148b2,
   0x2a066081,
   0x6b20d90b,
   0xf9f8f001,
   0xf7ff2000,
   0x2121ff87,
   0xd0084208,
   0x43c02002,
   0x2a06bdf8,
   0x69e1d203,
   0xf0016b20,
   0x69e0f955,
   0xd01b2800,
   0x08897bf1,
   0xd00807c9,
   0x09097b21,
   0xd00407c9,
   0x7be24601,
   0x61e01c40,
   0x7bf0700a,
   0x07c008c0,
   0x69e0d00a,
   0x1c4210e9,
   0x700161e2,
   0x69e0076a,
   0x1c410f52,
   0x700261e1,
   0xbdf84628,
   0x43c02000,
   0xb570bdf8,
   0x20004c90,
   0x43c07b21,
   0x4d940889,
   0xd10007c9,
   0xf7ff7868,
   0x2800ff8e,
   0x83a8db08,
   0x200f6821,
   0x60604788,
   0x2000498e,
   0xe01f4788,
   0xd0081c81,
   0xd01d1cc0,
   0x2010498b,
   0x498b6008,
   0x20016008,
   0x6ba0bd70,
   0xd0022800,
   0x1c497941,
   0x20017141,
   0x0680497f,
   0xf0016088,
   0x4884f8f2,
   0x21004780,
   0x5501202c,
   0x200c6821,
   0x60604788,
   0xbd702000,
   0x02c0200b,
   0x20028120,
   0x200372a0,
   0x496ebd70,
   0x47706108,
   0x6908496c,
   0x2310690a,
   0x610a431a,
   0xb5704770,
   0xfff6f7ff,
   0x4a7221ff,
   0x60113101,
   0xe0004973,
   0x6acabf20,
   0xd0fb07d2,
   0x61104a62,
   0x69424870,
   0x431a230f,
   0x69826142,
   0x00d208d2,
   0x61821d12,
   0x25024863,
   0x60453880,
   0x60822201,
   0x60042400,
   0x608a6084,
   0x608c600c,
   0x60412108,
   0x49616041,
   0x31804864,
   0x49646008,
   0x47884620,
   0x47804863,
   0x70054863,
   0x63054855,
   0x3040485c,
   0x48556004,
   0x70444960,
   0x47882078,
   0x3080484e,
   0x28007b40,
   0xf001d001,
   0xbd70f93d,
   0x4c4ab570,
   0x7b203480,
   0xd0012800,
   0x47884958,
   0x30404846,
   0x0a8a8801,
   0xd10207d2,
   0x28007ac0,
   0x0908d005,
   0xd00207c0,
   0x387a484e,
   0x48514780,
   0x77012100,
   0x38404840,
   0x48436201,
   0x60022210,
   0x60022204,
   0x60050195,
   0x60020252,
   0x60324e3f,
   0x62c14840,
   0x62012114,
   0x4c367ae0,
   0xd00307c0,
   0x21016960,
   0x61604308,
   0x2001493d,
   0x493e4788,
   0x70082006,
   0x48386320,
   0x209d6841,
   0xf902f001,
   0xbd706035,
   0xf7ffb500,
   0x21ffff6f,
   0x31014a2e,
   0x49306011,
   0xbf20e000,
   0x07d26aca,
   0x491fd0fb,
   0x482d6108,
   0x220f6941,
   0x61414311,
   0x08c96981,
   0x1d0900c9,
   0x49256181,
   0x31804828,
   0x491e6008,
   0x39402000,
   0xbd0062c8,
   0xb282491b,
   0x628a3180,
   0x62ca0c02,
   0x79ca4915,
   0xd10907d3,
   0x88890892,
   0x07d04002,
   0x43c8d001,
   0x4813b281,
   0x62413840,
   0xb5f84770,
   0x49204c0c,
   0x79884625,
   0x28003520,
   0x4b1dd070,
   0x20006809,
   0x791f795a,
   0xd0562900,
   0x095b7beb,
   0xd03307db,
   0xe02f7b6b,
   0xe000ed00,
   0xe000e400,
   0x0002db23,
   0x21000160,
   0x21000028,
   0x0000369b,
   0x40041100,
   0x40045080,
   0x21000380,
   0x210001a0,
   0x00000fc1,
   0xe000e280,
   0xe000e100,
   0x00005b29,
   0x40046000,
   0x40043000,
   0x00000d04,
   0x000085bd,
   0x000090fd,
   0x21000018,
   0x0000423d,
   0x0000586f,
   0x210002a0,
   0x21005d40,
   0x1c49700b,
   0x099b7beb,
   0xd00c07db,
   0x5d1b234c,
   0x43337bae,
   0x0edb06db,
   0x433301d6,
   0x0e7607fe,
   0x700b4333,
   0x7beb1c49,
   0xd00a09db,
   0x700b6be3,
   0x0a1b6be3,
   0x6be3704b,
   0x708b0c1b,
   0x0e1b6be3,
   0x6b2170cb,
   0x29002600,
   0x2a00d01f,
   0x7bead00d,
   0x07d20852,
   0x7aead009,
   0xd0022a00,
   0x72e92100,
   0x4608e00f,
   0xe00b49f9,
   0x2f00e04a,
   0x7bead002,
   0xd1f607d2,
   0x2a007aea,
   0x4608d103,
   0x39b649f3,
   0x07404788,
   0x2601d501,
   0x7ae805f6,
   0xd0022800,
   0x05802001,
   0x48eee00e,
   0x29007941,
   0x2001d002,
   0xe0070440,
   0x28007900,
   0x2001d002,
   0xe0010480,
   0x04002001,
   0x6ba04306,
   0xd01c2800,
   0xd5030271,
   0x1c497901,
   0xe0107101,
   0xd50303b1,
   0x1c497881,
   0xe00a7081,
   0xd5030371,
   0x1c4978c1,
   0xe00470c1,
   0xd50203f1,
   0x1c497841,
   0x6ba17041,
   0x71c87b68,
   0x6be16ba0,
   0x48d76081,
   0x49d56086,
   0x71882000,
   0x32084ad3,
   0x28007990,
   0x6810d071,
   0x91007951,
   0xd0202800,
   0x09497be9,
   0xd00207c9,
   0x70017b69,
   0x7be91c40,
   0x07c90989,
   0x9900d00a,
   0x01cb7a2e,
   0x2e002101,
   0x2100d000,
   0x430b0189,
   0x1c407003,
   0x09c97be9,
   0x6be1d007,
   0x0a0b7001,
   0x0c0b7043,
   0x0e097083,
   0x49be70c1,
   0x31082600,
   0x6b21790f,
   0x29004630,
   0x9a00d01e,
   0xd0072a00,
   0x08527bea,
   0xd10907d2,
   0x4608e002,
   0xe00e49b4,
   0x2a007a2a,
   0x7bead106,
   0xd00307d2,
   0xd0f42f00,
   0xe0052700,
   0xd1032f00,
   0x49ad4608,
   0x478839b6,
   0xd5010740,
   0x05f62601,
   0xd0022f00,
   0x05802001,
   0x9800e00c,
   0xd0022800,
   0x04402001,
   0x48a5e006,
   0x79c03008,
   0xd00b2800,
   0x04002001,
   0x6ba04306,
   0xd01e2800,
   0xd5060271,
   0x1c497901,
   0xe0147101,
   0x04802001,
   0x03b1e7f2,
   0x7881d504,
   0x70811c49,
   0xe015e00b,
   0xd5030371,
   0x1c4978c1,
   0xe00470c1,
   0xd50203f1,
   0x1c497841,
   0x7b697041,
   0x6be171c1,
   0x48916081,
   0x20006086,
   0x7328498e,
   0x71883108,
   0x498e2001,
   0x60080440,
   0x6008498d,
   0x488dbdf8,
   0x07c96ac1,
   0x6901d104,
   0xd1fc07c9,
   0x62012101,
   0xb5704770,
   0x20004d88,
   0x49856228,
   0x60082014,
   0x20014c85,
   0x60603c40,
   0x60602008,
   0x20006060,
   0x1c40bf00,
   0xdbfb280a,
   0x47804880,
   0x49814880,
   0xb2826840,
   0x0c00614a,
   0x26026188,
   0x497e6066,
   0x02007888,
   0x61a81cc0,
   0x4a7c4b76,
   0x62da3340,
   0x06847808,
   0x631ad503,
   0x401022df,
   0x704e7008,
   0xb5febd70,
   0x4c764f6b,
   0x78781f3f,
   0x35404625,
   0xd1122800,
   0x08407b20,
   0xd00e07c0,
   0x7ce07829,
   0x184100c9,
   0x8dc2486f,
   0x43518cc0,
   0x09096e22,
   0x18081810,
   0x70792101,
   0x486363e0,
   0x07c06ac0,
   0x4961d07f,
   0x39402003,
   0xf7ff6048,
   0xf7ffffaa,
   0x2600ff9e,
   0x707e4958,
   0x60882010,
   0x28006ba0,
   0x7801d002,
   0x70011c49,
   0x21e77e28,
   0x7b614008,
   0x07891c49,
   0x43080ec9,
   0x69a07628,
   0xd0022800,
   0x6b604959,
   0x6ca14788,
   0x70c87e28,
   0x8b686ca1,
   0x484a8108,
   0x68003080,
   0xd5010380,
   0xfe1df7ff,
   0x47804852,
   0x7ae84d52,
   0x07c97ae9,
   0x4851d004,
   0x72a68120,
   0xe0062080,
   0xd5070740,
   0x1f00484d,
   0x72a68120,
   0xf000208e,
   0xe032febf,
   0x08407b20,
   0xd02907c0,
   0x6d20707e,
   0xfdeaf7ff,
   0xfdc6f7ff,
   0x20004945,
   0xf7ff4788,
   0xf000fd7f,
   0x7ae8fe0e,
   0x400821fb,
   0x230072e8,
   0x483a2204,
   0x92009301,
   0x8a4030a0,
   0x4d3d6be1,
   0x2182180a,
   0x47a84618,
   0xd0022800,
   0xf0002097,
   0x6821fe97,
   0x4788200c,
   0x20016060,
   0xe00cbdfe,
   0x02802015,
   0x20018120,
   0x707e72a0,
   0xfd13f7ff,
   0xf0002096,
   0x2002fe85,
   0x4825e7f0,
   0x08497801,
   0x70010049,
   0x2004491b,
   0x60083980,
   0x4608e7e5,
   0xb5104922,
   0x7aca3180,
   0x07d14b15,
   0x6959d003,
   0x00490849,
   0x08d16159,
   0xd00907c9,
   0x69514a22,
   0x432124f0,
   0x69946151,
   0x438c2170,
   0x61943440,
   0x491e4a0c,
   0x490e6011,
   0x39402202,
   0x4c0c604a,
   0x63e12100,
   0x700a491a,
   0x491a631a,
   0x490c4788,
   0x70482003,
   0x0000bd10,
   0x00003b11,
   0x21005d40,
   0x40041100,
   0xe000e180,
   0xe000e280,
   0x40046000,
   0x40045040,
   0x000057bf,
   0x210002c0,
   0x40045180,
   0x21000380,
   0x0000ff80,
   0x21000160,
   0x21000028,
   0x000035f1,
   0x00000d1d,
   0x21000128,
   0x00005405,
   0x00008303,
   0x00000e43,
   0x40043000,
   0x00000914,
   0x21000018,
   0x0000729f,
   0xb085b5f0,
   0x49ff2000,
   0x4cff7048,
   0x36204626,
   0x28007a30,
   0x48fdd003,
   0x28004780,
   0x2700d171,
   0x97004625,
   0x97033540,
   0x07007e68,
   0xd00b0f80,
   0xd0082801,
   0xd0022802,
   0xd1052803,
   0x8ba8e04f,
   0x17c007c0,
   0x90001c40,
   0x200049f1,
   0x48f16008,
   0x90017c40,
   0x28109002,
   0x4aedd90e,
   0x3a40200f,
   0x460863d0,
   0x07896841,
   0x6b57d5fc,
   0x62202010,
   0x38109802,
   0x9002b2c0,
   0x28009800,
   0x48e6d014,
   0x7a314780,
   0x00c97ce0,
   0x48e21841,
   0x8d008dc2,
   0x6be24351,
   0x18100909,
   0x4ae01808,
   0x66202101,
   0x49df4790,
   0x47882001,
   0x28009802,
   0x4ad8d034,
   0x3a401e40,
   0x48d663d0,
   0x07896841,
   0x6b50d5fc,
   0x40886a21,
   0x4fd74338,
   0x6a3a9901,
   0x6a794790,
   0x47889801,
   0x7a704607,
   0xd0042800,
   0x8ba8e008,
   0x0fc007c0,
   0x9801e7af,
   0x1a082120,
   0xba3f4087,
   0x09007bf0,
   0xd00f07c0,
   0x280069e0,
   0x2000d00c,
   0xe126e007,
   0x69e1463a,
   0x1c4b40c2,
   0x700a61e3,
   0x99013008,
   0xdbf54288,
   0x28009800,
   0x2100d00f,
   0xf7ff2001,
   0x49c0ff10,
   0x62082013,
   0x49b848bd,
   0x02007880,
   0x39401c80,
   0x48bc6188,
   0x48bc4780,
   0x90014780,
   0x06807e68,
   0x90020fc0,
   0x28009801,
   0x7e28d165,
   0xd01507c1,
   0x07418baa,
   0x0f890752,
   0x42910f92,
   0x8b6ad10e,
   0x4291b2b9,
   0x2001d10a,
   0x7af09003,
   0xd01a2800,
   0x07c07bf0,
   0x2000d04f,
   0xe01472f0,
   0x29009903,
   0x7af0d003,
   0xd00e2800,
   0x7af1e045,
   0xd1422900,
   0x43082101,
   0x400821f9,
   0x07498ba9,
   0x00490f89,
   0x76284308,
   0x9800836f,
   0xd0342800,
   0x21074896,
   0x63813840,
   0x28007bb0,
   0x6d60d002,
   0xfc6cf7ff,
   0x20014999,
   0x478839d2,
   0x28007bb0,
   0x6d61d001,
   0x6d21e000,
   0x4a94488d,
   0x3a387880,
   0x7b204790,
   0x07c00900,
   0x4f8dd00a,
   0x69fa7be0,
   0x47902108,
   0x20086a79,
   0x49844788,
   0x63083940,
   0x4f8b9803,
   0xd0372800,
   0x09407e28,
   0xd00207c0,
   0x47b86b60,
   0x2000e000,
   0x487961a0,
   0x1d0069e1,
   0x99036001,
   0x99017101,
   0x21017141,
   0x21027181,
   0xf7ff2011,
   0x2001fa4f,
   0x0440497e,
   0x497e6008,
   0x497c6008,
   0x60083980,
   0x2700486d,
   0x73377007,
   0x28009800,
   0x73a7d037,
   0x06c87e29,
   0x73600f80,
   0x280069a0,
   0x2220d019,
   0x76294311,
   0x702988c1,
   0x47884972,
   0xe01561e0,
   0x28009802,
   0x7e28d1cb,
   0x07c00940,
   0x496ad0c4,
   0x31866b60,
   0x28004788,
   0x208bd1be,
   0xfccef000,
   0x20dfe7ba,
   0x76294001,
   0x61e7702f,
   0x26ef7b20,
   0x0fcd06c1,
   0x73204030,
   0x98024963,
   0x7b204788,
   0x40300129,
   0x73204308,
   0x68212011,
   0xf7ffe040,
   0x6ca1fbfe,
   0x70c87e28,
   0x8b686ca1,
   0x7af08108,
   0xd0062800,
   0x38984852,
   0x20028120,
   0x207e72a0,
   0x9801e039,
   0x7b202800,
   0x0880d007,
   0xd10707c0,
   0x81204852,
   0x209272a7,
   0x0840e02d,
   0xd02407c0,
   0xfbf5f000,
   0x38724841,
   0x484d4780,
   0x22fb7ac1,
   0x72c14011,
   0x68003820,
   0x7ec12204,
   0x230069c0,
   0x46029200,
   0x46189301,
   0xfc98f000,
   0xd0022800,
   0xf000208f,
   0x2083fc7b,
   0xfc78f000,
   0x200c6821,
   0x60604788,
   0xb0052000,
   0x2015bdf0,
   0x81200280,
   0x72a02001,
   0xf0002091,
   0x2003fc69,
   0xb5f8e7f3,
   0x4c264828,
   0x6ac03840,
   0xd04407c0,
   0xfd01f7ff,
   0x20104e34,
   0x6ba060b0,
   0xd0022800,
   0x1c497801,
   0x7b207001,
   0x08404f1c,
   0x250007c0,
   0xd01c2800,
   0x28007ba0,
   0x7d60d003,
   0x07c00880,
   0xf7ffd015,
   0x707dfcf2,
   0x20056821,
   0x60604788,
   0x5d002040,
   0x00c07ce1,
   0x48141809,
   0x8cc08dc2,
   0x6e224351,
   0x18100909,
   0x63e01808,
   0x4917e056,
   0x31866b60,
   0x28004788,
   0x2090d102,
   0xfc28f000,
   0x02802001,
   0x7b6060b0,
   0x1c404916,
   0x0f800780,
   0x39207360,
   0x75486809,
   0xe041e028,
   0x21005d3c,
   0x21000160,
   0x0002de75,
   0x40045080,
   0x21000028,
   0x00005b9b,
   0x000075f7,
   0x00008303,
   0x21000380,
   0x40046000,
   0x00005899,
   0x000064c9,
   0x0000359d,
   0xe000e280,
   0xe000e100,
   0x00003b77,
   0x0002d137,
   0x00005403,
   0x21000128,
   0x40041100,
   0xfa7bf7ff,
   0x707d48ff,
   0x07c07ac0,
   0x48fed007,
   0x72a58120,
   0xf000209e,
   0x2002fbe5,
   0x7c20bdf8,
   0x74201c40,
   0x478048f9,
   0x20016821,
   0x60604788,
   0xbdf82000,
   0x780148f6,
   0x00490849,
   0x49f57001,
   0x60082004,
   0xbdf82001,
   0x49f4b57c,
   0x20004cf2,
   0xf7ff4788,
   0xf000fad9,
   0xf7fffb26,
   0x48f0fa93,
   0x78804af0,
   0x47906d21,
   0x7ac148e6,
   0x401122fb,
   0x230072c1,
   0x48ea2204,
   0x92009301,
   0x8a4030a0,
   0x4de96be1,
   0x2182180a,
   0x47a84618,
   0x478048e7,
   0x20066821,
   0x60604788,
   0xbd7c2000,
   0x2098b570,
   0xfba0f000,
   0xfa22f7ff,
   0x20004605,
   0xe0004ce0,
   0x6821bf20,
   0xd0fb2900,
   0x4ade6821,
   0x42910c09,
   0x2101d104,
   0x4adc6061,
   0xe0046011,
   0x385e48d6,
   0x20004780,
   0x49d943c0,
   0x2100610d,
   0xbd706021,
   0x48c8b5f8,
   0x38204ccc,
   0x4ad56800,
   0x70512100,
   0x636069c0,
   0xf000208a,
   0x4ed2fb75,
   0x47b06b60,
   0xd0190005,
   0xf0002093,
   0x4ecffb6d,
   0x68706e21,
   0xfb86f000,
   0xd0012800,
   0x66206870,
   0x462849cb,
   0x61a04788,
   0x344088e8,
   0x48c97020,
   0x49c94780,
   0x47884604,
   0xbdf84620,
   0xf000207d,
   0xf7fffb53,
   0x2702ffad,
   0xd0052800,
   0xf0002082,
   0x48aefb4b,
   0xe0081c40,
   0x47b06b60,
   0xd1d60005,
   0xf000209c,
   0x200bfb41,
   0x812002c0,
   0x200372a7,
   0xb510bdf8,
   0x7b204ca9,
   0x07c00880,
   0x2000d001,
   0xf7ff43c0,
   0x2800f90c,
   0x6821db06,
   0x47882009,
   0x20006060,
   0xe01849b1,
   0xd0081c81,
   0xd01c1cc0,
   0x201049a6,
   0x499c6008,
   0x20016008,
   0x4898e4ce,
   0x28004780,
   0x6821d00c,
   0x47882001,
   0x209f6060,
   0xfb12f000,
   0x6b6049a0,
   0x47883154,
   0xe4bd2000,
   0x1ec0488e,
   0x20008120,
   0x200be003,
   0x812002c0,
   0x72a02002,
   0xe4b12003,
   0x4889b570,
   0x478030bc,
   0x46054c8a,
   0x20016821,
   0x68614788,
   0xd1064288,
   0xf000209a,
   0x4990faf1,
   0x31546b60,
   0x46284788,
   0xb5f8bd70,
   0x4c814d8b,
   0x28007828,
   0x2001d10e,
   0xf87af7ff,
   0x42082121,
   0x200bd006,
   0x812002c0,
   0x72a02002,
   0xbdf82003,
   0x70282001,
   0x35204625,
   0x7aee4887,
   0x90004780,
   0x682172ee,
   0x4788200e,
   0x42886861,
   0x4622d13f,
   0x32407ba8,
   0x78976c61,
   0x2800468c,
   0x2302d001,
   0x2301e000,
   0xe0042000,
   0x421e780e,
   0x310cd105,
   0x42b81c40,
   0x2000dbf8,
   0x280043c0,
   0x6ba0da18,
   0xd0022800,
   0x1c497941,
   0x20017141,
   0x06804967,
   0xf0006088,
   0x4871fa06,
   0x20004780,
   0x20867328,
   0xfa9ef000,
   0x200c6821,
   0x60604788,
   0xbdf82000,
   0x230c7310,
   0x44604358,
   0x780164a0,
   0x78417651,
   0x78c17051,
   0x89017611,
   0x68408351,
   0x98006360,
   0xb5f8bdf8,
   0x4c4f4d59,
   0x28007828,
   0x2001d10e,
   0xf816f7ff,
   0x42082121,
   0x200bd006,
   0x812002c0,
   0x72a02002,
   0xbdf82003,
   0x70282001,
   0x37204627,
   0x7afe4841,
   0x47803054,
   0x483d4605,
   0x7ac072fe,
   0xd5020740,
   0xf000207f,
   0x2d00fa63,
   0x6821d10c,
   0x47882001,
   0x42886861,
   0x208cd106,
   0xfa58f000,
   0x6b604943,
   0x47883154,
   0xbdf84628,
   0x4830b5f0,
   0x38204c34,
   0xb0856800,
   0x20009001,
   0x69e69002,
   0x90034943,
   0x48316008,
   0x95007c45,
   0xd90d2d10,
   0x200f4a3f,
   0x63d03a40,
   0x68414608,
   0xd5fc0789,
   0x90026b50,
   0x3d102010,
   0x9003b2ed,
   0x30724837,
   0x46274780,
   0x7a393720,
   0x00c97ce0,
   0x48231841,
   0x8d008dc2,
   0x6be24351,
   0x18100909,
   0x4a311808,
   0x66202101,
   0x28004790,
   0x2084d006,
   0xfa18f000,
   0x482d4921,
   0xe7fe6048,
   0x20014917,
   0x2d004788,
   0x4a27d061,
   0x3a401e6d,
   0x482563d5,
   0x07896841,
   0x6b50d5fc,
   0x4d0d9903,
   0x99024088,
   0x43086a2a,
   0x47909900,
   0x98006a69,
   0x7a794788,
   0xd1042900,
   0x22209900,
   0x40881a51,
   0x7bf9ba00,
   0xe0350909,
   0x21000128,
   0x00005405,
   0x0002d53b,
   0x21000380,
   0xe000e100,
   0x21000160,
   0x00008303,
   0x21000028,
   0x00006491,
   0x00000e43,
   0x000078d9,
   0x40041100,
   0x00000412,
   0xe000e280,
   0xe000ed00,
   0x21005d3c,
   0x0000359d,
   0x40043000,
   0x00003b77,
   0x0002d1cb,
   0x00004be3,
   0x00000fc1,
   0x0002dc99,
   0x00005b29,
   0x40045080,
   0x000075f7,
   0x80000000,
   0xd00a07c9,
   0xd0082e00,
   0xe0032100,
   0x1c767030,
   0x31080a00,
   0x42919a00,
   0x2100dbf8,
   0xf7ff2001,
   0x49abfb30,
   0x62082013,
   0x49ab48aa,
   0x02007880,
   0x61881c80,
   0x478048a9,
   0x478048a9,
   0x460549a9,
   0x7af8600e,
   0x714d7108,
   0x71ca7a3a,
   0x718b2301,
   0x390c2600,
   0x6b21700e,
   0xd00d2900,
   0xd0032d00,
   0x08497bf9,
   0xd10407c9,
   0xd1052a00,
   0x07c97bf9,
   0x2800d002,
   0x2000d000,
   0x28009901,
   0x636169c9,
   0x2095d007,
   0xf976f000,
   0xf8bdf7ff,
   0x38984893,
   0x4895e03e,
   0x48954780,
   0x00287ac7,
   0xd03a4d94,
   0xf0002094,
   0x4993f967,
   0x47886b60,
   0xd00607f8,
   0xf8a9f7ff,
   0x81204890,
   0x208572a6,
   0x488fe049,
   0x28004780,
   0x4887d01d,
   0x7046380c,
   0xf0002008,
   0x9801f975,
   0x69002200,
   0x46206520,
   0x30504611,
   0xf972f000,
   0xf0002088,
   0x2102f945,
   0xf7fe2011,
   0x4883fe91,
   0x48836005,
   0x48816005,
   0x60053880,
   0x208de064,
   0xf936f000,
   0xf87df7ff,
   0x1e80487a,
   0x72a68120,
   0x4977e01f,
   0x31326b60,
   0x28004788,
   0x2089d102,
   0xf926f000,
   0x49772001,
   0x60880280,
   0x496e7b60,
   0x07801c40,
   0x73600f80,
   0x68093920,
   0x07f87548,
   0xf7ffd009,
   0x486bf85e,
   0x72a68120,
   0xf0002099,
   0x2003f90f,
   0x9801e499,
   0x69c04965,
   0x63603954,
   0x00064788,
   0x495bd02d,
   0x39402002,
   0x49666048,
   0x47884630,
   0x88f161a0,
   0x55112240,
   0x485561e0,
   0x63812107,
   0x20014955,
   0x478839d2,
   0x4a53485f,
   0x3a387880,
   0x47906d21,
   0x495d7b20,
   0x478809c0,
   0x20026821,
   0x60604788,
   0x20112102,
   0xfe30f7fe,
   0x60054852,
   0x60054852,
   0x38804850,
   0x20006005,
   0x209be463,
   0xf8d4f000,
   0xf81bf7ff,
   0x20016821,
   0x60604788,
   0xb500e7f3,
   0x4603494e,
   0xf00072c8,
   0x2314f8f7,
   0x19232315,
   0x13110d17,
   0x0f210b23,
   0x231b1f23,
   0x231d2323,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0xbd004847,
   0x00804947,
   0x6b001840,
   0x492abd00,
   0x2000b510,
   0x478839d2,
   0x20004925,
   0x60083140,
   0x47804841,
   0xd1021c40,
   0xf0002087,
   0xe56ff88f,
   0x4b2fb530,
   0xd0322800,
   0x28006800,
   0x7944d02f,
   0x28027900,
   0x202fd12b,
   0x08855cc0,
   0xd00407ed,
   0x091b7b1b,
   0xd00007db,
   0x08c31c52,
   0xd00007db,
   0x09031c92,
   0xd00407db,
   0x7c5b4b1f,
   0x08db1ddb,
   0x0943189a,
   0xd00007db,
   0x09831c52,
   0xd00007db,
   0x09c01c52,
   0x1d12d000,
   0x0f800720,
   0x2801d007,
   0x2802d006,
   0x1e89d103,
   0x1210700a,
   0xbd307048,
   0x700a1e49,
   0x0000bd30,
   0x40046000,
   0x21000380,
   0x40045040,
   0x00005899,
   0x000064c9,
   0x21005d48,
   0x00000d1d,
   0x21000128,
   0x00020000,
   0x000035f1,
   0x00005405,
   0x0002d53b,
   0xe000e280,
   0xe000e100,
   0x40041100,
   0x00003b77,
   0x21000028,
   0x0002d137,
   0x21000160,
   0x2100581d,
   0x210057b3,
   0x210056eb,
   0x210056c1,
   0x2100564b,
   0x210055bd,
   0x21005525,
   0x210053f3,
   0x21005089,
   0x21004e7b,
   0x21004943,
   0x2100479d,
   0x00032dc0,
   0x000078d9,
   0x07810882,
   0x0ec90092,
   0x78c0ca0c,
   0x424940ca,
   0x408b3120,
   0x0211431a,
   0x06000a09,
   0x47704308,
   0x4801b403,
   0xbd019001,
   0x00003cc3,
   0x4801b403,
   0xbd019001,
   0x00003b11,
   0x4801b403,
   0xbd019001,
   0x00005bbb,
   0x4801b403,
   0xbd019001,
   0x00003c8f,
   0x4801b403,
   0xbd019001,
   0x00000e43,
   0x4801b403,
   0xbd019001,
   0x000075d1,
   0x4801b403,
   0xbd019001,
   0x0000424f,
   0x4801b403,
   0xbd019001,
   0x00005ee7,
   0x4674b430,
   0x78251e64,
   0x42ab1c64,
   0x461dd200,
   0x005b5d63,
   0xbc3018e3,
   0x00004718,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
};
#define _NWORD_PATCHIMAGE_MULTI_PROTOCOL_HID 1857

CPE_PATCH_TYPE patchCpeHd[] = {
   0x00000000,
};
#define _NWORD_PATCHCPEHD_MULTI_PROTOCOL_HID 1

#define _NWORD_PATCHSYS_MULTI_PROTOCOL_HID 0

#define _IRQ_PATCH_0 0x21004261


#ifndef _MULTI_PROTOCOL_HID_SYSRAM_START
#define _MULTI_PROTOCOL_HID_SYSRAM_START 0x20000000
#endif

#ifndef _MULTI_PROTOCOL_HID_CPERAM_START
#define _MULTI_PROTOCOL_HID_CPERAM_START 0x21000000
#endif

#define _MULTI_PROTOCOL_HID_SYS_PATCH_FIXED_ADDR 0x20000000

#define _MULTI_PROTOCOL_HID_PATCH_VEC_ADDR_OFFSET 0x03D0
#define _MULTI_PROTOCOL_HID_PATCH_TAB_OFFSET 0x03D4
#define _MULTI_PROTOCOL_HID_IRQPATCH_OFFSET 0x0480
#define _MULTI_PROTOCOL_HID_PATCH_VEC_OFFSET 0x404C

#define _MULTI_PROTOCOL_HID_PATCH_CPEHD_OFFSET 0x04E0

#ifndef _MULTI_PROTOCOL_HID_NO_PROG_STATE_VAR
static uint8_t bMultiProtocolHidPatchEntered = 0;
#endif

PATCH_FUN_SPEC void enterMultiProtocolHidCpePatch(void)
{
#if (_NWORD_PATCHIMAGE_MULTI_PROTOCOL_HID > 0)
   uint32_t *pPatchVec = (uint32_t *) (_MULTI_PROTOCOL_HID_CPERAM_START + _MULTI_PROTOCOL_HID_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageMultiProtocolHid, sizeof(patchImageMultiProtocolHid));
#endif
}

PATCH_FUN_SPEC void enterMultiProtocolHidCpeHdPatch(void)
{
#if (_NWORD_PATCHCPEHD_MULTI_PROTOCOL_HID > 0)
   uint32_t *pPatchCpeHd = (uint32_t *) (_MULTI_PROTOCOL_HID_CPERAM_START + _MULTI_PROTOCOL_HID_PATCH_CPEHD_OFFSET);

   memcpy(pPatchCpeHd, patchCpeHd, sizeof(patchCpeHd));
#endif
}

PATCH_FUN_SPEC void enterMultiProtocolHidSysPatch(void)
{
}

PATCH_FUN_SPEC void configureMultiProtocolHidPatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) (_MULTI_PROTOCOL_HID_CPERAM_START + _MULTI_PROTOCOL_HID_PATCH_TAB_OFFSET);
   uint32_t *pIrqPatch = (uint32_t *) (_MULTI_PROTOCOL_HID_CPERAM_START + _MULTI_PROTOCOL_HID_IRQPATCH_OFFSET);


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
   pPatchTab[4] = 18;
   pPatchTab[139] = 19;

   pIrqPatch[1] = _IRQ_PATCH_0;
}

PATCH_FUN_SPEC void applyMultiProtocolHidPatch(void)
{
#ifdef _MULTI_PROTOCOL_HID_NO_PROG_STATE_VAR
   enterMultiProtocolHidSysPatch();
   enterMultiProtocolHidCpePatch();
#else
   if (!bMultiProtocolHidPatchEntered)
   {
      enterMultiProtocolHidSysPatch();
      enterMultiProtocolHidCpePatch();
      bMultiProtocolHidPatchEntered = 1;
   }
#endif
   enterMultiProtocolHidCpeHdPatch();
   configureMultiProtocolHidPatch();
}

void refreshMultiProtocolHidPatch(void)
{
   enterMultiProtocolHidCpeHdPatch();
   configureMultiProtocolHidPatch();
}

void cleanMultiProtocolHidPatch(void)
{
#ifndef _MULTI_PROTOCOL_HID_NO_PROG_STATE_VAR
   bMultiProtocolHidPatchEntered = 0;
#endif
}

void rf_patch_cpe_multi_protocol_hid(void)
{
   applyMultiProtocolHidPatch();
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


