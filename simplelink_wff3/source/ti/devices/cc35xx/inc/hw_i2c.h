/******************************************************************************
*  Filename:       hw_i2c.h
*
*  Description:    Defines and prototypes for the I2C peripheral.
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
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
#ifndef __HW_I2C_H__
#define __HW_I2C_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the I2C component

--------------------------------------------------------------------------------- */

//This register controls the glitch filter on the SCL and SDA lines
#define I2C_O_GFCTL                                                  0x00000100U

//Controller target address register
#define I2C_O_CSA                                                    0x00000104U

//This control register configures the *I2C* controller operation
#define I2C_O_CCTR                                                   0x00000108U

//The status register indicates the state of the bus controller
#define I2C_O_CSR                                                    0x0000010CU

//This register is programmed to set the timer period for the SCL clock and assign the SCL clock to standard mode
#define I2C_O_CTPR                                                   0x00000110U

//Controller configuration register
#define I2C_O_CCR                                                    0x00000114U

//This register is used to determine the SCL and SDA signal status
#define I2C_O_CBMON                                                  0x00000118U

//This register consists of seven address bits that identify the I2C device on the I2C bus
#define I2C_O_TOAR                                                   0x0000011CU

//This register consists of seven address bits that identify the alternate address for the *I2C* device on the *I2C* bus
#define I2C_O_TOAR2                                                  0x00000120U

//Target control register
#define I2C_O_TCTR                                                   0x00000124U

//Target status register
#define I2C_O_TSR                                                    0x00000128U

//RX FIFO read data byte
#define I2C_O_RXDATA                                                 0x0000012CU

//Transmit data register
#define I2C_O_TXDATA                                                 0x00000130U

//This register enables the target to not acknowledge (NACK) for invalid data or command or acknowledge (ACK) for valid data or command
#define I2C_O_TACKCTL                                                0x00000134U

//Target FIFO control
#define I2C_O_FIFOCTL                                                0x00000138U

//FIFO status register
#define I2C_O_FIFOSR                                                 0x0000013CU

//Register for the selection of divider value to generate functional clock from SVT clock
#define I2C_O_FCLKDIV                                                0x00000140U

//This register can be used by the software developer to control the behavior of the peripheral relative to the 'Core Halted' input
#define I2C_O_PDBGCTL                                                0x00000000U

//Interrupt Mask
#define I2C_O_EVENT0_IMASK                                           0x00000004U

//Raw interrupt status
#define I2C_O_EVENT0_RIS                                             0x00000008U

//Masked interrupt status
#define I2C_O_EVENT0_MIS                                             0x0000000CU

//Interrupt set
#define I2C_O_EVENT0_IEN                                             0x00000010U

//Interrupt clear
#define I2C_O_EVENT0_IDIS                                            0x00000014U

//Interrupt mask set
#define I2C_O_EVENT0_IMEN                                            0x00000018U

//Interrupt clear
#define I2C_O_EVENT0_IMDIS                                           0x0000001CU

//Event mode register
#define I2C_O_EVT_MODE                                               0x00000020U

//This register identifies the peripheral and its exact version
#define I2C_O_DESC                                                   0x00000024U

//This register controls the bus clock to *I2C*
#define I2C_O_CLKCFG                                                 0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       GFCTL
    Offset name:         I2C_O_GFCTL
    Relative address:    0x100
    Description:         This register controls the glitch filter on the SCL and SDA lines
    Default Value:       0x00000000

        Field:           GFSEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Glitch suppression pulse width

                         This field controls the pulse width select for glitch suppression on the SCL and SDA lines. The following values are the glitch suppression values in terms of functional clocks.

        ENUMs:
            DIS:                         Bypass
            CLK_1:                       1 clock
            CLK_2:                       2 clocks
            CLK_3:                       3 clocks
            CLK_4:                       4 clocks
            CLK_5:                       5 clocks
            CLK_6:                       6 clocks
            CLK_7:                       7 clocks
            CLK_8:                       8 clocks
            CLK_9:                       10 clocks
            CLK_A:                       12 clocks
            CLK_B:                       14 clocks
            CLK_C:                       16 clocks
            CLK_D:                       20 clocks
            CLK_E:                       24 clocks
            CLK_F:                       31 clocks
*/
#define I2C_GFCTL_GFSEL_W                                            4U
#define I2C_GFCTL_GFSEL_M                                            0x0000000FU
#define I2C_GFCTL_GFSEL_S                                            0U
#define I2C_GFCTL_GFSEL_DIS                                          0x00000000U
#define I2C_GFCTL_GFSEL_CLK_1                                        0x00000001U
#define I2C_GFCTL_GFSEL_CLK_2                                        0x00000002U
#define I2C_GFCTL_GFSEL_CLK_3                                        0x00000003U
#define I2C_GFCTL_GFSEL_CLK_4                                        0x00000004U
#define I2C_GFCTL_GFSEL_CLK_5                                        0x00000005U
#define I2C_GFCTL_GFSEL_CLK_6                                        0x00000006U
#define I2C_GFCTL_GFSEL_CLK_7                                        0x00000007U
#define I2C_GFCTL_GFSEL_CLK_8                                        0x00000008U
#define I2C_GFCTL_GFSEL_CLK_9                                        0x00000009U
#define I2C_GFCTL_GFSEL_CLK_A                                        0x0000000AU
#define I2C_GFCTL_GFSEL_CLK_B                                        0x0000000BU
#define I2C_GFCTL_GFSEL_CLK_C                                        0x0000000CU
#define I2C_GFCTL_GFSEL_CLK_D                                        0x0000000DU
#define I2C_GFCTL_GFSEL_CLK_E                                        0x0000000EU
#define I2C_GFCTL_GFSEL_CLK_F                                        0x0000000FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CSA
    Offset name:         I2C_O_CSA
    Relative address:    0x104
    Description:         Controller target address register
    Default Value:       0x00000000

        Field:           DIR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field specifies if the next controller operation is a Receive or Transmit

        ENUMs:
            TRANSMIT:                    The controller is in transmit mode.
            RECEIVE:                     The controller is in receive mode.
*/
#define I2C_CSA_DIR                                                  0x00000001U
#define I2C_CSA_DIR_M                                                0x00000001U
#define I2C_CSA_DIR_S                                                0U
#define I2C_CSA_DIR_TRANSMIT                                         0x00000000U
#define I2C_CSA_DIR_RECEIVE                                          0x00000001U
/*

        Field:           TADDR
        From..to bits:   1...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     *I2C* Target Address This field specifies bits A9 through A0 of the target address.
                         In 7-field addressing mode as selected by MODE field, the top 3 bits are don't care

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_CSA_TADDR_W                                              10U
#define I2C_CSA_TADDR_M                                              0x000007FEU
#define I2C_CSA_TADDR_S                                              1U
#define I2C_CSA_TADDR_MINIMUM                                        0x00000000U
#define I2C_CSA_TADDR_MAXIMUM                                        0x000007FEU
/*

        Field:           CMODE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field selects the addressing mode(7-field/10-field) to be used in controller mode

        ENUMs:
            SEVEN_BIT:                   7-field addressing mode
            TEN_BIT:                     10-field addressing mode
*/
#define I2C_CSA_CMODE                                                0x00008000U
#define I2C_CSA_CMODE_M                                              0x00008000U
#define I2C_CSA_CMODE_S                                              15U
#define I2C_CSA_CMODE_SEVEN_BIT                                      0x00000000U
#define I2C_CSA_CMODE_TEN_BIT                                        0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCTR
    Offset name:         I2C_O_CCTR
    Relative address:    0x108
    Description:         This control register configures the *I2C* controller operation. The START field generates the START or REPEATED START condition. The STOP field determines if the cycle stops at the end of the data cycle or continues to the next transfer cycle, which could be a repeated START. To generate a single transmit cycle, the *I2C* Controller Target Address [CSA] register is written with the desired address, the RS field is cleared, and this register is written with ACK = X (0 or 1), STOP = 1, START = 1, and RUN = 1 to perform the operation and stop. When the operation is completed (or aborted due an error), an byte transaction completed interrupt becomes active and the data may be read from the RXDATA register. When the I2C module operates in Controller receiver mode, a set ACK field causes the I2C bus controller to transmit an acknowledge automatically after each byte. This field must be cleared when the *I2C* bus controller requires no further data to be transmitted from the target transmitter.
    Default Value:       0x00000000

        Field:           BURSTRUN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller enable and start transaction

        ENUMs:
            DIS:                         In standard mode, the controller will be unable to transmit or receive data.
            EN:                          The controller will be able to transmit or receive data
*/
#define I2C_CCTR_BURSTRUN                                            0x00000001U
#define I2C_CCTR_BURSTRUN_M                                          0x00000001U
#define I2C_CCTR_BURSTRUN_S                                          0U
#define I2C_CCTR_BURSTRUN_DIS                                        0x00000000U
#define I2C_CCTR_BURSTRUN_EN                                         0x00000001U
/*

        Field:           START
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Generate START

        ENUMs:
            DIS_START:                   The controller does not generate the START condition.
            EN_START:                    The controller generates the START or repeated START condition
*/
#define I2C_CCTR_START                                               0x00000002U
#define I2C_CCTR_START_M                                             0x00000002U
#define I2C_CCTR_START_S                                             1U
#define I2C_CCTR_START_DIS_START                                     0x00000000U
#define I2C_CCTR_START_EN_START                                      0x00000002U
/*

        Field:           STOP
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Generate STOP

        ENUMs:
            DIS_STOP:                    The controller does not generate the STOP condition.
            EN_STOP:                     The controller generates the STOP condition
*/
#define I2C_CCTR_STOP                                                0x00000004U
#define I2C_CCTR_STOP_M                                              0x00000004U
#define I2C_CCTR_STOP_S                                              2U
#define I2C_CCTR_STOP_DIS_STOP                                       0x00000000U
#define I2C_CCTR_STOP_EN_STOP                                        0x00000004U
/*

        Field:           ACK
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Acknowledge Enable. Configure this field to send the ACK or NACK.

        ENUMs:
            DIS_ACK:                     The last received data byte of a transaction is not acknowledged automatically by the controller.
            EN_ACK:                      The last received data byte of a transaction is acknowledged automatically by the controller.
*/
#define I2C_CCTR_ACK                                                 0x00000008U
#define I2C_CCTR_ACK_M                                               0x00000008U
#define I2C_CCTR_ACK_S                                               3U
#define I2C_CCTR_ACK_DIS_ACK                                         0x00000000U
#define I2C_CCTR_ACK_EN_ACK                                          0x00000008U
/*

        Field:           CACKOEN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller ACK overrride enable

        ENUMs:
            EN:                          When 1 and the controller is receiving data and the number of bytes indicated in MBLEN have been received, the state machine will generate an rxdone interrupt and wait at the start of the ACK for FW to indicate if an ACK or NACK should be sent. The ACK or NACK is selected by writing the [CCTR] register and setting ACK accordingly. The other fields in this register can also be written at this time to continue on with the transaction. If a NACK is sent the state machine will automatically send a Stop.
            DIS:                         No special behavior
*/
#define I2C_CCTR_CACKOEN                                             0x00000010U
#define I2C_CCTR_CACKOEN_M                                           0x00000010U
#define I2C_CCTR_CACKOEN_S                                           4U
#define I2C_CCTR_CACKOEN_EN                                          0x00000010U
#define I2C_CCTR_CACKOEN_DIS                                         0x00000000U
/*

        Field:           RDONTXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Read on TXFIFO empty

        ENUMs:
            EN:                          When 1 the controller will transmit all bytes from the TX FIFO before continuing with the programmed Burst Run Read. If the [CSA.DIR] is not set to read, then this field is ignored. The Start must be set in the [CCTR] for proper *I2C* protocol. The controller will first send the Start Condition, *I2C* Address with R/W field set to write, before sending the bytes in the TX FIFO. When the TX FIFO is empty, the *I2C* transaction will continue as programmed in [CCTR] and [CSA] without sending a Stop Condition.
                         This is intended to be used to perform simple *I2C* command based reads transition that will complete after initiating them without having to get an interrupt to turn the bus around.
            DIS:                         No special behaviour
*/
#define I2C_CCTR_RDONTXEMPTY                                         0x00000020U
#define I2C_CCTR_RDONTXEMPTY_M                                       0x00000020U
#define I2C_CCTR_RDONTXEMPTY_S                                       5U
#define I2C_CCTR_RDONTXEMPTY_EN                                      0x00000020U
#define I2C_CCTR_RDONTXEMPTY_DIS                                     0x00000000U
/*

        Field:           MBLEN
        From..to bits:   16...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction length
                         This field contains the programmed length of bytes of the Transaction.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_CCTR_MBLEN_W                                             12U
#define I2C_CCTR_MBLEN_M                                             0x0FFF0000U
#define I2C_CCTR_MBLEN_S                                             16U
#define I2C_CCTR_MBLEN_MINIMUM                                       0x00000000U
#define I2C_CCTR_MBLEN_MAXIMUM                                       0x0FFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CSR
    Offset name:         I2C_O_CSR
    Relative address:    0x10C
    Description:         The status register indicates the state of the bus controller.
    Default Value:       0x00000000

        Field:           BUSY
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller FSM busy

                         The field is set during an ongoing transaction, so is set during the transmit/receive of the amount of data set in [CCTR.MBLEN] including START, RESTART, Address and STOP signal generation when required for the current transaction.

        ENUMs:
            CLEAR:                       The controller is idle.
            SET:                         The controller is busy.
*/
#define I2C_CSR_BUSY                                                 0x00000001U
#define I2C_CSR_BUSY_M                                               0x00000001U
#define I2C_CSR_BUSY_S                                               0U
#define I2C_CSR_BUSY_CLEAR                                           0x00000000U
#define I2C_CSR_BUSY_SET                                             0x00000001U
/*

        Field:           ERR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Error

                         The error can be from the target address not being acknowledged or the transmit data not being acknowledged.

        ENUMs:
            CLEAR:                       No error was detected on the last operation.
            SET:                         An error occurred on the last operation.
*/
#define I2C_CSR_ERR                                                  0x00000002U
#define I2C_CSR_ERR_M                                                0x00000002U
#define I2C_CSR_ERR_S                                                1U
#define I2C_CSR_ERR_CLEAR                                            0x00000000U
#define I2C_CSR_ERR_SET                                              0x00000002U
/*

        Field:           ADRACK
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Acknowledge address

        ENUMs:
            CLEAR:                       The transmitted address was acknowledged
            SET:                         The transmitted address was not acknowledged.
*/
#define I2C_CSR_ADRACK                                               0x00000004U
#define I2C_CSR_ADRACK_M                                             0x00000004U
#define I2C_CSR_ADRACK_S                                             2U
#define I2C_CSR_ADRACK_CLEAR                                         0x00000000U
#define I2C_CSR_ADRACK_SET                                           0x00000004U
/*

        Field:           DATACK
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Acknowledge data

        ENUMs:
            CLEAR:                       The transmitted data was acknowledged
            SET:                         The transmitted data was not acknowledged.
*/
#define I2C_CSR_DATACK                                               0x00000008U
#define I2C_CSR_DATACK_M                                             0x00000008U
#define I2C_CSR_DATACK_S                                             3U
#define I2C_CSR_DATACK_CLEAR                                         0x00000000U
#define I2C_CSR_DATACK_SET                                           0x00000008U
/*

        Field:           ARBLST
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Arbitration lost

        ENUMs:
            CLEAR:                       The controller won arbitration.
            SET:                         The controller lost arbitration.
*/
#define I2C_CSR_ARBLST                                               0x00000010U
#define I2C_CSR_ARBLST_M                                             0x00000010U
#define I2C_CSR_ARBLST_S                                             4U
#define I2C_CSR_ARBLST_CLEAR                                         0x00000000U
#define I2C_CSR_ARBLST_SET                                           0x00000010U
/*

        Field:           IDLE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     *I2C* Idle

        ENUMs:
            CLEAR:                       The controller is not idle.
            SET:                         The controller is idle.
*/
#define I2C_CSR_IDLE                                                 0x00000020U
#define I2C_CSR_IDLE_M                                               0x00000020U
#define I2C_CSR_IDLE_S                                               5U
#define I2C_CSR_IDLE_CLEAR                                           0x00000000U
#define I2C_CSR_IDLE_SET                                             0x00000020U
/*

        Field:           BUSBSY
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus is busy
                         Controller state machine will wait until this field is cleared before starting a transaction. When first enabling the controller in multi controller environments, FW should wait for one I2C clock period after setting ACTIVE high before writing to the [CCTR] register to start the transaction so that if SCL goes low it will trigger the BUSBSY.

        ENUMs:
            CLEAR:                       The bus is idle.
            SET:                         This Status field is set on a START or when SCL goes low. It is cleared on a STOP,  or when a SCL high bus busy timeout occurs and SCL and SDA are both high. This status is cleared when the ACTIVE field is low.

                         Note that the controller state machine will wait until this field is cleared before starting a transaction. When first enabling the controller in multi controller environments, FW should wait for one I2C clock period after setting ACTIVE high before writing to the [CCTR] register to start the transaction so that if SCL goes low it will trigger the BUSBSY.
*/
#define I2C_CSR_BUSBSY                                               0x00000040U
#define I2C_CSR_BUSBSY_M                                             0x00000040U
#define I2C_CSR_BUSBSY_S                                             6U
#define I2C_CSR_BUSBSY_CLEAR                                         0x00000000U
#define I2C_CSR_BUSBSY_SET                                           0x00000040U
/*

        Field:           CBCNT
        From..to bits:   16...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller Transaction Count
                         This field contains the current count-down value of the transaction.

        ENUMs:
            MAXIMUM:                     Highest possible value
            MINIMUM:                     Smallest value
*/
#define I2C_CSR_CBCNT_W                                              12U
#define I2C_CSR_CBCNT_M                                              0x0FFF0000U
#define I2C_CSR_CBCNT_S                                              16U
#define I2C_CSR_CBCNT_MAXIMUM                                        0x0FFF0000U
#define I2C_CSR_CBCNT_MINIMUM                                        0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTPR
    Offset name:         I2C_O_CTPR
    Relative address:    0x110
    Description:         This register is programmed to set the timer period for the SCL clock and assign the SCL clock to standard mode.
    Default Value:       0x00000001

        Field:           TPR
        From..to bits:   0...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Timer Period

                         This field is used in the equation to configure SCL_PERIOD :

                         SCL_PERIOD = (1 + TPR ) x (SCL_LP + SCL_HP ) x INT_CLK_PRD
                         where:

                         SCL_PRD is the SCL line period (I2C clock).

                         TPR is the Timer Period register value (range of 1 to 127).

                         SCL_LP is the SCL Low period (fixed at 6).

                         SCL_HP is the SCL High period (fixed at 4).

                         INT_CLK_PRD is the functional clock period in ns.

                         Note: INT_CLK_PRD is based on divider value selected in [FCLK_DIV:FCLK:DIV]

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_CTPR_TPR_W                                               7U
#define I2C_CTPR_TPR_M                                               0x0000007FU
#define I2C_CTPR_TPR_S                                               0U
#define I2C_CTPR_TPR_MINIMUM                                         0x00000000U
#define I2C_CTPR_TPR_MAXIMUM                                         0x0000007FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCR
    Offset name:         I2C_O_CCR
    Relative address:    0x114
    Description:         Controller configuration register
    Default Value:       0x00000000

        Field:           ACTIVE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device Active  After this field has been set, it should not be set again unless it has been cleared by writing a 0 or by a reset, otherwise transfer failures may occur.

        ENUMs:
            DIS:                         Disables the *I2C* controller operation.
            EN:                          Enables the *I2C* controller operation.
*/
#define I2C_CCR_ACTIVE                                               0x00000001U
#define I2C_CCR_ACTIVE_M                                             0x00000001U
#define I2C_CCR_ACTIVE_S                                             0U
#define I2C_CCR_ACTIVE_DIS                                           0x00000000U
#define I2C_CCR_ACTIVE_EN                                            0x00000001U
/*

        Field:           MCST
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Multicontroller mode. In Multicontroller mode the SCL high time counts once the SCL line has been detected high. If this is not enabled the high time counts as soon as the SCL line has been set high by the *I2C* controller.

        ENUMs:
            DIS:                         Disable Multicontroller mode.
            EN:                          Enable Multicontroller mode.
*/
#define I2C_CCR_MCST                                                 0x00000002U
#define I2C_CCR_MCST_M                                               0x00000002U
#define I2C_CCR_MCST_S                                               1U
#define I2C_CCR_MCST_DIS                                             0x00000000U
#define I2C_CCR_MCST_EN                                              0x00000002U
/*

        Field:           CLKSTRETCH
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Stretching. This field controls the support for clock stretching of the *I2C* bus.

        ENUMs:
            DIS:                         Disables the clock stretching detection.
                         This can be disabled if no target on the bus does support clock streching, so that the maximum speed on the bus can be reached.
            EN:                          Enables the clock stretching detection.
                         Enabling the clock strechting ensures compliance to the I2C standard but could limit the speed due the clock stretching.
*/
#define I2C_CCR_CLKSTRETCH                                           0x00000004U
#define I2C_CCR_CLKSTRETCH_M                                         0x00000004U
#define I2C_CCR_CLKSTRETCH_S                                         2U
#define I2C_CCR_CLKSTRETCH_DIS                                       0x00000000U
#define I2C_CCR_CLKSTRETCH_EN                                        0x00000004U
/*

        Field:           LPBK
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     I2C Loopback

        ENUMs:
            DIS:                         Normal operation.
            EN:                          The controller in a test mode loopback configuration.
*/
#define I2C_CCR_LPBK                                                 0x00000100U
#define I2C_CCR_LPBK_M                                               0x00000100U
#define I2C_CCR_LPBK_S                                               8U
#define I2C_CCR_LPBK_DIS                                             0x00000000U
#define I2C_CCR_LPBK_EN                                              0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CBMON
    Offset name:         I2C_O_CBMON
    Relative address:    0x118
    Description:         This register is used to determine the SCL and SDA signal status.
    Default Value:       0x00000003

        Field:           SCL
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     SCL status

        ENUMs:
            CLEAR:                       The SCL signal is low.
            SET:                         The SCL signal is high
                         Note: During and right after reset, the SCL pin is in GPIO input mode without the internal pull enabled. For proper *I2C* operation, the user should have the external pull-up resistor in place.
*/
#define I2C_CBMON_SCL                                                0x00000001U
#define I2C_CBMON_SCL_M                                              0x00000001U
#define I2C_CBMON_SCL_S                                              0U
#define I2C_CBMON_SCL_CLEAR                                          0x00000000U
#define I2C_CBMON_SCL_SET                                            0x00000001U
/*

        Field:           SDA
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     SDA status

        ENUMs:
            CLEAR:                       The SDA signal is low.
            SET:                         The SDA signal is high.
                         Note: During and right after reset, the SDA pin is in GPIO input mode without the internal pull enabled. For proper *I2C* operation, the user should have the external pull-up resistor in place.
*/
#define I2C_CBMON_SDA                                                0x00000002U
#define I2C_CBMON_SDA_M                                              0x00000002U
#define I2C_CBMON_SDA_S                                              1U
#define I2C_CBMON_SDA_CLEAR                                          0x00000000U
#define I2C_CBMON_SDA_SET                                            0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TOAR
    Offset name:         I2C_O_TOAR
    Relative address:    0x11C
    Description:         This register consists of seven address bits that identify the I2C device on the I2C bus.
    Default Value:       0x00004000

        Field:           OAR
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target own address: This field specifies bits A9 through A0 of the target address.
                         In 7-field addressing mode as selected by [TOAR.MODE] field, the top 3 bits are don't care

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_TOAR_OAR_W                                               10U
#define I2C_TOAR_OAR_M                                               0x000003FFU
#define I2C_TOAR_OAR_S                                               0U
#define I2C_TOAR_OAR_MINIMUM                                         0x00000000U
#define I2C_TOAR_OAR_MAXIMUM                                         0x000003FFU
/*

        Field:           OAREN
        From..to bits:   14...14
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Target own address enable

        ENUMs:
            EN:                          Enable OAR address
            DIS:                         Disable OAR address
*/
#define I2C_TOAR_OAREN                                               0x00004000U
#define I2C_TOAR_OAREN_M                                             0x00004000U
#define I2C_TOAR_OAREN_S                                             14U
#define I2C_TOAR_OAREN_EN                                            0x00004000U
#define I2C_TOAR_OAREN_DIS                                           0x00000000U
/*

        Field:           MODE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field selects the addressing mode(7-field/10-field) to be used in target mode.

        ENUMs:
            SEVEN_BIT:                   Enable 7-field addressing
            TEN_BIT:                     Enable 10-field addressing
*/
#define I2C_TOAR_MODE                                                0x00008000U
#define I2C_TOAR_MODE_M                                              0x00008000U
#define I2C_TOAR_MODE_S                                              15U
#define I2C_TOAR_MODE_SEVEN_BIT                                      0x00000000U
#define I2C_TOAR_MODE_TEN_BIT                                        0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TOAR2
    Offset name:         I2C_O_TOAR2
    Relative address:    0x120
    Description:         This register consists of seven address bits that identify the alternate address for the *I2C* device on the *I2C* bus.
    Default Value:       0x00000000

        Field:           OAR2
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target own address 2
                         This field specifies the alternate target own address.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_TOAR2_OAR2_W                                             7U
#define I2C_TOAR2_OAR2_M                                             0x0000007FU
#define I2C_TOAR2_OAR2_S                                             0U
#define I2C_TOAR2_OAR2_MINIMUM                                       0x00000000U
#define I2C_TOAR2_OAR2_MAXIMUM                                       0x0000007FU
/*

        Field:           OAR2EN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target own address 2 enable

        ENUMs:
            DIS:                         The alternate address is disabled.
            EN:                          Enables the use of the alternate address in the OAR2 field.
*/
#define I2C_TOAR2_OAR2EN                                             0x00000080U
#define I2C_TOAR2_OAR2EN_M                                           0x00000080U
#define I2C_TOAR2_OAR2EN_S                                           7U
#define I2C_TOAR2_OAR2EN_DIS                                         0x00000000U
#define I2C_TOAR2_OAR2EN_EN                                          0x00000080U
/*

        Field:           OAR2_MASK
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target own address 2 mask: This field specifies bits A6 through A0 of the target address.
                         The bits with value '1' in this field will make the corresponding incoming address bits to match by default regardless of the value inside this field i.e. corresponding bits of this field are don't care.

        ENUMs:
            MINIMUM:                     Minimum Value
            MAXIMUM:                     Maximum Value
*/
#define I2C_TOAR2_OAR2_MASK_W                                        7U
#define I2C_TOAR2_OAR2_MASK_M                                        0x007F0000U
#define I2C_TOAR2_OAR2_MASK_S                                        16U
#define I2C_TOAR2_OAR2_MASK_MINIMUM                                  0x00000000U
#define I2C_TOAR2_OAR2_MASK_MAXIMUM                                  0x007F0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TCTR
    Offset name:         I2C_O_TCTR
    Relative address:    0x124
    Description:         Target control register
    Default Value:       0x00000004

        Field:           ACTIVE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Device active. Setting this field enables the target functionality.

        ENUMs:
            DIS:                         Disables the target operation.
            EN:                          Enables the target operation.
*/
#define I2C_TCTR_ACTIVE                                              0x00000001U
#define I2C_TCTR_ACTIVE_M                                            0x00000001U
#define I2C_TCTR_ACTIVE_S                                            0U
#define I2C_TCTR_ACTIVE_DIS                                          0x00000000U
#define I2C_TCTR_ACTIVE_EN                                           0x00000001U
/*

        Field:           GENCALL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     General call response enable.

        ENUMs:
            DIS:                         Do not respond to a general call
            EN:                          Respond to a general call
*/
#define I2C_TCTR_GENCALL                                             0x00000002U
#define I2C_TCTR_GENCALL_M                                           0x00000002U
#define I2C_TCTR_GENCALL_S                                           1U
#define I2C_TCTR_GENCALL_DIS                                         0x00000000U
#define I2C_TCTR_GENCALL_EN                                          0x00000002U
/*

        Field:           CLKSTRETCH
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Target clock stretch enable

        ENUMs:
            EN:                          Target clock stretching is enabled
            DIS:                         Target clock stretching is disabled
*/
#define I2C_TCTR_CLKSTRETCH                                          0x00000004U
#define I2C_TCTR_CLKSTRETCH_M                                        0x00000004U
#define I2C_TCTR_CLKSTRETCH_S                                        2U
#define I2C_TCTR_CLKSTRETCH_EN                                       0x00000004U
#define I2C_TCTR_CLKSTRETCH_DIS                                      0x00000000U
/*

        Field:           TXEMPTYONTREQ
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tx Empty Interrupt on TREQ

        ENUMs:
            EN:                          [RIS.STXEMPTY] will be set when the Target State Machine is in the TX_WAIT state which occurs when the TX FIFO is empty and the transaction is clock stretched waiting for the FIFO to receive data.
            DIS:                         [RIS.TTXEMPTY] will be set when only the target TX FIFO is empty.
                         This allows the [RIS.TTXEMPTY] interrupt to be used to indicate that the bus is being clock stretched and that target TX data is required.
*/
#define I2C_TCTR_TXEMPTYONTREQ                                       0x00000008U
#define I2C_TCTR_TXEMPTYONTREQ_M                                     0x00000008U
#define I2C_TCTR_TXEMPTYONTREQ_S                                     3U
#define I2C_TCTR_TXEMPTYONTREQ_EN                                    0x00000008U
#define I2C_TCTR_TXEMPTYONTREQ_DIS                                   0x00000000U
/*

        Field:           TXTRIGXMODE
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tx trigger when target FSM is in TX mode

        ENUMs:
            EN:                          [RIS.TXFIFOTRG] will be set when the Target TX FIFO has reached the trigger level AND the target state machine is in the as defined in the [TSR.TXMODE] field.
                         When cleared [RIS.TXFIFOTRG] will be set when the Target TX FIFO is at or above the trigger level.
                         This setting can be used to hold off the TX DMA until a transaction starts.
                         This allows the DMA to be configured when the *I2C* is idle but have it wait till the transaction starts to load the Target TX FIFO, so it can load from a memory buffer that might be changing over time.
            DIS:                         No special behavior
*/
#define I2C_TCTR_TXTRIGXMODE                                         0x00000010U
#define I2C_TCTR_TXTRIGXMODE_M                                       0x00000010U
#define I2C_TCTR_TXTRIGXMODE_S                                       4U
#define I2C_TCTR_TXTRIGXMODE_EN                                      0x00000010U
#define I2C_TCTR_TXTRIGXMODE_DIS                                     0x00000000U
/*

        Field:           TXWAITSTALETXFIFO
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tx transfer waits when stale data in Tx FIFO.
                         This prevents stale bytes left in the TX FIFO from automatically being sent on the next I2C packet. Note: this should be used with [TCTR:TXEMPTY_ON_TREQ] set to prevent the Target State Machine from waiting for TX FIFO data without an interrupt notification when the FIFO data is stale.

        ENUMs:
            EN:                          The TX FIFO empty signal to the Target State Machine will indicate that the TX FIFO is empty or that the TX FIFO data is stale. The TX FIFO data is determined to be stale when there is data in the TX FIFO when the target state machine leaves the [TSR.TXMODE] field. This can occur is a stop or timeout occur when there are bytes left in the TX FIFO.
            DIS:                         The TX FIFO empty signal to the Target State Machine indicates that the TX FIFO is empty.
*/
#define I2C_TCTR_TXWAITSTALETXFIFO                                   0x00000020U
#define I2C_TCTR_TXWAITSTALETXFIFO_M                                 0x00000020U
#define I2C_TCTR_TXWAITSTALETXFIFO_S                                 5U
#define I2C_TCTR_TXWAITSTALETXFIFO_EN                                0x00000020U
#define I2C_TCTR_TXWAITSTALETXFIFO_DIS                               0x00000000U
/*

        Field:           RXFULLONRREQ
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Rx full interrupt generated based on [TSR.RREQ] filed.

        ENUMs:
            EN:                           [RIS.SRXFULL] will be set when the target state machine is in the RX_WAIT or RX_ACK_WAIT states which occurs when the transaction is clock stretched because the RX FIFO is full or the ACKOEN has been set and the state machine is waiting for FW to ACK/NACK the current byte.
            DIS:                         [RIS.TRXFULL] will be set when only the Target RX FIFO is full.
                         This allows the [RIS.TRXFULL] interrupt to be used to indicate that the I2C bus is being clock stretched and that the FW must either read the RX FIFO or ACK/NACK the current RX byte.
*/
#define I2C_TCTR_RXFULLONRREQ                                        0x00000040U
#define I2C_TCTR_RXFULLONRREQ_M                                      0x00000040U
#define I2C_TCTR_RXFULLONRREQ_S                                      6U
#define I2C_TCTR_RXFULLONRREQ_EN                                     0x00000040U
#define I2C_TCTR_RXFULLONRREQ_DIS                                    0x00000000U
/*

        Field:           ENALRESPADR
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable alert response address

        ENUMs:
            EN:                          Alert response address of 7'h000_1100 is always matched by the target address match logic.
            DIS:                         The alert response address is not matched.
                          NOTE: It may still be matched if programmed inside [TOAR]/[TOAR2]
*/
#define I2C_TCTR_ENALRESPADR                                         0x00000100U
#define I2C_TCTR_ENALRESPADR_M                                       0x00000100U
#define I2C_TCTR_ENALRESPADR_S                                       8U
#define I2C_TCTR_ENALRESPADR_EN                                      0x00000100U
#define I2C_TCTR_ENALRESPADR_DIS                                     0x00000000U
/*

        Field:           ENDEFDEVADR
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable default device address

        ENUMs:
            EN:                          When this field is 1, default device address of 7'h110_0001 is always matched by the target address match logic.
            DIS:                         When this field is 0, the default device address is not matched. NOTE: it may still be matched if programmed inside TOAR/TOAR2.
*/
#define I2C_TCTR_ENDEFDEVADR                                         0x00000200U
#define I2C_TCTR_ENDEFDEVADR_M                                       0x00000200U
#define I2C_TCTR_ENDEFDEVADR_S                                       9U
#define I2C_TCTR_ENDEFDEVADR_EN                                      0x00000200U
#define I2C_TCTR_ENDEFDEVADR_DIS                                     0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TSR
    Offset name:         I2C_O_TSR
    Relative address:    0x128
    Description:         Target status register
    Default Value:       0x00000000

        Field:           RREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive Request

        ENUMs:
            CLEAR:                       No outstanding receive data.
            SET:                         The controller has outstanding receive data and is using clock stretching to delay the controller until the data has been read from the RXDATA FIFO (target RX FIFO is full).
*/
#define I2C_TSR_RREQ                                                 0x00000001U
#define I2C_TSR_RREQ_M                                               0x00000001U
#define I2C_TSR_RREQ_S                                               0U
#define I2C_TSR_RREQ_CLEAR                                           0x00000000U
#define I2C_TSR_RREQ_SET                                             0x00000001U
/*

        Field:           TREQ
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit Request

        ENUMs:
            CLEAR:                       No outstanding transmit request.
            SET:                         The controller has been addressed as a target transmitter and is using clock stretching to delay the controller until data has been written to the TXDATA FIFO (Target TX FIFO is empty).
*/
#define I2C_TSR_TREQ                                                 0x00000002U
#define I2C_TSR_TREQ_M                                               0x00000002U
#define I2C_TSR_TREQ_S                                               1U
#define I2C_TSR_TREQ_CLEAR                                           0x00000000U
#define I2C_TSR_TREQ_SET                                             0x00000002U
/*

        Field:           RXMODE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target FSM is in RX MODE

        ENUMs:
            SET:                         The target state machine is in the RX_DATA, RX_ACK, RX_WAIT, RX_ACK_WAIT or ADDR_ACK state with the bus direction set to write.
            CLEAR:                       The target state machine is not in the RX_DATA, RX_ACK, RX_WAIT, RX_ACK_WAIT or ADDR_ACK state with the bus direction set to write.
*/
#define I2C_TSR_RXMODE                                               0x00000004U
#define I2C_TSR_RXMODE_M                                             0x00000004U
#define I2C_TSR_RXMODE_S                                             2U
#define I2C_TSR_RXMODE_SET                                           0x00000004U
#define I2C_TSR_RXMODE_CLEAR                                         0x00000000U
/*

        Field:           OAR2SEL
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     OAR2 address matched
                          This field gets re-evaluated after every address comparison.

        ENUMs:
            CLEAR:                       Either the OAR2 address is not matched or the match is in legacy mode.
            SET:                         OAR2 address matched and acknowledged by the target.
*/
#define I2C_TSR_OAR2SEL                                              0x00000008U
#define I2C_TSR_OAR2SEL_M                                            0x00000008U
#define I2C_TSR_OAR2SEL_S                                            3U
#define I2C_TSR_OAR2SEL_CLEAR                                        0x00000000U
#define I2C_TSR_OAR2SEL_SET                                          0x00000008U
/*

        Field:           BUSBSY
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus is busy

        ENUMs:
            SET:                         Bus is busy. This is cleared on a timeout.
            CLEAR:                       Bus is not busy
*/
#define I2C_TSR_BUSBSY                                               0x00000040U
#define I2C_TSR_BUSBSY_M                                             0x00000040U
#define I2C_TSR_BUSBSY_S                                             6U
#define I2C_TSR_BUSBSY_SET                                           0x00000040U
#define I2C_TSR_BUSBSY_CLEAR                                         0x00000000U
/*

        Field:           TXMODE
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target FSM is in TX MODE

        ENUMs:
            SET:                         The target state machine is in TX_DATA, TX_WAIT, TX_ACK  or ADDR_ACK state with the bus direction set to read.
            CLEAR:                       The target state machine is not in TX_DATA, TX_WAIT, TX_ACK  or ADDR_ACK state with the bus direction set to read.
*/
#define I2C_TSR_TXMODE                                               0x00000080U
#define I2C_TSR_TXMODE_M                                             0x00000080U
#define I2C_TSR_TXMODE_S                                             7U
#define I2C_TSR_TXMODE_SET                                           0x00000080U
#define I2C_TSR_TXMODE_CLEAR                                         0x00000000U
/*

        Field:           STALETXFIFO
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Stale TX FIFO

        ENUMs:
            SET:                         The TX FIFO is stale. This occurs when the TX FIFO was not emptied during the previous transaction.
            CLEAR:                       Tx FIFO is not stale
*/
#define I2C_TSR_STALETXFIFO                                          0x00000100U
#define I2C_TSR_STALETXFIFO_M                                        0x00000100U
#define I2C_TSR_STALETXFIFO_S                                        8U
#define I2C_TSR_STALETXFIFO_SET                                      0x00000100U
#define I2C_TSR_STALETXFIFO_CLEAR                                    0x00000000U
/*

        Field:           ADDRMATCH
        From..to bits:   9...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates the address for which target address match happened

        ENUMs:
            MINIMUM:                     Minimum Value
            MAXIMUM:                     Maximum Value
*/
#define I2C_TSR_ADDRMATCH_W                                          10U
#define I2C_TSR_ADDRMATCH_M                                          0x0007FE00U
#define I2C_TSR_ADDRMATCH_S                                          9U
#define I2C_TSR_ADDRMATCH_MINIMUM                                    0x00000000U
#define I2C_TSR_ADDRMATCH_MAXIMUM                                    0x0007FE00U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXDATA
    Offset name:         I2C_O_RXDATA
    Relative address:    0x12C
    Description:         RX FIFO read data byte
                        This field contains the current byte being read in the RX FIFO stack.
                        If the FIFO is disabled, the data byte and status are stored in the receiving holding register (the bottom word of the receive FIFO). The received data can be retrieved by reading this register.
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Received Data.

                         This field contains the last received data.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_RXDATA_VALUE_W                                           8U
#define I2C_RXDATA_VALUE_M                                           0x000000FFU
#define I2C_RXDATA_VALUE_S                                           0U
#define I2C_RXDATA_VALUE_MINIMUM                                     0x00000000U
#define I2C_RXDATA_VALUE_MAXIMUM                                     0x000000FFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXDATA
    Offset name:         I2C_O_TXDATA
    Relative address:    0x130
    Description:         Transmit data register.
                        This register is the transmit data register (the interface to the FIFOs). For transmitted data, if the FIFO is enabled, data written to this location is pushed onto the transmit FIFO. If the FIFO is disabled, data is stored in the transmitter holding register (the bottom word of the transmit FIFO).
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit data
                         This byte contains the data to be transferred during the next transaction.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_TXDATA_VALUE_W                                           8U
#define I2C_TXDATA_VALUE_M                                           0x000000FFU
#define I2C_TXDATA_VALUE_S                                           0U
#define I2C_TXDATA_VALUE_MINIMUM                                     0x00000000U
#define I2C_TXDATA_VALUE_MAXIMUM                                     0x000000FFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       TACKCTL
    Offset name:         I2C_O_TACKCTL
    Relative address:    0x134
    Description:         This register enables the target to not acknowledge (NACK) for invalid data or command or acknowledge (ACK) for valid data or command. The *I2C* clock is pulled low after the last data field until this register is written.
    Default Value:       0x00000000

        Field:           ACKOEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target ACK override enable

        ENUMs:
            DIS:                         A response in not provided.
            EN:                          An ACK or NACK is sent according to the value written to the ACKOVAL field.
*/
#define I2C_TACKCTL_ACKOEN                                           0x00000001U
#define I2C_TACKCTL_ACKOEN_M                                         0x00000001U
#define I2C_TACKCTL_ACKOEN_S                                         0U
#define I2C_TACKCTL_ACKOEN_DIS                                       0x00000000U
#define I2C_TACKCTL_ACKOEN_EN                                        0x00000001U
/*

        Field:           ACKOVAL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target ACK override Value

                         Note: For general call this field will be ignored if set to NACK and target continues to receive data.

        ENUMs:
            DIS:                         An ACK is sent indicating valid data or command.
            EN:                          A NACK is sent indicating invalid data or command.
*/
#define I2C_TACKCTL_ACKOVAL                                          0x00000002U
#define I2C_TACKCTL_ACKOVAL_M                                        0x00000002U
#define I2C_TACKCTL_ACKOVAL_S                                        1U
#define I2C_TACKCTL_ACKOVAL_DIS                                      0x00000000U
#define I2C_TACKCTL_ACKOVAL_EN                                       0x00000002U
/*

        Field:           ACKOENONSTART
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When set this field will automatically turn on the target ACKOEN field following a start condition.

        ENUMs:
            EN:                          When set this field will automatically turn on the Target ACKOEN field following a start condition.
            DIS:                         No special behavior
*/
#define I2C_TACKCTL_ACKOENONSTART                                    0x00000004U
#define I2C_TACKCTL_ACKOENONSTART_M                                  0x00000004U
#define I2C_TACKCTL_ACKOENONSTART_S                                  2U
#define I2C_TACKCTL_ACKOENONSTART_EN                                 0x00000004U
#define I2C_TACKCTL_ACKOENONSTART_DIS                                0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOCTL
    Offset name:         I2C_O_FIFOCTL
    Relative address:    0x138
    Description:         Target FIFO control
    Default Value:       0x00000000

        Field:           TXTRIG
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX FIFO trigger
                         Indicates at what fill level in the TX FIFO a trigger will be generated.

        ENUMs:
            EMPTY:                       Trigger when the TX FIFO is empty.
            LEVEL_1:                     Trigger when TX FIFO contains bigger or equal to 1 byte
            LEVEL_2:                     Trigger when TX FIFO contains bigger or equal to 2 byte
            LEVEL_3:                     Trigger when TX FIFO contains bigger or equal to 3 byte
            LEVEL_6:                     Trigger when TX FIFO contains bigger or equal to 6 byte
            LEVEL_4:                     Trigger when TX FIFO contains bigger or equal to  4 byte
            LEVEL_5:                     Trigger when TX FIFO contains bigger or equal to  5 byte
            LEVEL_7:                     Trigger when TX FIFO contains bigger or equal to  7 byte
*/
#define I2C_FIFOCTL_TXTRIG_W                                         3U
#define I2C_FIFOCTL_TXTRIG_M                                         0x00000007U
#define I2C_FIFOCTL_TXTRIG_S                                         0U
#define I2C_FIFOCTL_TXTRIG_EMPTY                                     0x00000000U
#define I2C_FIFOCTL_TXTRIG_LEVEL_1                                   0x00000001U
#define I2C_FIFOCTL_TXTRIG_LEVEL_2                                   0x00000002U
#define I2C_FIFOCTL_TXTRIG_LEVEL_3                                   0x00000003U
#define I2C_FIFOCTL_TXTRIG_LEVEL_6                                   0x00000006U
#define I2C_FIFOCTL_TXTRIG_LEVEL_4                                   0x00000004U
#define I2C_FIFOCTL_TXTRIG_LEVEL_5                                   0x00000005U
#define I2C_FIFOCTL_TXTRIG_LEVEL_7                                   0x00000007U
/*

        Field:           TXFLUSH
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX FIFO flush
                         Setting this field will flush the TX FIFO.
                         Before resetting this field to stop flush the TXFIFOCNT should be checked to be 8 and indicating that the flush has completed.

        ENUMs:
            DIS:                         Do not flush FIFO
            EN:                          flush FIFO
*/
#define I2C_FIFOCTL_TXFLUSH                                          0x00000080U
#define I2C_FIFOCTL_TXFLUSH_M                                        0x00000080U
#define I2C_FIFOCTL_TXFLUSH_S                                        7U
#define I2C_FIFOCTL_TXFLUSH_DIS                                      0x00000000U
#define I2C_FIFOCTL_TXFLUSH_EN                                       0x00000080U
/*

        Field:           RXTRIG
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX FIFO trigger
                         Indicates at what fill level in the RX FIFO a trigger will be generated.
                         Note: Programming this field to 0x0 has no effect since no data is
                         present to transfer out of RX FIFO.

        ENUMs:
            LEVEL_1:                     Trigger when RX FIFO contains >= 1 byte
            LEVEL_2:                     Trigger when RX FIFO contains >= 2 byte
            LEVEL_3:                     Trigger when RX FIFO contains >= 3 byte
            LEVEL_4:                     Trigger when RX FIFO contains >= 4 byte
            LEVEL_5:                     Trigger when RX FIFO contains >= 5 byte
            LEVEL_6:                     Trigger when RX FIFO contains >= 6 byte
            LEVEL_7:                     Trigger when RX FIFO contains >= 7 byte
            LEVEL_8:                     Trigger when RX FIFO contains >= 8 byte
*/
#define I2C_FIFOCTL_RXTRIG_W                                         3U
#define I2C_FIFOCTL_RXTRIG_M                                         0x00000700U
#define I2C_FIFOCTL_RXTRIG_S                                         8U
#define I2C_FIFOCTL_RXTRIG_LEVEL_1                                   0x00000000U
#define I2C_FIFOCTL_RXTRIG_LEVEL_2                                   0x00000100U
#define I2C_FIFOCTL_RXTRIG_LEVEL_3                                   0x00000200U
#define I2C_FIFOCTL_RXTRIG_LEVEL_4                                   0x00000300U
#define I2C_FIFOCTL_RXTRIG_LEVEL_5                                   0x00000400U
#define I2C_FIFOCTL_RXTRIG_LEVEL_6                                   0x00000500U
#define I2C_FIFOCTL_RXTRIG_LEVEL_7                                   0x00000600U
#define I2C_FIFOCTL_RXTRIG_LEVEL_8                                   0x00000700U
/*

        Field:           RXFLUSH
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX FIFO flush
                         Setting this field will flush the RX FIFO.
                         Before resetting this field to stop flush the [FIFOSR.RXFIFOCNT] should be checked to be 0 and indicating that the flush has completed.

        ENUMs:
            DIS:                         Do not flush FIFO
            EN:                          Flush FIFO
*/
#define I2C_FIFOCTL_RXFLUSH                                          0x00008000U
#define I2C_FIFOCTL_RXFLUSH_M                                        0x00008000U
#define I2C_FIFOCTL_RXFLUSH_S                                        15U
#define I2C_FIFOCTL_RXFLUSH_DIS                                      0x00000000U
#define I2C_FIFOCTL_RXFLUSH_EN                                       0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOSR
    Offset name:         I2C_O_FIFOSR
    Relative address:    0x13C
    Description:         FIFO status register
                        Note: This register should only be read when BUSY is 0
    Default Value:       0x00000800

        Field:           RXFIFOCNT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes which could be read from the RX FIFO

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_FIFOSR_RXFIFOCNT_W                                       4U
#define I2C_FIFOSR_RXFIFOCNT_M                                       0x0000000FU
#define I2C_FIFOSR_RXFIFOCNT_S                                       0U
#define I2C_FIFOSR_RXFIFOCNT_MINIMUM                                 0x00000000U
#define I2C_FIFOSR_RXFIFOCNT_MAXIMUM                                 0x00000008U
/*

        Field:           RXFLUSH
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO flush
                         When this field is set a flush operation for the RX FIFO is active. Clear the [FIFOCTL.RXFLUSH] field to stop.

        ENUMs:
            CLEAR:                       FIFO flush not active
            SET:                         FIFO flush active
*/
#define I2C_FIFOSR_RXFLUSH                                           0x00000080U
#define I2C_FIFOSR_RXFLUSH_M                                         0x00000080U
#define I2C_FIFOSR_RXFLUSH_S                                         7U
#define I2C_FIFOSR_RXFLUSH_CLEAR                                     0x00000000U
#define I2C_FIFOSR_RXFLUSH_SET                                       0x00000080U
/*

        Field:           TXFIFOCNT
        From..to bits:   8...11
        DefaultValue:    0x8
        Access type:     read-only
        Description:     Number of bytes which could be put into the TX FIFO

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_FIFOSR_TXFIFOCNT_W                                       4U
#define I2C_FIFOSR_TXFIFOCNT_M                                       0x00000F00U
#define I2C_FIFOSR_TXFIFOCNT_S                                       8U
#define I2C_FIFOSR_TXFIFOCNT_MINIMUM                                 0x00000000U
#define I2C_FIFOSR_TXFIFOCNT_MAXIMUM                                 0x00000800U
/*

        Field:           TXFLUSH
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO flush
                         When this field is set a flush operation for the TX FIFO is active. Clear [FIFOCTL.TXFLUSH] to stop.

        ENUMs:
            CLEAR:                       FIFO flush not active
            SET:                         FIFO flush active
*/
#define I2C_FIFOSR_TXFLUSH                                           0x00008000U
#define I2C_FIFOSR_TXFLUSH_M                                         0x00008000U
#define I2C_FIFOSR_TXFLUSH_S                                         15U
#define I2C_FIFOSR_TXFLUSH_CLEAR                                     0x00000000U
#define I2C_FIFOSR_TXFLUSH_SET                                       0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FCLKDIV
    Offset name:         I2C_O_FCLKDIV
    Relative address:    0x140
    Description:         Register for the selection of divider value to generate functional clock from SVT clock
    Default Value:       NA

        Field:           FCLKDIV
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Divider value selection

        ENUMs:
            BY_1:                        Divide by 1 = 80MHz
            BY_2:                        Divide by 2 = 40MHz
            BY_4:                        Divide by 4 = 20MHz
            BY_5:                        Divide by 5 = 16MHz
            BY_8:                        Divide by 8 = 10MHz
            BY_10:                       Divide by 10 = 8MHz
            BY_16:                       Divide by 16 = 5MHz
            BY_20:                       Divide by 20 = 4MHz
            BY_25:                       Divide by 25 = 3.2MHz
            BY_32:                       Divide by 32 = 2.5MHz
            BY_40:                       Divide by 40 = 2MHz
            BY_80:                       Divide by 80 = 1MHz
*/
#define I2C_FCLKDIV_FCLKDIV_W                                        4U
#define I2C_FCLKDIV_FCLKDIV_M                                        0x0000000FU
#define I2C_FCLKDIV_FCLKDIV_S                                        0U
#define I2C_FCLKDIV_FCLKDIV_BY_1                                     0x00000000U
#define I2C_FCLKDIV_FCLKDIV_BY_2                                     0x00000001U
#define I2C_FCLKDIV_FCLKDIV_BY_4                                     0x00000002U
#define I2C_FCLKDIV_FCLKDIV_BY_5                                     0x00000003U
#define I2C_FCLKDIV_FCLKDIV_BY_8                                     0x00000004U
#define I2C_FCLKDIV_FCLKDIV_BY_10                                    0x00000005U
#define I2C_FCLKDIV_FCLKDIV_BY_16                                    0x00000006U
#define I2C_FCLKDIV_FCLKDIV_BY_20                                    0x00000007U
#define I2C_FCLKDIV_FCLKDIV_BY_25                                    0x00000008U
#define I2C_FCLKDIV_FCLKDIV_BY_32                                    0x00000009U
#define I2C_FCLKDIV_FCLKDIV_BY_40                                    0x0000000AU
#define I2C_FCLKDIV_FCLKDIV_BY_80                                    0x0000000BU


/*-----------------------------------REGISTER------------------------------------
    Register name:       PDBGCTL
    Offset name:         I2C_O_PDBGCTL
    Relative address:    0x0
    Description:         This register can be used by the software developer to control the behavior of the peripheral relative to the 'Core Halted' input
    Default Value:       0x00000001

        Field:           FREE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Free run control

        ENUMs:
            DIS:                         The peripheral freezes functionality while the Core Halted input is asserted and resumes when it is deasserted.
            EN:                          The peripheral ignores the state of the Core Halted input
*/
#define I2C_PDBGCTL_FREE                                             0x00000001U
#define I2C_PDBGCTL_FREE_M                                           0x00000001U
#define I2C_PDBGCTL_FREE_S                                           0U
#define I2C_PDBGCTL_FREE_DIS                                         0x00000000U
#define I2C_PDBGCTL_FREE_EN                                          0x00000001U
/*

        Field:           SOFT
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Soft halt boundary control. This function is only available, if FREE is set to 'STOP'

        ENUMs:
            DIS:                         The peripheral will halt immediately, even if the resultant state will result in corruption if the system is restarted
            EN:                          The peripheral blocks the debug freeze until it has reached a boundary where it can resume without corruption
*/
#define I2C_PDBGCTL_SOFT                                             0x00000002U
#define I2C_PDBGCTL_SOFT_M                                           0x00000002U
#define I2C_PDBGCTL_SOFT_S                                           1U
#define I2C_PDBGCTL_SOFT_DIS                                         0x00000000U
#define I2C_PDBGCTL_SOFT_EN                                          0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_IMASK
    Offset name:         I2C_O_EVENT0_IMASK
    Relative address:    0x4
    Description:         Interrupt Mask. If a field is set, then corresponding interrupt is masked. Un-masking the interrupt causes the raw interrupt to be visible in [RIS], as well as [MIS].
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller receive transaction completed Interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CRXDONE                                     0x00000001U
#define I2C_EVENT0_IMASK_CRXDONE_M                                   0x00000001U
#define I2C_EVENT0_IMASK_CRXDONE_S                                   0U
#define I2C_EVENT0_IMASK_CRXDONE_EN                                  0x00000001U
#define I2C_EVENT0_IMASK_CRXDONE_DIS                                 0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller transmit transaction completed Interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CTXDONE                                     0x00000002U
#define I2C_EVENT0_IMASK_CTXDONE_M                                   0x00000002U
#define I2C_EVENT0_IMASK_CTXDONE_S                                   1U
#define I2C_EVENT0_IMASK_CTXDONE_EN                                  0x00000002U
#define I2C_EVENT0_IMASK_CTXDONE_DIS                                 0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive FIFO trigger in controller code
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_RXFIFOTRGC                                  0x00000004U
#define I2C_EVENT0_IMASK_RXFIFOTRGC_M                                0x00000004U
#define I2C_EVENT0_IMASK_RXFIFOTRGC_S                                2U
#define I2C_EVENT0_IMASK_RXFIFOTRGC_EN                               0x00000004U
#define I2C_EVENT0_IMASK_RXFIFOTRGC_DIS                              0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit FIFO trigger in controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TXFIFOTRGC                                  0x00000008U
#define I2C_EVENT0_IMASK_TXFIFOTRGC_M                                0x00000008U
#define I2C_EVENT0_IMASK_TXFIFOTRGC_S                                3U
#define I2C_EVENT0_IMASK_TXFIFOTRGC_EN                               0x00000008U
#define I2C_EVENT0_IMASK_TXFIFOTRGC_DIS                              0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RXFIFO full event in controller mode. This interrupt is set if an RX FIFO is full in controller mode.

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_RXFIFOFULLC                                 0x00000010U
#define I2C_EVENT0_IMASK_RXFIFOFULLC_M                               0x00000010U
#define I2C_EVENT0_IMASK_RXFIFOFULLC_S                               4U
#define I2C_EVENT0_IMASK_RXFIFOFULLC_EN                              0x00000010U
#define I2C_EVENT0_IMASK_RXFIFOFULLC_DIS                             0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TXFIFO empty interrupt in controller mode. This interrupt is set if all data in the TX FIFO in controller mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TXEMPTYC                                    0x00000020U
#define I2C_EVENT0_IMASK_TXEMPTYC_M                                  0x00000020U
#define I2C_EVENT0_IMASK_TXEMPTYC_S                                  5U
#define I2C_EVENT0_IMASK_TXEMPTYC_EN                                 0x00000020U
#define I2C_EVENT0_IMASK_TXEMPTYC_DIS                                0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Address/Data NACK interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CNACK                                       0x00000040U
#define I2C_EVENT0_IMASK_CNACK_M                                     0x00000040U
#define I2C_EVENT0_IMASK_CNACK_S                                     6U
#define I2C_EVENT0_IMASK_CNACK_EN                                    0x00000040U
#define I2C_EVENT0_IMASK_CNACK_DIS                                   0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     START detection interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CSTART                                      0x00000080U
#define I2C_EVENT0_IMASK_CSTART_M                                    0x00000080U
#define I2C_EVENT0_IMASK_CSTART_S                                    7U
#define I2C_EVENT0_IMASK_CSTART_EN                                   0x00000080U
#define I2C_EVENT0_IMASK_CSTART_DIS                                  0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     STOP detection interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CSTOP                                       0x00000100U
#define I2C_EVENT0_IMASK_CSTOP_M                                     0x00000100U
#define I2C_EVENT0_IMASK_CSTOP_S                                     8U
#define I2C_EVENT0_IMASK_CSTOP_EN                                    0x00000100U
#define I2C_EVENT0_IMASK_CSTOP_DIS                                   0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Arbitration lost interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_CARBLOST                                    0x00000200U
#define I2C_EVENT0_IMASK_CARBLOST_M                                  0x00000200U
#define I2C_EVENT0_IMASK_CARBLOST_S                                  9U
#define I2C_EVENT0_IMASK_CARBLOST_EN                                 0x00000200U
#define I2C_EVENT0_IMASK_CARBLOST_DIS                                0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TRXDONE                                     0x00010000U
#define I2C_EVENT0_IMASK_TRXDONE_M                                   0x00010000U
#define I2C_EVENT0_IMASK_TRXDONE_S                                   16U
#define I2C_EVENT0_IMASK_TRXDONE_EN                                  0x00010000U
#define I2C_EVENT0_IMASK_TRXDONE_DIS                                 0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TTXDONE                                     0x00020000U
#define I2C_EVENT0_IMASK_TTXDONE_M                                   0x00020000U
#define I2C_EVENT0_IMASK_TTXDONE_S                                   17U
#define I2C_EVENT0_IMASK_TTXDONE_EN                                  0x00020000U
#define I2C_EVENT0_IMASK_TTXDONE_DIS                                 0x00000000U
/*

        Field:           RXFIFOTRGMT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX FIFO trigger in target mode

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_RXFIFOTRGMT                                 0x00040000U
#define I2C_EVENT0_IMASK_RXFIFOTRGMT_M                               0x00040000U
#define I2C_EVENT0_IMASK_RXFIFOTRGMT_S                               18U
#define I2C_EVENT0_IMASK_RXFIFOTRGMT_EN                              0x00040000U
#define I2C_EVENT0_IMASK_RXFIFOTRGMT_DIS                             0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX FIFO trigger in target mode

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TXFIFOTRGT                                  0x00080000U
#define I2C_EVENT0_IMASK_TXFIFOTRGT_M                                0x00080000U
#define I2C_EVENT0_IMASK_TXFIFOTRGT_S                                19U
#define I2C_EVENT0_IMASK_TXFIFOTRGT_EN                               0x00080000U
#define I2C_EVENT0_IMASK_TXFIFOTRGT_DIS                              0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX FIFO full event. This interrupt is set if an target RX FIFO is full in target mode.

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_RXFIFOFULLT                                 0x00100000U
#define I2C_EVENT0_IMASK_RXFIFOFULLT_M                               0x00100000U
#define I2C_EVENT0_IMASK_RXFIFOFULLT_S                               20U
#define I2C_EVENT0_IMASK_RXFIFOFULLT_EN                              0x00100000U
#define I2C_EVENT0_IMASK_RXFIFOFULLT_DIS                             0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the Transmit FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TXEMPTYT                                    0x00200000U
#define I2C_EVENT0_IMASK_TXEMPTYT_M                                  0x00200000U
#define I2C_EVENT0_IMASK_TXEMPTYT_S                                  21U
#define I2C_EVENT0_IMASK_TXEMPTYT_EN                                 0x00200000U
#define I2C_EVENT0_IMASK_TXEMPTYT_DIS                                0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target start condition interrupt. Asserted when the received address matches the target address

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TSTART                                      0x00400000U
#define I2C_EVENT0_IMASK_TSTART_M                                    0x00400000U
#define I2C_EVENT0_IMASK_TSTART_S                                    22U
#define I2C_EVENT0_IMASK_TSTART_EN                                   0x00400000U
#define I2C_EVENT0_IMASK_TSTART_DIS                                  0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Stop condition interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TSTOP                                       0x00800000U
#define I2C_EVENT0_IMASK_TSTOP_M                                     0x00800000U
#define I2C_EVENT0_IMASK_TSTOP_S                                     23U
#define I2C_EVENT0_IMASK_TSTOP_EN                                    0x00800000U
#define I2C_EVENT0_IMASK_TSTOP_DIS                                   0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     General call interrupt

        ENUMs:
            EN:                          Set Interrrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TGENCALL                                    0x01000000U
#define I2C_EVENT0_IMASK_TGENCALL_M                                  0x01000000U
#define I2C_EVENT0_IMASK_TGENCALL_S                                  24U
#define I2C_EVENT0_IMASK_TGENCALL_EN                                 0x01000000U
#define I2C_EVENT0_IMASK_TGENCALL_DIS                                0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX FIFO underflow in target mode

        ENUMs:
            EN:                          Set Interrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TX_UNFL_T                                   0x02000000U
#define I2C_EVENT0_IMASK_TX_UNFL_T_M                                 0x02000000U
#define I2C_EVENT0_IMASK_TX_UNFL_T_S                                 25U
#define I2C_EVENT0_IMASK_TX_UNFL_T_EN                                0x02000000U
#define I2C_EVENT0_IMASK_TX_UNFL_T_DIS                               0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX FIFO overflow in target mode

        ENUMs:
            EN:                          Set Interrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_RX_OVFL_T                                   0x04000000U
#define I2C_EVENT0_IMASK_RX_OVFL_T_M                                 0x04000000U
#define I2C_EVENT0_IMASK_RX_OVFL_T_S                                 26U
#define I2C_EVENT0_IMASK_RX_OVFL_T_EN                                0x04000000U
#define I2C_EVENT0_IMASK_RX_OVFL_T_DIS                               0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Target arbitration lost

        ENUMs:
            EN:                          Set Interrupt Mask
            DIS:                         Clear Interrupt Mask
*/
#define I2C_EVENT0_IMASK_TARBLOST                                    0x08000000U
#define I2C_EVENT0_IMASK_TARBLOST_M                                  0x08000000U
#define I2C_EVENT0_IMASK_TARBLOST_S                                  27U
#define I2C_EVENT0_IMASK_TARBLOST_EN                                 0x08000000U
#define I2C_EVENT0_IMASK_TARBLOST_DIS                                0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_RIS
    Offset name:         I2C_O_EVENT0_RIS
    Relative address:    0x8
    Description:         Raw interrupt status. Reflects all pending interrupts, regardless of masking. The RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the [ICLR] register field even if the corresponding [IMASK] field is not enabled.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller receive transaction completed interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CRXDONE                                       0x00000001U
#define I2C_EVENT0_RIS_CRXDONE_M                                     0x00000001U
#define I2C_EVENT0_RIS_CRXDONE_S                                     0U
#define I2C_EVENT0_RIS_CRXDONE_SET                                   0x00000001U
#define I2C_EVENT0_RIS_CRXDONE_CLR                                   0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CTXDONE                                       0x00000002U
#define I2C_EVENT0_RIS_CTXDONE_M                                     0x00000002U
#define I2C_EVENT0_RIS_CTXDONE_S                                     1U
#define I2C_EVENT0_RIS_CTXDONE_SET                                   0x00000002U
#define I2C_EVENT0_RIS_CTXDONE_CLR                                   0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_RXFIFOTRGC                                    0x00000004U
#define I2C_EVENT0_RIS_RXFIFOTRGC_M                                  0x00000004U
#define I2C_EVENT0_RIS_RXFIFOTRGC_S                                  2U
#define I2C_EVENT0_RIS_RXFIFOTRGC_SET                                0x00000004U
#define I2C_EVENT0_RIS_RXFIFOTRGC_CLR                                0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO Trigger in Transmit Mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TXFIFOTRGC                                    0x00000008U
#define I2C_EVENT0_RIS_TXFIFOTRGC_M                                  0x00000008U
#define I2C_EVENT0_RIS_TXFIFOTRGC_S                                  3U
#define I2C_EVENT0_RIS_TXFIFOTRGC_SET                                0x00000008U
#define I2C_EVENT0_RIS_TXFIFOTRGC_CLR                                0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO full event in controller mode. This interrupt is set if an RX FIFO is full in controller mode.

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_RXFIFOFULLC                                   0x00000010U
#define I2C_EVENT0_RIS_RXFIFOFULLC_M                                 0x00000010U
#define I2C_EVENT0_RIS_RXFIFOFULLC_S                                 4U
#define I2C_EVENT0_RIS_RXFIFOFULLC_SET                               0x00000010U
#define I2C_EVENT0_RIS_RXFIFOFULLC_CLR                               0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO empty interrupt mask in controller mode. This interrupt is set if all data in the TX FIFO in controller mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TXEMPTYC                                      0x00000020U
#define I2C_EVENT0_RIS_TXEMPTYC_M                                    0x00000020U
#define I2C_EVENT0_RIS_TXEMPTYC_S                                    5U
#define I2C_EVENT0_RIS_TXEMPTYC_SET                                  0x00000020U
#define I2C_EVENT0_RIS_TXEMPTYC_CLR                                  0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CNACK                                         0x00000040U
#define I2C_EVENT0_RIS_CNACK_M                                       0x00000040U
#define I2C_EVENT0_RIS_CNACK_S                                       6U
#define I2C_EVENT0_RIS_CNACK_SET                                     0x00000040U
#define I2C_EVENT0_RIS_CNACK_CLR                                     0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:      START detection interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CSTART                                        0x00000080U
#define I2C_EVENT0_RIS_CSTART_M                                      0x00000080U
#define I2C_EVENT0_RIS_CSTART_S                                      7U
#define I2C_EVENT0_RIS_CSTART_SET                                    0x00000080U
#define I2C_EVENT0_RIS_CSTART_CLR                                    0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:      STOP detection interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CSTOP                                         0x00000100U
#define I2C_EVENT0_RIS_CSTOP_M                                       0x00000100U
#define I2C_EVENT0_RIS_CSTOP_S                                       8U
#define I2C_EVENT0_RIS_CSTOP_SET                                     0x00000100U
#define I2C_EVENT0_RIS_CSTOP_CLR                                     0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Arbitration lost interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_CARBLOST                                      0x00000200U
#define I2C_EVENT0_RIS_CARBLOST_M                                    0x00000200U
#define I2C_EVENT0_RIS_CARBLOST_S                                    9U
#define I2C_EVENT0_RIS_CARBLOST_SET                                  0x00000200U
#define I2C_EVENT0_RIS_CARBLOST_CLR                                  0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TRXDONE                                       0x00010000U
#define I2C_EVENT0_RIS_TRXDONE_M                                     0x00010000U
#define I2C_EVENT0_RIS_TRXDONE_S                                     16U
#define I2C_EVENT0_RIS_TRXDONE_SET                                   0x00010000U
#define I2C_EVENT0_RIS_TRXDONE_CLR                                   0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TTXDONE                                       0x00020000U
#define I2C_EVENT0_RIS_TTXDONE_M                                     0x00020000U
#define I2C_EVENT0_RIS_TTXDONE_S                                     17U
#define I2C_EVENT0_RIS_TTXDONE_SET                                   0x00020000U
#define I2C_EVENT0_RIS_TTXDONE_CLR                                   0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO trigger in target mode

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_RXFIFOTRGT                                    0x00040000U
#define I2C_EVENT0_RIS_RXFIFOTRGT_M                                  0x00040000U
#define I2C_EVENT0_RIS_RXFIFOTRGT_S                                  18U
#define I2C_EVENT0_RIS_RXFIFOTRGT_SET                                0x00040000U
#define I2C_EVENT0_RIS_RXFIFOTRGT_CLR                                0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TXFIFOTRGT                                    0x00080000U
#define I2C_EVENT0_RIS_TXFIFOTRGT_M                                  0x00080000U
#define I2C_EVENT0_RIS_TXFIFOTRGT_S                                  19U
#define I2C_EVENT0_RIS_TXFIFOTRGT_SET                                0x00080000U
#define I2C_EVENT0_RIS_TXFIFOTRGT_CLR                                0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO full event in target mode. This interrupt is set if an RX FIFO is full in target mode.

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_RXFIFOFULLT                                   0x00100000U
#define I2C_EVENT0_RIS_RXFIFOFULLT_M                                 0x00100000U
#define I2C_EVENT0_RIS_RXFIFOFULLT_S                                 20U
#define I2C_EVENT0_RIS_RXFIFOFULLT_SET                               0x00100000U
#define I2C_EVENT0_RIS_RXFIFOFULLT_CLR                               0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TXEMPTYT                                      0x00200000U
#define I2C_EVENT0_RIS_TXEMPTYT_M                                    0x00200000U
#define I2C_EVENT0_RIS_TXEMPTYT_S                                    21U
#define I2C_EVENT0_RIS_TXEMPTYT_SET                                  0x00200000U
#define I2C_EVENT0_RIS_TXEMPTYT_CLR                                  0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target start condition interrupt.When the received address matches the target address, this interrupt asserted.

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TSTART                                        0x00400000U
#define I2C_EVENT0_RIS_TSTART_M                                      0x00400000U
#define I2C_EVENT0_RIS_TSTART_S                                      22U
#define I2C_EVENT0_RIS_TSTART_SET                                    0x00400000U
#define I2C_EVENT0_RIS_TSTART_CLR                                    0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Stop condition interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TSTOP                                         0x00800000U
#define I2C_EVENT0_RIS_TSTOP_M                                       0x00800000U
#define I2C_EVENT0_RIS_TSTOP_S                                       23U
#define I2C_EVENT0_RIS_TSTOP_SET                                     0x00800000U
#define I2C_EVENT0_RIS_TSTOP_CLR                                     0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     General call interrupt

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TGENCALL                                      0x01000000U
#define I2C_EVENT0_RIS_TGENCALL_M                                    0x01000000U
#define I2C_EVENT0_RIS_TGENCALL_S                                    24U
#define I2C_EVENT0_RIS_TGENCALL_SET                                  0x01000000U
#define I2C_EVENT0_RIS_TGENCALL_CLR                                  0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO underflow in target mode

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TX_UNFL_T                                     0x02000000U
#define I2C_EVENT0_RIS_TX_UNFL_T_M                                   0x02000000U
#define I2C_EVENT0_RIS_TX_UNFL_T_S                                   25U
#define I2C_EVENT0_RIS_TX_UNFL_T_SET                                 0x02000000U
#define I2C_EVENT0_RIS_TX_UNFL_T_CLR                                 0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            SET:                         Interrupt Occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_RX_OVFL_T                                     0x04000000U
#define I2C_EVENT0_RIS_RX_OVFL_T_M                                   0x04000000U
#define I2C_EVENT0_RIS_RX_OVFL_T_S                                   26U
#define I2C_EVENT0_RIS_RX_OVFL_T_SET                                 0x04000000U
#define I2C_EVENT0_RIS_RX_OVFL_T_CLR                                 0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target arbitration lost

        ENUMs:
            SET:                         Interrupt occured
            CLR:                         Interrupt did not occur
*/
#define I2C_EVENT0_RIS_TARBLOST                                      0x08000000U
#define I2C_EVENT0_RIS_TARBLOST_M                                    0x08000000U
#define I2C_EVENT0_RIS_TARBLOST_S                                    27U
#define I2C_EVENT0_RIS_TARBLOST_SET                                  0x08000000U
#define I2C_EVENT0_RIS_TARBLOST_CLR                                  0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_MIS
    Offset name:         I2C_O_EVENT0_MIS
    Relative address:    0xC
    Description:         Masked interrupt status. This is an AND of the [IMASK] and [RIS] registers.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller receive data interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CRXDONE                                       0x00000001U
#define I2C_EVENT0_MIS_CRXDONE_M                                     0x00000001U
#define I2C_EVENT0_MIS_CRXDONE_S                                     0U
#define I2C_EVENT0_MIS_CRXDONE_SET                                   0x00000001U
#define I2C_EVENT0_MIS_CRXDONE_CLR                                   0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CTXDONE                                       0x00000002U
#define I2C_EVENT0_MIS_CTXDONE_M                                     0x00000002U
#define I2C_EVENT0_MIS_CTXDONE_S                                     1U
#define I2C_EVENT0_MIS_CTXDONE_SET                                   0x00000002U
#define I2C_EVENT0_MIS_CTXDONE_CLR                                   0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_RXFIFOTRGC                                    0x00000004U
#define I2C_EVENT0_MIS_RXFIFOTRGC_M                                  0x00000004U
#define I2C_EVENT0_MIS_RXFIFOTRGC_S                                  2U
#define I2C_EVENT0_MIS_RXFIFOTRGC_SET                                0x00000004U
#define I2C_EVENT0_MIS_RXFIFOTRGC_CLR                                0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO trigger in controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TXFIFOTRGC                                    0x00000008U
#define I2C_EVENT0_MIS_TXFIFOTRGC_M                                  0x00000008U
#define I2C_EVENT0_MIS_TXFIFOTRGC_S                                  3U
#define I2C_EVENT0_MIS_TXFIFOTRGC_SET                                0x00000008U
#define I2C_EVENT0_MIS_TXFIFOTRGC_CLR                                0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO full event. This interrupt is set if the RX FIFO is full in controller mode.

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_RXFIFOFULLC                                   0x00000010U
#define I2C_EVENT0_MIS_RXFIFOFULLC_M                                 0x00000010U
#define I2C_EVENT0_MIS_RXFIFOFULLC_S                                 4U
#define I2C_EVENT0_MIS_RXFIFOFULLC_SET                               0x00000010U
#define I2C_EVENT0_MIS_RXFIFOFULLC_CLR                               0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO Empty interrupt mask in controller mode. This interrupt is set if all data in the TX FIFO in controller mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TXEMPTYC                                      0x00000020U
#define I2C_EVENT0_MIS_TXEMPTYC_M                                    0x00000020U
#define I2C_EVENT0_MIS_TXEMPTYC_S                                    5U
#define I2C_EVENT0_MIS_TXEMPTYC_SET                                  0x00000020U
#define I2C_EVENT0_MIS_TXEMPTYC_CLR                                  0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CNACK                                         0x00000040U
#define I2C_EVENT0_MIS_CNACK_M                                       0x00000040U
#define I2C_EVENT0_MIS_CNACK_S                                       6U
#define I2C_EVENT0_MIS_CNACK_SET                                     0x00000040U
#define I2C_EVENT0_MIS_CNACK_CLR                                     0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:      START detection interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CSTART                                        0x00000080U
#define I2C_EVENT0_MIS_CSTART_M                                      0x00000080U
#define I2C_EVENT0_MIS_CSTART_S                                      7U
#define I2C_EVENT0_MIS_CSTART_SET                                    0x00000080U
#define I2C_EVENT0_MIS_CSTART_CLR                                    0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:      STOP detection interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CSTOP                                         0x00000100U
#define I2C_EVENT0_MIS_CSTOP_M                                       0x00000100U
#define I2C_EVENT0_MIS_CSTOP_S                                       8U
#define I2C_EVENT0_MIS_CSTOP_SET                                     0x00000100U
#define I2C_EVENT0_MIS_CSTOP_CLR                                     0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Arbitration lost interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_CARBLOST                                      0x00000200U
#define I2C_EVENT0_MIS_CARBLOST_M                                    0x00000200U
#define I2C_EVENT0_MIS_CARBLOST_S                                    9U
#define I2C_EVENT0_MIS_CARBLOST_SET                                  0x00000200U
#define I2C_EVENT0_MIS_CARBLOST_CLR                                  0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TRXDONE                                       0x00010000U
#define I2C_EVENT0_MIS_TRXDONE_M                                     0x00010000U
#define I2C_EVENT0_MIS_TRXDONE_S                                     16U
#define I2C_EVENT0_MIS_TRXDONE_SET                                   0x00010000U
#define I2C_EVENT0_MIS_TRXDONE_CLR                                   0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TTXDONE                                       0x00020000U
#define I2C_EVENT0_MIS_TTXDONE_M                                     0x00020000U
#define I2C_EVENT0_MIS_TTXDONE_S                                     17U
#define I2C_EVENT0_MIS_TTXDONE_SET                                   0x00020000U
#define I2C_EVENT0_MIS_TTXDONE_CLR                                   0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target RX FIFO trigger

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_RXFIFOTRGT                                    0x00040000U
#define I2C_EVENT0_MIS_RXFIFOTRGT_M                                  0x00040000U
#define I2C_EVENT0_MIS_RXFIFOTRGT_S                                  18U
#define I2C_EVENT0_MIS_RXFIFOTRGT_SET                                0x00040000U
#define I2C_EVENT0_MIS_RXFIFOTRGT_CLR                                0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TXFIFOTRGT                                    0x00080000U
#define I2C_EVENT0_MIS_TXFIFOTRGT_M                                  0x00080000U
#define I2C_EVENT0_MIS_TXFIFOTRGT_S                                  19U
#define I2C_EVENT0_MIS_TXFIFOTRGT_SET                                0x00080000U
#define I2C_EVENT0_MIS_TXFIFOTRGT_CLR                                0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RXFIFO full event in Target mode. This interrupt is set if an RX FIFO is full in target mode.

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_RXFIFOFULLT                                   0x00100000U
#define I2C_EVENT0_MIS_RXFIFOFULLT_M                                 0x00100000U
#define I2C_EVENT0_MIS_RXFIFOFULLT_S                                 20U
#define I2C_EVENT0_MIS_RXFIFOFULLT_SET                               0x00100000U
#define I2C_EVENT0_MIS_RXFIFOFULLT_CLR                               0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TXEMPTYT                                      0x00200000U
#define I2C_EVENT0_MIS_TXEMPTYT_M                                    0x00200000U
#define I2C_EVENT0_MIS_TXEMPTYT_S                                    21U
#define I2C_EVENT0_MIS_TXEMPTYT_SET                                  0x00200000U
#define I2C_EVENT0_MIS_TXEMPTYT_CLR                                  0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target start condition interrupt. Asserted when the received address matches the target address

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TSTART                                        0x00400000U
#define I2C_EVENT0_MIS_TSTART_M                                      0x00400000U
#define I2C_EVENT0_MIS_TSTART_S                                      22U
#define I2C_EVENT0_MIS_TSTART_SET                                    0x00400000U
#define I2C_EVENT0_MIS_TSTART_CLR                                    0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target STOP detection interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TSTOP                                         0x00800000U
#define I2C_EVENT0_MIS_TSTOP_M                                       0x00800000U
#define I2C_EVENT0_MIS_TSTOP_S                                       23U
#define I2C_EVENT0_MIS_TSTOP_SET                                     0x00800000U
#define I2C_EVENT0_MIS_TSTOP_CLR                                     0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     General call interrupt

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TGENCALL                                      0x01000000U
#define I2C_EVENT0_MIS_TGENCALL_M                                    0x01000000U
#define I2C_EVENT0_MIS_TGENCALL_S                                    24U
#define I2C_EVENT0_MIS_TGENCALL_SET                                  0x01000000U
#define I2C_EVENT0_MIS_TGENCALL_CLR                                  0x00000000U
/*

        Field:           TTX_UNFL
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX FIFO underflow in target mode

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TTX_UNFL                                      0x02000000U
#define I2C_EVENT0_MIS_TTX_UNFL_M                                    0x02000000U
#define I2C_EVENT0_MIS_TTX_UNFL_S                                    25U
#define I2C_EVENT0_MIS_TTX_UNFL_SET                                  0x02000000U
#define I2C_EVENT0_MIS_TTX_UNFL_CLR                                  0x00000000U
/*

        Field:           TRX_OVFL
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Masked Interrupt did not occur
*/
#define I2C_EVENT0_MIS_TRX_OVFL                                      0x04000000U
#define I2C_EVENT0_MIS_TRX_OVFL_M                                    0x04000000U
#define I2C_EVENT0_MIS_TRX_OVFL_S                                    26U
#define I2C_EVENT0_MIS_TRX_OVFL_SET                                  0x04000000U
#define I2C_EVENT0_MIS_TRX_OVFL_CLR                                  0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Target arbitration lost

        ENUMs:
            SET:                         Masked interrupt occured
            CLR:                         Clear interrupt mask
*/
#define I2C_EVENT0_MIS_TARBLOST                                      0x08000000U
#define I2C_EVENT0_MIS_TARBLOST_M                                    0x08000000U
#define I2C_EVENT0_MIS_TARBLOST_S                                    27U
#define I2C_EVENT0_MIS_TARBLOST_SET                                  0x08000000U
#define I2C_EVENT0_MIS_TARBLOST_CLR                                  0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_IEN
    Offset name:         I2C_O_EVENT0_IEN
    Relative address:    0x10
    Description:         Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a field in IEN will set the event and therefore the related RIS field also gets set. If the interrupt is enabled through the mask, then the corresponding MIS field is also set.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller receive data interrupt
                         Signals that a byte has been received

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CRXDONE                                       0x00000001U
#define I2C_EVENT0_IEN_CRXDONE_M                                     0x00000001U
#define I2C_EVENT0_IEN_CRXDONE_S                                     0U
#define I2C_EVENT0_IEN_CRXDONE_EN                                    0x00000001U
#define I2C_EVENT0_IEN_CRXDONE_DIS                                   0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CTXDONE                                       0x00000002U
#define I2C_EVENT0_IEN_CTXDONE_M                                     0x00000002U
#define I2C_EVENT0_IEN_CTXDONE_S                                     1U
#define I2C_EVENT0_IEN_CTXDONE_EN                                    0x00000002U
#define I2C_EVENT0_IEN_CTXDONE_DIS                                   0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_RXFIFOTRGC                                    0x00000004U
#define I2C_EVENT0_IEN_RXFIFOTRGC_M                                  0x00000004U
#define I2C_EVENT0_IEN_RXFIFOTRGC_S                                  2U
#define I2C_EVENT0_IEN_RXFIFOTRGC_EN                                 0x00000004U
#define I2C_EVENT0_IEN_RXFIFOTRGC_DIS                                0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TXFIFOTRGC                                    0x00000008U
#define I2C_EVENT0_IEN_TXFIFOTRGC_M                                  0x00000008U
#define I2C_EVENT0_IEN_TXFIFOTRGC_S                                  3U
#define I2C_EVENT0_IEN_TXFIFOTRGC_EN                                 0x00000008U
#define I2C_EVENT0_IEN_TXFIFOTRGC_DIS                                0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in controller mode.

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_RXFIFOFULLC                                   0x00000010U
#define I2C_EVENT0_IEN_RXFIFOFULLC_M                                 0x00000010U
#define I2C_EVENT0_IEN_RXFIFOFULLC_S                                 4U
#define I2C_EVENT0_IEN_RXFIFOFULLC_EN                                0x00000010U
#define I2C_EVENT0_IEN_RXFIFOFULLC_DIS                               0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask in controller mode. This interrupt is set if all data in the TX FIFO in controller mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TXEMPTYC                                      0x00000020U
#define I2C_EVENT0_IEN_TXEMPTYC_M                                    0x00000020U
#define I2C_EVENT0_IEN_TXEMPTYC_S                                    5U
#define I2C_EVENT0_IEN_TXEMPTYC_EN                                   0x00000020U
#define I2C_EVENT0_IEN_TXEMPTYC_DIS                                  0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CNACK                                         0x00000040U
#define I2C_EVENT0_IEN_CNACK_M                                       0x00000040U
#define I2C_EVENT0_IEN_CNACK_S                                       6U
#define I2C_EVENT0_IEN_CNACK_EN                                      0x00000040U
#define I2C_EVENT0_IEN_CNACK_DIS                                     0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:      START detection interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CSTART                                        0x00000080U
#define I2C_EVENT0_IEN_CSTART_M                                      0x00000080U
#define I2C_EVENT0_IEN_CSTART_S                                      7U
#define I2C_EVENT0_IEN_CSTART_EN                                     0x00000080U
#define I2C_EVENT0_IEN_CSTART_DIS                                    0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:      STOP detection interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CSTOP                                         0x00000100U
#define I2C_EVENT0_IEN_CSTOP_M                                       0x00000100U
#define I2C_EVENT0_IEN_CSTOP_S                                       8U
#define I2C_EVENT0_IEN_CSTOP_EN                                      0x00000100U
#define I2C_EVENT0_IEN_CSTOP_DIS                                     0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Arbitration lost interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_CARBLOST                                      0x00000200U
#define I2C_EVENT0_IEN_CARBLOST_M                                    0x00000200U
#define I2C_EVENT0_IEN_CARBLOST_S                                    9U
#define I2C_EVENT0_IEN_CARBLOST_EN                                   0x00000200U
#define I2C_EVENT0_IEN_CARBLOST_DIS                                  0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TRXDONE                                       0x00010000U
#define I2C_EVENT0_IEN_TRXDONE_M                                     0x00010000U
#define I2C_EVENT0_IEN_TRXDONE_S                                     16U
#define I2C_EVENT0_IEN_TRXDONE_EN                                    0x00010000U
#define I2C_EVENT0_IEN_TRXDONE_DIS                                   0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target transmit transaction completed Interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TTXDONE                                       0x00020000U
#define I2C_EVENT0_IEN_TTXDONE_M                                     0x00020000U
#define I2C_EVENT0_IEN_TTXDONE_S                                     17U
#define I2C_EVENT0_IEN_TTXDONE_EN                                    0x00020000U
#define I2C_EVENT0_IEN_TTXDONE_DIS                                   0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in target mode

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_RXFIFOTRGT                                    0x00040000U
#define I2C_EVENT0_IEN_RXFIFOTRGT_M                                  0x00040000U
#define I2C_EVENT0_IEN_RXFIFOTRGT_S                                  18U
#define I2C_EVENT0_IEN_RXFIFOTRGT_EN                                 0x00040000U
#define I2C_EVENT0_IEN_RXFIFOTRGT_DIS                                0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TXFIFOTRGT                                    0x00080000U
#define I2C_EVENT0_IEN_TXFIFOTRGT_M                                  0x00080000U
#define I2C_EVENT0_IEN_TXFIFOTRGT_S                                  19U
#define I2C_EVENT0_IEN_TXFIFOTRGT_EN                                 0x00080000U
#define I2C_EVENT0_IEN_TXFIFOTRGT_DIS                                0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in Target mode. This interrupt is set if an RX FIFO is full in Target mode.

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_RXFIFOFULLT                                   0x00100000U
#define I2C_EVENT0_IEN_RXFIFOFULLT_M                                 0x00100000U
#define I2C_EVENT0_IEN_RXFIFOFULLT_S                                 20U
#define I2C_EVENT0_IEN_RXFIFOFULLT_EN                                0x00100000U
#define I2C_EVENT0_IEN_RXFIFOFULLT_DIS                               0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TXEMPTYT                                      0x00200000U
#define I2C_EVENT0_IEN_TXEMPTYT_M                                    0x00200000U
#define I2C_EVENT0_IEN_TXEMPTYT_S                                    21U
#define I2C_EVENT0_IEN_TXEMPTYT_EN                                   0x00200000U
#define I2C_EVENT0_IEN_TXEMPTYT_DIS                                  0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target start condition interrupt. Asserted when the received address matches the target address

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TSTART                                        0x00400000U
#define I2C_EVENT0_IEN_TSTART_M                                      0x00400000U
#define I2C_EVENT0_IEN_TSTART_S                                      22U
#define I2C_EVENT0_IEN_TSTART_EN                                     0x00400000U
#define I2C_EVENT0_IEN_TSTART_DIS                                    0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Stop condition interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TSTOP                                         0x00800000U
#define I2C_EVENT0_IEN_TSTOP_M                                       0x00800000U
#define I2C_EVENT0_IEN_TSTOP_S                                       23U
#define I2C_EVENT0_IEN_TSTOP_EN                                      0x00800000U
#define I2C_EVENT0_IEN_TSTOP_DIS                                     0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     write-only
        Description:     General call interrupt

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TGENCALL                                      0x01000000U
#define I2C_EVENT0_IEN_TGENCALL_M                                    0x01000000U
#define I2C_EVENT0_IEN_TGENCALL_S                                    24U
#define I2C_EVENT0_IEN_TGENCALL_EN                                   0x01000000U
#define I2C_EVENT0_IEN_TGENCALL_DIS                                  0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO underflow in target mode

        ENUMs:
            EN:                          Set interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TX_UNFL_T                                     0x02000000U
#define I2C_EVENT0_IEN_TX_UNFL_T_M                                   0x02000000U
#define I2C_EVENT0_IEN_TX_UNFL_T_S                                   25U
#define I2C_EVENT0_IEN_TX_UNFL_T_EN                                  0x02000000U
#define I2C_EVENT0_IEN_TX_UNFL_T_DIS                                 0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            EN:                          Set Interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_RX_OVFL_T                                     0x04000000U
#define I2C_EVENT0_IEN_RX_OVFL_T_M                                   0x04000000U
#define I2C_EVENT0_IEN_RX_OVFL_T_S                                   26U
#define I2C_EVENT0_IEN_RX_OVFL_T_EN                                  0x04000000U
#define I2C_EVENT0_IEN_RX_OVFL_T_DIS                                 0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target arbitration lost

        ENUMs:
            EN:                          Set Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IEN_TARBLOST                                      0x08000000U
#define I2C_EVENT0_IEN_TARBLOST_M                                    0x08000000U
#define I2C_EVENT0_IEN_TARBLOST_S                                    27U
#define I2C_EVENT0_IEN_TARBLOST_EN                                   0x08000000U
#define I2C_EVENT0_IEN_TARBLOST_DIS                                  0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_IDIS
    Offset name:         I2C_O_EVENT0_IDIS
    Relative address:    0x14
    Description:         Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CRXDONE                                      0x00000001U
#define I2C_EVENT0_IDIS_CRXDONE_M                                    0x00000001U
#define I2C_EVENT0_IDIS_CRXDONE_S                                    0U
#define I2C_EVENT0_IDIS_CRXDONE_EN                                   0x00000001U
#define I2C_EVENT0_IDIS_CRXDONE_DIS                                  0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CTXDONE                                      0x00000002U
#define I2C_EVENT0_IDIS_CTXDONE_M                                    0x00000002U
#define I2C_EVENT0_IDIS_CTXDONE_S                                    1U
#define I2C_EVENT0_IDIS_CTXDONE_EN                                   0x00000002U
#define I2C_EVENT0_IDIS_CTXDONE_DIS                                  0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_RXFIFOTRGC                                   0x00000004U
#define I2C_EVENT0_IDIS_RXFIFOTRGC_M                                 0x00000004U
#define I2C_EVENT0_IDIS_RXFIFOTRGC_S                                 2U
#define I2C_EVENT0_IDIS_RXFIFOTRGC_EN                                0x00000004U
#define I2C_EVENT0_IDIS_RXFIFOTRGC_DIS                               0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TXFIFOTRGC                                   0x00000008U
#define I2C_EVENT0_IDIS_TXFIFOTRGC_M                                 0x00000008U
#define I2C_EVENT0_IDIS_TXFIFOTRGC_S                                 3U
#define I2C_EVENT0_IDIS_TXFIFOTRGC_EN                                0x00000008U
#define I2C_EVENT0_IDIS_TXFIFOTRGC_DIS                               0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in controller mode.

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_RXFIFOFULLC                                  0x00000010U
#define I2C_EVENT0_IDIS_RXFIFOFULLC_M                                0x00000010U
#define I2C_EVENT0_IDIS_RXFIFOFULLC_S                                4U
#define I2C_EVENT0_IDIS_RXFIFOFULLC_EN                               0x00000010U
#define I2C_EVENT0_IDIS_RXFIFOFULLC_DIS                              0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask. This interrupt is set if all data in the TX FIFO have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TXEMPTYC                                     0x00000020U
#define I2C_EVENT0_IDIS_TXEMPTYC_M                                   0x00000020U
#define I2C_EVENT0_IDIS_TXEMPTYC_S                                   5U
#define I2C_EVENT0_IDIS_TXEMPTYC_EN                                  0x00000020U
#define I2C_EVENT0_IDIS_TXEMPTYC_DIS                                 0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CNACK                                        0x00000040U
#define I2C_EVENT0_IDIS_CNACK_M                                      0x00000040U
#define I2C_EVENT0_IDIS_CNACK_S                                      6U
#define I2C_EVENT0_IDIS_CNACK_EN                                     0x00000040U
#define I2C_EVENT0_IDIS_CNACK_DIS                                    0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:      START detection interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CSTART                                       0x00000080U
#define I2C_EVENT0_IDIS_CSTART_M                                     0x00000080U
#define I2C_EVENT0_IDIS_CSTART_S                                     7U
#define I2C_EVENT0_IDIS_CSTART_EN                                    0x00000080U
#define I2C_EVENT0_IDIS_CSTART_DIS                                   0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:      STOP detection interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CSTOP                                        0x00000100U
#define I2C_EVENT0_IDIS_CSTOP_M                                      0x00000100U
#define I2C_EVENT0_IDIS_CSTOP_S                                      8U
#define I2C_EVENT0_IDIS_CSTOP_EN                                     0x00000100U
#define I2C_EVENT0_IDIS_CSTOP_DIS                                    0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Arbitration lost interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_CARBLOST                                     0x00000200U
#define I2C_EVENT0_IDIS_CARBLOST_M                                   0x00000200U
#define I2C_EVENT0_IDIS_CARBLOST_S                                   9U
#define I2C_EVENT0_IDIS_CARBLOST_EN                                  0x00000200U
#define I2C_EVENT0_IDIS_CARBLOST_DIS                                 0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target receive data interrupt
                         Signals that a byte has been received

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TRXDONE                                      0x00010000U
#define I2C_EVENT0_IDIS_TRXDONE_M                                    0x00010000U
#define I2C_EVENT0_IDIS_TRXDONE_S                                    16U
#define I2C_EVENT0_IDIS_TRXDONE_EN                                   0x00010000U
#define I2C_EVENT0_IDIS_TRXDONE_DIS                                  0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TTXDONE                                      0x00020000U
#define I2C_EVENT0_IDIS_TTXDONE_M                                    0x00020000U
#define I2C_EVENT0_IDIS_TTXDONE_S                                    17U
#define I2C_EVENT0_IDIS_TTXDONE_EN                                   0x00020000U
#define I2C_EVENT0_IDIS_TTXDONE_DIS                                  0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in target mode

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_RXFIFOTRGT                                   0x00040000U
#define I2C_EVENT0_IDIS_RXFIFOTRGT_M                                 0x00040000U
#define I2C_EVENT0_IDIS_RXFIFOTRGT_S                                 18U
#define I2C_EVENT0_IDIS_RXFIFOTRGT_EN                                0x00040000U
#define I2C_EVENT0_IDIS_RXFIFOTRGT_DIS                               0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TXFIFOTRGT                                   0x00080000U
#define I2C_EVENT0_IDIS_TXFIFOTRGT_M                                 0x00080000U
#define I2C_EVENT0_IDIS_TXFIFOTRGT_S                                 19U
#define I2C_EVENT0_IDIS_TXFIFOTRGT_EN                                0x00080000U
#define I2C_EVENT0_IDIS_TXFIFOTRGT_DIS                               0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in target mode. This interrupt is set if an RX FIFO is full in target mode.

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_RXFIFOFULLT                                  0x00100000U
#define I2C_EVENT0_IDIS_RXFIFOFULLT_M                                0x00100000U
#define I2C_EVENT0_IDIS_RXFIFOFULLT_S                                20U
#define I2C_EVENT0_IDIS_RXFIFOFULLT_EN                               0x00100000U
#define I2C_EVENT0_IDIS_RXFIFOFULLT_DIS                              0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TXEMPTYT                                     0x00200000U
#define I2C_EVENT0_IDIS_TXEMPTYT_M                                   0x00200000U
#define I2C_EVENT0_IDIS_TXEMPTYT_S                                   21U
#define I2C_EVENT0_IDIS_TXEMPTYT_EN                                  0x00200000U
#define I2C_EVENT0_IDIS_TXEMPTYT_DIS                                 0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target start condition interrupt. Asserted when the received address matches the target address

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TSTART                                       0x00400000U
#define I2C_EVENT0_IDIS_TSTART_M                                     0x00400000U
#define I2C_EVENT0_IDIS_TSTART_S                                     22U
#define I2C_EVENT0_IDIS_TSTART_EN                                    0x00400000U
#define I2C_EVENT0_IDIS_TSTART_DIS                                   0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target STOP detection interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TSTOP                                        0x00800000U
#define I2C_EVENT0_IDIS_TSTOP_M                                      0x00800000U
#define I2C_EVENT0_IDIS_TSTOP_S                                      23U
#define I2C_EVENT0_IDIS_TSTOP_EN                                     0x00800000U
#define I2C_EVENT0_IDIS_TSTOP_DIS                                    0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     write-only
        Description:     General call interrupt

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TGENCALL                                     0x01000000U
#define I2C_EVENT0_IDIS_TGENCALL_M                                   0x01000000U
#define I2C_EVENT0_IDIS_TGENCALL_S                                   24U
#define I2C_EVENT0_IDIS_TGENCALL_EN                                  0x01000000U
#define I2C_EVENT0_IDIS_TGENCALL_DIS                                 0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO underflow	in target mode

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TX_UNFL_T                                    0x02000000U
#define I2C_EVENT0_IDIS_TX_UNFL_T_M                                  0x02000000U
#define I2C_EVENT0_IDIS_TX_UNFL_T_S                                  25U
#define I2C_EVENT0_IDIS_TX_UNFL_T_EN                                 0x02000000U
#define I2C_EVENT0_IDIS_TX_UNFL_T_DIS                                0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_RX_OVFL_T                                    0x04000000U
#define I2C_EVENT0_IDIS_RX_OVFL_T_M                                  0x04000000U
#define I2C_EVENT0_IDIS_RX_OVFL_T_S                                  26U
#define I2C_EVENT0_IDIS_RX_OVFL_T_EN                                 0x04000000U
#define I2C_EVENT0_IDIS_RX_OVFL_T_DIS                                0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target arbitration lost

        ENUMs:
            EN:                          Clear Interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IDIS_TARBLOST                                     0x08000000U
#define I2C_EVENT0_IDIS_TARBLOST_M                                   0x08000000U
#define I2C_EVENT0_IDIS_TARBLOST_S                                   27U
#define I2C_EVENT0_IDIS_TARBLOST_EN                                  0x08000000U
#define I2C_EVENT0_IDIS_TARBLOST_DIS                                 0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_IMEN
    Offset name:         I2C_O_EVENT0_IMEN
    Relative address:    0x18
    Description:         Interrupt mask set. Writing a 1 to a field in IMEN will set the related IMASK field.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CRXDONE                                      0x00000001U
#define I2C_EVENT0_IMEN_CRXDONE_M                                    0x00000001U
#define I2C_EVENT0_IMEN_CRXDONE_S                                    0U
#define I2C_EVENT0_IMEN_CRXDONE_EN                                   0x00000001U
#define I2C_EVENT0_IMEN_CRXDONE_DIS                                  0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CTXDONE                                      0x00000002U
#define I2C_EVENT0_IMEN_CTXDONE_M                                    0x00000002U
#define I2C_EVENT0_IMEN_CTXDONE_S                                    1U
#define I2C_EVENT0_IMEN_CTXDONE_EN                                   0x00000002U
#define I2C_EVENT0_IMEN_CTXDONE_DIS                                  0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_RXFIFOTRGC                                   0x00000004U
#define I2C_EVENT0_IMEN_RXFIFOTRGC_M                                 0x00000004U
#define I2C_EVENT0_IMEN_RXFIFOTRGC_S                                 2U
#define I2C_EVENT0_IMEN_RXFIFOTRGC_EN                                0x00000004U
#define I2C_EVENT0_IMEN_RXFIFOTRGC_DIS                               0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in Controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TXFIFOTRGC                                   0x00000008U
#define I2C_EVENT0_IMEN_TXFIFOTRGC_M                                 0x00000008U
#define I2C_EVENT0_IMEN_TXFIFOTRGC_S                                 3U
#define I2C_EVENT0_IMEN_TXFIFOTRGC_EN                                0x00000008U
#define I2C_EVENT0_IMEN_TXFIFOTRGC_DIS                               0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in controller mode.

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_RXFIFOFULLC                                  0x00000010U
#define I2C_EVENT0_IMEN_RXFIFOFULLC_M                                0x00000010U
#define I2C_EVENT0_IMEN_RXFIFOFULLC_S                                4U
#define I2C_EVENT0_IMEN_RXFIFOFULLC_EN                               0x00000010U
#define I2C_EVENT0_IMEN_RXFIFOFULLC_DIS                              0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask in controller mode. This interrupt is set if all data in the TX FIFO in controller mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TXEMPTYC                                     0x00000020U
#define I2C_EVENT0_IMEN_TXEMPTYC_M                                   0x00000020U
#define I2C_EVENT0_IMEN_TXEMPTYC_S                                   5U
#define I2C_EVENT0_IMEN_TXEMPTYC_EN                                  0x00000020U
#define I2C_EVENT0_IMEN_TXEMPTYC_DIS                                 0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CNACK                                        0x00000040U
#define I2C_EVENT0_IMEN_CNACK_M                                      0x00000040U
#define I2C_EVENT0_IMEN_CNACK_S                                      6U
#define I2C_EVENT0_IMEN_CNACK_EN                                     0x00000040U
#define I2C_EVENT0_IMEN_CNACK_DIS                                    0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:      START detection interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CSTART                                       0x00000080U
#define I2C_EVENT0_IMEN_CSTART_M                                     0x00000080U
#define I2C_EVENT0_IMEN_CSTART_S                                     7U
#define I2C_EVENT0_IMEN_CSTART_EN                                    0x00000080U
#define I2C_EVENT0_IMEN_CSTART_DIS                                   0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:      STOP detection interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CSTOP                                        0x00000100U
#define I2C_EVENT0_IMEN_CSTOP_M                                      0x00000100U
#define I2C_EVENT0_IMEN_CSTOP_S                                      8U
#define I2C_EVENT0_IMEN_CSTOP_EN                                     0x00000100U
#define I2C_EVENT0_IMEN_CSTOP_DIS                                    0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Arbitration lost interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_CARBLOST                                     0x00000200U
#define I2C_EVENT0_IMEN_CARBLOST_M                                   0x00000200U
#define I2C_EVENT0_IMEN_CARBLOST_S                                   9U
#define I2C_EVENT0_IMEN_CARBLOST_EN                                  0x00000200U
#define I2C_EVENT0_IMEN_CARBLOST_DIS                                 0x00000000U
/*

        Field:           SRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_SRXDONE                                      0x00010000U
#define I2C_EVENT0_IMEN_SRXDONE_M                                    0x00010000U
#define I2C_EVENT0_IMEN_SRXDONE_S                                    16U
#define I2C_EVENT0_IMEN_SRXDONE_EN                                   0x00010000U
#define I2C_EVENT0_IMEN_SRXDONE_DIS                                  0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TTXDONE                                      0x00020000U
#define I2C_EVENT0_IMEN_TTXDONE_M                                    0x00020000U
#define I2C_EVENT0_IMEN_TTXDONE_S                                    17U
#define I2C_EVENT0_IMEN_TTXDONE_EN                                   0x00020000U
#define I2C_EVENT0_IMEN_TTXDONE_DIS                                  0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in target mode

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_RXFIFOTRGT                                   0x00040000U
#define I2C_EVENT0_IMEN_RXFIFOTRGT_M                                 0x00040000U
#define I2C_EVENT0_IMEN_RXFIFOTRGT_S                                 18U
#define I2C_EVENT0_IMEN_RXFIFOTRGT_EN                                0x00040000U
#define I2C_EVENT0_IMEN_RXFIFOTRGT_DIS                               0x00000000U
/*

        Field:           TXFIFOTRGST
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TXFIFOTRGST                                  0x00080000U
#define I2C_EVENT0_IMEN_TXFIFOTRGST_M                                0x00080000U
#define I2C_EVENT0_IMEN_TXFIFOTRGST_S                                19U
#define I2C_EVENT0_IMEN_TXFIFOTRGST_EN                               0x00080000U
#define I2C_EVENT0_IMEN_TXFIFOTRGST_DIS                              0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in target mode. This interrupt is set if an RX FIFO is full in target mode.

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_RXFIFOFULLT                                  0x00100000U
#define I2C_EVENT0_IMEN_RXFIFOFULLT_M                                0x00100000U
#define I2C_EVENT0_IMEN_RXFIFOFULLT_S                                20U
#define I2C_EVENT0_IMEN_RXFIFOFULLT_EN                               0x00100000U
#define I2C_EVENT0_IMEN_RXFIFOFULLT_DIS                              0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO Empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TXEMPTYT                                     0x00200000U
#define I2C_EVENT0_IMEN_TXEMPTYT_M                                   0x00200000U
#define I2C_EVENT0_IMEN_TXEMPTYT_S                                   21U
#define I2C_EVENT0_IMEN_TXEMPTYT_EN                                  0x00200000U
#define I2C_EVENT0_IMEN_TXEMPTYT_DIS                                 0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target start condition interrupt. Asserted when the received address matches the target address

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TSTART                                       0x00400000U
#define I2C_EVENT0_IMEN_TSTART_M                                     0x00400000U
#define I2C_EVENT0_IMEN_TSTART_S                                     22U
#define I2C_EVENT0_IMEN_TSTART_EN                                    0x00400000U
#define I2C_EVENT0_IMEN_TSTART_DIS                                   0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Stop condition interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TSTOP                                        0x00800000U
#define I2C_EVENT0_IMEN_TSTOP_M                                      0x00800000U
#define I2C_EVENT0_IMEN_TSTOP_S                                      23U
#define I2C_EVENT0_IMEN_TSTOP_EN                                     0x00800000U
#define I2C_EVENT0_IMEN_TSTOP_DIS                                    0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     write-only
        Description:     General call interrupt

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TGENCALL                                     0x01000000U
#define I2C_EVENT0_IMEN_TGENCALL_M                                   0x01000000U
#define I2C_EVENT0_IMEN_TGENCALL_S                                   24U
#define I2C_EVENT0_IMEN_TGENCALL_EN                                  0x01000000U
#define I2C_EVENT0_IMEN_TGENCALL_DIS                                 0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO underflow in target mode

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TX_UNFL_T                                    0x02000000U
#define I2C_EVENT0_IMEN_TX_UNFL_T_M                                  0x02000000U
#define I2C_EVENT0_IMEN_TX_UNFL_T_S                                  25U
#define I2C_EVENT0_IMEN_TX_UNFL_T_EN                                 0x02000000U
#define I2C_EVENT0_IMEN_TX_UNFL_T_DIS                                0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_RX_OVFL_T                                    0x04000000U
#define I2C_EVENT0_IMEN_RX_OVFL_T_M                                  0x04000000U
#define I2C_EVENT0_IMEN_RX_OVFL_T_S                                  26U
#define I2C_EVENT0_IMEN_RX_OVFL_T_EN                                 0x04000000U
#define I2C_EVENT0_IMEN_RX_OVFL_T_DIS                                0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target srbitration lost

        ENUMs:
            EN:                          Set masked interrrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMEN_TARBLOST                                     0x08000000U
#define I2C_EVENT0_IMEN_TARBLOST_M                                   0x08000000U
#define I2C_EVENT0_IMEN_TARBLOST_S                                   27U
#define I2C_EVENT0_IMEN_TARBLOST_EN                                  0x08000000U
#define I2C_EVENT0_IMEN_TARBLOST_DIS                                 0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVENT0_IMDIS
    Offset name:         I2C_O_EVENT0_IMDIS
    Relative address:    0x1C
    Description:         Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           CRXDONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CRXDONE                                     0x00000001U
#define I2C_EVENT0_IMDIS_CRXDONE_M                                   0x00000001U
#define I2C_EVENT0_IMDIS_CRXDONE_S                                   0U
#define I2C_EVENT0_IMDIS_CRXDONE_EN                                  0x00000001U
#define I2C_EVENT0_IMDIS_CRXDONE_DIS                                 0x00000000U
/*

        Field:           CTXDONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Controller transmit transaction completed interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CTXDONE                                     0x00000002U
#define I2C_EVENT0_IMDIS_CTXDONE_M                                   0x00000002U
#define I2C_EVENT0_IMDIS_CTXDONE_S                                   1U
#define I2C_EVENT0_IMDIS_CTXDONE_EN                                  0x00000002U
#define I2C_EVENT0_IMDIS_CTXDONE_DIS                                 0x00000000U
/*

        Field:           RXFIFOTRGC
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in controller mode
                         Trigger when RX FIFO contains >= defined bytes

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_RXFIFOTRGC                                  0x00000004U
#define I2C_EVENT0_IMDIS_RXFIFOTRGC_M                                0x00000004U
#define I2C_EVENT0_IMDIS_RXFIFOTRGC_S                                2U
#define I2C_EVENT0_IMDIS_RXFIFOTRGC_EN                               0x00000004U
#define I2C_EVENT0_IMDIS_RXFIFOTRGC_DIS                              0x00000000U
/*

        Field:           TXFIFOTRGC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in controller mode
                         Trigger when TX FIFO contains <= defined bytes

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TXFIFOTRGC                                  0x00000008U
#define I2C_EVENT0_IMDIS_TXFIFOTRGC_M                                0x00000008U
#define I2C_EVENT0_IMDIS_TXFIFOTRGC_S                                3U
#define I2C_EVENT0_IMDIS_TXFIFOTRGC_EN                               0x00000008U
#define I2C_EVENT0_IMDIS_TXFIFOTRGC_DIS                              0x00000000U
/*

        Field:           RXFIFOFULLC
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO full event in controller mode.

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_RXFIFOFULLC                                 0x00000010U
#define I2C_EVENT0_IMDIS_RXFIFOFULLC_M                               0x00000010U
#define I2C_EVENT0_IMDIS_RXFIFOFULLC_S                               4U
#define I2C_EVENT0_IMDIS_RXFIFOFULLC_EN                              0x00000010U
#define I2C_EVENT0_IMDIS_RXFIFOFULLC_DIS                             0x00000000U
/*

        Field:           TXEMPTYC
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask. This interrupt is set if all data in the TX FIFO have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TXEMPTYC                                    0x00000020U
#define I2C_EVENT0_IMDIS_TXEMPTYC_M                                  0x00000020U
#define I2C_EVENT0_IMDIS_TXEMPTYC_S                                  5U
#define I2C_EVENT0_IMDIS_TXEMPTYC_EN                                 0x00000020U
#define I2C_EVENT0_IMDIS_TXEMPTYC_DIS                                0x00000000U
/*

        Field:           CNACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Address/Data NACK interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CNACK                                       0x00000040U
#define I2C_EVENT0_IMDIS_CNACK_M                                     0x00000040U
#define I2C_EVENT0_IMDIS_CNACK_S                                     6U
#define I2C_EVENT0_IMDIS_CNACK_EN                                    0x00000040U
#define I2C_EVENT0_IMDIS_CNACK_DIS                                   0x00000000U
/*

        Field:           CSTART
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:      START detection interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CSTART                                      0x00000080U
#define I2C_EVENT0_IMDIS_CSTART_M                                    0x00000080U
#define I2C_EVENT0_IMDIS_CSTART_S                                    7U
#define I2C_EVENT0_IMDIS_CSTART_EN                                   0x00000080U
#define I2C_EVENT0_IMDIS_CSTART_DIS                                  0x00000000U
/*

        Field:           CSTOP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:      STOP detection interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CSTOP                                       0x00000100U
#define I2C_EVENT0_IMDIS_CSTOP_M                                     0x00000100U
#define I2C_EVENT0_IMDIS_CSTOP_S                                     8U
#define I2C_EVENT0_IMDIS_CSTOP_EN                                    0x00000100U
#define I2C_EVENT0_IMDIS_CSTOP_DIS                                   0x00000000U
/*

        Field:           CARBLOST
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:      Arbitration lost interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_CARBLOST                                    0x00000200U
#define I2C_EVENT0_IMDIS_CARBLOST_M                                  0x00000200U
#define I2C_EVENT0_IMDIS_CARBLOST_S                                  9U
#define I2C_EVENT0_IMDIS_CARBLOST_EN                                 0x00000200U
#define I2C_EVENT0_IMDIS_CARBLOST_DIS                                0x00000000U
/*

        Field:           TRXDONE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target receive data interrupt. Signals that a byte has been received

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TRXDONE                                     0x00010000U
#define I2C_EVENT0_IMDIS_TRXDONE_M                                   0x00010000U
#define I2C_EVENT0_IMDIS_TRXDONE_S                                   16U
#define I2C_EVENT0_IMDIS_TRXDONE_EN                                  0x00010000U
#define I2C_EVENT0_IMDIS_TRXDONE_DIS                                 0x00000000U
/*

        Field:           TTXDONE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target transmit transaction completed interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TTXDONE                                     0x00020000U
#define I2C_EVENT0_IMDIS_TTXDONE_M                                   0x00020000U
#define I2C_EVENT0_IMDIS_TTXDONE_S                                   17U
#define I2C_EVENT0_IMDIS_TTXDONE_EN                                  0x00020000U
#define I2C_EVENT0_IMDIS_TTXDONE_DIS                                 0x00000000U
/*

        Field:           RXFIFOTRGT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO trigger in target mode

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_RXFIFOTRGT                                  0x00040000U
#define I2C_EVENT0_IMDIS_RXFIFOTRGT_M                                0x00040000U
#define I2C_EVENT0_IMDIS_RXFIFOTRGT_S                                18U
#define I2C_EVENT0_IMDIS_RXFIFOTRGT_EN                               0x00040000U
#define I2C_EVENT0_IMDIS_RXFIFOTRGT_DIS                              0x00000000U
/*

        Field:           TXFIFOTRGT
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO trigger in target mode

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TXFIFOTRGT                                  0x00080000U
#define I2C_EVENT0_IMDIS_TXFIFOTRGT_M                                0x00080000U
#define I2C_EVENT0_IMDIS_TXFIFOTRGT_S                                19U
#define I2C_EVENT0_IMDIS_TXFIFOTRGT_EN                               0x00080000U
#define I2C_EVENT0_IMDIS_TXFIFOTRGT_DIS                              0x00000000U
/*

        Field:           RXFIFOFULLT
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RXFIFO full event in target mode. This interrupt is set if an RX FIFO is full in target mode.

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_RXFIFOFULLT                                 0x00100000U
#define I2C_EVENT0_IMDIS_RXFIFOFULLT_M                               0x00100000U
#define I2C_EVENT0_IMDIS_RXFIFOFULLT_S                               20U
#define I2C_EVENT0_IMDIS_RXFIFOFULLT_EN                              0x00100000U
#define I2C_EVENT0_IMDIS_RXFIFOFULLT_DIS                             0x00000000U
/*

        Field:           TXEMPTYT
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO empty interrupt mask in target mode. This interrupt is set if all data in the TX FIFO in target mode have been shifted out and the transmit goes into idle mode.

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TXEMPTYT                                    0x00200000U
#define I2C_EVENT0_IMDIS_TXEMPTYT_M                                  0x00200000U
#define I2C_EVENT0_IMDIS_TXEMPTYT_S                                  21U
#define I2C_EVENT0_IMDIS_TXEMPTYT_EN                                 0x00200000U
#define I2C_EVENT0_IMDIS_TXEMPTYT_DIS                                0x00000000U
/*

        Field:           TSTART
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target start condition interrupt. Asserted when the received address matches the target address.

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TSTART                                      0x00400000U
#define I2C_EVENT0_IMDIS_TSTART_M                                    0x00400000U
#define I2C_EVENT0_IMDIS_TSTART_S                                    22U
#define I2C_EVENT0_IMDIS_TSTART_EN                                   0x00400000U
#define I2C_EVENT0_IMDIS_TSTART_DIS                                  0x00000000U
/*

        Field:           TSTOP
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target STOP detection interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TSTOP                                       0x00800000U
#define I2C_EVENT0_IMDIS_TSTOP_M                                     0x00800000U
#define I2C_EVENT0_IMDIS_TSTOP_S                                     23U
#define I2C_EVENT0_IMDIS_TSTOP_EN                                    0x00800000U
#define I2C_EVENT0_IMDIS_TSTOP_DIS                                   0x00000000U
/*

        Field:           TGENCALL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     write-only
        Description:     General call interrupt

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TGENCALL                                    0x01000000U
#define I2C_EVENT0_IMDIS_TGENCALL_M                                  0x01000000U
#define I2C_EVENT0_IMDIS_TGENCALL_S                                  24U
#define I2C_EVENT0_IMDIS_TGENCALL_EN                                 0x01000000U
#define I2C_EVENT0_IMDIS_TGENCALL_DIS                                0x00000000U
/*

        Field:           TX_UNFL_T
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX FIFO underflow	in target mode

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TX_UNFL_T                                   0x02000000U
#define I2C_EVENT0_IMDIS_TX_UNFL_T_M                                 0x02000000U
#define I2C_EVENT0_IMDIS_TX_UNFL_T_S                                 25U
#define I2C_EVENT0_IMDIS_TX_UNFL_T_EN                                0x02000000U
#define I2C_EVENT0_IMDIS_TX_UNFL_T_DIS                               0x00000000U
/*

        Field:           RX_OVFL_T
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX FIFO overflow in target mode

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_RX_OVFL_T                                   0x04000000U
#define I2C_EVENT0_IMDIS_RX_OVFL_T_M                                 0x04000000U
#define I2C_EVENT0_IMDIS_RX_OVFL_T_S                                 26U
#define I2C_EVENT0_IMDIS_RX_OVFL_T_EN                                0x04000000U
#define I2C_EVENT0_IMDIS_RX_OVFL_T_DIS                               0x00000000U
/*

        Field:           TARBLOST
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Target arbitration lost

        ENUMs:
            EN:                          Clear masked interrupt
            DIS:                         Writing 0 has no effect
*/
#define I2C_EVENT0_IMDIS_TARBLOST                                    0x08000000U
#define I2C_EVENT0_IMDIS_TARBLOST_M                                  0x08000000U
#define I2C_EVENT0_IMDIS_TARBLOST_S                                  27U
#define I2C_EVENT0_IMDIS_TARBLOST_EN                                 0x08000000U
#define I2C_EVENT0_IMDIS_TARBLOST_DIS                                0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVT_MODE
    Offset name:         I2C_O_EVT_MODE
    Relative address:    0x20
    Description:         Event mode register. It is used to select whether each line is disabled, in software mode (software clears the [RIS]) or in hardware mode (hardware clears the [RIS])
    Default Value:       0x00000001

        Field:           INT0_CFG
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Event line mode select for event corresponding to [INT_EVENT0]

        ENUMs:
            DIS:                         The interrupt or event line is disabled.
            SOFTWARE:                    The interrupt or event line is in software mode. Software must clear the RIS.
            HARDWARE:                    The interrupt or event line is in hardware mode. The hardware (another module) clears automatically the associated RIS flag.
*/
#define I2C_EVT_MODE_INT0_CFG_W                                      2U
#define I2C_EVT_MODE_INT0_CFG_M                                      0x00000003U
#define I2C_EVT_MODE_INT0_CFG_S                                      0U
#define I2C_EVT_MODE_INT0_CFG_DIS                                    0x00000000U
#define I2C_EVT_MODE_INT0_CFG_SOFTWARE                               0x00000001U
#define I2C_EVT_MODE_INT0_CFG_HARDWARE                               0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         I2C_O_DESC
    Relative address:    0x24
    Description:         This register identifies the peripheral and its exact version.
    Default Value:       0x00000000

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor rev of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_DESC_MINREV_W                                            4U
#define I2C_DESC_MINREV_M                                            0x0000000FU
#define I2C_DESC_MINREV_S                                            0U
#define I2C_DESC_MINREV_MINIMUM                                      0x00000000U
#define I2C_DESC_MINREV_MAXIMUM                                      0x0000000FU
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major rev of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_DESC_MAJREV_W                                            4U
#define I2C_DESC_MAJREV_M                                            0x000000F0U
#define I2C_DESC_MAJREV_S                                            4U
#define I2C_DESC_MAJREV_MINIMUM                                      0x00000000U
#define I2C_DESC_MAJREV_MAXIMUM                                      0x000000F0U
/*

        Field:           INSTNUM
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Instance Number within the device. This will be a parameter to the RTL for modules that can have multiple instances

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_DESC_INSTNUM_W                                           4U
#define I2C_DESC_INSTNUM_M                                           0x00000F00U
#define I2C_DESC_INSTNUM_S                                           8U
#define I2C_DESC_INSTNUM_MINIMUM                                     0x00000000U
#define I2C_DESC_INSTNUM_MAXIMUM                                     0x00000F00U
/*

        Field:           FEATUREVER
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Feature Set for the module *instance*

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_DESC_FEATUREVER_W                                        4U
#define I2C_DESC_FEATUREVER_M                                        0x0000F000U
#define I2C_DESC_FEATUREVER_S                                        12U
#define I2C_DESC_FEATUREVER_MINIMUM                                  0x00000000U
#define I2C_DESC_FEATUREVER_MAXIMUM                                  0x0000F000U
/*

        Field:           MODULEID
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Module identification contains a unique peripheral identification number. The assignments are maintained in a central database for all of the platform modules to ensure uniqueness.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define I2C_DESC_MODULEID_W                                          16U
#define I2C_DESC_MODULEID_M                                          0xFFFF0000U
#define I2C_DESC_MODULEID_S                                          16U
#define I2C_DESC_MODULEID_MINIMUM                                    0x00000000U
#define I2C_DESC_MODULEID_MAXIMUM                                    0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         I2C_O_CLKCFG
    Relative address:    0x1000
    Description:         This register controls the bus clock to *I2C*
    Default Value:       NA

        Field:           ENABLE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field enables or disables the bus clock to *I2C*

        ENUMs:
            DIS:                         I2C clock disabled
            EN:                          I2C clock disabled
*/
#define I2C_CLKCFG_ENABLE                                            0x00000001U
#define I2C_CLKCFG_ENABLE_M                                          0x00000001U
#define I2C_CLKCFG_ENABLE_S                                          0U
#define I2C_CLKCFG_ENABLE_DIS                                        0x00000000U
#define I2C_CLKCFG_ENABLE_EN                                         0x00000001U

#endif /* __HW_I2C_H__*/
