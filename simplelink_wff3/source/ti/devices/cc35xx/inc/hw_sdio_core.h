/******************************************************************************
*  Filename:       hw_sdio_core.h
*
*  Description:    Defines and prototypes for the SDIO_CORE peripheral.
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
#ifndef __HW_SDIO_CORE_H__
#define __HW_SDIO_CORE_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SDIO_CORE component

--------------------------------------------------------------------------------- */

//CCCR00
#define SDIO_CORE_O_CCCR00                                           0x00000000U

//CCCR04
#define SDIO_CORE_O_CCCR04                                           0x00000004U

//CCCR08
#define SDIO_CORE_O_CCCR08                                           0x00000008U

//CCCR10
#define SDIO_CORE_O_CCCR10                                           0x00000010U

//CCCR14
#define SDIO_CORE_O_CCCR14                                           0x00000014U

//CCCR40
#define SDIO_CORE_O_CCCR40                                           0x00000040U

//CCCR44
#define SDIO_CORE_O_CCCR44                                           0x00000044U

//CCCR48
#define SDIO_CORE_O_CCCR48                                           0x00000048U

//CCCR60
#define SDIO_CORE_O_CCCR60                                           0x00000060U

//Any read from this register clears the all GPI bits
#define SDIO_CORE_O_CCCR64                                           0x00000064U

//CCCR68
#define SDIO_CORE_O_CCCR68                                           0x00000068U

//CCCR80
#define SDIO_CORE_O_CCCR80                                           0x00000080U

//CCCR84
#define SDIO_CORE_O_CCCR84                                           0x00000084U

//CCCR88
#define SDIO_CORE_O_CCCR88                                           0x00000088U

//WSPI is not supported in Osprey Mx
#define SDIO_CORE_O_CCCR8C                                           0x0000008CU

//WSPI is not supported in Osprey Mx
#define SDIO_CORE_O_CCCR90                                           0x00000090U

//WSPI is not supported in Osprey Mx
#define SDIO_CORE_O_CCCR94                                           0x00000094U

//WSPI is not supported in Osprey Mx
#define SDIO_CORE_O_CCCR98                                           0x00000098U

//WSPI is not supported in Osprey Mx
#define SDIO_CORE_O_CCCR9C                                           0x0000009CU

//CCCRA0
#define SDIO_CORE_O_CCCRA0                                           0x000000A0U

//CCCRA4
#define SDIO_CORE_O_CCCRA4                                           0x000000A4U

//CCCRC0
#define SDIO_CORE_O_CCCRC0                                           0x000000C0U

//GPI FN1 and FN2 combined register
#define SDIO_CORE_O_CCCRC4                                           0x000000C4U

//FBR1R100
#define SDIO_CORE_O_FBR1R100                                         0x00000100U

//FBR1R108
#define SDIO_CORE_O_FBR1R108                                         0x00000108U

//FBR1R110
#define SDIO_CORE_O_FBR1R110                                         0x00000110U

//FBR2R200
#define SDIO_CORE_O_FBR2R200                                         0x00000200U

//FBR2R208
#define SDIO_CORE_O_FBR2R208                                         0x00000208U

//FBR2R210
#define SDIO_CORE_O_FBR2R210                                         0x00000210U

//FN0 CIS patch1 address
#define SDIO_CORE_O_CISP1ADDR                                        0x0001FFE0U

//FN0 CIS patch2 address
#define SDIO_CORE_O_CISP2ADDR                                        0x0001FFE4U

//FN0 CIS patch3 address
#define SDIO_CORE_O_CISP3ADDR                                        0x0001FFE8U

//FN0 CIS patch4 address
#define SDIO_CORE_O_CISP4ADDR                                        0x0001FFECU

//FN0 CIS patch5 address
#define SDIO_CORE_O_CISP5ADDR                                        0x0001FFF0U



/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR00
    Offset name:         SDIO_CORE_O_CCCR00
    Relative address:    0x0
    Description:
    Default Value:       0x00000343

        Field:           CCCR
        From..to bits:   0...3
        DefaultValue:    0x3
        Access type:     read-only
        Description:     4 CCCRx bits defines the version used by CCCR and the FBR format it supports

*/
#define SDIO_CORE_CCCR00_CCCR_W                                      4U
#define SDIO_CORE_CCCR00_CCCR_M                                      0x0000000FU
#define SDIO_CORE_CCCR00_CCCR_S                                      0U
/*

        Field:           SDIO
        From..to bits:   4...7
        DefaultValue:    0x4
        Access type:     read-only
        Description:     SDIO Specification Revision number

*/
#define SDIO_CORE_CCCR00_SDIO_W                                      4U
#define SDIO_CORE_CCCR00_SDIO_M                                      0x000000F0U
#define SDIO_CORE_CCCR00_SDIO_S                                      4U
/*

        Field:           SD
        From..to bits:   8...11
        DefaultValue:    0x3
        Access type:     read-only
        Description:     SD Format Version number

*/
#define SDIO_CORE_CCCR00_SD_W                                        4U
#define SDIO_CORE_CCCR00_SD_M                                        0x00000F00U
#define SDIO_CORE_CCCR00_SD_S                                        8U
/*

        Field:           FN1EN
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable Function 1

*/
#define SDIO_CORE_CCCR00_FN1EN                                       0x00020000U
#define SDIO_CORE_CCCR00_FN1EN_M                                     0x00020000U
#define SDIO_CORE_CCCR00_FN1EN_S                                     17U
/*

        Field:           FN1RDY
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Function 1 Ready

*/
#define SDIO_CORE_CCCR00_FN1RDY                                      0x02000000U
#define SDIO_CORE_CCCR00_FN1RDY_M                                    0x02000000U
#define SDIO_CORE_CCCR00_FN1RDY_S                                    25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR04
    Offset name:         SDIO_CORE_O_CCCR04
    Relative address:    0x4
    Description:
    Default Value:       0x00000000

        Field:           CINTEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt Enable controller

*/
#define SDIO_CORE_CCCR04_CINTEN                                      0x00000001U
#define SDIO_CORE_CCCR04_CINTEN_M                                    0x00000001U
#define SDIO_CORE_CCCR04_CINTEN_S                                    0U
/*

        Field:           FN1INTEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt Enable for function 1

*/
#define SDIO_CORE_CCCR04_FN1INTEN                                    0x00000002U
#define SDIO_CORE_CCCR04_FN1INTEN_M                                  0x00000002U
#define SDIO_CORE_CCCR04_FN1INTEN_S                                  1U
/*

        Field:           FN1INTPEND
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Interrupt pending for function 1

*/
#define SDIO_CORE_CCCR04_FN1INTPEND                                  0x00000200U
#define SDIO_CORE_CCCR04_FN1INTPEND_M                                0x00000200U
#define SDIO_CORE_CCCR04_FN1INTPEND_S                                9U
/*

        Field:           SDIOABORT
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Abort read or write transaction and free the SDIO bus.

*/
#define SDIO_CORE_CCCR04_SDIOABORT_W                                 3U
#define SDIO_CORE_CCCR04_SDIOABORT_M                                 0x00070000U
#define SDIO_CORE_CCCR04_SDIOABORT_S                                 16U
/*

        Field:           SDIORSTREQ
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     write-only
        Description:     reset sdio IP due to a SDIO Card Reset command

*/
#define SDIO_CORE_CCCR04_SDIORSTREQ                                  0x00080000U
#define SDIO_CORE_CCCR04_SDIORSTREQ_M                                0x00080000U
#define SDIO_CORE_CCCR04_SDIORSTREQ_S                                19U
/*

        Field:           BW
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines SDIO data bus width

*/
#define SDIO_CORE_CCCR04_BW_W                                        2U
#define SDIO_CORE_CCCR04_BW_M                                        0x03000000U
#define SDIO_CORE_CCCR04_BW_S                                        24U
/*

        Field:           CDDIS
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Connect/Disconnect (0/1) the pull-up resistor on SDIO data line 3

*/
#define SDIO_CORE_CCCR04_CDDIS                                       0x80000000U
#define SDIO_CORE_CCCR04_CDDIS_M                                     0x80000000U
#define SDIO_CORE_CCCR04_CDDIS_S                                     31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR08
    Offset name:         SDIO_CORE_O_CCCR08
    Relative address:    0x8
    Description:
    Default Value:       0x00100012

        Field:           SDC
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card support direct commands during data transfer

*/
#define SDIO_CORE_CCCR08_SDC                                         0x00000001U
#define SDIO_CORE_CCCR08_SDC_M                                       0x00000001U
#define SDIO_CORE_CCCR08_SDC_S                                       0U
/*

        Field:           SMB
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Card support Multi-Block

*/
#define SDIO_CORE_CCCR08_SMB                                         0x00000002U
#define SDIO_CORE_CCCR08_SMB_M                                       0x00000002U
#define SDIO_CORE_CCCR08_SMB_S                                       1U
/*

        Field:           SRW
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card support read wait

*/
#define SDIO_CORE_CCCR08_SRW                                         0x00000004U
#define SDIO_CORE_CCCR08_SRW_M                                       0x00000004U
#define SDIO_CORE_CCCR08_SRW_S                                       2U
/*

        Field:           SBS
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card support Suspend/Resume

*/
#define SDIO_CORE_CCCR08_SBS                                         0x00000008U
#define SDIO_CORE_CCCR08_SBS_M                                       0x00000008U
#define SDIO_CORE_CCCR08_SBS_S                                       3U
/*

        Field:           S4MI
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Supports interrupt between blocks of data in SDIO 4 bit mode

*/
#define SDIO_CORE_CCCR08_S4MI                                        0x00000010U
#define SDIO_CORE_CCCR08_S4MI_M                                      0x00000010U
#define SDIO_CORE_CCCR08_S4MI_S                                      4U
/*

        Field:           E4MI
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable interrupt between blocks of data in SDIO 4 bit mode

*/
#define SDIO_CORE_CCCR08_E4MI                                        0x00000020U
#define SDIO_CORE_CCCR08_E4MI_M                                      0x00000020U
#define SDIO_CORE_CCCR08_E4MI_S                                      5U
/*

        Field:           LSC
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card is a low speed card

*/
#define SDIO_CORE_CCCR08_LSC                                         0x00000040U
#define SDIO_CORE_CCCR08_LSC_M                                       0x00000040U
#define SDIO_CORE_CCCR08_LSC_S                                       6U
/*

        Field:           BLS4
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     4 bit support for low speed cards

*/
#define SDIO_CORE_CCCR08_BLS4                                        0x00000080U
#define SDIO_CORE_CCCR08_BLS4_M                                      0x00000080U
#define SDIO_CORE_CCCR08_BLS4_S                                      7U
/*

        Field:           CISPTR0
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits 7:0 of cards common CIS pointer

*/
#define SDIO_CORE_CCCR08_CISPTR0_W                                   8U
#define SDIO_CORE_CCCR08_CISPTR0_M                                   0x0000FF00U
#define SDIO_CORE_CCCR08_CISPTR0_S                                   8U
/*

        Field:           CISPTR1
        From..to bits:   16...31
        DefaultValue:    0x10
        Access type:     read-only
        Description:     Bits 23:8 of cards common CIS pointer

*/
#define SDIO_CORE_CCCR08_CISPTR1_W                                   16U
#define SDIO_CORE_CCCR08_CISPTR1_M                                   0xFFFF0000U
#define SDIO_CORE_CCCR08_CISPTR1_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR10
    Offset name:         SDIO_CORE_O_CCCR10
    Relative address:    0x10
    Description:
    Default Value:       0x01000000

        Field:           FN0BLKSIZE
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Function 0 block size

*/
#define SDIO_CORE_CCCR10_FN0BLKSIZE_W                                12U
#define SDIO_CORE_CCCR10_FN0BLKSIZE_M                                0x00000FFFU
#define SDIO_CORE_CCCR10_FN0BLKSIZE_S                                0U
/*

        Field:           SHS
        From..to bits:   24...24
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Support High Speed

*/
#define SDIO_CORE_CCCR10_SHS                                         0x01000000U
#define SDIO_CORE_CCCR10_SHS_M                                       0x01000000U
#define SDIO_CORE_CCCR10_SHS_S                                       24U
/*

        Field:           EHS
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable High Speed

*/
#define SDIO_CORE_CCCR10_EHS                                         0x02000000U
#define SDIO_CORE_CCCR10_EHS_M                                       0x02000000U
#define SDIO_CORE_CCCR10_EHS_S                                       25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR14
    Offset name:         SDIO_CORE_O_CCCR14
    Relative address:    0x14
    Description:
    Default Value:       0x00010000

        Field:           SAI
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Support Asynchronous Interrupt: Support bit of Asynchronous Interrupt. If the card supports asynchronous interrupt in SD 4-bit mode, this bit is set to 1.

*/
#define SDIO_CORE_CCCR14_SAI                                         0x00010000U
#define SDIO_CORE_CCCR14_SAI_M                                       0x00010000U
#define SDIO_CORE_CCCR14_SAI_S                                       16U
/*

        Field:           EAI
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable Asynchronous Interrupt: Enable bit of asynchronous interrupt. When Sai is set to 0, writing to this bit is ignored and always indicates 0. This bit is effective in in SD 4-bit mode.

*/
#define SDIO_CORE_CCCR14_EAI                                         0x00020000U
#define SDIO_CORE_CCCR14_EAI_M                                       0x00020000U
#define SDIO_CORE_CCCR14_EAI_S                                       17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR40
    Offset name:         SDIO_CORE_O_CCCR40
    Relative address:    0x40
    Description:
    Default Value:       0x00010000

        Field:           FN1ELPSTA
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enter Low Power mode Status bit

*/
#define SDIO_CORE_CCCR40_FN1ELPSTA                                   0x00010000U
#define SDIO_CORE_CCCR40_FN1ELPSTA_M                                 0x00010000U
#define SDIO_CORE_CCCR40_FN1ELPSTA_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR44
    Offset name:         SDIO_CORE_O_CCCR44
    Relative address:    0x44
    Description:
    Default Value:       0x00003F01

        Field:           FN1OBIEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enable Out Band Interrupt

*/
#define SDIO_CORE_CCCR44_FN1OBIEN                                    0x00000001U
#define SDIO_CORE_CCCR44_FN1OBIEN_M                                  0x00000001U
#define SDIO_CORE_CCCR44_FN1OBIEN_S                                  0U
/*

        Field:           FN1OBIINV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Invert Out Band Interrupt polarity

*/
#define SDIO_CORE_CCCR44_FN1OBIINV                                   0x00000002U
#define SDIO_CORE_CCCR44_FN1OBIINV_M                                 0x00000002U
#define SDIO_CORE_CCCR44_FN1OBIINV_S                                 1U
/*

        Field:           FN1GPIMSK
        From..to bits:   8...14
        DefaultValue:    0x3F
        Access type:     read-write
        Description:     General Purpose Interrupt source mask.
                         bit 0 - ELP signal transition from "0" to "1"
                         bit 1 - ELP signal transition from "1" to "0"
                         bit 2 - Host write to IOE1 register (Function 0 address 0x2)
                         bit 3 - Host write to function 0 CCCR area
                         bit 4 - Function 1 data block completion
                         bit 5 - Function 1 data block with CRC error
                         bit 6 - Autonomous mode: cmd 53 valid WR command to data FIFO

*/
#define SDIO_CORE_CCCR44_FN1GPIMSK_W                                 7U
#define SDIO_CORE_CCCR44_FN1GPIMSK_M                                 0x00007F00U
#define SDIO_CORE_CCCR44_FN1GPIMSK_S                                 8U
/*

        Field:           FN1STA
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Function 1 interrupt status.

*/
#define SDIO_CORE_CCCR44_FN1STA                                      0x00008000U
#define SDIO_CORE_CCCR44_FN1STA_M                                    0x00008000U
#define SDIO_CORE_CCCR44_FN1STA_S                                    15U
/*

        Field:           FN1GPISTA
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     General Purpose Interrupt sources status.
                         bit 0 - ELP signal transition from "0" to "1"
                         bit 1 - ELP signal transition from "1" to "0"
                         bit 2 - Host write to IOE1 register (Function 0 address 0x2)
                         bit 3 - Host write to function 0 CCCR area
                         bit 4 - Function 1 data block completion
                         bit 5 - Function 1 data block with CRC error
                         bit 6 - Autonomous mode: cmd 53 valid WR command to data FIFO

*/
#define SDIO_CORE_CCCR44_FN1GPISTA_W                                 7U
#define SDIO_CORE_CCCR44_FN1GPISTA_M                                 0x007F0000U
#define SDIO_CORE_CCCR44_FN1GPISTA_S                                 16U
/*

        Field:           FN1GPICLR
        From..to bits:   24...29
        DefaultValue:    0x0
        Access type:     write-only
        Description:     General Purpose clear Interrupt sources. Write "1" to clear the desire source.
                         bit 0 - ELP signal transition from "0" to "1"
                         bit 1 - ELP signal transition from "1" to "0"
                         bit 2 - Host write to IOE1 register (Function 0 address 0x2)
                         bit 3 - Host write to function 0 CCCR area
                         bit 4 - Function 1 data block completion
                         bit 5 - Function 1 data block with CRC error

*/
#define SDIO_CORE_CCCR44_FN1GPICLR_W                                 6U
#define SDIO_CORE_CCCR44_FN1GPICLR_M                                 0x3F000000U
#define SDIO_CORE_CCCR44_FN1GPICLR_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR48
    Offset name:         SDIO_CORE_O_CCCR48
    Relative address:    0x48
    Description:
    Default Value:       0x00000000

        Field:           FN1BUSY
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set function 1 busy signal override value

*/
#define SDIO_CORE_CCCR48_FN1BUSY                                     0x00000001U
#define SDIO_CORE_CCCR48_FN1BUSY_M                                   0x00000001U
#define SDIO_CORE_CCCR48_FN1BUSY_S                                   0U
/*

        Field:           FN1BUSYOV
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Override function 1 busy signal value.
                         0 - Do not override.
                         1 - Override.

*/
#define SDIO_CORE_CCCR48_FN1BUSYOV                                   0x00000002U
#define SDIO_CORE_CCCR48_FN1BUSYOV_M                                 0x00000002U
#define SDIO_CORE_CCCR48_FN1BUSYOV_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR60
    Offset name:         SDIO_CORE_O_CCCR60
    Relative address:    0x60
    Description:
    Default Value:       0x00000001

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR64
    Offset name:         SDIO_CORE_O_CCCR64
    Relative address:    0x64
    Description:         Any read from this register clears the all GPI bits
    Default Value:       0x00000F09

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR68
    Offset name:         SDIO_CORE_O_CCCR68
    Relative address:    0x68
    Description:
    Default Value:       0x02000000

        Field:           CMDERR
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bit map:
                         0 - Address error
                         1 - Function number error
                         2 - General error
                         3 - Illegal command error
                         4 - CRC error
                         5 - Out of range error

*/
#define SDIO_CORE_CCCR68_CMDERR_W                                    6U
#define SDIO_CORE_CCCR68_CMDERR_M                                    0x003F0000U
#define SDIO_CORE_CCCR68_CMDERR_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR80
    Offset name:         SDIO_CORE_O_CCCR80
    Relative address:    0x80
    Description:
    Default Value:       0x00FFFFC0

        Field:           OCR
        From..to bits:   0...23
        DefaultValue:    0xFFFFC0
        Access type:     read-write
        Description:     Bits 23:0 of Operation Conditions Register

*/
#define SDIO_CORE_CCCR80_OCR_W                                       24U
#define SDIO_CORE_CCCR80_OCR_M                                       0x00FFFFFFU
#define SDIO_CORE_CCCR80_OCR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR84
    Offset name:         SDIO_CORE_O_CCCR84
    Relative address:    0x84
    Description:
    Default Value:       0x09610121

        Field:           SDCMDST
        From..to bits:   0...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     SDIO command decoder state machine

*/
#define SDIO_CORE_CCCR84_SDCMDST_W                                   5U
#define SDIO_CORE_CCCR84_SDCMDST_M                                   0x0000001FU
#define SDIO_CORE_CCCR84_SDCMDST_S                                   0U
/*

        Field:           SDRESPST
        From..to bits:   5...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Response state machine

*/
#define SDIO_CORE_CCCR84_SDRESPST_W                                  3U
#define SDIO_CORE_CCCR84_SDRESPST_M                                  0x000000E0U
#define SDIO_CORE_CCCR84_SDRESPST_S                                  5U
/*

        Field:           SDDAT3ST
        From..to bits:   8...11
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Data line 3 state machine

*/
#define SDIO_CORE_CCCR84_SDDAT3ST_W                                  4U
#define SDIO_CORE_CCCR84_SDDAT3ST_M                                  0x00000F00U
#define SDIO_CORE_CCCR84_SDDAT3ST_S                                  8U
/*

        Field:           SDDAT0ST
        From..to bits:   16...20
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Data line 0 state machine

*/
#define SDIO_CORE_CCCR84_SDDAT0ST_W                                  5U
#define SDIO_CORE_CCCR84_SDDAT0ST_M                                  0x001F0000U
#define SDIO_CORE_CCCR84_SDDAT0ST_S                                  16U
/*

        Field:           SDDAT1ST
        From..to bits:   21...25
        DefaultValue:    0xB
        Access type:     read-only
        Description:     Data line 1 state machine

*/
#define SDIO_CORE_CCCR84_SDDAT1ST_W                                  5U
#define SDIO_CORE_CCCR84_SDDAT1ST_M                                  0x03E00000U
#define SDIO_CORE_CCCR84_SDDAT1ST_S                                  21U
/*

        Field:           SDDAT2ST
        From..to bits:   26...29
        DefaultValue:    0x2
        Access type:     read-only
        Description:     Data line 2 state machine

*/
#define SDIO_CORE_CCCR84_SDDAT2ST_W                                  4U
#define SDIO_CORE_CCCR84_SDDAT2ST_M                                  0x3C000000U
#define SDIO_CORE_CCCR84_SDDAT2ST_S                                  26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR88
    Offset name:         SDIO_CORE_O_CCCR88
    Relative address:    0x88
    Description:
    Default Value:       0x00000000

        Field:           RCA
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Relative Card Address

*/
#define SDIO_CORE_CCCR88_RCA_W                                       16U
#define SDIO_CORE_CCCR88_RCA_M                                       0xFFFF0000U
#define SDIO_CORE_CCCR88_RCA_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR8C
    Offset name:         SDIO_CORE_O_CCCR8C
    Relative address:    0x8C
    Description:         WSPI is not supported in Osprey Mx. read only, reserved as zero
    Default Value:       0x00000000

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR90
    Offset name:         SDIO_CORE_O_CCCR90
    Relative address:    0x90
    Description:         WSPI is not supported in Osprey Mx. read only, reserved as zero
    Default Value:       0x00000000

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR94
    Offset name:         SDIO_CORE_O_CCCR94
    Relative address:    0x94
    Description:         WSPI is not supported in Osprey Mx. read only, reserved as zero
    Default Value:       0x0000060C

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR98
    Offset name:         SDIO_CORE_O_CCCR98
    Relative address:    0x98
    Description:         WSPI is not supported in Osprey Mx. read only, reserved as zero
    Default Value:       0x00000004

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCR9C
    Offset name:         SDIO_CORE_O_CCCR9C
    Relative address:    0x9C
    Description:         WSPI is not supported in Osprey Mx. read only, reserved as zero
    Default Value:       0x00000000

*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCRA0
    Offset name:         SDIO_CORE_O_CCCRA0
    Relative address:    0xA0
    Description:
    Default Value:       0x00000000

        Field:           OCPSTA0
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ocp status 3-0
                         OCP write command status. Clear on read

*/
#define SDIO_CORE_CCCRA0_OCPSTA0_W                                   4U
#define SDIO_CORE_CCCRA0_OCPSTA0_M                                   0x000F0000U
#define SDIO_CORE_CCCRA0_OCPSTA0_S                                   16U
/*

        Field:           OCPSTA1
        From..to bits:   20...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     ocp status 7-4
                         OCP read command status. Clear on read

*/
#define SDIO_CORE_CCCRA0_OCPSTA1_W                                   4U
#define SDIO_CORE_CCCRA0_OCPSTA1_M                                   0x00F00000U
#define SDIO_CORE_CCCRA0_OCPSTA1_S                                   20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCRA4
    Offset name:         SDIO_CORE_O_CCCRA4
    Relative address:    0xA4
    Description:
    Default Value:       0x0000271F

        Field:           RAWTMRVAL
        From..to bits:   0...4
        DefaultValue:    0x1F
        Access type:     read-write
        Description:     Determine the duration between write and read request in CMD52 raw.

*/
#define SDIO_CORE_CCCRA4_RAWTMRVAL_W                                 5U
#define SDIO_CORE_CCCRA4_RAWTMRVAL_M                                 0x0000001FU
#define SDIO_CORE_CCCRA4_RAWTMRVAL_S                                 0U
/*

        Field:           USECTMRVAL
        From..to bits:   8...13
        DefaultValue:    0x27
        Access type:     read-write
        Description:     Set usec timer count value. This timer is running at sys_ocp_clk_aod_i clock.

*/
#define SDIO_CORE_CCCRA4_USECTMRVAL_W                                6U
#define SDIO_CORE_CCCRA4_USECTMRVAL_M                                0x00003F00U
#define SDIO_CORE_CCCRA4_USECTMRVAL_S                                8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCRC0
    Offset name:         SDIO_CORE_O_CCCRC0
    Relative address:    0xC0
    Description:
    Default Value:       0x002F0100

        Field:           WUCMD53
        From..to bits:   16...16
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DUE CMD 53 ONLY:
                         0: Wakeup due to command 53 Or command 52
                         1: Wakeup due to command 53 only (default)

*/
#define SDIO_CORE_CCCRC0_WUCMD53                                     0x00010000U
#define SDIO_CORE_CCCRC0_WUCMD53_M                                   0x00010000U
#define SDIO_CORE_CCCRC0_WUCMD53_S                                   16U
/*

        Field:           WUHOSTRD
        From..to bits:   17...17
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DUE HOST RD:
                         0: Do not wakeup due host Read
                         1: Wakeup due to host Read (default)

*/
#define SDIO_CORE_CCCRC0_WUHOSTRD                                    0x00020000U
#define SDIO_CORE_CCCRC0_WUHOSTRD_M                                  0x00020000U
#define SDIO_CORE_CCCRC0_WUHOSTRD_S                                  17U
/*

        Field:           WUHOSTWR
        From..to bits:   18...18
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DUE HOST WR:
                         0: Do not Wakeup due host Write
                         1: Wakeup due to host Write (default)

*/
#define SDIO_CORE_CCCRC0_WUHOSTWR                                    0x00040000U
#define SDIO_CORE_CCCRC0_WUHOSTWR_M                                  0x00040000U
#define SDIO_CORE_CCCRC0_WUHOSTWR_S                                  18U
/*

        Field:           WUADDR
        From..to bits:   19...19
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DUE KNOWN ADDRESS:
                         0: Wakeup regardless to address parsing
                         1: Wakeup due to  command toward known address (default)

*/
#define SDIO_CORE_CCCRC0_WUADDR                                      0x00080000U
#define SDIO_CORE_CCCRC0_WUADDR_M                                    0x00080000U
#define SDIO_CORE_CCCRC0_WUADDR_S                                    19U
/*

        Field:           WUELP
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     WAKEUP DUE KNOWN ADDRESS:
                         0: Do not wakeup due to SDIO cmd 52 or SPI wr to ELP reg (default)
                         1: Wakeup due to SDIO cmd 52 or SPI wr to ELP reg

*/
#define SDIO_CORE_CCCRC0_WUELP                                       0x00100000U
#define SDIO_CORE_CCCRC0_WUELP_M                                     0x00100000U
#define SDIO_CORE_CCCRC0_WUELP_S                                     20U
/*

        Field:           WUAUT
        From..to bits:   21...21
        DefaultValue:    0x1
        Access type:     read-write
        Description:     WAKEUP DUE HOST CMD AUT:
                         0: Do not Wakeup upon arrival of host command in an Autonomous manner
                         1: Wakeup due to host command arrival in an Autonomous manner (default)

*/
#define SDIO_CORE_CCCRC0_WUAUT                                       0x00200000U
#define SDIO_CORE_CCCRC0_WUAUT_M                                     0x00200000U
#define SDIO_CORE_CCCRC0_WUAUT_S                                     21U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CCCRC4
    Offset name:         SDIO_CORE_O_CCCRC4
    Relative address:    0xC4
    Description:         GPI FN1 and FN2 combined register. Clear on Read.
                        Reading this reguster clears the fn1/2_gpi_sts in 0x44/0x64 Regs respectively as well
    Default Value:       0x00003F01

        Field:           FN1GPISTA
        From..to bits:   0...6
        DefaultValue:    0x1
        Access type:     read-only
        Description:     General Purpose Interrupt sources status.
                         bit 0 - ELP signal transition from "0" to "1"
                         bit 1 - ELP signal transition from "1" to "0"
                         bit 2 - Host write to IOE1 register (Function 0 address 0x2)
                         bit 3 - Host write to function 0 CCCR area
                         bit 4 - Function 1 data block completion
                         bit 5 - Function 1 data block with CRC error
                         bit 6 - Autonomous mode: cmd 53 valid WR command to data FIFO


*/
#define SDIO_CORE_CCCRC4_FN1GPISTA_W                                 7U
#define SDIO_CORE_CCCRC4_FN1GPISTA_M                                 0x0000007FU
#define SDIO_CORE_CCCRC4_FN1GPISTA_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR1R100
    Offset name:         SDIO_CORE_O_FBR1R100
    Relative address:    0x100
    Description:
    Default Value:       0x00000002

        Field:           SDIO
        From..to bits:   0...3
        DefaultValue:    0x2
        Access type:     read-only
        Description:     SDIO standard function 1 interface code

*/
#define SDIO_CORE_FBR1R100_SDIO_W                                    4U
#define SDIO_CORE_FBR1R100_SDIO_M                                    0x0000000FU
#define SDIO_CORE_FBR1R100_SDIO_S                                    0U
/*

        Field:           CSA
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Function 1 Supports CSA

*/
#define SDIO_CORE_FBR1R100_CSA                                       0x00000040U
#define SDIO_CORE_FBR1R100_CSA_M                                     0x00000040U
#define SDIO_CORE_FBR1R100_CSA_S                                     6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR1R108
    Offset name:         SDIO_CORE_O_FBR1R108
    Relative address:    0x108
    Description:
    Default Value:       0x00000000

        Field:           CISPTR0
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits 7:0 of address pointer to function 1 CIS

*/
#define SDIO_CORE_FBR1R108_CISPTR0_W                                 8U
#define SDIO_CORE_FBR1R108_CISPTR0_M                                 0x0000FF00U
#define SDIO_CORE_FBR1R108_CISPTR0_S                                 8U
/*

        Field:           CISPTR1
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits 23:8 of address pointer to function 1 CIS

*/
#define SDIO_CORE_FBR1R108_CISPTR1_W                                 16U
#define SDIO_CORE_FBR1R108_CISPTR1_M                                 0xFFFF0000U
#define SDIO_CORE_FBR1R108_CISPTR1_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR1R110
    Offset name:         SDIO_CORE_O_FBR1R110
    Relative address:    0x110
    Description:
    Default Value:       0x00000000

        Field:           FNBLKSIZE
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     function 1 block size register

*/
#define SDIO_CORE_FBR1R110_FNBLKSIZE_W                               12U
#define SDIO_CORE_FBR1R110_FNBLKSIZE_M                               0x00000FFFU
#define SDIO_CORE_FBR1R110_FNBLKSIZE_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR2R200
    Offset name:         SDIO_CORE_O_FBR2R200
    Relative address:    0x200
    Description:
    Default Value:       0x00000000

        Field:           SDIO
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SDIO standard function 2 interface code

*/
#define SDIO_CORE_FBR2R200_SDIO_W                                    4U
#define SDIO_CORE_FBR2R200_SDIO_M                                    0x0000000FU
#define SDIO_CORE_FBR2R200_SDIO_S                                    0U
/*

        Field:           CSA
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Function 2 Supports CSA

*/
#define SDIO_CORE_FBR2R200_CSA                                       0x00000040U
#define SDIO_CORE_FBR2R200_CSA_M                                     0x00000040U
#define SDIO_CORE_FBR2R200_CSA_S                                     6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR2R208
    Offset name:         SDIO_CORE_O_FBR2R208
    Relative address:    0x208
    Description:
    Default Value:       0x00003000

        Field:           CISPTR0
        From..to bits:   8...15
        DefaultValue:    0x30
        Access type:     read-only
        Description:     Bits 7:0 of address pointer to function 2 CIS

*/
#define SDIO_CORE_FBR2R208_CISPTR0_W                                 8U
#define SDIO_CORE_FBR2R208_CISPTR0_M                                 0x0000FF00U
#define SDIO_CORE_FBR2R208_CISPTR0_S                                 8U
/*

        Field:           CISPTR1
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits 23:8 of address pointer to function 2 CIS

*/
#define SDIO_CORE_FBR2R208_CISPTR1_W                                 16U
#define SDIO_CORE_FBR2R208_CISPTR1_M                                 0xFFFF0000U
#define SDIO_CORE_FBR2R208_CISPTR1_S                                 16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FBR2R210
    Offset name:         SDIO_CORE_O_FBR2R210
    Relative address:    0x210
    Description:
    Default Value:       0x00000000

        Field:           FNBLKSIZE
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     function 2 block size register

*/
#define SDIO_CORE_FBR2R210_FNBLKSIZE_W                               12U
#define SDIO_CORE_FBR2R210_FNBLKSIZE_M                               0x00000FFFU
#define SDIO_CORE_FBR2R210_FNBLKSIZE_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CISP1ADDR
    Offset name:         SDIO_CORE_O_CISP1ADDR
    Relative address:    0x1FFE0
    Description:         FN0 CIS patch1 address
    Default Value:       0x00000000

        Field:           PCH1ADDR
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS address patch 1

*/
#define SDIO_CORE_CISP1ADDR_PCH1ADDR_W                               16U
#define SDIO_CORE_CISP1ADDR_PCH1ADDR_M                               0x0000FFFFU
#define SDIO_CORE_CISP1ADDR_PCH1ADDR_S                               0U
/*

        Field:           PCH1DAT
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS data patch 1

*/
#define SDIO_CORE_CISP1ADDR_PCH1DAT_W                                8U
#define SDIO_CORE_CISP1ADDR_PCH1DAT_M                                0x00FF0000U
#define SDIO_CORE_CISP1ADDR_PCH1DAT_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CISP2ADDR
    Offset name:         SDIO_CORE_O_CISP2ADDR
    Relative address:    0x1FFE4
    Description:         FN0 CIS patch2 address
    Default Value:       0x00000000

        Field:           PCH2ADDR
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS address patch 2

*/
#define SDIO_CORE_CISP2ADDR_PCH2ADDR_W                               16U
#define SDIO_CORE_CISP2ADDR_PCH2ADDR_M                               0x0000FFFFU
#define SDIO_CORE_CISP2ADDR_PCH2ADDR_S                               0U
/*

        Field:           PCH2DAT
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS data patch 2

*/
#define SDIO_CORE_CISP2ADDR_PCH2DAT_W                                8U
#define SDIO_CORE_CISP2ADDR_PCH2DAT_M                                0x00FF0000U
#define SDIO_CORE_CISP2ADDR_PCH2DAT_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CISP3ADDR
    Offset name:         SDIO_CORE_O_CISP3ADDR
    Relative address:    0x1FFE8
    Description:         FN0 CIS patch3 address
    Default Value:       0x00000000

        Field:           PCH3ADDR
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS address patch 3

*/
#define SDIO_CORE_CISP3ADDR_PCH3ADDR_W                               16U
#define SDIO_CORE_CISP3ADDR_PCH3ADDR_M                               0x0000FFFFU
#define SDIO_CORE_CISP3ADDR_PCH3ADDR_S                               0U
/*

        Field:           PCH3DAT
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS data patch 3

*/
#define SDIO_CORE_CISP3ADDR_PCH3DAT_W                                8U
#define SDIO_CORE_CISP3ADDR_PCH3DAT_M                                0x00FF0000U
#define SDIO_CORE_CISP3ADDR_PCH3DAT_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CISP4ADDR
    Offset name:         SDIO_CORE_O_CISP4ADDR
    Relative address:    0x1FFEC
    Description:         FN0 CIS patch4 address
    Default Value:       0x00000000

        Field:           PCH4ADDR
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS address patch 4

*/
#define SDIO_CORE_CISP4ADDR_PCH4ADDR_W                               16U
#define SDIO_CORE_CISP4ADDR_PCH4ADDR_M                               0x0000FFFFU
#define SDIO_CORE_CISP4ADDR_PCH4ADDR_S                               0U
/*

        Field:           PCH4DAT
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS data patch 4

*/
#define SDIO_CORE_CISP4ADDR_PCH4DAT_W                                8U
#define SDIO_CORE_CISP4ADDR_PCH4DAT_M                                0x00FF0000U
#define SDIO_CORE_CISP4ADDR_PCH4DAT_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CISP5ADDR
    Offset name:         SDIO_CORE_O_CISP5ADDR
    Relative address:    0x1FFF0
    Description:         FN0 CIS patch5 address
    Default Value:       0x00000000

        Field:           PCH5ADDR
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS address patch 5

*/
#define SDIO_CORE_CISP5ADDR_PCH5ADDR_W                               16U
#define SDIO_CORE_CISP5ADDR_PCH5ADDR_M                               0x0000FFFFU
#define SDIO_CORE_CISP5ADDR_PCH5ADDR_S                               0U
/*

        Field:           PCH5DAT
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CIS data patch 5

*/
#define SDIO_CORE_CISP5ADDR_PCH5DAT_W                                8U
#define SDIO_CORE_CISP5ADDR_PCH5DAT_M                                0x00FF0000U
#define SDIO_CORE_CISP5ADDR_PCH5DAT_S                                16U

#endif /* __HW_SDIO_CORE_H__*/
