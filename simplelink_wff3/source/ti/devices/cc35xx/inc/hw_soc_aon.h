/******************************************************************************
*  Filename:       hw_soc_aon.h
*
*  Description:    Defines and prototypes for the SOC_AON peripheral.
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
#ifndef __HW_SOC_AON_H__
#define __HW_SOC_AON_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SOC_AON component

--------------------------------------------------------------------------------- */

//M3 Event MUXs Selectors
#define SOC_AON_O_M3EVTCTL1                                          0x00000000U

//M3 Event MUXs Selectors
#define SOC_AON_O_M3IRQCTL2                                          0x00000004U

//M3 Event MUXs Selectors
#define SOC_AON_O_M3EVTCTL3                                          0x00000008U

//Shared Peripherals Event MUXs Selectors
#define SOC_AON_O_SPEVTCTL                                           0x0000000CU

//Timers Event MUXs Selectors
#define SOC_AON_O_TMEVTCTL                                           0x00000010U

//GPTIMER0 Channels Event MUXs Selectors
#define SOC_AON_O_GPT0EVTCTL0                                        0x00000014U

//GPTIMER1 Event MUXs Selectors
#define SOC_AON_O_GPT1EVTCTL0                                        0x00000018U

//Doorbell 0 M33 Clear Register
#define SOC_AON_O_DB0M33CLR                                          0x0000001CU

//Doorbell 0 M33 Set Register
#define SOC_AON_O_DB0M33SET                                          0x00000020U

//Doorbell 0 M33 Lock Bit
#define SOC_AON_O_DB0M33LOCK                                         0x00000024U

//Doorbell 1 M33 Clear Register
#define SOC_AON_O_DB1M33CLR                                          0x00000028U

//Doorbell 1 M33 Set Register
#define SOC_AON_O_DB1M33SET                                          0x0000002CU

//Doorbell 1 M33 Lock Bit
#define SOC_AON_O_DB1M33LOCK                                         0x00000030U

//Doorbell 4 M33 Clear Register
#define SOC_AON_O_DB4M33CLR                                          0x00000034U

//Doorbell 4 M33 Set Register
#define SOC_AON_O_DB4M33SET                                          0x00000038U

//Doorbell 4 M33 Lock Bit
#define SOC_AON_O_DB4M33LOCK                                         0x0000003CU

//Doorbell 5 M33 Clear Register
#define SOC_AON_O_DB5M33CLR                                          0x00000040U

//Doorbell 5 M33 Set Register
#define SOC_AON_O_DB5M33SET                                          0x00000044U

//Doorbell 5 M33 Lock Bit
#define SOC_AON_O_DB5M33LOCK                                         0x00000048U

//CODE Memory MEMSS Start Address
#define SOC_AON_O_CMEMSTART                                          0x0000004CU

//CODE Memory MEMSS End Address
#define SOC_AON_O_CMEMEND                                            0x00000050U

//DATA Memory MEMSS Start Address
#define SOC_AON_O_DMEMSTART                                          0x00000054U

//DATA Memory MEMSS End Address
#define SOC_AON_O_DMEMEND                                            0x00000058U

//TCM DATA Memory MEMSS Start Address
#define SOC_AON_O_TCMSTART                                           0x00000064U

//TCM DATA Memory MEMSS End Address
#define SOC_AON_O_TCMEND                                             0x00000068U

//Secured GPIO Event Status, 1st Register
#define SOC_AON_O_GPIOEVTS0                                          0x0000007CU

//Secured GPIO Event Status, 2nd Register
#define SOC_AON_O_GPIOEVTS1                                          0x00000080U

//MEMSS General Control Register
#define SOC_AON_O_MEMSSCTL0                                          0x00000084U

//MEMSS General Control Register
#define SOC_AON_O_MEMSSCTL1                                          0x00000088U

//Spare Register
#define SOC_AON_O_SPARE0                                             0x00000090U

//M33 Secure Vector Table Base Address
#define SOC_AON_O_VTORS                                              0x0000009CU

//M33 Non-Secure Vector Table Base Address
#define SOC_AON_O_VTORNS                                             0x000000A0U

//CPU Locks
#define SOC_AON_O_CPULOCKS                                           0x000000A8U

//Host Lock Signals
#define SOC_AON_O_HOSTLOCKS                                          0x000000ACU

//Host Boot Done
#define SOC_AON_O_HOSTBOOT                                           0x000000B0U

//Security Configurations
#define SOC_AON_O_SECCFG                                             0x000000B4U

//Doorbell M33 Secured IMASK
#define SOC_AON_O_DBSIMASK                                           0x000000B8U

//Doorbell M33 Secured ISET
#define SOC_AON_O_DBSISET                                            0x000000BCU

//Doorbell M33 Secured ICLR
#define SOC_AON_O_DBSICLR                                            0x000000C0U

//Doorbell M33 Secured IMSET
#define SOC_AON_O_DBSIMSET                                           0x000000C4U

//Doorbell M33 Secured IMCLR
#define SOC_AON_O_DBSIMCLR                                           0x000000C8U

//Doorbell M33 Secured RIS
#define SOC_AON_O_DBSRIS                                             0x000000CCU

//Doorbell M33 Secured MIS
#define SOC_AON_O_DBSMIS                                             0x000000D0U

//M33 Secured Error IMASK
#define SOC_AON_O_ERRSIMASK                                          0x000000D4U

//M33 Secured Error ISET
#define SOC_AON_O_ERRSISET                                           0x000000D8U

//M33 Secured Error ICLR
#define SOC_AON_O_ERRSICLR                                           0x000000DCU

//M33 Secured Error IMSET
#define SOC_AON_O_ERRSIMSET                                          0x000000E0U

//M33 Secured Error IMCLR
#define SOC_AON_O_ERRSIMCLR                                          0x000000E4U

//M33 Secured Error RIS
#define SOC_AON_O_ERRSRIS                                            0x000000E8U

//M33 Secured Error MIS
#define SOC_AON_O_ERRSMIS                                            0x000000ECU

//GPTIMER0 Sync, Tick Enable and Fault Event MUXs Selectors
#define SOC_AON_O_GPT0EVTCTL1                                        0x000000F0U

//GPTIMER1 Sync, Tick Enable and Fault Event MUXs Selectors
#define SOC_AON_O_GPT1EVTCTL1                                        0x000000F4U

//Customer ESMs Status
#define SOC_AON_O_ESMSTACST                                          0x00000104U

//MEMSS Configurations
#define SOC_AON_O_MEMSSCFG                                           0x0000010CU

//Secured Gpio MIS
#define SOC_AON_O_GPIOMIS0S                                          0x00000138U

//Secured Gpio MIS
#define SOC_AON_O_GPIOMIS1S                                          0x0000013CU

//Secured GPIO Functional Mask
#define SOC_AON_O_GPIOFNC0S                                          0x00000140U

//Secured GPIO Functional Mask
#define SOC_AON_O_GPIOFNC1S                                          0x00000144U

//Spare Reg, M33S Aperture
#define SOC_AON_O_SPARE1                                             0x00000148U

//ESM1 2nd Magic Value
#define SOC_AON_O_ESM1VAL2ND                                         0x0000014CU

//ESM2 2nd Magic Value
#define SOC_AON_O_ESM2VAL2ND                                         0x00000150U

//ESM1 2nd Magic Value Status
#define SOC_AON_O_ESM1STA2ND                                         0x00000154U

//ESM2 2nd Magic Value
#define SOC_AON_O_ESM2STA2ND                                         0x00000158U

//HOST FW Bypass
#define SOC_AON_O_FWCFGHOST                                          0x0000015CU

//DMA FW BYPASS
#define SOC_AON_O_FWCFGDMA                                           0x00000160U

//Peripheral Firewall Bypass
#define SOC_AON_O_FWCFGFPRPH                                         0x00000164U

//HOST MCU Firewall Bypass
#define SOC_AON_O_FWCFGM33                                           0x00000168U

//MEMSS Firewall Bypass
#define SOC_AON_O_FWCFGMEMSS                                         0x0000016CU

//IOMUX General firewall access permission
#define SOC_AON_O_FWIOGENSEL                                         0x00000170U

//PRCM_HOST firewall access permission
#define SOC_AON_O_FWPRCMHOST                                         0x00000174U

//M33 SCRATCHPAD firewall access permission
#define SOC_AON_O_FWPRCMSPAD                                         0x00000178U

//PRCM_COMMON firewall access permission
#define SOC_AON_O_FWPRCMCMN                                          0x0000017CU

//CKM firewall access permission
#define SOC_AON_O_FWCKM                                              0x00000180U

//SOC_IC firewall access permission
#define SOC_AON_O_FWSOCIC                                            0x00000184U

//AON_M33_S firewall access permission
#define SOC_AON_O_FWAONM33S                                          0x00000188U

//AON_M33_NS firewall access permission
#define SOC_AON_O_FWAONM33NS                                         0x0000018CU

//AAON_M33_S firewall access permission
#define SOC_AON_O_FWAAONM33S                                         0x00000190U

//AAON_M33_NS firewall access permission
#define SOC_AON_O_FWAAONM33NS                                        0x00000194U

//RTC firewall access permission
#define SOC_AON_O_FWCMNRTC                                           0x00000198U

//MEMSS region 0 firewall access permission
#define SOC_AON_O_FWMEMSS0                                           0x0000019CU

//MEMSS region 1 firewall access permission
#define SOC_AON_O_FWMEMSS1                                           0x000001A0U

//MEMSS region 2 firewall access permission
#define SOC_AON_O_FWMEMSS2                                           0x000001A4U

//HOST_AON_SLV firewall access permission
#define SOC_AON_O_FWHOSTAON                                          0x000001A8U

//HIF firewall access permission
#define SOC_AON_O_FWHIF                                              0x000001B0U

//HOST MCU region 0 firewall access permission
#define SOC_AON_O_FWHOST0                                            0x000001B4U

//HOST MCU region 1 firewall access permission
#define SOC_AON_O_FWHOST1                                            0x000001B8U

//HOST MCU region 2 firewall access permission
#define SOC_AON_O_FWHOST2                                            0x000001BCU

//HOST MCU region 3 firewall access permission
#define SOC_AON_O_FWHOST3                                            0x000001C0U

//access permission for 3 controller id :
#define SOC_AON_O_FWHOST4                                            0x000001C4U

//HOST MCU region 5 firewall access permission
#define SOC_AON_O_FWHOST5                                            0x000001C8U

//HOST MCU region 6 firewall access permission
#define SOC_AON_O_FWHOST6                                            0x000001CCU

//HOST MCU region 7 firewall access permission
#define SOC_AON_O_FWHOST7                                            0x000001D0U

//HOST MCU region 8 firewall access permission
#define SOC_AON_O_FWHOST8                                            0x000001D4U

//HOST MCU region 9 firewall access permission
#define SOC_AON_O_FWHOST9                                            0x000001D8U

//HOST MCU region 10 firewall access permission
#define SOC_AON_O_FWHOST10                                           0x000001DCU

//HOST MCU region 11 firewall access permission
#define SOC_AON_O_FWHOST11                                           0x000001E0U

//XIP_OSPI firewall access permission
#define SOC_AON_O_FWXIPOSPI                                          0x000001E4U

//OSPI_INDAC firewall access permission
#define SOC_AON_O_FWXIPINDAC                                         0x000001E8U

//XIP_GEN firewall access permission
#define SOC_AON_O_FWXIPGEN                                           0x000001ECU

//XIP_UDMA_SEC firewall access permission
#define SOC_AON_O_FWXIPUDMAS                                         0x000001F0U

//UDMA_NONSEC firewall access permission
#define SOC_AON_O_FWXIPUDMANS                                        0x000001F4U

//OTFDE_REGION0 firewall access permission
#define SOC_AON_O_FWOTFDE0                                           0x000001F8U

//OTFDE_REGION1 firewall access permission
#define SOC_AON_O_FWOTFDE1                                           0x000001FCU

//OTFDE_REGION2 firewall access permission
#define SOC_AON_O_FWOTFDE2                                           0x00000200U

//OTFDE_REGION3 firewall access permission
#define SOC_AON_O_FWOTFDE3                                           0x00000204U

//DMA_GEN firewall access permission
#define SOC_AON_O_FWDMAGEN                                           0x00000208U

//DMA_CH_0 firewall access permission
#define SOC_AON_O_FWDMA0                                             0x0000020CU

//DMA_CH_1 firewall access permission
#define SOC_AON_O_FWDMA1                                             0x00000210U

//DMA_CH_2 firewall access permission
#define SOC_AON_O_FWDMA2                                             0x00000214U

//DMA_CH_3 firewall access permission
#define SOC_AON_O_FWDMA3                                             0x00000218U

//DMA_CH_4 firewall access permission
#define SOC_AON_O_FWDMA4                                             0x0000021CU

//DMA_CH_5 firewall access permission
#define SOC_AON_O_FWDMA5                                             0x00000220U

//DMA_CH_6 firewall access permission
#define SOC_AON_O_FWDMA6                                             0x00000224U

//DMA_CH_7 firewall access permission
#define SOC_AON_O_FWDMA7                                             0x00000228U

//DMA_CH_8 firewall access permission
#define SOC_AON_O_FWDMA8                                             0x0000022CU

//DMA_CH_9 firewall access permission
#define SOC_AON_O_FWDMA9                                             0x00000230U

//DMA_CH_10 firewall access permission
#define SOC_AON_O_FWDMA10                                            0x00000234U

//DMA_CH_11 firewall access permission
#define SOC_AON_O_FWDMA11                                            0x00000238U

//HSM EIP NONSEC firewall access permission
#define SOC_AON_O_FWHSMEIPNS                                         0x0000023CU

//HSM EIP SEC firewall access permission
#define SOC_AON_O_FWHSMEIPS                                          0x00000240U

//HSM Wrapper NONSEC firewall access permission
#define SOC_AON_O_FWHSMWRAPNS                                        0x00000244U

//HSM Wrapper SEC firewall access permission
#define SOC_AON_O_FWHSMWRAPS                                         0x00000248U

//HSM DEBUG firewall access permission
#define SOC_AON_O_FWHSMDBG                                           0x0000024CU

//I2C0 firewall access permission
#define SOC_AON_O_FWI2C0                                             0x00000250U

//I2C1 firewall access permission
#define SOC_AON_O_FWI2C1                                             0x00000254U

//SPI0 firewall access permission
#define SOC_AON_O_FWSPSPI0                                           0x00000258U

//SPI1 firewall access permission
#define SOC_AON_O_FWSPSPI1                                           0x0000025CU

//UART0 firewall access permission
#define SOC_AON_O_FWSPUART0                                          0x00000260U

//UART1 firewall access permission
#define SOC_AON_O_FWSPUART1                                          0x00000264U

//GPTIMER0 firewall access permission
#define SOC_AON_O_FWSPGPT0                                           0x00000268U

//GPTIMER1 firewall access permission
#define SOC_AON_O_FWSPGPT1                                           0x0000026CU

//I2S firewall access permission
#define SOC_AON_O_FWSPI2S                                            0x00000270U

//PDM firewall access permission
#define SOC_AON_O_FWPDM                                              0x00000274U

//CAN firewall access permission
#define SOC_AON_O_FWSPCAN                                            0x00000278U

//ADC firewall access permission
#define SOC_AON_O_FWSPADC                                            0x0000027CU

//SDMMC firewall access permission
#define SOC_AON_O_FWSPSDMMC                                          0x00000280U

//SDIO firewall access permission
#define SOC_AON_O_FWSPSDIO                                           0x00000284U

//UART2 firewall access permission
#define SOC_AON_O_FWSPUART2                                          0x00000288U

//uDMA Non-secured Channel Control
#define SOC_AON_O_UDMANSCTL                                          0x0000028CU

//IOMUX_PAD_0 firewall access permission
#define SOC_AON_O_FWIOPAD0                                           0x00000290U

//IOMUX_PAD_1 firewall access permission
#define SOC_AON_O_FWIOPAD1                                           0x00000294U

//IOMUX_PAD_2 firewall access permission
#define SOC_AON_O_FWIOPAD2                                           0x00000298U

//IOMUX_PAD_3 firewall access permission
#define SOC_AON_O_FWIOPAD3                                           0x0000029CU

//IOMUX_PAD_4 firewall access permission
#define SOC_AON_O_FWIOPAD4                                           0x000002A0U

//IOMUX_PAD_5 firewall access permission
#define SOC_AON_O_FWIOPAD5                                           0x000002A4U

//IOMUX_PAD_6 firewall access permission
#define SOC_AON_O_FWIOPAD6                                           0x000002A8U

//IOMUX_PAD_7 firewall access permission
#define SOC_AON_O_FWIOPAD7                                           0x000002ACU

//IOMUX_PAD_8 firewall access permission
#define SOC_AON_O_FWIOPAD8                                           0x000002B0U

//IOMUX_PAD_9 firewall access permission
#define SOC_AON_O_FWIOPAD9                                           0x000002B4U

//IOMUX_PAD_10 firewall access permission
#define SOC_AON_O_FWIOPAD10                                          0x000002B8U

//IOMUX_PAD_11 firewall access permission
#define SOC_AON_O_FWIOPAD11                                          0x000002BCU

//IOMUX_PAD_12 firewall access permission
#define SOC_AON_O_FWIOPAD12                                          0x000002C0U

//IOMUX_PAD_13 firewall access permission
#define SOC_AON_O_FWIOPAD13                                          0x000002C4U

//IOMUX_PAD_14 firewall access permission
#define SOC_AON_O_FWIOPAD14                                          0x000002C8U

//IOMUX_PAD_15 firewall access permission
#define SOC_AON_O_FWIOPAD15                                          0x000002CCU

//IOMUX_PAD_16 firewall access permission
#define SOC_AON_O_FWIOPAD16                                          0x000002D0U

//IOMUX_PAD_17 firewall access permission
#define SOC_AON_O_FWIOPAD17                                          0x000002D4U

//IOMUX_PAD_18 firewall access permission
#define SOC_AON_O_FWIOPAD18                                          0x000002D8U

//IOMUX_PAD_19 firewall access permission
#define SOC_AON_O_FWIOPAD19                                          0x000002DCU

//IOMUX_PAD_20 firewall access permission
#define SOC_AON_O_FWIOPAD20                                          0x000002E0U

//IOMUX_PAD_21 firewall access permission
#define SOC_AON_O_FWIOPAD21                                          0x000002E4U

//IOMUX_PAD_22 firewall access permission
#define SOC_AON_O_FWIOPAD22                                          0x000002E8U

//IOMUX_PAD_23 firewall access permission
#define SOC_AON_O_FWIOPAD23                                          0x000002ECU

//IOMUX_PAD_24 firewall access permission
#define SOC_AON_O_FWIOPAD24                                          0x000002F0U

//IOMUX_PAD_25 firewall access permission
#define SOC_AON_O_FWIOPAD25                                          0x000002F4U

//IOMUX_PAD_26 firewall access permission
#define SOC_AON_O_FWIOPAD26                                          0x000002F8U

//IOMUX_PAD_27 firewall access permission
#define SOC_AON_O_FWIOPAD27                                          0x000002FCU

//IOMUX_PAD_28 firewall access permission
#define SOC_AON_O_FWIOPAD28                                          0x00000300U

//IOMUX_PAD_29 firewall access permission
#define SOC_AON_O_FWIOPAD29                                          0x00000304U

//IOMUX_PAD_30 firewall access permission
#define SOC_AON_O_FWIOPAD30                                          0x00000308U

//IOMUX_PAD_31 firewall access permission
#define SOC_AON_O_FWIOPAD31                                          0x0000030CU

//IOMUX_PAD_32 firewall access permission
#define SOC_AON_O_FWIOPAD32                                          0x00000310U

//IOMUX_PAD_33 firewall access permission
#define SOC_AON_O_FWIOPAD33                                          0x00000314U

//IOMUX_PAD_34 firewall access permission
#define SOC_AON_O_FWIOPAD34                                          0x00000318U

//IOMUX_PAD_35 firewall access permission
#define SOC_AON_O_FWIOPAD35                                          0x0000031CU

//IOMUX_PAD_36 firewall access permission
#define SOC_AON_O_FWIOPAD36                                          0x00000320U

//IOMUX_PAD_37 firewall access permission
#define SOC_AON_O_FWIOPAD37                                          0x00000324U

//IOMUX_PAD_38 firewall access permission
#define SOC_AON_O_FWIOPAD38                                          0x00000328U

//IOMUX_PAD_39 firewall access permission
#define SOC_AON_O_FWIOPAD39                                          0x0000032CU

//IOMUX_PAD_40 firewall access permission
#define SOC_AON_O_FWIOPAD40                                          0x00000330U

//IOMUX_PAD_41 firewall access permission
#define SOC_AON_O_FWIOPAD41                                          0x00000334U

//IOMUX_PAD_42 firewall access permission
#define SOC_AON_O_FWIOPAD42                                          0x00000338U

//IOMUX_PAD_43 firewall access permission
#define SOC_AON_O_FWIOPAD43                                          0x0000033CU

//IOMUX_PAD_44 firewall access permission
#define SOC_AON_O_FWIOPAD44                                          0x00000340U

//IOMUX_PAD_45 firewall access permission
#define SOC_AON_O_FWIOPAD45                                          0x00000344U

//IOMUX_PAD_46 firewall access permission
#define SOC_AON_O_FWIOPAD46                                          0x00000348U

//IOMUX_PAD_47 firewall access permission
#define SOC_AON_O_FWIOPAD47                                          0x0000034CU

//IOMUX_PAD_48 firewall access permission
#define SOC_AON_O_FWIOPAD48                                          0x00000350U

//DMA_CH_12 firewall access permission
#define SOC_AON_O_FWDMA12                                            0x00000354U

//DMA_CH_13 firewall access permission
#define SOC_AON_O_FWDMA13                                            0x00000358U

//Spare firewall access register
#define SOC_AON_O_FWSPARE0                                           0x0000035CU

//Micro Second STB
#define SOC_AON_O_USECSTB                                            0x00001000U

//Doorbell 2 M33 Clear Register
#define SOC_AON_O_DB2M33CLR                                          0x00001004U

//Doorbell 2 M33 Set Register
#define SOC_AON_O_DB2M33SET                                          0x00001008U

//Doorbell 2 M33 Lockbit Register
#define SOC_AON_O_DB2M33LOCK                                         0x0000100CU

//Doorbell 3 M33 Clear Register
#define SOC_AON_O_DB3M33CLR                                          0x00001010U

//Doorbell 3 M33 Set Register
#define SOC_AON_O_DB3M33SET                                          0x00001014U

//Doorbell 3 M33 Lockbit Register
#define SOC_AON_O_DB3M33LOCK                                         0x00001018U

//Doorbell 6 M33 Clear Register
#define SOC_AON_O_DB6M33CLR                                          0x0000101CU

//Doorbell 6 M33 Set Register
#define SOC_AON_O_DB6M33SET                                          0x00001020U

//Doorbell 6 M33 Lockbit Register
#define SOC_AON_O_DB6M33LOCK                                         0x00001024U

//Doorbell 7 M33 Clear Register
#define SOC_AON_O_DB7M33CLR                                          0x00001028U

//Doorbell 7 M33 Set Register
#define SOC_AON_O_DB7M33SET                                          0x0000102CU

//Doorbell 7 M33 Lockbit Register
#define SOC_AON_O_DB7M33LOCK                                         0x00001030U

//Non-Secured GPIO Event Status, 1st Register
#define SOC_AON_O_GPIOEVT0NS                                         0x00001044U

//Non-Secured GPIO Event Status, 2nd Register
#define SOC_AON_O_GPIOEVT1NS                                         0x00001048U

//M33 Non-Secured Doorbell IMASK
#define SOC_AON_O_DBM33NS0                                           0x00001054U

//M33 Non-Secured Doorbells ISET
#define SOC_AON_O_DBNSISET                                           0x00001058U

//M33 Non-Secured Doorbell ICLR
#define SOC_AON_O_DBNSICLR                                           0x0000105CU

//M33 Non-Secured Doorbell IMSET
#define SOC_AON_O_DBNSIMSET                                          0x00001060U

//M33 Non-Secured Doorbell IMCLR,
#define SOC_AON_O_DBNSIMCLR                                          0x00001064U

//M33 Non-Secured Doorbell RIS
#define SOC_AON_O_DBNSRIS                                            0x00001068U

//M33 Non-Secured Doorbell MIS
#define SOC_AON_O_DBNSMIS                                            0x0000106CU

//Non Secured GPIO MIS
#define SOC_AON_O_GPIOMIS0NS                                         0x00001070U

//Non Secure GPIO MIS
#define SOC_AON_O_GPIOMIS1NS                                         0x00001074U

//Non Secured GPIO Functional Mask
#define SOC_AON_O_GPIOFNC0NS                                         0x00001078U

//non secured gpio functional mask
#define SOC_AON_O_GPIOFNC1NS                                         0x0000107CU

//Spare Register for M22 Secured Aperture
#define SOC_AON_O_SPARE2                                             0x00001080U

//Selected Security Fuse Lines
#define SOC_AON_O_FUSE                                               0x00002004U

//ESM1 Configuration- Customer Debug M33 Non Secure Enable Sequence Monitor
#define SOC_AON_O_ESM1CFG                                            0x00002048U

//ESM1 Enable Number 1
#define SOC_AON_O_ESM1EN1                                            0x0000204CU

//ESM1 Enable Number 2
#define SOC_AON_O_ESM1EN2                                            0x00002050U

//ESM1 Enable Number 3
#define SOC_AON_O_ESM1EN3                                            0x00002054U

//ESM1 Enable Number 4
#define SOC_AON_O_ESM1EN4                                            0x00002058U

//ESM1 Enable Number 5
#define SOC_AON_O_ESM1EN5                                            0x0000205CU

//ESM2 Enable Number 1
#define SOC_AON_O_ESM2EN1                                            0x00002060U

//ESM2 Enable Number 2
#define SOC_AON_O_ESM2EN2                                            0x00002064U

//ESM2 Enable Number 3
#define SOC_AON_O_ESM2EN3                                            0x00002068U

//ESM2 Enable Number 4
#define SOC_AON_O_ESM2EN4                                            0x0000206CU

//ESM2 Enable Number 5
#define SOC_AON_O_ESM2EN5                                            0x00002070U

//ESM2 Configuration- Customer Debug M33 Secure Enable Sequence Monitor
#define SOC_AON_O_ESM2CFG                                            0x00002074U

//This register allow indication of debug port is present:  ble, wlphy, wsoccpu, app cpu
#define SOC_AON_O_DBGSSDSSM                                          0x000020A4U

//ESM3 Configuration- TI Debug Enable Sequence Monitor
#define SOC_AON_O_ESM3CFG                                            0x000020B4U

//ESM3 Enable Number 1
#define SOC_AON_O_ESM3EN1                                            0x000020B8U

//ESM3 Enable Number 2
#define SOC_AON_O_ESM3EN2                                            0x000020BCU

//ESM3 Enable Number 3
#define SOC_AON_O_ESM3EN3                                            0x000020C0U

//ESM3 Enable Number 4
#define SOC_AON_O_ESM3EN4                                            0x000020C4U

//ESM3 Enable Number 5
#define SOC_AON_O_ESM3EN5                                            0x000020C8U

//Fuse Line 0
#define SOC_AON_O_FUSELINE0                                          0x000020CCU

//Fuse Line 1
#define SOC_AON_O_FUSELINE1                                          0x000020D0U

//Fuse Line 2
#define SOC_AON_O_FUSELINE2                                          0x000020D4U

//Fuse Line 3
#define SOC_AON_O_FUSELINE3                                          0x000020D8U

//Fuse Line 4
#define SOC_AON_O_FUSELINE4                                          0x000020DCU

//Fuse Line 5
#define SOC_AON_O_FUSELINE5                                          0x000020E0U

//Fuse Line 6
#define SOC_AON_O_FUSELINE6                                          0x000020E4U

//Fuse Line 7
#define SOC_AON_O_FUSELINE7                                          0x000020E8U

//Fuse Line 8
#define SOC_AON_O_FUSELINE8                                          0x000020ECU

//Fuse Access Control
#define SOC_AON_O_FUSECTL                                            0x00002100U

//CORE Memory Access Control
#define SOC_AON_O_COREMEMCTL                                         0x00002104U

//Access Control - Core Global Port Enable
#define SOC_AON_O_COREGPCTL                                          0x00002108U

//MEMSS Global Port Access Control
#define SOC_AON_O_MEMSSGPCTL                                         0x0000210CU

//BLE Fuse Access Control
#define SOC_AON_O_BLEFUSECTL                                         0x00002110U

//not in use
#define SOC_AON_O_SPARE4                                             0x00002118U

//ESM4 Configuration- TI DFT Enable Sequence Monitor
#define SOC_AON_O_ESM4CFG                                            0x0000211CU

//ESM4 Enable Number 1
#define SOC_AON_O_ESM4EN1                                            0x00002120U

//ESM4 Enable Number 2
#define SOC_AON_O_ESM4EN2                                            0x00002124U

//ESM4 Enable Number 3
#define SOC_AON_O_ESM4EN3                                            0x00002128U

//ESM4 Enable Number 4
#define SOC_AON_O_ESM4EN4                                            0x0000212CU

//ESM4 Enable Number 5
#define SOC_AON_O_ESM4EN5                                            0x00002130U

//This register is locking the CORE related security bits , should be written in boot and on elevated mode exit:
#define SOC_AON_O_MEMPROT                                            0x00002140U

//WSOC MCU VTOR CONFIGURATION
#define SOC_AON_O_VTORCFG                                            0x00002144U

//MCU ROM Jump Disable
#define SOC_AON_O_ROMJUMPCTL                                         0x00002148U

//Execution RAM (CRAM) - Threshold register
#define SOC_AON_O_CRAMPROT1                                          0x0000214CU

//Execution RAM (CRAM) - Protect from write
#define SOC_AON_O_CRAMPROT0                                          0x00002150U

//Data RAM (DRAM) - Threshold register
#define SOC_AON_O_DRAMPROT1                                          0x00002154U

//Data RAM (DRAM) - Protect from fetch
#define SOC_AON_O_DRAMPROT0                                          0x00002158U

//Packet RAM (PRAM) - Protect from fetch
#define SOC_AON_O_PRAMPROT0                                          0x0000215CU

//Security Strong Pattern
#define SOC_AON_O_STRONGPAT                                          0x00002160U

//Unique Device Secret
#define SOC_AON_O_UDS0                                               0x00002164U

//Unique Device Secret
#define SOC_AON_O_UDS1                                               0x00002168U

//Unique Device Secret
#define SOC_AON_O_UDS2                                               0x0000216CU

//Unique Device Secret
#define SOC_AON_O_UDS3                                               0x00002170U

//SOC_AON Debug Bus
#define SOC_AON_O_DBGBUS                                             0x00002174U

//DEBUGSS JTAG User Code
#define SOC_AON_O_DEBUGSS                                            0x0000217CU

//Execution RAM (CRAM) - Threshold register
#define SOC_AON_O_CPEPROT1                                           0x00002180U

//CPE Data RAM (DRAM) - Protect from fetch
#define SOC_AON_O_CPEPROT0                                           0x00002184U

//Security Fuse Shift CRC
#define SOC_AON_O_FUSESHIFT                                          0x00002188U

//Security Hide Rom Assets
#define SOC_AON_O_SECROM                                             0x0000218CU

//Security Hide UDS Assets
#define SOC_AON_O_SECUDS                                             0x00002190U

//WLPHY RAM memory protection - Threshold register
#define SOC_AON_O_PHYPROT1                                           0x00002198U

//WLPHY RAM  - Protect from fetch
#define SOC_AON_O_PHYPROT0                                           0x0000219CU

//ESMs Graceful Disable
#define SOC_AON_O_ESMDIS                                             0x000021A0U

//Spare bits , locked on boot
#define SOC_AON_O_SPARE5                                             0x000021A4U

//Top Debug Selectors
#define SOC_AON_O_TOPDBG                                             0x000021A8U

//Doorbell 0 M3 Clear Register
#define SOC_AON_O_DB0M3CLR                                           0x00002370U

//Doorbell 0 M3 Set Register
#define SOC_AON_O_DB0M3SET                                           0x00002374U

//Doorbell 0 M3 Lock Bit
#define SOC_AON_O_DB0M3LOCK                                          0x00002378U

//Doorbell 1 M3 Clear Register
#define SOC_AON_O_DB1M3CLR                                           0x0000237CU

//Doorbell 1 M3 Set Register
#define SOC_AON_O_DB1M3SET                                           0x00002380U

//Doorbell 1 M3 Lock Bit
#define SOC_AON_O_DB1M3LOCK                                          0x00002384U

//Doorbell 2 M3 Clear Register
#define SOC_AON_O_DB2M3CLR                                           0x00002388U

//Doorbell 2 M3 Set Register
#define SOC_AON_O_DB2M3SET                                           0x0000238CU

//Doorbell 2 M3 Lock Bit
#define SOC_AON_O_DB2M3LOCK                                          0x00002390U

//Doorbell 3 M3 Clear Register
#define SOC_AON_O_DB3M3CLR                                           0x00002394U

//Doorbell 3 M3 Set Register
#define SOC_AON_O_DB3M3SET                                           0x00002398U

//Doorbell 3 M3 Lock Bit
#define SOC_AON_O_DB3M3LOCK                                          0x0000239CU

//Doorbell 4 M3 Clear Register
#define SOC_AON_O_DB4M3CLR                                           0x000023A0U

//Doorbell 4 M3 Set Register
#define SOC_AON_O_DB4M3SET                                           0x000023A4U

//Doorbell 4 M3 Lock Bit
#define SOC_AON_O_DB4M3LOCK                                          0x000023A8U

//Doorbell 5 M3 Clear Register
#define SOC_AON_O_DB5M3CLR                                           0x000023ACU

//Doorbell 5 M3 Set Register
#define SOC_AON_O_DB5M3SET                                           0x000023B0U

//Doorbell 5 M3 Lock Bit
#define SOC_AON_O_DB5M3LOCK                                          0x000023B4U

//Doorbell 6 M3 Clear Register
#define SOC_AON_O_DB6M3CLR                                           0x000023B8U

//Doorbell 6 M3 Set Register
#define SOC_AON_O_DB6M3SET                                           0x000023BCU

//Doorbell 6 M3 Lock Bit
#define SOC_AON_O_DB6M3LOCK                                          0x000023C0U

//Doorbell 7 M3 Clear Register
#define SOC_AON_O_DB7M3CLR                                           0x000023C4U

//Doorbell 7 M3 Set Register
#define SOC_AON_O_DB7M3SET                                           0x000023C8U

//Doorbell 7 M3 Lock Bit
#define SOC_AON_O_DB7M3LOCK                                          0x000023CCU

//M3 GPIO Event Status
#define SOC_AON_O_M3GPIOEVT0                                         0x000023D0U

//M3 GPIO Event Status
#define SOC_AON_O_M3GPIOEVT1                                         0x000023D4U

//Fuse Lock
#define SOC_AON_O_FUSELOCK                                           0x000023E8U

//ROM Boot Done
#define SOC_AON_O_ROMBOOT                                            0x000023ECU

//SOC Boot Done
#define SOC_AON_O_SOCBOOT                                            0x000023FCU

//Elevated Mode Done
#define SOC_AON_O_ELEVATED                                           0x00002400U

//M3 TCM Access
#define SOC_AON_O_M3TCM                                              0x00002408U

//HSM Configurations
#define SOC_AON_O_HSMCFG                                             0x0000240CU

//ESM4 Configuration- Customer HSM Debug Enable Sequence Monitor
#define SOC_AON_O_ESM5CFG                                            0x00002410U

//ESM5 Enable Number 1
#define SOC_AON_O_ESM5EN1                                            0x00002414U

//ESM5 Enable Number 2
#define SOC_AON_O_ESM5EN2                                            0x00002418U

//ESM5 Enable Number 3
#define SOC_AON_O_ESM5EN3                                            0x0000241CU

//ESM5 Enable Number 4
#define SOC_AON_O_ESM5EN4                                            0x00002420U

//ESM5 Enable Number 5
#define SOC_AON_O_ESM5EN5                                            0x00002424U

//ESM1 1st Magic Value
#define SOC_AON_O_ESM1VAL1ST                                         0x00002428U

//ESM2 1st Magic Value
#define SOC_AON_O_ESM2VAL1ST                                         0x0000242CU

//ESM3 1st Magic Value
#define SOC_AON_O_ESM3VAL1ST                                         0x00002430U

//ESM4 1st Magic Value
#define SOC_AON_O_ESM4VAL1ST                                         0x00002434U

//ESM5 1st Magic Value
#define SOC_AON_O_ESM5VAL1ST                                         0x00002438U

//M3 Doorbell IMASK
#define SOC_AON_O_DBM3IMASK                                          0x00002450U

//M3 Doorbell ISET
#define SOC_AON_O_DBM3ISET                                           0x00002454U

//M3 Doorbell ICLR
#define SOC_AON_O_DBM3ICLR                                           0x00002458U

//M3 Doorbell IMSET
#define SOC_AON_O_DBM3IMSET                                          0x0000245CU

//M3 Doorbell IMCLR
#define SOC_AON_O_DBM3IMCLR                                          0x00002460U

//M3 Doorbell RIS
#define SOC_AON_O_DBM3RIS                                            0x00002464U

//M3 Doorbell MIS
#define SOC_AON_O_DBM3MIS                                            0x00002468U

//M33 cortex system reset request
#define SOC_AON_O_HOSTCRTX                                           0x00002680U

//SOC Firewall Bypass
#define SOC_AON_O_FWCFGSOC                                           0x00002684U

//COEX firewall access permission
#define SOC_AON_O_FWCOEX                                             0x00002688U

//PRCM CORE + M3 Scratchpad firewall access permission
#define SOC_AON_O_FWPRCM                                             0x0000268CU

//FUSE FARM firewall access permission
#define SOC_AON_O_FWFUSE                                             0x00002690U

//GPADC firewall access permission
#define SOC_AON_O_FWGPADC                                            0x00002694U

//DEBUGSS firewall access permission
#define SOC_AON_O_FWDBGSS                                            0x00002698U

//SOC_AON_M3 firewall access permission
#define SOC_AON_O_FWAONM3                                            0x0000269CU

//OCLA firewall access permission
#define SOC_AON_O_FWOCLA                                             0x000026A0U

//WSOC_IC firewall access permission
#define SOC_AON_O_FWCORE                                             0x000026A4U

//SOC_AAON_M3 firewall access permission
#define SOC_AON_O_FWAAONM3                                           0x000026A8U

//XIP_CFG firewall access permission
#define SOC_AON_O_FWXIPCFG                                           0x000026ACU

//OTFE_BOOT_LOCK firewall access permission
#define SOC_AON_O_FWOTFLCK                                           0x000026B0U

//OTFDE_NON_LOCK firewall access permission
#define SOC_AON_O_FWOTFNLCK                                          0x000026B4U

//CORE_AON firewall access permission
#define SOC_AON_O_FWCOREAON                                          0x00002808U

//Spare firewall access register
#define SOC_AON_O_FWSPARE1                                           0x0000287CU

//Boot Status
#define SOC_AON_O_SOCSTA                                             0x00002898U

//LifeCycle Config
#define SOC_AON_O_LCCFG                                              0x0000289CU

//status register , for each of the ESM (enable sequence monitor) what is the current state of esm
#define SOC_AON_O_ESM1STA                                            0x000028A0U

//status register , for each of the ESM (enable sequence monitor) what is the current state of esm
#define SOC_AON_O_ESM2STA                                            0x000028A4U

//ESM1 1st magic value match indication
#define SOC_AON_O_ESM1STA1ST                                         0x000028A8U

//ESM2 1st magic value match indication
#define SOC_AON_O_ESM2STA1ST                                         0x000028ACU

//ESM3 1st magic value match indication
#define SOC_AON_O_ESM3STA1ST                                         0x000028B0U

//ESM4 1st magic value match indication
#define SOC_AON_O_ESM4STA1ST                                         0x000028B4U

//ESM5 1st magic value match indication
#define SOC_AON_O_ESM5STA1ST                                         0x000028B8U

//Enable Security Group SERROR
#define SOC_AON_O_SECGSERR                                           0x00002908U

//Erase Assets DRAM
#define SOC_AON_O_DRAMCTL                                            0x0000290CU

//Conn Stop Control By M33
#define SOC_AON_O_CONNSTPCTL                                         0x00002910U

//TI ESMs STATUS (3,4,5)
#define SOC_AON_O_ESMSTATI                                           0x00002914U

//M3 GPIO Functional MIS
#define SOC_AON_O_M3GPIOMIS0                                         0x00002918U

//M3 GPIO Functional MIS
#define SOC_AON_O_M3GPIOMIS1                                         0x0000291CU

//M3 GPIO Functional Mask
#define SOC_AON_O_M3GPIOFNC0                                         0x00002920U

//M3 GPIO Functional Mask
#define SOC_AON_O_M3GPIOFNC1                                         0x00002924U

//Debug Bus Out Select
#define SOC_AON_O_DBGOCLA                                            0x00002928U

//M33 CPUWAIT
#define SOC_AON_O_CPUWAIT                                            0x0000292CU

//spare reg for m3 aperture
#define SOC_AON_O_SPARE6                                             0x00002930U

//Security AON Status
#define SOC_AON_O_SECSTA                                             0x00002934U

//ESM3 2nd Magic Value
#define SOC_AON_O_ESM3VAL2ND                                         0x00002938U

//ESM4 2nd Magic Value
#define SOC_AON_O_ESM4VAL2ND                                         0x0000293CU

//ESM5 2nd Magic Value
#define SOC_AON_O_ESM5VAL2ND                                         0x00002940U

//ESM3 Status
#define SOC_AON_O_ESM3STA                                            0x00002944U

//ESM4 Status
#define SOC_AON_O_ESM4STA                                            0x00002948U

//ESM5 Status
#define SOC_AON_O_ESM5STA                                            0x0000294CU

//ESM3 2nd magic value match indication
#define SOC_AON_O_ESM3STA2ND                                         0x00002950U

//ESM4 2nd magic value match indication
#define SOC_AON_O_ESM4STA2ND                                         0x00002954U

//ESM5 2nd magic value match indication
#define SOC_AON_O_ESM5STA2ND                                         0x00002958U

//This register contains information on Device Life Cycles ad follow:
#define SOC_AON_O_LCSTA                                              0x0000295CU

//DRAM_ASSET
#define SOC_AON_O_DRMAST                                             0x00002960U

//FLASH MASK
#define SOC_AON_O_FLASHMASK                                          0x00002964U

//WSOC ROM Unhide
#define SOC_AON_O_WSOCROM                                            0x00002968U



/*-----------------------------------REGISTER------------------------------------
    Register name:       M3EVTCTL1
    Offset name:         SOC_AON_O_M3EVTCTL1
    Relative address:    0x0
    Description:         M3 Event MUXs Selectors.

                        One of three registers that contain selectors to M3 events.
                        There are 10 event MUXs for M3.
                        The selected event goes to ELP module as a wakeup event.

                        INTERNAL NOTES:
                        Event Manager DD - CORE 10 MUXs Selector Table
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-CORE10MUXSelectorTable]
    Default Value:       NA

        Field:           SEL0
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 1st MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL1_SEL0_W                                     6U
#define SOC_AON_M3EVTCTL1_SEL0_M                                     0x0000003FU
#define SOC_AON_M3EVTCTL1_SEL0_S                                     0U
/*

        Field:           SEL1
        From..to bits:   8...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 2nd MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL1_SEL1_W                                     6U
#define SOC_AON_M3EVTCTL1_SEL1_M                                     0x00003F00U
#define SOC_AON_M3EVTCTL1_SEL1_S                                     8U
/*

        Field:           SEL2
        From..to bits:   16...21
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 3rd MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL1_SEL2_W                                     6U
#define SOC_AON_M3EVTCTL1_SEL2_M                                     0x003F0000U
#define SOC_AON_M3EVTCTL1_SEL2_S                                     16U
/*

        Field:           SEL3
        From..to bits:   24...29
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 4th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL1_SEL3_W                                     6U
#define SOC_AON_M3EVTCTL1_SEL3_M                                     0x3F000000U
#define SOC_AON_M3EVTCTL1_SEL3_S                                     24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3IRQCTL2
    Offset name:         SOC_AON_O_M3IRQCTL2
    Relative address:    0x4
    Description:         M3 Event MUXs Selectors.

                        One of three registers that contain selectors to M3 events.
                        There are 10 event MUXs for M3.
                        The selected event goes to ELP module as a wakeup event.

                        INTERNAL NOTES:
                        Event Manager DD - CORE 10 MUXs Selector Table
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-CORE10MUXSelectorTable]
    Default Value:       NA

        Field:           SEL4
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 5th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3IRQCTL2_SEL4_W                                     6U
#define SOC_AON_M3IRQCTL2_SEL4_M                                     0x0000003FU
#define SOC_AON_M3IRQCTL2_SEL4_S                                     0U
/*

        Field:           SEL5
        From..to bits:   8...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 6th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3IRQCTL2_SEL5_W                                     6U
#define SOC_AON_M3IRQCTL2_SEL5_M                                     0x00003F00U
#define SOC_AON_M3IRQCTL2_SEL5_S                                     8U
/*

        Field:           SEL6
        From..to bits:   16...21
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 7th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3IRQCTL2_SEL6_W                                     6U
#define SOC_AON_M3IRQCTL2_SEL6_M                                     0x003F0000U
#define SOC_AON_M3IRQCTL2_SEL6_S                                     16U
/*

        Field:           SEL7
        From..to bits:   24...29
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 8th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3IRQCTL2_SEL7_W                                     6U
#define SOC_AON_M3IRQCTL2_SEL7_M                                     0x3F000000U
#define SOC_AON_M3IRQCTL2_SEL7_S                                     24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3EVTCTL3
    Offset name:         SOC_AON_O_M3EVTCTL3
    Relative address:    0x8
    Description:         M3 Event MUXs Selectors.

                        One of three registers that contain selectors to M3 events.
                        There are 10 event MUXs for M3.
                        The selected event goes to ELP module as a wakeup event.

                        INTERNAL NOTES:
                        Event Manager DD - CORE 10 MUXs Selector Table
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-CORE10MUXSelectorTable]
    Default Value:       NA

        Field:           SEL8
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 9th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL3_SEL8_W                                     6U
#define SOC_AON_M3EVTCTL3_SEL8_M                                     0x0000003FU
#define SOC_AON_M3EVTCTL3_SEL8_S                                     0U
/*

        Field:           SEL9
        From..to bits:   8...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 Event Select Mux.

                         This field selects 10th MUX output to M3 IRQ trough ELP as a wakeup event.

*/
#define SOC_AON_M3EVTCTL3_SEL9_W                                     6U
#define SOC_AON_M3EVTCTL3_SEL9_M                                     0x00003F00U
#define SOC_AON_M3EVTCTL3_SEL9_S                                     8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPEVTCTL
    Offset name:         SOC_AON_O_SPEVTCTL
    Relative address:    0xC
    Description:         Shared Peripherals Event MUXs Selectors.

                        This register selects events to ADC, I2S and PDM.

                        INTERNAL NOTE:
                        Shared Peripherals selector table-
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-SharedPeripheralsMUXSelectorTable]
    Default Value:       NA

        Field:           ADC
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     ADC Event Selector.

                         This field selects event to ADC.

                         INTERNAL NOTE:
                         ADC event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-ADCEventSelectorTable]

*/
#define SOC_AON_SPEVTCTL_ADC_W                                       6U
#define SOC_AON_SPEVTCTL_ADC_M                                       0x0000003FU
#define SOC_AON_SPEVTCTL_ADC_S                                       0U
/*

        Field:           I2S
        From..to bits:   8...14
        DefaultValue:    NA
        Access type:     read-write
        Description:     I2S Event Selector.

                         This field selects event to I2S.

                         INTERNAL NOTE:
                         I2S event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-I2SEventSelectorTable]

*/
#define SOC_AON_SPEVTCTL_I2S_W                                       7U
#define SOC_AON_SPEVTCTL_I2S_M                                       0x00007F00U
#define SOC_AON_SPEVTCTL_I2S_S                                       8U
/*

        Field:           PDM
        From..to bits:   16...22
        DefaultValue:    NA
        Access type:     read-write
        Description:     PDM Event Selector.

                         This field selects event to PDM.

                         INTERNAL NOTE:
                         PDM event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-PDMEventSelectorTable]

*/
#define SOC_AON_SPEVTCTL_PDM_W                                       7U
#define SOC_AON_SPEVTCTL_PDM_M                                       0x007F0000U
#define SOC_AON_SPEVTCTL_PDM_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TMEVTCTL
    Offset name:         SOC_AON_O_TMEVTCTL
    Relative address:    0x10
    Description:         Timers Event MUXs Selectors.

                        This register selects events to SYSTIMER and RTC.
                        There are two MUXs of SYSTIMER and one for RTC.
    Default Value:       NA

        Field:           SYSTM0
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     SYSTIMER Event 1st Selector.

                         This field selects event to SYSTIMER.

                         INTERNAL NOTE:
                         SYSTIMER event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-SysTimerEventSelectorTable]

*/
#define SOC_AON_TMEVTCTL_SYSTM0_W                                    6U
#define SOC_AON_TMEVTCTL_SYSTM0_M                                    0x0000003FU
#define SOC_AON_TMEVTCTL_SYSTM0_S                                    0U
/*

        Field:           SYSTM1
        From..to bits:   8...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     SYSTIMER Event 2nd Selector.

                         This field selects event to SYSTIMER.

                         INTERNAL NOTE:
                         SYSTIMER event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-SysTimerEventSelectorTable]

*/
#define SOC_AON_TMEVTCTL_SYSTM1_W                                    6U
#define SOC_AON_TMEVTCTL_SYSTM1_M                                    0x00003F00U
#define SOC_AON_TMEVTCTL_SYSTM1_S                                    8U
/*

        Field:           RTC
        From..to bits:   16...22
        DefaultValue:    NA
        Access type:     read-write
        Description:     RTC Event Selector.

                         This field selects event to RTC.

                         INTERNAL NOTE:
                         RTC event selector table:
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-RTCEventSelectorTable]

*/
#define SOC_AON_TMEVTCTL_RTC_W                                       7U
#define SOC_AON_TMEVTCTL_RTC_M                                       0x007F0000U
#define SOC_AON_TMEVTCTL_RTC_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPT0EVTCTL0
    Offset name:         SOC_AON_O_GPT0EVTCTL0
    Relative address:    0x14
    Description:         GPTIMER0 Channels Event MUXs Selectors.

                        This register selects events to GPTIMER0. There are 4 event MUXs for GPTIMER Channels.

                        INTERNAL NOTE:
                        GPTIMER0 selector table-
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-GPTIMER0EventSelectorTable]
    Default Value:       NA

        Field:           CH0SEL
        From..to bits:   0...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH0 of GPTIMER0 IRQ.

*/
#define SOC_AON_GPT0EVTCTL0_CH0SEL_W                                 7U
#define SOC_AON_GPT0EVTCTL0_CH0SEL_M                                 0x0000007FU
#define SOC_AON_GPT0EVTCTL0_CH0SEL_S                                 0U
/*

        Field:           CH1SEL
        From..to bits:   7...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH1 of GPTIMER0 IRQ.

*/
#define SOC_AON_GPT0EVTCTL0_CH1SEL_W                                 7U
#define SOC_AON_GPT0EVTCTL0_CH1SEL_M                                 0x00003F80U
#define SOC_AON_GPT0EVTCTL0_CH1SEL_S                                 7U
/*

        Field:           CH2SEL
        From..to bits:   14...20
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH2 of GPTIMER0 IRQ.

*/
#define SOC_AON_GPT0EVTCTL0_CH2SEL_W                                 7U
#define SOC_AON_GPT0EVTCTL0_CH2SEL_M                                 0x001FC000U
#define SOC_AON_GPT0EVTCTL0_CH2SEL_S                                 14U
/*

        Field:           CH3SEL
        From..to bits:   21...27
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH3 of GPTIMER0 IRQ.

*/
#define SOC_AON_GPT0EVTCTL0_CH3SEL_W                                 7U
#define SOC_AON_GPT0EVTCTL0_CH3SEL_M                                 0x0FE00000U
#define SOC_AON_GPT0EVTCTL0_CH3SEL_S                                 21U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPT1EVTCTL0
    Offset name:         SOC_AON_O_GPT1EVTCTL0
    Relative address:    0x18
    Description:         GPTIMER1 Event MUXs Selectors.

                        This register selects events to GPTIMER1. There are 4 event MUXs for GPTIMER Channels.

                        INTERNAL NOTE:
                        GPTIMER1 selector table-
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD-GPTIMER1EventSelectorTable]
    Default Value:       NA

        Field:           CH0SEL
        From..to bits:   0...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH0 of GPTIMER1 IRQ.

*/
#define SOC_AON_GPT1EVTCTL0_CH0SEL_W                                 7U
#define SOC_AON_GPT1EVTCTL0_CH0SEL_M                                 0x0000007FU
#define SOC_AON_GPT1EVTCTL0_CH0SEL_S                                 0U
/*

        Field:           CH1SEL
        From..to bits:   7...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH1 of GPTIMER1 IRQ.

*/
#define SOC_AON_GPT1EVTCTL0_CH1SEL_W                                 7U
#define SOC_AON_GPT1EVTCTL0_CH1SEL_M                                 0x00003F80U
#define SOC_AON_GPT1EVTCTL0_CH1SEL_S                                 7U
/*

        Field:           CH2SEL
        From..to bits:   14...20
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH2 of GPTIMER1 IRQ.

*/
#define SOC_AON_GPT1EVTCTL0_CH2SEL_W                                 7U
#define SOC_AON_GPT1EVTCTL0_CH2SEL_M                                 0x001FC000U
#define SOC_AON_GPT1EVTCTL0_CH2SEL_S                                 14U
/*

        Field:           CH3SEL
        From..to bits:   21...27
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field selects MUX output to CH3 of GPTIMER1 IRQ.

*/
#define SOC_AON_GPT1EVTCTL0_CH3SEL_W                                 7U
#define SOC_AON_GPT1EVTCTL0_CH3SEL_M                                 0x0FE00000U
#define SOC_AON_GPT1EVTCTL0_CH3SEL_S                                 21U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M33CLR
    Offset name:         SOC_AON_O_DB0M33CLR
    Relative address:    0x1C
    Description:         Doorbell 0 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ after handled the massage from M3.
                         type : Write-Clear

*/
#define SOC_AON_DB0M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB0M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB0M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M33SET
    Offset name:         SOC_AON_O_DB0M33SET
    Relative address:    0x20
    Description:         Doorbell 0 M33 Set Register.
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB0M33SET_SET                                        0x00000001U
#define SOC_AON_DB0M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB0M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M33LOCK
    Offset name:         SOC_AON_O_DB0M33LOCK
    Relative address:    0x24
    Description:         Doorbell 0 M33 Lock Bit.
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33  always looses to M3

                         Reading value:
                         	0. not taken
                                 1. taken by M3
                                 2. taken by M33 (should wr IRQ afterwards)
                                 3. invalid.

                         generating the IRQ towards M3 clears the lock.
                         Writing '00' also release the lock.

                         '01' means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB0M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB0M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB0M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M33CLR
    Offset name:         SOC_AON_O_DB1M33CLR
    Relative address:    0x28
    Description:         Doorbell 1 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ after handled the massage from M3.
                         type : Write-Clear

*/
#define SOC_AON_DB1M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB1M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB1M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M33SET
    Offset name:         SOC_AON_O_DB1M33SET
    Relative address:    0x2C
    Description:         Doorbell 1 M33 Set Register.
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB1M33SET_SET                                        0x00000001U
#define SOC_AON_DB1M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB1M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M33LOCK
    Offset name:         SOC_AON_O_DB1M33LOCK
    Relative address:    0x30
    Description:         Doorbell 1 M33 Lock Bit.
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33  always looses to M3

                         Reading value:
                         	0. not taken
                                 1. taken by M3
                                 2. taken by M33 (should wr IRQ afterwards)
                                 3. invalid.

                         generating the IRQ towards M3 clears the lock.
                         Writing '00' also release the lock.

                         '01' means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB1M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB1M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB1M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M33CLR
    Offset name:         SOC_AON_O_DB4M33CLR
    Relative address:    0x34
    Description:         Doorbell 4 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ after handled the massage from M3.
                         type : Write-Clear

*/
#define SOC_AON_DB4M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB4M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB4M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M33SET
    Offset name:         SOC_AON_O_DB4M33SET
    Relative address:    0x38
    Description:         Doorbell 4 M33 Set Register.
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB4M33SET_SET                                        0x00000001U
#define SOC_AON_DB4M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB4M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M33LOCK
    Offset name:         SOC_AON_O_DB4M33LOCK
    Relative address:    0x3C
    Description:         Doorbell 4 M33 Lock Bit.
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33  always looses to M3

                         Reading value:
                         	0. not taken
                                 1. taken by M3
                                 2. taken by M33 (should wr IRQ afterwards)
                                 3. invalid.

                         generating the IRQ towards M3 clears the lock.
                         Writing '00' also release the lock.

                         '01' means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB4M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB4M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB4M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M33CLR
    Offset name:         SOC_AON_O_DB5M33CLR
    Relative address:    0x40
    Description:         Doorbell 5 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ after handled the massage from M3.
                         type : Write-Clear

*/
#define SOC_AON_DB5M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB5M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB5M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M33SET
    Offset name:         SOC_AON_O_DB5M33SET
    Relative address:    0x44
    Description:         Doorbell 5 M33 Set Register.
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB5M33SET_SET                                        0x00000001U
#define SOC_AON_DB5M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB5M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M33LOCK
    Offset name:         SOC_AON_O_DB5M33LOCK
    Relative address:    0x48
    Description:         Doorbell 5 M33 Lock Bit.
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33  always looses to M3

                         Reading value:
                         	0. not taken
                                 1. taken by M3
                                 2. taken by M33 (should wr IRQ afterwards)
                                 3. invalid.

                         generating the IRQ towards M3 clears the lock.
                         Writing '00' also release the lock.

                         '01' means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB5M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB5M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB5M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CMEMSTART
    Offset name:         SOC_AON_O_CMEMSTART
    Relative address:    0x4C
    Description:         CODE Memory MEMSS Start Address.

                        CMEM Start Address-also define S/NS region split. split is in 1k resolution
    Default Value:       0x08000000

        Field:           ADDR
        From..to bits:   12...31
        DefaultValue:    0x8000
        Access type:     read-write
        Description:     CMEM Start Address-also define S/NS region split. split is in 1k resolution

*/
#define SOC_AON_CMEMSTART_ADDR_W                                     20U
#define SOC_AON_CMEMSTART_ADDR_M                                     0xFFFFF000U
#define SOC_AON_CMEMSTART_ADDR_S                                     12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CMEMEND
    Offset name:         SOC_AON_O_CMEMEND
    Relative address:    0x50
    Description:         CODE Memory MEMSS End Address.

                        CMEM end Address-also define S/NS region split
    Default Value:       0x0FFFFFFF

        Field:           ADDR
        From..to bits:   12...31
        DefaultValue:    0xFFFF
        Access type:     read-write
        Description:     CMEM end Address-also define S/NS region split

*/
#define SOC_AON_CMEMEND_ADDR_W                                       20U
#define SOC_AON_CMEMEND_ADDR_M                                       0xFFFFF000U
#define SOC_AON_CMEMEND_ADDR_S                                       12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMEMSTART
    Offset name:         SOC_AON_O_DMEMSTART
    Relative address:    0x54
    Description:         DATA Memory MEMSS Start Address.

                        DMEM Start Address-also define S/NS region split
    Default Value:       0x28000000

        Field:           ADDR
        From..to bits:   12...31
        DefaultValue:    0x28000
        Access type:     read-write
        Description:     DMEM Start Address-also define S/NS region split

*/
#define SOC_AON_DMEMSTART_ADDR_W                                     20U
#define SOC_AON_DMEMSTART_ADDR_M                                     0xFFFFF000U
#define SOC_AON_DMEMSTART_ADDR_S                                     12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMEMEND
    Offset name:         SOC_AON_O_DMEMEND
    Relative address:    0x58
    Description:         DATA Memory MEMSS End Address.

                        DMEM end Address-also define S/NS region split
    Default Value:       0x2FFFFFFF

        Field:           ADDR
        From..to bits:   12...31
        DefaultValue:    0x2FFFF
        Access type:     read-write
        Description:     DMEM end Address-also define S/NS region split

*/
#define SOC_AON_DMEMEND_ADDR_W                                       20U
#define SOC_AON_DMEMEND_ADDR_M                                       0xFFFFF000U
#define SOC_AON_DMEMEND_ADDR_S                                       12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TCMSTART
    Offset name:         SOC_AON_O_TCMSTART
    Relative address:    0x64
    Description:         TCM DATA Memory MEMSS Start Address.

                        TCM data  Start Address-also define S/NS region split
    Default Value:       0x20000000

        Field:           ADDR
        From..to bits:   10...31
        DefaultValue:    0x80000
        Access type:     read-write
        Description:     TCM data  Start Address-also define S/NS region split

*/
#define SOC_AON_TCMSTART_ADDR_W                                      22U
#define SOC_AON_TCMSTART_ADDR_M                                      0xFFFFFC00U
#define SOC_AON_TCMSTART_ADDR_S                                      10U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TCMEND
    Offset name:         SOC_AON_O_TCMEND
    Relative address:    0x68
    Description:         TCM DATA Memory MEMSS End Address.

                        TCM data  end Address-also define S/NS region split
    Default Value:       0x27FFFFFF

        Field:           ADDR
        From..to bits:   10...31
        DefaultValue:    0x9FFFF
        Access type:     read-write
        Description:     TCM data  end Address-also define S/NS region split

*/
#define SOC_AON_TCMEND_ADDR_W                                        22U
#define SOC_AON_TCMEND_ADDR_M                                        0xFFFFFC00U
#define SOC_AON_TCMEND_ADDR_S                                        10U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOEVTS0
    Offset name:         SOC_AON_O_GPIOEVTS0
    Relative address:    0x7C
    Description:         Secured GPIO Event Status, 1st Register.

                        45 bits status over two registers.
    Default Value:       0x00000000

        Field:           STA31TO0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Secured event status , first 32 bits. ([31:0])

*/
#define SOC_AON_GPIOEVTS0_STA31TO0_W                                 32U
#define SOC_AON_GPIOEVTS0_STA31TO0_M                                 0xFFFFFFFFU
#define SOC_AON_GPIOEVTS0_STA31TO0_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOEVTS1
    Offset name:         SOC_AON_O_GPIOEVTS1
    Relative address:    0x80
    Description:         Secured GPIO Event Status, 2nd Register.

                        45 bits status over two registers.
    Default Value:       0x00000000

        Field:           STA44TO32
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Secured event status , 13 MSBs. ([44:32])

*/
#define SOC_AON_GPIOEVTS1_STA44TO32_W                                13U
#define SOC_AON_GPIOEVTS1_STA44TO32_M                                0x00001FFFU
#define SOC_AON_GPIOEVTS1_STA44TO32_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSSCTL0
    Offset name:         SOC_AON_O_MEMSSCTL0
    Relative address:    0x84
    Description:         MEMSS General Control Register.

                        This register controls starvation mechanism counter value and MEMSS bus fault mask.
    Default Value:       0x00000000

        Field:           STRVCNTV
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Starvation Counter Value Configuration.

                         That value reflect how long writing to mailbox can be delayed.

*/
#define SOC_AON_MEMSSCTL0_STRVCNTV_W                                 3U
#define SOC_AON_MEMSSCTL0_STRVCNTV_M                                 0x00000007U
#define SOC_AON_MEMSSCTL0_STRVCNTV_S                                 0U
/*

        Field:           BFLTMASK
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     MEMSS Bus Fault Mask

                         1. Mask
                         0. Do not mask

*/
#define SOC_AON_MEMSSCTL0_BFLTMASK                                   0x00000008U
#define SOC_AON_MEMSSCTL0_BFLTMASK_M                                 0x00000008U
#define SOC_AON_MEMSSCTL0_BFLTMASK_S                                 3U
/*

        Field:           BFLTMSTA
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus Fault Masked Status.

                         Out of Memory Index:
                         0. No error
                         1. M33 Code
                         2. M33 Data #1 + #2
                         3. M3 Code
                         4. M3 Data
                         5. M3 PRAM
                         6. BLE Code
                         7. Global OCP

*/
#define SOC_AON_MEMSSCTL0_BFLTMSTA_W                                 3U
#define SOC_AON_MEMSSCTL0_BFLTMSTA_M                                 0x00000070U
#define SOC_AON_MEMSSCTL0_BFLTMSTA_S                                 4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSSCTL1
    Offset name:         SOC_AON_O_MEMSSCTL1
    Relative address:    0x88
    Description:         MEMSS General Control Register.

                        This is a status register for bus fault raw status.
    Default Value:       0x00000000

        Field:           BFLTRWSTA
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus Fault Raw Status.
                         Error indication from memss.

                         Out of Memory Index:
                         0. No error
                         1. M33 Code
                         2. M33 Data #1 + #2
                         3. M3 Code
                         4. M3 Data
                         5. M3 PRAM
                         6. BLE Code
                         7. Global OCP

                         Type: Read-Clear

*/
#define SOC_AON_MEMSSCTL1_BFLTRWSTA_W                                3U
#define SOC_AON_MEMSSCTL1_BFLTRWSTA_M                                0x00000007U
#define SOC_AON_MEMSSCTL1_BFLTRWSTA_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE0
    Offset name:         SOC_AON_O_SPARE0
    Relative address:    0x90
    Description:         Spare Register.
                        This is a spare register in M33S aperture.
    Default Value:       0x00000000

        Field:           BF
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Spare Field.

                         Non-locked , M33S aperture.

*/
#define SOC_AON_SPARE0_BF_W                                          4U
#define SOC_AON_SPARE0_BF_M                                          0x0000000FU
#define SOC_AON_SPARE0_BF_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       VTORS
    Offset name:         SOC_AON_O_VTORS
    Relative address:    0x9C
    Description:         M33 Secure Vector Table Base Address.
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   7...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     init VTOR Secured Address.

*/
#define SOC_AON_VTORS_ADDR_W                                         25U
#define SOC_AON_VTORS_ADDR_M                                         0xFFFFFF80U
#define SOC_AON_VTORS_ADDR_S                                         7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       VTORNS
    Offset name:         SOC_AON_O_VTORNS
    Relative address:    0xA0
    Description:         M33 Non-Secure Vector Table Base Address.
    Default Value:       0x00000000

        Field:           ADDR
        From..to bits:   7...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     init VTOR non Secured address

*/
#define SOC_AON_VTORNS_ADDR_W                                        25U
#define SOC_AON_VTORNS_ADDR_M                                        0xFFFFFF80U
#define SOC_AON_VTORNS_ADDR_S                                        7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CPULOCKS
    Offset name:         SOC_AON_O_CPULOCKS
    Relative address:    0xA8
    Description:         CPU Locks.

                        This register contain 5 locks. Issued to M33 Cortex and used to lock internal cortex registers.
                        LOCKSVTAIRCR, LOCKNSVTOR, LOCKSMPU, LOCKNSMPU, LOCKSAU.
    Default Value:       0x00000000

        Field:           SVTAIRCR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Locking this Cortex internal configuration

*/
#define SOC_AON_CPULOCKS_SVTAIRCR                                    0x00000001U
#define SOC_AON_CPULOCKS_SVTAIRCR_M                                  0x00000001U
#define SOC_AON_CPULOCKS_SVTAIRCR_S                                  0U
/*

        Field:           NSVTOR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Locking this Cortex internal configuration

*/
#define SOC_AON_CPULOCKS_NSVTOR                                      0x00000002U
#define SOC_AON_CPULOCKS_NSVTOR_M                                    0x00000002U
#define SOC_AON_CPULOCKS_NSVTOR_S                                    1U
/*

        Field:           SMPU
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Locking this Cortex internal configuration

*/
#define SOC_AON_CPULOCKS_SMPU                                        0x00000004U
#define SOC_AON_CPULOCKS_SMPU_M                                      0x00000004U
#define SOC_AON_CPULOCKS_SMPU_S                                      2U
/*

        Field:           NSPMU
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Locking this Cortex internal configuration

*/
#define SOC_AON_CPULOCKS_NSPMU                                       0x00000008U
#define SOC_AON_CPULOCKS_NSPMU_M                                     0x00000008U
#define SOC_AON_CPULOCKS_NSPMU_S                                     3U
/*

        Field:           SAU
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Locking this Cortex internal configuration

*/
#define SOC_AON_CPULOCKS_SAU                                         0x00000010U
#define SOC_AON_CPULOCKS_SAU_M                                       0x00000010U
#define SOC_AON_CPULOCKS_SAU_S                                       4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HOSTLOCKS
    Offset name:         SOC_AON_O_HOSTLOCKS
    Relative address:    0xAC
    Description:         Host Lock Signals.

                        lock once. Do Not lock until written.
                        When written Locked immediately,
                        cleared only at soc aon reset or por reset.
                        These are host security lock configurations (some can be also locked by TI)
    Default Value:       0x00000000

        Field:           CACHE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of ICACHE

*/
#define SOC_AON_HOSTLOCKS_CACHE                                      0x00000001U
#define SOC_AON_HOSTLOCKS_CACHE_M                                    0x00000001U
#define SOC_AON_HOSTLOCKS_CACHE_S                                    0U
/*

        Field:           M33
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of Host MCU, both Secured and non Secured

*/
#define SOC_AON_HOSTLOCKS_M33                                        0x00000002U
#define SOC_AON_HOSTLOCKS_M33_M                                      0x00000002U
#define SOC_AON_HOSTLOCKS_M33_S                                      1U
/*

        Field:           MEMSSANDFW
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of Memory Sub System

*/
#define SOC_AON_HOSTLOCKS_MEMSSANDFW                                 0x00000004U
#define SOC_AON_HOSTLOCKS_MEMSSANDFW_M                               0x00000004U
#define SOC_AON_HOSTLOCKS_MEMSSANDFW_S                               2U
/*

        Field:           DMA
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of System DMA

*/
#define SOC_AON_HOSTLOCKS_DMA                                        0x00000008U
#define SOC_AON_HOSTLOCKS_DMA_M                                      0x00000008U
#define SOC_AON_HOSTLOCKS_DMA_S                                      3U
/*

        Field:           FLASH
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of On The Fly Enc/Decryption Module Region Related Registers (four registers per region, four regions)

*/
#define SOC_AON_HOSTLOCKS_FLASH                                      0x00000010U
#define SOC_AON_HOSTLOCKS_FLASH_M                                    0x00000010U
#define SOC_AON_HOSTLOCKS_FLASH_S                                    4U
/*

        Field:           M3EVT
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations of M3 Events

*/
#define SOC_AON_HOSTLOCKS_M3EVT                                      0x00000020U
#define SOC_AON_HOSTLOCKS_M3EVT_M                                    0x00000020U
#define SOC_AON_HOSTLOCKS_M3EVT_S                                    5U
/*

        Field:           PERIPHEVT
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the firewall configurations of: HIF, CORE, CORE AON, HSM, shared Periphs

*/
#define SOC_AON_HOSTLOCKS_PERIPHEVT                                  0x00000040U
#define SOC_AON_HOSTLOCKS_PERIPHEVT_M                                0x00000040U
#define SOC_AON_HOSTLOCKS_PERIPHEVT_S                                6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HOSTBOOT
    Offset name:         SOC_AON_O_HOSTBOOT
    Relative address:    0xB0
    Description:         Host Boot Done

                        1 lock. Write once.
                        Asserted by FW by the end of soc boot done Or in elevated mode
                        By either by TI of by the host
                        and indicates device exit from secure boot mode.

                        this signal also locks host security configurations ,
                        Locked immediately ,
                        cleared only at soc aon reset or por reset
    Default Value:       0x00000000

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking host security configurations

*/
#define SOC_AON_HOSTBOOT_DONE                                        0x00000001U
#define SOC_AON_HOSTBOOT_DONE_M                                      0x00000001U
#define SOC_AON_HOSTBOOT_DONE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECCFG
    Offset name:         SOC_AON_O_SECCFG
    Relative address:    0xB4
    Description:         Security Configurations.
    Default Value:       NA

        Field:           BLKDMA
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This Field blocks the uDMA transactions to CMEM.

                         0. un-Block
                         1. Block

*/
#define SOC_AON_SECCFG_BLKDMA                                        0x00000001U
#define SOC_AON_SECCFG_BLKDMA_M                                      0x00000001U
#define SOC_AON_SECCFG_BLKDMA_S                                      0U
/*

        Field:           SELNSIRQ
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field determine whether the 4 SW interrupts MSbits will be owned by secured/non secured.

                         0. Non-Secured
                         1. Secured

*/
#define SOC_AON_SECCFG_SELNSIRQ                                      0x00000002U
#define SOC_AON_SECCFG_SELNSIRQ_M                                    0x00000002U
#define SOC_AON_SECCFG_SELNSIRQ_S                                    1U
/*

        Field:           BLKSBSWR
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLOCK SBUS WRITE LOCK

                         Enable this field to block sbus write transactions

*/
#define SOC_AON_SECCFG_BLKSBSWR                                      0x00000004U
#define SOC_AON_SECCFG_BLKSBSWR_M                                    0x00000004U
#define SOC_AON_SECCFG_BLKSBSWR_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSIMASK
    Offset name:         SOC_AON_O_DBSIMASK
    Relative address:    0xB8
    Description:         Doorbell M33 Secured IMASK.
                        Mask Event.

                        0. CLR - Clear Interrupt Mask
                        1. SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBSIMASK_IMASK_W                                     4U
#define SOC_AON_DBSIMASK_IMASK_M                                     0x0000000FU
#define SOC_AON_DBSIMASK_IMASK_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSISET
    Offset name:         SOC_AON_O_DBSISET
    Relative address:    0xBC
    Description:         Doorbell M33 Secured ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBSISET_ISET_W                                       4U
#define SOC_AON_DBSISET_ISET_M                                       0x0000000FU
#define SOC_AON_DBSISET_ISET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSICLR
    Offset name:         SOC_AON_O_DBSICLR
    Relative address:    0xC0
    Description:         Doorbell M33 Secured ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBSICLR_ICLR_W                                       4U
#define SOC_AON_DBSICLR_ICLR_M                                       0x0000000FU
#define SOC_AON_DBSICLR_ICLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSIMSET
    Offset name:         SOC_AON_O_DBSIMSET
    Relative address:    0xC4
    Description:         Doorbell M33 Secured IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBSIMSET_IMSET_W                                     4U
#define SOC_AON_DBSIMSET_IMSET_M                                     0x0000000FU
#define SOC_AON_DBSIMSET_IMSET_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSIMCLR
    Offset name:         SOC_AON_O_DBSIMCLR
    Relative address:    0xC8
    Description:         Doorbell M33 Secured IMCLR.
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBSIMCLR_IMCLR_W                                     4U
#define SOC_AON_DBSIMCLR_IMCLR_M                                     0x0000000FU
#define SOC_AON_DBSIMCLR_IMCLR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSRIS
    Offset name:         SOC_AON_O_DBSRIS
    Relative address:    0xCC
    Description:         Doorbell M33 Secured RIS.
                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBSRIS_RIS_W                                         4U
#define SOC_AON_DBSRIS_RIS_M                                         0x0000000FU
#define SOC_AON_DBSRIS_RIS_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBSMIS
    Offset name:         SOC_AON_O_DBSMIS
    Relative address:    0xD0
    Description:         Doorbell M33 Secured MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits division to events:

                         bit [3] - doorbell 5 M3 IRQ
                         bit [2] - doorbell 4 M3 IRQ
                         bit [1] - doorbell 1 M3 IRQ
                         bit [0] - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBSMIS_MIS_W                                         4U
#define SOC_AON_DBSMIS_MIS_M                                         0x0000000FU
#define SOC_AON_DBSMIS_MIS_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSIMASK
    Offset name:         SOC_AON_O_ERRSIMASK
    Relative address:    0xD4
    Description:         M33 Secured Error IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

*/
#define SOC_AON_ERRSIMASK_IMASK_W                                    9U
#define SOC_AON_ERRSIMASK_IMASK_M                                    0x000001FFU
#define SOC_AON_ERRSIMASK_IMASK_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSISET
    Offset name:         SOC_AON_O_ERRSISET
    Relative address:    0xD8
    Description:         M33 Secured Error ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error
                         Type: Write-Clear

*/
#define SOC_AON_ERRSISET_ISET_W                                      9U
#define SOC_AON_ERRSISET_ISET_M                                      0x000001FFU
#define SOC_AON_ERRSISET_ISET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSICLR
    Offset name:         SOC_AON_O_ERRSICLR
    Relative address:    0xDC
    Description:         M33 Secured Error ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

                         Type: Write-Clear

*/
#define SOC_AON_ERRSICLR_ICLR_W                                      9U
#define SOC_AON_ERRSICLR_ICLR_M                                      0x000001FFU
#define SOC_AON_ERRSICLR_ICLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSIMSET
    Offset name:         SOC_AON_O_ERRSIMSET
    Relative address:    0xE0
    Description:         M33 Secured Error IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

                         Type: Write-Clear

*/
#define SOC_AON_ERRSIMSET_IMSET_W                                    9U
#define SOC_AON_ERRSIMSET_IMSET_M                                    0x000001FFU
#define SOC_AON_ERRSIMSET_IMSET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSIMCLR
    Offset name:         SOC_AON_O_ERRSIMCLR
    Relative address:    0xE4
    Description:         M33 Secured Error IMCLR.
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

                         Type: Write-Clear

*/
#define SOC_AON_ERRSIMCLR_IMCLR_W                                    9U
#define SOC_AON_ERRSIMCLR_IMCLR_M                                    0x000001FFU
#define SOC_AON_ERRSIMCLR_IMCLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSRIS
    Offset name:         SOC_AON_O_ERRSRIS
    Relative address:    0xE8
    Description:         M33 Secured Error RIS.
                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

*/
#define SOC_AON_ERRSRIS_RIS_W                                        9U
#define SOC_AON_ERRSRIS_RIS_M                                        0x000001FFU
#define SOC_AON_ERRSRIS_RIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSMIS
    Offset name:         SOC_AON_O_ERRSMIS
    Relative address:    0xEC
    Description:         M33 Secured Error MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits division to events:

                         bit[8] - UDMA ERR IRQ
                         bit[7] - CORE ELP WATCHDOG Timer
                         bit[6] - SOC IC IRQs - Address Watch
                         bit[5] - SOC IC IRQs - IC Timeout
                         bit[4] - SOC IC IRQs - serror
                         bit[3] - CORE to SDIO WATCHDOG
                         bit[2] - PLL Unlock
                         bit[1] - MEMss bus fault
                         bit[0] - HSM fatal error

*/
#define SOC_AON_ERRSMIS_MIS_W                                        9U
#define SOC_AON_ERRSMIS_MIS_M                                        0x000001FFU
#define SOC_AON_ERRSMIS_MIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPT0EVTCTL1
    Offset name:         SOC_AON_O_GPT0EVTCTL1
    Relative address:    0xF0
    Description:         GPTIMER0 Sync, Tick Enable and Fault Event MUXs Selectors.

                        This register selects events to GPTIMER0.

                        INTERNAL NOTE:
                        GPTIMER0 selector table-
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD]
    Default Value:       NA

        Field:           SYNC
        From..to bits:   0...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects sync MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT0EVTCTL1_SYNC_W                                   7U
#define SOC_AON_GPT0EVTCTL1_SYNC_M                                   0x0000007FU
#define SOC_AON_GPT0EVTCTL1_SYNC_S                                   0U
/*

        Field:           TICKEN
        From..to bits:   8...14
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects tick enable MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT0EVTCTL1_TICKEN_W                                 7U
#define SOC_AON_GPT0EVTCTL1_TICKEN_M                                 0x00007F00U
#define SOC_AON_GPT0EVTCTL1_TICKEN_S                                 8U
/*

        Field:           FAULT
        From..to bits:   16...22
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects fault MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT0EVTCTL1_FAULT_W                                  7U
#define SOC_AON_GPT0EVTCTL1_FAULT_M                                  0x007F0000U
#define SOC_AON_GPT0EVTCTL1_FAULT_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPT1EVTCTL1
    Offset name:         SOC_AON_O_GPT1EVTCTL1
    Relative address:    0xF4
    Description:         GPTIMER1 Sync, Tick Enable and Fault Event MUXs Selectors.

                        This register selects events to GPTIMER1.

                        INTERNAL NOTE:
                        GPTIMER0 selector table-
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Event+Manager+DD#EventManagerDD]
    Default Value:       NA

        Field:           SYNC
        From..to bits:   0...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects sync MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT1EVTCTL1_SYNC_W                                   7U
#define SOC_AON_GPT1EVTCTL1_SYNC_M                                   0x0000007FU
#define SOC_AON_GPT1EVTCTL1_SYNC_S                                   0U
/*

        Field:           TICKEN
        From..to bits:   8...14
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects tick enable MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT1EVTCTL1_TICKEN_W                                 7U
#define SOC_AON_GPT1EVTCTL1_TICKEN_M                                 0x00007F00U
#define SOC_AON_GPT1EVTCTL1_TICKEN_S                                 8U
/*

        Field:           FAULT
        From..to bits:   16...22
        DefaultValue:    NA
        Access type:     read-write
        Description:     Selects fault MUX output to GPTIMER0 IRQ

*/
#define SOC_AON_GPT1EVTCTL1_FAULT_W                                  7U
#define SOC_AON_GPT1EVTCTL1_FAULT_M                                  0x007F0000U
#define SOC_AON_GPT1EVTCTL1_FAULT_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESMSTACST
    Offset name:         SOC_AON_O_ESMSTACST
    Relative address:    0x104
    Description:         Customer ESMs Status.
                        status register , for each of the ESM (enable sequence monitor) what is the status  (Done, violated, or None)
                        Final ESM status for the entire ESM - ESM machine + magic value comparators
    Default Value:       NA

        Field:           ESM1DONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field indicates that ESM1 is done.

*/
#define SOC_AON_ESMSTACST_ESM1DONE                                   0x00000001U
#define SOC_AON_ESMSTACST_ESM1DONE_M                                 0x00000001U
#define SOC_AON_ESMSTACST_ESM1DONE_S                                 0U
/*

        Field:           ESM1VIO
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field indicates that ESM1 is violated.

*/
#define SOC_AON_ESMSTACST_ESM1VIO                                    0x00000002U
#define SOC_AON_ESMSTACST_ESM1VIO_M                                  0x00000002U
#define SOC_AON_ESMSTACST_ESM1VIO_S                                  1U
/*

        Field:           ESM2DONE
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field indicates that ESM2 is done.

*/
#define SOC_AON_ESMSTACST_ESM2DONE                                   0x00000100U
#define SOC_AON_ESMSTACST_ESM2DONE_M                                 0x00000100U
#define SOC_AON_ESMSTACST_ESM2DONE_S                                 8U
/*

        Field:           ESM2VIO
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field indicates that ESM1 is violated.

*/
#define SOC_AON_ESMSTACST_ESM2VIO                                    0x00000200U
#define SOC_AON_ESMSTACST_ESM2VIO_M                                  0x00000200U
#define SOC_AON_ESMSTACST_ESM2VIO_S                                  9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSSCFG
    Offset name:         SOC_AON_O_MEMSSCFG
    Relative address:    0x10C
    Description:         MEMSS Configurations.
                        Supported Memory configurations:

                        Functional Modes:
                        0x0. Baseline
                        0x1. Extended M3
                        0x2. Extended throughput
                        0x3. Extended throughput + WIFI features
                        0x4. Extended Host Execution
                        0x5. Extended M33 Data
                        Debug Modes (OCLA Memory):
                        0x6. Core debug (<M33 Data)
                        0x7. Core debug Extended throughput (<M33 Data <M3 Exec)
                        0x8. Core debug PHY only (<M3,M33 Data)
                        0x9. Host debug (<M3 Exec)
                        0xA. Host debug extended Host Execution
                        0xB. Host debug extended M33 Data
    Default Value:       NA

        Field:           MODE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     MEMSS mode of bank ownership

*/
#define SOC_AON_MEMSSCFG_MODE_W                                      4U
#define SOC_AON_MEMSSCFG_MODE_M                                      0x0000000FU
#define SOC_AON_MEMSSCFG_MODE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOMIS0S
    Offset name:         SOC_AON_O_GPIOMIS0S
    Relative address:    0x138
    Description:         Secured Gpio MIS.
    Default Value:       NA

        Field:           31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     32 LSBs of MIS. (45 Total)

*/
#define SOC_AON_GPIOMIS0S_31TO0_W                                    32U
#define SOC_AON_GPIOMIS0S_31TO0_M                                    0xFFFFFFFFU
#define SOC_AON_GPIOMIS0S_31TO0_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOMIS1S
    Offset name:         SOC_AON_O_GPIOMIS1S
    Relative address:    0x13C
    Description:         Secured Gpio MIS.
    Default Value:       NA

        Field:           44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     13 MSBs of MIS. (45 Total)

*/
#define SOC_AON_GPIOMIS1S_44TO32_W                                   13U
#define SOC_AON_GPIOMIS1S_44TO32_M                                   0x00001FFFU
#define SOC_AON_GPIOMIS1S_44TO32_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOFNC0S
    Offset name:         SOC_AON_O_GPIOFNC0S
    Relative address:    0x140
    Description:         Secured GPIO Functional Mask.

                        0. Mask
                        1. Un-Mask
    Default Value:       NA

        Field:           MASK31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     32 LSBs of MASK. (45 Total)

*/
#define SOC_AON_GPIOFNC0S_MASK31TO0_W                                32U
#define SOC_AON_GPIOFNC0S_MASK31TO0_M                                0xFFFFFFFFU
#define SOC_AON_GPIOFNC0S_MASK31TO0_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOFNC1S
    Offset name:         SOC_AON_O_GPIOFNC1S
    Relative address:    0x144
    Description:         Secured GPIO Functional Mask.

                        0. Mask
                        1. Un-Mask
    Default Value:       NA

        Field:           MASK44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     13 MSBs of MASK. (45 Total)

*/
#define SOC_AON_GPIOFNC1S_MASK44TO32_W                               13U
#define SOC_AON_GPIOFNC1S_MASK44TO32_M                               0x00001FFFU
#define SOC_AON_GPIOFNC1S_MASK44TO32_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE1
    Offset name:         SOC_AON_O_SPARE1
    Relative address:    0x148
    Description:         Spare Reg, M33S Aperture.
                        non-locked.
    Default Value:       0x00000000

        Field:           BF
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M33S spare register.
                         not locked.

*/
#define SOC_AON_SPARE1_BF_W                                          4U
#define SOC_AON_SPARE1_BF_M                                          0x0000000FU
#define SOC_AON_SPARE1_BF_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1VAL2ND
    Offset name:         SOC_AON_O_ESM1VAL2ND
    Relative address:    0x14C
    Description:         ESM1 2nd Magic Value.
                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow additional protection on ESM and also allow vendor to unmask ESM only at the end of vendor secure boot (SBL) is completed
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 2nd magic value

*/
#define SOC_AON_ESM1VAL2ND_MGCVAL_W                                  8U
#define SOC_AON_ESM1VAL2ND_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM1VAL2ND_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2VAL2ND
    Offset name:         SOC_AON_O_ESM2VAL2ND
    Relative address:    0x150
    Description:         ESM2 2nd Magic Value.
                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow additional protection on ESM and also allow vendor to unmask ESM only at the end of vendor secure boot (SBL) is completed
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 2nd magic value

*/
#define SOC_AON_ESM2VAL2ND_MGCVAL_W                                  8U
#define SOC_AON_ESM2VAL2ND_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM2VAL2ND_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1STA2ND
    Offset name:         SOC_AON_O_ESM1STA2ND
    Relative address:    0x154
    Description:         ESM1 2nd Magic Value Status.
                        ESM magic value match indication.
    Default Value:       NA

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val match

*/
#define SOC_AON_ESM1STA2ND_DONE                                      0x00000001U
#define SOC_AON_ESM1STA2ND_DONE_M                                    0x00000001U
#define SOC_AON_ESM1STA2ND_DONE_S                                    0U
/*

        Field:           FAULT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM1STA2ND_FAULT                                     0x00000002U
#define SOC_AON_ESM1STA2ND_FAULT_M                                   0x00000002U
#define SOC_AON_ESM1STA2ND_FAULT_S                                   1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2STA2ND
    Offset name:         SOC_AON_O_ESM2STA2ND
    Relative address:    0x158
    Description:         ESM2 2nd Magic Value.
                        ESM magic value match indication.
    Default Value:       NA

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val match

*/
#define SOC_AON_ESM2STA2ND_DONE                                      0x00000001U
#define SOC_AON_ESM2STA2ND_DONE_M                                    0x00000001U
#define SOC_AON_ESM2STA2ND_DONE_S                                    0U
/*

        Field:           FAULT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM2STA2ND_FAULT                                     0x00000002U
#define SOC_AON_ESM2STA2ND_FAULT_M                                   0x00000002U
#define SOC_AON_ESM2STA2ND_FAULT_S                                   1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGHOST
    Offset name:         SOC_AON_O_FWCFGHOST
    Relative address:    0x15C
    Description:         HOST FW Bypass.
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     bypass the following module's firewall configuration:
                         IOMUX_COMMON_SEL
                         PRCM_AON_HOST
                         PRCM_AON_COMMON
                         SCRATCHPAD
                         PLLSHARING
                         SOC_IC
                         SOC_AON_M33_S
                         SOC_AON_M33_NS
                         SOC_AAON_M33_S
                         SOC_AAON_M33_NS
                         RTC
                         XIP_OSPI
                         XIP_OSPI_INDAC
                         XIP_GENERAL
                         XIP_UDMA_SEC
                         XIP_UDMA_NON_SEC
                         OTFDE_REGION0-3
                         HOST_DMA_GENERAL_CFG

*/
#define SOC_AON_FWCFGHOST_BYPASS                                     0x00000001U
#define SOC_AON_FWCFGHOST_BYPASS_M                                   0x00000001U
#define SOC_AON_FWCFGHOST_BYPASS_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGDMA
    Offset name:         SOC_AON_O_FWCFGDMA
    Relative address:    0x160
    Description:         DMA FW BYPASS
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Bypass the firewall configuration for HOST_DMA module

*/
#define SOC_AON_FWCFGDMA_BYPASS                                      0x00000001U
#define SOC_AON_FWCFGDMA_BYPASS_M                                    0x00000001U
#define SOC_AON_FWCFGDMA_BYPASS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGFPRPH
    Offset name:         SOC_AON_O_FWCFGFPRPH
    Relative address:    0x164
    Description:         Peripheral Firewall Bypass.
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     bypass the following module's firewall configuration:
                         HIF
                         HSM
                         CORE_AON
                         I2C0/1
                         SPI0/1
                         UART0/1
                         GPTIMER0/1
                         I2S
                         PDM
                         CAN
                         ADC
                         SDMMC
                         SDIO

*/
#define SOC_AON_FWCFGFPRPH_BYPASS                                    0x00000001U
#define SOC_AON_FWCFGFPRPH_BYPASS_M                                  0x00000001U
#define SOC_AON_FWCFGFPRPH_BYPASS_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGM33
    Offset name:         SOC_AON_O_FWCFGM33
    Relative address:    0x168
    Description:         HOST MCU Firewall Bypass
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     bypass the firewall configuration for HOST MCU module.

*/
#define SOC_AON_FWCFGM33_BYPASS                                      0x00000001U
#define SOC_AON_FWCFGM33_BYPASS_M                                    0x00000001U
#define SOC_AON_FWCFGM33_BYPASS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGMEMSS
    Offset name:         SOC_AON_O_FWCFGMEMSS
    Relative address:    0x16C
    Description:         MEMSS Firewall Bypass
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     bypass the Firewall configuration for MEMSS module.

*/
#define SOC_AON_FWCFGMEMSS_BYPASS                                    0x00000001U
#define SOC_AON_FWCFGMEMSS_BYPASS_M                                  0x00000001U
#define SOC_AON_FWCFGMEMSS_BYPASS_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOGENSEL
    Offset name:         SOC_AON_O_FWIOGENSEL
    Relative address:    0x170
    Description:         IOMUX General firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOGENSEL_M33NS                                     0x00000001U
#define SOC_AON_FWIOGENSEL_M33NS_M                                   0x00000001U
#define SOC_AON_FWIOGENSEL_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOGENSEL_M33S                                      0x00000002U
#define SOC_AON_FWIOGENSEL_M33S_M                                    0x00000002U
#define SOC_AON_FWIOGENSEL_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOGENSEL_CORENS                                    0x00000004U
#define SOC_AON_FWIOGENSEL_CORENS_M                                  0x00000004U
#define SOC_AON_FWIOGENSEL_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWPRCMHOST
    Offset name:         SOC_AON_O_FWPRCMHOST
    Relative address:    0x174
    Description:         PRCM_HOST firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33S
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMHOST_M33S                                      0x00000001U
#define SOC_AON_FWPRCMHOST_M33S_M                                    0x00000001U
#define SOC_AON_FWPRCMHOST_M33S_S                                    0U
/*

        Field:           CORENS
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMHOST_CORENS                                    0x00000002U
#define SOC_AON_FWPRCMHOST_CORENS_M                                  0x00000002U
#define SOC_AON_FWPRCMHOST_CORENS_S                                  1U
/*

        Field:           M33NS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMHOST_M33NS                                     0x00000004U
#define SOC_AON_FWPRCMHOST_M33NS_M                                   0x00000004U
#define SOC_AON_FWPRCMHOST_M33NS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWPRCMSPAD
    Offset name:         SOC_AON_O_FWPRCMSPAD
    Relative address:    0x178
    Description:         M33 SCRATCHPAD firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMSPAD_M33NS                                     0x00000001U
#define SOC_AON_FWPRCMSPAD_M33NS_M                                   0x00000001U
#define SOC_AON_FWPRCMSPAD_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMSPAD_M33S                                      0x00000002U
#define SOC_AON_FWPRCMSPAD_M33S_M                                    0x00000002U
#define SOC_AON_FWPRCMSPAD_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMSPAD_CORENS                                    0x00000004U
#define SOC_AON_FWPRCMSPAD_CORENS_M                                  0x00000004U
#define SOC_AON_FWPRCMSPAD_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWPRCMCMN
    Offset name:         SOC_AON_O_FWPRCMCMN
    Relative address:    0x17C
    Description:         PRCM_COMMON firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33SWR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_M33SWR                                     0x00000001U
#define SOC_AON_FWPRCMCMN_M33SWR_M                                   0x00000001U
#define SOC_AON_FWPRCMCMN_M33SWR_S                                   0U
/*

        Field:           M33SRD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_M33SRD                                     0x00000002U
#define SOC_AON_FWPRCMCMN_M33SRD_M                                   0x00000002U
#define SOC_AON_FWPRCMCMN_M33SRD_S                                   1U
/*

        Field:           M33NSWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_M33NSWR                                    0x00000004U
#define SOC_AON_FWPRCMCMN_M33NSWR_M                                  0x00000004U
#define SOC_AON_FWPRCMCMN_M33NSWR_S                                  2U
/*

        Field:           M33NSRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_M33NSRD                                    0x00000008U
#define SOC_AON_FWPRCMCMN_M33NSRD_M                                  0x00000008U
#define SOC_AON_FWPRCMCMN_M33NSRD_S                                  3U
/*

        Field:           CORENSWR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_CORENSWR                                   0x00000010U
#define SOC_AON_FWPRCMCMN_CORENSWR_M                                 0x00000010U
#define SOC_AON_FWPRCMCMN_CORENSWR_S                                 4U
/*

        Field:           CORENSRD
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCMCMN_CORENSRD                                   0x00000020U
#define SOC_AON_FWPRCMCMN_CORENSRD_M                                 0x00000020U
#define SOC_AON_FWPRCMCMN_CORENSRD_S                                 5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCKM
    Offset name:         SOC_AON_O_FWCKM
    Relative address:    0x180
    Description:         CKM firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCKM_M33NS                                          0x00000001U
#define SOC_AON_FWCKM_M33NS_M                                        0x00000001U
#define SOC_AON_FWCKM_M33NS_S                                        0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCKM_M33S                                           0x00000002U
#define SOC_AON_FWCKM_M33S_M                                         0x00000002U
#define SOC_AON_FWCKM_M33S_S                                         1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCKM_CORENS                                         0x00000004U
#define SOC_AON_FWCKM_CORENS_M                                       0x00000004U
#define SOC_AON_FWCKM_CORENS_S                                       2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSOCIC
    Offset name:         SOC_AON_O_FWSOCIC
    Relative address:    0x184
    Description:         SOC_IC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NSWR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_M33NSWR                                      0x00000001U
#define SOC_AON_FWSOCIC_M33NSWR_M                                    0x00000001U
#define SOC_AON_FWSOCIC_M33NSWR_S                                    0U
/*

        Field:           M33NSRD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_M33NSRD                                      0x00000002U
#define SOC_AON_FWSOCIC_M33NSRD_M                                    0x00000002U
#define SOC_AON_FWSOCIC_M33NSRD_S                                    1U
/*

        Field:           M33SWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_M33SWR                                       0x00000004U
#define SOC_AON_FWSOCIC_M33SWR_M                                     0x00000004U
#define SOC_AON_FWSOCIC_M33SWR_S                                     2U
/*

        Field:           M33SRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_M33SRD                                       0x00000008U
#define SOC_AON_FWSOCIC_M33SRD_M                                     0x00000008U
#define SOC_AON_FWSOCIC_M33SRD_S                                     3U
/*

        Field:           CORENSWR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_CORENSWR                                     0x00000010U
#define SOC_AON_FWSOCIC_CORENSWR_M                                   0x00000010U
#define SOC_AON_FWSOCIC_CORENSWR_S                                   4U
/*

        Field:           CORENSRD
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSOCIC_CORENSRD                                     0x00000020U
#define SOC_AON_FWSOCIC_CORENSRD_M                                   0x00000020U
#define SOC_AON_FWSOCIC_CORENSRD_S                                   5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAONM33S
    Offset name:         SOC_AON_O_FWAONM33S
    Relative address:    0x188
    Description:         AON_M33_S firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33S_M33NS                                      0x00000001U
#define SOC_AON_FWAONM33S_M33NS_M                                    0x00000001U
#define SOC_AON_FWAONM33S_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33S_M33S                                       0x00000002U
#define SOC_AON_FWAONM33S_M33S_M                                     0x00000002U
#define SOC_AON_FWAONM33S_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33S_CORENS                                     0x00000004U
#define SOC_AON_FWAONM33S_CORENS_M                                   0x00000004U
#define SOC_AON_FWAONM33S_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAONM33NS
    Offset name:         SOC_AON_O_FWAONM33NS
    Relative address:    0x18C
    Description:         AON_M33_NS firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33NS_M33NS                                     0x00000001U
#define SOC_AON_FWAONM33NS_M33NS_M                                   0x00000001U
#define SOC_AON_FWAONM33NS_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33NS_M33S                                      0x00000002U
#define SOC_AON_FWAONM33NS_M33S_M                                    0x00000002U
#define SOC_AON_FWAONM33NS_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM33NS_CORENS                                    0x00000004U
#define SOC_AON_FWAONM33NS_CORENS_M                                  0x00000004U
#define SOC_AON_FWAONM33NS_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAAONM33S
    Offset name:         SOC_AON_O_FWAAONM33S
    Relative address:    0x190
    Description:         AAON_M33_S firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33S_M33NS                                     0x00000001U
#define SOC_AON_FWAAONM33S_M33NS_M                                   0x00000001U
#define SOC_AON_FWAAONM33S_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33S_M33S                                      0x00000002U
#define SOC_AON_FWAAONM33S_M33S_M                                    0x00000002U
#define SOC_AON_FWAAONM33S_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33S_CORENS                                    0x00000004U
#define SOC_AON_FWAAONM33S_CORENS_M                                  0x00000004U
#define SOC_AON_FWAAONM33S_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAAONM33NS
    Offset name:         SOC_AON_O_FWAAONM33NS
    Relative address:    0x194
    Description:         AAON_M33_NS firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33NS_M33NS                                    0x00000001U
#define SOC_AON_FWAAONM33NS_M33NS_M                                  0x00000001U
#define SOC_AON_FWAAONM33NS_M33NS_S                                  0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33NS_M33S                                     0x00000002U
#define SOC_AON_FWAAONM33NS_M33S_M                                   0x00000002U
#define SOC_AON_FWAAONM33NS_M33S_S                                   1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM33NS_CORENS                                   0x00000004U
#define SOC_AON_FWAAONM33NS_CORENS_M                                 0x00000004U
#define SOC_AON_FWAAONM33NS_CORENS_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCMNRTC
    Offset name:         SOC_AON_O_FWCMNRTC
    Relative address:    0x198
    Description:         RTC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NSWR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_M33NSWR                                     0x00000001U
#define SOC_AON_FWCMNRTC_M33NSWR_M                                   0x00000001U
#define SOC_AON_FWCMNRTC_M33NSWR_S                                   0U
/*

        Field:           M33NSRD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_M33NSRD                                     0x00000002U
#define SOC_AON_FWCMNRTC_M33NSRD_M                                   0x00000002U
#define SOC_AON_FWCMNRTC_M33NSRD_S                                   1U
/*

        Field:           M33SWR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_M33SWR                                      0x00000004U
#define SOC_AON_FWCMNRTC_M33SWR_M                                    0x00000004U
#define SOC_AON_FWCMNRTC_M33SWR_S                                    2U
/*

        Field:           M33SRD
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_M33SRD                                      0x00000008U
#define SOC_AON_FWCMNRTC_M33SRD_M                                    0x00000008U
#define SOC_AON_FWCMNRTC_M33SRD_S                                    3U
/*

        Field:           CORENSWR
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_CORENSWR                                    0x00000010U
#define SOC_AON_FWCMNRTC_CORENSWR_M                                  0x00000010U
#define SOC_AON_FWCMNRTC_CORENSWR_S                                  4U
/*

        Field:           CORENSRD
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCMNRTC_CORENSRD                                    0x00000020U
#define SOC_AON_FWCMNRTC_CORENSRD_M                                  0x00000020U
#define SOC_AON_FWCMNRTC_CORENSRD_S                                  5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWMEMSS0
    Offset name:         SOC_AON_O_FWMEMSS0
    Relative address:    0x19C
    Description:         MEMSS region 0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured (valid only in privilege mode)
                        1 - M33 Secured (valid only in privilege mode)
                        2 - Core (Non Secure)

                        MEMSS address space: 0x41C00000 - 0x41CCFFFF
                        for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                        max window size is 256Kb (M33D banks) + 10*32K (Flex) = 576Kb
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS0_M33NS                                       0x00000001U
#define SOC_AON_FWMEMSS0_M33NS_M                                     0x00000001U
#define SOC_AON_FWMEMSS0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS0_M33S                                        0x00000002U
#define SOC_AON_FWMEMSS0_M33S_M                                      0x00000002U
#define SOC_AON_FWMEMSS0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS0_CORENS                                      0x00000004U
#define SOC_AON_FWMEMSS0_CORENS_M                                    0x00000004U
#define SOC_AON_FWMEMSS0_CORENS_S                                    2U
/*

        Field:           BASE
        From..to bits:   4...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         MEMSS address space: 0x41C00000 - 0x41CCFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max base value is 0x23F
                         max window size is 576Kb
                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C40504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x41C40504 --> ((0x41C40504 - 0x41C40000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS0_BASE_W                                      10U
#define SOC_AON_FWMEMSS0_BASE_M                                      0x00003FF0U
#define SOC_AON_FWMEMSS0_BASE_S                                      4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         MEMSS address space: 0x41C00000 - 0x41CCFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max window size is 576Kb

                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C41514
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x41C41514 --> ((0x41C41514 - 0x41C40000) >> 10) -->0x5
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS0_LEN_W                                       10U
#define SOC_AON_FWMEMSS0_LEN_M                                       0x03FF0000U
#define SOC_AON_FWMEMSS0_LEN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWMEMSS1
    Offset name:         SOC_AON_O_FWMEMSS1
    Relative address:    0x1A0
    Description:         MEMSS region 1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured (valid only in privilege mode)
                        1 - M33 Secured (valid only in privilege mode)
                        2 - Core (Non Secure)

                        MEMSS address space: 0x41C00000 - 0x41CCFFFF
                        for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                        max window size is 256Kb (M33D banks) + 10*32K (Flex) = 576Kb
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS1_M33NS                                       0x00000001U
#define SOC_AON_FWMEMSS1_M33NS_M                                     0x00000001U
#define SOC_AON_FWMEMSS1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS1_M33S                                        0x00000002U
#define SOC_AON_FWMEMSS1_M33S_M                                      0x00000002U
#define SOC_AON_FWMEMSS1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS1_CORENS                                      0x00000004U
#define SOC_AON_FWMEMSS1_CORENS_M                                    0x00000004U
#define SOC_AON_FWMEMSS1_CORENS_S                                    2U
/*

        Field:           BASE
        From..to bits:   4...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         MEMSS address space: 0x41C00000 - 0x41DFFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max base value is 0x23F
                         max window size is 576Kb
                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C40504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x41C40504 --> ((0x41C40504 - 0x41C40000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS1_BASE_W                                      10U
#define SOC_AON_FWMEMSS1_BASE_M                                      0x00003FF0U
#define SOC_AON_FWMEMSS1_BASE_S                                      4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         MEMSS address space: 0x41C00000 - 0x41CCFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max window size is 576Kb

                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C41514
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x41C41514 --> ((0x41C41514 - 0x41C40000) >> 10) -->0x5
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS1_LEN_W                                       10U
#define SOC_AON_FWMEMSS1_LEN_M                                       0x03FF0000U
#define SOC_AON_FWMEMSS1_LEN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWMEMSS2
    Offset name:         SOC_AON_O_FWMEMSS2
    Relative address:    0x1A4
    Description:         MEMSS region 2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured (valid only in privilege mode)
                        1 - M33 Secured (valid only in privilege mode)
                        2 - Core (Non Secure)

                        MEMSS address space: 0x41C00000 - 0x41CCFFFF
                        for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                        max window size is 256Kb (M33D banks) + 10*32K (Flex) = 576Kb
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 non Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS2_M33NS                                       0x00000001U
#define SOC_AON_FWMEMSS2_M33NS_M                                     0x00000001U
#define SOC_AON_FWMEMSS2_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured: (valid only in privilege mode)
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS2_M33S                                        0x00000002U
#define SOC_AON_FWMEMSS2_M33S_M                                      0x00000002U
#define SOC_AON_FWMEMSS2_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWMEMSS2_CORENS                                      0x00000004U
#define SOC_AON_FWMEMSS2_CORENS_M                                    0x00000004U
#define SOC_AON_FWMEMSS2_CORENS_S                                    2U
/*

        Field:           BASE
        From..to bits:   4...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         MEMSS address space: 0x41C00000 - 0x41DFFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max base value is 0x23F
                         max window size is 576Kb
                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C40504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x41C40504 --> ((0x41C40504 - 0x41C40000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS2_BASE_W                                      10U
#define SOC_AON_FWMEMSS2_BASE_M                                      0x00003FF0U
#define SOC_AON_FWMEMSS2_BASE_S                                      4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         MEMSS address space: 0x41C00000 - 0x41CCFFFF
                         for Memss the base address for security firewalls is 0x41c40000 ( M33 Data Ram from global port access)
                         max window size is 576Kb

                         example:
                         worker base address: 0x41C40000
                         current address to access: 0x41C41514
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x41C41514 --> ((0x41C41514 - 0x41C40000) >> 10) -->0x5
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWMEMSS2_LEN_W                                       10U
#define SOC_AON_FWMEMSS2_LEN_M                                       0x03FF0000U
#define SOC_AON_FWMEMSS2_LEN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOSTAON
    Offset name:         SOC_AON_O_FWHOSTAON
    Relative address:    0x1A8
    Description:         HOST_AON_SLV firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOSTAON_M33NS                                      0x00000001U
#define SOC_AON_FWHOSTAON_M33NS_M                                    0x00000001U
#define SOC_AON_FWHOSTAON_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOSTAON_M33S                                       0x00000002U
#define SOC_AON_FWHOSTAON_M33S_M                                     0x00000002U
#define SOC_AON_FWHOSTAON_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOSTAON_CORENS                                     0x00000004U
#define SOC_AON_FWHOSTAON_CORENS_M                                   0x00000004U
#define SOC_AON_FWHOSTAON_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHIF
    Offset name:         SOC_AON_O_FWHIF
    Relative address:    0x1B0
    Description:         HIF firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure) - Not in use , core always has access.
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHIF_M33NS                                          0x00000001U
#define SOC_AON_FWHIF_M33NS_M                                        0x00000001U
#define SOC_AON_FWHIF_M33NS_S                                        0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHIF_M33S                                           0x00000002U
#define SOC_AON_FWHIF_M33S_M                                         0x00000002U
#define SOC_AON_FWHIF_M33S_S                                         1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHIF_CORENS                                         0x00000004U
#define SOC_AON_FWHIF_CORENS_M                                       0x00000004U
#define SOC_AON_FWHIF_CORENS_S                                       2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST0
    Offset name:         SOC_AON_O_FWHOST0
    Relative address:    0x1B4
    Description:         HOST MCU region 0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST0_M33NS                                        0x00000001U
#define SOC_AON_FWHOST0_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST0_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST0_M33S                                         0x00000002U
#define SOC_AON_FWHOST0_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST0_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST0_CORENS                                       0x00000004U
#define SOC_AON_FWHOST0_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST0_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_0 is assigned to TCM DATA RAM
                         HOST_MCU_REGION_0 base address can range from:
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F800000 - 0x2401FC00

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F80504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x23F80504 --> ((0x23F80504 - 0x23F800000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST0_BASE_W                                       11U
#define SOC_AON_FWHOST0_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST0_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_0 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_0 base_len can range from:
                         ##register base_len value##
                         0x0 - 0x7F

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x23F80000 ( HOST_MCU_REGION_0 )
                         max window size is 128Kb

                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST0_LEN_W                                        10U
#define SOC_AON_FWHOST0_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST0_LEN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST1
    Offset name:         SOC_AON_O_FWHOST1
    Relative address:    0x1B8
    Description:         HOST MCU region 1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST1_M33NS                                        0x00000001U
#define SOC_AON_FWHOST1_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST1_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST1_M33S                                         0x00000002U
#define SOC_AON_FWHOST1_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST1_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST1_CORENS                                       0x00000004U
#define SOC_AON_FWHOST1_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST1_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_1 is assigned to TCM DATA RAM
                         HOST_MCU_REGION_1 base address can range from:
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F800000 - 0x2401FC00

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F80504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x23F80504 --> ((0x23F80504 - 0x23F800000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST1_BASE_W                                       11U
#define SOC_AON_FWHOST1_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST1_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_0 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_0 base_len can range from:
                         ##register base_len value##
                         0x0 - 0x7F

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x23F80000 ( HOST_MCU_REGION_1 )
                         max window size is 128Kb

                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST1_LEN_W                                        10U
#define SOC_AON_FWHOST1_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST1_LEN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST2
    Offset name:         SOC_AON_O_FWHOST2
    Relative address:    0x1BC
    Description:         HOST MCU region 2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST2_M33NS                                        0x00000001U
#define SOC_AON_FWHOST2_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST2_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST2_M33S                                         0x00000002U
#define SOC_AON_FWHOST2_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST2_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST2_CORENS                                       0x00000004U
#define SOC_AON_FWHOST2_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST2_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_2 is assigned to M33 DATA RAM
                         HOST_MCU_REGION_2 base address can range from:
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_2 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)
                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF000000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST2_BASE_W                                       11U
#define SOC_AON_FWHOST2_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST2_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_2 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_2 base_len can range from:
                         ##register base_len value##
                         0x0 - 0x240

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x2BF00000 ( HOST_MCU_REGION_2 )
                         max window size is 576Kb

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF01504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x2BF01504 --> ((0x2BF01504 - 0x2BF00000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST2_LEN_W                                        10U
#define SOC_AON_FWHOST2_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST2_LEN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST3
    Offset name:         SOC_AON_O_FWHOST3
    Relative address:    0x1C0
    Description:         HOST MCU region 3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST3_M33NS                                        0x00000001U
#define SOC_AON_FWHOST3_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST3_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST3_M33S                                         0x00000002U
#define SOC_AON_FWHOST3_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST3_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST3_CORENS                                       0x00000004U
#define SOC_AON_FWHOST3_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST3_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_3 is assigned to M33 DATA RAM
                         HOST_MCU_REGION_3 base address can range from:
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_2 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)
                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF000000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST3_BASE_W                                       11U
#define SOC_AON_FWHOST3_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST3_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_2 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_2 base_len can range from:
                         ##register base_len value##
                         0x0 - 0x240

                         for HOST_MCU_REGION_0 the base address for security firewalls is 0x2BF00000 ( HOST_MCU_REGION_2 )
                         max window size is 576Kb

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF01504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x2BF01504 --> ((0x2BF01504 - 0x2BF00000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST3_LEN_W                                        10U
#define SOC_AON_FWHOST3_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST3_LEN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST4
    Offset name:         SOC_AON_O_FWHOST4
    Relative address:    0x1C4
    Description:         access permission for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST4_M33NS                                        0x00000001U
#define SOC_AON_FWHOST4_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST4_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST4_M33S                                         0x00000002U
#define SOC_AON_FWHOST4_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST4_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST4_CORENS                                       0x00000004U
#define SOC_AON_FWHOST4_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST4_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_4 is assigned to TCM DATA RAM (base_sel = 0) or M33 Data Ram (base_sel = 1)
                         HOST_MCU_REGION_4 base address can range from:
                         (base_sel = 0)
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F80000 - 0x2401FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM Data RAM )
                         max window size is 128Kb
                         ##################
                         (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF000000 - 0x2C08FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST4_BASE_W                                       11U
#define SOC_AON_FWHOST4_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST4_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_4 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_4 base_len can range from:
                         base_sel = 0
                         ##register base_len value##
                         0x0 - 0x7F
                         base_sel = 0 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM M33 Data RAM )
                         max window size is 128Kb
                         #################
                         base_sel = 1
                         ##register base_len value##
                         0x0 - 0x240
                         base_sel = 1 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 (M33 Data RAM )
                         max window size is 576Kb
                         #################
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST4_LEN_W                                        10U
#define SOC_AON_FWHOST4_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST4_LEN_S                                        16U
/*

        Field:           BASESEL
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Base select for Reserved region defaulted to M33 TCM Data RAM (base_sel = 0):
                         this select bit will assign this region to either
                         TCM Data  (base_sel = 0)
                         ##register base value##
                         0x0 - 0x80
                         ##absolute equivalent value##
                         0x200000000 - 0x20001FFFF

                         or Data RAM (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_4 with base_sel = 0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb (depending on the MEMSS mode)

                         for HOST_MCU_REGION_4 with base_sel = 1 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST4_BASESEL                                      0x04000000U
#define SOC_AON_FWHOST4_BASESEL_M                                    0x04000000U
#define SOC_AON_FWHOST4_BASESEL_S                                    26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST5
    Offset name:         SOC_AON_O_FWHOST5
    Relative address:    0x1C8
    Description:         HOST MCU region 5 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST5_M33NS                                        0x00000001U
#define SOC_AON_FWHOST5_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST5_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST5_M33S                                         0x00000002U
#define SOC_AON_FWHOST5_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST5_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST5_CORENS                                       0x00000004U
#define SOC_AON_FWHOST5_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST5_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_4 is assigned to TCM DATA RAM (base_sel = 0) or M33 Data Ram (base_sel = 1)
                         HOST_MCU_REGION_4 base address can range from:
                         (base_sel = 0)
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F80000 - 0x2401FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM Data RAM )
                         max window size is 128Kb
                         ##################
                         (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF000000 - 0x2C08FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST5_BASE_W                                       11U
#define SOC_AON_FWHOST5_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST5_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_4 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_4 base_len can range from:
                         base_sel = 0
                         ##register base_len value##
                         0x0 - 0x7F
                         base_sel = 0 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM M33 Data RAM )
                         max window size is 128Kb
                         #################
                         base_sel = 1
                         ##register base_len value##
                         0x0 - 0x240
                         base_sel = 1 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 (M33 Data RAM )
                         max window size is 576Kb
                         #################
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST5_LEN_W                                        10U
#define SOC_AON_FWHOST5_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST5_LEN_S                                        16U
/*

        Field:           BASESEL
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Base select for Reserved region defaulted to M33 TCM Data RAM (base_sel = 0):
                         this select bit will assign this region to either
                         TCM Data  (base_sel = 0)
                         ##register base value##
                         0x0 - 0x80
                         ##absolute equivalent value##
                         0x200000000 - 0x20001FFFF

                         or Data RAM (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_4 with base_sel = 0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb (depending on the MEMSS mode)

                         for HOST_MCU_REGION_4 with base_sel = 1 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST5_BASESEL                                      0x04000000U
#define SOC_AON_FWHOST5_BASESEL_M                                    0x04000000U
#define SOC_AON_FWHOST5_BASESEL_S                                    26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST6
    Offset name:         SOC_AON_O_FWHOST6
    Relative address:    0x1CC
    Description:         HOST MCU region 6 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST6_M33NS                                        0x00000001U
#define SOC_AON_FWHOST6_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST6_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST6_M33S                                         0x00000002U
#define SOC_AON_FWHOST6_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST6_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST6_CORENS                                       0x00000004U
#define SOC_AON_FWHOST6_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST6_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_4 is assigned to TCM DATA RAM (base_sel = 0) or M33 Data Ram (base_sel = 1)
                         HOST_MCU_REGION_4 base address can range from:
                         (base_sel = 0)
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F80000 - 0x2401FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM Data RAM )
                         max window size is 128Kb
                         ##################
                         (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF000000 - 0x2C08FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST6_BASE_W                                       11U
#define SOC_AON_FWHOST6_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST6_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_4 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_4 base_len can range from:
                         base_sel = 0
                         ##register base_len value##
                         0x0 - 0x7F
                         base_sel = 0 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM M33 Data RAM )
                         max window size is 128Kb
                         #################
                         base_sel = 1
                         ##register base_len value##
                         0x0 - 0x240
                         base_sel = 1 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 (M33 Data RAM )
                         max window size is 576Kb
                         #################
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST6_LEN_W                                        10U
#define SOC_AON_FWHOST6_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST6_LEN_S                                        16U
/*

        Field:           BASESEL
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Base select for Reserved region defaulted to M33 TCM Data RAM (base_sel = 0):
                         this select bit will assign this region to either
                         TCM Data  (base_sel = 0)
                         ##register base value##
                         0x0 - 0x80
                         ##absolute equivalent value##
                         0x200000000 - 0x20001FFFF

                         or Data RAM (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_4 with base_sel = 0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb (depending on the MEMSS mode)

                         for HOST_MCU_REGION_4 with base_sel = 1 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST6_BASESEL                                      0x04000000U
#define SOC_AON_FWHOST6_BASESEL_M                                    0x04000000U
#define SOC_AON_FWHOST6_BASESEL_S                                    26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST7
    Offset name:         SOC_AON_O_FWHOST7
    Relative address:    0x1D0
    Description:         HOST MCU region 7 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST7_M33NS                                        0x00000001U
#define SOC_AON_FWHOST7_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST7_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST7_M33S                                         0x00000002U
#define SOC_AON_FWHOST7_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST7_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST7_CORENS                                       0x00000004U
#define SOC_AON_FWHOST7_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST7_CORENS_S                                     2U
/*

        Field:           BASE
        From..to bits:   4...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HOST_MCU address space: 0x00000000 - 0x2FFFFFFF / 0x41900000 - 0x4190FFFF
                         HOST_MCU_REGION_4 is assigned to TCM DATA RAM (base_sel = 0) or M33 Data Ram (base_sel = 1)
                         HOST_MCU_REGION_4 base address can range from:
                         (base_sel = 0)
                         ##register base value##
                         0x0 - 0x27F
                         ##absolute equivalent value##
                         0x23F80000 - 0x2401FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM Data RAM )
                         max window size is 128Kb
                         ##################
                         (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF000000 - 0x2C08FC00
                         for HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF000000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST7_BASE_W                                       11U
#define SOC_AON_FWHOST7_BASE_M                                       0x00007FF0U
#define SOC_AON_FWHOST7_BASE_S                                       4U
/*

        Field:           LEN
        From..to bits:   16...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HOST_MCU_REGION_4 address space: 0x20000000 - 0x2FFFFFFF
                         HOST_MCU_REGION_4 base_len can range from:
                         base_sel = 0
                         ##register base_len value##
                         0x0 - 0x7F
                         base_sel = 0 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x23F80000 ( TCM M33 Data RAM )
                         max window size is 128Kb
                         #################
                         base_sel = 1
                         ##register base_len value##
                         0x0 - 0x240
                         base_sel = 1 --> HOST_MCU_REGION_4 the base address for security firewalls is 0x2BF00000 (M33 Data RAM )
                         max window size is 576Kb
                         #################
                         example:
                         worker base address: 0x23F80000
                         current address to access: 0x23F81504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x23F81504 --> ((0x23F81504 - 0x23F80000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST7_LEN_W                                        10U
#define SOC_AON_FWHOST7_LEN_M                                        0x03FF0000U
#define SOC_AON_FWHOST7_LEN_S                                        16U
/*

        Field:           BASESEL
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Base select for Reserved region defaulted to M33 TCM Data RAM (base_sel = 0):
                         this select bit will assign this region to either
                         TCM Data  (base_sel = 0)
                         ##register base value##
                         0x0 - 0x80
                         ##absolute equivalent value##
                         0x200000000 - 0x20001FFFF

                         or Data RAM (base_sel = 1)
                         ##register base value##
                         0x0 - 0x63F
                         ##absolute equivalent value##
                         0x2BF00000 - 0x2C08FC00

                         for HOST_MCU_REGION_4 with base_sel = 0 the base address for security firewalls is 0x23F80000 ( M33 TCM Data RAM )
                         max window size is 128Kb (depending on the MEMSS mode)

                         for HOST_MCU_REGION_4 with base_sel = 1 the base address for security firewalls is 0x2BF00000 ( M33 Data RAM )
                         max window size is 576Kb (depending on the MEMSS mode)

                         example:
                         worker base address: 0x2BF00000
                         current address to access: 0x2BF00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x2BF00504 --> ((0x2BF00504 - 0x2BF00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHOST7_BASESEL                                      0x04000000U
#define SOC_AON_FWHOST7_BASESEL_M                                    0x04000000U
#define SOC_AON_FWHOST7_BASESEL_S                                    26U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST8
    Offset name:         SOC_AON_O_FWHOST8
    Relative address:    0x1D4
    Description:         HOST MCU region 8 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST8_M33NS                                        0x00000001U
#define SOC_AON_FWHOST8_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST8_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST8_M33S                                         0x00000002U
#define SOC_AON_FWHOST8_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST8_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST8_CORENS                                       0x00000004U
#define SOC_AON_FWHOST8_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST8_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST9
    Offset name:         SOC_AON_O_FWHOST9
    Relative address:    0x1D8
    Description:         HOST MCU region 9 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST9_M33NS                                        0x00000001U
#define SOC_AON_FWHOST9_M33NS_M                                      0x00000001U
#define SOC_AON_FWHOST9_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST9_M33S                                         0x00000002U
#define SOC_AON_FWHOST9_M33S_M                                       0x00000002U
#define SOC_AON_FWHOST9_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST9_CORENS                                       0x00000004U
#define SOC_AON_FWHOST9_CORENS_M                                     0x00000004U
#define SOC_AON_FWHOST9_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST10
    Offset name:         SOC_AON_O_FWHOST10
    Relative address:    0x1DC
    Description:         HOST MCU region 10 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST10_M33NS                                       0x00000001U
#define SOC_AON_FWHOST10_M33NS_M                                     0x00000001U
#define SOC_AON_FWHOST10_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST10_M33S                                        0x00000002U
#define SOC_AON_FWHOST10_M33S_M                                      0x00000002U
#define SOC_AON_FWHOST10_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST10_CORENS                                      0x00000004U
#define SOC_AON_FWHOST10_CORENS_M                                    0x00000004U
#define SOC_AON_FWHOST10_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHOST11
    Offset name:         SOC_AON_O_FWHOST11
    Relative address:    0x1E0
    Description:         HOST MCU region 11 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST11_M33NS                                       0x00000001U
#define SOC_AON_FWHOST11_M33NS_M                                     0x00000001U
#define SOC_AON_FWHOST11_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST11_M33S                                        0x00000002U
#define SOC_AON_FWHOST11_M33S_M                                      0x00000002U
#define SOC_AON_FWHOST11_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHOST11_CORENS                                      0x00000004U
#define SOC_AON_FWHOST11_CORENS_M                                    0x00000004U
#define SOC_AON_FWHOST11_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPOSPI
    Offset name:         SOC_AON_O_FWXIPOSPI
    Relative address:    0x1E4
    Description:         XIP_OSPI firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPOSPI_M33NS                                      0x00000001U
#define SOC_AON_FWXIPOSPI_M33NS_M                                    0x00000001U
#define SOC_AON_FWXIPOSPI_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPOSPI_M33S                                       0x00000002U
#define SOC_AON_FWXIPOSPI_M33S_M                                     0x00000002U
#define SOC_AON_FWXIPOSPI_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPOSPI_CORENS                                     0x00000004U
#define SOC_AON_FWXIPOSPI_CORENS_M                                   0x00000004U
#define SOC_AON_FWXIPOSPI_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPINDAC
    Offset name:         SOC_AON_O_FWXIPINDAC
    Relative address:    0x1E8
    Description:         OSPI_INDAC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPINDAC_M33NS                                     0x00000001U
#define SOC_AON_FWXIPINDAC_M33NS_M                                   0x00000001U
#define SOC_AON_FWXIPINDAC_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPINDAC_M33S                                      0x00000002U
#define SOC_AON_FWXIPINDAC_M33S_M                                    0x00000002U
#define SOC_AON_FWXIPINDAC_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPINDAC_CORENS                                    0x00000004U
#define SOC_AON_FWXIPINDAC_CORENS_M                                  0x00000004U
#define SOC_AON_FWXIPINDAC_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPGEN
    Offset name:         SOC_AON_O_FWXIPGEN
    Relative address:    0x1EC
    Description:         XIP_GEN firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPGEN_M33NS                                       0x00000001U
#define SOC_AON_FWXIPGEN_M33NS_M                                     0x00000001U
#define SOC_AON_FWXIPGEN_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPGEN_M33S                                        0x00000002U
#define SOC_AON_FWXIPGEN_M33S_M                                      0x00000002U
#define SOC_AON_FWXIPGEN_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPGEN_CORENS                                      0x00000004U
#define SOC_AON_FWXIPGEN_CORENS_M                                    0x00000004U
#define SOC_AON_FWXIPGEN_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPUDMAS
    Offset name:         SOC_AON_O_FWXIPUDMAS
    Relative address:    0x1F0
    Description:         XIP_UDMA_SEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMAS_M33NS                                     0x00000001U
#define SOC_AON_FWXIPUDMAS_M33NS_M                                   0x00000001U
#define SOC_AON_FWXIPUDMAS_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMAS_M33S                                      0x00000002U
#define SOC_AON_FWXIPUDMAS_M33S_M                                    0x00000002U
#define SOC_AON_FWXIPUDMAS_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMAS_CORENS                                    0x00000004U
#define SOC_AON_FWXIPUDMAS_CORENS_M                                  0x00000004U
#define SOC_AON_FWXIPUDMAS_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPUDMANS
    Offset name:         SOC_AON_O_FWXIPUDMANS
    Relative address:    0x1F4
    Description:         UDMA_NONSEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMANS_M33NS                                    0x00000001U
#define SOC_AON_FWXIPUDMANS_M33NS_M                                  0x00000001U
#define SOC_AON_FWXIPUDMANS_M33NS_S                                  0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMANS_M33S                                     0x00000002U
#define SOC_AON_FWXIPUDMANS_M33S_M                                   0x00000002U
#define SOC_AON_FWXIPUDMANS_M33S_S                                   1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPUDMANS_CORENS                                   0x00000004U
#define SOC_AON_FWXIPUDMANS_CORENS_M                                 0x00000004U
#define SOC_AON_FWXIPUDMANS_CORENS_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFDE0
    Offset name:         SOC_AON_O_FWOTFDE0
    Relative address:    0x1F8
    Description:         OTFDE_REGION0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE0_M33NS                                       0x00000001U
#define SOC_AON_FWOTFDE0_M33NS_M                                     0x00000001U
#define SOC_AON_FWOTFDE0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE0_M33S                                        0x00000002U
#define SOC_AON_FWOTFDE0_M33S_M                                      0x00000002U
#define SOC_AON_FWOTFDE0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE0_CORENS                                      0x00000004U
#define SOC_AON_FWOTFDE0_CORENS_M                                    0x00000004U
#define SOC_AON_FWOTFDE0_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFDE1
    Offset name:         SOC_AON_O_FWOTFDE1
    Relative address:    0x1FC
    Description:         OTFDE_REGION1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE1_M33NS                                       0x00000001U
#define SOC_AON_FWOTFDE1_M33NS_M                                     0x00000001U
#define SOC_AON_FWOTFDE1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE1_M33S                                        0x00000002U
#define SOC_AON_FWOTFDE1_M33S_M                                      0x00000002U
#define SOC_AON_FWOTFDE1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE1_CORENS                                      0x00000004U
#define SOC_AON_FWOTFDE1_CORENS_M                                    0x00000004U
#define SOC_AON_FWOTFDE1_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFDE2
    Offset name:         SOC_AON_O_FWOTFDE2
    Relative address:    0x200
    Description:         OTFDE_REGION2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE2_M33NS                                       0x00000001U
#define SOC_AON_FWOTFDE2_M33NS_M                                     0x00000001U
#define SOC_AON_FWOTFDE2_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE2_M33S                                        0x00000002U
#define SOC_AON_FWOTFDE2_M33S_M                                      0x00000002U
#define SOC_AON_FWOTFDE2_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE2_CORENS                                      0x00000004U
#define SOC_AON_FWOTFDE2_CORENS_M                                    0x00000004U
#define SOC_AON_FWOTFDE2_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFDE3
    Offset name:         SOC_AON_O_FWOTFDE3
    Relative address:    0x204
    Description:         OTFDE_REGION3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE3_M33NS                                       0x00000001U
#define SOC_AON_FWOTFDE3_M33NS_M                                     0x00000001U
#define SOC_AON_FWOTFDE3_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE3_M33S                                        0x00000002U
#define SOC_AON_FWOTFDE3_M33S_M                                      0x00000002U
#define SOC_AON_FWOTFDE3_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFDE3_CORENS                                      0x00000004U
#define SOC_AON_FWOTFDE3_CORENS_M                                    0x00000004U
#define SOC_AON_FWOTFDE3_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMAGEN
    Offset name:         SOC_AON_O_FWDMAGEN
    Relative address:    0x208
    Description:         DMA_GEN firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMAGEN_M33NS                                       0x00000001U
#define SOC_AON_FWDMAGEN_M33NS_M                                     0x00000001U
#define SOC_AON_FWDMAGEN_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMAGEN_M33S                                        0x00000002U
#define SOC_AON_FWDMAGEN_M33S_M                                      0x00000002U
#define SOC_AON_FWDMAGEN_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMAGEN_CORENS                                      0x00000004U
#define SOC_AON_FWDMAGEN_CORENS_M                                    0x00000004U
#define SOC_AON_FWDMAGEN_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA0
    Offset name:         SOC_AON_O_FWDMA0
    Relative address:    0x20C
    Description:         DMA_CH_0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA0_M33NS                                         0x00000001U
#define SOC_AON_FWDMA0_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA0_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA0_M33S                                          0x00000002U
#define SOC_AON_FWDMA0_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA0_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA0_CORENS                                        0x00000004U
#define SOC_AON_FWDMA0_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA0_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA1
    Offset name:         SOC_AON_O_FWDMA1
    Relative address:    0x210
    Description:         DMA_CH_1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA1_M33NS                                         0x00000001U
#define SOC_AON_FWDMA1_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA1_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA1_M33S                                          0x00000002U
#define SOC_AON_FWDMA1_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA1_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA1_CORENS                                        0x00000004U
#define SOC_AON_FWDMA1_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA1_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA2
    Offset name:         SOC_AON_O_FWDMA2
    Relative address:    0x214
    Description:         DMA_CH_2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA2_M33NS                                         0x00000001U
#define SOC_AON_FWDMA2_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA2_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA2_M33S                                          0x00000002U
#define SOC_AON_FWDMA2_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA2_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA2_CORENS                                        0x00000004U
#define SOC_AON_FWDMA2_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA2_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA3
    Offset name:         SOC_AON_O_FWDMA3
    Relative address:    0x218
    Description:         DMA_CH_3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA3_M33NS                                         0x00000001U
#define SOC_AON_FWDMA3_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA3_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA3_M33S                                          0x00000002U
#define SOC_AON_FWDMA3_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA3_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA3_CORENS                                        0x00000004U
#define SOC_AON_FWDMA3_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA3_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA4
    Offset name:         SOC_AON_O_FWDMA4
    Relative address:    0x21C
    Description:         DMA_CH_4 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA4_M33NS                                         0x00000001U
#define SOC_AON_FWDMA4_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA4_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA4_M33S                                          0x00000002U
#define SOC_AON_FWDMA4_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA4_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA4_CORENS                                        0x00000004U
#define SOC_AON_FWDMA4_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA4_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA5
    Offset name:         SOC_AON_O_FWDMA5
    Relative address:    0x220
    Description:         DMA_CH_5 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA5_M33NS                                         0x00000001U
#define SOC_AON_FWDMA5_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA5_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA5_M33S                                          0x00000002U
#define SOC_AON_FWDMA5_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA5_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA5_CORENS                                        0x00000004U
#define SOC_AON_FWDMA5_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA5_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA6
    Offset name:         SOC_AON_O_FWDMA6
    Relative address:    0x224
    Description:         DMA_CH_6 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA6_M33NS                                         0x00000001U
#define SOC_AON_FWDMA6_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA6_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA6_M33S                                          0x00000002U
#define SOC_AON_FWDMA6_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA6_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA6_CORENS                                        0x00000004U
#define SOC_AON_FWDMA6_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA6_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA7
    Offset name:         SOC_AON_O_FWDMA7
    Relative address:    0x228
    Description:         DMA_CH_7 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA7_M33NS                                         0x00000001U
#define SOC_AON_FWDMA7_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA7_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA7_M33S                                          0x00000002U
#define SOC_AON_FWDMA7_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA7_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA7_CORENS                                        0x00000004U
#define SOC_AON_FWDMA7_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA7_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA8
    Offset name:         SOC_AON_O_FWDMA8
    Relative address:    0x22C
    Description:         DMA_CH_8 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA8_M33NS                                         0x00000001U
#define SOC_AON_FWDMA8_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA8_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA8_M33S                                          0x00000002U
#define SOC_AON_FWDMA8_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA8_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA8_CORENS                                        0x00000004U
#define SOC_AON_FWDMA8_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA8_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA9
    Offset name:         SOC_AON_O_FWDMA9
    Relative address:    0x230
    Description:         DMA_CH_9 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA9_M33NS                                         0x00000001U
#define SOC_AON_FWDMA9_M33NS_M                                       0x00000001U
#define SOC_AON_FWDMA9_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA9_M33S                                          0x00000002U
#define SOC_AON_FWDMA9_M33S_M                                        0x00000002U
#define SOC_AON_FWDMA9_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA9_CORENS                                        0x00000004U
#define SOC_AON_FWDMA9_CORENS_M                                      0x00000004U
#define SOC_AON_FWDMA9_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA10
    Offset name:         SOC_AON_O_FWDMA10
    Relative address:    0x234
    Description:         DMA_CH_10 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA10_M33NS                                        0x00000001U
#define SOC_AON_FWDMA10_M33NS_M                                      0x00000001U
#define SOC_AON_FWDMA10_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA10_M33S                                         0x00000002U
#define SOC_AON_FWDMA10_M33S_M                                       0x00000002U
#define SOC_AON_FWDMA10_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA10_CORENS                                       0x00000004U
#define SOC_AON_FWDMA10_CORENS_M                                     0x00000004U
#define SOC_AON_FWDMA10_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA11
    Offset name:         SOC_AON_O_FWDMA11
    Relative address:    0x238
    Description:         DMA_CH_11 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA11_M33NS                                        0x00000001U
#define SOC_AON_FWDMA11_M33NS_M                                      0x00000001U
#define SOC_AON_FWDMA11_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA11_M33S                                         0x00000002U
#define SOC_AON_FWDMA11_M33S_M                                       0x00000002U
#define SOC_AON_FWDMA11_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA11_CORENS                                       0x00000004U
#define SOC_AON_FWDMA11_CORENS_M                                     0x00000004U
#define SOC_AON_FWDMA11_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHSMEIPNS
    Offset name:         SOC_AON_O_FWHSMEIPNS
    Relative address:    0x23C
    Description:         HSM EIP NONSEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPNS_M33NS                                     0x00000001U
#define SOC_AON_FWHSMEIPNS_M33NS_M                                   0x00000001U
#define SOC_AON_FWHSMEIPNS_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPNS_M33S                                      0x00000002U
#define SOC_AON_FWHSMEIPNS_M33S_M                                    0x00000002U
#define SOC_AON_FWHSMEIPNS_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPNS_CORENS                                    0x00000004U
#define SOC_AON_FWHSMEIPNS_CORENS_M                                  0x00000004U
#define SOC_AON_FWHSMEIPNS_CORENS_S                                  2U
/*

        Field:           BASE
        From..to bits:   4...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HSM address space: 0x41B00000 - 0x41B3FFFF
                         HSM_EIP_REGS base address can range from:
                         ##register base value##
                         0x0 - 0xF
                         ##absolute equivalent value##
                         0x41B00000 - 0x41B03FFF

                         for HSM the base address for security firewalls is 0x41B00000 ( HSM_EIP_REGS )
                         max window size is 16Kb
                         example:
                         worker base address: 0x41B00000
                         current address to access: 0x41B00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x41B00504 --> ((0x41B00504 - 0x41B00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHSMEIPNS_BASE_W                                    5U
#define SOC_AON_FWHSMEIPNS_BASE_M                                    0x000001F0U
#define SOC_AON_FWHSMEIPNS_BASE_S                                    4U
/*

        Field:           LEN
        From..to bits:   16...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HSM address space: 0x41B00000 - 0x41B3FFFF
                         HSM_EIP_REGS base_len can range from:
                         ##register base_len value##
                         0x0 - 0xF

                         for HSM the base address for security firewalls is 0x41B00000 ( HSM_EIP_REGS )
                         max window size is 16Kb

                         example:
                         worker base address: 0x41B00000
                         current address to access: 0x41B01504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x41B01504 --> ((0x41B01504 - 0x41B00000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHSMEIPNS_LEN_W                                     5U
#define SOC_AON_FWHSMEIPNS_LEN_M                                     0x001F0000U
#define SOC_AON_FWHSMEIPNS_LEN_S                                     16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHSMEIPS
    Offset name:         SOC_AON_O_FWHSMEIPS
    Relative address:    0x240
    Description:         HSM EIP SEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPS_M33NS                                      0x00000001U
#define SOC_AON_FWHSMEIPS_M33NS_M                                    0x00000001U
#define SOC_AON_FWHSMEIPS_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPS_M33S                                       0x00000002U
#define SOC_AON_FWHSMEIPS_M33S_M                                     0x00000002U
#define SOC_AON_FWHSMEIPS_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMEIPS_CORENS                                     0x00000004U
#define SOC_AON_FWHSMEIPS_CORENS_M                                   0x00000004U
#define SOC_AON_FWHSMEIPS_CORENS_S                                   2U
/*

        Field:           BASE
        From..to bits:   4...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base for firewall
                         is the the offset start address from a worker base address
                         describing the beginning of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id
                         HSM address space: 0x41B00000 - 0x41B3FFFF
                         HSM_EIP_REGS base address can range from:
                         ##register base value##
                         0x0 -
                         ##absolute equivalent value##
                         0x41B00000 - 0x41B03FFF

                         for HSM the base address for security firewalls is 0x41B00000 ( HSM_EIP_REGS )
                         max window size is 16Kb
                         example:
                         worker base address: 0x41B00000
                         current address to access: 0x41B00504
                         region_base_address: 0x1
                         region_base_address_len: 0x1

                         0x41B00504 --> ((0x41B00504 - 0x41B00000) >> 10) --> 0x1
                         0x1(base) <= 0x1(current) < 0x1(base)+0x1(len)
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHSMEIPS_BASE_W                                     5U
#define SOC_AON_FWHSMEIPS_BASE_M                                     0x000001F0U
#define SOC_AON_FWHSMEIPS_BASE_S                                     4U
/*

        Field:           LEN
        From..to bits:   16...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     address base with 1K granularity :
                         address base len for firewall
                         is the offset from the region's base address indicated in the same region field
                         describing the end of a firewall window that has a certain access rules (R/W Permission)
                         for each controller-id

                         HSM address space: 0x41B00000 - 0x41B3FFFF
                         HSM_EIP_REGS base_len can range from:
                         ##register base_len value##
                         0x0 - 0xF

                         for HSM the base address for security firewalls is 0x41B00000 ( HSM_EIP_REGS )
                         max window size is 16Kb

                         example:
                         worker base address: 0x41B00000
                         current address to access: 0x41B01504
                         region_base_address: 0x4
                         region_base_address_len: 0x2 --> (region_base_address + region_base_address_len) --> 0x4+0x2 -->0x6

                         0x41B01504 --> ((0x41B01504 - 0x41B00000) >> 10) -->0x4
                         0x4 <= 0x5 < 0x6
                         that address falls on the region window and therefor obeys to that region set of access rules

*/
#define SOC_AON_FWHSMEIPS_LEN_W                                      5U
#define SOC_AON_FWHSMEIPS_LEN_M                                      0x001F0000U
#define SOC_AON_FWHSMEIPS_LEN_S                                      16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHSMWRAPNS
    Offset name:         SOC_AON_O_FWHSMWRAPNS
    Relative address:    0x244
    Description:         HSM Wrapper NONSEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPNS_M33NS                                    0x00000001U
#define SOC_AON_FWHSMWRAPNS_M33NS_M                                  0x00000001U
#define SOC_AON_FWHSMWRAPNS_M33NS_S                                  0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPNS_M33S                                     0x00000002U
#define SOC_AON_FWHSMWRAPNS_M33S_M                                   0x00000002U
#define SOC_AON_FWHSMWRAPNS_M33S_S                                   1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPNS_CORENS                                   0x00000004U
#define SOC_AON_FWHSMWRAPNS_CORENS_M                                 0x00000004U
#define SOC_AON_FWHSMWRAPNS_CORENS_S                                 2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHSMWRAPS
    Offset name:         SOC_AON_O_FWHSMWRAPS
    Relative address:    0x248
    Description:         HSM Wrapper SEC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPS_M33NS                                     0x00000001U
#define SOC_AON_FWHSMWRAPS_M33NS_M                                   0x00000001U
#define SOC_AON_FWHSMWRAPS_M33NS_S                                   0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPS_M33S                                      0x00000002U
#define SOC_AON_FWHSMWRAPS_M33S_M                                    0x00000002U
#define SOC_AON_FWHSMWRAPS_M33S_S                                    1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMWRAPS_CORENS                                    0x00000004U
#define SOC_AON_FWHSMWRAPS_CORENS_M                                  0x00000004U
#define SOC_AON_FWHSMWRAPS_CORENS_S                                  2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWHSMDBG
    Offset name:         SOC_AON_O_FWHSMDBG
    Relative address:    0x24C
    Description:         HSM DEBUG firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMDBG_M33NS                                       0x00000001U
#define SOC_AON_FWHSMDBG_M33NS_M                                     0x00000001U
#define SOC_AON_FWHSMDBG_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMDBG_M33S                                        0x00000002U
#define SOC_AON_FWHSMDBG_M33S_M                                      0x00000002U
#define SOC_AON_FWHSMDBG_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWHSMDBG_CORENS                                      0x00000004U
#define SOC_AON_FWHSMDBG_CORENS_M                                    0x00000004U
#define SOC_AON_FWHSMDBG_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWI2C0
    Offset name:         SOC_AON_O_FWI2C0
    Relative address:    0x250
    Description:         I2C0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C0_M33NS                                         0x00000001U
#define SOC_AON_FWI2C0_M33NS_M                                       0x00000001U
#define SOC_AON_FWI2C0_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C0_M33S                                          0x00000002U
#define SOC_AON_FWI2C0_M33S_M                                        0x00000002U
#define SOC_AON_FWI2C0_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C0_CORENS                                        0x00000004U
#define SOC_AON_FWI2C0_CORENS_M                                      0x00000004U
#define SOC_AON_FWI2C0_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWI2C1
    Offset name:         SOC_AON_O_FWI2C1
    Relative address:    0x254
    Description:         I2C1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C1_M33NS                                         0x00000001U
#define SOC_AON_FWI2C1_M33NS_M                                       0x00000001U
#define SOC_AON_FWI2C1_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C1_M33S                                          0x00000002U
#define SOC_AON_FWI2C1_M33S_M                                        0x00000002U
#define SOC_AON_FWI2C1_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWI2C1_CORENS                                        0x00000004U
#define SOC_AON_FWI2C1_CORENS_M                                      0x00000004U
#define SOC_AON_FWI2C1_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPSPI0
    Offset name:         SOC_AON_O_FWSPSPI0
    Relative address:    0x258
    Description:         SPI0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI0_M33NS                                       0x00000001U
#define SOC_AON_FWSPSPI0_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPSPI0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI0_M33S                                        0x00000002U
#define SOC_AON_FWSPSPI0_M33S_M                                      0x00000002U
#define SOC_AON_FWSPSPI0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI0_CORENS                                      0x00000004U
#define SOC_AON_FWSPSPI0_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPSPI0_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPSPI1
    Offset name:         SOC_AON_O_FWSPSPI1
    Relative address:    0x25C
    Description:         SPI1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI1_M33NS                                       0x00000001U
#define SOC_AON_FWSPSPI1_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPSPI1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI1_M33S                                        0x00000002U
#define SOC_AON_FWSPSPI1_M33S_M                                      0x00000002U
#define SOC_AON_FWSPSPI1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSPI1_CORENS                                      0x00000004U
#define SOC_AON_FWSPSPI1_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPSPI1_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPUART0
    Offset name:         SOC_AON_O_FWSPUART0
    Relative address:    0x260
    Description:         UART0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART0_M33NS                                      0x00000001U
#define SOC_AON_FWSPUART0_M33NS_M                                    0x00000001U
#define SOC_AON_FWSPUART0_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART0_M33S                                       0x00000002U
#define SOC_AON_FWSPUART0_M33S_M                                     0x00000002U
#define SOC_AON_FWSPUART0_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART0_CORENS                                     0x00000004U
#define SOC_AON_FWSPUART0_CORENS_M                                   0x00000004U
#define SOC_AON_FWSPUART0_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPUART1
    Offset name:         SOC_AON_O_FWSPUART1
    Relative address:    0x264
    Description:         UART1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART1_M33NS                                      0x00000001U
#define SOC_AON_FWSPUART1_M33NS_M                                    0x00000001U
#define SOC_AON_FWSPUART1_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART1_M33S                                       0x00000002U
#define SOC_AON_FWSPUART1_M33S_M                                     0x00000002U
#define SOC_AON_FWSPUART1_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART1_CORENS                                     0x00000004U
#define SOC_AON_FWSPUART1_CORENS_M                                   0x00000004U
#define SOC_AON_FWSPUART1_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPGPT0
    Offset name:         SOC_AON_O_FWSPGPT0
    Relative address:    0x268
    Description:         GPTIMER0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT0_M33NS                                       0x00000001U
#define SOC_AON_FWSPGPT0_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPGPT0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT0_M33S                                        0x00000002U
#define SOC_AON_FWSPGPT0_M33S_M                                      0x00000002U
#define SOC_AON_FWSPGPT0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT0_CORENS                                      0x00000004U
#define SOC_AON_FWSPGPT0_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPGPT0_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPGPT1
    Offset name:         SOC_AON_O_FWSPGPT1
    Relative address:    0x26C
    Description:         GPTIMER1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT1_M33NS                                       0x00000001U
#define SOC_AON_FWSPGPT1_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPGPT1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT1_M33S                                        0x00000002U
#define SOC_AON_FWSPGPT1_M33S_M                                      0x00000002U
#define SOC_AON_FWSPGPT1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPGPT1_CORENS                                      0x00000004U
#define SOC_AON_FWSPGPT1_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPGPT1_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPI2S
    Offset name:         SOC_AON_O_FWSPI2S
    Relative address:    0x270
    Description:         I2S firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPI2S_M33NS                                        0x00000001U
#define SOC_AON_FWSPI2S_M33NS_M                                      0x00000001U
#define SOC_AON_FWSPI2S_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPI2S_M33S                                         0x00000002U
#define SOC_AON_FWSPI2S_M33S_M                                       0x00000002U
#define SOC_AON_FWSPI2S_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPI2S_CORENS                                       0x00000004U
#define SOC_AON_FWSPI2S_CORENS_M                                     0x00000004U
#define SOC_AON_FWSPI2S_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWPDM
    Offset name:         SOC_AON_O_FWPDM
    Relative address:    0x274
    Description:         PDM firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPDM_M33NS                                          0x00000001U
#define SOC_AON_FWPDM_M33NS_M                                        0x00000001U
#define SOC_AON_FWPDM_M33NS_S                                        0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPDM_M33S                                           0x00000002U
#define SOC_AON_FWPDM_M33S_M                                         0x00000002U
#define SOC_AON_FWPDM_M33S_S                                         1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPDM_CORENS                                         0x00000004U
#define SOC_AON_FWPDM_CORENS_M                                       0x00000004U
#define SOC_AON_FWPDM_CORENS_S                                       2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPCAN
    Offset name:         SOC_AON_O_FWSPCAN
    Relative address:    0x278
    Description:         CAN firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPCAN_M33NS                                        0x00000001U
#define SOC_AON_FWSPCAN_M33NS_M                                      0x00000001U
#define SOC_AON_FWSPCAN_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPCAN_M33S                                         0x00000002U
#define SOC_AON_FWSPCAN_M33S_M                                       0x00000002U
#define SOC_AON_FWSPCAN_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPCAN_CORENS                                       0x00000004U
#define SOC_AON_FWSPCAN_CORENS_M                                     0x00000004U
#define SOC_AON_FWSPCAN_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPADC
    Offset name:         SOC_AON_O_FWSPADC
    Relative address:    0x27C
    Description:         ADC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPADC_M33NS                                        0x00000001U
#define SOC_AON_FWSPADC_M33NS_M                                      0x00000001U
#define SOC_AON_FWSPADC_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPADC_M33S                                         0x00000002U
#define SOC_AON_FWSPADC_M33S_M                                       0x00000002U
#define SOC_AON_FWSPADC_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPADC_CORENS                                       0x00000004U
#define SOC_AON_FWSPADC_CORENS_M                                     0x00000004U
#define SOC_AON_FWSPADC_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPSDMMC
    Offset name:         SOC_AON_O_FWSPSDMMC
    Relative address:    0x280
    Description:         SDMMC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDMMC_M33NS                                      0x00000001U
#define SOC_AON_FWSPSDMMC_M33NS_M                                    0x00000001U
#define SOC_AON_FWSPSDMMC_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDMMC_M33S                                       0x00000002U
#define SOC_AON_FWSPSDMMC_M33S_M                                     0x00000002U
#define SOC_AON_FWSPSDMMC_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDMMC_CORENS                                     0x00000004U
#define SOC_AON_FWSPSDMMC_CORENS_M                                   0x00000004U
#define SOC_AON_FWSPSDMMC_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPSDIO
    Offset name:         SOC_AON_O_FWSPSDIO
    Relative address:    0x284
    Description:         SDIO firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDIO_M33NS                                       0x00000001U
#define SOC_AON_FWSPSDIO_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPSDIO_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDIO_M33S                                        0x00000002U
#define SOC_AON_FWSPSDIO_M33S_M                                      0x00000002U
#define SOC_AON_FWSPSDIO_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPSDIO_CORENS                                      0x00000004U
#define SOC_AON_FWSPSDIO_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPSDIO_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPUART2
    Offset name:         SOC_AON_O_FWSPUART2
    Relative address:    0x288
    Description:         UART2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART2_M33NS                                      0x00000001U
#define SOC_AON_FWSPUART2_M33NS_M                                    0x00000001U
#define SOC_AON_FWSPUART2_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART2_M33S                                       0x00000002U
#define SOC_AON_FWSPUART2_M33S_M                                     0x00000002U
#define SOC_AON_FWSPUART2_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPUART2_CORENS                                     0x00000004U
#define SOC_AON_FWSPUART2_CORENS_M                                   0x00000004U
#define SOC_AON_FWSPUART2_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDMANSCTL
    Offset name:         SOC_AON_O_UDMANSCTL
    Relative address:    0x28C
    Description:         uDMA Non-secured Channel Control.
    Default Value:       0x00000000

        Field:           ACCPER
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Access Permission.

                         Define uDMA non-sec channel access permission to secured flash address:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_UDMANSCTL_ACCPER                                     0x00000001U
#define SOC_AON_UDMANSCTL_ACCPER_M                                   0x00000001U
#define SOC_AON_UDMANSCTL_ACCPER_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD0
    Offset name:         SOC_AON_O_FWIOPAD0
    Relative address:    0x290
    Description:         IOMUX_PAD_0 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD0_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD0_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD0_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD0_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD0_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD0_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD0_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD1
    Offset name:         SOC_AON_O_FWIOPAD1
    Relative address:    0x294
    Description:         IOMUX_PAD_1 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD1_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD1_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD1_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD1_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD1_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD1_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD1_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD2
    Offset name:         SOC_AON_O_FWIOPAD2
    Relative address:    0x298
    Description:         IOMUX_PAD_2 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD2_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD2_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD2_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD2_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD2_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD2_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD2_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD2_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD2_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD3
    Offset name:         SOC_AON_O_FWIOPAD3
    Relative address:    0x29C
    Description:         IOMUX_PAD_3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD3_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD3_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD3_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD3_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD3_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD3_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD3_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD3_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD3_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD4
    Offset name:         SOC_AON_O_FWIOPAD4
    Relative address:    0x2A0
    Description:         IOMUX_PAD_4 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD4_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD4_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD4_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD4_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD4_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD4_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD4_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD4_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD4_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD5
    Offset name:         SOC_AON_O_FWIOPAD5
    Relative address:    0x2A4
    Description:         IOMUX_PAD_5 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD5_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD5_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD5_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD5_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD5_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD5_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD5_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD5_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD5_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD6
    Offset name:         SOC_AON_O_FWIOPAD6
    Relative address:    0x2A8
    Description:         IOMUX_PAD_6 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD6_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD6_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD6_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD6_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD6_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD6_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD6_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD6_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD6_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD7
    Offset name:         SOC_AON_O_FWIOPAD7
    Relative address:    0x2AC
    Description:         IOMUX_PAD_7 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD7_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD7_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD7_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD7_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD7_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD7_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD7_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD7_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD7_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD8
    Offset name:         SOC_AON_O_FWIOPAD8
    Relative address:    0x2B0
    Description:         IOMUX_PAD_8 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD8_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD8_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD8_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD8_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD8_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD8_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD8_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD8_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD8_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD9
    Offset name:         SOC_AON_O_FWIOPAD9
    Relative address:    0x2B4
    Description:         IOMUX_PAD_9 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD9_M33NS                                       0x00000001U
#define SOC_AON_FWIOPAD9_M33NS_M                                     0x00000001U
#define SOC_AON_FWIOPAD9_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD9_M33S                                        0x00000002U
#define SOC_AON_FWIOPAD9_M33S_M                                      0x00000002U
#define SOC_AON_FWIOPAD9_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD9_CORENS                                      0x00000004U
#define SOC_AON_FWIOPAD9_CORENS_M                                    0x00000004U
#define SOC_AON_FWIOPAD9_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD10
    Offset name:         SOC_AON_O_FWIOPAD10
    Relative address:    0x2B8
    Description:         IOMUX_PAD_10 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD10_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD10_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD10_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD10_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD10_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD10_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD10_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD10_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD10_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD11
    Offset name:         SOC_AON_O_FWIOPAD11
    Relative address:    0x2BC
    Description:         IOMUX_PAD_11 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD11_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD11_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD11_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD11_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD11_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD11_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD11_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD11_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD11_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD12
    Offset name:         SOC_AON_O_FWIOPAD12
    Relative address:    0x2C0
    Description:         IOMUX_PAD_12 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD12_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD12_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD12_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD12_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD12_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD12_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD12_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD12_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD12_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD13
    Offset name:         SOC_AON_O_FWIOPAD13
    Relative address:    0x2C4
    Description:         IOMUX_PAD_13 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD13_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD13_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD13_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD13_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD13_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD13_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD13_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD13_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD13_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD14
    Offset name:         SOC_AON_O_FWIOPAD14
    Relative address:    0x2C8
    Description:         IOMUX_PAD_14 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD14_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD14_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD14_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD14_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD14_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD14_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD14_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD14_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD14_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD15
    Offset name:         SOC_AON_O_FWIOPAD15
    Relative address:    0x2CC
    Description:         IOMUX_PAD_15 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD15_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD15_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD15_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD15_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD15_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD15_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD15_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD15_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD15_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD16
    Offset name:         SOC_AON_O_FWIOPAD16
    Relative address:    0x2D0
    Description:         IOMUX_PAD_16 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD16_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD16_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD16_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD16_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD16_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD16_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD16_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD16_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD16_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD17
    Offset name:         SOC_AON_O_FWIOPAD17
    Relative address:    0x2D4
    Description:         IOMUX_PAD_17 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD17_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD17_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD17_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD17_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD17_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD17_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD17_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD17_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD17_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD18
    Offset name:         SOC_AON_O_FWIOPAD18
    Relative address:    0x2D8
    Description:         IOMUX_PAD_18 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD18_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD18_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD18_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD18_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD18_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD18_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD18_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD18_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD18_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD19
    Offset name:         SOC_AON_O_FWIOPAD19
    Relative address:    0x2DC
    Description:         IOMUX_PAD_19 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD19_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD19_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD19_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD19_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD19_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD19_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD19_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD19_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD19_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD20
    Offset name:         SOC_AON_O_FWIOPAD20
    Relative address:    0x2E0
    Description:         IOMUX_PAD_20 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD20_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD20_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD20_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD20_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD20_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD20_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD20_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD20_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD20_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD21
    Offset name:         SOC_AON_O_FWIOPAD21
    Relative address:    0x2E4
    Description:         IOMUX_PAD_21 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD21_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD21_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD21_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD21_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD21_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD21_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD21_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD21_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD21_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD22
    Offset name:         SOC_AON_O_FWIOPAD22
    Relative address:    0x2E8
    Description:         IOMUX_PAD_22 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD22_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD22_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD22_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD22_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD22_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD22_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD22_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD22_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD22_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD23
    Offset name:         SOC_AON_O_FWIOPAD23
    Relative address:    0x2EC
    Description:         IOMUX_PAD_23 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD23_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD23_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD23_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD23_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD23_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD23_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD23_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD23_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD23_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD24
    Offset name:         SOC_AON_O_FWIOPAD24
    Relative address:    0x2F0
    Description:         IOMUX_PAD_24 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD24_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD24_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD24_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD24_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD24_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD24_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD24_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD24_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD24_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD25
    Offset name:         SOC_AON_O_FWIOPAD25
    Relative address:    0x2F4
    Description:         IOMUX_PAD_25 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD25_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD25_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD25_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD25_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD25_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD25_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD25_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD25_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD25_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD26
    Offset name:         SOC_AON_O_FWIOPAD26
    Relative address:    0x2F8
    Description:         IOMUX_PAD_26 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD26_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD26_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD26_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD26_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD26_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD26_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD26_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD26_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD26_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD27
    Offset name:         SOC_AON_O_FWIOPAD27
    Relative address:    0x2FC
    Description:         IOMUX_PAD_27 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD27_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD27_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD27_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD27_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD27_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD27_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD27_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD27_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD27_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD28
    Offset name:         SOC_AON_O_FWIOPAD28
    Relative address:    0x300
    Description:         IOMUX_PAD_28 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD28_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD28_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD28_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD28_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD28_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD28_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD28_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD28_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD28_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD29
    Offset name:         SOC_AON_O_FWIOPAD29
    Relative address:    0x304
    Description:         IOMUX_PAD_29 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD29_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD29_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD29_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD29_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD29_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD29_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD29_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD29_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD29_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD30
    Offset name:         SOC_AON_O_FWIOPAD30
    Relative address:    0x308
    Description:         IOMUX_PAD_30 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD30_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD30_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD30_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD30_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD30_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD30_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD30_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD30_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD30_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD31
    Offset name:         SOC_AON_O_FWIOPAD31
    Relative address:    0x30C
    Description:         IOMUX_PAD_31 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD31_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD31_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD31_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD31_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD31_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD31_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD31_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD31_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD31_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD32
    Offset name:         SOC_AON_O_FWIOPAD32
    Relative address:    0x310
    Description:         IOMUX_PAD_32 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD32_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD32_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD32_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD32_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD32_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD32_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD32_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD32_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD32_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD33
    Offset name:         SOC_AON_O_FWIOPAD33
    Relative address:    0x314
    Description:         IOMUX_PAD_33 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD33_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD33_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD33_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD33_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD33_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD33_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD33_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD33_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD33_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD34
    Offset name:         SOC_AON_O_FWIOPAD34
    Relative address:    0x318
    Description:         IOMUX_PAD_34 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD34_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD34_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD34_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD34_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD34_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD34_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD34_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD34_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD34_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD35
    Offset name:         SOC_AON_O_FWIOPAD35
    Relative address:    0x31C
    Description:         IOMUX_PAD_35 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD35_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD35_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD35_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD35_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD35_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD35_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD35_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD35_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD35_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD36
    Offset name:         SOC_AON_O_FWIOPAD36
    Relative address:    0x320
    Description:         IOMUX_PAD_36 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD36_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD36_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD36_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD36_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD36_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD36_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD36_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD36_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD36_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD37
    Offset name:         SOC_AON_O_FWIOPAD37
    Relative address:    0x324
    Description:         IOMUX_PAD_37 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD37_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD37_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD37_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD37_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD37_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD37_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD37_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD37_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD37_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD38
    Offset name:         SOC_AON_O_FWIOPAD38
    Relative address:    0x328
    Description:         IOMUX_PAD_38 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD38_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD38_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD38_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD38_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD38_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD38_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD38_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD38_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD38_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD39
    Offset name:         SOC_AON_O_FWIOPAD39
    Relative address:    0x32C
    Description:         IOMUX_PAD_39 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD39_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD39_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD39_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD39_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD39_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD39_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD39_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD39_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD39_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD40
    Offset name:         SOC_AON_O_FWIOPAD40
    Relative address:    0x330
    Description:         IOMUX_PAD_40 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD40_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD40_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD40_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD40_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD40_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD40_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD40_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD40_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD40_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD41
    Offset name:         SOC_AON_O_FWIOPAD41
    Relative address:    0x334
    Description:         IOMUX_PAD_41 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD41_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD41_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD41_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD41_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD41_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD41_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD41_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD41_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD41_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD42
    Offset name:         SOC_AON_O_FWIOPAD42
    Relative address:    0x338
    Description:         IOMUX_PAD_42 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD42_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD42_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD42_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD42_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD42_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD42_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD42_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD42_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD42_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD43
    Offset name:         SOC_AON_O_FWIOPAD43
    Relative address:    0x33C
    Description:         IOMUX_PAD_43 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD43_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD43_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD43_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD43_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD43_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD43_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD43_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD43_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD43_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD44
    Offset name:         SOC_AON_O_FWIOPAD44
    Relative address:    0x340
    Description:         IOMUX_PAD_44 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD44_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD44_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD44_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD44_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD44_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD44_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD44_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD44_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD44_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD45
    Offset name:         SOC_AON_O_FWIOPAD45
    Relative address:    0x344
    Description:         IOMUX_PAD_45 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD45_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD45_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD45_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD45_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD45_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD45_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD45_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD45_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD45_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD46
    Offset name:         SOC_AON_O_FWIOPAD46
    Relative address:    0x348
    Description:         IOMUX_PAD_46 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD46_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD46_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD46_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD46_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD46_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD46_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD46_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD46_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD46_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD47
    Offset name:         SOC_AON_O_FWIOPAD47
    Relative address:    0x34C
    Description:         IOMUX_PAD_47 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD47_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD47_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD47_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD47_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD47_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD47_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD47_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD47_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD47_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWIOPAD48
    Offset name:         SOC_AON_O_FWIOPAD48
    Relative address:    0x350
    Description:         IOMUX_PAD_48 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD48_M33NS                                      0x00000001U
#define SOC_AON_FWIOPAD48_M33NS_M                                    0x00000001U
#define SOC_AON_FWIOPAD48_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD48_M33S                                       0x00000002U
#define SOC_AON_FWIOPAD48_M33S_M                                     0x00000002U
#define SOC_AON_FWIOPAD48_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWIOPAD48_CORENS                                     0x00000004U
#define SOC_AON_FWIOPAD48_CORENS_M                                   0x00000004U
#define SOC_AON_FWIOPAD48_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA12
    Offset name:         SOC_AON_O_FWDMA12
    Relative address:    0x354
    Description:         DMA_CH_12 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA12_M33NS                                        0x00000001U
#define SOC_AON_FWDMA12_M33NS_M                                      0x00000001U
#define SOC_AON_FWDMA12_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA12_M33S                                         0x00000002U
#define SOC_AON_FWDMA12_M33S_M                                       0x00000002U
#define SOC_AON_FWDMA12_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA12_CORENS                                       0x00000004U
#define SOC_AON_FWDMA12_CORENS_M                                     0x00000004U
#define SOC_AON_FWDMA12_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDMA13
    Offset name:         SOC_AON_O_FWDMA13
    Relative address:    0x358
    Description:         DMA_CH_13 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA13_M33NS                                        0x00000001U
#define SOC_AON_FWDMA13_M33NS_M                                      0x00000001U
#define SOC_AON_FWDMA13_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA13_M33S                                         0x00000002U
#define SOC_AON_FWDMA13_M33S_M                                       0x00000002U
#define SOC_AON_FWDMA13_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDMA13_CORENS                                       0x00000004U
#define SOC_AON_FWDMA13_CORENS_M                                     0x00000004U
#define SOC_AON_FWDMA13_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPARE0
    Offset name:         SOC_AON_O_FWSPARE0
    Relative address:    0x35C
    Description:         Spare firewall access register.
                        locked by HOST BOOT DONE (secgk)
                        3 access bits - {M33NS , M33S , M3} .
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE0_M33NS                                       0x00000001U
#define SOC_AON_FWSPARE0_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPARE0_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE0_M33S                                        0x00000002U
#define SOC_AON_FWSPARE0_M33S_M                                      0x00000002U
#define SOC_AON_FWSPARE0_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE0_CORENS                                      0x00000004U
#define SOC_AON_FWSPARE0_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPARE0_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       USECSTB
    Offset name:         SOC_AON_O_USECSTB
    Relative address:    0x1000
    Description:         Micro Second STB
    Default Value:       0x0000004F

        Field:           US
        From..to bits:   0...7
        DefaultValue:    0x4F
        Access type:     read-write
        Description:     Set how many soc clk are in one micro second, minus 1.
                         for 40mhz : should be 39.
                         for 80mhz : should be 79. (Soc clock default is 80MHz)

*/
#define SOC_AON_USECSTB_US_W                                         8U
#define SOC_AON_USECSTB_US_M                                         0x000000FFU
#define SOC_AON_USECSTB_US_S                                         0U
/*

        Field:           16US
        From..to bits:   8...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Set how many micro second strobes are in 16 micro seconds, minus 1.
                         Default: 16-1 =15.

*/
#define SOC_AON_USECSTB_16US_W                                       6U
#define SOC_AON_USECSTB_16US_M                                       0x00003F00U
#define SOC_AON_USECSTB_16US_S                                       8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M33CLR
    Offset name:         SOC_AON_O_DB2M33CLR
    Relative address:    0x1004
    Description:         Doorbell 2 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ when handled the massage from M3
                         Type: Write-Clear

*/
#define SOC_AON_DB2M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB2M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB2M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M33SET
    Offset name:         SOC_AON_O_DB2M33SET
    Relative address:    0x1008
    Description:         Doorbell 2 M33 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message
                         Type: Write-Clear

*/
#define SOC_AON_DB2M33SET_SET                                        0x00000001U
#define SOC_AON_DB2M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB2M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M33LOCK
    Offset name:         SOC_AON_O_DB2M33LOCK
    Relative address:    0x100C
    Description:         Doorbell 2 M33 Lockbit Register
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33 always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3
                                 10: taken by M33 (should wr IRQ afterwards)
                                 11: invalid.

                         generating the IRQ towards M1 clears the lock.
                         Writing '00' also release the lock.

                         2'b01 means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB2M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB2M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB2M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M33CLR
    Offset name:         SOC_AON_O_DB3M33CLR
    Relative address:    0x1010
    Description:         Doorbell 3 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ when handled the massage from M3
                         Type: Write-Clear

*/
#define SOC_AON_DB3M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB3M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB3M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M33SET
    Offset name:         SOC_AON_O_DB3M33SET
    Relative address:    0x1014
    Description:         Doorbell 3 M33 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message
                         Type: Write-Clear

*/
#define SOC_AON_DB3M33SET_SET                                        0x00000001U
#define SOC_AON_DB3M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB3M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M33LOCK
    Offset name:         SOC_AON_O_DB3M33LOCK
    Relative address:    0x1018
    Description:         Doorbell 3 M33 Lockbit Register
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33 always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3
                                 10: taken by M33 (should wr IRQ afterwards)
                                 11: invalid.

                         generating the IRQ towards M1 clears the lock.
                         Writing '00' also release the lock.

                         2'b01 means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB3M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB3M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB3M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M33CLR
    Offset name:         SOC_AON_O_DB6M33CLR
    Relative address:    0x101C
    Description:         Doorbell 6 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ when handled the massage from M3
                         Type: Write-Clear

*/
#define SOC_AON_DB6M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB6M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB6M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M33SET
    Offset name:         SOC_AON_O_DB6M33SET
    Relative address:    0x1020
    Description:         Doorbell 6 M33 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message
                         Type: Write-Clear

*/
#define SOC_AON_DB6M33SET_SET                                        0x00000001U
#define SOC_AON_DB6M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB6M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M33LOCK
    Offset name:         SOC_AON_O_DB6M33LOCK
    Relative address:    0x1024
    Description:         Doorbell 6 M33 Lockbit Register
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33 always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3
                                 10: taken by M33 (should wr IRQ afterwards)
                                 11: invalid.

                         generating the IRQ towards M1 clears the lock.
                         Writing '00' also release the lock.

                         2'b01 means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB6M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB6M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB6M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M33CLR
    Offset name:         SOC_AON_O_DB7M33CLR
    Relative address:    0x1028
    Description:         Doorbell 7 M33 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to clear the IRQ when handled the massage from M3
                         Type: Write-Clear

*/
#define SOC_AON_DB7M33CLR_CLR                                        0x00000001U
#define SOC_AON_DB7M33CLR_CLR_M                                      0x00000001U
#define SOC_AON_DB7M33CLR_CLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M33SET
    Offset name:         SOC_AON_O_DB7M33SET
    Relative address:    0x102C
    Description:         Doorbell 7 M33 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M33 to generate IRQ towards M3 after writing the message
                         Type: Write-Clear

*/
#define SOC_AON_DB7M33SET_SET                                        0x00000001U
#define SOC_AON_DB7M33SET_SET_M                                      0x00000001U
#define SOC_AON_DB7M33SET_SET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M33LOCK
    Offset name:         SOC_AON_O_DB7M33LOCK
    Relative address:    0x1030
    Description:         Doorbell 7 M33 Lockbit Register
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 2 by h/w.
                         M33 always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3
                                 10: taken by M33 (should wr IRQ afterwards)
                                 11: invalid.

                         generating the IRQ towards M1 clears the lock.
                         Writing '00' also release the lock.

                         2'b01 means lock obtained by receiver side

                         Type: Write-Read-Clear

*/
#define SOC_AON_DB7M33LOCK_LOCKBIT_W                                 2U
#define SOC_AON_DB7M33LOCK_LOCKBIT_M                                 0x00000003U
#define SOC_AON_DB7M33LOCK_LOCKBIT_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOEVT0NS
    Offset name:         SOC_AON_O_GPIOEVT0NS
    Relative address:    0x1044
    Description:         Non-Secured GPIO Event Status, 1st Register.

                        45 bits status over two registers.
    Default Value:       0x00000000

        Field:           STA31TO0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Non-Secured event status , first 32 bits. ([31:0])

*/
#define SOC_AON_GPIOEVT0NS_STA31TO0_W                                32U
#define SOC_AON_GPIOEVT0NS_STA31TO0_M                                0xFFFFFFFFU
#define SOC_AON_GPIOEVT0NS_STA31TO0_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOEVT1NS
    Offset name:         SOC_AON_O_GPIOEVT1NS
    Relative address:    0x1048
    Description:         Non-Secured GPIO Event Status, 2nd Register.

                        45 bits status over two registers.
    Default Value:       0x00000000

        Field:           STA44TO32
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Non-Secured event status , 13 MSBs. ([44:32])

*/
#define SOC_AON_GPIOEVT1NS_STA44TO32_W                               13U
#define SOC_AON_GPIOEVT1NS_STA44TO32_M                               0x00001FFFU
#define SOC_AON_GPIOEVT1NS_STA44TO32_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM33NS0
    Offset name:         SOC_AON_O_DBM33NS0
    Relative address:    0x1054
    Description:         M33 Non-Secured Doorbell IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

*/
#define SOC_AON_DBM33NS0_IMASK_W                                     4U
#define SOC_AON_DBM33NS0_IMASK_M                                     0x0000000FU
#define SOC_AON_DBM33NS0_IMASK_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSISET
    Offset name:         SOC_AON_O_DBNSISET
    Relative address:    0x1058
    Description:         M33 Non-Secured Doorbells ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBNSISET_ISET_W                                      4U
#define SOC_AON_DBNSISET_ISET_M                                      0x0000000FU
#define SOC_AON_DBNSISET_ISET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSICLR
    Offset name:         SOC_AON_O_DBNSICLR
    Relative address:    0x105C
    Description:         M33 Non-Secured Doorbell ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBNSICLR_ICLR_W                                      4U
#define SOC_AON_DBNSICLR_ICLR_M                                      0x0000000FU
#define SOC_AON_DBNSICLR_ICLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSIMSET
    Offset name:         SOC_AON_O_DBNSIMSET
    Relative address:    0x1060
    Description:         M33 Non-Secured Doorbell IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBNSIMSET_IMSET_W                                    4U
#define SOC_AON_DBNSIMSET_IMSET_M                                    0x0000000FU
#define SOC_AON_DBNSIMSET_IMSET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSIMCLR
    Offset name:         SOC_AON_O_DBNSIMCLR
    Relative address:    0x1064
    Description:         M33 Non-Secured Doorbell IMCLR,
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

                         Type: Write-Clear

*/
#define SOC_AON_DBNSIMCLR_IMCLR_W                                    4U
#define SOC_AON_DBNSIMCLR_IMCLR_M                                    0x0000000FU
#define SOC_AON_DBNSIMCLR_IMCLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSRIS
    Offset name:         SOC_AON_O_DBNSRIS
    Relative address:    0x1068
    Description:         M33 Non-Secured Doorbell RIS.
                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

*/
#define SOC_AON_DBNSRIS_RIS_W                                        4U
#define SOC_AON_DBNSRIS_RIS_M                                        0x0000000FU
#define SOC_AON_DBNSRIS_RIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBNSMIS
    Offset name:         SOC_AON_O_DBNSMIS
    Relative address:    0x106C
    Description:         M33 Non-Secured Doorbell MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     bit3 - doorbell 7 M3 IRQ
                         bit2 - doorbell 6 M3 IRQ
                         bit1 - doorbell 3 M3 IRQ
                         bit0 - doorbell 2 M3 IRQ

*/
#define SOC_AON_DBNSMIS_MIS_W                                        4U
#define SOC_AON_DBNSMIS_MIS_M                                        0x0000000FU
#define SOC_AON_DBNSMIS_MIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOMIS0NS
    Offset name:         SOC_AON_O_GPIOMIS0NS
    Relative address:    0x1070
    Description:         Non Secured GPIO MIS. 31-0
    Default Value:       NA

        Field:           31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     32 LSBs of GPIO MIS

*/
#define SOC_AON_GPIOMIS0NS_31TO0_W                                   32U
#define SOC_AON_GPIOMIS0NS_31TO0_M                                   0xFFFFFFFFU
#define SOC_AON_GPIOMIS0NS_31TO0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOMIS1NS
    Offset name:         SOC_AON_O_GPIOMIS1NS
    Relative address:    0x1074
    Description:         Non Secure GPIO MIS. 44-32
    Default Value:       NA

        Field:           44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     13 MSBs of GPIO MIS. 44-32

*/
#define SOC_AON_GPIOMIS1NS_44TO32_W                                  13U
#define SOC_AON_GPIOMIS1NS_44TO32_M                                  0x00001FFFU
#define SOC_AON_GPIOMIS1NS_44TO32_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOFNC0NS
    Offset name:         SOC_AON_O_GPIOFNC0NS
    Relative address:    0x1078
    Description:         Non Secured GPIO Functional Mask. 31-0

                        0. Mask
                        1. Un-Mask
    Default Value:       NA

        Field:           MASK31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     32 LSBs  of non-secured functional mask for GPIO.

*/
#define SOC_AON_GPIOFNC0NS_MASK31TO0_W                               32U
#define SOC_AON_GPIOFNC0NS_MASK31TO0_M                               0xFFFFFFFFU
#define SOC_AON_GPIOFNC0NS_MASK31TO0_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIOFNC1NS
    Offset name:         SOC_AON_O_GPIOFNC1NS
    Relative address:    0x107C
    Description:         non secured gpio functional mask
    Default Value:       NA

        Field:           MASK44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     13 MSBs of non-secured functional mask for GPIO. 44-32

*/
#define SOC_AON_GPIOFNC1NS_MASK44TO32_W                              13U
#define SOC_AON_GPIOFNC1NS_MASK44TO32_M                              0x00001FFFU
#define SOC_AON_GPIOFNC1NS_MASK44TO32_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE2
    Offset name:         SOC_AON_O_SPARE2
    Relative address:    0x1080
    Description:         Spare Register for M22 Secured Aperture.
                        not locked.
    Default Value:       0x00000000

        Field:           BF
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M33NS spare register.
                         not locked.

*/
#define SOC_AON_SPARE2_BF_W                                          4U
#define SOC_AON_SPARE2_BF_M                                          0x0000000FU
#define SOC_AON_SPARE2_BF_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSE
    Offset name:         SOC_AON_O_FUSE
    Relative address:    0x2004
    Description:         Selected Security Fuse Lines.
                        This register contain selected fields reflects Security from Fuse lines.
    Default Value:       NA

        Field:           BOOTLVL
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     Determine which part of the boot ROM bypass options for risk mitigation
                         Level0 - Do not bypass anything
                         Level1- Ignore Error
                         Level2 - TI ROM bypass
                         Level3 - Minimize access to HW. Do min mandatory.
                         0b0110 - Level3
                         0b1010 - Level 2
                         0b0101 - Level 1
                         All the rest - Level 0

*/
#define SOC_AON_FUSE_BOOTLVL_W                                       4U
#define SOC_AON_FUSE_BOOTLVL_M                                       0x0000000FU
#define SOC_AON_FUSE_BOOTLVL_S                                       0U
/*

        Field:           DIS5GHZ
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable 5GHz
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSE_DIS5GHZ                                         0x00000010U
#define SOC_AON_FUSE_DIS5GHZ_M                                       0x00000010U
#define SOC_AON_FUSE_DIS5GHZ_S                                       4U
/*

        Field:           DIS6GHZ
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable 6GHz
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSE_DIS6GHZ                                         0x00000020U
#define SOC_AON_FUSE_DIS6GHZ_M                                       0x00000020U
#define SOC_AON_FUSE_DIS6GHZ_S                                       5U
/*

        Field:           DISBLE
        From..to bits:   6...6
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable BLE (RFC_MDM_CLKEN)
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSE_DISBLE                                          0x00000040U
#define SOC_AON_FUSE_DISBLE_M                                        0x00000040U
#define SOC_AON_FUSE_DISBLE_S                                        6U
/*

        Field:           DISBLEM0P
        From..to bits:   7...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable BLE M0+ (RFC_CPE_CLKEN )
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSE_DISBLEM0P                                       0x00000080U
#define SOC_AON_FUSE_DISBLEM0P_M                                     0x00000080U
#define SOC_AON_FUSE_DISBLEM0P_S                                     7U
/*

        Field:           DISM33
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable M33
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSE_DISM33                                          0x00000100U
#define SOC_AON_FUSE_DISM33_M                                        0x00000100U
#define SOC_AON_FUSE_DISM33_S                                        8U
/*

        Field:           TEMP
        From..to bits:   9...10
        DefaultValue:    NA
        Access type:     read-only
        Description:     Supported Temperature
                         00 - 85degC
                         01 - 105degC
                         10 - 125degC
                         11 - Reserved

*/
#define SOC_AON_FUSE_TEMP_W                                          2U
#define SOC_AON_FUSE_TEMP_M                                          0x00000600U
#define SOC_AON_FUSE_TEMP_S                                          9U
/*

        Field:           DISCANFD
        From..to bits:   11...11
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable CAN FD - to eliminate the need to pay royalties
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)
                         HCANEN (Enable/Disable the CAN IP) - Determined according to paper spin
                         HCANRAMEN(Enable disable access to CAN memory) - Determined according to paper spin.
                         HCANFDEN - Disable/Enable CAN. Determined according to eFuse bit (this bit)

*/
#define SOC_AON_FUSE_DISCANFD                                        0x00000800U
#define SOC_AON_FUSE_DISCANFD_M                                      0x00000800U
#define SOC_AON_FUSE_DISCANFD_S                                      11U
/*

        Field:           ENBOOTWDT
        From..to bits:   12...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enable watchdog timer for protecting boot:
                         (This enable M33 watchdog second threshold to reset device when asserted).
                         0 - Disable Boot Watchdog
                         1 - Enable Boot Watchdog

*/
#define SOC_AON_FUSE_ENBOOTWDT                                       0x00001000U
#define SOC_AON_FUSE_ENBOOTWDT_M                                     0x00001000U
#define SOC_AON_FUSE_ENBOOTWDT_S                                     12U
/*

        Field:           RANDDLYEN
        From..to bits:   13...13
        DefaultValue:    NA
        Access type:     read-only
        Description:     Random Delay Enable:
                         0 - Disable
                         1 - Enable

*/
#define SOC_AON_FUSE_RANDDLYEN                                       0x00002000U
#define SOC_AON_FUSE_RANDDLYEN_M                                     0x00002000U
#define SOC_AON_FUSE_RANDDLYEN_S                                     13U
/*

        Field:           DISVERB
        From..to bits:   14...14
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable Verbose Mode
                         0 - Verbose Mode (Enable) - Full Logger
                         1 - Normal Mode (Disable)

*/
#define SOC_AON_FUSE_DISVERB                                         0x00004000U
#define SOC_AON_FUSE_DISVERB_M                                       0x00004000U
#define SOC_AON_FUSE_DISVERB_S                                       14U
/*

        Field:           RESBOOTEXE
        From..to bits:   15...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     Resume boot in non-normal boot flows where the boot cannot progress (e.g. when assets are hidden). For example, in forced supply in operational or deployed life cycles, 1st bday/at test (normal) life cycles, etc.

                         0 - Halt boot execution as early as possible
                         1 - Resume/Continue boot execution

                         This bit is ignored when the device can run the boot flow normally (e.g. deployed life cycle with default SOP).

*/
#define SOC_AON_FUSE_RESBOOTEXE                                      0x00008000U
#define SOC_AON_FUSE_RESBOOTEXE_M                                    0x00008000U
#define SOC_AON_FUSE_RESBOOTEXE_S                                    15U
/*

        Field:           LDAUTHEN
        From..to bits:   16...17
        DefaultValue:    NA
        Access type:     read-only
        Description:     RAM Bootloader authentication enable:
                         00 - Disable
                         Other- Enable

*/
#define SOC_AON_FUSE_LDAUTHEN_W                                      2U
#define SOC_AON_FUSE_LDAUTHEN_M                                      0x00030000U
#define SOC_AON_FUSE_LDAUTHEN_S                                      16U
/*

        Field:           PRIVDBGREQ
        From..to bits:   18...20
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enforce TI privilege Debug Request (Relevant  in AT TEST privilege only  used by SW)
                         0 - Disable
                         other (1-7) - Enable
                         (When SW check these bits: if equal to '0' bypass otherwise check.)

*/
#define SOC_AON_FUSE_PRIVDBGREQ_W                                    3U
#define SOC_AON_FUSE_PRIVDBGREQ_M                                    0x001C0000U
#define SOC_AON_FUSE_PRIVDBGREQ_S                                    18U
/*

        Field:           MEMSTCK
        From..to bits:   21...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enable watchdog timer for protecting boot:
                         (This enable M33 watchdog second threshold to reset device when asserted).
                         0 - Disable Boot Watchdog
                         1 - Enable Boot Watchdog

*/
#define SOC_AON_FUSE_MEMSTCK_W                                       3U
#define SOC_AON_FUSE_MEMSTCK_M                                       0x00E00000U
#define SOC_AON_FUSE_MEMSTCK_S                                       21U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1CFG
    Offset name:         SOC_AON_O_ESM1CFG
    Relative address:    0x2048
    Description:         ESM1 Configuration- Customer Debug M33 Non Secure Enable Sequence Monitor.

                        Enable timeout mechanism and timeout counter value.
    Default Value:       0x00000001

        Field:           ENTIMEOUT
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field enables timeout mechanism for ESM.

*/
#define SOC_AON_ESM1CFG_ENTIMEOUT                                    0x00000001U
#define SOC_AON_ESM1CFG_ENTIMEOUT_M                                  0x00000001U
#define SOC_AON_ESM1CFG_ENTIMEOUT_S                                  0U
/*

        Field:           TIMEOUTCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field sets the timeout value.
                         time resolution equals to 16us. while:
                         value 0 representing 16us
                         value 1 - 2*16us
                         value 2 - 3*16us and so on.
                         value 15 is not supported.

*/
#define SOC_AON_ESM1CFG_TIMEOUTCNT_W                                 4U
#define SOC_AON_ESM1CFG_TIMEOUTCNT_M                                 0x00000F00U
#define SOC_AON_ESM1CFG_TIMEOUTCNT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1EN1
    Offset name:         SOC_AON_O_ESM1EN1
    Relative address:    0x204C
    Description:         ESM1 Enable Number 1.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 1st enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM1EN1_EN1                                          0x00000001U
#define SOC_AON_ESM1EN1_EN1_M                                        0x00000001U
#define SOC_AON_ESM1EN1_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1EN2
    Offset name:         SOC_AON_O_ESM1EN2
    Relative address:    0x2050
    Description:         ESM1 Enable Number 2.
    Default Value:       NA

        Field:           EN2
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 2nd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM1EN2_EN2                                          0x00000001U
#define SOC_AON_ESM1EN2_EN2_M                                        0x00000001U
#define SOC_AON_ESM1EN2_EN2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1EN3
    Offset name:         SOC_AON_O_ESM1EN3
    Relative address:    0x2054
    Description:         ESM1 Enable Number 3.
    Default Value:       NA

        Field:           EN3
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 3rd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM1EN3_EN3                                          0x00000001U
#define SOC_AON_ESM1EN3_EN3_M                                        0x00000001U
#define SOC_AON_ESM1EN3_EN3_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1EN4
    Offset name:         SOC_AON_O_ESM1EN4
    Relative address:    0x2058
    Description:         ESM1 Enable Number 4.
    Default Value:       NA

        Field:           EN4
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 4th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM1EN4_EN4                                          0x00000001U
#define SOC_AON_ESM1EN4_EN4_M                                        0x00000001U
#define SOC_AON_ESM1EN4_EN4_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1EN5
    Offset name:         SOC_AON_O_ESM1EN5
    Relative address:    0x205C
    Description:         ESM1 Enable Number 5.
    Default Value:       NA

        Field:           EN5
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 5th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM1EN5_EN5                                          0x00000001U
#define SOC_AON_ESM1EN5_EN5_M                                        0x00000001U
#define SOC_AON_ESM1EN5_EN5_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2EN1
    Offset name:         SOC_AON_O_ESM2EN1
    Relative address:    0x2060
    Description:         ESM2 Enable Number 1.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 1st enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM2EN1_EN1                                          0x00000001U
#define SOC_AON_ESM2EN1_EN1_M                                        0x00000001U
#define SOC_AON_ESM2EN1_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2EN2
    Offset name:         SOC_AON_O_ESM2EN2
    Relative address:    0x2064
    Description:         ESM2 Enable Number 2.
    Default Value:       NA

        Field:           EN2
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 2nd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM2EN2_EN2                                          0x00000001U
#define SOC_AON_ESM2EN2_EN2_M                                        0x00000001U
#define SOC_AON_ESM2EN2_EN2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2EN3
    Offset name:         SOC_AON_O_ESM2EN3
    Relative address:    0x2068
    Description:         ESM2 Enable Number 3.
    Default Value:       NA

        Field:           EN3
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 3rd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM2EN3_EN3                                          0x00000001U
#define SOC_AON_ESM2EN3_EN3_M                                        0x00000001U
#define SOC_AON_ESM2EN3_EN3_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2EN4
    Offset name:         SOC_AON_O_ESM2EN4
    Relative address:    0x206C
    Description:         ESM2 Enable Number 4.
    Default Value:       NA

        Field:           EN4
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 4th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM2EN4_EN4                                          0x00000001U
#define SOC_AON_ESM2EN4_EN4_M                                        0x00000001U
#define SOC_AON_ESM2EN4_EN4_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2EN5
    Offset name:         SOC_AON_O_ESM2EN5
    Relative address:    0x2070
    Description:         ESM2 Enable Number 5.
    Default Value:       NA

        Field:           EN5
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 5th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM2EN5_EN5                                          0x00000001U
#define SOC_AON_ESM2EN5_EN5_M                                        0x00000001U
#define SOC_AON_ESM2EN5_EN5_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2CFG
    Offset name:         SOC_AON_O_ESM2CFG
    Relative address:    0x2074
    Description:         ESM2 Configuration- Customer Debug M33 Secure Enable Sequence Monitor.

                        Enable timeout mechanism and timeout counter value.
    Default Value:       0x00000001

        Field:           ENTIMEOUT
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field enables timeout mechanism for ESM.

*/
#define SOC_AON_ESM2CFG_ENTIMEOUT                                    0x00000001U
#define SOC_AON_ESM2CFG_ENTIMEOUT_M                                  0x00000001U
#define SOC_AON_ESM2CFG_ENTIMEOUT_S                                  0U
/*

        Field:           TIMEOUTCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field sets the timeout value.
                         time resolution equals to 16us. while:
                         value 0 representing 16us
                         value 1 - 2*16us
                         value 2 - 3*16us and so on.
                         value 15 is not supported.

*/
#define SOC_AON_ESM2CFG_TIMEOUTCNT_W                                 4U
#define SOC_AON_ESM2CFG_TIMEOUTCNT_M                                 0x00000F00U
#define SOC_AON_ESM2CFG_TIMEOUTCNT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGSSDSSM
    Offset name:         SOC_AON_O_DBGSSDSSM
    Relative address:    0x20A4
    Description:         This register allow indication of debug port is present:  ble, wlphy, wsoccpu, app cpu
    Default Value:       0x00000001

        Field:           MBOXRSTEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     If this signal is set, debug request command sent to DSSM TX DAT register shall assert "Mailbox_reset_req" signal above, otherwise the debug request command is ignored.

*/
#define SOC_AON_DBGSSDSSM_MBOXRSTEN                                  0x00000001U
#define SOC_AON_DBGSSDSSM_MBOXRSTEN_M                                0x00000001U
#define SOC_AON_DBGSSDSSM_MBOXRSTEN_S                                0U
/*

        Field:           SWJINSTID
        From..to bits:   9...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Single wire Jtag, these field set the instance ID for multi probe SWJDP configuration,
                         going to debugss and locked on boot done

*/
#define SOC_AON_DBGSSDSSM_SWJINSTID_W                                4U
#define SOC_AON_DBGSSDSSM_SWJINSTID_M                                0x00001E00U
#define SOC_AON_DBGSSDSSM_SWJINSTID_S                                9U
/*

        Field:           WSOCCPU
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     WSOC MCU , debug port present (enable), locked on boot done

*/
#define SOC_AON_DBGSSDSSM_WSOCCPU                                    0x00010000U
#define SOC_AON_DBGSSDSSM_WSOCCPU_M                                  0x00010000U
#define SOC_AON_DBGSSDSSM_WSOCCPU_S                                  16U
/*

        Field:           WLPHYCPU
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     WLPHY MCU , debug port present (enable), locked on boot done

*/
#define SOC_AON_DBGSSDSSM_WLPHYCPU                                   0x00020000U
#define SOC_AON_DBGSSDSSM_WLPHYCPU_M                                 0x00020000U
#define SOC_AON_DBGSSDSSM_WLPHYCPU_S                                 17U
/*

        Field:           BLE
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     BLE MCU , debug port present (enable), locked on boot done

*/
#define SOC_AON_DBGSSDSSM_BLE                                        0x00040000U
#define SOC_AON_DBGSSDSSM_BLE_M                                      0x00040000U
#define SOC_AON_DBGSSDSSM_BLE_S                                      18U
/*

        Field:           APPSCPU
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST M33 MCU , debug port present (enable), locked on boot done
                         applicable only for MDB

*/
#define SOC_AON_DBGSSDSSM_APPSCPU                                    0x00080000U
#define SOC_AON_DBGSSDSSM_APPSCPU_M                                  0x00080000U
#define SOC_AON_DBGSSDSSM_APPSCPU_S                                  19U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3CFG
    Offset name:         SOC_AON_O_ESM3CFG
    Relative address:    0x20B4
    Description:         ESM3 Configuration- TI Debug Enable Sequence Monitor.

                        Enable timeout mechanism and timeout counter value.
    Default Value:       0x00000001

        Field:           ENTIMEOUT
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field enables timeout mechanism for ESM.

*/
#define SOC_AON_ESM3CFG_ENTIMEOUT                                    0x00000001U
#define SOC_AON_ESM3CFG_ENTIMEOUT_M                                  0x00000001U
#define SOC_AON_ESM3CFG_ENTIMEOUT_S                                  0U
/*

        Field:           TIMEOUTCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field sets the timeout value.
                         time resolution equals to 16us. while:
                         value 0 representing 16us
                         value 1 - 2*16us
                         value 2 - 3*16us and so on.
                         value 15 is not supported.

*/
#define SOC_AON_ESM3CFG_TIMEOUTCNT_W                                 4U
#define SOC_AON_ESM3CFG_TIMEOUTCNT_M                                 0x00000F00U
#define SOC_AON_ESM3CFG_TIMEOUTCNT_S                                 8U
/*

        Field:           BACK2IDLE
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     1 - Allow ESM3 to be restarted (IDLE) when entering Elevated mode
                         0 - Keep ESM3 state (not restarted) when entering Elevated mode

*/
#define SOC_AON_ESM3CFG_BACK2IDLE                                    0x00010000U
#define SOC_AON_ESM3CFG_BACK2IDLE_M                                  0x00010000U
#define SOC_AON_ESM3CFG_BACK2IDLE_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3EN1
    Offset name:         SOC_AON_O_ESM3EN1
    Relative address:    0x20B8
    Description:         ESM3 Enable Number 1.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 1st enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM3EN1_EN1                                          0x00000001U
#define SOC_AON_ESM3EN1_EN1_M                                        0x00000001U
#define SOC_AON_ESM3EN1_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3EN2
    Offset name:         SOC_AON_O_ESM3EN2
    Relative address:    0x20BC
    Description:         ESM3 Enable Number 2.
    Default Value:       NA

        Field:           EN2
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 2nd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM3EN2_EN2                                          0x00000001U
#define SOC_AON_ESM3EN2_EN2_M                                        0x00000001U
#define SOC_AON_ESM3EN2_EN2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3EN3
    Offset name:         SOC_AON_O_ESM3EN3
    Relative address:    0x20C0
    Description:         ESM3 Enable Number 3.
    Default Value:       NA

        Field:           EN3
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 3rd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM3EN3_EN3                                          0x00000001U
#define SOC_AON_ESM3EN3_EN3_M                                        0x00000001U
#define SOC_AON_ESM3EN3_EN3_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3EN4
    Offset name:         SOC_AON_O_ESM3EN4
    Relative address:    0x20C4
    Description:         ESM3 Enable Number 4.
    Default Value:       NA

        Field:           EN4
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 4th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM3EN4_EN4                                          0x00000001U
#define SOC_AON_ESM3EN4_EN4_M                                        0x00000001U
#define SOC_AON_ESM3EN4_EN4_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3EN5
    Offset name:         SOC_AON_O_ESM3EN5
    Relative address:    0x20C8
    Description:         ESM3 Enable Number 5.
    Default Value:       NA

        Field:           EN5
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 5th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM3EN5_EN5                                          0x00000001U
#define SOC_AON_ESM3EN5_EN5_M                                        0x00000001U
#define SOC_AON_ESM3EN5_EN5_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE0
    Offset name:         SOC_AON_O_FUSELINE0
    Relative address:    0x20CC
    Description:         Fuse Line 0.

                        Actual fuse line is 32
    Default Value:       NA

        Field:           DEVLCHW
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device Life Cycle (HW Managed) - Programmed on Package
                         0 - 1st Birthday
                         1 - ATTEST (For Development)
                         3 - Operational (For Customer)
                         7 - Reserved

*/
#define SOC_AON_FUSELINE0_DEVLCHW_W                                  4U
#define SOC_AON_FUSELINE0_DEVLCHW_M                                  0x0000000FU
#define SOC_AON_FUSELINE0_DEVLCHW_S                                  0U
/*

        Field:           DEVLCSW
        From..to bits:   4...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device Life Cycle (SW Managed)

*/
#define SOC_AON_FUSELINE0_DEVLCSW_W                                  4U
#define SOC_AON_FUSELINE0_DEVLCSW_M                                  0x000000F0U
#define SOC_AON_FUSELINE0_DEVLCSW_S                                  4U
/*

        Field:           DEVLCSPAT
        From..to bits:   8...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device Life Cycle Operational (Strong Pattern)
                         24'hca5b3a
                         Device Life Cycle AT TEST Privilege  (Strong Pattern)
                         Allows unhide the assets in device AT TEST for TI debug/development.
                         24'h484a28 (This number allows moving to operational assuming no HW CRC is disabled)

*/
#define SOC_AON_FUSELINE0_DEVLCSPAT_W                                24U
#define SOC_AON_FUSELINE0_DEVLCSPAT_M                                0xFFFFFF00U
#define SOC_AON_FUSELINE0_DEVLCSPAT_S                                8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE1
    Offset name:         SOC_AON_O_FUSELINE1
    Relative address:    0x20D0
    Description:         Fuse Line 1.

                        Actual fuse line is 33.
    Default Value:       NA

        Field:           UNQ31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Identification [31:0]

*/
#define SOC_AON_FUSELINE1_UNQ31TO0_W                                 32U
#define SOC_AON_FUSELINE1_UNQ31TO0_M                                 0xFFFFFFFFU
#define SOC_AON_FUSELINE1_UNQ31TO0_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE2
    Offset name:         SOC_AON_O_FUSELINE2
    Relative address:    0x20D4
    Description:         Fuse Line 2.

                        Actual fuse line is 34.
    Default Value:       NA

        Field:           UNQ63TO32
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Identification [63:32]

*/
#define SOC_AON_FUSELINE2_UNQ63TO32_W                                32U
#define SOC_AON_FUSELINE2_UNQ63TO32_M                                0xFFFFFFFFU
#define SOC_AON_FUSELINE2_UNQ63TO32_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE3
    Offset name:         SOC_AON_O_FUSELINE3
    Relative address:    0x20D8
    Description:         Fuse Line 3.

                        Actual fuse line is 35.
    Default Value:       NA

        Field:           UNQS31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Secret [31:0]

*/
#define SOC_AON_FUSELINE3_UNQS31TO0_W                                32U
#define SOC_AON_FUSELINE3_UNQS31TO0_M                                0xFFFFFFFFU
#define SOC_AON_FUSELINE3_UNQS31TO0_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE4
    Offset name:         SOC_AON_O_FUSELINE4
    Relative address:    0x20DC
    Description:         Fuse Line 4.

                        Actual fuse line is 36.
    Default Value:       NA

        Field:           UNQS63TO32
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Secret [63:32]

*/
#define SOC_AON_FUSELINE4_UNQS63TO32_W                               32U
#define SOC_AON_FUSELINE4_UNQS63TO32_M                               0xFFFFFFFFU
#define SOC_AON_FUSELINE4_UNQS63TO32_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE5
    Offset name:         SOC_AON_O_FUSELINE5
    Relative address:    0x20E0
    Description:         Fuse Line 5.

                        Actual fuse line is 37.
    Default Value:       NA

        Field:           UNQS95TO64
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Secret [95:64]

*/
#define SOC_AON_FUSELINE5_UNQS95TO64_W                               32U
#define SOC_AON_FUSELINE5_UNQS95TO64_M                               0xFFFFFFFFU
#define SOC_AON_FUSELINE5_UNQS95TO64_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE6
    Offset name:         SOC_AON_O_FUSELINE6
    Relative address:    0x20E4
    Description:         Fuse Line 6.

                        Actual fuse line is 38.
    Default Value:       NA

        Field:           UNQS127TO96
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Unique Device Secret [127:96]

*/
#define SOC_AON_FUSELINE6_UNQS127TO96_W                              32U
#define SOC_AON_FUSELINE6_UNQS127TO96_M                              0xFFFFFFFFU
#define SOC_AON_FUSELINE6_UNQS127TO96_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE7
    Offset name:         SOC_AON_O_FUSELINE7
    Relative address:    0x20E8
    Description:         Fuse Line 7.

                        Actual fuse line is 39.
    Default Value:       NA

        Field:           HWCRCEN
        From..to bits:   0...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     HW CRC check Enable/Disable:
                         0 - Disable
                         other (1-7) - Enable
                         (When HW check these bits: if equal to '0' do not check otherwise check.)

*/
#define SOC_AON_FUSELINE7_HWCRCEN_W                                  3U
#define SOC_AON_FUSELINE7_HWCRCEN_M                                  0x00000007U
#define SOC_AON_FUSELINE7_HWCRCEN_S                                  0U
/*

        Field:           SWCRCEN
        From..to bits:   3...5
        DefaultValue:    NA
        Access type:     read-only
        Description:     SW CRC check Enable/Disable:
                         0 - Disable
                         Other (1-7) - Enable
                         (When SW check these bits: if equal to '0' do not check otherwise check.)

*/
#define SOC_AON_FUSELINE7_SWCRCEN_W                                  3U
#define SOC_AON_FUSELINE7_SWCRCEN_M                                  0x00000038U
#define SOC_AON_FUSELINE7_SWCRCEN_S                                  3U
/*

        Field:           BOOTLVL
        From..to bits:   6...9
        DefaultValue:    NA
        Access type:     read-only
        Description:     Determine which part of the boot ROM bypass options for risk mitigation
                         Level0 - Do not bypass anything
                         Level1- Ignore Error
                         Level2 - TI ROM bypass
                         Level3 - Minimize access to HW. Do min mandatory.
                         0b0110 - Level3
                         0b1010 - Level 2
                         0b0101 - Level 1
                         All the rest - Level 0

*/
#define SOC_AON_FUSELINE7_BOOTLVL_W                                  4U
#define SOC_AON_FUSELINE7_BOOTLVL_M                                  0x000003C0U
#define SOC_AON_FUSELINE7_BOOTLVL_S                                  6U
/*

        Field:           DIS5GHZ
        From..to bits:   12...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable 5GHz
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSELINE7_DIS5GHZ                                    0x00001000U
#define SOC_AON_FUSELINE7_DIS5GHZ_M                                  0x00001000U
#define SOC_AON_FUSELINE7_DIS5GHZ_S                                  12U
/*

        Field:           DIS6GHZ
        From..to bits:   13...13
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable 6GHz
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSELINE7_DIS6GHZ                                    0x00002000U
#define SOC_AON_FUSELINE7_DIS6GHZ_M                                  0x00002000U
#define SOC_AON_FUSELINE7_DIS6GHZ_S                                  13U
/*

        Field:           DISBLE
        From..to bits:   14...14
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable BLE (RFC_MDM_CLKEN)
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSELINE7_DISBLE                                     0x00004000U
#define SOC_AON_FUSELINE7_DISBLE_M                                   0x00004000U
#define SOC_AON_FUSELINE7_DISBLE_S                                   14U
/*

        Field:           DISBLEM0P
        From..to bits:   15...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable BLE M0+ (RFC_CPE_CLKEN )
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSELINE7_DISBLEM0P                                  0x00008000U
#define SOC_AON_FUSELINE7_DISBLEM0P_M                                0x00008000U
#define SOC_AON_FUSELINE7_DISBLEM0P_S                                15U
/*

        Field:           DISM33
        From..to bits:   16...16
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable M33
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)

*/
#define SOC_AON_FUSELINE7_DISM33                                     0x00010000U
#define SOC_AON_FUSELINE7_DISM33_M                                   0x00010000U
#define SOC_AON_FUSELINE7_DISM33_S                                   16U
/*

        Field:           TEMP
        From..to bits:   17...18
        DefaultValue:    NA
        Access type:     read-only
        Description:     Supported Temperature
                         00 - 85degC
                         01 - 105degC
                         10 - 125degC
                         11 - Reserved

*/
#define SOC_AON_FUSELINE7_TEMP_W                                     2U
#define SOC_AON_FUSELINE7_TEMP_M                                     0x00060000U
#define SOC_AON_FUSELINE7_TEMP_S                                     17U
/*

        Field:           DISCANFD
        From..to bits:   19...19
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable CAN FD - to eliminate the need to pay royalties
                         0 - Enable
                         1 - Disable
                         (In probe we can program '0' (which practically means not programming) to achieve continuous programming it of all shifted rows)
                         HCANEN (Enable/Disable the CAN IP) - Determined according to paper spin
                         HCANRAMEN(Enable disable access to CAN memory) - Determined according to paper spin.
                         HCANFDEN - Disable/Enable CAN. Determined according to eFuse bit (this bit)

*/
#define SOC_AON_FUSELINE7_DISCANFD                                   0x00080000U
#define SOC_AON_FUSELINE7_DISCANFD_M                                 0x00080000U
#define SOC_AON_FUSELINE7_DISCANFD_S                                 19U
/*

        Field:           MEMSTCK
        From..to bits:   20...22
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enable watchdog timer for protecting boot:
                         (This enable M33 watchdog second threshold to reset device when asserted).
                         0 - Disable Boot Watchdog
                         1 - Enable Boot Watchdog

*/
#define SOC_AON_FUSELINE7_MEMSTCK_W                                  3U
#define SOC_AON_FUSELINE7_MEMSTCK_M                                  0x00700000U
#define SOC_AON_FUSELINE7_MEMSTCK_S                                  20U
/*

        Field:           ENBOOTWDT
        From..to bits:   23...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enable watchdog timer for protecting boot:
                         (This enable M33 watchdog second threshold to reset device when asserted).
                         0 - Disable Boot Watchdog
                         1 - Enable Boot Watchdog

*/
#define SOC_AON_FUSELINE7_ENBOOTWDT                                  0x00800000U
#define SOC_AON_FUSELINE7_ENBOOTWDT_M                                0x00800000U
#define SOC_AON_FUSELINE7_ENBOOTWDT_S                                23U
/*

        Field:           RANDDLYEN
        From..to bits:   24...24
        DefaultValue:    NA
        Access type:     read-only
        Description:     Random Delay Enable:
                         0 - Disable
                         1 - Enable

*/
#define SOC_AON_FUSELINE7_RANDDLYEN                                  0x01000000U
#define SOC_AON_FUSELINE7_RANDDLYEN_M                                0x01000000U
#define SOC_AON_FUSELINE7_RANDDLYEN_S                                24U
/*

        Field:           DISVERB
        From..to bits:   25...25
        DefaultValue:    NA
        Access type:     read-only
        Description:     Disable Verbose Mode
                         0 - Verbose Mode (Enable) - Full Logger
                         1 - Normal Mode (Disable)

*/
#define SOC_AON_FUSELINE7_DISVERB                                    0x02000000U
#define SOC_AON_FUSELINE7_DISVERB_M                                  0x02000000U
#define SOC_AON_FUSELINE7_DISVERB_S                                  25U
/*

        Field:           RESBOOTEXE
        From..to bits:   26...26
        DefaultValue:    NA
        Access type:     read-only
        Description:     Resume boot in non-normal boot flows where the boot cannot progress (e.g. when assets are hidden). For example, in forced supply in operational or deployed life cycles, 1st bday/at test (normal) life cycles, etc.

                         0 - Halt boot execution as early as possible
                         1 - Resume/Continue boot execution

                         This bit is ignored when the device can run the boot flow normally (e.g. deployed life cycle with default SOP).

*/
#define SOC_AON_FUSELINE7_RESBOOTEXE                                 0x04000000U
#define SOC_AON_FUSELINE7_RESBOOTEXE_M                               0x04000000U
#define SOC_AON_FUSELINE7_RESBOOTEXE_S                               26U
/*

        Field:           LDAUTHEN
        From..to bits:   27...28
        DefaultValue:    NA
        Access type:     read-only
        Description:     RAM Bootloader authentication enable:
                         00 - Disable
                         Other- Enable

*/
#define SOC_AON_FUSELINE7_LDAUTHEN_W                                 2U
#define SOC_AON_FUSELINE7_LDAUTHEN_M                                 0x18000000U
#define SOC_AON_FUSELINE7_LDAUTHEN_S                                 27U
/*

        Field:           PRIVDBGREQ
        From..to bits:   29...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Enforce TI privilege Debug Request (Relevant  in AT TEST privilege only  used by SW)
                         0 - Disable
                         other (1-7) - Enable
                         (When SW check these bits: if equal to '0' bypass otherwise check.)

*/
#define SOC_AON_FUSELINE7_PRIVDBGREQ_W                               3U
#define SOC_AON_FUSELINE7_PRIVDBGREQ_M                               0xE0000000U
#define SOC_AON_FUSELINE7_PRIVDBGREQ_S                               29U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELINE8
    Offset name:         SOC_AON_O_FUSELINE8
    Relative address:    0x20EC
    Description:         Fuse Line 8.

                        Actual fuse line is 40.
    Default Value:       0x00000000

        Field:           HWCRCVAL
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW CRC Check for all shifted rows.
                         XORs operation with 0x04C11DB7 CRC32 polynomial engine.
                         Init value = 0

*/
#define SOC_AON_FUSELINE8_HWCRCVAL_W                                 32U
#define SOC_AON_FUSELINE8_HWCRCVAL_M                                 0xFFFFFFFFU
#define SOC_AON_FUSELINE8_HWCRCVAL_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSECTL
    Offset name:         SOC_AON_O_FUSECTL
    Relative address:    0x2100
    Description:         Fuse Access Control.

                        disconnect fuse from OCP access.
                        locked with fuse_ocp_disable_lock.
    Default Value:       0x00000000

        Field:           OCPDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Disconnect FUSE FARM and OTP OCP access, should be configured once as locked on boot done

*/
#define SOC_AON_FUSECTL_OCPDIS                                       0x00000001U
#define SOC_AON_FUSECTL_OCPDIS_M                                     0x00000001U
#define SOC_AON_FUSECTL_OCPDIS_S                                     0U
/*

        Field:           OCPEN
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OTP FROM , when jtag is 1 the i/f is jtag regardless of ocp_en
                         to enable OCP need to write this bit to 1 and jtag to 0
                         '1' by default. optional - write once to '0'.

*/
#define SOC_AON_FUSECTL_OCPEN                                        0x00000002U
#define SOC_AON_FUSECTL_OCPEN_M                                      0x00000002U
#define SOC_AON_FUSECTL_OCPEN_S                                      1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       COREMEMCTL
    Offset name:         SOC_AON_O_COREMEMCTL
    Relative address:    0x2104
    Description:         CORE Memory Access Control
                        CORE CPU:
                        Allow M3 Fetch From non-owned memory
                        Allow WiFi M0+ Fetch From non-owned memory
                        Allow BLE M0+ Fetch From non-owned memory
    Default Value:       NA

        Field:           WLPHYFETCH
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     Allow WiFi M0+ Fetch From non-owned memory

*/
#define SOC_AON_COREMEMCTL_WLPHYFETCH                                0x00000001U
#define SOC_AON_COREMEMCTL_WLPHYFETCH_M                              0x00000001U
#define SOC_AON_COREMEMCTL_WLPHYFETCH_S                              0U
/*

        Field:           WSOCMCUFET
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     Allow M3 Fetch From non-owned memory

*/
#define SOC_AON_COREMEMCTL_WSOCMCUFET                                0x00000002U
#define SOC_AON_COREMEMCTL_WSOCMCUFET_M                              0x00000002U
#define SOC_AON_COREMEMCTL_WSOCMCUFET_S                              1U
/*

        Field:           BLEFETCH
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     Allow BLE M0+ Fetch From non-owned memory

*/
#define SOC_AON_COREMEMCTL_BLEFETCH                                  0x00000004U
#define SOC_AON_COREMEMCTL_BLEFETCH_M                                0x00000004U
#define SOC_AON_COREMEMCTL_BLEFETCH_S                                2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       COREGPCTL
    Offset name:         SOC_AON_O_COREGPCTL
    Relative address:    0x2108
    Description:         Access Control - Core Global Port Enable
    Default Value:       0x00000001

        Field:           ALLOW
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Allow CORE global port.
                         when enabled allow access to core (based on firewall configuration), must stay enabled to allow host access to Nub (sdio) and locked on soc_boot_done

*/
#define SOC_AON_COREGPCTL_ALLOW                                      0x00000001U
#define SOC_AON_COREGPCTL_ALLOW_M                                    0x00000001U
#define SOC_AON_COREGPCTL_ALLOW_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSSGPCTL
    Offset name:         SOC_AON_O_MEMSSGPCTL
    Relative address:    0x210C
    Description:         MEMSS Global Port Access Control.

                        Allow access to entire memss through memss global port.
                        Default: Access is disabled
    Default Value:       0x00000000

        Field:           ALLOW
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Access is allowed to both M33 & M3 during privilege boot and changed to M3 only (fixed firewall) after boot (controlled by soc_boot_done)

*/
#define SOC_AON_MEMSSGPCTL_ALLOW                                     0x00000001U
#define SOC_AON_MEMSSGPCTL_ALLOW_M                                   0x00000001U
#define SOC_AON_MEMSSGPCTL_ALLOW_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEFUSECTL
    Offset name:         SOC_AON_O_BLEFUSECTL
    Relative address:    0x2110
    Description:         BLE Fuse Access Control.

                        Disable BLE modem and CPE clock - based on indication bits on fuse
    Default Value:       NA

        Field:           CPEOFF
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This control disable the clk  to the CPE clk gate. should be disabled in WIFI only paper spin (based on fuse)

*/
#define SOC_AON_BLEFUSECTL_CPEOFF                                    0x00000001U
#define SOC_AON_BLEFUSECTL_CPEOFF_M                                  0x00000001U
#define SOC_AON_BLEFUSECTL_CPEOFF_S                                  0U
/*

        Field:           MDMOFF
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     Disable the BLE MDM clock , should be configured based on fuse pare spin

*/
#define SOC_AON_BLEFUSECTL_MDMOFF                                    0x00000002U
#define SOC_AON_BLEFUSECTL_MDMOFF_M                                  0x00000002U
#define SOC_AON_BLEFUSECTL_MDMOFF_S                                  1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE4
    Offset name:         SOC_AON_O_SPARE4
    Relative address:    0x2118
    Description:         not in use.
                        can be use as spare
    Default Value:       NA

        Field:           BIT
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     spare bit

*/
#define SOC_AON_SPARE4_BIT                                           0x00000001U
#define SOC_AON_SPARE4_BIT_M                                         0x00000001U
#define SOC_AON_SPARE4_BIT_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4CFG
    Offset name:         SOC_AON_O_ESM4CFG
    Relative address:    0x211C
    Description:         ESM4 Configuration- TI DFT Enable Sequence Monitor.

                        Enable timeout mechanism and timeout counter value.
    Default Value:       0x00000001

        Field:           ENTIMEOUT
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field enables timeout mechanism for ESM.

*/
#define SOC_AON_ESM4CFG_ENTIMEOUT                                    0x00000001U
#define SOC_AON_ESM4CFG_ENTIMEOUT_M                                  0x00000001U
#define SOC_AON_ESM4CFG_ENTIMEOUT_S                                  0U
/*

        Field:           TIMEOUTCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field sets the timeout value.
                         time resolution equals to 16us. while:
                         value 0 representing 16us
                         value 1 - 2*16us
                         value 2 - 3*16us and so on.
                         value 15 is not supported.

*/
#define SOC_AON_ESM4CFG_TIMEOUTCNT_W                                 4U
#define SOC_AON_ESM4CFG_TIMEOUTCNT_M                                 0x00000F00U
#define SOC_AON_ESM4CFG_TIMEOUTCNT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4EN1
    Offset name:         SOC_AON_O_ESM4EN1
    Relative address:    0x2120
    Description:         ESM4 Enable Number 1.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 1st enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM4EN1_EN1                                          0x00000001U
#define SOC_AON_ESM4EN1_EN1_M                                        0x00000001U
#define SOC_AON_ESM4EN1_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4EN2
    Offset name:         SOC_AON_O_ESM4EN2
    Relative address:    0x2124
    Description:         ESM4 Enable Number 2.
    Default Value:       NA

        Field:           EN2
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 2nd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM4EN2_EN2                                          0x00000001U
#define SOC_AON_ESM4EN2_EN2_M                                        0x00000001U
#define SOC_AON_ESM4EN2_EN2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4EN3
    Offset name:         SOC_AON_O_ESM4EN3
    Relative address:    0x2128
    Description:         ESM4 Enable Number 3.
    Default Value:       NA

        Field:           EN4
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 3rd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM4EN3_EN4                                          0x00000001U
#define SOC_AON_ESM4EN3_EN4_M                                        0x00000001U
#define SOC_AON_ESM4EN3_EN4_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4EN4
    Offset name:         SOC_AON_O_ESM4EN4
    Relative address:    0x212C
    Description:         ESM4 Enable Number 4.
    Default Value:       NA

        Field:           EN4
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 4th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM4EN4_EN4                                          0x00000001U
#define SOC_AON_ESM4EN4_EN4_M                                        0x00000001U
#define SOC_AON_ESM4EN4_EN4_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4EN5
    Offset name:         SOC_AON_O_ESM4EN5
    Relative address:    0x2130
    Description:         ESM4 Enable Number 5.
    Default Value:       NA

        Field:           EN5
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 5th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM4EN5_EN5                                          0x00000001U
#define SOC_AON_ESM4EN5_EN5_M                                        0x00000001U
#define SOC_AON_ESM4EN5_EN5_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMPROT
    Offset name:         SOC_AON_O_MEMPROT
    Relative address:    0x2140
    Description:         This register is locking the CORE related security bits , should be written in boot and on elevated mode exit:
                        [COREMEMCTL],  [CRAMPROT1.FETCHTH], [DRAMPROT1.FETCHTH], [MEMPROT.MEMLOCK], [ROMJUMPCTL.DIS], [DRAMCTL.ERASEASST], [VTORCFG.INIT], [CPEPROT1.RFCOVR], [CPEPROT1.RFCMODE], [CPEPROT1.FETCHTH], [PHYPROT1.FETCHTH]
    Default Value:       0x00000000

        Field:           MEMLOCK
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the configurations on mem prot

*/
#define SOC_AON_MEMPROT_MEMLOCK                                      0x00010000U
#define SOC_AON_MEMPROT_MEMLOCK_M                                    0x00010000U
#define SOC_AON_MEMPROT_MEMLOCK_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       VTORCFG
    Offset name:         SOC_AON_O_VTORCFG
    Relative address:    0x2144
    Description:         WSOC MCU VTOR CONFIGURATION.
                        this is the jump address during boot (default is 0 - Rom) and after boot done - as POR this should be configured to CRAM start during boot of ROM.
                        in boot done command the MCU will jump to this address
    Default Value:       0x00000000

        Field:           INIT
        From..to bits:   7...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     VTOR Init register

*/
#define SOC_AON_VTORCFG_INIT_W                                       25U
#define SOC_AON_VTORCFG_INIT_M                                       0xFFFFFF80U
#define SOC_AON_VTORCFG_INIT_S                                       7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ROMJUMPCTL
    Offset name:         SOC_AON_O_ROMJUMPCTL
    Relative address:    0x2148
    Description:         MCU ROM Jump Disable.

                        Prevents the use of the VTOR function , by default it is off.
    Default Value:       0x00000000

        Field:           DIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - CTX icode bus jumps from 0x0/0x04 to vtor/vtor+4.
                         1 - Do not jump.

*/
#define SOC_AON_ROMJUMPCTL_DIS                                       0x00000001U
#define SOC_AON_ROMJUMPCTL_DIS_M                                     0x00000001U
#define SOC_AON_ROMJUMPCTL_DIS_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRAMPROT1
    Offset name:         SOC_AON_O_CRAMPROT1
    Relative address:    0x214C
    Description:         Execution RAM (CRAM) - Threshold register
    Default Value:       0x00000000

        Field:           WRTH
        From..to bits:   7...15
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Below this CRAM Threshold register - Fetch/read only after 'mem_cram_write_disable_pulse'.
                         Write is allowed above this threshold regardless to S/W setting the [CRAMPROT0.WRDIS].
                         Resolution is 1KB: (1- 1KB, 2 - 2KB, ..., 511 - 511KB). Effectively we have 76+398KB of Code-RAM

*/
#define SOC_AON_CRAMPROT1_WRTH_W                                     9U
#define SOC_AON_CRAMPROT1_WRTH_M                                     0x0000FF80U
#define SOC_AON_CRAMPROT1_WRTH_S                                     7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CRAMPROT0
    Offset name:         SOC_AON_O_CRAMPROT0
    Relative address:    0x2150
    Description:         Execution RAM (CRAM) - Protect from write
    Default Value:       0x00000000

        Field:           WRDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write Once MMR protection - Do not allow writing to CRAM (below a threshold) after this MMR is set.
                         Before this MMR is set - write is allowed , fetch is not allowed. (for all the memory)
                         S/W pulse (WRCL) that sets an H/W F.F - cannot be cleared by S/W.


*/
#define SOC_AON_CRAMPROT0_WRDIS                                      0x00000001U
#define SOC_AON_CRAMPROT0_WRDIS_M                                    0x00000001U
#define SOC_AON_CRAMPROT0_WRDIS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DRAMPROT1
    Offset name:         SOC_AON_O_DRAMPROT1
    Relative address:    0x2154
    Description:         Data RAM (DRAM) - Threshold register
    Default Value:       0x00000000

        Field:           FETCHTH
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Below this DRAM Threshold register - read/write only (never-execute-region) after 'mem_dram_fetch_disable_pulse'.
                         Fetch is allowed above this threshold regardless to S/W setting the [DRAMPROT0.FETCHDIS].
                         Resolution is 1KB: (1- 1KB, 2 - 2KB, ..., 255 - 255KB). Effectively we have 144KB of Data-RAM.
                         [Cortex fetch from 61xx_xxxx (executable region) instead of 45xx_xxxx and the address is automatically (MCUSS H/W) remapped to 45xx_xxxx]

*/
#define SOC_AON_DRAMPROT1_FETCHTH_W                                  8U
#define SOC_AON_DRAMPROT1_FETCHTH_M                                  0x00007F80U
#define SOC_AON_DRAMPROT1_FETCHTH_S                                  7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DRAMPROT0
    Offset name:         SOC_AON_O_DRAMPROT0
    Relative address:    0x2158
    Description:         Data RAM (DRAM) - Protect from fetch
    Default Value:       0x00000100

        Field:           FETCHDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write Once MMR protection - Do not allow fetching from DRAM (below a threshold) after this MMR is set.
                         Before this MMR is set - write is allowed , fetch is not allowed. (for all the memory)
                         S/W pulse (WRCL) that sets an H/W F.F - cannot be cleared by S/W.

*/
#define SOC_AON_DRAMPROT0_FETCHDIS                                   0x00000001U
#define SOC_AON_DRAMPROT0_FETCHDIS_M                                 0x00000001U
#define SOC_AON_DRAMPROT0_FETCHDIS_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRAMPROT0
    Offset name:         SOC_AON_O_PRAMPROT0
    Relative address:    0x215C
    Description:         Packet RAM (PRAM) - Protect from fetch
    Default Value:       0x00000100

        Field:           FETCHDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write Once MMR protection - Do not allow fetching from PRAM after this MMR is set.
                         Before this MMR is set - write is allowed , fetch is not allowed.
                         S/W pulse (WRCL) that sets an H/W F.F - cannot be cleared by S/W.

*/
#define SOC_AON_PRAMPROT0_FETCHDIS                                   0x00000001U
#define SOC_AON_PRAMPROT0_FETCHDIS_M                                 0x00000001U
#define SOC_AON_PRAMPROT0_FETCHDIS_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STRONGPAT
    Offset name:         SOC_AON_O_STRONGPAT
    Relative address:    0x2160
    Description:         Security Strong Pattern.
                        the 24 bit pattern that is burn on the fuse to qualify the fuse data against possible attack
    Default Value:       NA

        Field:           PAT
        From..to bits:   0...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     24 bit pattern from fuse

*/
#define SOC_AON_STRONGPAT_PAT_W                                      24U
#define SOC_AON_STRONGPAT_PAT_M                                      0x00FFFFFFU
#define SOC_AON_STRONGPAT_PAT_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDS0
    Offset name:         SOC_AON_O_UDS0
    Relative address:    0x2164
    Description:         Unique Device Secret. 31-0
    Default Value:       NA

        Field:           31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     bits 31-0

*/
#define SOC_AON_UDS0_31TO0_W                                         32U
#define SOC_AON_UDS0_31TO0_M                                         0xFFFFFFFFU
#define SOC_AON_UDS0_31TO0_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDS1
    Offset name:         SOC_AON_O_UDS1
    Relative address:    0x2168
    Description:         Unique Device Secret. 63-32
    Default Value:       NA

        Field:           63TO32
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Bits 63-32

*/
#define SOC_AON_UDS1_63TO32_W                                        32U
#define SOC_AON_UDS1_63TO32_M                                        0xFFFFFFFFU
#define SOC_AON_UDS1_63TO32_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDS2
    Offset name:         SOC_AON_O_UDS2
    Relative address:    0x216C
    Description:         Unique Device Secret. 95-64
    Default Value:       NA

        Field:           95TO64
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Bits 95-64

*/
#define SOC_AON_UDS2_95TO64_W                                        32U
#define SOC_AON_UDS2_95TO64_M                                        0xFFFFFFFFU
#define SOC_AON_UDS2_95TO64_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       UDS3
    Offset name:         SOC_AON_O_UDS3
    Relative address:    0x2170
    Description:         Unique Device Secret. 127-96
    Default Value:       NA

        Field:           127TO96
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Bits 127-96

*/
#define SOC_AON_UDS3_127TO96_W                                       32U
#define SOC_AON_UDS3_127TO96_M                                       0xFFFFFFFFU
#define SOC_AON_UDS3_127TO96_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGBUS
    Offset name:         SOC_AON_O_DBGBUS
    Relative address:    0x2174
    Description:         SOC_AON Debug Bus.
                        This register sets the debug over sleep and IOMUX debug bus selection
    Default Value:       0x00000000

        Field:           IOCLKSEL
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     selects the clock source for iomux debug clk
                         0 :SCLK
                         1: SOC CLK (40)
                         2: CORE M3 CLK (80)

*/
#define SOC_AON_DBGBUS_IOCLKSEL_W                                    2U
#define SOC_AON_DBGBUS_IOCLKSEL_M                                    0x00000003U
#define SOC_AON_DBGBUS_IOCLKSEL_S                                    0U
/*

        Field:           OCLASEL
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     OCLA bus upper/lower selector.
                         selects upper or lower 16 bits out of the ocla bus of 32
                         '1' - 16 MSBs
                         '0' - 16 LSBs

*/
#define SOC_AON_DBGBUS_OCLASEL                                       0x00000004U
#define SOC_AON_DBGBUS_OCLASEL_M                                     0x00000004U
#define SOC_AON_DBGBUS_OCLASEL_S                                     2U
/*

        Field:           ELPUPSEL
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM ELP Upper Byte Selector.

                         Chooses upper byte out of prcm elp 32 bit
                         '00' - [7:0]
                         '01' - [15:8]
                         '10' - [23:16]
                         '11' - [31:24]

*/
#define SOC_AON_DBGBUS_ELPUPSEL_W                                    2U
#define SOC_AON_DBGBUS_ELPUPSEL_M                                    0x00000018U
#define SOC_AON_DBGBUS_ELPUPSEL_S                                    3U
/*

        Field:           ELPLOSEL
        From..to bits:   5...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM ELP Lower Byte Selector.

                         Chooses lower byte out of prcm elp 32 bit
                         '00' - [7:0]
                         '01' - [15:8]
                         '10' - [23:16]
                         '11' - [31:24]

*/
#define SOC_AON_DBGBUS_ELPLOSEL_W                                    2U
#define SOC_AON_DBGBUS_ELPLOSEL_M                                    0x00000060U
#define SOC_AON_DBGBUS_ELPLOSEL_S                                    5U
/*

        Field:           ELPLOPSEL
        From..to bits:   7...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM ELP Lower Port Selector.

                         Chooses lower byte port
                         '00' - prcm tp1
                         '01' - prcm tp2
                         '10' - elp tp1
                         '11' - elp tp2

*/
#define SOC_AON_DBGBUS_ELPLOPSEL_W                                   2U
#define SOC_AON_DBGBUS_ELPLOPSEL_M                                   0x00000180U
#define SOC_AON_DBGBUS_ELPLOPSEL_S                                   7U
/*

        Field:           ELPUPPSEL
        From..to bits:   9...10
        DefaultValue:    0x0
        Access type:     read-write
        Description:     PRCM ELP Upper Port Selector.

                         Chooses upper byte port
                         '00' - prcm tp1
                         '01' - prcm tp2
                         '10' - elp tp1
                         '11' - elp tp2

*/
#define SOC_AON_DBGBUS_ELPUPPSEL_W                                   2U
#define SOC_AON_DBGBUS_ELPUPPSEL_M                                   0x00000600U
#define SOC_AON_DBGBUS_ELPUPPSEL_S                                   9U
/*

        Field:           AODSEL
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC AOD Upper/Lower Selector.

                         selects upper or lower 16 bits out of the soc aod bus of 32
                         '1' - 16 MSBs
                         '0' - 16 LSBs

*/
#define SOC_AON_DBGBUS_AODSEL                                        0x00000800U
#define SOC_AON_DBGBUS_AODSEL_M                                      0x00000800U
#define SOC_AON_DBGBUS_AODSEL_S                                      11U
/*

        Field:           AODPSEL
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     SOC AOD Port Selector.

                         Chooses soc aod port
                         '000' - host_aon_tp1
                         '001' - host_aon_tp2
                         '010' - io mux tp1
                         '011' - io mux tp2
                         '100' - debug aon tp1
                         '101' - debug aon tp2
                         '110' - soc aon tp1
                         '111' - rtc_tp1

*/
#define SOC_AON_DBGBUS_AODPSEL_W                                     3U
#define SOC_AON_DBGBUS_AODPSEL_M                                     0x00007000U
#define SOC_AON_DBGBUS_AODPSEL_S                                     12U
/*

        Field:           MUXPSEL
        From..to bits:   15...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Debug Mux Port Selector.

                         Chooses debug mux port
                         '00' - prcm/elp
                         '01' - soc aod
                         '10' - ocla

*/
#define SOC_AON_DBGBUS_MUXPSEL_W                                     2U
#define SOC_AON_DBGBUS_MUXPSEL_M                                     0x00018000U
#define SOC_AON_DBGBUS_MUXPSEL_S                                     15U
/*

        Field:           SECSEL
        From..to bits:   17...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Security Debug Selector.

                         selects soc aon debug bus

*/
#define SOC_AON_DBGBUS_SECSEL_W                                      2U
#define SOC_AON_DBGBUS_SECSEL_M                                      0x00060000U
#define SOC_AON_DBGBUS_SECSEL_S                                      17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DEBUGSS
    Offset name:         SOC_AON_O_DEBUGSS
    Relative address:    0x217C
    Description:         DEBUGSS JTAG User Code.

                        This 32 bit register can be read through JTAG , and reflected on CFG-AP
    Default Value:       NA

        Field:           JTAGUSER
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     This 32 bit register can be read through JTAG , and reflected on CFG-AP

*/
#define SOC_AON_DEBUGSS_JTAGUSER_W                                   32U
#define SOC_AON_DEBUGSS_JTAGUSER_M                                   0xFFFFFFFFU
#define SOC_AON_DEBUGSS_JTAGUSER_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CPEPROT1
    Offset name:         SOC_AON_O_CPEPROT1
    Relative address:    0x2180
    Description:         Execution RAM (CRAM) - Threshold register
    Default Value:       0x00318001

        Field:           RFCOVR
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     RFC Confidential Over.

*/
#define SOC_AON_CPEPROT1_RFCOVR                                      0x00000001U
#define SOC_AON_CPEPROT1_RFCOVR_M                                    0x00000001U
#define SOC_AON_CPEPROT1_RFCOVR_S                                    0U
/*

        Field:           RFCMODE
        From..to bits:   1...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     RFC Confidential Mode.

*/
#define SOC_AON_CPEPROT1_RFCMODE_W                                   3U
#define SOC_AON_CPEPROT1_RFCMODE_M                                   0x0000000EU
#define SOC_AON_CPEPROT1_RFCMODE_S                                   1U
/*

        Field:           FETCHTH
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Above this BLE CPE Threshold register - read/write only (never-execute-region) after 'mem_dram_fetch_disable_pulse'.
                         Fetch is allowed below this threshold regardless to S/W setting the [CPEPROT0.FETCHDIS].
                         Resolution is 1KB: (1- 1KB, 2 - 2KB, ..., 255 - 255KB).
                         MSBit not in use (MSBit is reserved bit).

*/
#define SOC_AON_CPEPROT1_FETCHTH_W                                   8U
#define SOC_AON_CPEPROT1_FETCHTH_M                                   0x00007F80U
#define SOC_AON_CPEPROT1_FETCHTH_S                                   7U
/*

        Field:           GENERAL
        From..to bits:   15...18
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Bit 0 is force clk en for all BLE sub clocks . this is enabled on default for safety reasons on boot.
                         this bit should be cleared by SW during boot and then internal IP clock manager takes control

*/
#define SOC_AON_CPEPROT1_GENERAL_W                                   4U
#define SOC_AON_CPEPROT1_GENERAL_M                                   0x00078000U
#define SOC_AON_CPEPROT1_GENERAL_S                                   15U
/*

        Field:           HIACCESS
        From..to bits:   20...23
        DefaultValue:    0x3
        Access type:     read-write
        Description:     Define  the CPE (BLE CM0+) most high address space access allowed (should be configured according to MEM-SS mode).
                         Value granularity is 16K, So for the default allocation of 64k it set to 3. (value 0 is for the lower 16k, value 15 is for 256k)

*/
#define SOC_AON_CPEPROT1_HIACCESS_W                                  4U
#define SOC_AON_CPEPROT1_HIACCESS_M                                  0x00F00000U
#define SOC_AON_CPEPROT1_HIACCESS_S                                  20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CPEPROT0
    Offset name:         SOC_AON_O_CPEPROT0
    Relative address:    0x2184
    Description:         CPE Data RAM (DRAM) - Protect from fetch
    Default Value:       0x00000100

        Field:           FETCHDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write Once MMR protection - Do not allow fetching from DRAM (above a threshold) after this MMR is set.
                         S/W pulse (WRCL) that sets an H/W F.F - cannot be cleared by S/W.

*/
#define SOC_AON_CPEPROT0_FETCHDIS                                    0x00000001U
#define SOC_AON_CPEPROT0_FETCHDIS_M                                  0x00000001U
#define SOC_AON_CPEPROT0_FETCHDIS_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSESHIFT
    Offset name:         SOC_AON_O_FUSESHIFT
    Relative address:    0x2188
    Description:         Security Fuse Shift CRC
                        Calc result on fuse chain
    Default Value:       NA

        Field:           CRCCALC
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     Calc CRC result of fuse chain - this include the CRC result crunching a s well, so expected / correct result would be 0.

*/
#define SOC_AON_FUSESHIFT_CRCCALC_W                                  32U
#define SOC_AON_FUSESHIFT_CRCCALC_M                                  0xFFFFFFFFU
#define SOC_AON_FUSESHIFT_CRCCALC_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECROM
    Offset name:         SOC_AON_O_SECROM
    Relative address:    0x218C
    Description:         Security Hide Rom Assets.

                        SW control to hide ROM assets, written once
    Default Value:       0x00000000

        Field:           HIDEASSETS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     ROM assets is Hidden in case ATTEST or Error or if SOP=FS.
                         during either Operational or ATTEST Privilege:
                         1. ROM assets is Hidden by default
                         2. Unhide ROM assets by setting [UNHIDE] bitfield.
                         3. After unhide ROM it could be Hidden by setting [HIDEASSETS] bitfield.
                         4. ROM will be Hidden when privilege/elevated mode done without dependancy of [HIDEASSETS] field.

                         Type: Write-Clear.

*/
#define SOC_AON_SECROM_HIDEASSETS                                    0x00000001U
#define SOC_AON_SECROM_HIDEASSETS_M                                  0x00000001U
#define SOC_AON_SECROM_HIDEASSETS_S                                  0U
/*

        Field:           UNHIDE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     write-only
        Description:     ROM assets is Hidden in case ATTEST or Error or if SOP=FS.
                         during either Operational or ATTEST Privilege:
                         1. ROM assets is Hidden by default
                         2. Unhide ROM assets by setting [UNHIDE] bitfield.
                         3. After unhide ROM it could be Hidden by setting [HIDEASSETS] bitfield.
                         4. ROM will be Hidden when privilege/elevated mode done without dependancy of [HIDEASSETS] field.

                         Type: Write-Clear.

*/
#define SOC_AON_SECROM_UNHIDE                                        0x00000002U
#define SOC_AON_SECROM_UNHIDE_M                                      0x00000002U
#define SOC_AON_SECROM_UNHIDE_S                                      1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECUDS
    Offset name:         SOC_AON_O_SECUDS
    Relative address:    0x2190
    Description:         Security Hide UDS Assets.

                        SW control to hide UDS assets, written once
    Default Value:       0x00000000

        Field:           HIDEASSETS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     UDS is Hidden in case ATTEST or Error or..
                         during ATTEST-Privilege or Operational-and-not-in-force-supply-SOPs (except during soc privilege in which this MMR applies the hide)
                         Type: Write-Clear.

*/
#define SOC_AON_SECUDS_HIDEASSETS                                    0x00000001U
#define SOC_AON_SECUDS_HIDEASSETS_M                                  0x00000001U
#define SOC_AON_SECUDS_HIDEASSETS_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PHYPROT1
    Offset name:         SOC_AON_O_PHYPROT1
    Relative address:    0x2198
    Description:         WLPHY RAM memory protection - Threshold register
    Default Value:       0x00000000

        Field:           FETCHTH
        From..to bits:   7...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Above this WLPHY  Threshold register - read/write only (never-execute-region) after 'mem_wlphy_fetch_disable_pulse'.
                         Fetch is allowed below this threshold regardless to S/W setting the [PHYPROT0.FETCHDIS].
                         Resolution is 1KB: (1- 1KB, 2 - 2KB, ..., 255 - 255KB).
                         MSBit not in use. (MSBit is reserved bit)

*/
#define SOC_AON_PHYPROT1_FETCHTH_W                                   8U
#define SOC_AON_PHYPROT1_FETCHTH_M                                   0x00007F80U
#define SOC_AON_PHYPROT1_FETCHTH_S                                   7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PHYPROT0
    Offset name:         SOC_AON_O_PHYPROT0
    Relative address:    0x219C
    Description:         WLPHY RAM  - Protect from fetch
    Default Value:       0x00000100

        Field:           FETCHDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write Once MMR protection - Do not allow fetching from WLPHY RAM  (above a threshold) after this MMR is set.
                         S/W pulse (WRCL) that sets an H/W F.F - cannot be cleared by S/W.

*/
#define SOC_AON_PHYPROT0_FETCHDIS                                    0x00000001U
#define SOC_AON_PHYPROT0_FETCHDIS_M                                  0x00000001U
#define SOC_AON_PHYPROT0_FETCHDIS_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESMDIS
    Offset name:         SOC_AON_O_ESMDIS
    Relative address:    0x21A0
    Description:         ESMs Graceful Disable.

                        Setting this bit - moving all ESM's from IDLE state to disabled state and cannot be configured until the next AON reset.
                        notice this can be set only in IDLE mode - prior to other ESM configurations (i,e if ESM state is VIOLATED or DONE it will remain there)
    Default Value:       0x00000100

        Field:           DIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Setting this bit - moving all ESM's from IDLE state to disabled state and cannot be configured until the next AON reset.
                         notice this can be set only in IDLE mode - prior to other ESM configurations (i,e if ESM state is VIOLATED or DONE it will remain there)

*/
#define SOC_AON_ESMDIS_DIS                                           0x00000001U
#define SOC_AON_ESMDIS_DIS_M                                         0x00000001U
#define SOC_AON_ESMDIS_DIS_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE5
    Offset name:         SOC_AON_O_SPARE5
    Relative address:    0x21A4
    Description:         Spare bits , locked on boot
    Default Value:       0x00000000

        Field:           BF0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Spare0 locked on boot done

*/
#define SOC_AON_SPARE5_BF0                                           0x00000001U
#define SOC_AON_SPARE5_BF0_M                                         0x00000001U
#define SOC_AON_SPARE5_BF0_S                                         0U
/*

        Field:           BF1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Spare1 locked on boot done

*/
#define SOC_AON_SPARE5_BF1                                           0x00000002U
#define SOC_AON_SPARE5_BF1_M                                         0x00000002U
#define SOC_AON_SPARE5_BF1_S                                         1U
/*

        Field:           BF2
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Spare2 locked on boot done

*/
#define SOC_AON_SPARE5_BF2                                           0x00000004U
#define SOC_AON_SPARE5_BF2_M                                         0x00000004U
#define SOC_AON_SPARE5_BF2_S                                         2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TOPDBG
    Offset name:         SOC_AON_O_TOPDBG
    Relative address:    0x21A8
    Description:         Top Debug Selectors.

                        This register selects debug ports from Top debug to OCLA.

                        INTERNAL NOTE:
                        [Confluence][https://confluence.itg.ti.com/display/WNG/Osprey+MDB+PG1.0+-+OCLA+integration+Spec]
                        [LINUX- OSPREYMDB - MDBPG10C3V2 Branch][toplevel/wsoc/doc/wsoc.xls]
    Default Value:       NA

        Field:           P2SUB
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Port Set 2 - Submodule Selector.

                         Selects the Submodule from the IP.

                         INTERNAL NOTE-
                         [LINUX- OSPREYMDB - MDBPG10C3V2 Branch][toplevel/wsoc/doc/wsoc.xls]

*/
#define SOC_AON_TOPDBG_P2SUB_W                                       5U
#define SOC_AON_TOPDBG_P2SUB_M                                       0x0000001FU
#define SOC_AON_TOPDBG_P2SUB_S                                       0U
/*

        Field:           P1SUB
        From..to bits:   8...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     Port Set 1 - Submodule Selector.

                         Selects the Submodule from the IP.

                         INTERNAL NOTE-
                         [LINUX- OSPREYMDB - MDBPG10C3V2 Branch][toplevel/wsoc/doc/wsoc.xls]

*/
#define SOC_AON_TOPDBG_P1SUB_W                                       5U
#define SOC_AON_TOPDBG_P1SUB_M                                       0x00001F00U
#define SOC_AON_TOPDBG_P1SUB_S                                       8U
/*

        Field:           P2SEL
        From..to bits:   16...20
        DefaultValue:    NA
        Access type:     read-write
        Description:     Port Set 2 - IP Selector.

                         Selects the IP.

                         INTERNAL NOTE-
                         2.2.4 SOC (TOP)
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Osprey+MDB+PG1.0+-+OCLA+integration+Spec]

*/
#define SOC_AON_TOPDBG_P2SEL_W                                       5U
#define SOC_AON_TOPDBG_P2SEL_M                                       0x001F0000U
#define SOC_AON_TOPDBG_P2SEL_S                                       16U
/*

        Field:           P1SEL
        From..to bits:   24...28
        DefaultValue:    NA
        Access type:     read-write
        Description:     Port Set 1 - IP Selector.

                         Selects the IP.

                         INTERNAL NOTE-
                         2.2.4 SOC (TOP)
                         [Confluence][https://confluence.itg.ti.com/display/WNG/Osprey+MDB+PG1.0+-+OCLA+integration+Spec]

*/
#define SOC_AON_TOPDBG_P1SEL_W                                       5U
#define SOC_AON_TOPDBG_P1SEL_M                                       0x1F000000U
#define SOC_AON_TOPDBG_P1SEL_S                                       24U
/*

        Field:           TPSEL
        From..to bits:   31...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     TP1/TP2 Selector.

                         This field is used for Peripheral TP that have two 32bits TP (mode #3) e.g.  SDIO_PHY, SDIO_FN1
                         In this case TP include 64 bits but we can expose only 32bits
                         So we need this MMR field  to select either TP1 or TP2
                         In this case this 16LSB(15:0) bit are connected to TP1 and 16MSB(31:16) to TP2
                         0 - Select IP TP1
                         1 - Select IP TP2

                         Example:
                         TP1 = mem_ocla_tp1_tp2_sel  ?  IP_TP2[15:  0]  :  IP_TP1[15:  0] ;
                         TP2 = mem_ocla_tp1_tp2_sel  ?  IP_TP2[31:16]  :  IP_TP1[31:16] ;

*/
#define SOC_AON_TOPDBG_TPSEL                                         0x80000000U
#define SOC_AON_TOPDBG_TPSEL_M                                       0x80000000U
#define SOC_AON_TOPDBG_TPSEL_S                                       31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M3CLR
    Offset name:         SOC_AON_O_DB0M3CLR
    Relative address:    0x2370
    Description:         Doorbell 0 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB0M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB0M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB0M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M3SET
    Offset name:         SOC_AON_O_DB0M3SET
    Relative address:    0x2374
    Description:         Doorbell 0 M3 Set Register
    Default Value:       0x00000000

        Field:           IRQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB0M3SET_IRQ                                         0x00000001U
#define SOC_AON_DB0M3SET_IRQ_M                                       0x00000001U
#define SOC_AON_DB0M3SET_IRQ_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB0M3LOCK
    Offset name:         SOC_AON_O_DB0M3LOCK
    Relative address:    0x2378
    Description:         Doorbell 0 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB0M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB0M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB0M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M3CLR
    Offset name:         SOC_AON_O_DB1M3CLR
    Relative address:    0x237C
    Description:         Doorbell 1 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB1M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB1M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB1M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M3SET
    Offset name:         SOC_AON_O_DB1M3SET
    Relative address:    0x2380
    Description:         Doorbell 1 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB1M3SET_SET                                         0x00000001U
#define SOC_AON_DB1M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB1M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB1M3LOCK
    Offset name:         SOC_AON_O_DB1M3LOCK
    Relative address:    0x2384
    Description:         Doorbell 1 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB1M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB1M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB1M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M3CLR
    Offset name:         SOC_AON_O_DB2M3CLR
    Relative address:    0x2388
    Description:         Doorbell 2 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB2M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB2M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB2M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M3SET
    Offset name:         SOC_AON_O_DB2M3SET
    Relative address:    0x238C
    Description:         Doorbell 2 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB2M3SET_SET                                         0x00000001U
#define SOC_AON_DB2M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB2M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB2M3LOCK
    Offset name:         SOC_AON_O_DB2M3LOCK
    Relative address:    0x2390
    Description:         Doorbell 2 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB2M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB2M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB2M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M3CLR
    Offset name:         SOC_AON_O_DB3M3CLR
    Relative address:    0x2394
    Description:         Doorbell 3 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB3M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB3M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB3M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M3SET
    Offset name:         SOC_AON_O_DB3M3SET
    Relative address:    0x2398
    Description:         Doorbell 3 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB3M3SET_SET                                         0x00000001U
#define SOC_AON_DB3M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB3M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB3M3LOCK
    Offset name:         SOC_AON_O_DB3M3LOCK
    Relative address:    0x239C
    Description:         Doorbell 3 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB3M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB3M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB3M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M3CLR
    Offset name:         SOC_AON_O_DB4M3CLR
    Relative address:    0x23A0
    Description:         Doorbell 4 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB4M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB4M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB4M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M3SET
    Offset name:         SOC_AON_O_DB4M3SET
    Relative address:    0x23A4
    Description:         Doorbell 4 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB4M3SET_SET                                         0x00000001U
#define SOC_AON_DB4M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB4M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB4M3LOCK
    Offset name:         SOC_AON_O_DB4M3LOCK
    Relative address:    0x23A8
    Description:         Doorbell 4 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB4M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB4M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB4M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M3CLR
    Offset name:         SOC_AON_O_DB5M3CLR
    Relative address:    0x23AC
    Description:         Doorbell 5 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB5M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB5M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB5M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M3SET
    Offset name:         SOC_AON_O_DB5M3SET
    Relative address:    0x23B0
    Description:         Doorbell 5 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB5M3SET_SET                                         0x00000001U
#define SOC_AON_DB5M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB5M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB5M3LOCK
    Offset name:         SOC_AON_O_DB5M3LOCK
    Relative address:    0x23B4
    Description:         Doorbell 5 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB5M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB5M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB5M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M3CLR
    Offset name:         SOC_AON_O_DB6M3CLR
    Relative address:    0x23B8
    Description:         Doorbell 6 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB6M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB6M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB6M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M3SET
    Offset name:         SOC_AON_O_DB6M3SET
    Relative address:    0x23BC
    Description:         Doorbell 6 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB6M3SET_SET                                         0x00000001U
#define SOC_AON_DB6M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB6M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB6M3LOCK
    Offset name:         SOC_AON_O_DB6M3LOCK
    Relative address:    0x23C0
    Description:         Doorbell 6 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB6M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB6M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB6M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M3CLR
    Offset name:         SOC_AON_O_DB7M3CLR
    Relative address:    0x23C4
    Description:         Doorbell 7 M3 Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to clear the IRQ after handled the massage from M33.
                         type : Write-Clear

*/
#define SOC_AON_DB7M3CLR_CLR                                         0x00000001U
#define SOC_AON_DB7M3CLR_CLR_M                                       0x00000001U
#define SOC_AON_DB7M3CLR_CLR_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M3SET
    Offset name:         SOC_AON_O_DB7M3SET
    Relative address:    0x23C8
    Description:         Doorbell 7 M3 Set Register
    Default Value:       0x00000000

        Field:           SET
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     write-only
        Description:     M3 to generate IRQ towards M33 after writing the message.
                         type: Write-Clear

*/
#define SOC_AON_DB7M3SET_SET                                         0x00000001U
#define SOC_AON_DB7M3SET_SET_M                                       0x00000001U
#define SOC_AON_DB7M3SET_SET_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DB7M3LOCK
    Offset name:         SOC_AON_O_DB7M3LOCK
    Relative address:    0x23CC
    Description:         Doorbell 7 M3 Lock Bit
    Default Value:       0x00000000

        Field:           LOCKBIT
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Lock Bit.
                         S/w attempt to lock upon read.
                         if lock obtained, value set to 1 by h/w.
                         M33  always looses to M3
                         Reading value:
                                 00: not taken
                                 01: taken by M3 (should wr IRQ afterwards)
                                 10: taken by M33
                                 11: invalid.

                         generating the IRQ towards M33 clears the lock.
                         Writing '00' also release the lock.

                         2'b10 means lock obtained by receiver side

                         Type: Write-Read-Clear.

*/
#define SOC_AON_DB7M3LOCK_LOCKBIT_W                                  2U
#define SOC_AON_DB7M3LOCK_LOCKBIT_M                                  0x00000003U
#define SOC_AON_DB7M3LOCK_LOCKBIT_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOEVT0
    Offset name:         SOC_AON_O_M3GPIOEVT0
    Relative address:    0x23D0
    Description:         M3 GPIO Event Status. 32 LSBs
    Default Value:       0x00000000

        Field:           STA31TO0
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     32 LSBs

*/
#define SOC_AON_M3GPIOEVT0_STA31TO0_W                                32U
#define SOC_AON_M3GPIOEVT0_STA31TO0_M                                0xFFFFFFFFU
#define SOC_AON_M3GPIOEVT0_STA31TO0_S                                0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOEVT1
    Offset name:         SOC_AON_O_M3GPIOEVT1
    Relative address:    0x23D4
    Description:         M3 GPIO Event Status. 13 MSBs
    Default Value:       0x00000000

        Field:           STA44TO32
        From..to bits:   0...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     13 MSBs (44-32)

*/
#define SOC_AON_M3GPIOEVT1_STA44TO32_W                               13U
#define SOC_AON_M3GPIOEVT1_STA44TO32_M                               0x00001FFFU
#define SOC_AON_M3GPIOEVT1_STA44TO32_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FUSELOCK
    Offset name:         SOC_AON_O_FUSELOCK
    Relative address:    0x23E8
    Description:         Fuse Lock.

                        1 lock. Write once. Issued to Fusefram Reg file
                        and used to lock fusefarm OCP Disable indication (MMR),
                        Locked immediately , cleared by core disable (or at soc aon reset or por reset)
    Default Value:       0x00000000

        Field:           OCPDIS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Locking the FUSE FARM OCP Reg File

*/
#define SOC_AON_FUSELOCK_OCPDIS                                      0x00000001U
#define SOC_AON_FUSELOCK_OCPDIS_M                                    0x00000001U
#define SOC_AON_FUSELOCK_OCPDIS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ROMBOOT
    Offset name:         SOC_AON_O_ROMBOOT
    Relative address:    0x23EC
    Description:         ROM Boot Done.

                        1 lock. Write once.
                        Asserted by FW at the end of ROM boot.
                        Used to implement the ROM Hide,
                        Locked immediately ,
                        cleared by core disable (or at soc aon reset or por reset)
    Default Value:       0x00000000

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     Hiding the ROM at ROM Boot

*/
#define SOC_AON_ROMBOOT_DONE                                         0x00000001U
#define SOC_AON_ROMBOOT_DONE_M                                       0x00000001U
#define SOC_AON_ROMBOOT_DONE_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCBOOT
    Offset name:         SOC_AON_O_SOCBOOT
    Relative address:    0x23FC
    Description:         SOC Boot Done.

                        1 lock. Write once.
                        Asserted by FW at the end of TI secure boot,
                        Used to lock the access to SOC security configurations ,
                        Locked immediately,
                        cleared only at soc aon reset or por reset
    Default Value:       0x00000000

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     locking the access to SOC security configurations

*/
#define SOC_AON_SOCBOOT_DONE                                         0x00000001U
#define SOC_AON_SOCBOOT_DONE_M                                       0x00000001U
#define SOC_AON_SOCBOOT_DONE_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ELEVATED
    Offset name:         SOC_AON_O_ELEVATED
    Relative address:    0x2400
    Description:         Elevated Mode Done.

                        1 lock. Write once.
                        Asserted by FW at the end of elevated mode
                        and indicates the end of elevated mode,
                        Locked immediately ,
                        cleared by core disable (or at soc aon reset or por reset)
    Default Value:       0x00000000

        Field:           DONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     nd of elevated mode (M3 Boot ROM + M3 Core Boot)

*/
#define SOC_AON_ELEVATED_DONE                                        0x00000001U
#define SOC_AON_ELEVATED_DONE_M                                      0x00000001U
#define SOC_AON_ELEVATED_DONE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3TCM
    Offset name:         SOC_AON_O_M3TCM
    Relative address:    0x2408
    Description:         M3 TCM Access.

                        TCM access between M3 to M33
    Default Value:       NA

        Field:           ACCESSDIS
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 TCM Access Disable.

                         Control the mux which select TCM access between M3 to M33

                         0. M3
                         1. M33

*/
#define SOC_AON_M3TCM_ACCESSDIS                                      0x00000001U
#define SOC_AON_M3TCM_ACCESSDIS_M                                    0x00000001U
#define SOC_AON_M3TCM_ACCESSDIS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HSMCFG
    Offset name:         SOC_AON_O_HSMCFG
    Relative address:    0x240C
    Description:         HSM Configurations.
                        Fips Support, HSM_Configs, HSM_assets_hide, hsm_controller_host_mode (or firewall_mode).
    Default Value:       0x00000006

        Field:           FIPS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Indication if  hsm FIPS support:
                         1- HSM run in fips compliant mode
                         0- HSM doesn't run in fips compliant mode

*/
#define SOC_AON_HSMCFG_FIPS                                          0x00000001U
#define SOC_AON_HSMCFG_FIPS_M                                        0x00000001U
#define SOC_AON_HSMCFG_FIPS_S                                        0U
/*

        Field:           SELFDIS
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     Disable self test & crc check on hsm reset exit, possible only is fips not supported:
                         post_disable: 0-enable self test on reset exit, 1-disable self test on reset exit (default=1)

*/
#define SOC_AON_HSMCFG_SELFDIS                                       0x00000002U
#define SOC_AON_HSMCFG_SELFDIS_M                                     0x00000002U
#define SOC_AON_HSMCFG_SELFDIS_S                                     1U
/*

        Field:           WMSELFDIS
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     HSM Warmboot Post Disable.
                         Disable self test & crc check on hsm reset exit, possible only is fips not supported:
                         warmboot_post_disable: 0-enable self test on sleep exit, 1-disable self test on sleep exit  (default=1)

*/
#define SOC_AON_HSMCFG_WMSELFDIS                                     0x00000004U
#define SOC_AON_HSMCFG_WMSELFDIS_M                                   0x00000004U
#define SOC_AON_HSMCFG_WMSELFDIS_S                                   2U
/*

        Field:           DMAGATEWAY
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     DMA Gateway Mode.

                         Define the ids to be used on hsm dma access to OCP:

                         0-M33 using HSM, use M33S and M33NS Mater IDs

                         1-M33+M3 are using the HSM, use M33S and M3 Mater IDs

*/
#define SOC_AON_HSMCFG_DMAGATEWAY                                    0x00000008U
#define SOC_AON_HSMCFG_DMAGATEWAY_M                                  0x00000008U
#define SOC_AON_HSMCFG_DMAGATEWAY_S                                  3U
/*

        Field:           FIREWALL
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HSM Firewall Mode.

                         Select the controller id to hsm cpu_id transaction mode:

                         0-M3_MST_ID is translated to hsm cpu id 0 (controller host), this mode is used during boot (default=0)
                         1-M33_MST_ID (secure and non secure) are translated to hsm cpu id 0 (controller host), operational mode

*/
#define SOC_AON_HSMCFG_FIREWALL                                      0x00000010U
#define SOC_AON_HSMCFG_FIREWALL_M                                    0x00000010U
#define SOC_AON_HSMCFG_FIREWALL_S                                    4U
/*

        Field:           HIDEASSETS
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HSM Assets Hide.

                         Change the control on HSM assets from OCP to HSM. Controlling this value is allowed during boot (before soc_boot_done) is enabled

*/
#define SOC_AON_HSMCFG_HIDEASSETS                                    0x00000020U
#define SOC_AON_HSMCFG_HIDEASSETS_M                                  0x00000020U
#define SOC_AON_HSMCFG_HIDEASSETS_S                                  5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5CFG
    Offset name:         SOC_AON_O_ESM5CFG
    Relative address:    0x2410
    Description:         ESM4 Configuration- Customer HSM Debug Enable Sequence Monitor.

                        Enable timeout mechanism and timeout counter value.
    Default Value:       0x00000001

        Field:           ENTIMEOUT
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This field enables timeout mechanism for ESM.

*/
#define SOC_AON_ESM5CFG_ENTIMEOUT                                    0x00000001U
#define SOC_AON_ESM5CFG_ENTIMEOUT_M                                  0x00000001U
#define SOC_AON_ESM5CFG_ENTIMEOUT_S                                  0U
/*

        Field:           TIMEOUTCNT
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field sets the timeout value.
                         time resolution equals to 16us. while:
                         value 0 representing 16us
                         value 1 - 2*16us
                         value 2 - 3*16us and so on.
                         value 15 is not supported.

*/
#define SOC_AON_ESM5CFG_TIMEOUTCNT_W                                 4U
#define SOC_AON_ESM5CFG_TIMEOUTCNT_M                                 0x00000F00U
#define SOC_AON_ESM5CFG_TIMEOUTCNT_S                                 8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5EN1
    Offset name:         SOC_AON_O_ESM5EN1
    Relative address:    0x2414
    Description:         ESM5 Enable Number 1.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 1st enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM5EN1_EN1                                          0x00000001U
#define SOC_AON_ESM5EN1_EN1_M                                        0x00000001U
#define SOC_AON_ESM5EN1_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5EN2
    Offset name:         SOC_AON_O_ESM5EN2
    Relative address:    0x2418
    Description:         ESM5 Enable Number 2.
    Default Value:       NA

        Field:           EN2
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 2nd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM5EN2_EN2                                          0x00000001U
#define SOC_AON_ESM5EN2_EN2_M                                        0x00000001U
#define SOC_AON_ESM5EN2_EN2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5EN3
    Offset name:         SOC_AON_O_ESM5EN3
    Relative address:    0x241C
    Description:         ESM5 Enable Number 3.
    Default Value:       NA

        Field:           EN3
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 3rd enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM5EN3_EN3                                          0x00000001U
#define SOC_AON_ESM5EN3_EN3_M                                        0x00000001U
#define SOC_AON_ESM5EN3_EN3_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5EN4
    Offset name:         SOC_AON_O_ESM5EN4
    Relative address:    0x2420
    Description:         ESM5 Enable Number 4.
    Default Value:       NA

        Field:           EN1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 4th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM5EN4_EN1                                          0x00000001U
#define SOC_AON_ESM5EN4_EN1_M                                        0x00000001U
#define SOC_AON_ESM5EN4_EN1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5EN5
    Offset name:         SOC_AON_O_ESM5EN5
    Relative address:    0x2424
    Description:         ESM5 Enable Number 5.
    Default Value:       NA

        Field:           EN5
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     This field is the 5th enable for the ESM.
                         Type: Write-Clear

*/
#define SOC_AON_ESM5EN5_EN5                                          0x00000001U
#define SOC_AON_ESM5EN5_EN5_M                                        0x00000001U
#define SOC_AON_ESM5EN5_EN5_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1VAL1ST
    Offset name:         SOC_AON_O_ESM1VAL1ST
    Relative address:    0x2428
    Description:         ESM1 1st Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow ESM protection against fault injection
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 1st magic value

*/
#define SOC_AON_ESM1VAL1ST_MGCVAL_W                                  8U
#define SOC_AON_ESM1VAL1ST_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM1VAL1ST_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2VAL1ST
    Offset name:         SOC_AON_O_ESM2VAL1ST
    Relative address:    0x242C
    Description:         ESM2 1st Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow ESM protection against fault injection
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 1st magic value

*/
#define SOC_AON_ESM2VAL1ST_MGCVAL_W                                  8U
#define SOC_AON_ESM2VAL1ST_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM2VAL1ST_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3VAL1ST
    Offset name:         SOC_AON_O_ESM3VAL1ST
    Relative address:    0x2430
    Description:         ESM3 1st Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow ESM protection against fault injection
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 1st magic value

*/
#define SOC_AON_ESM3VAL1ST_MGCVAL_W                                  8U
#define SOC_AON_ESM3VAL1ST_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM3VAL1ST_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4VAL1ST
    Offset name:         SOC_AON_O_ESM4VAL1ST
    Relative address:    0x2434
    Description:         ESM4 1st Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow ESM protection against fault injection
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 1st magic value

*/
#define SOC_AON_ESM4VAL1ST_MGCVAL_W                                  8U
#define SOC_AON_ESM4VAL1ST_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM4VAL1ST_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5VAL1ST
    Offset name:         SOC_AON_O_ESM5VAL1ST
    Relative address:    0x2438
    Description:         ESM5 1st Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow ESM protection against fault injection
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 1st magic value

*/
#define SOC_AON_ESM5VAL1ST_MGCVAL_W                                  8U
#define SOC_AON_ESM5VAL1ST_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM5VAL1ST_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3IMASK
    Offset name:         SOC_AON_O_DBM3IMASK
    Relative address:    0x2450
    Description:         M3 Doorbell IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3IMASK_IMASK_W                                    8U
#define SOC_AON_DBM3IMASK_IMASK_M                                    0x000000FFU
#define SOC_AON_DBM3IMASK_IMASK_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3ISET
    Offset name:         SOC_AON_O_DBM3ISET
    Relative address:    0x2454
    Description:         M3 Doorbell ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3ISET_ISET_W                                      8U
#define SOC_AON_DBM3ISET_ISET_M                                      0x000000FFU
#define SOC_AON_DBM3ISET_ISET_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3ICLR
    Offset name:         SOC_AON_O_DBM3ICLR
    Relative address:    0x2458
    Description:         M3 Doorbell ICLR.

                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3ICLR_ICLR_W                                      8U
#define SOC_AON_DBM3ICLR_ICLR_M                                      0x000000FFU
#define SOC_AON_DBM3ICLR_ICLR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3IMSET
    Offset name:         SOC_AON_O_DBM3IMSET
    Relative address:    0x245C
    Description:         M3 Doorbell IMSET.

                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3IMSET_IMSET_W                                    8U
#define SOC_AON_DBM3IMSET_IMSET_M                                    0x000000FFU
#define SOC_AON_DBM3IMSET_IMSET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3IMCLR
    Offset name:         SOC_AON_O_DBM3IMCLR
    Relative address:    0x2460
    Description:         M3 Doorbell IMCLR.

                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     write-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3IMCLR_IMCLR_W                                    8U
#define SOC_AON_DBM3IMCLR_IMCLR_M                                    0x000000FFU
#define SOC_AON_DBM3IMCLR_IMCLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3RIS
    Offset name:         SOC_AON_O_DBM3RIS
    Relative address:    0x2464
    Description:         M3 Doorbell RIS.

                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3RIS_RIS_W                                        8U
#define SOC_AON_DBM3RIS_RIS_M                                        0x000000FFU
#define SOC_AON_DBM3RIS_RIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBM3MIS
    Offset name:         SOC_AON_O_DBM3MIS
    Relative address:    0x2468
    Description:         M3 Doorbell MIS.

                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     bit7 - doorbell 7 M3 IRQ
                         bit6 - doorbell6 M3 IRQ
                         bit5 - doorbell 5 M3 IRQ
                         bit4 - doorbell 4 M3 IRQ
                         bit3 - doorbell 3 M3 IRQ
                         bit2 - doorbell 2 M3 IRQ
                         bit1 - doorbell 1 M3 IRQ
                         bit0 - doorbell 0 M3 IRQ

*/
#define SOC_AON_DBM3MIS_MIS_W                                        8U
#define SOC_AON_DBM3MIS_MIS_M                                        0x000000FFU
#define SOC_AON_DBM3MIS_MIS_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HOSTCRTX
    Offset name:         SOC_AON_O_HOSTCRTX
    Relative address:    0x2680
    Description:         M33 cortex system reset request
    Default Value:       0x00000000

        Field:           SYSRSTREQ
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M33 cortex system reset request. Level register.
                         1 - request for reset
                         0- lower reset request
                         User should set and clear this register (two writes)

*/
#define SOC_AON_HOSTCRTX_SYSRSTREQ                                   0x00000001U
#define SOC_AON_HOSTCRTX_SYSRSTREQ_M                                 0x00000001U
#define SOC_AON_HOSTCRTX_SYSRSTREQ_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCFGSOC
    Offset name:         SOC_AON_O_FWCFGSOC
    Relative address:    0x2684
    Description:         SOC Firewall Bypass
    Default Value:       0x00000001

        Field:           BYPASS
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     SOC Firewall Bypass

*/
#define SOC_AON_FWCFGSOC_BYPASS                                      0x00000001U
#define SOC_AON_FWCFGSOC_BYPASS_M                                    0x00000001U
#define SOC_AON_FWCFGSOC_BYPASS_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCOEX
    Offset name:         SOC_AON_O_FWCOEX
    Relative address:    0x2688
    Description:         COEX firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOEX_M33NS                                         0x00000001U
#define SOC_AON_FWCOEX_M33NS_M                                       0x00000001U
#define SOC_AON_FWCOEX_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOEX_M33S                                          0x00000002U
#define SOC_AON_FWCOEX_M33S_M                                        0x00000002U
#define SOC_AON_FWCOEX_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOEX_CORENS                                        0x00000004U
#define SOC_AON_FWCOEX_CORENS_M                                      0x00000004U
#define SOC_AON_FWCOEX_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWPRCM
    Offset name:         SOC_AON_O_FWPRCM
    Relative address:    0x268C
    Description:         PRCM CORE + M3 Scratchpad firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCM_M33NS                                         0x00000001U
#define SOC_AON_FWPRCM_M33NS_M                                       0x00000001U
#define SOC_AON_FWPRCM_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCM_M33S                                          0x00000002U
#define SOC_AON_FWPRCM_M33S_M                                        0x00000002U
#define SOC_AON_FWPRCM_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWPRCM_CORENS                                        0x00000004U
#define SOC_AON_FWPRCM_CORENS_M                                      0x00000004U
#define SOC_AON_FWPRCM_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWFUSE
    Offset name:         SOC_AON_O_FWFUSE
    Relative address:    0x2690
    Description:         FUSE FARM firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured (valid only in privilege mode)
                        1 - M33 Secured (valid only in privilege mode)
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWFUSE_M33NS                                         0x00000001U
#define SOC_AON_FWFUSE_M33NS_M                                       0x00000001U
#define SOC_AON_FWFUSE_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWFUSE_M33S                                          0x00000002U
#define SOC_AON_FWFUSE_M33S_M                                        0x00000002U
#define SOC_AON_FWFUSE_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWFUSE_CORENS                                        0x00000004U
#define SOC_AON_FWFUSE_CORENS_M                                      0x00000004U
#define SOC_AON_FWFUSE_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWGPADC
    Offset name:         SOC_AON_O_FWGPADC
    Relative address:    0x2694
    Description:         GPADC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWGPADC_M33NS                                        0x00000001U
#define SOC_AON_FWGPADC_M33NS_M                                      0x00000001U
#define SOC_AON_FWGPADC_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWGPADC_M33S                                         0x00000002U
#define SOC_AON_FWGPADC_M33S_M                                       0x00000002U
#define SOC_AON_FWGPADC_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWGPADC_CORENS                                       0x00000004U
#define SOC_AON_FWGPADC_CORENS_M                                     0x00000004U
#define SOC_AON_FWGPADC_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWDBGSS
    Offset name:         SOC_AON_O_FWDBGSS
    Relative address:    0x2698
    Description:         DEBUGSS firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDBGSS_M33NS                                        0x00000001U
#define SOC_AON_FWDBGSS_M33NS_M                                      0x00000001U
#define SOC_AON_FWDBGSS_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDBGSS_M33S                                         0x00000002U
#define SOC_AON_FWDBGSS_M33S_M                                       0x00000002U
#define SOC_AON_FWDBGSS_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWDBGSS_CORENS                                       0x00000004U
#define SOC_AON_FWDBGSS_CORENS_M                                     0x00000004U
#define SOC_AON_FWDBGSS_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAONM3
    Offset name:         SOC_AON_O_FWAONM3
    Relative address:    0x269C
    Description:         SOC_AON_M3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM3_M33NS                                        0x00000001U
#define SOC_AON_FWAONM3_M33NS_M                                      0x00000001U
#define SOC_AON_FWAONM3_M33NS_S                                      0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM3_M33S                                         0x00000002U
#define SOC_AON_FWAONM3_M33S_M                                       0x00000002U
#define SOC_AON_FWAONM3_M33S_S                                       1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAONM3_CORENS                                       0x00000004U
#define SOC_AON_FWAONM3_CORENS_M                                     0x00000004U
#define SOC_AON_FWAONM3_CORENS_S                                     2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOCLA
    Offset name:         SOC_AON_O_FWOCLA
    Relative address:    0x26A0
    Description:         OCLA firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOCLA_M33NS                                         0x00000001U
#define SOC_AON_FWOCLA_M33NS_M                                       0x00000001U
#define SOC_AON_FWOCLA_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOCLA_M33S                                          0x00000002U
#define SOC_AON_FWOCLA_M33S_M                                        0x00000002U
#define SOC_AON_FWOCLA_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOCLA_CORENS                                        0x00000004U
#define SOC_AON_FWOCLA_CORENS_M                                      0x00000004U
#define SOC_AON_FWOCLA_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCORE
    Offset name:         SOC_AON_O_FWCORE
    Relative address:    0x26A4
    Description:         WSOC_IC firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCORE_M33NS                                         0x00000001U
#define SOC_AON_FWCORE_M33NS_M                                       0x00000001U
#define SOC_AON_FWCORE_M33NS_S                                       0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCORE_M33S                                          0x00000002U
#define SOC_AON_FWCORE_M33S_M                                        0x00000002U
#define SOC_AON_FWCORE_M33S_S                                        1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCORE_CORENS                                        0x00000004U
#define SOC_AON_FWCORE_CORENS_M                                      0x00000004U
#define SOC_AON_FWCORE_CORENS_S                                      2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWAAONM3
    Offset name:         SOC_AON_O_FWAAONM3
    Relative address:    0x26A8
    Description:         SOC_AAON_M3 firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM3_M33NS                                       0x00000001U
#define SOC_AON_FWAAONM3_M33NS_M                                     0x00000001U
#define SOC_AON_FWAAONM3_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM3_M33S                                        0x00000002U
#define SOC_AON_FWAAONM3_M33S_M                                      0x00000002U
#define SOC_AON_FWAAONM3_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWAAONM3_CORENS                                      0x00000004U
#define SOC_AON_FWAAONM3_CORENS_M                                    0x00000004U
#define SOC_AON_FWAAONM3_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWXIPCFG
    Offset name:         SOC_AON_O_FWXIPCFG
    Relative address:    0x26AC
    Description:         XIP_CFG firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPCFG_M33NS                                       0x00000001U
#define SOC_AON_FWXIPCFG_M33NS_M                                     0x00000001U
#define SOC_AON_FWXIPCFG_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPCFG_M33S                                        0x00000002U
#define SOC_AON_FWXIPCFG_M33S_M                                      0x00000002U
#define SOC_AON_FWXIPCFG_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWXIPCFG_CORENS                                      0x00000004U
#define SOC_AON_FWXIPCFG_CORENS_M                                    0x00000004U
#define SOC_AON_FWXIPCFG_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFLCK
    Offset name:         SOC_AON_O_FWOTFLCK
    Relative address:    0x26B0
    Description:         OTFE_BOOT_LOCK firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFLCK_M33NS                                       0x00000001U
#define SOC_AON_FWOTFLCK_M33NS_M                                     0x00000001U
#define SOC_AON_FWOTFLCK_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFLCK_M33S                                        0x00000002U
#define SOC_AON_FWOTFLCK_M33S_M                                      0x00000002U
#define SOC_AON_FWOTFLCK_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFLCK_CORENS                                      0x00000004U
#define SOC_AON_FWOTFLCK_CORENS_M                                    0x00000004U
#define SOC_AON_FWOTFLCK_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWOTFNLCK
    Offset name:         SOC_AON_O_FWOTFNLCK
    Relative address:    0x26B4
    Description:         OTFDE_NON_LOCK firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFNLCK_M33NS                                      0x00000001U
#define SOC_AON_FWOTFNLCK_M33NS_M                                    0x00000001U
#define SOC_AON_FWOTFNLCK_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFNLCK_M33S                                       0x00000002U
#define SOC_AON_FWOTFNLCK_M33S_M                                     0x00000002U
#define SOC_AON_FWOTFNLCK_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWOTFNLCK_CORENS                                     0x00000004U
#define SOC_AON_FWOTFNLCK_CORENS_M                                   0x00000004U
#define SOC_AON_FWOTFNLCK_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWCOREAON
    Offset name:         SOC_AON_O_FWCOREAON
    Relative address:    0x2808
    Description:         CORE_AON firewall access permission
                        for 3 controller id :
                        0 - M33 Non Secured
                        1 - M33 Secured
                        2 - Core (Non Secure)
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOREAON_M33NS                                      0x00000001U
#define SOC_AON_FWCOREAON_M33NS_M                                    0x00000001U
#define SOC_AON_FWCOREAON_M33NS_S                                    0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOREAON_M33S                                       0x00000002U
#define SOC_AON_FWCOREAON_M33S_M                                     0x00000002U
#define SOC_AON_FWCOREAON_M33S_S                                     1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWCOREAON_CORENS                                     0x00000004U
#define SOC_AON_FWCOREAON_CORENS_M                                   0x00000004U
#define SOC_AON_FWCOREAON_CORENS_S                                   2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FWSPARE1
    Offset name:         SOC_AON_O_FWSPARE1
    Relative address:    0x287C
    Description:         Spare firewall access register.
                        locked by SOC BOOT DONE (secgk)
                        3 access bits - {M33NS , M33S , M3} .
    Default Value:       0x00000000

        Field:           M33NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 None Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE1_M33NS                                       0x00000001U
#define SOC_AON_FWSPARE1_M33NS_M                                     0x00000001U
#define SOC_AON_FWSPARE1_M33NS_S                                     0U
/*

        Field:           M33S
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller M33 Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE1_M33S                                        0x00000002U
#define SOC_AON_FWSPARE1_M33S_M                                      0x00000002U
#define SOC_AON_FWSPARE1_M33S_S                                      1U
/*

        Field:           CORENS
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Controller Core Non Secured:
                         '0' - access not allowed
                         '1' - access allowed

*/
#define SOC_AON_FWSPARE1_CORENS                                      0x00000004U
#define SOC_AON_FWSPARE1_CORENS_M                                    0x00000004U
#define SOC_AON_FWSPARE1_CORENS_S                                    2U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCSTA
    Offset name:         SOC_AON_O_SOCSTA
    Relative address:    0x2898
    Description:         Boot Status.

                        Report boot status which reflected on Config AP on DebugSS and can be read by JTAG (tools), these configuration will be used by both privilege and elevated boot code
                        The Boot status reveal is controlled by FW - status will be updated using authenticated request.
    Default Value:       0x00000000

        Field:           BOOTSTA
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Boot Status.

*/
#define SOC_AON_SOCSTA_BOOTSTA_W                                     32U
#define SOC_AON_SOCSTA_BOOTSTA_M                                     0xFFFFFFFFU
#define SOC_AON_SOCSTA_BOOTSTA_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LCCFG
    Offset name:         SOC_AON_O_LCCFG
    Relative address:    0x289C
    Description:         LifeCycle Config.

                        Report device parameters to config - AP.
    Default Value:       0x00000000

        Field:           DEVPARAMS
        From..to bits:   8...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Bits 7:0   - Fixed lifecycle taken from HW (SW_LIFECYCLE, HW_LIFECYCLE)
                         Bits 31:8 - device parameters (fuse/SW)

*/
#define SOC_AON_LCCFG_DEVPARAMS_W                                    24U
#define SOC_AON_LCCFG_DEVPARAMS_M                                    0xFFFFFF00U
#define SOC_AON_LCCFG_DEVPARAMS_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1STA
    Offset name:         SOC_AON_O_ESM1STA
    Relative address:    0x28A0
    Description:         status register , for each of the ESM (enable sequence monitor) what is the current state of esm.
    Default Value:       NA

        Field:           STATE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     5 states:
                         0000 - READY
                         0001 - ENABLED (not guarenteed that magic values match)
                         0010 - PENDING TO NEXT WRITE
                         0100 - GRACFULLY LOCKED
                         1000 - FAULT


*/
#define SOC_AON_ESM1STA_STATE_W                                      4U
#define SOC_AON_ESM1STA_STATE_M                                      0x0000000FU
#define SOC_AON_ESM1STA_STATE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2STA
    Offset name:         SOC_AON_O_ESM2STA
    Relative address:    0x28A4
    Description:         status register , for each of the ESM (enable sequence monitor) what is the current state of esm.
    Default Value:       NA

        Field:           STATE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     5 states:
                         0000 - READY
                         0001 - ENABLED (not guarenteed that magic values match)
                         0010 - PENDING TO NEXT WRITE
                         0100 - GRACFULLY LOCKED
                         1000 - FAULT


*/
#define SOC_AON_ESM2STA_STATE_W                                      4U
#define SOC_AON_ESM2STA_STATE_M                                      0x0000000FU
#define SOC_AON_ESM2STA_STATE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM1STA1ST
    Offset name:         SOC_AON_O_ESM1STA1ST
    Relative address:    0x28A8
    Description:         ESM1 1st magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val match

*/
#define SOC_AON_ESM1STA1ST_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM1STA1ST_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM1STA1ST_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM1STA1ST_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM1STA1ST_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM1STA1ST_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM2STA1ST
    Offset name:         SOC_AON_O_ESM2STA1ST
    Relative address:    0x28AC
    Description:         ESM2 1st magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val match

*/
#define SOC_AON_ESM2STA1ST_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM2STA1ST_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM2STA1ST_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM2STA1ST_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM2STA1ST_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM2STA1ST_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3STA1ST
    Offset name:         SOC_AON_O_ESM3STA1ST
    Relative address:    0x28B0
    Description:         ESM3 1st magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val match

*/
#define SOC_AON_ESM3STA1ST_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM3STA1ST_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM3STA1ST_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM3STA1ST_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM3STA1ST_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM3STA1ST_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4STA1ST
    Offset name:         SOC_AON_O_ESM4STA1ST
    Relative address:    0x28B4
    Description:         ESM4 1st magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val match

*/
#define SOC_AON_ESM4STA1ST_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM4STA1ST_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM4STA1ST_MGCVDONE_S                                0U
/*

        Field:           MGCVFAULT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM4STA1ST_MGCVFAULT                                 0x00000002U
#define SOC_AON_ESM4STA1ST_MGCVFAULT_M                               0x00000002U
#define SOC_AON_ESM4STA1ST_MGCVFAULT_S                               1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5STA1ST
    Offset name:         SOC_AON_O_ESM5STA1ST
    Relative address:    0x28B8
    Description:         ESM5 1st magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val match

*/
#define SOC_AON_ESM5STA1ST_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM5STA1ST_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM5STA1ST_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 1st magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM5STA1ST_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM5STA1ST_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM5STA1ST_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECGSERR
    Offset name:         SOC_AON_O_SECGSERR
    Relative address:    0x2908
    Description:         Enable Security Group SERROR.
                        Enable SERROR when trying to access locked register in SOC AON , HOSTXIP and WSOCCOMMONS regfiles
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable secgroup serror.

*/
#define SOC_AON_SECGSERR_EN                                          0x00000001U
#define SOC_AON_SECGSERR_EN_M                                        0x00000001U
#define SOC_AON_SECGSERR_EN_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DRAMCTL
    Offset name:         SOC_AON_O_DRAMCTL
    Relative address:    0x290C
    Description:         Erase Assets DRAM.
    Default Value:       0x00000100

        Field:           ERASEASST
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable the automatic erase of the assets area of DRAM (8K)  upon core reset exit. This action erase 8k in 25.6us

*/
#define SOC_AON_DRAMCTL_ERASEASST                                    0x00000001U
#define SOC_AON_DRAMCTL_ERASEASST_M                                  0x00000001U
#define SOC_AON_DRAMCTL_ERASEASST_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CONNSTPCTL
    Offset name:         SOC_AON_O_CONNSTPCTL
    Relative address:    0x2910
    Description:         Conn Stop Control By M33.

                        '1' - Switch control of con_stop from HW (default con start) to M33 (default con stop)
    Default Value:       0x00000100

        Field:           SWITCH
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     '1' - Switch control of con_stop from HW (default con start) to M33 (default con stop)

*/
#define SOC_AON_CONNSTPCTL_SWITCH                                    0x00000001U
#define SOC_AON_CONNSTPCTL_SWITCH_M                                  0x00000001U
#define SOC_AON_CONNSTPCTL_SWITCH_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESMSTATI
    Offset name:         SOC_AON_O_ESMSTATI
    Relative address:    0x2914
    Description:         TI ESMs STATUS (3,4,5)

                        status register , for each of the ESM (enable sequence monitor) what is the status  (Done, violated, or None).
                        Final ESM status for the entire ESM - ESM machine + magic value comparators
    Default Value:       NA

        Field:           ESM3DONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 3 Done.

*/
#define SOC_AON_ESMSTATI_ESM3DONE                                    0x00000001U
#define SOC_AON_ESMSTATI_ESM3DONE_M                                  0x00000001U
#define SOC_AON_ESMSTATI_ESM3DONE_S                                  0U
/*

        Field:           ESM3VIO
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 3 Violated.

*/
#define SOC_AON_ESMSTATI_ESM3VIO                                     0x00000002U
#define SOC_AON_ESMSTATI_ESM3VIO_M                                   0x00000002U
#define SOC_AON_ESMSTATI_ESM3VIO_S                                   1U
/*

        Field:           ESM4DONE
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 4 Done.

*/
#define SOC_AON_ESMSTATI_ESM4DONE                                    0x00000100U
#define SOC_AON_ESMSTATI_ESM4DONE_M                                  0x00000100U
#define SOC_AON_ESMSTATI_ESM4DONE_S                                  8U
/*

        Field:           ESM4VIO
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 4 Violated.

*/
#define SOC_AON_ESMSTATI_ESM4VIO                                     0x00000200U
#define SOC_AON_ESMSTATI_ESM4VIO_M                                   0x00000200U
#define SOC_AON_ESMSTATI_ESM4VIO_S                                   9U
/*

        Field:           ESM5DONE
        From..to bits:   16...16
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 5Done.

*/
#define SOC_AON_ESMSTATI_ESM5DONE                                    0x00010000U
#define SOC_AON_ESMSTATI_ESM5DONE_M                                  0x00010000U
#define SOC_AON_ESMSTATI_ESM5DONE_S                                  16U
/*

        Field:           ESM5VIO
        From..to bits:   17...17
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 5 Violated.

*/
#define SOC_AON_ESMSTATI_ESM5VIO                                     0x00020000U
#define SOC_AON_ESMSTATI_ESM5VIO_M                                   0x00020000U
#define SOC_AON_ESMSTATI_ESM5VIO_S                                   17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOMIS0
    Offset name:         SOC_AON_O_M3GPIOMIS0
    Relative address:    0x2918
    Description:         M3 GPIO Functional MIS. 32 LSBs
    Default Value:       NA

        Field:           31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     M3 GPIO Functional MIS. 32 LSBs

*/
#define SOC_AON_M3GPIOMIS0_31TO0_W                                   32U
#define SOC_AON_M3GPIOMIS0_31TO0_M                                   0xFFFFFFFFU
#define SOC_AON_M3GPIOMIS0_31TO0_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOMIS1
    Offset name:         SOC_AON_O_M3GPIOMIS1
    Relative address:    0x291C
    Description:         M3 GPIO Functional MIS. 13 MSBs (44-32)
    Default Value:       NA

        Field:           44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     M3 GPIO Functional MIS. 13 MSBs (44-32)

*/
#define SOC_AON_M3GPIOMIS1_44TO32_W                                  13U
#define SOC_AON_M3GPIOMIS1_44TO32_M                                  0x00001FFFU
#define SOC_AON_M3GPIOMIS1_44TO32_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOFNC0
    Offset name:         SOC_AON_O_M3GPIOFNC0
    Relative address:    0x2920
    Description:         M3 GPIO Functional Mask
    Default Value:       NA

        Field:           MASK31TO0
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 GPIO Functional Mask. 32 LSBs

                         0. Mask
                         1. Un-Mask

*/
#define SOC_AON_M3GPIOFNC0_MASK31TO0_W                               32U
#define SOC_AON_M3GPIOFNC0_MASK31TO0_M                               0xFFFFFFFFU
#define SOC_AON_M3GPIOFNC0_MASK31TO0_S                               0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       M3GPIOFNC1
    Offset name:         SOC_AON_O_M3GPIOFNC1
    Relative address:    0x2924
    Description:         M3 GPIO Functional Mask
    Default Value:       NA

        Field:           MASK44TO32
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     M3 GPIO Functional Mask. 13 MSBs (44-32)

                         0. Mask
                         1. Un-Mask

*/
#define SOC_AON_M3GPIOFNC1_MASK44TO32_W                              13U
#define SOC_AON_M3GPIOFNC1_MASK44TO32_M                              0x00001FFFU
#define SOC_AON_M3GPIOFNC1_MASK44TO32_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGOCLA
    Offset name:         SOC_AON_O_DBGOCLA
    Relative address:    0x2928
    Description:         Debug Bus Out Select.
                        This register sets the debug over sleep and IOMUX debug bus selection
    Default Value:       0x00000000

        Field:           SELLSB
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Debug mux port select LSB:
                         Chooses debug mux port to iomux
                         '000' - prcm/elp debug mux [7:0]
                         '001' - prcm/elp debug mux [15:8]
                         '010' - soc aod debug mux [7:0]
                         '011' - soc aod debug mux [15:8]
                         '100' - ocla debug mux [7:0]
                         '101' - ocla debug mux [15:8]

*/
#define SOC_AON_DBGOCLA_SELLSB_W                                     3U
#define SOC_AON_DBGOCLA_SELLSB_M                                     0x00000007U
#define SOC_AON_DBGOCLA_SELLSB_S                                     0U
/*

        Field:           SELMSB
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Debug mux port select MSB:
                         Chooses debug mux port to iomux
                         '000' - prcm/elp debug mux [7:0]
                         '001' - prcm/elp debug mux [15:8]
                         '010' - soc aod debug mux [7:0]
                         '011' - soc aod debug mux [15:8]
                         '100' - ocla debug mux [7:0]
                         '101' - ocla debug mux [15:8]

*/
#define SOC_AON_DBGOCLA_SELMSB_W                                     3U
#define SOC_AON_DBGOCLA_SELMSB_M                                     0x00000038U
#define SOC_AON_DBGOCLA_SELMSB_S                                     3U
/*

        Field:           AODTP1SEL
        From..to bits:   6...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AOD to OCLA TP1 select.
                         Chooses debug mux port to ocla
                         '000' - prcm tp1
                         '001' - elp tp1
                         '010' - rtc tp1
                         '011' - iomux tp1
                         '100' - debug aon tp1
                         '101' - soc aon tp1
                         '110' - host aon tp1

*/
#define SOC_AON_DBGOCLA_AODTP1SEL_W                                  3U
#define SOC_AON_DBGOCLA_AODTP1SEL_M                                  0x000001C0U
#define SOC_AON_DBGOCLA_AODTP1SEL_S                                  6U
/*

        Field:           AODTP2SEL
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     AOD to OCLA TP2 Select.
                         Chooses debug mux port to ocla
                         '000' - prcm tp2
                         '001' - elp tp2
                         '010' - rtc tp2
                         '011' - iomux tp2
                         '100' - debug aon tp2
                         '101' - soc aon tp1
                         '110' - host aon tp2

*/
#define SOC_AON_DBGOCLA_AODTP2SEL_W                                  3U
#define SOC_AON_DBGOCLA_AODTP2SEL_M                                  0x00000E00U
#define SOC_AON_DBGOCLA_AODTP2SEL_S                                  9U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CPUWAIT
    Offset name:         SOC_AON_O_CPUWAIT
    Relative address:    0x292C
    Description:         M33 CPUWAIT.

                        lock once. Do Not lock until written.
                        When written Locked immediately,
                        cleared only at soc aon reset or por reset.
                        These are host security lock configurations
    Default Value:       0x00000000

        Field:           EXIT
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     writeOnce
        Description:     locking HOSTMCU CPUWAIT
                         '1' - use FSM value
                         '0' - CPUWAIT

*/
#define SOC_AON_CPUWAIT_EXIT                                         0x00000001U
#define SOC_AON_CPUWAIT_EXIT_M                                       0x00000001U
#define SOC_AON_CPUWAIT_EXIT_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SPARE6
    Offset name:         SOC_AON_O_SPARE6
    Relative address:    0x2930
    Description:         spare reg for m3 aperture.
                        not locked.
    Default Value:       0x00000000

        Field:           BF
        From..to bits:   0...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M3 spare register

*/
#define SOC_AON_SPARE6_BF_W                                          4U
#define SOC_AON_SPARE6_BF_M                                          0x0000000FU
#define SOC_AON_SPARE6_BF_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SECSTA
    Offset name:         SOC_AON_O_SECSTA
    Relative address:    0x2934
    Description:         Security AON Status.
    Default Value:       NA

        Field:           HIDEASST
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     Hide assets.

                         0. OPEN
                         1. HIDE

                         This bit is the status of ROM hide H/W indication. 1 - ROM Assets (2KB in M3  BOOT ROM is hidden); 0 - ROM Assets (2KB in M3  BOOT ROM) is NOT hidden.
                         NOTE: same as [ROMASSETS]

*/
#define SOC_AON_SECSTA_HIDEASST                                      0x00000001U
#define SOC_AON_SECSTA_HIDEASST_M                                    0x00000001U
#define SOC_AON_SECSTA_HIDEASST_S                                    0U
/*

        Field:           UDSRDEN
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     UDS Read Enable.

                         0 - HIDE
                         1- OPEN

                         This bit is the status of UDS hide H/W indication. 1 - UDS is readable; 0 - UDS is hidden.
                         The Status Registers  [UDS0.*],  [UDS1.*], [UDS2.*], [UDS3.*] and [FUSELINE3.*], [FUSELINE4.*], [FUSELINE5.*], [FUSELINE6.*]  will be read as 0

*/
#define SOC_AON_SECSTA_UDSRDEN                                       0x00000002U
#define SOC_AON_SECSTA_UDSRDEN_M                                     0x00000002U
#define SOC_AON_SECSTA_UDSRDEN_S                                     1U
/*

        Field:           DEVATTEST
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device At test.

                         0 - FALSE
                         1 - TRUE

                         This bit indicates the Device is in ATTEST (or First Birthday).
                         Specifically, the Fuse pass without EFC or CRC errors, the Lifecycle is either 0 or 1 and strong pattern is all zeros.
                         NOTE: same as [SECBYPASS]

*/
#define SOC_AON_SECSTA_DEVATTEST                                     0x00000004U
#define SOC_AON_SECSTA_DEVATTEST_M                                   0x00000004U
#define SOC_AON_SECSTA_DEVATTEST_S                                   2U
/*

        Field:           SECBYPASS
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-only
        Description:     Security Bypass.

                         0 - FALSE
                         1 - TRUE

                         This bit indicates the Device is in ATTEST (or First Birthday).
                         Specifically, the Fuse pass without EFC or CRC errors, the Lifecycle is either 0 or 1 and strong pattern is all zeros.
                         NOTE: same as [DEVATTEST]

*/
#define SOC_AON_SECSTA_SECBYPASS                                     0x00000010U
#define SOC_AON_SECSTA_SECBYPASS_M                                   0x00000010U
#define SOC_AON_SECSTA_SECBYPASS_S                                   4U
/*

        Field:           HWCRCEN
        From..to bits:   5...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     HW CRC Enable.

                         This field reflects the Device fuse shift field HWCRCEN (3b) in case that EFC check has passed. Otherwise, it reflects "000"

*/
#define SOC_AON_SECSTA_HWCRCEN_W                                     3U
#define SOC_AON_SECSTA_HWCRCEN_M                                     0x000000E0U
#define SOC_AON_SECSTA_HWCRCEN_S                                     5U
/*

        Field:           PRCMSOP
        From..to bits:   8...9
        DefaultValue:    NA
        Access type:     read-only
        Description:     PRCM SOP:

                         0- DEBUG
                         1- DEFAULT
                         2- FSPKG
                         3- FSPRB

                         This field reflects the Device Sense on Power (SOP):
                         OSPREY_DEV_SOP_SOC_DEBUG                   2'h0
                         OSPREY_DEV_SOP_DEFAULT                          2'h1
                         OSPREY_DEV_SOP_FORCE_SUPPLY_PKG        2'h2
                         OSPREY_DEV_SOP_FORCE_SUPPLY                2'h3

*/
#define SOC_AON_SECSTA_PRCMSOP_W                                     2U
#define SOC_AON_SECSTA_PRCMSOP_M                                     0x00000300U
#define SOC_AON_SECSTA_PRCMSOP_S                                     8U
/*

        Field:           EFCERR
        From..to bits:   11...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     EFC Error.

                         This field reflects the Device fuse shift EFC error 5 bits. All zeros means no error.

*/
#define SOC_AON_SECSTA_EFCERR_W                                      5U
#define SOC_AON_SECSTA_EFCERR_M                                      0x0000F800U
#define SOC_AON_SECSTA_EFCERR_S                                      11U
/*

        Field:           EFCLDDONE
        From..to bits:   16...16
        DefaultValue:    NA
        Access type:     read-only
        Description:     EFC Autoload Done.

                         0 - FAIL
                         1 - PASS

                         This bit indicates the Device h/w fuse shit progress has been done.

*/
#define SOC_AON_SECSTA_EFCLDDONE                                     0x00010000U
#define SOC_AON_SECSTA_EFCLDDONE_M                                   0x00010000U
#define SOC_AON_SECSTA_EFCLDDONE_S                                   16U
/*

        Field:           LCVALID
        From..to bits:   17...17
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device LifeCycle Valid.

                         0 - FAIL
                         1 - PASS

                         This bit indicates the Device h/w fuse shift has pass without EFC or CRC errors and that the Lifecycle matches the strong pattern.
                         Meaning pattern equal to 0 in LC equal to 0 or 1; pattern equal to LC of ATTST PRIVILEGE;  pattern equal to LC of Operational;

*/
#define SOC_AON_SECSTA_LCVALID                                       0x00020000U
#define SOC_AON_SECSTA_LCVALID_M                                     0x00020000U
#define SOC_AON_SECSTA_LCVALID_S                                     17U
/*

        Field:           COREEN
        From..to bits:   18...18
        DefaultValue:    NA
        Access type:     read-only
        Description:     Core Enable,

                         0 - NO
                         1 - YES

                         This bit indicates the Device Application CPU requested the Network CPU to power off ("Connectivity Stop"  a.k.a "SL STOP" in former device family).
                         When This bit is set the Network Core CPU registers will be automatically cleared.
                         The device is now ready to be reloaded in "elevated mode" namely Secondary Boot.

*/
#define SOC_AON_SECSTA_COREEN                                        0x00040000U
#define SOC_AON_SECSTA_COREEN_M                                      0x00040000U
#define SOC_AON_SECSTA_COREEN_S                                      18U
/*

        Field:           LCPATMATCH
        From..to bits:   19...19
        DefaultValue:    NA
        Access type:     read-only
        Description:     Pattern Match LyfeCycle.

                         0 - NO_MATCH
                         1 - MATCH

                         This bit indicates the Device h/w fuse shift has done and that the Lifecycle matches the strong pattern.
                         Meaning pattern equal to 0 in LC equal to 0 or 1; pattern equal to LC of ATTST PRIVILEGE;  pattern equal to LC of Operational;
                         NOTE: No validity Check is conditioning this indication. Specifically no EFC or CRC check masks this indication.

*/
#define SOC_AON_SECSTA_LCPATMATCH                                    0x00080000U
#define SOC_AON_SECSTA_LCPATMATCH_M                                  0x00080000U
#define SOC_AON_SECSTA_LCPATMATCH_S                                  19U
/*

        Field:           CRCPASSED
        From..to bits:   20...20
        DefaultValue:    NA
        Access type:     read-only
        Description:     Fuse CRC Check Passed.

                         0 - NO
                         1- YES

                         This bit indicates the Device h/w fuse shift has passed without CRC error, or that fuse shift is done with the CRC check being ignored by System PRCM module

*/
#define SOC_AON_SECSTA_CRCPASSED                                     0x00100000U
#define SOC_AON_SECSTA_CRCPASSED_M                                   0x00100000U
#define SOC_AON_SECSTA_CRCPASSED_S                                   20U
/*

        Field:           CRCIGNORE
        From..to bits:   21...21
        DefaultValue:    NA
        Access type:     read-only
        Description:     PRCM Ignore Fuse CRC Check.

                         0 - NO
                         1 - YES

                         This bit indicates the Device System PRCM module sets the CRC check ignored bit

*/
#define SOC_AON_SECSTA_CRCIGNORE                                     0x00200000U
#define SOC_AON_SECSTA_CRCIGNORE_M                                   0x00200000U
#define SOC_AON_SECSTA_CRCIGNORE_S                                   21U
/*

        Field:           LCSTRONG
        From..to bits:   22...22
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device LifeCycle Strong Pattern Valid.

                         0 - FAIL
                         1- PASS

                         This bit indicates the fuse shift is done without EFC error

*/
#define SOC_AON_SECSTA_LCSTRONG                                      0x00400000U
#define SOC_AON_SECSTA_LCSTRONG_M                                    0x00400000U
#define SOC_AON_SECSTA_LCSTRONG_S                                    22U
/*

        Field:           BOOTROM
        From..to bits:   23...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     Hide Boot ROM.

                         This bit is the status of ROM hide H/W indication. 1 - entire Boot ROM is hidden; 0 - Boot ROM is NOT hidden.

*/
#define SOC_AON_SECSTA_BOOTROM                                       0x00800000U
#define SOC_AON_SECSTA_BOOTROM_M                                     0x00800000U
#define SOC_AON_SECSTA_BOOTROM_S                                     23U
/*

        Field:           ROMASSETS
        From..to bits:   24...24
        DefaultValue:    NA
        Access type:     read-only
        Description:     Hide Rom Assets,

                         0 - OPEN
                         1- HIDE

                         This bit is the status of ROM hide H/W indication. 1 - ROM Assets (2KB in M3  BOOT ROM is hidden); 0 - ROM Assets (2KB in M3  BOOT ROM) is NOT hidden.
                         NOTE: same as [HIDEASSETS]

*/
#define SOC_AON_SECSTA_ROMASSETS                                     0x01000000U
#define SOC_AON_SECSTA_ROMASSETS_M                                   0x01000000U
#define SOC_AON_SECSTA_ROMASSETS_S                                   24U
/*

        Field:           ELEVMODE
        From..to bits:   25...25
        DefaultValue:    NA
        Access type:     read-only
        Description:     Device Elevated Mode.

*/
#define SOC_AON_SECSTA_ELEVMODE                                      0x02000000U
#define SOC_AON_SECSTA_ELEVMODE_M                                    0x02000000U
#define SOC_AON_SECSTA_ELEVMODE_S                                    25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3VAL2ND
    Offset name:         SOC_AON_O_ESM3VAL2ND
    Relative address:    0x2938
    Description:         ESM3 2nd Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow additional protection on ESM and also allow vendor to unmask ESM only at the end of vendor secure boot (SBL) is completed
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 2nd magic value

*/
#define SOC_AON_ESM3VAL2ND_MGCVAL_W                                  8U
#define SOC_AON_ESM3VAL2ND_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM3VAL2ND_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4VAL2ND
    Offset name:         SOC_AON_O_ESM4VAL2ND
    Relative address:    0x293C
    Description:         ESM4 2nd Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow additional protection on ESM and also allow vendor to unmask ESM only at the end of vendor secure boot (SBL) is completed
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 2nd magic value

*/
#define SOC_AON_ESM4VAL2ND_MGCVAL_W                                  8U
#define SOC_AON_ESM4VAL2ND_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM4VAL2ND_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5VAL2ND
    Offset name:         SOC_AON_O_ESM5VAL2ND
    Relative address:    0x2940
    Description:         ESM5 2nd Magic Value.

                        This value is compared to hard coded value and unmask ESM only when value is matched. This additional compare allow additional protection on ESM and also allow vendor to unmask ESM only at the end of vendor secure boot (SBL) is completed
    Default Value:       NA

        Field:           MGCVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     ESM 2nd magic value

*/
#define SOC_AON_ESM5VAL2ND_MGCVAL_W                                  8U
#define SOC_AON_ESM5VAL2ND_MGCVAL_M                                  0x000000FFU
#define SOC_AON_ESM5VAL2ND_MGCVAL_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3STA
    Offset name:         SOC_AON_O_ESM3STA
    Relative address:    0x2944
    Description:         ESM3 Status.

                        status register , for each of the ESM (enable sequence monitor) what is the current state of esm.
    Default Value:       NA

        Field:           STATE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     5 states:
                         0000 - READY
                         0001 - ENABLED (not guarenteed that magic values match)
                         0010 - PENDING TO NEXT WRITE
                         0100 - GRACFULLY LOCKED
                         1000 - FAULT


*/
#define SOC_AON_ESM3STA_STATE_W                                      4U
#define SOC_AON_ESM3STA_STATE_M                                      0x0000000FU
#define SOC_AON_ESM3STA_STATE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4STA
    Offset name:         SOC_AON_O_ESM4STA
    Relative address:    0x2948
    Description:         ESM4 Status.

                        status register , for each of the ESM (enable sequence monitor) what is the current state of esm.
    Default Value:       NA

        Field:           STATE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     5 states:
                         0000 - READY
                         0001 - ENABLED (not guarenteed that magic values match)
                         0010 - PENDING TO NEXT WRITE
                         0100 - GRACFULLY LOCKED
                         1000 - FAULT


*/
#define SOC_AON_ESM4STA_STATE_W                                      4U
#define SOC_AON_ESM4STA_STATE_M                                      0x0000000FU
#define SOC_AON_ESM4STA_STATE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5STA
    Offset name:         SOC_AON_O_ESM5STA
    Relative address:    0x294C
    Description:         ESM5 Status.

                        status register , for each of the ESM (enable sequence monitor) what is the current state of esm.
    Default Value:       NA

        Field:           STATE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     5 states:
                         0000 - READY
                         0001 - ENABLED (not guarenteed that magic values match)
                         0010 - PENDING TO NEXT WRITE
                         0100 - GRACFULLY LOCKED
                         1000 - FAULT


*/
#define SOC_AON_ESM5STA_STATE_W                                      4U
#define SOC_AON_ESM5STA_STATE_M                                      0x0000000FU
#define SOC_AON_ESM5STA_STATE_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM3STA2ND
    Offset name:         SOC_AON_O_ESM3STA2ND
    Relative address:    0x2950
    Description:         ESM3 2nd magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val match

*/
#define SOC_AON_ESM3STA2ND_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM3STA2ND_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM3STA2ND_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM3STA2ND_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM3STA2ND_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM3STA2ND_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM4STA2ND
    Offset name:         SOC_AON_O_ESM4STA2ND
    Relative address:    0x2954
    Description:         ESM4 2nd magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val match

*/
#define SOC_AON_ESM4STA2ND_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM4STA2ND_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM4STA2ND_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM4STA2ND_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM4STA2ND_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM4STA2ND_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ESM5STA2ND
    Offset name:         SOC_AON_O_ESM5STA2ND
    Relative address:    0x2958
    Description:         ESM5 2nd magic value match indication.
    Default Value:       NA

        Field:           MGCVDONE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val match

*/
#define SOC_AON_ESM5STA2ND_MGCVDONE                                  0x00000001U
#define SOC_AON_ESM5STA2ND_MGCVDONE_M                                0x00000001U
#define SOC_AON_ESM5STA2ND_MGCVDONE_S                                0U
/*

        Field:           MGCVFLT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     ESM 2nd magic val fault ( note: indicates fault before a write to the magic val register)

*/
#define SOC_AON_ESM5STA2ND_MGCVFLT                                   0x00000002U
#define SOC_AON_ESM5STA2ND_MGCVFLT_M                                 0x00000002U
#define SOC_AON_ESM5STA2ND_MGCVFLT_S                                 1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LCSTA
    Offset name:         SOC_AON_O_LCSTA
    Relative address:    0x295C
    Description:         This register contains information on Device Life Cycles ad follow:

                        1. [11:8] Device Life Cycle SW Managed - as exist at [FUSELINE0.DEVLCSW]
                        2. [3:0] Device Life Cycle - based on Device Life Cycle HW Managed as exist at [FUSELINE0.DEVLCHW]
                            but with following decoding and validation logic:
                        	if fuse data is valid- no crc/no efc ready /pattern error the Decoded value is:
                        		0 - 1st Birthday
                        		1 - AT TEST
                        		2 - AT TEST Privilege
                        		3 - Operational
                        	otherwise, the value is
                        		4 - fault mode -fault occurred on life cycle read
    Default Value:       NA

        Field:           LIFECYCLE
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     OSPREY device lifecycle

*/
#define SOC_AON_LCSTA_LIFECYCLE_W                                    4U
#define SOC_AON_LCSTA_LIFECYCLE_M                                    0x0000000FU
#define SOC_AON_LCSTA_LIFECYCLE_S                                    0U
/*

        Field:           SWMNG
        From..to bits:   8...11
        DefaultValue:    NA
        Access type:     read-only
        Description:     OSPREY SW device lifecycle


*/
#define SOC_AON_LCSTA_SWMNG_W                                        4U
#define SOC_AON_LCSTA_SWMNG_M                                        0x00000F00U
#define SOC_AON_LCSTA_SWMNG_S                                        8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DRMAST
    Offset name:         SOC_AON_O_DRMAST
    Relative address:    0x2960
    Description:         DRAM_ASSET
    Default Value:       NA

        Field:           ERSDRMDN
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     ERASE_DRAM_ASSET_DONE

                         1: erase done
                         0: erase in progress

*/
#define SOC_AON_DRMAST_ERSDRMDN                                      0x00000001U
#define SOC_AON_DRMAST_ERSDRMDN_M                                    0x00000001U
#define SOC_AON_DRMAST_ERSDRMDN_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       FLASHMASK
    Offset name:         SOC_AON_O_FLASHMASK
    Relative address:    0x2964
    Description:         FLASH MASK
    Default Value:       0x00000001

        Field:           FLASHMASKOV
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     FLASH_MASK_OVERRIDE
                         Override flash data output masking logic ( done using flash cs ) to allow working on external flash on stacked PSRAM devices
                         1: unmask flash lines, data visible on external pins
                         0: flash lines are masked according to flash_cs

*/
#define SOC_AON_FLASHMASK_FLASHMASKOV                                0x00000001U
#define SOC_AON_FLASHMASK_FLASHMASKOV_M                              0x00000001U
#define SOC_AON_FLASHMASK_FLASHMASKOV_S                              0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WSOCROM
    Offset name:         SOC_AON_O_WSOCROM
    Relative address:    0x2968
    Description:         WSOC ROM Unhide.

                        1 lock. Write once.
                        Asserted by FW at the end of ROM boot.
                        Locked immediately ,
                        cleared by core disable (or at soc aon reset or por reset)
    Default Value:       0x00000001

        Field:           UNHIDE
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     writeOnce
        Description:     Hiding the ROM

*/
#define SOC_AON_WSOCROM_UNHIDE                                       0x00000001U
#define SOC_AON_WSOCROM_UNHIDE_M                                     0x00000001U
#define SOC_AON_WSOCROM_UNHIDE_S                                     0U

#endif /* __HW_SOC_AON_H__*/
