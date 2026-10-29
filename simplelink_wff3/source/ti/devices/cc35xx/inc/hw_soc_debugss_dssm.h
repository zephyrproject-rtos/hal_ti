/******************************************************************************
*  Filename:       hw_soc_debugss_dssm.h
*
*  Description:    Defines and prototypes for the SOC_DEBUGSS_DSSM peripheral.
*
*  Copyright (c) 2023-2025, Texas Instruments Incorporated
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
#ifndef __HW_SOC_DEBUGSS_DSSM_H__
#define __HW_SOC_DEBUGSS_DSSM_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SOC_DEBUGSS_DSSM component

--------------------------------------------------------------------------------- */

//This register provides the highest priority enabled interrupt index
#define SOC_DEBUGSS_DSSM_O_IIDX                                      0x00000020U

//Interrupt Mask
#define SOC_DEBUGSS_DSSM_O_IMASK                                     0x00000028U

//Raw Interrupt Status
#define SOC_DEBUGSS_DSSM_O_RIS                                       0x00000030U

//Masked Interrupt Status
#define SOC_DEBUGSS_DSSM_O_MIS                                       0x00000038U

//Interrupt Clear
#define SOC_DEBUGSS_DSSM_O_ICLR                                      0x00000040U

//Interrupt Set
#define SOC_DEBUGSS_DSSM_O_TRIG                                      0x00000048U

//This register is to select the primary debug domain
#define SOC_DEBUGSS_DSSM_O_PRIDBGDMN                                 0x000000E0U

//This register is used for data transfers from external debug tools to the DSSM module
#define SOC_DEBUGSS_DSSM_O_TXD                                       0x00000060U

//Transmit control register
#define SOC_DEBUGSS_DSSM_O_TXCTL                                     0x00000064U

//Receive data register
#define SOC_DEBUGSS_DSSM_O_RXD                                       0x00000068U

//Receive control register
#define SOC_DEBUGSS_DSSM_O_RXCTL                                     0x0000006CU

//This register is used to control SEC_DBG, NONSEC_DBG, SPIDEN, and SPNONSEC_DBG of Application APPCPU
#define SOC_DEBUGSS_DSSM_O_AUTHAPPCPU                                0x00000090U

//This register is used to control SEC_DBG, NONSEC_DBG, SPIDEN, and SPNONSEC_DBG of Application CORE
#define SOC_DEBUGSS_DSSM_O_AUTHCORE                                  0x000000A0U



/*-----------------------------------REGISTER------------------------------------
    Register name:       IIDX
    Offset name:         SOC_DEBUGSS_DSSM_O_IIDX
    Relative address:    0x20
    Description:         This register provides the highest priority enabled interrupt index. FFh means no event pending. Interrupt 0h is the highest priority, 1h next highest, and FEh is the least priority. The priority order is fixed. However, users can implement their own prioritization schemes using other registers that expose the full set of interrupts that have occurred.

                        On each read, only one interrupt is indicated. On a read, the current interrupt (highest priority) is automatically cleared by the hardware and the corresponding interrupt flag in the RIS and MIS are cleared as well. After a read from the CPU (not from the debug interface), the register must be updated with the next highest priority interrupt, if none are pending, then it displays FFh.
    Default Value:       0x00000000

        Field:           STAT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Interrupt index status

        ENUMs:
            NO_INTR:                     No pending interrupt request
            MSG_PEND:                    TX interrupt
            MSG_TAKEN:                   RX interrupt
*/
#define SOC_DEBUGSS_DSSM_IIDX_STAT_W                                 2U
#define SOC_DEBUGSS_DSSM_IIDX_STAT_M                                 0x00000003U
#define SOC_DEBUGSS_DSSM_IIDX_STAT_S                                 0U
#define SOC_DEBUGSS_DSSM_IIDX_STAT_NO_INTR                           0x00000000U
#define SOC_DEBUGSS_DSSM_IIDX_STAT_MSG_PEND                          0x00000001U
#define SOC_DEBUGSS_DSSM_IIDX_STAT_MSG_TAKEN                         0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMASK
    Offset name:         SOC_DEBUGSS_DSSM_O_IMASK
    Relative address:    0x28
    Description:         Interrupt Mask.

                        If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in IIDX, as well as MIS.
    Default Value:       0x00000000

        Field:           MSGPEND
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Masks MSG_PEND in MIS register

        ENUMs:
            CLR:                         Interrupt is masked out
            SET:                         Interrupt will request an interrupt service routine and corresponding bit in MIS will be set
*/
#define SOC_DEBUGSS_DSSM_IMASK_MSGPEND                               0x00000001U
#define SOC_DEBUGSS_DSSM_IMASK_MSGPEND_M                             0x00000001U
#define SOC_DEBUGSS_DSSM_IMASK_MSGPEND_S                             0U
#define SOC_DEBUGSS_DSSM_IMASK_MSGPEND_CLR                           0x00000000U
#define SOC_DEBUGSS_DSSM_IMASK_MSGPEND_SET                           0x00000001U
/*

        Field:           MSGTAKEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Masks MSG_TAKEN in MIS register

        ENUMs:
            CLR:                         Interrupt is masked out
            SET:                         Interrupt will request an interrupt service routine and corresponding bit in MIS will be set
*/
#define SOC_DEBUGSS_DSSM_IMASK_MSGTAKEN                              0x00000002U
#define SOC_DEBUGSS_DSSM_IMASK_MSGTAKEN_M                            0x00000002U
#define SOC_DEBUGSS_DSSM_IMASK_MSGTAKEN_S                            1U
#define SOC_DEBUGSS_DSSM_IMASK_MSGTAKEN_CLR                          0x00000000U
#define SOC_DEBUGSS_DSSM_IMASK_MSGTAKEN_SET                          0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         SOC_DEBUGSS_DSSM_O_RIS
    Relative address:    0x30
    Description:         Raw Interrupt Status.

                        Reflects all pending interrupts, regardless of masking. The RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           MSGPEND
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MSG_PEND

        ENUMs:
            SET:                         MSG_PEND occurred
            CLR:                         MSG_PEND did not occur
*/
#define SOC_DEBUGSS_DSSM_RIS_MSGPEND                                 0x00000001U
#define SOC_DEBUGSS_DSSM_RIS_MSGPEND_M                               0x00000001U
#define SOC_DEBUGSS_DSSM_RIS_MSGPEND_S                               0U
#define SOC_DEBUGSS_DSSM_RIS_MSGPEND_SET                             0x00000001U
#define SOC_DEBUGSS_DSSM_RIS_MSGPEND_CLR                             0x00000000U
/*

        Field:           MSGTAKEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MSG_TAKEN

        ENUMs:
            SET:                         MSG_TAKEN occurred
            CLR:                         MSG_TAKEN did not occur
*/
#define SOC_DEBUGSS_DSSM_RIS_MSGTAKEN                                0x00000002U
#define SOC_DEBUGSS_DSSM_RIS_MSGTAKEN_M                              0x00000002U
#define SOC_DEBUGSS_DSSM_RIS_MSGTAKEN_S                              1U
#define SOC_DEBUGSS_DSSM_RIS_MSGTAKEN_SET                            0x00000002U
#define SOC_DEBUGSS_DSSM_RIS_MSGTAKEN_CLR                            0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         SOC_DEBUGSS_DSSM_O_MIS
    Relative address:    0x38
    Description:         Masked Interrupt Status.

                        This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           MSGPEND
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked interrupt status for MSG_PEND

        ENUMs:
            SET:                         MSG_PEND requests an interrupt service routine
            CLR:                         MSG_PEND did not request an interrupt service routine
*/
#define SOC_DEBUGSS_DSSM_MIS_MSGPEND                                 0x00000001U
#define SOC_DEBUGSS_DSSM_MIS_MSGPEND_M                               0x00000001U
#define SOC_DEBUGSS_DSSM_MIS_MSGPEND_S                               0U
#define SOC_DEBUGSS_DSSM_MIS_MSGPEND_SET                             0x00000001U
#define SOC_DEBUGSS_DSSM_MIS_MSGPEND_CLR                             0x00000000U
/*

        Field:           MSGTAKEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked interrupt status for MSG_TAKEN

        ENUMs:
            SET:                         MSG_TAKEN requests an interrupt service routine
            CLR:                         MSG_TAKEN did not request an interrupt service routine
*/
#define SOC_DEBUGSS_DSSM_MIS_MSGTAKEN                                0x00000002U
#define SOC_DEBUGSS_DSSM_MIS_MSGTAKEN_M                              0x00000002U
#define SOC_DEBUGSS_DSSM_MIS_MSGTAKEN_S                              1U
#define SOC_DEBUGSS_DSSM_MIS_MSGTAKEN_SET                            0x00000002U
#define SOC_DEBUGSS_DSSM_MIS_MSGTAKEN_CLR                            0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         SOC_DEBUGSS_DSSM_O_ICLR
    Relative address:    0x40
    Description:         Interrupt Clear.

                        Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           MSGPEND
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears MSG_PEND_WROPT in RIS register

        ENUMs:
            CLR:                         RIS bit corresponding to MSG_PEND is cleared
            NO_EFFECT:                   Writing a 0 has no effect
*/
#define SOC_DEBUGSS_DSSM_ICLR_MSGPEND                                0x00000001U
#define SOC_DEBUGSS_DSSM_ICLR_MSGPEND_M                              0x00000001U
#define SOC_DEBUGSS_DSSM_ICLR_MSGPEND_S                              0U
#define SOC_DEBUGSS_DSSM_ICLR_MSGPEND_CLR                            0x00000001U
#define SOC_DEBUGSS_DSSM_ICLR_MSGPEND_NO_EFFECT                      0x00000000U
/*

        Field:           MSGTAKEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears MSG_TAKEN_WROPT in RIS register

        ENUMs:
            CLR:                         RIS bit corresponding to MSG_TAKEN is cleared
            NO_EFFECT:                   Writing a 0 has no effect
*/
#define SOC_DEBUGSS_DSSM_ICLR_MSGTAKEN                               0x00000002U
#define SOC_DEBUGSS_DSSM_ICLR_MSGTAKEN_M                             0x00000002U
#define SOC_DEBUGSS_DSSM_ICLR_MSGTAKEN_S                             1U
#define SOC_DEBUGSS_DSSM_ICLR_MSGTAKEN_CLR                           0x00000002U
#define SOC_DEBUGSS_DSSM_ICLR_MSGTAKEN_NO_EFFECT                     0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TRIG
    Offset name:         SOC_DEBUGSS_DSSM_O_TRIG
    Relative address:    0x48
    Description:         Interrupt Set.

                        Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           MSGPEND
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets MSG_PEND_WROPT in RIS register

        ENUMs:
            SET:                         RIS bit corresponding to MSG_PEND is set
            NO_EFFECT:                   Writing a 0 has no effect
*/
#define SOC_DEBUGSS_DSSM_TRIG_MSGPEND                                0x00000001U
#define SOC_DEBUGSS_DSSM_TRIG_MSGPEND_M                              0x00000001U
#define SOC_DEBUGSS_DSSM_TRIG_MSGPEND_S                              0U
#define SOC_DEBUGSS_DSSM_TRIG_MSGPEND_SET                            0x00000001U
#define SOC_DEBUGSS_DSSM_TRIG_MSGPEND_NO_EFFECT                      0x00000000U
/*

        Field:           MSGTAKEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Sets MSG_TAKEN_WROPT in RIS register

        ENUMs:
            SET:                         RIS bit corresponding to MSG_TAKEN is set
            NO_EFFECT:                   Writing a 0 has no effect
*/
#define SOC_DEBUGSS_DSSM_TRIG_MSGTAKEN                               0x00000002U
#define SOC_DEBUGSS_DSSM_TRIG_MSGTAKEN_M                             0x00000002U
#define SOC_DEBUGSS_DSSM_TRIG_MSGTAKEN_S                             1U
#define SOC_DEBUGSS_DSSM_TRIG_MSGTAKEN_SET                           0x00000002U
#define SOC_DEBUGSS_DSSM_TRIG_MSGTAKEN_NO_EFFECT                     0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIDBGDMN
    Offset name:         SOC_DEBUGSS_DSSM_O_PRIDBGDMN
    Relative address:    0xE0
    Description:         This register is to select the primary debug domain. Whichever domain is selected as primary gets powered up by writing onto csyspwrupreq bit
    Default Value:       0x00000001

        Field:           HOST
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Set this bit to 1 if host is to be selected as primary debug domain

*/
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_HOST                              0x00000001U
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_HOST_M                            0x00000001U
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_HOST_S                            0U
/*

        Field:           CORE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set this bit to 1 if core is to be selected as primary debug domain

*/
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_CORE                              0x00000002U
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_CORE_M                            0x00000002U
#define SOC_DEBUGSS_DSSM_PRIDBGDMN_CORE_S                            1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXD
    Offset name:         SOC_DEBUGSS_DSSM_O_TXD
    Relative address:    0x60
    Description:         This register is used for data transfers from external debug tools to the DSSM module. With the first write access to this register after power cycle a system reset request is issued.

                        The first write to this register after RESET_ALL will trigger a SYSRST request being asserted for one (or as many as required by the system) clock cycle.
    Default Value:       0x00000000

        Field:           TXDATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Contains data written by an external debug tool to the SEC-AP TXDATA register

*/
#define SOC_DEBUGSS_DSSM_TXD_TXDATA_W                                32U
#define SOC_DEBUGSS_DSSM_TXD_TXDATA_M                                0xFFFFFFFFU
#define SOC_DEBUGSS_DSSM_TXD_TXDATA_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXCTL
    Offset name:         SOC_DEBUGSS_DSSM_O_TXCTL
    Relative address:    0x64
    Description:         Transmit control register
    Default Value:       0x00000000

        Field:           TX
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates data request in DSSM.TXD, set on write via Debug AP to DSSM.TXD.

                         A read of the DSSM.TXD register by SM/OW will clear the TX field. The tool can check that TXD is empty by reading this field.
                         When this flag is 1, a debug request to the SM/OW controller is asserted. If the command starts with 0xAA,
                         the interrupt goes to the SM (or the OW if there is no SM) and if starts with 0x55, it always goes to the OW (going to AT-TEST authentication).

        ENUMs:
            EMPTY:                       TXD is empty
            FULL:                        TXD is full
*/
#define SOC_DEBUGSS_DSSM_TXCTL_TX                                    0x00000001U
#define SOC_DEBUGSS_DSSM_TXCTL_TX_M                                  0x00000001U
#define SOC_DEBUGSS_DSSM_TXCTL_TX_S                                  0U
#define SOC_DEBUGSS_DSSM_TXCTL_TX_EMPTY                              0x00000000U
#define SOC_DEBUGSS_DSSM_TXCTL_TX_FULL                               0x00000001U
/*

        Field:           TXFLAG
        From..to bits:   1...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Generic TX flags that can be set by external debug tool. Functionality is defined by SW.

*/
#define SOC_DEBUGSS_DSSM_TXCTL_TXFLAG_W                              31U
#define SOC_DEBUGSS_DSSM_TXCTL_TXFLAG_M                              0xFFFFFFFEU
#define SOC_DEBUGSS_DSSM_TXCTL_TXFLAG_S                              1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXD
    Offset name:         SOC_DEBUGSS_DSSM_O_RXD
    Relative address:    0x68
    Description:         Receive data register. This register contains the data received from SM/OW.
                        This data is read by external debug tool.
    Default Value:       0x00000000

        Field:           RXDATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Contains data written by SM/OW.

*/
#define SOC_DEBUGSS_DSSM_RXD_RXDATA_W                                32U
#define SOC_DEBUGSS_DSSM_RXD_RXDATA_M                                0xFFFFFFFFU
#define SOC_DEBUGSS_DSSM_RXD_RXDATA_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXCTL
    Offset name:         SOC_DEBUGSS_DSSM_O_RXCTL
    Relative address:    0x6C
    Description:         Receive control register
    Default Value:       0x00000000

        Field:           RCV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates SM/OW write to the DSSM.RXD register.
                         A read of the DSSM.RXD register by SWD (JTAG) Access Port will clear the RX field.

        ENUMs:
            EMPTY:                       RXD empty
            FULL:                        RXD full
*/
#define SOC_DEBUGSS_DSSM_RXCTL_RCV                                   0x00000001U
#define SOC_DEBUGSS_DSSM_RXCTL_RCV_M                                 0x00000001U
#define SOC_DEBUGSS_DSSM_RXCTL_RCV_S                                 0U
#define SOC_DEBUGSS_DSSM_RXCTL_RCV_EMPTY                             0x00000000U
#define SOC_DEBUGSS_DSSM_RXCTL_RCV_FULL                              0x00000001U
/*

        Field:           RCVFLAGS
        From..to bits:   1...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Generic RX flags that can be set by SW and read by external debug tool. Functionality is defined by SW.

*/
#define SOC_DEBUGSS_DSSM_RXCTL_RCVFLAGS_W                            31U
#define SOC_DEBUGSS_DSSM_RXCTL_RCVFLAGS_M                            0xFFFFFFFEU
#define SOC_DEBUGSS_DSSM_RXCTL_RCVFLAGS_S                            1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AUTHAPPCPU
    Offset name:         SOC_DEBUGSS_DSSM_O_AUTHAPPCPU
    Relative address:    0x90
    Description:         This register is used to control SEC_DBG, NONSEC_DBG, SPIDEN, and SPNONSEC_DBG of Application APPCPU.
                        SEC_DBG, NONSEC_DBG are further processed by DSW based on Active and Debug IPF ID.
    Default Value:       0x00000000

        Field:           SECDBG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controls invasive debug enable.
                         SEC_DBG is further processed by DSW based on Active and Debug IPF ID.

        ENUMs:
            DISABLE:                     Invasive debug disabled
            ENABLE:                      Invasive debug enabled
*/
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_SECDBG                           0x00000001U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_SECDBG_M                         0x00000001U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_SECDBG_S                         0U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_SECDBG_DISABLE                   0x00000000U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_SECDBG_ENABLE                    0x00000001U
/*

        Field:           NONSECDBG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controls non-invasive debug enable.
                         NONSEC_DBG is further processed by DSW based on Active and Debug IPF ID.

        ENUMs:
            DISABLE:                     Non-invasive debug disabled
            ENABLE:                      Non-invasive debug enabled
*/
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_NONSECDBG                        0x00000002U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_NONSECDBG_M                      0x00000002U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_NONSECDBG_S                      1U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_NONSECDBG_DISABLE                0x00000000U
#define SOC_DEBUGSS_DSSM_AUTHAPPCPU_NONSECDBG_ENABLE                 0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AUTHCORE
    Offset name:         SOC_DEBUGSS_DSSM_O_AUTHCORE
    Relative address:    0xA0
    Description:         This register is used to control SEC_DBG, NONSEC_DBG, SPIDEN, and SPNONSEC_DBG of Application CORE.
                        SEC_DBG, NONSEC_DBG are further processed by DSW based on Active and Debug IPF ID.
    Default Value:       0x00000000

        Field:           DBG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Controls invasive debug enable.
                         DBG is further processed by DSW based on Active and Debug IPF ID.

        ENUMs:
            DISABLE:                     Invasive debug disabled
            ENABLE:                      Invasive debug enabled
*/
#define SOC_DEBUGSS_DSSM_AUTHCORE_DBG                                0x00000001U
#define SOC_DEBUGSS_DSSM_AUTHCORE_DBG_M                              0x00000001U
#define SOC_DEBUGSS_DSSM_AUTHCORE_DBG_S                              0U
#define SOC_DEBUGSS_DSSM_AUTHCORE_DBG_DISABLE                        0x00000000U
#define SOC_DEBUGSS_DSSM_AUTHCORE_DBG_ENABLE                         0x00000001U

#endif /* __HW_SOC_DEBUGSS_DSSM_H__*/
