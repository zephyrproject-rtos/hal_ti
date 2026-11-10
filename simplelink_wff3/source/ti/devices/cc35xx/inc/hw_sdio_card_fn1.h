/******************************************************************************
*  Filename:       hw_sdio_card_fn1.h
*
*  Description:    Defines and prototypes for the SDIO_CARD_FN1 peripheral.
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
#ifndef __HW_SDIO_CARD_FN1_H__
#define __HW_SDIO_CARD_FN1_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SDIO_CARD_FN1 component

--------------------------------------------------------------------------------- */

//A write only register
#define SDIO_CARD_FN1_O_FLUSHCMD                                     0x00000000U

//A R/W register that stores one of the RX buffer thresholds
#define SDIO_CARD_FN1_O_RXTHR                                        0x00000004U

//TX IRQ TRIG THR:
#define SDIO_CARD_FN1_O_TXIRQTHR                                     0x0000000CU

//A R/W register setting the BLOCK SIZE for the RX and TX DMA flow control
#define SDIO_CARD_FN1_O_DMABLKTHR                                    0x00000010U

//A RO register
#define SDIO_CARD_FN1_O_IRQSTA                                       0x00000014U

//A R/W register
#define SDIO_CARD_FN1_O_IRQMASK                                      0x00000018U

//A R/W register to control SDIO operation
#define SDIO_CARD_FN1_O_CTRL                                         0x0000001CU

//RX SDIO PACKET SIZE:
#define SDIO_CARD_FN1_O_RXPACS                                       0x00000020U

//RX BYTES IN BUFF:
#define SDIO_CARD_FN1_O_RXBBUF                                       0x00000024U

//RX BYTES LEFT:
#define SDIO_CARD_FN1_O_RXBLFT                                       0x00000028U

//A read/write register
#define SDIO_CARD_FN1_O_RETCTL                                       0x0000002CU

//IRQ2Host Message 16b
#define SDIO_CARD_FN1_O_C2HMSG                                       0x00000030U

//IRQ from Host to card Message 16b
#define SDIO_CARD_FN1_O_H2CMSG                                       0x00000034U

//Clock gating control
#define SDIO_CARD_FN1_O_CLKEN                                        0x00000038U

//A read/write 8-bit register that serves for future debug only
#define SDIO_CARD_FN1_O_SPAREREG                                     0x0000003CU

//A write-only register
#define SDIO_CARD_FN1_O_IRQCLR                                       0x00000040U

//reset sdio IP due to a SDIO Card Reset command:
#define SDIO_CARD_FN1_O_RSTREQ                                       0x00000044U

//Common shadow register to access SDIO-Card RX-Fifo or TX-Fifo
#define SDIO_CARD_FN1_O_DATAFIFO                                     0x00001000U



/*-----------------------------------REGISTER------------------------------------
    Register name:       FLUSHCMD
    Offset name:         SDIO_CARD_FN1_O_FLUSHCMD
    Relative address:    0x0
    Description:         A write only register. Flush command of the RX / TX buffers
    Default Value:       0x00000000

        Field:           RXBUF
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX BUFFER FLUSH:
                         Writing to this address triggers the flush command of the RX buffer (data value is irrelevant).

*/
#define SDIO_CARD_FN1_FLUSHCMD_RXBUF                                 0x00000001U
#define SDIO_CARD_FN1_FLUSHCMD_RXBUF_M                               0x00000001U
#define SDIO_CARD_FN1_FLUSHCMD_RXBUF_S                               0U
/*

        Field:           TXBUF
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX BUFFER FLUSH:
                         Writing to this address triggers the flush command of the TX buffer (data value is irrelevant).

*/
#define SDIO_CARD_FN1_FLUSHCMD_TXBUF                                 0x00000002U
#define SDIO_CARD_FN1_FLUSHCMD_TXBUF_M                               0x00000002U
#define SDIO_CARD_FN1_FLUSHCMD_TXBUF_S                               1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXTHR
    Offset name:         SDIO_CARD_FN1_O_RXTHR
    Relative address:    0x4
    Description:         A R/W register that stores one of the RX buffer thresholds.
    Default Value:       0x00000004

        Field:           VAL
        From..to bits:   2...7
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Buffer almost full threshold - When passing threshold an interrupt is generated (used by the software to indicate packets in buffer)
                         The threshold is configured to allow receiving a completer packet header including packet length.
                         Typical packet header could be   1 - 128 Bytes however the threshold must be 32bits aligned since SDIO FIFO supports 32bits aligned read only.

*/
#define SDIO_CARD_FN1_RXTHR_VAL_W                                    6U
#define SDIO_CARD_FN1_RXTHR_VAL_M                                    0x000000FCU
#define SDIO_CARD_FN1_RXTHR_VAL_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TXIRQTHR
    Offset name:         SDIO_CARD_FN1_O_TXIRQTHR
    Relative address:    0xC
    Description:         TX IRQ TRIG THR:
                        A R/W register that stores the Threshold in bytes to raise host irq.
    Default Value:       0x00000080

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    0x80
        Access type:     read-write
        Description:     8-bit value describing the number of bytes needed to trigger host irq
                         1. If HCI packet length > SDIO block (128-bytes) trigger is set to 128 Byte (entire block)
                         2. If HCI packet length < SDIO block, FW sets packet length in bytes as the trigger value

*/
#define SDIO_CARD_FN1_TXIRQTHR_VAL_W                                 8U
#define SDIO_CARD_FN1_TXIRQTHR_VAL_M                                 0x000000FFU
#define SDIO_CARD_FN1_TXIRQTHR_VAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMABLKTHR
    Offset name:         SDIO_CARD_FN1_O_DMABLKTHR
    Relative address:    0x10
    Description:         A R/W register setting the BLOCK SIZE for the RX and TX DMA flow control
    Default Value:       0x00020002

        Field:           RXDMABLK
        From..to bits:   0...2
        DefaultValue:    0x2
        Access type:     read-write
        Description:     RX DMA BLOCK SIZE SEL:
                         HOST Writes to FIFO
                         Determine when to assert flow control to DMA.
                         The flow should be asserted when num of bytes in FIFO > Threshold.
                         The threshold is determined according to the DMA block size
                         0 -     4 Bytes
                         1 -     8 Bytes
                         2 -   16 Bytes (Default)
                         3 -   32 Bytes
                         4 -   64 Bytes
                         5 - 128 Bytes
                         6,7 - Reserved HOST Writes to FIFO
                         Determine when to assert flow control to DMA.
                         The flow should be asserted when num of bytes in FIFO > Threshold.
                         The threshold is determined according to the DMA block size
                         0 -     4 Bytes
                         1 -     8 Bytes
                         2 -   16 Bytes (Default)
                         3 -   32 Bytes
                         4 -   64 Bytes
                         5 - 128 Bytes
                         6,7 - Reserved

*/
#define SDIO_CARD_FN1_DMABLKTHR_RXDMABLK_W                           3U
#define SDIO_CARD_FN1_DMABLKTHR_RXDMABLK_M                           0x00000007U
#define SDIO_CARD_FN1_DMABLKTHR_RXDMABLK_S                           0U
/*

        Field:           TXDMABLK
        From..to bits:   16...18
        DefaultValue:    0x2
        Access type:     read-write
        Description:     TX DMA BLOCK SIZE SEL:
                         HOST reads from FIFO
                         Determine when to assert flow control to DMA.
                         The flow should be asserted when FIFO has enough free buffer >= Threshold.
                         The threshold is determined according to the DMA block size
                         0 -     4 Bytes
                         1 -     8 Bytes
                         2 -   16 Bytes (Default)
                         3 -   32 Bytes
                         4 -   64 Bytes
                         5 - 128 Bytes
                         6,7 - Reserved

*/
#define SDIO_CARD_FN1_DMABLKTHR_TXDMABLK_W                           3U
#define SDIO_CARD_FN1_DMABLKTHR_TXDMABLK_M                           0x00070000U
#define SDIO_CARD_FN1_DMABLKTHR_TXDMABLK_S                           16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQSTA
    Offset name:         SDIO_CARD_FN1_O_IRQSTA
    Relative address:    0x14
    Description:         A RO register. Holds the status of the different interrupts of the SDIO.
                        This register is cleared by writing to IRQ_CLEAR register
                        Each interrupt is set when the event is active. In the case of ACKINT the software has to read the ACKNAK bit value to see if an ACK event was received or a read retry is starting.
    Default Value:       0x00000000

        Field:           RXALMSFULL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX Buffer almost full interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_RXALMSFULL                              0x00000001U
#define SDIO_CARD_FN1_IRQSTA_RXALMSFULL_M                            0x00000001U
#define SDIO_CARD_FN1_IRQSTA_RXALMSFULL_S                            0U
/*

        Field:           FN1EN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Function #1 enable interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_FN1EN                                   0x00000002U
#define SDIO_CARD_FN1_IRQSTA_FN1EN_M                                 0x00000002U
#define SDIO_CARD_FN1_IRQSTA_FN1EN_S                                 1U
/*

        Field:           RXBUFOVR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX Buffer overrun interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_RXBUFOVR                                0x00000004U
#define SDIO_CARD_FN1_IRQSTA_RXBUFOVR_M                              0x00000004U
#define SDIO_CARD_FN1_IRQSTA_RXBUFOVR_S                              2U
/*

        Field:           RXBUFUNR
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX Buffer under-run interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_RXBUFUNR                                0x00000008U
#define SDIO_CARD_FN1_IRQSTA_RXBUFUNR_M                              0x00000008U
#define SDIO_CARD_FN1_IRQSTA_RXBUFUNR_S                              3U
/*

        Field:           TXBUFOVR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX Buffer overrun interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_TXBUFOVR                                0x00000010U
#define SDIO_CARD_FN1_IRQSTA_TXBUFOVR_M                              0x00000010U
#define SDIO_CARD_FN1_IRQSTA_TXBUFOVR_S                              4U
/*

        Field:           TXBUFUNR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     TX Buffer under-run interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_TXBUFUNR                                0x00000020U
#define SDIO_CARD_FN1_IRQSTA_TXBUFUNR_M                              0x00000020U
#define SDIO_CARD_FN1_IRQSTA_TXBUFUNR_S                              5U
/*

        Field:           HCIACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HCI packet ACK interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_HCIACK                                  0x00000040U
#define SDIO_CARD_FN1_IRQSTA_HCIACK_M                                0x00000040U
#define SDIO_CARD_FN1_IRQSTA_HCIACK_S                                6U
/*

        Field:           HCINACK
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HCI packet NACK interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_HCINACK                                 0x00000080U
#define SDIO_CARD_FN1_IRQSTA_HCINACK_M                               0x00000080U
#define SDIO_CARD_FN1_IRQSTA_HCINACK_S                               7U
/*

        Field:           HCIWRRET
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HCI packet write retry

*/
#define SDIO_CARD_FN1_IRQSTA_HCIWRRET                                0x00000100U
#define SDIO_CARD_FN1_IRQSTA_HCIWRRET_M                              0x00000100U
#define SDIO_CARD_FN1_IRQSTA_HCIWRRET_S                              8U
/*

        Field:           PHYIFERR
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Error in the OCP interface of the SDIO PHY

*/
#define SDIO_CARD_FN1_IRQSTA_PHYIFERR                                0x00000200U
#define SDIO_CARD_FN1_IRQSTA_PHYIFERR_M                              0x00000200U
#define SDIO_CARD_FN1_IRQSTA_PHYIFERR_S                              9U
/*

        Field:           CARDRST
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Card Reset interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_CARDRST                                 0x00000400U
#define SDIO_CARD_FN1_IRQSTA_CARDRST_M                               0x00000400U
#define SDIO_CARD_FN1_IRQSTA_CARDRST_S                               10U
/*

        Field:           PHYINT
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SDIO PHY interrupt

*/
#define SDIO_CARD_FN1_IRQSTA_PHYINT                                  0x00000800U
#define SDIO_CARD_FN1_IRQSTA_PHYINT_M                                0x00000800U
#define SDIO_CARD_FN1_IRQSTA_PHYINT_S                                11U
/*

        Field:           CRCERR
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' = CRC Error was detected for rx flow

*/
#define SDIO_CARD_FN1_IRQSTA_CRCERR                                  0x00001000U
#define SDIO_CARD_FN1_IRQSTA_CRCERR_M                                0x00001000U
#define SDIO_CARD_FN1_IRQSTA_CRCERR_S                                12U
/*

        Field:           HOST2CORE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Host to Card 15 bit message ready indication

*/
#define SDIO_CARD_FN1_IRQSTA_HOST2CORE                               0x00002000U
#define SDIO_CARD_FN1_IRQSTA_HOST2CORE_M                             0x00002000U
#define SDIO_CARD_FN1_IRQSTA_HOST2CORE_S                             13U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQMASK
    Offset name:         SDIO_CARD_FN1_O_IRQMASK
    Relative address:    0x18
    Description:         A R/W register. Holds the mask bits of the different interrupts of the SDIO.
    Default Value:       0x00003FFF

        Field:           RXALMSFULL
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RX Buffer almost full interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_RXALMSFULL                             0x00000001U
#define SDIO_CARD_FN1_IRQMASK_RXALMSFULL_M                           0x00000001U
#define SDIO_CARD_FN1_IRQMASK_RXALMSFULL_S                           0U
/*

        Field:           FN1EN
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Function #1 enable interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_FN1EN                                  0x00000002U
#define SDIO_CARD_FN1_IRQMASK_FN1EN_M                                0x00000002U
#define SDIO_CARD_FN1_IRQMASK_FN1EN_S                                1U
/*

        Field:           RXBUFOVR
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RX Buffer overrun interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_RXBUFOVR                               0x00000004U
#define SDIO_CARD_FN1_IRQMASK_RXBUFOVR_M                             0x00000004U
#define SDIO_CARD_FN1_IRQMASK_RXBUFOVR_S                             2U
/*

        Field:           RXBUFUNR
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RX Buffer under-run interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_RXBUFUNR                               0x00000008U
#define SDIO_CARD_FN1_IRQMASK_RXBUFUNR_M                             0x00000008U
#define SDIO_CARD_FN1_IRQMASK_RXBUFUNR_S                             3U
/*

        Field:           TXBUFOVR
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     TX Buffer overrun interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_TXBUFOVR                               0x00000010U
#define SDIO_CARD_FN1_IRQMASK_TXBUFOVR_M                             0x00000010U
#define SDIO_CARD_FN1_IRQMASK_TXBUFOVR_S                             4U
/*

        Field:           TXBUFUNR
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-write
        Description:     TX Buffer under-run interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_TXBUFUNR                               0x00000020U
#define SDIO_CARD_FN1_IRQMASK_TXBUFUNR_M                             0x00000020U
#define SDIO_CARD_FN1_IRQMASK_TXBUFUNR_S                             5U
/*

        Field:           HCIACK
        From..to bits:   6...6
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HCI packet ACK interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_HCIACK                                 0x00000040U
#define SDIO_CARD_FN1_IRQMASK_HCIACK_M                               0x00000040U
#define SDIO_CARD_FN1_IRQMASK_HCIACK_S                               6U
/*

        Field:           HCINACK
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HCI packet NACK interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_HCINACK                                0x00000080U
#define SDIO_CARD_FN1_IRQMASK_HCINACK_M                              0x00000080U
#define SDIO_CARD_FN1_IRQMASK_HCINACK_S                              7U
/*

        Field:           HCIWRRET
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HCI packet write retry

*/
#define SDIO_CARD_FN1_IRQMASK_HCIWRRET                               0x00000100U
#define SDIO_CARD_FN1_IRQMASK_HCIWRRET_M                             0x00000100U
#define SDIO_CARD_FN1_IRQMASK_HCIWRRET_S                             8U
/*

        Field:           PHYIFERR
        From..to bits:   9...9
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Error in the OCP interface of the SDIO PHY

*/
#define SDIO_CARD_FN1_IRQMASK_PHYIFERR                               0x00000200U
#define SDIO_CARD_FN1_IRQMASK_PHYIFERR_M                             0x00000200U
#define SDIO_CARD_FN1_IRQMASK_PHYIFERR_S                             9U
/*

        Field:           CARDRST
        From..to bits:   10...10
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Card Reset interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_CARDRST                                0x00000400U
#define SDIO_CARD_FN1_IRQMASK_CARDRST_M                              0x00000400U
#define SDIO_CARD_FN1_IRQMASK_CARDRST_S                              10U
/*

        Field:           PHYMASK
        From..to bits:   11...11
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SDIO PHY interrupt

*/
#define SDIO_CARD_FN1_IRQMASK_PHYMASK                                0x00000800U
#define SDIO_CARD_FN1_IRQMASK_PHYMASK_M                              0x00000800U
#define SDIO_CARD_FN1_IRQMASK_PHYMASK_S                              11U
/*

        Field:           CRCERR
        From..to bits:   12...12
        DefaultValue:    0x1
        Access type:     read-write
        Description:     '1' = CRC Error was detected for rx flow

*/
#define SDIO_CARD_FN1_IRQMASK_CRCERR                                 0x00001000U
#define SDIO_CARD_FN1_IRQMASK_CRCERR_M                               0x00001000U
#define SDIO_CARD_FN1_IRQMASK_CRCERR_S                               12U
/*

        Field:           HOST2CORE
        From..to bits:   13...13
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Host to Card 15 bit message ready indication

*/
#define SDIO_CARD_FN1_IRQMASK_HOST2CORE                              0x00002000U
#define SDIO_CARD_FN1_IRQMASK_HOST2CORE_M                            0x00002000U
#define SDIO_CARD_FN1_IRQMASK_HOST2CORE_S                            13U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTRL
    Offset name:         SDIO_CARD_FN1_O_CTRL
    Relative address:    0x1C
    Description:         A R/W register to control SDIO operation.
    Default Value:       0x00000007

        Field:           SDIOEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SDIO enable - Enable SDIO after CRC error.
                         Cleared by HW after CRC error; Set by FW to de-assert the busy signal

*/
#define SDIO_CARD_FN1_CTRL_SDIOEN                                    0x00000001U
#define SDIO_CARD_FN1_CTRL_SDIOEN_M                                  0x00000001U
#define SDIO_CARD_FN1_CTRL_SDIOEN_S                                  0U
/*

        Field:           BACE
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     BUSY AFTER CRC ERROR:
                         Enables the module to activate the busy signal after CRC error on data only if sdio_enable was set

*/
#define SDIO_CARD_FN1_CTRL_BACE                                      0x00000002U
#define SDIO_CARD_FN1_CTRL_BACE_M                                    0x00000002U
#define SDIO_CARD_FN1_CTRL_BACE_S                                    1U
/*

        Field:           TXFLEN
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     TX BUFFER FLUSH ENABLE:
                         Enables the module to flush the TX buffer after receiving packet-read-retry indication (ACK or NACK). When this bit is '0', FW must flush the buffer manually (by writing to FLUSH_CMD register) upon receiving ACK/NACK interrupt. It is needed for the correct operation of the TX FIFO

*/
#define SDIO_CARD_FN1_CTRL_TXFLEN                                    0x00000004U
#define SDIO_CARD_FN1_CTRL_TXFLEN_M                                  0x00000004U
#define SDIO_CARD_FN1_CTRL_TXFLEN_S                                  2U
/*

        Field:           HIRQSYNC
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST IRQ SYNCHRONIZATION:
                         This bit controls the synchronization of the host interrupt (interrupt from BT to host through the PHY). '1' - interrupt is synchronized to sdio_clk. '0' - interrupt is not synchronized to sdio_clk (and thus synchronized to ocp_clk)

*/
#define SDIO_CARD_FN1_CTRL_HIRQSYNC                                  0x00000008U
#define SDIO_CARD_FN1_CTRL_HIRQSYNC_M                                0x00000008U
#define SDIO_CARD_FN1_CTRL_HIRQSYNC_S                                3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXPACS
    Offset name:         SDIO_CARD_FN1_O_RXPACS
    Relative address:    0x20
    Description:         RX SDIO PACKET SIZE:
                        A read only register. Holds the length of the current received SDIO packet. Updated at the beginning of each SDIO packet.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Length of the current received SDIO packet. Updated at the beginning of each SDIO packet

*/
#define SDIO_CARD_FN1_RXPACS_VAL_W                                   10U
#define SDIO_CARD_FN1_RXPACS_VAL_M                                   0x000003FFU
#define SDIO_CARD_FN1_RXPACS_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXBBUF
    Offset name:         SDIO_CARD_FN1_O_RXBBUF
    Relative address:    0x24
    Description:         RX BYTES IN BUFF:
                        A read only status register. Holds the current number of bytes in SDIO RX buffer.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Current number of bytes in SDIO RX buffer

*/
#define SDIO_CARD_FN1_RXBBUF_VAL_W                                   11U
#define SDIO_CARD_FN1_RXBBUF_VAL_M                                   0x000007FFU
#define SDIO_CARD_FN1_RXBBUF_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RXBLFT
    Offset name:         SDIO_CARD_FN1_O_RXBLFT
    Relative address:    0x28
    Description:         RX BYTES LEFT:
                        A read only status register. A down-count counter. Holds the number of bytes in current SDIO packet that were not transmitted to RX buffer yet. Please notice: Before reading this register, the FW MUST read RX_BYTES_IN_BUFFER register.
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     A counter that is loaded with SDIO packet length and decremented the same as the incrementing of bytes-in-buffer status register

*/
#define SDIO_CARD_FN1_RXBLFT_VAL_W                                   11U
#define SDIO_CARD_FN1_RXBLFT_VAL_M                                   0x000007FFU
#define SDIO_CARD_FN1_RXBLFT_VAL_S                                   0U
/*

        Field:           BLIL
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     BYTES LEFT IS LOCKED:
                         When '0' - the value that is read from rx_bytes_left is the current number of bytes left to transfer to the end of the block.
                         When '1' - the value that is read from rx_bytes_left is the number of bytes left to transfer to the end of the block that was locked on the last read from RX_BYTES_IN_BUF.

*/
#define SDIO_CARD_FN1_RXBLFT_BLIL                                    0x00008000U
#define SDIO_CARD_FN1_RXBLFT_BLIL_M                                  0x00008000U
#define SDIO_CARD_FN1_RXBLFT_BLIL_S                                  15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RETCTL
    Offset name:         SDIO_CARD_FN1_O_RETCTL
    Relative address:    0x2C
    Description:         A read/write register. The value states if the BT-SDIO is working with Retry Control mechanism as specified in SDIO spec.
    Default Value:       0x00000001

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     When FW writes '1' to this bit, it states that the BT-SDIO is using retry control mechanism. When FW reads this bit, it actually reads the value of the Function 1's RETRY_CONTROL register (the value that the host configured). Default value is '1' because BT FW MUST have retry control mechanism working

*/
#define SDIO_CARD_FN1_RETCTL_VAL                                     0x00000001U
#define SDIO_CARD_FN1_RETCTL_VAL_M                                   0x00000001U
#define SDIO_CARD_FN1_RETCTL_VAL_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       C2HMSG
    Offset name:         SDIO_CARD_FN1_O_C2HMSG
    Relative address:    0x30
    Description:         IRQ2Host Message 16b
    Default Value:       0x00000000

        Field:           C2HSTS
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CARD TO HOST STS:
                         To Host: 16bits MMR which can be written/read by M33 and read/clear (bit map) by host
                         Cleared by HOST writing to CLINTERD (Interrupt Clear 0x13)

*/
#define SDIO_CARD_FN1_C2HMSG_C2HSTS_W                                16U
#define SDIO_CARD_FN1_C2HMSG_C2HSTS_M                                0x0000FFFFU
#define SDIO_CARD_FN1_C2HMSG_C2HSTS_S                                0U
/*

        Field:           C2HIRQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CARD TO HOST IRQ:
                         To Host: 16bits MMR which can be written/read by M33 and read/clear (bit map) by host

*/
#define SDIO_CARD_FN1_C2HMSG_C2HIRQ                                  0x00010000U
#define SDIO_CARD_FN1_C2HMSG_C2HIRQ_M                                0x00010000U
#define SDIO_CARD_FN1_C2HMSG_C2HIRQ_S                                16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       H2CMSG
    Offset name:         SDIO_CARD_FN1_O_H2CMSG
    Relative address:    0x34
    Description:         IRQ from Host to card Message 16b
    Default Value:       0x00000000

        Field:           H2CSTS
        From..to bits:   0...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HOST TO CARD STS:
                         From Host: 15bits MMR which can be written by host and read/clear (bit map) by M33.
                         (bit 16 is the host_to_card_irq that is generated by the HOST and goes to [IRQ_STATUS.HOST_TO_CARD_INT])

*/
#define SDIO_CARD_FN1_H2CMSG_H2CSTS_W                                15U
#define SDIO_CARD_FN1_H2CMSG_H2CSTS_M                                0x00007FFFU
#define SDIO_CARD_FN1_H2CMSG_H2CSTS_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKEN
    Offset name:         SDIO_CARD_FN1_O_CLKEN
    Relative address:    0x38
    Description:         Clock gating control
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1'b0 - disable clk
                         1'b1 - enable clk

*/
#define SDIO_CARD_FN1_CLKEN_VAL                                      0x00000001U
#define SDIO_CARD_FN1_CLKEN_VAL_M                                    0x00000001U
#define SDIO_CARD_FN1_CLKEN_VAL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPAREREG
    Offset name:         SDIO_CARD_FN1_O_SPAREREG
    Relative address:    0x3C
    Description:         A read/write 8-bit register that serves for future debug only.
    Default Value:       0x00000000

        Field:           SPARE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define SDIO_CARD_FN1_SPAREREG_SPARE_W                               8U
#define SDIO_CARD_FN1_SPAREREG_SPARE_M                               0x000000FFU
#define SDIO_CARD_FN1_SPAREREG_SPARE_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQCLR
    Offset name:         SDIO_CARD_FN1_O_IRQCLR
    Relative address:    0x40
    Description:         A write-only register. When written, it clears all SDIO pending interrupts
    Default Value:       0x00000000

        Field:           RXALMSFULL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX Buffer almost full interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_RXALMSFULL                              0x00000001U
#define SDIO_CARD_FN1_IRQCLR_RXALMSFULL_M                            0x00000001U
#define SDIO_CARD_FN1_IRQCLR_RXALMSFULL_S                            0U
/*

        Field:           FN1EN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Function #1 enable interrupt

*/
#define SDIO_CARD_FN1_IRQCLR_FN1EN                                   0x00000002U
#define SDIO_CARD_FN1_IRQCLR_FN1EN_M                                 0x00000002U
#define SDIO_CARD_FN1_IRQCLR_FN1EN_S                                 1U
/*

        Field:           RXBUFOVR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX Buffer overrun interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_RXBUFOVR                                0x00000004U
#define SDIO_CARD_FN1_IRQCLR_RXBUFOVR_M                              0x00000004U
#define SDIO_CARD_FN1_IRQCLR_RXBUFOVR_S                              2U
/*

        Field:           RXBUFUNR
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     RX Buffer under-run interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_RXBUFUNR                                0x00000008U
#define SDIO_CARD_FN1_IRQCLR_RXBUFUNR_M                              0x00000008U
#define SDIO_CARD_FN1_IRQCLR_RXBUFUNR_S                              3U
/*

        Field:           TXBUFOVR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX Buffer overrun interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_TXBUFOVR                                0x00000010U
#define SDIO_CARD_FN1_IRQCLR_TXBUFOVR_M                              0x00000010U
#define SDIO_CARD_FN1_IRQCLR_TXBUFOVR_S                              4U
/*

        Field:           TXBUFUNR
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     TX Buffer under-run interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_TXBUFUNR                                0x00000020U
#define SDIO_CARD_FN1_IRQCLR_TXBUFUNR_M                              0x00000020U
#define SDIO_CARD_FN1_IRQCLR_TXBUFUNR_S                              5U
/*

        Field:           HCIACK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HCI packet ACK interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_HCIACK                                  0x00000040U
#define SDIO_CARD_FN1_IRQCLR_HCIACK_M                                0x00000040U
#define SDIO_CARD_FN1_IRQCLR_HCIACK_S                                6U
/*

        Field:           HCINACK
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HCI packet NACK interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_HCINACK                                 0x00000080U
#define SDIO_CARD_FN1_IRQCLR_HCINACK_M                               0x00000080U
#define SDIO_CARD_FN1_IRQCLR_HCINACK_S                               7U
/*

        Field:           HCIWRRET
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     HCI packet write retry clear

*/
#define SDIO_CARD_FN1_IRQCLR_HCIWRRET                                0x00000100U
#define SDIO_CARD_FN1_IRQCLR_HCIWRRET_M                              0x00000100U
#define SDIO_CARD_FN1_IRQCLR_HCIWRRET_S                              8U
/*

        Field:           PHYIFERR
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Error in the OCP interface of the SDIO PHY clear

*/
#define SDIO_CARD_FN1_IRQCLR_PHYIFERR                                0x00000200U
#define SDIO_CARD_FN1_IRQCLR_PHYIFERR_M                              0x00000200U
#define SDIO_CARD_FN1_IRQCLR_PHYIFERR_S                              9U
/*

        Field:           CARDRST
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Card Reset interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_CARDRST                                 0x00000400U
#define SDIO_CARD_FN1_IRQCLR_CARDRST_M                               0x00000400U
#define SDIO_CARD_FN1_IRQCLR_CARDRST_S                               10U
/*

        Field:           PHYCLEAR
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     SDIO PHY interrupt clear

*/
#define SDIO_CARD_FN1_IRQCLR_PHYCLEAR                                0x00000800U
#define SDIO_CARD_FN1_IRQCLR_PHYCLEAR_M                              0x00000800U
#define SDIO_CARD_FN1_IRQCLR_PHYCLEAR_S                              11U
/*

        Field:           CRCERR
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     write-only
        Description:     CRC Error clear

*/
#define SDIO_CARD_FN1_IRQCLR_CRCERR                                  0x00001000U
#define SDIO_CARD_FN1_IRQCLR_CRCERR_M                                0x00001000U
#define SDIO_CARD_FN1_IRQCLR_CRCERR_S                                12U
/*

        Field:           HOST2CORE
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Host to Card 15 bit message ready indication

*/
#define SDIO_CARD_FN1_IRQCLR_HOST2CORE                               0x00002000U
#define SDIO_CARD_FN1_IRQCLR_HOST2CORE_M                             0x00002000U
#define SDIO_CARD_FN1_IRQCLR_HOST2CORE_S                             13U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RSTREQ
    Offset name:         SDIO_CARD_FN1_O_RSTREQ
    Relative address:    0x44
    Description:         reset sdio IP due to a SDIO Card Reset command:

                        0 - do not reset / de-assert initiated sdio reset
                        1 - initiate reset sdio reset (both PHY and SDIO System)
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Function #1 enable interrupt

*/
#define SDIO_CARD_FN1_RSTREQ_EN                                      0x00000001U
#define SDIO_CARD_FN1_RSTREQ_EN_M                                    0x00000001U
#define SDIO_CARD_FN1_RSTREQ_EN_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DATAFIFO
    Offset name:         SDIO_CARD_FN1_O_DATAFIFO
    Relative address:    0x1000
    Description:         Common shadow register to access SDIO-Card RX-Fifo or TX-Fifo
    Default Value:       0x00000000

        Field:           RDRXWRTX
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Common access for either:
                         1. Reading 'sdio_rxfifo'
                         2. Writing 'sdio_txfifo'
                         Can be used either as local ocp rd/wr commands, or transactions through DMA machine.

*/
#define SDIO_CARD_FN1_DATAFIFO_RDRXWRTX_W                            32U
#define SDIO_CARD_FN1_DATAFIFO_RDRXWRTX_M                            0xFFFFFFFFU
#define SDIO_CARD_FN1_DATAFIFO_RDRXWRTX_S                            0U

#endif /* __HW_SDIO_CARD_FN1_H__*/
