/******************************************************************************
*  Filename:       hw_rtc.h
*
*  Description:    Defines and prototypes for the RTC peripheral.
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
#ifndef __HW_RTC_H__
#define __HW_RTC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the RTC component

--------------------------------------------------------------------------------- */

//Description Register
#define RTC_O_DESC                                                   0x00000000U

//RTC Control register
#define RTC_O_CTL                                                    0x00000004U

//RTC channel mode set register
#define RTC_O_ARMSET                                                 0x00000008U

//RTC channel mode clear register
#define RTC_O_ARMCLR                                                 0x0000000CU

//RTC Time value register
#define RTC_O_TIME250N                                               0x00000010U

//RTC Time value register
#define RTC_O_TIME1U                                                 0x00000014U

//RTC Time value register
#define RTC_O_TIME8U                                                 0x00000018U

//RTC time value register
#define RTC_O_TIME524M                                               0x0000001CU

//Channel 0 compare value with 250ns resolution
#define RTC_O_CH0CC250N                                              0x00000020U

//Channel 0 compare value with 1us resolution
#define RTC_O_CH0CC1U                                                0x00000024U

//Channel 0 compare value
#define RTC_O_CH0CC8U                                                0x00000028U

//Channel 1 capture value
#define RTC_O_CH1CC8U                                                0x00000038U

//Channel 1 configuration register
#define RTC_O_CH1CFG                                                 0x0000003CU

//Interrupt Mask
#define RTC_O_IMASK                                                  0x00000044U

//Interrupt mask
#define RTC_O_RIS                                                    0x00000048U

//Masked interrupt status
#define RTC_O_MIS                                                    0x0000004CU

//Interrupt set register
#define RTC_O_ISET                                                   0x00000050U

//Interrupt clear register
#define RTC_O_ICLR                                                   0x00000054U

//Interrupt mask set register
#define RTC_O_IMSET                                                  0x00000058U

//Interrupt mask clear register
#define RTC_O_IMCLR                                                  0x0000005CU

//Emulation control register
#define RTC_O_EMU                                                    0x00000060U

//Digital test bus control register
#define RTC_O_DTB                                                    0x00000064U

//A delta time mechanism is implemented for RTC that allows the TIME value to be adjusted under software control
#define RTC_O_DTIME                                                  0x00000068U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         RTC_O_DESC
    Relative address:    0x0
    Description:         Description Register. This register provides IP module ID, revision information, instance index and standard MMR registers offset.
    Default Value:       0x64421010

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision of IP (0-15).

*/
#define RTC_DESC_MINREV_W                                            4U
#define RTC_DESC_MINREV_M                                            0x0000000FU
#define RTC_DESC_MINREV_S                                            0U
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Major revision of IP (0-15).

*/
#define RTC_DESC_MAJREV_W                                            4U
#define RTC_DESC_MAJREV_M                                            0x000000F0U
#define RTC_DESC_MAJREV_S                                            4U
/*

        Field:           INSTIDX
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IP Instance ID number. If multiple instances of IP exist in the device, this field can identify the instance number (0-15).

*/
#define RTC_DESC_INSTIDX_W                                           4U
#define RTC_DESC_INSTIDX_M                                           0x00000F00U
#define RTC_DESC_INSTIDX_S                                           8U
/*

        Field:           STDIPOFF
        From..to bits:   12...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Standard IP MMR block offset. Standard IP MMRs are the set of from aggregated IRQ registers till DTB.

                         0: Standard IP MMRs do not exist

                         0x1-0xF: Standard IP MMRs begin at offset of (64*[STDIPOFF] from the base IP address)

*/
#define RTC_DESC_STDIPOFF_W                                          4U
#define RTC_DESC_STDIPOFF_M                                          0x0000F000U
#define RTC_DESC_STDIPOFF_S                                          12U
/*

        Field:           MODID
        From..to bits:   16...31
        DefaultValue:    0x6442
        Access type:     read-only
        Description:     Module identifier used to uniquely identify this IP.

*/
#define RTC_DESC_MODID_W                                             16U
#define RTC_DESC_MODID_M                                             0xFFFF0000U
#define RTC_DESC_MODID_S                                             16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL
    Offset name:         RTC_O_CTL
    Relative address:    0x4
    Description:         RTC Control register. This register controls resetting the of RTC counter
    Default Value:       0x00000000

        Field:           RST
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RTC counter reset. Writing 1 to this bit will reset the RTC counter, and cause it to resume counting from 0x0

        ENUMs:
            NOEFF:                       No effect
            CLR:                         Reset the timer.
*/
#define RTC_CTL_RST                                                  0x00000001U
#define RTC_CTL_RST_M                                                0x00000001U
#define RTC_CTL_RST_S                                                0U
#define RTC_CTL_RST_NOEFF                                            0x00000000U
#define RTC_CTL_RST_CLR                                              0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARMSET
    Offset name:         RTC_O_ARMSET
    Relative address:    0x8
    Description:         RTC channel mode set register. Read to each bit field of this register provides the current channel mode.
                        - Read of 1'b0 indicates the channel is unarmed.
                        - Read of 1'b1 indicates the channel is either in capture or compare mode.

                        A write to each bitfield of this register the following effect:
                        - Write of 1'b0 has no effect on channel mode.
                        - Write of 1'b1 has no effect on the compare channel. While write of 1'b1 for capture channel will arm it in capture mode if it is disabled.
    Default Value:       0x00000000

        Field:           CH0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     No effect on arming the channel. Read will give the status of the Channel 0.

        ENUMs:
            NOEFF:                       No effect on the channel
            SET:                         No effect on the compare channel
*/
#define RTC_ARMSET_CH0                                               0x00000001U
#define RTC_ARMSET_CH0_M                                             0x00000001U
#define RTC_ARMSET_CH0_S                                             0U
#define RTC_ARMSET_CH0_NOEFF                                         0x00000000U
#define RTC_ARMSET_CH0_SET                                           0x00000001U
/*

        Field:           CH1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Arming Channel 1 for capture operation.

        ENUMs:
            NOEFF:                       No effect on the channel
            SET:                         Enable the Channel 1 for capture operation
*/
#define RTC_ARMSET_CH1                                               0x00000002U
#define RTC_ARMSET_CH1_M                                             0x00000002U
#define RTC_ARMSET_CH1_S                                             1U
#define RTC_ARMSET_CH1_NOEFF                                         0x00000000U
#define RTC_ARMSET_CH1_SET                                           0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ARMCLR
    Offset name:         RTC_O_ARMCLR
    Relative address:    0xC
    Description:         RTC channel mode clear register. Read to each bit field of this register provides the current channel mode.
                        - Read of 1'b0 indicates the channel is unarmed.
                        - Read of 1'b1 indicates the channel is either in capture or compare mode.

                        A write to each bitfield of this register the following effect:
                        - Write of 1'b0 has no effect on channel mode.
                        - Write of 1'b1 for capture/compare channel will disarm it without triggering event unless a compare/capture event happens in the same cycle.
    Default Value:       0x00000000

        Field:           CH0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Disarming Channel 0

        ENUMs:
            NOEFF:                       No effect on the channel
            CLR:                         Set channel in UNARMED state without triggering event unless a compare event happens in the same cycle
*/
#define RTC_ARMCLR_CH0                                               0x00000001U
#define RTC_ARMCLR_CH0_M                                             0x00000001U
#define RTC_ARMCLR_CH0_S                                             0U
#define RTC_ARMCLR_CH0_NOEFF                                         0x00000000U
#define RTC_ARMCLR_CH0_CLR                                           0x00000001U
/*

        Field:           CH1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Disarming Channel 1

        ENUMs:
            NOEFF:                       No effect on the channel
            CLR:                         Set channel in UNARMED state without triggering event unless a capture event happens in the same cycle
*/
#define RTC_ARMCLR_CH1                                               0x00000002U
#define RTC_ARMCLR_CH1_M                                             0x00000002U
#define RTC_ARMCLR_CH1_S                                             1U
#define RTC_ARMCLR_CH1_NOEFF                                         0x00000000U
#define RTC_ARMCLR_CH1_CLR                                           0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME250N
    Offset name:         RTC_O_TIME250N
    Relative address:    0x10
    Description:         RTC Time value register. 32-bit unsigned integer representing [29:-2] time slice of the real time clock counter. The counter runs on **LFCLK**. This field has a resolution of 250ns, and range of about 17.8 minutes.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Unsigned integer representing [34:3]slice of real time counter.

*/
#define RTC_TIME250N_VAL_W                                           32U
#define RTC_TIME250N_VAL_M                                           0xFFFFFFFFU
#define RTC_TIME250N_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME1U
    Offset name:         RTC_O_TIME1U
    Relative address:    0x14
    Description:         RTC Time value register. 32-bit unsigned integer representing [31:0] time slice of the real time clock counter. The counter runs on **LFCLK**. This field has a resolution of 1us, and range of about 1.19 hours.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Unsigned integer representing [34:3]slice of real time counter.


*/
#define RTC_TIME1U_VAL_W                                             32U
#define RTC_TIME1U_VAL_M                                             0xFFFFFFFFU
#define RTC_TIME1U_VAL_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME8U
    Offset name:         RTC_O_TIME8U
    Relative address:    0x18
    Description:         RTC Time value register. 32-bit unsigned integer representing [34:3] time slice of the real time clock counter. The counter runs on **LFCLK**. This field has a resolution of 8us, and range of about 9.5 hours.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Unsigned integer representing [34:3]slice of real time counter.


*/
#define RTC_TIME8U_VAL_W                                             32U
#define RTC_TIME8U_VAL_M                                             0xFFFFFFFFU
#define RTC_TIME8U_VAL_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIME524M
    Offset name:         RTC_O_TIME524M
    Relative address:    0x1C
    Description:         RTC time value register. 32-bit unsigned integer representing [50:19] time slice of the real time clock counter. This field has a resolution of about 0.5s and a range of about 71.4 years.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Unsigned integer representing. [50:19]slice of real time counter.

*/
#define RTC_TIME524M_VAL_W                                           32U
#define RTC_TIME524M_VAL_M                                           0xFFFFFFFFU
#define RTC_TIME524M_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CC250N
    Offset name:         RTC_O_CH0CC250N
    Relative address:    0x20
    Description:         Channel 0 compare value with 250ns resolution. A read to this register returns the value {CH0CC8U[29:3], 5b'0}
                        A write to this register arms the channel in compare mode.  Event would occur at the same time +/ Tlfclk/2 on the RTC as if it was written to SYSTIM.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RTC Channel 0 compare value. This value is compared against [TIME8U.VAL]. A Channel 0 event is generated when [TIME8U.VAL] value reaches or exceeds this compare value.

*/
#define RTC_CH0CC250N_VAL_W                                          32U
#define RTC_CH0CC250N_VAL_M                                          0xFFFFFFFFU
#define RTC_CH0CC250N_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CC1U
    Offset name:         RTC_O_CH0CC1U
    Relative address:    0x24
    Description:         Channel 0 compare value with 1us resolution. A read to this register returns the value {CH0CC8U[31:3], 3b'0}
                        A write to this register arms the channel in compare mode.  Event would occur at the same time +/ Tlfclk/2 on the RTC as if it was written to SYSTIM.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RTC Channel 0 compare value. This value is compared against [TIME8U.VAL]. A Channel 0 event is generated when [TIME8U.VAL] value reaches or exceeds this compare value.

*/
#define RTC_CH0CC1U_VAL_W                                            32U
#define RTC_CH0CC1U_VAL_M                                            0xFFFFFFFFU
#define RTC_CH0CC1U_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0CC8U
    Offset name:         RTC_O_CH0CC8U
    Relative address:    0x28
    Description:         Channel 0 compare value. A write to this register automatically enables the channel to trigger an event when RTC timer reaches the programmed value or if the programmed value is 1 sec in the past.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RTC Channel 0 compare value. This value is compared against [TIME8U.VAL]. A Channel 0 event is generated when [TIME8U.VAL] value reaches or exceeds this compare value.

*/
#define RTC_CH0CC8U_VAL_W                                            32U
#define RTC_CH0CC8U_VAL_M                                            0xFFFFFFFFU
#define RTC_CH0CC8U_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1CC8U
    Offset name:         RTC_O_CH1CC8U
    Relative address:    0x38
    Description:         Channel 1 capture value. This register captures the RTC time slice [34:3] on each selected edge of the capture event when the [ARMSET.CH1] = 1.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     [TIME8U.VAL] captured value at the last selected edge of capture event.

*/
#define RTC_CH1CC8U_VAL_W                                            21U
#define RTC_CH1CC8U_VAL_M                                            0x001FFFFFU
#define RTC_CH1CC8U_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1CFG
    Offset name:         RTC_O_CH1CFG
    Relative address:    0x3C
    Description:         Channel 1 configuration register. This register can be used to select the capture edge for generating the capture event.
    Default Value:       0x00000000

        Field:           EDGE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Edge detect configuration for capture source

        ENUMs:
            RISE:                        Rising Edge.
            FALL:                        Falling Edge.
*/
#define RTC_CH1CFG_EDGE                                              0x00000001U
#define RTC_CH1CFG_EDGE_M                                            0x00000001U
#define RTC_CH1CFG_EDGE_S                                            0U
#define RTC_CH1CFG_EDGE_RISE                                         0x00000000U
#define RTC_CH1CFG_EDGE_FALL                                         0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMASK
    Offset name:         RTC_O_IMASK
    Relative address:    0x44
    Description:         Interrupt Mask. If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in IIDX, as well as MIS.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 0 Event Interrupt Mask.

        ENUMs:
            DIS:                         Disable Interrupt Mask
            EN:                          Enable Interrupt Mask
*/
#define RTC_IMASK_EV0                                                0x00000001U
#define RTC_IMASK_EV0_M                                              0x00000001U
#define RTC_IMASK_EV0_S                                              0U
#define RTC_IMASK_EV0_DIS                                            0x00000000U
#define RTC_IMASK_EV0_EN                                             0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 1 Event Interrupt Mask.

        ENUMs:
            DIS:                         Clear Interrupt Mask
            EN:                          Enable Interrrupt Mask
*/
#define RTC_IMASK_EV1                                                0x00000002U
#define RTC_IMASK_EV1_M                                              0x00000002U
#define RTC_IMASK_EV1_S                                              1U
#define RTC_IMASK_EV1_DIS                                            0x00000000U
#define RTC_IMASK_EV1_EN                                             0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         RTC_O_RIS
    Relative address:    0x48
    Description:         Interrupt mask. This register selects interrupt sources which are allowed to pass from [RIS.*] to [MIS.*] when the corresponding bit-fields are set to 1.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for Channel 0 event.

                         This bit is set to 1 when a compare event occurs on Channel 0.
                         This bit will be cleared. When the corresponding bit in [ICLR.EV0] is set to 1. Or when a new compare value is written in [CH0CC8U.*] register

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define RTC_RIS_EV0                                                  0x00000001U
#define RTC_RIS_EV0_M                                                0x00000001U
#define RTC_RIS_EV0_S                                                0U
#define RTC_RIS_EV0_CLR                                              0x00000000U
#define RTC_RIS_EV0_SET                                              0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for Channel 1 event.

                         This bit is set to 1 when a capture event is received on Channel 1.
                         This bit will be cleared when the bit in [ICLR.EV1] is set to 1 or when the captured time value is read from the [CH1CC8U.*] register.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define RTC_RIS_EV1                                                  0x00000002U
#define RTC_RIS_EV1_M                                                0x00000002U
#define RTC_RIS_EV1_S                                                1U
#define RTC_RIS_EV1_CLR                                              0x00000000U
#define RTC_RIS_EV1_SET                                              0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         RTC_O_MIS
    Relative address:    0x4C
    Description:         Masked interrupt status. This register is simply a bitwise AND of the contents of [IMASK.*] and RIS.*] registers. A flag set in this register can be cleared by writing 1 to the corresponding [ICLR.*] register bit.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked interrupt status for channel 0 event.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define RTC_MIS_EV0                                                  0x00000001U
#define RTC_MIS_EV0_M                                                0x00000001U
#define RTC_MIS_EV0_S                                                0U
#define RTC_MIS_EV0_CLR                                              0x00000000U
#define RTC_MIS_EV0_SET                                              0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked interrupt status for channel 1 event.

        ENUMs:
            CLR:                         Interrupt did not occur
            SET:                         Interrupt occured
*/
#define RTC_MIS_EV1                                                  0x00000002U
#define RTC_MIS_EV1_M                                                0x00000002U
#define RTC_MIS_EV1_S                                                1U
#define RTC_MIS_EV1_CLR                                              0x00000000U
#define RTC_MIS_EV1_SET                                              0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISET
    Offset name:         RTC_O_ISET
    Relative address:    0x50
    Description:         Interrupt set register. This register can used by software for diagnostics and safety checking purposes. Writing a 1 to a bit in this register will set the event and the corresponding [RIS.*] bit also gets set. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets set.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Channel 0 event Interrupt.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set interrupt
*/
#define RTC_ISET_EV0                                                 0x00000001U
#define RTC_ISET_EV0_M                                               0x00000001U
#define RTC_ISET_EV0_S                                               0U
#define RTC_ISET_EV0_NO_EFFECT                                       0x00000000U
#define RTC_ISET_EV0_SET                                             0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Channel 1 event Interrupt.

        ENUMs:
            NO_EFFECT:                   Writing 0 has no effect
            SET:                         Set interrupt
*/
#define RTC_ISET_EV1                                                 0x00000002U
#define RTC_ISET_EV1_M                                               0x00000002U
#define RTC_ISET_EV1_S                                               1U
#define RTC_ISET_EV1_NO_EFFECT                                       0x00000000U
#define RTC_ISET_EV1_SET                                             0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         RTC_O_ICLR
    Relative address:    0x54
    Description:         Interrupt clear register. This register allows software to clear interrupts. Writing a 1 to a bit in this register will clear the event and the corresponding [RIS.*] bit also gets cleared. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets cleared.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears channel 0 event interrupt.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            CLR:                         Clear Interrupt.
*/
#define RTC_ICLR_EV0                                                 0x00000001U
#define RTC_ICLR_EV0_M                                               0x00000001U
#define RTC_ICLR_EV0_S                                               0U
#define RTC_ICLR_EV0_NO_EFF                                          0x00000000U
#define RTC_ICLR_EV0_CLR                                             0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears channel 1 event interrupt.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            CLR:                         Clear Interrupt
*/
#define RTC_ICLR_EV1                                                 0x00000002U
#define RTC_ICLR_EV1_M                                               0x00000002U
#define RTC_ICLR_EV1_S                                               1U
#define RTC_ICLR_EV1_NO_EFF                                          0x00000000U
#define RTC_ICLR_EV1_CLR                                             0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMSET
    Offset name:         RTC_O_IMSET
    Relative address:    0x58
    Description:         Interrupt mask set register. Writing a 1 to a bit in this register will set the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set channel 0 event interrupt mask.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            SET:                         Set interrupt mask
*/
#define RTC_IMSET_EV0                                                0x00000001U
#define RTC_IMSET_EV0_M                                              0x00000001U
#define RTC_IMSET_EV0_S                                              0U
#define RTC_IMSET_EV0_NO_EFF                                         0x00000000U
#define RTC_IMSET_EV0_SET                                            0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set channel 1 event interrupt mask.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            SET:                         Set interrupt mask
*/
#define RTC_IMSET_EV1                                                0x00000002U
#define RTC_IMSET_EV1_M                                              0x00000002U
#define RTC_IMSET_EV1_S                                              1U
#define RTC_IMSET_EV1_NO_EFF                                         0x00000000U
#define RTC_IMSET_EV1_SET                                            0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMCLR
    Offset name:         RTC_O_IMCLR
    Relative address:    0x5C
    Description:         Interrupt mask clear register. Writing a 1 to a bit in this register will clear the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           EV0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears Channel 0 event interrupt mask.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            CLR:                         Clear Interrupt Mask
*/
#define RTC_IMCLR_EV0                                                0x00000001U
#define RTC_IMCLR_EV0_M                                              0x00000001U
#define RTC_IMCLR_EV0_S                                              0U
#define RTC_IMCLR_EV0_NO_EFF                                         0x00000000U
#define RTC_IMCLR_EV0_CLR                                            0x00000001U
/*

        Field:           EV1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clears Channel 1 event interrupt mask.

        ENUMs:
            NO_EFF:                      Writing 0 has no effect
            CLR:                         Clear Interrupt Mask
*/
#define RTC_IMCLR_EV1                                                0x00000002U
#define RTC_IMCLR_EV1_M                                              0x00000002U
#define RTC_IMCLR_EV1_S                                              1U
#define RTC_IMCLR_EV1_NO_EFF                                         0x00000000U
#define RTC_IMCLR_EV1_CLR                                            0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EMU
    Offset name:         RTC_O_EMU
    Relative address:    0x60
    Description:         Emulation control register. This register controls the behavior of the IP related to core halted input.
    Default Value:       0x00000000

        Field:           HALT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Halt control.

        ENUMs:
            STOP:                        Freeze option. The IP freezes functionality when the core halted input is asserted, and resumes when it is deasserted. The freeze can either be immediate or after the IP has reached a boundary from where it can resume without corruption.
            RUN:                         Free run option. The IP ignores the state of the core halted input.
*/
#define RTC_EMU_HALT                                                 0x00000001U
#define RTC_EMU_HALT_M                                               0x00000001U
#define RTC_EMU_HALT_S                                               0U
#define RTC_EMU_HALT_STOP                                            0x00000001U
#define RTC_EMU_HALT_RUN                                             0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DTB
    Offset name:         RTC_O_DTB
    Relative address:    0x64
    Description:         Digital test bus control register. This register can be used to bring out IP internal signals to the pads for observation. 16 signals can be observed per select value.
    Default Value:       0x00000000

        Field:           SEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Digital test bus selection mux control.

                         Non-zero select values output a 16 bit selected group of signals per value.

        ENUMs:
            DIS:                         All 16 observation signals are set to zero.
*/
#define RTC_DTB_SEL_W                                                4U
#define RTC_DTB_SEL_M                                                0x0000000FU
#define RTC_DTB_SEL_S                                                0U
#define RTC_DTB_SEL_DIS                                              0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DTIME
    Offset name:         RTC_O_DTIME
    Relative address:    0x68
    Description:         A delta time mechanism is implemented for RTC that allows the TIME value to be adjusted under software control. This is used by boot code to perform the compensation for reset duration (accomplished by adding MMR write to FCFG.generalTrims copylist to avoid ROM changes)
                            DTIME format is:
                                [31]: E       (exponent)
                                [30:0] M    (mantissa)
                            TIME[50:-2] is adjusted by TIME += sxt(M[30:0], 53) * 2^(22*E). In other words:
                                (E==0): TIME is adjusted by M * 250 ns (range +/-134 s)
                                (E==1): TIME is adjusted by M * 1.049 s (range +/- 35.7 yr)
    Default Value:       0x00000000

*/
#endif /* __HW_RTC_H__*/
