/******************************************************************************
*  Filename:       hw_adc.h
*
*  Description:    Defines and prototypes for the ADC peripheral.
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
#ifndef __HW_ADC_H__
#define __HW_ADC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the ADC component

--------------------------------------------------------------------------------- */

//FUSE CONTROL 0
#define ADC_O_FSCTL0                                                 0x00000000U

//FUSE CONTROL 1
#define ADC_O_FSCTL1                                                 0x00000004U

//FUSE CONTROL 2
#define ADC_O_FSCTL2                                                 0x00000008U

//FUSE CONTROL 3
#define ADC_O_FSCTL3                                                 0x0000000CU

//REFERENCE BUFFER
#define ADC_O_REFBUF                                                 0x00000010U

//ATB
#define ADC_O_ATB                                                    0x00000014U

//INTERNAL EVENT 0 IRQ IDX
#define ADC_O_INTEVT0IDX                                             0x00001020U

//INTERNAL EVENT 0 IRQ MASK
#define ADC_O_INTEVT0BM                                              0x00001028U

//INTERNAL EVENT 0 RAW IRQ STATUS
#define ADC_O_INTEVT0RIS                                             0x00001030U

//INTERNAL EVENT 0 MASKED IRQ STATUS
#define ADC_O_INTEVT0MIS                                             0x00001038U

//INTERNAL EVENT 0 IRQ SET
#define ADC_O_INTEVT0SET                                             0x00001040U

//INTERNAL EVENT 0 IRQ CLEAR
#define ADC_O_INTEVT0CLR                                             0x00001048U

//INTERNAL EVENT 1 IRQ IDX
#define ADC_O_INTEVT1IDX                                             0x00001050U

//INTERNAL EVENT 1 IRQ MASK
#define ADC_O_INTEVT1BM                                              0x00001058U

//INTERNAL EVENT 1 RAW IRQ STATUS
#define ADC_O_INTEVT1RIS                                             0x00001060U

//INTERNAL EVENT 1 MASKED IRQ STATUS
#define ADC_O_INTEVT1MIS                                             0x00001068U

//INTERNAL EVENT 1 IRQ SET
#define ADC_O_INTEVT1SET                                             0x00001070U

//INTERNAL EVENT 1 IRQ CLEAR
#define ADC_O_INTEVT1CLR                                             0x00001078U

//INTERNAL EVENT 2 IRQ IDX
#define ADC_O_INTEVT2IDX                                             0x00001080U

//INTERNAL EVENT 2 IRQ MASK
#define ADC_O_INTEVT2BM                                              0x00001088U

//INTERNAL EVENT 2 RAW IRQ STATUS
#define ADC_O_INTEVT2RIS                                             0x00001090U

//INTERNAL EVENT 2 MASKED IRQ STATUS
#define ADC_O_INTEVT2MIS                                             0x00001098U

//INTERNAL EVENT 2 IRQ SET
#define ADC_O_INTEVT2SET                                             0x000010A0U

//INTERNAL EVENT 2 IRQ CLEAR
#define ADC_O_INTEVT2CLR                                             0x000010A8U

//EVENT MODE
#define ADC_O_EVTMOD                                                 0x000010E0U

//This register identifies the peripheral and its exact version
#define ADC_O_DESC                                                   0x000010FCU

//ULP_ADCHP Control Register 0
#define ADC_O_CTL0                                                   0x00001100U

//Primary Sequence Control Register
#define ADC_O_CTL1                                                   0x00001104U

//Primary Sequence Control Register
#define ADC_O_CTL2                                                   0x00001108U

//Control Register 3
#define ADC_O_CTL3                                                   0x0000110CU

//ADC sampling clock frequency range register
#define ADC_O_CLKFREQ                                                0x00001110U

//ULP_ADCHP sample time register x
#define ADC_O_SCOMP0                                                 0x00001114U

//ULP_ADCHP sample time register x
#define ADC_O_SCOMP1                                                 0x00001118U

//REFBUF configuration register
#define ADC_O_REFCFG                                                 0x0000111CU

//ULP_ADCHP Window Comparator Low Threshold 0 Register
#define ADC_O_WCLOW                                                  0x00001148U

//WC HIGH
#define ADC_O_WCHI                                                   0x00001150U

//Virtual data register used to do a read from FIFO
#define ADC_O_FIFODATA                                               0x00001160U

//ASC result register
#define ADC_O_ASCRES                                                 0x00001170U

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_0                                               0x00001180U

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_1                                               0x00001184U

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_2                                               0x00001188U

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_3                                               0x0000118CU

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_4                                               0x00001190U

//ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
#define ADC_O_MEMCTL_5                                               0x00001194U

//Memory Results Register
#define ADC_O_MEMRES_0                                               0x00001280U

//Memory Results Register
#define ADC_O_MEMRES_1                                               0x00001284U

//Memory Results Register
#define ADC_O_MEMRES_2                                               0x00001288U

//Memory Results Register
#define ADC_O_MEMRES_3                                               0x0000128CU

//Memory Results Register
#define ADC_O_MEMRES_4                                               0x00001290U

//Memory Results Register
#define ADC_O_MEMRES_5                                               0x00001294U

//Memory Results Register
#define ADC_O_MEMRES_6                                               0x00001298U

//Memory Results Register
#define ADC_O_MEMRES_7                                               0x0000129CU

//Memory Results Register
#define ADC_O_MEMRES_8                                               0x000012A0U

//Memory Results Register
#define ADC_O_MEMRES_9                                               0x000012A4U

//Memory Results Register
#define ADC_O_MEMRES_10                                              0x000012A8U

//Memory Results Register
#define ADC_O_MEMRES_11                                              0x000012ACU

//Memory Results Register
#define ADC_O_MEMRES_12                                              0x000012B0U

//Memory Results Register
#define ADC_O_MEMRES_13                                              0x000012B4U

//Memory Results Register
#define ADC_O_MEMRES_14                                              0x000012B8U

//Memory Results Register
#define ADC_O_MEMRES_15                                              0x000012BCU

//STATUS
#define ADC_O_STA                                                    0x00001340U

//Test0 register for ATB Mux sel for ATBBUF and ATBUNBUF
#define ADC_O_TEST0                                                  0x00001E00U

//DTB MUX Selection
#define ADC_O_TEST1                                                  0x00001E04U

//ATB Ch sel as ADC input
#define ADC_O_TEST2                                                  0x00001E08U

//ADC CAL Accumulation Register
#define ADC_O_TEST3                                                  0x00001E0CU

//CAL Control register: Average Sample count, Step number, Recall En and Debug option to override ull_usc_ulpadchp_dft_i<26:0>
#define ADC_O_TEST4                                                  0x00001E10U

//This register updated ull_usc_ulpadchp_dft_i[26:0] value  if Test 5: HW_STEP_SEL_DIS bit enable
#define ADC_O_TEST5                                                  0x00001E14U

//REFBUF ATB selection
#define ADC_O_TEST6                                                  0x00001E18U

//DEBUG1
#define ADC_O_DBG1                                                   0x00001E20U

//DEBUG 2
#define ADC_O_DBG2                                                   0x00001E24U

//DEBUG 3
#define ADC_O_DBG3                                                   0x00001E28U

//DEBUG 4
#define ADC_O_DBG4                                                   0x00001E2CU

//Conversion Control
#define ADC_O_CONVCTL                                                0x00001F14U

//CTRL
#define ADC_O_CTRL                                                   0x00001F18U

//MODE CONTROL
#define ADC_O_MODCTL                                                 0x00001F1CU

//INTERNAL CHANNEL CONTROL
#define ADC_O_INTCHCTL                                               0x00001F20U

//SETTLING TIME
#define ADC_O_STLTIM                                                 0x00001F24U

//ADC CLK CONFIG
#define ADC_O_CLKCFG                                                 0x00002000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       FSCTL0
    Offset name:         ADC_O_FSCTL0
    Relative address:    0x0
    Description:         FUSE CONTROL 0

                        Primarily for lab testing, needs to be written by TI boot code

                        All may not be used now, few spare are kept intentionally
    Default Value:       0x0044554A

        Field:           TRIM0
        From..to bits:   0...31
        DefaultValue:    0x44554A
        Access type:     read-write
        Description:     TRIM VALUE 0

*/
#define ADC_FSCTL0_TRIM0_W                                           32U
#define ADC_FSCTL0_TRIM0_M                                           0xFFFFFFFFU
#define ADC_FSCTL0_TRIM0_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FSCTL1
    Offset name:         ADC_O_FSCTL1
    Relative address:    0x4
    Description:         FUSE CONTROL 1

                        Primarily for lab testing, needs to be written by TI boot code

                        All may not be used now, few spare are kept intentionally
    Default Value:       0x18F06630

        Field:           TRIM1
        From..to bits:   0...31
        DefaultValue:    0x18F06630
        Access type:     read-write
        Description:     TRIM VALUE 1

*/
#define ADC_FSCTL1_TRIM1_W                                           32U
#define ADC_FSCTL1_TRIM1_M                                           0xFFFFFFFFU
#define ADC_FSCTL1_TRIM1_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FSCTL2
    Offset name:         ADC_O_FSCTL2
    Relative address:    0x8
    Description:         FUSE CONTROL 2

                        Primarily for lab testing, needs to be written by TI boot code

                        All may not be used now, few spare are kept intentionally
    Default Value:       0x0010208A

        Field:           TRIM2
        From..to bits:   0...31
        DefaultValue:    0x10208A
        Access type:     read-write
        Description:     TRIM VALUE 2

*/
#define ADC_FSCTL2_TRIM2_W                                           32U
#define ADC_FSCTL2_TRIM2_M                                           0xFFFFFFFFU
#define ADC_FSCTL2_TRIM2_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FSCTL3
    Offset name:         ADC_O_FSCTL3
    Relative address:    0xC
    Description:         FUSE CONTROL 3

                        Primarily for lab testing, needs to be written by TI boot code

                        All may not be used now, few spare are kept intentionally
    Default Value:       0x00000000

        Field:           TRIM3
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIM VALUE 3

*/
#define ADC_FSCTL3_TRIM3_W                                           16U
#define ADC_FSCTL3_TRIM3_M                                           0x0000FFFFU
#define ADC_FSCTL3_TRIM3_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REFBUF
    Offset name:         ADC_O_REFBUF
    Relative address:    0x10
    Description:         REFERENCE BUFFER
    Default Value:       0x000A6E09

        Field:           CFG
        From..to bits:   0...31
        DefaultValue:    0xA6E09
        Access type:     read-write
        Description:     CONFIG

                         bit[0] - Enable Internal Reference Mode
                         bits[3:1] - Vsel for 3.3V mode Internal Reference Mode.  Vrefbuf = 1.3V
                         bits[6:4] - Vsel bits for higher tap points - For debug purpose
                         <6:4> --> 001 (0.9V)
                         <6:4> --> 010 (1.45V)
                         <6:4> --> 100 (1.4V)
                         bits[8:7] - Enable Test mux to check ground and reference thought test pins
                         01--> Vref Internal available to measure
                         10 --> vss Internal Reference available to measure
                         bits[10:9] - Trim bits to change the bias current in Ref buf 1st stage
                         bits[12:11] - Trim bits to change the bias current in Ref buf
                         bits[14:13] - Trim bits to change the bias current in Ref buf output stage
                         bits[16:15] - NU
                         bits[19:17] - Vsel for 1.8V mode Internal Reference Mode .Vrefbuf = 1.35V
                         bits[31:20] - NU

*/
#define ADC_REFBUF_CFG_W                                             32U
#define ADC_REFBUF_CFG_M                                             0xFFFFFFFFU
#define ADC_REFBUF_CFG_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ATB
    Offset name:         ADC_O_ATB
    Relative address:    0x14
    Description:         ATB
    Default Value:       0x00000000

        Field:           CTRL
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CONTROL

                         bit0- master enable of test mux for AIP
                         bit1- refbuf test enable
                         bit2- 20uA current (scaled from PMCIO) test enable
                         bit3- vbat_div test enable
                         bit4- Tsense test enable
                         bit5- Bandgap 0p9v test enable
                         bit6- No connect
                         bit7- No connect

*/
#define ADC_ATB_CTRL_W                                               8U
#define ADC_ATB_CTRL_M                                               0x000000FFU
#define ADC_ATB_CTRL_S                                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0IDX
    Offset name:         ADC_O_INTEVT0IDX
    Relative address:    0x1020
    Description:         INTERNAL EVENT 0 IRQ IDX

                        This register provides the highest priority enabled interrupt index. 0x0 means no event pending. Interrupt 1 is the highest priority, 2 next highest, 4, 8, ... 2^31 is the least priority. That is, the least bit position that is set to 1 denotes the highest priority pending interrupt. The priority order is fixed. However, users can implement their own prioritization schemes using other registers that expose the full set of interrupts that have occurred.

                        On each read, only one interrupt is indicated. On a read, the current interrupt (highest priority) is automatically cleared by the hardware and the corresponding interrupt flag in the RIS and MIS are cleared as well. After a read from the CPU (not from the debug interface), the register must be updated with the next highest priority interrupt, if none are pending, then it should display 0x0.

    Default Value:       0x00000000

        Field:           STAT
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Interrupt index status

        ENUMs:
            NO_INTR:                     No bit is set means there is no pending interrupt request
            OVIFG:                       MEMRESx overflow interrupt
            UVIFG:                       MEMRESx underflow interrupt
            TOVIFG:                      Sequence Conversion time overflow interrupt
            HIGHIFG:                     High threshold compare interrupt
            LOWIFG:                      Low threshold compare interrupt
            INIFG:                       Primary Sequence In range comparator interrupt
            MEMRESIFG0:                  MEMRES0 data loaded interrupt
            MEMRESIFG1:                  MEMRES1 data loaded interrupt
            MEMRESIFG2:                  MEMRES2 data loaded interrupt
            MEMRESIFG3:                  MEMRES3 data loaded interrupt
            MEMRESIFG4:                  MEMRES4 data loaded interrupt
            MEMRESIFG5:                  MEMRES5 data loaded interrupt
            MEMRESIFG6:                  MEMRES6 data loaded interrupt
            MEMRESIFG7:                  MEMRES7 data loaded interrupt
            MEMRESIFG8:                  MEMRES8 data loaded interrupt
            MEMRESIFG9:                  MEMRES9 data  loaded interrupt
            MEMRESIFG10:                 MEMRES10 data  loaded interrupt
            MEMRESIFG11:                 MEMRES11 data  loaded interrupt
            MEMRESIFG12:                 MEMRES12 data  loaded interrupt
            MEMRESIFG13:                 MEMRES13 data  loaded interrupt
            MEMRESIFG14:                 MEMRES14 data  loaded interrupt
            MEMRESIFG15:                 MEMRES15 data  loaded interrupt
            MEMRESIFG16:                 MEMRES16 data loaded interrupt
            MEMRESIFG17:                 MEMRES17 data loaded interrupt
            MEMRESIFG18:                 MEMRES18 data loaded interrupt
            MEMRESIFG19:                 MEMRES19 data loaded interrupt
            MEMRESIFG20:                 MEMRES20 data loaded interrupt
            MEMRESIFG21:                 MEMRES21 data loaded interrupt
            MEMRESIFG22:                 MEMRES22 data loaded interrupt
            MEMRESIFG23:                 MEMRES23 data loaded interrupt
            DMADONE:                     DMA done interrupt, generated on DMA transfer completion,
*/
#define ADC_INTEVT0IDX_STAT_W                                        10U
#define ADC_INTEVT0IDX_STAT_M                                        0x000003FFU
#define ADC_INTEVT0IDX_STAT_S                                        0U
#define ADC_INTEVT0IDX_STAT_NO_INTR                                  0x00000000U
#define ADC_INTEVT0IDX_STAT_OVIFG                                    0x00000001U
#define ADC_INTEVT0IDX_STAT_UVIFG                                    0x00000007U
#define ADC_INTEVT0IDX_STAT_TOVIFG                                   0x00000002U
#define ADC_INTEVT0IDX_STAT_HIGHIFG                                  0x00000003U
#define ADC_INTEVT0IDX_STAT_LOWIFG                                   0x00000004U
#define ADC_INTEVT0IDX_STAT_INIFG                                    0x00000005U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG0                               0x00000009U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG1                               0x0000000AU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG2                               0x0000000BU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG3                               0x0000000CU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG4                               0x0000000DU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG5                               0x0000000EU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG6                               0x0000000FU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG7                               0x00000010U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG8                               0x00000011U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG9                               0x00000012U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG10                              0x00000013U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG11                              0x00000014U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG12                              0x00000015U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG13                              0x00000016U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG14                              0x00000017U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG15                              0x00000018U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG16                              0x00000019U
#define ADC_INTEVT0IDX_STAT_MEMRESIFG17                              0x0000001AU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG18                              0x0000001BU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG19                              0x0000001CU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG20                              0x0000001DU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG21                              0x0000001EU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG22                              0x0000001FU
#define ADC_INTEVT0IDX_STAT_MEMRESIFG23                              0x00000020U
#define ADC_INTEVT0IDX_STAT_DMADONE                                  0x00000006U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0BM
    Offset name:         ADC_O_INTEVT0BM
    Relative address:    0x1028
    Description:         INTERNAL EVENT 0 IRQ MASK

                        Interrupt Mask. If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in IIDX, as well as MIS.
    Default Value:       0x00000000

        Field:           OVIFG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt flag for MEMRESx overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_OVIFG                                          0x00000001U
#define ADC_INTEVT0BM_OVIFG_M                                        0x00000001U
#define ADC_INTEVT0BM_OVIFG_S                                        0U
#define ADC_INTEVT0BM_OVIFG_CLR                                      0x00000000U
#define ADC_INTEVT0BM_OVIFG_SET                                      0x00000001U
/*

        Field:           TOVIFG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt flag for sequence conversion timeout overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_TOVIFG                                         0x00000002U
#define ADC_INTEVT0BM_TOVIFG_M                                       0x00000002U
#define ADC_INTEVT0BM_TOVIFG_S                                       1U
#define ADC_INTEVT0BM_TOVIFG_CLR                                     0x00000000U
#define ADC_INTEVT0BM_TOVIFG_SET                                     0x00000002U
/*

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_HIFG                                           0x00000004U
#define ADC_INTEVT0BM_HIFG_M                                         0x00000004U
#define ADC_INTEVT0BM_HIFG_S                                         2U
#define ADC_INTEVT0BM_HIFG_CLR                                       0x00000000U
#define ADC_INTEVT0BM_HIFG_SET                                       0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_LOFG                                           0x00000008U
#define ADC_INTEVT0BM_LOFG_M                                         0x00000008U
#define ADC_INTEVT0BM_LOFG_S                                         3U
#define ADC_INTEVT0BM_LOFG_CLR                                       0x00000000U
#define ADC_INTEVT0BM_LOFG_SET                                       0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_INIFG                                          0x00000010U
#define ADC_INTEVT0BM_INIFG_M                                        0x00000010U
#define ADC_INTEVT0BM_INIFG_S                                        4U
#define ADC_INTEVT0BM_INIFG_CLR                                      0x00000000U
#define ADC_INTEVT0BM_INIFG_SET                                      0x00000010U
/*

        Field:           DMADONE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt flag for DMADONE.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_DMADONE                                        0x00000020U
#define ADC_INTEVT0BM_DMADONE_M                                      0x00000020U
#define ADC_INTEVT0BM_DMADONE_S                                      5U
#define ADC_INTEVT0BM_DMADONE_CLR                                    0x00000000U
#define ADC_INTEVT0BM_DMADONE_SET                                    0x00000020U
/*

        Field:           UVIFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt flag for MEMRESx underflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0BM_UVIFG                                          0x00000040U
#define ADC_INTEVT0BM_UVIFG_M                                        0x00000040U
#define ADC_INTEVT0BM_UVIFG_S                                        6U
#define ADC_INTEVT0BM_UVIFG_CLR                                      0x00000000U
#define ADC_INTEVT0BM_UVIFG_SET                                      0x00000040U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG0                                     0x00000100U
#define ADC_INTEVT0BM_MEMRESIFG0_M                                   0x00000100U
#define ADC_INTEVT0BM_MEMRESIFG0_S                                   8U
#define ADC_INTEVT0BM_MEMRESIFG0_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG0_SET                                 0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG1                                     0x00000200U
#define ADC_INTEVT0BM_MEMRESIFG1_M                                   0x00000200U
#define ADC_INTEVT0BM_MEMRESIFG1_S                                   9U
#define ADC_INTEVT0BM_MEMRESIFG1_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG1_SET                                 0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG2                                     0x00000400U
#define ADC_INTEVT0BM_MEMRESIFG2_M                                   0x00000400U
#define ADC_INTEVT0BM_MEMRESIFG2_S                                   10U
#define ADC_INTEVT0BM_MEMRESIFG2_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG2_SET                                 0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG3                                     0x00000800U
#define ADC_INTEVT0BM_MEMRESIFG3_M                                   0x00000800U
#define ADC_INTEVT0BM_MEMRESIFG3_S                                   11U
#define ADC_INTEVT0BM_MEMRESIFG3_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG3_SET                                 0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG4                                     0x00001000U
#define ADC_INTEVT0BM_MEMRESIFG4_M                                   0x00001000U
#define ADC_INTEVT0BM_MEMRESIFG4_S                                   12U
#define ADC_INTEVT0BM_MEMRESIFG4_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG4_SET                                 0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG5                                     0x00002000U
#define ADC_INTEVT0BM_MEMRESIFG5_M                                   0x00002000U
#define ADC_INTEVT0BM_MEMRESIFG5_S                                   13U
#define ADC_INTEVT0BM_MEMRESIFG5_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG5_SET                                 0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG6                                     0x00004000U
#define ADC_INTEVT0BM_MEMRESIFG6_M                                   0x00004000U
#define ADC_INTEVT0BM_MEMRESIFG6_S                                   14U
#define ADC_INTEVT0BM_MEMRESIFG6_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG6_SET                                 0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG7                                     0x00008000U
#define ADC_INTEVT0BM_MEMRESIFG7_M                                   0x00008000U
#define ADC_INTEVT0BM_MEMRESIFG7_S                                   15U
#define ADC_INTEVT0BM_MEMRESIFG7_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG7_SET                                 0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG8                                     0x00010000U
#define ADC_INTEVT0BM_MEMRESIFG8_M                                   0x00010000U
#define ADC_INTEVT0BM_MEMRESIFG8_S                                   16U
#define ADC_INTEVT0BM_MEMRESIFG8_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG8_SET                                 0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG9                                     0x00020000U
#define ADC_INTEVT0BM_MEMRESIFG9_M                                   0x00020000U
#define ADC_INTEVT0BM_MEMRESIFG9_S                                   17U
#define ADC_INTEVT0BM_MEMRESIFG9_CLR                                 0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG9_SET                                 0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG10                                    0x00040000U
#define ADC_INTEVT0BM_MEMRESIFG10_M                                  0x00040000U
#define ADC_INTEVT0BM_MEMRESIFG10_S                                  18U
#define ADC_INTEVT0BM_MEMRESIFG10_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG10_SET                                0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG11                                    0x00080000U
#define ADC_INTEVT0BM_MEMRESIFG11_M                                  0x00080000U
#define ADC_INTEVT0BM_MEMRESIFG11_S                                  19U
#define ADC_INTEVT0BM_MEMRESIFG11_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG11_SET                                0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG12                                    0x00100000U
#define ADC_INTEVT0BM_MEMRESIFG12_M                                  0x00100000U
#define ADC_INTEVT0BM_MEMRESIFG12_S                                  20U
#define ADC_INTEVT0BM_MEMRESIFG12_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG12_SET                                0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG13                                    0x00200000U
#define ADC_INTEVT0BM_MEMRESIFG13_M                                  0x00200000U
#define ADC_INTEVT0BM_MEMRESIFG13_S                                  21U
#define ADC_INTEVT0BM_MEMRESIFG13_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG13_SET                                0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG14                                    0x00400000U
#define ADC_INTEVT0BM_MEMRESIFG14_M                                  0x00400000U
#define ADC_INTEVT0BM_MEMRESIFG14_S                                  22U
#define ADC_INTEVT0BM_MEMRESIFG14_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG14_SET                                0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0BM_MEMRESIFG15                                    0x00800000U
#define ADC_INTEVT0BM_MEMRESIFG15_M                                  0x00800000U
#define ADC_INTEVT0BM_MEMRESIFG15_S                                  23U
#define ADC_INTEVT0BM_MEMRESIFG15_CLR                                0x00000000U
#define ADC_INTEVT0BM_MEMRESIFG15_SET                                0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0RIS
    Offset name:         ADC_O_INTEVT0RIS
    Relative address:    0x1030
    Description:         INTERNAL EVENT 0 RAW IRQ STATUS

                        Raw interrupt status. Reflects all pending interrupts, regardless of masking. The INT_EVENT0_RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           OVIFG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for MEMRESx overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_OVIFG                                         0x00000001U
#define ADC_INTEVT0RIS_OVIFG_M                                       0x00000001U
#define ADC_INTEVT0RIS_OVIFG_S                                       0U
#define ADC_INTEVT0RIS_OVIFG_CLR                                     0x00000000U
#define ADC_INTEVT0RIS_OVIFG_SET                                     0x00000001U
/*

        Field:           TOVIFG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for sequence conversion timeout overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_TOVIFG                                        0x00000002U
#define ADC_INTEVT0RIS_TOVIFG_M                                      0x00000002U
#define ADC_INTEVT0RIS_TOVIFG_S                                      1U
#define ADC_INTEVT0RIS_TOVIFG_CLR                                    0x00000000U
#define ADC_INTEVT0RIS_TOVIFG_SET                                    0x00000002U
/*

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_HIFG                                          0x00000004U
#define ADC_INTEVT0RIS_HIFG_M                                        0x00000004U
#define ADC_INTEVT0RIS_HIFG_S                                        2U
#define ADC_INTEVT0RIS_HIFG_CLR                                      0x00000000U
#define ADC_INTEVT0RIS_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_LOFG                                          0x00000008U
#define ADC_INTEVT0RIS_LOFG_M                                        0x00000008U
#define ADC_INTEVT0RIS_LOFG_S                                        3U
#define ADC_INTEVT0RIS_LOFG_CLR                                      0x00000000U
#define ADC_INTEVT0RIS_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_INIFG                                         0x00000010U
#define ADC_INTEVT0RIS_INIFG_M                                       0x00000010U
#define ADC_INTEVT0RIS_INIFG_S                                       4U
#define ADC_INTEVT0RIS_INIFG_CLR                                     0x00000000U
#define ADC_INTEVT0RIS_INIFG_SET                                     0x00000010U
/*

        Field:           DMADONE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for DMADONE.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_DMADONE                                       0x00000020U
#define ADC_INTEVT0RIS_DMADONE_M                                     0x00000020U
#define ADC_INTEVT0RIS_DMADONE_S                                     5U
#define ADC_INTEVT0RIS_DMADONE_CLR                                   0x00000000U
#define ADC_INTEVT0RIS_DMADONE_SET                                   0x00000020U
/*

        Field:           UVIFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for MEMRESx underflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0RIS_UVIFG                                         0x00000040U
#define ADC_INTEVT0RIS_UVIFG_M                                       0x00000040U
#define ADC_INTEVT0RIS_UVIFG_S                                       6U
#define ADC_INTEVT0RIS_UVIFG_CLR                                     0x00000000U
#define ADC_INTEVT0RIS_UVIFG_SET                                     0x00000040U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT0RIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT0RIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT0RIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT0RIS_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT0RIS_MEMRESIFG1_S                                  9U
#define ADC_INTEVT0RIS_MEMRESIFG1_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT0RIS_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT0RIS_MEMRESIFG2_S                                  10U
#define ADC_INTEVT0RIS_MEMRESIFG2_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT0RIS_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT0RIS_MEMRESIFG3_S                                  11U
#define ADC_INTEVT0RIS_MEMRESIFG3_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT0RIS_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT0RIS_MEMRESIFG4_S                                  12U
#define ADC_INTEVT0RIS_MEMRESIFG4_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT0RIS_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT0RIS_MEMRESIFG5_S                                  13U
#define ADC_INTEVT0RIS_MEMRESIFG5_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT0RIS_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT0RIS_MEMRESIFG6_S                                  14U
#define ADC_INTEVT0RIS_MEMRESIFG6_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT0RIS_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT0RIS_MEMRESIFG7_S                                  15U
#define ADC_INTEVT0RIS_MEMRESIFG7_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT0RIS_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT0RIS_MEMRESIFG8_S                                  16U
#define ADC_INTEVT0RIS_MEMRESIFG8_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT0RIS_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT0RIS_MEMRESIFG9_S                                  17U
#define ADC_INTEVT0RIS_MEMRESIFG9_CLR                                0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT0RIS_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT0RIS_MEMRESIFG10_S                                 18U
#define ADC_INTEVT0RIS_MEMRESIFG10_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT0RIS_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT0RIS_MEMRESIFG11_S                                 19U
#define ADC_INTEVT0RIS_MEMRESIFG11_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT0RIS_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT0RIS_MEMRESIFG12_S                                 20U
#define ADC_INTEVT0RIS_MEMRESIFG12_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT0RIS_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT0RIS_MEMRESIFG13_S                                 21U
#define ADC_INTEVT0RIS_MEMRESIFG13_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT0RIS_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT0RIS_MEMRESIFG14_S                                 22U
#define ADC_INTEVT0RIS_MEMRESIFG14_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0RIS_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT0RIS_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT0RIS_MEMRESIFG15_S                                 23U
#define ADC_INTEVT0RIS_MEMRESIFG15_CLR                               0x00000000U
#define ADC_INTEVT0RIS_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0MIS
    Offset name:         ADC_O_INTEVT0MIS
    Relative address:    0x1038
    Description:         INTERNAL EVENT 0 MASKED IRQ STATUS

                        Masked interrupt status. This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           OVIFG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for MEMRESx overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_OVIFG                                         0x00000001U
#define ADC_INTEVT0MIS_OVIFG_M                                       0x00000001U
#define ADC_INTEVT0MIS_OVIFG_S                                       0U
#define ADC_INTEVT0MIS_OVIFG_CLR                                     0x00000000U
#define ADC_INTEVT0MIS_OVIFG_SET                                     0x00000001U
/*

        Field:           TOVIFG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for sequence conversion timeout overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_TOVIFG                                        0x00000002U
#define ADC_INTEVT0MIS_TOVIFG_M                                      0x00000002U
#define ADC_INTEVT0MIS_TOVIFG_S                                      1U
#define ADC_INTEVT0MIS_TOVIFG_CLR                                    0x00000000U
#define ADC_INTEVT0MIS_TOVIFG_SET                                    0x00000002U
/*

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_HIFG                                          0x00000004U
#define ADC_INTEVT0MIS_HIFG_M                                        0x00000004U
#define ADC_INTEVT0MIS_HIFG_S                                        2U
#define ADC_INTEVT0MIS_HIFG_CLR                                      0x00000000U
#define ADC_INTEVT0MIS_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_LOFG                                          0x00000008U
#define ADC_INTEVT0MIS_LOFG_M                                        0x00000008U
#define ADC_INTEVT0MIS_LOFG_S                                        3U
#define ADC_INTEVT0MIS_LOFG_CLR                                      0x00000000U
#define ADC_INTEVT0MIS_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_INIFG                                         0x00000010U
#define ADC_INTEVT0MIS_INIFG_M                                       0x00000010U
#define ADC_INTEVT0MIS_INIFG_S                                       4U
#define ADC_INTEVT0MIS_INIFG_CLR                                     0x00000000U
#define ADC_INTEVT0MIS_INIFG_SET                                     0x00000010U
/*

        Field:           DMADONE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for DMADONE.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_DMADONE                                       0x00000020U
#define ADC_INTEVT0MIS_DMADONE_M                                     0x00000020U
#define ADC_INTEVT0MIS_DMADONE_S                                     5U
#define ADC_INTEVT0MIS_DMADONE_CLR                                   0x00000000U
#define ADC_INTEVT0MIS_DMADONE_SET                                   0x00000020U
/*

        Field:           UVIFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt flag for MEMRESx underflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0MIS_UVIFG                                         0x00000040U
#define ADC_INTEVT0MIS_UVIFG_M                                       0x00000040U
#define ADC_INTEVT0MIS_UVIFG_S                                       6U
#define ADC_INTEVT0MIS_UVIFG_CLR                                     0x00000000U
#define ADC_INTEVT0MIS_UVIFG_SET                                     0x00000040U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 11

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT0MIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT0MIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT0MIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT0MIS_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT0MIS_MEMRESIFG1_S                                  9U
#define ADC_INTEVT0MIS_MEMRESIFG1_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT0MIS_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT0MIS_MEMRESIFG2_S                                  10U
#define ADC_INTEVT0MIS_MEMRESIFG2_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT0MIS_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT0MIS_MEMRESIFG3_S                                  11U
#define ADC_INTEVT0MIS_MEMRESIFG3_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT0MIS_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT0MIS_MEMRESIFG4_S                                  12U
#define ADC_INTEVT0MIS_MEMRESIFG4_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT0MIS_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT0MIS_MEMRESIFG5_S                                  13U
#define ADC_INTEVT0MIS_MEMRESIFG5_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT0MIS_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT0MIS_MEMRESIFG6_S                                  14U
#define ADC_INTEVT0MIS_MEMRESIFG6_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT0MIS_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT0MIS_MEMRESIFG7_S                                  15U
#define ADC_INTEVT0MIS_MEMRESIFG7_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT0MIS_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT0MIS_MEMRESIFG8_S                                  16U
#define ADC_INTEVT0MIS_MEMRESIFG8_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT0MIS_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT0MIS_MEMRESIFG9_S                                  17U
#define ADC_INTEVT0MIS_MEMRESIFG9_CLR                                0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT0MIS_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT0MIS_MEMRESIFG10_S                                 18U
#define ADC_INTEVT0MIS_MEMRESIFG10_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT0MIS_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT0MIS_MEMRESIFG11_S                                 19U
#define ADC_INTEVT0MIS_MEMRESIFG11_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT0MIS_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT0MIS_MEMRESIFG12_S                                 20U
#define ADC_INTEVT0MIS_MEMRESIFG12_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT0MIS_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT0MIS_MEMRESIFG13_S                                 21U
#define ADC_INTEVT0MIS_MEMRESIFG13_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT0MIS_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT0MIS_MEMRESIFG14_S                                 22U
#define ADC_INTEVT0MIS_MEMRESIFG14_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0MIS_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT0MIS_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT0MIS_MEMRESIFG15_S                                 23U
#define ADC_INTEVT0MIS_MEMRESIFG15_CLR                               0x00000000U
#define ADC_INTEVT0MIS_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0SET
    Offset name:         ADC_O_INTEVT0SET
    Relative address:    0x1040
    Description:         INTERNAL EVENT 0 IRQ SET

                        Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in INT_EVENT0_ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           OVIFG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for MEMRESx overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_OVIFG                                         0x00000001U
#define ADC_INTEVT0SET_OVIFG_M                                       0x00000001U
#define ADC_INTEVT0SET_OVIFG_S                                       0U
#define ADC_INTEVT0SET_OVIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0SET_OVIFG_SET                                     0x00000001U
/*

        Field:           TOVIFG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for sequence conversion timeout overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_TOVIFG                                        0x00000002U
#define ADC_INTEVT0SET_TOVIFG_M                                      0x00000002U
#define ADC_INTEVT0SET_TOVIFG_S                                      1U
#define ADC_INTEVT0SET_TOVIFG_NO_EFFECT                              0x00000000U
#define ADC_INTEVT0SET_TOVIFG_SET                                    0x00000002U
/*

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_HIFG                                          0x00000004U
#define ADC_INTEVT0SET_HIFG_M                                        0x00000004U
#define ADC_INTEVT0SET_HIFG_S                                        2U
#define ADC_INTEVT0SET_HIFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT0SET_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_LOFG                                          0x00000008U
#define ADC_INTEVT0SET_LOFG_M                                        0x00000008U
#define ADC_INTEVT0SET_LOFG_S                                        3U
#define ADC_INTEVT0SET_LOFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT0SET_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_INIFG                                         0x00000010U
#define ADC_INTEVT0SET_INIFG_M                                       0x00000010U
#define ADC_INTEVT0SET_INIFG_S                                       4U
#define ADC_INTEVT0SET_INIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0SET_INIFG_SET                                     0x00000010U
/*

        Field:           DMADONE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for DMADONE.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_DMADONE                                       0x00000020U
#define ADC_INTEVT0SET_DMADONE_M                                     0x00000020U
#define ADC_INTEVT0SET_DMADONE_S                                     5U
#define ADC_INTEVT0SET_DMADONE_NO_EFFECT                             0x00000000U
#define ADC_INTEVT0SET_DMADONE_SET                                   0x00000020U
/*

        Field:           UVIFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for MEMRESx underflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT0SET_UVIFG                                         0x00000040U
#define ADC_INTEVT0SET_UVIFG_M                                       0x00000040U
#define ADC_INTEVT0SET_UVIFG_S                                       6U
#define ADC_INTEVT0SET_UVIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0SET_UVIFG_SET                                     0x00000040U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT0SET_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT0SET_MEMRESIFG0_S                                  8U
#define ADC_INTEVT0SET_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT0SET_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT0SET_MEMRESIFG1_S                                  9U
#define ADC_INTEVT0SET_MEMRESIFG1_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT0SET_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT0SET_MEMRESIFG2_S                                  10U
#define ADC_INTEVT0SET_MEMRESIFG2_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT0SET_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT0SET_MEMRESIFG3_S                                  11U
#define ADC_INTEVT0SET_MEMRESIFG3_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT0SET_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT0SET_MEMRESIFG4_S                                  12U
#define ADC_INTEVT0SET_MEMRESIFG4_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT0SET_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT0SET_MEMRESIFG5_S                                  13U
#define ADC_INTEVT0SET_MEMRESIFG5_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT0SET_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT0SET_MEMRESIFG6_S                                  14U
#define ADC_INTEVT0SET_MEMRESIFG6_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT0SET_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT0SET_MEMRESIFG7_S                                  15U
#define ADC_INTEVT0SET_MEMRESIFG7_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT0SET_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT0SET_MEMRESIFG8_S                                  16U
#define ADC_INTEVT0SET_MEMRESIFG8_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT0SET_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT0SET_MEMRESIFG9_S                                  17U
#define ADC_INTEVT0SET_MEMRESIFG9_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT0SET_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT0SET_MEMRESIFG10_S                                 18U
#define ADC_INTEVT0SET_MEMRESIFG10_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT0SET_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT0SET_MEMRESIFG11_S                                 19U
#define ADC_INTEVT0SET_MEMRESIFG11_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT0SET_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT0SET_MEMRESIFG12_S                                 20U
#define ADC_INTEVT0SET_MEMRESIFG12_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT0SET_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT0SET_MEMRESIFG13_S                                 21U
#define ADC_INTEVT0SET_MEMRESIFG13_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT0SET_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT0SET_MEMRESIFG14_S                                 22U
#define ADC_INTEVT0SET_MEMRESIFG14_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT0SET_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT0SET_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT0SET_MEMRESIFG15_S                                 23U
#define ADC_INTEVT0SET_MEMRESIFG15_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0SET_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT0CLR
    Offset name:         ADC_O_INTEVT0CLR
    Relative address:    0x1048
    Description:         INTERNAL EVENT 0 IRQ CLEAR

                        Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           OVIFG
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for MEMRESx overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_OVIFG                                         0x00000001U
#define ADC_INTEVT0CLR_OVIFG_M                                       0x00000001U
#define ADC_INTEVT0CLR_OVIFG_S                                       0U
#define ADC_INTEVT0CLR_OVIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0CLR_OVIFG_CLR                                     0x00000001U
/*

        Field:           TOVIFG
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for sequence conversion timeout overflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_TOVIFG                                        0x00000002U
#define ADC_INTEVT0CLR_TOVIFG_M                                      0x00000002U
#define ADC_INTEVT0CLR_TOVIFG_S                                      1U
#define ADC_INTEVT0CLR_TOVIFG_NO_EFFECT                              0x00000000U
#define ADC_INTEVT0CLR_TOVIFG_CLR                                    0x00000002U
/*

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_HIFG                                          0x00000004U
#define ADC_INTEVT0CLR_HIFG_M                                        0x00000004U
#define ADC_INTEVT0CLR_HIFG_S                                        2U
#define ADC_INTEVT0CLR_HIFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT0CLR_HIFG_CLR                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_LOFG                                          0x00000008U
#define ADC_INTEVT0CLR_LOFG_M                                        0x00000008U
#define ADC_INTEVT0CLR_LOFG_S                                        3U
#define ADC_INTEVT0CLR_LOFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT0CLR_LOFG_CLR                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_INIFG                                         0x00000010U
#define ADC_INTEVT0CLR_INIFG_M                                       0x00000010U
#define ADC_INTEVT0CLR_INIFG_S                                       4U
#define ADC_INTEVT0CLR_INIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0CLR_INIFG_CLR                                     0x00000010U
/*

        Field:           DMADONE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for DMADONE.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_DMADONE                                       0x00000020U
#define ADC_INTEVT0CLR_DMADONE_M                                     0x00000020U
#define ADC_INTEVT0CLR_DMADONE_S                                     5U
#define ADC_INTEVT0CLR_DMADONE_NO_EFFECT                             0x00000000U
#define ADC_INTEVT0CLR_DMADONE_CLR                                   0x00000020U
/*

        Field:           UVIFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt flag for MEMRESx underflow.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT0CLR_UVIFG                                         0x00000040U
#define ADC_INTEVT0CLR_UVIFG_M                                       0x00000040U
#define ADC_INTEVT0CLR_UVIFG_S                                       6U
#define ADC_INTEVT0CLR_UVIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT0CLR_UVIFG_CLR                                     0x00000040U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT0CLR_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT0CLR_MEMRESIFG0_S                                  8U
#define ADC_INTEVT0CLR_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG0_CLR                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT0CLR_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT0CLR_MEMRESIFG1_S                                  9U
#define ADC_INTEVT0CLR_MEMRESIFG1_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG1_CLR                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT0CLR_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT0CLR_MEMRESIFG2_S                                  10U
#define ADC_INTEVT0CLR_MEMRESIFG2_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG2_CLR                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT0CLR_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT0CLR_MEMRESIFG3_S                                  11U
#define ADC_INTEVT0CLR_MEMRESIFG3_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG3_CLR                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT0CLR_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT0CLR_MEMRESIFG4_S                                  12U
#define ADC_INTEVT0CLR_MEMRESIFG4_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG4_CLR                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT0CLR_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT0CLR_MEMRESIFG5_S                                  13U
#define ADC_INTEVT0CLR_MEMRESIFG5_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG5_CLR                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT0CLR_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT0CLR_MEMRESIFG6_S                                  14U
#define ADC_INTEVT0CLR_MEMRESIFG6_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG6_CLR                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT0CLR_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT0CLR_MEMRESIFG7_S                                  15U
#define ADC_INTEVT0CLR_MEMRESIFG7_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG7_CLR                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT0CLR_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT0CLR_MEMRESIFG8_S                                  16U
#define ADC_INTEVT0CLR_MEMRESIFG8_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG8_CLR                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT0CLR_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT0CLR_MEMRESIFG9_S                                  17U
#define ADC_INTEVT0CLR_MEMRESIFG9_NO_EFFECT                          0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG9_CLR                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT0CLR_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT0CLR_MEMRESIFG10_S                                 18U
#define ADC_INTEVT0CLR_MEMRESIFG10_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG10_CLR                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT0CLR_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT0CLR_MEMRESIFG11_S                                 19U
#define ADC_INTEVT0CLR_MEMRESIFG11_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG11_CLR                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT0CLR_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT0CLR_MEMRESIFG12_S                                 20U
#define ADC_INTEVT0CLR_MEMRESIFG12_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG12_CLR                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT0CLR_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT0CLR_MEMRESIFG13_S                                 21U
#define ADC_INTEVT0CLR_MEMRESIFG13_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG13_CLR                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT0CLR_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT0CLR_MEMRESIFG14_S                                 22U
#define ADC_INTEVT0CLR_MEMRESIFG14_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG14_CLR                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT0CLR_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT0CLR_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT0CLR_MEMRESIFG15_S                                 23U
#define ADC_INTEVT0CLR_MEMRESIFG15_NO_EFFECT                         0x00000000U
#define ADC_INTEVT0CLR_MEMRESIFG15_CLR                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1IDX
    Offset name:         ADC_O_INTEVT1IDX
    Relative address:    0x1050
    Description:         INTERNAL EVENT 1 IRQ IDX

                        This register provides the highest priority enabled interrupt index. 0x0 means no event pending. Interrupt 1 is the highest priority, 2 next highest, 4, 8, ... 2^31 is the least priority. That is, the least bit position that is set to 1 denotes the highest priority pending interrupt. The priority order is fixed. However, users can implement their own prioritization schemes using other registers that expose the full set of interrupts that have occurred.

                        On each read, only one interrupt is indicated. On a read, the current interrupt (highest priority) is automatically cleared by the hardware and the corresponding interrupt flag in the RIS and MIS are cleared as well. After a read from the CPU (not from the debug interface), the register must be updated with the next highest priority interrupt, if none are pending, then it should display 0x0.

    Default Value:       0x00000000

        Field:           STAT
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Interrupt index status

        ENUMs:
            NO_INTR:                     No bit is set means there is no pending interrupt request
            HIGHIFG:                     High threshold compare interrupt
            LOWIFG:                      Low threshold compare interrupt
            INIFG:                       Primary Sequence In range comparator interrupt
            MEMRESIFG0:                  MEMRES0 data loaded interrupt
*/
#define ADC_INTEVT1IDX_STAT_W                                        10U
#define ADC_INTEVT1IDX_STAT_M                                        0x000003FFU
#define ADC_INTEVT1IDX_STAT_S                                        0U
#define ADC_INTEVT1IDX_STAT_NO_INTR                                  0x00000000U
#define ADC_INTEVT1IDX_STAT_HIGHIFG                                  0x00000003U
#define ADC_INTEVT1IDX_STAT_LOWIFG                                   0x00000004U
#define ADC_INTEVT1IDX_STAT_INIFG                                    0x00000005U
#define ADC_INTEVT1IDX_STAT_MEMRESIFG0                               0x00000009U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1BM
    Offset name:         ADC_O_INTEVT1BM
    Relative address:    0x1058
    Description:         INTERNAL EVENT 1 IRQ MASK

                        Interrupt Mask. If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in IIDX, as well as MIS.
    Default Value:       0x00000000

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1BM_HIFG                                           0x00000004U
#define ADC_INTEVT1BM_HIFG_M                                         0x00000004U
#define ADC_INTEVT1BM_HIFG_S                                         2U
#define ADC_INTEVT1BM_HIFG_CLR                                       0x00000000U
#define ADC_INTEVT1BM_HIFG_SET                                       0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1BM_LOFG                                           0x00000008U
#define ADC_INTEVT1BM_LOFG_M                                         0x00000008U
#define ADC_INTEVT1BM_LOFG_S                                         3U
#define ADC_INTEVT1BM_LOFG_CLR                                       0x00000000U
#define ADC_INTEVT1BM_LOFG_SET                                       0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1BM_INIFG                                          0x00000010U
#define ADC_INTEVT1BM_INIFG_M                                        0x00000010U
#define ADC_INTEVT1BM_INIFG_S                                        4U
#define ADC_INTEVT1BM_INIFG_CLR                                      0x00000000U
#define ADC_INTEVT1BM_INIFG_SET                                      0x00000010U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT1BM_MEMRESIFG0                                     0x00000100U
#define ADC_INTEVT1BM_MEMRESIFG0_M                                   0x00000100U
#define ADC_INTEVT1BM_MEMRESIFG0_S                                   8U
#define ADC_INTEVT1BM_MEMRESIFG0_CLR                                 0x00000000U
#define ADC_INTEVT1BM_MEMRESIFG0_SET                                 0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1RIS
    Offset name:         ADC_O_INTEVT1RIS
    Relative address:    0x1060
    Description:         INTERNAL EVENT 1 RAW IRQ STATUS

                        Raw interrupt status. Reflects all pending interrupts, regardless of masking. The INT_EVENT1_RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1RIS_HIFG                                          0x00000004U
#define ADC_INTEVT1RIS_HIFG_M                                        0x00000004U
#define ADC_INTEVT1RIS_HIFG_S                                        2U
#define ADC_INTEVT1RIS_HIFG_CLR                                      0x00000000U
#define ADC_INTEVT1RIS_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1RIS_LOFG                                          0x00000008U
#define ADC_INTEVT1RIS_LOFG_M                                        0x00000008U
#define ADC_INTEVT1RIS_LOFG_S                                        3U
#define ADC_INTEVT1RIS_LOFG_CLR                                      0x00000000U
#define ADC_INTEVT1RIS_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1RIS_INIFG                                         0x00000010U
#define ADC_INTEVT1RIS_INIFG_M                                       0x00000010U
#define ADC_INTEVT1RIS_INIFG_S                                       4U
#define ADC_INTEVT1RIS_INIFG_CLR                                     0x00000000U
#define ADC_INTEVT1RIS_INIFG_SET                                     0x00000010U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT1RIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT1RIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT1RIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT1RIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT1RIS_MEMRESIFG0_SET                                0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1MIS
    Offset name:         ADC_O_INTEVT1MIS
    Relative address:    0x1068
    Description:         INTERNAL EVENT 1 MASKED IRQ STATUS

                        Masked interrupt status. This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1MIS_HIFG                                          0x00000004U
#define ADC_INTEVT1MIS_HIFG_M                                        0x00000004U
#define ADC_INTEVT1MIS_HIFG_S                                        2U
#define ADC_INTEVT1MIS_HIFG_CLR                                      0x00000000U
#define ADC_INTEVT1MIS_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1MIS_LOFG                                          0x00000008U
#define ADC_INTEVT1MIS_LOFG_M                                        0x00000008U
#define ADC_INTEVT1MIS_LOFG_S                                        3U
#define ADC_INTEVT1MIS_LOFG_CLR                                      0x00000000U
#define ADC_INTEVT1MIS_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            CLR:                         Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1MIS_INIFG                                         0x00000010U
#define ADC_INTEVT1MIS_INIFG_M                                       0x00000010U
#define ADC_INTEVT1MIS_INIFG_S                                       4U
#define ADC_INTEVT1MIS_INIFG_CLR                                     0x00000000U
#define ADC_INTEVT1MIS_INIFG_SET                                     0x00000010U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT1MIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT1MIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT1MIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT1MIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT1MIS_MEMRESIFG0_SET                                0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1SET
    Offset name:         ADC_O_INTEVT1SET
    Relative address:    0x1070
    Description:         INTERNAL EVENT 1 IRQ SET

                        Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in INT_EVENT1_ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1SET_HIFG                                          0x00000004U
#define ADC_INTEVT1SET_HIFG_M                                        0x00000004U
#define ADC_INTEVT1SET_HIFG_S                                        2U
#define ADC_INTEVT1SET_HIFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT1SET_HIFG_SET                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1SET_LOFG                                          0x00000008U
#define ADC_INTEVT1SET_LOFG_M                                        0x00000008U
#define ADC_INTEVT1SET_LOFG_S                                        3U
#define ADC_INTEVT1SET_LOFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT1SET_LOFG_SET                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            SET:                         Interrupt is pending.
*/
#define ADC_INTEVT1SET_INIFG                                         0x00000010U
#define ADC_INTEVT1SET_INIFG_M                                       0x00000010U
#define ADC_INTEVT1SET_INIFG_S                                       4U
#define ADC_INTEVT1SET_INIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT1SET_INIFG_SET                                     0x00000010U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT1SET_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT1SET_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT1SET_MEMRESIFG0_S                                  8U
#define ADC_INTEVT1SET_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT1SET_MEMRESIFG0_SET                                0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT1CLR
    Offset name:         ADC_O_INTEVT1CLR
    Relative address:    0x1078
    Description:         INTERNAL EVENT 1 IRQ CLEAR

                        Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           HIFG
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HIGH FG

                         Raw interrupt flag for the MEMRESx result register being higher
                         than the WCHIGHx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT1CLR_HIFG                                          0x00000004U
#define ADC_INTEVT1CLR_HIFG_M                                        0x00000004U
#define ADC_INTEVT1CLR_HIFG_S                                        2U
#define ADC_INTEVT1CLR_HIFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT1CLR_HIFG_CLR                                      0x00000004U
/*

        Field:           LOFG
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     LOW FG

                         Raw interrupt flag for the MEMRESx result register being below
                         than the WCLOWx threshold of the window comparator.
                         This bit is reset to 0 by IIDX read or when corresponding bit in
                         ICLR_EX is set to 1.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT1CLR_LOFG                                          0x00000008U
#define ADC_INTEVT1CLR_LOFG_M                                        0x00000008U
#define ADC_INTEVT1CLR_LOFG_S                                        3U
#define ADC_INTEVT1CLR_LOFG_NO_EFFECT                                0x00000000U
#define ADC_INTEVT1CLR_LOFG_CLR                                      0x00000008U
/*

        Field:           INIFG
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Mask INIFG in MIS_EX register.

        ENUMs:
            NO_EFFECT:                   Interrupt is not pending.
            CLR:                         Interrupt is pending.
*/
#define ADC_INTEVT1CLR_INIFG                                         0x00000010U
#define ADC_INTEVT1CLR_INIFG_M                                       0x00000010U
#define ADC_INTEVT1CLR_INIFG_S                                       4U
#define ADC_INTEVT1CLR_INIFG_NO_EFFECT                               0x00000000U
#define ADC_INTEVT1CLR_INIFG_CLR                                     0x00000010U
/*

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT1CLR_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT1CLR_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT1CLR_MEMRESIFG0_S                                  8U
#define ADC_INTEVT1CLR_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT1CLR_MEMRESIFG0_CLR                                0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2IDX
    Offset name:         ADC_O_INTEVT2IDX
    Relative address:    0x1080
    Description:         INTERNAL EVENT 2 IRQ IDX

                        This register provides the highest priority enabled interrupt index. 0x0 means no event pending. Interrupt 1 is the highest priority, 2 next highest, 4, 8, ... 2^31 is the least priority. That is, the least bit position that is set to 1 denotes the highest priority pending interrupt. The priority order is fixed. However, users can implement their own prioritization schemes using other registers that expose the full set of interrupts that have occurred.

                        On each read, only one interrupt is indicated. On a read, the current interrupt (highest priority) is automatically cleared by the hardware and the corresponding interrupt flag in the RIS and MIS are cleared as well. After a read from the CPU (not from the debug interface), the register must be updated with the next highest priority interrupt, if none are pending, then it should display 0x0.

    Default Value:       0x00000000

        Field:           STAT
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Interrupt index status

        ENUMs:
            NO_INTR:                     No bit is set means there is no pending interrupt request
            MEMRESIFG0:                  MEMRES0 data loaded interrupt
            MEMRESIFG1:                  MEMRES1 data loaded interrupt
            MEMRESIFG2:                  MEMRES2 data loaded interrupt
            MEMRESIFG3:                  MEMRES3 data loaded interrupt
            MEMRESIFG4:                  MEMRES4 data loaded interrupt
            MEMRESIFG5:                  MEMRES5 data loaded interrupt
            MEMRESIFG6:                  MEMRES6 data loaded interrupt
            MEMRESIFG7:                  MEMRES7 data loaded interrupt
            MEMRESIFG8:                  MEMRES8 data loaded interrupt
            MEMRESIFG9:                  MEMRES9 data  loaded interrupt
            MEMRESIFG10:                 MEMRES10 data  loaded interrupt
            MEMRESIFG11:                 MEMRES11 data  loaded interrupt
            MEMRESIFG12:                 MEMRES12 data  loaded interrupt
            MEMRESIFG13:                 MEMRES13 data  loaded interrupt
            MEMRESIFG14:                 MEMRES14 data  loaded interrupt
            MEMRESIFG15:                 MEMRES15 data  loaded interrupt
            MEMRESIFG16:                 MEMRES16 data loaded interrupt
            MEMRESIFG17:                 MEMRES17 data loaded interrupt
            MEMRESIFG18:                 MEMRES18 data loaded interrupt
            MEMRESIFG19:                 MEMRES19 data loaded interrupt
            MEMRESIFG20:                 MEMRES20 data loaded interrupt
            MEMRESIFG21:                 MEMRES21 data loaded interrupt
            MEMRESIFG22:                 MEMRES22 data loaded interrupt
            MEMRESIFG23:                 MEMRES23 data loaded interrupt
*/
#define ADC_INTEVT2IDX_STAT_W                                        10U
#define ADC_INTEVT2IDX_STAT_M                                        0x000003FFU
#define ADC_INTEVT2IDX_STAT_S                                        0U
#define ADC_INTEVT2IDX_STAT_NO_INTR                                  0x00000000U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG0                               0x00000009U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG1                               0x0000000AU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG2                               0x0000000BU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG3                               0x0000000CU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG4                               0x0000000DU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG5                               0x0000000EU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG6                               0x0000000FU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG7                               0x00000010U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG8                               0x00000011U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG9                               0x00000012U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG10                              0x00000013U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG11                              0x00000014U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG12                              0x00000015U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG13                              0x00000016U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG14                              0x00000017U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG15                              0x00000018U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG16                              0x00000019U
#define ADC_INTEVT2IDX_STAT_MEMRESIFG17                              0x0000001AU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG18                              0x0000001BU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG19                              0x0000001CU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG20                              0x0000001DU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG21                              0x0000001EU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG22                              0x0000001FU
#define ADC_INTEVT2IDX_STAT_MEMRESIFG23                              0x00000020U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2BM
    Offset name:         ADC_O_INTEVT2BM
    Relative address:    0x1088
    Description:         INTERNAL EVENT 2 IRQ MASK

                        Interrupt Mask. If a bit is set, then corresponding interrupt is un-masked. Un-masking the interrupt causes the raw interrupt to be visible in IIDX, as well as MIS.
    Default Value:       0x00000000

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG0                                     0x00000100U
#define ADC_INTEVT2BM_MEMRESIFG0_M                                   0x00000100U
#define ADC_INTEVT2BM_MEMRESIFG0_S                                   8U
#define ADC_INTEVT2BM_MEMRESIFG0_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG0_SET                                 0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG1                                     0x00000200U
#define ADC_INTEVT2BM_MEMRESIFG1_M                                   0x00000200U
#define ADC_INTEVT2BM_MEMRESIFG1_S                                   9U
#define ADC_INTEVT2BM_MEMRESIFG1_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG1_SET                                 0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG2                                     0x00000400U
#define ADC_INTEVT2BM_MEMRESIFG2_M                                   0x00000400U
#define ADC_INTEVT2BM_MEMRESIFG2_S                                   10U
#define ADC_INTEVT2BM_MEMRESIFG2_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG2_SET                                 0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG3                                     0x00000800U
#define ADC_INTEVT2BM_MEMRESIFG3_M                                   0x00000800U
#define ADC_INTEVT2BM_MEMRESIFG3_S                                   11U
#define ADC_INTEVT2BM_MEMRESIFG3_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG3_SET                                 0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG4                                     0x00001000U
#define ADC_INTEVT2BM_MEMRESIFG4_M                                   0x00001000U
#define ADC_INTEVT2BM_MEMRESIFG4_S                                   12U
#define ADC_INTEVT2BM_MEMRESIFG4_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG4_SET                                 0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG5                                     0x00002000U
#define ADC_INTEVT2BM_MEMRESIFG5_M                                   0x00002000U
#define ADC_INTEVT2BM_MEMRESIFG5_S                                   13U
#define ADC_INTEVT2BM_MEMRESIFG5_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG5_SET                                 0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG6                                     0x00004000U
#define ADC_INTEVT2BM_MEMRESIFG6_M                                   0x00004000U
#define ADC_INTEVT2BM_MEMRESIFG6_S                                   14U
#define ADC_INTEVT2BM_MEMRESIFG6_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG6_SET                                 0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG7                                     0x00008000U
#define ADC_INTEVT2BM_MEMRESIFG7_M                                   0x00008000U
#define ADC_INTEVT2BM_MEMRESIFG7_S                                   15U
#define ADC_INTEVT2BM_MEMRESIFG7_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG7_SET                                 0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG8                                     0x00010000U
#define ADC_INTEVT2BM_MEMRESIFG8_M                                   0x00010000U
#define ADC_INTEVT2BM_MEMRESIFG8_S                                   16U
#define ADC_INTEVT2BM_MEMRESIFG8_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG8_SET                                 0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG9                                     0x00020000U
#define ADC_INTEVT2BM_MEMRESIFG9_M                                   0x00020000U
#define ADC_INTEVT2BM_MEMRESIFG9_S                                   17U
#define ADC_INTEVT2BM_MEMRESIFG9_CLR                                 0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG9_SET                                 0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG10                                    0x00040000U
#define ADC_INTEVT2BM_MEMRESIFG10_M                                  0x00040000U
#define ADC_INTEVT2BM_MEMRESIFG10_S                                  18U
#define ADC_INTEVT2BM_MEMRESIFG10_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG10_SET                                0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG11                                    0x00080000U
#define ADC_INTEVT2BM_MEMRESIFG11_M                                  0x00080000U
#define ADC_INTEVT2BM_MEMRESIFG11_S                                  19U
#define ADC_INTEVT2BM_MEMRESIFG11_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG11_SET                                0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG12                                    0x00100000U
#define ADC_INTEVT2BM_MEMRESIFG12_M                                  0x00100000U
#define ADC_INTEVT2BM_MEMRESIFG12_S                                  20U
#define ADC_INTEVT2BM_MEMRESIFG12_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG12_SET                                0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG13                                    0x00200000U
#define ADC_INTEVT2BM_MEMRESIFG13_M                                  0x00200000U
#define ADC_INTEVT2BM_MEMRESIFG13_S                                  21U
#define ADC_INTEVT2BM_MEMRESIFG13_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG13_SET                                0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG14                                    0x00400000U
#define ADC_INTEVT2BM_MEMRESIFG14_M                                  0x00400000U
#define ADC_INTEVT2BM_MEMRESIFG14_S                                  22U
#define ADC_INTEVT2BM_MEMRESIFG14_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG14_SET                                0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2BM_MEMRESIFG15                                    0x00800000U
#define ADC_INTEVT2BM_MEMRESIFG15_M                                  0x00800000U
#define ADC_INTEVT2BM_MEMRESIFG15_S                                  23U
#define ADC_INTEVT2BM_MEMRESIFG15_CLR                                0x00000000U
#define ADC_INTEVT2BM_MEMRESIFG15_SET                                0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2RIS
    Offset name:         ADC_O_INTEVT2RIS
    Relative address:    0x1090
    Description:         INTERNAL EVENT 2 RAW IRQ STATUS

                        Raw interrupt status. Reflects all pending interrupts, regardless of masking. The INT_EVENT2_RIS register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the ICLR register bit even if the corresponding IMASK bit is not enabled.
    Default Value:       0x00000000

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT2RIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT2RIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT2RIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT2RIS_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT2RIS_MEMRESIFG1_S                                  9U
#define ADC_INTEVT2RIS_MEMRESIFG1_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT2RIS_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT2RIS_MEMRESIFG2_S                                  10U
#define ADC_INTEVT2RIS_MEMRESIFG2_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT2RIS_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT2RIS_MEMRESIFG3_S                                  11U
#define ADC_INTEVT2RIS_MEMRESIFG3_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT2RIS_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT2RIS_MEMRESIFG4_S                                  12U
#define ADC_INTEVT2RIS_MEMRESIFG4_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT2RIS_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT2RIS_MEMRESIFG5_S                                  13U
#define ADC_INTEVT2RIS_MEMRESIFG5_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT2RIS_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT2RIS_MEMRESIFG6_S                                  14U
#define ADC_INTEVT2RIS_MEMRESIFG6_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT2RIS_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT2RIS_MEMRESIFG7_S                                  15U
#define ADC_INTEVT2RIS_MEMRESIFG7_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT2RIS_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT2RIS_MEMRESIFG8_S                                  16U
#define ADC_INTEVT2RIS_MEMRESIFG8_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT2RIS_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT2RIS_MEMRESIFG9_S                                  17U
#define ADC_INTEVT2RIS_MEMRESIFG9_CLR                                0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT2RIS_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT2RIS_MEMRESIFG10_S                                 18U
#define ADC_INTEVT2RIS_MEMRESIFG10_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT2RIS_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT2RIS_MEMRESIFG11_S                                 19U
#define ADC_INTEVT2RIS_MEMRESIFG11_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT2RIS_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT2RIS_MEMRESIFG12_S                                 20U
#define ADC_INTEVT2RIS_MEMRESIFG12_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT2RIS_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT2RIS_MEMRESIFG13_S                                 21U
#define ADC_INTEVT2RIS_MEMRESIFG13_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT2RIS_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT2RIS_MEMRESIFG14_S                                 22U
#define ADC_INTEVT2RIS_MEMRESIFG14_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2RIS_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT2RIS_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT2RIS_MEMRESIFG15_S                                 23U
#define ADC_INTEVT2RIS_MEMRESIFG15_CLR                               0x00000000U
#define ADC_INTEVT2RIS_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2MIS
    Offset name:         ADC_O_INTEVT2MIS
    Relative address:    0x1098
    Description:         INTERNAL EVENT 2 MASKED IRQ STATUS

                        Extension of Masked interrupt status. This is an AND of the IMASK and RIS registers.
    Default Value:       0x00000000

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT2MIS_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT2MIS_MEMRESIFG0_S                                  8U
#define ADC_INTEVT2MIS_MEMRESIFG0_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT2MIS_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT2MIS_MEMRESIFG1_S                                  9U
#define ADC_INTEVT2MIS_MEMRESIFG1_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT2MIS_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT2MIS_MEMRESIFG2_S                                  10U
#define ADC_INTEVT2MIS_MEMRESIFG2_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT2MIS_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT2MIS_MEMRESIFG3_S                                  11U
#define ADC_INTEVT2MIS_MEMRESIFG3_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT2MIS_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT2MIS_MEMRESIFG4_S                                  12U
#define ADC_INTEVT2MIS_MEMRESIFG4_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT2MIS_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT2MIS_MEMRESIFG5_S                                  13U
#define ADC_INTEVT2MIS_MEMRESIFG5_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT2MIS_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT2MIS_MEMRESIFG6_S                                  14U
#define ADC_INTEVT2MIS_MEMRESIFG6_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT2MIS_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT2MIS_MEMRESIFG7_S                                  15U
#define ADC_INTEVT2MIS_MEMRESIFG7_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT2MIS_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT2MIS_MEMRESIFG8_S                                  16U
#define ADC_INTEVT2MIS_MEMRESIFG8_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT2MIS_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT2MIS_MEMRESIFG9_S                                  17U
#define ADC_INTEVT2MIS_MEMRESIFG9_CLR                                0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT2MIS_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT2MIS_MEMRESIFG10_S                                 18U
#define ADC_INTEVT2MIS_MEMRESIFG10_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT2MIS_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT2MIS_MEMRESIFG11_S                                 19U
#define ADC_INTEVT2MIS_MEMRESIFG11_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT2MIS_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT2MIS_MEMRESIFG12_S                                 20U
#define ADC_INTEVT2MIS_MEMRESIFG12_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT2MIS_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT2MIS_MEMRESIFG13_S                                 21U
#define ADC_INTEVT2MIS_MEMRESIFG13_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT2MIS_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT2MIS_MEMRESIFG14_S                                 22U
#define ADC_INTEVT2MIS_MEMRESIFG14_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            CLR:                         No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2MIS_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT2MIS_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT2MIS_MEMRESIFG15_S                                 23U
#define ADC_INTEVT2MIS_MEMRESIFG15_CLR                               0x00000000U
#define ADC_INTEVT2MIS_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2SET
    Offset name:         ADC_O_INTEVT2SET
    Relative address:    0x10A0
    Description:         INTERNAL EVENT 2 IRQ SET

                        Interrupt set. Allows interrupts to be set by software (useful in diagnostics and safety checks). Writing a 1 to a bit in INT_EVENT2_ISET will set the event and therefore the related RIS bit also gets set. If the interrupt is enabled through the mask, then the corresponding MIS bit is also set.
    Default Value:       0x00000000

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT2SET_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT2SET_MEMRESIFG0_S                                  8U
#define ADC_INTEVT2SET_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG0_SET                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT2SET_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT2SET_MEMRESIFG1_S                                  9U
#define ADC_INTEVT2SET_MEMRESIFG1_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG1_SET                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT2SET_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT2SET_MEMRESIFG2_S                                  10U
#define ADC_INTEVT2SET_MEMRESIFG2_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG2_SET                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT2SET_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT2SET_MEMRESIFG3_S                                  11U
#define ADC_INTEVT2SET_MEMRESIFG3_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG3_SET                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT2SET_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT2SET_MEMRESIFG4_S                                  12U
#define ADC_INTEVT2SET_MEMRESIFG4_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG4_SET                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT2SET_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT2SET_MEMRESIFG5_S                                  13U
#define ADC_INTEVT2SET_MEMRESIFG5_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG5_SET                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT2SET_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT2SET_MEMRESIFG6_S                                  14U
#define ADC_INTEVT2SET_MEMRESIFG6_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG6_SET                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT2SET_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT2SET_MEMRESIFG7_S                                  15U
#define ADC_INTEVT2SET_MEMRESIFG7_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG7_SET                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT2SET_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT2SET_MEMRESIFG8_S                                  16U
#define ADC_INTEVT2SET_MEMRESIFG8_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG8_SET                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT2SET_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT2SET_MEMRESIFG9_S                                  17U
#define ADC_INTEVT2SET_MEMRESIFG9_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG9_SET                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT2SET_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT2SET_MEMRESIFG10_S                                 18U
#define ADC_INTEVT2SET_MEMRESIFG10_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG10_SET                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT2SET_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT2SET_MEMRESIFG11_S                                 19U
#define ADC_INTEVT2SET_MEMRESIFG11_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG11_SET                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT2SET_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT2SET_MEMRESIFG12_S                                 20U
#define ADC_INTEVT2SET_MEMRESIFG12_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG12_SET                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT2SET_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT2SET_MEMRESIFG13_S                                 21U
#define ADC_INTEVT2SET_MEMRESIFG13_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG13_SET                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT2SET_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT2SET_MEMRESIFG14_S                                 22U
#define ADC_INTEVT2SET_MEMRESIFG14_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG14_SET                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            SET:                         A new data is ready to be read.
*/
#define ADC_INTEVT2SET_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT2SET_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT2SET_MEMRESIFG15_S                                 23U
#define ADC_INTEVT2SET_MEMRESIFG15_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2SET_MEMRESIFG15_SET                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTEVT2CLR
    Offset name:         ADC_O_INTEVT2CLR
    Relative address:    0x10A8
    Description:         INTERNAL EVENT 2 IRQ CLEAR

                        Interrupt clear. Write a 1 to clear corresponding Interrupt.
    Default Value:       0x00000000

        Field:           MEMRESIFG0
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES0.
                         This bit is set to 1 when MEMRES0 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG0                                    0x00000100U
#define ADC_INTEVT2CLR_MEMRESIFG0_M                                  0x00000100U
#define ADC_INTEVT2CLR_MEMRESIFG0_S                                  8U
#define ADC_INTEVT2CLR_MEMRESIFG0_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG0_CLR                                0x00000100U
/*

        Field:           MEMRESIFG1
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES1.
                         This bit is set to 1 when MEMRES1 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG1                                    0x00000200U
#define ADC_INTEVT2CLR_MEMRESIFG1_M                                  0x00000200U
#define ADC_INTEVT2CLR_MEMRESIFG1_S                                  9U
#define ADC_INTEVT2CLR_MEMRESIFG1_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG1_CLR                                0x00000200U
/*

        Field:           MEMRESIFG2
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES2.
                         This bit is set to 1 when MEMRES2 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG2                                    0x00000400U
#define ADC_INTEVT2CLR_MEMRESIFG2_M                                  0x00000400U
#define ADC_INTEVT2CLR_MEMRESIFG2_S                                  10U
#define ADC_INTEVT2CLR_MEMRESIFG2_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG2_CLR                                0x00000400U
/*

        Field:           MEMRESIFG3
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES3.
                         This bit is set to 1 when MEMRES3 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG3                                    0x00000800U
#define ADC_INTEVT2CLR_MEMRESIFG3_M                                  0x00000800U
#define ADC_INTEVT2CLR_MEMRESIFG3_S                                  11U
#define ADC_INTEVT2CLR_MEMRESIFG3_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG3_CLR                                0x00000800U
/*

        Field:           MEMRESIFG4
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES4.
                         This bit is set to 1 when MEMRES4 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG4                                    0x00001000U
#define ADC_INTEVT2CLR_MEMRESIFG4_M                                  0x00001000U
#define ADC_INTEVT2CLR_MEMRESIFG4_S                                  12U
#define ADC_INTEVT2CLR_MEMRESIFG4_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG4_CLR                                0x00001000U
/*

        Field:           MEMRESIFG5
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES5.
                         This bit is set to 1 when MEMRES5 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG5                                    0x00002000U
#define ADC_INTEVT2CLR_MEMRESIFG5_M                                  0x00002000U
#define ADC_INTEVT2CLR_MEMRESIFG5_S                                  13U
#define ADC_INTEVT2CLR_MEMRESIFG5_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG5_CLR                                0x00002000U
/*

        Field:           MEMRESIFG6
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES6.
                         This bit is set to 1 when MEMRES6 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG6                                    0x00004000U
#define ADC_INTEVT2CLR_MEMRESIFG6_M                                  0x00004000U
#define ADC_INTEVT2CLR_MEMRESIFG6_S                                  14U
#define ADC_INTEVT2CLR_MEMRESIFG6_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG6_CLR                                0x00004000U
/*

        Field:           MEMRESIFG7
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES7.
                         This bit is set to 1 when MEMRES7 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG7                                    0x00008000U
#define ADC_INTEVT2CLR_MEMRESIFG7_M                                  0x00008000U
#define ADC_INTEVT2CLR_MEMRESIFG7_S                                  15U
#define ADC_INTEVT2CLR_MEMRESIFG7_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG7_CLR                                0x00008000U
/*

        Field:           MEMRESIFG8
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES8.
                         This bit is set to 1 when MEMRES8 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG8                                    0x00010000U
#define ADC_INTEVT2CLR_MEMRESIFG8_M                                  0x00010000U
#define ADC_INTEVT2CLR_MEMRESIFG8_S                                  16U
#define ADC_INTEVT2CLR_MEMRESIFG8_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG8_CLR                                0x00010000U
/*

        Field:           MEMRESIFG9
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES9.
                         This bit is set to 1 when MEMRES9 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG9                                    0x00020000U
#define ADC_INTEVT2CLR_MEMRESIFG9_M                                  0x00020000U
#define ADC_INTEVT2CLR_MEMRESIFG9_S                                  17U
#define ADC_INTEVT2CLR_MEMRESIFG9_NO_EFFECT                          0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG9_CLR                                0x00020000U
/*

        Field:           MEMRESIFG10
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES10.
                         This bit is set to 1 when MEMRES10 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG10                                   0x00040000U
#define ADC_INTEVT2CLR_MEMRESIFG10_M                                 0x00040000U
#define ADC_INTEVT2CLR_MEMRESIFG10_S                                 18U
#define ADC_INTEVT2CLR_MEMRESIFG10_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG10_CLR                               0x00040000U
/*

        Field:           MEMRESIFG11
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES11.
                         This bit is set to 1 when MEMRES11 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG11                                   0x00080000U
#define ADC_INTEVT2CLR_MEMRESIFG11_M                                 0x00080000U
#define ADC_INTEVT2CLR_MEMRESIFG11_S                                 19U
#define ADC_INTEVT2CLR_MEMRESIFG11_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG11_CLR                               0x00080000U
/*

        Field:           MEMRESIFG12
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES12.
                         This bit is set to 1 when MEMRES12 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG12                                   0x00100000U
#define ADC_INTEVT2CLR_MEMRESIFG12_M                                 0x00100000U
#define ADC_INTEVT2CLR_MEMRESIFG12_S                                 20U
#define ADC_INTEVT2CLR_MEMRESIFG12_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG12_CLR                               0x00100000U
/*

        Field:           MEMRESIFG13
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES13.
                         This bit is set to 1 when MEMRES13 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG13                                   0x00200000U
#define ADC_INTEVT2CLR_MEMRESIFG13_M                                 0x00200000U
#define ADC_INTEVT2CLR_MEMRESIFG13_S                                 21U
#define ADC_INTEVT2CLR_MEMRESIFG13_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG13_CLR                               0x00200000U
/*

        Field:           MEMRESIFG14
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES14.
                         This bit is set to 1 when MEMRES14 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG14                                   0x00400000U
#define ADC_INTEVT2CLR_MEMRESIFG14_M                                 0x00400000U
#define ADC_INTEVT2CLR_MEMRESIFG14_S                                 22U
#define ADC_INTEVT2CLR_MEMRESIFG14_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG14_CLR                               0x00400000U
/*

        Field:           MEMRESIFG15
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Raw interrupt status for MEMRES15.
                         This bit is set to 1 when MEMRES15 is loaded with a new
                         conversion result.
                         To clear this bit, corresponding bit in ICLR should be set to 1

        ENUMs:
            NO_EFFECT:                   No new data ready.
            CLR:                         A new data is ready to be read.
*/
#define ADC_INTEVT2CLR_MEMRESIFG15                                   0x00800000U
#define ADC_INTEVT2CLR_MEMRESIFG15_M                                 0x00800000U
#define ADC_INTEVT2CLR_MEMRESIFG15_S                                 23U
#define ADC_INTEVT2CLR_MEMRESIFG15_NO_EFFECT                         0x00000000U
#define ADC_INTEVT2CLR_MEMRESIFG15_CLR                               0x00800000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EVTMOD
    Offset name:         ADC_O_EVTMOD
    Relative address:    0x10E0
    Description:         EVENT MODE

                        Event mode register. It is used to select whether each line is disabled, in software mode (software clears the RIS) or in hardware mode (hardware clears the RIS)
    Default Value:       0x00000001

        Field:           INT0CFG
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     INTERNAL 0 CONFIG

                         Event line mode select for event corresponding to [IPSTANDARD.INT_EVENT0]

        ENUMs:
            DISABLE:                     The interrupt or event line is disabled.
            SOFTWARE:                    The interrupt or event line is in software mode. Software must clear the RIS.
            HARDWARE:                    The interrupt or event line is in hardware mode. The hardware (another module) clears automatically the associated RIS flag.
*/
#define ADC_EVTMOD_INT0CFG_W                                         2U
#define ADC_EVTMOD_INT0CFG_M                                         0x00000003U
#define ADC_EVTMOD_INT0CFG_S                                         0U
#define ADC_EVTMOD_INT0CFG_DISABLE                                   0x00000000U
#define ADC_EVTMOD_INT0CFG_SOFTWARE                                  0x00000001U
#define ADC_EVTMOD_INT0CFG_HARDWARE                                  0x00000002U
/*

        Field:           EVT1CFG
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     EVENT 1 CONFIG

                         Event line mode select for event corresponding to [IPSTANDARD.INT_EVENT1]

        ENUMs:
            DISABLE:                     The interrupt or event line is disabled.
            SOFTWARE:                    The interrupt or event line is in software mode. Software must clear the RIS.
            HARDWARE:                    The interrupt or event line is in hardware mode. The hardware (another module) clears automatically the associated RIS flag.
*/
#define ADC_EVTMOD_EVT1CFG_W                                         2U
#define ADC_EVTMOD_EVT1CFG_M                                         0x0000000CU
#define ADC_EVTMOD_EVT1CFG_S                                         2U
#define ADC_EVTMOD_EVT1CFG_DISABLE                                   0x00000000U
#define ADC_EVTMOD_EVT1CFG_SOFTWARE                                  0x00000004U
#define ADC_EVTMOD_EVT1CFG_HARDWARE                                  0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         ADC_O_DESC
    Relative address:    0x10FC
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
#define ADC_DESC_MINREV_W                                            4U
#define ADC_DESC_MINREV_M                                            0x0000000FU
#define ADC_DESC_MINREV_S                                            0U
#define ADC_DESC_MINREV_MINIMUM                                      0x00000000U
#define ADC_DESC_MINREV_MAXIMUM                                      0x0000000FU
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
#define ADC_DESC_MAJREV_W                                            4U
#define ADC_DESC_MAJREV_M                                            0x000000F0U
#define ADC_DESC_MAJREV_S                                            4U
#define ADC_DESC_MAJREV_MINIMUM                                      0x00000000U
#define ADC_DESC_MAJREV_MAXIMUM                                      0x000000F0U
/*

        Field:           INSTNUM
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Instance Number within the device. This will be a parameter to the RTL for modules that can have multiple instances

*/
#define ADC_DESC_INSTNUM_W                                           4U
#define ADC_DESC_INSTNUM_M                                           0x00000F00U
#define ADC_DESC_INSTNUM_S                                           8U
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
#define ADC_DESC_FEATUREVER_W                                        4U
#define ADC_DESC_FEATUREVER_M                                        0x0000F000U
#define ADC_DESC_FEATUREVER_S                                        12U
#define ADC_DESC_FEATUREVER_MINIMUM                                  0x00000000U
#define ADC_DESC_FEATUREVER_MAXIMUM                                  0x0000F000U
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
#define ADC_DESC_MODULEID_W                                          16U
#define ADC_DESC_MODULEID_M                                          0xFFFF0000U
#define ADC_DESC_MODULEID_S                                          16U
#define ADC_DESC_MODULEID_MINIMUM                                    0x00000000U
#define ADC_DESC_MODULEID_MAXIMUM                                    0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL0
    Offset name:         ADC_O_CTL0
    Relative address:    0x1100
    Description:         ULP_ADCHP Control Register 0
    Default Value:       0x00000000

        Field:           ENC
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Enable Conversions.

        ENUMs:
            OFF:                         ULP_ADCHP primary sequencer is off
                         Transition from ON to OFF will abort the primary single or repeat sequence on a MEMCTLx boundary. (The current conversion will finish and result stored in corresponding MEMRESx)
            ON:                          ULP_ADCHP primary sequencer is ON.
                         Waiting for valid trigger (Software or Hardware)
*/
#define ADC_CTL0_ENC                                                 0x00000001U
#define ADC_CTL0_ENC_M                                               0x00000001U
#define ADC_CTL0_ENC_S                                               0U
#define ADC_CTL0_ENC_OFF                                             0x00000000U
#define ADC_CTL0_ENC_ON                                              0x00000001U
/*

        Field:           PWRDN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto or manual power down mode.

        ENUMs:
            AUTO:                        ADC is powered down on completion of a conversion, if there isn't a pending trigger.
            MANUAL:                      ADC is kept powered up as long as ADCEN bit is set.
*/
#define ADC_CTL0_PWRDN                                               0x00010000U
#define ADC_CTL0_PWRDN_M                                             0x00010000U
#define ADC_CTL0_PWRDN_S                                             16U
#define ADC_CTL0_PWRDN_AUTO                                          0x00000000U
#define ADC_CTL0_PWRDN_MANUAL                                        0x00010000U
/*

        Field:           SCLKDIV
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     NU - should keep as '0'.

                         Selects divide ratio of of sample clock.

        ENUMs:
            DIV_BY_1:                    Do not divide clock source
            DIV_BY_2:                    Divide clock source by 2
            DIV_BY_4:                    Divide clock source by 3
            DIV_BY_8:                    Divide clock source by 4
            DIV_BY_16:                   Divide clock source by 5
            DIV_BY_24:                   Divide clock source by 6
            DIV_BY_32:                   Divide clock source by 7
            DIV_BY_48:                   Divide clock source by 8
*/
#define ADC_CTL0_SCLKDIV_W                                           3U
#define ADC_CTL0_SCLKDIV_M                                           0x07000000U
#define ADC_CTL0_SCLKDIV_S                                           24U
#define ADC_CTL0_SCLKDIV_DIV_BY_1                                    0x00000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_2                                    0x01000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_4                                    0x02000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_8                                    0x03000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_16                                   0x04000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_24                                   0x05000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_32                                   0x06000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_48                                   0x07000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL1
    Offset name:         ADC_O_CTL1
    Relative address:    0x1104
    Description:         Primary Sequence Control Register
    Default Value:       0x00000000

        Field:           TRIGSRC
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP  Primary Sequence Trigger Source.

        ENUMs:
            SOFTWARE:                    Primary sequence or single conversion is triggered by software.


            EVENT:                       Primary sequence or single conversion is triggered by hardware event_0.
                         (See device specific data-sheet for source for availability of this trigger)
*/
#define ADC_CTL1_TRIGSRC                                             0x00000001U
#define ADC_CTL1_TRIGSRC_M                                           0x00000001U
#define ADC_CTL1_TRIGSRC_S                                           0U
#define ADC_CTL1_TRIGSRC_SOFTWARE                                    0x00000000U
#define ADC_CTL1_TRIGSRC_EVENT                                       0x00000001U
/*

        Field:           SC
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Sequencer Start Of Conversion.
                         If ULP_ADCHP is configured as FOLLOWER, this bit has no effect.

        ENUMs:
            START:                       When PSAMPMODE is set to MANUAL (1), setting this bit, will start the sampling phase. Sample phase will last as long as this bit is set.
                         When PSAMPMODE is set to AUTO mode (0), setting this bit will trigger the timer based sample time.
            STOP:                        When PSAMPMODE is set to MANUAL (1) mode, clearing this bit will end the sampling phase and the conversion phase will start.
                         When PSAMPMODE is set to AUTO mode (0), writing 0 has no effect.
                         This bit is automatically cleared at the end of the current  conversion.
*/
#define ADC_CTL1_SC                                                  0x00000100U
#define ADC_CTL1_SC_M                                                0x00000100U
#define ADC_CTL1_SC_S                                                8U
#define ADC_CTL1_SC_START                                            0x00000100U
#define ADC_CTL1_SC_STOP                                             0x00000000U
/*

        Field:           CONSEQ
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Primary Sequencer Conversion Sequence Mode Select.

        ENUMs:
            SINGLE:                      The MEMCTLx pointed by PSTARTADD will be converted once.
            SEQUENCE:                    The primary sequence pointed by PSTARTADD will be converted once.
            REPEATSINGLE:                The MEMCTLx pointed by PSTARTADD will be converted in repeat mode.
            REPEATSEQUENCE:              Primary sequence pointed by PSTARTADD will be converted in repeat mode.
*/
#define ADC_CTL1_CONSEQ_W                                            2U
#define ADC_CTL1_CONSEQ_M                                            0x00030000U
#define ADC_CTL1_CONSEQ_S                                            16U
#define ADC_CTL1_CONSEQ_SINGLE                                       0x00000000U
#define ADC_CTL1_CONSEQ_SEQUENCE                                     0x00010000U
#define ADC_CTL1_CONSEQ_REPEATSINGLE                                 0x00020000U
#define ADC_CTL1_CONSEQ_REPEATSEQUENCE                               0x00030000U
/*

        Field:           SAMPMODE
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Primary Sequencer Sample Mode.
                         This bit select the source of the sampling signal.

        ENUMs:
            AUTO:                        The sample timer high phase is used as sample signal.
            MANUAL:                      The external or software trigger is used as sample signal.
*/
#define ADC_CTL1_SAMPMODE                                            0x00100000U
#define ADC_CTL1_SAMPMODE_M                                          0x00100000U
#define ADC_CTL1_SAMPMODE_S                                          20U
#define ADC_CTL1_SAMPMODE_AUTO                                       0x00000000U
#define ADC_CTL1_SAMPMODE_MANUAL                                     0x00100000U
/*

        Field:           AVGN
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Hardware averager numerator. Selects number of conversions to accumulate for current MEMCTLx and then is get divided by AVGD. Result will be stored in MEMRESx.

        ENUMs:
            DISABLE:                     Disables averager.
            AVG_2:                       Averages 2 conversions before storing in MEMRES register.
            AVG_4:                       Averages 4 conversions before storing in MEMRES register.
            AVG_8:                       Averages 8 conversions before storing in MEMRES register.
            AVG_16:                      Averages 16 conversions before storing in MEMRES register.
            AVG_32:                      Averages 32 conversions before storing in MEMRES register.
            AVG_64:                      Averages 64 conversions before storing in MEMRES register.
            AVG_128:                     Averages 128 conversions before storing in MEMRES register.
*/
#define ADC_CTL1_AVGN_W                                              3U
#define ADC_CTL1_AVGN_M                                              0x07000000U
#define ADC_CTL1_AVGN_S                                              24U
#define ADC_CTL1_AVGN_DISABLE                                        0x00000000U
#define ADC_CTL1_AVGN_AVG_2                                          0x01000000U
#define ADC_CTL1_AVGN_AVG_4                                          0x02000000U
#define ADC_CTL1_AVGN_AVG_8                                          0x03000000U
#define ADC_CTL1_AVGN_AVG_16                                         0x04000000U
#define ADC_CTL1_AVGN_AVG_32                                         0x05000000U
#define ADC_CTL1_AVGN_AVG_64                                         0x06000000U
#define ADC_CTL1_AVGN_AVG_128                                        0x07000000U
/*

        Field:           AVGD
        From..to bits:   28...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Hardware average denominator. The number to divide the accumulated value by (this is a shift). Note results register is maximum of 16-bits long so if not shifted appropriately result will be truncated.

        ENUMs:
            SHIFT0:                      0 bit shift
            SHIFT1:                      1 bit shift
            SHIFT2:                      2 bit shift
            SHIFT3:                      3 bit shift
            SHIFT4:                      4 bit shift
            SHIFT5:                      5 bit shift
            SHIFT6:                      6 bit shift
            SHIFT7:                      7 bit shift
*/
#define ADC_CTL1_AVGD_W                                              3U
#define ADC_CTL1_AVGD_M                                              0x70000000U
#define ADC_CTL1_AVGD_S                                              28U
#define ADC_CTL1_AVGD_SHIFT0                                         0x00000000U
#define ADC_CTL1_AVGD_SHIFT1                                         0x10000000U
#define ADC_CTL1_AVGD_SHIFT2                                         0x20000000U
#define ADC_CTL1_AVGD_SHIFT3                                         0x30000000U
#define ADC_CTL1_AVGD_SHIFT4                                         0x40000000U
#define ADC_CTL1_AVGD_SHIFT5                                         0x50000000U
#define ADC_CTL1_AVGD_SHIFT6                                         0x60000000U
#define ADC_CTL1_AVGD_SHIFT7                                         0x70000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL2
    Offset name:         ADC_O_CTL2
    Relative address:    0x1108
    Description:         Primary Sequence Control Register
    Default Value:       0x00000000

        Field:           DF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP data read-back format. Data is always stored in binary unsigned format.

        ENUMs:
            UNSIGNED:                    Digital result reads as Binary Unsigned.
            SIGNED:                      Digital result reads Signed Binary. (2s complement), left aligned.
*/
#define ADC_CTL2_DF                                                  0x00000001U
#define ADC_CTL2_DF_M                                                0x00000001U
#define ADC_CTL2_DF_S                                                0U
#define ADC_CTL2_DF_UNSIGNED                                         0x00000000U
#define ADC_CTL2_DF_SIGNED                                           0x00000001U
/*

        Field:           RES
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP resolution. This bits define the conversion result resolution.
                         Note : A value of 3 defaults to 12 bit resolution.

        ENUMs:
            BIT_12:                      16-bits resolution
*/
#define ADC_CTL2_RES_W                                               2U
#define ADC_CTL2_RES_M                                               0x00000006U
#define ADC_CTL2_RES_S                                               1U
#define ADC_CTL2_RES_BIT_12                                          0x00000000U
/*

        Field:           DMAEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA for data transfer.

        ENUMs:
            DISABLE:                     DMA triggers are not enabled.
            ENABLE:                      Enable DMA.
*/
#define ADC_CTL2_DMAEN                                               0x00000100U
#define ADC_CTL2_DMAEN_M                                             0x00000100U
#define ADC_CTL2_DMAEN_S                                             8U
#define ADC_CTL2_DMAEN_DISABLE                                       0x00000000U
#define ADC_CTL2_DMAEN_ENABLE                                        0x00000100U
/*

        Field:           FIFOEN
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables configuring of MEMRES register in FIFO mode.

        ENUMs:
            ENABLE:                      Enables FIFO mode of operation.
            DISABLE:                     Disabled FIFO mode of operation,
*/
#define ADC_CTL2_FIFOEN                                              0x00000400U
#define ADC_CTL2_FIFOEN_M                                            0x00000400U
#define ADC_CTL2_FIFOEN_S                                            10U
#define ADC_CTL2_FIFOEN_ENABLE                                       0x00000400U
#define ADC_CTL2_FIFOEN_DISABLE                                      0x00000000U
/*

        Field:           STARTADD
        From..to bits:   16...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Primary Sequence Start Address.
                         These bits select which MEMCTLx is used for single conversion or as first MEMCTL for primary sequence mode.
                         The value of PSTARTADD is 0x00 to 0x1F, corresponding to MEMRES0 to MEMRES31.

        ENUMs:
            ADDR_00:                     MEMCTL0 is selected as start address of a primary sequence or as a single conversion.
            ADDR_01:                     MEMCTL1 is selected as start address of a primary sequence or as a single conversion.
            ADDR_02:                     MEMCTL2 is selected as start address of a primary sequence or as a single conversion.
            ADDR_03:                     MEMCTL3 is selected as start address of a primary sequence or as a single conversion.
            ADDR_04:                     MEMCTL4 is selected as start address of a primary sequence or as a single conversion.
            ADDR_05:                     MEMCTL5 is selected as start address of a primary sequence or as a single conversion.
            ADDR_06:                     MEMCTL6 is selected as start address of a primary sequence or as a single conversion.
            ADDR_07:                     MEMCTL7 is selected as start address of a primary sequence or as a single conversion.
            ADDR_08:                     MEMCTL8 is selected as start address of a primary sequence or as a single conversion.
            ADDR_09:                     MEMCTL9 is selected as start address of a primary sequence or as a single conversion.
            ADDR_10:                     MEMCTL10 is selected as start address of a primary sequence or as a single conversion.
            ADDR_11:                     MEMCTL11 is selected as start address of a primary sequence or as a single conversion.
            ADDR_12:                     MEMCTL12 is selected as start address of a primary sequence or as a single conversion.
            ADDR_13:                     MEMCTL13 is selected as start address of a primary sequence or as a single conversion.
            ADDR_14:                     MEMCTL14 is selected as start address of a primary sequence or as a single conversion.
            ADDR_15:                     MEMCTL15 is selected as start address of a primary sequence or as a single conversion.
            ADDR_16:                     MEMCTL16 is selected as start address of a primary sequence or as a single conversion.
            ADDR_17:                     MEMCTL17 is selected as start address of a primary sequence or as a single conversion.
            ADDR_18:                     MEMCTL18 is selected as start address of a primary sequence or as a single conversion.
            ADDR_19:                     MEMCTL19 is selected as start address of a primary sequence or as a single conversion.
            ADDR_20:                     MEMCTL20 is selected as start address of a primary sequence or as a single conversion.
            ADDR_21:                     MEMCTL21 is selected as start address of a primary sequence or as a single conversion.
            ADDR_22:                     MEMCTL22 is selected as start address of a primary sequence or as a single conversion.
            ADDR_23:                     MEMCTL23 is selected as start address of a primary sequence or as a single conversion.
            ADDR_24:                     MEMCTL24 is selected as start address of a primary sequence or as a single conversion.
            ADDR_25:                     MEMCTL25 is selected as start address of a primary sequence or as a single conversion.
            ADDR_26:                     MEMCTL26 is selected as start address of a primary sequence or as a single conversion.
            ADDR_31:                     MEMCTL31 is selected as start address of a primary sequence or as a single conversion.
            ADDR_30:                     MEMCTL30 is selected as start address of a primary sequence or as a single conversion.
            ADDR_29:                     MEMCTL29 is selected as start address of a primary sequence or as a single conversion.
            ADDR_28:                     MEMCTL28 is selected as start address of a primary sequence or as a single conversion.
            ADDR_27:                     MEMCTL27 is selected as start address of a primary sequence or as a single conversion.
*/
#define ADC_CTL2_STARTADD_W                                          5U
#define ADC_CTL2_STARTADD_M                                          0x001F0000U
#define ADC_CTL2_STARTADD_S                                          16U
#define ADC_CTL2_STARTADD_ADDR_00                                    0x00000000U
#define ADC_CTL2_STARTADD_ADDR_01                                    0x00010000U
#define ADC_CTL2_STARTADD_ADDR_02                                    0x00020000U
#define ADC_CTL2_STARTADD_ADDR_03                                    0x00030000U
#define ADC_CTL2_STARTADD_ADDR_04                                    0x00040000U
#define ADC_CTL2_STARTADD_ADDR_05                                    0x00050000U
#define ADC_CTL2_STARTADD_ADDR_06                                    0x00060000U
#define ADC_CTL2_STARTADD_ADDR_07                                    0x00070000U
#define ADC_CTL2_STARTADD_ADDR_08                                    0x00080000U
#define ADC_CTL2_STARTADD_ADDR_09                                    0x00090000U
#define ADC_CTL2_STARTADD_ADDR_10                                    0x000A0000U
#define ADC_CTL2_STARTADD_ADDR_11                                    0x000B0000U
#define ADC_CTL2_STARTADD_ADDR_12                                    0x000C0000U
#define ADC_CTL2_STARTADD_ADDR_13                                    0x000D0000U
#define ADC_CTL2_STARTADD_ADDR_14                                    0x000E0000U
#define ADC_CTL2_STARTADD_ADDR_15                                    0x000F0000U
#define ADC_CTL2_STARTADD_ADDR_16                                    0x00100000U
#define ADC_CTL2_STARTADD_ADDR_17                                    0x00110000U
#define ADC_CTL2_STARTADD_ADDR_18                                    0x00120000U
#define ADC_CTL2_STARTADD_ADDR_19                                    0x00130000U
#define ADC_CTL2_STARTADD_ADDR_20                                    0x00140000U
#define ADC_CTL2_STARTADD_ADDR_21                                    0x00150000U
#define ADC_CTL2_STARTADD_ADDR_22                                    0x00160000U
#define ADC_CTL2_STARTADD_ADDR_23                                    0x00170000U
#define ADC_CTL2_STARTADD_ADDR_24                                    0x00180000U
#define ADC_CTL2_STARTADD_ADDR_25                                    0x00190000U
#define ADC_CTL2_STARTADD_ADDR_26                                    0x001A0000U
#define ADC_CTL2_STARTADD_ADDR_31                                    0x001F0000U
#define ADC_CTL2_STARTADD_ADDR_30                                    0x001E0000U
#define ADC_CTL2_STARTADD_ADDR_29                                    0x001D0000U
#define ADC_CTL2_STARTADD_ADDR_28                                    0x001C0000U
#define ADC_CTL2_STARTADD_ADDR_27                                    0x001B0000U
/*

        Field:           ENDADD
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Primary Sequence End Address.
                         These bits select which MEMCTLx is the last MEMCTL for primary sequence mode.
                         The value of PSTARTADD is 0x00 to 0x1F, corresponding to MEMRES0 to MEMRES31.

        ENUMs:
            ADDR_00:                     MEMCTL0 is selected as end address of primary sequence.
            ADDR_01:                     MEMCTL1 is selected as end address of primary sequence.
            ADDR_02:                     MEMCTL2 is selected as end address of primary sequence.
            ADDR_03:                     MEMCTL3 is selected as end address of primary sequence.
            ADDR_04:                     MEMCTL4 is selected as end address of primary sequence.
            ADDR_05:                     MEMCTL5 is selected as end address of primary sequence.
            ADDR_06:                     MEMCTL6 is selected as end address of primary sequence.
            ADDR_07:                     MEMCTL7 is selected as end address of primary sequence.
            ADDR_08:                     MEMCTL8 is selected as end address of primary sequence.
            ADDR_09:                     MEMCTL9 is selected as end address of primary sequence.
            ADDR_10:                     MEMCTL10 is selected as end address of primary sequence.
            ADDR_11:                     MEMCTL11 is selected as end address of primary sequence.
            ADDR_12:                     MEMCTL12 is selected as end address of primary sequence.
            ADDR_13:                     MEMCTL13 is selected as end address of primary sequence.
            ADDR_14:                     MEMCTL14 is selected as end address of primary sequence.
            ADDR_15:                     MEMCTL15 is selected as end address of primary sequence.
            ADDR_16:                     MEMCTL16 is selected as end address of primary sequence.
            ADDR_17:                     MEMCTL17 is selected as end address of primary sequence.
            ADDR_18:                     MEMCTL18 is selected as end address of primary sequence.
            ADDR_19:                     MEMCTL19 is selected as end address of primary sequence.
            ADDR_20:                     MEMCTL20 is selected as end address of primary sequence.
            ADDR_21:                     MEMCTL21 is selected as end address of primary sequence.
            ADDR_22:                     MEMCTL22 is selected as end address of primary sequence.
            ADDR_23:                     MEMCTL23 is selected as end address of primary sequence.
            ADDR_24:                     MEMCTL24 is selected as end address of primary sequence.
            ADDR_25:                     MEMCTL25 is selected as end address of primary sequence.
            ADDR_26:                     MEMCTL26 is selected as end address of primary sequence.
            ADDR_27:                     MEMCTL27 is selected as end address of primary sequence.
            ADDR_28:                     MEMCTL28 is selected as end address of primary sequence.
            ADDR_29:                     MEMCTL29 is selected as end address of primary sequence.
            ADDR_30:                     MEMCTL30 is selected as end address of primary sequence.
            ADDR_31:                     MEMCTL31 is selected as end address of primary sequence.
*/
#define ADC_CTL2_ENDADD_W                                            5U
#define ADC_CTL2_ENDADD_M                                            0x1F000000U
#define ADC_CTL2_ENDADD_S                                            24U
#define ADC_CTL2_ENDADD_ADDR_00                                      0x00000000U
#define ADC_CTL2_ENDADD_ADDR_01                                      0x01000000U
#define ADC_CTL2_ENDADD_ADDR_02                                      0x02000000U
#define ADC_CTL2_ENDADD_ADDR_03                                      0x03000000U
#define ADC_CTL2_ENDADD_ADDR_04                                      0x04000000U
#define ADC_CTL2_ENDADD_ADDR_05                                      0x05000000U
#define ADC_CTL2_ENDADD_ADDR_06                                      0x06000000U
#define ADC_CTL2_ENDADD_ADDR_07                                      0x07000000U
#define ADC_CTL2_ENDADD_ADDR_08                                      0x08000000U
#define ADC_CTL2_ENDADD_ADDR_09                                      0x09000000U
#define ADC_CTL2_ENDADD_ADDR_10                                      0x0A000000U
#define ADC_CTL2_ENDADD_ADDR_11                                      0x0B000000U
#define ADC_CTL2_ENDADD_ADDR_12                                      0x0C000000U
#define ADC_CTL2_ENDADD_ADDR_13                                      0x0D000000U
#define ADC_CTL2_ENDADD_ADDR_14                                      0x0E000000U
#define ADC_CTL2_ENDADD_ADDR_15                                      0x0F000000U
#define ADC_CTL2_ENDADD_ADDR_16                                      0x10000000U
#define ADC_CTL2_ENDADD_ADDR_17                                      0x11000000U
#define ADC_CTL2_ENDADD_ADDR_18                                      0x12000000U
#define ADC_CTL2_ENDADD_ADDR_19                                      0x13000000U
#define ADC_CTL2_ENDADD_ADDR_20                                      0x14000000U
#define ADC_CTL2_ENDADD_ADDR_21                                      0x15000000U
#define ADC_CTL2_ENDADD_ADDR_22                                      0x16000000U
#define ADC_CTL2_ENDADD_ADDR_23                                      0x17000000U
#define ADC_CTL2_ENDADD_ADDR_24                                      0x18000000U
#define ADC_CTL2_ENDADD_ADDR_25                                      0x19000000U
#define ADC_CTL2_ENDADD_ADDR_26                                      0x1A000000U
#define ADC_CTL2_ENDADD_ADDR_27                                      0x1B000000U
#define ADC_CTL2_ENDADD_ADDR_28                                      0x1C000000U
#define ADC_CTL2_ENDADD_ADDR_29                                      0x1D000000U
#define ADC_CTL2_ENDADD_ADDR_30                                      0x1E000000U
#define ADC_CTL2_ENDADD_ADDR_31                                      0x1F000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL3
    Offset name:         ADC_O_CTL3
    Relative address:    0x110C
    Description:         Control Register 3. This register is used to configure ADC for ad-hoc single conversion.
    Default Value:       0x00000000

        Field:           ASCCHSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ASC channel select

        ENUMs:
            CHAN_0:                      Selects channel 0
            CHAN_1:                      Selects channel 1
            CHAN_2:                      Selects channel 2
            CHAN_3:                      Selects channel 3
            CHAN_4:                      Selects channel 4
            CHAN_5:                      Selects channel 5
            CHAN_6:                      Selects channel 6
            CHAN_7:                      Selects channel 7
            CHAN_8:                      Selects channel 8
            CHAN_9:                      Selects channel 9
            CHAN_10:                     Selects channel 10
            CHAN_11:                     Selects channel 11
            CHAN_12:                     Selects channel 12
            CHAN_13:                     Selects channel 13
            CHAN_14:                     Selects channel 14
            CHAN_15:                     Selects channel 15
            CHAN_16:                     Selects channel 16
            CHAN_17:                     Selects channel 17
            CHAN_18:                     Selects channel 18
            CHAN_19:                     Selects channel 19
            CHAN_20:                     Selects channel 20
            CHAN_21:                     Selects channel 21
            CHAN_22:                     Selects channel 22
            CHAN_23:                     Selects channel 23
            CHAN_24:                     Selects channel 24
            CHAN_25:                     Selects channel 25
            CHAN_26:                     Selects channel 26
            CHAN_27:                     Selects channel 27
            CHAN_28:                     Selects channel 28
            CHAN_29:                     Selects channel 29
            CHAN_30:                     Selects channel 30
            CHAN_31:                     Selects channel 31
*/
#define ADC_CTL3_ASCCHSEL_W                                          5U
#define ADC_CTL3_ASCCHSEL_M                                          0x0000001FU
#define ADC_CTL3_ASCCHSEL_S                                          0U
#define ADC_CTL3_ASCCHSEL_CHAN_0                                     0x00000000U
#define ADC_CTL3_ASCCHSEL_CHAN_1                                     0x00000001U
#define ADC_CTL3_ASCCHSEL_CHAN_2                                     0x00000002U
#define ADC_CTL3_ASCCHSEL_CHAN_3                                     0x00000003U
#define ADC_CTL3_ASCCHSEL_CHAN_4                                     0x00000004U
#define ADC_CTL3_ASCCHSEL_CHAN_5                                     0x00000005U
#define ADC_CTL3_ASCCHSEL_CHAN_6                                     0x00000006U
#define ADC_CTL3_ASCCHSEL_CHAN_7                                     0x00000007U
#define ADC_CTL3_ASCCHSEL_CHAN_8                                     0x00000008U
#define ADC_CTL3_ASCCHSEL_CHAN_9                                     0x00000009U
#define ADC_CTL3_ASCCHSEL_CHAN_10                                    0x0000000AU
#define ADC_CTL3_ASCCHSEL_CHAN_11                                    0x0000000BU
#define ADC_CTL3_ASCCHSEL_CHAN_12                                    0x0000000CU
#define ADC_CTL3_ASCCHSEL_CHAN_13                                    0x0000000DU
#define ADC_CTL3_ASCCHSEL_CHAN_14                                    0x0000000EU
#define ADC_CTL3_ASCCHSEL_CHAN_15                                    0x0000000FU
#define ADC_CTL3_ASCCHSEL_CHAN_16                                    0x00000010U
#define ADC_CTL3_ASCCHSEL_CHAN_17                                    0x00000011U
#define ADC_CTL3_ASCCHSEL_CHAN_18                                    0x00000012U
#define ADC_CTL3_ASCCHSEL_CHAN_19                                    0x00000013U
#define ADC_CTL3_ASCCHSEL_CHAN_20                                    0x00000014U
#define ADC_CTL3_ASCCHSEL_CHAN_21                                    0x00000015U
#define ADC_CTL3_ASCCHSEL_CHAN_22                                    0x00000016U
#define ADC_CTL3_ASCCHSEL_CHAN_23                                    0x00000017U
#define ADC_CTL3_ASCCHSEL_CHAN_24                                    0x00000018U
#define ADC_CTL3_ASCCHSEL_CHAN_25                                    0x00000019U
#define ADC_CTL3_ASCCHSEL_CHAN_26                                    0x0000001AU
#define ADC_CTL3_ASCCHSEL_CHAN_27                                    0x0000001BU
#define ADC_CTL3_ASCCHSEL_CHAN_28                                    0x0000001CU
#define ADC_CTL3_ASCCHSEL_CHAN_29                                    0x0000001DU
#define ADC_CTL3_ASCCHSEL_CHAN_30                                    0x0000001EU
#define ADC_CTL3_ASCCHSEL_CHAN_31                                    0x0000001FU
/*

        Field:           ASCSTIME
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ASC sample time compare value select. This is used to select between SCOMP0 and SCOMP1 registers for ASC operation.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0
            SEL_SCOMP1:                  Select SCOMP1
*/
#define ADC_CTL3_ASCSTIME                                            0x00000100U
#define ADC_CTL3_ASCSTIME_M                                          0x00000100U
#define ADC_CTL3_ASCSTIME_S                                          8U
#define ADC_CTL3_ASCSTIME_SEL_SCOMP0                                 0x00000000U
#define ADC_CTL3_ASCSTIME_SEL_SCOMP1                                 0x00000100U
/*

        Field:           ASCVRSEL
        From..to bits:   12...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the voltage reference for ASC operation. VEREFM must be connected to on-board ground when external reference option is selected.
                         Note: Writing value 0x3 defaults to INTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      Internal reference.
*/
#define ADC_CTL3_ASCVRSEL_W                                          2U
#define ADC_CTL3_ASCVRSEL_M                                          0x00003000U
#define ADC_CTL3_ASCVRSEL_S                                          12U
#define ADC_CTL3_ASCVRSEL_EXTREF                                     0x00001000U
#define ADC_CTL3_ASCVRSEL_INTREF                                     0x00002000U
/*

        Field:           ASCFSR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V

                         *Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_CTL3_ASCFSR                                              0x00004000U
#define ADC_CTL3_ASCFSR_M                                            0x00004000U
#define ADC_CTL3_ASCFSR_S                                            14U
/*

        Field:           ASCMODE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Single vs Differential

*/
#define ADC_CTL3_ASCMODE                                             0x00008000U
#define ADC_CTL3_ASCMODE_M                                           0x00008000U
#define ADC_CTL3_ASCMODE_S                                           15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKFREQ
    Offset name:         ADC_O_CLKFREQ
    Relative address:    0x1110
    Description:         ADC sampling clock frequency range register.
    Default Value:       0x00000000

        Field:           FRANGE
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Frequency Range.

                         NU

        ENUMs:
            RANGE1TO4:                   1 to 4 MHz
            RANGE4TO8:                   4 to 8 MHz
            RANGE8TO16:                  8 to 16 MHz
            RANGE16TO20:                 16 to 20 MHz
            RANGE20TO24:                 20 to 24 MHz
            RANGE24TO32:                 24 to 32 MHz
            RANGE32TO40:                 32 to 40 MHz
            RANGE40TO48:                 40 to 48 MHz
*/
#define ADC_CLKFREQ_FRANGE_W                                         3U
#define ADC_CLKFREQ_FRANGE_M                                         0x00000007U
#define ADC_CLKFREQ_FRANGE_S                                         0U
#define ADC_CLKFREQ_FRANGE_RANGE1TO4                                 0x00000000U
#define ADC_CLKFREQ_FRANGE_RANGE4TO8                                 0x00000001U
#define ADC_CLKFREQ_FRANGE_RANGE8TO16                                0x00000002U
#define ADC_CLKFREQ_FRANGE_RANGE16TO20                               0x00000003U
#define ADC_CLKFREQ_FRANGE_RANGE20TO24                               0x00000004U
#define ADC_CLKFREQ_FRANGE_RANGE24TO32                               0x00000005U
#define ADC_CLKFREQ_FRANGE_RANGE32TO40                               0x00000006U
#define ADC_CLKFREQ_FRANGE_RANGE40TO48                               0x00000007U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCOMP0
    Offset name:         ADC_O_SCOMP0
    Relative address:    0x1114
    Description:         ULP_ADCHP sample time register x
                        Specifies the sample time,  in number of ADCCLK cycles,  when PSSM = 0 (AUTO) or SSSM = 0 (AUTO).
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000000

        Field:           SMP
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SAMPLE

                         This bit-field specify the number of sample time clocks  (SCOMPx +1) for a conversion when SAMPLE_TIME in MEMCTLx is set to SCOMPx.

*/
#define ADC_SCOMP0_SMP_W                                             14U
#define ADC_SCOMP0_SMP_M                                             0x00003FFFU
#define ADC_SCOMP0_SMP_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCOMP1
    Offset name:         ADC_O_SCOMP1
    Relative address:    0x1118
    Description:         ULP_ADCHP sample time register x
                        Specifies the sample time,  in number of ADCCLK cycles,  when PSSM = 0 (AUTO) or SSSM = 0 (AUTO).
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000000

        Field:           SMP
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SAMPLE

                         This bitfield specify the number of sample time clocks  (SCOMPx +1) for a conversion when SAMPLE_TIME in MEMCTLx is set to SCOMPx.

*/
#define ADC_SCOMP1_SMP_W                                             14U
#define ADC_SCOMP1_SMP_M                                             0x00003FFFU
#define ADC_SCOMP1_SMP_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REFCFG
    Offset name:         ADC_O_REFCFG
    Relative address:    0x111C
    Description:         REFBUF configuration register
    Default Value:       0x00000000

        Field:           REFEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REFBUF enable

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define ADC_REFCFG_REFEN                                             0x00000001U
#define ADC_REFCFG_REFEN_M                                           0x00000001U
#define ADC_REFCFG_REFEN_S                                           0U
#define ADC_REFCFG_REFEN_DISABLE                                     0x00000000U
#define ADC_REFCFG_REFEN_ENABLE                                      0x00000001U
/*

        Field:           REFVSEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Configures REFBUF output voltage

        ENUMs:
            V1P4:                        REFBUF generates 1.4V output
*/
#define ADC_REFCFG_REFVSEL                                           0x00000002U
#define ADC_REFCFG_REFVSEL_M                                         0x00000002U
#define ADC_REFCFG_REFVSEL_S                                         1U
#define ADC_REFCFG_REFVSEL_V1P4                                      0x00000000U
/*

        Field:           IBEN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     REFBUF IBIAS enable

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define ADC_REFCFG_IBEN                                              0x00000004U
#define ADC_REFCFG_IBEN_M                                            0x00000004U
#define ADC_REFCFG_IBEN_S                                            2U
#define ADC_REFCFG_IBEN_DISABLE                                      0x00000000U
#define ADC_REFCFG_IBEN_ENABLE                                       0x00000004U
/*

        Field:           IBPROG
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Configures REFBUF IBIAS current output value

        ENUMs:
            VAL0:                        1uA
            VAL1:                        0.5uA
            VAL2:                        2uA
            VAL3:                        0.67uA
*/
#define ADC_REFCFG_IBPROG_W                                          2U
#define ADC_REFCFG_IBPROG_M                                          0x00000018U
#define ADC_REFCFG_IBPROG_S                                          3U
#define ADC_REFCFG_IBPROG_VAL0                                       0x00000000U
#define ADC_REFCFG_IBPROG_VAL1                                       0x00000008U
#define ADC_REFCFG_IBPROG_VAL2                                       0x00000010U
#define ADC_REFCFG_IBPROG_VAL3                                       0x00000018U
/*

        Field:           OSPRPWRDN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OSPREY POWER DOWN

                         Similar to ADC PWRDN control to save power in duty cycled mode of operation. 0 - AUTO, 1 - MANUAL

                         In case of ADC, Sample time MMR needs to take into account time required to power on ADC. Since REF BUF may take time in us, recommendation is to use REFOKf th output oe buffer instead to start ADC conversion

*/
#define ADC_REFCFG_OSPRPWRDN                                         0x00000020U
#define ADC_REFCFG_OSPRPWRDN_M                                       0x00000020U
#define ADC_REFCFG_OSPRPWRDN_S                                       5U
/*

        Field:           SPAR
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPARE

*/
#define ADC_REFCFG_SPAR_W                                            2U
#define ADC_REFCFG_SPAR_M                                            0x000000C0U
#define ADC_REFCFG_SPAR_S                                            6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCLOW
    Offset name:         ADC_O_WCLOW
    Relative address:    0x1148
    Description:         ULP_ADCHP Window Comparator Low Threshold 0 Register.
                        The data format that is used to write and read WCLOW0 depends on the value of the DATAFORMAT bit in the CTL1 register. If DATAFORMAT = 0, the data is binary unsigned and right aligned. If DATAFORMAT = 1, the data is 2s complement and left aligned. Refer to the WCLOW0 bit-field description for details.
                        CTL0.ENC  must be set to 0 to write to this register.
                        Design Note: To minimize cycles transforming data, the data written to WCLOW0 should be transformed into DATAFORMAT = 0 to match the MEMRESx register so a direct comparison can be done. Thus, there are extra cycles to write to this register but no penalty when a comparison is done.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Low threshold register 0.
                         If DATAFORMAT = 0, unsigned binary format has to be used:
                         The value based on the resolution has to be right aligned with the MSB on the left.
                         For 14-bits and 12-bits resolution, unused bit have to be 0s
                         Reset value is 0x0000.
                         If DATAFORMAT = 1, 2s-complement format has to be used.
                         The value based on the resolution has to be left aligned with the LSB on the right.
                         For 14-bits and 12-bits resolution, unused bit have to be 0s
                         Reset value is 0x8000.

*/
#define ADC_WCLOW_DATA_W                                             16U
#define ADC_WCLOW_DATA_M                                             0x0000FFFFU
#define ADC_WCLOW_DATA_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WCHI
    Offset name:         ADC_O_WCHI
    Relative address:    0x1150
    Description:         WC HIGH

                        ULP_ADCHP Window Comparator High Threshold 0 Register.
                        The data format that is used to write and read WCHIGH0 depends on the value of the DATAFORMAT bit in the CTL1 register. If DATAFORMAT = 0, the data is binary unsigned and right aligned. If DATAFORMAT = 1, the data is 2s complement and left aligned. Refer to the WCHIGH0 bit-field description for details.
                        CTL0.ENC  must be set to 0 to write to this register.
                        Design Note: To minimize cycles transforming data, the data written to WCHIGH0 should be transformed in DATAFORMAT = 0 to match the MEMRESx register so a direct comparison can be done. Thus, there are extra cycles to write to this register but no penalty when a comparison is done.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Low threshold register 0.
                         If DATAFORMAT = 0, unsigned binary format has to be used:
                         The threshold value has to be right aligned, with the MSB on the left.
                         Reset value are: 0xFFFF (16-bit), 0x3FFF (14-bit) or 0x0FFF (12-bit)

                         If DATAFORMAT = 1, 2s-complement format has to be used.
                         The value based on the resolution has to be left aligned with the LSB on the right.
                         For 14-bits and 12-bits resolution, unused bit have to be 0s
                         Reset value are: 0x7FFF (16-bit), 0x7FFC (14-bit) or 0x7FF0 (12-bit)


*/
#define ADC_WCHI_DATA_W                                              16U
#define ADC_WCHI_DATA_M                                              0x0000FFFFU
#define ADC_WCHI_DATA_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFODATA
    Offset name:         ADC_O_FIFODATA
    Relative address:    0x1160
    Description:         Virtual data register used to do a read from FIFO.
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Read from data field returns the data from the top of FIFO.

*/
#define ADC_FIFODATA_DATA_W                                          32U
#define ADC_FIFODATA_DATA_M                                          0xFFFFFFFFU
#define ADC_FIFODATA_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ASCRES
    Offset name:         ADC_O_ASCRES
    Relative address:    0x1170
    Description:         ASC result register.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Data

*/
#define ADC_ASCRES_DATA_W                                            16U
#define ADC_ASCRES_DATA_M                                            0x0000FFFFU
#define ADC_ASCRES_DATA_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_0
    Offset name:         ADC_O_MEMCTL_0
    Relative address:    0x1180
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_0_CHANSEL_W                                       5U
#define ADC_MEMCTL_0_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_0_CHANSEL_S                                       0U
#define ADC_MEMCTL_0_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_0_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_0_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_0_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_0_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_0_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_0_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_0_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_0_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_0_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_0_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_0_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_0_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_0_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_0_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_0_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_0_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_0_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_0_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_0_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_0_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_0_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_0_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_0_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_0_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_0_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_0_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_0_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_0_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_0_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_0_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_0_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_0_VRSEL_W                                         2U
#define ADC_MEMCTL_0_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_0_VRSEL_S                                         8U
#define ADC_MEMCTL_0_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_0_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_0_STIME                                           0x00001000U
#define ADC_MEMCTL_0_STIME_M                                         0x00001000U
#define ADC_MEMCTL_0_STIME_S                                         12U
#define ADC_MEMCTL_0_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_0_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_0_AVGEN                                           0x00010000U
#define ADC_MEMCTL_0_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_0_AVGEN_S                                         16U
#define ADC_MEMCTL_0_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_0_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_0_TRIG                                            0x01000000U
#define ADC_MEMCTL_0_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_0_TRIG_S                                          24U
#define ADC_MEMCTL_0_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_0_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_0_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_0_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_0_WINCOMP_S                                       28U
#define ADC_MEMCTL_0_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_0_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_0_FSR                                             0x20000000U
#define ADC_MEMCTL_0_FSR_M                                           0x20000000U
#define ADC_MEMCTL_0_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_0_MOD                                             0x40000000U
#define ADC_MEMCTL_0_MOD_M                                           0x40000000U
#define ADC_MEMCTL_0_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_1
    Offset name:         ADC_O_MEMCTL_1
    Relative address:    0x1184
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_1_CHANSEL_W                                       5U
#define ADC_MEMCTL_1_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_1_CHANSEL_S                                       0U
#define ADC_MEMCTL_1_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_1_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_1_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_1_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_1_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_1_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_1_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_1_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_1_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_1_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_1_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_1_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_1_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_1_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_1_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_1_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_1_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_1_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_1_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_1_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_1_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_1_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_1_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_1_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_1_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_1_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_1_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_1_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_1_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_1_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_1_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_1_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_1_VRSEL_W                                         2U
#define ADC_MEMCTL_1_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_1_VRSEL_S                                         8U
#define ADC_MEMCTL_1_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_1_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_1_STIME                                           0x00001000U
#define ADC_MEMCTL_1_STIME_M                                         0x00001000U
#define ADC_MEMCTL_1_STIME_S                                         12U
#define ADC_MEMCTL_1_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_1_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_1_AVGEN                                           0x00010000U
#define ADC_MEMCTL_1_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_1_AVGEN_S                                         16U
#define ADC_MEMCTL_1_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_1_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_1_TRIG                                            0x01000000U
#define ADC_MEMCTL_1_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_1_TRIG_S                                          24U
#define ADC_MEMCTL_1_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_1_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_1_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_1_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_1_WINCOMP_S                                       28U
#define ADC_MEMCTL_1_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_1_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_1_FSR                                             0x20000000U
#define ADC_MEMCTL_1_FSR_M                                           0x20000000U
#define ADC_MEMCTL_1_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_1_MOD                                             0x40000000U
#define ADC_MEMCTL_1_MOD_M                                           0x40000000U
#define ADC_MEMCTL_1_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_2
    Offset name:         ADC_O_MEMCTL_2
    Relative address:    0x1188
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_2_CHANSEL_W                                       5U
#define ADC_MEMCTL_2_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_2_CHANSEL_S                                       0U
#define ADC_MEMCTL_2_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_2_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_2_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_2_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_2_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_2_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_2_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_2_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_2_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_2_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_2_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_2_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_2_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_2_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_2_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_2_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_2_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_2_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_2_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_2_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_2_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_2_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_2_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_2_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_2_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_2_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_2_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_2_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_2_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_2_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_2_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_2_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_2_VRSEL_W                                         2U
#define ADC_MEMCTL_2_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_2_VRSEL_S                                         8U
#define ADC_MEMCTL_2_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_2_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_2_STIME                                           0x00001000U
#define ADC_MEMCTL_2_STIME_M                                         0x00001000U
#define ADC_MEMCTL_2_STIME_S                                         12U
#define ADC_MEMCTL_2_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_2_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_2_AVGEN                                           0x00010000U
#define ADC_MEMCTL_2_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_2_AVGEN_S                                         16U
#define ADC_MEMCTL_2_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_2_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_2_TRIG                                            0x01000000U
#define ADC_MEMCTL_2_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_2_TRIG_S                                          24U
#define ADC_MEMCTL_2_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_2_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_2_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_2_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_2_WINCOMP_S                                       28U
#define ADC_MEMCTL_2_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_2_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_2_FSR                                             0x20000000U
#define ADC_MEMCTL_2_FSR_M                                           0x20000000U
#define ADC_MEMCTL_2_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_2_MOD                                             0x40000000U
#define ADC_MEMCTL_2_MOD_M                                           0x40000000U
#define ADC_MEMCTL_2_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_3
    Offset name:         ADC_O_MEMCTL_3
    Relative address:    0x118C
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_3_CHANSEL_W                                       5U
#define ADC_MEMCTL_3_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_3_CHANSEL_S                                       0U
#define ADC_MEMCTL_3_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_3_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_3_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_3_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_3_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_3_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_3_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_3_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_3_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_3_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_3_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_3_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_3_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_3_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_3_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_3_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_3_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_3_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_3_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_3_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_3_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_3_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_3_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_3_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_3_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_3_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_3_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_3_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_3_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_3_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_3_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_3_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_3_VRSEL_W                                         2U
#define ADC_MEMCTL_3_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_3_VRSEL_S                                         8U
#define ADC_MEMCTL_3_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_3_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_3_STIME                                           0x00001000U
#define ADC_MEMCTL_3_STIME_M                                         0x00001000U
#define ADC_MEMCTL_3_STIME_S                                         12U
#define ADC_MEMCTL_3_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_3_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_3_AVGEN                                           0x00010000U
#define ADC_MEMCTL_3_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_3_AVGEN_S                                         16U
#define ADC_MEMCTL_3_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_3_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_3_TRIG                                            0x01000000U
#define ADC_MEMCTL_3_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_3_TRIG_S                                          24U
#define ADC_MEMCTL_3_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_3_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_3_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_3_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_3_WINCOMP_S                                       28U
#define ADC_MEMCTL_3_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_3_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_3_FSR                                             0x20000000U
#define ADC_MEMCTL_3_FSR_M                                           0x20000000U
#define ADC_MEMCTL_3_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_3_MOD                                             0x40000000U
#define ADC_MEMCTL_3_MOD_M                                           0x40000000U
#define ADC_MEMCTL_3_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_4
    Offset name:         ADC_O_MEMCTL_4
    Relative address:    0x1190
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_4_CHANSEL_W                                       5U
#define ADC_MEMCTL_4_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_4_CHANSEL_S                                       0U
#define ADC_MEMCTL_4_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_4_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_4_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_4_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_4_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_4_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_4_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_4_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_4_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_4_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_4_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_4_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_4_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_4_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_4_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_4_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_4_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_4_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_4_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_4_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_4_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_4_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_4_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_4_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_4_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_4_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_4_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_4_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_4_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_4_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_4_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_4_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_4_VRSEL_W                                         2U
#define ADC_MEMCTL_4_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_4_VRSEL_S                                         8U
#define ADC_MEMCTL_4_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_4_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_4_STIME                                           0x00001000U
#define ADC_MEMCTL_4_STIME_M                                         0x00001000U
#define ADC_MEMCTL_4_STIME_S                                         12U
#define ADC_MEMCTL_4_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_4_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_4_AVGEN                                           0x00010000U
#define ADC_MEMCTL_4_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_4_AVGEN_S                                         16U
#define ADC_MEMCTL_4_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_4_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_4_TRIG                                            0x01000000U
#define ADC_MEMCTL_4_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_4_TRIG_S                                          24U
#define ADC_MEMCTL_4_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_4_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_4_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_4_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_4_WINCOMP_S                                       28U
#define ADC_MEMCTL_4_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_4_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_4_FSR                                             0x20000000U
#define ADC_MEMCTL_4_FSR_M                                           0x20000000U
#define ADC_MEMCTL_4_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_4_MOD                                             0x40000000U
#define ADC_MEMCTL_4_MOD_M                                           0x40000000U
#define ADC_MEMCTL_4_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMCTL_5
    Offset name:         ADC_O_MEMCTL_5
    Relative address:    0x1194
    Description:         ULP_ADCHP Conversion Memory Control Register x (x=0 to 31)
                        CTL0.ENC  must be set to 0 to write to this register.
    Default Value:       0x00000100

        Field:           CHANSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ULP_ADCHP Input channel select.
                         In single ended mode, any of the 32 channels can be selected.
                         In differential mode, this field will select which EVEN channel to be connected to the vin+ input.
                         The vin- is automatically set to the next ODD channel. (CHANSEL+1)

        ENUMs:
            CHAN_0:                      If DIFIN= 0:  Ain+ = A0. If DIFIN = 1: Ain+ = A0, Ain- = A1

            CHAN_1:                      If DIFIN= 0:  Ain+ = A1. If DIFIN = 1: Ain+ = A0, Ain- = A1
            CHAN_2:                      If DIFIN = 0:  Ain+ = A2. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_3:                      If DIFIN = 0:  Ain+ = A3. If DIFIN = 1: Ain+ = A2, Ain- = A3
            CHAN_4:                      If DIFIN = 0:  Ain+ = A4. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_5:                      If DIFIN = 0:  Ain+ = A5. If DIFIN = 1: Ain+ = A4, Ain- = A5
            CHAN_6:                      If DIFIN = 0:  Ain+ = A6. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_7:                      If DIFIN = 0:  Ain+ = A7. If DIFIN = 1: Ain+ = A6, Ain- = A7
            CHAN_8:                      If DIFIN = 0:  Ain+ = A8. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_9:                      If DIFIN= 0:  Ain+ = A9. If DIFIN = 1: Ain+ = A8, Ain- = A9
            CHAN_10:                     If DIFIN= 0:  Ain+ = A10. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_11:                     If DIFIN= 0:  Ain+ = A11. If DIFIN = 1: Ain+ = A10, Ain- = A11
            CHAN_12:                     If DIFIN= 0:  Ain+ = A12. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_13:                     If DIFIN= 0:  Ain+ = A13. If DIFIN = 1: Ain+ = A12, Ain- = A13
            CHAN_14:                     If DIFIN= 0:  Ain+ = A14. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_15:                     If DIFIN= 0:  Ain+ = A15. If DIFIN = 1: Ain+ = A14, Ain- = A15
            CHAN_16:                     If DIFIN= 0:  Ain+ = A16. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_17:                     If DIFIN= 0:  Ain+ = A17. If DIFIN = 1: Ain+ = A16, Ain- = A17
            CHAN_18:                     If DIFIN= 0:  Ain+ = A18. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_19:                     If DIFIN= 0:  Ain+ = A19. If DIFIN = 1: Ain+ = A18, Ain- = A19
            CHAN_20:                     If DIFIN= 0:  Ain+ = A20. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_21:                     If DIFIN= 0:  Ain+ = A21. If DIFIN = 1: Ain+ = A20, Ain- = A21
            CHAN_22:                     If DIFIN= 0:  Ain+ = A22. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_23:                     If DIFIN= 0:  Ain+ = A23. If DIFIN = 1: Ain+ = A22, Ain- = A23
            CHAN_24:                     If DIFIN= 0:  Ain+ = A24. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_25:                     If DIFIN= 0:  Ain+ = A25. If DIFIN = 1: Ain+ = A24, Ain- = A25
            CHAN_26:                     If DIFIN= 0:  Ain+ = A26. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_27:                     If DIFIN= 0:  Ain+ = A27. If DIFIN = 1: Ain+ = A26, Ain- = A27
            CHAN_28:                     If DIFIN= 0:  Ain+ = A28. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_29:                     If DIFIN= 0:  Ain+ = A29. If DIFIN = 1: Ain+ = A28, Ain- = A29
            CHAN_30:                     If DIFIN= 0:  Ain+ = A30. If DIFIN = 1: Ain+ = A30, Ain- = A31
            CHAN_31:                     If DIFIN= 0:  Ain+ = A31. If DIFIN = 1: Ain+ = A30, Ain- = A31
*/
#define ADC_MEMCTL_5_CHANSEL_W                                       5U
#define ADC_MEMCTL_5_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL_5_CHANSEL_S                                       0U
#define ADC_MEMCTL_5_CHANSEL_CHAN_0                                  0x00000000U
#define ADC_MEMCTL_5_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL_5_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL_5_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL_5_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL_5_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL_5_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL_5_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL_5_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL_5_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL_5_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL_5_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL_5_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL_5_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL_5_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL_5_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL_5_CHANSEL_CHAN_16                                 0x00000010U
#define ADC_MEMCTL_5_CHANSEL_CHAN_17                                 0x00000011U
#define ADC_MEMCTL_5_CHANSEL_CHAN_18                                 0x00000012U
#define ADC_MEMCTL_5_CHANSEL_CHAN_19                                 0x00000013U
#define ADC_MEMCTL_5_CHANSEL_CHAN_20                                 0x00000014U
#define ADC_MEMCTL_5_CHANSEL_CHAN_21                                 0x00000015U
#define ADC_MEMCTL_5_CHANSEL_CHAN_22                                 0x00000016U
#define ADC_MEMCTL_5_CHANSEL_CHAN_23                                 0x00000017U
#define ADC_MEMCTL_5_CHANSEL_CHAN_24                                 0x00000018U
#define ADC_MEMCTL_5_CHANSEL_CHAN_25                                 0x00000019U
#define ADC_MEMCTL_5_CHANSEL_CHAN_26                                 0x0000001AU
#define ADC_MEMCTL_5_CHANSEL_CHAN_27                                 0x0000001BU
#define ADC_MEMCTL_5_CHANSEL_CHAN_28                                 0x0000001CU
#define ADC_MEMCTL_5_CHANSEL_CHAN_29                                 0x0000001DU
#define ADC_MEMCTL_5_CHANSEL_CHAN_30                                 0x0000001EU
#define ADC_MEMCTL_5_CHANSEL_CHAN_31                                 0x0000001FU
/*

        Field:           VRSEL
        From..to bits:   8...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Selects the combination of V(Rp) and V(Rn) sources.
                         It is recommended to connect VeREFn0 to on-board ground when VeREFn is selected for V(Rn).

                         Note: A value of 3 defaults to INTREF and value of 0 defaults to EXTREF.

        ENUMs:
            EXTREF:                      EXTREF pin reference.
            INTREF:                      INTREF reference.
*/
#define ADC_MEMCTL_5_VRSEL_W                                         2U
#define ADC_MEMCTL_5_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL_5_VRSEL_S                                         8U
#define ADC_MEMCTL_5_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL_5_VRSEL_INTREF                                    0x00000200U
/*

        Field:           STIME
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects the source of sample timer period. Can choose between SCOMP0 and SCOMP1.

        ENUMs:
            SEL_SCOMP0:                  Select SCOMP0.
            SEL_SCOMP1:                  Select SCOMP1.
*/
#define ADC_MEMCTL_5_STIME                                           0x00001000U
#define ADC_MEMCTL_5_STIME_M                                         0x00001000U
#define ADC_MEMCTL_5_STIME_S                                         12U
#define ADC_MEMCTL_5_STIME_SEL_SCOMP0                                0x00000000U
#define ADC_MEMCTL_5_STIME_SEL_SCOMP1                                0x00001000U
/*

        Field:           AVGEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable averaging.

        ENUMs:
            DISABLE:                     Averaging disabled.
            ENABLE:                      Averaging enabled.
*/
#define ADC_MEMCTL_5_AVGEN                                           0x00010000U
#define ADC_MEMCTL_5_AVGEN_M                                         0x00010000U
#define ADC_MEMCTL_5_AVGEN_S                                         16U
#define ADC_MEMCTL_5_AVGEN_DISABLE                                   0x00000000U
#define ADC_MEMCTL_5_AVGEN_ENABLE                                    0x00010000U
/*

        Field:           TRIG
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TRIG. Indicates if a trigger will be needed to step to the next MEMCTL in the sequence.

        ENUMs:
            AUTO_NEXT:                   Automatically step to next MEMCTL register.
            TRIGGER_NEXT:                A valid trigger will step to next MEMCTL register.
*/
#define ADC_MEMCTL_5_TRIG                                            0x01000000U
#define ADC_MEMCTL_5_TRIG_M                                          0x01000000U
#define ADC_MEMCTL_5_TRIG_S                                          24U
#define ADC_MEMCTL_5_TRIG_AUTO_NEXT                                  0x00000000U
#define ADC_MEMCTL_5_TRIG_TRIGGER_NEXT                               0x01000000U
/*

        Field:           WINCOMP
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Window Comparator Enable.
                         Select for the current conversion if the Window Comparator feature is used.

        ENUMs:
            DISABLE:                     Window Comparator is disabled.
            ENABLE:                      Window Comparator is enabled.
*/
#define ADC_MEMCTL_5_WINCOMP                                         0x10000000U
#define ADC_MEMCTL_5_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL_5_WINCOMP_S                                       28U
#define ADC_MEMCTL_5_WINCOMP_DISABLE                                 0x00000000U
#define ADC_MEMCTL_5_WINCOMP_ENABLE                                  0x10000000U
/*

        Field:           FSR
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Full scale range of ADC limited to 1.8V or 3.3V
                         '0' - 3.3V
                         '1' - 1.8V
                         * Exact range may be limited below the above mentioned voltages based on the design constraints

*/
#define ADC_MEMCTL_5_FSR                                             0x20000000U
#define ADC_MEMCTL_5_FSR_M                                           0x20000000U
#define ADC_MEMCTL_5_FSR_S                                           29U
/*

        Field:           MOD
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MODE

                         Single vs Differential

*/
#define ADC_MEMCTL_5_MOD                                             0x40000000U
#define ADC_MEMCTL_5_MOD_M                                           0x40000000U
#define ADC_MEMCTL_5_MOD_S                                           30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_0
    Offset name:         ADC_O_MEMRES_0
    Relative address:    0x1280
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_0_DATA_W                                          16U
#define ADC_MEMRES_0_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_0_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_1
    Offset name:         ADC_O_MEMRES_1
    Relative address:    0x1284
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_1_DATA_W                                          16U
#define ADC_MEMRES_1_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_1_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_2
    Offset name:         ADC_O_MEMRES_2
    Relative address:    0x1288
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_2_DATA_W                                          16U
#define ADC_MEMRES_2_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_2_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_3
    Offset name:         ADC_O_MEMRES_3
    Relative address:    0x128C
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_3_DATA_W                                          16U
#define ADC_MEMRES_3_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_3_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_4
    Offset name:         ADC_O_MEMRES_4
    Relative address:    0x1290
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_4_DATA_W                                          16U
#define ADC_MEMRES_4_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_4_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_5
    Offset name:         ADC_O_MEMRES_5
    Relative address:    0x1294
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_5_DATA_W                                          16U
#define ADC_MEMRES_5_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_5_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_6
    Offset name:         ADC_O_MEMRES_6
    Relative address:    0x1298
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_6_DATA_W                                          16U
#define ADC_MEMRES_6_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_6_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_7
    Offset name:         ADC_O_MEMRES_7
    Relative address:    0x129C
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_7_DATA_W                                          16U
#define ADC_MEMRES_7_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_7_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_8
    Offset name:         ADC_O_MEMRES_8
    Relative address:    0x12A0
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_8_DATA_W                                          16U
#define ADC_MEMRES_8_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_8_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_9
    Offset name:         ADC_O_MEMRES_9
    Relative address:    0x12A4
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_9_DATA_W                                          16U
#define ADC_MEMRES_9_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES_9_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_10
    Offset name:         ADC_O_MEMRES_10
    Relative address:    0x12A8
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_10_DATA_W                                         16U
#define ADC_MEMRES_10_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_10_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_11
    Offset name:         ADC_O_MEMRES_11
    Relative address:    0x12AC
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_11_DATA_W                                         16U
#define ADC_MEMRES_11_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_11_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_12
    Offset name:         ADC_O_MEMRES_12
    Relative address:    0x12B0
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_12_DATA_W                                         16U
#define ADC_MEMRES_12_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_12_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_13
    Offset name:         ADC_O_MEMRES_13
    Relative address:    0x12B4
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_13_DATA_W                                         16U
#define ADC_MEMRES_13_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_13_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_14
    Offset name:         ADC_O_MEMRES_14
    Relative address:    0x12B8
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_14_DATA_W                                         16U
#define ADC_MEMRES_14_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_14_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMRES_15
    Offset name:         ADC_O_MEMRES_15
    Relative address:    0x12BC
    Description:         Memory Results Register
    Default Value:       NA

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     MEMRESx result register.
                         If DATAFORMAT = 0, unsigned binary:
                         The conversion results are right aligned. In 14 and 12 bit mode, the unused MSB bits are forced to 0.

                         If DATAFORMAT = 1, 2s-complement format:
                         The conversion results are left aligned. In 14 and 12 bit mode, the unused LSB bits are forced to 0.

                         The data is stored in the right-justified format and is converted to the left-justified 2s-complement format during read back.
                         Reading this register clears the corresponding bit in RIS.

*/
#define ADC_MEMRES_15_DATA_W                                         16U
#define ADC_MEMRES_15_DATA_M                                         0x0000FFFFU
#define ADC_MEMRES_15_DATA_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STA
    Offset name:         ADC_O_STA
    Relative address:    0x1340
    Description:         STATUS

                        ULP_ADCHP Status Register 0
    Default Value:       0x00000000

        Field:           BUSY
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ULP_ADCHP busy. This bit indicates that an active sample or conversion operation is in progress.

        ENUMs:
            ACTIVE:                      A sample or conversion is in progress.
            IDLE:                        No sampling or conversion in progress.
*/
#define ADC_STA_BUSY                                                 0x00000001U
#define ADC_STA_BUSY_M                                               0x00000001U
#define ADC_STA_BUSY_S                                               0U
#define ADC_STA_BUSY_ACTIVE                                          0x00000001U
#define ADC_STA_BUSY_IDLE                                            0x00000000U
/*

        Field:           REFBUFRDY
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates reference buffer is powered up.

        ENUMs:
            READY:                       REFBUF is ready.
            NOTREADY:                    REFBUF not ready.
*/
#define ADC_STA_REFBUFRDY                                            0x00000002U
#define ADC_STA_REFBUFRDY_M                                          0x00000002U
#define ADC_STA_REFBUFRDY_S                                          1U
#define ADC_STA_REFBUFRDY_READY                                      0x00000002U
#define ADC_STA_REFBUFRDY_NOTREADY                                   0x00000000U
/*

        Field:           ASCACT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ASC active

        ENUMs:
            ACTIVE:                      ASC active
            IDLE:                        Idle or done
*/
#define ADC_STA_ASCACT                                               0x00000004U
#define ADC_STA_ASCACT_M                                             0x00000004U
#define ADC_STA_ASCACT_S                                             2U
#define ADC_STA_ASCACT_ACTIVE                                        0x00000004U
#define ADC_STA_ASCACT_IDLE                                          0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST0
    Offset name:         ADC_O_TEST0
    Relative address:    0x1E00
    Description:         Test0 register for ATB Mux sel for ATBBUF and ATBUNBUF
    Default Value:       0x00000000

        Field:           AMBUFSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ATBBUF MUX Sel
                         Bit 4: DIG LDO Output
                         Bit 3: Ana LDO output
                         Bit 2: CM buffer output
                         Bit 1 , and Bit 0 : VDDA3P3 signal

*/
#define ADC_TEST0_AMBUFSEL_W                                         5U
#define ADC_TEST0_AMBUFSEL_M                                         0x0000001FU
#define ADC_TEST0_AMBUFSEL_S                                         0U
/*

        Field:           AMUNBUFSEL
        From..to bits:   8...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ATBUNBUF MUX Sel
                         ull_dft_atb_usc_ulpadchp_unbuf_muxsel<4> : Vint REF BUF1 Output
                         ull_dft_atb_usc_ulpadchp_unbuf_muxsel<3> : Vint REF BUF2 Output
                         ull_dft_atb_usc_ulpadchp_unbuf_muxsel<2> : ADC internal VREFN signal
                         ull_dft_atb_usc_ulpadchp_unbuf_muxsel<1> : Not used
                         ull_dft_atb_usc_ulpadchp_unbuf_muxsel<0> : Not used

*/
#define ADC_TEST0_AMUNBUFSEL_W                                       5U
#define ADC_TEST0_AMUNBUFSEL_M                                       0x00001F00U
#define ADC_TEST0_AMUNBUFSEL_S                                       8U
/*

        Field:           ATBUNBUFEN
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ATB_UNBUF Enable
                         ADC Signal = ull_dft_atb_usc_ulpadchp_en<0> := 1

*/
#define ADC_TEST0_ATBUNBUFEN                                         0x20000000U
#define ADC_TEST0_ATBUNBUFEN_M                                       0x20000000U
#define ADC_TEST0_ATBUNBUFEN_S                                       29U
/*

        Field:           ATBBUFEN
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ATB_BUF Enable
                         ADC Signal = ull_dft_atb_usc_ulpadchp_en<1> := 1

*/
#define ADC_TEST0_ATBBUFEN                                           0x40000000U
#define ADC_TEST0_ATBBUFEN_M                                         0x40000000U
#define ADC_TEST0_ATBBUFEN_S                                         30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST1
    Offset name:         ADC_O_TEST1
    Relative address:    0x1E04
    Description:         DTB MUX Selection
    Default Value:       0x00000000

        Field:           DTBMSEL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DTB Mux Sel
                         ull_dft_dtb_usc_ulpadchp_muxsel<0x0> :  ADC 16 bit data
                         ull_dft_dtb_usc_ulpadchp_muxsel<0x1> :
                         DTB0: ADC CLK DIV2
                         DTB1 - 9 : See implementation document for detail signal name.

*/
#define ADC_TEST1_DTBMSEL_W                                          5U
#define ADC_TEST1_DTBMSEL_M                                          0x0000001FU
#define ADC_TEST1_DTBMSEL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST2
    Offset name:         ADC_O_TEST2
    Relative address:    0x1E08
    Description:         ATB Ch sel as ADC input
                        MUX Test mode sel, ATB REF and CAP OSVT enable
    Default Value:       0x00000000

        Field:           MUXTSEL
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MUX TEST SELECTOR

                         ADC Input MUX test mode selection:
                         ull_usc_ulpachp_mux_testmode_i<1:0>: 0x01 : Selected Even ch short with ATBBUF CH sel
                         ull_usc_ulpachp_mux_testmode_i<1:0>: 0x10 : Selected Odd ch short with ATBUnBUFCh sel

*/
#define ADC_TEST2_MUXTSEL                                            0x00000100U
#define ADC_TEST2_MUXTSEL_M                                          0x00000100U
#define ADC_TEST2_MUXTSEL_S                                          8U
/*

        Field:           CMPGNTRIM
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     COMP GAIN TRIM

                         Resistor Trim Enable Control Signal
                         ull_usc_ulpadchp_dft_i<30>:1 -> Resistor Trim Enable Control Signal

*/
#define ADC_TEST2_CMPGNTRIM                                          0x00100000U
#define ADC_TEST2_CMPGNTRIM_M                                        0x00100000U
#define ADC_TEST2_CMPGNTRIM_S                                        20U
/*

        Field:           LTRIMEN
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Latch trim enable.

*/
#define ADC_TEST2_LTRIMEN                                            0x01000000U
#define ADC_TEST2_LTRIMEN_M                                          0x01000000U
#define ADC_TEST2_LTRIMEN_S                                          24U
/*

        Field:           CDACOVSTEN
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADC P_CDAC CAP OVST Enable Control Signal
                         ull_usc_ulpadchp_dft_i<31>:1 -> ADC CDAC CAP OVST Enable Control Signal

*/
#define ADC_TEST2_CDACOVSTEN                                         0x80000000U
#define ADC_TEST2_CDACOVSTEN_M                                       0x80000000U
#define ADC_TEST2_CDACOVSTEN_S                                       31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST3
    Offset name:         ADC_O_TEST3
    Relative address:    0x1E0C
    Description:         ADC CAL Accumulation Register
    Default Value:       0x00000000

        Field:           CALACUML
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Accumulation of # samples during Calibration step

*/
#define ADC_TEST3_CALACUML_W                                         32U
#define ADC_TEST3_CALACUML_M                                         0xFFFFFFFFU
#define ADC_TEST3_CALACUML_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST4
    Offset name:         ADC_O_TEST4
    Relative address:    0x1E10
    Description:         CAL Control register: Average Sample count, Step number, Recall En and Debug option to override ull_usc_ulpadchp_dft_i<26:0>.
    Default Value:       0x00000000

        Field:           CALSTPSEL
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADC CAL STEP SELECTION

*/
#define ADC_TEST4_CALSTPSEL_W                                        6U
#define ADC_TEST4_CALSTPSEL_M                                        0x003F0000U
#define ADC_TEST4_CALSTPSEL_S                                        16U
/*

        Field:           CALMODEN
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADC CDAC Calibration mode enable

*/
#define ADC_TEST4_CALMODEN                                           0x01000000U
#define ADC_TEST4_CALMODEN_M                                         0x01000000U
#define ADC_TEST4_CALMODEN_S                                         24U
/*

        Field:           HWSTPSELDIS
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     By Enabling this bit, DLC written value overwritten of ull_usc_ulpadchp_dft_i<26:0> from TEST7 register.
                         This is for debug.

*/
#define ADC_TEST4_HWSTPSELDIS                                        0x80000000U
#define ADC_TEST4_HWSTPSELDIS_M                                      0x80000000U
#define ADC_TEST4_HWSTPSELDIS_S                                      31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST5
    Offset name:         ADC_O_TEST5
    Relative address:    0x1E14
    Description:         This register updated ull_usc_ulpadchp_dft_i[26:0] value  if Test 5: HW_STEP_SEL_DIS bit enable
    Default Value:       0x00000000

        Field:           CALCAPCTL
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This register updated ull_usc_ulpadchp_dft_i[26:0] value  if Test 5: HW_STEP_SEL_DIS bit enabled
                         ull_usc_ulpadchp_dft_i[26:0]

*/
#define ADC_TEST5_CALCAPCTL_W                                        10U
#define ADC_TEST5_CALCAPCTL_M                                        0x000003FFU
#define ADC_TEST5_CALCAPCTL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TEST6
    Offset name:         ADC_O_TEST6
    Relative address:    0x1E18
    Description:         REFBUF ATB selection. This register is used to select the REFBUF signals on ATB.
    Default Value:       0x00000000

        Field:           ATBSEL
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ATB selection. The undefined values are reserved and should not be used.

        ENUMs:
            VAL0:                        Both ATEST0 and ATEST1 switches are open
            VAL1:                        REFBUF output (ATEST0/BUF path)
            VAL2:                        1st stage output (ATEST0/BUF path)

            VAL4:                        Resistor ladder feedback (ATEST0/BUF path)
            VAL8:                        1st stage source (ATEST1/UNBUF path)
*/
#define ADC_TEST6_ATBSEL_W                                           4U
#define ADC_TEST6_ATBSEL_M                                           0x0000000FU
#define ADC_TEST6_ATBSEL_S                                           0U
#define ADC_TEST6_ATBSEL_VAL0                                        0x00000000U
#define ADC_TEST6_ATBSEL_VAL1                                        0x00000001U
#define ADC_TEST6_ATBSEL_VAL2                                        0x00000002U
#define ADC_TEST6_ATBSEL_VAL4                                        0x00000004U
#define ADC_TEST6_ATBSEL_VAL8                                        0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBG1
    Offset name:         ADC_O_DBG1
    Relative address:    0x1E20
    Description:         DEBUG1

                        COMP CTL Debug register
    Default Value:       0x00801000

        Field:           CTRL
        From..to bits:   0...31
        DefaultValue:    0x801000
        Access type:     read-write
        Description:     COMP Debug signals control
                         ull_usc_ulpadchp_ctrl_comp_i[31]: Enable the use of external value for comaparor gain and IB settings

*/
#define ADC_DBG1_CTRL_W                                              32U
#define ADC_DBG1_CTRL_M                                              0xFFFFFFFFU
#define ADC_DBG1_CTRL_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBG2
    Offset name:         ADC_O_DBG2
    Relative address:    0x1E24
    Description:         DEBUG 2

                        OSC, LATCH_OS, VTOI Debug CTL register
    Default Value:       0x00000000

        Field:           VTSTODEN
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VTOI TETSMODE Enable

*/
#define ADC_DBG2_VTSTODEN                                            0x01000000U
#define ADC_DBG2_VTSTODEN_M                                          0x01000000U
#define ADC_DBG2_VTSTODEN_S                                          24U
/*

        Field:           VTOICTL
        From..to bits:   28...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VTOI Debug Signals control
                         ull_usc_ulpadchp_ctrl_vtoi_i[3:0]

*/
#define ADC_DBG2_VTOICTL_W                                           2U
#define ADC_DBG2_VTOICTL_M                                           0x30000000U
#define ADC_DBG2_VTOICTL_S                                           28U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBG3
    Offset name:         ADC_O_DBG3
    Relative address:    0x1E28
    Description:         DEBUG 3

                        Boost, DCLK Sel, Int coex dirty and Dec disable debug control register
    Default Value:       0x00000000

        Field:           BSTENZ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BOOST ENZ

*/
#define ADC_DBG3_BSTENZ                                              0x00000001U
#define ADC_DBG3_BSTENZ_M                                            0x00000001U
#define ADC_DBG3_BSTENZ_S                                            0U
/*

        Field:           DEC0DIS
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DEC0 Disable control signal

*/
#define ADC_DBG3_DEC0DIS                                             0x00000010U
#define ADC_DBG3_DEC0DIS_M                                           0x00000010U
#define ADC_DBG3_DEC0DIS_S                                           4U
/*

        Field:           DEC1DIS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DEC1 Disable control signal

*/
#define ADC_DBG3_DEC1DIS                                             0x00000020U
#define ADC_DBG3_DEC1DIS_M                                           0x00000020U
#define ADC_DBG3_DEC1DIS_S                                           5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBG4
    Offset name:         ADC_O_DBG4
    Relative address:    0x1E2C
    Description:         DEBUG 4

                        ADC MSIP Control signal for Debug: adc_ctrl<31:0>
    Default Value:       0x00000000

        Field:           ADCCTL0
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADC CONTROL 0

                         ADC MSIP Control signal for Debug: adc_ctrl<15:0>

*/
#define ADC_DBG4_ADCCTL0_W                                           16U
#define ADC_DBG4_ADCCTL0_M                                           0x0000FFFFU
#define ADC_DBG4_ADCCTL0_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CONVCTL
    Offset name:         ADC_O_CONVCTL
    Relative address:    0x1F14
    Description:         Conversion Control
    Default Value:       NA

        Field:           DAC
        From..to bits:   0...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     000 : 1 Clock delay, ...., 111 : 8 Clock delay

*/
#define ADC_CONVCTL_DAC_W                                            3U
#define ADC_CONVCTL_DAC_M                                            0x00000007U
#define ADC_CONVCTL_DAC_S                                            0U
/*

        Field:           PREAMP
        From..to bits:   3...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     00 : 1 Clock delay, ..., 11 : 4 Clock delay

*/
#define ADC_CONVCTL_PREAMP_W                                         2U
#define ADC_CONVCTL_PREAMP_M                                         0x00000018U
#define ADC_CONVCTL_PREAMP_S                                         3U
/*

        Field:           HOLD
        From..to bits:   5...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     000 : 1 Clock delay, ...., 111 : 8 Clock delay
                         bit[3] - don't care and not used

*/
#define ADC_CONVCTL_HOLD_W                                           4U
#define ADC_CONVCTL_HOLD_M                                           0x000001E0U
#define ADC_CONVCTL_HOLD_S                                           5U
/*

        Field:           OV
        From..to bits:   15...15
        DefaultValue:    NA
        Access type:     read-write
        Description:     OVERRIDE

                         1 : Override, 0 : Use LUT values

                         LUT is mentioned since the proposal was to pick up values automatically based on Internal vs External reference

*/
#define ADC_CONVCTL_OV                                               0x00008000U
#define ADC_CONVCTL_OV_M                                             0x00008000U
#define ADC_CONVCTL_OV_S                                             15U
/*

        Field:           CONCLKSEL
        From..to bits:   16...17
        DefaultValue:    NA
        Access type:     read-write
        Description:     CONVERSION CLOCK SELECTOR

                         ADC functional clock selection

                         0x0 - (Reset/Default) CLK_GATE
                         0x1 - SOC_CLK
                         0x2 - HFXT
                         0x3 - SOC_PLL_CLK_DIV

                         note: not glitch free, therefore ICG should be enabled after selecting the right clk

*/
#define ADC_CONVCTL_CONCLKSEL_W                                      2U
#define ADC_CONVCTL_CONCLKSEL_M                                      0x00030000U
#define ADC_CONVCTL_CONCLKSEL_S                                      16U
/*

        Field:           CONVCLKEN
        From..to bits:   18...18
        DefaultValue:    NA
        Access type:     read-write
        Description:     CONV CLK ICG EN

                         should be enabled after selecting CONV CLK

*/
#define ADC_CONVCTL_CONVCLKEN                                        0x00040000U
#define ADC_CONVCTL_CONVCLKEN_M                                      0x00040000U
#define ADC_CONVCTL_CONVCLKEN_S                                      18U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTRL
    Offset name:         ADC_O_CTRL
    Relative address:    0x1F18
    Description:
    Default Value:       0x00000000

        Field:           FSBIT0
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FUSE BITS 0

                         values for fuse OV

*/
#define ADC_CTRL_FSBIT0_W                                            9U
#define ADC_CTRL_FSBIT0_M                                            0x000001FFU
#define ADC_CTRL_FSBIT0_S                                            0U
/*

        Field:           FSBIT1
        From..to bits:   9...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     FUSE BITS 1

                         values for fuse OV

*/
#define ADC_CTRL_FSBIT1_W                                            8U
#define ADC_CTRL_FSBIT1_M                                            0x0001FE00U
#define ADC_CTRL_FSBIT1_S                                            9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MODCTL
    Offset name:         ADC_O_MODCTL
    Relative address:    0x1F1C
    Description:         MODE CONTROL
    Default Value:       0x00000000

        Field:           VREFRAN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VOLTAGE REFERENCE RANGE

                         0 --> 0 - 4095 in 0 - 3.2V
                         1 --> 0 - 4095 in 0.1 to 3.3V

                         Only in Single Ended mode

*/
#define ADC_MODCTL_VREFRAN                                           0x00000001U
#define ADC_MODCTL_VREFRAN_M                                         0x00000001U
#define ADC_MODCTL_VREFRAN_S                                         0U
/*

        Field:           SCASEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SCALE SELECT

                         0 --> Normal output
                         1 --> scale 0-4223 in 0-4095 (efectively supporting 0-3.3V in 12 bit space)

*/
#define ADC_MODCTL_SCASEL                                            0x00000002U
#define ADC_MODCTL_SCASEL_M                                          0x00000002U
#define ADC_MODCTL_SCASEL_S                                          1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INTCHCTL
    Offset name:         ADC_O_INTCHCTL
    Relative address:    0x1F20
    Description:         INTERNAL CHANNEL CONTROL
    Default Value:       0x00000000

        Field:           RLVAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RLADDER VALUE

                         0 --> 0 - 4095 in 0 - 3.2V
                         1 --> 0 - 4095 in 0.1 to 3.3V

                         Only in Single Ended mode

*/
#define ADC_INTCHCTL_RLVAL                                           0x00000001U
#define ADC_INTCHCTL_RLVAL_M                                         0x00000001U
#define ADC_INTCHCTL_RLVAL_S                                         0U
/*

        Field:           RLOV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RLADDER OVERRIDE

                         Override Enable/Disable control for R-ladder inside RFCIO.
                         This provides divided voltage to ADC by limiting the max. voltage.
                         Default : 0 use value driven by ADC FSM

*/
#define ADC_INTCHCTL_RLOV                                            0x00000002U
#define ADC_INTCHCTL_RLOV_M                                          0x00000002U
#define ADC_INTCHCTL_RLOV_S                                          1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STLTIM
    Offset name:         ADC_O_STLTIM
    Relative address:    0x1F24
    Description:         SETTLING TIME
    Default Value:       0x01670027

        Field:           SWCTRLDEL
        From..to bits:   0...5
        DefaultValue:    0x27
        Access type:     read-write
        Description:     SWITCH CONTROL DELAY
                         delay value for SWITCH CONTROL.
                         calculated using conv clk
                         '1' - 2 conv clks
                         '2' - 3 conv clks
                         ...
                         '3F' - 64 conv clks

*/
#define ADC_STLTIM_SWCTRLDEL_W                                       6U
#define ADC_STLTIM_SWCTRLDEL_M                                       0x0000003FU
#define ADC_STLTIM_SWCTRLDEL_S                                       0U
/*

        Field:           RCSETDEL
        From..to bits:   16...25
        DefaultValue:    0x167
        Access type:     read-write
        Description:     RC SETTLING DELAY
                         delay value for RC SETTLING DELAY. value should be added to switch control delay.
                         calculated using conv clk
                         '1' - 1 conv clks
                         '2' - 2 conv clks
                         ...
                         '3FF' - 1023 conv clks

*/
#define ADC_STLTIM_RCSETDEL_W                                        10U
#define ADC_STLTIM_RCSETDEL_M                                        0x03FF0000U
#define ADC_STLTIM_RCSETDEL_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         ADC_O_CLKCFG
    Relative address:    0x2000
    Description:         ADC CLK CONFIG
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ENABLE

                         enables system clk to work with ADC
                         '1' - enable adc clk
                         '0' - disable adc clk

*/
#define ADC_CLKCFG_EN                                                0x00000001U
#define ADC_CLKCFG_EN_M                                              0x00000001U
#define ADC_CLKCFG_EN_S                                              0U

#endif /* __HW_ADC_H__*/
