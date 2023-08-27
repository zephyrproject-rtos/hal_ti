/******************************************************************************
 *  Filename:       gpio.h
 *
 *  Description:    Defines and prototypes for the GPIO.
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

#ifndef __GPIO_H__
#define __GPIO_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! @{
//! \addtogroup gpio_api
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
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_gpio.h"
#include "debug.h"

//*****************************************************************************
//
// Check for legal range of variable dioNumber
//
//*****************************************************************************
#ifdef DRIVERLIB_DEBUG
    #include "chipinfo.h"

static bool dioNumberLegal(uint32_t dioNumber)
{
    // TODO: Implement properly
    // Get number of GPIOs supported by platform. Number of DIOs is NUMDIO + 1.
    // Actual number available may be less for some package types.
    uint32_t numDio = 1 + ((HWREG(GPIO_BASE + GPIO_O_DESCEX) & GPIO_DESCEX_NUMDIO_M) >> GPIO_DESCEX_NUMDIO_S);
    return (dioNumber < numDio);
}
#endif

//*****************************************************************************
//
// The following values define the bit field for the GPIO DIOs.
//
//*****************************************************************************
#define GPIO_DIO_0_MASK   0x00000001 // GPIO DIO 0 mask
#define GPIO_DIO_1_MASK   0x00000002 // GPIO DIO 1 mask
#define GPIO_DIO_2_MASK   0x00000004 // GPIO DIO 2 mask
#define GPIO_DIO_3_MASK   0x00000008 // GPIO DIO 3 mask
#define GPIO_DIO_4_MASK   0x00000010 // GPIO DIO 4 mask
#define GPIO_DIO_5_MASK   0x00000020 // GPIO DIO 5 mask
#define GPIO_DIO_6_MASK   0x00000040 // GPIO DIO 6 mask
#define GPIO_DIO_7_MASK   0x00000080 // GPIO DIO 7 mask
#define GPIO_DIO_8_MASK   0x00000100 // GPIO DIO 8 mask
#define GPIO_DIO_9_MASK   0x00000200 // GPIO DIO 9 mask
#define GPIO_DIO_10_MASK  0x00000400 // GPIO DIO 10 mask
#define GPIO_DIO_11_MASK  0x00000800 // GPIO DIO 11 mask
#define GPIO_DIO_12_MASK  0x00001000 // GPIO DIO 12 mask
#define GPIO_DIO_13_MASK  0x00002000 // GPIO DIO 13 mask
#define GPIO_DIO_14_MASK  0x00004000 // GPIO DIO 14 mask
#define GPIO_DIO_15_MASK  0x00008000 // GPIO DIO 15 mask
#define GPIO_DIO_16_MASK  0x00010000 // GPIO DIO 16 mask
#define GPIO_DIO_17_MASK  0x00020000 // GPIO DIO 17 mask
#define GPIO_DIO_18_MASK  0x00040000 // GPIO DIO 18 mask
#define GPIO_DIO_19_MASK  0x00080000 // GPIO DIO 19 mask
#define GPIO_DIO_20_MASK  0x00100000 // GPIO DIO 20 mask
#define GPIO_DIO_21_MASK  0x00200000 // GPIO DIO 21 mask
#define GPIO_DIO_22_MASK  0x00400000 // GPIO DIO 22 mask
#define GPIO_DIO_23_MASK  0x00800000 // GPIO DIO 23 mask
#define GPIO_DIO_24_MASK  0x01000000 // GPIO DIO 24 mask
#define GPIO_DIO_25_MASK  0x02000000 // GPIO DIO 25 mask
#define GPIO_DIO_ALL_MASK 0xFFFFFFFF // GPIO all DIOs mask

//*****************************************************************************
//
// Define constants that shall be passed as the outputEnableValue parameter to
// GPIOSetOutputEnableDio() and will be returned from the function
// GPIOGetOutputEnableDio().
//
//*****************************************************************************
#define GPIO_OUTPUT_DISABLE 0x00000000 // DIO output is disabled
#define GPIO_OUTPUT_ENABLE  0x00000001 // DIO output is enabled

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Reads a specific DIO.
//!
//! \param dioNumber specifies the DIO to read (0-31).
//!
//! \return Returns 0 or 1 reflecting the input value of the specified DIO.
//!
//! \sa \ref GPIOReadMultiDio(), \ref GPIOWriteDio(), \ref GPIOWriteMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOReadDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Return the input value from the specified DIO.
    return ((HWREG( GPIO_BASE + GPIO_O_DIN31_0 ) >> dioNumber) & 1);
}

//*****************************************************************************
//
//! \brief Reads the input value for the specified DIOs.
//!
//! This function returns the input value for multiple DIOs.
//! The value returned is not shifted and hence matches the corresponding dioMask bits.
//!
//! \param dioMask is the bit-mask representation of the DIOs to read.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return Returns a bit vector reflecting the input value of the corresponding DIOs.
//! - 0 : Corresponding DIO is low.
//! - 1 : Corresponding DIO is high.
//!
//! \sa \ref GPIOReadDio(), \ref GPIOWriteDio(), \ref GPIOWriteMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOReadMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Return the input value from the specified DIOs.
    return (HWREG( GPIO_BASE + GPIO_O_DIN31_0 ) & dioMask);
}

//*****************************************************************************
//
//! \brief Writes a value to a specific DIO.
//!
//! \param dioNumber specifies the DIO to update (0-31).
//! \param value specifies the value to write
//! - 0 : Logic zero (low)
//! - 1 : Logic one (high)
//!
//! \return None
//!
//! \sa \ref GPIOWriteMultiDio(), \ref GPIOReadDio(), \ref GPIOReadMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOWriteDio(uint32_t dioNumber, uint32_t value)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));
    ASSERT((value == 0) || (value == 1));

    // Write 0 or 1 to the byte indexed DOUT map
    HWREGB( GPIO_BASE + GPIO_O_DOUT3_0 + dioNumber ) = value;
}

//*****************************************************************************
//
//! \brief Writes masked data to the specified DIOs.
//!
//! Enables for writing multiple bits simultaneously.
//! The value to write must be shifted so it matches the corresponding dioMask bits.
//!
//! \note Note that this is a read-modify-write operation and hence not atomic.
//!
//! \param dioMask is the bit-mask representation of the DIOs to write.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//! \param bitVectoredValue holds the value to be written to the corresponding DIO-bits.
//!
//! \return None
//!
//! \sa \ref GPIOWriteDio(), \ref GPIOReadDio(), \ref GPIOReadMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOWriteMultiDio(uint32_t dioMask, uint32_t bitVectoredValue)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    HWREG( GPIO_BASE + GPIO_O_DOUT31_0 ) = (HWREG( GPIO_BASE + GPIO_O_DOUT31_0 ) & ~dioMask) |
                                            (bitVectoredValue & dioMask);
}

//*****************************************************************************
//
//! \brief Sets a specific DIO to 1 (high).
//!
//! \param dioNumber specifies the DIO to set (0-31).
//!
//! \return None
//!
//! \sa \ref GPIOSetMultiDio(), \ref GPIOClearDio(), \ref GPIOClearMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOSetDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Set the specified DIO.
    HWREG( GPIO_BASE + GPIO_O_DOUTSET31_0 ) = (1 << dioNumber);
}

//*****************************************************************************
//
//! \brief Sets the specified DIOs to 1 (high).
//!
//! \param dioMask is the bit-mask representation of the DIOs to set.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return None
//!
//! \sa \ref GPIOSetDio(), \ref GPIOClearDio(), \ref GPIOClearMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOSetMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Set the DIOs.
    HWREG( GPIO_BASE + GPIO_O_DOUTSET31_0 ) = dioMask;
}

//*****************************************************************************
//
//! \brief Clears a specific DIO to 0 (low).
//!
//! \param dioNumber specifies the DIO to clear (0-31).
//!
//! \return None
//!
//! \sa \ref GPIOClearMultiDio(), \ref GPIOSetDio(), \ref GPIOSetMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOClearDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Clear the specified DIO.
    HWREG( GPIO_BASE + GPIO_O_DOUTCLR31_0 ) = (1 << dioNumber);
}

//*****************************************************************************
//
//! \brief Clears the specified DIOs to 0 (low).
//!
//! \param dioMask is the bit-mask representation of the DIOs to clear.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return None
//!
//! \sa \ref GPIOClearDio(), \ref GPIOSetDio(), \ref GPIOSetMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOClearMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Clear the DIOs.
    HWREG( GPIO_BASE + GPIO_O_DOUTCLR31_0 ) = dioMask;
}

//*****************************************************************************
//
//! \brief Toggles a specific DIO.
//!
//! \param dioNumber specifies the DIO to toggle (0-31).
//!
//! \return None
//!
//! \sa \ref GPIOToggleMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOToggleDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Toggle the specified DIO.
    HWREG( GPIO_BASE + GPIO_O_DOUTTGL31_0 ) = (1 << dioNumber);
}

//*****************************************************************************
//
//! \brief Toggles the specified DIOs.
//!
//! \param dioMask is the bit-mask representation of the DIOs to toggle.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return None
//!
//! \sa \ref GPIOToggleDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOToggleMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Toggle the DIOs.
    HWREG( GPIO_BASE + GPIO_O_DOUTTGL31_0 ) = dioMask;
}

//*****************************************************************************
//
//! \brief Gets the output enable status of a specific DIO.
//!
//! This function returns the output enable status for the specified DIO.
//! The DIO can be configured as either input or output under software control.
//!
//! \param dioNumber specifies the DIO to get the output enable setting from (0-31).
//!
//! \return Returns one of the enumerated data types (0 or 1):
//! - \ref GPIO_OUTPUT_DISABLE : DIO output is disabled.
//! - \ref GPIO_OUTPUT_ENABLE  : DIO output is enabled.
//!
//! \sa \ref GPIOGetOutputEnableMultiDio(), \ref GPIOSetOutputEnableDio(), \ref GPIOSetOutputEnableMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOGetOutputEnableDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Return the output enable status for the specified DIO.
    return ((HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) >> dioNumber) & 1);
}

//*****************************************************************************
//
//! \brief Gets the output enable setting of the specified DIOs.
//!
//! This function returns the output enable setting for multiple DIOs.
//! The value returned is not shifted and hence matches the corresponding dioMask bits.
//!
//! \param dioMask is the bit-mask representation of the DIOs to return the output enable settings from.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return Returns the output enable setting for multiple DIOs as a bit vector corresponding to the dioMask bits.
//! - 0 : Corresponding DIO is configured with output disabled.
//! - 1 : Corresponding DIO is configured with output enabled.
//!
//! \sa \ref GPIOGetOutputEnableDio(), \ref GPIOSetOutputEnableDio(), \ref GPIOSetOutputEnableMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOGetOutputEnableMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Return the output enable value for the specified DIOs.
    return (HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) & dioMask);
}

//*****************************************************************************
//
//! \brief Sets output enable of a specific DIO.
//!
//! This function sets the GPIO output enable bit for the specified DIO.
//! The DIO can be configured as either input or output under software control.
//!
//! \param dioNumber specifies the DIO to configure (0-31).
//! \param outputEnableValue specifies the output enable setting of the specified DIO:
//! - \ref GPIO_OUTPUT_DISABLE : DIO output is disabled.
//! - \ref GPIO_OUTPUT_ENABLE  : DIO output is enabled.
//!
//! \return None
//!
//! \sa \ref GPIOSetOutputEnableMultiDio(), \ref GPIOGetOutputEnableDio(), \ref GPIOGetOutputEnableMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOSetOutputEnableDio(uint32_t dioNumber, uint32_t outputEnableValue)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));
    ASSERT((outputEnableValue == GPIO_OUTPUT_DISABLE) || (outputEnableValue == GPIO_OUTPUT_ENABLE));

    // Update the output enable bit for the specified DIO.
    if (outputEnableValue == GPIO_OUTPUT_ENABLE)
    {
        HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) |= (1 << dioNumber);
    }
    else
    {
        HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) &= ~(1 << dioNumber);
    }
}

//*****************************************************************************
//
//! \brief Configures the output enable setting for all specified DIOs.
//!
//! This function configures the output enable setting for the specified DIOs.
//! The output enable setting must be shifted so it matches the corresponding dioMask bits.
//! The DIOs can be configured as either an input or output under software control.
//!
//! \note Note that this is a read-modify-write operation and hence not atomic.
//!
//! \param dioMask is the bit-mask representation of the DIOs on which to configure the
//! output enable setting. The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//! \param bitVectoredOutputEnable holds the output enable setting the corresponding DIO-bits:
//! - 0 : Corresponding DIO is configured with output disabled.
//! - 1 : Corresponding DIO is configured with output enabled.
//!
//! \return None
//!
//! \sa \ref GPIOSetOutputEnableDio(), \ref GPIOGetOutputEnableDio(), \ref GPIOGetOutputEnableMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOSetOutputEnableMultiDio(uint32_t dioMask, uint32_t bitVectoredOutputEnable)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) = (HWREG( GPIO_BASE + GPIO_O_DOE31_0 ) & ~dioMask) |
                                           (bitVectoredOutputEnable & dioMask);
}

//*****************************************************************************
//
//! \brief Gets the event status of a specific DIO.
//!
//! \param dioNumber specifies the DIO to get the event status from (0-31).
//!
//! \return Returns the current event status on the specified DIO.
//! - 0 : Non-triggered event.
//! - 1 : Triggered event.
//!
//! \sa \ref GPIOGetEventMultiDio(), \ref GPIOClearEventDio(), \ref GPIOClearEventMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOGetEventDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Return the event status for the specified DIO.
    return ((HWREG( GPIO_BASE + GPIO_O_RIS ) >> dioNumber) & 1);
}

//*****************************************************************************
//
//! \brief Gets the event status of the specified DIOs.
//!
//! This function returns the event status for multiple DIOs.
//! The value returned is not shifted and hence matches the corresponding dioMask bits.
//!
//! \param dioMask is the bit-mask representation of the DIOs to get the
//! event status from (0-31).
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return Returns a bit vector with the current event status corresponding to the specified DIOs.
//! - 0 : Corresponding DIO has no triggered event.
//! - 1 : Corresponding DIO has a triggered event.
//!
//! \sa \ref GPIOGetEventDio(), \ref GPIOClearEventDio(), \ref GPIOClearEventMultiDio()
//
//*****************************************************************************
__STATIC_INLINE uint32_t GPIOGetEventMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Return the event status for the specified DIO.
    return (HWREG( GPIO_BASE + GPIO_O_RIS ) & dioMask);
}

//*****************************************************************************
//
//! \brief Clears the IO event status of a specific DIO.
//!
//! \param dioNumber specifies the DIO on which to clear the event status (0-31).
//!
//! \return None
//!
//! \sa \ref GPIOClearEventMultiDio(), \ref GPIOGetEventDio(), \ref GPIOGetEventMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOClearEventDio(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Clear the event status for the specified DIO.
    HWREG( GPIO_BASE + GPIO_O_ICLR ) = (1 << dioNumber);
}

//*****************************************************************************
//
//! \brief Clears the IO event status on the specified DIOs.
//!
//! \param dioMask is the bit-mask representation of the DIOs on which to
//! clear the events status.
//! The parameter must be a bitwise OR'ed combination of the following:
//! - \ref GPIO_DIO_0_MASK
//! - ...
//! - \ref GPIO_DIO_25_MASK
//!
//! \return None
//!
//! \sa \ref GPIOClearEventDio(), \ref GPIOGetEventDio(), \ref GPIOGetEventMultiDio()
//
//*****************************************************************************
__STATIC_INLINE void GPIOClearEventMultiDio(uint32_t dioMask)
{
    // Check the arguments.
    ASSERT(dioMask & GPIO_DIO_ALL_MASK);

    // Clear the event status for the specified DIOs.
    HWREG( GPIO_BASE + GPIO_O_ICLR ) = dioMask;
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

#endif // __GPIO_H__
