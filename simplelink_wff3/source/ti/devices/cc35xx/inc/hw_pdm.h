/******************************************************************************
*  Filename:       hw_pdm.h
*
*  Description:    Defines and prototypes for the PDM peripheral.
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
#ifndef __HW_PDM_H__
#define __HW_PDM_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the PDM component

--------------------------------------------------------------------------------- */

//Description Register
#define PDM_O_DESC                                                   0x00000000U

//This register reflects the configuration of this peripheral instance
#define PDM_O_DESCEX                                                 0x00000004U

//Interrupt Mask
#define PDM_O_IMASK                                                  0x00000044U

//Raw interrupt status
#define PDM_O_RIS                                                    0x00000048U

//Masked interrupt status
#define PDM_O_MIS                                                    0x0000004CU

//Interrupt set
#define PDM_O_ISET                                                   0x00000050U

//Interrupt clear
#define PDM_O_ICLR                                                   0x00000054U

//This register can be used by the software developer to control the behavior of the peripheral relative to the 'Core Halted' input
#define PDM_O_EMU                                                    0x00000060U

//PDM control register
#define PDM_O_CTL                                                    0x00000100U

//Input clock Control Register
#define PDM_O_ICLKCTL                                                0x00000104U

//PDM FIFO control register
#define PDM_O_FIFOCTL1                                               0x00000108U

//*FIFO* Data Register (FIFO read)
#define PDM_O_FIFODATA                                               0x0000010CU

//PDM Channel control register
#define PDM_O_CCTL                                                   0x00000110U

//Oversampling Control Register
#define PDM_O_OSR                                                    0x00000114U

//PDM control register
#define PDM_O_STA                                                    0x00000118U

//FIFO Control
#define PDM_O_FIFOCTL2                                               0x00000120U

//FIFO Status Register
#define PDM_O_FIFOSR                                                 0x00000124U

//Average sample value for channel-0, 32-bit register
#define PDM_O_AVGVAL0                                                0x00000200U

//Peak sample value for channel-0
#define PDM_O_PKVAL0                                                 0x00000204U

//Average sample power for channel-0
#define PDM_O_AVGPOW0                                                0x00000208U

//Average sample value for channel-1, 32-bit register
#define PDM_O_AVGVAL1                                                0x0000020CU

//Peak sample value for channel-1
#define PDM_O_PKVAL1                                                 0x00000210U

//Average sample power for channel-1
#define PDM_O_AVGPOW1                                                0x00000214U

//Samplestamp Generator Control Register
#define PDM_O_STPCTL                                                 0x00000300U

//Captured REFCLK Counter Value, Capture Channel 0
#define PDM_O_STPXCAPT                                               0x00000304U

//REFCLK Period Value
#define PDM_O_STPXPER                                                0x00000308U

//Captured Sample Clock Counter Value, Capture Channel 0
#define PDM_O_STPSCAPT                                               0x0000030CU

//Sample Clock Counter Period Value
#define PDM_O_STPSPER                                                0x00000310U

//WS Counter Trigger Value for Input Pins
#define PDM_O_STPINTRG                                               0x00000314U

//Sample Clock Counter Set Operation
#define PDM_O_STPSSET                                                0x00000318U

//Sample Clock Counter Add Operation
#define PDM_O_STPSADD                                                0x0000031CU

//REFCLK Minimum Period Value;Minimum Value of [STPXPER]
#define PDM_O_STPXMIN                                                0x00000320U

//Current Value of sample clock count
#define PDM_O_STPWCNT                                                0x00000324U

//Current Value of XCNT
#define PDM_O_STPXCNT                                                0x00000328U

//Samplestamp Generator Status Register
#define PDM_O_STPSTAT                                                0x0000032CU

//Clock configuration register
#define PDM_O_CLKCFG                                                 0x00001000U

//ADFS control register
#define PDM_O_ADFSCTL1                                               0x00001004U

//ADFS control register 2
#define PDM_O_ADFSCTL2                                               0x00001008U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         PDM_O_DESC
    Relative address:    0x0
    Description:         Description Register
                        This register identifies the peripheral and its exact version.
    Default Value:       0x00000000

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESC_MINREV_W                                            4U
#define PDM_DESC_MINREV_M                                            0x0000000FU
#define PDM_DESC_MINREV_S                                            0U
#define PDM_DESC_MINREV_MINIMUM                                      0x00000000U
#define PDM_DESC_MINREV_MAXIMUM                                      0x0000000FU
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major revision of the IP

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESC_MAJREV_W                                            4U
#define PDM_DESC_MAJREV_M                                            0x000000F0U
#define PDM_DESC_MAJREV_S                                            4U
#define PDM_DESC_MAJREV_MINIMUM                                      0x00000000U
#define PDM_DESC_MAJREV_MAXIMUM                                      0x000000F0U
/*

        Field:           INSTIDX
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Instance Number within the device. This will be a parameter to the RTL for modules that can have multiple instances

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESC_INSTIDX_W                                           4U
#define PDM_DESC_INSTIDX_M                                           0x00000F00U
#define PDM_DESC_INSTIDX_S                                           8U
#define PDM_DESC_INSTIDX_MINIMUM                                     0x00000000U
#define PDM_DESC_INSTIDX_MAXIMUM                                     0x00000F00U
/*

        Field:           STDIPOFF
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Standard IP offset
                         64 Bit standard IP MMR block (beginning with aggregated IRQ registers)

                         0: STDIP MMRs do not exist
                         1:15: These MMRs begin at offset 64*STDIPOFF from IP base address

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESC_STDIPOFF_W                                          4U
#define PDM_DESC_STDIPOFF_M                                          0x0000F000U
#define PDM_DESC_STDIPOFF_S                                          12U
#define PDM_DESC_STDIPOFF_MINIMUM                                    0x00000000U
#define PDM_DESC_STDIPOFF_MAXIMUM                                    0x0000F000U
/*

        Field:           MODID
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Module identification contains a unique peripheral identification number. The assignments are maintained in a central database for all of the platform modules to ensure uniqueness.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESC_MODID_W                                             16U
#define PDM_DESC_MODID_M                                             0xFFFF0000U
#define PDM_DESC_MODID_S                                             16U
#define PDM_DESC_MODID_MINIMUM                                       0x00000000U
#define PDM_DESC_MODID_MAXIMUM                                       0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DESCEX
    Offset name:         PDM_O_DESCEX
    Relative address:    0x4
    Description:         This register reflects the configuration of this peripheral instance
    Default Value:       0x00000004

        Field:           NUMCHAN
        From..to bits:   0...2
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Number of available PDM Channels.
                         Value 1 indicates two channels that can be used for stereo or dual mono microphone connections.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_DESCEX_NUMCHAN_W                                         3U
#define PDM_DESCEX_NUMCHAN_M                                         0x00000007U
#define PDM_DESCEX_NUMCHAN_S                                         0U
#define PDM_DESCEX_NUMCHAN_MINIMUM                                   0x00000000U
#define PDM_DESCEX_NUMCHAN_MAXIMUM                                   0x00000007U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMASK
    Offset name:         PDM_O_IMASK
    Relative address:    0x44
    Description:         Interrupt Mask. If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in MIS.
    Default Value:       0x00000000

        Field:           PDMDATA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     *PDM* data event mask

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrupt Enable
*/
#define PDM_IMASK_PDMDATA                                            0x00000001U
#define PDM_IMASK_PDMDATA_M                                          0x00000001U
#define PDM_IMASK_PDMDATA_S                                          0U
#define PDM_IMASK_PDMDATA_CLR                                        0x00000000U
#define PDM_IMASK_PDMDATA_SET                                        0x00000001U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Overflow event mask.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_IMASK_OVFL                                               0x00000040U
#define PDM_IMASK_OVFL_M                                             0x00000040U
#define PDM_IMASK_OVFL_S                                             6U
#define PDM_IMASK_OVFL_CLR                                           0x00000000U
#define PDM_IMASK_OVFL_SET                                           0x00000040U
/*

        Field:           UNFL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Underflow event mask.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_IMASK_UNFL                                               0x00000080U
#define PDM_IMASK_UNFL_M                                             0x00000080U
#define PDM_IMASK_UNFL_S                                             7U
#define PDM_IMASK_UNFL_CLR                                           0x00000000U
#define PDM_IMASK_UNFL_SET                                           0x00000080U
/*

        Field:           STPTRIG
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Samplestamp Trigger event mask

        ENUMs:
            SET:                         Interrrupt Enable
            CLR:                         Clear Interrupt Mask
*/
#define PDM_IMASK_STPTRIG                                            0x00000100U
#define PDM_IMASK_STPTRIG_M                                          0x00000100U
#define PDM_IMASK_STPTRIG_S                                          8U
#define PDM_IMASK_STPTRIG_SET                                        0x00000100U
#define PDM_IMASK_STPTRIG_CLR                                        0x00000000U
/*

        Field:           DMADONE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Done event mask.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_IMASK_DMADONE                                            0x00000200U
#define PDM_IMASK_DMADONE_M                                          0x00000200U
#define PDM_IMASK_DMADONE_S                                          9U
#define PDM_IMASK_DMADONE_CLR                                        0x00000000U
#define PDM_IMASK_DMADONE_SET                                        0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         PDM_O_RIS
    Relative address:    0x48
    Description:         Raw interrupt status. Reflects all pending interrupts, regardless of masking. The RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           PDMDATA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     PDM DATA event

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_RIS_PDMDATA                                              0x00000001U
#define PDM_RIS_PDMDATA_M                                            0x00000001U
#define PDM_RIS_PDMDATA_S                                            0U
#define PDM_RIS_PDMDATA_CLR                                          0x00000000U
#define PDM_RIS_PDMDATA_SET                                          0x00000001U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Data Overflow event.
                         Data has been written to the buffer before the previous values was read.
                         This flag gets set if one of the channel OVERFLOW flags gets set

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_RIS_OVFL                                                 0x00000040U
#define PDM_RIS_OVFL_M                                               0x00000040U
#define PDM_RIS_OVFL_S                                               6U
#define PDM_RIS_OVFL_CLR                                             0x00000000U
#define PDM_RIS_OVFL_SET                                             0x00000040U
/*

        Field:           UNFL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Data Underflow event.
                         Data has been read from an emty FIFO.
                         This flag gets set if one of the channel UNDERFLOW flags gets set.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_RIS_UNFL                                                 0x00000080U
#define PDM_RIS_UNFL_M                                               0x00000080U
#define PDM_RIS_UNFL_S                                               7U
#define PDM_RIS_UNFL_CLR                                             0x00000000U
#define PDM_RIS_UNFL_SET                                             0x00000080U
/*

        Field:           STPTRIG
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Samplestamp Trigger event

        ENUMs:
            SET:                         Interrrupt Enable
            CLR:                         Interrupt did not occur
*/
#define PDM_RIS_STPTRIG                                              0x00000100U
#define PDM_RIS_STPTRIG_M                                            0x00000100U
#define PDM_RIS_STPTRIG_S                                            8U
#define PDM_RIS_STPTRIG_SET                                          0x00000100U
#define PDM_RIS_STPTRIG_CLR                                          0x00000000U
/*

        Field:           DMADONE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA Done  event.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_RIS_DMADONE                                              0x00000200U
#define PDM_RIS_DMADONE_M                                            0x00000200U
#define PDM_RIS_DMADONE_S                                            9U
#define PDM_RIS_DMADONE_CLR                                          0x00000000U
#define PDM_RIS_DMADONE_SET                                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         PDM_O_MIS
    Relative address:    0x4C
    Description:         Masked interrupt status. This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           PDMDATA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked PDMDATA event

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_MIS_PDMDATA                                              0x00000001U
#define PDM_MIS_PDMDATA_M                                            0x00000001U
#define PDM_MIS_PDMDATA_S                                            0U
#define PDM_MIS_PDMDATA_CLR                                          0x00000000U
#define PDM_MIS_PDMDATA_SET                                          0x00000001U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Data Overflow event.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_MIS_OVFL                                                 0x00000040U
#define PDM_MIS_OVFL_M                                               0x00000040U
#define PDM_MIS_OVFL_S                                               6U
#define PDM_MIS_OVFL_CLR                                             0x00000000U
#define PDM_MIS_OVFL_SET                                             0x00000040U
/*

        Field:           UNFL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Data Underflow event.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_MIS_UNFL                                                 0x00000080U
#define PDM_MIS_UNFL_M                                               0x00000080U
#define PDM_MIS_UNFL_S                                               7U
#define PDM_MIS_UNFL_CLR                                             0x00000000U
#define PDM_MIS_UNFL_SET                                             0x00000080U
/*

        Field:           STPTRIG
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Samplestamp Trigger event.

        ENUMs:
            SET:                         Interrrupt Enable
            CLR:                         Interrupt did not occur
*/
#define PDM_MIS_STPTRIG                                              0x00000100U
#define PDM_MIS_STPTRIG_M                                            0x00000100U
#define PDM_MIS_STPTRIG_S                                            8U
#define PDM_MIS_STPTRIG_SET                                          0x00000100U
#define PDM_MIS_STPTRIG_CLR                                          0x00000000U
/*

        Field:           DMADONE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked DMA Done  event.

        ENUMs:
            CLR:                         Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_MIS_DMADONE                                              0x00000200U
#define PDM_MIS_DMADONE_M                                            0x00000200U
#define PDM_MIS_DMADONE_S                                            9U
#define PDM_MIS_DMADONE_CLR                                          0x00000000U
#define PDM_MIS_DMADONE_SET                                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISET
    Offset name:         PDM_O_ISET
    Relative address:    0x50
    Description:         Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           PDMDATA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set PDMDATA event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_ISET_PDMDATA                                             0x00000001U
#define PDM_ISET_PDMDATA_M                                           0x00000001U
#define PDM_ISET_PDMDATA_S                                           0U
#define PDM_ISET_PDMDATA_NO_EFFECT                                   0x00000000U
#define PDM_ISET_PDMDATA_SET                                         0x00000001U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Data Overflow event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_ISET_OVFL                                                0x00000040U
#define PDM_ISET_OVFL_M                                              0x00000040U
#define PDM_ISET_OVFL_S                                              6U
#define PDM_ISET_OVFL_NO_EFFECT                                      0x00000000U
#define PDM_ISET_OVFL_SET                                            0x00000040U
/*

        Field:           UNFL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Data Underflow event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_ISET_UNFL                                                0x00000080U
#define PDM_ISET_UNFL_M                                              0x00000080U
#define PDM_ISET_UNFL_S                                              7U
#define PDM_ISET_UNFL_NO_EFFECT                                      0x00000000U
#define PDM_ISET_UNFL_SET                                            0x00000080U
/*

        Field:           STPTRIG
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Samplestamp Trigger event.

        ENUMs:
            SET:                         Interrrupt Enable
            NO_EFFECT:                   Writing 0 has no effect
*/
#define PDM_ISET_STPTRIG                                             0x00000100U
#define PDM_ISET_STPTRIG_M                                           0x00000100U
#define PDM_ISET_STPTRIG_S                                           8U
#define PDM_ISET_STPTRIG_SET                                         0x00000100U
#define PDM_ISET_STPTRIG_NO_EFFECT                                   0x00000000U
/*

        Field:           DMADONE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set DMA Done  event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            SET:                         Interrrupt Enable
*/
#define PDM_ISET_DMADONE                                             0x00000200U
#define PDM_ISET_DMADONE_M                                           0x00000200U
#define PDM_ISET_DMADONE_S                                           9U
#define PDM_ISET_DMADONE_NO_EFFECT                                   0x00000000U
#define PDM_ISET_DMADONE_SET                                         0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         PDM_O_ICLR
    Relative address:    0x54
    Description:         Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           PDMDATA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear PDMDATA event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            CLR:                         Interrrupt Enable
*/
#define PDM_ICLR_PDMDATA                                             0x00000001U
#define PDM_ICLR_PDMDATA_M                                           0x00000001U
#define PDM_ICLR_PDMDATA_S                                           0U
#define PDM_ICLR_PDMDATA_NO_EFFECT                                   0x00000000U
#define PDM_ICLR_PDMDATA_CLR                                         0x00000001U
/*

        Field:           OVFL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Data Overflow event.


        ENUMs:
            NO_EFFECT:                   Interrupt disable
            CLR:                         Interrrupt Enable
*/
#define PDM_ICLR_OVFL                                                0x00000040U
#define PDM_ICLR_OVFL_M                                              0x00000040U
#define PDM_ICLR_OVFL_S                                              6U
#define PDM_ICLR_OVFL_NO_EFFECT                                      0x00000000U
#define PDM_ICLR_OVFL_CLR                                            0x00000040U
/*

        Field:           UNFL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Data Underflow event.


        ENUMs:
            NO_EFFECT:                   Interrupt disable
            CLR:                         Interrrupt Enable
*/
#define PDM_ICLR_UNFL                                                0x00000080U
#define PDM_ICLR_UNFL_M                                              0x00000080U
#define PDM_ICLR_UNFL_S                                              7U
#define PDM_ICLR_UNFL_NO_EFFECT                                      0x00000000U
#define PDM_ICLR_UNFL_CLR                                            0x00000080U
/*

        Field:           STPTRIG
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Samplestamp Trigger event.

        ENUMs:
            CLR:                         Interrrupt Enable
            NO_EFFECT:                   Writing 0 has no effect
*/
#define PDM_ICLR_STPTRIG                                             0x00000100U
#define PDM_ICLR_STPTRIG_M                                           0x00000100U
#define PDM_ICLR_STPTRIG_S                                           8U
#define PDM_ICLR_STPTRIG_CLR                                         0x00000100U
#define PDM_ICLR_STPTRIG_NO_EFFECT                                   0x00000000U
/*

        Field:           DMADONE
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear DMA Done event.

        ENUMs:
            NO_EFFECT:                   Interrupt disable
            CLR:                         Interrrupt Enable
*/
#define PDM_ICLR_DMADONE                                             0x00000200U
#define PDM_ICLR_DMADONE_M                                           0x00000200U
#define PDM_ICLR_DMADONE_S                                           9U
#define PDM_ICLR_DMADONE_NO_EFFECT                                   0x00000000U
#define PDM_ICLR_DMADONE_CLR                                         0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EMU
    Offset name:         PDM_O_EMU
    Relative address:    0x60
    Description:         This register can be used by the software developer to control the behavior of the peripheral relative to the 'Core Halted' input
    Default Value:       0x00000000

        Field:           HALT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Free run control

        ENUMs:
            STOP:                        The peripheral freezes functionality while the Core Halted input is asserted and resumes when it is deasserted.
            RUN:                         The peripheral ignores the state of the Core Halted input
*/
#define PDM_EMU_HALT                                                 0x00000001U
#define PDM_EMU_HALT_M                                               0x00000001U
#define PDM_EMU_HALT_S                                               0U
#define PDM_EMU_HALT_STOP                                            0x00000001U
#define PDM_EMU_HALT_RUN                                             0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL
    Offset name:         PDM_O_CTL
    Relative address:    0x100
    Description:         PDM control register
    Default Value:       0x00000000

        Field:           ENPDM
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable conversion on *PDM*

        ENUMs:
            DIS:                         Disable Channel
            EN:                          Enable Channel
*/
#define PDM_CTL_ENPDM                                                0x00000001U
#define PDM_CTL_ENPDM_M                                              0x00000001U
#define PDM_CTL_ENPDM_S                                              0U
#define PDM_CTL_ENPDM_DIS                                            0x00000000U
#define PDM_CTL_ENPDM_EN                                             0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLKCTL
    Offset name:         PDM_O_ICLKCTL
    Relative address:    0x104
    Description:         Input clock Control Register
    Default Value:       0x00000000

        Field:           IDIV
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Divider for ICLK
                         iclk = PLLCLK/(ICLK +1)

        ENUMs:
            MIN:                         Minimum value of BDIV
            MAX:                         Maximum value of BDIV
*/
#define PDM_ICLKCTL_IDIV_W                                           10U
#define PDM_ICLKCTL_IDIV_M                                           0x000003FFU
#define PDM_ICLKCTL_IDIV_S                                           0U
#define PDM_ICLKCTL_IDIV_MIN                                         0x00000000U
#define PDM_ICLKCTL_IDIV_MAX                                         0x000003FFU
/*

        Field:           BCLKEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit is used to enable BCLK to Sigma-Delta Modulator on-chip.

        ENUMs:
            DIS:                         BCLK is disabled
            EN:                          BCLK is enabled
*/
#define PDM_ICLKCTL_BCLKEN                                           0x00010000U
#define PDM_ICLKCTL_BCLKEN_M                                         0x00010000U
#define PDM_ICLKCTL_BCLKEN_S                                         16U
#define PDM_ICLKCTL_BCLKEN_DIS                                       0x00000000U
#define PDM_ICLKCTL_BCLKEN_EN                                        0x00010000U
/*

        Field:           RESERED17
        From..to bits:   17...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Software should not rely on the value of a reserved. Writing any other value than the reset value may result in undefined behavior.

*/
#define PDM_ICLKCTL_RESERED17_W                                      15U
#define PDM_ICLKCTL_RESERED17_M                                      0xFFFE0000U
#define PDM_ICLKCTL_RESERED17_S                                      17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOCTL1
    Offset name:         PDM_O_FIFOCTL1
    Relative address:    0x108
    Description:         PDM FIFO control register
    Default Value:       0x00000000

        Field:           ENFIFO0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable FIFO0 for DMA access through the [FIFODATA] Register

        ENUMs:
            DIS:                         Disable Channel
            EN:                          Enable Channel
*/
#define PDM_FIFOCTL1_ENFIFO0                                         0x00000001U
#define PDM_FIFOCTL1_ENFIFO0_M                                       0x00000001U
#define PDM_FIFOCTL1_ENFIFO0_S                                       0U
#define PDM_FIFOCTL1_ENFIFO0_DIS                                     0x00000000U
#define PDM_FIFOCTL1_ENFIFO0_EN                                      0x00000001U
/*

        Field:           ENFIFO1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable FIFO1 for DMA access through the [FIFODATA] Register

        ENUMs:
            DIS:                         Disable Channel
            EN:                          Enable Channel
*/
#define PDM_FIFOCTL1_ENFIFO1                                         0x00000002U
#define PDM_FIFOCTL1_ENFIFO1_M                                       0x00000002U
#define PDM_FIFOCTL1_ENFIFO1_S                                       1U
#define PDM_FIFOCTL1_ENFIFO1_DIS                                     0x00000000U
#define PDM_FIFOCTL1_ENFIFO1_EN                                      0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFODATA
    Offset name:         PDM_O_FIFODATA
    Relative address:    0x10C
    Description:         *FIFO* Data Register (FIFO read)
                        This register provides the Data of the FIFO based on [FIFOCTL.ENFIFO0] and [FIFOCTL.ENFIFO1]
                        This allows the DMA to just have single address to read all the FIFO content when triggered.
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FIFO Read Register

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_FIFODATA_VALUE_W                                         32U
#define PDM_FIFODATA_VALUE_M                                         0xFFFFFFFFU
#define PDM_FIFODATA_VALUE_S                                         0U
#define PDM_FIFODATA_VALUE_MINIMUM                                   0x00000000U
#define PDM_FIFODATA_VALUE_MAXIMUM                                   0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCTL
    Offset name:         PDM_O_CCTL
    Relative address:    0x110
    Description:         PDM Channel control register
    Default Value:       0x00700000

        Field:           CHEN
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Input Configuration

        ENUMs:
            CH0ENABLE:                   Input channel 0 is enabled.
            CH0_1ENABLE:                 Input channel 1 is enabled.
            MANC:                        Input from Manchester Decoder, also enables Manchester Coding of bitstream.
                         CH0 is enabled by default as the operation and CH1 enable bit is discarded.
            DISABLE:                     Both Channels are disabled.
*/
#define PDM_CCTL_CHEN_W                                              3U
#define PDM_CCTL_CHEN_M                                              0x00000007U
#define PDM_CCTL_CHEN_S                                              0U
#define PDM_CCTL_CHEN_CH0ENABLE                                      0x00000001U
#define PDM_CCTL_CHEN_CH0_1ENABLE                                    0x00000002U
#define PDM_CCTL_CHEN_MANC                                           0x00000004U
#define PDM_CCTL_CHEN_DISABLE                                        0x00000000U
/*

        Field:           DFS
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Digital Filter Select

        ENUMs:
            SINC1:                       SINC1 filter
            SINC2:                       SINC2 filter
            SINC3:                       SINC3 filter
            SINC4:                       SINC4 filter
*/
#define PDM_CCTL_DFS_W                                               2U
#define PDM_CCTL_DFS_M                                               0x00000300U
#define PDM_CCTL_DFS_S                                               8U
#define PDM_CCTL_DFS_SINC1                                           0x00000000U
#define PDM_CCTL_DFS_SINC2                                           0x00000100U
#define PDM_CCTL_DFS_SINC3                                           0x00000200U
#define PDM_CCTL_DFS_SINC4                                           0x00000300U
/*

        Field:           ALIGN
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data alignment

        ENUMs:
            RIGHT:                       Right-aligned. LSB of filter output is bit 0.
            LEFT:                        Left-aligned. MSB of filter output (depending on OSR) is bit 31.
*/
#define PDM_CCTL_ALIGN                                               0x00000400U
#define PDM_CCTL_ALIGN_M                                             0x00000400U
#define PDM_CCTL_ALIGN_S                                             10U
#define PDM_CCTL_ALIGN_RIGHT                                         0x00000000U
#define PDM_CCTL_ALIGN_LEFT                                          0x00000400U
/*

        Field:           DATAFMT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Format

        ENUMs:
            OFFSET:                      Offset binary
            TWOSCOMP:                    Twos complement
*/
#define PDM_CCTL_DATAFMT                                             0x00000800U
#define PDM_CCTL_DATAFMT_M                                           0x00000800U
#define PDM_CCTL_DATAFMT_S                                           11U
#define PDM_CCTL_DATAFMT_OFFSET                                      0x00000000U
#define PDM_CCTL_DATAFMT_TWOSCOMP                                    0x00000800U
/*

        Field:           ENPKCH0
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables peak value detection for channel-0

        ENUMs:
            EN:                          Enables peak value detection for channel-0
            DIS:                         Disables peak value detection for channel-0
*/
#define PDM_CCTL_ENPKCH0                                             0x00010000U
#define PDM_CCTL_ENPKCH0_M                                           0x00010000U
#define PDM_CCTL_ENPKCH0_S                                           16U
#define PDM_CCTL_ENPKCH0_EN                                          0x00010000U
#define PDM_CCTL_ENPKCH0_DIS                                         0x00000000U
/*

        Field:           ENPKCH1
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables peak value detection for channel-0

        ENUMs:
            EN:                          Enables peak value detection for channel-1
            DIS:                         Enables peak value detection for channel-1
*/
#define PDM_CCTL_ENPKCH1                                             0x00020000U
#define PDM_CCTL_ENPKCH1_M                                           0x00020000U
#define PDM_CCTL_ENPKCH1_S                                           17U
#define PDM_CCTL_ENPKCH1_EN                                          0x00020000U
#define PDM_CCTL_ENPKCH1_DIS                                         0x00000000U
/*

        Field:           ENPOWCH0
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables average power calculation for channel-0

        ENUMs:
            EN:                          Enables average power calculation for channel-0
            DIS:                         Disables average power calculation for channel-0
*/
#define PDM_CCTL_ENPOWCH0                                            0x00040000U
#define PDM_CCTL_ENPOWCH0_M                                          0x00040000U
#define PDM_CCTL_ENPOWCH0_S                                          18U
#define PDM_CCTL_ENPOWCH0_EN                                         0x00040000U
#define PDM_CCTL_ENPOWCH0_DIS                                        0x00000000U
/*

        Field:           ENPOWCH1
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables average power calculation for channel-1

        ENUMs:
            EN:                          Enables average power calculation for channel-1
            DIS:                         Enables average power calculation for channel-1
*/
#define PDM_CCTL_ENPOWCH1                                            0x00080000U
#define PDM_CCTL_ENPOWCH1_M                                          0x00080000U
#define PDM_CCTL_ENPOWCH1_S                                          19U
#define PDM_CCTL_ENPOWCH1_EN                                         0x00080000U
#define PDM_CCTL_ENPOWCH1_DIS                                        0x00000000U
/*

        Field:           SELSCALE
        From..to bits:   20...22
        DefaultValue:    0x7
        Access type:     read-write
        Description:     Select scaling factor for the averaging blocks. Selscale value used internally is 1/(2^(3+VALUE))
                         Ex: When value is 0, selscale is 1/8, and when value is 7, selscale is 1/1024

        ENUMs:
            VAL0:                        Scaling factor is 1/8
            VAL1:                        Scaling factor is 1/16
            VAL2:                        Scaling factor is 1/32
            VAL3:                        Scaling factor is 1/64
            VAL4:                        Scaling factor is 1/128
            VAL5:                        Scaling factor is 1/256
            VAL6:                        Scaling factor is 1/512
            VAL7:                        Scaling factor is 1/1024
*/
#define PDM_CCTL_SELSCALE_W                                          3U
#define PDM_CCTL_SELSCALE_M                                          0x00700000U
#define PDM_CCTL_SELSCALE_S                                          20U
#define PDM_CCTL_SELSCALE_VAL0                                       0x00000000U
#define PDM_CCTL_SELSCALE_VAL1                                       0x00100000U
#define PDM_CCTL_SELSCALE_VAL2                                       0x00200000U
#define PDM_CCTL_SELSCALE_VAL3                                       0x00300000U
#define PDM_CCTL_SELSCALE_VAL4                                       0x00400000U
#define PDM_CCTL_SELSCALE_VAL5                                       0x00500000U
#define PDM_CCTL_SELSCALE_VAL6                                       0x00600000U
#define PDM_CCTL_SELSCALE_VAL7                                       0x00700000U
/*

        Field:           CH0CLKEG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select the clock edge for data channel 0

        ENUMs:
            RISING:                      Rising edge is selected
            FALLING:                     Failing edge is selected
*/
#define PDM_CCTL_CH0CLKEG                                            0x01000000U
#define PDM_CCTL_CH0CLKEG_M                                          0x01000000U
#define PDM_CCTL_CH0CLKEG_S                                          24U
#define PDM_CCTL_CH0CLKEG_RISING                                     0x00000000U
#define PDM_CCTL_CH0CLKEG_FALLING                                    0x01000000U
/*

        Field:           CH0IPSEL
        From..to bits:   25...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 0 Data Input Select

        ENUMs:
            DATA0:                       Data pin 0 selected as source for channel 0.
            DATA1:                       Data pin 1 selected as source for channel 0.
            SDM:                         SDM output selected as source for channel 0.
            RESERVED:                    Data pin 0 selected as source for channel 0.
*/
#define PDM_CCTL_CH0IPSEL_W                                          2U
#define PDM_CCTL_CH0IPSEL_M                                          0x06000000U
#define PDM_CCTL_CH0IPSEL_S                                          25U
#define PDM_CCTL_CH0IPSEL_DATA0                                      0x00000000U
#define PDM_CCTL_CH0IPSEL_DATA1                                      0x02000000U
#define PDM_CCTL_CH0IPSEL_SDM                                        0x04000000U
#define PDM_CCTL_CH0IPSEL_RESERVED                                   0x06000000U
/*

        Field:           CH1CLKEG
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select the clock edge for data channel 1

        ENUMs:
            RISING:                      Rising edge is selected
            FALLING:                     Failing edge is selected
*/
#define PDM_CCTL_CH1CLKEG                                            0x10000000U
#define PDM_CCTL_CH1CLKEG_M                                          0x10000000U
#define PDM_CCTL_CH1CLKEG_S                                          28U
#define PDM_CCTL_CH1CLKEG_RISING                                     0x00000000U
#define PDM_CCTL_CH1CLKEG_FALLING                                    0x10000000U
/*

        Field:           CH1IPSEL
        From..to bits:   29...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 1 Data Input Select

        ENUMs:
            DATA0:                       Data pin 0 selected as source for channel 1.
            DATA1:                       Data pin 1 selected as source for channel 1.
            SDM:                         SDM output selected as source for channel 1.
            RESERVED:                    Data pin 0 selected as source for channel 1.
*/
#define PDM_CCTL_CH1IPSEL_W                                          2U
#define PDM_CCTL_CH1IPSEL_M                                          0x60000000U
#define PDM_CCTL_CH1IPSEL_S                                          29U
#define PDM_CCTL_CH1IPSEL_DATA0                                      0x00000000U
#define PDM_CCTL_CH1IPSEL_DATA1                                      0x20000000U
#define PDM_CCTL_CH1IPSEL_SDM                                        0x40000000U
#define PDM_CCTL_CH1IPSEL_RESERVED                                   0x60000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OSR
    Offset name:         PDM_O_OSR
    Relative address:    0x114
    Description:         Oversampling Control Register
    Default Value:       0x0000003F

        Field:           VALUE
        From..to bits:   0...7
        DefaultValue:    0x3F
        Access type:     read-write
        Description:     Oversampling rate. The oversampling rate is defined as OSRx + 1.
                         Applicable oversampling rates are 2 to 256. Default is 64.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_OSR_VALUE_W                                              8U
#define PDM_OSR_VALUE_M                                              0x000000FFU
#define PDM_OSR_VALUE_S                                              0U
#define PDM_OSR_VALUE_MINIMUM                                        0x00000001U
#define PDM_OSR_VALUE_MAXIMUM                                        0x000000FFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STA
    Offset name:         PDM_O_STA
    Relative address:    0x118
    Description:         PDM control register
    Default Value:       0x00000000

        Field:           AGCRDY
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     *AGC* accelerator ready status. Software must read AGCVALx, PKVALx and AVGPOWx registers only when AGCRDY is '1'. Reading these registers while AGCRDY is 0 may provide incorrect values.

        ENUMs:
            NOT_RDY:                     Not ready
            RDY:                         Ready
*/
#define PDM_STA_AGCRDY                                               0x00000001U
#define PDM_STA_AGCRDY_M                                             0x00000001U
#define PDM_STA_AGCRDY_S                                             0U
#define PDM_STA_AGCRDY_NOT_RDY                                       0x00000000U
#define PDM_STA_AGCRDY_RDY                                           0x00000001U
/*

        Field:           MANCLK
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Manchester Clock status.
                         Indicates that Manchester mode is in locked mode or not.

        ENUMs:
            UNLOCKED:                    Manchester clock not locked.
            LOCKED:                      Manchester clock locked.
*/
#define PDM_STA_MANCLK                                               0x00020000U
#define PDM_STA_MANCLK_M                                             0x00020000U
#define PDM_STA_MANCLK_S                                             17U
#define PDM_STA_MANCLK_UNLOCKED                                      0x00000000U
#define PDM_STA_MANCLK_LOCKED                                        0x00020000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOCTL2
    Offset name:         PDM_O_FIFOCTL2
    Relative address:    0x120
    Description:         FIFO Control
    Default Value:       0x00000000

        Field:           TRGLVL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FIFO Trigger Level Select  Sets the trigger points for the FIFO events.
                         Note: FIFO depth is only 2 the level 1/4 and 3/4 default to 1/2.

        ENUMs:
            LEVEL_1:                     Trigger when RX FIFO contains >= 1 byte
            LEVEL_2:                     Trigger when RX FIFO contains >= 2 byte
            LEVEL_3:                     Trigger when RX FIFO contains >= 3 byte
            LEVEL_4:                     Trigger when RX FIFO contains >= 4 byte
            LEVEL_5:                     Trigger when RX FIFO contains >= 5 byte
            LEVEL_6:                     Trigger when RX FIFO contains >= 6 byte
            LEVEL_7:                     Trigger when RX FIFO contains >= 7 byte
            LEVEL_8:                     Trigger when RX FIFO contains >= 8 byte
            LEVEL_9:                     Trigger when RX FIFO contains >= 9 byte
            LEVEL_10:                    Trigger when RX FIFO contains >= 10 byte
            LEVEL_11:                    Trigger when RX FIFO contains >= 11 byte
            LEVEL_12:                    Trigger when RX FIFO contains >= 12 byte
*/
#define PDM_FIFOCTL2_TRGLVL_W                                        4U
#define PDM_FIFOCTL2_TRGLVL_M                                        0x0000000FU
#define PDM_FIFOCTL2_TRGLVL_S                                        0U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_1                                  0x00000000U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_2                                  0x00000001U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_3                                  0x00000002U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_4                                  0x00000003U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_5                                  0x00000004U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_6                                  0x00000005U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_7                                  0x00000006U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_8                                  0x00000007U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_9                                  0x00000008U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_10                                 0x00000009U
#define PDM_FIFOCTL2_TRGLVL_LEVEL_11                                 0x0000000AU
#define PDM_FIFOCTL2_TRGLVL_LEVEL_12                                 0x0000000BU
/*

        Field:           FIFOFLSH
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FIFO Flush
                         Setting this bit will Flush the FIFO. This bit will self-clear when the
                         flush has completed.

        ENUMs:
            NOFLUSH:                     Do not Flush FIFO
            FLUSH:                       Flush FIFO
*/
#define PDM_FIFOCTL2_FIFOFLSH                                        0x00000080U
#define PDM_FIFOCTL2_FIFOFLSH_M                                      0x00000080U
#define PDM_FIFOCTL2_FIFOFLSH_S                                      7U
#define PDM_FIFOCTL2_FIFOFLSH_NOFLUSH                                0x00000000U
#define PDM_FIFOCTL2_FIFOFLSH_FLUSH                                  0x00000080U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOSR
    Offset name:         PDM_O_FIFOSR
    Relative address:    0x124
    Description:         FIFO Status Register.
    Default Value:       0x00000000

        Field:           CH0FCNT
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of Bytes which could be read from the CH0 FIFO

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_FIFOSR_CH0FCNT_W                                         4U
#define PDM_FIFOSR_CH0FCNT_M                                         0x0000000FU
#define PDM_FIFOSR_CH0FCNT_S                                         0U
#define PDM_FIFOSR_CH0FCNT_MINIMUM                                   0x00000000U
#define PDM_FIFOSR_CH0FCNT_MAXIMUM                                   0x0000000FU
/*

        Field:           CH0FEMP
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CH0 FIFO Empty

        ENUMs:
            CLEARED:                     The receiver is not empty.
            SET:                         If the FIFO is disabled (FEN is 0), the receive holding register is empty. If the FIFO is enabled (FEN is 1), the receive FIFO is empty.
*/
#define PDM_FIFOSR_CH0FEMP                                           0x00000040U
#define PDM_FIFOSR_CH0FEMP_M                                         0x00000040U
#define PDM_FIFOSR_CH0FEMP_S                                         6U
#define PDM_FIFOSR_CH0FEMP_CLEARED                                   0x00000000U
#define PDM_FIFOSR_CH0FEMP_SET                                       0x00000040U
/*

        Field:           CH0FFULL
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CH0 FIFO Full

        ENUMs:
            CLEARED:                     The receiver can receive data.
            SET:                         If the FIFO is disabled (FEN is 0), the receive holding register is full. If the FIFO is enabled (FEN is 1), the receive FIFO is full.
*/
#define PDM_FIFOSR_CH0FFULL                                          0x00000080U
#define PDM_FIFOSR_CH0FFULL_M                                        0x00000080U
#define PDM_FIFOSR_CH0FFULL_S                                        7U
#define PDM_FIFOSR_CH0FFULL_CLEARED                                  0x00000000U
#define PDM_FIFOSR_CH0FFULL_SET                                      0x00000080U
/*

        Field:           CH1FCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of Bytes which could be read from the CH1 FIFO

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_FIFOSR_CH1FCNT_W                                         4U
#define PDM_FIFOSR_CH1FCNT_M                                         0x00000F00U
#define PDM_FIFOSR_CH1FCNT_S                                         8U
#define PDM_FIFOSR_CH1FCNT_MINIMUM                                   0x00000000U
#define PDM_FIFOSR_CH1FCNT_MAXIMUM                                   0x00000F00U
/*

        Field:           CH1FEMP
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CH1 FIFO Empty

        ENUMs:
            CLEARED:                     The transmitter has data to transmit.
            SET:                         If the FIFO is disabled (FEN is 0), the transmit holding register is empty. If the FIFO is enabled (FEN is 1), the transmit FIFO is empty.
*/
#define PDM_FIFOSR_CH1FEMP                                           0x00004000U
#define PDM_FIFOSR_CH1FEMP_M                                         0x00004000U
#define PDM_FIFOSR_CH1FEMP_S                                         14U
#define PDM_FIFOSR_CH1FEMP_CLEARED                                   0x00000000U
#define PDM_FIFOSR_CH1FEMP_SET                                       0x00004000U
/*

        Field:           CH1FFULL
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CH1 FIFO Full

        ENUMs:
            CLEARED:                     The transmitter is not full.
            SET:                         If the FIFO is disabled (FEN is 0), the transmit holding register is full. If the FIFO is enabled (FEN is 1), the transmit FIFO is full.
*/
#define PDM_FIFOSR_CH1FFULL                                          0x00008000U
#define PDM_FIFOSR_CH1FFULL_M                                        0x00008000U
#define PDM_FIFOSR_CH1FFULL_S                                        15U
#define PDM_FIFOSR_CH1FFULL_CLEARED                                  0x00000000U
#define PDM_FIFOSR_CH1FFULL_SET                                      0x00008000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AVGVAL0
    Offset name:         PDM_O_AVGVAL0
    Relative address:    0x200
    Description:         Average sample value for channel-0, 32-bit register.
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Average sample value for channel-0

        ENUMs:
            MINIMUM:                     Minimum value of register
            MAXIMUM:                     Highest value
*/
#define PDM_AVGVAL0_VALUE_W                                          32U
#define PDM_AVGVAL0_VALUE_M                                          0xFFFFFFFFU
#define PDM_AVGVAL0_VALUE_S                                          0U
#define PDM_AVGVAL0_VALUE_MINIMUM                                    0x00000000U
#define PDM_AVGVAL0_VALUE_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       PKVAL0
    Offset name:         PDM_O_PKVAL0
    Relative address:    0x204
    Description:         Peak sample value for channel-0
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Peak sample value for channel-0. Bits [22:0] applicable for operation in 2's complement format and bits [23:0] applicable for operation in offset binary format.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Largest value
*/
#define PDM_PKVAL0_VALUE_W                                           24U
#define PDM_PKVAL0_VALUE_M                                           0x00FFFFFFU
#define PDM_PKVAL0_VALUE_S                                           0U
#define PDM_PKVAL0_VALUE_MINIMUM                                     0x00000000U
#define PDM_PKVAL0_VALUE_MAXIMUM                                     0x007FFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       AVGPOW0
    Offset name:         PDM_O_AVGPOW0
    Relative address:    0x208
    Description:         Average sample power for channel-0
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Average sample power for channel-0

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest value
*/
#define PDM_AVGPOW0_VALUE_W                                          32U
#define PDM_AVGPOW0_VALUE_M                                          0xFFFFFFFFU
#define PDM_AVGPOW0_VALUE_S                                          0U
#define PDM_AVGPOW0_VALUE_MINIMUM                                    0x00000000U
#define PDM_AVGPOW0_VALUE_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       AVGVAL1
    Offset name:         PDM_O_AVGVAL1
    Relative address:    0x20C
    Description:         Average sample value for channel-1, 32-bit register.
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Average sample value for channel-1

        ENUMs:
            MINIMUM:                     Minimum value of register
            MAXIMUM:                     Highest value
*/
#define PDM_AVGVAL1_VALUE_W                                          32U
#define PDM_AVGVAL1_VALUE_M                                          0xFFFFFFFFU
#define PDM_AVGVAL1_VALUE_S                                          0U
#define PDM_AVGVAL1_VALUE_MINIMUM                                    0x00000000U
#define PDM_AVGVAL1_VALUE_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       PKVAL1
    Offset name:         PDM_O_PKVAL1
    Relative address:    0x210
    Description:         Peak sample value for channel-1
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Peak sample value for channel-1. Bits [22:0] applicable for operation in 2's complement format and bits [23:0] applicable for operation in offset binary format.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Largest value
*/
#define PDM_PKVAL1_VALUE_W                                           24U
#define PDM_PKVAL1_VALUE_M                                           0x00FFFFFFU
#define PDM_PKVAL1_VALUE_S                                           0U
#define PDM_PKVAL1_VALUE_MINIMUM                                     0x00000000U
#define PDM_PKVAL1_VALUE_MAXIMUM                                     0x007FFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       AVGPOW1
    Offset name:         PDM_O_AVGPOW1
    Relative address:    0x214
    Description:         Average sample power for channel-1
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Average sample power for channel-1

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest value
*/
#define PDM_AVGPOW1_VALUE_W                                          32U
#define PDM_AVGPOW1_VALUE_M                                          0xFFFFFFFFU
#define PDM_AVGPOW1_VALUE_S                                          0U
#define PDM_AVGPOW1_VALUE_MINIMUM                                    0x00000000U
#define PDM_AVGPOW1_VALUE_MAXIMUM                                    0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPCTL
    Offset name:         PDM_O_STPCTL
    Relative address:    0x300
    Description:         Samplestamp Generator Control Register
    Default Value:       0x00000000

        Field:           STPEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables the samplestamp generator. The samplestamp generator must only be enabled after it has been properly configured.;When cleared, all samplestamp generator counters and capture values are cleared.

        ENUMs:
            DIS:                         Disable the samplestamp generator
            EN:                          Enable the samplestamp generator
*/
#define PDM_STPCTL_STPEN                                             0x00000001U
#define PDM_STPCTL_STPEN_M                                           0x00000001U
#define PDM_STPCTL_STPEN_S                                           0U
#define PDM_STPCTL_STPEN_DIS                                         0x00000000U
#define PDM_STPCTL_STPEN_EN                                          0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPXCAPT
    Offset name:         PDM_O_STPXCAPT
    Relative address:    0x304
    Description:         Captured REFCLK Counter Value, Capture Channel 0
    Default Value:       0x00000000

        Field:           CAPTVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The value of the samplestamp XOSC counter [STMPXCNT.CURR_VALUE] last time an event was pulsed. The value is cleared when [STMPCTL.STMP_EN] = 0.
                         Note: When calculating the fractional part of the sample stamp, [STMPXPER] may be less than this bit field.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPXCAPT_CAPTVAL_W                                       16U
#define PDM_STPXCAPT_CAPTVAL_M                                       0x0000FFFFU
#define PDM_STPXCAPT_CAPTVAL_S                                       0U
#define PDM_STPXCAPT_CAPTVAL_MINIMUM                                 0x00000000U
#define PDM_STPXCAPT_CAPTVAL_MAXIMUM                                 0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPXPER
    Offset name:         PDM_O_STPXPER
    Relative address:    0x308
    Description:         REFCLK Period Value
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The number of REFCLK clock cycles in the previous Sample Clock period (that is -  the next value of the REFCLK counter at the positive Sample Clock edge, had it not been reset to 0).;The value is cleared when [STMPCTL.STMP_EN] = 0.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPXPER_VALUE_W                                          16U
#define PDM_STPXPER_VALUE_M                                          0x0000FFFFU
#define PDM_STPXPER_VALUE_S                                          0U
#define PDM_STPXPER_VALUE_MINIMUM                                    0x00000000U
#define PDM_STPXPER_VALUE_MAXIMUM                                    0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPSCAPT
    Offset name:         PDM_O_STPSCAPT
    Relative address:    0x30C
    Description:         Captured Sample Clock Counter Value, Capture Channel 0
    Default Value:       0x00000000

        Field:           CAPTVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The value of the samplestamp Sample Clock counter [STMPWCNT.CURR_VALUE] last time an event was pulsed. This number corresponds to the number of positive Sample Clock edges since the samplestamp generator was enabled;The value is cleared when [STMPCTL.STPEN] = 0.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPSCAPT_CAPTVAL_W                                       16U
#define PDM_STPSCAPT_CAPTVAL_M                                       0x0000FFFFU
#define PDM_STPSCAPT_CAPTVAL_S                                       0U
#define PDM_STPSCAPT_CAPTVAL_MINIMUM                                 0x00000000U
#define PDM_STPSCAPT_CAPTVAL_MAXIMUM                                 0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPSPER
    Offset name:         PDM_O_STPSPER
    Relative address:    0x310
    Description:         Sample Clock Counter Period Value
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define when [STMPWCNT] is to be reset so number of Sample Clock edges are found for the size of the sample buffer. This is thus a modulo value for the Sample Clock counter. This number must correspond to the size of the sample buffer used by the system (that is the index of the last sample plus 1).

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPSPER_VALUE_W                                          16U
#define PDM_STPSPER_VALUE_M                                          0x0000FFFFU
#define PDM_STPSPER_VALUE_S                                          0U
#define PDM_STPSPER_VALUE_MINIMUM                                    0x00000000U
#define PDM_STPSPER_VALUE_MAXIMUM                                    0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPINTRG
    Offset name:         PDM_O_STPINTRG
    Relative address:    0x314
    Description:         WS Counter Trigger Value for Input Pins
    Default Value:       0x00000000

        Field:           INSTRWCT
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In Start W Count
                         Compare value used to start the incoming audio streams.;This bit field must equal the Sample Clock counter value during the Sample Clock period in which the first input word(s) are sampled and stored to memory (that is the sample at the start of the very first DMA input buffer).;The value of this register takes effect when at least 32 PDMxCLK cycle ticks have happened.;Note: To avoid false triggers, this bit field must be set higher than [STPWPER.VALUE].

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPINTRG_INSTRWCT_W                                      16U
#define PDM_STPINTRG_INSTRWCT_M                                      0x0000FFFFU
#define PDM_STPINTRG_INSTRWCT_S                                      0U
#define PDM_STPINTRG_INSTRWCT_MINIMUM                                0x00000000U
#define PDM_STPINTRG_INSTRWCT_MAXIMUM                                0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPSSET
    Offset name:         PDM_O_STPSSET
    Relative address:    0x318
    Description:         Sample Clock Counter Set Operation
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sample Clock counter modification: Sets the running Sample Clock counter equal to the written value.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPSSET_VALUE_W                                          16U
#define PDM_STPSSET_VALUE_M                                          0x0000FFFFU
#define PDM_STPSSET_VALUE_S                                          0U
#define PDM_STPSSET_VALUE_MINIMUM                                    0x00000000U
#define PDM_STPSSET_VALUE_MAXIMUM                                    0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPSADD
    Offset name:         PDM_O_STPSADD
    Relative address:    0x31C
    Description:         Sample Clock Counter Add Operation
    Default Value:       0x00000000

        Field:           VALINC
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sample Clock counter modification: Adds the written value to the running Sample Clock counter. If a positive edge of Sample Clock occurs at the same time as the operation, this will be taken into account.;To add a negative value, write "[STMPWPER.VALUE] - value".;

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPSADD_VALINC_W                                         16U
#define PDM_STPSADD_VALINC_M                                         0x0000FFFFU
#define PDM_STPSADD_VALINC_S                                         0U
#define PDM_STPSADD_VALINC_MINIMUM                                   0x00000000U
#define PDM_STPSADD_VALINC_MAXIMUM                                   0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPXMIN
    Offset name:         PDM_O_STPXMIN
    Relative address:    0x320
    Description:         REFCLK Minimum Period Value;Minimum Value of [STPXPER]
    Default Value:       0x0000FFFF

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0xFFFF
        Access type:     read-write
        Description:     Each time [STMPXPER] is updated, the value is also loaded into this register, provided that the value is smaller than the current value in this register.;When written, the register is reset to 0xFFFF (65535), regardless of the value written.;The minimum value can be used to detect extra Sample Clock pulses (this registers value will be significantly smaller than [STMPXPER.VALUE]).

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPXMIN_VALUE_W                                          16U
#define PDM_STPXMIN_VALUE_M                                          0x0000FFFFU
#define PDM_STPXMIN_VALUE_S                                          0U
#define PDM_STPXMIN_VALUE_MINIMUM                                    0x00000000U
#define PDM_STPXMIN_VALUE_MAXIMUM                                    0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPWCNT
    Offset name:         PDM_O_STPWCNT
    Relative address:    0x324
    Description:         Current Value of sample clock count
                        This register is reset when [STPCTL.STPEN]  = 0.
    Default Value:       0x00000000

        Field:           CURRVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Current value of the Sample Clock counter

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPWCNT_CURRVAL_W                                        16U
#define PDM_STPWCNT_CURRVAL_M                                        0x0000FFFFU
#define PDM_STPWCNT_CURRVAL_S                                        0U
#define PDM_STPWCNT_CURRVAL_MINIMUM                                  0x00000000U
#define PDM_STPWCNT_CURRVAL_MAXIMUM                                  0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPXCNT
    Offset name:         PDM_O_STPXCNT
    Relative address:    0x328
    Description:         Current Value of XCNT
                        This register is reset when [STPCTL.STPEN]  = 0.
    Default Value:       0x00000000

        Field:           CURRVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Current value of the REFCLK counter, latched when reading [STMPWCNT].

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define PDM_STPXCNT_CURRVAL_W                                        16U
#define PDM_STPXCNT_CURRVAL_M                                        0x0000FFFFU
#define PDM_STPXCNT_CURRVAL_S                                        0U
#define PDM_STPXCNT_CURRVAL_MINIMUM                                  0x00000000U
#define PDM_STPXCNT_CURRVAL_MAXIMUM                                  0x0000FFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       STPSTAT
    Offset name:         PDM_O_STPSTAT
    Relative address:    0x32C
    Description:         Samplestamp Generator Status Register
    Default Value:       0x00000000

        Field:           INRDY
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Low until the input pins are ready to be started by the samplestamp generator. When started (that is [STMPINTRIG] equals the WCLK counter) the bit goes back low.

        ENUMs:
            CLR:                         Clear
            SET:                         Set
*/
#define PDM_STPSTAT_INRDY                                            0x00000002U
#define PDM_STPSTAT_INRDY_M                                          0x00000002U
#define PDM_STPSTAT_INRDY_S                                          1U
#define PDM_STPSTAT_INRDY_CLR                                        0x00000000U
#define PDM_STPSTAT_INRDY_SET                                        0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         PDM_O_CLKCFG
    Relative address:    0x1000
    Description:         Clock configuration register
                        Note: Disable the [CLKCFG.MEM_CLK_EN] and [CLKCFG.ADFS_EN] to change [CLK_CFG.MEM_CLK_SEL] or [ADFS_CTRL1]/[ADFS_CTRL2]
                        After changing [CLK_CFG.MEM_CLK_SEL] or [ADFS_CTRL1]/[ADFS_CTRL2],  enable [CLKCFG.ADFS_EN] followed by [CLKCFG.MEM_CLK_EN]

    Default Value:       0x00000000

        Field:           CLKEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock enable

        ENUMs:
            DIS:                         Disable Clock
            EN:                          Enable Clock
*/
#define PDM_CLKCFG_CLKEN                                             0x00000001U
#define PDM_CLKCFG_CLKEN_M                                           0x00000001U
#define PDM_CLKCFG_CLKEN_S                                           0U
#define PDM_CLKCFG_CLKEN_DIS                                         0x00000000U
#define PDM_CLKCFG_CLKEN_EN                                          0x00000001U
/*

        Field:           CLKSEL
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Select

        ENUMs:
            SEL_0:                       No Clock
            SEL_1:                       SOC Clock(80MHz)
            SEL_2:                       SOC PLL Clock(un-swallowed 80MHz)
            SEL_3:                       HFXT
*/
#define PDM_CLKCFG_CLKSEL_W                                          3U
#define PDM_CLKCFG_CLKSEL_M                                          0x00000070U
#define PDM_CLKCFG_CLKSEL_S                                          4U
#define PDM_CLKCFG_CLKSEL_SEL_0                                      0x00000000U
#define PDM_CLKCFG_CLKSEL_SEL_1                                      0x00000010U
#define PDM_CLKCFG_CLKSEL_SEL_2                                      0x00000020U
#define PDM_CLKCFG_CLKSEL_SEL_3                                      0x00000030U
/*

        Field:           ADFSEN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADFS Enable bit

        ENUMs:
            DIS:                         Disable ADFS
            EN:                          Enable ADFS
*/
#define PDM_CLKCFG_ADFSEN                                            0x00000080U
#define PDM_CLKCFG_ADFSEN_M                                          0x00000080U
#define PDM_CLKCFG_ADFSEN_S                                          7U
#define PDM_CLKCFG_ADFSEN_DIS                                        0x00000000U
#define PDM_CLKCFG_ADFSEN_EN                                         0x00000080U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADFSCTL1
    Offset name:         PDM_O_ADFSCTL1
    Relative address:    0x1004
    Description:         ADFS control register
    Default Value:       0x00000000

        Field:           TREF
        From..to bits:   0...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Reference clock time period

*/
#define PDM_ADFSCTL1_TREF_W                                          21U
#define PDM_ADFSCTL1_TREF_M                                          0x001FFFFFU
#define PDM_ADFSCTL1_TREF_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADFSCTL2
    Offset name:         PDM_O_ADFSCTL2
    Relative address:    0x1008
    Description:         ADFS control register 2
    Default Value:       0x00000000

        Field:           DELTA
        From..to bits:   0...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Difference in time periods of (reference clk/divisor) and required clock

*/
#define PDM_ADFSCTL2_DELTA_W                                         17U
#define PDM_ADFSCTL2_DELTA_M                                         0x0001FFFFU
#define PDM_ADFSCTL2_DELTA_S                                         0U
/*

        Field:           DLTASIGN
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sign of delta value to be used.

        ENUMs:
            POS:                         Positive Sign
            NEG:                         Negative sign
*/
#define PDM_ADFSCTL2_DLTASIGN                                        0x00020000U
#define PDM_ADFSCTL2_DLTASIGN_M                                      0x00020000U
#define PDM_ADFSCTL2_DLTASIGN_S                                      17U
#define PDM_ADFSCTL2_DLTASIGN_POS                                    0x00000000U
#define PDM_ADFSCTL2_DLTASIGN_NEG                                    0x00020000U
/*

        Field:           DIV
        From..to bits:   20...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Value of divider to be used for ADFS

*/
#define PDM_ADFSCTL2_DIV_W                                           10U
#define PDM_ADFSCTL2_DIV_M                                           0x3FF00000U
#define PDM_ADFSCTL2_DIV_S                                           20U

#endif /* __HW_PDM_H__*/
