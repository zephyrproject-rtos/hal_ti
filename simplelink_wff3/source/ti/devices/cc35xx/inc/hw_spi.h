/******************************************************************************
*  Filename:       hw_spi.h
*
*  Description:    Defines and prototypes for the SPI peripheral.
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
#ifndef __HW_SPI_H__
#define __HW_SPI_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SPI component

--------------------------------------------------------------------------------- */

//Description Register
#define SPI_O_DESC                                                   0x00000000U

//Interrupt mask
#define SPI_O_IMASK                                                  0x00000044U

//Raw interrupt status
#define SPI_O_RIS                                                    0x00000048U

//Masked interrupt status
#define SPI_O_MIS                                                    0x0000004CU

//Interrupt set register
#define SPI_O_ISET                                                   0x00000050U

//Interrupt clear register
#define SPI_O_ICLR                                                   0x00000054U

//Interrupt mask set register
#define SPI_O_IMSET                                                  0x00000058U

//Interrupt mask clear register
#define SPI_O_IMCLR                                                  0x0000005CU

//Emulation control register
#define SPI_O_EMU                                                    0x00000060U

//SPI control register 0
#define SPI_O_CTL0                                                   0x00000100U

//SPI control register 1
#define SPI_O_CTL1                                                   0x00000104U

//Clock configuration register 0
#define SPI_O_CLKCFG0                                                0x00000108U

//Clock configuration register 1
#define SPI_O_CLKCFG1                                                0x0000010CU

//Interrupt FIFO level select register
#define SPI_O_IFLS                                                   0x00000110U

//DMA Control Register
#define SPI_O_DMACR                                                  0x00000114U

//Receive CRC register
#define SPI_O_RXCRC                                                  0x00000118U

//Transmit CRC register
#define SPI_O_TXCRC                                                  0x0000011CU

//Header update reigster for 32 bits of header data
#define SPI_O_TXFHDR32                                               0x00000120U

//Header update reigster for 24 bits of header data
#define SPI_O_TXFHDR24                                               0x00000124U

//Header update reigster for 16 bits of data
#define SPI_O_TXFHDR16                                               0x00000128U

//Header update reigster for 8 bits of header data
#define SPI_O_TXFHDR8                                                0x0000012CU

//Atomic Header control register
#define SPI_O_TXFHDRC                                                0x00000130U

//RXDATA Register
#define SPI_O_RXDATA                                                 0x00000140U

//TXDATA Register
#define SPI_O_TXDATA                                                 0x00000150U

//Status Register
#define SPI_O_STA                                                    0x00000160U

//Clock Enable Register
#define SPI_O_CLKCFG                                                 0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DESC
    Offset name:         SPI_O_DESC
    Relative address:    0x0
    Description:         Description Register. This register provides IP module ID, revision information, instance index and standard MMR registers offset.
    Default Value:       0x00000000

        Field:           MINREV
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision of IP (0-15).

*/
#define SPI_DESC_MINREV_W                                            4U
#define SPI_DESC_MINREV_M                                            0x0000000FU
#define SPI_DESC_MINREV_S                                            0U
/*

        Field:           MAJREV
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major revision of IP (0-15).

*/
#define SPI_DESC_MAJREV_W                                            4U
#define SPI_DESC_MAJREV_M                                            0x000000F0U
#define SPI_DESC_MAJREV_S                                            4U
/*

        Field:           INSTIDX
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     IP Instance ID number. If multiple instances of IP exist in the device, this field can identify the instance number (0-15).

*/
#define SPI_DESC_INSTIDX_W                                           4U
#define SPI_DESC_INSTIDX_M                                           0x00000F00U
#define SPI_DESC_INSTIDX_S                                           8U
/*

        Field:           STDIPOFF
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Standard IP MMR block offset. Standard IP MMRs are the set of from aggregated IRQ registers till DTB.

                         0: Standard IP MMRs do not exist

                         0x1-0xF: Standard IP MMRs begin at offset of (64*[STDIPOFF] from the base IP address)

*/
#define SPI_DESC_STDIPOFF_W                                          4U
#define SPI_DESC_STDIPOFF_M                                          0x0000F000U
#define SPI_DESC_STDIPOFF_S                                          12U
/*

        Field:           MODID
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Module identifier used to uniquely identify this IP.

*/
#define SPI_DESC_MODID_W                                             16U
#define SPI_DESC_MODID_M                                             0xFFFF0000U
#define SPI_DESC_MODID_S                                             16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMASK
    Offset name:         SPI_O_IMASK
    Relative address:    0x44
    Description:         Interrupt mask. This register selects interrupt sources which are allowed to pass from [RIS.*] to [MIS.*] when the corresponding bit-fields are set to 1.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RXFIFO overflow event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_RXOVF                                              0x00000001U
#define SPI_IMASK_RXOVF_M                                            0x00000001U
#define SPI_IMASK_RXOVF_S                                            0U
#define SPI_IMASK_RXOVF_SET                                          0x00000001U
#define SPI_IMASK_RXOVF_CLR                                          0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Parity error event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_PER                                                0x00000002U
#define SPI_IMASK_PER_M                                              0x00000002U
#define SPI_IMASK_PER_S                                              1U
#define SPI_IMASK_PER_SET                                            0x00000002U
#define SPI_IMASK_PER_CLR                                            0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPI Receive Time-Out event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_RTOUT                                              0x00000004U
#define SPI_IMASK_RTOUT_M                                            0x00000004U
#define SPI_IMASK_RTOUT_S                                            2U
#define SPI_IMASK_RTOUT_SET                                          0x00000004U
#define SPI_IMASK_RTOUT_CLR                                          0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive FIFO event.

        ENUMs:
            SET:                         Set Interrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_RX                                                 0x00000008U
#define SPI_IMASK_RX_M                                               0x00000008U
#define SPI_IMASK_RX_S                                               3U
#define SPI_IMASK_RX_SET                                             0x00000008U
#define SPI_IMASK_RX_CLR                                             0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit FIFO event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_TX                                                 0x00000010U
#define SPI_IMASK_TX_M                                               0x00000010U
#define SPI_IMASK_TX_S                                               4U
#define SPI_IMASK_TX_SET                                             0x00000010U
#define SPI_IMASK_TX_CLR                                             0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit FIFO Empty event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_TXEMPTY                                            0x00000020U
#define SPI_IMASK_TXEMPTY_M                                          0x00000020U
#define SPI_IMASK_TXEMPTY_S                                          5U
#define SPI_IMASK_TXEMPTY_SET                                        0x00000020U
#define SPI_IMASK_TXEMPTY_CLR                                        0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPI Idle event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_IDLE                                               0x00000040U
#define SPI_IMASK_IDLE_M                                             0x00000040U
#define SPI_IMASK_IDLE_S                                             6U
#define SPI_IMASK_IDLE_SET                                           0x00000040U
#define SPI_IMASK_IDLE_CLR                                           0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Done RX event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_DMARX                                              0x00000080U
#define SPI_IMASK_DMARX_M                                            0x00000080U
#define SPI_IMASK_DMARX_S                                            7U
#define SPI_IMASK_DMARX_SET                                          0x00000080U
#define SPI_IMASK_DMARX_CLR                                          0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Done TX event mask.

        ENUMs:
            SET:                         Set Interrrupt Mask
            CLR:                         Clear Interrupt Mask
*/
#define SPI_IMASK_DMATX                                              0x00000100U
#define SPI_IMASK_DMATX_M                                            0x00000100U
#define SPI_IMASK_DMATX_S                                            8U
#define SPI_IMASK_DMATX_SET                                          0x00000100U
#define SPI_IMASK_DMATX_CLR                                          0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RIS
    Offset name:         SPI_O_RIS
    Relative address:    0x48
    Description:         Raw interrupt status. This register reflects the state of all pending interrupts, regardless of masking. This register allows the user to implement a poll scheme. A flag set in this register can be cleared by writing 1 to the corresponding [ICLR.*] register bit.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RXFIFO overflow event. This interrupt is set if an RX FIFO overflow has been detected.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_RXOVF                                                0x00000001U
#define SPI_RIS_RXOVF_M                                              0x00000001U
#define SPI_RIS_RXOVF_S                                              0U
#define SPI_RIS_RXOVF_SET                                            0x00000001U
#define SPI_RIS_RXOVF_CLR                                            0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Parity error event. This bit is set if a Parity error has been detected

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_PER                                                  0x00000002U
#define SPI_RIS_PER_M                                                0x00000002U
#define SPI_RIS_PER_S                                                1U
#define SPI_RIS_PER_SET                                              0x00000002U
#define SPI_RIS_PER_CLR                                              0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SPI Receive Time-Out event. This interrupt is set if no activity is detected on the input clock line within the time period dictated by [CTL1.RTOUT] value. This is applicable only in peripheral mode.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_RTOUT                                                0x00000004U
#define SPI_RIS_RTOUT_M                                              0x00000004U
#define SPI_RIS_RTOUT_S                                              2U
#define SPI_RIS_RTOUT_SET                                            0x00000004U
#define SPI_RIS_RTOUT_CLR                                            0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive FIFO event.This interrupt is set if the selected Receive FIFO level has been reached

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_RX                                                   0x00000008U
#define SPI_RIS_RX_M                                                 0x00000008U
#define SPI_RIS_RX_S                                                 3U
#define SPI_RIS_RX_SET                                               0x00000008U
#define SPI_RIS_RX_CLR                                               0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit FIFO event.This interrupt is set if the selected Transmit FIFO level has been reached.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_TX                                                   0x00000010U
#define SPI_RIS_TX_M                                                 0x00000010U
#define SPI_RIS_TX_S                                                 4U
#define SPI_RIS_TX_SET                                               0x00000010U
#define SPI_RIS_TX_CLR                                               0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit FIFO Empty interrupt mask. This interrupt is set when all data in the Transmit FIFO has been moved to the shift register.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_TXEMPTY                                              0x00000020U
#define SPI_RIS_TXEMPTY_M                                            0x00000020U
#define SPI_RIS_TXEMPTY_S                                            5U
#define SPI_RIS_TXEMPTY_SET                                          0x00000020U
#define SPI_RIS_TXEMPTY_CLR                                          0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SPI has completed transfers and moved to IDLE mode. This bit is set when [STA.BUSY] goes low.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_IDLE                                                 0x00000040U
#define SPI_RIS_IDLE_M                                               0x00000040U
#define SPI_RIS_IDLE_S                                               6U
#define SPI_RIS_IDLE_SET                                             0x00000040U
#define SPI_RIS_IDLE_CLR                                             0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA Done event for RX. This interrupt is set if the RX DMA channel sends the DONE signal. This allows handling of the DMA RX event inside SPI.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_DMARX                                                0x00000080U
#define SPI_RIS_DMARX_M                                              0x00000080U
#define SPI_RIS_DMARX_S                                              7U
#define SPI_RIS_DMARX_SET                                            0x00000080U
#define SPI_RIS_DMARX_CLR                                            0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     DMA Done event for TX. This interrupt is set if the TX DMA channel sends the DONE signal. This allows the handling of the TX DMA event inside SPI.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_RIS_DMATX                                                0x00000100U
#define SPI_RIS_DMATX_M                                              0x00000100U
#define SPI_RIS_DMATX_S                                              8U
#define SPI_RIS_DMATX_SET                                            0x00000100U
#define SPI_RIS_DMATX_CLR                                            0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MIS
    Offset name:         SPI_O_MIS
    Relative address:    0x4C
    Description:         Masked interrupt status. This register is simply a bitwise AND of the contents of [IMASK.*] and [RIS.*] registers. A flag set in this register can be cleared by writing 1 to the corresponding [ICLR.*] register bit.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked RXFIFO overflow event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_RXOVF                                                0x00000001U
#define SPI_MIS_RXOVF_M                                              0x00000001U
#define SPI_MIS_RXOVF_S                                              0U
#define SPI_MIS_RXOVF_SET                                            0x00000001U
#define SPI_MIS_RXOVF_CLR                                            0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Parity error event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_PER                                                  0x00000002U
#define SPI_MIS_PER_M                                                0x00000002U
#define SPI_MIS_PER_S                                                1U
#define SPI_MIS_PER_SET                                              0x00000002U
#define SPI_MIS_PER_CLR                                              0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked SPI Receive Time-Out event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_RTOUT                                                0x00000004U
#define SPI_MIS_RTOUT_M                                              0x00000004U
#define SPI_MIS_RTOUT_S                                              2U
#define SPI_MIS_RTOUT_SET                                            0x00000004U
#define SPI_MIS_RTOUT_CLR                                            0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked receive FIFO event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_RX                                                   0x00000008U
#define SPI_MIS_RX_M                                                 0x00000008U
#define SPI_MIS_RX_S                                                 3U
#define SPI_MIS_RX_SET                                               0x00000008U
#define SPI_MIS_RX_CLR                                               0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Transmit FIFO event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_TX                                                   0x00000010U
#define SPI_MIS_TX_M                                                 0x00000010U
#define SPI_MIS_TX_S                                                 4U
#define SPI_MIS_TX_SET                                               0x00000010U
#define SPI_MIS_TX_CLR                                               0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked Transmit FIFO Empty event.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_TXEMPTY                                              0x00000020U
#define SPI_MIS_TXEMPTY_M                                            0x00000020U
#define SPI_MIS_TXEMPTY_S                                            5U
#define SPI_MIS_TXEMPTY_SET                                          0x00000020U
#define SPI_MIS_TXEMPTY_CLR                                          0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked SPI IDLE event.


        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_IDLE                                                 0x00000040U
#define SPI_MIS_IDLE_M                                               0x00000040U
#define SPI_MIS_IDLE_S                                               6U
#define SPI_MIS_IDLE_SET                                             0x00000040U
#define SPI_MIS_IDLE_CLR                                             0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked DMA Done event for RX.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_DMARX                                                0x00000080U
#define SPI_MIS_DMARX_M                                              0x00000080U
#define SPI_MIS_DMARX_S                                              7U
#define SPI_MIS_DMARX_SET                                            0x00000080U
#define SPI_MIS_DMARX_CLR                                            0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Masked DMA Done event for TX.

        ENUMs:
            SET:                         Interrupt occurred
            CLR:                         Interrupt did not occur
*/
#define SPI_MIS_DMATX                                                0x00000100U
#define SPI_MIS_DMATX_M                                              0x00000100U
#define SPI_MIS_DMATX_S                                              8U
#define SPI_MIS_DMATX_SET                                            0x00000100U
#define SPI_MIS_DMATX_CLR                                            0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ISET
    Offset name:         SPI_O_ISET
    Relative address:    0x50
    Description:         Interrupt set register. This register can used by software for diagnostics and safety checking purposes. Writing a 1 to a bit in this register will set the event and the corresponding [RIS.*] bit also gets set. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets set.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set RXFIFO overflow event.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_RXOVF                                               0x00000001U
#define SPI_ISET_RXOVF_M                                             0x00000001U
#define SPI_ISET_RXOVF_S                                             0U
#define SPI_ISET_RXOVF_SET                                           0x00000001U
#define SPI_ISET_RXOVF_NO_EFFECT                                     0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Parity error event.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_PER                                                 0x00000002U
#define SPI_ISET_PER_M                                               0x00000002U
#define SPI_ISET_PER_S                                               1U
#define SPI_ISET_PER_SET                                             0x00000002U
#define SPI_ISET_PER_NO_EFFECT                                       0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set SPI Receive Time-Out Event.

        ENUMs:
            SET:                         Set Interrrupt Mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_RTOUT                                               0x00000004U
#define SPI_ISET_RTOUT_M                                             0x00000004U
#define SPI_ISET_RTOUT_S                                             2U
#define SPI_ISET_RTOUT_SET                                           0x00000004U
#define SPI_ISET_RTOUT_NO_EFFECT                                     0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Receive FIFO event.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_RX                                                  0x00000008U
#define SPI_ISET_RX_M                                                0x00000008U
#define SPI_ISET_RX_S                                                3U
#define SPI_ISET_RX_SET                                              0x00000008U
#define SPI_ISET_RX_NO_EFFECT                                        0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Transmit FIFO event.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_TX                                                  0x00000010U
#define SPI_ISET_TX_M                                                0x00000010U
#define SPI_ISET_TX_S                                                4U
#define SPI_ISET_TX_SET                                              0x00000010U
#define SPI_ISET_TX_NO_EFFECT                                        0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Transmit FIFO Empty event.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_TXEMPTY                                             0x00000020U
#define SPI_ISET_TXEMPTY_M                                           0x00000020U
#define SPI_ISET_TXEMPTY_S                                           5U
#define SPI_ISET_TXEMPTY_SET                                         0x00000020U
#define SPI_ISET_TXEMPTY_NO_EFFECT                                   0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set SPI IDLE event.


        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_IDLE                                                0x00000040U
#define SPI_ISET_IDLE_M                                              0x00000040U
#define SPI_ISET_IDLE_S                                              6U
#define SPI_ISET_IDLE_SET                                            0x00000040U
#define SPI_ISET_IDLE_NO_EFFECT                                      0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set DMA Done event for RX.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_DMARX                                               0x00000080U
#define SPI_ISET_DMARX_M                                             0x00000080U
#define SPI_ISET_DMARX_S                                             7U
#define SPI_ISET_DMARX_SET                                           0x00000080U
#define SPI_ISET_DMARX_NO_EFFECT                                     0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set DMA Done event for TX.

        ENUMs:
            SET:                         Set Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ISET_DMATX                                               0x00000100U
#define SPI_ISET_DMATX_M                                             0x00000100U
#define SPI_ISET_DMATX_S                                             8U
#define SPI_ISET_DMATX_SET                                           0x00000100U
#define SPI_ISET_DMATX_NO_EFFECT                                     0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ICLR
    Offset name:         SPI_O_ICLR
    Relative address:    0x54
    Description:         Interrupt clear register. This register allows software to clear interrupts. Writing a 1 to a bit in this register will clear the event and the corresponding [RIS.*] bit also gets cleared. If the corresponding [IMASK.*] bit is set, then the corresponding [MIS.*] register bit also gets cleared.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear RXFIFO overflow event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_RXOVF                                               0x00000001U
#define SPI_ICLR_RXOVF_M                                             0x00000001U
#define SPI_ICLR_RXOVF_S                                             0U
#define SPI_ICLR_RXOVF_CLR                                           0x00000001U
#define SPI_ICLR_RXOVF_NO_EFFECT                                     0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Parity error event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_PER                                                 0x00000002U
#define SPI_ICLR_PER_M                                               0x00000002U
#define SPI_ICLR_PER_S                                               1U
#define SPI_ICLR_PER_CLR                                             0x00000002U
#define SPI_ICLR_PER_NO_EFFECT                                       0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear SPI Receive Time-Out Event.

        ENUMs:
            CLR:                         Set Interrrupt Mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_RTOUT                                               0x00000004U
#define SPI_ICLR_RTOUT_M                                             0x00000004U
#define SPI_ICLR_RTOUT_S                                             2U
#define SPI_ICLR_RTOUT_CLR                                           0x00000004U
#define SPI_ICLR_RTOUT_NO_EFFECT                                     0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Receive FIFO event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_RX                                                  0x00000008U
#define SPI_ICLR_RX_M                                                0x00000008U
#define SPI_ICLR_RX_S                                                3U
#define SPI_ICLR_RX_CLR                                              0x00000008U
#define SPI_ICLR_RX_NO_EFFECT                                        0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Transmit FIFO event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_TX                                                  0x00000010U
#define SPI_ICLR_TX_M                                                0x00000010U
#define SPI_ICLR_TX_S                                                4U
#define SPI_ICLR_TX_CLR                                              0x00000010U
#define SPI_ICLR_TX_NO_EFFECT                                        0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Transmit FIFO Empty event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_TXEMPTY                                             0x00000020U
#define SPI_ICLR_TXEMPTY_M                                           0x00000020U
#define SPI_ICLR_TXEMPTY_S                                           5U
#define SPI_ICLR_TXEMPTY_CLR                                         0x00000020U
#define SPI_ICLR_TXEMPTY_NO_EFFECT                                   0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear SPI IDLE event.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_IDLE                                                0x00000040U
#define SPI_ICLR_IDLE_M                                              0x00000040U
#define SPI_ICLR_IDLE_S                                              6U
#define SPI_ICLR_IDLE_CLR                                            0x00000040U
#define SPI_ICLR_IDLE_NO_EFFECT                                      0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear DMA Done event for RX.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_DMARX                                               0x00000080U
#define SPI_ICLR_DMARX_M                                             0x00000080U
#define SPI_ICLR_DMARX_S                                             7U
#define SPI_ICLR_DMARX_CLR                                           0x00000080U
#define SPI_ICLR_DMARX_NO_EFFECT                                     0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear DMA Done event for TX.

        ENUMs:
            CLR:                         Clear Interrupt
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_ICLR_DMATX                                               0x00000100U
#define SPI_ICLR_DMATX_M                                             0x00000100U
#define SPI_ICLR_DMATX_S                                             8U
#define SPI_ICLR_DMATX_CLR                                           0x00000100U
#define SPI_ICLR_DMATX_NO_EFFECT                                     0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMSET
    Offset name:         SPI_O_IMSET
    Relative address:    0x58
    Description:         Interrupt mask set register. Writing a 1 to a bit in this register will set the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set RXFIFO overflow event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_RXOVF                                              0x00000001U
#define SPI_IMSET_RXOVF_M                                            0x00000001U
#define SPI_IMSET_RXOVF_S                                            0U
#define SPI_IMSET_RXOVF_SET                                          0x00000001U
#define SPI_IMSET_RXOVF_NO_EFFECT                                    0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Parity error event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_PER                                                0x00000002U
#define SPI_IMSET_PER_M                                              0x00000002U
#define SPI_IMSET_PER_S                                              1U
#define SPI_IMSET_PER_SET                                            0x00000002U
#define SPI_IMSET_PER_NO_EFFECT                                      0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set SPI Receive Time-Out event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_RTOUT                                              0x00000004U
#define SPI_IMSET_RTOUT_M                                            0x00000004U
#define SPI_IMSET_RTOUT_S                                            2U
#define SPI_IMSET_RTOUT_SET                                          0x00000004U
#define SPI_IMSET_RTOUT_NO_EFFECT                                    0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Receive FIFO event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_RX                                                 0x00000008U
#define SPI_IMSET_RX_M                                               0x00000008U
#define SPI_IMSET_RX_S                                               3U
#define SPI_IMSET_RX_SET                                             0x00000008U
#define SPI_IMSET_RX_NO_EFFECT                                       0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Transmit FIFO event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_TX                                                 0x00000010U
#define SPI_IMSET_TX_M                                               0x00000010U
#define SPI_IMSET_TX_S                                               4U
#define SPI_IMSET_TX_SET                                             0x00000010U
#define SPI_IMSET_TX_NO_EFFECT                                       0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set Transmit FIFO Empty event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_TXEMPTY                                            0x00000020U
#define SPI_IMSET_TXEMPTY_M                                          0x00000020U
#define SPI_IMSET_TXEMPTY_S                                          5U
#define SPI_IMSET_TXEMPTY_SET                                        0x00000020U
#define SPI_IMSET_TXEMPTY_NO_EFFECT                                  0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set SPI IDLE event mask


        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_IDLE                                               0x00000040U
#define SPI_IMSET_IDLE_M                                             0x00000040U
#define SPI_IMSET_IDLE_S                                             6U
#define SPI_IMSET_IDLE_SET                                           0x00000040U
#define SPI_IMSET_IDLE_NO_EFFECT                                     0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set DMA Done for RX event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_DMARX                                              0x00000080U
#define SPI_IMSET_DMARX_M                                            0x00000080U
#define SPI_IMSET_DMARX_S                                            7U
#define SPI_IMSET_DMARX_SET                                          0x00000080U
#define SPI_IMSET_DMARX_NO_EFFECT                                    0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Set DMA Done for TX event mask

        ENUMs:
            SET:                         Set interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMSET_DMATX                                              0x00000100U
#define SPI_IMSET_DMATX_M                                            0x00000100U
#define SPI_IMSET_DMATX_S                                            8U
#define SPI_IMSET_DMATX_SET                                          0x00000100U
#define SPI_IMSET_DMATX_NO_EFFECT                                    0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IMCLR
    Offset name:         SPI_O_IMCLR
    Relative address:    0x5C
    Description:         Interrupt mask clear register. Writing a 1 to a bit in this register will clear the corresponding [IMASK.*] bit.
    Default Value:       0x00000000

        Field:           RXOVF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear RXFIFO overflow event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_RXOVF                                              0x00000001U
#define SPI_IMCLR_RXOVF_M                                            0x00000001U
#define SPI_IMCLR_RXOVF_S                                            0U
#define SPI_IMCLR_RXOVF_CLR                                          0x00000001U
#define SPI_IMCLR_RXOVF_NO_EFFECT                                    0x00000000U
/*

        Field:           PER
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Parity error event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_PER                                                0x00000002U
#define SPI_IMCLR_PER_M                                              0x00000002U
#define SPI_IMCLR_PER_S                                              1U
#define SPI_IMCLR_PER_CLR                                            0x00000002U
#define SPI_IMCLR_PER_NO_EFFECT                                      0x00000000U
/*

        Field:           RTOUT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear SPI Receive Time-Out event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_RTOUT                                              0x00000004U
#define SPI_IMCLR_RTOUT_M                                            0x00000004U
#define SPI_IMCLR_RTOUT_S                                            2U
#define SPI_IMCLR_RTOUT_CLR                                          0x00000004U
#define SPI_IMCLR_RTOUT_NO_EFFECT                                    0x00000000U
/*

        Field:           RX
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Receive FIFO event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_RX                                                 0x00000008U
#define SPI_IMCLR_RX_M                                               0x00000008U
#define SPI_IMCLR_RX_S                                               3U
#define SPI_IMCLR_RX_CLR                                             0x00000008U
#define SPI_IMCLR_RX_NO_EFFECT                                       0x00000000U
/*

        Field:           TX
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Transmit FIFO event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_TX                                                 0x00000010U
#define SPI_IMCLR_TX_M                                               0x00000010U
#define SPI_IMCLR_TX_S                                               4U
#define SPI_IMCLR_TX_CLR                                             0x00000010U
#define SPI_IMCLR_TX_NO_EFFECT                                       0x00000000U
/*

        Field:           TXEMPTY
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear Transmit FIFO Empty event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_TXEMPTY                                            0x00000020U
#define SPI_IMCLR_TXEMPTY_M                                          0x00000020U
#define SPI_IMCLR_TXEMPTY_S                                          5U
#define SPI_IMCLR_TXEMPTY_CLR                                        0x00000020U
#define SPI_IMCLR_TXEMPTY_NO_EFFECT                                  0x00000000U
/*

        Field:           IDLE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear SPI IDLE event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_IDLE                                               0x00000040U
#define SPI_IMCLR_IDLE_M                                             0x00000040U
#define SPI_IMCLR_IDLE_S                                             6U
#define SPI_IMCLR_IDLE_CLR                                           0x00000040U
#define SPI_IMCLR_IDLE_NO_EFFECT                                     0x00000000U
/*

        Field:           DMARX
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear DMA Done for RX event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_DMARX                                              0x00000080U
#define SPI_IMCLR_DMARX_M                                            0x00000080U
#define SPI_IMCLR_DMARX_S                                            7U
#define SPI_IMCLR_DMARX_CLR                                          0x00000080U
#define SPI_IMCLR_DMARX_NO_EFFECT                                    0x00000000U
/*

        Field:           DMATX
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Clear DMA Done for TX event mask

        ENUMs:
            CLR:                         Clear interrupt mask
            NO_EFFECT:                   Writing 0 has no effect
*/
#define SPI_IMCLR_DMATX                                              0x00000100U
#define SPI_IMCLR_DMATX_M                                            0x00000100U
#define SPI_IMCLR_DMATX_S                                            8U
#define SPI_IMCLR_DMATX_CLR                                          0x00000100U
#define SPI_IMCLR_DMATX_NO_EFFECT                                    0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EMU
    Offset name:         SPI_O_EMU
    Relative address:    0x60
    Description:         Emulation control register. This register controls the behavior of the IP related to core halted input.
    Default Value:       0x00000000

        Field:           HALT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Halt control

        ENUMs:
            STOP:                        Freeze option. The IP freezes functionality when the core halted input is asserted, and resumes when it is deasserted. The freeze can either be immediate or after the IP has reached a boundary (end of word boundary, based on DSS configuration) from where it can resume without corruption.
            RUN:                         Free run option. The IP ignores the state of the core halted input.
*/
#define SPI_EMU_HALT                                                 0x00000001U
#define SPI_EMU_HALT_M                                               0x00000001U
#define SPI_EMU_HALT_S                                               0U
#define SPI_EMU_HALT_STOP                                            0x00000001U
#define SPI_EMU_HALT_RUN                                             0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL0
    Offset name:         SPI_O_CTL0
    Relative address:    0x100
    Description:         SPI control register 0
    Default Value:       0x00000000

        Field:           DSS
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data size select. The applicable DSS values for controller mode operation are 0x3 to 0xF and for peripheral mode operation are 0x6 to 0xF. DSS values 0x0 to 0x2 are reserved and must not be used.

        ENUMs:
            BITS_4:                      4-bits data size
            BITS_5:                      5-bits data size
            BITS_6:                      6-bits data size
            BITS_7:                      7-bits data size
            BITS_8:                      8-bits data size
            BITS_9:                      9-bits data size
            BITS_10:                     10-bits data size
            BITS_11:                     11-bits data size
            BITS_12:                     12-bits data size
            BITS_13:                     13-bits data size
            BITS_14:                     14-bits data size
            BITS_15:                     15-bits data size
            BITS_16:                     16-bits data size
*/
#define SPI_CTL0_DSS_W                                               4U
#define SPI_CTL0_DSS_M                                               0x0000000FU
#define SPI_CTL0_DSS_S                                               0U
#define SPI_CTL0_DSS_BITS_4                                          0x00000003U
#define SPI_CTL0_DSS_BITS_5                                          0x00000004U
#define SPI_CTL0_DSS_BITS_6                                          0x00000005U
#define SPI_CTL0_DSS_BITS_7                                          0x00000006U
#define SPI_CTL0_DSS_BITS_8                                          0x00000007U
#define SPI_CTL0_DSS_BITS_9                                          0x00000008U
#define SPI_CTL0_DSS_BITS_10                                         0x00000009U
#define SPI_CTL0_DSS_BITS_11                                         0x0000000AU
#define SPI_CTL0_DSS_BITS_12                                         0x0000000BU
#define SPI_CTL0_DSS_BITS_13                                         0x0000000CU
#define SPI_CTL0_DSS_BITS_14                                         0x0000000DU
#define SPI_CTL0_DSS_BITS_15                                         0x0000000EU
#define SPI_CTL0_DSS_BITS_16                                         0x0000000FU
/*

        Field:           FRF
        From..to bits:   5...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Frame format select

        ENUMs:
            MOTOROLA_3WIRE:              Motorola SPI frame format (3 wire mode)
            MOTOROLA_4WIRE:              Motorola SPI frame format (4 wire mode)
            TI_SYNC:                     TI synchronous serial frame format
            MICROWIRE:                   National Microwire frame format
*/
#define SPI_CTL0_FRF_W                                               2U
#define SPI_CTL0_FRF_M                                               0x00000060U
#define SPI_CTL0_FRF_S                                               5U
#define SPI_CTL0_FRF_MOTOROLA_3WIRE                                  0x00000000U
#define SPI_CTL0_FRF_MOTOROLA_4WIRE                                  0x00000020U
#define SPI_CTL0_FRF_TI_SYNC                                         0x00000040U
#define SPI_CTL0_FRF_MICROWIRE                                       0x00000060U
/*

        Field:           SPO
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLKOUT polarity (Motorola SPI frame format only).

        ENUMs:
            LOW:                         SPI produces a steady state LOW value on the CLKOUT
            HIGH:                        SPI produces a steady state HIGH value on the CLKOUT
*/
#define SPI_CTL0_SPO                                                 0x00000100U
#define SPI_CTL0_SPO_M                                               0x00000100U
#define SPI_CTL0_SPO_S                                               8U
#define SPI_CTL0_SPO_LOW                                             0x00000000U
#define SPI_CTL0_SPO_HIGH                                            0x00000100U
/*

        Field:           SPH
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CLKOUT phase (Motorola SPI frame format only).
                         This bit selects the clock edge that captures data and enables it to change state.
                         It has the most impact on the first bit transmitted by either permitting or not permitting a clock transition before the first data capture clock edge.

        ENUMs:
            FIRST:                       Data is captured on the first clock edge transition.
            SECOND:                      Data is captured on the second clock edge transition.
*/
#define SPI_CTL0_SPH                                                 0x00000200U
#define SPI_CTL0_SPH_M                                               0x00000200U
#define SPI_CTL0_SPH_S                                               9U
#define SPI_CTL0_SPH_FIRST                                           0x00000000U
#define SPI_CTL0_SPH_SECOND                                          0x00000200U
/*

        Field:           HWCSN
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Hardware controlled chip select (CS) value. When set CS is zero till TX FIFO is empty, as in -
                         a.	CS is de-asserted
                         b.	All data bytes are transmitted
                         c.	CS is asserted

        ENUMs:
            ENABLE:                      HWCS Enable
            DISABLE:                     HWCS Disable
*/
#define SPI_CTL0_HWCSN                                               0x00000400U
#define SPI_CTL0_HWCSN_M                                             0x00000400U
#define SPI_CTL0_HWCSN_S                                             10U
#define SPI_CTL0_HWCSN_ENABLE                                        0x00000400U
#define SPI_CTL0_HWCSN_DISABLE                                       0x00000000U
/*

        Field:           FIFORST
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit is used to reset transmit and receive FIFO pointers. This bit is auto cleared once the FIFO pointer reset operation is completed.

        ENUMs:
            RST_DONE:                    FIFO pointers reset completed when 0 is read
            RST_TRIG:                    Trigger FIFO pointers reset when written to 1.
*/
#define SPI_CTL0_FIFORST                                             0x00000800U
#define SPI_CTL0_FIFORST_M                                           0x00000800U
#define SPI_CTL0_FIFORST_S                                           11U
#define SPI_CTL0_FIFORST_RST_DONE                                    0x00000000U
#define SPI_CTL0_FIFORST_RST_TRIG                                    0x00000800U
/*

        Field:           CSCLR
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clear shift register counter on CS inactive.
                         This bit is relevant only in the peripheral mode, when [CTL1.MS]=0.

        ENUMs:
            DISABLE:                     Disable automatic clear of shift register when CS goes inactive.
            ENABLE:                      Enable automatic clear of shift register when CS goes inactive.
*/
#define SPI_CTL0_CSCLR                                               0x00001000U
#define SPI_CTL0_CSCLR_M                                             0x00001000U
#define SPI_CTL0_CSCLR_S                                             12U
#define SPI_CTL0_CSCLR_DISABLE                                       0x00000000U
#define SPI_CTL0_CSCLR_ENABLE                                        0x00001000U
/*

        Field:           CRCEND
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC16 Endianness

        ENUMs:
            CRC_END_MSB:                 Auto-insertion of CRC16 is most-significant byte first
            CRC_END_LSB:                 Auto-insertion of CRC16 is least-significant byte first
*/
#define SPI_CTL0_CRCEND                                              0x00002000U
#define SPI_CTL0_CRCEND_M                                            0x00002000U
#define SPI_CTL0_CRCEND_S                                            13U
#define SPI_CTL0_CRCEND_CRC_END_MSB                                  0x00000000U
#define SPI_CTL0_CRCEND_CRC_END_LSB                                  0x00002000U
/*

        Field:           AUTOCRC
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Auto insert CRC

        ENUMs:
            DISABLE:                     Do not insert CRC into TXFIFO upon TXFIFO underflow

            ENABLE:                      Insert CRC into TXFIFO upon TXFIFO underflow
*/
#define SPI_CTL0_AUTOCRC                                             0x00004000U
#define SPI_CTL0_AUTOCRC_M                                           0x00004000U
#define SPI_CTL0_AUTOCRC_S                                           14U
#define SPI_CTL0_AUTOCRC_DISABLE                                     0x00000000U
#define SPI_CTL0_AUTOCRC_ENABLE                                      0x00004000U
/*

        Field:           CRCPOLY
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC polynomial selection.

        ENUMs:
            _8BIT:                       Selects 8-bit CCITT CRC polynomial
            _16BIT:                      Selects 16-bit CCITT CRC polynomial
*/
#define SPI_CTL0_CRCPOLY                                             0x00008000U
#define SPI_CTL0_CRCPOLY_M                                           0x00008000U
#define SPI_CTL0_CRCPOLY_S                                           15U
#define SPI_CTL0_CRCPOLY__8BIT                                       0x00000000U
#define SPI_CTL0_CRCPOLY__16BIT                                      0x00008000U
/*

        Field:           GPCRCEN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     General purpose CRC enable. This bit enables transmit side CRC unit for general purpose use by software when SPI is disabled ([CTL1.EN] = 0). This bit must be 0 when SPI is enabled.

        ENUMs:
            DISABLE:                     Transmit side CRC unit is not available for general purpose software use
            ENABLE:                      Transmit side CRC unit is available for general purpose software use
*/
#define SPI_CTL0_GPCRCEN                                             0x00010000U
#define SPI_CTL0_GPCRCEN_M                                           0x00010000U
#define SPI_CTL0_GPCRCEN_S                                           16U
#define SPI_CTL0_GPCRCEN_DISABLE                                     0x00000000U
#define SPI_CTL0_GPCRCEN_ENABLE                                      0x00010000U
/*

        Field:           IDLEPOCI
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The Idle value of POCI - when TXFIFO is empty and before data is written into TXFIFO - can be controlled by this field.

        ENUMs:
            IDLE_ZERO:                   POCI output idle value of '0'
            IDLE_ONE:                    POCI outputs idle value of '1'
*/
#define SPI_CTL0_IDLEPOCI                                            0x00020000U
#define SPI_CTL0_IDLEPOCI_M                                          0x00020000U
#define SPI_CTL0_IDLEPOCI_S                                          17U
#define SPI_CTL0_IDLEPOCI_IDLE_ZERO                                  0x00000000U
#define SPI_CTL0_IDLEPOCI_IDLE_ONE                                   0x00020000U
/*

        Field:           CSSEL
        From..to bits:   18...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CS select for Multi SPI support
                         00 - CS0
                         01 - CS1
                         10 - CS2
                         11 - CS3

        ENUMs:
            CS0:                         Select CS0
            CS1:                         Select CS1
            CS2:                         Select CS2
            CS3:                         Select CS3
*/
#define SPI_CTL0_CSSEL_W                                             2U
#define SPI_CTL0_CSSEL_M                                             0x000C0000U
#define SPI_CTL0_CSSEL_S                                             18U
#define SPI_CTL0_CSSEL_CS0                                           0x00000000U
#define SPI_CTL0_CSSEL_CS1                                           0x00040000U
#define SPI_CTL0_CSSEL_CS2                                           0x00080000U
#define SPI_CTL0_CSSEL_CS3                                           0x000C0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTL1
    Offset name:         SPI_O_CTL1
    Relative address:    0x104
    Description:         SPI control register 1
    Default Value:       0x00000004

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPI enable.

        ENUMs:
            DISABLE:                     SPI is disabled
            ENABLE:                      SPI Enabled and released for operation.
*/
#define SPI_CTL1_EN                                                  0x00000001U
#define SPI_CTL1_EN_M                                                0x00000001U
#define SPI_CTL1_EN_S                                                0U
#define SPI_CTL1_EN_DISABLE                                          0x00000000U
#define SPI_CTL1_EN_ENABLE                                           0x00000001U
/*

        Field:           LBM
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Loop back mode control

        ENUMs:
            DISABLE:                     Disable loopback mode. Normal serial port operation enabled.
            ENABLE:                      Enable loopback mode. Output of transmit serial shifter is connected to input of receive serial shifter internally.
*/
#define SPI_CTL1_LBM                                                 0x00000002U
#define SPI_CTL1_LBM_M                                               0x00000002U
#define SPI_CTL1_LBM_S                                               1U
#define SPI_CTL1_LBM_DISABLE                                         0x00000000U
#define SPI_CTL1_LBM_ENABLE                                          0x00000002U
/*

        Field:           MS
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Controller or peripheral mode select. This bit can be modified only when SPI is disabled, [CTL1.EN]=0.

        ENUMs:
            PERIPHERAL:                  Select Peripheral mode
            CONTROLLER:                  Select Controller mode
*/
#define SPI_CTL1_MS                                                  0x00000004U
#define SPI_CTL1_MS_M                                                0x00000004U
#define SPI_CTL1_MS_S                                                2U
#define SPI_CTL1_MS_PERIPHERAL                                       0x00000000U
#define SPI_CTL1_MS_CONTROLLER                                       0x00000004U
/*

        Field:           POD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Peripheral data output disable.
                         This bit is relevant only in the peripheral mode, [MS]=1. In multiple-peripheral systems, it is possible for a SPI controller to broadcast a message to all peripherals in the system while ensuring that only one peripheral drives data onto its serial output line. In such systems the POCI lines from multiple peripherals could be tied together. To operate in such systems, this bit field can be set if the SPI peripheral is not supposed to drive the POCI output.

        ENUMs:
            DISABLE:                     SPI can drive the POCI output in peripheral mode.
            ENABLE:                      SPI cannot drive the POCI output in peripheral mode.
*/
#define SPI_CTL1_POD                                                 0x00000008U
#define SPI_CTL1_POD_M                                               0x00000008U
#define SPI_CTL1_POD_S                                               3U
#define SPI_CTL1_POD_DISABLE                                         0x00000000U
#define SPI_CTL1_POD_ENABLE                                          0x00000008U
/*

        Field:           MSB
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MSB first select. Controls the direction of receive and transmit shift register. MSB first configuration (MSB = 1) must be selected when CRC feature is used for SPI communication.

        ENUMs:
            LSB:                         LSB first
            MSB:                         MSB first
*/
#define SPI_CTL1_MSB                                                 0x00000010U
#define SPI_CTL1_MSB_M                                               0x00000010U
#define SPI_CTL1_MSB_S                                               4U
#define SPI_CTL1_MSB_LSB                                             0x00000000U
#define SPI_CTL1_MSB_MSB                                             0x00000010U
/*

        Field:           PEN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Parity enable. If enabled the last bit will be used as parity to evaluate the correct reception of the previous bits.
                         In case of parity mismatch the parity error flag [RIS.PER] will be set. This feature is available only in SPI controller mode.

        ENUMs:
            DISABLE:                     Disable Parity function
            ENABLE:                      Enable Parity function
*/
#define SPI_CTL1_PEN                                                 0x00000020U
#define SPI_CTL1_PEN_M                                               0x00000020U
#define SPI_CTL1_PEN_S                                               5U
#define SPI_CTL1_PEN_DISABLE                                         0x00000000U
#define SPI_CTL1_PEN_ENABLE                                          0x00000020U
/*

        Field:           PES
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Even parity select.

        ENUMs:
            ODD:                         Odd Parity mode
            EVEN:                        Even Parity mode
*/
#define SPI_CTL1_PES                                                 0x00000040U
#define SPI_CTL1_PES_M                                               0x00000040U
#define SPI_CTL1_PES_S                                               6U
#define SPI_CTL1_PES_ODD                                             0x00000000U
#define SPI_CTL1_PES_EVEN                                            0x00000040U
/*

        Field:           PBS
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Parity bit select

        ENUMs:
            BIT0:                        Bit 0 is used for Parity
            BIT1:                        Bit 1 is used for Parity, Bit 0 is ignored
*/
#define SPI_CTL1_PBS                                                 0x00000080U
#define SPI_CTL1_PBS_M                                               0x00000080U
#define SPI_CTL1_PBS_S                                               7U
#define SPI_CTL1_PBS_BIT0                                            0x00000000U
#define SPI_CTL1_PBS_BIT1                                            0x00000080U
/*

        Field:           CDEN
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command/Data mode enable. This feature is applicable only in controller mode and for 8-bit transfers ([CTL0.DSS] = 7). The chip select pin is used for command/data signaling in Motorola SPI frame format (3-wire) operation.

        ENUMs:
            DISABLE:                     C/D Mode Disable
            ENABLE:                      C/D Mode Enable
*/
#define SPI_CTL1_CDEN                                                0x00000800U
#define SPI_CTL1_CDEN_M                                              0x00000800U
#define SPI_CTL1_CDEN_S                                              11U
#define SPI_CTL1_CDEN_DISABLE                                        0x00000000U
#define SPI_CTL1_CDEN_ENABLE                                         0x00000800U
/*

        Field:           CDMODE
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Data Mode. This bit field value determines the behavior of C/D or CS signal when [CDEN] = 1. CS pin held low indicates command phase and CS pin held high indicates data phase.
                         When [CDMODE] = 0x0, the CS pin is always held high during transfer indicating data phase only operation (manual mode).
                         When [CDMODE] = 0xF, the CS pin is always held low during transfer indicating command phase only operation (manual mode).
                         When [CDMODE] = 0x1 to 0xE, the CS pin is held low for the number of bytes indicated by [CDMODE] value for the command phase and held high for the remaining transfers in the data phase (automatic mode).
                         When [CDMODE] is set to value 0x1 to 0xE, reading [CDMODE] during operation indicates the remaining bytes to be transferred in the command phase.

        ENUMs:
            COMMAND:                     Manual mode: Command
            DATA:                        Manual mode: Data
*/
#define SPI_CTL1_CDMODE_W                                            4U
#define SPI_CTL1_CDMODE_M                                            0x0000F000U
#define SPI_CTL1_CDMODE_S                                            12U
#define SPI_CTL1_CDMODE_COMMAND                                      0x0000F000U
#define SPI_CTL1_CDMODE_DATA                                         0x00000000U
/*

        Field:           REPTX
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Counter to repeat last transfer
                         0: repeat last transfer is disabled.
                         x: repeat the last transfer with the provided value.
                         The transfer will be started with writing a data into the TX FIFO. Sending the data will be repeated provided value number of times, so the data will be transferred x+1 times in total.
                         The behavior would be as if the data were be written into the TX FIFO as many times as defined by the value here additionally.
                         It can be used to clean a transfer or to pull a certain amount of data by a peripheral.

        ENUMs:
            DISABLE:                     REPTX disable
*/
#define SPI_CTL1_REPTX_W                                             8U
#define SPI_CTL1_REPTX_M                                             0x00FF0000U
#define SPI_CTL1_REPTX_S                                             16U
#define SPI_CTL1_REPTX_DISABLE                                       0x00000000U
/*

        Field:           RTOUT
        From..to bits:   24...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive Timeout (only for Peripheral mode)
                         Defines the number of Clock Cycles before after which the Receive Timeout flag [RIS.RTOUT] is set.
                         The time is calculated using the control register for the clock selection and divider in the Controller mode configuration.
                         A value of 0 disables this function.

*/
#define SPI_CTL1_RTOUT_W                                             6U
#define SPI_CTL1_RTOUT_M                                             0x3F000000U
#define SPI_CTL1_RTOUT_S                                             24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG0
    Offset name:         SPI_O_CLKCFG0
    Relative address:    0x108
    Description:         Clock configuration register 0. This register is used to configure the clock prescaler.
    Default Value:       0x00000000

        Field:           PRESC
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Prescaler configuration

        ENUMs:
            DIV_BY_1:                    Do not divide clock source
            DIV_BY_2:                    Divide clock source by 2
            DIV_BY_3:                    Divide clock source by 3
            DIV_BY_4:                    Divide clock source by 4
            DIV_BY_5:                    Divide clock source by 5
            DIV_BY_6:                    Divide clock source by 6
            DIV_BY_7:                    Divide clock source by 7
            DIV_BY_8:                    Divide clock source by 8
*/
#define SPI_CLKCFG0_PRESC_W                                          3U
#define SPI_CLKCFG0_PRESC_M                                          0x00000007U
#define SPI_CLKCFG0_PRESC_S                                          0U
#define SPI_CLKCFG0_PRESC_DIV_BY_1                                   0x00000000U
#define SPI_CLKCFG0_PRESC_DIV_BY_2                                   0x00000001U
#define SPI_CLKCFG0_PRESC_DIV_BY_3                                   0x00000002U
#define SPI_CLKCFG0_PRESC_DIV_BY_4                                   0x00000003U
#define SPI_CLKCFG0_PRESC_DIV_BY_5                                   0x00000004U
#define SPI_CLKCFG0_PRESC_DIV_BY_6                                   0x00000005U
#define SPI_CLKCFG0_PRESC_DIV_BY_7                                   0x00000006U
#define SPI_CLKCFG0_PRESC_DIV_BY_8                                   0x00000007U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG1
    Offset name:         SPI_O_CLKCFG1
    Relative address:    0x10C
    Description:         Clock configuration register 1. This register is used to configure serial clock rate and clock count for delayed sampling in controller mode.
    Default Value:       0x00000000

        Field:           SCR
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Serial clock divider. This is used to generate the transmit and receive bit rate of the SPI.
                         The SPI bit rate: (SPI functional clock frequency)/((SCR+1)*2). SCR value can be from 0 to 1023.

*/
#define SPI_CLKCFG1_SCR_W                                            10U
#define SPI_CLKCFG1_SCR_M                                            0x000003FFU
#define SPI_CLKCFG1_SCR_S                                            0U
/*

        Field:           DSAMPLE
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Delayed sampling. In controller mode the data on the input pin will be delayed sampled by the defined clock cycles. DSAMPLE values can range from 0 to SCR+1. Typically, values of 1 or 2 would suffice.

*/
#define SPI_CLKCFG1_DSAMPLE_W                                        4U
#define SPI_CLKCFG1_DSAMPLE_M                                        0x000F0000U
#define SPI_CLKCFG1_DSAMPLE_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IFLS
    Offset name:         SPI_O_IFLS
    Relative address:    0x110
    Description:         Interrupt FIFO level select register. This register can be used to define the levels at which the [RIS.TX], [RIS.RX] flags are triggered. The interrupts are generated based on FIFO level. Out of reset, the [IFLS.TXSEL] and [IFLS.RXSEL] bits are configured so that the FIFOs trigger an interrupt at the half-way mark.
    Default Value:       0x00000202

        Field:           TXSEL
        From..to bits:   0...2
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Transmit FIFO Level Select. The trigger points for the transmit interrupt are as follows:

        ENUMs:
            LVL_OFF:                     Reserved
            LVL_3_4:                     TX FIFO <= 3/4 empty
            LVL_1_2:                     TX FIFO <= 1/2 empty (default)
            LVL_1_4:                     TX FIFO <= 1/4 empty
            LVL_RES4:                    Reserved
            LVL_EMPTY:                   TX FIFO is empty
            LVL_RES6:                    Reserved
            LEVEL_1:                     Trigger when TX FIFO has >= 1 byte free
*/
#define SPI_IFLS_TXSEL_W                                             3U
#define SPI_IFLS_TXSEL_M                                             0x00000007U
#define SPI_IFLS_TXSEL_S                                             0U
#define SPI_IFLS_TXSEL_LVL_OFF                                       0x00000000U
#define SPI_IFLS_TXSEL_LVL_3_4                                       0x00000001U
#define SPI_IFLS_TXSEL_LVL_1_2                                       0x00000002U
#define SPI_IFLS_TXSEL_LVL_1_4                                       0x00000003U
#define SPI_IFLS_TXSEL_LVL_RES4                                      0x00000004U
#define SPI_IFLS_TXSEL_LVL_EMPTY                                     0x00000005U
#define SPI_IFLS_TXSEL_LVL_RES6                                      0x00000006U
#define SPI_IFLS_TXSEL_LEVEL_1                                       0x00000007U
/*

        Field:           RXSEL
        From..to bits:   8...10
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Receive FIFO Level Select. The trigger points for the receive interrupt are as follows:

        ENUMs:
            LVL_OFF:                     Reserved
            LVL_1_4:                     RX FIFO >= 1/4 full
            LVL_1_2:                     RX FIFO >= 1/2 full (default)
            LVL_3_4:                     RX FIFO >= 3/4 full
            LVL_RES4:                    Reserved
            LVL_FULL:                    RX FIFO is full
            LVL_RES6:                    Reserved
            LEVEL_1:                     Trigger when RX FIFO contains >= 1 byte

*/
#define SPI_IFLS_RXSEL_W                                             3U
#define SPI_IFLS_RXSEL_M                                             0x00000700U
#define SPI_IFLS_RXSEL_S                                             8U
#define SPI_IFLS_RXSEL_LVL_OFF                                       0x00000000U
#define SPI_IFLS_RXSEL_LVL_1_4                                       0x00000100U
#define SPI_IFLS_RXSEL_LVL_1_2                                       0x00000200U
#define SPI_IFLS_RXSEL_LVL_3_4                                       0x00000300U
#define SPI_IFLS_RXSEL_LVL_RES4                                      0x00000400U
#define SPI_IFLS_RXSEL_LVL_FULL                                      0x00000500U
#define SPI_IFLS_RXSEL_LVL_RES6                                      0x00000600U
#define SPI_IFLS_RXSEL_LEVEL_1                                       0x00000700U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMACR
    Offset name:         SPI_O_DMACR
    Relative address:    0x114
    Description:         DMA Control Register
    Default Value:       0x00000000

        Field:           RXEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive DMA enable. If this bit is set to 1, DMA for the receive FIFO is enabled.

        ENUMs:
            DISABLE:                     Disable RX DMA
            ENABLE:                      Enable RX DMA
*/
#define SPI_DMACR_RXEN                                               0x00000001U
#define SPI_DMACR_RXEN_M                                             0x00000001U
#define SPI_DMACR_RXEN_S                                             0U
#define SPI_DMACR_RXEN_DISABLE                                       0x00000000U
#define SPI_DMACR_RXEN_ENABLE                                        0x00000001U
/*

        Field:           TXEN
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit DMA enable. If this bit is set to 1, DMA for the transmit FIFO is enabled.

        ENUMs:
            DISABLE:                     Disable TX DMA
            ENABLE:                      Enable TX DMA
*/
#define SPI_DMACR_TXEN                                               0x00000100U
#define SPI_DMACR_TXEN_M                                             0x00000100U
#define SPI_DMACR_TXEN_S                                             8U
#define SPI_DMACR_TXEN_DISABLE                                       0x00000000U
#define SPI_DMACR_TXEN_ENABLE                                        0x00000100U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXCRC
    Offset name:         SPI_O_RXCRC
    Relative address:    0x118
    Description:         Receive CRC register. Reading this register provides the computed CRC value from the receive side CRC unit. Reading this register or writing to this register with any value auto initializes the seed. The seed value is 0xFF when [CTL0.CRCPOLY] = 0 and 0xFFFF when [CTL0.CRCPOLY] = 1 for CCITT CRC polynomials. Bits[15:8] are a don't care when [CTL0.CRCPOLY] = 0.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC value

*/
#define SPI_RXCRC_DATA_W                                             16U
#define SPI_RXCRC_DATA_M                                             0x0000FFFFU
#define SPI_RXCRC_DATA_S                                             0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXCRC
    Offset name:         SPI_O_TXCRC
    Relative address:    0x11C
    Description:         Transmit CRC register. Reading this register provides the computed CRC value from the transmit side CRC unit. Reading this register or writing to this register with any value auto initializes the seed. The seed value is 0xFF when [CTL0.CRCPOLY] = 0 and 0xFFFF when [CTL0.CRCPOLY] = 1 for CCITT CRC polynomials. Bits[15:8] are a don't care when [CTL0.CRCPOLY] = 0.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC value

*/
#define SPI_TXCRC_DATA_W                                             16U
#define SPI_TXCRC_DATA_M                                             0x0000FFFFU
#define SPI_TXCRC_DATA_S                                             0U
/*

        Field:           AUTOCRCINS
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Status to indicate if Auto CRC has been inserted into TXFIFO.
                         This is applicable only if [CTL0.AUTOCRC] enable bit is set

        ENUMs:
            NOT_INSERTED:                Auto CRC not yet inserted
            INSERTED:                    Auto CRC inserted
*/
#define SPI_TXCRC_AUTOCRCINS                                         0x80000000U
#define SPI_TXCRC_AUTOCRCINS_M                                       0x80000000U
#define SPI_TXCRC_AUTOCRCINS_S                                       31U
#define SPI_TXCRC_AUTOCRCINS_NOT_INSERTED                            0x00000000U
#define SPI_TXCRC_AUTOCRCINS_INSERTED                                0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXFHDR32
    Offset name:         SPI_O_TXFHDR32
    Relative address:    0x120
    Description:         Header update reigster for 32 bits of header data.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     write-only
        Description:     This field can be used to write four bytes of header data

*/
#define SPI_TXFHDR32_DATA_W                                          32U
#define SPI_TXFHDR32_DATA_M                                          0xFFFFFFFFU
#define SPI_TXFHDR32_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXFHDR24
    Offset name:         SPI_O_TXFHDR24
    Relative address:    0x124
    Description:         Header update reigster for 24 bits of header data.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     write-only
        Description:     This field can be used to write three bytes of header data

*/
#define SPI_TXFHDR24_DATA_W                                          32U
#define SPI_TXFHDR24_DATA_M                                          0xFFFFFFFFU
#define SPI_TXFHDR24_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXFHDR16
    Offset name:         SPI_O_TXFHDR16
    Relative address:    0x128
    Description:         Header update reigster for 16 bits of data.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     write-only
        Description:     This field can be used to write two bytes of header data

*/
#define SPI_TXFHDR16_DATA_W                                          32U
#define SPI_TXFHDR16_DATA_M                                          0xFFFFFFFFU
#define SPI_TXFHDR16_DATA_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXFHDR8
    Offset name:         SPI_O_TXFHDR8
    Relative address:    0x12C
    Description:         Header update reigster for 8 bits of header data.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     write-only
        Description:     This field can be used to write one byte of header data

*/
#define SPI_TXFHDR8_DATA_W                                           32U
#define SPI_TXFHDR8_DATA_M                                           0xFFFFFFFFU
#define SPI_TXFHDR8_DATA_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXFHDRC
    Offset name:         SPI_O_TXFHDRC
    Relative address:    0x130
    Description:         Atomic Header control register
    Default Value:       0x00000000

        Field:           HDREN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Header enable field. When [CSGATE] is set to BLK, this bit has to be set by software to enable this feature. When [CSGATE] is set to UNBLK, this field is set automatically whenever a write to header update registers occurs [TXFHDRn.*]

        ENUMs:
            DISABLE:                     Atomic header update feature disable
            ENABLE:                      Atomic header update feature enable
*/
#define SPI_TXFHDRC_HDREN                                            0x00000001U
#define SPI_TXFHDRC_HDREN_M                                          0x00000001U
#define SPI_TXFHDRC_HDREN_S                                          0U
#define SPI_TXFHDRC_HDREN_DISABLE                                    0x00000000U
#define SPI_TXFHDRC_HDREN_ENABLE                                     0x00000001U
/*

        Field:           HDRIGN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Header Ignored field. When [CSGATE] is set to BLK, this bit is set when the last Header update register [TXFHDRn.*] is written when CS is low or [HDRCMT] is already set. When [CSGATE] is set to UNBLK, this bit is set only when the header update register is written when [HDRCMT] is already set. This bit remains 0 otherwise. When set, this bit can be written to a value of 0 to clear.

        ENUMs:
            SET:                         Header update is ignored
            CLEAR:                       Header update is not ignored
*/
#define SPI_TXFHDRC_HDRIGN                                           0x00000002U
#define SPI_TXFHDRC_HDRIGN_M                                         0x00000002U
#define SPI_TXFHDRC_HDRIGN_S                                         1U
#define SPI_TXFHDRC_HDRIGN_SET                                       0x00000002U
#define SPI_TXFHDRC_HDRIGN_CLEAR                                     0x00000002U
/*

        Field:           HDRCMT
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Header Committed field. This bit is set when the [HDREN] bit is set and CS is sampled low. This bit remains 0 otherwise. When set, this bit can be written to a value of 0 to clear.

        ENUMs:
            SET:                         Header update is committed
            CLEAR:                       Header update is not committed
*/
#define SPI_TXFHDRC_HDRCMT                                           0x00000004U
#define SPI_TXFHDRC_HDRCMT_M                                         0x00000004U
#define SPI_TXFHDRC_HDRCMT_S                                         2U
#define SPI_TXFHDRC_HDRCMT_SET                                       0x00000004U
#define SPI_TXFHDRC_HDRCMT_CLEAR                                     0x00000000U
/*

        Field:           CSGATE
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Chip Select Gating control register. If this bit is set header update register writes are blocked when chip select (CS) is active low, and [HDRIGN] bit is set.
                         This bit resets to 0.

        ENUMs:
            BLOCKED:                     Header update register writes are blocked when CS is active (low)
            UNBLOCKED:                   The first header update register write is not blocked based on CS active status (low).
                         If no header update occurred when CS was high (inactive), the first header update is allowed when CS is low (active), and the HDRCMT bit is set. The use case is for the external controller to ensure that the SCLK is not driven during this header update.
                         If the header is already updated when CS is high and inactive, HDRCMT is set immediately when CS drops to active low state, and header writes when CS is low are ignored even if this UNBLK bit is set.
*/
#define SPI_TXFHDRC_CSGATE                                           0x00000008U
#define SPI_TXFHDRC_CSGATE_M                                         0x00000008U
#define SPI_TXFHDRC_CSGATE_S                                         3U
#define SPI_TXFHDRC_CSGATE_BLOCKED                                   0x00000008U
#define SPI_TXFHDRC_CSGATE_UNBLOCKED                                 0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXDATA
    Offset name:         SPI_O_RXDATA
    Relative address:    0x140
    Description:         RXDATA Register. Reading this register returns first value in the RX FIFO. If the FIFO is empty the last read value is returned. Writing has no effect and is ignored.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Received Data. When read, the entry in the receive FIFO, pointed to by the current FIFO read pointer is accessed. As data values are read by the receive logic from the incoming data frame, they are placed into the entry in the receive FIFO, pointed to by the current RX FIFO write pointer.
                         Received data less than 16 bits is automatically right-justified in the receive buffer.

*/
#define SPI_RXDATA_DATA_W                                            16U
#define SPI_RXDATA_DATA_M                                            0x0000FFFFU
#define SPI_RXDATA_DATA_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXDATA
    Offset name:         SPI_O_TXDATA
    Relative address:    0x150
    Description:         TXDATA Register. Writing a value in this register puts the data into the TX FIFO. Reading this register returns the last written value.
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit Data. When read, the last entry in the transmit FIFO, pointed to by the current FIFO write pointer is accessed.
                         When written, the entry in the TX FIFO pointed to by the write pointer, is written to. Data values are read from the transmit FIFO by the transmit logic. It is loaded into the transmit serial shifter, then serially shifted out onto the output pin at the programmed bit rate.
                         When a data size of less than 16 bits is selected, the user must right-justify data written to the transmit FIFO. The transmit logic ignores the unused bits.

*/
#define SPI_TXDATA_DATA_W                                            16U
#define SPI_TXDATA_DATA_M                                            0x0000FFFFU
#define SPI_TXDATA_DATA_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STA
    Offset name:         SPI_O_STA
    Relative address:    0x160
    Description:         Status Register
    Default Value:       0x00000001

        Field:           TFE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Transmit FIFO empty status.

        ENUMs:
            NOT_EMPTY:                   Transmit FIFO is not empty.
            EMPTY:                       Transmit FIFO is empty.
*/
#define SPI_STA_TFE                                                  0x00000001U
#define SPI_STA_TFE_M                                                0x00000001U
#define SPI_STA_TFE_S                                                0U
#define SPI_STA_TFE_NOT_EMPTY                                        0x00000000U
#define SPI_STA_TFE_EMPTY                                            0x00000001U
/*

        Field:           TNF
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Transmit FIFO not full status.

        ENUMs:
            NOT_FULL:                    Transmit FIFO is not full.
            FULL:                        Transmit FIFO is full.
*/
#define SPI_STA_TNF                                                  0x00000002U
#define SPI_STA_TNF_M                                                0x00000002U
#define SPI_STA_TNF_S                                                1U
#define SPI_STA_TNF_NOT_FULL                                         0x00000002U
#define SPI_STA_TNF_FULL                                             0x00000000U
/*

        Field:           RFE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive FIFO empty status.

        ENUMs:
            NOT_EMPTY:                   Receive FIFO is not empty.
            EMPTY:                       Receive FIFO is empty.
*/
#define SPI_STA_RFE                                                  0x00000004U
#define SPI_STA_RFE_M                                                0x00000004U
#define SPI_STA_RFE_S                                                2U
#define SPI_STA_RFE_NOT_EMPTY                                        0x00000000U
#define SPI_STA_RFE_EMPTY                                            0x00000004U
/*

        Field:           RNF
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Receive FIFO not full status.

        ENUMs:
            NOT_FULL:                    Receive FIFO is not full.
            FULL:                        Receive FIFO is full.
*/
#define SPI_STA_RNF                                                  0x00000008U
#define SPI_STA_RNF_M                                                0x00000008U
#define SPI_STA_RNF_S                                                3U
#define SPI_STA_RNF_NOT_FULL                                         0x00000008U
#define SPI_STA_RNF_FULL                                             0x00000000U
/*

        Field:           BUSY
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SPI Busy status

        ENUMs:
            ACTIVE:                      SPI is currently transmitting and/or receiving data, or transmit FIFO is not empty.
            IDLE:                        SPI is in idle mode.
*/
#define SPI_STA_BUSY                                                 0x00000010U
#define SPI_STA_BUSY_M                                               0x00000010U
#define SPI_STA_BUSY_S                                               4U
#define SPI_STA_BUSY_ACTIVE                                          0x00000010U
#define SPI_STA_BUSY_IDLE                                            0x00000000U
/*

        Field:           CSD
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Detection of CS deassertion in the middle of a word transmission results in this error being set. This feature is only available in the peripheral mode.

        ENUMs:
            ERROR:                       An error is generated when CS posedge (deassertion) is detected before the entire word is transmitted.
            NO_ERROR:                    No CS posedge is detected before the entire word has been transmitted.
*/
#define SPI_STA_CSD                                                  0x00000020U
#define SPI_STA_CSD_M                                                0x00000020U
#define SPI_STA_CSD_S                                                5U
#define SPI_STA_CSD_ERROR                                            0x00000020U
#define SPI_STA_CSD_NO_ERROR                                         0x00000000U
/*

        Field:           TXDONE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transmit done. Indicates whether the last bit left the Shift register after a transmission

        ENUMs:
            TRANSMIT_DONE:               Last bit has been shifted out, and the transmission is done
            TRANSMIT_INPROGRESS:         Last bit has not yet left the Shift register, and the transmission is ongoing.
*/
#define SPI_STA_TXDONE                                               0x00000040U
#define SPI_STA_TXDONE_M                                             0x00000040U
#define SPI_STA_TXDONE_S                                             6U
#define SPI_STA_TXDONE_TRANSMIT_DONE                                 0x00000040U
#define SPI_STA_TXDONE_TRANSMIT_INPROGRESS                           0x00000000U
/*

        Field:           TXFIFOLVL
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indicates how many locations of TXFIFO are currently filled with data

*/
#define SPI_STA_TXFIFOLVL_W                                          6U
#define SPI_STA_TXFIFOLVL_M                                          0x00003F00U
#define SPI_STA_TXFIFOLVL_S                                          8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         SPI_O_CLKCFG
    Relative address:    0x1000
    Description:         Clock Enable Register
    Default Value:       0x00000000

        Field:           ENABLE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SPI main clock Enable

*/
#define SPI_CLKCFG_ENABLE                                            0x00000001U
#define SPI_CLKCFG_ENABLE_M                                          0x00000001U
#define SPI_CLKCFG_ENABLE_S                                          0U

#endif /* __HW_SPI_H__*/
