/******************************************************************************
 *  Filename:       cpu.c
 *
 *  Description:    Instruction wrappers for special CPU instructions needed by
 *                  the drivers.
 *
 *  Copyright (c) 2022 Texas Instruments Incorporated
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
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
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

#include "cpu.h"

//*****************************************************************************
//
// Provide a small delay
//
//*****************************************************************************
#if defined(DOXYGEN)
void CPUDelay(uint32_t count)
{
    // This function is written in assembly. See cpu.c for compiler specific implementation.
}
#elif defined(__IAR_SYSTEMS_ICC__)
void CPUDelay(uint32_t count)
{
    // Loop the specified number of times
    __asm("CPUDelay:\n"
          "    subs    r0, #1\n"
          "    bne.n   CPUDelay\n"
          "    bx      lr");
    #pragma diag_suppress = Pe940
}
    #pragma diag_default  = Pe940

#elif defined(__TI_COMPILER_VERSION__)
// For CCS implement this function in pure assembly. This prevents the TI
// compiler from doing funny things with the optimizer.

// Loop the specified number of times
__asm("    .sect \".text:CPUDelay\"\n"
      "    .clink\n"
      "    .thumbfunc CPUDelay\n"
      "    .thumb\n"
      "    .global CPUDelay\n"
      "CPUDelay:\n"
      "    subs r0, #1\n"
      "    bne.n CPUDelay\n"
      "    bx lr\n");

#elif defined(__clang__)
void CPUDelay(uint32_t count)
{
    (void)count; // Linter does not see the use of r0 in asm.
    // Loop the specified number of times
    __asm("    subs    r0, #1\n"
          "    bne.n   CPUDelay\n"
          "    bx      lr");
}
#else
// GCC
void __attribute__((naked)) CPUDelay(uint32_t count)
{
    // Loop the specified number of times
    __asm volatile(".syntax unified\n"
                   "%=:  subs  %0, #1\n"
                   "     bne   %=b\n"
                   "     bx    lr\n"
                   : /* No output */
                   : "r"(count));
}
#endif
