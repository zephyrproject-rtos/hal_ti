/******************************************************************************
*  Filename:       hw_ospi.h
*
*  Description:    Defines and prototypes for the OSPI peripheral.
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
#ifndef __HW_OSPI_H__
#define __HW_OSPI_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the OSPI component

--------------------------------------------------------------------------------- */

//Octal-SPI Configuration Register
#define OSPI_O_CONFIG                                                0x00000000U

//Device Read Instruction Configuration Register
#define OSPI_O_DEV_INSTR_RD_CONFIG                                   0x00000004U

//Device Write Instruction Configuration Register
#define OSPI_O_DEV_INSTR_WR_CONFIG                                   0x00000008U

//Octal-SPI Device Delay Register: This register is used to introduce relative delays into the generation of the master output signals
#define OSPI_O_DEV_DELAY                                             0x0000000CU

//Read Data Capture Register
#define OSPI_O_RD_DATA_CAPTURE                                       0x00000010U

//Device Size Configuration Register
#define OSPI_O_DEV_SIZE_CONFIG                                       0x00000014U

//SRAM Partition Configuration Register
#define OSPI_O_SRAM_PARTITION_CFG                                    0x00000018U

//Indirect AHB Address Trigger Register
#define OSPI_O_IND_AHB_ADDR_TRIGGER                                  0x0000001CU

//DMA Peripheral Configuration Register
#define OSPI_O_DMA_PERIPH_CONFIG                                     0x00000020U

//Remap Address Register
#define OSPI_O_REMAP_ADDR                                            0x00000024U

//Mode Bit Configuration Register
#define OSPI_O_MODE_BIT_CONFIG                                       0x00000028U

//SRAM Fill Register
#define OSPI_O_SRAM_FILL                                             0x0000002CU

//TX Threshold Register
#define OSPI_O_TX_THRESH                                             0x00000030U

//RX Threshold Register
#define OSPI_O_RX_THRESH                                             0x00000034U

//Write Completion Control Register: This register defines how the controller will poll the device following a write transfer
#define OSPI_O_WRITE_COMPLETION_CTRL                                 0x00000038U

//Polling Expiration Register
#define OSPI_O_NO_OF_POLLS_BEF_EXP                                   0x0000003CU

//Interrupt Status Register: The status fields in this register are set when the described event occurs and the interrupt is enabled in the mask register
#define OSPI_O_IRQ_STATUS                                            0x00000040U

//Interrupt Mask:  0 : the interrupt for the corresponding interrupt status register bit is disabled
#define OSPI_O_IRQ_MASK                                              0x00000044U

//Lower Write Protection Register
#define OSPI_O_LOWER_WR_PROT                                         0x00000050U

//Upper Write Protection Register
#define OSPI_O_UPPER_WR_PROT                                         0x00000054U

//Write Protection Control Register
#define OSPI_O_WR_PROT_CTRL                                          0x00000058U

//Indirect Read Transfer Control Register
#define OSPI_O_INDIRECT_READ_XFER_CTRL                               0x00000060U

//Indirect Read Transfer Watermark Register
#define OSPI_O_INDIRECT_READ_XFER_WATERMARK                          0x00000064U

//Indirect Read Transfer Start Address Register
#define OSPI_O_INDIRECT_READ_XFER_START                              0x00000068U

//Indirect Read Transfer Number Bytes Register
#define OSPI_O_INDIRECT_READ_XFER_NUM_BYTES                          0x0000006CU

//Indirect Write Transfer Control Register
#define OSPI_O_INDIRECT_WRITE_XFER_CTRL                              0x00000070U

//Indirect Write Transfer Watermark Register
#define OSPI_O_INDIRECT_WRITE_XFER_WATERMARK                         0x00000074U

//Indirect Write Transfer Start Address Register
#define OSPI_O_INDIRECT_WRITE_XFER_START                             0x00000078U

//Indirect Write Transfer Number Bytes Register
#define OSPI_O_INDIRECT_WRITE_XFER_NUM_BYTES                         0x0000007CU

//Indirect Trigger Address Range Register
#define OSPI_O_INDIRECT_TRIGGER_ADDR_RANGE                           0x00000080U

//Flash Command Control Memory Register
#define OSPI_O_FLASH_COMMAND_CTRL_MEM                                0x0000008CU

//Flash Command Control Register
#define OSPI_O_FLASH_CMD_CTRL                                        0x00000090U

//Flash Command Address Register
#define OSPI_O_FLASH_CMD_ADDR                                        0x00000094U

//Flash Command Read Data Register (Lower)
#define OSPI_O_FLASH_RD_DATA_LOWER                                   0x000000A0U

//Flash Command Read Data Register (Upper)
#define OSPI_O_FLASH_RD_DATA_UPPER                                   0x000000A4U

//Flash Command Write Data Register (Lower)
#define OSPI_O_FLASH_WR_DATA_LOWER                                   0x000000A8U

//Flash Command Write Data Register (Upper)
#define OSPI_O_FLASH_WR_DATA_UPPER                                   0x000000ACU

//Polling Flash Status Register
#define OSPI_O_POLLING_FLASH_STATUS                                  0x000000B0U

//PHY Configuration Register
#define OSPI_O_PHY_CONFIGURATION                                     0x000000B4U

//PHY DLL Master Control Register
#define OSPI_O_PHY_MASTER_CONTROL                                    0x000000B8U

//DLL Observable Register Lower
#define OSPI_O_DLL_OBSERVABLE_LOWER                                  0x000000BCU

//DLL Observable Register Upper
#define OSPI_O_DLL_OBSERVABLE_UPPER                                  0x000000C0U

//Opcode Extension Register (Lower)
#define OSPI_O_OPCODE_EXT_LOWER                                      0x000000E0U

//Opcode Extension Register (Upper)
#define OSPI_O_OPCODE_EXT_UPPER                                      0x000000E4U

//Module ID Register
#define OSPI_O_MODULE_ID                                             0x000000FCU



/*-----------------------------------REGISTER------------------------------------
    Register name:       CONFIG
    Offset name:         OSPI_O_CONFIG
    Relative address:    0x0
    Description:         Octal-SPI Configuration Register
    Default Value:       0x82080081

        Field:           ENB_SPI
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Octal-SPI Enable:

        ENUMs:
            DISABLE:                     disable the Octal-SPI, once current transfer of the data word (FF_W) is complete. 1 : enable the Octal-SPI, when spi_enable = 0, all output enables are inactive and all pins are set to input mode.
            ENABLE:                      enable the Octal-SPI, when spi_enable = 0, all output enables are inactive and all pins are set to input mode.
*/
#define OSPI_CONFIG_ENB_SPI                                          0x00000001U
#define OSPI_CONFIG_ENB_SPI_M                                        0x00000001U
#define OSPI_CONFIG_ENB_SPI_S                                        0U
#define OSPI_CONFIG_ENB_SPI_DISABLE                                  0x00000000U
#define OSPI_CONFIG_ENB_SPI_ENABLE                                   0x00000001U
/*

        Field:           SEL_CLK_POL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock polarity outside SPI word:

        ENUMs:
            DISABLE:                     the SPI clock is quiescent low 1 : the SPI clock is quiescent high
            ENABLE:                      the SPI clock is quiescent high
*/
#define OSPI_CONFIG_SEL_CLK_POL                                      0x00000002U
#define OSPI_CONFIG_SEL_CLK_POL_M                                    0x00000002U
#define OSPI_CONFIG_SEL_CLK_POL_S                                    1U
#define OSPI_CONFIG_SEL_CLK_POL_DISABLE                              0x00000000U
#define OSPI_CONFIG_SEL_CLK_POL_ENABLE                               0x00000002U
/*

        Field:           SEL_CLK_PHASE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Select Clock Phase: Selects whether the clock is in an active or inactive phase outside the SPI word.

        ENUMs:
            DISABLE:                     the SPI clock is active outside the word 1 : the SPI clock is inactive outside the word
            ENABLE:                      the SPI clock is inactive outside the word
*/
#define OSPI_CONFIG_SEL_CLK_PHASE                                    0x00000004U
#define OSPI_CONFIG_SEL_CLK_PHASE_M                                  0x00000004U
#define OSPI_CONFIG_SEL_CLK_PHASE_S                                  2U
#define OSPI_CONFIG_SEL_CLK_PHASE_DISABLE                            0x00000000U
#define OSPI_CONFIG_SEL_CLK_PHASE_ENABLE                             0x00000004U
/*

        Field:           PHY_MODE_ENABLE
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PHY mode enable: When enabled, the controller is informed that PHY Module is to be used for handling SPI transfers. This bit is relevant only for configuration with PHY Module.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_PHY_MODE_ENABLE                                  0x00000008U
#define OSPI_CONFIG_PHY_MODE_ENABLE_M                                0x00000008U
#define OSPI_CONFIG_PHY_MODE_ENABLE_S                                3U
#define OSPI_CONFIG_PHY_MODE_ENABLE_DISABLE                          0x00000000U
#define OSPI_CONFIG_PHY_MODE_ENABLE_ENABLE                           0x00000008U
/*

        Field:           HOLD_PIN
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set to drive the HOLD pin of the FLASH device and reset for de-activation of the HOLD pin feature

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_HOLD_PIN                                         0x00000010U
#define OSPI_CONFIG_HOLD_PIN_M                                       0x00000010U
#define OSPI_CONFIG_HOLD_PIN_S                                       4U
#define OSPI_CONFIG_HOLD_PIN_DISABLE                                 0x00000000U
#define OSPI_CONFIG_HOLD_PIN_ENABLE                                  0x00000010U
/*

        Field:           RESET_PIN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set to drive the RESET pin of the FLASH device and reset for de-activation of the RESET pin feature

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_RESET_PIN                                        0x00000020U
#define OSPI_CONFIG_RESET_PIN_M                                      0x00000020U
#define OSPI_CONFIG_RESET_PIN_S                                      5U
#define OSPI_CONFIG_RESET_PIN_DISABLE                                0x00000000U
#define OSPI_CONFIG_RESET_PIN_ENABLE                                 0x00000020U
/*

        Field:           RESET_CFG
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RESET pin configuration: 0 = RESET feature on DQ3 pin of the device 1 = RESET feature on dedicated pin of the device (controlling of 5th bit influences on reset_out output)

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_RESET_CFG                                        0x00000040U
#define OSPI_CONFIG_RESET_CFG_M                                      0x00000040U
#define OSPI_CONFIG_RESET_CFG_S                                      6U
#define OSPI_CONFIG_RESET_CFG_DISABLE                                0x00000000U
#define OSPI_CONFIG_RESET_CFG_ENABLE                                 0x00000040U
/*

        Field:           ENB_DIR_ACC_CTLR
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Enable Direct Access Controller:

        ENUMs:
            DISABLE:                     disable the Direct Access Controller once current transfer of the data word (FF_W) is complete. 1 : enable the Direct Access Controller When the Direct Access Controller and Indirect Access Controller are both disabled, all AHB requested are completed with an error response.
            ENABLE:                      enable the Direct Access Controller When the Direct Access Controller and Indirect Access Controller are both disabled, all AHB requested are completed with an error response.
*/
#define OSPI_CONFIG_ENB_DIR_ACC_CTLR                                 0x00000080U
#define OSPI_CONFIG_ENB_DIR_ACC_CTLR_M                               0x00000080U
#define OSPI_CONFIG_ENB_DIR_ACC_CTLR_S                               7U
#define OSPI_CONFIG_ENB_DIR_ACC_CTLR_DISABLE                         0x00000000U
#define OSPI_CONFIG_ENB_DIR_ACC_CTLR_ENABLE                          0x00000080U
/*

        Field:           ENB_LEGACY_IP_MODE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Legacy IP Mode Enable:

        ENUMs:
            DISABLE:                     Use Direct Access Controller/Indirect Access Controller 1 : legacy Mode is enabled. In this mode, any write to the controller via the AHB interface is serialized and sent to the FLASH device. Any valid AHB read will pop the internal RX-FIFO, retrieving data that was forwarded by the external FLASH device on the SPI lines,4,2 or 1 byte transfers are permitted and controlled via the HSIZE input.
            ENABLE:                      legacy Mode is enabled. In this mode, any write to the controller via the AHB interface is serialized and sent to the FLASH device. Any valid AHB read will pop the internal RX-FIFO, retrieving data that was forwarded by the external FLASH device on the SPI lines,4,2 or 1 byte transfers are permitted and controlled via the HSIZE input.
*/
#define OSPI_CONFIG_ENB_LEGACY_IP_MODE                               0x00000100U
#define OSPI_CONFIG_ENB_LEGACY_IP_MODE_M                             0x00000100U
#define OSPI_CONFIG_ENB_LEGACY_IP_MODE_S                             8U
#define OSPI_CONFIG_ENB_LEGACY_IP_MODE_DISABLE                       0x00000000U
#define OSPI_CONFIG_ENB_LEGACY_IP_MODE_ENABLE                        0x00000100U
/*

        Field:           PERIPH_SEL_DEC
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Peripheral select decode:

        ENUMs:
            DISABLE:                     only 1 of 4 selects n_ss_out[3:0] is active 1 : allow external 4-to-16 decode (n_ss_out = ss)
            ENABLE:                      allow external 4-to-16 decode (n_ss_out = ss)
*/
#define OSPI_CONFIG_PERIPH_SEL_DEC                                   0x00000200U
#define OSPI_CONFIG_PERIPH_SEL_DEC_M                                 0x00000200U
#define OSPI_CONFIG_PERIPH_SEL_DEC_S                                 9U
#define OSPI_CONFIG_PERIPH_SEL_DEC_DISABLE                           0x00000000U
#define OSPI_CONFIG_PERIPH_SEL_DEC_ENABLE                            0x00000200U
/*

        Field:           PERIPH_CS_LINES
        From..to bits:   10...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Peripheral Chip Select Lines: Peripheral chip select lines If pdec = 0, ss[3:0] are output thus: ss[3:0] n_ss_out[3:0] xxx0 1110 xx01 1101 x011 1011 0111 0111 1111 1111 (no peripheral selected) else ss[3:0] directly drives n_ss_out[3:0]

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_CONFIG_PERIPH_CS_LINES_W                                4U
#define OSPI_CONFIG_PERIPH_CS_LINES_M                                0x00003C00U
#define OSPI_CONFIG_PERIPH_CS_LINES_S                                10U
#define OSPI_CONFIG_PERIPH_CS_LINES_MINIMUM                          0x00000000U
#define OSPI_CONFIG_PERIPH_CS_LINES_MAXIMUM                          0x00003C00U
/*

        Field:           WR_PROT_FLASH
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write Protect Flash Pin: Set to drive the Write Protect pin of the FLASH device. This is resynchronized to the generated memory clock as necessary.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_WR_PROT_FLASH                                    0x00004000U
#define OSPI_CONFIG_WR_PROT_FLASH_M                                  0x00004000U
#define OSPI_CONFIG_WR_PROT_FLASH_S                                  14U
#define OSPI_CONFIG_WR_PROT_FLASH_DISABLE                            0x00000000U
#define OSPI_CONFIG_WR_PROT_FLASH_ENABLE                             0x00004000U
/*

        Field:           ENB_DMA_IF
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA Peripheral Interface: Set to 1 to enable the DMA handshaking logic. When enabled the controller will trigger DMA transfer requests via the DMA peripheral interface. Set to 0 to disable

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENB_DMA_IF                                       0x00008000U
#define OSPI_CONFIG_ENB_DMA_IF_M                                     0x00008000U
#define OSPI_CONFIG_ENB_DMA_IF_S                                     15U
#define OSPI_CONFIG_ENB_DMA_IF_DISABLE                               0x00000000U
#define OSPI_CONFIG_ENB_DMA_IF_ENABLE                                0x00008000U
/*

        Field:           ENB_AHB_ADDR_REMAP
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable AHB Address Re-mapping: (Direct Access Mode Only) When set to 1, the incoming AHB address will be adapted and sent to the FLASH device as (address + N), where N is the value stored in the remap address register.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENB_AHB_ADDR_REMAP                               0x00010000U
#define OSPI_CONFIG_ENB_AHB_ADDR_REMAP_M                             0x00010000U
#define OSPI_CONFIG_ENB_AHB_ADDR_REMAP_S                             16U
#define OSPI_CONFIG_ENB_AHB_ADDR_REMAP_DISABLE                       0x00000000U
#define OSPI_CONFIG_ENB_AHB_ADDR_REMAP_ENABLE                        0x00010000U
/*

        Field:           ENTER_XIP_MODE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enter XIP Mode on next READ: Value=0 : If XIP is enabled, then setting to 0 will cause the controller to exit XIP mode on the next READ instruction. Value=1 : If XIP is disabled, then setting to ?1? will inform the controller that the device is ready to enter XIP on the next READ instruction. The controller will therefore send the appropriate command sequence, including mode bits to cause the device to enter XIP mode. Use this register after the controller has ensured the FLASH device has been configured to be ready to enter XIP mode. Note : To exit XIP mode, this bit should be set to 0. This will take effect in the attached device only AFTER the next READ instruction is executed. Software should therefore ensure that at least one READ instruction is requested after resetting this bit before it can be sure XIP mode in the device is exited.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENTER_XIP_MODE                                   0x00020000U
#define OSPI_CONFIG_ENTER_XIP_MODE_M                                 0x00020000U
#define OSPI_CONFIG_ENTER_XIP_MODE_S                                 17U
#define OSPI_CONFIG_ENTER_XIP_MODE_DISABLE                           0x00000000U
#define OSPI_CONFIG_ENTER_XIP_MODE_ENABLE                            0x00020000U
/*

        Field:           ENTER_XIP_MODE_IMM
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enter XIP Mode immediately: Value=0 : If XIP is enabled, then setting to 0 will cause the controller to exit XIP mode on the next READ instruction. Value=1 : Operate the device in XIP mode immediately Use this register when the external device wakes up in XIP mode (as per the contents of its non- volatile configuration register). The controller will assume the next READ instruction will be passed to the device as an XIP instruction, and therefore will not require the READ opcode to be transferred. Note: To exit XIP mode, this bit should be set to 0. This will take effect in the attached device only after the next READ instruction is executed. Software therefore should ensure that at least one READ instruction is requested after resetting this bit in order to be sure that XIP mode is exited.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENTER_XIP_MODE_IMM                               0x00040000U
#define OSPI_CONFIG_ENTER_XIP_MODE_IMM_M                             0x00040000U
#define OSPI_CONFIG_ENTER_XIP_MODE_IMM_S                             18U
#define OSPI_CONFIG_ENTER_XIP_MODE_IMM_DISABLE                       0x00000000U
#define OSPI_CONFIG_ENTER_XIP_MODE_IMM_ENABLE                        0x00040000U
/*

        Field:           MSTR_BAUD_DIV
        From..to bits:   19...22
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Master Mode Baud Rate Divisor: SPI baud rate = (master reference clock) baud_rate_divisor. The baud rate is the clock rate divided by 2 multiplied by (Divisor + 1). Meaning, when Divisor Value is set to 0,1,2,..15 it sets the baud rate is the clock rate divided by 2, 4, 6,..32 respectively

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_CONFIG_MSTR_BAUD_DIV_W                                  4U
#define OSPI_CONFIG_MSTR_BAUD_DIV_M                                  0x00780000U
#define OSPI_CONFIG_MSTR_BAUD_DIV_S                                  19U
#define OSPI_CONFIG_MSTR_BAUD_DIV_MINIMUM                            0x00000000U
#define OSPI_CONFIG_MSTR_BAUD_DIV_MAXIMUM                            0x00780000U
/*

        Field:           ENABLE_AHB_DECODER
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable AHB Decoder: Value=0 : Active slave is selected based on Peripheral Chip Select Lines (bits [13:10]). Value=1 Active slave is selected based on actual AHB address (the partition for each device is calculated with respect to bits [28:21] of Device Size Configuration Register)

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENABLE_AHB_DECODER                               0x00800000U
#define OSPI_CONFIG_ENABLE_AHB_DECODER_M                             0x00800000U
#define OSPI_CONFIG_ENABLE_AHB_DECODER_S                             23U
#define OSPI_CONFIG_ENABLE_AHB_DECODER_DISABLE                       0x00000000U
#define OSPI_CONFIG_ENABLE_AHB_DECODER_ENABLE                        0x00800000U
/*

        Field:           ENABLE_DTR_PROTOCOL
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DTR Protocol: This bit should be set if device is configured to work in DTR protocol.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_ENABLE_DTR_PROTOCOL                              0x01000000U
#define OSPI_CONFIG_ENABLE_DTR_PROTOCOL_M                            0x01000000U
#define OSPI_CONFIG_ENABLE_DTR_PROTOCOL_S                            24U
#define OSPI_CONFIG_ENABLE_DTR_PROTOCOL_DISABLE                      0x00000000U
#define OSPI_CONFIG_ENABLE_DTR_PROTOCOL_ENABLE                       0x01000000U
/*

        Field:           PIPELINE_PHY
        From..to bits:   25...25
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Pipeline PHY Mode enable: This bit is relevant only for configuration with PHY Module. It should be asserted to '1' between consecutive PHY pipeline reads transfers and de-asserted to '0' otherwise.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_PIPELINE_PHY                                     0x02000000U
#define OSPI_CONFIG_PIPELINE_PHY_M                                   0x02000000U
#define OSPI_CONFIG_PIPELINE_PHY_S                                   25U
#define OSPI_CONFIG_PIPELINE_PHY_DISABLE                             0x00000000U
#define OSPI_CONFIG_PIPELINE_PHY_ENABLE                              0x02000000U
/*

        Field:           CRC_ENABLE
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC enable bit This bit is to be set in case the target Flash Device supports CRC (Macronix MX25). It is applicable for Octal DDR Protocol only so should be set back to low if the device is configured to work in another SPI Mode.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_CRC_ENABLE                                       0x20000000U
#define OSPI_CONFIG_CRC_ENABLE_M                                     0x20000000U
#define OSPI_CONFIG_CRC_ENABLE_S                                     29U
#define OSPI_CONFIG_CRC_ENABLE_DISABLE                               0x00000000U
#define OSPI_CONFIG_CRC_ENABLE_ENABLE                                0x20000000U
/*

        Field:           DUAL_BYTE_OPCODE_EN
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Dual-byte Opcode Mode enable bit This bit is to be set in case the target Flash Device supports dual byte opcode (i.e. Macronix MX25). It is applicable for Octal I/O Mode or Protocol only so should be set back to low if the device is configured to work in another SPI Mode. If enabled, the supplementing bytes are taken from Opcode Extension Register (Lower) and from Opcode Extension Register (Upper).

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_DUAL_BYTE_OPCODE_EN                              0x40000000U
#define OSPI_CONFIG_DUAL_BYTE_OPCODE_EN_M                            0x40000000U
#define OSPI_CONFIG_DUAL_BYTE_OPCODE_EN_S                            30U
#define OSPI_CONFIG_DUAL_BYTE_OPCODE_EN_DISABLE                      0x00000000U
#define OSPI_CONFIG_DUAL_BYTE_OPCODE_EN_ENABLE                       0x40000000U
/*

        Field:           IDLE
        From..to bits:   31...31
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Serial interface and low level SPI pipeline is IDLE: This is a STATUS read-only bit. Note this is a retimed signal, so there will be some inherent delay on the generation of this status signal.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_CONFIG_IDLE                                             0x80000000U
#define OSPI_CONFIG_IDLE_M                                           0x80000000U
#define OSPI_CONFIG_IDLE_S                                           31U
#define OSPI_CONFIG_IDLE_DISABLE                                     0x00000000U
#define OSPI_CONFIG_IDLE_ENABLE                                      0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DEV_INSTR_RD_CONFIG
    Offset name:         OSPI_O_DEV_INSTR_RD_CONFIG
    Relative address:    0x4
    Description:         Device Read Instruction Configuration Register
    Default Value:       0x00000003

        Field:           RD_OPCODE_NON_XIP
        From..to bits:   0...7
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Read Opcode in non-XIP mode: Read Opcode to use when not in XIP mode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_RD_CONFIG_RD_OPCODE_NON_XIP_W                 8U
#define OSPI_DEV_INSTR_RD_CONFIG_RD_OPCODE_NON_XIP_M                 0x000000FFU
#define OSPI_DEV_INSTR_RD_CONFIG_RD_OPCODE_NON_XIP_S                 0U
#define OSPI_DEV_INSTR_RD_CONFIG_RD_OPCODE_NON_XIP_MINIMUM           0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_RD_OPCODE_NON_XIP_MAXIMUM           0x000000FFU
/*

        Field:           INSTR_TYPE
        From..to bits:   8...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Instruction Type:
                         0 : Use Standard SPI mode (instruction always shifted into the device on DQ0 only)
                         1 : Use DIO-SPI mode (Instructions always sent on DQ0 and DQ1)
                         2 : Use QIO-SPI mode (Instructions always sent on DQ0, DQ1, DQ2 and DQ3)
                         3 : Use Octal-IO-SPI mode (Instructions always sent on DQ[7:0])

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_RD_CONFIG_INSTR_TYPE_W                        2U
#define OSPI_DEV_INSTR_RD_CONFIG_INSTR_TYPE_M                        0x00000300U
#define OSPI_DEV_INSTR_RD_CONFIG_INSTR_TYPE_S                        8U
#define OSPI_DEV_INSTR_RD_CONFIG_INSTR_TYPE_MINIMUM                  0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_INSTR_TYPE_MAXIMUM                  0x00000300U
/*

        Field:           DDR_EN
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DDR Enable: This is to inform that opcode from rd_opcode_non_xip_fld is compliant with one of the DDR READ Commands

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DEV_INSTR_RD_CONFIG_DDR_EN                              0x00000400U
#define OSPI_DEV_INSTR_RD_CONFIG_DDR_EN_M                            0x00000400U
#define OSPI_DEV_INSTR_RD_CONFIG_DDR_EN_S                            10U
#define OSPI_DEV_INSTR_RD_CONFIG_DDR_EN_DISABLE                      0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_DDR_EN_ENABLE                       0x00000400U
/*

        Field:           PRED_DIS
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Predicted Read Disable Bit: Disable generation of predicted read when doing read accesses using Direct Mode

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DEV_INSTR_RD_CONFIG_PRED_DIS                            0x00000800U
#define OSPI_DEV_INSTR_RD_CONFIG_PRED_DIS_M                          0x00000800U
#define OSPI_DEV_INSTR_RD_CONFIG_PRED_DIS_S                          11U
#define OSPI_DEV_INSTR_RD_CONFIG_PRED_DIS_DISABLE                    0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_PRED_DIS_ENABLE                     0x00000800U
/*

        Field:           ADDR_XFER_TYPE_STD_MODE
        From..to bits:   12...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Address Transfer Type for Standard SPI modes: 0 : Addresses can be shifted to the device on DQ0 only 1 : Addresses can be shifted to the device on DQ0 and DQ1 only 2 : Addresses can be shifted to the device on DQ0, DQ1, DQ2 and DQ3 3 : Addresses can be shifted to the device on DQ[7:0]

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_RD_CONFIG_ADDR_XFER_TYPE_STD_MODE_W           2U
#define OSPI_DEV_INSTR_RD_CONFIG_ADDR_XFER_TYPE_STD_MODE_M           0x00003000U
#define OSPI_DEV_INSTR_RD_CONFIG_ADDR_XFER_TYPE_STD_MODE_S           12U
#define OSPI_DEV_INSTR_RD_CONFIG_ADDR_XFER_TYPE_STD_MODE_MINIMUM     0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_ADDR_XFER_TYPE_STD_MODE_MAXIMUM     0x00003000U
/*

        Field:           DATA_XFER_TYPE_EXT_MODE
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Transfer Type for Standard SPI modes: 0 : SIO mode data is shifted to the device on DQ0 only and from the device on DQ1 only 1 : Used for Dual Input/Output instructions. For data transfers, DQ0 and DQ1 are used as both inputs and outputs. 2 : Used for Quad Input/Output instructions. For data transfers, DQ0,DQ1,DQ2 and DQ3 are used as both inputs and outputs. 3 : Used for Quad Input/Output instructions. For data transfers, DQ[7:0] are used as both inputs and outputs.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_RD_CONFIG_DATA_XFER_TYPE_EXT_MODE_W           2U
#define OSPI_DEV_INSTR_RD_CONFIG_DATA_XFER_TYPE_EXT_MODE_M           0x00030000U
#define OSPI_DEV_INSTR_RD_CONFIG_DATA_XFER_TYPE_EXT_MODE_S           16U
#define OSPI_DEV_INSTR_RD_CONFIG_DATA_XFER_TYPE_EXT_MODE_MINIMUM     0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_DATA_XFER_TYPE_EXT_MODE_MAXIMUM     0x00030000U
/*

        Field:           MODE_BIT_ENABLE
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mode Bit Enable: Set this field to 1 to ensure that the mode bits as defined in the Mode Bit Configuration register are sent following the address bytes.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DEV_INSTR_RD_CONFIG_MODE_BIT_ENABLE                     0x00100000U
#define OSPI_DEV_INSTR_RD_CONFIG_MODE_BIT_ENABLE_M                   0x00100000U
#define OSPI_DEV_INSTR_RD_CONFIG_MODE_BIT_ENABLE_S                   20U
#define OSPI_DEV_INSTR_RD_CONFIG_MODE_BIT_ENABLE_DISABLE             0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_MODE_BIT_ENABLE_ENABLE              0x00100000U
/*

        Field:           DUMMY_RD_CLK_CYCLES
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Dummy Read Clock Cycles: Number of dummy clock cycles required by device for read instruction.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_RD_CONFIG_DUMMY_RD_CLK_CYCLES_W               5U
#define OSPI_DEV_INSTR_RD_CONFIG_DUMMY_RD_CLK_CYCLES_M               0x1F000000U
#define OSPI_DEV_INSTR_RD_CONFIG_DUMMY_RD_CLK_CYCLES_S               24U
#define OSPI_DEV_INSTR_RD_CONFIG_DUMMY_RD_CLK_CYCLES_MINIMUM         0x00000000U
#define OSPI_DEV_INSTR_RD_CONFIG_DUMMY_RD_CLK_CYCLES_MAXIMUM         0x1F000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DEV_INSTR_WR_CONFIG
    Offset name:         OSPI_O_DEV_INSTR_WR_CONFIG
    Relative address:    0x8
    Description:         Device Write Instruction Configuration Register
    Default Value:       0x00000002

        Field:           WR_OPCODE
        From..to bits:   0...7
        DefaultValue:    0x2
        Access type:     read-write
        Description:      Write Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_WR_CONFIG_WR_OPCODE_W                         8U
#define OSPI_DEV_INSTR_WR_CONFIG_WR_OPCODE_M                         0x000000FFU
#define OSPI_DEV_INSTR_WR_CONFIG_WR_OPCODE_S                         0U
#define OSPI_DEV_INSTR_WR_CONFIG_WR_OPCODE_MINIMUM                   0x00000000U
#define OSPI_DEV_INSTR_WR_CONFIG_WR_OPCODE_MAXIMUM                   0x000000FFU
/*

        Field:           WEL_DIS
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     WEL Disable: This is to turn off automatic issuing of WEL Command before write operation for DAC or INDAC

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DEV_INSTR_WR_CONFIG_WEL_DIS                             0x00000100U
#define OSPI_DEV_INSTR_WR_CONFIG_WEL_DIS_M                           0x00000100U
#define OSPI_DEV_INSTR_WR_CONFIG_WEL_DIS_S                           8U
#define OSPI_DEV_INSTR_WR_CONFIG_WEL_DIS_DISABLE                     0x00000000U
#define OSPI_DEV_INSTR_WR_CONFIG_WEL_DIS_ENABLE                      0x00000100U
/*

        Field:           ADDR_XFER_TYPE_STD_MODE
        From..to bits:   12...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Address Transfer Type for Standard SPI modes: 0 : Addresses can be shifted to the device on DQ0 only 1 : Addresses can be shifted to the device on DQ0 and DQ1 only 2 : Addresses can be shifted to the device on DQ0, DQ1, DQ2 and DQ3 3 : Addresses can be shifted to the device on DQ[7:0]

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_WR_CONFIG_ADDR_XFER_TYPE_STD_MODE_W           2U
#define OSPI_DEV_INSTR_WR_CONFIG_ADDR_XFER_TYPE_STD_MODE_M           0x00003000U
#define OSPI_DEV_INSTR_WR_CONFIG_ADDR_XFER_TYPE_STD_MODE_S           12U
#define OSPI_DEV_INSTR_WR_CONFIG_ADDR_XFER_TYPE_STD_MODE_MINIMUM     0x00000000U
#define OSPI_DEV_INSTR_WR_CONFIG_ADDR_XFER_TYPE_STD_MODE_MAXIMUM     0x00003000U
/*

        Field:           DATA_XFER_TYPE_EXT_MODE
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Data Transfer Type for Standard SPI modes: 0 : SIO mode data is shifted to the device on DQ0 only and from the device on DQ1 only 1 : Used for Dual Input/Output instructions. For data transfers, DQ0 and DQ1 are used as both inputs and outputs. 2 : Used for Quad Input/Output instructions. For data transfers, DQ0,DQ1,DQ2 and DQ3 are used as both inputs and outputs. 3 : Used for Quad Input/Output instructions. For data transfers, DQ[7:0] are used as both inputs and outputs.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_WR_CONFIG_DATA_XFER_TYPE_EXT_MODE_W           2U
#define OSPI_DEV_INSTR_WR_CONFIG_DATA_XFER_TYPE_EXT_MODE_M           0x00030000U
#define OSPI_DEV_INSTR_WR_CONFIG_DATA_XFER_TYPE_EXT_MODE_S           16U
#define OSPI_DEV_INSTR_WR_CONFIG_DATA_XFER_TYPE_EXT_MODE_MINIMUM     0x00000000U
#define OSPI_DEV_INSTR_WR_CONFIG_DATA_XFER_TYPE_EXT_MODE_MAXIMUM     0x00030000U
/*

        Field:           DUMMY_WR_CLK_CYCLES
        From..to bits:   24...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Dummy Write Clock Cycles: Number of dummy clock cycles required by device for write instruction.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_INSTR_WR_CONFIG_DUMMY_WR_CLK_CYCLES_W               5U
#define OSPI_DEV_INSTR_WR_CONFIG_DUMMY_WR_CLK_CYCLES_M               0x1F000000U
#define OSPI_DEV_INSTR_WR_CONFIG_DUMMY_WR_CLK_CYCLES_S               24U
#define OSPI_DEV_INSTR_WR_CONFIG_DUMMY_WR_CLK_CYCLES_MINIMUM         0x00000000U
#define OSPI_DEV_INSTR_WR_CONFIG_DUMMY_WR_CLK_CYCLES_MAXIMUM         0x1F000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DEV_DELAY
    Offset name:         OSPI_O_DEV_DELAY
    Relative address:    0xC
    Description:         Octal-SPI Device Delay Register: This register is used to introduce relative delays into the generation of the master output signals. All timings are defined in cycles of the SPI REFERENCE CLOCK/ext_clk, defined in this table as SPI master ref clock.
    Default Value:       0x00000000

        Field:           D_INIT
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Delay with n_ss_out: Delay in master reference clocks between setting n_ss_out low and first bit transfer.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_DELAY_D_INIT_W                                      8U
#define OSPI_DEV_DELAY_D_INIT_M                                      0x000000FFU
#define OSPI_DEV_DELAY_D_INIT_S                                      0U
#define OSPI_DEV_DELAY_D_INIT_MINIMUM                                0x00000000U
#define OSPI_DEV_DELAY_D_INIT_MAXIMUM                                0x000000FFU
/*

        Field:           D_AFTER
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Delay for Last Transaction Bit: Delay in master reference clocks between last bit of current transaction and deasserting the device chip select (n_ss_out). By default, the chip select will be deasserted on the cycle following the completion of the current transaction.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_DELAY_D_AFTER_W                                     8U
#define OSPI_DEV_DELAY_D_AFTER_M                                     0x0000FF00U
#define OSPI_DEV_DELAY_D_AFTER_S                                     8U
#define OSPI_DEV_DELAY_D_AFTER_MINIMUM                               0x00000000U
#define OSPI_DEV_DELAY_D_AFTER_MAXIMUM                               0x0000FF00U
/*

        Field:           D_BTWN
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Delay for Chip Select Deactivation: Delay in master reference clocks between one chip select being de-activated and the activation of another. This is used to ensure a quiet period between the selection of two different slaves and requires the transmit FIFO to be empty.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_DELAY_D_BTWN_W                                      8U
#define OSPI_DEV_DELAY_D_BTWN_M                                      0x00FF0000U
#define OSPI_DEV_DELAY_D_BTWN_S                                      16U
#define OSPI_DEV_DELAY_D_BTWN_MINIMUM                                0x00000000U
#define OSPI_DEV_DELAY_D_BTWN_MAXIMUM                                0x00FF0000U
/*

        Field:           D_NSS
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Clock Delay for Chip Select Deassert: Delay in master reference clocks for the length that the master mode chip select outputs are de-asserted between transactions. The minimum delay is always SCLK period to ensure the chip select is never re-asserted within an SCLK period.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_DELAY_D_NSS_W                                       8U
#define OSPI_DEV_DELAY_D_NSS_M                                       0xFF000000U
#define OSPI_DEV_DELAY_D_NSS_S                                       24U
#define OSPI_DEV_DELAY_D_NSS_MINIMUM                                 0x00000000U
#define OSPI_DEV_DELAY_D_NSS_MAXIMUM                                 0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RD_DATA_CAPTURE
    Offset name:         OSPI_O_RD_DATA_CAPTURE
    Relative address:    0x10
    Description:         Read Data Capture Register
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Bypass the adapted loopback clock circuit

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_RD_DATA_CAPTURE_BYPASS                                  0x00000001U
#define OSPI_RD_DATA_CAPTURE_BYPASS_M                                0x00000001U
#define OSPI_RD_DATA_CAPTURE_BYPASS_S                                0U
#define OSPI_RD_DATA_CAPTURE_BYPASS_DISABLE                          0x00000000U
#define OSPI_RD_DATA_CAPTURE_BYPASS_ENABLE                           0x00000001U
/*

        Field:           DELAY
        From..to bits:   1...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Read Delay: Delay the read data capturing logic by the programmed number of ref_clk cycles

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_RD_DATA_CAPTURE_DELAY_W                                 4U
#define OSPI_RD_DATA_CAPTURE_DELAY_M                                 0x0000001EU
#define OSPI_RD_DATA_CAPTURE_DELAY_S                                 1U
#define OSPI_RD_DATA_CAPTURE_DELAY_MINIMUM                           0x00000000U
#define OSPI_RD_DATA_CAPTURE_DELAY_MAXIMUM                           0x0000001EU
/*

        Field:           SAMPLE_EDGE_SEL
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Sample edge selection: Choose edge on which data outputs from flash memory will be sampled

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_RD_DATA_CAPTURE_SAMPLE_EDGE_SEL                         0x00000020U
#define OSPI_RD_DATA_CAPTURE_SAMPLE_EDGE_SEL_M                       0x00000020U
#define OSPI_RD_DATA_CAPTURE_SAMPLE_EDGE_SEL_S                       5U
#define OSPI_RD_DATA_CAPTURE_SAMPLE_EDGE_SEL_DISABLE                 0x00000000U
#define OSPI_RD_DATA_CAPTURE_SAMPLE_EDGE_SEL_ENABLE                  0x00000020U
/*

        Field:           DQS_ENABLE
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DQS enable bit: If enabled, signal from DQS input is driven into RX DLL and is used for data capturing in PHY Mode rather than internally generated gated ref_clk..

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_RD_DATA_CAPTURE_DQS_ENABLE                              0x00000100U
#define OSPI_RD_DATA_CAPTURE_DQS_ENABLE_M                            0x00000100U
#define OSPI_RD_DATA_CAPTURE_DQS_ENABLE_S                            8U
#define OSPI_RD_DATA_CAPTURE_DQS_ENABLE_DISABLE                      0x00000000U
#define OSPI_RD_DATA_CAPTURE_DQS_ENABLE_ENABLE                       0x00000100U
/*

        Field:           DDR_READ_DELAY
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DDR read delay: Delay the transmitted data by the programmed number of ref_clk cycles.This field is only relevant when DDR Read Command is executed. Otherwise can be ignored.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_RD_DATA_CAPTURE_DDR_READ_DELAY_W                        4U
#define OSPI_RD_DATA_CAPTURE_DDR_READ_DELAY_M                        0x000F0000U
#define OSPI_RD_DATA_CAPTURE_DDR_READ_DELAY_S                        16U
#define OSPI_RD_DATA_CAPTURE_DDR_READ_DELAY_MINIMUM                  0x00000000U
#define OSPI_RD_DATA_CAPTURE_DDR_READ_DELAY_MAXIMUM                  0x000F0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DEV_SIZE_CONFIG
    Offset name:         OSPI_O_DEV_SIZE_CONFIG
    Relative address:    0x14
    Description:         Device Size Configuration Register
    Default Value:       0x00101002

        Field:           NUM_ADDR_BYTES
        From..to bits:   0...3
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Number of address bytes. A value of 0 indicates 1 byte.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_NUM_ADDR_BYTES_W                        4U
#define OSPI_DEV_SIZE_CONFIG_NUM_ADDR_BYTES_M                        0x0000000FU
#define OSPI_DEV_SIZE_CONFIG_NUM_ADDR_BYTES_S                        0U
#define OSPI_DEV_SIZE_CONFIG_NUM_ADDR_BYTES_MINIMUM                  0x00000000U
#define OSPI_DEV_SIZE_CONFIG_NUM_ADDR_BYTES_MAXIMUM                  0x0000000FU
/*

        Field:           BYTES_PER_DEVICE_PAGE
        From..to bits:   4...15
        DefaultValue:    0x100
        Access type:     read-write
        Description:      Number of bytes per device page. This is required by the controller for performing FLASH writes up to and across page boundaries.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_DEVICE_PAGE_W                 12U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_DEVICE_PAGE_M                 0x0000FFF0U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_DEVICE_PAGE_S                 4U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_DEVICE_PAGE_MINIMUM           0x00000000U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_DEVICE_PAGE_MAXIMUM           0x0000FFF0U
/*

        Field:           BYTES_PER_SUBSECTOR
        From..to bits:   16...20
        DefaultValue:    0x10
        Access type:     read-write
        Description:      Number of bytes per Block. This is required by the controller for performing the write protection logic. The number of bytes per block must be a power of 2 number.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_SUBSECTOR_W                   5U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_SUBSECTOR_M                   0x001F0000U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_SUBSECTOR_S                   16U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_SUBSECTOR_MINIMUM             0x00000000U
#define OSPI_DEV_SIZE_CONFIG_BYTES_PER_SUBSECTOR_MAXIMUM             0x001F0000U
/*

        Field:           MEM_SIZE_ON_CS0
        From..to bits:   21...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Size of Flash Device connected to CS[0] pin: Value=00 : size of 512Mb. Value=01 : size of 1Gb. Value=10 : size of 2Gb. Value=11 : size of 4Gb.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS0_W                       2U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS0_M                       0x00600000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS0_S                       21U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS0_MINIMUM                 0x00000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS0_MAXIMUM                 0x00600000U
/*

        Field:           MEM_SIZE_ON_CS1
        From..to bits:   23...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Size of Flash Device connected to CS[1] pin: Value=00 : size of 512Mb. Value=01 : size of 1Gb. Value=10 : size of 2Gb. Value=11 : size of 4Gb.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS1_W                       2U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS1_M                       0x01800000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS1_S                       23U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS1_MINIMUM                 0x00000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS1_MAXIMUM                 0x01800000U
/*

        Field:           MEM_SIZE_ON_CS2
        From..to bits:   25...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Size of Flash Device connected to CS[2] pin: Value=00 : size of 512Mb. Value=01 : size of 1Gb. Value=10 : size of 2Gb. Value=11 : size of 4Gb.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS2_W                       2U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS2_M                       0x06000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS2_S                       25U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS2_MINIMUM                 0x00000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS2_MAXIMUM                 0x06000000U
/*

        Field:           MEM_SIZE_ON_CS3
        From..to bits:   27...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Size of Flash Device connected to CS[3] pin: Value=00 : size of 512Mb. Value=01 : size of 1Gb. Value=10 : size of 2Gb. Value=11 : size of 4Gb.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS3_W                       2U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS3_M                       0x18000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS3_S                       27U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS3_MINIMUM                 0x00000000U
#define OSPI_DEV_SIZE_CONFIG_MEM_SIZE_ON_CS3_MAXIMUM                 0x18000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRAM_PARTITION_CFG
    Offset name:         OSPI_O_SRAM_PARTITION_CFG
    Relative address:    0x18
    Description:         SRAM Partition Configuration Register
    Default Value:       0x00000080

        Field:           THRESHOLD
        From..to bits:   0...7
        DefaultValue:    0x80
        Access type:     read-write
        Description:     Defines the size of the indirect read partition in the SRAM,
                         in units of SRAM locations. By default, half of the SRAM is
                         reserved for indirect read operation, and half for indirect write.
                         The size of this register will scale with the depth of the SRAM.

*/
#define OSPI_SRAM_PARTITION_CFG_THRESHOLD_W                          8U
#define OSPI_SRAM_PARTITION_CFG_THRESHOLD_M                          0x000000FFU
#define OSPI_SRAM_PARTITION_CFG_THRESHOLD_S                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IND_AHB_ADDR_TRIGGER
    Offset name:         OSPI_O_IND_AHB_ADDR_TRIGGER
    Relative address:    0x1C
    Description:         Indirect AHB Address Trigger Register
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      This is the base address that will be used by the AHB controller. When the incoming AHB read access address matches a range of addresses from this trigger address to the trigger address + 15, then the AHB request will be completed by fetching data from the Indirect Controllers SRAM.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_IND_AHB_ADDR_TRIGGER_ADDR_W                             32U
#define OSPI_IND_AHB_ADDR_TRIGGER_ADDR_M                             0xFFFFFFFFU
#define OSPI_IND_AHB_ADDR_TRIGGER_ADDR_S                             0U
#define OSPI_IND_AHB_ADDR_TRIGGER_ADDR_MINIMUM                       0x00000000U
#define OSPI_IND_AHB_ADDR_TRIGGER_ADDR_MAXIMUM                       0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMA_PERIPH_CONFIG
    Offset name:         OSPI_O_DMA_PERIPH_CONFIG
    Relative address:    0x20
    Description:         DMA Peripheral Configuration Register
    Default Value:       0x00000000

        Field:           NUM_SINGLE_REQ_BYTES
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Single Bytes: Number of bytes in a single type request on the DMA peripheral request. A programmed value of 0 represents a single byte. This should be setup before starting the indirect read or write operation. The actual number of bytes used is 2**(value in this register) which will simplify implementation.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DMA_PERIPH_CONFIG_NUM_SINGLE_REQ_BYTES_W                4U
#define OSPI_DMA_PERIPH_CONFIG_NUM_SINGLE_REQ_BYTES_M                0x0000000FU
#define OSPI_DMA_PERIPH_CONFIG_NUM_SINGLE_REQ_BYTES_S                0U
#define OSPI_DMA_PERIPH_CONFIG_NUM_SINGLE_REQ_BYTES_MINIMUM          0x00000000U
#define OSPI_DMA_PERIPH_CONFIG_NUM_SINGLE_REQ_BYTES_MAXIMUM          0x0000000FU
/*

        Field:           NUM_BURST_REQ_BYTES
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Burst Bytes: Number of bytes in a burst type request on the DMA peripheral request. A programmed value of 0 represents a single byte. This should be setup before starting the indirect read or write operation. The actual number of bytes used is 2**(value in this register) which will simplify implementation.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DMA_PERIPH_CONFIG_NUM_BURST_REQ_BYTES_W                 4U
#define OSPI_DMA_PERIPH_CONFIG_NUM_BURST_REQ_BYTES_M                 0x00000F00U
#define OSPI_DMA_PERIPH_CONFIG_NUM_BURST_REQ_BYTES_S                 8U
#define OSPI_DMA_PERIPH_CONFIG_NUM_BURST_REQ_BYTES_MINIMUM           0x00000000U
#define OSPI_DMA_PERIPH_CONFIG_NUM_BURST_REQ_BYTES_MAXIMUM           0x00000F00U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REMAP_ADDR
    Offset name:         OSPI_O_REMAP_ADDR
    Relative address:    0x24
    Description:         Remap Address Register
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      This register is used to remap an incoming AHB address to a different address used by the FLASH device.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_REMAP_ADDR_VALUE_W                                      32U
#define OSPI_REMAP_ADDR_VALUE_M                                      0xFFFFFFFFU
#define OSPI_REMAP_ADDR_VALUE_S                                      0U
#define OSPI_REMAP_ADDR_VALUE_MINIMUM                                0x00000000U
#define OSPI_REMAP_ADDR_VALUE_MAXIMUM                                0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       MODE_BIT_CONFIG
    Offset name:         OSPI_O_MODE_BIT_CONFIG
    Relative address:    0x28
    Description:         Mode Bit Configuration Register
    Default Value:       0x00000200

        Field:           MODE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     These are the 8 mode bits that are sent to the device following the address bytes if mode bit transmission has been enabled.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODE_BIT_CONFIG_MODE_W                                  8U
#define OSPI_MODE_BIT_CONFIG_MODE_M                                  0x000000FFU
#define OSPI_MODE_BIT_CONFIG_MODE_S                                  0U
#define OSPI_MODE_BIT_CONFIG_MODE_MINIMUM                            0x00000000U
#define OSPI_MODE_BIT_CONFIG_MODE_MAXIMUM                            0x000000FFU
/*

        Field:           CHUNK_SIZE
        From..to bits:   8...10
        DefaultValue:    0x2
        Access type:     read-write
        Description:     It defines size of chunk after which CRC data is expected to show up on the SPI interface for write and read data transfers.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODE_BIT_CONFIG_CHUNK_SIZE_W                            3U
#define OSPI_MODE_BIT_CONFIG_CHUNK_SIZE_M                            0x00000700U
#define OSPI_MODE_BIT_CONFIG_CHUNK_SIZE_S                            8U
#define OSPI_MODE_BIT_CONFIG_CHUNK_SIZE_MINIMUM                      0x00000000U
#define OSPI_MODE_BIT_CONFIG_CHUNK_SIZE_MAXIMUM                      0x00000700U
/*

        Field:           CRC_OUT_ENABLE
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     CRC# output enable bit When enabled, the controller expects the Flash Device to toggle CRC data on both SPI clock edges in CRC->CRC# sequence and calculates CRC compliance accordingly.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_MODE_BIT_CONFIG_CRC_OUT_ENABLE                          0x00008000U
#define OSPI_MODE_BIT_CONFIG_CRC_OUT_ENABLE_M                        0x00008000U
#define OSPI_MODE_BIT_CONFIG_CRC_OUT_ENABLE_S                        15U
#define OSPI_MODE_BIT_CONFIG_CRC_OUT_ENABLE_DISABLE                  0x00000000U
#define OSPI_MODE_BIT_CONFIG_CRC_OUT_ENABLE_ENABLE                   0x00008000U
/*

        Field:           RX_CRC_DATA_UP
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX CRC data (upper) The second CRC byte returned after RX data chunk.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_UP_W                        8U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_UP_M                        0x00FF0000U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_UP_S                        16U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_UP_MINIMUM                  0x00000000U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_UP_MAXIMUM                  0x00FF0000U
/*

        Field:           RX_CRC_DATA_LOW
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     RX CRC data (lower) The first CRC byte returned after RX data chunk.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_LOW_W                       8U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_LOW_M                       0xFF000000U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_LOW_S                       24U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_LOW_MINIMUM                 0x00000000U
#define OSPI_MODE_BIT_CONFIG_RX_CRC_DATA_LOW_MAXIMUM                 0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SRAM_FILL
    Offset name:         OSPI_O_SRAM_FILL
    Relative address:    0x2C
    Description:         SRAM Fill Register
    Default Value:       0x00000000

        Field:           SRAM_FILL_INDAC_READ
        From..to bits:   0...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SRAM Fill Level (Indirect Read Partition): Identifies the current fill level of the SRAM Indirect Read partition

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_READ_W                        16U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_READ_M                        0x0000FFFFU
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_READ_S                        0U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_READ_MINIMUM                  0x00000000U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_READ_MAXIMUM                  0x0000FFFFU
/*

        Field:           SRAM_FILL_INDAC_WRITE
        From..to bits:   16...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     SRAM Fill Level (Indirect Write Partition): Identifies the current fill level of the SRAM Indirect Write partition

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_WRITE_W                       16U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_WRITE_M                       0xFFFF0000U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_WRITE_S                       16U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_WRITE_MINIMUM                 0x00000000U
#define OSPI_SRAM_FILL_SRAM_FILL_INDAC_WRITE_MAXIMUM                 0xFFFF0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TX_THRESH
    Offset name:         OSPI_O_TX_THRESH
    Relative address:    0x30
    Description:         TX Threshold Register
    Default Value:       0x00000001

        Field:           LEVEL
        From..to bits:   0...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Defines the level at which the small TX FIFO not full interrupt is generated

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_TX_THRESH_LEVEL_W                                       5U
#define OSPI_TX_THRESH_LEVEL_M                                       0x0000001FU
#define OSPI_TX_THRESH_LEVEL_S                                       0U
#define OSPI_TX_THRESH_LEVEL_MINIMUM                                 0x00000000U
#define OSPI_TX_THRESH_LEVEL_MAXIMUM                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       RX_THRESH
    Offset name:         OSPI_O_RX_THRESH
    Relative address:    0x34
    Description:         RX Threshold Register
    Default Value:       0x00000001

        Field:           LEVEL
        From..to bits:   0...4
        DefaultValue:    0x1
        Access type:     read-write
        Description:      Defines the level at which the small RX FIFO not empty interrupt is generated

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_RX_THRESH_LEVEL_W                                       5U
#define OSPI_RX_THRESH_LEVEL_M                                       0x0000001FU
#define OSPI_RX_THRESH_LEVEL_S                                       0U
#define OSPI_RX_THRESH_LEVEL_MINIMUM                                 0x00000000U
#define OSPI_RX_THRESH_LEVEL_MAXIMUM                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       WRITE_COMPLETION_CTRL
    Offset name:         OSPI_O_WRITE_COMPLETION_CTRL
    Relative address:    0x38
    Description:         Write Completion Control Register: This register defines how the controller will poll the device following a write transfer
    Default Value:       0x00040005

        Field:           OPCODE
        From..to bits:   0...7
        DefaultValue:    0x5
        Access type:     read-write
        Description:     Defines the opcode that should be issued by the controller when it is automatically polling for device program completion. This command is issued followed all device write operations. By default, this will poll the standard device STATUS register using opcode 0x05

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_WRITE_COMPLETION_CTRL_OPCODE_W                          8U
#define OSPI_WRITE_COMPLETION_CTRL_OPCODE_M                          0x000000FFU
#define OSPI_WRITE_COMPLETION_CTRL_OPCODE_S                          0U
#define OSPI_WRITE_COMPLETION_CTRL_OPCODE_MINIMUM                    0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_OPCODE_MAXIMUM                    0x000000FFU
/*

        Field:           POLLING_BIT_INDEX
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines the bit index that should be polled. A value of 010 means that bit 2 of the returned data will be polled for.A value of 111 means that bit 7 of the returned data will be polled for.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_BIT_INDEX_W               3U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_BIT_INDEX_M               0x00000700U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_BIT_INDEX_S               8U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_BIT_INDEX_MINIMUM         0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_BIT_INDEX_MAXIMUM         0x00000700U
/*

        Field:           POLLING_ADDR_EN
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enables address phase of auto-polling (Read Status) command.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_ADDR_EN                   0x00000800U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_ADDR_EN_M                 0x00000800U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_ADDR_EN_S                 11U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_ADDR_EN_DISABLE           0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_ADDR_EN_ENABLE            0x00000800U
/*

        Field:           POLLING_POLARITY
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines the polling polarity. If '1', then the write transfer to the device will be complete if the polled bit is equal to '1'. If '0', then the write transfer to the device will be complete if the polled bit is equal to '0'.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_POLARITY                  0x00002000U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_POLARITY_M                0x00002000U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_POLARITY_S                13U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_POLARITY_DISABLE          0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLLING_POLARITY_ENABLE           0x00002000U
/*

        Field:           DISABLE_POLLING
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This switches off the automatic polling function

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WRITE_COMPLETION_CTRL_DISABLE_POLLING                   0x00004000U
#define OSPI_WRITE_COMPLETION_CTRL_DISABLE_POLLING_M                 0x00004000U
#define OSPI_WRITE_COMPLETION_CTRL_DISABLE_POLLING_S                 14U
#define OSPI_WRITE_COMPLETION_CTRL_DISABLE_POLLING_DISABLE           0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_DISABLE_POLLING_ENABLE            0x00004000U
/*

        Field:           ENABLE_POLLING_EXP
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Set to '1' for enabling auto-polling expiration.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WRITE_COMPLETION_CTRL_ENABLE_POLLING_EXP                0x00008000U
#define OSPI_WRITE_COMPLETION_CTRL_ENABLE_POLLING_EXP_M              0x00008000U
#define OSPI_WRITE_COMPLETION_CTRL_ENABLE_POLLING_EXP_S              15U
#define OSPI_WRITE_COMPLETION_CTRL_ENABLE_POLLING_EXP_DISABLE        0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_ENABLE_POLLING_EXP_ENABLE         0x00008000U
/*

        Field:           POLL_COUNT
        From..to bits:   16...23
        DefaultValue:    0x4
        Access type:     read-write
        Description:     Defines the number of times the controller should expect to see a true result from the polling in successive reads of the device register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_WRITE_COMPLETION_CTRL_POLL_COUNT_W                      8U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_COUNT_M                      0x00FF0000U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_COUNT_S                      16U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_COUNT_MINIMUM                0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_COUNT_MAXIMUM                0x00FF0000U
/*

        Field:           POLL_REP_DELAY
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Defines additional delay for maintain Chip Select de-asserted during auto-polling phase

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_WRITE_COMPLETION_CTRL_POLL_REP_DELAY_W                  8U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_REP_DELAY_M                  0xFF000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_REP_DELAY_S                  24U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_REP_DELAY_MINIMUM            0x00000000U
#define OSPI_WRITE_COMPLETION_CTRL_POLL_REP_DELAY_MAXIMUM            0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       NO_OF_POLLS_BEF_EXP
    Offset name:         OSPI_O_NO_OF_POLLS_BEF_EXP
    Relative address:    0x3C
    Description:         Polling Expiration Register
    Default Value:       0xFFFFFFFF

        Field:           NO_OF_POLLS_BEF_EXP
        From..to bits:   0...31
        DefaultValue:    0xFFFFFFFF
        Access type:     read-write
        Description:     Number of polls cycles before expiration

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_NO_OF_POLLS_BEF_EXP_NO_OF_POLLS_BEF_EXP_W               32U
#define OSPI_NO_OF_POLLS_BEF_EXP_NO_OF_POLLS_BEF_EXP_M               0xFFFFFFFFU
#define OSPI_NO_OF_POLLS_BEF_EXP_NO_OF_POLLS_BEF_EXP_S               0U
#define OSPI_NO_OF_POLLS_BEF_EXP_NO_OF_POLLS_BEF_EXP_MINIMUM         0x00000000U
#define OSPI_NO_OF_POLLS_BEF_EXP_NO_OF_POLLS_BEF_EXP_MAXIMUM         0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_STATUS
    Offset name:         OSPI_O_IRQ_STATUS
    Relative address:    0x40
    Description:         Interrupt Status Register: The status fields in this register are set when the described event occurs and the interrupt is enabled in the mask register. When any of these bit fields are set, the interrupt output is asserted high. The fields are each cleared by writing a 1 to the field. Note that bit fields 6 thru 10 are only valid when legacy SPI mode is active.
    Default Value:       0x00000000

        Field:           MODE_M_FAIL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mode M Failure: Mode M failure indicates the voltage on pin n_ss_in is inconsistent with the SPI mode. Set =1 if n_ss_in is low in master mode (multi-master contention). These conditions will clear the spi_enable bit and disable the SPI. This bit is reset only by a system reset and cleared only when this register is read.

        ENUMs:
            DISABLE:                     no mode fault has been detected 1 : a mode fault has occurred
            ENABLE:                      a mode fault has occurred
*/
#define OSPI_IRQ_STATUS_MODE_M_FAIL                                  0x00000001U
#define OSPI_IRQ_STATUS_MODE_M_FAIL_M                                0x00000001U
#define OSPI_IRQ_STATUS_MODE_M_FAIL_S                                0U
#define OSPI_IRQ_STATUS_MODE_M_FAIL_DISABLE                          0x00000000U
#define OSPI_IRQ_STATUS_MODE_M_FAIL_ENABLE                           0x00000001U
/*

        Field:           UNDERFLOW_DET
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Underflow Detected:

        ENUMs:
            DISABLE:                     no underflow has been detected 1 : underflow is detected and an attempt to transfer data is made when the small TX FIFO is empty. This may occur when AHB write data is being supplied too slowly to keep up with the requested write operation This bit is reset only by a system reset and cleared only when the register is read.
            ENABLE:                      underflow is detected and an attempt to transfer data is made when the small TX FIFO is empty. This may occur when AHB write data is being supplied too slowly to keep up with the requested write operation This bit is reset only by a system reset and cleared only when the register is read.
*/
#define OSPI_IRQ_STATUS_UNDERFLOW_DET                                0x00000002U
#define OSPI_IRQ_STATUS_UNDERFLOW_DET_M                              0x00000002U
#define OSPI_IRQ_STATUS_UNDERFLOW_DET_S                              1U
#define OSPI_IRQ_STATUS_UNDERFLOW_DET_DISABLE                        0x00000000U
#define OSPI_IRQ_STATUS_UNDERFLOW_DET_ENABLE                         0x00000002U
/*

        Field:           INDIRECT_OP_DONE
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Operation Complete: Controller has completed last triggered indirect operation

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_INDIRECT_OP_DONE                             0x00000004U
#define OSPI_IRQ_STATUS_INDIRECT_OP_DONE_M                           0x00000004U
#define OSPI_IRQ_STATUS_INDIRECT_OP_DONE_S                           2U
#define OSPI_IRQ_STATUS_INDIRECT_OP_DONE_DISABLE                     0x00000000U
#define OSPI_IRQ_STATUS_INDIRECT_OP_DONE_ENABLE                      0x00000004U
/*

        Field:           INDIRECT_TRANSFER_REJECT
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Indirect operation was requested but could not be accepted. Two indirect operations already in storage.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_INDIRECT_TRANSFER_REJECT                     0x00000008U
#define OSPI_IRQ_STATUS_INDIRECT_TRANSFER_REJECT_M                   0x00000008U
#define OSPI_IRQ_STATUS_INDIRECT_TRANSFER_REJECT_S                   3U
#define OSPI_IRQ_STATUS_INDIRECT_TRANSFER_REJECT_DISABLE             0x00000000U
#define OSPI_IRQ_STATUS_INDIRECT_TRANSFER_REJECT_ENABLE              0x00000008U
/*

        Field:           PROT_WR_ATTEMPT
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write to protected area was attempted and rejected.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_PROT_WR_ATTEMPT                              0x00000010U
#define OSPI_IRQ_STATUS_PROT_WR_ATTEMPT_M                            0x00000010U
#define OSPI_IRQ_STATUS_PROT_WR_ATTEMPT_S                            4U
#define OSPI_IRQ_STATUS_PROT_WR_ATTEMPT_DISABLE                      0x00000000U
#define OSPI_IRQ_STATUS_PROT_WR_ATTEMPT_ENABLE                       0x00000010U
/*

        Field:           ILLEGAL_ACCESS_DET
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Illegal AHB access has been detected. AHB wrapping bursts and the use of SPLIT/RETRY accesses will cause this error interrupt to trigger.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_ILLEGAL_ACCESS_DET                           0x00000020U
#define OSPI_IRQ_STATUS_ILLEGAL_ACCESS_DET_M                         0x00000020U
#define OSPI_IRQ_STATUS_ILLEGAL_ACCESS_DET_S                         5U
#define OSPI_IRQ_STATUS_ILLEGAL_ACCESS_DET_DISABLE                   0x00000000U
#define OSPI_IRQ_STATUS_ILLEGAL_ACCESS_DET_ENABLE                    0x00000020U
/*

        Field:           INDIRECT_XFER_LEVEL_BREACH
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Transfer Watermark Level Breached

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_INDIRECT_XFER_LEVEL_BREACH                   0x00000040U
#define OSPI_IRQ_STATUS_INDIRECT_XFER_LEVEL_BREACH_M                 0x00000040U
#define OSPI_IRQ_STATUS_INDIRECT_XFER_LEVEL_BREACH_S                 6U
#define OSPI_IRQ_STATUS_INDIRECT_XFER_LEVEL_BREACH_DISABLE           0x00000000U
#define OSPI_IRQ_STATUS_INDIRECT_XFER_LEVEL_BREACH_ENABLE            0x00000040U
/*

        Field:           RECV_OVERFLOW
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive Overflow: This should only occur in Legacy SPI mode. Set if an attempt is made to push the RX FIFO when it is full. This bit is reset only by a system reset and cleared only when this register is read. If a new push to the RX FIFO occurs coincident with a register read this flag will remain set.

        ENUMs:
            DISABLE:                     no overflow has been detected. 1 : an overflow has occurred.
            ENABLE:                      an overflow has occurred.
*/
#define OSPI_IRQ_STATUS_RECV_OVERFLOW                                0x00000080U
#define OSPI_IRQ_STATUS_RECV_OVERFLOW_M                              0x00000080U
#define OSPI_IRQ_STATUS_RECV_OVERFLOW_S                              7U
#define OSPI_IRQ_STATUS_RECV_OVERFLOW_DISABLE                        0x00000000U
#define OSPI_IRQ_STATUS_RECV_OVERFLOW_ENABLE                         0x00000080U
/*

        Field:           TX_FIFO_NOT_FULL
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small TX FIFO not full: Current FIFO status can be ignored in non-SPI legacy mode

        ENUMs:
            DISABLE:                     FIFO has >= THRESHOLD entries, 1 : FIFO has less than THRESHOLD entries
            ENABLE:                      FIFO has less than THRESHOLD entries
*/
#define OSPI_IRQ_STATUS_TX_FIFO_NOT_FULL                             0x00000100U
#define OSPI_IRQ_STATUS_TX_FIFO_NOT_FULL_M                           0x00000100U
#define OSPI_IRQ_STATUS_TX_FIFO_NOT_FULL_S                           8U
#define OSPI_IRQ_STATUS_TX_FIFO_NOT_FULL_DISABLE                     0x00000000U
#define OSPI_IRQ_STATUS_TX_FIFO_NOT_FULL_ENABLE                      0x00000100U
/*

        Field:           TX_FIFO_FULL
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small TX FIFO full: Current FIFO status can be ignored in non-SPI legacy mode

        ENUMs:
            DISABLE:                     FIFO is not full, 1 : FIFO is full
            ENABLE:                      FIFO is full
*/
#define OSPI_IRQ_STATUS_TX_FIFO_FULL                                 0x00000200U
#define OSPI_IRQ_STATUS_TX_FIFO_FULL_M                               0x00000200U
#define OSPI_IRQ_STATUS_TX_FIFO_FULL_S                               9U
#define OSPI_IRQ_STATUS_TX_FIFO_FULL_DISABLE                         0x00000000U
#define OSPI_IRQ_STATUS_TX_FIFO_FULL_ENABLE                          0x00000200U
/*

        Field:           RX_FIFO_NOT_EMPTY
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small RX FIFO not empty: Current FIFO status can be ignored in non-SPI legacy mode

        ENUMs:
            DISABLE:                     FIFO has less than RX THRESHOLD entries, 1 : FIFO has >= THRESHOLD entries
            ENABLE:                      FIFO has >= THRESHOLD entries
*/
#define OSPI_IRQ_STATUS_RX_FIFO_NOT_EMPTY                            0x00000400U
#define OSPI_IRQ_STATUS_RX_FIFO_NOT_EMPTY_M                          0x00000400U
#define OSPI_IRQ_STATUS_RX_FIFO_NOT_EMPTY_S                          10U
#define OSPI_IRQ_STATUS_RX_FIFO_NOT_EMPTY_DISABLE                    0x00000000U
#define OSPI_IRQ_STATUS_RX_FIFO_NOT_EMPTY_ENABLE                     0x00000400U
/*

        Field:           RX_FIFO_FULL
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small RX FIFO full: Current FIFO status can be ignored in non-SPI legacy mode

        ENUMs:
            DISABLE:                     FIFO is not full 1 : FIFO is full
            ENABLE:                      FIFO is full
*/
#define OSPI_IRQ_STATUS_RX_FIFO_FULL                                 0x00000800U
#define OSPI_IRQ_STATUS_RX_FIFO_FULL_M                               0x00000800U
#define OSPI_IRQ_STATUS_RX_FIFO_FULL_S                               11U
#define OSPI_IRQ_STATUS_RX_FIFO_FULL_DISABLE                         0x00000000U
#define OSPI_IRQ_STATUS_RX_FIFO_FULL_ENABLE                          0x00000800U
/*

        Field:           INDRD_SRAM_FULL
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Read Partition overflow: Indirect Read Partition of SRAM is full and unable to immediately complete indirect operation

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_INDRD_SRAM_FULL                              0x00001000U
#define OSPI_IRQ_STATUS_INDRD_SRAM_FULL_M                            0x00001000U
#define OSPI_IRQ_STATUS_INDRD_SRAM_FULL_S                            12U
#define OSPI_IRQ_STATUS_INDRD_SRAM_FULL_DISABLE                      0x00000000U
#define OSPI_IRQ_STATUS_INDRD_SRAM_FULL_ENABLE                       0x00001000U
/*

        Field:           POLL_EXP_INT
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:      The maximum number of programmed polls cycles is expired

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_POLL_EXP_INT                                 0x00002000U
#define OSPI_IRQ_STATUS_POLL_EXP_INT_M                               0x00002000U
#define OSPI_IRQ_STATUS_POLL_EXP_INT_S                               13U
#define OSPI_IRQ_STATUS_POLL_EXP_INT_DISABLE                         0x00000000U
#define OSPI_IRQ_STATUS_POLL_EXP_INT_ENABLE                          0x00002000U
/*

        Field:           STIG_REQ_INT
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:      The controller is ready for getting another STIG request.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_STIG_REQ_INT                                 0x00004000U
#define OSPI_IRQ_STATUS_STIG_REQ_INT_M                               0x00004000U
#define OSPI_IRQ_STATUS_STIG_REQ_INT_S                               14U
#define OSPI_IRQ_STATUS_STIG_REQ_INT_DISABLE                         0x00000000U
#define OSPI_IRQ_STATUS_STIG_REQ_INT_ENABLE                          0x00004000U
/*

        Field:           RX_CRC_DATA_ERR
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX CRC data error CRC data from Flash Device does not correspond to the one dynamically calculated by the controller.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_RX_CRC_DATA_ERR                              0x00010000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_ERR_M                            0x00010000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_ERR_S                            16U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_ERR_DISABLE                      0x00000000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_ERR_ENABLE                       0x00010000U
/*

        Field:           RX_CRC_DATA_VAL
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX CRC data valid New RX CRC data was captured from Flash Device

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_RX_CRC_DATA_VAL                              0x00020000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_VAL_M                            0x00020000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_VAL_S                            17U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_VAL_DISABLE                      0x00000000U
#define OSPI_IRQ_STATUS_RX_CRC_DATA_VAL_ENABLE                       0x00020000U
/*

        Field:           TX_CRC_CHUNK_BRK
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX CRC chunk was broken This interrupt informs the system that program page SPI transfer was discontinued somewhere inside the chunk.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_TX_CRC_CHUNK_BRK                             0x00040000U
#define OSPI_IRQ_STATUS_TX_CRC_CHUNK_BRK_M                           0x00040000U
#define OSPI_IRQ_STATUS_TX_CRC_CHUNK_BRK_S                           18U
#define OSPI_IRQ_STATUS_TX_CRC_CHUNK_BRK_DISABLE                     0x00000000U
#define OSPI_IRQ_STATUS_TX_CRC_CHUNK_BRK_ENABLE                      0x00040000U
/*

        Field:           ECC_FAIL
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ECC failure This interrupt informs the system that Flash Device reported ECC error.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_STATUS_ECC_FAIL                                     0x00080000U
#define OSPI_IRQ_STATUS_ECC_FAIL_M                                   0x00080000U
#define OSPI_IRQ_STATUS_ECC_FAIL_S                                   19U
#define OSPI_IRQ_STATUS_ECC_FAIL_DISABLE                             0x00000000U
#define OSPI_IRQ_STATUS_ECC_FAIL_ENABLE                              0x00080000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_MASK
    Offset name:         OSPI_O_IRQ_MASK
    Relative address:    0x44
    Description:         Interrupt Mask:  0 : the interrupt for the corresponding interrupt status register bit is disabled.
                         1 : the interrupt for the corresponding interrupt status register bit is enabled.
    Default Value:       0x00000000

        Field:           MODE_M_FAIL_MASK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mode M Failure Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_MODE_M_FAIL_MASK                               0x00000001U
#define OSPI_IRQ_MASK_MODE_M_FAIL_MASK_M                             0x00000001U
#define OSPI_IRQ_MASK_MODE_M_FAIL_MASK_S                             0U
#define OSPI_IRQ_MASK_MODE_M_FAIL_MASK_DISABLE                       0x00000000U
#define OSPI_IRQ_MASK_MODE_M_FAIL_MASK_ENABLE                        0x00000001U
/*

        Field:           UNDERFLOW_DET_MASK
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Underflow Detected Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_UNDERFLOW_DET_MASK                             0x00000002U
#define OSPI_IRQ_MASK_UNDERFLOW_DET_MASK_M                           0x00000002U
#define OSPI_IRQ_MASK_UNDERFLOW_DET_MASK_S                           1U
#define OSPI_IRQ_MASK_UNDERFLOW_DET_MASK_DISABLE                     0x00000000U
#define OSPI_IRQ_MASK_UNDERFLOW_DET_MASK_ENABLE                      0x00000002U
/*

        Field:           INDIRECT_OP_DONE_MASK
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Complete Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_INDIRECT_OP_DONE_MASK                          0x00000004U
#define OSPI_IRQ_MASK_INDIRECT_OP_DONE_MASK_M                        0x00000004U
#define OSPI_IRQ_MASK_INDIRECT_OP_DONE_MASK_S                        2U
#define OSPI_IRQ_MASK_INDIRECT_OP_DONE_MASK_DISABLE                  0x00000000U
#define OSPI_IRQ_MASK_INDIRECT_OP_DONE_MASK_ENABLE                   0x00000004U
/*

        Field:           INDIRECT_TRANSFER_REJECT_MASK
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Read Reject Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_INDIRECT_TRANSFER_REJECT_MASK                  0x00000008U
#define OSPI_IRQ_MASK_INDIRECT_TRANSFER_REJECT_MASK_M                0x00000008U
#define OSPI_IRQ_MASK_INDIRECT_TRANSFER_REJECT_MASK_S                3U
#define OSPI_IRQ_MASK_INDIRECT_TRANSFER_REJECT_MASK_DISABLE          0x00000000U
#define OSPI_IRQ_MASK_INDIRECT_TRANSFER_REJECT_MASK_ENABLE           0x00000008U
/*

        Field:           PROT_WR_ATTEMPT_MASK
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Protected Area Write Attempt Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_PROT_WR_ATTEMPT_MASK                           0x00000010U
#define OSPI_IRQ_MASK_PROT_WR_ATTEMPT_MASK_M                         0x00000010U
#define OSPI_IRQ_MASK_PROT_WR_ATTEMPT_MASK_S                         4U
#define OSPI_IRQ_MASK_PROT_WR_ATTEMPT_MASK_DISABLE                   0x00000000U
#define OSPI_IRQ_MASK_PROT_WR_ATTEMPT_MASK_ENABLE                    0x00000010U
/*

        Field:           ILLEGAL_ACCESS_DET_MASK
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Illegal Access Detected Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_ILLEGAL_ACCESS_DET_MASK                        0x00000020U
#define OSPI_IRQ_MASK_ILLEGAL_ACCESS_DET_MASK_M                      0x00000020U
#define OSPI_IRQ_MASK_ILLEGAL_ACCESS_DET_MASK_S                      5U
#define OSPI_IRQ_MASK_ILLEGAL_ACCESS_DET_MASK_DISABLE                0x00000000U
#define OSPI_IRQ_MASK_ILLEGAL_ACCESS_DET_MASK_ENABLE                 0x00000020U
/*

        Field:           INDIRECT_XFER_LEVEL_BREACH_MASK
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transfer Watermark Breach Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_INDIRECT_XFER_LEVEL_BREACH_MASK                0x00000040U
#define OSPI_IRQ_MASK_INDIRECT_XFER_LEVEL_BREACH_MASK_M              0x00000040U
#define OSPI_IRQ_MASK_INDIRECT_XFER_LEVEL_BREACH_MASK_S              6U
#define OSPI_IRQ_MASK_INDIRECT_XFER_LEVEL_BREACH_MASK_DISABLE        0x00000000U
#define OSPI_IRQ_MASK_INDIRECT_XFER_LEVEL_BREACH_MASK_ENABLE         0x00000040U
/*

        Field:           RECV_OVERFLOW_MASK
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Receive Overflow Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_RECV_OVERFLOW_MASK                             0x00000080U
#define OSPI_IRQ_MASK_RECV_OVERFLOW_MASK_M                           0x00000080U
#define OSPI_IRQ_MASK_RECV_OVERFLOW_MASK_S                           7U
#define OSPI_IRQ_MASK_RECV_OVERFLOW_MASK_DISABLE                     0x00000000U
#define OSPI_IRQ_MASK_RECV_OVERFLOW_MASK_ENABLE                      0x00000080U
/*

        Field:           TX_FIFO_NOT_FULL_MASK
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small TX FIFO not full Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_TX_FIFO_NOT_FULL_MASK                          0x00000100U
#define OSPI_IRQ_MASK_TX_FIFO_NOT_FULL_MASK_M                        0x00000100U
#define OSPI_IRQ_MASK_TX_FIFO_NOT_FULL_MASK_S                        8U
#define OSPI_IRQ_MASK_TX_FIFO_NOT_FULL_MASK_DISABLE                  0x00000000U
#define OSPI_IRQ_MASK_TX_FIFO_NOT_FULL_MASK_ENABLE                   0x00000100U
/*

        Field:           TX_FIFO_FULL_MASK
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small TX FIFO full Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_TX_FIFO_FULL_MASK                              0x00000200U
#define OSPI_IRQ_MASK_TX_FIFO_FULL_MASK_M                            0x00000200U
#define OSPI_IRQ_MASK_TX_FIFO_FULL_MASK_S                            9U
#define OSPI_IRQ_MASK_TX_FIFO_FULL_MASK_DISABLE                      0x00000000U
#define OSPI_IRQ_MASK_TX_FIFO_FULL_MASK_ENABLE                       0x00000200U
/*

        Field:           RX_FIFO_NOT_EMPTY_MASK
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small RX FIFO not empty Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_RX_FIFO_NOT_EMPTY_MASK                         0x00000400U
#define OSPI_IRQ_MASK_RX_FIFO_NOT_EMPTY_MASK_M                       0x00000400U
#define OSPI_IRQ_MASK_RX_FIFO_NOT_EMPTY_MASK_S                       10U
#define OSPI_IRQ_MASK_RX_FIFO_NOT_EMPTY_MASK_DISABLE                 0x00000000U
#define OSPI_IRQ_MASK_RX_FIFO_NOT_EMPTY_MASK_ENABLE                  0x00000400U
/*

        Field:           RX_FIFO_FULL_MASK
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Small RX FIFO full Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_RX_FIFO_FULL_MASK                              0x00000800U
#define OSPI_IRQ_MASK_RX_FIFO_FULL_MASK_M                            0x00000800U
#define OSPI_IRQ_MASK_RX_FIFO_FULL_MASK_S                            11U
#define OSPI_IRQ_MASK_RX_FIFO_FULL_MASK_DISABLE                      0x00000000U
#define OSPI_IRQ_MASK_RX_FIFO_FULL_MASK_ENABLE                       0x00000800U
/*

        Field:           INDRD_SRAM_FULL_MASK
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Read Partition overflow mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_INDRD_SRAM_FULL_MASK                           0x00001000U
#define OSPI_IRQ_MASK_INDRD_SRAM_FULL_MASK_M                         0x00001000U
#define OSPI_IRQ_MASK_INDRD_SRAM_FULL_MASK_S                         12U
#define OSPI_IRQ_MASK_INDRD_SRAM_FULL_MASK_DISABLE                   0x00000000U
#define OSPI_IRQ_MASK_INDRD_SRAM_FULL_MASK_ENABLE                    0x00001000U
/*

        Field:           POLL_EXP_INT_MASK
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Polling expiration detected Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_POLL_EXP_INT_MASK                              0x00002000U
#define OSPI_IRQ_MASK_POLL_EXP_INT_MASK_M                            0x00002000U
#define OSPI_IRQ_MASK_POLL_EXP_INT_MASK_S                            13U
#define OSPI_IRQ_MASK_POLL_EXP_INT_MASK_DISABLE                      0x00000000U
#define OSPI_IRQ_MASK_POLL_EXP_INT_MASK_ENABLE                       0x00002000U
/*

        Field:           STIG_REQ_MASK
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     STIG request completion Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_STIG_REQ_MASK                                  0x00004000U
#define OSPI_IRQ_MASK_STIG_REQ_MASK_M                                0x00004000U
#define OSPI_IRQ_MASK_STIG_REQ_MASK_S                                14U
#define OSPI_IRQ_MASK_STIG_REQ_MASK_DISABLE                          0x00000000U
#define OSPI_IRQ_MASK_STIG_REQ_MASK_ENABLE                           0x00004000U
/*

        Field:           RX_CRC_DATA_ERR_MASK
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX CRC data error Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_RX_CRC_DATA_ERR_MASK                           0x00010000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_ERR_MASK_M                         0x00010000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_ERR_MASK_S                         16U
#define OSPI_IRQ_MASK_RX_CRC_DATA_ERR_MASK_DISABLE                   0x00000000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_ERR_MASK_ENABLE                    0x00010000U
/*

        Field:           RX_CRC_DATA_VAL_MASK
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX CRC data valid Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_RX_CRC_DATA_VAL_MASK                           0x00020000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_VAL_MASK_M                         0x00020000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_VAL_MASK_S                         17U
#define OSPI_IRQ_MASK_RX_CRC_DATA_VAL_MASK_DISABLE                   0x00000000U
#define OSPI_IRQ_MASK_RX_CRC_DATA_VAL_MASK_ENABLE                    0x00020000U
/*

        Field:           TX_CRC_CHUNK_BRK_MASK
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX CRC chunk was broken Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_TX_CRC_CHUNK_BRK_MASK                          0x00040000U
#define OSPI_IRQ_MASK_TX_CRC_CHUNK_BRK_MASK_M                        0x00040000U
#define OSPI_IRQ_MASK_TX_CRC_CHUNK_BRK_MASK_S                        18U
#define OSPI_IRQ_MASK_TX_CRC_CHUNK_BRK_MASK_DISABLE                  0x00000000U
#define OSPI_IRQ_MASK_TX_CRC_CHUNK_BRK_MASK_ENABLE                   0x00040000U
/*

        Field:           ECC_FAIL_MASK
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ECC failure Mask

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_IRQ_MASK_ECC_FAIL_MASK                                  0x00080000U
#define OSPI_IRQ_MASK_ECC_FAIL_MASK_M                                0x00080000U
#define OSPI_IRQ_MASK_ECC_FAIL_MASK_S                                19U
#define OSPI_IRQ_MASK_ECC_FAIL_MASK_DISABLE                          0x00000000U
#define OSPI_IRQ_MASK_ECC_FAIL_MASK_ENABLE                           0x00080000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOWER_WR_PROT
    Offset name:         OSPI_O_LOWER_WR_PROT
    Relative address:    0x50
    Description:         Lower Write Protection Register
    Default Value:       0x00000000

        Field:           SUBSECTOR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      The block number that defines the lower block in the range of blocks that is to be locked from writing. The definition of a block in terms of number of bytes is programmable via the Device Size Configuration register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_LOWER_WR_PROT_SUBSECTOR_W                               32U
#define OSPI_LOWER_WR_PROT_SUBSECTOR_M                               0xFFFFFFFFU
#define OSPI_LOWER_WR_PROT_SUBSECTOR_S                               0U
#define OSPI_LOWER_WR_PROT_SUBSECTOR_MINIMUM                         0x00000000U
#define OSPI_LOWER_WR_PROT_SUBSECTOR_MAXIMUM                         0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       UPPER_WR_PROT
    Offset name:         OSPI_O_UPPER_WR_PROT
    Relative address:    0x54
    Description:         Upper Write Protection Register
    Default Value:       0x00000000

        Field:           SUBSECTOR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      The block number that defines the upper block in the range of blocks that is to be locked from writing. The definition of a block in terms of number of bytes is programmable via the Device Size Configuration register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_UPPER_WR_PROT_SUBSECTOR_W                               32U
#define OSPI_UPPER_WR_PROT_SUBSECTOR_M                               0xFFFFFFFFU
#define OSPI_UPPER_WR_PROT_SUBSECTOR_S                               0U
#define OSPI_UPPER_WR_PROT_SUBSECTOR_MINIMUM                         0x00000000U
#define OSPI_UPPER_WR_PROT_SUBSECTOR_MAXIMUM                         0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       WR_PROT_CTRL
    Offset name:         OSPI_O_WR_PROT_CTRL
    Relative address:    0x58
    Description:         Write Protection Control Register
    Default Value:       0x00000000

        Field:           INV
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write Protection Inversion Bit: When set to 1, the protection region defined in the lower and upper write protection registers is inverted meaning it is the region that the system is permitted to write to. When set to 0, the protection region defined in the lower and upper write protection registers is the region that the system is not permitted to write to.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WR_PROT_CTRL_INV                                        0x00000001U
#define OSPI_WR_PROT_CTRL_INV_M                                      0x00000001U
#define OSPI_WR_PROT_CTRL_INV_S                                      0U
#define OSPI_WR_PROT_CTRL_INV_DISABLE                                0x00000000U
#define OSPI_WR_PROT_CTRL_INV_ENABLE                                 0x00000001U
/*

        Field:           ENB
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write Protection Enable Bit: When set to 1, any AHB write access with an address within the protection region defined in the lower and upper write protection registers is rejected. An AHB error response is generated and an interrupt source triggered. When set to 0, the protection region is disabled.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_WR_PROT_CTRL_ENB                                        0x00000002U
#define OSPI_WR_PROT_CTRL_ENB_M                                      0x00000002U
#define OSPI_WR_PROT_CTRL_ENB_S                                      1U
#define OSPI_WR_PROT_CTRL_ENB_DISABLE                                0x00000000U
#define OSPI_WR_PROT_CTRL_ENB_ENABLE                                 0x00000002U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_READ_XFER_CTRL
    Offset name:         OSPI_O_INDIRECT_READ_XFER_CTRL
    Relative address:    0x60
    Description:         Indirect Read Transfer Control Register
    Default Value:       0x00000000

        Field:           START
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Start Indirect Read: Writing a 1 to this bit will trigger an indirect read operation. The assumption is that the indirect start address and the indirect number of bytes register is setup before triggering the indirect read operation.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_START                           0x00000001U
#define OSPI_INDIRECT_READ_XFER_CTRL_START_M                         0x00000001U
#define OSPI_INDIRECT_READ_XFER_CTRL_START_S                         0U
#define OSPI_INDIRECT_READ_XFER_CTRL_START_DISABLE                   0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_START_ENABLE                    0x00000001U
/*

        Field:           CANCEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Cancel Indirect Read: Writing a 1 to this bit will cancel all ongoing indirect read operations.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_CANCEL                          0x00000002U
#define OSPI_INDIRECT_READ_XFER_CTRL_CANCEL_M                        0x00000002U
#define OSPI_INDIRECT_READ_XFER_CTRL_CANCEL_S                        1U
#define OSPI_INDIRECT_READ_XFER_CTRL_CANCEL_DISABLE                  0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_CANCEL_ENABLE                   0x00000002U
/*

        Field:           RD_STATUS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indirect Read Status: Indirect read operation in progress (status)

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_STATUS                       0x00000004U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_STATUS_M                     0x00000004U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_STATUS_S                     2U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_STATUS_DISABLE               0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_STATUS_ENABLE                0x00000004U
/*

        Field:           SRAM_FULL
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SRAM Full: SRAM full and unable to immediately complete an indirect operation. Write a 1 to this field to clear it.\"; indirect operation (status)

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_SRAM_FULL                       0x00000008U
#define OSPI_INDIRECT_READ_XFER_CTRL_SRAM_FULL_M                     0x00000008U
#define OSPI_INDIRECT_READ_XFER_CTRL_SRAM_FULL_S                     3U
#define OSPI_INDIRECT_READ_XFER_CTRL_SRAM_FULL_DISABLE               0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_SRAM_FULL_ENABLE                0x00000008U
/*

        Field:           RD_QUEUED
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Two indirect read operations have been queued

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_QUEUED                       0x00000010U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_QUEUED_M                     0x00000010U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_QUEUED_S                     4U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_QUEUED_DISABLE               0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_RD_QUEUED_ENABLE                0x00000010U
/*

        Field:           IND_OPS_DONE_STATUS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Completion Status: This field is set to 1 when an indirect operation has completed. Write a 1 to this field to clear it.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_IND_OPS_DONE_STATUS             0x00000020U
#define OSPI_INDIRECT_READ_XFER_CTRL_IND_OPS_DONE_STATUS_M           0x00000020U
#define OSPI_INDIRECT_READ_XFER_CTRL_IND_OPS_DONE_STATUS_S           5U
#define OSPI_INDIRECT_READ_XFER_CTRL_IND_OPS_DONE_STATUS_DISABLE     0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_IND_OPS_DONE_STATUS_ENABLE      0x00000020U
/*

        Field:           NUM_IND_OPS_DONE
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field contains the number of indirect operations which have been completed. This is used in conjunction with the indirect completion status field (bit 5). It is incremented by hardware when an indirect operation has completed. Write a 1 to bit 5 of this register to decrement it.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_READ_XFER_CTRL_NUM_IND_OPS_DONE_W              2U
#define OSPI_INDIRECT_READ_XFER_CTRL_NUM_IND_OPS_DONE_M              0x000000C0U
#define OSPI_INDIRECT_READ_XFER_CTRL_NUM_IND_OPS_DONE_S              6U
#define OSPI_INDIRECT_READ_XFER_CTRL_NUM_IND_OPS_DONE_MINIMUM        0x00000000U
#define OSPI_INDIRECT_READ_XFER_CTRL_NUM_IND_OPS_DONE_MAXIMUM        0x000000C0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_READ_XFER_WATERMARK
    Offset name:         OSPI_O_INDIRECT_READ_XFER_WATERMARK
    Relative address:    0x64
    Description:         Indirect Read Transfer Watermark Register
    Default Value:       0x00000000

        Field:           LEVEL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Watermark Value: This represents the minimum fill level of the SRAM before a DMA peripheral access is permitted. When the SRAM fill level passes the watermark, an interrupt is also generated. This field can be disabled by writing a value of all zeroes.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_READ_XFER_WATERMARK_LEVEL_W                    32U
#define OSPI_INDIRECT_READ_XFER_WATERMARK_LEVEL_M                    0xFFFFFFFFU
#define OSPI_INDIRECT_READ_XFER_WATERMARK_LEVEL_S                    0U
#define OSPI_INDIRECT_READ_XFER_WATERMARK_LEVEL_MINIMUM              0x00000000U
#define OSPI_INDIRECT_READ_XFER_WATERMARK_LEVEL_MAXIMUM              0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_READ_XFER_START
    Offset name:         OSPI_O_INDIRECT_READ_XFER_START
    Relative address:    0x68
    Description:         Indirect Read Transfer Start Address Register
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      This is the start address from which the indirect access will commence its READ operation.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_READ_XFER_START_ADDR_W                         32U
#define OSPI_INDIRECT_READ_XFER_START_ADDR_M                         0xFFFFFFFFU
#define OSPI_INDIRECT_READ_XFER_START_ADDR_S                         0U
#define OSPI_INDIRECT_READ_XFER_START_ADDR_MINIMUM                   0x00000000U
#define OSPI_INDIRECT_READ_XFER_START_ADDR_MAXIMUM                   0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_READ_XFER_NUM_BYTES
    Offset name:         OSPI_O_INDIRECT_READ_XFER_NUM_BYTES
    Relative address:    0x6C
    Description:         Indirect Read Transfer Number Bytes Register
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:      This is the number of bytes that the indirect access will consume. This can be bigger than the configured size of SRAM.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_READ_XFER_NUM_BYTES_VALUE_W                    32U
#define OSPI_INDIRECT_READ_XFER_NUM_BYTES_VALUE_M                    0xFFFFFFFFU
#define OSPI_INDIRECT_READ_XFER_NUM_BYTES_VALUE_S                    0U
#define OSPI_INDIRECT_READ_XFER_NUM_BYTES_VALUE_MINIMUM              0x00000000U
#define OSPI_INDIRECT_READ_XFER_NUM_BYTES_VALUE_MAXIMUM              0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_WRITE_XFER_CTRL
    Offset name:         OSPI_O_INDIRECT_WRITE_XFER_CTRL
    Relative address:    0x70
    Description:         Indirect Write Transfer Control Register
    Default Value:       0x00000000

        Field:           START
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Start Indirect Write: Writing a 1 to this bit will trigger an indirect write operation. The assumption is that the indirect start address and the indirect number of bytes register is setup before triggering the indirect write operation.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_START                          0x00000001U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_START_M                        0x00000001U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_START_S                        0U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_START_DISABLE                  0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_START_ENABLE                   0x00000001U
/*

        Field:           CANCEL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Cancel Indirect Write: Writing a 1 to this bit will cancel all ongoing indirect write operations.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_CANCEL                         0x00000002U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_CANCEL_M                       0x00000002U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_CANCEL_S                       1U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_CANCEL_DISABLE                 0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_CANCEL_ENABLE                  0x00000002U
/*

        Field:           WR_STATUS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indirect Write Status: Indirect write operation in progress (status)

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_STATUS                      0x00000004U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_STATUS_M                    0x00000004U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_STATUS_S                    2U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_STATUS_DISABLE              0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_STATUS_ENABLE               0x00000004U
/*

        Field:           WR_QUEUED
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Two indirect write operations have been queued

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_QUEUED                      0x00000010U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_QUEUED_M                    0x00000010U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_QUEUED_S                    4U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_QUEUED_DISABLE              0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_WR_QUEUED_ENABLE               0x00000010U
/*

        Field:           IND_OPS_DONE_STATUS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Completion Status: This field is set to 1 when an indirect operation has completed. Write a 1 to this field to clear it.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_IND_OPS_DONE_STATUS            0x00000020U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_IND_OPS_DONE_STATUS_M          0x00000020U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_IND_OPS_DONE_STATUS_S          5U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_IND_OPS_DONE_STATUS_DISABLE    0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_IND_OPS_DONE_STATUS_ENABLE     0x00000020U
/*

        Field:           NUM_IND_OPS_DONE
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field contains the number of indirect operations which have been completed. This is used in conjunction with the indirect completion status field (bit 5). It is incremented by hardware when an indirect operation has completed. Write a 1 to bit 5 of this register to decrement it.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_WRITE_XFER_CTRL_NUM_IND_OPS_DONE_W             2U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_NUM_IND_OPS_DONE_M             0x000000C0U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_NUM_IND_OPS_DONE_S             6U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_NUM_IND_OPS_DONE_MINIMUM       0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_CTRL_NUM_IND_OPS_DONE_MAXIMUM       0x000000C0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_WRITE_XFER_WATERMARK
    Offset name:         OSPI_O_INDIRECT_WRITE_XFER_WATERMARK
    Relative address:    0x74
    Description:         Indirect Write Transfer Watermark Register
    Default Value:       0xFFFFFFFF

        Field:           LEVEL
        From..to bits:   0...31
        DefaultValue:    0xFFFFFFFF
        Access type:     read-write
        Description:     Watermark Value: This represents the maximum fill level of the SRAM before a DMA peripheral access is permitted. When the SRAM fill level falls below the watermark, an interrupt is also generated. This field can be disabled by writing a value of all ones.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_WRITE_XFER_WATERMARK_LEVEL_W                   32U
#define OSPI_INDIRECT_WRITE_XFER_WATERMARK_LEVEL_M                   0xFFFFFFFFU
#define OSPI_INDIRECT_WRITE_XFER_WATERMARK_LEVEL_S                   0U
#define OSPI_INDIRECT_WRITE_XFER_WATERMARK_LEVEL_MINIMUM             0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_WATERMARK_LEVEL_MAXIMUM             0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_WRITE_XFER_START
    Offset name:         OSPI_O_INDIRECT_WRITE_XFER_START
    Relative address:    0x78
    Description:         Indirect Write Transfer Start Address Register
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Start of Indirect Access: This is the start address from which the indirect access will commence its READ operation.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_WRITE_XFER_START_ADDR_W                        32U
#define OSPI_INDIRECT_WRITE_XFER_START_ADDR_M                        0xFFFFFFFFU
#define OSPI_INDIRECT_WRITE_XFER_START_ADDR_S                        0U
#define OSPI_INDIRECT_WRITE_XFER_START_ADDR_MINIMUM                  0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_START_ADDR_MAXIMUM                  0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_WRITE_XFER_NUM_BYTES
    Offset name:         OSPI_O_INDIRECT_WRITE_XFER_NUM_BYTES
    Relative address:    0x7C
    Description:         Indirect Write Transfer Number Bytes Register
    Default Value:       0x00000000

        Field:           VALUE
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indirect Number of Bytes: This is the number of bytes that the indirect access will consume. This can be bigger than the configured size of SRAM.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_VALUE_W                   32U
#define OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_VALUE_M                   0xFFFFFFFFU
#define OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_VALUE_S                   0U
#define OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_VALUE_MINIMUM             0x00000000U
#define OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_VALUE_MAXIMUM             0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       INDIRECT_TRIGGER_ADDR_RANGE
    Offset name:         OSPI_O_INDIRECT_TRIGGER_ADDR_RANGE
    Relative address:    0x80
    Description:         Indirect Trigger Address Range Register
    Default Value:       0x00000004

        Field:           IND_RANGE_WIDTH
        From..to bits:   0...3
        DefaultValue:    0x4
        Access type:     read-write
        Description:      This is the address offset of Indirect Trigger Address Register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_INDIRECT_TRIGGER_ADDR_RANGE_IND_RANGE_WIDTH_W           4U
#define OSPI_INDIRECT_TRIGGER_ADDR_RANGE_IND_RANGE_WIDTH_M           0x0000000FU
#define OSPI_INDIRECT_TRIGGER_ADDR_RANGE_IND_RANGE_WIDTH_S           0U
#define OSPI_INDIRECT_TRIGGER_ADDR_RANGE_IND_RANGE_WIDTH_MINIMUM     0x00000000U
#define OSPI_INDIRECT_TRIGGER_ADDR_RANGE_IND_RANGE_WIDTH_MAXIMUM     0x0000000FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_COMMAND_CTRL_MEM
    Offset name:         OSPI_O_FLASH_COMMAND_CTRL_MEM
    Relative address:    0x8C
    Description:         Flash Command Control Memory Register
    Default Value:       0x00000000

        Field:           TRIGGER_MEM_BANK_REQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Trigger the Memory Bank data request.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_COMMAND_CTRL_MEM_TRIGGER_MEM_BANK_REQ             0x00000001U
#define OSPI_FLASH_COMMAND_CTRL_MEM_TRIGGER_MEM_BANK_REQ_M           0x00000001U
#define OSPI_FLASH_COMMAND_CTRL_MEM_TRIGGER_MEM_BANK_REQ_S           0U
#define OSPI_FLASH_COMMAND_CTRL_MEM_TRIGGER_MEM_BANK_REQ_DISABLE     0x00000000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_TRIGGER_MEM_BANK_REQ_ENABLE      0x00000001U
/*

        Field:           MEM_BANK_REQ_IN_PROGRESS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Memory Bank data request in progress.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_REQ_IN_PROGRESS         0x00000002U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_REQ_IN_PROGRESS_M       0x00000002U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_REQ_IN_PROGRESS_S       1U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_REQ_IN_PROGRESS_DISABLE 0x00000000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_REQ_IN_PROGRESS_ENABLE  0x00000002U
/*

        Field:           MEM_BANK_READ_DATA
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Last requested data from the STIG Memory Bank.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_READ_DATA_W             8U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_READ_DATA_M             0x0000FF00U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_READ_DATA_S             8U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_READ_DATA_MINIMUM       0x00000000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_READ_DATA_MAXIMUM       0x0000FF00U
/*

        Field:           NB_OF_STIG_READ_BYTES
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:      It defines the number of read bytes for the extended STIG.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_COMMAND_CTRL_MEM_NB_OF_STIG_READ_BYTES_W          3U
#define OSPI_FLASH_COMMAND_CTRL_MEM_NB_OF_STIG_READ_BYTES_M          0x00070000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_NB_OF_STIG_READ_BYTES_S          16U
#define OSPI_FLASH_COMMAND_CTRL_MEM_NB_OF_STIG_READ_BYTES_MINIMUM    0x00000000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_NB_OF_STIG_READ_BYTES_MAXIMUM    0x00070000U
/*

        Field:           MEM_BANK_ADDR
        From..to bits:   20...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:      The address of the Memory Bank which data will be read from.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_ADDR_W                  9U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_ADDR_M                  0x1FF00000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_ADDR_S                  20U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_ADDR_MINIMUM            0x00000000U
#define OSPI_FLASH_COMMAND_CTRL_MEM_MEM_BANK_ADDR_MAXIMUM            0x1FF00000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_CMD_CTRL
    Offset name:         OSPI_O_FLASH_CMD_CTRL
    Relative address:    0x90
    Description:         Flash Command Control Register
    Default Value:       0x00000000

        Field:           CMD_EXEC
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Execute the command.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC                                 0x00000001U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_M                               0x00000001U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_S                               0U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_DISABLE                         0x00000000U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_ENABLE                          0x00000001U
/*

        Field:           CMD_EXEC_STATUS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Command execution in progress.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS                          0x00000002U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_M                        0x00000002U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_S                        1U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_DISABLE                  0x00000000U
#define OSPI_FLASH_CMD_CTRL_CMD_EXEC_STATUS_ENABLE                   0x00000002U
/*

        Field:           STIG_MEM_BANK_EN
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     STIG Memory Bank enable bit.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN                         0x00000004U
#define OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_M                       0x00000004U
#define OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_S                       2U
#define OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_DISABLE                 0x00000000U
#define OSPI_FLASH_CMD_CTRL_STIG_MEM_BANK_EN_ENABLE                  0x00000004U
/*

        Field:           CMD_GEN_FSM_STATE
        From..to bits:   3...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     CMD_GEN_FSM_STATE is used to define the "Polling flag":

                         If (CMD_GEN_FSM_STATE[6:3] = 0x7 or 0x8 or 0xa or 0xb ) then "Polling_flag"=1

                         Usage: In order to make sure a write to external device was done and ended successfully, following condition should be met:

                         "Command execution in progress" (FLASH_CMD_CTRL.CMD_EXEC_STATUS) = 0 AND "Polling flag" is '0'.

                         Design NOTE: Command gen FSM polling states are:

                         	  CMD_GEN_FSM_STATE == POLL_STATUS_AFTER_WRITE   (0x7)

                         	  CMD_GEN_FSM_STATE == POLL_STATUS_AFTER_WRITE2  (0x8)

                         	  CMD_GEN_FSM_STATE == POLL_STATUS_WAIT   (0xb)

                         	  CMD_GEN_FSM_STATE == LET_TXFIFO_EMPTY   (0xa)

        ENUMs:
            IDLE:
            SEND_ADDR_BYTES:
            STIG_MODE_BYTE:
            STIG_DUMMY_BYTES:
            SEND_DATA:
            SEND_STIG_DATA_LOWER:
            SEND_STIG_DATA_UPPER:
            POLL_STATUS_AFTER_WRITE:
            POLL_STATUS_AFTER_WRITE2:
            LET_TXFIFO_EMPTY:
            POLL_STATUS_WAIT:
            SEND_DATA_PIPE:
*/
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_W                      4U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_M                      0x00000078U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_S                      3U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_IDLE                   0x00000000U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_SEND_ADDR_BYTES        0x00000008U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_STIG_MODE_BYTE         0x00000010U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_STIG_DUMMY_BYTES       0x00000018U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_SEND_DATA              0x00000020U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_SEND_STIG_DATA_LOWER   0x00000028U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_SEND_STIG_DATA_UPPER   0x00000030U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_POLL_STATUS_AFTER_WRITE 0x00000038U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_POLL_STATUS_AFTER_WRITE2 0x00000040U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_LET_TXFIFO_EMPTY       0x00000050U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_POLL_STATUS_WAIT       0x00000058U
#define OSPI_FLASH_CMD_CTRL_CMD_GEN_FSM_STATE_SEND_DATA_PIPE         0x00000060U
/*

        Field:           NUM_DUMMY_CYCLES
        From..to bits:   7...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Dummy cycles: Set to the number of dummy cycles required. This should be setup before triggering the command via the execute field of this register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_W                       5U
#define OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_M                       0x00000F80U
#define OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_S                       7U
#define OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_MINIMUM                 0x00000000U
#define OSPI_FLASH_CMD_CTRL_NUM_DUMMY_CYCLES_MAXIMUM                 0x00000F80U
/*

        Field:           NUM_WR_DATA_BYTES
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Write Data Bytes: Up to 8 Data bytes may be written using this command Set to 0 for 1 byte, 7 for 8 bytes.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_W                      3U
#define OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_M                      0x00007000U
#define OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_S                      12U
#define OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_MINIMUM                0x00000000U
#define OSPI_FLASH_CMD_CTRL_NUM_WR_DATA_BYTES_MAXIMUM                0x00007000U
/*

        Field:           ENB_WRITE_DATA
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write Data Enable: Set to 1 if the command specified in the command opcode field requires write data bytes to be sent to the device.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA                           0x00008000U
#define OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_M                         0x00008000U
#define OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_S                         15U
#define OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_DISABLE                   0x00000000U
#define OSPI_FLASH_CMD_CTRL_ENB_WRITE_DATA_ENABLE                    0x00008000U
/*

        Field:           NUM_ADDR_BYTES
        From..to bits:   16...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Address Bytes: Set to the number of address bytes required (the address itself is programmed in the FLASH COMMAND ADDRESS REGISTERS). This should be setup before triggering the command via bit 0 of this register. 2'b00 : 1 address byte 2'b01 : 2 address bytes 2'b10 : 3 address bytes 2'b11 : 4 address bytes

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_W                         2U
#define OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_M                         0x00030000U
#define OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_S                         16U
#define OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_MINIMUM                   0x00000000U
#define OSPI_FLASH_CMD_CTRL_NUM_ADDR_BYTES_MAXIMUM                   0x00030000U
/*

        Field:           ENB_MODE_BIT
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Mode Bit Enable: Set to 1 to ensure the mode bits as defined in the Mode Bit Configuration register are sent following the address bytes.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT                             0x00040000U
#define OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_M                           0x00040000U
#define OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_S                           18U
#define OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_DISABLE                     0x00000000U
#define OSPI_FLASH_CMD_CTRL_ENB_MODE_BIT_ENABLE                      0x00040000U
/*

        Field:           ENB_COMD_ADDR
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Address Enable: Set to 1 if the command specified in bits 31:24 requires an address. This should be setup before triggering the command via writing a 1 to the execute field.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR                            0x00080000U
#define OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_M                          0x00080000U
#define OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_S                          19U
#define OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_DISABLE                    0x00000000U
#define OSPI_FLASH_CMD_CTRL_ENB_COMD_ADDR_ENABLE                     0x00080000U
/*

        Field:           NUM_RD_DATA_BYTES
        From..to bits:   20...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of Read Data Bytes: Up to 8 data bytes may be read using this command. Set to 0 for 1 byte and 7 for 8 bytes.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_W                      3U
#define OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_M                      0x00700000U
#define OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_S                      20U
#define OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_MINIMUM                0x00000000U
#define OSPI_FLASH_CMD_CTRL_NUM_RD_DATA_BYTES_MAXIMUM                0x00700000U
/*

        Field:           ENB_READ_DATA
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Read Data Enable: Set to 1 if the command specified in the command opcode field (bits 31:24) requires read data bytes to be received from the device.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_FLASH_CMD_CTRL_ENB_READ_DATA                            0x00800000U
#define OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_M                          0x00800000U
#define OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_S                          23U
#define OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_DISABLE                    0x00000000U
#define OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_ENABLE                     0x00800000U
/*

        Field:           CMD_OPCODE
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Opcode: The command opcode field should be setup before triggering the command. For example, 0x20 maps to SubSector Erase. Writing to the execute field (bit 0) of this register launches the command. NOTE : Using this approach to issue commands to the device will make use of the instruction type of the device instruction configuration register. If this field is set to 2'b00, then the command opcode, command address, command dummy bytes and command data will all be transferred in a serial fashion. If this field is set to 2'b01, then the command opcode, command address, command dummy bytes and command data will all be transferred in parallel using DQ0 and DQ1 pins. If this field is set to 2'b10, then the command opcode, command address, command dummy bytes and command data will all be transferred in parallel using DQ0, DQ1, DQ2 and DQ3 pins.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_CTRL_CMD_OPCODE_W                             8U
#define OSPI_FLASH_CMD_CTRL_CMD_OPCODE_M                             0xFF000000U
#define OSPI_FLASH_CMD_CTRL_CMD_OPCODE_S                             24U
#define OSPI_FLASH_CMD_CTRL_CMD_OPCODE_MINIMUM                       0x00000000U
#define OSPI_FLASH_CMD_CTRL_CMD_OPCODE_MAXIMUM                       0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_CMD_ADDR
    Offset name:         OSPI_O_FLASH_CMD_ADDR
    Relative address:    0x94
    Description:         Flash Command Address Register
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Address: This should be setup before triggering the command with execute field (bit 0) of the Flash Command Control register. It is the address used by the command specified in the opcode field (bits 31:24) of the Flash Command Control register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_CMD_ADDR_ADDR_W                                   32U
#define OSPI_FLASH_CMD_ADDR_ADDR_M                                   0xFFFFFFFFU
#define OSPI_FLASH_CMD_ADDR_ADDR_S                                   0U
#define OSPI_FLASH_CMD_ADDR_ADDR_MINIMUM                             0x00000000U
#define OSPI_FLASH_CMD_ADDR_ADDR_MAXIMUM                             0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_RD_DATA_LOWER
    Offset name:         OSPI_O_FLASH_RD_DATA_LOWER
    Relative address:    0xA0
    Description:         Flash Command Read Data Register (Lower)
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:      This is the data that is returned by the flash device for any status or configuration read operation carried out by triggering the event in the control register. The register will be valid when the polling bit in the control register is low.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_RD_DATA_LOWER_DATA_W                              32U
#define OSPI_FLASH_RD_DATA_LOWER_DATA_M                              0xFFFFFFFFU
#define OSPI_FLASH_RD_DATA_LOWER_DATA_S                              0U
#define OSPI_FLASH_RD_DATA_LOWER_DATA_MINIMUM                        0x00000000U
#define OSPI_FLASH_RD_DATA_LOWER_DATA_MAXIMUM                        0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_RD_DATA_UPPER
    Offset name:         OSPI_O_FLASH_RD_DATA_UPPER
    Relative address:    0xA4
    Description:         Flash Command Read Data Register (Upper)
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:      This is the data that is returned by the FLASH device for any status or configuration read operation carried out by triggering the event in the control register. The register will be valid when the polling bit in the control register is low.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_RD_DATA_UPPER_DATA_W                              32U
#define OSPI_FLASH_RD_DATA_UPPER_DATA_M                              0xFFFFFFFFU
#define OSPI_FLASH_RD_DATA_UPPER_DATA_S                              0U
#define OSPI_FLASH_RD_DATA_UPPER_DATA_MINIMUM                        0x00000000U
#define OSPI_FLASH_RD_DATA_UPPER_DATA_MAXIMUM                        0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_WR_DATA_LOWER
    Offset name:         OSPI_O_FLASH_WR_DATA_LOWER
    Relative address:    0xA8
    Description:         Flash Command Write Data Register (Lower)
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Write Data Lower Byte: This is the command write data lower byte. This should be setup before triggering the command with execute field (bit 0) of the Flash Command Control register. It is the data that is to be written to the flash for any status or configuration write operation carried out by triggering the event in the Flash Command Control register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_WR_DATA_LOWER_DATA_W                              32U
#define OSPI_FLASH_WR_DATA_LOWER_DATA_M                              0xFFFFFFFFU
#define OSPI_FLASH_WR_DATA_LOWER_DATA_S                              0U
#define OSPI_FLASH_WR_DATA_LOWER_DATA_MINIMUM                        0x00000000U
#define OSPI_FLASH_WR_DATA_LOWER_DATA_MAXIMUM                        0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASH_WR_DATA_UPPER
    Offset name:         OSPI_O_FLASH_WR_DATA_UPPER
    Relative address:    0xAC
    Description:         Flash Command Write Data Register (Upper)
    Default Value:       0x00000000

        Field:           DATA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Command Write Data Upper Byte: This is the command write data upper byte. This should be setup before triggering the command with execute field (bit 0) of the Flash Command Control register. It is the data that is to be written to the flash for any status or configuration write operation carried out by triggering the event in the Flash Command Control register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_FLASH_WR_DATA_UPPER_DATA_W                              32U
#define OSPI_FLASH_WR_DATA_UPPER_DATA_M                              0xFFFFFFFFU
#define OSPI_FLASH_WR_DATA_UPPER_DATA_S                              0U
#define OSPI_FLASH_WR_DATA_UPPER_DATA_MINIMUM                        0x00000000U
#define OSPI_FLASH_WR_DATA_UPPER_DATA_MAXIMUM                        0xFFFFFFFFU


/*-----------------------------------REGISTER------------------------------------
    Register name:       POLLING_FLASH_STATUS
    Offset name:         OSPI_O_POLLING_FLASH_STATUS
    Relative address:    0xB0
    Description:         Polling Flash Status Register
    Default Value:       0x00000000

        Field:           DEVICE_STATUS
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Defines actual Status Register of Device

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_W                    8U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_M                    0x000000FFU
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_S                    0U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_MINIMUM              0x00000000U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_MAXIMUM              0x000000FFU
/*

        Field:           DEVICE_STATUS_VALID
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Device Status Valid: This should be set when value in bits from 7 to 0 is valid.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_VALID                0x00000100U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_VALID_M              0x00000100U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_VALID_S              8U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_VALID_DISABLE        0x00000000U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_VALID_ENABLE         0x00000100U
/*

        Field:           DEVICE_STATUS_NB_DUMMY
        From..to bits:   16...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Number of dummy cycles for auto-polling

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_NB_DUMMY_W           5U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_NB_DUMMY_M           0x001F0000U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_NB_DUMMY_S           16U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_NB_DUMMY_MINIMUM     0x00000000U
#define OSPI_POLLING_FLASH_STATUS_DEVICE_STATUS_NB_DUMMY_MAXIMUM     0x001F0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PHY_CONFIGURATION
    Offset name:         OSPI_O_PHY_CONFIGURATION
    Relative address:    0xB4
    Description:         PHY Configuration Register
    Default Value:       0x40000000

        Field:           PHY_CONFIG_RX_DLL_DELAY
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX DLL Delay: This field determines the number of delay elements to insert on data path between ref_clk and rx_dll_clk.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_DELAY_W             7U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_DELAY_M             0x0000007FU
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_DELAY_S             0U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_DELAY_MINIMUM       0x00000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_DELAY_MAXIMUM       0x0000007FU
/*

        Field:           PHY_CONFIG_TX_DLL_DELAY
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:     TX DLL Delay: This field determines the number of delay elements to insert on data path between ref_clk and spi_clk.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_TX_DLL_DELAY_W             7U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_TX_DLL_DELAY_M             0x007F0000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_TX_DLL_DELAY_S             16U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_TX_DLL_DELAY_MINIMUM       0x00000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_TX_DLL_DELAY_MAXIMUM       0x007F0000U
/*

        Field:           PHY_CONFIG_RX_DLL_BYPASS
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RX DLL Bypass: This field determines id RX DLL is bypassed.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_BYPASS              0x20000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_BYPASS_M            0x20000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_BYPASS_S            29U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_BYPASS_DISABLE      0x00000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RX_DLL_BYPASS_ENABLE       0x20000000U
/*

        Field:           PHY_CONFIG_RESET
        From..to bits:   30...30
        DefaultValue:    0x1
        Access type:     write-only
        Description:     DLL Reset bit: This bit is used for reset of Delay Lines by software.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESET                      0x40000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESET_M                    0x40000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESET_S                    30U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESET_DISABLE              0x00000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESET_ENABLE               0x40000000U
/*

        Field:           PHY_CONFIG_RESYNC
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     write-only
        Description:      This bit is used for re-synchronisation delay lines to update them with values from TX DLL Delay and RX DLL Delay fields.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESYNC                     0x80000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESYNC_M                   0x80000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESYNC_S                   31U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESYNC_DISABLE             0x00000000U
#define OSPI_PHY_CONFIGURATION_PHY_CONFIG_RESYNC_ENABLE              0x80000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PHY_MASTER_CONTROL
    Offset name:         OSPI_O_PHY_MASTER_CONTROL
    Relative address:    0xB8
    Description:         PHY DLL Master Control Register
    Default Value:       0x00800000

        Field:           PHY_MASTER_INITIAL_DELAY
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:      This value is the initial delay value for the DLL.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_INITIAL_DELAY_W           7U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_INITIAL_DELAY_M           0x0000007FU
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_INITIAL_DELAY_S           0U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_INITIAL_DELAY_MINIMUM     0x00000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_INITIAL_DELAY_MAXIMUM     0x0000007FU
/*

        Field:           PHY_MASTER_NB_INDICATIONS
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Holds the number of consecutive increment or decrement indications.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_NB_INDICATIONS_W          3U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_NB_INDICATIONS_M          0x00070000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_NB_INDICATIONS_S          16U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_NB_INDICATIONS_MINIMUM    0x00000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_NB_INDICATIONS_MAXIMUM    0x00070000U
/*

        Field:           PHY_MASTER_PHASE_DETECT_SELECTOR
        From..to bits:   20...22
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Selects the number of delay elements to be inserted between the phase detect flip-flops.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_PHASE_DETECT_SELECTOR_W   3U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_PHASE_DETECT_SELECTOR_M   0x00700000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_PHASE_DETECT_SELECTOR_S   20U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_PHASE_DETECT_SELECTOR_MINIMUM 0x00000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_PHASE_DETECT_SELECTOR_MAXIMUM 0x00700000U
/*

        Field:           PHY_MASTER_BYPASS_MODE
        From..to bits:   23...23
        DefaultValue:    0x1
        Access type:     read-write
        Description:      Controls the bypass mode of the master and slave DLLs.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_BYPASS_MODE               0x00800000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_BYPASS_MODE_M             0x00800000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_BYPASS_MODE_S             23U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_BYPASS_MODE_DISABLE       0x00000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_BYPASS_MODE_ENABLE        0x00800000U
/*

        Field:           PHY_MASTER_LOCK_MODE
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Determines if the master delay line locks on a full cycle or half cycle of delay.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_LOCK_MODE                 0x01000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_LOCK_MODE_M               0x01000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_LOCK_MODE_S               24U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_LOCK_MODE_DISABLE         0x00000000U
#define OSPI_PHY_MASTER_CONTROL_PHY_MASTER_LOCK_MODE_ENABLE          0x01000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLL_OBSERVABLE_LOWER
    Offset name:         OSPI_O_DLL_OBSERVABLE_LOWER
    Relative address:    0xBC
    Description:         DLL Observable Register Lower
    Default Value:       0x00000000

        Field:           DLL_OBSERVABLE_LOWER_DLL_LOCK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Indicates status of DLL.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK      0x00000001U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_M    0x00000001U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_S    0U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DISABLE 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_ENABLE 0x00000001U
/*

        Field:           DLL_OBSERVABLE_LOWER_LOCK_MODE
        From..to bits:   1...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Defines the mode in which the DLL has achieved the lock.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_MODE_W   2U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_MODE_M   0x00000006U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_MODE_S   1U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_MODE_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_MODE_MAXIMUM 0x00000006U
/*

        Field:           DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER
        From..to bits:   3...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Reports the number of increments or decrements required for the master DLL to complete the locking process.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER_W 5U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER_M 0x000000F8U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER_S 3U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_UNLOCK_COUNTER_MAXIMUM 0x000000F8U
/*

        Field:           DLL_OBSERVABLE_LOWER_LOCK_VALUE
        From..to bits:   8...14
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Reports the DLL encoder value from the master DLL to the slave DLLs.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_VALUE_W  7U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_VALUE_M  0x00007F00U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_VALUE_S  8U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_VALUE_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOCK_VALUE_MAXIMUM 0x00007F00U
/*

        Field:           DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK
        From..to bits:   15...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:      This bit indicates that lock of loopback is done.

        ENUMs:
            DISABLE:                     Disable
            ENABLE:                      Enable
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK 0x00008000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_M 0x00008000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_S 15U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_DISABLE 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_ENABLE 0x00008000U
/*

        Field:           DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Holds the state of the cumulative dll_lock_dec register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC_W 8U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC_M 0x00FF0000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC_S 16U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_DEC_MAXIMUM 0x00FF0000U
/*

        Field:           DLL_OBSERVABLE_LOWER_DLL_LOCK_INC
        From..to bits:   24...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Holds the state of the cumulative dll_lock_inc register.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_INC_W 8U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_INC_M 0xFF000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_INC_S 24U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_INC_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_LOWER_DLL_OBSERVABLE_LOWER_DLL_LOCK_INC_MAXIMUM 0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DLL_OBSERVABLE_UPPER
    Offset name:         OSPI_O_DLL_OBSERVABLE_UPPER
    Relative address:    0xC0
    Description:         DLL Observable Register Upper
    Default Value:       0x00000000

        Field:           DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT
        From..to bits:   0...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Holds the encoded value for the RX delay line for this slice.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_W 7U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_M 0x0000007FU
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_S 0U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE__UPPER_RX_DECODER_OUTPUT_MAXIMUM 0x0000007FU
/*

        Field:           DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT
        From..to bits:   16...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Holds the encoded value for the TX delay line for this slice.

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_W 7U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_M 0x007F0000U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_S 16U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_MINIMUM 0x00000000U
#define OSPI_DLL_OBSERVABLE_UPPER_DLL_OBSERVABLE_UPPER_TX_DECODER_OUTPUT_MAXIMUM 0x007F0000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OPCODE_EXT_LOWER
    Offset name:         OSPI_O_OPCODE_EXT_LOWER
    Relative address:    0xE0
    Description:         Opcode Extension Register (Lower)
    Default Value:       0x13EDFA00

        Field:           EXT_STIG_OPCODE
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Supplement byte of any STIG Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_LOWER_EXT_STIG_OPCODE_W                      8U
#define OSPI_OPCODE_EXT_LOWER_EXT_STIG_OPCODE_M                      0x000000FFU
#define OSPI_OPCODE_EXT_LOWER_EXT_STIG_OPCODE_S                      0U
#define OSPI_OPCODE_EXT_LOWER_EXT_STIG_OPCODE_MINIMUM                0x00000000U
#define OSPI_OPCODE_EXT_LOWER_EXT_STIG_OPCODE_MAXIMUM                0x000000FFU
/*

        Field:           EXT_POLL_OPCODE
        From..to bits:   8...15
        DefaultValue:    0xFA
        Access type:     read-write
        Description:     Supplement byte of any Polling Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_LOWER_EXT_POLL_OPCODE_W                      8U
#define OSPI_OPCODE_EXT_LOWER_EXT_POLL_OPCODE_M                      0x0000FF00U
#define OSPI_OPCODE_EXT_LOWER_EXT_POLL_OPCODE_S                      8U
#define OSPI_OPCODE_EXT_LOWER_EXT_POLL_OPCODE_MINIMUM                0x00000000U
#define OSPI_OPCODE_EXT_LOWER_EXT_POLL_OPCODE_MAXIMUM                0x0000FF00U
/*

        Field:           EXT_WRITE_OPCODE
        From..to bits:   16...23
        DefaultValue:    0xED
        Access type:     read-write
        Description:     Supplement byte of any Write Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_LOWER_EXT_WRITE_OPCODE_W                     8U
#define OSPI_OPCODE_EXT_LOWER_EXT_WRITE_OPCODE_M                     0x00FF0000U
#define OSPI_OPCODE_EXT_LOWER_EXT_WRITE_OPCODE_S                     16U
#define OSPI_OPCODE_EXT_LOWER_EXT_WRITE_OPCODE_MINIMUM               0x00000000U
#define OSPI_OPCODE_EXT_LOWER_EXT_WRITE_OPCODE_MAXIMUM               0x00FF0000U
/*

        Field:           EXT_READ_OPCODE
        From..to bits:   24...31
        DefaultValue:    0x13
        Access type:     read-write
        Description:     Supplement byte of any Read Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_LOWER_EXT_READ_OPCODE_W                      8U
#define OSPI_OPCODE_EXT_LOWER_EXT_READ_OPCODE_M                      0xFF000000U
#define OSPI_OPCODE_EXT_LOWER_EXT_READ_OPCODE_S                      24U
#define OSPI_OPCODE_EXT_LOWER_EXT_READ_OPCODE_MINIMUM                0x00000000U
#define OSPI_OPCODE_EXT_LOWER_EXT_READ_OPCODE_MAXIMUM                0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       OPCODE_EXT_UPPER
    Offset name:         OSPI_O_OPCODE_EXT_UPPER
    Relative address:    0xE4
    Description:         Opcode Extension Register (Upper)
    Default Value:       0x06F90000

        Field:           EXT_WEL_OPCODE
        From..to bits:   16...23
        DefaultValue:    0xF9
        Access type:     read-write
        Description:     Supplement byte of any WEL Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_UPPER_EXT_WEL_OPCODE_W                       8U
#define OSPI_OPCODE_EXT_UPPER_EXT_WEL_OPCODE_M                       0x00FF0000U
#define OSPI_OPCODE_EXT_UPPER_EXT_WEL_OPCODE_S                       16U
#define OSPI_OPCODE_EXT_UPPER_EXT_WEL_OPCODE_MINIMUM                 0x00000000U
#define OSPI_OPCODE_EXT_UPPER_EXT_WEL_OPCODE_MAXIMUM                 0x00FF0000U
/*

        Field:           WEL_OPCODE
        From..to bits:   24...31
        DefaultValue:    0x6
        Access type:     read-write
        Description:     First byte of any WEL Opcode

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_OPCODE_EXT_UPPER_WEL_OPCODE_W                           8U
#define OSPI_OPCODE_EXT_UPPER_WEL_OPCODE_M                           0xFF000000U
#define OSPI_OPCODE_EXT_UPPER_WEL_OPCODE_S                           24U
#define OSPI_OPCODE_EXT_UPPER_WEL_OPCODE_MINIMUM                     0x00000000U
#define OSPI_OPCODE_EXT_UPPER_WEL_OPCODE_MAXIMUM                     0xFF000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MODULE_ID
    Offset name:         OSPI_O_MODULE_ID
    Relative address:    0xFC
    Description:         Module ID Register
    Default Value:       0x04000300

        Field:           CONF
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Configuration ID number: 0 : OCTAL + PHY Configuration 1 : OCTAL Configuration 2 : QUAD + PHY Configuration 3 : QUAD Configuration

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODULE_ID_CONF_W                                        2U
#define OSPI_MODULE_ID_CONF_M                                        0x00000003U
#define OSPI_MODULE_ID_CONF_S                                        0U
#define OSPI_MODULE_ID_CONF_MINIMUM                                  0x00000000U
#define OSPI_MODULE_ID_CONF_MAXIMUM                                  0x00000003U
/*

        Field:           MODULE_ID
        From..to bits:   8...23
        DefaultValue:    0x3
        Access type:     read-only
        Description:     Module/Revision ID number

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODULE_ID_MODULE_ID_W                                   16U
#define OSPI_MODULE_ID_MODULE_ID_M                                   0x00FFFF00U
#define OSPI_MODULE_ID_MODULE_ID_S                                   8U
#define OSPI_MODULE_ID_MODULE_ID_MINIMUM                             0x00000000U
#define OSPI_MODULE_ID_MODULE_ID_MAXIMUM                             0x00FFFF00U
/*

        Field:           FIX_PATCH
        From..to bits:   24...31
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Fix/path number related to revision described by 3 LSBs of this register

        ENUMs:
            MINIMUM:                     Smallest value
            MAXIMUM:                     Highest possible value
*/
#define OSPI_MODULE_ID_FIX_PATCH_W                                   8U
#define OSPI_MODULE_ID_FIX_PATCH_M                                   0xFF000000U
#define OSPI_MODULE_ID_FIX_PATCH_S                                   24U
#define OSPI_MODULE_ID_FIX_PATCH_MINIMUM                             0x00000000U
#define OSPI_MODULE_ID_FIX_PATCH_MAXIMUM                             0xFF000000U

#endif /* __HW_OSPI_H__*/
