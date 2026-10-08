/******************************************************************************
*  Filename:       hw_hsm_sec.h
*
*  Description:    Defines and prototypes for the HSM_SEC peripheral.
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
#ifndef __HW_HSM_SEC_H__
#define __HW_HSM_SEC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HSM_SEC component

--------------------------------------------------------------------------------- */

//Clock Control Secured Register
#define HSM_SEC_O_CLKCTL                                             0x00000000U

//Soft Reset Control
#define HSM_SEC_O_SRSTCTL                                            0x00000004U

//PKA Abort Control Secured Register
#define HSM_SEC_O_PKACTL                                             0x00000008U

//Debug Control
#define HSM_SEC_O_DBGCTL                                             0x0000000CU

//DFT Control
#define HSM_SEC_O_DFTCTL                                             0x00000010U

//Clock FRO Divide Configuration
#define HSM_SEC_O_CLKFRODIV                                          0x00000014U

//Sleep Control
#define HSM_SEC_O_SLPCTL                                             0x00000018U



/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCTL
    Offset name:         HSM_SEC_O_CLKCTL
    Relative address:    0x0
    Description:         Clock Control Secured Register.

                        This register is used for enabling clock to the module.
    Default Value:       0x00000000

        Field:           CLKGO
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable clock to the module

        ENUMs:
            DIS:                         Write 0 to disable clock
            EN:                          Write 1 to enable clock
*/
#define HSM_SEC_CLKCTL_CLKGO                                         0x00000001U
#define HSM_SEC_CLKCTL_CLKGO_M                                       0x00000001U
#define HSM_SEC_CLKCTL_CLKGO_S                                       0U
#define HSM_SEC_CLKCTL_CLKGO_DIS                                     0x00000000U
#define HSM_SEC_CLKCTL_CLKGO_EN                                      0x00000001U
/*

        Field:           HIFCLKGO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable host interface clock

        ENUMs:
            DIS:                         Write 0 to disable clock

            EN:                          Write 1 to enable clock
*/
#define HSM_SEC_CLKCTL_HIFCLKGO                                      0x00000002U
#define HSM_SEC_CLKCTL_HIFCLKGO_M                                    0x00000002U
#define HSM_SEC_CLKCTL_HIFCLKGO_S                                    1U
#define HSM_SEC_CLKCTL_HIFCLKGO_DIS                                  0x00000000U
#define HSM_SEC_CLKCTL_HIFCLKGO_EN                                   0x00000002U
/*

        Field:           CNTCLKGO
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable counter clock

        ENUMs:
            DIS:                         Write 0 to disable clock

            EN:                          Write 1 to enable clock
*/
#define HSM_SEC_CLKCTL_CNTCLKGO                                      0x00000004U
#define HSM_SEC_CLKCTL_CNTCLKGO_M                                    0x00000004U
#define HSM_SEC_CLKCTL_CNTCLKGO_S                                    2U
#define HSM_SEC_CLKCTL_CNTCLKGO_DIS                                  0x00000000U
#define HSM_SEC_CLKCTL_CNTCLKGO_EN                                   0x00000004U
/*

        Field:           CLKDISREQ
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit is set to disable all clock sources.

        ENUMs:
            DIS:                         Write 1 to disable clock
*/
#define HSM_SEC_CLKCTL_CLKDISREQ                                     0x00000008U
#define HSM_SEC_CLKCTL_CLKDISREQ_M                                   0x00000008U
#define HSM_SEC_CLKCTL_CLKDISREQ_S                                   3U
#define HSM_SEC_CLKCTL_CLKDISREQ_DIS                                 0x00000008U
/*

        Field:           CLKBUSY
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     when 1b, indicates that the module is active and busy with processing data and tokens.

*/
#define HSM_SEC_CLKCTL_CLKBUSY                                       0x00000010U
#define HSM_SEC_CLKCTL_CLKBUSY_M                                     0x00000010U
#define HSM_SEC_CLKCTL_CLKBUSY_S                                     4U
/*

        Field:           HIFCLKBUSY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     When 1b indicates the Host interface is active and busy with Host bus transfers.

*/
#define HSM_SEC_CLKCTL_HIFCLKBUSY                                    0x00000020U
#define HSM_SEC_CLKCTL_HIFCLKBUSY_M                                  0x00000020U
#define HSM_SEC_CLKCTL_HIFCLKBUSY_S                                  5U
/*

        Field:           CTLCLKBUSY
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     When 1b, indicates that the counter clock domain is active. This signal is always asserted (set to '1'), except when the
                         counter module is in reset (ctr_reset_n set to '0').

*/
#define HSM_SEC_CLKCTL_CTLCLKBUSY                                    0x00000040U
#define HSM_SEC_CLKCTL_CTLCLKBUSY_M                                  0x00000040U
#define HSM_SEC_CLKCTL_CTLCLKBUSY_S                                  6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRSTCTL
    Offset name:         HSM_SEC_O_SRSTCTL
    Relative address:    0x4
    Description:         Soft Reset Control.

                        This register is used for controlling soft reset mechanism.
    Default Value:       0x00000000

        Field:           ABORTREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write this bit to request soft reset. It is a write-clear or auto clear register.

        ENUMs:
            REQ:                         To enable Abort request
*/
#define HSM_SEC_SRSTCTL_ABORTREQ                                     0x00000001U
#define HSM_SEC_SRSTCTL_ABORTREQ_M                                   0x00000001U
#define HSM_SEC_SRSTCTL_ABORTREQ_S                                   0U
#define HSM_SEC_SRSTCTL_ABORTREQ_REQ                                 0x00000001U
/*

        Field:           ABORTACK
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     when 1b, indicates abort request is acknowledged by EIP and soft reset is asserted

*/
#define HSM_SEC_SRSTCTL_ABORTACK                                     0x00000002U
#define HSM_SEC_SRSTCTL_ABORTACK_M                                   0x00000002U
#define HSM_SEC_SRSTCTL_ABORTACK_S                                   1U
/*

        Field:           FRCACK
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 1b, to forcely assert soft reset without waiting for abort acknowledge from EIP.

        ENUMs:
            EN:                          To force soft reset
*/
#define HSM_SEC_SRSTCTL_FRCACK                                       0x00000004U
#define HSM_SEC_SRSTCTL_FRCACK_M                                     0x00000004U
#define HSM_SEC_SRSTCTL_FRCACK_S                                     2U
#define HSM_SEC_SRSTCTL_FRCACK_EN                                    0x00000004U
/*

        Field:           STA
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     When 1b, soft reset is asserted to the module

*/
#define HSM_SEC_SRSTCTL_STA                                          0x00000008U
#define HSM_SEC_SRSTCTL_STA_M                                        0x00000008U
#define HSM_SEC_SRSTCTL_STA_S                                        3U
/*

        Field:           STATE
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     It indicates state of soft reset assertion.

        ENUMs:
            IDLE:                        soft reset is not requested
            REQ:                         Soft reset is requested
            ACK:                         Soft reset is acknowledged.
            ASSERT:                      Soft reset can be asserted
            SET:                         soft reset is set
*/
#define HSM_SEC_SRSTCTL_STATE_W                                      3U
#define HSM_SEC_SRSTCTL_STATE_M                                      0x00000070U
#define HSM_SEC_SRSTCTL_STATE_S                                      4U
#define HSM_SEC_SRSTCTL_STATE_IDLE                                   0x00000000U
#define HSM_SEC_SRSTCTL_STATE_REQ                                    0x00000010U
#define HSM_SEC_SRSTCTL_STATE_ACK                                    0x00000020U
#define HSM_SEC_SRSTCTL_STATE_ASSERT                                 0x00000030U
#define HSM_SEC_SRSTCTL_STATE_SET                                    0x00000040U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PKACTL
    Offset name:         HSM_SEC_O_PKACTL
    Relative address:    0x8
    Description:         PKA Abort Control Secured Register.

                        This register is used for aborting PKA operation.
    Default Value:       0x00000000

        Field:           ABORT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write 1 to Abort.

        ENUMs:
            ABORT:                       Write 1 to this bit to abort PKA operation
*/
#define HSM_SEC_PKACTL_ABORT                                         0x00000001U
#define HSM_SEC_PKACTL_ABORT_M                                       0x00000001U
#define HSM_SEC_PKACTL_ABORT_S                                       0U
#define HSM_SEC_PKACTL_ABORT_ABORT                                   0x00000001U
/*

        Field:           NSMASKREQ
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit is used to mask PKA abort request generated by non-secure controller.

        ENUMs:
            MASK:                        Mask request
*/
#define HSM_SEC_PKACTL_NSMASKREQ                                     0x00000002U
#define HSM_SEC_PKACTL_NSMASKREQ_M                                   0x00000002U
#define HSM_SEC_PKACTL_NSMASKREQ_S                                   1U
#define HSM_SEC_PKACTL_NSMASKREQ_MASK                                0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGCTL
    Offset name:         HSM_SEC_O_DBGCTL
    Relative address:    0xC
    Description:         Debug Control.

                        This register is used for HSM memory and asset debug through OCP only if TI debug access is enabled
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This register enables debug through OCP.
                         To enable FIFO0   , bit0 should be set.
                         To enable FIFO1   , bit1 should be set.
                         To enable MBIN    , bit2 should be set.
                         To enable MBOUT, bit3 should be set.
                         To enable OTP      , bit4 should be set.
                         To enable DRAM   , bit5 should be set.
                         To enable PROM   , bit6 should be set.

*/
#define HSM_SEC_DBGCTL_SEL_W                                         7U
#define HSM_SEC_DBGCTL_SEL_M                                         0x0000007FU
#define HSM_SEC_DBGCTL_SEL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DFTCTL
    Offset name:         HSM_SEC_O_DFTCTL
    Relative address:    0x10
    Description:         DFT Control.

                        This register is used for enabling FRO controls if TI test access is enabled
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FRO selection input. A selected FRO will have its fro_testin input forced low. Valid value to select FRO's is 0-7.

*/
#define HSM_SEC_DFTCTL_SEL_W                                         5U
#define HSM_SEC_DFTCTL_SEL_M                                         0x0000001FU
#define HSM_SEC_DFTCTL_SEL_S                                         0U
/*

        Field:           CTLEN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Active HIGH enable signal for FRO characterization (enables the tst_fro_select, tst_fro_enable and tst_fro_delay inputs).
                         This is a combinatorial function. The TRNG module clocks do not need to run for this to work.

*/
#define HSM_SEC_DFTCTL_CTLEN                                         0x00000020U
#define HSM_SEC_DFTCTL_CTLEN_M                                       0x00000020U
#define HSM_SEC_DFTCTL_CTLEN_S                                       5U
/*

        Field:           ENABLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Active HIGH enable signal for FRO selected by tst_fro_select

*/
#define HSM_SEC_DFTCTL_ENABLE                                        0x00000040U
#define HSM_SEC_DFTCTL_ENABLE_M                                      0x00000040U
#define HSM_SEC_DFTCTL_ENABLE_S                                      6U
/*

        Field:           DLY
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Delay chain length selection for FRO selected by tst_fro_select. This input should only be changed while
                         tst_fro_enable is LOW.

*/
#define HSM_SEC_DFTCTL_DLY                                           0x00000080U
#define HSM_SEC_DFTCTL_DLY_M                                         0x00000080U
#define HSM_SEC_DFTCTL_DLY_S                                         7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKFRODIV
    Offset name:         HSM_SEC_O_CLKFRODIV
    Relative address:    0x14
    Description:         Clock FRO Divide Configuration.

                        This register is used for controlling FRO clock measurements.
    Default Value:       0x00000002

        Field:           VAL
        From..to bits:   0...6
        DefaultValue:    0x2
        Access type:     read-write
        Description:     It is used for dividing FRO clock withe the division value specified by this register.
                         Division value should be from 2-80.

*/
#define HSM_SEC_CLKFRODIV_VAL_W                                      7U
#define HSM_SEC_CLKFRODIV_VAL_M                                      0x0000007FU
#define HSM_SEC_CLKFRODIV_VAL_S                                      0U
/*

        Field:           EN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     It is write enable signal used for loading division value onto divider.
                         It should be disable and re-enable after changing the mem_value

*/
#define HSM_SEC_CLKFRODIV_EN                                         0x00000080U
#define HSM_SEC_CLKFRODIV_EN_M                                       0x00000080U
#define HSM_SEC_CLKFRODIV_EN_S                                       7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SLPCTL
    Offset name:         HSM_SEC_O_SLPCTL
    Relative address:    0x18
    Description:         Sleep Control.
    Default Value:       0x00000000

        Field:           OVRVAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     power_mode_in override value by FW. FW can set to 1 after cold boot

*/
#define HSM_SEC_SLPCTL_OVRVAL                                        0x00000001U
#define HSM_SEC_SLPCTL_OVRVAL_M                                      0x00000001U
#define HSM_SEC_SLPCTL_OVRVAL_S                                      0U
/*

        Field:           SRCVAL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     power_mode_in source select MMR
                         0-power_mode_in comes from logic
                         1-power_mode_in comes from mem_slp_ovr_val

*/
#define HSM_SEC_SLPCTL_SRCVAL                                        0x00000002U
#define HSM_SEC_SLPCTL_SRCVAL_M                                      0x00000002U
#define HSM_SEC_SLPCTL_SRCVAL_S                                      1U

#endif /* __HW_HSM_SEC_H__*/
