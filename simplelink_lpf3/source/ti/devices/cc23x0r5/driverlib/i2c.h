/******************************************************************************
 *  Filename:       i2c.h
 *
 *  Description:    Prototypes and defines for the I2C API.
 *
 *  Copyright (c) 2022 Texas Instruments Incorporated
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

#ifndef __I2C_H__
#define __I2C_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup i2c_api
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

#include <stdbool.h>
#include <stdint.h>
#include "../inc/hw_types.h"
#include "../inc/hw_ints.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_i2c.h"
#include "debug.h"
#include "interrupt.h"
#include "cpu.h"

//*****************************************************************************
//
// I2C Controller commands
//
//*****************************************************************************
#define I2C_CONTROLLER_CMD_SINGLE_SEND              0x00000007
#define I2C_CONTROLLER_CMD_SINGLE_RECEIVE           0x00000007
#define I2C_CONTROLLER_CMD_BURST_SEND_START         0x00000003
#define I2C_CONTROLLER_CMD_BURST_SEND_CONT          0x00000001
#define I2C_CONTROLLER_CMD_BURST_SEND_FINISH        0x00000005
#define I2C_CONTROLLER_CMD_BURST_SEND_ERROR_STOP    0x00000004
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_START      0x0000000b
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT       0x00000009
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH     0x00000005
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_ERROR_STOP 0x00000004

//*****************************************************************************
//
// I2C Controller error status
//
//*****************************************************************************
#define I2C_CONTROLLER_ERR_NONE     0
#define I2C_CONTROLLER_ERR_ADDR_ACK 0x00000004
#define I2C_CONTROLLER_ERR_DATA_ACK 0x00000008
#define I2C_CONTROLLER_ERR_ARB_LOST 0x00000010

//*****************************************************************************
//
// I2C Target action requests
//
//*****************************************************************************
#define I2C_TARGET_ACT_NONE     0
#define I2C_TARGET_ACT_RREQ     0x00000001 // Controller has sent data
#define I2C_TARGET_ACT_TREQ     0x00000002 // Controller has requested data
#define I2C_TARGET_ACT_RREQ_FBR 0x00000005 // Controller has sent first byte

//*****************************************************************************
//
// I2C Target interrupts
//
//*****************************************************************************
#define I2C_TARGET_INT_STOP  0x00000004 // Stop Condition Interrupt.
#define I2C_TARGET_INT_START 0x00000002 // Start Condition Interrupt.
#define I2C_TARGET_INT_DATA  0x00000001 // Data Interrupt.

//*****************************************************************************
//
// I2C module clock frequency
//
//*****************************************************************************
#define I2C_CLK_FREQ 48000000 // Clock supplied to I2C periph in Hz

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

#ifdef DRIVERLIB_DEBUG
//*****************************************************************************
//
//! \internal
//!
//! \brief Checks an I2C base address.
//!
//! This function determines if a I2C port base address is valid.
//!
//! \param base is the base address of the I2C port.
//!
//! \return Returns \c true if the base address is valid and \c false
//! otherwise
//
//*****************************************************************************
static bool I2CBaseValid(uint32_t base)
{
    return (base == I2C0_BASE);
}
#endif

//*****************************************************************************
//
//! \brief Initializes the \I2C Controller module.
//!
//! This function initializes operation of the \I2C Controller module. Upon
//! successful initialization of the \I2C module, this function will have set the
//! bus speed for the controller, and will have enabled the \I2C Controller module.
//!
//! If the parameter \c fast is \c true, then the controller module will be set up
//! to transfer data at 400 kbps; otherwise, it will be set up to transfer data
//! at 100 kbps.
//!
//! \param base is the base address of the \I2C module.
//! \param fast set up for fast data transfers.
//!
//! \return None
//
//*****************************************************************************
extern void I2CControllerInitExpClk(uint32_t base, bool fast);

//*****************************************************************************
//
//! \brief Controls the state of the \I2C Controller module.
//!
//! This function is used to control the state of the Controller module send and
//! receive operations.
//!
//! \param base is the base address of the \I2C module.
//! \param cmd is the command to be issued by the \I2C Controller module
//! The parameter can be one of the following values:
//! - \ref I2C_CONTROLLER_CMD_SINGLE_SEND
//! - \ref I2C_CONTROLLER_CMD_SINGLE_RECEIVE
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_START
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_CONT
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_FINISH
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_ERROR_STOP
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_START
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_ERROR_STOP
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerCommand(uint32_t base, uint32_t cmd)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT((cmd == I2C_CONTROLLER_CMD_SINGLE_SEND) ||
           //     (cmd == I2C_CONTROLLER_CMD_SINGLE_RECEIVE) || -> Equal to SINGLE_SEND
           (cmd == I2C_CONTROLLER_CMD_BURST_SEND_START) || (cmd == I2C_CONTROLLER_CMD_BURST_SEND_CONT) ||
           (cmd == I2C_CONTROLLER_CMD_BURST_SEND_FINISH) || (cmd == I2C_CONTROLLER_CMD_BURST_SEND_ERROR_STOP) ||
           (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_START) || (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT) ||
           (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH) || (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_ERROR_STOP));

    // Send the command.
    HWREG(base + I2C_O_CCTL) = cmd;

    // Delay minimum four cycles in order to ensure that the I2C_O_CCTL
    // register has been correctly updated before function exit
    CPUDelay(2);
}

//*****************************************************************************
//
//! \brief Sets the address that the \I2C Controller will place on the bus.
//!
//! This function will set the address that the \I2C Controller will place on the
//! bus when initiating a transaction. When the \c receive parameter is set
//! to \b true, the address will indicate that the \I2C Controller is initiating a
//! read from the target; otherwise the address will indicate that the \I2C
//! Controller is initiating a write to the target.
//!
//! \param base is the base address of the \I2C module.
//! \param targetAddr is a 7-bit target address
//! \param receive flag indicates the type of communication with the target.
//! - \c true  : \I2C Controller is initiating a read from the target.
//! - \c false : \I2C Controller is initiating a write to the target.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerSetTargetAddr(uint32_t base, uint8_t targetAddr, bool receive)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT(!(targetAddr & 0x80));

    // Set the address of the target with which the controller will communicate.
    HWREG(base + I2C_O_CTA) = (targetAddr << 1) | receive;
}

//*****************************************************************************
//
//! \brief Enables the \I2C Controller module.
//!
//! This will enable operation of the \I2C Controller module.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerEnable(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Enable the clock for the controller.
    HWREG(base + I2C_O_CCR) |= I2C_CCR_CFE_M;

    // Enable the controller module.
    HWREG(base + I2C_O_CCTL) = I2C_CCTL_RUN_EN;
}

//*****************************************************************************
//
//! \brief Disables the \I2C controller module.
//!
//! This will disable operation of the \I2C controller module.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerDisable(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Disable the controller module.
    HWREG(base + I2C_O_CCTL) = 0;

    // Disable the clock for the controller.
    HWREG(base + I2C_O_CCR) &= ~I2C_CCR_CFE_M;
}

//*****************************************************************************
//
//! \brief Indicates whether or not the \I2C Controller is busy.
//!
//! This function returns an indication of whether or not the \I2C Controller is
//! busy transmitting or receiving data.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns status of \I2C Controller:
//! - \c true  : \I2C Controller is busy.
//! - \c false : \I2C Controller is not busy.
//
//*****************************************************************************
__STATIC_INLINE bool I2CControllerBusy(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Return the busy status.
    if (HWREG(base + I2C_O_CSTA) & I2C_CSTA_BUSY_M)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

//*****************************************************************************
//
//! \brief Indicates whether or not the \I2C bus is busy.
//!
//! This function returns an indication of whether or not the \I2C bus is busy.
//! This function can be used in a multi-controller environment to determine if
//! another controller is currently using the bus.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns status of the \I2C bus:
//! - \c true  : \I2C bus is busy.
//! - \c false : \I2C bus is not busy.
//
//*****************************************************************************
__STATIC_INLINE bool I2CControllerBusBusy(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Return the bus busy status.
    if (HWREG(base + I2C_O_CSTA) & I2C_CSTA_BUSBSY_M)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

//*****************************************************************************
//
//! \brief Receives a byte that has been sent to the \I2C Controller.
//!
//! This function reads a byte of data from the \I2C Controller Data Register.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns the byte received from by the \I2C Controller, cast as an
//! uint32_t.
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CControllerGetData(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Read a byte.
    return (HWREG(base + I2C_O_CDR));
}

//*****************************************************************************
//
//! \brief Transmits a byte from the \I2C Controller.
//!
//! This function will place the supplied data into \I2C Controller Data Register.
//!
//! \param base is the base address of the \I2C module.
//! \param data is the data to be transmitted by the \I2C Controller
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerPutData(uint32_t base, uint8_t data)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Write the byte.
    HWREG(base + I2C_O_CDR) = data;
}

//*****************************************************************************
//
//! \brief Gets the error status of the \I2C Controller module.
//!
//! This function is used to obtain the error status of the Controller module send
//! and receive operations.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns the error status of the Controller module:
//! - \ref I2C_CONTROLLER_ERR_NONE
//! - \ref I2C_CONTROLLER_ERR_ADDR_ACK
//! - \ref I2C_CONTROLLER_ERR_DATA_ACK
//! - \ref I2C_CONTROLLER_ERR_ARB_LOST
//
//*****************************************************************************
extern uint32_t I2CControllerError(uint32_t base);

//*****************************************************************************
//
//! \brief Enables the \I2C Controller interrupt.
//!
//! Enables the \I2C Controller interrupt source.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerEnableInt(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Enable the controller interrupt.
    HWREG(base + I2C_O_CIMR) = I2C_CIMR_IM;
}

//*****************************************************************************
//
//! \brief Disables the \I2C Controller interrupt.
//!
//! Disables the \I2C Controller interrupt source.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerDisableInt(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Disable the controller interrupt.
    HWREG(base + I2C_O_CIMR) = 0;
}

//*****************************************************************************
//
//! \brief Clears \I2C Controller interrupt sources.
//!
//! The \I2C Controller interrupt source is cleared, so that it no longer asserts.
//! This must be done in the interrupt handler to keep it from being called
//! again immediately upon exit.
//!
//! \note Due to write buffers and synchronizers in the system it may take several
//! clock cycles from a register write clearing an event in a module and until the
//! event is actually cleared in the NVIC of the system CPU. It is recommended to
//! clear the event source early in the interrupt service routine (ISR) to allow
//! the event clear to propagate to the NVIC before returning from the ISR.
//! At the same time, an early event clear allows new events of the same type to be
//! pended instead of ignored if the event is cleared later in the ISR.
//! It is the responsibility of the programmer to make sure that enough time has passed
//! before returning from the ISR to avoid false re-triggering of the cleared event.
//! A simple, although not necessarily optimal, way of clearing an event before
//! returning from the ISR is:
//! -# Write to clear event (interrupt source). (buffered write)
//! -# Dummy read from the event source module. (making sure the write has propagated)
//! -# Wait two system CPU clock cycles (user code or two NOPs). (allowing cleared event to propagate through any
//! synchronizers)
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerClearInt(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Clear the I2C controller interrupt source.
    HWREG(base + I2C_O_CICR) = I2C_CICR_IC;
}

//*****************************************************************************
//
//! \brief Gets the current \I2C Controller interrupt status.
//!
//! This returns the interrupt status for the \I2C Controller module. Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \param base is the base address of the \I2C Controller module.
//! \param masked selects either raw or masked interrupt status.
//! - \c false : Raw interrupt status is requested.
//! - \c true  : Masked interrupt status is requested.
//!
//! \return Returns the current interrupt status.
//! - \c true  : Active.
//! - \c false : Not active.
//
//*****************************************************************************
__STATIC_INLINE bool I2CControllerIntStatus(uint32_t base, bool masked)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Return either the interrupt status or the raw interrupt status as
    // requested.
    if (masked)
    {
        return ((HWREG(base + I2C_O_CMIS)) ? true : false);
    }
    else
    {
        return ((HWREG(base + I2C_O_CRIS)) ? true : false);
    }
}

//*****************************************************************************
//
//! \brief Enables the \I2C Target module.
//!
//! This will enable operation of the \I2C Target module.
//!
//! \param base is the base address of the \I2C Target module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetEnable(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Enable the clock to the target module.
    HWREG(base + I2C_O_CCR) |= I2C_CCR_TFE_M;

    // Enable the target.
    HWREG(base + I2C_O_TCTL) = I2C_TCTL_DA_EN;
}

//*****************************************************************************
//
//! \brief Initializes the \I2C Target module.
//!
//! This function initializes operation of the \I2C Target module. Upon
//! successful initialization of the \I2C module, this function will have set
//! the target address and have enabled the \I2C Target module.
//!
//! The parameter \c targetAddr is the value that will be compared against the
//! target address sent by an \I2C controller.
//!
//! \param base is the base address of the \I2C Target module.
//! \param targetAddr is the 7-bit target address.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetInit(uint32_t base, uint8_t targetAddr)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT(!(targetAddr & 0x80));

    // Must enable the device before doing anything else.
    I2CTargetEnable(base);

    // Set up the target address.
    HWREG(base + I2C_O_TOAR) = targetAddr;
}

//*****************************************************************************
//
//! \brief Sets the \I2C target address.
//!
//! This function writes the specified target address.
//!
//! \param base is the base address of the \I2C Target module.
//! \param targetAddr is the 7-bit target address
//!
//! \return None.
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetSetAddress(uint32_t base, uint8_t targetAddr)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT(!(targetAddr & 0x80));

    // Set up the primary target address.
    HWREG(base + I2C_O_TOAR) = targetAddr;
}

//*****************************************************************************
//
//! \brief Disables the \I2C target module.
//!
//! This will disable operation of the \I2C target module.
//!
//! \param base is the base address of the \I2C Target module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetDisable(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Disable the target.
    HWREG(base + I2C_O_TCTL) = 0x0;

    // Disable the clock to the target module.
    HWREG(base + I2C_O_CCR) &= ~I2C_CCR_TFE_M;
}

//*****************************************************************************
//
//! \brief Gets the \I2C Target module status.
//!
//! This function will return the action requested from a controller, if any.
//!
//! \param base is the base address of the \I2C Target module.
//!
//! \return Returns the status of the \I2C Target module:
//! - \ref I2C_TARGET_ACT_NONE : No action has been requested of the \I2C Target module.
//! - \ref I2C_TARGET_ACT_RREQ : An \I2C controller has sent data to the \I2C Target module.
//! - \ref I2C_TARGET_ACT_TREQ : An \I2C controller has requested that the \I2C Target module send data.
//! - \ref I2C_TARGET_ACT_RREQ_FBR : An \I2C controller has sent data to the \I2C target
//!        and the first byte following the target's own address has been received.
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CTargetStatus(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Return the target status.
    return (HWREG(base + I2C_O_TSTA));
}

//*****************************************************************************
//
//! \brief Receives a byte that has been sent to the \I2C Target.
//!
//! This function reads a byte of data from the \I2C Target Data Register.
//!
//! \param base is the base address of the \I2C Target module.
//!
//! \return Returns the byte received from by the \I2C Target, cast as an
//! uint32_t.
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CTargetGetData(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Read a byte.
    return (HWREG(base + I2C_O_TDR));
}

//*****************************************************************************
//
//! \brief Transmits a byte from the \I2C Target.
//!
//! This function will place the supplied data into \I2C Target Data Register.
//!
//! \param base is the base address of the \I2C Target module.
//! \param data data to be transmitted from the \I2C Target.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetPutData(uint32_t base, uint8_t data)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Write the byte.
    HWREG(base + I2C_O_TDR) = data;
}

//*****************************************************************************
//
//! \brief Enables individual \I2C Target interrupt sources.
//!
//! Enables the indicated \I2C Target interrupt sources. Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! \param base is the base address of the \I2C module.
//! \param intFlags is the bit mask of the target interrupt sources to be enabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_DATA
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetEnableInt(uint32_t base, uint32_t intFlags)
{
    uint32_t val;

    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT(intFlags & (I2C_TARGET_INT_STOP | I2C_TARGET_INT_START | I2C_TARGET_INT_DATA));

    // Enable the target interrupt.
    val = HWREG(base + I2C_O_TIMR);
    val |= intFlags;
    HWREG(base + I2C_O_TIMR) = val;
}

//*****************************************************************************
//
//! \brief Disables individual \I2C Target interrupt sources.
//!
//! Disables the indicated \I2C Target interrupt sources. Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! \param base is the base address of the \I2C Target module.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_DATA
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetDisableInt(uint32_t base, uint32_t intFlags)
{
    uint32_t val;

    // Check the arguments.
    ASSERT(I2CBaseValid(base));
    ASSERT(intFlags & (I2C_TARGET_INT_STOP | I2C_TARGET_INT_START | I2C_TARGET_INT_DATA));

    // Disable the target interrupt.
    val = HWREG(base + I2C_O_TIMR);
    val &= ~intFlags;
    HWREG(base + I2C_O_TIMR) = val;
}

//*****************************************************************************
//
//! \brief Clears \I2C Target interrupt sources.
//!
//! The specified \I2C Target interrupt sources are cleared, so that they no
//! longer assert. This must be done in the interrupt handler to keep it from
//! being called again immediately upon exit.
//!
//! \note Due to write buffers and synchronizers in the system it may take several
//! clock cycles from a register write clearing an event in a module and until the
//! event is actually cleared in the NVIC of the system CPU. It is recommended to
//! clear the event source early in the interrupt service routine (ISR) to allow
//! the event clear to propagate to the NVIC before returning from the ISR.
//! At the same time, an early event clear allows new events of the same type to be
//! pended instead of ignored if the event is cleared later in the ISR.
//! It is the responsibility of the programmer to make sure that enough time has passed
//! before returning from the ISR to avoid false re-triggering of the cleared event.
//! A simple, although not necessarily optimal, way of clearing an event before
//! returning from the ISR is:
//! -# Write to clear event (interrupt source). (buffered write)
//! -# Dummy read from the event source module. (making sure the write has propagated)
//! -# Wait two system CPU clock cycles (user code or two NOPs). (allowing cleared event to propagate through any
//! synchronizers)
//!
//! \param base is the base address of the \I2C module.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_DATA
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CTargetClearInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Clear the I2C target interrupt source.
    HWREG(base + I2C_O_TICR) = intFlags;
}

//*****************************************************************************
//
//! \brief Gets the current \I2C Target interrupt status.
//!
//! This returns the interrupt status for the \I2C Target module. Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \param base is the base address of the \I2C Target module.
//! \param masked selects either raw or masked interrupt status.
//! - \c false : Raw interrupt status is requested.
//! - \c true  : Masked interrupt status is requested.
//!
//! \return Returns the current interrupt status as an OR'ed combination of:
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_DATA
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CTargetIntStatus(uint32_t base, bool masked)
{
    // Check the arguments.
    ASSERT(I2CBaseValid(base));

    // Return either the interrupt status or the raw interrupt status as
    // requested.
    if (masked)
    {
        return (HWREG(base + I2C_O_TMIS));
    }
    else
    {
        return (HWREG(base + I2C_O_TRIS));
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

#endif // __I2C_H__
