// This file is AUTO GENERATED, DO NOT EDIT manually

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
 * @defgroup DL_COMMON_AM13E230X  Driverlib common API
 * @ingroup DL_AM13E230X
 *
 * APIs used across multiple DriverLib modules
 *
 * @{
 */

#ifndef DL_COMMON_H
#define DL_COMMON_H

#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief STATUS OK  */

#define DL_STATUS_OK (0)

/** @brief STATUS FAIL  */

#define DL_STATUS_FAIL (1)

/** @brief Reads a register as uint32_t */
#define HWREG(x)  (*((volatile uint32_t *)(x)))
/** @brief Reads a register as uint16_t */
#define HWREGH(x) (*((volatile uint16_t *)(x)))
/** @brief Reads a register as uint8_t */
#define HWREGB(x) (*((volatile uint8_t *)(x)))

/** @brief Assertion macro. __error__ should be defined by application */
#define ASSERT(expr)                   \
    if (!(expr))                       \
    {                                  \
        __error__(__FILE__, __LINE__); \
    }

/** @brief RAMFUNC macro is added before a function to execute the
    function from RAM */
#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define RAMFUNC __attribute__((section(".TI.ramfunc"))) __attribute__((noinline))
#elif defined(__GNUC__)
#define RAMFUNC __attribute__((section(".ramfunc"))) __attribute__((noinline))
#elif defined(__IAR_SYSTEMS_ICC__)
#define RAMFUNC __ramfunc __attribute__((noinline))
#else
#error "Compiler not supported for this function"
#endif

/**
 *  @brief Error function that is called when an invalid argument is passed to an API
 *
 *  It is the application's responsibility to define the __error__ function.
 *  A weak definition of the function is available in dl_common.c file
 *
 *  @param[in] filename File Name
 *  @param[in] line     Line number
 *
 */
extern void __error__(const char *filename, uint32_t line);

/**
 * @brief   Writes value to specified register - retaining bits unaffected by mask.
 *
 * @param[in] reg     Pointer to the register overlay for the peripheral.
 * @param[in] val     Value to be written to the register.
 * @param[in] mask    Mask defines which bits will be altered.
 */
__STATIC_INLINE void DL_Common_updateReg(volatile uint32_t *reg, uint32_t val, uint32_t mask)
{
    uint32_t tmp;

    tmp  = *reg;
    tmp  = tmp & ~mask;
    *reg = tmp | (val & mask);
}

/**
 * @brief   Consumes the number of CPU cycles specified.
 *
 * @param[in] cycles  Floor number of cycles to delay.
 *                    Specifying zero will result in the maximum
 *                    possible delay. Note that guarantees at least
 *                    this number of cycles will be delayed,
 *                    not that exactly this number of cycles will be
 *                    delayed. If a more precise number of cycle delay value
 *                    is needed, GPTimer is recommended.
 *
 *                    Typical variance from this function is 10 cycles or
 *                    less assuming that the function is located in flash and
 *                    that caching is enabled. Disabling caching may result in
 *                    wait-states when fetching from flash.
 *                    Other variance occurs due:
 *                      - Amount of register stacking/unstacking around API entry/exit
 *                      - Value of cycles relative to 4-cycle loop counter
 *                      - Placement of code on a 2- or 4-byte aligned boundary
 */
void DL_Common_delayCycles(uint32_t cycles);

#ifdef __cplusplus
}
#endif

#endif /* DL_COMMON_H */
/** @}*/

/**
 * @defgroup DL_AM13E230X  Driverlib (AM13E230X) APIs
 */
