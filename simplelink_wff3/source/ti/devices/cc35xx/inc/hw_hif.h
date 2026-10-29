/******************************************************************************
*  Filename:       hw_hif.h
*
*  Description:    Defines and prototypes for the HIF peripheral.
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
#ifndef __HW_HIF_H__
#define __HW_HIF_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HIF component

--------------------------------------------------------------------------------- */

//INTERCONNECT WRITE FIFO
#define HIF_O_ICWRFIFO                                               0x00000000U

//INTERCONNECT READ FIFO
#define HIF_O_ICRDFIFO                                               0x00000010U

//MODE
#define HIF_O_MOD                                                    0x00000024U

//HIF FIFO Status
#define HIF_O_FIFOSTA                                                0x0000002CU

//UNDERFLOW
#define HIF_O_UNDER                                                  0x00000030U

//OVERFLOW
#define HIF_O_OVER                                                   0x00000034U

//RESET
#define HIF_O_RST                                                    0x00000038U

//FSM STATUS
#define HIF_O_FSMSTA                                                 0x0000003CU

//HIF FIFO Threshold Status
#define HIF_O_FIFOTH                                                 0x00000040U

//IRQ
#define HIF_O_IRQ                                                    0x00000044U

//IRQ MASK Config
#define HIF_O_IM                                                     0x00000048U

//NAB READY
#define HIF_O_NABRDY                                                 0x0000004CU

//CORE
#define HIF_O_CR                                                     0x00000050U

//RX AON
#define HIF_O_RXAON                                                  0x00000054U

//RX STATUS LATCH
#define HIF_O_RXSTALAT                                               0x00000058U

//NAB HINT STATUS
#define HIF_O_NABHNTSTA                                              0x0000005CU

//NAB
#define HIF_O_NAB                                                    0x00000060U

//HINT BIT MASK
#define HIF_O_HNTBM                                                  0x00000064U

//HINT BIT MASK CLEAR
#define HIF_O_HNTBMCLR                                               0x00000068U

//HINT STATUS CLEAR
#define HIF_O_HNTSTACLR                                              0x0000006CU

//NAB HINT
#define HIF_O_NABHNT                                                 0x00000070U

//NAB HINT CLEAR
#define HIF_O_NABHNTCLR                                              0x00000074U



/*-----------------------------------REGISTER------------------------------------
    Register name:       ICWRFIFO
    Offset name:         HIF_O_ICWRFIFO
    Relative address:    0x0
    Description:         INTERCONNECT WRITE FIFO

                        Host interface FIFO
    Default Value:       NA

        Field:           WORD
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     write-only
        Description:     WORD

                         write opt

                         IC to NAB write word

*/
#define HIF_ICWRFIFO_WORD_W                                          32U
#define HIF_ICWRFIFO_WORD_M                                          0xFFFFFFFFU
#define HIF_ICWRFIFO_WORD_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICRDFIFO
    Offset name:         HIF_O_ICRDFIFO
    Relative address:    0x10
    Description:         INTERCONNECT READ FIFO

                        Host interface FIFO
    Default Value:       0xEEEEEEEE

        Field:           WORD
        From..to bits:   0...31
        DefaultValue:    0xEEEEEEEE
        Access type:     read-only
        Description:     WORD

                         read clear

                         NAB to IC read word

*/
#define HIF_ICRDFIFO_WORD_W                                          32U
#define HIF_ICRDFIFO_WORD_M                                          0xFFFFFFFFU
#define HIF_ICRDFIFO_WORD_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MOD
    Offset name:         HIF_O_MOD
    Relative address:    0x24
    Description:         MODE

                        HIF Mode Configuration
    Default Value:       NA

        Field:           CFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     CONFIG

                         "00" - Direct Access WR
                         "01" - DMA WR
                         "10" - Direct Access RD
                         "11" - DMA RD

*/
#define HIF_MOD_CFG_W                                                2U
#define HIF_MOD_CFG_M                                                0x00000003U
#define HIF_MOD_CFG_S                                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOSTA
    Offset name:         HIF_O_FIFOSTA
    Relative address:    0x2C
    Description:         HIF FIFO Status
    Default Value:       0x00000001

        Field:           RDPTR
        From..to bits:   0...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     READ POINTER

*/
#define HIF_FIFOSTA_RDPTR_W                                          5U
#define HIF_FIFOSTA_RDPTR_M                                          0x0000001FU
#define HIF_FIFOSTA_RDPTR_S                                          0U
/*

        Field:           WRPTR
        From..to bits:   8...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     WRITE POINTER

*/
#define HIF_FIFOSTA_WRPTR_W                                          5U
#define HIF_FIFOSTA_WRPTR_M                                          0x00001F00U
#define HIF_FIFOSTA_WRPTR_S                                          8U
/*

        Field:           EMP
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     EMPTY

*/
#define HIF_FIFOSTA_EMP                                              0x00100000U
#define HIF_FIFOSTA_EMP_M                                            0x00100000U
#define HIF_FIFOSTA_EMP_S                                            20U
/*

        Field:           FULL
        From..to bits:   21...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FULL

*/
#define HIF_FIFOSTA_FULL                                             0x00200000U
#define HIF_FIFOSTA_FULL_M                                           0x00200000U
#define HIF_FIFOSTA_FULL_S                                           21U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UNDER
    Offset name:         HIF_O_UNDER
    Relative address:    0x30
    Description:         UNDERFLOW

                        clear on read.
                        H/W latch underflow and s/w clears it by reading.
    Default Value:       NA

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     STATUS

                         read clear

                         FIFO Underflow - RD when FIFO is empty.

*/
#define HIF_UNDER_STA                                                0x00000001U
#define HIF_UNDER_STA_M                                              0x00000001U
#define HIF_UNDER_STA_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OVER
    Offset name:         HIF_O_OVER
    Relative address:    0x34
    Description:         OVERFLOW

                        clear on read.
                        H/W latch overflow and s/w clears it by reading.
    Default Value:       NA

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     STATUS

                         read clear

                         FIFO Overflow - WR when FIFO is full.

*/
#define HIF_OVER_STA                                                 0x00000001U
#define HIF_OVER_STA_M                                               0x00000001U
#define HIF_OVER_STA_S                                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RST
    Offset name:         HIF_O_RST
    Relative address:    0x38
    Description:         RESET

                        HIF FIFO set RESET
    Default Value:       NA

        Field:           FIFO
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     FIFO

                         write clear

                         Setting this bit clears the FIFO Controls.

*/
#define HIF_RST_FIFO                                                 0x00000001U
#define HIF_RST_FIFO_M                                               0x00000001U
#define HIF_RST_FIFO_S                                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FSMSTA
    Offset name:         HIF_O_FSMSTA
    Relative address:    0x3C
    Description:         FSM STATUS
    Default Value:       NA

        Field:           HANDLER
        From..to bits:   0...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     HANDLER

                          IDLE                            = 3'b000
                          DMA_BL_WR               = 3'b101
                          DMA_HOLD_WR          = 3'b110
                          DIRECT_ACCESS_WR  = 3'b111
                          NAB_WR                     = 3'b001
                          DMA_BL_RD               = 3'b010
                          DIRECT_ACCESS_RD  = 3'b011 ;

*/
#define HIF_FSMSTA_HANDLER_W                                         3U
#define HIF_FSMSTA_HANDLER_M                                         0x00000007U
#define HIF_FSMSTA_HANDLER_S                                         0U
/*

        Field:           WRNAB
        From..to bits:   8...10
        DefaultValue:    NA
        Access type:     read-only
        Description:     WRITE NAB

*/
#define HIF_FSMSTA_WRNAB_W                                           3U
#define HIF_FSMSTA_WRNAB_M                                           0x00000700U
#define HIF_FSMSTA_WRNAB_S                                           8U
/*

        Field:           RDNAB
        From..to bits:   16...18
        DefaultValue:    NA
        Access type:     read-only
        Description:     READ NAB

*/
#define HIF_FSMSTA_RDNAB_W                                           3U
#define HIF_FSMSTA_RDNAB_M                                           0x00070000U
#define HIF_FSMSTA_RDNAB_S                                           16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FIFOTH
    Offset name:         HIF_O_FIFOTH
    Relative address:    0x40
    Description:         HIF FIFO Threshold Status
    Default Value:       0x0000000F

        Field:           THR
        From..to bits:   0...3
        DefaultValue:    0xF
        Access type:     read-write
        Description:     THRESHOLD

                         Sets the HIF threshold:
                         for TX (DMA to NAB)-
                         0 - if there is room for 1 word the req to DMA will be send
                         ...
                         15 - if there is room for 16 words the req to DMA will be send

                         for RX (NAB to DMA)-
                         0 - if FIFO is occupied by at lest 1 word, the req to DMA will be send
                         ...
                         15 - if FIFO is occupied by at lest 16 word, the req to DMA will be send

*/
#define HIF_FIFOTH_THR_W                                             4U
#define HIF_FIFOTH_THR_M                                             0x0000000FU
#define HIF_FIFOTH_THR_S                                             0U
/*

        Field:           WRTHRNTHIT
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     WRITE THRESHOLD NOT HIT

                         indication if the write threshold not hit

*/
#define HIF_FIFOTH_WRTHRNTHIT                                        0x00000100U
#define HIF_FIFOTH_WRTHRNTHIT_M                                      0x00000100U
#define HIF_FIFOTH_WRTHRNTHIT_S                                      8U
/*

        Field:           RDTHRHIT
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     READ THRESHOLD HIT

                         indication if the read threshold hit

*/
#define HIF_FIFOTH_RDTHRHIT                                          0x00000200U
#define HIF_FIFOTH_RDTHRHIT_M                                        0x00000200U
#define HIF_FIFOTH_RDTHRHIT_S                                        9U
/*

        Field:           SZAVAIL
        From..to bits:   16...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SIZE AVAILABLE

                         indication of free space left at FIFO
                         0 - FIFO full
                         1 - 1 word can be written
                         ...
                         16 - 16 words can be written

*/
#define HIF_FIFOTH_SZAVAIL_W                                         5U
#define HIF_FIFOTH_SZAVAIL_M                                         0x001F0000U
#define HIF_FIFOTH_SZAVAIL_S                                         16U
/*

        Field:           SZOCC
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SIZE OCCUPIED

                         indication of how many words have been written to FIFO
                         0 - nothing was written
                         1 - 1 word have been written
                         ...
                         16 - 16 words have been written

*/
#define HIF_FIFOTH_SZOCC_W                                           5U
#define HIF_FIFOTH_SZOCC_M                                           0x1F000000U
#define HIF_FIFOTH_SZOCC_S                                           24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ
    Offset name:         HIF_O_IRQ
    Relative address:    0x44
    Description:         IRQ
    Default Value:       0x00000001

        Field:           RIS
        From..to bits:   0...5
        DefaultValue:    0x1
        Access type:     read-only
        Description:     RIS

                         read clear

                         bit[0] - empty
                         bit[1] - full
                         bit[2] - underflow
                         bit[3] - overflow
                         bit[4] - not empty with direct access read
                         bit[5] - nab data receive done

*/
#define HIF_IRQ_RIS_W                                                6U
#define HIF_IRQ_RIS_M                                                0x0000003FU
#define HIF_IRQ_RIS_S                                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IM
    Offset name:         HIF_O_IM
    Relative address:    0x48
    Description:         IRQ MASK Config
    Default Value:       0x0000003F

        Field:           EVTBM
        From..to bits:   0...5
        DefaultValue:    0x3F
        Access type:     read-write
        Description:     EVENT BIT MASK

                         '1' - Mask
                         '0' - Do Not Mask

                         bit[0] - empty
                         bit[1] - full
                         bit[2] - underflow
                         bit[3] - overflow
                         bit[4] - not empty with direct access read
                         bit[5] - nab data receive done

*/
#define HIF_IM_EVTBM_W                                               6U
#define HIF_IM_EVTBM_M                                               0x0000003FU
#define HIF_IM_EVTBM_S                                               0U
/*

        Field:           STA
        From..to bits:   6...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     STATUS

                         bit[0] - empty
                         bit[1] - full
                         bit[2] - underflow
                         bit[3] - overflow
                         bit[4] - not empty with direct access read
                         bit[5] - nab data receive done

*/
#define HIF_IM_STA_W                                                 6U
#define HIF_IM_STA_M                                                 0x00000FC0U
#define HIF_IM_STA_S                                                 6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NABRDY
    Offset name:         HIF_O_NABRDY
    Relative address:    0x4C
    Description:         NAB READY

                        HIF Mode Configuration
    Default Value:       NA

        Field:           TORCV
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     TO RECEIVE

                         indication when NAB is ready to receive data

*/
#define HIF_NABRDY_TORCV                                             0x00000001U
#define HIF_NABRDY_TORCV_M                                           0x00000001U
#define HIF_NABRDY_TORCV_S                                           0U
/*

        Field:           RCVDONE
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     RECEIVE DONE

                         indication when NAB data recieve done

*/
#define HIF_NABRDY_RCVDONE                                           0x00000002U
#define HIF_NABRDY_RCVDONE_M                                         0x00000002U
#define HIF_NABRDY_RCVDONE_S                                         1U
/*

        Field:           RCVDONEM2MIDL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     RECEIVE DONE AND M2M IDLE

                         indication when NAB data recieve done and M2M FSM IDLE

*/
#define HIF_NABRDY_RCVDONEM2MIDL                                     0x00000004U
#define HIF_NABRDY_RCVDONEM2MIDL_M                                   0x00000004U
#define HIF_NABRDY_RCVDONEM2MIDL_S                                   2U
/*

        Field:           FIFONEMPT
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     NAB HOST FIFO NOT EMPTY

                         indication when NAB FIFO not empty

*/
#define HIF_NABRDY_FIFONEMPT                                         0x00000008U
#define HIF_NABRDY_FIFONEMPT_M                                       0x00000008U
#define HIF_NABRDY_FIFONEMPT_S                                       3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CR
    Offset name:         HIF_O_CR
    Relative address:    0x50
    Description:         CORE

                        HIF Mode Configuration
    Default Value:       NA

        Field:           TMSTMP
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     TIMESTAMP

*/
#define HIF_CR_TMSTMP_W                                              32U
#define HIF_CR_TMSTMP_M                                              0xFFFFFFFFU
#define HIF_CR_TMSTMP_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXAON
    Offset name:         HIF_O_RXAON
    Relative address:    0x54
    Description:         RX AON
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     STATUS

                         read clear


                         This is not a regular clear-on-read register.
                         A fresh status value from Rx sub system is being latch upon reading the register.
                         The objective is for the device to have the last value the host has read

*/
#define HIF_RXAON_STA_W                                              32U
#define HIF_RXAON_STA_M                                              0xFFFFFFFFU
#define HIF_RXAON_STA_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXSTALAT
    Offset name:         HIF_O_RXSTALAT
    Relative address:    0x58
    Description:         RX STATUS LATCH
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     VALUE

                         Reflects the Rx status word current value (dynamic Read).
                         and automatically latch the value in RX_STATUS_LATCH_LATCHED.

                         Usage:  SDIO Wrapper reads this location and send the read value toward the host.

                         For bit field description refer to RX_STATUS_LATCH.

                         This register is valid only in BSD_BYPASS=1 (Osprey).

*/
#define HIF_RXSTALAT_VAL_W                                           32U
#define HIF_RXSTALAT_VAL_M                                           0xFFFFFFFFU
#define HIF_RXSTALAT_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NABHNTSTA
    Offset name:         HIF_O_NABHNTSTA
    Relative address:    0x5C
    Description:         NAB HINT STATUS
    Default Value:       NA

        Field:           BMVAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     BIT MASK VALUE

                         Host interrupt status read register. non-intrusive read. Post mask (masked).

*/
#define HIF_NABHNTSTA_BMVAL_W                                        32U
#define HIF_NABHNTSTA_BMVAL_M                                        0xFFFFFFFFU
#define HIF_NABHNTSTA_BMVAL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NAB
    Offset name:         HIF_O_NAB
    Relative address:    0x60
    Description:         NAB
    Default Value:       NA

        Field:           BMVAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     BIT MASK VALUE

                         Read mask bitmap.

                         Mask bit legend:
                         '0' - do not mask the interrupt.
                         '1' - Mask the related interrupt.

*/
#define HIF_NAB_BMVAL_W                                              32U
#define HIF_NAB_BMVAL_M                                              0xFFFFFFFFU
#define HIF_NAB_BMVAL_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HNTBM
    Offset name:         HIF_O_HNTBM
    Relative address:    0x64
    Description:         HINT BIT MASK
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     write-only
        Description:     VALUE

                         write clear

                         Host interrupt mask register set
                         Writing to this register will set to '1' the related interrupt mask bit.

                         Mask bit legend:
                         '0' - do not mask the interrupt.
                         '1' - Mask the related interrupt.

*/
#define HIF_HNTBM_VAL_W                                              32U
#define HIF_HNTBM_VAL_M                                              0xFFFFFFFFU
#define HIF_HNTBM_VAL_S                                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HNTBMCLR
    Offset name:         HIF_O_HNTBMCLR
    Relative address:    0x68
    Description:         HINT BIT MASK CLEAR
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     write-only
        Description:     VALUE

                         write clear

                         Host interrupt mask register clear
                         Writing to this register will clear the related interrupt mask bit.

                         Mask bit legend:
                         '0' - do not mask the interrupt.
                         '1' - Mask the related interrupt.

*/
#define HIF_HNTBMCLR_VAL_W                                           32U
#define HIF_HNTBMCLR_VAL_M                                           0xFFFFFFFFU
#define HIF_HNTBMCLR_VAL_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HNTSTACLR
    Offset name:         HIF_O_HNTSTACLR
    Relative address:    0x6C
    Description:         HINT STATUS CLEAR
    Default Value:       NA

        Field:           STA
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     STATUS

                         read clear

                         Host interrupt status clear-on-read register
                         Clears all bits of upon read.
                         Usage: host reads the IRQ register which is automatically getting cleared by H/W
                         Osprey Note: The endianness correction and word-size correction are done in SDIO(WSPI) H/W.

*/
#define HIF_HNTSTACLR_STA_W                                          32U
#define HIF_HNTSTACLR_STA_M                                          0xFFFFFFFFU
#define HIF_HNTSTACLR_STA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NABHNT
    Offset name:         HIF_O_NABHNT
    Relative address:    0x70
    Description:         NAB HINT
    Default Value:       NA

        Field:           SET
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     write-only
        Description:     SET

                         write clear register

                         Host interrupt set register

*/
#define HIF_NABHNT_SET_W                                             32U
#define HIF_NABHNT_SET_M                                             0xFFFFFFFFU
#define HIF_NABHNT_SET_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NABHNTCLR
    Offset name:         HIF_O_NABHNTCLR
    Relative address:    0x74
    Description:         NAB HINT CLEAR
    Default Value:       NA

        Field:           SET
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     write-only
        Description:     SET

                         write clear register

                         Host interrupt clear register


*/
#define HIF_NABHNTCLR_SET_W                                          32U
#define HIF_NABHNTCLR_SET_M                                          0xFFFFFFFFU
#define HIF_NABHNTCLR_SET_S                                          0U

#endif /* __HW_HIF_H__*/
