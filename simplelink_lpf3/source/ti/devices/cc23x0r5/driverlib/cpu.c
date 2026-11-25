/******************************************************************************
 *  Filename:       cpu.c
 *
 *  Description:    Instruction wrappers for special CPU instructions needed by
 *                  the drivers.
 *
 *  Copyright (c) 2022-2025 Texas Instruments Incorporated
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
#elif (defined(__clang__) || defined(__GNUC__))
void __attribute__((naked, no_profile_instrument_function)) CPUDelay(uint32_t count)
{
    // The naked attribute tells the compiler that the function is effectively
    // hand-coded assembly implemented using inlined assembly without operands.
    // In naked functions, we can't use parameter references directly.
    // For ARM calling convention, the first parameter (count) is in r0.
    // no_profile_instrument_function disables code coverage instrumentation.
    // which could break the above assumption that count is in r0.
    __asm volatile(".syntax unified\n"
                   "CPUDel%=:\n"           /* Label with unique suffix */
                   "    subs r0, r0, #1\n" /* Subtract 1 from r0 (count) - Thumb16 compatible */
                   "    bne CPUDel%=\n"    /* Branch to label if not zero */
                   "    bx lr\n"           /* Return */
                   :
                   :
                   : "r0", "cc" /* Clobbers. "cc" is the flags */
    );
}
#else
    #error "Unsupported toolchain!"
#endif
