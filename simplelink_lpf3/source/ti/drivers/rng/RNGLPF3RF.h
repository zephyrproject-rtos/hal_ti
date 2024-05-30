/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       RNGLPF3RF.h
 *
 *  @brief      RNG driver implementation for the CC23X0 family
 *
 *  This file should only be included in the board file to fill the RNG_config
 *  structure.
 *
 *  The CC23X0 family does not have a general purpose TRNG. However, it can
 *  collect radio noise when the radio is not being used (such as during boot)
 *  and use that noise as a source for a seed for an AES CTR DRBG.
 *
 *  The radio noise is first processed using AES CBC MAC in order to compress
 *  the entropy of the noise into a 256 bit value with close to 256 bits of
 *  entropy. That 256 bit value is then used as the seed value for the AES CTR
 *  DRBG.
 *
 *  The RNG driver then uses the AES CTR DRBG to fulfill any requests for
 *  entropy.
 *
 *  In order to ensure proper operation, RNG_init() must be called prior to to
 *  any other use of the radio. Because other drivers may be using the RNG
 *  driver, it is recommended that RNG_init() be called as part of the
 *  application's startup routines.
 *
 *  @note This implementation does not support the RNG_RETURN_BEHAVIOR_CALLBACK
 *        return mode.
 *
 *  @note This implementation treats RNG_RETURN_BEHAVIOR_POLLING as
 *        RNG_RETURN_BEHAVIOR_BLOCKING.
 */

#ifndef ti_drivers_rng_RNGLPF3RF__include
#define ti_drivers_rng_RNGLPF3RF__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/RNG.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Word length of the noise input from RCL */
extern const uint32_t RNGLPF3RF_noiseInputWordLen;

/*! \cond Internal APIs */

/*!
 *  @brief RNGLPF3RF Object
 *
 *  \note The application must not access any member variables of this structure!
 */
typedef struct
{
    bool isOpen;
    uint32_t timeout;
} RNGLPF3RF_Object;

typedef struct
{
    uint8_t intPriority;
} RNGLPF3RF_HWAttrs;

/*!
 *  @brief Conditions the noise buffer from RCL and seed the RNG.
 *
 *  This function conditions the provided RCL (Radio) noise
 *  using CBC MAC to generate a 256-bit seed which is used seed the RNG driver.
 *
 *  The noise input is read from RCL using RCL_AdcNoise_get_samples_blocking().
 *  The minimum word length of the noise input is 80 words to generate a 256-bit seed.
 *  The user must ensure #RNGLPF3RF_conditionNoiseToGenerateSeed() is called before #RNG_init(), otherwise
 *  RNG driver initialization will fail.
 *
 *  @param  noisePtr A pointer to the buffer containing noise input from RCL
 *
 *  @retval #RNG_STATUS_SUCCESS                  RNG driver was successfully seeded.
 *  @retval #RNG_STATUS_NOISE_INPUT_INVALID      RNG driver was not seeded as the noise input was invalid
 */
int_fast16_t RNGLPF3RF_conditionNoiseToGenerateSeed(uint32_t *noisePtr);

/*! \endcond */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_rng_RNGLPF3RF__include */
