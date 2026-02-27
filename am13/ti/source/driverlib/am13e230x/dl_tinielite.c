/*This file is AUTO GENERATED, DO NOT EDIT manually*/

/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <dl_tinielite.h>

/* ========================================================================== */
/*                             Private define's                               */
/* ========================================================================== */

/* TODO: Source from hw_tinielite.h once IPSPEC is updated*/
#define DL_TINIELITE_INTERRUPT_DONE 1

#define DL_TINIELITE_NUM_INSTMEM_REGS  256
#define DL_TINIELITE_NUM_PARAMMEM_REGS 512

/* ========================================================================== */
/*                             Private functions                              */
/* ========================================================================== */

/**
 * @brief Makes TINIELITE a privileged IP in GSC
 *
 * This function grants privileged status for the TINIELITE IP by
 * setting the appropriate bit in the GSC_PPC_PRIVATTRIB_COPROC register.
 */
__STATIC_INLINE void DL_TINIELITE_givePriv(void)
{
    GSC->PPC_PRIVATTRIB_COPROC |= GSC_PPC_PRIVATTRIB_COPROC_PRIV_TINIE_MASK;
}

/**
 * @brief Makes TINIELITE a non-privileged IP in GSC
 *
 * This function removes privileged status of the TINIELITE IP by
 * clearing the appropriate bit in the GSC_PPC_PRIVATTRIB_COPROC register.
 */
__STATIC_INLINE void DL_TINIELITE_removePriv(void)
{
    GSC->PPC_PRIVATTRIB_COPROC &= ~(GSC_PPC_PRIVATTRIB_COPROC_PRIV_TINIE_MASK);
}

/**
 * @brief Gets the address of the TINIELITE parameter memory
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @return uint32_t Address of the parameter memory (RFDATA registers) in the IPSPECIFIC block
 */
__STATIC_INLINE uint32_t DL_TINIELITE_getParamMemAddress(const TINIELITE_Regs *tinie)
{
    return ((uint32_t)(&tinie->REGFILE));
}

/**
 * @brief Gets the address of the TINIELITE instruction memory
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @return uint32_t Address of the instruction memory in the IPSPECIFIC block
 */
__STATIC_INLINE uint32_t DL_TINIELITE_getInstrMemAddress(const TINIELITE_Regs *tinie)
{
    return ((uint32_t)(&tinie->INSTMEM));
}

/* ========================================================================== */
/*                             Public functions                               */
/* ========================================================================== */

void DL_TINIELITE_setInstrMem(const TINIELITE_Regs *tinie, uint32_t byteOffset, uint32_t num_words, const uint32_t *src)
{
    if (src != NULL && byteOffset % sizeof(uint32_t) == 0 &&
        (DL_TINIELITE_NUM_INSTMEM_REGS >= (num_words + (byteOffset) / sizeof(uint32_t))) &&
        (num_words + (byteOffset) / sizeof(uint32_t)) > 0)
    {
        volatile uint32_t *dest;

        dest = (uint32_t *)(DL_TINIELITE_getInstrMemAddress(tinie) + byteOffset);

        while (num_words-- > 0)
        {
            *(dest++) = *(src++);
        }
    }
}

void DL_TINIELITE_setParamMem(const TINIELITE_Regs *tinie, uint32_t byteOffset, uint32_t num_words, const uint32_t *src)
{
    if (src != NULL && byteOffset % sizeof(uint32_t) == 0 &&
        (DL_TINIELITE_NUM_PARAMMEM_REGS >= (num_words + (byteOffset) / sizeof(uint32_t))) &&
        (num_words + (byteOffset) / sizeof(uint32_t)) > 0)
    {
        volatile uint32_t *dest;

        dest = (uint32_t *)(DL_TINIELITE_getParamMemAddress(tinie) + byteOffset);

        while (num_words-- > 0)
        {
            *(dest++) = *(src++);
        }
    }
}

void DL_TINIELITE_init(TINIELITE_Regs *tinie)
{
    /* Power up the neural processing unit (TINIELITE) module.
     * Clear and enable the TINIELITE interrupt.
     */
    DL_TINIELITE_reset();
    DL_TINIELITE_enablePower();

    DL_TINIELITE_clearInterruptStatus(tinie, DL_TINIELITE_INTERRUPT_DONE);
    DL_TINIELITE_enableInterrupt(tinie, DL_TINIELITE_INTERRUPT_DONE);

    // TODO: Use GSC driver once ready
    DL_TINIELITE_givePriv();
}

void DL_TINIELITE_deinit(TINIELITE_Regs *tinie)
{
    DL_TINIELITE_disableInterrupt(tinie, DL_TINIELITE_INTERRUPT_DONE);
    DL_TINIELITE_clearInterruptStatus(tinie, DL_TINIELITE_INTERRUPT_DONE);
    DL_TINIELITE_removePriv();
}
