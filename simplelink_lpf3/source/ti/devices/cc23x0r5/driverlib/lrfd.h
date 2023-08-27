/******************************************************************************
 *  Filename:       lrfd.h
 *
 *  Description:    Defines and prototypes for LRFD.
 *
 *  Copyright (c) 2023 Texas Instruments Incorporated
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

#ifndef __LRFD_H__
#define __LRFD_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup lrfd_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../inc/hw_lrfddbell.h"

// Number of LRFD clock dependency sets
#define LRFD_NUM_CLK_DEP   2
//! LRFD Clock dependency set to be used by the Power driver
#define LRFD_CLK_DEP_POWER 0
//! LRFD Clock dependency set to be used by the RCL
#define LRFD_CLK_DEP_RCL   1

//*****************************************************************************
//
//! \brief Set clock dependency on a set of modules in LRFD.
//!
//! \warning This API uses internal state, and is not thread safe.
//!
//! This API supports multiple clock dependency sets. For any given LRFD module,
//! it will be clocked if any of the dependency sets has a dependency for that
//! LRFD module.
//! If any dependency set has a dependency on at least one LRFD module, the LRFD
//! module itself will be clocked, otherwise it will not be clocked.
//!
//! \param mask bitmask defining the set of LRFD modules to set clock dependency on.
//! - \ref LRFDDBELL_O_CLKCTL
//! \param dependencySetId ID for the clock dependency set to use.
//! - \ref LRFD_CLK_DEP_POWER
//! - \ref LRFD_CLK_DEP_RCL
//!
//! \sa LRFDReleaseClockDependency()
//!
//! \return None
//
//*****************************************************************************
extern void LRFDSetClockDependency(uint16_t mask, uint8_t dependencySetId);

//*****************************************************************************
//
//! \brief Release clock dependency on a set of modules in LRFD.
//!
//! \warning This API uses internal state, and is not thread safe.
//!
//! This API supports multiple clock dependency sets.
//! See description of \ref LRFDSetClockDependency()
//!
//! \param mask bitmask defining the set of LRFD modules to release clock dependency from.
//! - \ref LRFDDBELL_O_CLKCTL
//! \param dependencySetId ID for the clock dependency set to use.
//! - \ref LRFD_CLK_DEP_POWER
//! - \ref LRFD_CLK_DEP_RCL
//!
//! \sa LRFDSetClockDependency()
//!
//! \return None
//
//*****************************************************************************
extern void LRFDReleaseClockDependency(uint16_t mask, uint8_t dependencySetId);

//*****************************************************************************
//
//! \brief Apply the currently set clock dependencies.
//!
//! \warning This API uses internal state, and is not thread safe.
//!
//! \note The dependencies automatically being applied when setting and
//! releasing dependencies using \ref LRFDSetClockDependency() and
//! \ref LRFDReleaseClockDependency(). This API is mainly intended for when
//! the enabled clocks gets out of sync with the current dependencies.
//! For example, after the device wakes up from standby.
//!
//! This will update the LRFD clock control based on the currently set clock
//! dependencies.
//! If there is a clock dependency on any module in LRFD, the LRFD module itself
//! will be clocked, otherwise it will not be clocked.
//!
//! \return None
//
//*****************************************************************************
extern void LRFDApplyClockDependencies(void);

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

#endif // __LRFD_H__