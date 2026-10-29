/******************************************************************************
 *  Filename:       systimer.h
 *
 *  Description:    Defines and prototypes for SysTimer.
 *
 *  Copyright (c) 2025 Texas Instruments Incorporated
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

#ifndef ti_devices_systimer__include
#define ti_devices_systimer__include

//*****************************************************************************
//
//! \addtogroup system_control_group
//! \{
//! \addtogroup systimer_api
//! \{
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
#include <string.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_systim.h"
#include "debug.h"

//! Mask to retrieve the resolution config from the return value of \ref SysTimerGetChannelConfig().
#define SYSTIMER_CONFIG_RESOLUTION_M     (SYSTIM_CH0CFG_RES_M)
//! Resolution of 250 ns
#define SYSTIMER_CONFIG_RESOLUTION_250NS (SYSTIM_CH0CFG_RES_NS)
//! Resolution of 1 us
#define SYSTIMER_CONFIG_RESOLUTION_1US   (SYSTIM_CH0CFG_RES_US)

//! Mask to retrieve the mode config from the return value of \ref SysTimerGetChannelConfig().
#define SYSTIMER_CONFIG_MODE_M                  (SYSTIM_CH0CFG_MODE_M | SYSTIM_CH0CFG_REARM_M)
//! Continuous capture mode, where the channel is automatically re-armed after a capture.
#define SYSTIMER_CONFIG_MODE_CONTINUOUS_CAPTURE (SYSTIM_CH0CFG_MODE_CAPT | SYSTIM_CH0CFG_REARM_EN)
//! Capture mode, where the channel is not automatically re-armed after a capture.
#define SYSTIMER_CONFIG_MODE_CAPTURE            (SYSTIM_CH0CFG_MODE_CAPT | SYSTIM_CH0CFG_REARM_DIS)
#undef SYSTIMER_CONFIG_MODE_COMPARE // Compare mode is supported, but there is no mode field for it.
//! Idle mode, this should also be used when setting up a channel for compare mode.
#define SYSTIMER_CONFIG_MODE_IDLE (SYSTIM_CH0CFG_MODE_DIS | SYSTIM_CH0CFG_REARM_DIS)

//! Mask to retrieve the trigger config from the return value of \ref SysTimerGetChannelConfig().
#define SYSTIMER_CONFIG_TRIGGER_M (SYSTIM_CH0CFG_INP_M)
#undef SYSTIMER_CONFIG_TRIGGER_NEVER // Not supported on this device.
//! Trigger capture on falling edge.
#define SYSTIMER_CONFIG_TRIGGER_FALLING (SYSTIM_CH0CFG_INP_FALL)
//! Trigger capture on rising edge.
#define SYSTIMER_CONFIG_TRIGGER_RISING  (SYSTIM_CH0CFG_INP_RISE)
//! Trigger capture on both falling and rising edge.
#define SYSTIMER_CONFIG_TRIGGER_BOTH    (SYSTIM_CH0CFG_INP_BOTH)

//! Halt the SysTimer when the CPU is halted by the debugger.
#define SYSTIMER_DEBUG_CONFIG_HALT_STOP (SYSTIM_EMU_HALT_STOP)
//! The SysTimer will continue to run when the CPU is halted by the debugger.
#define SYSTIMER_DEBUG_CONFIG_HALT_RUN  (SYSTIM_EMU_HALT_RUN)

//! \brief The maximum distance into the future that a compare value can be set.
//!
//! The SysTimer will trigger a compare event immediately if the compare value
//! is less than 2^22 ticks in the past (~4.194 s at 1 us resolution or ~1.048 s
//! at 250 ns resolution). Therefore, the max number of ticks you
//! can schedule into the future is 2^32 - 2^22 - 1.
#define SYSTIMER_MAX_DELTA (0xFFBFFFFFU)

//! Number of SysTimer channels for this device.
#define SYSTIMER_CHANNEL_COUNT (5U)

// Add checks to ensure that the memory layout of the SysTimer is as assumed
// by the implementation of this module.

// Check that the SysTimer channel capture/compare registers are all placed in a
// contiguous sequence in memory without gaps and that the size of each
// register is 4 bytes.
#if (((SYSTIM_O_CH1CC - SYSTIM_O_CH0CC) != 4) || ((SYSTIM_O_CH2CC - SYSTIM_O_CH1CC) != 4) || \
     ((SYSTIM_O_CH3CC - SYSTIM_O_CH2CC) != 4) || ((SYSTIM_O_CH4CC - SYSTIM_O_CH3CC) != 4))
    #error The memory layout does not match the assumptions made in this module.
#endif

// Check that the SysTimer channel capture/compare shadow registers are all
// placed in a contiguous sequence in memory without gaps and that the size of
// each register is 4 bytes.
#if (((SYSTIM_O_CH1CCSR - SYSTIM_O_CH0CCSR) != 4) || ((SYSTIM_O_CH2CCSR - SYSTIM_O_CH1CCSR) != 4) || \
     ((SYSTIM_O_CH3CCSR - SYSTIM_O_CH2CCSR) != 4) || ((SYSTIM_O_CH4CCSR - SYSTIM_O_CH3CCSR) != 4))
    #error The memory layout does not match the assumptions made in this module.
#endif

// Check that the SysTimer channel configuration registers are all placed in a
// contiguous sequence in memory without gaps and that the size of each register
// is 4 bytes.
#if (((SYSTIM_O_CH1CFG - SYSTIM_O_CH0CFG) != 4) || ((SYSTIM_O_CH2CFG - SYSTIM_O_CH1CFG) != 4) || \
     ((SYSTIM_O_CH3CFG - SYSTIM_O_CH2CFG) != 4) || ((SYSTIM_O_CH4CFG - SYSTIM_O_CH3CFG) != 4))
    #error The memory layout does not match the assumptions made in this module.
#endif

// Check that the SysTimer event register bits are placed sequentially in the
// interrupt register without gaps.
#if (((SYSTIM_RIS_EV1_S - SYSTIM_RIS_EV0_S) != 1) || ((SYSTIM_RIS_EV2_S - SYSTIM_RIS_EV1_S) != 1) || \
     ((SYSTIM_RIS_EV3_S - SYSTIM_RIS_EV2_S) != 1) || ((SYSTIM_RIS_EV4_S - SYSTIM_RIS_EV3_S) != 1))
    #error The memory layout does not match the assumptions made in this module.
#endif

// Check that the SysTimer channel arm clear bits are placed sequentially in the
// arm clear register without gaps.
#if (((SYSTIM_ARMCLR_CH1_S - SYSTIM_ARMCLR_CH0_S) != 1) || ((SYSTIM_ARMCLR_CH2_S - SYSTIM_ARMCLR_CH1_S) != 1) || \
     ((SYSTIM_ARMCLR_CH3_S - SYSTIM_ARMCLR_CH2_S) != 1) || ((SYSTIM_ARMCLR_CH4_S - SYSTIM_ARMCLR_CH3_S) != 1))
    #error The memory layout does not match the assumptions made in this module.
#endif

//*****************************************************************************
//
//! \brief Get the current SysTimer time with a resolution of 1 us.
//!
//! \return The 32-bit slice of the SyTimer counter where the LSB bit represents
//!         1 us.
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTimerGetTime1Us(void)
{
    return HWREG(SYSTIM_BASE + SYSTIM_O_TIME1U);
}

//*****************************************************************************
//
//! \brief Get the current SysTimer time with a resolution of 250 ns.
//!
//! \return The 32-bit slice of the SyTimer counter where the LSB bit represents
//!         250 ns.
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTimerGetTime250Ns(void)
{
    return HWREG(SYSTIM_BASE + SYSTIM_O_TIME250N);
}

//*****************************************************************************
//
//! \brief Set the compare value for a given SysTimer channel.
//!
//! This will change the SysTimer channel to compare mode.
//!
//! \param channelNumber The SysTimer channel number to set the compare value
//!                      for.
//!
//! \param value The compare value to set.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerSetCompareValue(uint32_t channelNumber, uint32_t value)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_CH0CC + (channelNumber * sizeof(uint32_t))) = value;
}

//*****************************************************************************
//
//! \brief Get the current capture or compare value for a given SysTimer
//!        channel.
//!
//! \param channelNumber The SysConfig channel number to get the capture/compare
//!                      value for.
//!
//! \return If the channel is configured to be in compare mode, the compare
//! value is returned. If the channel is configured to be in capture mode, the
//! capture value is returned.
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTimerGetCaptureCompareValue(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    return HWREG(SYSTIM_BASE + SYSTIM_O_CH0CCSR + (channelNumber * sizeof(uint32_t)));
}

//*****************************************************************************
//
//! \brief Set the configuration of a given SysTimer channel.
//!
//! \note To configure the channel for compare mode, the
//! \ref SYSTIMER_CONFIG_MODE_IDLE config option should be used, and the channel
//! will then switch to compare mode when a compare value is set using
//! \ref SysTimerSetCompareValue().
//!
//! \param channelNumber The SysTimer channel number to set up
//!
//! \param config A bitwise OR of the following:
//!  - For channels supporting dynamically changing the resolution, one of the
//!    following:
//!    - \ref SYSTIMER_CONFIG_RESOLUTION_250NS
//!    - \ref SYSTIMER_CONFIG_RESOLUTION_1US
//!  - One of the following:
//!    - \ref SYSTIMER_CONFIG_MODE_CONTINUOUS_CAPTURE
//!    - \ref SYSTIMER_CONFIG_MODE_CAPTURE
//!    - \ref SYSTIMER_CONFIG_MODE_IDLE
//!  - If \ref SYSTIMER_CONFIG_MODE_CAPTURE or
//!    \ref SYSTIMER_CONFIG_MODE_CONTINUOUS_CAPTURE is used, one of the
//!    following:
//!    - \ref SYSTIMER_CONFIG_TRIGGER_FALLING
//!    - \ref SYSTIMER_CONFIG_TRIGGER_RISING
//!    - \ref SYSTIMER_CONFIG_TRIGGER_BOTH
//!
//! \return None
//!
//! \sa SysTimerSetCompareValue().
//
//*****************************************************************************
__STATIC_INLINE void SysTimerSetChannelConfig(uint32_t channelNumber, uint32_t config)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_CH0CFG + (channelNumber * sizeof(uint32_t))) = config;
}

//*****************************************************************************
//
//! \brief Get the current configuration for a given SysTimer channel.
//!
//! \param channelNumber The SysTimer channel number to get the config of.
//!
//! \return A bitwise OR of the following:
//!  - For channels supporting dynamically changing the resolution, one of the
//!    following:
//!    - \ref SYSTIMER_CONFIG_RESOLUTION_250NS
//!    - \ref SYSTIMER_CONFIG_RESOLUTION_1US
//!  - One of the following:
//!    - \ref SYSTIMER_CONFIG_MODE_CONTINUOUS_CAPTURE
//!    - \ref SYSTIMER_CONFIG_MODE_CAPTURE
//!    - \ref SYSTIMER_CONFIG_MODE_IDLE
//!  - And one of the following:
//!    - \ref SYSTIMER_CONFIG_TRIGGER_FALLING
//!    - \ref SYSTIMER_CONFIG_TRIGGER_RISING
//!    - \ref SYSTIMER_CONFIG_TRIGGER_BOTH
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTimerGetChannelConfig(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    return HWREG(SYSTIM_BASE + SYSTIM_O_CH0CFG + (channelNumber * sizeof(uint32_t)));
}

//*****************************************************************************
//
//! \brief Get the current resolution for a given SysTimer channel.
//!
//! \warning Only some channels support dynamically changing the resolution.
//!          This API must only be used for those channels.
//!
//! \param channelNumber The SysTimer channel number to get the
//! resolution of.
//!
//! \return One of the following:
//! - \ref SYSTIMER_CONFIG_RESOLUTION_250NS
//! - \ref SYSTIMER_CONFIG_RESOLUTION_1US
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTimerGetChannelResolution(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    return SysTimerGetChannelConfig(channelNumber) & SYSTIMER_CONFIG_RESOLUTION_M;
}

//*****************************************************************************
//
//! \brief Enable interrupt for a specific channel.
//!
//! \param channelNumber The SysTimer channel number to enable interrupts
//! for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerEnableInterrupt(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_IMSET) = 1 << (SYSTIM_IMSET_EV0_S + channelNumber);
}

//*****************************************************************************
//
//! \brief Disable interrupt for a specific channel.
//!
//! \param channelNumber The SysTimer channel number to disable
//! interrupts for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerDisableInterrupt(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_IMCLR) = 1 << (SYSTIM_IMCLR_EV0_S + channelNumber);
}

//*****************************************************************************
//
//! \brief Clear the interrupt flag for a specific channel.
//!
//! \param channelNumber The SysTimer channel number to clear the
//! interrupt flag for.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerClearInterrupt(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_ICLR) = 1 << (SYSTIM_ICLR_EV0_S + channelNumber);
}

//*****************************************************************************
//
//! \brief Disarm a specific channel.
//!
//! \param channelNumber The SysTimer channel number to disarm.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerDisarmChannel(uint32_t channelNumber)
{
    ASSERT(channelNumber < SYSTIMER_CHANNEL_COUNT);
    HWREG(SYSTIM_BASE + SYSTIM_O_ARMCLR) = 1 << (SYSTIM_ARMCLR_CH0_S + channelNumber);
}

//*****************************************************************************
//
//! \brief Setup the debug config for the SysTimer.
//!
//! \param debugConfig One of the following:
//!  - \ref SYSTIMER_DEBUG_CONFIG_HALT_STOP
//!  - \ref SYSTIMER_DEBUG_CONFIG_HALT_RUN
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTimerSetDebugConfig(uint32_t debugConfig)
{
    HWREG(SYSTIM_BASE + SYSTIM_O_EMU) = debugConfig;
}

//*****************************************************************************
//
//! \brief Check if the 1 us time slice of SysTimer has wrapped around.
//!
//! \return true: if the 1 us time slice has wrapped around.
//!         false: otherwise
//!
//! \sa SysTimerClearWrapAroundStatus1Us()
//
//*****************************************************************************
__STATIC_INLINE bool SysTimerGetWrapAroundStatus1Us(void)
{
    if ((HWREG(SYSTIM_BASE + SYSTIM_O_RIS) & SYSTIM_RIS_OVFL_M) != 0)
    {
        return true; // Wrap around has occurred
    }
    else
    {
        return false; // No wrap around
    }
}

//*****************************************************************************
//
//! \brief Clear the 1 us time slice wrap around status of SysTimer.
//!
//! The \ref SysTimerGetWrapAroundStatus1Us() function will return false after
//! calling this function, unless a new wrap around occurs in the mean time.
//!
//! \return None
//!
//! \sa SysTimerGetWrapAroundStatus1Us()
//
//*****************************************************************************
__STATIC_INLINE void SysTimerClearWrapAroundStatus1Us(void)
{
    HWREG(SYSTIM_BASE + SYSTIM_O_ICLR) = SYSTIM_ICLR_OVFL_CLR;
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
//! \}
//! \}
//
//*****************************************************************************

#endif // ti_devices_systimer__include
