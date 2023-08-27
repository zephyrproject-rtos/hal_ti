//#########################################################################################
//  Copyright (c) 2022 Texas Instruments Incorporated
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1) Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2) Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3) Neither the name of the copyright holder nor the names of its contributors may
//     be used to endorse or promote products derived from this software without
//     specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
//#########################################################################################
// Filename: aes_iar.s
// Description: Low level AES functions
// Language: IAR Assembly for ARM
// Processor: ARM Cortex M0
// Compiler: IAR
//#########################################################################################

//-----------------------------------------------------------------------------------------
//  AESProcessAlignedBlocksCMAC
//-----------------------------------------------------------------------------------------
    SECTION .text:CODE(2)
    THUMB
    EXPORT AESProcessAlignedBlocksCMAC


    #define input   R0
    #define blocks  R1
    #define buf0    R2

AESProcessAlignedBlocksCMAC:
    PUSH {R4-R6}

CMAC_WRITE_BLOCK:
    LDM input!, {R3-R6}         // Read input block (4 words)
    LDR buf0, AES_BUF0_ADDR     // buf0 = AES BUF0 register addr
    STM buf0!, {R3-R6}          // Write input block to AES BUF regs
    SUBS blocks, blocks, #0x1   // Decrement block cnt by 1
    BNE CMAC_WRITE_BLOCK

    POP {R4-R6}
    BX LR

    #undef input
    #undef blocks
    #undef buf0

//-----------------------------------------------------------------------------------------
//  AESProcessAlignedBlocksCTR
//-----------------------------------------------------------------------------------------
    SECTION .text:CODE(2)
    THUMB
    EXPORT AESProcessAlignedBlocksCTR

    #define input   R0
    #define output  R1
    #define blocks  R2
    #define dst     R3

AESProcessAlignedBlocksCTR:

    PUSH {R4-R7}

CTR_PROCESS_BLOCK:
    LDM input!, {R4-R7}         // Read input block (4 words)
    LDR dst, AES_TXTX0_ADDR     // dst = AES TXTX0 register addr
    STM dst!, {R4-R7}           // Write input block to AES TXTX regs
    LDR dst, AES_TXT0_ADDR      // dst = AES TXT0 register addr
    LDM dst!, {R4-R7}           // Read output block from TXT regs (4 words)
    STM output!, {R4-R7}        // Write output block (4 words)
    SUBS blocks, blocks, #0x1   // Decrement block cnt by 1
    BNE CTR_PROCESS_BLOCK

    POP {R4-R7}
    BX LR

    #undef input
    #undef output
    #undef blocks
    #undef dst

//-----------------------------------------------------------------------------------------
//  AESProcessAlignedBlocksECB
//-----------------------------------------------------------------------------------------
    SECTION .text:CODE(2)
    THUMB
    EXPORT AESProcessAlignedBlocksECB

    #define input   R0
    #define output  R1
    #define blocks  R2
    #define dst     R3

AESProcessAlignedBlocksECB:

    PUSH {R4-R7}

    LDM input!, {R4-R7}         // Read first input block (4 words)
    LDR dst, AES_BUF0_ADDR      // dst = AES BUF0 register addr
    STM dst!, {R4-R7}           // Write first input block to AES TXTX regs
    SUBS blocks, blocks, #0x1   // Decrement block cnt by 1
    BEQ ECB_READ_FINAL_OUTPUT

ECB_PROCESS_BLOCK:
    LDM input!, {R4-R7}         // Read input block (4 words)
    LDR dst, AES_BUF0_ADDR      // dst = AES BUF0 register addr
    STM dst!, {R4-R7}           // Write input block to AES TXTX regs
    LDR dst, AES_TXT0_ADDR      // dst = AES TXT0 register addr
    LDM dst!, {R4-R7}           // Read output block from TXT regs (4 words)
    STM output!, {R4-R7}        // Write output block (4 words)
    SUBS blocks, blocks, #0x1   // Decrement block cnt by 1
    BNE ECB_PROCESS_BLOCK

ECB_READ_FINAL_OUTPUT:
    // Clear the AUTOCFG trigger mask to avoid triggering a spurious encryption
    // upon reading the TXT3 register.
    LDR R3, AES_AUTOCFG_ADDR    // R3 = AES AUTOCFG register addr
    LDR R4, [R3]                // R4 = AES AUTOCFG register value
    MOVS R5, #0xF               // R5 = TRGECB_MASK
    BICS R4, R4, R5             // R4 = AUTOCFG & ~TRGECB_MASK
    STR R4, [R3]                // Write modified AUTOCFG value

    LDR dst, AES_TXT0_ADDR      // dst = AES TXT0 register addr
    LDM dst!, {R4-R7}           // Read final output block from TXT regs (4 words)
    STM output!, {R4-R7}        // Write final output block (4 words)

    POP {R4-R7}
    BX LR

    #undef input
    #undef output
    #undef blocks
    #undef dst

//-----------------------------------------------------------------------------------------
//  Constants
//-----------------------------------------------------------------------------------------

    SECTION .text:CONST(2)
    DATA
    ALIGNROM 2

AES_AUTOCFG_ADDR:
    DC32 0x400C002C             // AES AUTOCFG register addr
AES_TXT0_ADDR:
    DC32 0x400C0070             // AES TXT0 register addr
AES_TXTX0_ADDR:
    DC32 0x400C0080             // AES TXTX0 register addr
AES_BUF0_ADDR:
    DC32 0x400C0090             // AES BUF0 register addr


//-----------------------------------------------------------------------------------------
//  AESCopyBlock
//-----------------------------------------------------------------------------------------
    SECTION .text:CODE(2)
    THUMB
    EXPORT AESCopyBlock

    #define dst R0
    #define src R1
    #define tmp R2
    #define len R3

AESCopyBlock:

    LSLS tmp, dst, #0x1e        // dst << 30
    BNE UNALIGNED_COPY
    LSLS tmp, src, #0x1e        // src << 30
    BNE UNALIGNED_COPY

WORD_ALIGNED_COPY:
    PUSH {R4-R5}
    LDM src!, {R2-R5}           // Read src block (4 words)
    STM dst!, {R2-R5}           // dst block = src block
    POP {R4-R5}
    BX LR

UNALIGNED_COPY:
    MOVS len, #16               // len = 16 bytes
UNALIGNED_COPY_LOOP:
    LDRB tmp, [src]             // tmp = src[i]
    STRB tmp, [dst]             // dst[i] = src[i]
    ADDS src, src, #1           // Increment src ptr by 1
    ADDS dst, dst, #1           // Increment dst ptr by 1
    SUBS len, #1                // Decrement len by 1
    BNE UNALIGNED_COPY_LOOP
    BX LR

    #undef dst
    #undef src
    #undef tmp
    #undef len

    END
