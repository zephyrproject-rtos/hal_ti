/******************************************************************************
 *  Filename:       lpcmp.h
 *
 *  Description:    Defines and prototypes for the LPCMP peripheral.
 *
 *  Copyright (c) 2022-2024, Texas Instruments Incorporated
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

#ifndef __LPCMP_H__
#define __LPCMP_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup lpcmp_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_sys0.h"

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
// Defines that can be passed to LPCMPSetDividerPath() to select the voltage
// divider path.
//
//*****************************************************************************
#define LPCMP_DIVISION_PATH_N SYS0_LPCMPCFG_DIVPATH_NSIDE //!< Apply voltage divider to the negative input
#define LPCMP_DIVISION_PATH_P SYS0_LPCMPCFG_DIVPATH_PSIDE //!< Apply voltage divider to the positive input

//*****************************************************************************
//
// Defines that can be passed to LPCMPSetDividerRatio() to select which ratio
// should be used by the voltage divider.
//
//*****************************************************************************
#define LPCMP_DIVISION_FACTOR_1_1 SYS0_LPCMPCFG_DIV_VAL0 //!< Apply a 1/1 voltage division ratio
#define LPCMP_DIVISION_FACTOR_3_4 SYS0_LPCMPCFG_DIV_VAL1 //!< Apply a 3/4 voltage division ratio
#define LPCMP_DIVISION_FACTOR_1_2 SYS0_LPCMPCFG_DIV_VAL2 //!< Apply a 1/2 voltage division ratio
#define LPCMP_DIVISION_FACTOR_1_3 SYS0_LPCMPCFG_DIV_VAL3 //!< Apply a 1/3 voltage division ratio
#define LPCMP_DIVISION_FACTOR_1_4 SYS0_LPCMPCFG_DIV_VAL4 //!< Apply a 1/4 voltage division ratio

//*****************************************************************************
//
// Defines that can be passed to LPCMPSetPolarity() to select which edge type
// should generate a LPCMP event.
//
//*****************************************************************************
#define LPCMP_POLARITY_FALL SYS0_LPCMPCFG_EDGCFG_FALL //!< Select falling edge for event generation
#define LPCMP_POLARITY_RISE SYS0_LPCMPCFG_EDGCFG_RISE //!< Select rising edge for event generation

//*****************************************************************************
//
// Defines that can be passed to LPCMPNegativeInputSelect() to select which
// signal should be muxed to LPCMP negative input.
//
//*****************************************************************************
#define LPCMP_NEG_INPUT_VDDD SYS0_LPCMPCFG_NSEL_VDDD      //!< Select VDDD as negative input
#define LPCMP_NEG_INPUT_VDDS SYS0_LPCMPCFG_NSEL_VDDA      //!< Select VDDS(VDDA) as negative input
#define LPCMP_NEG_INPUT_A2   SYS0_LPCMPCFG_NSEL_VA_PAD_A2 //!< Select PAD_A2 as negative input
#define LPCMP_NEG_INPUT_A3   SYS0_LPCMPCFG_NSEL_VA_PAD_A3 //!< Select PAD_A3 as negative input
#define LPCMP_NEG_INPUT_OPEN SYS0_LPCMPCFG_NSEL_OPEN      //!< Leave negative input floating

//*****************************************************************************
//
// Defines that can be passed to LPCMPPositiveInputSelect() to select which
// signal should be muxed to LPCMP positive input.
//
//*****************************************************************************
#define LPCMP_POS_INPUT_A1   SYS0_LPCMPCFG_PSEL_VA_PAD_A1 //!< Select PAD_A1 as positive input
#define LPCMP_POS_INPUT_A2   SYS0_LPCMPCFG_PSEL_VA_PAD_A2 //!< Select PAD_A2 as positive input
#define LPCMP_POS_INPUT_A3   SYS0_LPCMPCFG_PSEL_VA_PAD_A3 //!< Select PAD_A3 as positive input
#define LPCMP_POS_INPUT_VDDS SYS0_LPCMPCFG_PSEL_VDDA      //!< Selects VDDS(VDDA) as positive input
#define LPCMP_POS_INPUT_OPEN SYS0_LPCMPCFG_PSEL_OPEN      //!< Leave negative positive floating

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Enables LPCMP.
//!
//! This function enables LPCMP and it must be called after having configured
//! the peripheral's inputs, voltage divider and event generation logic.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPEnable(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) |= SYS0_LPCMPCFG_EN;
}

//*****************************************************************************
//
//! \brief Disables LPCMP.
//!
//! This function disables LPCMP after it has been enabled using \ref LPCMPEnable().
//
//*****************************************************************************
__STATIC_INLINE void LPCMPDisable(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_EN;
}

//*****************************************************************************
//
//! \brief Enables LPCMP event generation.
//!
//! This function enables LPCMP event generation to the event fabric.
//! Polarity must be selected using \ref LPCMPSetPolarity() to determine on which
//! edge type of LPCMP output an event should be generated. LPCMP doesn't have a
//! dedicated interrupt line, therefore a configurable interrupt line must be
//! configured to propagate LPCMP events.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPEnableEvent(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) |= SYS0_LPCMPCFG_EVTEN;
}

//*****************************************************************************
//
//! \brief Disables LPCMP event generation.
//!
//! This function disables LPCMP event generation to the event fabric.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPDisableEvent(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_EVTEN;
}

//*****************************************************************************
//
//! \brief Clear LPCMP event flag.
//!
//! This function clears LPCMP event flag and should be called from the ISR
//! registered to service LPCMP interrupts.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPClearEvent(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_EVTIFG;
}

//*****************************************************************************
//
//! \brief Enables LPCMP as wakeup source from standby.
//!
//! This function enables LPCMP as one of the sources that can wakeup the device
//! from standby.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPEnableWakeup(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) |= SYS0_LPCMPCFG_WUENSB;
}

//*****************************************************************************
//
//! \brief Disables LPCMP as wakeup source from standby.
//!
//! This function disables LPCMP as one of the sources that can wakeup the device
//! from standby.
//
//*****************************************************************************
__STATIC_INLINE void LPCMPDisableWakeup(void)
{
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_WUENSB;
}

//*****************************************************************************
//
//! \brief Selects the negative input of LPCMP.
//!
//! This function selects one of the available sources as the negative input of
//! LPCMP. This function must be called before enabling LPCMP using \ref LPCMPEnable().
//!
//! \param input
//!     LPCMP negative input source:
//!     - \ref LPCMP_NEG_INPUT_VDDD
//!     - \ref LPCMP_NEG_INPUT_VDDS
//!     - \ref LPCMP_NEG_INPUT_A2
//!     - \ref LPCMP_NEG_INPUT_A3
//!     - \ref LPCMP_NEG_INPUT_OPEN
//
//*****************************************************************************
__STATIC_INLINE void LPCMPSelectNegativeInput(uint32_t input)
{
    uint32_t lpcmpcfg;

    lpcmpcfg                           = HWREG(SYS0_BASE + SYS0_O_LPCMPCFG);
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) = (lpcmpcfg & ~SYS0_LPCMPCFG_NSEL_M) | (input & SYS0_LPCMPCFG_NSEL_M);
}

//*****************************************************************************
//
//! \brief Verifies if the raw output of LPCMP is high.
//!
//! This function returns a boolean value indicating whether the raw output of
//! LPCMP is high or low
//!
//! \return status of LPCMP raw output:
//! - \c true  : LPCMP raw output is high.
//! - \c false : LPCMP raw output is low.
//
//*****************************************************************************
__STATIC_INLINE bool LPCMPIsOutputHigh(void)
{
    if (HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) & SYS0_LPCMPCFG_COUT_HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*****************************************************************************
//
//! \brief Selects the positive input of LPCMP.
//!
//! This function selects one of the available sources as the positive input of
//! LPCMP. This function must be called before enabling LPCMP using \ref LPCMPEnable().
//!
//! \param input
//!     LPCMP positive input source:
//!     - \ref LPCMP_POS_INPUT_A1
//!     - \ref LPCMP_POS_INPUT_A2
//!     - \ref LPCMP_POS_INPUT_A3
//!     - \ref LPCMP_POS_INPUT_VDDS
//!     - \ref LPCMP_POS_INPUT_OPEN
//
//*****************************************************************************
__STATIC_INLINE void LPCMPSelectPositiveInput(uint32_t input)
{
    uint32_t lpcmpcfg;

    lpcmpcfg                           = HWREG(SYS0_BASE + SYS0_O_LPCMPCFG);
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) = (lpcmpcfg & ~SYS0_LPCMPCFG_PSEL_M) | (input & SYS0_LPCMPCFG_PSEL_M);
}

//*****************************************************************************
//
//! \brief Selects the edge polarity of LPCMP output on which an event
//! is triggered.
//!
//! This function selects whether a rising or falling edge of LPCMP output
//! will trigger an event propagated through the event fabric.
//!
//! \param polarity
//!     Edge polarity of LPCMP output on which the event is triggered:
//!     - \ref LPCMP_POLARITY_RISE
//!     - \ref LPCMP_POLARITY_FALL
//
//*****************************************************************************
__STATIC_INLINE void LPCMPSetPolarity(uint32_t polarity)
{
    if (polarity == LPCMP_POLARITY_FALL)
    {
        HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) |= SYS0_LPCMPCFG_EDGCFG;
    }
    else
    {
        HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_EDGCFG;
    }
}

//*****************************************************************************
//
//! \brief Selects the ratio used by LPCMP voltage divider
//!
//! This function selects the ratio used by LPCMP voltage divider to divide one
//! of the two comparator inputs. Use \ref LPCMPSetDividerPath() to select if
//! the ratio should be applied to the negative or positive input of LPCMP.
//!
//! \param divider
//!     Divider ratio used by LPCMP voltage divider:
//!     - \ref LPCMP_DIVISION_FACTOR_1_1
//!     - \ref LPCMP_DIVISION_FACTOR_3_4
//!     - \ref LPCMP_DIVISION_FACTOR_1_2
//!     - \ref LPCMP_DIVISION_FACTOR_1_3
//!     - \ref LPCMP_DIVISION_FACTOR_1_4
//
//*****************************************************************************
__STATIC_INLINE void LPCMPSetDividerRatio(uint32_t divider)
{
    uint32_t lpcmpcfg;

    lpcmpcfg                           = HWREG(SYS0_BASE + SYS0_O_LPCMPCFG);
    HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) = (lpcmpcfg & ~SYS0_LPCMPCFG_DIV_M) | (divider & SYS0_LPCMPCFG_DIV_M);
}

//*****************************************************************************
//
//! \brief Selects the input path on which the LPCMP voltage divider is applied
//!
//! This function selects the input path on which the LPCMP voltage divider is
//! applied. Use \ref LPCMPSetDividerRatio() to set the division ratio applied
//! by the LPCMP voltage divider on the selected path.
//!
//! \param path
//!     Input path the LPCMP voltage divider is applied to:
//!     - \ref LPCMP_DIVISION_PATH_N
//!     - \ref LPCMP_DIVISION_PATH_P
//
//*****************************************************************************
__STATIC_INLINE void LPCMPSetDividerPath(uint32_t path)
{
    if (path == LPCMP_DIVISION_PATH_P)
    {
        HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) |= SYS0_LPCMPCFG_DIVPATH;
    }
    else
    {
        HWREG(SYS0_BASE + SYS0_O_LPCMPCFG) &= ~SYS0_LPCMPCFG_DIVPATH;
    }
}

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

#endif // __LPCMP_H__
