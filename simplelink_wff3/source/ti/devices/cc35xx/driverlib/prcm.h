/******************************************************************************
 *  Filename:       prcm.h
 *
 *  Description:    Defines and prototypes for the PRCM
 *
 *  Copyright (c) 2026 Texas Instruments Incorporated
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

#ifndef ti_devices_prcm__include
#define ti_devices_prcm__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup prcm_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_hostmcu_aon.h"
#include "../inc/hw_prcm_aon.h"
#include "../inc/hw_ints.h"

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
//! \brief Enables and configures the LFXT
//!
//! This function sests the external crystal oscillator as the LFCLK source.
//!
//! \return None
//
//*****************************************************************************
extern void PRCMEnableLFXT(void);

//*****************************************************************************
//
//! \brief Disables the LFOSC
//!
//! When the LFOSC is not used as the LFCLK source, it can be turned off to save power.
//!
//! \return None
//
//*****************************************************************************
extern void PRCMDisableLFOSC(void);

//*****************************************************************************
//
//! \brief Sets the 'LFXT GOOD' bit
//!
//! When the software has properly configured LFXT, this function tells the HW that
//! the LFXT is operational.
//!
//! \return None
//
//*****************************************************************************
extern void PRCMSetLFXTGood(void);

//*****************************************************************************
//
//! \brief Sets the LFXT trim values
//!
//! Sets the LFXT ITRIM and RTRIM values.
//!
//! \return None
//
//*****************************************************************************
extern void PRCMSetLFXTTrims(void);

//*****************************************************************************
//
//! \brief Reads the status of the 'Detection GOOD' bit
//!
//! Get the status of the LFXT/EXT/XTAL.
//!
//! \return Returns \c true if the HW has detected 5 clock cycles from LFXT
//! and returns \c false otherwise
//
//*****************************************************************************
extern bool PRCMLFXTStatusGood(void);

//*****************************************************************************
//
//! \brief Select LFXT as LFCLK source
//!
//! This function configures the HW to use LFXT/EXT/XTAL signal
//! as source for the LFCLK
//!
//! \return None
//
//*****************************************************************************
extern void PRCMSelectLFXT(void);

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

#endif // ti_devices_prcm__include
