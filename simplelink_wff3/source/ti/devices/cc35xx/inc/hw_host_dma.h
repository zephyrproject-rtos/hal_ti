/******************************************************************************
*  Filename:       hw_host_dma.h
*
*  Description:    Defines and prototypes for the HOST_DMA peripheral.
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
#ifndef __HW_HOST_DMA_H__
#define __HW_HOST_DMA_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOST_DMA component

--------------------------------------------------------------------------------- */

//Host DMA Channel Controlled by Defined Peripheral
#define HOST_DMA_O_CHCTL0                                            0x00000000U

//Host DMA Channel Controlled by Defined Peripheral
#define HOST_DMA_O_CHCTL1                                            0x00000004U

//Priority Channel Configuration
#define HOST_DMA_O_PRIOCFG                                           0x00000018U

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH0STA                                            0x00001000U

//Input Pointer Channel Transaction
#define HOST_DMA_O_CH0TIPTR                                          0x00001004U

//Output Pointer Channel Transaction
#define HOST_DMA_O_CH0OPTR                                           0x00001008U

//Transaction control
#define HOST_DMA_O_CH0TCTL                                           0x0000100CU

//DMA command interface
#define HOST_DMA_O_CH0TCTL2                                          0x00001010U

//Transaction Status
#define HOST_DMA_O_CH0TSTA                                           0x00001014U

//Job control register
#define HOST_DMA_O_CH0JCTL                                           0x0000101CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH1STA                                            0x00002000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH1TIPTR                                          0x00002004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH1TOPTR                                          0x00002008U

//Transaction control
#define HOST_DMA_O_CH1TCTL                                           0x0000200CU

//DMA command interface
#define HOST_DMA_O_CH1TCTRL2                                         0x00002010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH1TSTA                                           0x00002014U

//Job control register
#define HOST_DMA_O_CH1JCTL                                           0x0000201CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH2STA                                            0x00003000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH2TIPTR                                          0x00003004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH2TOPTR                                          0x00003008U

//Transaction control
#define HOST_DMA_O_CH2TCTL                                           0x0000300CU

//DMA command interface
#define HOST_DMA_O_CH2TCTL2                                          0x00003010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH2TSTA                                           0x00003014U

//Job control register
#define HOST_DMA_O_CH2JCTL                                           0x0000301CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH3STA                                            0x00004000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH3TIPTR                                          0x00004004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH3TOPTR                                          0x00004008U

//Transaction control
#define HOST_DMA_O_CH3TCTL                                           0x0000400CU

//DMA command interface
#define HOST_DMA_O_CH3TCTL2                                          0x00004010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH3TSTA                                           0x00004014U

//Job control register
#define HOST_DMA_O_CH3JCTL                                           0x0000401CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH4STA                                            0x00005000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH4TIPTR                                          0x00005004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH4TOPTR                                          0x00005008U

//Transaction control
#define HOST_DMA_O_CH4TCTL                                           0x0000500CU

//DMA command interface
#define HOST_DMA_O_CH4TCTL2                                          0x00005010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH4TSTA                                           0x00005014U

//Job control register
#define HOST_DMA_O_CH4JCTL                                           0x0000501CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH5STA                                            0x00006000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH5TIPTR                                          0x00006004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH5TOPTR                                          0x00006008U

//Transaction control
#define HOST_DMA_O_CH5TCTL                                           0x0000600CU

//DMA command interface
#define HOST_DMA_O_CH5TCTL2                                          0x00006010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH5TSTA                                           0x00006014U

//Job control register
#define HOST_DMA_O_CH5JCTL                                           0x0000601CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH6STA                                            0x00007000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH6TIPTR                                          0x00007004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH6TOPTR                                          0x00007008U

//Transaction control
#define HOST_DMA_O_CH6TCTL                                           0x0000700CU

//DMA command interface
#define HOST_DMA_O_CH6TCTL2                                          0x00007010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH6TSTA                                           0x00007014U

//Job control register
#define HOST_DMA_O_CH6JCTL                                           0x0000701CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH7STA                                            0x00008000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH7TIPTR                                          0x00008004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH7TOPTR                                          0x00008008U

//Transaction control
#define HOST_DMA_O_CH7TCTL                                           0x0000800CU

//DMA command interface
#define HOST_DMA_O_CH7TCTL2                                          0x00008010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH7TSTA                                           0x00008014U

//Job control register
#define HOST_DMA_O_CH7JCTL                                           0x0000801CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH8STA                                            0x00009000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH8TIPTR                                          0x00009004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH8TOPTR                                          0x00009008U

//Transaction control
#define HOST_DMA_O_CH8TCTL                                           0x0000900CU

//DMA command interface
#define HOST_DMA_O_CH8TCTL2                                          0x00009010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH8TSTA                                           0x00009014U

//Job control register
#define HOST_DMA_O_CH8JCTL                                           0x0000901CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH9STA                                            0x0000A000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH9TIPTR                                          0x0000A004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH9TOPTR                                          0x0000A008U

//Transaction control
#define HOST_DMA_O_CH9TCTL                                           0x0000A00CU

//DMA command interface
#define HOST_DMA_O_CH9TCTL2                                          0x0000A010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH9TSTA                                           0x0000A014U

//Job control register
#define HOST_DMA_O_CH9JCTL                                           0x0000A01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH10STA                                           0x0000B000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH10TIPTR                                         0x0000B004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH10TOPTR                                         0x0000B008U

//Transaction control
#define HOST_DMA_O_CH10TCTL                                          0x0000B00CU

//DMA command interface
#define HOST_DMA_O_CH10TCTL2                                         0x0000B010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH10TSTA                                          0x0000B014U

//Job control register
#define HOST_DMA_O_CH10JCTL                                          0x0000B01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH11STA                                           0x0000C000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH11TIPTR                                         0x0000C004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH11TOPTR                                         0x0000C008U

//Transaction control
#define HOST_DMA_O_CH11TCTL                                          0x0000C00CU

//DMA command interface
#define HOST_DMA_O_CH11TCTL2                                         0x0000C010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH11TSTA                                          0x0000C014U

//Job control register
#define HOST_DMA_O_CH11JCTL                                          0x0000C01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH12STA                                           0x0000D000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH12TIPTR                                         0x0000D004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH12TOPTR                                         0x0000D008U

//Transaction control
#define HOST_DMA_O_CH12TCTL                                          0x0000D00CU

//DMA command interface
#define HOST_DMA_O_CH12TCTL2                                         0x0000D010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH12TSTA                                          0x0000D014U

//Job control register
#define HOST_DMA_O_CH12JCTL                                          0x0000D01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH13STA                                           0x0000E000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH13TIPTR                                         0x0000E004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH13TOPTR                                         0x0000E008U

//Transaction control
#define HOST_DMA_O_CH13TCTL                                          0x0000E00CU

//DMA command interface
#define HOST_DMA_O_CH13TCTL2                                         0x0000E010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH13TSTA                                          0x0000E014U

//Job control register
#define HOST_DMA_O_CH13JCTL                                          0x0000E01CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       CHCTL0
    Offset name:         HOST_DMA_O_CHCTL0
    Relative address:    0x0
    Description:         Host DMA Channel Controlled by Defined Peripheral.

                        The value of each fields concats with [HOST_DMA:JOBCTLCHx.SRCDSTCFG] (when x is channel num)
                        if [CHCTL0.CHx] = 4 and [JOBCTLCHx.SRCDSTCFG] = 1 (value = 0100_1 = 9)
                        then flow control signals of channel x are connected to periph number 9 flow control signals

                        Note: [CHCTL0.CHx] = 0xF is forbidden. This configuration should be only used for Dynamic Switch
    Default Value:       0x00000000

        Field:           CH0
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 0 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH0_W                                        4U
#define HOST_DMA_CHCTL0_CH0_M                                        0x0000000FU
#define HOST_DMA_CHCTL0_CH0_S                                        0U
#define HOST_DMA_CHCTL0_CH0_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH0_UART1                                    0x00000001U
#define HOST_DMA_CHCTL0_CH0_SPIO                                     0x00000002U
#define HOST_DMA_CHCTL0_CH0_SPI1                                     0x00000003U
#define HOST_DMA_CHCTL0_CH0_I2C0                                     0x00000004U
#define HOST_DMA_CHCTL0_CH0_I2C1                                     0x00000005U
#define HOST_DMA_CHCTL0_CH0_SDMMC                                    0x00000006U
#define HOST_DMA_CHCTL0_CH0_SDIO                                     0x00000007U
#define HOST_DMA_CHCTL0_CH0_MCAN                                     0x00000008U
#define HOST_DMA_CHCTL0_CH0_ADC                                      0x00000009U
#define HOST_DMA_CHCTL0_CH0_PDM                                      0x0000000AU
#define HOST_DMA_CHCTL0_CH0_HIF                                      0x0000000BU
#define HOST_DMA_CHCTL0_CH0_UART2                                    0x0000000CU
/*

        Field:           CH1
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 1 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH1_W                                        4U
#define HOST_DMA_CHCTL0_CH1_M                                        0x000000F0U
#define HOST_DMA_CHCTL0_CH1_S                                        4U
#define HOST_DMA_CHCTL0_CH1_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH1_UART1                                    0x00000010U
#define HOST_DMA_CHCTL0_CH1_SPIO                                     0x00000020U
#define HOST_DMA_CHCTL0_CH1_SPI1                                     0x00000030U
#define HOST_DMA_CHCTL0_CH1_I2C0                                     0x00000040U
#define HOST_DMA_CHCTL0_CH1_I2C1                                     0x00000050U
#define HOST_DMA_CHCTL0_CH1_SDMMC                                    0x00000060U
#define HOST_DMA_CHCTL0_CH1_SDIO                                     0x00000070U
#define HOST_DMA_CHCTL0_CH1_MCAN                                     0x00000080U
#define HOST_DMA_CHCTL0_CH1_ADC                                      0x00000090U
#define HOST_DMA_CHCTL0_CH1_PDM                                      0x000000A0U
#define HOST_DMA_CHCTL0_CH1_HIF                                      0x000000B0U
#define HOST_DMA_CHCTL0_CH1_UART2                                    0x000000C0U
/*

        Field:           CH2
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 2 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH2_W                                        4U
#define HOST_DMA_CHCTL0_CH2_M                                        0x00000F00U
#define HOST_DMA_CHCTL0_CH2_S                                        8U
#define HOST_DMA_CHCTL0_CH2_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH2_UART1                                    0x00000100U
#define HOST_DMA_CHCTL0_CH2_SPIO                                     0x00000200U
#define HOST_DMA_CHCTL0_CH2_SPI1                                     0x00000300U
#define HOST_DMA_CHCTL0_CH2_I2C0                                     0x00000400U
#define HOST_DMA_CHCTL0_CH2_I2C1                                     0x00000500U
#define HOST_DMA_CHCTL0_CH2_SDMMC                                    0x00000600U
#define HOST_DMA_CHCTL0_CH2_SDIO                                     0x00000700U
#define HOST_DMA_CHCTL0_CH2_MCAN                                     0x00000800U
#define HOST_DMA_CHCTL0_CH2_ADC                                      0x00000900U
#define HOST_DMA_CHCTL0_CH2_PDM                                      0x00000A00U
#define HOST_DMA_CHCTL0_CH2_HIF                                      0x00000B00U
#define HOST_DMA_CHCTL0_CH2_UART2                                    0x00000C00U
/*

        Field:           CH3
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 3 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH3_W                                        4U
#define HOST_DMA_CHCTL0_CH3_M                                        0x0000F000U
#define HOST_DMA_CHCTL0_CH3_S                                        12U
#define HOST_DMA_CHCTL0_CH3_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH3_UART1                                    0x00001000U
#define HOST_DMA_CHCTL0_CH3_SPIO                                     0x00002000U
#define HOST_DMA_CHCTL0_CH3_SPI1                                     0x00003000U
#define HOST_DMA_CHCTL0_CH3_I2C0                                     0x00004000U
#define HOST_DMA_CHCTL0_CH3_I2C1                                     0x00005000U
#define HOST_DMA_CHCTL0_CH3_SDMMC                                    0x00006000U
#define HOST_DMA_CHCTL0_CH3_SDIO                                     0x00007000U
#define HOST_DMA_CHCTL0_CH3_MCAN                                     0x00008000U
#define HOST_DMA_CHCTL0_CH3_ADC                                      0x00009000U
#define HOST_DMA_CHCTL0_CH3_PDM                                      0x0000A000U
#define HOST_DMA_CHCTL0_CH3_HIF                                      0x0000B000U
#define HOST_DMA_CHCTL0_CH3_UART2                                    0x0000C000U
/*

        Field:           CH4
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 4 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH4_W                                        4U
#define HOST_DMA_CHCTL0_CH4_M                                        0x000F0000U
#define HOST_DMA_CHCTL0_CH4_S                                        16U
#define HOST_DMA_CHCTL0_CH4_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH4_UART1                                    0x00010000U
#define HOST_DMA_CHCTL0_CH4_SPIO                                     0x00020000U
#define HOST_DMA_CHCTL0_CH4_SPI1                                     0x00030000U
#define HOST_DMA_CHCTL0_CH4_I2C0                                     0x00040000U
#define HOST_DMA_CHCTL0_CH4_I2C1                                     0x00050000U
#define HOST_DMA_CHCTL0_CH4_SDMMC                                    0x00060000U
#define HOST_DMA_CHCTL0_CH4_SDIO                                     0x00070000U
#define HOST_DMA_CHCTL0_CH4_MCAN                                     0x00080000U
#define HOST_DMA_CHCTL0_CH4_ADC                                      0x00090000U
#define HOST_DMA_CHCTL0_CH4_PDM                                      0x000A0000U
#define HOST_DMA_CHCTL0_CH4_HIF                                      0x000B0000U
#define HOST_DMA_CHCTL0_CH4_UART2                                    0x000C0000U
/*

        Field:           CH5
        From..to bits:   20...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 5 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH5_W                                        4U
#define HOST_DMA_CHCTL0_CH5_M                                        0x00F00000U
#define HOST_DMA_CHCTL0_CH5_S                                        20U
#define HOST_DMA_CHCTL0_CH5_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH5_UART1                                    0x00100000U
#define HOST_DMA_CHCTL0_CH5_SPIO                                     0x00200000U
#define HOST_DMA_CHCTL0_CH5_SPI1                                     0x00300000U
#define HOST_DMA_CHCTL0_CH5_I2C0                                     0x00400000U
#define HOST_DMA_CHCTL0_CH5_I2C1                                     0x00500000U
#define HOST_DMA_CHCTL0_CH5_SDMMC                                    0x00600000U
#define HOST_DMA_CHCTL0_CH5_SDIO                                     0x00700000U
#define HOST_DMA_CHCTL0_CH5_MCAN                                     0x00800000U
#define HOST_DMA_CHCTL0_CH5_ADC                                      0x00900000U
#define HOST_DMA_CHCTL0_CH5_PDM                                      0x00A00000U
#define HOST_DMA_CHCTL0_CH5_HIF                                      0x00B00000U
#define HOST_DMA_CHCTL0_CH5_UART2                                    0x00C00000U
/*

        Field:           CH6
        From..to bits:   24...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 6 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH6_W                                        4U
#define HOST_DMA_CHCTL0_CH6_M                                        0x0F000000U
#define HOST_DMA_CHCTL0_CH6_S                                        24U
#define HOST_DMA_CHCTL0_CH6_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH6_UART1                                    0x01000000U
#define HOST_DMA_CHCTL0_CH6_SPIO                                     0x02000000U
#define HOST_DMA_CHCTL0_CH6_SPI1                                     0x03000000U
#define HOST_DMA_CHCTL0_CH6_I2C0                                     0x04000000U
#define HOST_DMA_CHCTL0_CH6_I2C1                                     0x05000000U
#define HOST_DMA_CHCTL0_CH6_SDMMC                                    0x06000000U
#define HOST_DMA_CHCTL0_CH6_SDIO                                     0x07000000U
#define HOST_DMA_CHCTL0_CH6_MCAN                                     0x08000000U
#define HOST_DMA_CHCTL0_CH6_ADC                                      0x09000000U
#define HOST_DMA_CHCTL0_CH6_PDM                                      0x0A000000U
#define HOST_DMA_CHCTL0_CH6_HIF                                      0x0B000000U
#define HOST_DMA_CHCTL0_CH6_UART2                                    0x0C000000U
/*

        Field:           CH7
        From..to bits:   28...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 7 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL0_CH7_W                                        4U
#define HOST_DMA_CHCTL0_CH7_M                                        0xF0000000U
#define HOST_DMA_CHCTL0_CH7_S                                        28U
#define HOST_DMA_CHCTL0_CH7_UART0                                    0x00000000U
#define HOST_DMA_CHCTL0_CH7_UART1                                    0x10000000U
#define HOST_DMA_CHCTL0_CH7_SPIO                                     0x20000000U
#define HOST_DMA_CHCTL0_CH7_SPI1                                     0x30000000U
#define HOST_DMA_CHCTL0_CH7_I2C0                                     0x40000000U
#define HOST_DMA_CHCTL0_CH7_I2C1                                     0x50000000U
#define HOST_DMA_CHCTL0_CH7_SDMMC                                    0x60000000U
#define HOST_DMA_CHCTL0_CH7_SDIO                                     0x70000000U
#define HOST_DMA_CHCTL0_CH7_MCAN                                     0x80000000U
#define HOST_DMA_CHCTL0_CH7_ADC                                      0x90000000U
#define HOST_DMA_CHCTL0_CH7_PDM                                      0xA0000000U
#define HOST_DMA_CHCTL0_CH7_HIF                                      0xB0000000U
#define HOST_DMA_CHCTL0_CH7_UART2                                    0xC0000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CHCTL1
    Offset name:         HOST_DMA_O_CHCTL1
    Relative address:    0x4
    Description:         Host DMA Channel Controlled by Defined Peripheral.

                        The value of each fields concats with [HOST_DMA:JOBCTLCHx.SRCDSTCFG] (when x is channel num)
                        if [CHCTL1.CHx] = 4 and [JOBCTLCHx.SRCDSTCFG] = 1 (value = 0100_1 = 9)
                        then flow control signals of channel x are connected to periph number 9 flow control signals

                        Note: [CHCTL0.CHx] = 0xF is forbidden. This configuration should be only used for Dynamic Switch
    Default Value:       0x00000000

        Field:           CH8
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 8 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH8_W                                        4U
#define HOST_DMA_CHCTL1_CH8_M                                        0x0000000FU
#define HOST_DMA_CHCTL1_CH8_S                                        0U
#define HOST_DMA_CHCTL1_CH8_UART0                                    0x00000000U
#define HOST_DMA_CHCTL1_CH8_UART1                                    0x00000001U
#define HOST_DMA_CHCTL1_CH8_SPIO                                     0x00000002U
#define HOST_DMA_CHCTL1_CH8_SPI1                                     0x00000003U
#define HOST_DMA_CHCTL1_CH8_I2C0                                     0x00000004U
#define HOST_DMA_CHCTL1_CH8_I2C1                                     0x00000005U
#define HOST_DMA_CHCTL1_CH8_SDMMC                                    0x00000006U
#define HOST_DMA_CHCTL1_CH8_SDIO                                     0x00000007U
#define HOST_DMA_CHCTL1_CH8_MCAN                                     0x00000008U
#define HOST_DMA_CHCTL1_CH8_ADC                                      0x00000009U
#define HOST_DMA_CHCTL1_CH8_PDM                                      0x0000000AU
#define HOST_DMA_CHCTL1_CH8_HIF                                      0x0000000BU
#define HOST_DMA_CHCTL1_CH8_UART2                                    0x0000000CU
/*

        Field:           CH9
        From..to bits:   4...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 9 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH9_W                                        4U
#define HOST_DMA_CHCTL1_CH9_M                                        0x000000F0U
#define HOST_DMA_CHCTL1_CH9_S                                        4U
#define HOST_DMA_CHCTL1_CH9_UART0                                    0x00000000U
#define HOST_DMA_CHCTL1_CH9_UART1                                    0x00000010U
#define HOST_DMA_CHCTL1_CH9_SPIO                                     0x00000020U
#define HOST_DMA_CHCTL1_CH9_SPI1                                     0x00000030U
#define HOST_DMA_CHCTL1_CH9_I2C0                                     0x00000040U
#define HOST_DMA_CHCTL1_CH9_I2C1                                     0x00000050U
#define HOST_DMA_CHCTL1_CH9_SDMMC                                    0x00000060U
#define HOST_DMA_CHCTL1_CH9_SDIO                                     0x00000070U
#define HOST_DMA_CHCTL1_CH9_MCAN                                     0x00000080U
#define HOST_DMA_CHCTL1_CH9_ADC                                      0x00000090U
#define HOST_DMA_CHCTL1_CH9_PDM                                      0x000000A0U
#define HOST_DMA_CHCTL1_CH9_HIF                                      0x000000B0U
#define HOST_DMA_CHCTL1_CH9_UART2                                    0x000000C0U
/*

        Field:           CH10
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 10 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH10_W                                       4U
#define HOST_DMA_CHCTL1_CH10_M                                       0x00000F00U
#define HOST_DMA_CHCTL1_CH10_S                                       8U
#define HOST_DMA_CHCTL1_CH10_UART0                                   0x00000000U
#define HOST_DMA_CHCTL1_CH10_UART1                                   0x00000100U
#define HOST_DMA_CHCTL1_CH10_SPIO                                    0x00000200U
#define HOST_DMA_CHCTL1_CH10_SPI1                                    0x00000300U
#define HOST_DMA_CHCTL1_CH10_I2C0                                    0x00000400U
#define HOST_DMA_CHCTL1_CH10_I2C1                                    0x00000500U
#define HOST_DMA_CHCTL1_CH10_SDMMC                                   0x00000600U
#define HOST_DMA_CHCTL1_CH10_SDIO                                    0x00000700U
#define HOST_DMA_CHCTL1_CH10_MCAN                                    0x00000800U
#define HOST_DMA_CHCTL1_CH10_ADC                                     0x00000900U
#define HOST_DMA_CHCTL1_CH10_PDM                                     0x00000A00U
#define HOST_DMA_CHCTL1_CH10_HIF                                     0x00000B00U
#define HOST_DMA_CHCTL1_CH10_UART2                                   0x00000C00U
/*

        Field:           CH11
        From..to bits:   12...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 11 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH11_W                                       4U
#define HOST_DMA_CHCTL1_CH11_M                                       0x0000F000U
#define HOST_DMA_CHCTL1_CH11_S                                       12U
#define HOST_DMA_CHCTL1_CH11_UART0                                   0x00000000U
#define HOST_DMA_CHCTL1_CH11_UART1                                   0x00001000U
#define HOST_DMA_CHCTL1_CH11_SPIO                                    0x00002000U
#define HOST_DMA_CHCTL1_CH11_SPI1                                    0x00003000U
#define HOST_DMA_CHCTL1_CH11_I2C0                                    0x00004000U
#define HOST_DMA_CHCTL1_CH11_I2C1                                    0x00005000U
#define HOST_DMA_CHCTL1_CH11_SDMMC                                   0x00006000U
#define HOST_DMA_CHCTL1_CH11_SDIO                                    0x00007000U
#define HOST_DMA_CHCTL1_CH11_MCAN                                    0x00008000U
#define HOST_DMA_CHCTL1_CH11_ADC                                     0x00009000U
#define HOST_DMA_CHCTL1_CH11_PDM                                     0x0000A000U
#define HOST_DMA_CHCTL1_CH11_HIF                                     0x0000B000U
#define HOST_DMA_CHCTL1_CH11_UART2                                   0x0000C000U
/*

        Field:           CH12
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 12 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH12_W                                       4U
#define HOST_DMA_CHCTL1_CH12_M                                       0x000F0000U
#define HOST_DMA_CHCTL1_CH12_S                                       16U
#define HOST_DMA_CHCTL1_CH12_UART0                                   0x00000000U
#define HOST_DMA_CHCTL1_CH12_UART1                                   0x00010000U
#define HOST_DMA_CHCTL1_CH12_SPIO                                    0x00020000U
#define HOST_DMA_CHCTL1_CH12_SPI1                                    0x00030000U
#define HOST_DMA_CHCTL1_CH12_I2C0                                    0x00040000U
#define HOST_DMA_CHCTL1_CH12_I2C1                                    0x00050000U
#define HOST_DMA_CHCTL1_CH12_SDMMC                                   0x00060000U
#define HOST_DMA_CHCTL1_CH12_SDIO                                    0x00070000U
#define HOST_DMA_CHCTL1_CH12_MCAN                                    0x00080000U
#define HOST_DMA_CHCTL1_CH12_ADC                                     0x00090000U
#define HOST_DMA_CHCTL1_CH12_PDM                                     0x000A0000U
#define HOST_DMA_CHCTL1_CH12_HIF                                     0x000B0000U
#define HOST_DMA_CHCTL1_CH12_UART2                                   0x000C0000U
/*

        Field:           CH13
        From..to bits:   20...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Channel 13 Control.
                         Flow control signals:
                         25 UART2       TX
                         24 UART2       RX
                         23 HIF         TX
                         22 HIF         RX
                         21 Not Valid - PDM has only read
                         20 PDM
                         19 Not Valid - ADC has only read
                         18 ADC
                         17 MCAN        TX
                         16 MCAN        RX
                         15 SDIO        TX
                         14 SDIO        RX
                         13 SDMMC       TX
                         12 SDMMC       RX
                         11 I2C1        TX
                         10 I2C1        RX
                          9 I2C0        TX
                          8 I2C0        RX
                          7 SPI1        TX
                          6 SPI1        RX
                          5 SPI0        TX
                          4 SPI0        RX
                          3 UART1       TX
                          2 UART1       RX
                          1 UART0       TX
                          0 UART0       RX


        ENUMs:
            UART0:                       UART0 peripheral
            UART1:                       UART1 peripheral
            SPIO:                        SPI0 peripheral
            SPI1:                        SPI1 peripheral
            I2C0:                        I2C0 peripheral
            I2C1:                        I2C1 peripheral
            SDMMC:                       SDMMC peripheral
            SDIO:                        SDIO peripheral
            MCAN:                        MCAN peripheral
            ADC:                         ADC peripheral
            PDM:                         PDM peripheral
            HIF:                         HIF peripheral
            UART2:                       UART2 peripheral
*/
#define HOST_DMA_CHCTL1_CH13_W                                       4U
#define HOST_DMA_CHCTL1_CH13_M                                       0x00F00000U
#define HOST_DMA_CHCTL1_CH13_S                                       20U
#define HOST_DMA_CHCTL1_CH13_UART0                                   0x00000000U
#define HOST_DMA_CHCTL1_CH13_UART1                                   0x00100000U
#define HOST_DMA_CHCTL1_CH13_SPIO                                    0x00200000U
#define HOST_DMA_CHCTL1_CH13_SPI1                                    0x00300000U
#define HOST_DMA_CHCTL1_CH13_I2C0                                    0x00400000U
#define HOST_DMA_CHCTL1_CH13_I2C1                                    0x00500000U
#define HOST_DMA_CHCTL1_CH13_SDMMC                                   0x00600000U
#define HOST_DMA_CHCTL1_CH13_SDIO                                    0x00700000U
#define HOST_DMA_CHCTL1_CH13_MCAN                                    0x00800000U
#define HOST_DMA_CHCTL1_CH13_ADC                                     0x00900000U
#define HOST_DMA_CHCTL1_CH13_PDM                                     0x00A00000U
#define HOST_DMA_CHCTL1_CH13_HIF                                     0x00B00000U
#define HOST_DMA_CHCTL1_CH13_UART2                                   0x00C00000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIOCFG
    Offset name:         HOST_DMA_O_PRIOCFG
    Relative address:    0x18
    Description:         Priority Channel Configuration.
    Default Value:       0x1F0F0F00

        Field:           PRIOEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable priority channel.
                         Enable one channel to be prioritize - no round rubin would be done

*/
#define HOST_DMA_PRIOCFG_PRIOEN                                      0x00000001U
#define HOST_DMA_PRIOCFG_PRIOEN_M                                    0x00000001U
#define HOST_DMA_PRIOCFG_PRIOEN_S                                    0U
/*

        Field:           CH1ST
        From..to bits:   8...11
        DefaultValue:    0xF
        Access type:     read-write
        Description:     First priority channel.
                         channel with highest prioriry

*/
#define HOST_DMA_PRIOCFG_CH1ST_W                                     4U
#define HOST_DMA_PRIOCFG_CH1ST_M                                     0x00000F00U
#define HOST_DMA_PRIOCFG_CH1ST_S                                     8U
/*

        Field:           CH2ND
        From..to bits:   16...19
        DefaultValue:    0xF
        Access type:     read-write
        Description:     Second priority channel.
                         channel with second highest prioriry

*/
#define HOST_DMA_PRIOCFG_CH2ND_W                                     4U
#define HOST_DMA_PRIOCFG_CH2ND_M                                     0x000F0000U
#define HOST_DMA_PRIOCFG_CH2ND_S                                     16U
/*

        Field:           MAXBLOCKS
        From..to bits:   24...28
        DefaultValue:    0x1F
        Access type:     read-write
        Description:     Maximum consecutive priority blocks.
                         Maximum consecutive block transactions of "priority channels" . After this number of consecutive blocks one of "roubd robin" channels will win arbitration. 31 means there is no limitation  on number of consecutive priority blocks

*/
#define HOST_DMA_PRIOCFG_MAXBLOCKS_W                                 5U
#define HOST_DMA_PRIOCFG_MAXBLOCKS_M                                 0x1F000000U
#define HOST_DMA_PRIOCFG_MAXBLOCKS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0STA
    Offset name:         HOST_DMA_O_CH0STA
    Relative address:    0x1000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH0STA_HWEVENT_W                                    3U
#define HOST_DMA_CH0STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH0STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:

                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH0STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH0STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH0STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH0STA_RUN                                          0x00010000U
#define HOST_DMA_CH0STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH0STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TIPTR
    Offset name:         HOST_DMA_O_CH0TIPTR
    Relative address:    0x1004
    Description:         Input Pointer Channel Transaction.
                        32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction input pointer.
                         32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH0TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH0TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH0TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0OPTR
    Offset name:         HOST_DMA_O_CH0OPTR
    Relative address:    0x1008
    Description:         Output Pointer Channel Transaction.
                        32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction output pointer.
                         32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH0OPTR_OPTR_W                                      32U
#define HOST_DMA_CH0OPTR_OPTR_M                                      0xFFFFFFFFU
#define HOST_DMA_CH0OPTR_OPTR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TCTL
    Offset name:         HOST_DMA_O_CH0TCTL
    Relative address:    0x100C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction bytes number.
                         Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH0TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH0TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH0TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Use burst request.
                         In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH0TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH0TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH0TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH0TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH0TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH0TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH0TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH0TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH0TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TCTL2
    Offset name:         HOST_DMA_O_CH0TCTL2
    Relative address:    0x1010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

                         Type:Write-Clear.

*/
#define HOST_DMA_CH0TCTL2_CMD_W                                      3U
#define HOST_DMA_CH0TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH0TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TSTA
    Offset name:         HOST_DMA_O_CH0TSTA
    Relative address:    0x1014
    Description:         Transaction Status.
                        Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH0TSTA_STA                                         0x00000001U
#define HOST_DMA_CH0TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH0TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Word offset.
                         Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH0TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH0TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH0TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Remain bytes number.
                         Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH0TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH0TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH0TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0JCTL
    Offset name:         HOST_DMA_O_CH0JCTL
    Relative address:    0x101C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH0JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH0JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH0JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH0JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH0JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH0JCTL_BLKSIZE_S                                   16U
/*

        Field:           BLKMODESRC
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     source pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH0JCTL_BLKMODESRC                                  0x01000000U
#define HOST_DMA_CH0JCTL_BLKMODESRC_M                                0x01000000U
#define HOST_DMA_CH0JCTL_BLKMODESRC_S                                24U
/*

        Field:           BLKMODEDST
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH0JCTL_BLKMODEDST                                  0x02000000U
#define HOST_DMA_CH0JCTL_BLKMODEDST_M                                0x02000000U
#define HOST_DMA_CH0JCTL_BLKMODEDST_S                                25U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH0JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH0JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH0JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH0JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH0JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH0JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH0JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH0JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH0JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH0JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH0JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH0JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH0JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH0JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH0JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1STA
    Offset name:         HOST_DMA_O_CH1STA
    Relative address:    0x2000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH1STA_HWEVENT_W                                    3U
#define HOST_DMA_CH1STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH1STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH1STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH1STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH1STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH1STA_RUN                                          0x00010000U
#define HOST_DMA_CH1STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH1STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TIPTR
    Offset name:         HOST_DMA_O_CH1TIPTR
    Relative address:    0x2004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH1TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH1TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH1TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TOPTR
    Offset name:         HOST_DMA_O_CH1TOPTR
    Relative address:    0x2008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH1TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH1TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH1TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TCTL
    Offset name:         HOST_DMA_O_CH1TCTL
    Relative address:    0x200C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH1TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH1TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH1TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH1TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH1TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH1TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH1TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH1TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH1TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH1TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH1TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH1TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TCTRL2
    Offset name:         HOST_DMA_O_CH1TCTRL2
    Relative address:    0x2010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH1TCTRL2_CMD_W                                     3U
#define HOST_DMA_CH1TCTRL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH1TCTRL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TSTA
    Offset name:         HOST_DMA_O_CH1TSTA
    Relative address:    0x2014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH1TSTA_STA                                         0x00000001U
#define HOST_DMA_CH1TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH1TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH1TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH1TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH1TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH1TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH1TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH1TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1JCTL
    Offset name:         HOST_DMA_O_CH1JCTL
    Relative address:    0x201C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH1JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH1JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH1JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH1JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH1JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH1JCTL_BLKSIZE_S                                   16U
/*

        Field:           BLKMODESRC
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     source pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH1JCTL_BLKMODESRC                                  0x01000000U
#define HOST_DMA_CH1JCTL_BLKMODESRC_M                                0x01000000U
#define HOST_DMA_CH1JCTL_BLKMODESRC_S                                24U
/*

        Field:           BLKMODEDST
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH1JCTL_BLKMODEDST                                  0x02000000U
#define HOST_DMA_CH1JCTL_BLKMODEDST_M                                0x02000000U
#define HOST_DMA_CH1JCTL_BLKMODEDST_S                                25U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH1JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH1JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH1JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH1JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH1JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH1JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH1JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH1JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH1JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH1JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH1JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH1JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH1JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH1JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH1JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2STA
    Offset name:         HOST_DMA_O_CH2STA
    Relative address:    0x3000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH2STA_HWEVENT_W                                    3U
#define HOST_DMA_CH2STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH2STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH2STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH2STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH2STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH2STA_RUN                                          0x00010000U
#define HOST_DMA_CH2STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH2STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TIPTR
    Offset name:         HOST_DMA_O_CH2TIPTR
    Relative address:    0x3004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH2TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH2TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH2TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TOPTR
    Offset name:         HOST_DMA_O_CH2TOPTR
    Relative address:    0x3008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH2TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH2TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH2TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TCTL
    Offset name:         HOST_DMA_O_CH2TCTL
    Relative address:    0x300C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH2TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH2TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH2TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH2TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH2TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH2TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH2TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH2TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH2TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH2TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH2TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH2TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TCTL2
    Offset name:         HOST_DMA_O_CH2TCTL2
    Relative address:    0x3010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH2TCTL2_CMD_W                                      3U
#define HOST_DMA_CH2TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH2TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TSTA
    Offset name:         HOST_DMA_O_CH2TSTA
    Relative address:    0x3014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH2TSTA_STA                                         0x00000001U
#define HOST_DMA_CH2TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH2TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH2TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH2TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH2TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH2TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH2TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH2TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2JCTL
    Offset name:         HOST_DMA_O_CH2JCTL
    Relative address:    0x301C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH2JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH2JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH2JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH2JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH2JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH2JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH2JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH2JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH2JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH2JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH2JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH2JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH2JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH2JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH2JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH2JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH2JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH2JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH2JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH2JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH2JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3STA
    Offset name:         HOST_DMA_O_CH3STA
    Relative address:    0x4000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH3STA_HWEVENT_W                                    3U
#define HOST_DMA_CH3STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH3STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH3STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH3STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH3STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH3STA_RUN                                          0x00010000U
#define HOST_DMA_CH3STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH3STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TIPTR
    Offset name:         HOST_DMA_O_CH3TIPTR
    Relative address:    0x4004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH3TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH3TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH3TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TOPTR
    Offset name:         HOST_DMA_O_CH3TOPTR
    Relative address:    0x4008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH3TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH3TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH3TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TCTL
    Offset name:         HOST_DMA_O_CH3TCTL
    Relative address:    0x400C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH3TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH3TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH3TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH3TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH3TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH3TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH3TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH3TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH3TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH3TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH3TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH3TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TCTL2
    Offset name:         HOST_DMA_O_CH3TCTL2
    Relative address:    0x4010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH3TCTL2_CMD_W                                      3U
#define HOST_DMA_CH3TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH3TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TSTA
    Offset name:         HOST_DMA_O_CH3TSTA
    Relative address:    0x4014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH3TSTA_STA                                         0x00000001U
#define HOST_DMA_CH3TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH3TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH3TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH3TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH3TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH3TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH3TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH3TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3JCTL
    Offset name:         HOST_DMA_O_CH3JCTL
    Relative address:    0x401C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH3JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH3JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH3JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH3JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH3JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH3JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH3JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH3JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH3JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH3JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH3JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH3JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH3JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH3JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH3JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH3JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH3JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH3JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH3JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH3JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH3JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4STA
    Offset name:         HOST_DMA_O_CH4STA
    Relative address:    0x5000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH4STA_HWEVENT_W                                    3U
#define HOST_DMA_CH4STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH4STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH4STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH4STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH4STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH4STA_RUN                                          0x00010000U
#define HOST_DMA_CH4STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH4STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TIPTR
    Offset name:         HOST_DMA_O_CH4TIPTR
    Relative address:    0x5004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           INPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH4TIPTR_INPTR_W                                    32U
#define HOST_DMA_CH4TIPTR_INPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH4TIPTR_INPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TOPTR
    Offset name:         HOST_DMA_O_CH4TOPTR
    Relative address:    0x5008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH4TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH4TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH4TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TCTL
    Offset name:         HOST_DMA_O_CH4TCTL
    Relative address:    0x500C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH4TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH4TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH4TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH4TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH4TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH4TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH4TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH4TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH4TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH4TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH4TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH4TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TCTL2
    Offset name:         HOST_DMA_O_CH4TCTL2
    Relative address:    0x5010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH4TCTL2_CMD_W                                      3U
#define HOST_DMA_CH4TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH4TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TSTA
    Offset name:         HOST_DMA_O_CH4TSTA
    Relative address:    0x5014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH4TSTA_STA                                         0x00000001U
#define HOST_DMA_CH4TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH4TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH4TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH4TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH4TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH4TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH4TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH4TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4JCTL
    Offset name:         HOST_DMA_O_CH4JCTL
    Relative address:    0x501C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH4JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH4JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH4JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH4JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH4JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH4JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH4JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH4JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH4JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH4JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH4JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH4JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH4JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH4JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH4JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH4JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH4JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH4JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH4JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH4JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH4JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5STA
    Offset name:         HOST_DMA_O_CH5STA
    Relative address:    0x6000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH5STA_HWEVENT_W                                    3U
#define HOST_DMA_CH5STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH5STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH5STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH5STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH5STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH5STA_RUN                                          0x00010000U
#define HOST_DMA_CH5STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH5STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TIPTR
    Offset name:         HOST_DMA_O_CH5TIPTR
    Relative address:    0x6004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH5TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH5TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH5TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TOPTR
    Offset name:         HOST_DMA_O_CH5TOPTR
    Relative address:    0x6008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH5TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH5TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH5TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TCTL
    Offset name:         HOST_DMA_O_CH5TCTL
    Relative address:    0x600C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH5TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH5TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH5TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH5TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH5TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH5TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH5TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH5TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH5TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH5TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH5TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH5TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TCTL2
    Offset name:         HOST_DMA_O_CH5TCTL2
    Relative address:    0x6010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH5TCTL2_CMD_W                                      3U
#define HOST_DMA_CH5TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH5TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TSTA
    Offset name:         HOST_DMA_O_CH5TSTA
    Relative address:    0x6014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH5TSTA_STA                                         0x00000001U
#define HOST_DMA_CH5TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH5TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH5TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH5TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH5TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH5TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH5TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH5TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5JCTL
    Offset name:         HOST_DMA_O_CH5JCTL
    Relative address:    0x601C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH5JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH5JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH5JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH5JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH5JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH5JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH5JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH5JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH5JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH5JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH5JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH5JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH5JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH5JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH5JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH5JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH5JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH5JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH5JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH5JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH5JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6STA
    Offset name:         HOST_DMA_O_CH6STA
    Relative address:    0x7000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH6STA_HWEVENT_W                                    3U
#define HOST_DMA_CH6STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH6STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH6STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH6STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH6STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH6STA_RUN                                          0x00010000U
#define HOST_DMA_CH6STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH6STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TIPTR
    Offset name:         HOST_DMA_O_CH6TIPTR
    Relative address:    0x7004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH6TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH6TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH6TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TOPTR
    Offset name:         HOST_DMA_O_CH6TOPTR
    Relative address:    0x7008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH6TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH6TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH6TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TCTL
    Offset name:         HOST_DMA_O_CH6TCTL
    Relative address:    0x700C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH6TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH6TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH6TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH6TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH6TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH6TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH6TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH6TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH6TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH6TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH6TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH6TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TCTL2
    Offset name:         HOST_DMA_O_CH6TCTL2
    Relative address:    0x7010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH6TCTL2_CMD_W                                      3U
#define HOST_DMA_CH6TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH6TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TSTA
    Offset name:         HOST_DMA_O_CH6TSTA
    Relative address:    0x7014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH6TSTA_STA                                         0x00000001U
#define HOST_DMA_CH6TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH6TSTA_STA_S                                       0U
/*

        Field:           WORDOFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH6TSTA_WORDOFFSET_W                                8U
#define HOST_DMA_CH6TSTA_WORDOFFSET_M                                0x0000FF00U
#define HOST_DMA_CH6TSTA_WORDOFFSET_S                                8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH6TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH6TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH6TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6JCTL
    Offset name:         HOST_DMA_O_CH6JCTL
    Relative address:    0x701C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH6JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH6JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH6JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH6JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH6JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH6JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH6JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH6JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH6JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH6JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH6JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH6JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH6JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH6JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH6JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH6JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH6JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH6JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH6JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH6JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH6JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7STA
    Offset name:         HOST_DMA_O_CH7STA
    Relative address:    0x8000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH7STA_HWEVENT_W                                    3U
#define HOST_DMA_CH7STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH7STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH7STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH7STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH7STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH7STA_RUN                                          0x00010000U
#define HOST_DMA_CH7STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH7STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TIPTR
    Offset name:         HOST_DMA_O_CH7TIPTR
    Relative address:    0x8004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH7TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH7TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH7TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TOPTR
    Offset name:         HOST_DMA_O_CH7TOPTR
    Relative address:    0x8008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH7TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH7TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH7TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TCTL
    Offset name:         HOST_DMA_O_CH7TCTL
    Relative address:    0x800C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH7TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH7TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH7TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH7TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH7TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH7TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH7TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH7TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH7TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH7TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH7TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH7TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TCTL2
    Offset name:         HOST_DMA_O_CH7TCTL2
    Relative address:    0x8010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH7TCTL2_CMD_W                                      3U
#define HOST_DMA_CH7TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH7TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TSTA
    Offset name:         HOST_DMA_O_CH7TSTA
    Relative address:    0x8014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH7TSTA_STA                                         0x00000001U
#define HOST_DMA_CH7TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH7TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH7TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH7TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH7TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH7TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH7TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH7TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7JCTL
    Offset name:         HOST_DMA_O_CH7JCTL
    Relative address:    0x801C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH7JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH7JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH7JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH7JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH7JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH7JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH7JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH7JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH7JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH7JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH7JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH7JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH7JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH7JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH7JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH7JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH7JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH7JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH7JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH7JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH7JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8STA
    Offset name:         HOST_DMA_O_CH8STA
    Relative address:    0x9000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH8STA_HWEVENT_W                                    3U
#define HOST_DMA_CH8STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH8STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH8STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH8STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH8STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH8STA_RUN                                          0x00010000U
#define HOST_DMA_CH8STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH8STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TIPTR
    Offset name:         HOST_DMA_O_CH8TIPTR
    Relative address:    0x9004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH8TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH8TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH8TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TOPTR
    Offset name:         HOST_DMA_O_CH8TOPTR
    Relative address:    0x9008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH8TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH8TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH8TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TCTL
    Offset name:         HOST_DMA_O_CH8TCTL
    Relative address:    0x900C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH8TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH8TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH8TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH8TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH8TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH8TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH8TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH8TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH8TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH8TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH8TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH8TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TCTL2
    Offset name:         HOST_DMA_O_CH8TCTL2
    Relative address:    0x9010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH8TCTL2_CMD_W                                      3U
#define HOST_DMA_CH8TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH8TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TSTA
    Offset name:         HOST_DMA_O_CH8TSTA
    Relative address:    0x9014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH8TSTA_STA                                         0x00000001U
#define HOST_DMA_CH8TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH8TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH8TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH8TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH8TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH8TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH8TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH8TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8JCTL
    Offset name:         HOST_DMA_O_CH8JCTL
    Relative address:    0x901C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH8JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH8JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH8JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH8JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH8JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH8JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH8JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH8JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH8JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH8JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH8JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH8JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH8JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH8JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH8JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH8JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH8JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH8JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH8JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH8JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH8JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9STA
    Offset name:         HOST_DMA_O_CH9STA
    Relative address:    0xA000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH9STA_HWEVENT_W                                    3U
#define HOST_DMA_CH9STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH9STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH9STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH9STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH9STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH9STA_RUN                                          0x00010000U
#define HOST_DMA_CH9STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH9STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TIPTR
    Offset name:         HOST_DMA_O_CH9TIPTR
    Relative address:    0xA004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH9TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH9TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH9TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TOPTR
    Offset name:         HOST_DMA_O_CH9TOPTR
    Relative address:    0xA008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH9TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH9TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH9TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TCTL
    Offset name:         HOST_DMA_O_CH9TCTL
    Relative address:    0xA00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH9TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH9TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH9TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH9TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH9TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH9TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH9TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH9TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH9TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH9TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH9TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH9TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TCTL2
    Offset name:         HOST_DMA_O_CH9TCTL2
    Relative address:    0xA010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH9TCTL2_CMD_W                                      3U
#define HOST_DMA_CH9TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH9TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TSTA
    Offset name:         HOST_DMA_O_CH9TSTA
    Relative address:    0xA014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH9TSTA_STA                                         0x00000001U
#define HOST_DMA_CH9TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH9TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH9TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH9TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH9TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH9TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH9TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH9TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9JCTL
    Offset name:         HOST_DMA_O_CH9JCTL
    Relative address:    0xA01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH9JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH9JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH9JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH9JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH9JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH9JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH9JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH9JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH9JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH9JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH9JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH9JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH9JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH9JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH9JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH9JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH9JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH9JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH9JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH9JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH9JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10STA
    Offset name:         HOST_DMA_O_CH10STA
    Relative address:    0xB000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH10STA_HWEVENT_W                                   3U
#define HOST_DMA_CH10STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH10STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH10STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH10STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH10STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH10STA_RUN                                         0x00010000U
#define HOST_DMA_CH10STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH10STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TIPTR
    Offset name:         HOST_DMA_O_CH10TIPTR
    Relative address:    0xB004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH10TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH10TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH10TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TOPTR
    Offset name:         HOST_DMA_O_CH10TOPTR
    Relative address:    0xB008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH10TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH10TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH10TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TCTL
    Offset name:         HOST_DMA_O_CH10TCTL
    Relative address:    0xB00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH10TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH10TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH10TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH10TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH10TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH10TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH10TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH10TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH10TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH10TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH10TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH10TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TCTL2
    Offset name:         HOST_DMA_O_CH10TCTL2
    Relative address:    0xB010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH10TCTL2_CMD_W                                     3U
#define HOST_DMA_CH10TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH10TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TSTA
    Offset name:         HOST_DMA_O_CH10TSTA
    Relative address:    0xB014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH10TSTA_STA                                        0x00000001U
#define HOST_DMA_CH10TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH10TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH10TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH10TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH10TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH10TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH10TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH10TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10JCTL
    Offset name:         HOST_DMA_O_CH10JCTL
    Relative address:    0xB01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH10JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH10JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH10JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH10JCTL_BLKSIZE_W                                  8U
#define HOST_DMA_CH10JCTL_BLKSIZE_M                                  0x00FF0000U
#define HOST_DMA_CH10JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH10JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH10JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH10JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH10JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH10JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH10JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH10JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH10JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH10JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH10JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH10JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH10JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH10JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH10JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH10JCTL_ENCLR_S                                    30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11STA
    Offset name:         HOST_DMA_O_CH11STA
    Relative address:    0xC000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH11STA_HWEVENT_W                                   3U
#define HOST_DMA_CH11STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH11STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH11STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH11STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH11STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH11STA_RUN                                         0x00010000U
#define HOST_DMA_CH11STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH11STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TIPTR
    Offset name:         HOST_DMA_O_CH11TIPTR
    Relative address:    0xC004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH11TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH11TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH11TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TOPTR
    Offset name:         HOST_DMA_O_CH11TOPTR
    Relative address:    0xC008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH11TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH11TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH11TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TCTL
    Offset name:         HOST_DMA_O_CH11TCTL
    Relative address:    0xC00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH11TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH11TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH11TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH11TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH11TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH11TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH11TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH11TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH11TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH11TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH11TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH11TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TCTL2
    Offset name:         HOST_DMA_O_CH11TCTL2
    Relative address:    0xC010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH11TCTL2_CMD_W                                     3U
#define HOST_DMA_CH11TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH11TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TSTA
    Offset name:         HOST_DMA_O_CH11TSTA
    Relative address:    0xC014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH11TSTA_STA                                        0x00000001U
#define HOST_DMA_CH11TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH11TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH11TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH11TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH11TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH11TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH11TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH11TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11JCTL
    Offset name:         HOST_DMA_O_CH11JCTL
    Relative address:    0xC01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH11JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH11JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH11JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH11JCTL_BLKSIZE_W                                  6U
#define HOST_DMA_CH11JCTL_BLKSIZE_M                                  0x003F0000U
#define HOST_DMA_CH11JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH11JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH11JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH11JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH11JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH11JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH11JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH11JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH11JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH11JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH11JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH11JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH11JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH11JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH11JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH11JCTL_ENCLR_S                                    30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12STA
    Offset name:         HOST_DMA_O_CH12STA
    Relative address:    0xD000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH12STA_HWEVENT_W                                   3U
#define HOST_DMA_CH12STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH12STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH12STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH12STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH12STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH12STA_RUN                                         0x00010000U
#define HOST_DMA_CH12STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH12STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12TIPTR
    Offset name:         HOST_DMA_O_CH12TIPTR
    Relative address:    0xD004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH12TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH12TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH12TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12TOPTR
    Offset name:         HOST_DMA_O_CH12TOPTR
    Relative address:    0xD008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH12TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH12TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH12TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12TCTL
    Offset name:         HOST_DMA_O_CH12TCTL
    Relative address:    0xD00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH12TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH12TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH12TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH12TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH12TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH12TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH12TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH12TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH12TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH12TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH12TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH12TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12TCTL2
    Offset name:         HOST_DMA_O_CH12TCTL2
    Relative address:    0xD010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH12TCTL2_CMD_W                                     3U
#define HOST_DMA_CH12TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH12TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12TSTA
    Offset name:         HOST_DMA_O_CH12TSTA
    Relative address:    0xD014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH12TSTA_STA                                        0x00000001U
#define HOST_DMA_CH12TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH12TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH12TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH12TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH12TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH12TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH12TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH12TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH12JCTL
    Offset name:         HOST_DMA_O_CH12JCTL
    Relative address:    0xD01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH12JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH12JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH12JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH12JCTL_BLKSIZE_W                                  6U
#define HOST_DMA_CH12JCTL_BLKSIZE_M                                  0x003F0000U
#define HOST_DMA_CH12JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH12JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH12JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH12JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH12JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH12JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH12JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH12JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH12JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH12JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH12JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH12JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH12JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH12JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH12JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH12JCTL_ENCLR_S                                    30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13STA
    Offset name:         HOST_DMA_O_CH13STA
    Relative address:    0xE000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH13STA_HWEVENT_W                                   3U
#define HOST_DMA_CH13STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH13STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH13STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH13STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH13STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH13STA_RUN                                         0x00010000U
#define HOST_DMA_CH13STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH13STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13TIPTR
    Offset name:         HOST_DMA_O_CH13TIPTR
    Relative address:    0xE004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH13TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH13TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH13TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13TOPTR
    Offset name:         HOST_DMA_O_CH13TOPTR
    Relative address:    0xE008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH13TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH13TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH13TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13TCTL
    Offset name:         HOST_DMA_O_CH13TCTL
    Relative address:    0xE00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH13TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH13TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH13TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH13TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH13TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH13TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH13TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH13TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH13TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH13TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH13TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH13TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13TCTL2
    Offset name:         HOST_DMA_O_CH13TCTL2
    Relative address:    0xE010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH13TCTL2_CMD_W                                     3U
#define HOST_DMA_CH13TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH13TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13TSTA
    Offset name:         HOST_DMA_O_CH13TSTA
    Relative address:    0xE014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH13TSTA_STA                                        0x00000001U
#define HOST_DMA_CH13TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH13TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH13TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH13TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH13TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH13TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH13TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH13TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH13JCTL
    Offset name:         HOST_DMA_O_CH13JCTL
    Relative address:    0xE01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH13JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH13JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH13JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH13JCTL_BLKSIZE_W                                  6U
#define HOST_DMA_CH13JCTL_BLKSIZE_M                                  0x003F0000U
#define HOST_DMA_CH13JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH13JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH13JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH13JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH13JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH13JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH13JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH13JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH13JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH13JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH13JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH13JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH13JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH13JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH13JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH13JCTL_ENCLR_S                                    30U

#endif /* __HW_HOST_DMA_H__*/
