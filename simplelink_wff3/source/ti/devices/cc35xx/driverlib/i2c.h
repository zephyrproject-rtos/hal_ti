/******************************************************************************
 *  Filename:       i2c.h
 *
 *  Description:    Prototypes and defines for the I2C API.
 *
 *  Copyright (c) 2023-2026 Texas Instruments Incorporated
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

#ifndef ti_devices_i2c__include
#define ti_devices_i2c__include

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
//! \name I2C Controller Commands
//!
//! For usage details see description of \ref I2CControllerSetCommand()
//! \{
//
//*****************************************************************************
#define I2C_CONTROLLER_CMD_SINGLE_SEND       (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_START_EN_START | I2C_CCTR_STOP_EN_STOP)
#define I2C_CONTROLLER_CMD_SINGLE_RECEIVE    (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_START_EN_START | I2C_CCTR_STOP_EN_STOP)
#define I2C_CONTROLLER_CMD_BURST_SEND_START  (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_START_EN_START)
#define I2C_CONTROLLER_CMD_BURST_SEND_CONT   (I2C_CCTR_BURSTRUN_EN)
#define I2C_CONTROLLER_CMD_BURST_SEND_FINISH (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_STOP_EN_STOP)
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_START \
    (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_START_EN_START | I2C_CCTR_ACK_EN_ACK | I2C_CCTR_CACKOEN_EN)
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT   (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_ACK_EN_ACK | I2C_CCTR_CACKOEN_EN)
#define I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_STOP_EN_STOP)
#define I2C_CONTROLLER_CMD_BURST_FINISH         (I2C_CCTR_BURSTRUN_EN | I2C_CCTR_STOP_EN_STOP)
//! \}

//*****************************************************************************
//
//! \name I2C Controller Transaction Length
//!
//! For usage details see description of \ref I2CControllerSetCommand()
//! \{
//
//*****************************************************************************
//! \brief The maximum length of a burst transaction
#define I2C_CONTROLLER_TRANSACTION_LENGTH_MAX    0xFFF
//! \brief The length of a single byte transaction
#define I2C_CONTROLLER_TRANSACTION_LENGTH_SINGLE 0x001
//! \brief The length to be used together with some commands that does not have
//! any data associated with it.
#define I2C_CONTROLLER_TRANSACTION_LENGTH_NONE   0x000
//! \}

//*****************************************************************************
//
//! \name I2C Controller Configurations
//! \{
//
//*****************************************************************************
//! Default configuration
#define I2C_CONTROLLER_CONFIG_DEFAULT                    0
//! Enables the clock stretching detection.
#define I2C_CONTROLLER_CONFIG_CLOCK_STRETCHING_DETECTION I2C_CCR_CLKSTRETCH_EN
//! Enable Multicontroller mode.
#define I2C_CONTROLLER_CONFIG_MULTI_CONTROLLER_MODE      I2C_CCR_MCST_EN
//! The controller is in a test mode loopback configuration.
#define I2C_CONTROLLER_CONFIG_LOOPBACK                   I2C_CCR_LPBK_EN
//! \}

//*****************************************************************************
//
//! \name I2C Controller Transaction Direction
//! \{
//
//*****************************************************************************
//! \I2C Controller is initiating a read from the target.
#define I2C_CONTROLLER_DIR_RECEIVE  I2C_CSA_DIR_RECEIVE
//! \I2C Controller is initiating a write to the target.
#define I2C_CONTROLLER_DIR_TRANSMIT I2C_CSA_DIR_TRANSMIT
//! \}

//*****************************************************************************
//
//! \name I2C Controller Error Status
//! \{
//
//*****************************************************************************
//! No error
#define I2C_CONTROLLER_ERR_NONE     0
//! The transmitted address was not acknowledged.
#define I2C_CONTROLLER_ERR_ADDR_ACK I2C_CSR_ADRACK_SET
//! The transmitted data was not acknowledged.
#define I2C_CONTROLLER_ERR_DATA_ACK I2C_CSR_DATACK_SET
//! The controller lost arbitration.
#define I2C_CONTROLLER_ERR_ARB_LOST I2C_CSR_ARBLST_SET
//! \}

//*****************************************************************************
//
//! \name I2C Interrupts
//! \{
//
//*****************************************************************************
//! \brief The collection of all interrupt sources for the \I2C module.
//!
//! Can for example be used with \ref I2CDisableInt() or \ref I2CClearInt(), to
//! disable or clear all interrupts.
#define I2C_INT_ALL 0xFFFFFFFF
//! \}

//*****************************************************************************
//
//! \name I2C Controller Interrupts
//! \{
//
//*****************************************************************************
#define I2C_CONTROLLER_INT_RX_DONE         I2C_EVENT0_IMASK_CRXDONE
#define I2C_CONTROLLER_INT_TX_DONE         I2C_EVENT0_IMASK_CTXDONE
#define I2C_CONTROLLER_INT_RX_FIFO_TRIGGER I2C_EVENT0_IMASK_RXFIFOTRGC
#define I2C_CONTROLLER_INT_TX_FIFO_TRIGGER I2C_EVENT0_IMASK_TXFIFOTRGC
#define I2C_CONTROLLER_INT_RX_FIFO_FULL    I2C_EVENT0_IMASK_RXFIFOFULLC
#define I2C_CONTROLLER_INT_TX_FIFO_FULL    I2C_EVENT0_IMASK_TXFIFOFULLC
#define I2C_CONTROLLER_INT_TX_FIFO_EMPTY   I2C_EVENT0_IMASK_TXEMPTYC
#define I2C_CONTROLLER_INT_NACK            I2C_EVENT0_IMASK_CNACK
#define I2C_CONTROLLER_INT_START           I2C_EVENT0_IMASK_CSTART
#define I2C_CONTROLLER_INT_STOP            I2C_EVENT0_IMASK_CSTOP
#define I2C_CONTROLLER_INT_ARB_LOST        I2C_EVENT0_IMASK_CARBLOST
//! \}

//*****************************************************************************
//
//! \name I2C Target Interrupts
//! \{
//
//*****************************************************************************
#define I2C_TARGET_INT_RX_DONE           I2C_EVENT0_IMASK_TRXDONE
#define I2C_TARGET_INT_TX_DONE           I2C_EVENT0_IMASK_TTXDONE
#define I2C_TARGET_INT_RX_FIFO_TRIGGER   I2C_EVENT0_IMASK_RXFIFOTRGT
#define I2C_TARGET_INT_TX_FIFO_TRIGGER   I2C_EVENT0_IMASK_TXFIFOTRGT
#define I2C_TARGET_INT_RX_FIFO_FULL      I2C_EVENT0_IMASK_RXFIFOFULLT
#define I2C_TARGET_INT_TX_FIFO_FULL      I2C_EVENT0_IMASK_TXFIFOFULLT
#define I2C_TARGET_INT_TX_FIFO_EMPTY     I2C_EVENT0_IMASK_TXEMPTYT
#define I2C_TARGET_INT_START             I2C_EVENT0_IMASK_TSTART
#define I2C_TARGET_INT_STOP              I2C_EVENT0_IMASK_TSTOP
#define I2C_TARGET_INT_GEN_CALL          I2C_EVENT0_IMASK_TGENCALL
#define I2C_TARGET_INT_TX_FIFO_UNDERFLOW I2C_EVENT0_IMASK_TX_UNFL_T
#define I2C_TARGET_INT_ARB_LOST          I2C_EVENT0_IMASK_CARBLOST
//! \}

//*****************************************************************************
//
//! \name I2C Modes
//! \{
//
//*****************************************************************************
//! Standard-mode (100kbit/s)
#define I2C_MODE_STANDARD  0
//! Fast-mode (400kbit/s)
#define I2C_MODE_FAST      1
//! Fast-mode Plus (1Mbit/s)
#define I2C_MODE_FAST_PLUS 2
//! \}

//*****************************************************************************
//
//! \name I2C Controller Address modes
//! \{
//
//*****************************************************************************
//! 7-bit addressing
#define I2C_CONTROLLER_ADDR_MODE_7_BIT  I2C_CSA_CMODE_SEVEN_BIT
//! 10-bit addressing
#define I2C_CONTROLLER_ADDR_MODE_10_BIT I2C_CSA_CMODE_TEN_BIT
//! \}

//*****************************************************************************
//
//! \name I2C Target Address modes
//! \{
//
//*****************************************************************************
//! 7-bit addressing
#define I2C_TARGET_ADDR_MODE_7_BIT  I2C_TOAR_MODE_SEVEN_BIT
//! 10-bit addressing
#define I2C_TARGET_ADDR_MODE_10_BIT I2C_TOAR_MODE_TEN_BIT
//! \}

//*****************************************************************************
//
//! \name I2C FIFO Macros
//! \{
//
//*****************************************************************************
#define I2C_RX_FIFO_SIZE (I2C_FIFOSR_RXFIFOCNT_MAXIMUM >> I2C_FIFOSR_RXFIFOCNT_S)
#define I2C_TX_FIFO_SIZE (I2C_FIFOSR_TXFIFOCNT_MAXIMUM >> I2C_FIFOSR_TXFIFOCNT_S)
//! \}

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
//! \brief Checks an \I2C base address.
//!
//! This function determines if a \I2C module base address is valid.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns \c true if the base address is valid and \c false
//! otherwise
//
//*****************************************************************************
static bool I2CIsBaseValid(uint32_t base)
{
    return (base == I2C0_BASE || base == I2C1_BASE);
}
#endif

//*****************************************************************************
//
//! \brief Initializes the \I2C Controller module.
//!
//! This function initializes operation of the \I2C Controller module. Upon
//! successful initialization of the \I2C module, this function will have set the
//! bus speed for the controller, configured the glitch suppression filter for
//! for the given bus speed and will have enabled the \I2C Controller module.
//!
//! \note The \I2C Controller will be enabled by this function.
//!
//! \param base is the base address of the \I2C module.
//! \param config is the configuration to be used by the \I2C Controller module
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_CONTROLLER_CONFIG_CLOCK_STRETCHING_DETECTION
//! - \ref I2C_CONTROLLER_CONFIG_MULTI_CONTROLLER_MODE
//! - \ref I2C_CONTROLLER_CONFIG_LOOPBACK
//! Or:
//! - \ref I2C_CONTROLLER_CONFIG_DEFAULT
//! \param mode set up the \I2C mode
//! - \ref I2C_MODE_STANDARD
//! - \ref I2C_MODE_FAST
//! - \ref I2C_MODE_FAST_PLUS
//!
//! \return None
//
//*****************************************************************************
extern void I2CControllerInit(uint32_t base, uint32_t config, uint32_t mode);

//*****************************************************************************
//
//! \brief Controls the state of the \I2C Controller module.
//!
//! This function is used to control the state of the Controller module send and
//! receive operations.
//!
//! To perform a single-byte transmit transaction:
//!  - Put the byte to transmit in the TX FIFO
//!  - Call this function with:
//!    - \c transactionLength: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_SINGLE
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_SINGLE_SEND
//!  - Wait until the the command is done.
//!
//! To perform a single-byte receive transaction:
//!  - Call this function with:
//!    - \c transactionLength: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_SINGLE
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_SINGLE_RECEIVE
//!  - Wait until the command is done.
//!  - If the transaction was successful, the received byte can be read from the
//!    RX FIFO.
//!
//! To perform a multi-byte transmit transaction:
//!  - Fill the TX FIFO with the first bytes of the transaction.
//!  - Call this function with:
//!    - \c transactionLength: The number of bytes in the transaction, but at
//!      max \ref I2C_CONTROLLER_TRANSACTION_LENGTH_MAX.
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_SEND_START.
//!  - While the command is executing, repeatedly fill the TX FIFO with the data
//!    of the transaction.
//!  - The command is done when \c transactionLength bytes has been transmitted.
//!  - If more data needs to be transmitted call this function with below
//!    parameters and then continue to fill the TX FIFO as described above:
//!    - \c transactionLength: The number of remaining bytes in the transaction,
//!      but at max \ref I2C_CONTROLLER_TRANSACTION_LENGTH_MAX.
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_SEND_CONT
//!  - If no more data needs to be transmitted, end the \I2C transaction by
//!    calling this function with:
//!    - \c transactionLength: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_NONE
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH or
//!      \ref I2C_CONTROLLER_CMD_BURST_FINISH.
//!  - Alternatively, a repeated start condition can be sent either using
//!    \ref I2C_CONTROLLER_CMD_BURST_SEND_START or
//!    \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_START
//!
//! To perform a multi-byte receive transaction:
//!  - Call this function with:
//!    - \c transactionLength: The number of bytes in the transaction, but at
//!      max \ref I2C_CONTROLLER_TRANSACTION_LENGTH_MAX.
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_START.
//!  - While the command is executing repeatedly read the received data from the
//!    RX FIFO.
//!  - The command is done when \c transactionLength bytes has been received.
//!  - If more data needs to be received call this function with below
//!    parameters and then continue to read the RX FIFO as described above:
//!    - \c transactionLength: The number of remaining bytes in the transaction,
//!      but at max \ref I2C_CONTROLLER_TRANSACTION_LENGTH_MAX.
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT
//!  - If no more data needs to be received, end the \I2C transaction by
//!    calling this function with:
//!    - \c transactionLength: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_NONE
//!    - \c cmd: \ref I2C_CONTROLLER_CMD_BURST_SEND_FINISH or
//!      \ref I2C_CONTROLLER_CMD_BURST_FINISH.
//!  - Alternatively, a repeated start condition can be sent either using
//!    \ref I2C_CONTROLLER_CMD_BURST_SEND_START or
//!    \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_START
//!
//!
//! \param base is the base address of the \I2C module.
//! \param cmd is the command to be issued by the \I2C Controller module
//! The parameter can be one of the following values:
//! - \ref I2C_CONTROLLER_CMD_SINGLE_SEND
//! - \ref I2C_CONTROLLER_CMD_SINGLE_RECEIVE
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_START
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_CONT
//! - \ref I2C_CONTROLLER_CMD_BURST_SEND_FINISH
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_START
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT
//! - \ref I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH
//! - \ref I2C_CONTROLLER_CMD_BURST_FINISH
//! \param transactionLength
//! - Single transaction commands: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_SINGLE
//! - Burst start and continue transaction commands: The number of bytes in the
//!   transaction (Max: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_MAX )
//! - Burst finish commands: \ref I2C_CONTROLLER_TRANSACTION_LENGTH_NONE
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerSetCommand(uint32_t base, uint32_t cmd, uint16_t transactionLength)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));
    ASSERT((cmd == I2C_CONTROLLER_CMD_SINGLE_SEND) ||
           //     (cmd == I2C_CONTROLLER_CMD_SINGLE_RECEIVE) || -> Equal to SINGLE_SEND
           (cmd == I2C_CONTROLLER_CMD_BURST_SEND_START) || (cmd == I2C_CONTROLLER_CMD_BURST_SEND_CONT) ||
           (cmd == I2C_CONTROLLER_CMD_BURST_SEND_FINISH) || (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_START) ||
           (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_CONT)
           //     (cmd == I2C_CONTROLLER_CMD_BURST_RECEIVE_FINISH) || -> Equal to I2C_CONTROLLER_CMD_BURST_SEND_FINISH
           //     (cmd == I2C_CONTROLLER_CMD_BURST_FINISH) || -> Equal to I2C_CONTROLLER_CMD_BURST_SEND_FINISH
    );
    ASSERT(transactionLength <= 0xFFF);

    // Set the command.
    HWREG(base + I2C_O_CCTR) = cmd | ((transactionLength << I2C_CCTR_MBLEN_S) & I2C_CCTR_MBLEN_M);
}

//*****************************************************************************
//
//! \brief Sets the address that the \I2C Controller will place on the bus.
//!
//! This function will set the address mode, address and direction that the
//! \I2C Controller will place on the bus when initiating a transaction.
//!
//! \param base is the base address of the \I2C module.
//! \param addressMode specifies the address mode to be used by the \I2C Controller.
//! - \ref I2C_CONTROLLER_ADDR_MODE_7_BIT
//! - \ref I2C_CONTROLLER_ADDR_MODE_10_BIT
//! \param targetAddr is a 7-bit or 10-bit target address
//! \param direction indicates the direction of the transaction.
//! - \ref I2C_CONTROLLER_DIR_RECEIVE
//! - \ref I2C_CONTROLLER_DIR_TRANSMIT
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerSetTargetAddr(uint32_t base,
                                                uint32_t addressMode,
                                                uint16_t targetAddr,
                                                uint32_t direction)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));
    ASSERT((addressMode == I2C_CONTROLLER_ADDR_MODE_7_BIT) || (addressMode == I2C_CONTROLLER_ADDR_MODE_10_BIT));
    ASSERT(!(targetAddr & 0xFF80) || (addressMode == I2C_CONTROLLER_ADDR_MODE_10_BIT));
    ASSERT(!(targetAddr & 0xFC00));
    ASSERT((direction == I2C_CONTROLLER_DIR_RECEIVE) || (direction == I2C_CONTROLLER_DIR_TRANSMIT));

    // Set the address mode and the address of the target with which the
    // controller will communicate, and set the direction.
    // Note: The possible values for addressMode and direction are defined in
    // in terms of the enums for their corresponding fields in MSA, so they can
    // be added directly without any modification.
    HWREG(base + I2C_O_CSA) = (targetAddr << I2C_CSA_TADDR_S) | addressMode | direction;
}

//*****************************************************************************
//
//! \brief Enable the \I2C Controller module.
//!
//! This will enable operation of the \I2C Controller module.
//!
//! \warning Do not call this function if the \I2C Controller is already enabled.
//! Otherwise transfer failures may occur.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CControllerEnable(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Write to MCR register
    HWREG(base + I2C_O_CCR) |= I2C_CCR_ACTIVE_EN;
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
    ASSERT(I2CIsBaseValid(base));

    // Disable the clock for the controller.
    HWREG(base + I2C_O_CCR) &= ~I2C_CCR_ACTIVE_EN;
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
__STATIC_INLINE bool I2CControllerIsBusy(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Return the busy status.
    if ((HWREG(base + I2C_O_CSR) & I2C_CSR_BUSY_M) == I2C_CSR_BUSY_SET)
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
__STATIC_INLINE bool I2CControllerIsBusBusy(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Return the bus busy status.
    if ((HWREG(base + I2C_O_CSR) & I2C_CSR_BUSBSY_M) == I2C_CSR_BUSBSY_SET)
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
extern uint32_t I2CControllerGetError(uint32_t base);

//*****************************************************************************
//
//! \brief Get the number of bytes in the TX FIFO
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns the number of bytes in the TX FIFO
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CGetTxFifoCount(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // TXFIFOCNT contains the number of bytes that can be written to the TX
    // FIFO. This function needs to return the number of byte already in the TX
    // FIFO.
    return (I2C_FIFOSR_TXFIFOCNT_MAXIMUM - (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_TXFIFOCNT_M)) >>
            I2C_FIFOSR_TXFIFOCNT_S;
}

//*****************************************************************************
//
//! \brief Get the number of bytes in the RX FIFO
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns the number of bytes in the RX FIFO
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CGetRxFifoCount(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // RXFIFOCNT contains the number of bytes that can be read from the RX FIFO
    // I.e. the number of bytes in the RX FIFO
    return (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_RXFIFOCNT_M) >> I2C_FIFOSR_RXFIFOCNT_S;
}

//*****************************************************************************
//
//! \brief Check if TX FIFO is empty
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns \c true if the TX FIFO is empty otherwise \c false.
//
//*****************************************************************************
__STATIC_INLINE bool I2CIsTxFifoEmpty(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // If the maximum number of bytes can be put into the TX FIFO, then it is
    // empty
    return (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_TXFIFOCNT_M) == I2C_FIFOSR_TXFIFOCNT_MAXIMUM;
}

//*****************************************************************************
//
//! \brief Check if RX FIFO is empty
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns \c true if the RX FIFO is empty otherwise \c false.
//
//*****************************************************************************
__STATIC_INLINE bool I2CIsRxFifoEmpty(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // If the no bytes can be read from the RX FIFO, then it is empty
    return (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_RXFIFOCNT_M) == I2C_FIFOSR_RXFIFOCNT_MINIMUM;
}

//*****************************************************************************
//
//! \brief Check if TX FIFO is full
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns \c true if the TX FIFO is full otherwise \c false.
//
//*****************************************************************************
__STATIC_INLINE bool I2CIsTxFifoFull(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // If no bytes can be put into the TX FIFO, then it is full
    return (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_TXFIFOCNT_M) == I2C_FIFOSR_TXFIFOCNT_MINIMUM;
}

//*****************************************************************************
//
//! \brief Check if RX FIFO is full
//!
//! \param base is the base address of the \I2C module.
//!
//! \return Returns \c true of the RX FIFO is full otherwise \c false.
//
//*****************************************************************************
__STATIC_INLINE bool I2CIsRxFifoFull(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // If the maximum number of bytes can be read from the RX FIFO,
    // then it is full
    return (HWREG(base + I2C_O_FIFOSR) & I2C_FIFOSR_RXFIFOCNT_M) == I2C_FIFOSR_RXFIFOCNT_MAXIMUM;
}

//*****************************************************************************
//
//! \brief Set TX FIFO trigger level
//!
//! Indicates at what fill level in the TX FIFO a trigger will be generated.
//! Trigger when TX FIFO contains <= \c level byte(s).
//!
//! \param base is the base address of the \I2C module.
//! \param level is the trigger level. Must be in the interval [0, 7]
//
//*****************************************************************************
__STATIC_INLINE void I2CSetTxFifoTrigger(uint32_t base, uint8_t level)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));
    ASSERT(level <= 7);

    // Read FIFOCTL register
    uint32_t fifoCtlTmp = HWREG(base + I2C_O_FIFOCTL);

    // Clear bits in TXTRIG field
    fifoCtlTmp &= ~I2C_FIFOCTL_TXTRIG_M;

    // Set TXTRIG field to the specified trigger level
    fifoCtlTmp |= (level << I2C_FIFOCTL_TXTRIG_S) & I2C_FIFOCTL_TXTRIG_M;

    // Write back to FIFOCTL register
    HWREG(base + I2C_O_FIFOCTL) = fifoCtlTmp;
}

//*****************************************************************************
//
//! \brief Set RX FIFO trigger level
//!
//! Indicates at what fill level in the RX FIFO a trigger will be generated.
//! Trigger when RX FIFO contains >= \c level byte(s).
//!
//! \param base is the base address of the \I2C module.
//! \param level is the trigger level. Must be in the interval [1, 8]
//
//*****************************************************************************
__STATIC_INLINE void I2CSetRxFifoTrigger(uint32_t base, uint8_t level)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));
    ASSERT(1 <= level && level <= 8);

    // Read FIFOCTL register
    uint32_t fifoCtlTmp = HWREG(base + I2C_O_FIFOCTL);

    // Clear bits in RXTRIG field
    fifoCtlTmp &= ~I2C_FIFOCTL_RXTRIG_M;

    // Set RXTRIG field to the specified trigger level
    fifoCtlTmp |= ((level - 1) << I2C_FIFOCTL_RXTRIG_S) & I2C_FIFOCTL_RXTRIG_M;

    // Write back to FIFOCTL register
    HWREG(base + I2C_O_FIFOCTL) = fifoCtlTmp;
}

//*****************************************************************************
//
//! \brief Flush the \I2C TX FIFO.
//!
//! This function will instruct the \I2C module to flush the TX FIFO and wait
//! until the TX FIFO has been flushed.
//!
//! \warning The FIFOs must only be flushed when the \I2C is in IDLE mode.
//!
//! \pre The FIFO interrupts need to be disabled.
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//!
//! \post The FIFO interrupt flags need to be checked.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CFlushTxFifo(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Flush TX FIFO
    HWREG(base + I2C_O_FIFOCTL) |= I2C_FIFOCTL_TXFLUSH_EN;

    // Wait until TX FIFO is empty
    while (I2CIsTxFifoEmpty(base) != true) {}

    // Disable TX FIFO flushing
    HWREG(base + I2C_O_FIFOCTL) &= ~I2C_FIFOCTL_TXFLUSH_EN;
}

//*****************************************************************************
//
//! \brief Flush the \I2C RX FIFO.
//!
//! This function will instruct the \I2C module to flush the RX FIFO and wait
//! until the RX FIFO has been flushed.
//!
//! \warning The FIFOs must only be flushed when the \I2C is in IDLE mode.
//!
//! \pre The FIFO interrupts need to be disabled.
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//!
//! \post The FIFO interrupt flags need to be checked.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CFlushRxFifo(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Flush RX FIFO
    HWREG(base + I2C_O_FIFOCTL) |= I2C_FIFOCTL_RXFLUSH_EN;

    // Wait until RX FIFO is empty
    while (I2CIsRxFifoEmpty(base) != true) {}

    // Disable RX FIFO flushing
    HWREG(base + I2C_O_FIFOCTL) &= ~I2C_FIFOCTL_RXFLUSH_EN;
}

//*****************************************************************************
//
//! \brief Flush the \I2C TX and RX FIFOs.
//!
//! This function will instruct the \I2C module to flush the TX and RX FIFOs and
//! wait until both FIFOs have been flushed.
//! Using this function is slightly more efficient than sequentially using
//! \ref I2CFlushRxFifo and \ref I2CFlushTxFifo
//!
//! \warning The FIFOs must only be flushed when the \I2C is in IDLE mode.
//!
//! \pre The FIFO interrupts need to be disabled.
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//!
//! \post The FIFO interrupt flags need to be checked.
//!
//! \param base is the base address of the \I2C module.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CFlushFifos(uint32_t base)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Flush TX and RX FIFOs
    HWREG(base + I2C_O_FIFOCTL) |= I2C_FIFOCTL_TXFLUSH_EN | I2C_FIFOCTL_RXFLUSH_EN;

    // Wait until both FIFOs are empty.
    while ((HWREG(base + I2C_O_FIFOSR) & (I2C_FIFOSR_TXFIFOCNT_M | I2C_FIFOSR_RXFIFOCNT_M)) !=
            (I2C_FIFOSR_TXFIFOCNT_MAXIMUM | I2C_FIFOSR_RXFIFOCNT_MINIMUM))
    {}

    // Disable TX and RX FIFO flushing
    HWREG(base + I2C_O_FIFOCTL) &= ~(I2C_FIFOCTL_TXFLUSH_EN | I2C_FIFOCTL_RXFLUSH_EN);
}

//*****************************************************************************
//
//! \brief Gets a data element from the \I2C RX FIFO.
//!
//! This function reads a byte of data from the RX FIFO of the specified \I2C
//! module and places that data into the location specified by the \c data
//! parameter. If there is no data in the RX FIFO, this function waits until a
//! byte is available before returning.
//!
//! \param base is the base address of the \I2C module.
//! \param data is a pointer to a storage location for the data read from the RX
//! FIFO
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CGetData(uint32_t base, uint8_t *data)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Wait until there is data to be read.
    while (I2CIsRxFifoEmpty(base)) {}

    // Read a byte from I2C RX FIFO.
    *data = HWREGB(base + I2C_O_RXDATA);
}

//*****************************************************************************
//
//! \brief Gets a data element from the \I2C RX FIFO (non-blocking).
//!
//! This function reads a byte of data from the RX FIFO of the specified \I2C
//! module and places that data into the location specified by the \c data
//! parameter. If there is no data in the RX FIFO, this function returns a zero.
//!
//! \param base is the base address of the \I2C module.
//! \param data is a pointer to a storage location for the data read from the RX
//! FIFO
//!
//! \return Returns the number of bytes read from the \I2C RX FIFO (0 or 1).
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CGetDataNonBlocking(uint32_t base, uint8_t *data)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Check if there is data to be read
    if (I2CIsRxFifoEmpty(base))
    {
        return 0;
    }
    else
    {
        // Read a byte from I2C RX FIFO.
        *data = HWREGB(base + I2C_O_RXDATA);
        return 1;
    }
}

//*****************************************************************************
//
//! \brief Puts a data element into the \I2C TX FIFO.
//!
//! This function places the supplied data into the TX FIFO of the specified
//! \I2C module. If there is no space available in the TX FIFO, this function
//! waits until there is space available before returning.
//!
//! \param base is the base address of the \I2C module.
//! \param data is the data to be written to the TX FIFO.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CPutData(uint32_t base, uint8_t data)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Wait until space is available.
    while (I2CIsTxFifoFull(base)) {}

    // Write the byte.
    HWREGB(base + I2C_O_TXDATA) = data;
}

//*****************************************************************************
//
//! \brief Puts a data element into the \I2C TX FIFO (non-blocking).
//!
//! This function places the supplied data into the TX FIFO of the specified
//! \I2C module. If there is no space in the TX FIFO, this function returns a
//! zero.
//!
//! \param base is the base address of the \I2C module.
//! \param data is the data to be written to the TX FIFO.
//!
//! \return Returns the number of bytes written to the \I2C TX FIFO (0 or 1).
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CPutDataNonBlocking(uint32_t base, uint8_t data)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Check if there is space available.
    if (I2CIsTxFifoFull(base))
    {
        return 0;
    }
    else
    {
        // Write the byte.
        HWREGB(base + I2C_O_TXDATA) = data;
        return 1;
    }
}

//*****************************************************************************
//
//! \brief Enables individual \I2C interrupt sources.
//!
//! Enables the indicated \I2C interrupt sources. Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! \param base is the base address of the \I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_CONTROLLER_INT_RX_DONE
//! - \ref I2C_CONTROLLER_INT_TX_DONE
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_CONTROLLER_INT_NACK
//! - \ref I2C_CONTROLLER_INT_START
//! - \ref I2C_CONTROLLER_INT_STOP
//! - \ref I2C_CONTROLLER_INT_ARB_LOST
//! - \ref I2C_TARGET_INT_RX_DONE
//! - \ref I2C_TARGET_INT_TX_DONE
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_GEN_CALL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//! - \ref I2C_TARGET_INT_ARB_LOST
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CEnableInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Enable the specified interrupts.
    HWREG(base + I2C_O_EVENT0_IMEN) = intFlags;
}

//*****************************************************************************
//
//! \brief Disables individual \I2C interrupt sources.
//!
//! Disables the indicated \I2C interrupt sources. Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! \param base is the base address of the \I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//! The parameter is the bitwise OR of any of the following:
//! - \ref I2C_CONTROLLER_INT_RX_DONE
//! - \ref I2C_CONTROLLER_INT_TX_DONE
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_CONTROLLER_INT_NACK
//! - \ref I2C_CONTROLLER_INT_START
//! - \ref I2C_CONTROLLER_INT_STOP
//! - \ref I2C_CONTROLLER_INT_ARB_LOST
//! - \ref I2C_TARGET_INT_RX_DONE
//! - \ref I2C_TARGET_INT_TX_DONE
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_GEN_CALL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//! - \ref I2C_TARGET_INT_ARB_LOST
//! - \ref I2C_INT_ALL can be used to disable all interrupts
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CDisableInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Disable the specified interrupts.
    HWREG(base + I2C_O_EVENT0_IMDIS) = intFlags;
}

//*****************************************************************************
//
//! \brief Clears \I2C interrupt sources.
//!
//! The specified \I2C interrupt sources are cleared, so that they no
//! longer assert. This must be done in the interrupt handler to keep it from
//! being called again immediately upon exit.
//!
//! TODO: Determine if below note is needed (LPRFXXWARE-845)
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
//! - \ref I2C_CONTROLLER_INT_RX_DONE
//! - \ref I2C_CONTROLLER_INT_TX_DONE
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_CONTROLLER_INT_NACK
//! - \ref I2C_CONTROLLER_INT_START
//! - \ref I2C_CONTROLLER_INT_STOP
//! - \ref I2C_CONTROLLER_INT_ARB_LOST
//! - \ref I2C_TARGET_INT_RX_DONE
//! - \ref I2C_TARGET_INT_TX_DONE
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_GEN_CALL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//! - \ref I2C_TARGET_INT_ARB_LOST
//! - \ref I2C_INT_ALL can be used to clear all interrupts
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void I2CClearInt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Clear the specified I2C interrupt sources.
    HWREG(base + I2C_O_EVENT0_IDIS) = intFlags;
}

//*****************************************************************************
//
//! \brief Gets the current \I2C interrupt status.
//!
//! This returns the interrupt status for the \I2C module. Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \param base is the base address of the \I2C module.
//! \param masked selects either raw or masked interrupt status.
//! - \c false : Raw interrupt status is requested.
//! - \c true  : Masked interrupt status is requested.
//!
//! \return Returns the current interrupt status as an OR'ed combination of:
//! - \ref I2C_CONTROLLER_INT_RX_DONE
//! - \ref I2C_CONTROLLER_INT_TX_DONE
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_TRIGGER
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_RX_FIFO_FULL
//! - \ref I2C_CONTROLLER_INT_TX_FIFO_EMPTY
//! - \ref I2C_CONTROLLER_INT_NACK
//! - \ref I2C_CONTROLLER_INT_START
//! - \ref I2C_CONTROLLER_INT_STOP
//! - \ref I2C_CONTROLLER_INT_ARB_LOST
//! - \ref I2C_TARGET_INT_RX_DONE
//! - \ref I2C_TARGET_INT_TX_DONE
//! - \ref I2C_TARGET_INT_RX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_TX_FIFO_TRIGGER
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_RX_FIFO_FULL
//! - \ref I2C_TARGET_INT_TX_FIFO_EMPTY
//! - \ref I2C_TARGET_INT_START
//! - \ref I2C_TARGET_INT_STOP
//! - \ref I2C_TARGET_INT_GEN_CALL
//! - \ref I2C_TARGET_INT_TX_FIFO_UNDERFLOW
//! - \ref I2C_TARGET_INT_ARB_LOST
//
//*****************************************************************************
__STATIC_INLINE uint32_t I2CIntStatus(uint32_t base, bool masked)
{
    // Check the arguments.
    ASSERT(I2CIsBaseValid(base));

    // Return either the masked interrupt status or the raw interrupt status as
    // requested.
    if (masked)
    {
        return (HWREG(base + I2C_O_EVENT0_MIS));
    }
    else
    {
        return (HWREG(base + I2C_O_EVENT0_RIS));
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

#endif // ti_devices_i2c__include
