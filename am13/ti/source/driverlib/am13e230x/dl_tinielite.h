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

/**
 * @defgroup DL_TINIELITE_AM13E230X  Driverlib TINIELITE API
 * @ingroup DL_AM13E230X
 *
 * @{
 */

#ifndef DL_TINIELITE_H
#define DL_TINIELITE_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <soc.h>
#include <dl_sysctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/* =========================================================================== */
/*                             TINIELITE Functions                            	   */
/* =========================================================================== */

/**
 * @brief Enables power to the TINIELITE module
 *
 * This function enables power to the TINIELITE IP by
 * setting the appropriate power enable bit in the system control register.
 */
__STATIC_INLINE void DL_TINIELITE_enablePower(void)
{
    DL_SYSCTL_enablePower(DL_SYSCTL_PWREN_TINIE);
}

/**
 * @brief Disables power to the TINIELITE module
 *
 * This function disables power to the TINIELITE IP by
 * clearing the appropriate power enable bit in the system control register.
 */
__STATIC_INLINE void DL_TINIELITE_disablePower(void)
{
    DL_SYSCTL_disablePower(DL_SYSCTL_PWREN_TINIE);
}

/**
 * @brief Checks if power is enabled for the TINIELITE module
 *
 * @return bool Returns true if power is enabled for the TINIELITE module, false otherwise
 */
__STATIC_INLINE bool DL_TINIELITE_isPowerEnabled(void)
{
    return DL_SYSCTL_isPowerEnabled(DL_SYSCTL_PWREN_TINIE);
}

/**
 * @brief Resets the TINIELITE peripheral
 *
 * This function triggers a reset of the TINIELITE peripheral through
 * the system control module.
 */
__STATIC_INLINE void DL_TINIELITE_reset(void)
{
    DL_SYSCTL_resetPeripheral(DL_SYSCTL_RESET_TINIE);
}

/**
 * @brief Enables TINIELITE IP-level interrupts
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @param interruptMask Bit mask of interrupts to enable
 */
__STATIC_INLINE void DL_TINIELITE_enableInterrupt(TINIELITE_Regs *tinie, uint32_t interruptMask)
{
    tinie->CPU_INT.IMASK |= interruptMask;
}

/**
 * @brief Disables TINIELITE IP-level interrupts
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @param interruptMask Bit mask of interrupts to disable
 */
__STATIC_INLINE void DL_TINIELITE_disableInterrupt(TINIELITE_Regs *tinie, uint32_t interruptMask)
{
    tinie->CPU_INT.IMASK &= ~(interruptMask);
}

/**
 * @brief Clears specified TINIELITE interrupt status flags
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @param interruptMask Bit mask of interrupt status flags to clear
 */
__STATIC_INLINE void DL_TINIELITE_clearInterruptStatus(TINIELITE_Regs *tinie, uint32_t interruptMask)
{
    tinie->CPU_INT.ICLR = interruptMask;
}

/**
 * @brief Gets the address of the TINIELITE accumulator registers
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @return uint32_t Address of the accumulator registers in the IPSPECIFIC block
 */
__STATIC_INLINE uint32_t DL_TINIELITE_getAccRegAddress(const TINIELITE_Regs *tinie)
{
    return ((uint32_t)(&tinie->ACCREG));
}

/**
 * @brief Gets the address of the first TINIELITE control register
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @return uint32_t Address of the first control register in the IPSPECIFIC block
 */
__STATIC_INLINE uint32_t DL_TINIELITE_getCtlRegAddress(const TINIELITE_Regs *tinie)
{
    return ((uint32_t)(&tinie->CTL5));
}

/**
 * @brief Sets the instruction memory of the TINIELITE module
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @param byteOffset Byte offset into the instruction memory
 * @param num_words Number of 32-bit words to write
 * @param src Pointer to the source data to write to instruction memory
 */
void DL_TINIELITE_setInstrMem(const TINIELITE_Regs *tinie, uint32_t byteOffset, uint32_t num_words,
                              const uint32_t *src);

/**
 * @brief Sets the parameter memory of the TINIELITE module
 *
 * @param tinie Pointer to the TINIELITE register structure
 * @param byteOffset Byte offset into the parameter memory
 * @param num_words Number of 32-bit words to write
 * @param src Pointer to the source data to write to parameter memory
 */
void DL_TINIELITE_setParamMem(const TINIELITE_Regs *tinie, uint32_t byteOffset, uint32_t num_words,
                              const uint32_t *src);

/**
 * @brief Initializes the TINIELITE module
 *
 * @param tinie Pointer to the TINIELITE register structure
 *
 * This function performs the initialization sequence for the TINIELITE module,
 * including reset, power enable, and interrupt configuration.
 */
void DL_TINIELITE_init(TINIELITE_Regs *tinie);

/**
 * @brief De-Initializes the TINIELITE module
 *
 * @param tinie Pointer to the TINIELITE register structure
 */
void DL_TINIELITE_deinit(TINIELITE_Regs *tinie);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* DL_TINIELITE_H */
