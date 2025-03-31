/******************************************************************************
*  Filename:       rf_patch_mce_iqdump.h
*
*  Description: RF core patch for IQ-dump support in CC13x2 PG2.1 and CC26x2 PG2.1
*
*  Copyright (c) 2015-2020, Texas Instruments Incorporated
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

#include <stdint.h>
#include "rf_patch_mce_iqdump.h"
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)

#ifndef MCE_PATCH_TYPE
#define MCE_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC
#endif

#ifndef RFC_MCERAM_BASE
#define RFC_MCERAM_BASE 0x21008000
#endif

#ifndef MCE_PATCH_MODE
#define MCE_PATCH_MODE 0
#endif

MCE_PATCH_TYPE patchIqdumpMce[360] = { 
   0x2fcf6030,
   0x00013f9d,
   0xff00003f,
   0x07ff0fff,
   0x0300f800,
   0x00068080,
   0x00170003,
   0x00003d1f,
   0x08000000,
   0x0000000f,
   0x00000387,
   0x00434074,
   0x00828000,
   0x06f00080,
   0x091e0000,
   0x00540510,
   0x00000007,
   0x00505014,
   0xc02f0000,
   0x017f0c30,
   0x00000000,
   0x00000000,
   0x00000000,
   0x0000aa00,
   0x66c47223,
   0xa4e5a35d,
   0x73057303,
   0x73047203,
   0x72047306,
   0x72917391,
   0xffc0b008,
   0xa0089010,
   0x720e720d,
   0x7210720f,
   0x7100b0d0,
   0xa0d0b110,
   0x8162721b,
   0x39521020,
   0x0412c181,
   0x00200670,
   0x11011630,
   0x6c011401,
   0x60836082,
   0x613a60ff,
   0x60826082,
   0x60826082,
   0x60836082,
   0x61de60ff,
   0x60826082,
   0x60826082,
   0x60836082,
   0x614a60ff,
   0x60826082,
   0x60826082,
   0x60836082,
   0x61fa60ff,
   0x60826082,
   0x60826082,
   0x60836082,
   0x618260ff,
   0x72231210,
   0x73127311,
   0x81b17313,
   0x91b00010,
   0x6044b070,
   0xc0306078,
   0xc0c166ca,
   0xc4e0c2b2,
   0x6f131820,
   0x16116e23,
   0x68891612,
   0x99c07830,
   0x948078a0,
   0xc4f29490,
   0x1820c750,
   0x1203409b,
   0x16126e23,
   0x78b06898,
   0x72639990,
   0x6078b63c,
   0x96408190,
   0x39808170,
   0x10012a70,
   0x84a21611,
   0xc0f384b4,
   0xc200c0f5,
   0x40c41c01,
   0x1c10c100,
   0x4cbc40ba,
   0x18031013,
   0x1a131830,
   0x39121a10,
   0x60c468b7,
   0x60c413f3,
   0x101513f3,
   0x1850c100,
   0x1a101a15,
   0x68c23914,
   0x7100b0e8,
   0xa0e8b128,
   0xb910b230,
   0x99308990,
   0xb0d1b111,
   0xb0027100,
   0xb111b012,
   0x7291a0d1,
   0xb003b630,
   0x722cb013,
   0x7100b0e0,
   0x8170b120,
   0x710092c0,
   0x8170b120,
   0x44dd22f0,
   0x1c0313f0,
   0x92c340e9,
   0x71009642,
   0x92c5b120,
   0x71009644,
   0xb0e0b120,
   0x7000a630,
   0xc030a0e1,
   0xc0409910,
   0xb1119930,
   0x7100b0d1,
   0xa0d1b111,
   0xa0037291,
   0xa230a002,
   0x73117000,
   0x81607312,
   0x451022a0,
   0x66cac040,
   0x91f0c100,
   0xb63364a0,
   0xb0d3b113,
   0xa0d37100,
   0x607864f0,
   0x66cac050,
   0x91f0c030,
   0xb0e8b634,
   0xb1287100,
   0xb230a0e8,
   0xb012b002,
   0xb013b003,
   0x92f01200,
   0xb0e1b121,
   0xb1217100,
   0x06208210,
   0x45221e20,
   0x66cac060,
   0xb1217100,
   0x92f181d1,
   0x00000000,
   0x82120000,
   0x1e220622,
   0xc070412a,
   0xa63466ca,
   0x607864f0,
   0xa0f0a0d2,
   0x7311a0f3,
   0x663e7312,
   0x66cac080,
   0xc035b0d2,
   0x9b757100,
   0xb074ba38,
   0x6144b112,
   0xa0f0a0d2,
   0x7311a0f3,
   0x663e7312,
   0xc000c18b,
   0x120c91e0,
   0x786a1218,
   0x788e787d,
   0xb07410a9,
   0xc020b0d2,
   0x7100b112,
   0xc090695c,
   0xc03566ca,
   0x7100b112,
   0x8bf09b75,
   0x8ca165d3,
   0x416f2201,
   0x1ca81080,
   0x1208456e,
   0x65ca1618,
   0x65d38c00,
   0x22018ca1,
   0x1090417a,
   0x1e091a19,
   0x10a9457a,
   0x818465ca,
   0x41621e04,
   0x1c4c14bc,
   0x61624ead,
   0xa0f0a0d2,
   0x7311a0f3,
   0x663e7312,
   0x120c721e,
   0xb0741205,
   0xc020b0d2,
   0x7100b112,
   0xc0a0698e,
   0x789d66ca,
   0xb11289ce,
   0x8c907100,
   0x419e2200,
   0x22108230,
   0xb231459e,
   0x8ab29a3d,
   0x3d823182,
   0x31808af0,
   0x18023d80,
   0x1e0e063e,
   0x1e2e41c0,
   0x1e3e41b2,
   0x105641b9,
   0x3d161426,
   0x61c11065,
   0x31261056,
   0x14261856,
   0x10653d26,
   0x105661c1,
   0x18563136,
   0x3d361426,
   0x61c11065,
   0x39761026,
   0x818491c6,
   0x41951e04,
   0x1c4c161c,
   0x61954ead,
   0xc0b01001,
   0x391191c1,
   0x10001000,
   0x69cc1000,
   0x31307000,
   0x1cd03d30,
   0x1ce04dda,
   0x700049dc,
   0x700010d0,
   0x700010e0,
   0x66cac0b0,
   0xa0f0a0d2,
   0x7311a0f3,
   0x663e7312,
   0xb0f0b130,
   0x80b07100,
   0x45ed2200,
   0xb23161e8,
   0x66cac0c0,
   0xa0f0b130,
   0xc035b0d2,
   0x9b757100,
   0xb074ba38,
   0x61f4b112,
   0x66cac0d0,
   0xa0f0a0d2,
   0x7311a0f3,
   0x663e7312,
   0xc000c18b,
   0x120c91e0,
   0x786a1218,
   0x788e787d,
   0xb13010a9,
   0x7100b0f0,
   0x220080b0,
   0x620d4612,
   0xb231b074,
   0x66cac0e0,
   0xa0f0b130,
   0xc020b0d2,
   0x7100b112,
   0xc0356a1a,
   0x7100b112,
   0x8bf09b75,
   0x8ca165d3,
   0x422b2201,
   0x1ca81080,
   0x1208462a,
   0x65ca1618,
   0x65d38c00,
   0x22018ca1,
   0x10904236,
   0x1e091a19,
   0x10a94636,
   0x818465ca,
   0x421e1e04,
   0x1c4c14bc,
   0x621e4ead,
   0x22308240,
   0xb0d54646,
   0xb1157100,
   0x623ea0d5,
   0x66cac0f0,
   0xb006b118,
   0xb004b016,
   0xb002b014,
   0x8440b012,
   0x04207842,
   0x39838173,
   0x94e32a73,
   0x1832c1f2,
   0x10213162,
   0x00123151,
   0x94400020,
   0x16101030,
   0x22103930,
   0x12204264,
   0x10033150,
   0x16303180,
   0x12029380,
   0x22731204,
   0x84a04276,
   0x89829970,
   0x84c01a82,
   0x89849970,
   0x62781a84,
   0x42832263,
   0x997084b0,
   0x1a808980,
   0x84d01402,
   0x89809970,
   0x14041a80,
   0x84b0628f,
   0x04107851,
   0x89829970,
   0x84d01a42,
   0x04107851,
   0x89849970,
   0x31521a44,
   0x39633154,
   0x16130633,
   0x38343832,
   0x39823182,
   0x00423184,
   0x84a09722,
   0x84b09590,
   0x84c095a0,
   0x84d095b0,
   0x781095c0,
   0x90509030,
   0x90407820,
   0xb2359060,
   0x9170cd90,
   0xa2357000,
   0x7100b112,
   0xb112a0d2,
   0x81b0ba3c,
   0x39248b54,
   0x00043184,
   0xc10091b4,
   0x739166ca,
   0x66c47291,
   0x72027206,
   0x73057204,
   0x60787306,
   0xc8018630,
   0x04103151,
   0x70009630,
   0x89f09a00,
   0x46cb2200,
   0x7000b9e0
};

PATCH_FUN_SPEC void rf_patch_mce_iqdump(void)
{
#ifdef __PATCH_NO_UNROLLING
   uint32_t i;
   for (i = 0; i < 360; i++) {
      HWREG(RFC_MCERAM_BASE + 4 * i) = patchIqdumpMce[i];
   }
#else
   const uint32_t *pS = patchIqdumpMce;
   volatile unsigned long *pD = &HWREG(RFC_MCERAM_BASE);
   uint32_t t1, t2, t3, t4, t5, t6, t7, t8;
   uint32_t nIterations = 45;

   do {
      t1 = *pS++;
      t2 = *pS++;
      t3 = *pS++;
      t4 = *pS++;
      t5 = *pS++;
      t6 = *pS++;
      t7 = *pS++;
      t8 = *pS++;
      *pD++ = t1;
      *pD++ = t2;
      *pD++ = t3;
      *pD++ = t4;
      *pD++ = t5;
      *pD++ = t6;
      *pD++ = t7;
      *pD++ = t8;
   } while (--nIterations);
#endif
}
