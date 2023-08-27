
/******************************************************************************
 *  Filename:       uart.h
 *
 *  Description:    Defines and prototypes for the UART peripheral.
 *
 *  Copyright (c) 2022-2024 Texas Instruments Incorporated
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

#ifndef __UART_H__
#define __UART_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup uart_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "../inc/hw_types.h"
#include "../inc/hw_uart.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_ints.h"
#include "interrupt.h"
#include "debug.h"

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
// Values that can be passed to UARTEnableInt, UARTDisableInt, and UARTClearInt
// as the intFlags parameter, and returned from UARTIntStatus.
//
//*****************************************************************************
#define UART_INT_EOT       (UART_IMSC_EOT)       //!< End Of Transmission Interrupt Mask
#define UART_INT_OE        (UART_IMSC_OE)        //!< Overrun Error Interrupt Mask
#define UART_INT_BE        (UART_IMSC_BE)        //!< Break Error Interrupt Mask
#define UART_INT_PE        (UART_IMSC_PE)        //!< Parity Error Interrupt Mask
#define UART_INT_FE        (UART_IMSC_FE)        //!< Framing Error Interrupt Mask
#define UART_INT_RT        (UART_IMSC_RT)        //!< Receive Timeout Interrupt Mask
#define UART_INT_RX        (UART_IMSC_RX)        //!< Receive Interrupt Mask
#define UART_INT_TX        (UART_IMSC_TX)        //!< Transmit Interrupt Mask
#define UART_INT_CTS       (UART_IMSC_CTSM)      //!< CTS Modem Interrupt Mask
#define UART_INT_TXDMADONE (UART_IMSC_TXDMADONE) //!< Tx DMA done interrupt mask
#define UART_INT_RXDMADONE (UART_IMSC_RXDMADONE) //!< Rx DMA done interrupt mask

//*****************************************************************************
//
// Values that can be passed to UARTConfigSetExpClk as the config parameter
// and returned by UARTConfigGetExpClk in the pconfig parameter.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK 0x00000060 //!< Mask for extracting word length
#define UART_CONFIG_WLEN_8    0x00000060 //!< 8 bit data
#define UART_CONFIG_WLEN_7    0x00000040 //!< 7 bit data
#define UART_CONFIG_WLEN_6    0x00000020 //!< 6 bit data
#define UART_CONFIG_WLEN_5    0x00000000 //!< 5 bit data
#define UART_CONFIG_STOP_MASK 0x00000008 //!< Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE  0x00000000 //!< One stop bit
#define UART_CONFIG_STOP_TWO  0x00000008 //!< Two stop bits
#define UART_CONFIG_PAR_MASK  0x00000086 //!< Mask for extracting parity
#define UART_CONFIG_PAR_NONE  0x00000000 //!< No parity
#define UART_CONFIG_PAR_EVEN  0x00000006 //!< Even parity
#define UART_CONFIG_PAR_ODD   0x00000002 //!< Odd parity
#define UART_CONFIG_PAR_ONE   0x00000082 //!< Parity bit is one
#define UART_CONFIG_PAR_ZERO  0x00000086 //!< Parity bit is zero

//*****************************************************************************
//
// Values that can be passed to UARTSetFifoLevel as the txLevel parameter
//
//*****************************************************************************
#define UART_FIFO_TX2_8 0x00000001 //!< Transmit interrupt at 1/4 Full
#define UART_FIFO_TX4_8 0x00000002 //!< Transmit interrupt at 1/2 Full
#define UART_FIFO_TX6_8 0x00000003 //!< Transmit interrupt at 3/4 Full

//*****************************************************************************
//
// Values that can be passed to UARTSetFifoLevel as the rxLevel parameter
//
//*****************************************************************************
#define UART_FIFO_RX2_8 0x00000008 //!< Receive interrupt at 1/4 Full
#define UART_FIFO_RX4_8 0x00000010 //!< Receive interrupt at 1/2 Full
#define UART_FIFO_RX6_8 0x00000018 //!< Receive interrupt at 3/4 Full

//*****************************************************************************
//
// Values that can be passed to UARTEnableDMA() and UARTDisableDMA().
//
//*****************************************************************************
#define UART_DMA_ERR_RXSTOP 0x00000004 //!< Stop DMA receive if UART error
#define UART_DMA_TX         0x00000002 //!< Enable DMA for transmit
#define UART_DMA_RX         0x00000001 //!< Enable DMA for receive

//*****************************************************************************
//
// Values returned from UARTGetRxError().
//
//*****************************************************************************
#define UART_RXERROR_OVERRUN 0x00000008
#define UART_RXERROR_BREAK   0x00000004
#define UART_RXERROR_PARITY  0x00000002
#define UART_RXERROR_FRAMING 0x00000001

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Sets the FIFO level at which interrupts are generated.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \param base is the base address of the UART port.
//! \param txLevel is the transmit FIFO interrupt level, specified as one of:
//! - \ref UART_FIFO_TX2_8
//! - \ref UART_FIFO_TX4_8
//! - \ref UART_FIFO_TX6_8
//! \param rxLevel is the receive FIFO interrupt level, specified as one of:
//! - \ref UART_FIFO_RX2_8
//! - \ref UART_FIFO_RX4_8
//! - \ref UART_FIFO_RX6_8
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTSetFifoLevel(uint32_t base, uint32_t txLevel, uint32_t rxLevel)
{
    // Check the arguments.
    ASSERT((txLevel == UART_FIFO_TX2_8) || (txLevel == UART_FIFO_TX4_8) || (txLevel == UART_FIFO_TX6_8));
    ASSERT((rxLevel == UART_FIFO_RX2_8) || (rxLevel == UART_FIFO_RX4_8) || (rxLevel == UART_FIFO_RX6_8));

    // Set the FIFO interrupt levels.
    HWREG(base + UART_O_IFLS) = txLevel | rxLevel;
}

//*****************************************************************************
//
//! \brief Sets the configuration of a UART.
//!
//! This function configures the UART for operation in the specified data
//! format.
//!
//! \param base is the base address of the UART port.
//! \param UARTClkFreq is the rate of the clock supplied to the UART module.
//! \param baudFreq is the desired baud rate.
//! - Minimum baud rate: baudFreq >= ceil(UARTClkFreq / 1,048,559.875)
//! - Maximum baud rate: baudFreq <= floor(UARTClkFreq / 15.875)
//! \param config is the data format for the port.
//! The parameter is the bitwise OR of three values:
//! - Number of data bits
//!   - \ref UART_CONFIG_WLEN_8 : 8 data bits per byte.
//!   - \ref UART_CONFIG_WLEN_7 : 7 data bits per byte.
//!   - \ref UART_CONFIG_WLEN_6 : 6 data bits per byte.
//!   - \ref UART_CONFIG_WLEN_5 : 5 data bits per byte.
//! - Number of stop bits
//!   - \ref UART_CONFIG_STOP_ONE : One stop bit.
//!   - \ref UART_CONFIG_STOP_TWO : Two stop bits.
//! - Parity
//!   - \ref UART_CONFIG_PAR_NONE
//!   - \ref UART_CONFIG_PAR_EVEN
//!   - \ref UART_CONFIG_PAR_ODD
//!   - \ref UART_CONFIG_PAR_ONE
//!   - \ref UART_CONFIG_PAR_ZERO
//!
//! \return None
//
//*****************************************************************************
extern void UARTConfigSetExpClk(uint32_t base, uint32_t UARTClkFreq, uint32_t baudFreq, uint32_t config);

//*****************************************************************************
//
//! \brief Disables transmitting and receiving.
//!
//! This function waits until all data in the TX FIFO has been transmitted,
//! and then clears the UARTEN, TXE, and RXE bits, and disables the FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
extern void UARTDisable(uint32_t base);

//*****************************************************************************
//
//! \brief Enables the transmit and receive FIFOs.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTEnableFifo(uint32_t base)
{
    // Enable the FIFO.
    HWREG(base + UART_O_LCRH) |= UART_LCRH_FEN;
}

//*****************************************************************************
//
//! \brief Disables the transmit and receive FIFOs.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTDisableFIFO(uint32_t base)
{
    // Disable the FIFO.
    HWREG(base + UART_O_LCRH) &= ~(UART_LCRH_FEN);
}

//*****************************************************************************
//
//! \brief Determines if there are any characters in the receive FIFO.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns status of the receive FIFO.
//! - \c true  : There is data in the receive FIFO.
//! - \c false : There is no data in the receive FIFO.
//
//*****************************************************************************
__STATIC_INLINE bool UARTCharAvailable(uint32_t base)
{
    // Return the availability of characters.
    return ((HWREG(base + UART_O_FR) & UART_FR_RXFE) ? false : true);
}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! This function gets a character from the receive FIFO for the specified
//! port.
//!
//! \note The \ref UARTCharAvailable() function should be called before
//! attempting to call this function.
//!
//! \param[in] base is the base address of the UART port.
//!
//! \return Returns the character read from the specified port
//!
//! \sa \ref UARTCharAvailable()
//
//*****************************************************************************
__STATIC_INLINE uint8_t UARTGetCharNonBlocking(uint32_t base)
{
    // Return a character from the data register
    return (HWREGB(base + UART_O_DR));
}

//*****************************************************************************
//
//! \brief Waits for a character from the specified port.
//!
//! This function gets a character from the receive FIFO for the specified
//! port. If there are no characters available, this function waits until a
//! character is received before returning.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns the character read from the specified port
//
//*****************************************************************************
extern uint8_t UARTGetChar(uint32_t base);

//*****************************************************************************
//
//! \brief Determines if there is any space in the transmit FIFO.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns status of the transmit FIFO.
//! - \c true  : There is space available in the transmit FIFO.
//! - \c false : There is no space available in the transmit FIFO.
//
//*****************************************************************************
__STATIC_INLINE bool UARTSpaceAvailable(uint32_t base)
{
    // Return the availability of space.
    return ((HWREG(base + UART_O_FR) & UART_FR_TXFF) ? false : true);
}

//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! This function writes the character \c data to the transmit FIFO for the
//! specified port.
//!
//! \note The \ref UARTSpaceAvailable() function should be called before
//! attempting to call this function.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! \return None
//!
//! \sa \ref UARTSpaceAvailable()
//
//*****************************************************************************
__STATIC_INLINE void UARTPutCharNonBlocking(uint32_t base, uint8_t data)
{
    // Write this character to the transmit FIFO.
    HWREG(base + UART_O_DR) = data;
}

//*****************************************************************************
//
//! \brief Waits to send a character to the specified port.
//!
//! This function sends the character \c data to the transmit FIFO for the
//! specified port. If there is no space available in the transmit FIFO, this
//! function waits until there is space available before returning.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! \return None
//
//*****************************************************************************
extern void UARTPutChar(uint32_t base, uint8_t data);

//*****************************************************************************
//
//! \brief Determines whether the UART transmitter is busy or not.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware. If \c false is returned, the transmit FIFO is
//! empty and all bits of the last transmitted character, including all stop
//! bits, have left the hardware shift register.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns status of UART transmitter.
//! - \c true  : UART is transmitting.
//! - \c false : All transmissions are complete.
//
//*****************************************************************************
__STATIC_INLINE bool UARTBusy(uint32_t base)
{
    // Determine if the UART is busy.
    return ((HWREG(base + UART_O_FR) & UART_FR_BUSY) ? true : false);
}

//*****************************************************************************
//
//! \brief Enables individual UART interrupt sources.
//!
//! This function enables the indicated UART interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref UART_INT_EOT         : End Of Transmission interrupt.
//! - \ref UART_INT_OE          : Overrun Error interrupt.
//! - \ref UART_INT_BE          : Break Error interrupt.
//! - \ref UART_INT_PE          : Parity Error interrupt.
//! - \ref UART_INT_FE          : Framing Error interrupt.
//! - \ref UART_INT_RT          : Receive Timeout interrupt.
//! - \ref UART_INT_TX          : Transmit interrupt.
//! - \ref UART_INT_RX          : Receive interrupt.
//! - \ref UART_INT_CTS         : CTS interrupt.
//! - \ref UART_INT_TXDMADONE   : TX DMA Done interrupt.
//! - \ref UART_INT_RXDMADONE   : RX DMA Done interrupt.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTEnableInt(uint32_t base, uint32_t intFlags)
{
    // Enable the specified interrupts.
    HWREG(base + UART_O_IMSC) |= intFlags;
}

//*****************************************************************************
//
//! \brief Disables individual UART interrupt sources.
//!
//! This function disables the indicated UART interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//! - \ref UART_INT_EOT         : End Of Transmission interrupt.
//! - \ref UART_INT_OE          : Overrun Error interrupt.
//! - \ref UART_INT_BE          : Break Error interrupt.
//! - \ref UART_INT_PE          : Parity Error interrupt.
//! - \ref UART_INT_FE          : Framing Error interrupt.
//! - \ref UART_INT_RT          : Receive Timeout interrupt.
//! - \ref UART_INT_TX          : Transmit interrupt.
//! - \ref UART_INT_RX          : Receive interrupt.
//! - \ref UART_INT_CTS         : CTS interrupt.
//! - \ref UART_INT_TXDMADONE   : TX DMA Done interrupt.
//! - \ref UART_INT_RXDMADONE   : RX DMA Done interrupt.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTDisableInt(uint32_t base, uint32_t intFlags)
{
    // Disable the specified interrupts.
    HWREG(base + UART_O_IMSC) &= ~(intFlags);
}

//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! This function returns the interrupt status for the specified UART. Either
//! the raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \param base is the base address of the UART port.
//! \param masked selects either raw or masked interrupt.
//! - \c true  : Masked interrupt status is required.
//! - \c false : Raw interrupt status is required.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of:
//! - \ref UART_INT_EOT         : End Of Transmission interrupt.
//! - \ref UART_INT_OE          : Overrun Error interrupt.
//! - \ref UART_INT_BE          : Break Error interrupt.
//! - \ref UART_INT_PE          : Parity Error interrupt.
//! - \ref UART_INT_FE          : Framing Error interrupt.
//! - \ref UART_INT_RT          : Receive Timeout interrupt.
//! - \ref UART_INT_TX          : Transmit interrupt.
//! - \ref UART_INT_RX          : Receive interrupt.
//! - \ref UART_INT_CTS         : CTS interrupt.
//! - \ref UART_INT_TXDMADONE   : TX DMA Done interrupt.
//! - \ref UART_INT_RXDMADONE   : RX DMA Done interrupt.
//
//*****************************************************************************
__STATIC_INLINE uint32_t UARTIntStatus(uint32_t base, bool masked)
{
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    if (masked)
    {
        return (HWREG(base + UART_O_MIS));
    }
    else
    {
        return (HWREG(base + UART_O_RIS));
    }
}

//*****************************************************************************
//
//! \brief Clears UART interrupt sources.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert. This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
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
//! \param base is the base address of the UART port.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//! - \ref UART_INT_EOT         : End Of Transmission interrupt.
//! - \ref UART_INT_OE          : Overrun Error interrupt.
//! - \ref UART_INT_BE          : Break Error interrupt.
//! - \ref UART_INT_PE          : Parity Error interrupt.
//! - \ref UART_INT_FE          : Framing Error interrupt.
//! - \ref UART_INT_RT          : Receive Timeout interrupt.
//! - \ref UART_INT_TX          : Transmit interrupt.
//! - \ref UART_INT_RX          : Receive interrupt.
//! - \ref UART_INT_CTS         : CTS interrupt.
//! - \ref UART_INT_TXDMADONE   : TX DMA Done interrupt.
//! - \ref UART_INT_RXDMADONE   : RX DMA Done interrupt.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTClearInt(uint32_t base, uint32_t intFlags)
{
    // Clear the requested interrupt sources
    HWREG(base + UART_O_ICR) = intFlags;
}

//*****************************************************************************
//
//! \brief Enable UART DMA operation.
//!
//! The specified UART DMA features are enabled. The UART can be
//! configured to use DMA for transmit or receive, and to disable
//! receive if an error occurs.
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the UART.
//!
//! \param base is the base address of the UART port.
//! \param dmaFlags is a bit mask of the DMA features to enable.
//! The parameter is the bitwise OR of any of the following values:
//! - UART_DMA_RX         : Enable DMA for receive.
//! - UART_DMA_TX         : Enable DMA for transmit.
//! - UART_DMA_ERR_RXSTOP : Disable DMA receive on UART error.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTEnableDMA(uint32_t base, uint32_t dmaFlags)
{
    // Set the requested bits in the UART DMA control register.
    HWREG(base + UART_O_DMACTL) |= dmaFlags;
}

//*****************************************************************************
//
//! \brief Disable UART DMA operation.
//!
//! This function is used to disable UART DMA features that were enabled
//! by \ref UARTEnableDMA(). The specified UART DMA features are disabled.
//!
//! \param base is the base address of the UART port.
//! \param dmaFlags is a bit mask of the DMA features to disable.
//! The parameter is the bitwise OR of any of the following values:
//! - UART_DMA_RX         : Enable DMA for receive.
//! - UART_DMA_TX         : Enable DMA for transmit.
//! - UART_DMA_ERR_RXSTOP : Disable DMA receive on UART error.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTDisableDMA(uint32_t base, uint32_t dmaFlags)
{
    // Clear the requested bits in the UART DMA control register.
    HWREG(base + UART_O_DMACTL) &= ~dmaFlags;
}

//*****************************************************************************
//
//! \brief Gets current receiver errors.
//!
//! This function returns the current state of each of the 4 receiver error
//! sources. The returned errors are equivalent to the four error bits
//! returned via the previous call to \ref UARTGetChar() or \ref UARTGetCharNonBlocking()
//! with the exception that the overrun error is set immediately the overrun
//! occurs rather than when a character is next read.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns a bitwise OR combination of the receiver error flags:
//! - \ref UART_RXERROR_FRAMING
//! - \ref UART_RXERROR_PARITY
//! - \ref UART_RXERROR_BREAK
//! - \ref UART_RXERROR_OVERRUN
//
//*****************************************************************************
__STATIC_INLINE uint32_t UARTGetRxError(uint32_t base)
{
    // Return the current value of the receive status register.
    return (HWREG(base + UART_O_RSR_ECR) & 0x0000000F);
}

//*****************************************************************************
//
//! \brief Clears all reported receiver errors.
//!
//! This function is used to clear all receiver error conditions reported via
//! \ref UARTGetRxError(). If using the overrun, framing error, parity error or
//! break interrupts, this function must be called after clearing the interrupt
//! to ensure that later errors of the same type trigger another interrupt.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTClearRxError(uint32_t base)
{
    // Any write to the Error Clear Register will clear all bits which are
    // currently set.
    HWREG(base + UART_O_RSR_ECR) = 0;
}

//*****************************************************************************
//
//! \brief Enable CTS flow control
//!
//! Hardware flow control is disabled by default.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTEnableCTS(uint32_t base)
{
    HWREG(base + UART_O_CTL) |= (UART_CTL_CTSEN);
}

//*****************************************************************************
//
//! \brief Enable RTS flow control
//!
//! Hardware flow control is disabled by default.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTEnableRTS(uint32_t base)
{
    HWREG(base + UART_O_CTL) |= (UART_CTL_RTSEN);
}

//*****************************************************************************
//
//! \brief Disable CTS flow control
//!
//! Hardware flow control is disabled by default.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTDisableCTS(uint32_t base)
{
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_CTSEN);
}

//*****************************************************************************
//
//! \brief Disable RTS flow control
//!
//! Hardware flow control is disabled by default.
//!
//! \param base is the base address of the UART port.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void UARTDisableRTS(uint32_t base)
{
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_RTSEN);
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

#endif //  __UART_H__
