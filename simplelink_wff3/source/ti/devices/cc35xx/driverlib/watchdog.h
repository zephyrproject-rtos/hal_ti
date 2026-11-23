/******************************************************************************
 *  Filename:       watchdog.h
 *
 *  Description:    Defines and prototypes for the Watchdog capabilities of the
 *                  ELPTMR peripheral.
 *
 *  Copyright (c) 2025-2026 Texas Instruments Incorporated
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

#ifndef ti_devices_watchdog__include
#define ti_devices_watchdog__include

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup watchdog_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_hostmcu_aon.h"
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
// Extended hw_hostmcu_aon.h defines - shift 0 because ELP TMR is bit 0 of VAL
// bitfield.
//
//*****************************************************************************
#define HOSTMCU_AON_CFGWICSNS_ELP_TMR_EN (HOSTMCU_AON_CFGWICSNS_VAL_TMRREQ_EN << 0)
#define HOSTMCU_AON_CFGWUTP_ELP_TMR_FAST (HOSTMCU_AON_CFGWUTP_VAL_TMRREQ << 0)

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Clears the timer wake-up event.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogClearWakeUpEvent(void)
{
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_TMRWUREQ) = HOSTMCU_AON_TMRWUREQ_CLR_M;
}

//*****************************************************************************
//
//! \brief Disables the timer wake-up event.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogDisableWakeUpEvent(void)
{
    // Disable ELP TMR event as a sleep wake-up source
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) &= ~HOSTMCU_AON_CFGWICSNS_ELP_TMR_EN;

    // Disable the wake-up threshold
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU) &= ~HOSTMCU_AON_CFGTMRWU_EN;
}

//*****************************************************************************
//
//! \brief Disables the timer reset event.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogDisableResetEvent(void)
{
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWDT) &= ~HOSTMCU_AON_CFGWDT_EN;
}

//*****************************************************************************
//
//! \brief Enables the timer wake-up event.
//!
//! This function configures the wake-up event as a fast wake-up source, as a
//! sleep wake-up source and enables it.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogEnableWakeUpEvent(void)
{
    // Configure the ELP TMR event to be a fast wake-up source
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWUTP) |= HOSTMCU_AON_CFGWUTP_ELP_TMR_FAST;

    // Configure the ELP TMR event as a sleep wake-up source
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) |= HOSTMCU_AON_CFGWICSNS_ELP_TMR_EN;

    // Enable the wake-up event
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU) |= HOSTMCU_AON_CFGTMRWU_EN;
}

//*****************************************************************************
//
//! \brief Enables the timer reset event.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogEnableResetEvent(void)
{
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWDT) |= HOSTMCU_AON_CFGWDT_EN;
}

//*****************************************************************************
//
//! \brief Reads the status of the timer
//!
//! \return Returns if the timer is enabled or not

//
//*****************************************************************************
__STATIC_INLINE bool WatchdogStatus(void)
{
    bool timerStatus = ((HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) & HOSTMCU_AON_ELPTMREN_VAL_M) >>
                         HOSTMCU_AON_ELPTMREN_VAL_S);
    return timerStatus;
}

//*****************************************************************************
//
//! \brief Waits until the timer is enabled.
//!
//! \return None

//
//*****************************************************************************
__STATIC_INLINE void WatchdogWaitUntilEnabled(void)
{
    while (WatchdogStatus() != HOSTMCU_AON_ELPTMREN_VAL_EN) {}
}

//*****************************************************************************
//
//! \brief Waits until the timer is disabled.
//!
//! \return None

//
//*****************************************************************************
__STATIC_INLINE void WatchdogWaitUntilDisabled(void)
{
    while (WatchdogStatus() != HOSTMCU_AON_ELPTMREN_VAL_DIS) {}
}

//*****************************************************************************
//
//! \brief Re-sets the timer back to zero.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogReset(void)
{
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRLD;
}

//*****************************************************************************
//
//! \brief Sets the wake-up threshold.
//!
//! \note This function aligns the wake-up threshold resolution to match the
//!       reset resolution. Therefore, the resolution of one tick is 7.8125 ms.
//!
//! \param[in] ticks is the time in reset threshold ticks. Must be greater than
//!            1.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogSetWakeUpThreshold(uint32_t ticks)
{
    // Align the wake-up threshold resolution to match the reset resolution.
    // Each reset threshold tick corresponds to 256 (2^8) wake-up threshold
    // ticks because the reset threshold bit field is smaller.
    uint32_t ticksInResetResolution = (ticks << HOSTMCU_AON_CFGWDT_THR_S) & HOSTMCU_AON_CFGWDT_THR_M;

    uint32_t temp = HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU);
    temp &= ~HOSTMCU_AON_CFGTMRWU_THR_M;
    temp |= ticksInResetResolution;
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU) = temp;
}

//*****************************************************************************
//
//! \brief Sets the reset threshold.
//!
//! \note The resolution of one tick is 7.8125 ms.
//!
//! \param[in] ticks is the time in reset threshold ticks. Must be greater than
//!            1.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogSetResetThreshold(uint32_t ticks)
{
    uint32_t temp = HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWDT);
    temp &= ~HOSTMCU_AON_CFGWDT_THR_M;
    temp |= ((ticks << HOSTMCU_AON_CFGWDT_THR_S) & HOSTMCU_AON_CFGWDT_THR_M);
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWDT) = temp;
}

//*****************************************************************************
//
//! \brief Configures the timer to work in software mode.
//!
//! This function configures the timer to be operational during sleep and
//! wake-up. This requires to manually control the timer.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void WatchdogSetSwMode(void)
{
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_TMRSWCTL_SW;
}

//*****************************************************************************
//
//! \brief Sequence to start the timer.
//!
//! This function implements the sequence to start the timer as required by the
//! hardware.
//!
//! \return None
//
//*****************************************************************************
extern void WatchdogStartSequence(void);

//*****************************************************************************
//
//! \brief Sequence to stop the timer.
//!
//! This function implements the sequence to stop the timer as required by the
//! hardware.
//!
//! \return None
//
//*****************************************************************************
extern void WatchdogStopSequence(void);

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

#endif // ti_devices_watchdog__include
