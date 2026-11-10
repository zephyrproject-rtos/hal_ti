/******************************************************************************
*  Filename:       hw_i2s.h
*
*  Description:    Defines and prototypes for the I2S peripheral.
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
#ifndef __HW_I2S_H__
#define __HW_I2S_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the I2S component

--------------------------------------------------------------------------------- */

//WCLK Source Selection
#define I2S_O_AIFWCLKSRC                                             0x00000000U

//DMA Buffer Size Configuration
#define I2S_O_AIFDMACFG                                              0x00000004U

//Pin Direction
#define I2S_O_AIFDIRCFG                                              0x00000008U

//Serial Interface Format Configuration
#define I2S_O_AIFFMTCFG                                              0x0000000CU

//Word Selection Bit Mask for Pin 0
#define I2S_O_AIFWMASK0                                              0x00000010U

//Word Selection Bit Mask for Pin 1
#define I2S_O_AIFWMASK1                                              0x00000014U

//DMA Input Buffer Next Pointer
#define I2S_O_AIFINPTNXT                                             0x00000020U

//DMA Input Buffer Current Pointer
#define I2S_O_AIFINPTR                                               0x00000024U

//DMA Output Buffer Next Pointer
#define I2S_O_AIFOPTNXT                                              0x00000028U

//DMA Output Buffer Current Pointer
#define I2S_O_AIFOUTPTR                                              0x0000002CU

//Samplestamp Generator Control Register
#define I2S_O_STMPCTL                                                0x00000034U

//Captured **XOSC** Counter Value, Capture Channel 0
#define I2S_O_STMPXCPT0                                              0x00000038U

//XOSC Period Value
#define I2S_O_STMPXPER                                               0x0000003CU

//Captured **WCLK** Counter Value, Capture Channel 0
#define I2S_O_STMPWCPT0                                              0x00000040U

//**WCLK** Counter Period Value
#define I2S_O_STMPWPER                                               0x00000044U

//WCLK Counter Trigger Value for Input Pins
#define I2S_O_STMPINTRIG                                             0x00000048U

//WCLK Counter Trigger Value for Output Pins
#define I2S_O_STMPOTRIG                                              0x0000004CU

//WCLK Counter Set Operation
#define I2S_O_STMPWSET                                               0x00000050U

//WCLK Counter Add Operation
#define I2S_O_STMPWADD                                               0x00000054U

//XOSC Minimum Period Value
#define I2S_O_STMPXPRMIN                                             0x00000058U

//Current Value of WCNT
#define I2S_O_STMPWCNT                                               0x0000005CU

//Current Value of XCNT
#define I2S_O_STMPXCNT                                               0x00000060U

//Interrupt Mask Register
#define I2S_O_IRQMASK                                                0x00000070U

//Raw Interrupt Status Register
#define I2S_O_IRQFLAGS                                               0x00000074U

//Interrupt Set Register
#define I2S_O_IRQSET                                                 0x00000078U

//Interrupt Clear Register
#define I2S_O_IRQCLR                                                 0x0000007CU

//**MCLK** Division Ratio
#define I2S_O_AIFMCLKDIV                                             0x00000080U

//**BCLK** Division Ratio
#define I2S_O_AIFBCLKDIV                                             0x00000084U

//**WCLK** Division Ratio
#define I2S_O_AIFWCLKDIV                                             0x00000088U

//Internal Audio Clock Control
#define I2S_O_AIFCLKCTL                                              0x0000008CU

//Audio clock source selection and **I2S** enable register
#define I2S_O_CLKCFG                                                 0x00001000U

//ADFS TREF control register
#define I2S_O_ADFSCTRL1                                              0x00001004U

//ADFS general configuration register
#define I2S_O_ADFSCTRL2                                              0x00001008U



/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFWCLKSRC
    Offset name:         I2S_O_AIFWCLKSRC
    Relative address:    0x0
    Description:         WCLK Source Selection
    Default Value:       0x00000000

        Field:           WBCLKSRC
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects **WCLK** / **BCLK** source for **AIF**.

        ENUMs:
            NONE:                        None ('0')
            EXT:                         External **WCLK** generator, from pad
            INT:                         Internal **WCLK** generator, from module PRCM
            RESERVED:                    Not supported. Will give same **WCLK** as 'NONE' ('00')
*/
#define I2S_AIFWCLKSRC_WBCLKSRC_W                                    2U
#define I2S_AIFWCLKSRC_WBCLKSRC_M                                    0x00000003U
#define I2S_AIFWCLKSRC_WBCLKSRC_S                                    0U
#define I2S_AIFWCLKSRC_WBCLKSRC_NONE                                 0x00000000U
#define I2S_AIFWCLKSRC_WBCLKSRC_EXT                                  0x00000001U
#define I2S_AIFWCLKSRC_WBCLKSRC_INT                                  0x00000002U
#define I2S_AIFWCLKSRC_WBCLKSRC_RESERVED                             0x00000003U
/*

        Field:           WCLKINV
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Inverts **WCLK** source (pad or internal) when set.

                         0: Not inverted
                         1: Inverted

*/
#define I2S_AIFWCLKSRC_WCLKINV                                       0x00000004U
#define I2S_AIFWCLKSRC_WCLKINV_M                                     0x00000004U
#define I2S_AIFWCLKSRC_WCLKINV_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFDMACFG
    Offset name:         I2S_O_AIFDMACFG
    Relative address:    0x4
    Description:         DMA Buffer Size Configuration
    Default Value:       0x00000000

        Field:           ENDFRAMIDX
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines the length of the DMA buffer. Writing a non-zero value to this register field enables and initializes AIF. Note that before doing so, all other configuration must have been done, and [AIFINPTRNEXT.*]/[AIFOUTPTRNEXT.*] must have been loaded.

*/
#define I2S_AIFDMACFG_ENDFRAMIDX_W                                   8U
#define I2S_AIFDMACFG_ENDFRAMIDX_M                                   0x000000FFU
#define I2S_AIFDMACFG_ENDFRAMIDX_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFDIRCFG
    Offset name:         I2S_O_AIFDIRCFG
    Relative address:    0x8
    Description:         Pin Direction
    Default Value:       0x00000000

        Field:           AD0
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Configures the **AD0** audio data pin usage:

                         0x3: Reserved

        ENUMs:
            DIS:                         Not in use (disabled)
            IN:                          Input mode
            OUT:                         Output mode
*/
#define I2S_AIFDIRCFG_AD0_W                                          2U
#define I2S_AIFDIRCFG_AD0_M                                          0x00000003U
#define I2S_AIFDIRCFG_AD0_S                                          0U
#define I2S_AIFDIRCFG_AD0_DIS                                        0x00000000U
#define I2S_AIFDIRCFG_AD0_IN                                         0x00000001U
#define I2S_AIFDIRCFG_AD0_OUT                                        0x00000002U
/*

        Field:           AD1
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Configures the **AD1** audio data pin usage:

                         0x3: Reserved

        ENUMs:
            DIS:                         Not in use (disabled)
            IN:                          Input mode
            OUT:                         Output mode
*/
#define I2S_AIFDIRCFG_AD1_W                                          2U
#define I2S_AIFDIRCFG_AD1_M                                          0x00000030U
#define I2S_AIFDIRCFG_AD1_S                                          4U
#define I2S_AIFDIRCFG_AD1_DIS                                        0x00000000U
#define I2S_AIFDIRCFG_AD1_IN                                         0x00000010U
#define I2S_AIFDIRCFG_AD1_OUT                                        0x00000020U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFFMTCFG
    Offset name:         I2S_O_AIFFMTCFG
    Relative address:    0xC
    Description:         Serial Interface Format Configuration
    Default Value:       0x00000010

        Field:           WORDLEN
        From..to bits:   0...4
        DefaultValue:    0x10
        Access type:     read-write
        Description:     Number of bits per word (8-24):
                         In single-phase format, this is the exact number of bits per word.
                         In dual-phase format, this is the maximum number of bits per word.

                         Values below 8 and above 24 give undefined behavior. Data written to memory is always aligned to 16 or 24 bits as defined by [MEM_LEN_24]. Bit widths that differ from this alignment will either be truncated or zero padded.


*/
#define I2S_AIFFMTCFG_WORDLEN_W                                      5U
#define I2S_AIFFMTCFG_WORDLEN_M                                      0x0000001FU
#define I2S_AIFFMTCFG_WORDLEN_S                                      0U
/*

        Field:           DUALPHASE
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Selects dual- or single-phase format.

                         0: Single-phase: **DSP** format
                         1: Dual-phase: **I2S**, **LJF** and **RJF** formats

*/
#define I2S_AIFFMTCFG_DUALPHASE                                      0x00000020U
#define I2S_AIFFMTCFG_DUALPHASE_M                                    0x00000020U
#define I2S_AIFFMTCFG_DUALPHASE_S                                    5U
/*

        Field:           SMPLEDGE
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     On the serial audio interface, data (and wclk) is sampled and clocked out on opposite edges of BCLK.

        ENUMs:
            NEG:                         Data is sampled on the negative edge and clocked out on the positive edge.
            POS:                         Data is sampled on the positive edge and clocked out on the negative edge.
*/
#define I2S_AIFFMTCFG_SMPLEDGE                                       0x00000040U
#define I2S_AIFFMTCFG_SMPLEDGE_M                                     0x00000040U
#define I2S_AIFFMTCFG_SMPLEDGE_S                                     6U
#define I2S_AIFFMTCFG_SMPLEDGE_NEG                                   0x00000000U
#define I2S_AIFFMTCFG_SMPLEDGE_POS                                   0x00000040U
/*

        Field:           LEN32
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The size of each word stored to or loaded from memory:

        ENUMs:
            _16BIT:                      16-bit (one 16 bit access per sample)
            _32BIT:                      32-bit(one 32-bit access per sample)
*/
#define I2S_AIFFMTCFG_LEN32                                          0x00000080U
#define I2S_AIFFMTCFG_LEN32_M                                        0x00000080U
#define I2S_AIFFMTCFG_LEN32_S                                        7U
#define I2S_AIFFMTCFG_LEN32__16BIT                                   0x00000000U
#define I2S_AIFFMTCFG_LEN32__32BIT                                   0x00000080U
/*

        Field:           DATADELAY
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The number of **BCLK** periods between a **WCLK** edge and **MSB** of the first word in a phase:

                         0x00: **LJF** and **DSP** format
                         0x01: **I2S** and **DSP** format
                         0x02: **RJF** format
                         ...
                         0xFF: **RJF** format

                         Note: When 0, **MSB** of the next word will be output in the idle period between **LSB** of the previous word and the start of the next word. Otherwise logical 0 will be output until the data delay has expired.

*/
#define I2S_AIFFMTCFG_DATADELAY_W                                    8U
#define I2S_AIFFMTCFG_DATADELAY_M                                    0x0000FF00U
#define I2S_AIFFMTCFG_DATADELAY_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFWMASK0
    Offset name:         I2S_O_AIFWMASK0
    Relative address:    0x10
    Description:         Word Selection Bit Mask for Pin 0
    Default Value:       0x00000003

        Field:           MASK
        From..to bits:   0...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Bit-mask indicating valid channels in a frame on AD0.

                         In single-phase mode, each bit represents one channel, starting with **LSB** for the first word in the frame. A frame can contain up to 8 channels.  Channels that are not included in the mask will not be sampled and stored in memory, and clocked out as '0'.

                         In dual-phase mode, only the two **LSB**s are considered. For a stereo configuration, set both bits. For a mono configuration, set bit 0 only. In mono mode, only channel 0 will be sampled and stored to memory, and channel 0 will be repeated when clocked out.

                         In mono mode, only channel 0 will be sampled and stored to memory, and channel 0 will be repeated in the second phase when clocked out.

                         If all bits are zero, no input words will be stored to memory, and the output data lines will be constant '0'. This can be utilized when **PWM** debug output is desired without any actively used output pins.


*/
#define I2S_AIFWMASK0_MASK_W                                         8U
#define I2S_AIFWMASK0_MASK_M                                         0x000000FFU
#define I2S_AIFWMASK0_MASK_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFWMASK1
    Offset name:         I2S_O_AIFWMASK1
    Relative address:    0x14
    Description:         Word Selection Bit Mask for Pin 1
    Default Value:       0x00000003

        Field:           MASK
        From..to bits:   0...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Bit-mask indicating valid channels in a frame on AD1.

                         In single-phase mode, each bit represents one channel, starting with **LSB** for the first word in the frame. A frame can contain up to 8 channels.  Channels that are not included in the mask will not be sampled and stored in memory, and clocked out as '0'.

                         In dual-phase mode, only the two **LSB**s are considered. For a stereo configuration, set both bits. For a mono configuration, set bit 0 only. In mono mode, only channel 0 will be sampled and stored to memory, and channel 0 will be repeated when clocked out.

                         In mono mode, only channel 0 will be sampled and stored to memory, and channel 0 will be repeated in the second phase when clocked out.

                         If all bits are zero, no input words will be stored to memory, and the output data lines will be constant '0'. This can be utilized when **PWM** debug output is desired without any actively used output pins.

*/
#define I2S_AIFWMASK1_MASK_W                                         8U
#define I2S_AIFWMASK1_MASK_M                                         0x000000FFU
#define I2S_AIFWMASK1_MASK_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFINPTNXT
    Offset name:         I2S_O_AIFINPTNXT
    Relative address:    0x20
    Description:         DMA Input Buffer Next Pointer
    Default Value:       0x00000000

        Field:           PTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pointer to the first byte in the next **DMA** input buffer.

                         The read value equals the last written value until the currently used **DMA** input buffer is completed, and then becomes null when the last written value is transferred to the **DMA** controller to start on the next buffer. This event is signalized by [IRQFLAGS-AIF_DMA_IN].

                         At startup, the value must be written once before and once after configuring the **DMA** buffer size in [AIFDMACFG.*].

                         The next pointer must be written to this register while the **DMA** function uses the previously written pointer. If not written in time, [IRQFLAGS.PTR_ERR] will be raised and all input pins will be disabled.

*/
#define I2S_AIFINPTNXT_PTR_W                                         32U
#define I2S_AIFINPTNXT_PTR_M                                         0xFFFFFFFFU
#define I2S_AIFINPTNXT_PTR_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFINPTR
    Offset name:         I2S_O_AIFINPTR
    Relative address:    0x24
    Description:         DMA Input Buffer Current Pointer
    Default Value:       0x00000000

        Field:           PTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Value of the **DMA** input buffer pointer currently used by the **DMA** controller. Incremented by 1 (byte) or 2 (word) for each **AHB** access.

*/
#define I2S_AIFINPTR_PTR_W                                           32U
#define I2S_AIFINPTR_PTR_M                                           0xFFFFFFFFU
#define I2S_AIFINPTR_PTR_S                                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFOPTNXT
    Offset name:         I2S_O_AIFOPTNXT
    Relative address:    0x28
    Description:         DMA Output Buffer Next Pointer
    Default Value:       0x00000000

        Field:           PTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Pointer to the first byte in the next **DMA** output buffer.

                         The read value equals the last written value until the currently used **DMA** output buffer is completed, and then becomes null when the last written value is transferred to the **DMA** controller to start on the next buffer. This event is signalized by [IRQFLAGS.AIF_DMA_OUT].

                         At startup, the value must be written once before and once after configuring the **DMA** buffer size in [AIFDMACFG.*]. At this time, the first two samples will be fetched from memory.

                         The next pointer must be written to this register while the **DMA** function uses the previously written pointer. If not written in time, [IRQFLAGS.PTR_ERR] will be raised and all output pins will be disabled.

*/
#define I2S_AIFOPTNXT_PTR_W                                          32U
#define I2S_AIFOPTNXT_PTR_M                                          0xFFFFFFFFU
#define I2S_AIFOPTNXT_PTR_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFOUTPTR
    Offset name:         I2S_O_AIFOUTPTR
    Relative address:    0x2C
    Description:         DMA Output Buffer Current Pointer
    Default Value:       0x00000000

        Field:           PTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Value of the **DMA** output buffer pointer currently used by the **DMA** controller Incremented by 1 (byte) or 2 (word) for each **AHB** access.

*/
#define I2S_AIFOUTPTR_PTR_W                                          32U
#define I2S_AIFOUTPTR_PTR_M                                          0xFFFFFFFFU
#define I2S_AIFOUTPTR_PTR_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPCTL
    Offset name:         I2S_O_STMPCTL
    Relative address:    0x34
    Description:         Samplestamp Generator Control Register
    Default Value:       0x00000000

        Field:           STMPEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables the samplestamp generator. The samplestamp generator must only be enabled after it has been properly configured.
                         When cleared, all samplestamp generator counters and capture values are cleared.


*/
#define I2S_STMPCTL_STMPEN                                           0x00000001U
#define I2S_STMPCTL_STMPEN_M                                         0x00000001U
#define I2S_STMPCTL_STMPEN_S                                         0U
/*

        Field:           INRDY
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Low until the input pins are ready to be started by the samplestamp generator. When started (that is [STMPINTRIG.*] equals the **WCLK** counter) the bit goes back low.

*/
#define I2S_STMPCTL_INRDY                                            0x00000002U
#define I2S_STMPCTL_INRDY_M                                          0x00000002U
#define I2S_STMPCTL_INRDY_S                                          1U
/*

        Field:           OUTRDY
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Low until the output pins are ready to be started by the samplestamp generator. When started (that is [STMPOUTTRIG.*] equals the **WCLK** counter) the bit goes back low.

*/
#define I2S_STMPCTL_OUTRDY                                           0x00000004U
#define I2S_STMPCTL_OUTRDY_M                                         0x00000004U
#define I2S_STMPCTL_OUTRDY_S                                         2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPXCPT0
    Offset name:         I2S_O_STMPXCPT0
    Relative address:    0x38
    Description:         Captured **XOSC** Counter Value, Capture Channel 0
    Default Value:       0x00000000

        Field:           CAPTVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The value of the samplestamp **XOSC** counter ([STMPXCNT.CURR_VALUE]) last time an event was pulsed (event source selected in [EVENT.I2SSTMPSEL0.EV] for channel 0). This number corresponds to the number of 24 MHz clock cycles since the last positive edge of the selected **WCLK**.
                         The value is cleared when [STMPCTL.STMP_EN] = 0.
                         Note: Due to buffering and synchronization, **WCLK** is delayed by a small number of **BCLK** periods and clk periods.
                         Note: When calculating the fractional part of the sample stamp, [STMPXPER.*] may be less than this bit field.


*/
#define I2S_STMPXCPT0_CAPTVAL_W                                      16U
#define I2S_STMPXCPT0_CAPTVAL_M                                      0x0000FFFFU
#define I2S_STMPXCPT0_CAPTVAL_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPXPER
    Offset name:         I2S_O_STMPXPER
    Relative address:    0x3C
    Description:         XOSC Period Value
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The number of 24 MHz clock cycles in the previous **WCLK** period (that is -  the next value of the **XOSC** counter at the positive **WCLK** edge, had it not been reset to 0).
                         The value is cleared when [STMPCTL.STMP_EN] = 0.


*/
#define I2S_STMPXPER_VALUE_W                                         16U
#define I2S_STMPXPER_VALUE_M                                         0x0000FFFFU
#define I2S_STMPXPER_VALUE_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPWCPT0
    Offset name:         I2S_O_STMPWCPT0
    Relative address:    0x40
    Description:         Captured **WCLK** Counter Value, Capture Channel 0
    Default Value:       0x00000000

        Field:           CAPTVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The value of the samplestamp **WCLK** counter ([STMPWCNT.CURR_VALUE]) last time an event was pulsed (event source selected in [EVENT:I2SSTMPSEL0.EV] for channel 0). This number corresponds to the number of positive **WCLK** edges since the samplestamp generator was enabled (not taking modification through [STMPWADD.*]/[STMPWSET.*] into account).
                         The value is cleared when [STMPCTL.STMP_EN] = 0.


*/
#define I2S_STMPWCPT0_CAPTVAL_W                                      16U
#define I2S_STMPWCPT0_CAPTVAL_M                                      0x0000FFFFU
#define I2S_STMPWCPT0_CAPTVAL_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPWPER
    Offset name:         I2S_O_STMPWPER
    Relative address:    0x44
    Description:         **WCLK** Counter Period Value
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Used to define when [STMPWCNT.*] is to be reset so number of **WCLK** edges are found for the size of the sample buffer. This is thus a modulo value for the **WCLK** counter. This number must correspond to the size of the sample buffer used by the system (that is the index of the last sample plus 1).

*/
#define I2S_STMPWPER_VALUE_W                                         16U
#define I2S_STMPWPER_VALUE_M                                         0x0000FFFFU
#define I2S_STMPWPER_VALUE_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPINTRIG
    Offset name:         I2S_O_STMPINTRIG
    Relative address:    0x48
    Description:         WCLK Counter Trigger Value for Input Pins
    Default Value:       0x00000000

        Field:           INSTRTWCNT
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Compare value used to start the incoming audio streams.
                         This bit field shall equal the **WCLK** counter value during the **WCLK** period in which the first input word(s) are sampled and stored to memory (that is the sample at the start of the very first **DMA** input buffer).

                         The value of this register takes effect when the following conditions are met:
                         - One or more pins are configured as inputs in [AIFDIRCFG.*].
                         - [AIFDMACFG.*] has been configured for the correct buffer size, and at least 32 **BCLK** cycle ticks have happened.

                         Note: To avoid false triggers, this bit field should be set higher than [STMPWPER.VALUE].


*/
#define I2S_STMPINTRIG_INSTRTWCNT_W                                  16U
#define I2S_STMPINTRIG_INSTRTWCNT_M                                  0x0000FFFFU
#define I2S_STMPINTRIG_INSTRTWCNT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPOTRIG
    Offset name:         I2S_O_STMPOTRIG
    Relative address:    0x4C
    Description:         WCLK Counter Trigger Value for Output Pins
    Default Value:       0x00000000

        Field:           OSTRTWCNT
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OUT START WCNT:
                         Compare value used to start the outgoing audio streams.

                         This bit field must equal the **WCLK** counter value during the **WCLK** period in which the first output word(s) read from memory are clocked out (that is the sample at the start of the very first **DMA** output buffer).

                         The value of this register takes effect when the following conditions are met:
                         - One or more pins are configured as outputs in [AIFDIRCFG.*].
                         - [AIFDMACFG.*] has been configured for the correct buffer size, and 32 **BCLK** cycle ticks have happened.
                         - 2 samples have been preloaded from memory (examine the [AIFOUTPTR.*] register if necessary).
                         Note: The memory read access is only performed when required, that is channels 0/1 must be selected in [AIFWMASK0.*]/[AIFWMASK1.*].

                         Note: To avoid false triggers, this bit field should be set higher than [STMPWPER.VALUE].


*/
#define I2S_STMPOTRIG_OSTRTWCNT_W                                    16U
#define I2S_STMPOTRIG_OSTRTWCNT_M                                    0x0000FFFFU
#define I2S_STMPOTRIG_OSTRTWCNT_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPWSET
    Offset name:         I2S_O_STMPWSET
    Relative address:    0x50
    Description:         WCLK Counter Set Operation
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     **WCLK** counter modification: Sets the running **WCLK** counter equal to the written value.

*/
#define I2S_STMPWSET_VALUE_W                                         16U
#define I2S_STMPWSET_VALUE_M                                         0x0000FFFFU
#define I2S_STMPWSET_VALUE_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPWADD
    Offset name:         I2S_O_STMPWADD
    Relative address:    0x54
    Description:         WCLK Counter Add Operation
    Default Value:       0x00000000

        Field:           VALINC
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     write-only
        Description:     **WCLK** counter modification: Adds the written value to the running **WCLK** counter. If a positive edge of **WCLK** occurs at the same time as the operation, this will be taken into account.
                         To add a negative value, write "[STMPWPER.VALUE] - value".


*/
#define I2S_STMPWADD_VALINC_W                                        16U
#define I2S_STMPWADD_VALINC_M                                        0x0000FFFFU
#define I2S_STMPWADD_VALINC_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPXPRMIN
    Offset name:         I2S_O_STMPXPRMIN
    Relative address:    0x58
    Description:         XOSC Minimum Period Value
                        Minimum Value of [STMPXPER.*]
    Default Value:       0x0000FFFF

        Field:           VALUE
        From..to bits:   0...15
        DefaultValue:    0xFFFF
        Access type:     read-write
        Description:     Each time [STMPXPER.*] is updated, the value is also loaded into this register, provided that the value is smaller than the current value in this register.
                         When written, the register is reset to 0xFFFF (65535), regardless of the value written.
                         The minimum value can be used to detect extra **WCLK** pulses (this registers value will be significantly smaller than [STMPXPER.VALUE]).


*/
#define I2S_STMPXPRMIN_VALUE_W                                       16U
#define I2S_STMPXPRMIN_VALUE_M                                       0x0000FFFFU
#define I2S_STMPXPRMIN_VALUE_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPWCNT
    Offset name:         I2S_O_STMPWCNT
    Relative address:    0x5C
    Description:         Current Value of WCNT
    Default Value:       0x00000000

        Field:           CURRVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Current value of the **WCLK** counter

*/
#define I2S_STMPWCNT_CURRVAL_W                                       16U
#define I2S_STMPWCNT_CURRVAL_M                                       0x0000FFFFU
#define I2S_STMPWCNT_CURRVAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STMPXCNT
    Offset name:         I2S_O_STMPXCNT
    Relative address:    0x60
    Description:         Current Value of XCNT
    Default Value:       0x00000000

        Field:           CURRVAL
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Current value of the **XOSC** counter, latched when reading [STMPWCNT.*].

*/
#define I2S_STMPXCNT_CURRVAL_W                                       16U
#define I2S_STMPXCNT_CURRVAL_M                                       0x0000FFFFU
#define I2S_STMPXCNT_CURRVAL_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQMASK
    Offset name:         I2S_O_IRQMASK
    Relative address:    0x70
    Description:         Interrupt Mask Register

                        Selects mask states of the flags in [IRQFLAGS.*] that contribute to the **I2S_IRQ** event.
    Default Value:       0x00000000

        Field:           PTRERR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.PTR_ERR] interrupt mask.

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_PTRERR                                           0x00000001U
#define I2S_IRQMASK_PTRERR_M                                         0x00000001U
#define I2S_IRQMASK_PTRERR_S                                         0U
/*

        Field:           WCLKERR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.WCLK_ERR] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_WCLKERR                                          0x00000002U
#define I2S_IRQMASK_WCLKERR_M                                        0x00000002U
#define I2S_IRQMASK_WCLKERR_S                                        1U
/*

        Field:           BUSERR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.BUS_ERR] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_BUSERR                                           0x00000004U
#define I2S_IRQMASK_BUSERR_M                                         0x00000004U
#define I2S_IRQMASK_BUSERR_S                                         2U
/*

        Field:           WCLKTOUT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.WCLK_TIMEOUT] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_WCLKTOUT                                         0x00000008U
#define I2S_IRQMASK_WCLKTOUT_M                                       0x00000008U
#define I2S_IRQMASK_WCLKTOUT_S                                       3U
/*

        Field:           AIFDMAOUT
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.AIF_DMA_OUT] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_AIFDMAOUT                                        0x00000010U
#define I2S_IRQMASK_AIFDMAOUT_M                                      0x00000010U
#define I2S_IRQMASK_AIFDMAOUT_S                                      4U
/*

        Field:           AIFDMAIN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.AIF_DMA_IN] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_AIFDMAIN                                         0x00000020U
#define I2S_IRQMASK_AIFDMAIN_M                                       0x00000020U
#define I2S_IRQMASK_AIFDMAIN_S                                       5U
/*

        Field:           XCNTCPT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     [IRQFLAGS.XCNT_CAPTURE] interrupt mask

                         0: Disable
                         1: Enable

*/
#define I2S_IRQMASK_XCNTCPT                                          0x00000040U
#define I2S_IRQMASK_XCNTCPT_M                                        0x00000040U
#define I2S_IRQMASK_XCNTCPT_S                                        6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQFLAGS
    Offset name:         I2S_O_IRQFLAGS
    Relative address:    0x74
    Description:         Raw Interrupt Status Register
    Default Value:       0x00000000

        Field:           PTRERR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when [AIFINPTRNEXT.*] or [AIFOUTPTRNEXT.*] has not been loaded with the next block address in time.
                         This error requires a complete restart since word synchronization has been lost. The bit is sticky and may only be cleared by software (by writing '1' to [IRQCLR.PTR_ERR]).


*/
#define I2S_IRQFLAGS_PTRERR                                          0x00000001U
#define I2S_IRQFLAGS_PTRERR_M                                        0x00000001U
#define I2S_IRQFLAGS_PTRERR_S                                        0U
/*

        Field:           WCLKERR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when:
                         - An unexpected **WCLK** edge occurs during the data delay period of a phase.  Note unexpected **WCLK** edges during the word and idle periods of the phase are not detected.
                         -  In dual-phase mode, when two **WCLK** edges are less than 4 **BCLK** cycles apart.
                         -  In single-phase mode, when a **WCLK** pulse occurs before the last channel.
                         This error requires a complete restart since word synchronization has been lost. The bit is sticky and may only be cleared by software (by writing '1' to [IRQCLR.WCLK_ERR]).

*/
#define I2S_IRQFLAGS_WCLKERR                                         0x00000002U
#define I2S_IRQFLAGS_WCLKERR_M                                       0x00000002U
#define I2S_IRQFLAGS_WCLKERR_S                                       1U
/*

        Field:           BUSERR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when a **DMA** operation is not completed in time (that is audio output buffer underflow, or audio input buffer overflow).
                         This error requires a complete restart since word synchronization has been lost. The bit is sticky and may only be cleared by software (by writing '1' to [IRQCLR.BUS_ERR]).

                         Note that DMA initiated transactions to illegal addresses will not trigger an interrupt. The response to such transactions is undefined.

                         INTERNAL_NOTE:
                         The I2S module is not monitoring the AHB bus error response, hence bus faults resulting from access to illegal addresses are not generated. It is best practice to detect and report such errors and, therefore, a ticket has been entered into the CDDS bug tracking database for the I2S module. The reference is CC26_I2S--BUG00011.
                         All versions of CC13xx/CC26xx Chameleon and Lizard are impacted, and there is no plans to change this behavior.


*/
#define I2S_IRQFLAGS_BUSERR                                          0x00000004U
#define I2S_IRQFLAGS_BUSERR_M                                        0x00000004U
#define I2S_IRQFLAGS_BUSERR_S                                        2U
/*

        Field:           WCLKTOUT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when the sample stamp generator does not detect a positive **WCLK** edge for  65535 clk periods. This signalizes that the internal or external **BCLK** and **WCLK** generator source has been disabled.

                         The bit is sticky and may only be cleared by software (by writing '1' to [IRQCLR.WCLK_TIMEOUT]).

*/
#define I2S_IRQFLAGS_WCLKTOUT                                        0x00000008U
#define I2S_IRQFLAGS_WCLKTOUT_M                                      0x00000008U
#define I2S_IRQFLAGS_WCLKTOUT_S                                      3U
/*

        Field:           AIFDMAOUT
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when condition for this bit field event occurs (auto cleared when output pointer is updated - [AIFOUTPTRNEXT.*]), see description of [AIFOUTPTRNEXT.*] register for details

*/
#define I2S_IRQFLAGS_AIFDMAOUT                                       0x00000010U
#define I2S_IRQFLAGS_AIFDMAOUT_M                                     0x00000010U
#define I2S_IRQFLAGS_AIFDMAOUT_S                                     4U
/*

        Field:           AIFDMAIN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set when condition for this bit field event occurs (auto cleared when input pointer is updated - [AIFINPTRNEXT.*]), see description of [AIFINPTRNEXT.*] register for details.

*/
#define I2S_IRQFLAGS_AIFDMAIN                                        0x00000020U
#define I2S_IRQFLAGS_AIFDMAIN_M                                      0x00000020U
#define I2S_IRQFLAGS_AIFDMAIN_S                                      5U
/*

        Field:           XCNTCPT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Will be set when xcnt counter is captured either by events or software.
                                           Needs to be cleared by software.

*/
#define I2S_IRQFLAGS_XCNTCPT                                         0x00000040U
#define I2S_IRQFLAGS_XCNTCPT_M                                       0x00000040U
#define I2S_IRQFLAGS_XCNTCPT_S                                       6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQSET
    Offset name:         I2S_O_IRQSET
    Relative address:    0x78
    Description:         Interrupt Set Register
    Default Value:       0x00000000

        Field:           PTRERR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.PTR_ERR]

*/
#define I2S_IRQSET_PTRERR                                            0x00000001U
#define I2S_IRQSET_PTRERR_M                                          0x00000001U
#define I2S_IRQSET_PTRERR_S                                          0U
/*

        Field:           WCLKERR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.WCLK_ERR]

*/
#define I2S_IRQSET_WCLKERR                                           0x00000002U
#define I2S_IRQSET_WCLKERR_M                                         0x00000002U
#define I2S_IRQSET_WCLKERR_S                                         1U
/*

        Field:           BUSERR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.BUS_ERR]

*/
#define I2S_IRQSET_BUSERR                                            0x00000004U
#define I2S_IRQSET_BUSERR_M                                          0x00000004U
#define I2S_IRQSET_BUSERR_S                                          2U
/*

        Field:           WCLKTOUT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.WCLK_TIMEOUT]

*/
#define I2S_IRQSET_WCLKTOUT                                          0x00000008U
#define I2S_IRQSET_WCLKTOUT_M                                        0x00000008U
#define I2S_IRQSET_WCLKTOUT_S                                        3U
/*

        Field:           AIFDMAOUT
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.AIF_DMA_OUT] (unless a auto clear criteria was given at the same time, in which the set will be ignored)

*/
#define I2S_IRQSET_AIFDMAOUT                                         0x00000010U
#define I2S_IRQSET_AIFDMAOUT_M                                       0x00000010U
#define I2S_IRQSET_AIFDMAOUT_S                                       4U
/*

        Field:           AIFDMAIN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.AIF_DMA_IN] (unless a auto clear criteria was given at the same time, in which the set will be ignored)

*/
#define I2S_IRQSET_AIFDMAIN                                          0x00000020U
#define I2S_IRQSET_AIFDMAIN_M                                        0x00000020U
#define I2S_IRQSET_AIFDMAIN_S                                        5U
/*

        Field:           XCNTCPT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Sets the interrupt of [IRQFLAGS.XCNT_CAPTURE] (unless a auto clear criteria was given at the same time, in which the set will be ignored)

*/
#define I2S_IRQSET_XCNTCPT                                           0x00000040U
#define I2S_IRQSET_XCNTCPT_M                                         0x00000040U
#define I2S_IRQSET_XCNTCPT_S                                         6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQCLR
    Offset name:         I2S_O_IRQCLR
    Relative address:    0x7C
    Description:         Interrupt Clear Register
    Default Value:       0x00000000

        Field:           PTRERR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.PTR_ERR] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_PTRERR                                            0x00000001U
#define I2S_IRQCLR_PTRERR_M                                          0x00000001U
#define I2S_IRQCLR_PTRERR_S                                          0U
/*

        Field:           WCLKERR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.WCLK_ERR] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_WCLKERR                                           0x00000002U
#define I2S_IRQCLR_WCLKERR_M                                         0x00000002U
#define I2S_IRQCLR_WCLKERR_S                                         1U
/*

        Field:           BUSERR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.BUS_ERR] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_BUSERR                                            0x00000004U
#define I2S_IRQCLR_BUSERR_M                                          0x00000004U
#define I2S_IRQCLR_BUSERR_S                                          2U
/*

        Field:           WCLKTOUT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.WCLK_TIMEOUT] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_WCLKTOUT                                          0x00000008U
#define I2S_IRQCLR_WCLKTOUT_M                                        0x00000008U
#define I2S_IRQCLR_WCLKTOUT_S                                        3U
/*

        Field:           AIFDMAOUT
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.AIF_DMA_OUT] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_AIFDMAOUT                                         0x00000010U
#define I2S_IRQCLR_AIFDMAOUT_M                                       0x00000010U
#define I2S_IRQCLR_AIFDMAOUT_S                                       4U
/*

        Field:           AIFDMAIN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.AIF_DMA_IN] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_AIFDMAIN                                          0x00000020U
#define I2S_IRQCLR_AIFDMAIN_M                                        0x00000020U
#define I2S_IRQCLR_AIFDMAIN_S                                        5U
/*

        Field:           XCNTCPT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1: Clears the interrupt of [IRQFLAGS.XCNT_CAPTURE] (unless a set criteria was given at the same time in which the clear will be ignored)

*/
#define I2S_IRQCLR_XCNTCPT                                           0x00000040U
#define I2S_IRQCLR_XCNTCPT_M                                         0x00000040U
#define I2S_IRQCLR_XCNTCPT_S                                         6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFMCLKDIV
    Offset name:         I2S_O_AIFMCLKDIV
    Relative address:    0x80
    Description:         **MCLK** Division Ratio
    Default Value:       0x00000000

        Field:           MDIV
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:         An unsigned factor of the division ratio used to generate **MCLK** [2-1024]:
                                                                     **MCLK** = MCUCLK/MDIV[Hz] **MCUCLK** is upto 96MHz.
                                                                     A value of 0 is interpreted as 1024.
                                                                     A value of 1 is invalid.
                                                                     If MDIV is odd the low phase of the clock is one **MCUCLK** period longer than the high phase.

*/
#define I2S_AIFMCLKDIV_MDIV_W                                        10U
#define I2S_AIFMCLKDIV_MDIV_M                                        0x000003FFU
#define I2S_AIFMCLKDIV_MDIV_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFBCLKDIV
    Offset name:         I2S_O_AIFBCLKDIV
    Relative address:    0x84
    Description:         **BCLK** Division Ratio
    Default Value:       0x00000000

        Field:           BDIV
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:         An unsigned factor of the division ratio used to generate **BCLK** [2-1024]:
                                                                     **BCLK** = MCUCLK/BDIV[Hz] **MCUCLK** can be upto 96MHz.
                                                                     A value of 0 is interpreted as 1024.
                                                                     A value of 1 is invalid.
                                                                     If BDIV is odd and [AIFCLKCTL.SMPL_ON_POSEDGE.*] = 0, the low phase of the clock is one **MCUCLK** period longer than the high phase.
                                                                     If BDIV is odd and [AIFCLKCTL.SMPL_ON_POSEDGE.*] = 1 , the high phase of the clock is one **MCUCLK** period longer than the low phase.

*/
#define I2S_AIFBCLKDIV_BDIV_W                                        10U
#define I2S_AIFBCLKDIV_BDIV_M                                        0x000003FFU
#define I2S_AIFBCLKDIV_BDIV_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFWCLKDIV
    Offset name:         I2S_O_AIFWCLKDIV
    Relative address:    0x88
    Description:         **WCLK** Division Ratio
    Default Value:       0x00000000

        Field:           WDIV
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:        If [AIFCLKCTL.WCLK_PHASE.*] = 0, Single phase. **WCLK** is high one **BCLK** period and low WDIV[9:0] (unsigned, [1-1023]) **BCLK** periods.
                                                                    **WCLK** = **MCUCLK** / BDIV*(WDIV[9:0] + 1) [Hz] **MCUCLK** upto 96MHz.
                                                                    If [AIFCLKCTL.WCLK_PHASE.*] = 1, Dual phase. Each phase on **WCLK** (50% duty cycle) is WDIV[9:0] (unsigned, [1-1023]) **BCLK** periods.
                                                                    **WCLK **= **MCUCLK ** / BDIV*(2*WDIV[9:0]) [Hz]
                                                                    If [AIFCLKCTL.WCLK_PHASE.*] = 2, User defined. **WCLK** is high WDIV[7:0] (unsigned, [1-255]) **BCLK** periods and low WDIV[15:8] (unsigned, [1-255]) **BCLK** periods.
                                                                    **WCLK** = **MCUCLK ** / (BDIV*(WDIV[7:0] + WDIV[15:8]) [Hz]

*/
#define I2S_AIFWCLKDIV_WDIV_W                                        16U
#define I2S_AIFWCLKDIV_WDIV_M                                        0x0000FFFFU
#define I2S_AIFWCLKDIV_WDIV_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIFCLKCTL
    Offset name:         I2S_O_AIFCLKCTL
    Relative address:    0x8C
    Description:         Internal Audio Clock Control
    Default Value:       0x00000000

        Field:           WBEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0: WCLK/BCLK geneartion disabled, 1: WCLK/BCLK generation enabled

*/
#define I2S_AIFCLKCTL_WBEN                                           0x00000001U
#define I2S_AIFCLKCTL_WBEN_M                                         0x00000001U
#define I2S_AIFCLKCTL_WBEN_S                                         0U
/*

        Field:           WCLKPHASE
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Decides how the WCLK division ratio is calculated and used to generate different duty cycles (See [AIFWCLKDIV.WDIV.*]).

*/
#define I2S_AIFCLKCTL_WCLKPHASE_W                                    2U
#define I2S_AIFCLKCTL_WCLKPHASE_M                                    0x00000006U
#define I2S_AIFCLKCTL_WCLKPHASE_S                                    1U
/*

        Field:           MEN
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0: **MCLK** geneartion disabled, 1: **MCLK** generation enabled

*/
#define I2S_AIFCLKCTL_MEN                                            0x00000008U
#define I2S_AIFCLKCTL_MEN_M                                          0x00000008U
#define I2S_AIFCLKCTL_MEN_S                                          3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CLKCFG
    Offset name:         I2S_O_CLKCFG
    Relative address:    0x1000
    Description:         Audio clock source selection and **I2S** enable register
                        Note: Disable the [CLKCFG.MEM_CLK_EN] and [CLKCFG.ADFS_EN] to change [CLK_CFG.MEM_CLK_SEL]
                        After changing [CLK_CFG.MEM_CLK_SEL],  enable [CLKCFG.ADFS_EN] followed by [CLKCFG.MEM_CLK_EN]

    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:          0: **I2S** clock disabled
                                                                      1: **I2S** clock enabled

*/
#define I2S_CLKCFG_EN                                                0x00000001U
#define I2S_CLKCFG_EN_M                                              0x00000001U
#define I2S_CLKCFG_EN_S                                              0U
/*

        Field:           CLKSEL
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Audio clock selection

        ENUMs:
            SEL_0:                       No Clock
            SEL_1:                       SOC Clock(80MHz)
            SEL_2:                       SOC PLL Clock(un-swallowed 80MHz)
            SEL_3:                       HFXT
*/
#define I2S_CLKCFG_CLKSEL_W                                          3U
#define I2S_CLKCFG_CLKSEL_M                                          0x00000070U
#define I2S_CLKCFG_CLKSEL_S                                          4U
#define I2S_CLKCFG_CLKSEL_SEL_0                                      0x00000000U
#define I2S_CLKCFG_CLKSEL_SEL_1                                      0x00000010U
#define I2S_CLKCFG_CLKSEL_SEL_2                                      0x00000020U
#define I2S_CLKCFG_CLKSEL_SEL_3                                      0x00000030U
/*

        Field:           ADFSEN
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADFS enable field

*/
#define I2S_CLKCFG_ADFSEN                                            0x00000080U
#define I2S_CLKCFG_ADFSEN_M                                          0x00000080U
#define I2S_CLKCFG_ADFSEN_S                                          7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADFSCTRL1
    Offset name:         I2S_O_ADFSCTRL1
    Relative address:    0x1004
    Description:         ADFS TREF control register
    Default Value:       0x00000000

        Field:           TREF
        From..to bits:   0...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TREF value for ADFS

*/
#define I2S_ADFSCTRL1_TREF_W                                         21U
#define I2S_ADFSCTRL1_TREF_M                                         0x001FFFFFU
#define I2S_ADFSCTRL1_TREF_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADFSCTRL2
    Offset name:         I2S_O_ADFSCTRL2
    Relative address:    0x1008
    Description:         ADFS general configuration register
    Default Value:       0x00000000

        Field:           DELTA
        From..to bits:   0...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADFS delta value field

*/
#define I2S_ADFSCTRL2_DELTA_W                                        17U
#define I2S_ADFSCTRL2_DELTA_M                                        0x0001FFFFU
#define I2S_ADFSCTRL2_DELTA_S                                        0U
/*

        Field:           DELTASIGN
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADFS delta sign field

*/
#define I2S_ADFSCTRL2_DELTASIGN                                      0x00020000U
#define I2S_ADFSCTRL2_DELTASIGN_M                                    0x00020000U
#define I2S_ADFSCTRL2_DELTASIGN_S                                    17U
/*

        Field:           DIV
        From..to bits:   20...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ADFS div value field

*/
#define I2S_ADFSCTRL2_DIV_W                                          10U
#define I2S_ADFSCTRL2_DIV_M                                          0x3FF00000U
#define I2S_ADFSCTRL2_DIV_S                                          20U

#endif /* __HW_I2S_H__*/
