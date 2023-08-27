/******************************************************************************
 *  Filename:       tempdiode.h
 *
 *  Description:    Defines and prototypes for reading the high accuracy temperature diode
 *
 *  Copyright (c) 2023, Texas Instruments Incorporated
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

#ifndef __tempdiode_H__
#define __tempdiode_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup tempdiode_api
//! @{
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Reads temperature from high accuracy temperature diode
//!
//! This function reads the temperature from the high-accuracy temperature diode
//! The returned result contains 4 fractional bits. For example:
//! 0x00000200 = +32.0000 degC
//! 0x0000020C = +32.7500 degC
//! 0xFFFFFEC3 = -19.8125 degC
//!
//! \warning This function uses the SoC ADC to measure the temperature. This
//! function must not be called while the ADC driver is active, or the SoC ADC
//! is open.
//!
//! \warning This function uses the internal test-bus (ATEST) to measure the
//! temperature. The test-bus must not be used when calling this function.
//!
//! \note Due to long and repeated ADC sampling, this function takes
//! roughly 8 milliseconds to execute.
//!
//! \return Ambient temperature in degrees Celcius, with 4 fractional bits
//
//*****************************************************************************
extern int32_t TempDiodeGetTemp(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! Close the Doxygen group.
//! @}
//! @}
//
//*****************************************************************************

#endif // __tempdiode_H__
