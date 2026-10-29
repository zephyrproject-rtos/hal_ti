/******************************************************************************
*  Filename:       hw_iomux.h
*
*  Description:    Defines and prototypes for the IOMUX peripheral.
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
#ifndef __HW_IOMUX_H__
#define __HW_IOMUX_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the IOMUX component

--------------------------------------------------------------------------------- */

//CFG register for IO SLOW_CLOCK_IN
#define IOMUX_O_SCLKICFG                                             0x00000000U

//Pull control register of IO SLOW_CLOCK_IN
#define IOMUX_O_SCLKIPCTL                                            0x00000004U

//Control register of IO SLOW_CLOCK_IN
#define IOMUX_O_SCLKICTL                                             0x00000008U

//Event control register for IO SLOW_CLOCK_IN
#define IOMUX_O_SCLKIECTL                                            0x0000000CU

//CFG register for IO LFXTAL_N
#define IOMUX_O_LFXTNCFG                                             0x00001000U

//Pull control register of IO LFXTAL_N
#define IOMUX_O_LFXTNPCTL                                            0x00001004U

//Control register of IO LFXTAL_N
#define IOMUX_O_LFXTNCTL                                             0x00001008U

//Event control register for IO LFXTAL_N
#define IOMUX_O_LFXTNECTL                                            0x0000100CU

//CFG register for IO GPIO2
#define IOMUX_O_GPIO2CFG                                             0x00002000U

//Pull control register of IO GPIO2
#define IOMUX_O_GPIO2PCTL                                            0x00002004U

//Control register of IO GPIO2
#define IOMUX_O_GPIO2CTL                                             0x00002008U

//Event control register for IO GPIO2
#define IOMUX_O_GPIO2ECTL                                            0x0000200CU

//CFG register for IO GPIO3
#define IOMUX_O_GPIO3CFG                                             0x00003000U

//Pull control register of IO GPIO3
#define IOMUX_O_GPIO3PCTL                                            0x00003004U

//Control register of IO GPIO3
#define IOMUX_O_GPIO3CTL                                             0x00003008U

//Event control register for IO GPIO3
#define IOMUX_O_GPIO3ECTL                                            0x0000300CU

//CFG register for IO GPIO4
#define IOMUX_O_GPIO4CFG                                             0x00004000U

//Pull control register of IO GPIO4
#define IOMUX_O_GPIO4PCTL                                            0x00004004U

//Control register of IO GPIO4
#define IOMUX_O_GPIO4CTL                                             0x00004008U

//Event control register for IO GPIO4
#define IOMUX_O_GPIO4ECTL                                            0x0000400CU

//CFG register for IO GPIO5
#define IOMUX_O_GPIO5CFG                                             0x00005000U

//Pull control register of IO GPIO5
#define IOMUX_O_GPIO5PCTL                                            0x00005004U

//Control register of IO GPIO5
#define IOMUX_O_GPIO5CTL                                             0x00005008U

//Event control register for IO GPIO5
#define IOMUX_O_GPIO5ECTL                                            0x0000500CU

//CFG register for IO GPIO6
#define IOMUX_O_GPIO6CFG                                             0x00006000U

//Pull control register of IO GPIO6
#define IOMUX_O_GPIO6PCTL                                            0x00006004U

//Control register of IO GPIO6
#define IOMUX_O_GPIO6CTL                                             0x00006008U

//Event control register for IO GPIO6
#define IOMUX_O_GPIO6ECTL                                            0x0000600CU

//CFG register for IO SWDIO
#define IOMUX_O_SWDIOCFG                                             0x00007000U

//Pull control register of IO SWDIO
#define IOMUX_O_SWDIOPCTL                                            0x00007004U

//Control register of IO SWDIO
#define IOMUX_O_SWDIOCTL                                             0x00007008U

//Event control register for IO SWDIO
#define IOMUX_O_SWDIOECTL                                            0x0000700CU

//CFG register for IO SWCLK
#define IOMUX_O_SWCLKCFG                                             0x00008000U

//Pull control register of IO SWCLK
#define IOMUX_O_SWCLKPCTL                                            0x00008004U

//Control register of IO SWCLK
#define IOMUX_O_SWCLKCTL                                             0x00008008U

//Event control register for IO SWCLK
#define IOMUX_O_SWCLKECTL                                            0x0000800CU

//CFG register for IO LOGGER
#define IOMUX_O_LOGGERCFG                                            0x00009000U

//Pull control register of IO LOGGER
#define IOMUX_O_LOGGERPCTL                                           0x00009004U

//Control register of IO LOGGER
#define IOMUX_O_LOGGERCTL                                            0x00009008U

//Event control register for IO LOGGER
#define IOMUX_O_LOGGERECTL                                           0x0000900CU

//CFG register for IO GPIO10
#define IOMUX_O_GPIO10CFG                                            0x0000A000U

//Pull control register of IO GPIO10
#define IOMUX_O_GPIO10PCTL                                           0x0000A004U

//Control register of IO GPIO10
#define IOMUX_O_GPIO10CTL                                            0x0000A008U

//Event control register for IO GPIO10
#define IOMUX_O_GPIO10ECTL                                           0x0000A00CU

//CFG register for IO GPIO11
#define IOMUX_O_GPIO11CFG                                            0x0000B000U

//Pull control register of IO GPIO11
#define IOMUX_O_GPIO11PCTL                                           0x0000B004U

//Control register of IO GPIO11
#define IOMUX_O_GPIO11CTL                                            0x0000B008U

//Event control register for IO GPIO11
#define IOMUX_O_GPIO11ECTL                                           0x0000B00CU

//CFG register for IO GPIO12
#define IOMUX_O_GPIO12CFG                                            0x0000C000U

//Pull control register of IO GPIO12
#define IOMUX_O_GPIO12PCTL                                           0x0000C004U

//Control register of IO GPIO12
#define IOMUX_O_GPIO12CTL                                            0x0000C008U

//Event control register for IO GPIO12
#define IOMUX_O_GPIO12ECTL                                           0x0000C00CU

//CFG register for IO GPIO13
#define IOMUX_O_GPIO13CFG                                            0x0000D000U

//Pull control register of IO GPIO13
#define IOMUX_O_GPIO13PCTL                                           0x0000D004U

//Control register of IO GPIO13
#define IOMUX_O_GPIO13CTL                                            0x0000D008U

//Event control register for IO GPIO13
#define IOMUX_O_GPIO13ECTL                                           0x0000D00CU

//CFG register for IO GPIO14
#define IOMUX_O_GPIO14CFG                                            0x0000E000U

//Pull control register of IO GPIO14
#define IOMUX_O_GPIO14PCTL                                           0x0000E004U

//Control register of IO GPIO14
#define IOMUX_O_GPIO14CTL                                            0x0000E008U

//Event control register for IO GPIO14
#define IOMUX_O_GPIO14ECTL                                           0x0000E00CU

//CFG register for IO GPIO15
#define IOMUX_O_GPIO15CFG                                            0x0000F000U

//Pull control register of IO GPIO15
#define IOMUX_O_GPIO15PCTL                                           0x0000F004U

//Control register of IO GPIO15
#define IOMUX_O_GPIO15CTL                                            0x0000F008U

//Event control register for IO GPIO15
#define IOMUX_O_GPIO15ECTL                                           0x0000F00CU

//CFG register for IO GPIO16
#define IOMUX_O_GPIO16CFG                                            0x00010000U

//Pull control register of IO GPIO16
#define IOMUX_O_GPIO16PCTL                                           0x00010004U

//Control register of IO GPIO16
#define IOMUX_O_GPIO16CTL                                            0x00010008U

//Event control register for IO GPIO16
#define IOMUX_O_GPIO16ECTL                                           0x0001000CU

//CFG register for IO GPIO17
#define IOMUX_O_GPIO17CFG                                            0x00011000U

//Pull control register of IO GPIO17
#define IOMUX_O_GPIO17PCTL                                           0x00011004U

//Control register of IO GPIO17
#define IOMUX_O_GPIO17CTL                                            0x00011008U

//Event control register for IO GPIO17
#define IOMUX_O_GPIO17ECTL                                           0x0001100CU

//CFG register for IO GPIO18
#define IOMUX_O_GPIO18CFG                                            0x00012000U

//Pull control register of IO GPIO18
#define IOMUX_O_GPIO18PCTL                                           0x00012004U

//Control register of IO GPIO18
#define IOMUX_O_GPIO18CTL                                            0x00012008U

//Event control register for IO GPIO18
#define IOMUX_O_GPIO18ECTL                                           0x0001200CU

//CFG register for IO GPIO19
#define IOMUX_O_GPIO19CFG                                            0x00013000U

//Pull control register of IO GPIO19
#define IOMUX_O_GPIO19PCTL                                           0x00013004U

//Control register of IO GPIO19
#define IOMUX_O_GPIO19CTL                                            0x00013008U

//Event control register for IO GPIO19
#define IOMUX_O_GPIO19ECTL                                           0x0001300CU

//CFG register for IO GPIO20
#define IOMUX_O_GPIO20CFG                                            0x00014000U

//Pull control register of IO GPIO20
#define IOMUX_O_GPIO20PCTL                                           0x00014004U

//Control register of IO GPIO20
#define IOMUX_O_GPIO20CTL                                            0x00014008U

//Event control register for IO GPIO20
#define IOMUX_O_GPIO20ECTL                                           0x0001400CU

//CFG register for IO GPIO21
#define IOMUX_O_GPIO21CFG                                            0x00015000U

//Pull control register of IO GPIO21
#define IOMUX_O_GPIO21PCTL                                           0x00015004U

//Control register of IO GPIO21
#define IOMUX_O_GPIO21CTL                                            0x00015008U

//Event control register for IO GPIO21
#define IOMUX_O_GPIO21ECTL                                           0x0001500CU

//CFG register for IO GPIO22
#define IOMUX_O_GPIO22CFG                                            0x00016000U

//Pull control register of IO GPIO22
#define IOMUX_O_GPIO22PCTL                                           0x00016004U

//Control register of IO GPIO22
#define IOMUX_O_GPIO22CTL                                            0x00016008U

//Event control register for IO GPIO22
#define IOMUX_O_GPIO22ECTL                                           0x0001600CU

//CFG register for IO GPIO23
#define IOMUX_O_GPIO23CFG                                            0x00017000U

//Pull control register of IO GPIO23
#define IOMUX_O_GPIO23PCTL                                           0x00017004U

//Control register of IO GPIO23
#define IOMUX_O_GPIO23CTL                                            0x00017008U

//Event control register for IO GPIO23
#define IOMUX_O_GPIO23ECTL                                           0x0001700CU

//CFG register for IO GPIO24
#define IOMUX_O_GPIO24CFG                                            0x00018000U

//Pull control register of IO GPIO24
#define IOMUX_O_GPIO24PCTL                                           0x00018004U

//Control register of IO GPIO24
#define IOMUX_O_GPIO24CTL                                            0x00018008U

//Event control register for IO GPIO24
#define IOMUX_O_GPIO24ECTL                                           0x0001800CU

//CFG register for IO GPIO25
#define IOMUX_O_GPIO25CFG                                            0x00019000U

//Pull control register of IO GPIO25
#define IOMUX_O_GPIO25PCTL                                           0x00019004U

//Control register of IO GPIO25
#define IOMUX_O_GPIO25CTL                                            0x00019008U

//Event control register for IO GPIO25
#define IOMUX_O_GPIO25ECTL                                           0x0001900CU

//CFG register for IO GPIO26
#define IOMUX_O_GPIO26CFG                                            0x0001A000U

//Pull control register of IO GPIO26
#define IOMUX_O_GPIO26PCTL                                           0x0001A004U

//Control register of IO GPIO26
#define IOMUX_O_GPIO26CTL                                            0x0001A008U

//Event control register for IO GPIO26
#define IOMUX_O_GPIO26ECTL                                           0x0001A00CU

//CFG register for IO GPIO27
#define IOMUX_O_GPIO27CFG                                            0x0001B000U

//Pull control register of IO GPIO27
#define IOMUX_O_GPIO27PCTL                                           0x0001B004U

//Control register of IO GPIO27
#define IOMUX_O_GPIO27CTL                                            0x0001B008U

//Event control register for IO GPIO27
#define IOMUX_O_GPIO27ECTL                                           0x0001B00CU

//CFG register for IO GPIO28
#define IOMUX_O_GPIO28CFG                                            0x0001C000U

//Pull control register of IO GPIO28
#define IOMUX_O_GPIO28PCTL                                           0x0001C004U

//Control register of IO GPIO28
#define IOMUX_O_GPIO28CTL                                            0x0001C008U

//Event control register for IO GPIO28
#define IOMUX_O_GPIO28ECTL                                           0x0001C00CU

//CFG register for IO GPIO29
#define IOMUX_O_GPIO29CFG                                            0x0001D000U

//Pull control register of IO GPIO29
#define IOMUX_O_GPIO29PCTL                                           0x0001D004U

//Control register of IO GPIO29
#define IOMUX_O_GPIO29CTL                                            0x0001D008U

//Event control register for IO GPIO29
#define IOMUX_O_GPIO29ECTL                                           0x0001D00CU

//CFG register for IO GPIO30
#define IOMUX_O_GPIO30CFG                                            0x0001E000U

//Pull control register of IO GPIO30
#define IOMUX_O_GPIO30PCTL                                           0x0001E004U

//Control register of IO GPIO30
#define IOMUX_O_GPIO30CTL                                            0x0001E008U

//Event control register for IO GPIO30
#define IOMUX_O_GPIO30ECTL                                           0x0001E00CU

//CFG register for IO GPIO31
#define IOMUX_O_GPIO31CFG                                            0x0001F000U

//Pull control register of IO GPIO31
#define IOMUX_O_GPIO31PCTL                                           0x0001F004U

//Control register of IO GPIO31
#define IOMUX_O_GPIO31CTL                                            0x0001F008U

//Event control register for IO GPIO31
#define IOMUX_O_GPIO31ECTL                                           0x0001F00CU

//CFG register for IO GPIO32
#define IOMUX_O_GPIO32CFG                                            0x00020000U

//Pull control register of IO GPIO32
#define IOMUX_O_GPIO32PCTL                                           0x00020004U

//Control register of IO GPIO32
#define IOMUX_O_GPIO32CTL                                            0x00020008U

//Event control register for IO GPIO32
#define IOMUX_O_GPIO32ECTL                                           0x0002000CU

//CFG register for IO GPIO33
#define IOMUX_O_GPIO33CFG                                            0x00021000U

//Pull control register of IO GPIO33
#define IOMUX_O_GPIO33PCTL                                           0x00021004U

//Control register of IO GPIO33
#define IOMUX_O_GPIO33CTL                                            0x00021008U

//Event control register for IO GPIO33
#define IOMUX_O_GPIO33ECTL                                           0x0002100CU

//CFG register for IO GPIO34
#define IOMUX_O_GPIO34CFG                                            0x00022000U

//Pull control register of IO GPIO34
#define IOMUX_O_GPIO34PCTL                                           0x00022004U

//Control register of IO GPIO34
#define IOMUX_O_GPIO34CTL                                            0x00022008U

//Event control register for IO GPIO34
#define IOMUX_O_GPIO34ECTL                                           0x0002200CU

//CFG register for IO GPIO35
#define IOMUX_O_GPIO35CFG                                            0x00023000U

//Pull control register of IO GPIO35
#define IOMUX_O_GPIO35PCTL                                           0x00023004U

//Control register of IO GPIO35
#define IOMUX_O_GPIO35CTL                                            0x00023008U

//Event control register for IO GPIO35
#define IOMUX_O_GPIO35ECTL                                           0x0002300CU

//CFG register for IO GPIO36
#define IOMUX_O_GPIO36CFG                                            0x00024000U

//Pull control register of IO GPIO36
#define IOMUX_O_GPIO36PCTL                                           0x00024004U

//Control register of IO GPIO36
#define IOMUX_O_GPIO36CTL                                            0x00024008U

//Event control register for IO GPIO36
#define IOMUX_O_GPIO36ECTL                                           0x0002400CU

//CFG register for IO GPIO37
#define IOMUX_O_GPIO37CFG                                            0x00025000U

//Pull control register of IO GPIO37
#define IOMUX_O_GPIO37PCTL                                           0x00025004U

//Control register of IO GPIO37
#define IOMUX_O_GPIO37CTL                                            0x00025008U

//Event control register for IO GPIO37
#define IOMUX_O_GPIO37ECTL                                           0x0002500CU

//CFG register for IO GPIO38
#define IOMUX_O_GPIO38CFG                                            0x00026000U

//Pull control register of IO GPIO38
#define IOMUX_O_GPIO38PCTL                                           0x00026004U

//Control register of IO GPIO38
#define IOMUX_O_GPIO38CTL                                            0x00026008U

//Event control register for IO GPIO38
#define IOMUX_O_GPIO38ECTL                                           0x0002600CU

//CFG register for IO GPIO39
#define IOMUX_O_GPIO39CFG                                            0x00027000U

//Pull control register of IO GPIO39
#define IOMUX_O_GPIO39PCTL                                           0x00027004U

//Control register of IO GPIO39
#define IOMUX_O_GPIO39CTL                                            0x00027008U

//Event control register for IO GPIO39
#define IOMUX_O_GPIO39ECTL                                           0x0002700CU

//CFG register for IO GPIO40
#define IOMUX_O_GPIO40CFG                                            0x00028000U

//Pull control register of IO GPIO40
#define IOMUX_O_GPIO40PCTL                                           0x00028004U

//Control register of IO GPIO40
#define IOMUX_O_GPIO40CTL                                            0x00028008U

//Event control register for IO GPIO40
#define IOMUX_O_GPIO40ECTL                                           0x0002800CU

//CFG register for IO GPIO41
#define IOMUX_O_GPIO41CFG                                            0x00029000U

//Pull control register of IO GPIO41
#define IOMUX_O_GPIO41PCTL                                           0x00029004U

//Control register of IO GPIO41
#define IOMUX_O_GPIO41CTL                                            0x00029008U

//Event control register for IO GPIO41
#define IOMUX_O_GPIO41ECTL                                           0x0002900CU

//CFG register for IO GPIO42
#define IOMUX_O_GPIO42CFG                                            0x0002A000U

//Pull control register of IO GPIO42
#define IOMUX_O_GPIO42PCTL                                           0x0002A004U

//Control register of IO GPIO42
#define IOMUX_O_GPIO42CTL                                            0x0002A008U

//Event control register for IO GPIO42
#define IOMUX_O_GPIO42ECTL                                           0x0002A00CU

//CFG register for IO GPIO43
#define IOMUX_O_GPIO43CFG                                            0x0002B000U

//Pull control register of IO GPIO43
#define IOMUX_O_GPIO43PCTL                                           0x0002B004U

//Control register of IO GPIO43
#define IOMUX_O_GPIO43CTL                                            0x0002B008U

//Event control register for IO GPIO43
#define IOMUX_O_GPIO43ECTL                                           0x0002B00CU

//CFG register for IO GPIO44
#define IOMUX_O_GPIO44CFG                                            0x0002C000U

//Pull control register of IO GPIO44
#define IOMUX_O_GPIO44PCTL                                           0x0002C004U

//Control register of IO GPIO44
#define IOMUX_O_GPIO44CTL                                            0x0002C008U

//Event control register for IO GPIO44
#define IOMUX_O_GPIO44ECTL                                           0x0002C00CU

//This register disables the SOP overrides when the device was powered in one of the SoP modes
#define IOMUX_O_SOPDIS                                               0x0002D000U

//Port configuration register for IO SLOW_CLOCK_IN
#define IOMUX_O_SCLKIPCFG                                            0x0002D004U

//Port configuration register for IO LFXTAL_N
#define IOMUX_O_LFXTNPCFG                                            0x0002D008U

//Port configuration register for IO GPIO2
#define IOMUX_O_GPIO2PCFG                                            0x0002D00CU

//Port configuration register for IO GPIO3
#define IOMUX_O_GPIO3PCFG                                            0x0002D010U

//Port configuration register for IO GPIO4
#define IOMUX_O_GPIO4PCFG                                            0x0002D014U

//Port configuration register for IO GPIO5
#define IOMUX_O_GPIO5PCFG                                            0x0002D018U

//Port configuration register for IO GPIO6
#define IOMUX_O_GPIO6PCFG                                            0x0002D01CU

//Port configuration register for IO SWDIO
#define IOMUX_O_SWDIOPCFG                                            0x0002D020U

//Port configuration register for IO SWCLK
#define IOMUX_O_SWCLKPCFG                                            0x0002D024U

//Port configuration register for IO LOGGER
#define IOMUX_O_LOGGERPCFG                                           0x0002D028U

//Port configuration register for IO GPIO10
#define IOMUX_O_GPIO10PCFG                                           0x0002D02CU

//Port configuration register for IO GPIO11
#define IOMUX_O_GPIO11PCFG                                           0x0002D030U

//Port configuration register for IO GPIO12
#define IOMUX_O_GPIO12PCFG                                           0x0002D034U

//Port configuration register for IO GPIO13
#define IOMUX_O_GPIO13PCFG                                           0x0002D038U

//Port configuration register for IO GPIO14
#define IOMUX_O_GPIO14PCFG                                           0x0002D03CU

//Port configuration register for IO GPIO15
#define IOMUX_O_GPIO15PCFG                                           0x0002D040U

//Port configuration register for IO GPIO16
#define IOMUX_O_GPIO16PCFG                                           0x0002D044U

//Port configuration register for IO GPIO17
#define IOMUX_O_GPIO17PCFG                                           0x0002D048U

//Port configuration register for IO GPIO18
#define IOMUX_O_GPIO18PCFG                                           0x0002D04CU

//Port configuration register for IO GPIO19
#define IOMUX_O_GPIO19PCFG                                           0x0002D050U

//Port configuration register for IO GPIO20
#define IOMUX_O_GPIO20PCFG                                           0x0002D054U

//Port configuration register for IO GPIO21
#define IOMUX_O_GPIO21PCFG                                           0x0002D058U

//Port configuration register for IO GPIO22
#define IOMUX_O_GPIO22PCFG                                           0x0002D05CU

//Port configuration register for IO GPIO23
#define IOMUX_O_GPIO23PCFG                                           0x0002D060U

//Port configuration register for IO GPIO24
#define IOMUX_O_GPIO24PCFG                                           0x0002D064U

//Port configuration register for IO GPIO25
#define IOMUX_O_GPIO25PCFG                                           0x0002D068U

//Port configuration register for IO GPIO26
#define IOMUX_O_GPIO26PCFG                                           0x0002D06CU

//Port configuration register for IO GPIO27
#define IOMUX_O_GPIO27PCFG                                           0x0002D070U

//Port configuration register for IO GPIO28
#define IOMUX_O_GPIO28PCFG                                           0x0002D074U

//Port configuration register for IO GPIO29
#define IOMUX_O_GPIO29PCFG                                           0x0002D078U

//Port configuration register for IO GPIO30
#define IOMUX_O_GPIO30PCFG                                           0x0002D07CU

//Port configuration register for IO GPIO31
#define IOMUX_O_GPIO31PCFG                                           0x0002D080U

//Port configuration register for IO GPIO32
#define IOMUX_O_GPIO32PCFG                                           0x0002D084U

//Port configuration register for IO GPIO33
#define IOMUX_O_GPIO33PCFG                                           0x0002D088U

//Port configuration register for IO GPIO34
#define IOMUX_O_GPIO34PCFG                                           0x0002D08CU

//Port configuration register for IO GPIO35
#define IOMUX_O_GPIO35PCFG                                           0x0002D090U

//Port configuration register for IO GPIO36
#define IOMUX_O_GPIO36PCFG                                           0x0002D094U

//Port configuration register for IO GPIO37
#define IOMUX_O_GPIO37PCFG                                           0x0002D098U

//Port configuration register for IO GPIO38
#define IOMUX_O_GPIO38PCFG                                           0x0002D09CU

//Port configuration register for IO GPIO39
#define IOMUX_O_GPIO39PCFG                                           0x0002D0A0U

//Port configuration register for IO GPIO40
#define IOMUX_O_GPIO40PCFG                                           0x0002D0A4U

//Port configuration register for IO GPIO41
#define IOMUX_O_GPIO41PCFG                                           0x0002D0A8U

//Port configuration register for IO GPIO42
#define IOMUX_O_GPIO42PCFG                                           0x0002D0ACU

//Port configuration register for IO GPIO43
#define IOMUX_O_GPIO43PCFG                                           0x0002D0B0U

//Port configuration register for IO GPIO44
#define IOMUX_O_GPIO44PCFG                                           0x0002D0B4U

//The IO Process compensation is used to override the process compensation bits form the eFuse:IO Process: Common for all IOs
#define IOMUX_O_PROCCOMP                                             0x0002D0BCU

//Port configuration register for IO GPIO45
#define IOMUX_O_GPIO45PCFG                                           0x0002D0C0U

//Port configuration register for IO GPIO46
#define IOMUX_O_GPIO46PCFG                                           0x0002D0C4U

//Port configuration register for IO GPIO47
#define IOMUX_O_GPIO47PCFG                                           0x0002D0C8U

//Port configuration register for IO GPIO48
#define IOMUX_O_GPIO48PCFG                                           0x0002D0CCU

//CFG register for IO GPIO45
#define IOMUX_O_GPIO45CFG                                            0x0002E000U

//Pull control register of IO GPIO45
#define IOMUX_O_GPIO45PCTL                                           0x0002E004U

//Control register of IO GPIO45
#define IOMUX_O_GPIO45CTL                                            0x0002E008U

//Event control register for IO GPIO45
#define IOMUX_O_GPIO45ECTL                                           0x0002E00CU

//CFG register for IO GPIO46
#define IOMUX_O_GPIO46CFG                                            0x0002F000U

//Pull control register of IO GPIO46
#define IOMUX_O_GPIO46PCTL                                           0x0002F004U

//Control register of IO GPIO46
#define IOMUX_O_GPIO46CTL                                            0x0002F008U

//Event control register for IO GPIO46
#define IOMUX_O_GPIO46ECTL                                           0x0002F00CU

//CFG register for IO GPIO47
#define IOMUX_O_GPIO47CFG                                            0x00030000U

//Pull control register of IO GPIO47
#define IOMUX_O_GPIO47PCTL                                           0x00030004U

//Control register of IO GPIO47
#define IOMUX_O_GPIO47CTL                                            0x00030008U

//Event control register for IO GPIO47
#define IOMUX_O_GPIO47ECTL                                           0x0003000CU

//CFG register for IO GPIO48
#define IOMUX_O_GPIO48CFG                                            0x00031000U

//Pull control register of IO GPIO48
#define IOMUX_O_GPIO48PCTL                                           0x00031004U

//Control register of IO GPIO48
#define IOMUX_O_GPIO48CTL                                            0x00031008U

//Event control register for IO GPIO48
#define IOMUX_O_GPIO48ECTL                                           0x0003100CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKICFG
    Offset name:         IOMUX_O_SCLKICFG
    Relative address:    0x0
    Description:         CFG register for IO SLOW_CLOCK_IN. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_SCLKICFG_IE                                            0x00000800U
#define IOMUX_SCLKICFG_IE_M                                          0x00000800U
#define IOMUX_SCLKICFG_IE_S                                          11U
#define IOMUX_SCLKICFG_IE_DISABLE                                    0x00000000U
#define IOMUX_SCLKICFG_IE_ENABLE                                     0x00000800U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKIPCTL
    Offset name:         IOMUX_O_SCLKIPCTL
    Relative address:    0x4
    Description:         Pull control register of IO SLOW_CLOCK_IN
                        This register configures the pull control
    Default Value:       0x00000002

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            RSVD:                        RESERVED
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_SCLKIPCTL_CTL_W                                        2U
#define IOMUX_SCLKIPCTL_CTL_M                                        0x00000003U
#define IOMUX_SCLKIPCTL_CTL_S                                        0U
#define IOMUX_SCLKIPCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_SCLKIPCTL_CTL_RSVD                                     0x00000002U
#define IOMUX_SCLKIPCTL_CTL_UP                                       0x00000001U
#define IOMUX_SCLKIPCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_SCLKIPCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_SCLKIPCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_SCLKIPCTL_PULLDWNSTA_S                                 9U
#define IOMUX_SCLKIPCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_SCLKIPCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKICTL
    Offset name:         IOMUX_O_SCLKICTL
    Relative address:    0x8
    Description:         Control register of IO SLOW_CLOCK_IN
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_SCLKICTL_PADVAL                                        0x00000001U
#define IOMUX_SCLKICTL_PADVAL_M                                      0x00000001U
#define IOMUX_SCLKICTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_SCLKICTL_PADVALSYNC                                    0x00000002U
#define IOMUX_SCLKICTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_SCLKICTL_PADVALSYNC_S                                  1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKIECTL
    Offset name:         IOMUX_O_SCLKIECTL
    Relative address:    0xC
    Description:         Event control register for IO SLOW_CLOCK_IN
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_SCLKIECTL_EVTDETCFG_W                                  2U
#define IOMUX_SCLKIECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_SCLKIECTL_EVTDETCFG_S                                  0U
#define IOMUX_SCLKIECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_SCLKIECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_SCLKIECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_SCLKIECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_SCLKIECTL_TRGLVL                                       0x00000004U
#define IOMUX_SCLKIECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_SCLKIECTL_TRGLVL_S                                     2U
#define IOMUX_SCLKIECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_SCLKIECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_SCLKIECTL_CLR                                          0x00000008U
#define IOMUX_SCLKIECTL_CLR_M                                        0x00000008U
#define IOMUX_SCLKIECTL_CLR_S                                        3U
#define IOMUX_SCLKIECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_SCLKIECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTNCFG
    Offset name:         IOMUX_O_LFXTNCFG
    Relative address:    0x1000
    Description:         CFG register for IO LFXTAL_N. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_LFXTNCFG_OUTDISVAL                                     0x00000040U
#define IOMUX_LFXTNCFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_LFXTNCFG_OUTDISVAL_S                                   6U
#define IOMUX_LFXTNCFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_LFXTNCFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_LFXTNCFG_ANASW                                         0x00000100U
#define IOMUX_LFXTNCFG_ANASW_M                                       0x00000100U
#define IOMUX_LFXTNCFG_ANASW_S                                       8U
#define IOMUX_LFXTNCFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_LFXTNCFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_LFXTNCFG_ANASWOVREN                                    0x00000200U
#define IOMUX_LFXTNCFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_LFXTNCFG_ANASWOVREN_S                                  9U
#define IOMUX_LFXTNCFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_LFXTNCFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_LFXTNCFG_IE                                            0x00000800U
#define IOMUX_LFXTNCFG_IE_M                                          0x00000800U
#define IOMUX_LFXTNCFG_IE_S                                          11U
#define IOMUX_LFXTNCFG_IE_DISABLE                                    0x00000000U
#define IOMUX_LFXTNCFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_LFXTNCFG_OUTDIS                                        0x00001000U
#define IOMUX_LFXTNCFG_OUTDIS_M                                      0x00001000U
#define IOMUX_LFXTNCFG_OUTDIS_S                                      12U
#define IOMUX_LFXTNCFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_LFXTNCFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_LFXTNCFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_LFXTNCFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_LFXTNCFG_OUTDISOVREN_S                                 13U
#define IOMUX_LFXTNCFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_LFXTNCFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_LFXTNCFG_IOSTR                                         0x00004000U
#define IOMUX_LFXTNCFG_IOSTR_M                                       0x00004000U
#define IOMUX_LFXTNCFG_IOSTR_S                                       14U
#define IOMUX_LFXTNCFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_LFXTNCFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTNPCTL
    Offset name:         IOMUX_O_LFXTNPCTL
    Relative address:    0x1004
    Description:         Pull control register of IO LFXTAL_N
                        This register configures the pull control
    Default Value:       0x00000002

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_LFXTNPCTL_CTL_W                                        2U
#define IOMUX_LFXTNPCTL_CTL_M                                        0x00000003U
#define IOMUX_LFXTNPCTL_CTL_S                                        0U
#define IOMUX_LFXTNPCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_LFXTNPCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_LFXTNPCTL_CTL_UP                                       0x00000001U
#define IOMUX_LFXTNPCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_LFXTNPCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_LFXTNPCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_LFXTNPCTL_PULLUPSTA_S                                  8U
#define IOMUX_LFXTNPCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_LFXTNPCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_LFXTNPCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_LFXTNPCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_LFXTNPCTL_PULLDWNSTA_S                                 9U
#define IOMUX_LFXTNPCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_LFXTNPCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTNCTL
    Offset name:         IOMUX_O_LFXTNCTL
    Relative address:    0x1008
    Description:         Control register of IO LFXTAL_N
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_LFXTNCTL_PADVAL                                        0x00000001U
#define IOMUX_LFXTNCTL_PADVAL_M                                      0x00000001U
#define IOMUX_LFXTNCTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_LFXTNCTL_PADVALSYNC                                    0x00000002U
#define IOMUX_LFXTNCTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_LFXTNCTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_LFXTNCTL_OUT                                           0x00000100U
#define IOMUX_LFXTNCTL_OUT_M                                         0x00000100U
#define IOMUX_LFXTNCTL_OUT_S                                         8U
#define IOMUX_LFXTNCTL_OUT_LOW                                       0x00000000U
#define IOMUX_LFXTNCTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_LFXTNCTL_OUTOVREN                                      0x00000200U
#define IOMUX_LFXTNCTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_LFXTNCTL_OUTOVREN_S                                    9U
#define IOMUX_LFXTNCTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_LFXTNCTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTNECTL
    Offset name:         IOMUX_O_LFXTNECTL
    Relative address:    0x100C
    Description:         Event control register for IO LFXTAL_N
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_LFXTNECTL_EVTDETCFG_W                                  2U
#define IOMUX_LFXTNECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_LFXTNECTL_EVTDETCFG_S                                  0U
#define IOMUX_LFXTNECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_LFXTNECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_LFXTNECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_LFXTNECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_LFXTNECTL_TRGLVL                                       0x00000004U
#define IOMUX_LFXTNECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_LFXTNECTL_TRGLVL_S                                     2U
#define IOMUX_LFXTNECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_LFXTNECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_LFXTNECTL_CLR                                          0x00000008U
#define IOMUX_LFXTNECTL_CLR_M                                        0x00000008U
#define IOMUX_LFXTNECTL_CLR_S                                        3U
#define IOMUX_LFXTNECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_LFXTNECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO2CFG
    Offset name:         IOMUX_O_GPIO2CFG
    Relative address:    0x2000
    Description:         CFG register for IO GPIO2. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO2CFG_OUTDISVAL                                     0x00000040U
#define IOMUX_GPIO2CFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_GPIO2CFG_OUTDISVAL_S                                   6U
#define IOMUX_GPIO2CFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_GPIO2CFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO2CFG_ANASW                                         0x00000100U
#define IOMUX_GPIO2CFG_ANASW_M                                       0x00000100U
#define IOMUX_GPIO2CFG_ANASW_S                                       8U
#define IOMUX_GPIO2CFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_GPIO2CFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO2CFG_ANASWOVREN                                    0x00000200U
#define IOMUX_GPIO2CFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_GPIO2CFG_ANASWOVREN_S                                  9U
#define IOMUX_GPIO2CFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_GPIO2CFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO2CFG_IE                                            0x00000800U
#define IOMUX_GPIO2CFG_IE_M                                          0x00000800U
#define IOMUX_GPIO2CFG_IE_S                                          11U
#define IOMUX_GPIO2CFG_IE_DISABLE                                    0x00000000U
#define IOMUX_GPIO2CFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO2CFG_OUTDIS                                        0x00001000U
#define IOMUX_GPIO2CFG_OUTDIS_M                                      0x00001000U
#define IOMUX_GPIO2CFG_OUTDIS_S                                      12U
#define IOMUX_GPIO2CFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_GPIO2CFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO2CFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_GPIO2CFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_GPIO2CFG_OUTDISOVREN_S                                 13U
#define IOMUX_GPIO2CFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO2CFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO2CFG_IOSTR                                         0x00004000U
#define IOMUX_GPIO2CFG_IOSTR_M                                       0x00004000U
#define IOMUX_GPIO2CFG_IOSTR_S                                       14U
#define IOMUX_GPIO2CFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_GPIO2CFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO2PCTL
    Offset name:         IOMUX_O_GPIO2PCTL
    Relative address:    0x2004
    Description:         Pull control register of IO GPIO2
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO2PCTL_CTL_W                                        2U
#define IOMUX_GPIO2PCTL_CTL_M                                        0x00000003U
#define IOMUX_GPIO2PCTL_CTL_S                                        0U
#define IOMUX_GPIO2PCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_GPIO2PCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_GPIO2PCTL_CTL_UP                                       0x00000001U
#define IOMUX_GPIO2PCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO2PCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_GPIO2PCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_GPIO2PCTL_PULLUPSTA_S                                  8U
#define IOMUX_GPIO2PCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_GPIO2PCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO2PCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_GPIO2PCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_GPIO2PCTL_PULLDWNSTA_S                                 9U
#define IOMUX_GPIO2PCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO2PCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO2CTL
    Offset name:         IOMUX_O_GPIO2CTL
    Relative address:    0x2008
    Description:         Control register of IO GPIO2
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO2CTL_PADVAL                                        0x00000001U
#define IOMUX_GPIO2CTL_PADVAL_M                                      0x00000001U
#define IOMUX_GPIO2CTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO2CTL_PADVALSYNC                                    0x00000002U
#define IOMUX_GPIO2CTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_GPIO2CTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO2CTL_OUT                                           0x00000100U
#define IOMUX_GPIO2CTL_OUT_M                                         0x00000100U
#define IOMUX_GPIO2CTL_OUT_S                                         8U
#define IOMUX_GPIO2CTL_OUT_LOW                                       0x00000000U
#define IOMUX_GPIO2CTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO2CTL_OUTOVREN                                      0x00000200U
#define IOMUX_GPIO2CTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_GPIO2CTL_OUTOVREN_S                                    9U
#define IOMUX_GPIO2CTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_GPIO2CTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO2ECTL
    Offset name:         IOMUX_O_GPIO2ECTL
    Relative address:    0x200C
    Description:         Event control register for IO GPIO2
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO2ECTL_EVTDETCFG_W                                  2U
#define IOMUX_GPIO2ECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_GPIO2ECTL_EVTDETCFG_S                                  0U
#define IOMUX_GPIO2ECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_GPIO2ECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_GPIO2ECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_GPIO2ECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO2ECTL_TRGLVL                                       0x00000004U
#define IOMUX_GPIO2ECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_GPIO2ECTL_TRGLVL_S                                     2U
#define IOMUX_GPIO2ECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_GPIO2ECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO2ECTL_CLR                                          0x00000008U
#define IOMUX_GPIO2ECTL_CLR_M                                        0x00000008U
#define IOMUX_GPIO2ECTL_CLR_S                                        3U
#define IOMUX_GPIO2ECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_GPIO2ECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO3CFG
    Offset name:         IOMUX_O_GPIO3CFG
    Relative address:    0x3000
    Description:         CFG register for IO GPIO3. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO3CFG_OUTDISVAL                                     0x00000040U
#define IOMUX_GPIO3CFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_GPIO3CFG_OUTDISVAL_S                                   6U
#define IOMUX_GPIO3CFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_GPIO3CFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO3CFG_ANASW                                         0x00000100U
#define IOMUX_GPIO3CFG_ANASW_M                                       0x00000100U
#define IOMUX_GPIO3CFG_ANASW_S                                       8U
#define IOMUX_GPIO3CFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_GPIO3CFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO3CFG_ANASWOVREN                                    0x00000200U
#define IOMUX_GPIO3CFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_GPIO3CFG_ANASWOVREN_S                                  9U
#define IOMUX_GPIO3CFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_GPIO3CFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO3CFG_IE                                            0x00000800U
#define IOMUX_GPIO3CFG_IE_M                                          0x00000800U
#define IOMUX_GPIO3CFG_IE_S                                          11U
#define IOMUX_GPIO3CFG_IE_DISABLE                                    0x00000000U
#define IOMUX_GPIO3CFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO3CFG_OUTDIS                                        0x00001000U
#define IOMUX_GPIO3CFG_OUTDIS_M                                      0x00001000U
#define IOMUX_GPIO3CFG_OUTDIS_S                                      12U
#define IOMUX_GPIO3CFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_GPIO3CFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO3CFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_GPIO3CFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_GPIO3CFG_OUTDISOVREN_S                                 13U
#define IOMUX_GPIO3CFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO3CFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO3CFG_IOSTR                                         0x00004000U
#define IOMUX_GPIO3CFG_IOSTR_M                                       0x00004000U
#define IOMUX_GPIO3CFG_IOSTR_S                                       14U
#define IOMUX_GPIO3CFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_GPIO3CFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO3PCTL
    Offset name:         IOMUX_O_GPIO3PCTL
    Relative address:    0x3004
    Description:         Pull control register of IO GPIO3
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO3PCTL_CTL_W                                        2U
#define IOMUX_GPIO3PCTL_CTL_M                                        0x00000003U
#define IOMUX_GPIO3PCTL_CTL_S                                        0U
#define IOMUX_GPIO3PCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_GPIO3PCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_GPIO3PCTL_CTL_UP                                       0x00000001U
#define IOMUX_GPIO3PCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO3PCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_GPIO3PCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_GPIO3PCTL_PULLUPSTA_S                                  8U
#define IOMUX_GPIO3PCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_GPIO3PCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO3PCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_GPIO3PCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_GPIO3PCTL_PULLDWNSTA_S                                 9U
#define IOMUX_GPIO3PCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO3PCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO3CTL
    Offset name:         IOMUX_O_GPIO3CTL
    Relative address:    0x3008
    Description:         Control register of IO GPIO3
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO3CTL_PADVAL                                        0x00000001U
#define IOMUX_GPIO3CTL_PADVAL_M                                      0x00000001U
#define IOMUX_GPIO3CTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO3CTL_PADVALSYNC                                    0x00000002U
#define IOMUX_GPIO3CTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_GPIO3CTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO3CTL_OUT                                           0x00000100U
#define IOMUX_GPIO3CTL_OUT_M                                         0x00000100U
#define IOMUX_GPIO3CTL_OUT_S                                         8U
#define IOMUX_GPIO3CTL_OUT_LOW                                       0x00000000U
#define IOMUX_GPIO3CTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO3CTL_OUTOVREN                                      0x00000200U
#define IOMUX_GPIO3CTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_GPIO3CTL_OUTOVREN_S                                    9U
#define IOMUX_GPIO3CTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_GPIO3CTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO3ECTL
    Offset name:         IOMUX_O_GPIO3ECTL
    Relative address:    0x300C
    Description:         Event control register for IO GPIO3
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO3ECTL_EVTDETCFG_W                                  2U
#define IOMUX_GPIO3ECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_GPIO3ECTL_EVTDETCFG_S                                  0U
#define IOMUX_GPIO3ECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_GPIO3ECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_GPIO3ECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_GPIO3ECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO3ECTL_TRGLVL                                       0x00000004U
#define IOMUX_GPIO3ECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_GPIO3ECTL_TRGLVL_S                                     2U
#define IOMUX_GPIO3ECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_GPIO3ECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO3ECTL_CLR                                          0x00000008U
#define IOMUX_GPIO3ECTL_CLR_M                                        0x00000008U
#define IOMUX_GPIO3ECTL_CLR_S                                        3U
#define IOMUX_GPIO3ECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_GPIO3ECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO4CFG
    Offset name:         IOMUX_O_GPIO4CFG
    Relative address:    0x4000
    Description:         CFG register for IO GPIO4. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO4CFG_OUTDISVAL                                     0x00000040U
#define IOMUX_GPIO4CFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_GPIO4CFG_OUTDISVAL_S                                   6U
#define IOMUX_GPIO4CFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_GPIO4CFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO4CFG_ANASW                                         0x00000100U
#define IOMUX_GPIO4CFG_ANASW_M                                       0x00000100U
#define IOMUX_GPIO4CFG_ANASW_S                                       8U
#define IOMUX_GPIO4CFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_GPIO4CFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO4CFG_ANASWOVREN                                    0x00000200U
#define IOMUX_GPIO4CFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_GPIO4CFG_ANASWOVREN_S                                  9U
#define IOMUX_GPIO4CFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_GPIO4CFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO4CFG_IE                                            0x00000800U
#define IOMUX_GPIO4CFG_IE_M                                          0x00000800U
#define IOMUX_GPIO4CFG_IE_S                                          11U
#define IOMUX_GPIO4CFG_IE_DISABLE                                    0x00000000U
#define IOMUX_GPIO4CFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO4CFG_OUTDIS                                        0x00001000U
#define IOMUX_GPIO4CFG_OUTDIS_M                                      0x00001000U
#define IOMUX_GPIO4CFG_OUTDIS_S                                      12U
#define IOMUX_GPIO4CFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_GPIO4CFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO4CFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_GPIO4CFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_GPIO4CFG_OUTDISOVREN_S                                 13U
#define IOMUX_GPIO4CFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO4CFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO4CFG_IOSTR                                         0x00004000U
#define IOMUX_GPIO4CFG_IOSTR_M                                       0x00004000U
#define IOMUX_GPIO4CFG_IOSTR_S                                       14U
#define IOMUX_GPIO4CFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_GPIO4CFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO4PCTL
    Offset name:         IOMUX_O_GPIO4PCTL
    Relative address:    0x4004
    Description:         Pull control register of IO GPIO4
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO4PCTL_CTL_W                                        2U
#define IOMUX_GPIO4PCTL_CTL_M                                        0x00000003U
#define IOMUX_GPIO4PCTL_CTL_S                                        0U
#define IOMUX_GPIO4PCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_GPIO4PCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_GPIO4PCTL_CTL_UP                                       0x00000001U
#define IOMUX_GPIO4PCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO4PCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_GPIO4PCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_GPIO4PCTL_PULLUPSTA_S                                  8U
#define IOMUX_GPIO4PCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_GPIO4PCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO4PCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_GPIO4PCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_GPIO4PCTL_PULLDWNSTA_S                                 9U
#define IOMUX_GPIO4PCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO4PCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO4CTL
    Offset name:         IOMUX_O_GPIO4CTL
    Relative address:    0x4008
    Description:         Control register of IO GPIO4
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO4CTL_PADVAL                                        0x00000001U
#define IOMUX_GPIO4CTL_PADVAL_M                                      0x00000001U
#define IOMUX_GPIO4CTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO4CTL_PADVALSYNC                                    0x00000002U
#define IOMUX_GPIO4CTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_GPIO4CTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO4CTL_OUT                                           0x00000100U
#define IOMUX_GPIO4CTL_OUT_M                                         0x00000100U
#define IOMUX_GPIO4CTL_OUT_S                                         8U
#define IOMUX_GPIO4CTL_OUT_LOW                                       0x00000000U
#define IOMUX_GPIO4CTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO4CTL_OUTOVREN                                      0x00000200U
#define IOMUX_GPIO4CTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_GPIO4CTL_OUTOVREN_S                                    9U
#define IOMUX_GPIO4CTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_GPIO4CTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO4ECTL
    Offset name:         IOMUX_O_GPIO4ECTL
    Relative address:    0x400C
    Description:         Event control register for IO GPIO4
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO4ECTL_EVTDETCFG_W                                  2U
#define IOMUX_GPIO4ECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_GPIO4ECTL_EVTDETCFG_S                                  0U
#define IOMUX_GPIO4ECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_GPIO4ECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_GPIO4ECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_GPIO4ECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO4ECTL_TRGLVL                                       0x00000004U
#define IOMUX_GPIO4ECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_GPIO4ECTL_TRGLVL_S                                     2U
#define IOMUX_GPIO4ECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_GPIO4ECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO4ECTL_CLR                                          0x00000008U
#define IOMUX_GPIO4ECTL_CLR_M                                        0x00000008U
#define IOMUX_GPIO4ECTL_CLR_S                                        3U
#define IOMUX_GPIO4ECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_GPIO4ECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO5CFG
    Offset name:         IOMUX_O_GPIO5CFG
    Relative address:    0x5000
    Description:         CFG register for IO GPIO5. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO5CFG_OUTDISVAL                                     0x00000040U
#define IOMUX_GPIO5CFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_GPIO5CFG_OUTDISVAL_S                                   6U
#define IOMUX_GPIO5CFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_GPIO5CFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO5CFG_ANASW                                         0x00000100U
#define IOMUX_GPIO5CFG_ANASW_M                                       0x00000100U
#define IOMUX_GPIO5CFG_ANASW_S                                       8U
#define IOMUX_GPIO5CFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_GPIO5CFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO5CFG_ANASWOVREN                                    0x00000200U
#define IOMUX_GPIO5CFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_GPIO5CFG_ANASWOVREN_S                                  9U
#define IOMUX_GPIO5CFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_GPIO5CFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO5CFG_IE                                            0x00000800U
#define IOMUX_GPIO5CFG_IE_M                                          0x00000800U
#define IOMUX_GPIO5CFG_IE_S                                          11U
#define IOMUX_GPIO5CFG_IE_DISABLE                                    0x00000000U
#define IOMUX_GPIO5CFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO5CFG_OUTDIS                                        0x00001000U
#define IOMUX_GPIO5CFG_OUTDIS_M                                      0x00001000U
#define IOMUX_GPIO5CFG_OUTDIS_S                                      12U
#define IOMUX_GPIO5CFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_GPIO5CFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO5CFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_GPIO5CFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_GPIO5CFG_OUTDISOVREN_S                                 13U
#define IOMUX_GPIO5CFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO5CFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO5CFG_IOSTR                                         0x00004000U
#define IOMUX_GPIO5CFG_IOSTR_M                                       0x00004000U
#define IOMUX_GPIO5CFG_IOSTR_S                                       14U
#define IOMUX_GPIO5CFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_GPIO5CFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO5PCTL
    Offset name:         IOMUX_O_GPIO5PCTL
    Relative address:    0x5004
    Description:         Pull control register of IO GPIO5
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO5PCTL_CTL_W                                        2U
#define IOMUX_GPIO5PCTL_CTL_M                                        0x00000003U
#define IOMUX_GPIO5PCTL_CTL_S                                        0U
#define IOMUX_GPIO5PCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_GPIO5PCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_GPIO5PCTL_CTL_UP                                       0x00000001U
#define IOMUX_GPIO5PCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO5PCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_GPIO5PCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_GPIO5PCTL_PULLUPSTA_S                                  8U
#define IOMUX_GPIO5PCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_GPIO5PCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO5PCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_GPIO5PCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_GPIO5PCTL_PULLDWNSTA_S                                 9U
#define IOMUX_GPIO5PCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO5PCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO5CTL
    Offset name:         IOMUX_O_GPIO5CTL
    Relative address:    0x5008
    Description:         Control register of IO GPIO5
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO5CTL_PADVAL                                        0x00000001U
#define IOMUX_GPIO5CTL_PADVAL_M                                      0x00000001U
#define IOMUX_GPIO5CTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO5CTL_PADVALSYNC                                    0x00000002U
#define IOMUX_GPIO5CTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_GPIO5CTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO5CTL_OUT                                           0x00000100U
#define IOMUX_GPIO5CTL_OUT_M                                         0x00000100U
#define IOMUX_GPIO5CTL_OUT_S                                         8U
#define IOMUX_GPIO5CTL_OUT_LOW                                       0x00000000U
#define IOMUX_GPIO5CTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO5CTL_OUTOVREN                                      0x00000200U
#define IOMUX_GPIO5CTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_GPIO5CTL_OUTOVREN_S                                    9U
#define IOMUX_GPIO5CTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_GPIO5CTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO5ECTL
    Offset name:         IOMUX_O_GPIO5ECTL
    Relative address:    0x500C
    Description:         Event control register for IO GPIO5
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO5ECTL_EVTDETCFG_W                                  2U
#define IOMUX_GPIO5ECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_GPIO5ECTL_EVTDETCFG_S                                  0U
#define IOMUX_GPIO5ECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_GPIO5ECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_GPIO5ECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_GPIO5ECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO5ECTL_TRGLVL                                       0x00000004U
#define IOMUX_GPIO5ECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_GPIO5ECTL_TRGLVL_S                                     2U
#define IOMUX_GPIO5ECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_GPIO5ECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO5ECTL_CLR                                          0x00000008U
#define IOMUX_GPIO5ECTL_CLR_M                                        0x00000008U
#define IOMUX_GPIO5ECTL_CLR_S                                        3U
#define IOMUX_GPIO5ECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_GPIO5ECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO6CFG
    Offset name:         IOMUX_O_GPIO6CFG
    Relative address:    0x6000
    Description:         CFG register for IO GPIO6. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO6CFG_OUTDISVAL                                     0x00000040U
#define IOMUX_GPIO6CFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_GPIO6CFG_OUTDISVAL_S                                   6U
#define IOMUX_GPIO6CFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_GPIO6CFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO6CFG_ANASW                                         0x00000100U
#define IOMUX_GPIO6CFG_ANASW_M                                       0x00000100U
#define IOMUX_GPIO6CFG_ANASW_S                                       8U
#define IOMUX_GPIO6CFG_ANASW_DISABLE                                 0x00000000U
#define IOMUX_GPIO6CFG_ANASW_ENABLE                                  0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO6CFG_ANASWOVREN                                    0x00000200U
#define IOMUX_GPIO6CFG_ANASWOVREN_M                                  0x00000200U
#define IOMUX_GPIO6CFG_ANASWOVREN_S                                  9U
#define IOMUX_GPIO6CFG_ANASWOVREN_DISABLE                            0x00000000U
#define IOMUX_GPIO6CFG_ANASWOVREN_ENABLE                             0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO6CFG_IE                                            0x00000800U
#define IOMUX_GPIO6CFG_IE_M                                          0x00000800U
#define IOMUX_GPIO6CFG_IE_S                                          11U
#define IOMUX_GPIO6CFG_IE_DISABLE                                    0x00000000U
#define IOMUX_GPIO6CFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO6CFG_OUTDIS                                        0x00001000U
#define IOMUX_GPIO6CFG_OUTDIS_M                                      0x00001000U
#define IOMUX_GPIO6CFG_OUTDIS_S                                      12U
#define IOMUX_GPIO6CFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_GPIO6CFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO6CFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_GPIO6CFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_GPIO6CFG_OUTDISOVREN_S                                 13U
#define IOMUX_GPIO6CFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO6CFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO6CFG_IOSTR                                         0x00004000U
#define IOMUX_GPIO6CFG_IOSTR_M                                       0x00004000U
#define IOMUX_GPIO6CFG_IOSTR_S                                       14U
#define IOMUX_GPIO6CFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_GPIO6CFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO6PCTL
    Offset name:         IOMUX_O_GPIO6PCTL
    Relative address:    0x6004
    Description:         Pull control register of IO GPIO6
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO6PCTL_CTL_W                                        2U
#define IOMUX_GPIO6PCTL_CTL_M                                        0x00000003U
#define IOMUX_GPIO6PCTL_CTL_S                                        0U
#define IOMUX_GPIO6PCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_GPIO6PCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_GPIO6PCTL_CTL_UP                                       0x00000001U
#define IOMUX_GPIO6PCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO6PCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_GPIO6PCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_GPIO6PCTL_PULLUPSTA_S                                  8U
#define IOMUX_GPIO6PCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_GPIO6PCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO6PCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_GPIO6PCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_GPIO6PCTL_PULLDWNSTA_S                                 9U
#define IOMUX_GPIO6PCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO6PCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO6CTL
    Offset name:         IOMUX_O_GPIO6CTL
    Relative address:    0x6008
    Description:         Control register of IO GPIO6
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO6CTL_PADVAL                                        0x00000001U
#define IOMUX_GPIO6CTL_PADVAL_M                                      0x00000001U
#define IOMUX_GPIO6CTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO6CTL_PADVALSYNC                                    0x00000002U
#define IOMUX_GPIO6CTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_GPIO6CTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO6CTL_OUT                                           0x00000100U
#define IOMUX_GPIO6CTL_OUT_M                                         0x00000100U
#define IOMUX_GPIO6CTL_OUT_S                                         8U
#define IOMUX_GPIO6CTL_OUT_LOW                                       0x00000000U
#define IOMUX_GPIO6CTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO6CTL_OUTOVREN                                      0x00000200U
#define IOMUX_GPIO6CTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_GPIO6CTL_OUTOVREN_S                                    9U
#define IOMUX_GPIO6CTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_GPIO6CTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO6ECTL
    Offset name:         IOMUX_O_GPIO6ECTL
    Relative address:    0x600C
    Description:         Event control register for IO GPIO6
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO6ECTL_EVTDETCFG_W                                  2U
#define IOMUX_GPIO6ECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_GPIO6ECTL_EVTDETCFG_S                                  0U
#define IOMUX_GPIO6ECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_GPIO6ECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_GPIO6ECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_GPIO6ECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO6ECTL_TRGLVL                                       0x00000004U
#define IOMUX_GPIO6ECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_GPIO6ECTL_TRGLVL_S                                     2U
#define IOMUX_GPIO6ECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_GPIO6ECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO6ECTL_CLR                                          0x00000008U
#define IOMUX_GPIO6ECTL_CLR_M                                        0x00000008U
#define IOMUX_GPIO6ECTL_CLR_S                                        3U
#define IOMUX_GPIO6ECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_GPIO6ECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDIOCFG
    Offset name:         IOMUX_O_SWDIOCFG
    Relative address:    0x7000
    Description:         CFG register for IO SWDIO. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_SWDIOCFG_OUTDISVAL                                     0x00000040U
#define IOMUX_SWDIOCFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_SWDIOCFG_OUTDISVAL_S                                   6U
#define IOMUX_SWDIOCFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_SWDIOCFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_SWDIOCFG_IE                                            0x00000800U
#define IOMUX_SWDIOCFG_IE_M                                          0x00000800U
#define IOMUX_SWDIOCFG_IE_S                                          11U
#define IOMUX_SWDIOCFG_IE_DISABLE                                    0x00000000U
#define IOMUX_SWDIOCFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_SWDIOCFG_OUTDIS                                        0x00001000U
#define IOMUX_SWDIOCFG_OUTDIS_M                                      0x00001000U
#define IOMUX_SWDIOCFG_OUTDIS_S                                      12U
#define IOMUX_SWDIOCFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_SWDIOCFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_SWDIOCFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_SWDIOCFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_SWDIOCFG_OUTDISOVREN_S                                 13U
#define IOMUX_SWDIOCFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_SWDIOCFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_SWDIOCFG_IOSTR                                         0x00004000U
#define IOMUX_SWDIOCFG_IOSTR_M                                       0x00004000U
#define IOMUX_SWDIOCFG_IOSTR_S                                       14U
#define IOMUX_SWDIOCFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_SWDIOCFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDIOPCTL
    Offset name:         IOMUX_O_SWDIOPCTL
    Relative address:    0x7004
    Description:         Pull control register of IO SWDIO
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_SWDIOPCTL_CTL_W                                        2U
#define IOMUX_SWDIOPCTL_CTL_M                                        0x00000003U
#define IOMUX_SWDIOPCTL_CTL_S                                        0U
#define IOMUX_SWDIOPCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_SWDIOPCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_SWDIOPCTL_CTL_UP                                       0x00000001U
#define IOMUX_SWDIOPCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_SWDIOPCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_SWDIOPCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_SWDIOPCTL_PULLUPSTA_S                                  8U
#define IOMUX_SWDIOPCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_SWDIOPCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_SWDIOPCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_SWDIOPCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_SWDIOPCTL_PULLDWNSTA_S                                 9U
#define IOMUX_SWDIOPCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_SWDIOPCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDIOCTL
    Offset name:         IOMUX_O_SWDIOCTL
    Relative address:    0x7008
    Description:         Control register of IO SWDIO
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_SWDIOCTL_PADVAL                                        0x00000001U
#define IOMUX_SWDIOCTL_PADVAL_M                                      0x00000001U
#define IOMUX_SWDIOCTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_SWDIOCTL_PADVALSYNC                                    0x00000002U
#define IOMUX_SWDIOCTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_SWDIOCTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_SWDIOCTL_OUT                                           0x00000100U
#define IOMUX_SWDIOCTL_OUT_M                                         0x00000100U
#define IOMUX_SWDIOCTL_OUT_S                                         8U
#define IOMUX_SWDIOCTL_OUT_LOW                                       0x00000000U
#define IOMUX_SWDIOCTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_SWDIOCTL_OUTOVREN                                      0x00000200U
#define IOMUX_SWDIOCTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_SWDIOCTL_OUTOVREN_S                                    9U
#define IOMUX_SWDIOCTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_SWDIOCTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDIOECTL
    Offset name:         IOMUX_O_SWDIOECTL
    Relative address:    0x700C
    Description:         Event control register for IO SWDIO
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_SWDIOECTL_EVTDETCFG_W                                  2U
#define IOMUX_SWDIOECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_SWDIOECTL_EVTDETCFG_S                                  0U
#define IOMUX_SWDIOECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_SWDIOECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_SWDIOECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_SWDIOECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_SWDIOECTL_TRGLVL                                       0x00000004U
#define IOMUX_SWDIOECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_SWDIOECTL_TRGLVL_S                                     2U
#define IOMUX_SWDIOECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_SWDIOECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_SWDIOECTL_CLR                                          0x00000008U
#define IOMUX_SWDIOECTL_CLR_M                                        0x00000008U
#define IOMUX_SWDIOECTL_CLR_S                                        3U
#define IOMUX_SWDIOECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_SWDIOECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCLKCFG
    Offset name:         IOMUX_O_SWCLKCFG
    Relative address:    0x8000
    Description:         CFG register for IO SWCLK. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_SWCLKCFG_OUTDISVAL                                     0x00000040U
#define IOMUX_SWCLKCFG_OUTDISVAL_M                                   0x00000040U
#define IOMUX_SWCLKCFG_OUTDISVAL_S                                   6U
#define IOMUX_SWCLKCFG_OUTDISVAL_ENABLED                             0x00000000U
#define IOMUX_SWCLKCFG_OUTDISVAL_DISABLED                            0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_SWCLKCFG_IE                                            0x00000800U
#define IOMUX_SWCLKCFG_IE_M                                          0x00000800U
#define IOMUX_SWCLKCFG_IE_S                                          11U
#define IOMUX_SWCLKCFG_IE_DISABLE                                    0x00000000U
#define IOMUX_SWCLKCFG_IE_ENABLE                                     0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_SWCLKCFG_OUTDIS                                        0x00001000U
#define IOMUX_SWCLKCFG_OUTDIS_M                                      0x00001000U
#define IOMUX_SWCLKCFG_OUTDIS_S                                      12U
#define IOMUX_SWCLKCFG_OUTDIS_DISABLE                                0x00001000U
#define IOMUX_SWCLKCFG_OUTDIS_ENABLE                                 0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_SWCLKCFG_OUTDISOVREN                                   0x00002000U
#define IOMUX_SWCLKCFG_OUTDISOVREN_M                                 0x00002000U
#define IOMUX_SWCLKCFG_OUTDISOVREN_S                                 13U
#define IOMUX_SWCLKCFG_OUTDISOVREN_DISABLE                           0x00000000U
#define IOMUX_SWCLKCFG_OUTDISOVREN_ENABLE                            0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_SWCLKCFG_IOSTR                                         0x00004000U
#define IOMUX_SWCLKCFG_IOSTR_M                                       0x00004000U
#define IOMUX_SWCLKCFG_IOSTR_S                                       14U
#define IOMUX_SWCLKCFG_IOSTR_LOW                                     0x00000000U
#define IOMUX_SWCLKCFG_IOSTR_HIGH                                    0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCLKPCTL
    Offset name:         IOMUX_O_SWCLKPCTL
    Relative address:    0x8004
    Description:         Pull control register of IO SWCLK
                        This register configures the pull control
    Default Value:       0x00000002

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_SWCLKPCTL_CTL_W                                        2U
#define IOMUX_SWCLKPCTL_CTL_M                                        0x00000003U
#define IOMUX_SWCLKPCTL_CTL_S                                        0U
#define IOMUX_SWCLKPCTL_CTL_IPCTRL                                   0x00000000U
#define IOMUX_SWCLKPCTL_CTL_DOWN                                     0x00000002U
#define IOMUX_SWCLKPCTL_CTL_UP                                       0x00000001U
#define IOMUX_SWCLKPCTL_CTL_DISABLE                                  0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_SWCLKPCTL_PULLUPSTA                                    0x00000100U
#define IOMUX_SWCLKPCTL_PULLUPSTA_M                                  0x00000100U
#define IOMUX_SWCLKPCTL_PULLUPSTA_S                                  8U
#define IOMUX_SWCLKPCTL_PULLUPSTA_DISABLED                           0x00000000U
#define IOMUX_SWCLKPCTL_PULLUPSTA_ENABLED                            0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_SWCLKPCTL_PULLDWNSTA                                   0x00000200U
#define IOMUX_SWCLKPCTL_PULLDWNSTA_M                                 0x00000200U
#define IOMUX_SWCLKPCTL_PULLDWNSTA_S                                 9U
#define IOMUX_SWCLKPCTL_PULLDWNSTA_DISABLED                          0x00000000U
#define IOMUX_SWCLKPCTL_PULLDWNSTA_ENABLED                           0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCLKCTL
    Offset name:         IOMUX_O_SWCLKCTL
    Relative address:    0x8008
    Description:         Control register of IO SWCLK
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_SWCLKCTL_PADVAL                                        0x00000001U
#define IOMUX_SWCLKCTL_PADVAL_M                                      0x00000001U
#define IOMUX_SWCLKCTL_PADVAL_S                                      0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_SWCLKCTL_PADVALSYNC                                    0x00000002U
#define IOMUX_SWCLKCTL_PADVALSYNC_M                                  0x00000002U
#define IOMUX_SWCLKCTL_PADVALSYNC_S                                  1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_SWCLKCTL_OUT                                           0x00000100U
#define IOMUX_SWCLKCTL_OUT_M                                         0x00000100U
#define IOMUX_SWCLKCTL_OUT_S                                         8U
#define IOMUX_SWCLKCTL_OUT_LOW                                       0x00000000U
#define IOMUX_SWCLKCTL_OUT_HIGH                                      0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_SWCLKCTL_OUTOVREN                                      0x00000200U
#define IOMUX_SWCLKCTL_OUTOVREN_M                                    0x00000200U
#define IOMUX_SWCLKCTL_OUTOVREN_S                                    9U
#define IOMUX_SWCLKCTL_OUTOVREN_DISABLE                              0x00000000U
#define IOMUX_SWCLKCTL_OUTOVREN_ENABLE                               0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCLKECTL
    Offset name:         IOMUX_O_SWCLKECTL
    Relative address:    0x800C
    Description:         Event control register for IO SWCLK
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_SWCLKECTL_EVTDETCFG_W                                  2U
#define IOMUX_SWCLKECTL_EVTDETCFG_M                                  0x00000003U
#define IOMUX_SWCLKECTL_EVTDETCFG_S                                  0U
#define IOMUX_SWCLKECTL_EVTDETCFG_MASK                               0x00000000U
#define IOMUX_SWCLKECTL_EVTDETCFG_POS_EDGE                           0x00000001U
#define IOMUX_SWCLKECTL_EVTDETCFG_NEG_EDGE                           0x00000002U
#define IOMUX_SWCLKECTL_EVTDETCFG_LEVEL                              0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_SWCLKECTL_TRGLVL                                       0x00000004U
#define IOMUX_SWCLKECTL_TRGLVL_M                                     0x00000004U
#define IOMUX_SWCLKECTL_TRGLVL_S                                     2U
#define IOMUX_SWCLKECTL_TRGLVL_HIGH                                  0x00000000U
#define IOMUX_SWCLKECTL_TRGLVL_LOW                                   0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_SWCLKECTL_CLR                                          0x00000008U
#define IOMUX_SWCLKECTL_CLR_M                                        0x00000008U
#define IOMUX_SWCLKECTL_CLR_S                                        3U
#define IOMUX_SWCLKECTL_CLR_NOEFF                                    0x00000000U
#define IOMUX_SWCLKECTL_CLR_CLEAR                                    0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGGERCFG
    Offset name:         IOMUX_O_LOGGERCFG
    Relative address:    0x9000
    Description:         CFG register for IO LOGGER. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_LOGGERCFG_OUTDISVAL                                    0x00000040U
#define IOMUX_LOGGERCFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_LOGGERCFG_OUTDISVAL_S                                  6U
#define IOMUX_LOGGERCFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_LOGGERCFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_LOGGERCFG_IE                                           0x00000800U
#define IOMUX_LOGGERCFG_IE_M                                         0x00000800U
#define IOMUX_LOGGERCFG_IE_S                                         11U
#define IOMUX_LOGGERCFG_IE_DISABLE                                   0x00000000U
#define IOMUX_LOGGERCFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_LOGGERCFG_OUTDIS                                       0x00001000U
#define IOMUX_LOGGERCFG_OUTDIS_M                                     0x00001000U
#define IOMUX_LOGGERCFG_OUTDIS_S                                     12U
#define IOMUX_LOGGERCFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_LOGGERCFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_LOGGERCFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_LOGGERCFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_LOGGERCFG_OUTDISOVREN_S                                13U
#define IOMUX_LOGGERCFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_LOGGERCFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_LOGGERCFG_IOSTR                                        0x00004000U
#define IOMUX_LOGGERCFG_IOSTR_M                                      0x00004000U
#define IOMUX_LOGGERCFG_IOSTR_S                                      14U
#define IOMUX_LOGGERCFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_LOGGERCFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGGERPCTL
    Offset name:         IOMUX_O_LOGGERPCTL
    Relative address:    0x9004
    Description:         Pull control register of IO LOGGER
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_LOGGERPCTL_CTL_W                                       2U
#define IOMUX_LOGGERPCTL_CTL_M                                       0x00000003U
#define IOMUX_LOGGERPCTL_CTL_S                                       0U
#define IOMUX_LOGGERPCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_LOGGERPCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_LOGGERPCTL_CTL_UP                                      0x00000001U
#define IOMUX_LOGGERPCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_LOGGERPCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_LOGGERPCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_LOGGERPCTL_PULLUPSTA_S                                 8U
#define IOMUX_LOGGERPCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_LOGGERPCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_LOGGERPCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_LOGGERPCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_LOGGERPCTL_PULLDWNSTA_S                                9U
#define IOMUX_LOGGERPCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_LOGGERPCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGGERCTL
    Offset name:         IOMUX_O_LOGGERCTL
    Relative address:    0x9008
    Description:         Control register of IO LOGGER
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_LOGGERCTL_PADVAL                                       0x00000001U
#define IOMUX_LOGGERCTL_PADVAL_M                                     0x00000001U
#define IOMUX_LOGGERCTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_LOGGERCTL_PADVALSYNC                                   0x00000002U
#define IOMUX_LOGGERCTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_LOGGERCTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_LOGGERCTL_OUT                                          0x00000100U
#define IOMUX_LOGGERCTL_OUT_M                                        0x00000100U
#define IOMUX_LOGGERCTL_OUT_S                                        8U
#define IOMUX_LOGGERCTL_OUT_LOW                                      0x00000000U
#define IOMUX_LOGGERCTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_LOGGERCTL_OUTOVREN                                     0x00000200U
#define IOMUX_LOGGERCTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_LOGGERCTL_OUTOVREN_S                                   9U
#define IOMUX_LOGGERCTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_LOGGERCTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGGERECTL
    Offset name:         IOMUX_O_LOGGERECTL
    Relative address:    0x900C
    Description:         Event control register for IO LOGGER
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_LOGGERECTL_EVTDETCFG_W                                 2U
#define IOMUX_LOGGERECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_LOGGERECTL_EVTDETCFG_S                                 0U
#define IOMUX_LOGGERECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_LOGGERECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_LOGGERECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_LOGGERECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_LOGGERECTL_TRGLVL                                      0x00000004U
#define IOMUX_LOGGERECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_LOGGERECTL_TRGLVL_S                                    2U
#define IOMUX_LOGGERECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_LOGGERECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_LOGGERECTL_CLR                                         0x00000008U
#define IOMUX_LOGGERECTL_CLR_M                                       0x00000008U
#define IOMUX_LOGGERECTL_CLR_S                                       3U
#define IOMUX_LOGGERECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_LOGGERECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO10CFG
    Offset name:         IOMUX_O_GPIO10CFG
    Relative address:    0xA000
    Description:         CFG register for IO GPIO10. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO10CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO10CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO10CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO10CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO10CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO10CFG_ANASW                                        0x00000100U
#define IOMUX_GPIO10CFG_ANASW_M                                      0x00000100U
#define IOMUX_GPIO10CFG_ANASW_S                                      8U
#define IOMUX_GPIO10CFG_ANASW_DISABLE                                0x00000000U
#define IOMUX_GPIO10CFG_ANASW_ENABLE                                 0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO10CFG_ANASWOVREN                                   0x00000200U
#define IOMUX_GPIO10CFG_ANASWOVREN_M                                 0x00000200U
#define IOMUX_GPIO10CFG_ANASWOVREN_S                                 9U
#define IOMUX_GPIO10CFG_ANASWOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO10CFG_ANASWOVREN_ENABLE                            0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO10CFG_IE                                           0x00000800U
#define IOMUX_GPIO10CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO10CFG_IE_S                                         11U
#define IOMUX_GPIO10CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO10CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO10CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO10CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO10CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO10CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO10CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO10CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO10CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO10CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO10CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO10CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO10CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO10CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO10CFG_IOSTR_S                                      14U
#define IOMUX_GPIO10CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO10CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO10PCTL
    Offset name:         IOMUX_O_GPIO10PCTL
    Relative address:    0xA004
    Description:         Pull control register of IO GPIO10
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO10PCTL_CTL_W                                       2U
#define IOMUX_GPIO10PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO10PCTL_CTL_S                                       0U
#define IOMUX_GPIO10PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO10PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO10PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO10PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO10PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO10PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO10PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO10PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO10PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO10PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO10PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO10PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO10PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO10PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO10CTL
    Offset name:         IOMUX_O_GPIO10CTL
    Relative address:    0xA008
    Description:         Control register of IO GPIO10
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO10CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO10CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO10CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO10CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO10CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO10CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO10CTL_OUT                                          0x00000100U
#define IOMUX_GPIO10CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO10CTL_OUT_S                                        8U
#define IOMUX_GPIO10CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO10CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO10CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO10CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO10CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO10CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO10CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO10ECTL
    Offset name:         IOMUX_O_GPIO10ECTL
    Relative address:    0xA00C
    Description:         Event control register for IO GPIO10
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO10ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO10ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO10ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO10ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO10ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO10ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO10ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO10ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO10ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO10ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO10ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO10ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO10ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO10ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO10ECTL_CLR_S                                       3U
#define IOMUX_GPIO10ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO10ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO11CFG
    Offset name:         IOMUX_O_GPIO11CFG
    Relative address:    0xB000
    Description:         CFG register for IO GPIO11. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO11CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO11CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO11CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO11CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO11CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           ANASW
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field defines the Ana switch state. If the switch is enabled, the analog signal is routed to the IO pad
                         Note: This field is applicable when [ANASWOVREN] is enabled

        ENUMs:
            DISABLE:                     Analog switch open
            ENABLE:                      Analog switch closed
*/
#define IOMUX_GPIO11CFG_ANASW                                        0x00000100U
#define IOMUX_GPIO11CFG_ANASW_M                                      0x00000100U
#define IOMUX_GPIO11CFG_ANASW_S                                      8U
#define IOMUX_GPIO11CFG_ANASW_DISABLE                                0x00000000U
#define IOMUX_GPIO11CFG_ANASW_ENABLE                                 0x00000100U
/*

        Field:           ANASWOVREN
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the analog switch override

        ENUMs:
            DISABLE:                     Analog switch is controlled by IP
            ENABLE:                      Enable override on analog switch control
*/
#define IOMUX_GPIO11CFG_ANASWOVREN                                   0x00000200U
#define IOMUX_GPIO11CFG_ANASWOVREN_M                                 0x00000200U
#define IOMUX_GPIO11CFG_ANASWOVREN_S                                 9U
#define IOMUX_GPIO11CFG_ANASWOVREN_DISABLE                           0x00000000U
#define IOMUX_GPIO11CFG_ANASWOVREN_ENABLE                            0x00000200U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO11CFG_IE                                           0x00000800U
#define IOMUX_GPIO11CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO11CFG_IE_S                                         11U
#define IOMUX_GPIO11CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO11CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO11CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO11CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO11CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO11CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO11CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO11CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO11CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO11CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO11CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO11CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO11CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO11CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO11CFG_IOSTR_S                                      14U
#define IOMUX_GPIO11CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO11CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO11PCTL
    Offset name:         IOMUX_O_GPIO11PCTL
    Relative address:    0xB004
    Description:         Pull control register of IO GPIO11
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO11PCTL_CTL_W                                       2U
#define IOMUX_GPIO11PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO11PCTL_CTL_S                                       0U
#define IOMUX_GPIO11PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO11PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO11PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO11PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO11PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO11PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO11PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO11PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO11PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO11PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO11PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO11PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO11PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO11PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO11CTL
    Offset name:         IOMUX_O_GPIO11CTL
    Relative address:    0xB008
    Description:         Control register of IO GPIO11
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO11CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO11CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO11CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO11CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO11CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO11CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO11CTL_OUT                                          0x00000100U
#define IOMUX_GPIO11CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO11CTL_OUT_S                                        8U
#define IOMUX_GPIO11CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO11CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO11CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO11CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO11CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO11CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO11CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO11ECTL
    Offset name:         IOMUX_O_GPIO11ECTL
    Relative address:    0xB00C
    Description:         Event control register for IO GPIO11
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO11ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO11ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO11ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO11ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO11ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO11ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO11ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO11ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO11ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO11ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO11ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO11ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO11ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO11ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO11ECTL_CLR_S                                       3U
#define IOMUX_GPIO11ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO11ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO12CFG
    Offset name:         IOMUX_O_GPIO12CFG
    Relative address:    0xC000
    Description:         CFG register for IO GPIO12. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO12CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO12CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO12CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO12CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO12CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO12CFG_IE                                           0x00000800U
#define IOMUX_GPIO12CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO12CFG_IE_S                                         11U
#define IOMUX_GPIO12CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO12CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO12CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO12CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO12CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO12CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO12CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO12CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO12CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO12CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO12CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO12CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO12CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO12CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO12CFG_IOSTR_S                                      14U
#define IOMUX_GPIO12CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO12CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO12PCTL
    Offset name:         IOMUX_O_GPIO12PCTL
    Relative address:    0xC004
    Description:         Pull control register of IO GPIO12
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO12PCTL_CTL_W                                       2U
#define IOMUX_GPIO12PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO12PCTL_CTL_S                                       0U
#define IOMUX_GPIO12PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO12PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO12PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO12PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO12PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO12PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO12PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO12PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO12PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO12PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO12PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO12PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO12PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO12PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO12CTL
    Offset name:         IOMUX_O_GPIO12CTL
    Relative address:    0xC008
    Description:         Control register of IO GPIO12
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO12CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO12CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO12CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO12CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO12CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO12CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO12CTL_OUT                                          0x00000100U
#define IOMUX_GPIO12CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO12CTL_OUT_S                                        8U
#define IOMUX_GPIO12CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO12CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO12CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO12CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO12CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO12CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO12CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO12ECTL
    Offset name:         IOMUX_O_GPIO12ECTL
    Relative address:    0xC00C
    Description:         Event control register for IO GPIO12
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO12ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO12ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO12ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO12ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO12ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO12ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO12ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO12ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO12ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO12ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO12ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO12ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO12ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO12ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO12ECTL_CLR_S                                       3U
#define IOMUX_GPIO12ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO12ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO13CFG
    Offset name:         IOMUX_O_GPIO13CFG
    Relative address:    0xD000
    Description:         CFG register for IO GPIO13. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO13CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO13CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO13CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO13CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO13CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO13CFG_IE                                           0x00000800U
#define IOMUX_GPIO13CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO13CFG_IE_S                                         11U
#define IOMUX_GPIO13CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO13CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO13CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO13CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO13CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO13CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO13CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO13CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO13CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO13CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO13CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO13CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO13CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO13CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO13CFG_IOSTR_S                                      14U
#define IOMUX_GPIO13CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO13CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO13PCTL
    Offset name:         IOMUX_O_GPIO13PCTL
    Relative address:    0xD004
    Description:         Pull control register of IO GPIO13
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO13PCTL_CTL_W                                       2U
#define IOMUX_GPIO13PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO13PCTL_CTL_S                                       0U
#define IOMUX_GPIO13PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO13PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO13PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO13PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO13PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO13PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO13PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO13PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO13PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO13PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO13PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO13PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO13PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO13PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO13CTL
    Offset name:         IOMUX_O_GPIO13CTL
    Relative address:    0xD008
    Description:         Control register of IO GPIO13
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO13CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO13CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO13CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO13CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO13CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO13CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO13CTL_OUT                                          0x00000100U
#define IOMUX_GPIO13CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO13CTL_OUT_S                                        8U
#define IOMUX_GPIO13CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO13CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO13CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO13CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO13CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO13CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO13CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO13ECTL
    Offset name:         IOMUX_O_GPIO13ECTL
    Relative address:    0xD00C
    Description:         Event control register for IO GPIO13
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO13ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO13ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO13ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO13ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO13ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO13ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO13ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO13ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO13ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO13ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO13ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO13ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO13ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO13ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO13ECTL_CLR_S                                       3U
#define IOMUX_GPIO13ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO13ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO14CFG
    Offset name:         IOMUX_O_GPIO14CFG
    Relative address:    0xE000
    Description:         CFG register for IO GPIO14. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO14CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO14CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO14CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO14CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO14CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO14CFG_IE                                           0x00000800U
#define IOMUX_GPIO14CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO14CFG_IE_S                                         11U
#define IOMUX_GPIO14CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO14CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO14CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO14CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO14CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO14CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO14CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO14CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO14CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO14CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO14CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO14CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO14CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO14CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO14CFG_IOSTR_S                                      14U
#define IOMUX_GPIO14CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO14CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO14PCTL
    Offset name:         IOMUX_O_GPIO14PCTL
    Relative address:    0xE004
    Description:         Pull control register of IO GPIO14
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO14PCTL_CTL_W                                       2U
#define IOMUX_GPIO14PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO14PCTL_CTL_S                                       0U
#define IOMUX_GPIO14PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO14PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO14PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO14PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO14PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO14PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO14PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO14PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO14PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO14PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO14PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO14PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO14PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO14PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO14CTL
    Offset name:         IOMUX_O_GPIO14CTL
    Relative address:    0xE008
    Description:         Control register of IO GPIO14
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO14CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO14CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO14CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO14CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO14CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO14CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO14CTL_OUT                                          0x00000100U
#define IOMUX_GPIO14CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO14CTL_OUT_S                                        8U
#define IOMUX_GPIO14CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO14CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO14CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO14CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO14CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO14CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO14CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO14ECTL
    Offset name:         IOMUX_O_GPIO14ECTL
    Relative address:    0xE00C
    Description:         Event control register for IO GPIO14
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO14ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO14ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO14ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO14ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO14ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO14ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO14ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO14ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO14ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO14ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO14ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO14ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO14ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO14ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO14ECTL_CLR_S                                       3U
#define IOMUX_GPIO14ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO14ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO15CFG
    Offset name:         IOMUX_O_GPIO15CFG
    Relative address:    0xF000
    Description:         CFG register for IO GPIO15. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO15CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO15CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO15CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO15CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO15CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO15CFG_IE                                           0x00000800U
#define IOMUX_GPIO15CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO15CFG_IE_S                                         11U
#define IOMUX_GPIO15CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO15CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO15CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO15CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO15CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO15CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO15CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO15CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO15CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO15CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO15CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO15CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO15CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO15CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO15CFG_IOSTR_S                                      14U
#define IOMUX_GPIO15CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO15CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO15PCTL
    Offset name:         IOMUX_O_GPIO15PCTL
    Relative address:    0xF004
    Description:         Pull control register of IO GPIO15
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO15PCTL_CTL_W                                       2U
#define IOMUX_GPIO15PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO15PCTL_CTL_S                                       0U
#define IOMUX_GPIO15PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO15PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO15PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO15PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO15PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO15PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO15PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO15PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO15PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO15PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO15PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO15PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO15PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO15PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO15CTL
    Offset name:         IOMUX_O_GPIO15CTL
    Relative address:    0xF008
    Description:         Control register of IO GPIO15
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO15CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO15CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO15CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO15CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO15CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO15CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO15CTL_OUT                                          0x00000100U
#define IOMUX_GPIO15CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO15CTL_OUT_S                                        8U
#define IOMUX_GPIO15CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO15CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO15CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO15CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO15CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO15CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO15CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO15ECTL
    Offset name:         IOMUX_O_GPIO15ECTL
    Relative address:    0xF00C
    Description:         Event control register for IO GPIO15
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO15ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO15ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO15ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO15ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO15ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO15ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO15ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO15ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO15ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO15ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO15ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO15ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO15ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO15ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO15ECTL_CLR_S                                       3U
#define IOMUX_GPIO15ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO15ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO16CFG
    Offset name:         IOMUX_O_GPIO16CFG
    Relative address:    0x10000
    Description:         CFG register for IO GPIO16. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO16CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO16CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO16CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO16CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO16CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO16CFG_IE                                           0x00000800U
#define IOMUX_GPIO16CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO16CFG_IE_S                                         11U
#define IOMUX_GPIO16CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO16CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO16CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO16CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO16CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO16CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO16CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO16CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO16CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO16CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO16CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO16CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO16CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO16CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO16CFG_IOSTR_S                                      14U
#define IOMUX_GPIO16CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO16CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO16PCTL
    Offset name:         IOMUX_O_GPIO16PCTL
    Relative address:    0x10004
    Description:         Pull control register of IO GPIO16
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO16PCTL_CTL_W                                       2U
#define IOMUX_GPIO16PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO16PCTL_CTL_S                                       0U
#define IOMUX_GPIO16PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO16PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO16PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO16PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO16PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO16PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO16PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO16PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO16PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO16PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO16PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO16PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO16PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO16PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO16CTL
    Offset name:         IOMUX_O_GPIO16CTL
    Relative address:    0x10008
    Description:         Control register of IO GPIO16
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO16CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO16CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO16CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO16CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO16CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO16CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO16CTL_OUT                                          0x00000100U
#define IOMUX_GPIO16CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO16CTL_OUT_S                                        8U
#define IOMUX_GPIO16CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO16CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO16CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO16CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO16CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO16CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO16CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO16ECTL
    Offset name:         IOMUX_O_GPIO16ECTL
    Relative address:    0x1000C
    Description:         Event control register for IO GPIO16
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO16ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO16ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO16ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO16ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO16ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO16ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO16ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO16ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO16ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO16ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO16ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO16ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO16ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO16ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO16ECTL_CLR_S                                       3U
#define IOMUX_GPIO16ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO16ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO17CFG
    Offset name:         IOMUX_O_GPIO17CFG
    Relative address:    0x11000
    Description:         CFG register for IO GPIO17. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO17CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO17CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO17CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO17CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO17CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO17CFG_IE                                           0x00000800U
#define IOMUX_GPIO17CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO17CFG_IE_S                                         11U
#define IOMUX_GPIO17CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO17CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO17CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO17CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO17CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO17CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO17CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO17CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO17CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO17CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO17CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO17CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO17CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO17CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO17CFG_IOSTR_S                                      14U
#define IOMUX_GPIO17CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO17CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO17PCTL
    Offset name:         IOMUX_O_GPIO17PCTL
    Relative address:    0x11004
    Description:         Pull control register of IO GPIO17
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO17PCTL_CTL_W                                       2U
#define IOMUX_GPIO17PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO17PCTL_CTL_S                                       0U
#define IOMUX_GPIO17PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO17PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO17PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO17PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO17PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO17PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO17PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO17PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO17PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO17PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO17PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO17PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO17PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO17PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO17CTL
    Offset name:         IOMUX_O_GPIO17CTL
    Relative address:    0x11008
    Description:         Control register of IO GPIO17
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO17CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO17CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO17CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO17CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO17CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO17CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO17CTL_OUT                                          0x00000100U
#define IOMUX_GPIO17CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO17CTL_OUT_S                                        8U
#define IOMUX_GPIO17CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO17CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO17CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO17CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO17CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO17CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO17CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO17ECTL
    Offset name:         IOMUX_O_GPIO17ECTL
    Relative address:    0x1100C
    Description:         Event control register for IO GPIO17
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO17ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO17ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO17ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO17ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO17ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO17ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO17ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO17ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO17ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO17ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO17ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO17ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO17ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO17ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO17ECTL_CLR_S                                       3U
#define IOMUX_GPIO17ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO17ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO18CFG
    Offset name:         IOMUX_O_GPIO18CFG
    Relative address:    0x12000
    Description:         CFG register for IO GPIO18. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO18CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO18CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO18CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO18CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO18CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO18CFG_IE                                           0x00000800U
#define IOMUX_GPIO18CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO18CFG_IE_S                                         11U
#define IOMUX_GPIO18CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO18CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO18CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO18CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO18CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO18CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO18CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO18CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO18CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO18CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO18CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO18CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO18CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO18CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO18CFG_IOSTR_S                                      14U
#define IOMUX_GPIO18CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO18CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO18PCTL
    Offset name:         IOMUX_O_GPIO18PCTL
    Relative address:    0x12004
    Description:         Pull control register of IO GPIO18
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO18PCTL_CTL_W                                       2U
#define IOMUX_GPIO18PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO18PCTL_CTL_S                                       0U
#define IOMUX_GPIO18PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO18PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO18PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO18PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO18PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO18PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO18PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO18PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO18PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO18PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO18PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO18PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO18PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO18PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO18CTL
    Offset name:         IOMUX_O_GPIO18CTL
    Relative address:    0x12008
    Description:         Control register of IO GPIO18
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO18CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO18CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO18CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO18CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO18CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO18CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO18CTL_OUT                                          0x00000100U
#define IOMUX_GPIO18CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO18CTL_OUT_S                                        8U
#define IOMUX_GPIO18CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO18CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO18CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO18CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO18CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO18CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO18CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO18ECTL
    Offset name:         IOMUX_O_GPIO18ECTL
    Relative address:    0x1200C
    Description:         Event control register for IO GPIO18
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO18ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO18ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO18ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO18ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO18ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO18ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO18ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO18ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO18ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO18ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO18ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO18ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO18ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO18ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO18ECTL_CLR_S                                       3U
#define IOMUX_GPIO18ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO18ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO19CFG
    Offset name:         IOMUX_O_GPIO19CFG
    Relative address:    0x13000
    Description:         CFG register for IO GPIO19. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO19CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO19CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO19CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO19CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO19CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO19CFG_IE                                           0x00000800U
#define IOMUX_GPIO19CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO19CFG_IE_S                                         11U
#define IOMUX_GPIO19CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO19CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO19CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO19CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO19CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO19CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO19CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO19CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO19CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO19CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO19CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO19CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO19CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO19CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO19CFG_IOSTR_S                                      14U
#define IOMUX_GPIO19CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO19CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO19PCTL
    Offset name:         IOMUX_O_GPIO19PCTL
    Relative address:    0x13004
    Description:         Pull control register of IO GPIO19
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO19PCTL_CTL_W                                       2U
#define IOMUX_GPIO19PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO19PCTL_CTL_S                                       0U
#define IOMUX_GPIO19PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO19PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO19PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO19PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO19PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO19PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO19PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO19PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO19PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO19PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO19PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO19PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO19PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO19PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO19CTL
    Offset name:         IOMUX_O_GPIO19CTL
    Relative address:    0x13008
    Description:         Control register of IO GPIO19
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO19CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO19CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO19CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO19CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO19CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO19CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO19CTL_OUT                                          0x00000100U
#define IOMUX_GPIO19CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO19CTL_OUT_S                                        8U
#define IOMUX_GPIO19CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO19CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO19CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO19CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO19CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO19CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO19CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO19ECTL
    Offset name:         IOMUX_O_GPIO19ECTL
    Relative address:    0x1300C
    Description:         Event control register for IO GPIO19
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO19ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO19ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO19ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO19ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO19ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO19ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO19ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO19ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO19ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO19ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO19ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO19ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO19ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO19ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO19ECTL_CLR_S                                       3U
#define IOMUX_GPIO19ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO19ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO20CFG
    Offset name:         IOMUX_O_GPIO20CFG
    Relative address:    0x14000
    Description:         CFG register for IO GPIO20. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO20CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO20CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO20CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO20CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO20CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO20CFG_IE                                           0x00000800U
#define IOMUX_GPIO20CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO20CFG_IE_S                                         11U
#define IOMUX_GPIO20CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO20CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO20CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO20CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO20CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO20CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO20CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO20CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO20CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO20CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO20CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO20CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO20CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO20CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO20CFG_IOSTR_S                                      14U
#define IOMUX_GPIO20CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO20CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO20PCTL
    Offset name:         IOMUX_O_GPIO20PCTL
    Relative address:    0x14004
    Description:         Pull control register of IO GPIO20
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO20PCTL_CTL_W                                       2U
#define IOMUX_GPIO20PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO20PCTL_CTL_S                                       0U
#define IOMUX_GPIO20PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO20PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO20PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO20PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO20PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO20PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO20PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO20PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO20PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO20PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO20PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO20PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO20PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO20PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO20CTL
    Offset name:         IOMUX_O_GPIO20CTL
    Relative address:    0x14008
    Description:         Control register of IO GPIO20
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO20CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO20CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO20CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO20CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO20CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO20CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO20CTL_OUT                                          0x00000100U
#define IOMUX_GPIO20CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO20CTL_OUT_S                                        8U
#define IOMUX_GPIO20CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO20CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO20CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO20CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO20CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO20CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO20CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO20ECTL
    Offset name:         IOMUX_O_GPIO20ECTL
    Relative address:    0x1400C
    Description:         Event control register for IO GPIO20
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO20ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO20ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO20ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO20ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO20ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO20ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO20ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO20ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO20ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO20ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO20ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO20ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO20ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO20ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO20ECTL_CLR_S                                       3U
#define IOMUX_GPIO20ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO20ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO21CFG
    Offset name:         IOMUX_O_GPIO21CFG
    Relative address:    0x15000
    Description:         CFG register for IO GPIO21. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO21CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO21CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO21CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO21CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO21CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO21CFG_IE                                           0x00000800U
#define IOMUX_GPIO21CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO21CFG_IE_S                                         11U
#define IOMUX_GPIO21CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO21CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO21CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO21CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO21CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO21CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO21CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO21CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO21CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO21CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO21CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO21CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO21CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO21CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO21CFG_IOSTR_S                                      14U
#define IOMUX_GPIO21CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO21CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO21PCTL
    Offset name:         IOMUX_O_GPIO21PCTL
    Relative address:    0x15004
    Description:         Pull control register of IO GPIO21
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO21PCTL_CTL_W                                       2U
#define IOMUX_GPIO21PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO21PCTL_CTL_S                                       0U
#define IOMUX_GPIO21PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO21PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO21PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO21PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO21PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO21PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO21PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO21PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO21PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO21PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO21PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO21PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO21PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO21PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO21CTL
    Offset name:         IOMUX_O_GPIO21CTL
    Relative address:    0x15008
    Description:         Control register of IO GPIO21
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO21CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO21CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO21CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO21CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO21CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO21CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO21CTL_OUT                                          0x00000100U
#define IOMUX_GPIO21CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO21CTL_OUT_S                                        8U
#define IOMUX_GPIO21CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO21CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO21CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO21CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO21CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO21CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO21CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO21ECTL
    Offset name:         IOMUX_O_GPIO21ECTL
    Relative address:    0x1500C
    Description:         Event control register for IO GPIO21
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO21ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO21ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO21ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO21ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO21ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO21ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO21ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO21ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO21ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO21ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO21ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO21ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO21ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO21ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO21ECTL_CLR_S                                       3U
#define IOMUX_GPIO21ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO21ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO22CFG
    Offset name:         IOMUX_O_GPIO22CFG
    Relative address:    0x16000
    Description:         CFG register for IO GPIO22. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO22CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO22CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO22CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO22CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO22CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO22CFG_IE                                           0x00000800U
#define IOMUX_GPIO22CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO22CFG_IE_S                                         11U
#define IOMUX_GPIO22CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO22CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO22CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO22CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO22CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO22CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO22CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO22CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO22CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO22CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO22CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO22CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO22CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO22CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO22CFG_IOSTR_S                                      14U
#define IOMUX_GPIO22CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO22CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO22PCTL
    Offset name:         IOMUX_O_GPIO22PCTL
    Relative address:    0x16004
    Description:         Pull control register of IO GPIO22
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO22PCTL_CTL_W                                       2U
#define IOMUX_GPIO22PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO22PCTL_CTL_S                                       0U
#define IOMUX_GPIO22PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO22PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO22PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO22PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO22PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO22PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO22PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO22PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO22PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO22PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO22PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO22PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO22PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO22PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO22CTL
    Offset name:         IOMUX_O_GPIO22CTL
    Relative address:    0x16008
    Description:         Control register of IO GPIO22
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO22CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO22CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO22CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO22CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO22CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO22CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO22CTL_OUT                                          0x00000100U
#define IOMUX_GPIO22CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO22CTL_OUT_S                                        8U
#define IOMUX_GPIO22CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO22CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO22CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO22CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO22CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO22CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO22CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO22ECTL
    Offset name:         IOMUX_O_GPIO22ECTL
    Relative address:    0x1600C
    Description:         Event control register for IO GPIO22
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO22ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO22ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO22ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO22ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO22ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO22ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO22ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO22ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO22ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO22ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO22ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO22ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO22ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO22ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO22ECTL_CLR_S                                       3U
#define IOMUX_GPIO22ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO22ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO23CFG
    Offset name:         IOMUX_O_GPIO23CFG
    Relative address:    0x17000
    Description:         CFG register for IO GPIO23. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO23CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO23CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO23CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO23CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO23CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO23CFG_IE                                           0x00000800U
#define IOMUX_GPIO23CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO23CFG_IE_S                                         11U
#define IOMUX_GPIO23CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO23CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO23CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO23CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO23CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO23CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO23CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO23CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO23CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO23CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO23CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO23CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO23CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO23CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO23CFG_IOSTR_S                                      14U
#define IOMUX_GPIO23CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO23CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO23PCTL
    Offset name:         IOMUX_O_GPIO23PCTL
    Relative address:    0x17004
    Description:         Pull control register of IO GPIO23
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO23PCTL_CTL_W                                       2U
#define IOMUX_GPIO23PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO23PCTL_CTL_S                                       0U
#define IOMUX_GPIO23PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO23PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO23PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO23PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO23PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO23PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO23PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO23PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO23PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO23PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO23PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO23PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO23PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO23PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO23CTL
    Offset name:         IOMUX_O_GPIO23CTL
    Relative address:    0x17008
    Description:         Control register of IO GPIO23
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO23CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO23CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO23CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO23CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO23CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO23CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO23CTL_OUT                                          0x00000100U
#define IOMUX_GPIO23CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO23CTL_OUT_S                                        8U
#define IOMUX_GPIO23CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO23CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO23CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO23CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO23CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO23CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO23CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO23ECTL
    Offset name:         IOMUX_O_GPIO23ECTL
    Relative address:    0x1700C
    Description:         Event control register for IO GPIO23
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO23ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO23ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO23ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO23ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO23ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO23ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO23ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO23ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO23ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO23ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO23ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO23ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO23ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO23ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO23ECTL_CLR_S                                       3U
#define IOMUX_GPIO23ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO23ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO24CFG
    Offset name:         IOMUX_O_GPIO24CFG
    Relative address:    0x18000
    Description:         CFG register for IO GPIO24. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO24CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO24CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO24CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO24CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO24CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO24CFG_IE                                           0x00000800U
#define IOMUX_GPIO24CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO24CFG_IE_S                                         11U
#define IOMUX_GPIO24CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO24CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO24CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO24CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO24CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO24CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO24CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO24CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO24CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO24CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO24CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO24CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO24CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO24CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO24CFG_IOSTR_S                                      14U
#define IOMUX_GPIO24CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO24CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO24PCTL
    Offset name:         IOMUX_O_GPIO24PCTL
    Relative address:    0x18004
    Description:         Pull control register of IO GPIO24
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO24PCTL_CTL_W                                       2U
#define IOMUX_GPIO24PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO24PCTL_CTL_S                                       0U
#define IOMUX_GPIO24PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO24PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO24PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO24PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO24PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO24PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO24PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO24PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO24PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO24PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO24PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO24PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO24PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO24PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO24CTL
    Offset name:         IOMUX_O_GPIO24CTL
    Relative address:    0x18008
    Description:         Control register of IO GPIO24
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO24CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO24CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO24CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO24CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO24CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO24CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO24CTL_OUT                                          0x00000100U
#define IOMUX_GPIO24CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO24CTL_OUT_S                                        8U
#define IOMUX_GPIO24CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO24CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO24CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO24CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO24CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO24CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO24CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO24ECTL
    Offset name:         IOMUX_O_GPIO24ECTL
    Relative address:    0x1800C
    Description:         Event control register for IO GPIO24
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO24ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO24ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO24ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO24ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO24ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO24ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO24ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO24ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO24ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO24ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO24ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO24ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO24ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO24ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO24ECTL_CLR_S                                       3U
#define IOMUX_GPIO24ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO24ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO25CFG
    Offset name:         IOMUX_O_GPIO25CFG
    Relative address:    0x19000
    Description:         CFG register for IO GPIO25. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO25CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO25CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO25CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO25CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO25CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO25CFG_IE                                           0x00000800U
#define IOMUX_GPIO25CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO25CFG_IE_S                                         11U
#define IOMUX_GPIO25CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO25CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO25CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO25CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO25CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO25CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO25CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO25CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO25CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO25CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO25CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO25CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO25CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO25CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO25CFG_IOSTR_S                                      14U
#define IOMUX_GPIO25CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO25CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO25PCTL
    Offset name:         IOMUX_O_GPIO25PCTL
    Relative address:    0x19004
    Description:         Pull control register of IO GPIO25
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO25PCTL_CTL_W                                       2U
#define IOMUX_GPIO25PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO25PCTL_CTL_S                                       0U
#define IOMUX_GPIO25PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO25PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO25PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO25PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO25PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO25PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO25PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO25PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO25PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO25PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO25PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO25PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO25PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO25PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO25CTL
    Offset name:         IOMUX_O_GPIO25CTL
    Relative address:    0x19008
    Description:         Control register of IO GPIO25
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO25CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO25CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO25CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO25CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO25CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO25CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO25CTL_OUT                                          0x00000100U
#define IOMUX_GPIO25CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO25CTL_OUT_S                                        8U
#define IOMUX_GPIO25CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO25CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO25CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO25CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO25CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO25CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO25CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO25ECTL
    Offset name:         IOMUX_O_GPIO25ECTL
    Relative address:    0x1900C
    Description:         Event control register for IO GPIO25
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO25ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO25ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO25ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO25ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO25ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO25ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO25ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO25ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO25ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO25ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO25ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO25ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO25ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO25ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO25ECTL_CLR_S                                       3U
#define IOMUX_GPIO25ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO25ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO26CFG
    Offset name:         IOMUX_O_GPIO26CFG
    Relative address:    0x1A000
    Description:         CFG register for IO GPIO26. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO26CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO26CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO26CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO26CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO26CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO26CFG_IE                                           0x00000800U
#define IOMUX_GPIO26CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO26CFG_IE_S                                         11U
#define IOMUX_GPIO26CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO26CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO26CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO26CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO26CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO26CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO26CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO26CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO26CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO26CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO26CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO26CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO26CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO26CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO26CFG_IOSTR_S                                      14U
#define IOMUX_GPIO26CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO26CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO26PCTL
    Offset name:         IOMUX_O_GPIO26PCTL
    Relative address:    0x1A004
    Description:         Pull control register of IO GPIO26
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO26PCTL_CTL_W                                       2U
#define IOMUX_GPIO26PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO26PCTL_CTL_S                                       0U
#define IOMUX_GPIO26PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO26PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO26PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO26PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO26PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO26PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO26PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO26PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO26PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO26PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO26PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO26PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO26PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO26PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO26CTL
    Offset name:         IOMUX_O_GPIO26CTL
    Relative address:    0x1A008
    Description:         Control register of IO GPIO26
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO26CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO26CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO26CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO26CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO26CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO26CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO26CTL_OUT                                          0x00000100U
#define IOMUX_GPIO26CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO26CTL_OUT_S                                        8U
#define IOMUX_GPIO26CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO26CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO26CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO26CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO26CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO26CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO26CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO26ECTL
    Offset name:         IOMUX_O_GPIO26ECTL
    Relative address:    0x1A00C
    Description:         Event control register for IO GPIO26
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO26ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO26ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO26ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO26ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO26ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO26ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO26ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO26ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO26ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO26ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO26ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO26ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO26ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO26ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO26ECTL_CLR_S                                       3U
#define IOMUX_GPIO26ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO26ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO27CFG
    Offset name:         IOMUX_O_GPIO27CFG
    Relative address:    0x1B000
    Description:         CFG register for IO GPIO27. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO27CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO27CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO27CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO27CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO27CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO27CFG_IE                                           0x00000800U
#define IOMUX_GPIO27CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO27CFG_IE_S                                         11U
#define IOMUX_GPIO27CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO27CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO27CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO27CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO27CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO27CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO27CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO27CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO27CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO27CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO27CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO27CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO27CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO27CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO27CFG_IOSTR_S                                      14U
#define IOMUX_GPIO27CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO27CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO27PCTL
    Offset name:         IOMUX_O_GPIO27PCTL
    Relative address:    0x1B004
    Description:         Pull control register of IO GPIO27
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO27PCTL_CTL_W                                       2U
#define IOMUX_GPIO27PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO27PCTL_CTL_S                                       0U
#define IOMUX_GPIO27PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO27PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO27PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO27PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO27PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO27PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO27PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO27PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO27PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO27PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO27PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO27PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO27PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO27PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO27CTL
    Offset name:         IOMUX_O_GPIO27CTL
    Relative address:    0x1B008
    Description:         Control register of IO GPIO27
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO27CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO27CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO27CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO27CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO27CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO27CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO27CTL_OUT                                          0x00000100U
#define IOMUX_GPIO27CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO27CTL_OUT_S                                        8U
#define IOMUX_GPIO27CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO27CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO27CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO27CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO27CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO27CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO27CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO27ECTL
    Offset name:         IOMUX_O_GPIO27ECTL
    Relative address:    0x1B00C
    Description:         Event control register for IO GPIO27
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO27ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO27ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO27ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO27ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO27ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO27ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO27ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO27ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO27ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO27ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO27ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO27ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO27ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO27ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO27ECTL_CLR_S                                       3U
#define IOMUX_GPIO27ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO27ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO28CFG
    Offset name:         IOMUX_O_GPIO28CFG
    Relative address:    0x1C000
    Description:         CFG register for IO GPIO28. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO28CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO28CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO28CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO28CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO28CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO28CFG_IE                                           0x00000800U
#define IOMUX_GPIO28CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO28CFG_IE_S                                         11U
#define IOMUX_GPIO28CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO28CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO28CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO28CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO28CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO28CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO28CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO28CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO28CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO28CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO28CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO28CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO28CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO28CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO28CFG_IOSTR_S                                      14U
#define IOMUX_GPIO28CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO28CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO28PCTL
    Offset name:         IOMUX_O_GPIO28PCTL
    Relative address:    0x1C004
    Description:         Pull control register of IO GPIO28
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO28PCTL_CTL_W                                       2U
#define IOMUX_GPIO28PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO28PCTL_CTL_S                                       0U
#define IOMUX_GPIO28PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO28PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO28PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO28PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO28PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO28PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO28PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO28PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO28PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO28PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO28PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO28PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO28PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO28PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO28CTL
    Offset name:         IOMUX_O_GPIO28CTL
    Relative address:    0x1C008
    Description:         Control register of IO GPIO28
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO28CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO28CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO28CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO28CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO28CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO28CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO28CTL_OUT                                          0x00000100U
#define IOMUX_GPIO28CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO28CTL_OUT_S                                        8U
#define IOMUX_GPIO28CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO28CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO28CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO28CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO28CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO28CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO28CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO28ECTL
    Offset name:         IOMUX_O_GPIO28ECTL
    Relative address:    0x1C00C
    Description:         Event control register for IO GPIO28
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO28ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO28ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO28ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO28ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO28ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO28ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO28ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO28ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO28ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO28ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO28ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO28ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO28ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO28ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO28ECTL_CLR_S                                       3U
#define IOMUX_GPIO28ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO28ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO29CFG
    Offset name:         IOMUX_O_GPIO29CFG
    Relative address:    0x1D000
    Description:         CFG register for IO GPIO29. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO29CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO29CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO29CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO29CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO29CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO29CFG_IE                                           0x00000800U
#define IOMUX_GPIO29CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO29CFG_IE_S                                         11U
#define IOMUX_GPIO29CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO29CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO29CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO29CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO29CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO29CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO29CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO29CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO29CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO29CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO29CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO29CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO29CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO29CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO29CFG_IOSTR_S                                      14U
#define IOMUX_GPIO29CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO29CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO29PCTL
    Offset name:         IOMUX_O_GPIO29PCTL
    Relative address:    0x1D004
    Description:         Pull control register of IO GPIO29
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO29PCTL_CTL_W                                       2U
#define IOMUX_GPIO29PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO29PCTL_CTL_S                                       0U
#define IOMUX_GPIO29PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO29PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO29PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO29PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO29PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO29PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO29PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO29PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO29PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO29PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO29PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO29PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO29PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO29PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO29CTL
    Offset name:         IOMUX_O_GPIO29CTL
    Relative address:    0x1D008
    Description:         Control register of IO GPIO29
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO29CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO29CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO29CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO29CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO29CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO29CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO29CTL_OUT                                          0x00000100U
#define IOMUX_GPIO29CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO29CTL_OUT_S                                        8U
#define IOMUX_GPIO29CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO29CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO29CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO29CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO29CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO29CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO29CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO29ECTL
    Offset name:         IOMUX_O_GPIO29ECTL
    Relative address:    0x1D00C
    Description:         Event control register for IO GPIO29
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO29ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO29ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO29ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO29ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO29ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO29ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO29ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO29ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO29ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO29ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO29ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO29ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO29ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO29ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO29ECTL_CLR_S                                       3U
#define IOMUX_GPIO29ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO29ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO30CFG
    Offset name:         IOMUX_O_GPIO30CFG
    Relative address:    0x1E000
    Description:         CFG register for IO GPIO30. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO30CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO30CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO30CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO30CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO30CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO30CFG_IE                                           0x00000800U
#define IOMUX_GPIO30CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO30CFG_IE_S                                         11U
#define IOMUX_GPIO30CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO30CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO30CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO30CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO30CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO30CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO30CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO30CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO30CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO30CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO30CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO30CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO30CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO30CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO30CFG_IOSTR_S                                      14U
#define IOMUX_GPIO30CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO30CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO30PCTL
    Offset name:         IOMUX_O_GPIO30PCTL
    Relative address:    0x1E004
    Description:         Pull control register of IO GPIO30
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO30PCTL_CTL_W                                       2U
#define IOMUX_GPIO30PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO30PCTL_CTL_S                                       0U
#define IOMUX_GPIO30PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO30PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO30PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO30PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO30PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO30PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO30PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO30PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO30PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO30PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO30PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO30PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO30PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO30PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO30CTL
    Offset name:         IOMUX_O_GPIO30CTL
    Relative address:    0x1E008
    Description:         Control register of IO GPIO30
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO30CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO30CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO30CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO30CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO30CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO30CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO30CTL_OUT                                          0x00000100U
#define IOMUX_GPIO30CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO30CTL_OUT_S                                        8U
#define IOMUX_GPIO30CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO30CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO30CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO30CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO30CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO30CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO30CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO30ECTL
    Offset name:         IOMUX_O_GPIO30ECTL
    Relative address:    0x1E00C
    Description:         Event control register for IO GPIO30
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO30ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO30ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO30ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO30ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO30ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO30ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO30ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO30ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO30ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO30ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO30ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO30ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO30ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO30ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO30ECTL_CLR_S                                       3U
#define IOMUX_GPIO30ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO30ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO31CFG
    Offset name:         IOMUX_O_GPIO31CFG
    Relative address:    0x1F000
    Description:         CFG register for IO GPIO31. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO31CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO31CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO31CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO31CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO31CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO31CFG_IE                                           0x00000800U
#define IOMUX_GPIO31CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO31CFG_IE_S                                         11U
#define IOMUX_GPIO31CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO31CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO31CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO31CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO31CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO31CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO31CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO31CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO31CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO31CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO31CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO31CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO31CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO31CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO31CFG_IOSTR_S                                      14U
#define IOMUX_GPIO31CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO31CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO31PCTL
    Offset name:         IOMUX_O_GPIO31PCTL
    Relative address:    0x1F004
    Description:         Pull control register of IO GPIO31
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO31PCTL_CTL_W                                       2U
#define IOMUX_GPIO31PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO31PCTL_CTL_S                                       0U
#define IOMUX_GPIO31PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO31PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO31PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO31PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO31PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO31PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO31PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO31PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO31PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO31PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO31PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO31PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO31PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO31PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO31CTL
    Offset name:         IOMUX_O_GPIO31CTL
    Relative address:    0x1F008
    Description:         Control register of IO GPIO31
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO31CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO31CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO31CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO31CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO31CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO31CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO31CTL_OUT                                          0x00000100U
#define IOMUX_GPIO31CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO31CTL_OUT_S                                        8U
#define IOMUX_GPIO31CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO31CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO31CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO31CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO31CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO31CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO31CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO31ECTL
    Offset name:         IOMUX_O_GPIO31ECTL
    Relative address:    0x1F00C
    Description:         Event control register for IO GPIO31
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO31ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO31ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO31ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO31ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO31ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO31ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO31ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO31ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO31ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO31ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO31ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO31ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO31ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO31ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO31ECTL_CLR_S                                       3U
#define IOMUX_GPIO31ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO31ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO32CFG
    Offset name:         IOMUX_O_GPIO32CFG
    Relative address:    0x20000
    Description:         CFG register for IO GPIO32. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO32CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO32CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO32CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO32CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO32CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO32CFG_IE                                           0x00000800U
#define IOMUX_GPIO32CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO32CFG_IE_S                                         11U
#define IOMUX_GPIO32CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO32CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO32CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO32CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO32CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO32CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO32CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO32CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO32CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO32CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO32CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO32CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO32CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO32CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO32CFG_IOSTR_S                                      14U
#define IOMUX_GPIO32CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO32CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO32PCTL
    Offset name:         IOMUX_O_GPIO32PCTL
    Relative address:    0x20004
    Description:         Pull control register of IO GPIO32
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO32PCTL_CTL_W                                       2U
#define IOMUX_GPIO32PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO32PCTL_CTL_S                                       0U
#define IOMUX_GPIO32PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO32PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO32PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO32PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO32PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO32PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO32PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO32PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO32PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO32PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO32PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO32PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO32PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO32PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO32CTL
    Offset name:         IOMUX_O_GPIO32CTL
    Relative address:    0x20008
    Description:         Control register of IO GPIO32
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO32CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO32CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO32CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO32CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO32CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO32CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO32CTL_OUT                                          0x00000100U
#define IOMUX_GPIO32CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO32CTL_OUT_S                                        8U
#define IOMUX_GPIO32CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO32CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO32CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO32CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO32CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO32CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO32CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO32ECTL
    Offset name:         IOMUX_O_GPIO32ECTL
    Relative address:    0x2000C
    Description:         Event control register for IO GPIO32
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO32ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO32ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO32ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO32ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO32ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO32ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO32ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO32ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO32ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO32ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO32ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO32ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO32ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO32ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO32ECTL_CLR_S                                       3U
#define IOMUX_GPIO32ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO32ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO33CFG
    Offset name:         IOMUX_O_GPIO33CFG
    Relative address:    0x21000
    Description:         CFG register for IO GPIO33. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO33CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO33CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO33CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO33CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO33CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO33CFG_IE                                           0x00000800U
#define IOMUX_GPIO33CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO33CFG_IE_S                                         11U
#define IOMUX_GPIO33CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO33CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO33CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO33CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO33CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO33CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO33CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO33CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO33CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO33CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO33CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO33CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO33CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO33CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO33CFG_IOSTR_S                                      14U
#define IOMUX_GPIO33CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO33CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO33PCTL
    Offset name:         IOMUX_O_GPIO33PCTL
    Relative address:    0x21004
    Description:         Pull control register of IO GPIO33
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO33PCTL_CTL_W                                       2U
#define IOMUX_GPIO33PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO33PCTL_CTL_S                                       0U
#define IOMUX_GPIO33PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO33PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO33PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO33PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO33PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO33PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO33PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO33PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO33PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO33PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO33PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO33PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO33PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO33PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO33CTL
    Offset name:         IOMUX_O_GPIO33CTL
    Relative address:    0x21008
    Description:         Control register of IO GPIO33
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO33CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO33CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO33CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO33CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO33CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO33CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO33CTL_OUT                                          0x00000100U
#define IOMUX_GPIO33CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO33CTL_OUT_S                                        8U
#define IOMUX_GPIO33CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO33CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO33CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO33CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO33CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO33CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO33CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO33ECTL
    Offset name:         IOMUX_O_GPIO33ECTL
    Relative address:    0x2100C
    Description:         Event control register for IO GPIO33
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO33ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO33ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO33ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO33ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO33ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO33ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO33ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO33ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO33ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO33ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO33ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO33ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO33ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO33ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO33ECTL_CLR_S                                       3U
#define IOMUX_GPIO33ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO33ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO34CFG
    Offset name:         IOMUX_O_GPIO34CFG
    Relative address:    0x22000
    Description:         CFG register for IO GPIO34. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO34CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO34CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO34CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO34CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO34CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO34CFG_IE                                           0x00000800U
#define IOMUX_GPIO34CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO34CFG_IE_S                                         11U
#define IOMUX_GPIO34CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO34CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO34CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO34CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO34CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO34CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO34CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO34CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO34CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO34CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO34CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO34CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO34CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO34CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO34CFG_IOSTR_S                                      14U
#define IOMUX_GPIO34CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO34CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO34PCTL
    Offset name:         IOMUX_O_GPIO34PCTL
    Relative address:    0x22004
    Description:         Pull control register of IO GPIO34
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO34PCTL_CTL_W                                       2U
#define IOMUX_GPIO34PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO34PCTL_CTL_S                                       0U
#define IOMUX_GPIO34PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO34PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO34PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO34PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO34PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO34PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO34PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO34PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO34PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO34PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO34PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO34PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO34PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO34PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO34CTL
    Offset name:         IOMUX_O_GPIO34CTL
    Relative address:    0x22008
    Description:         Control register of IO GPIO34
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO34CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO34CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO34CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO34CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO34CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO34CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO34CTL_OUT                                          0x00000100U
#define IOMUX_GPIO34CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO34CTL_OUT_S                                        8U
#define IOMUX_GPIO34CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO34CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO34CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO34CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO34CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO34CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO34CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO34ECTL
    Offset name:         IOMUX_O_GPIO34ECTL
    Relative address:    0x2200C
    Description:         Event control register for IO GPIO34
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO34ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO34ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO34ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO34ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO34ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO34ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO34ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO34ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO34ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO34ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO34ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO34ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO34ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO34ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO34ECTL_CLR_S                                       3U
#define IOMUX_GPIO34ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO34ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO35CFG
    Offset name:         IOMUX_O_GPIO35CFG
    Relative address:    0x23000
    Description:         CFG register for IO GPIO35. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO35CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO35CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO35CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO35CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO35CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO35CFG_IE                                           0x00000800U
#define IOMUX_GPIO35CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO35CFG_IE_S                                         11U
#define IOMUX_GPIO35CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO35CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO35CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO35CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO35CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO35CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO35CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO35CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO35CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO35CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO35CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO35CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO35CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO35CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO35CFG_IOSTR_S                                      14U
#define IOMUX_GPIO35CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO35CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO35PCTL
    Offset name:         IOMUX_O_GPIO35PCTL
    Relative address:    0x23004
    Description:         Pull control register of IO GPIO35
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO35PCTL_CTL_W                                       2U
#define IOMUX_GPIO35PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO35PCTL_CTL_S                                       0U
#define IOMUX_GPIO35PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO35PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO35PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO35PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO35PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO35PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO35PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO35PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO35PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO35PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO35PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO35PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO35PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO35PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO35CTL
    Offset name:         IOMUX_O_GPIO35CTL
    Relative address:    0x23008
    Description:         Control register of IO GPIO35
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO35CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO35CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO35CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO35CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO35CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO35CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO35CTL_OUT                                          0x00000100U
#define IOMUX_GPIO35CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO35CTL_OUT_S                                        8U
#define IOMUX_GPIO35CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO35CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO35CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO35CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO35CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO35CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO35CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO35ECTL
    Offset name:         IOMUX_O_GPIO35ECTL
    Relative address:    0x2300C
    Description:         Event control register for IO GPIO35
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO35ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO35ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO35ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO35ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO35ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO35ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO35ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO35ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO35ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO35ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO35ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO35ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO35ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO35ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO35ECTL_CLR_S                                       3U
#define IOMUX_GPIO35ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO35ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO36CFG
    Offset name:         IOMUX_O_GPIO36CFG
    Relative address:    0x24000
    Description:         CFG register for IO GPIO36. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO36CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO36CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO36CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO36CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO36CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO36CFG_IE                                           0x00000800U
#define IOMUX_GPIO36CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO36CFG_IE_S                                         11U
#define IOMUX_GPIO36CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO36CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO36CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO36CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO36CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO36CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO36CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO36CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO36CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO36CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO36CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO36CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO36CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO36CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO36CFG_IOSTR_S                                      14U
#define IOMUX_GPIO36CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO36CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO36PCTL
    Offset name:         IOMUX_O_GPIO36PCTL
    Relative address:    0x24004
    Description:         Pull control register of IO GPIO36
                        This register configures the pull control
    Default Value:       0x00000002

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO36PCTL_CTL_W                                       2U
#define IOMUX_GPIO36PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO36PCTL_CTL_S                                       0U
#define IOMUX_GPIO36PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO36PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO36PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO36PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO36PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO36PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO36PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO36PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO36PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO36PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO36PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO36PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO36PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO36PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO36CTL
    Offset name:         IOMUX_O_GPIO36CTL
    Relative address:    0x24008
    Description:         Control register of IO GPIO36
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO36CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO36CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO36CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO36CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO36CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO36CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO36CTL_OUT                                          0x00000100U
#define IOMUX_GPIO36CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO36CTL_OUT_S                                        8U
#define IOMUX_GPIO36CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO36CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO36CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO36CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO36CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO36CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO36CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO36ECTL
    Offset name:         IOMUX_O_GPIO36ECTL
    Relative address:    0x2400C
    Description:         Event control register for IO GPIO36
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO36ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO36ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO36ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO36ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO36ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO36ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO36ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO36ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO36ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO36ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO36ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO36ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO36ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO36ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO36ECTL_CLR_S                                       3U
#define IOMUX_GPIO36ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO36ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO37CFG
    Offset name:         IOMUX_O_GPIO37CFG
    Relative address:    0x25000
    Description:         CFG register for IO GPIO37. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO37CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO37CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO37CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO37CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO37CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO37CFG_IE                                           0x00000800U
#define IOMUX_GPIO37CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO37CFG_IE_S                                         11U
#define IOMUX_GPIO37CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO37CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO37CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO37CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO37CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO37CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO37CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO37CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO37CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO37CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO37CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO37CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO37CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO37CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO37CFG_IOSTR_S                                      14U
#define IOMUX_GPIO37CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO37CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO37PCTL
    Offset name:         IOMUX_O_GPIO37PCTL
    Relative address:    0x25004
    Description:         Pull control register of IO GPIO37
                        This register configures the pull control
    Default Value:       0x00000002

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO37PCTL_CTL_W                                       2U
#define IOMUX_GPIO37PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO37PCTL_CTL_S                                       0U
#define IOMUX_GPIO37PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO37PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO37PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO37PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO37PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO37PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO37PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO37PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO37PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO37PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO37PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO37PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO37PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO37PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO37CTL
    Offset name:         IOMUX_O_GPIO37CTL
    Relative address:    0x25008
    Description:         Control register of IO GPIO37
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO37CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO37CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO37CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO37CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO37CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO37CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO37CTL_OUT                                          0x00000100U
#define IOMUX_GPIO37CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO37CTL_OUT_S                                        8U
#define IOMUX_GPIO37CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO37CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO37CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO37CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO37CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO37CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO37CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO37ECTL
    Offset name:         IOMUX_O_GPIO37ECTL
    Relative address:    0x2500C
    Description:         Event control register for IO GPIO37
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO37ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO37ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO37ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO37ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO37ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO37ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO37ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO37ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO37ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO37ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO37ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO37ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO37ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO37ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO37ECTL_CLR_S                                       3U
#define IOMUX_GPIO37ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO37ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO38CFG
    Offset name:         IOMUX_O_GPIO38CFG
    Relative address:    0x26000
    Description:         CFG register for IO GPIO38. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO38CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO38CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO38CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO38CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO38CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO38CFG_IE                                           0x00000800U
#define IOMUX_GPIO38CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO38CFG_IE_S                                         11U
#define IOMUX_GPIO38CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO38CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO38CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO38CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO38CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO38CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO38CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO38CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO38CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO38CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO38CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO38CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO38CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO38CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO38CFG_IOSTR_S                                      14U
#define IOMUX_GPIO38CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO38CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO38PCTL
    Offset name:         IOMUX_O_GPIO38PCTL
    Relative address:    0x26004
    Description:         Pull control register of IO GPIO38
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO38PCTL_CTL_W                                       2U
#define IOMUX_GPIO38PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO38PCTL_CTL_S                                       0U
#define IOMUX_GPIO38PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO38PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO38PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO38PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO38PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO38PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO38PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO38PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO38PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO38PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO38PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO38PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO38PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO38PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO38CTL
    Offset name:         IOMUX_O_GPIO38CTL
    Relative address:    0x26008
    Description:         Control register of IO GPIO38
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO38CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO38CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO38CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO38CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO38CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO38CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO38CTL_OUT                                          0x00000100U
#define IOMUX_GPIO38CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO38CTL_OUT_S                                        8U
#define IOMUX_GPIO38CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO38CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO38CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO38CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO38CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO38CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO38CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO38ECTL
    Offset name:         IOMUX_O_GPIO38ECTL
    Relative address:    0x2600C
    Description:         Event control register for IO GPIO38
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO38ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO38ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO38ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO38ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO38ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO38ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO38ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO38ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO38ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO38ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO38ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO38ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO38ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO38ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO38ECTL_CLR_S                                       3U
#define IOMUX_GPIO38ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO38ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO39CFG
    Offset name:         IOMUX_O_GPIO39CFG
    Relative address:    0x27000
    Description:         CFG register for IO GPIO39. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO39CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO39CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO39CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO39CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO39CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO39CFG_IE                                           0x00000800U
#define IOMUX_GPIO39CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO39CFG_IE_S                                         11U
#define IOMUX_GPIO39CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO39CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO39CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO39CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO39CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO39CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO39CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO39CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO39CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO39CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO39CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO39CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO39CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO39CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO39CFG_IOSTR_S                                      14U
#define IOMUX_GPIO39CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO39CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO39PCTL
    Offset name:         IOMUX_O_GPIO39PCTL
    Relative address:    0x27004
    Description:         Pull control register of IO GPIO39
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO39PCTL_CTL_W                                       2U
#define IOMUX_GPIO39PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO39PCTL_CTL_S                                       0U
#define IOMUX_GPIO39PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO39PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO39PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO39PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO39PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO39PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO39PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO39PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO39PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO39PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO39PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO39PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO39PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO39PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO39CTL
    Offset name:         IOMUX_O_GPIO39CTL
    Relative address:    0x27008
    Description:         Control register of IO GPIO39
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO39CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO39CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO39CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO39CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO39CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO39CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO39CTL_OUT                                          0x00000100U
#define IOMUX_GPIO39CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO39CTL_OUT_S                                        8U
#define IOMUX_GPIO39CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO39CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO39CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO39CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO39CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO39CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO39CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO39ECTL
    Offset name:         IOMUX_O_GPIO39ECTL
    Relative address:    0x2700C
    Description:         Event control register for IO GPIO39
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO39ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO39ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO39ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO39ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO39ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO39ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO39ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO39ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO39ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO39ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO39ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO39ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO39ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO39ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO39ECTL_CLR_S                                       3U
#define IOMUX_GPIO39ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO39ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO40CFG
    Offset name:         IOMUX_O_GPIO40CFG
    Relative address:    0x28000
    Description:         CFG register for IO GPIO40. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO40CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO40CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO40CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO40CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO40CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO40CFG_IE                                           0x00000800U
#define IOMUX_GPIO40CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO40CFG_IE_S                                         11U
#define IOMUX_GPIO40CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO40CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO40CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO40CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO40CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO40CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO40CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO40CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO40CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO40CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO40CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO40CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO40CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO40CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO40CFG_IOSTR_S                                      14U
#define IOMUX_GPIO40CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO40CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO40PCTL
    Offset name:         IOMUX_O_GPIO40PCTL
    Relative address:    0x28004
    Description:         Pull control register of IO GPIO40
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO40PCTL_CTL_W                                       2U
#define IOMUX_GPIO40PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO40PCTL_CTL_S                                       0U
#define IOMUX_GPIO40PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO40PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO40PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO40PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO40PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO40PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO40PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO40PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO40PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO40PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO40PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO40PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO40PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO40PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO40CTL
    Offset name:         IOMUX_O_GPIO40CTL
    Relative address:    0x28008
    Description:         Control register of IO GPIO40
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO40CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO40CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO40CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO40CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO40CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO40CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO40CTL_OUT                                          0x00000100U
#define IOMUX_GPIO40CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO40CTL_OUT_S                                        8U
#define IOMUX_GPIO40CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO40CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO40CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO40CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO40CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO40CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO40CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO40ECTL
    Offset name:         IOMUX_O_GPIO40ECTL
    Relative address:    0x2800C
    Description:         Event control register for IO GPIO40
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO40ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO40ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO40ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO40ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO40ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO40ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO40ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO40ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO40ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO40ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO40ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO40ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO40ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO40ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO40ECTL_CLR_S                                       3U
#define IOMUX_GPIO40ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO40ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO41CFG
    Offset name:         IOMUX_O_GPIO41CFG
    Relative address:    0x29000
    Description:         CFG register for IO GPIO41. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO41CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO41CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO41CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO41CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO41CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO41CFG_IE                                           0x00000800U
#define IOMUX_GPIO41CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO41CFG_IE_S                                         11U
#define IOMUX_GPIO41CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO41CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO41CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO41CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO41CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO41CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO41CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO41CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO41CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO41CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO41CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO41CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO41CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO41CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO41CFG_IOSTR_S                                      14U
#define IOMUX_GPIO41CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO41CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO41PCTL
    Offset name:         IOMUX_O_GPIO41PCTL
    Relative address:    0x29004
    Description:         Pull control register of IO GPIO41
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO41PCTL_CTL_W                                       2U
#define IOMUX_GPIO41PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO41PCTL_CTL_S                                       0U
#define IOMUX_GPIO41PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO41PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO41PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO41PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO41PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO41PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO41PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO41PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO41PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO41PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO41PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO41PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO41PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO41PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO41CTL
    Offset name:         IOMUX_O_GPIO41CTL
    Relative address:    0x29008
    Description:         Control register of IO GPIO41
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO41CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO41CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO41CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO41CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO41CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO41CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO41CTL_OUT                                          0x00000100U
#define IOMUX_GPIO41CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO41CTL_OUT_S                                        8U
#define IOMUX_GPIO41CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO41CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO41CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO41CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO41CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO41CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO41CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO41ECTL
    Offset name:         IOMUX_O_GPIO41ECTL
    Relative address:    0x2900C
    Description:         Event control register for IO GPIO41
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO41ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO41ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO41ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO41ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO41ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO41ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO41ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO41ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO41ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO41ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO41ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO41ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO41ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO41ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO41ECTL_CLR_S                                       3U
#define IOMUX_GPIO41ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO41ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO42CFG
    Offset name:         IOMUX_O_GPIO42CFG
    Relative address:    0x2A000
    Description:         CFG register for IO GPIO42. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO42CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO42CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO42CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO42CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO42CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO42CFG_IE                                           0x00000800U
#define IOMUX_GPIO42CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO42CFG_IE_S                                         11U
#define IOMUX_GPIO42CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO42CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO42CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO42CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO42CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO42CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO42CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO42CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO42CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO42CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO42CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO42CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO42CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO42CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO42CFG_IOSTR_S                                      14U
#define IOMUX_GPIO42CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO42CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO42PCTL
    Offset name:         IOMUX_O_GPIO42PCTL
    Relative address:    0x2A004
    Description:         Pull control register of IO GPIO42
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO42PCTL_CTL_W                                       2U
#define IOMUX_GPIO42PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO42PCTL_CTL_S                                       0U
#define IOMUX_GPIO42PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO42PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO42PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO42PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO42PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO42PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO42PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO42PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO42PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO42PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO42PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO42PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO42PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO42PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO42CTL
    Offset name:         IOMUX_O_GPIO42CTL
    Relative address:    0x2A008
    Description:         Control register of IO GPIO42
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO42CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO42CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO42CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO42CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO42CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO42CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO42CTL_OUT                                          0x00000100U
#define IOMUX_GPIO42CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO42CTL_OUT_S                                        8U
#define IOMUX_GPIO42CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO42CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO42CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO42CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO42CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO42CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO42CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO42ECTL
    Offset name:         IOMUX_O_GPIO42ECTL
    Relative address:    0x2A00C
    Description:         Event control register for IO GPIO42
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO42ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO42ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO42ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO42ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO42ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO42ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO42ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO42ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO42ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO42ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO42ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO42ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO42ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO42ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO42ECTL_CLR_S                                       3U
#define IOMUX_GPIO42ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO42ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO43CFG
    Offset name:         IOMUX_O_GPIO43CFG
    Relative address:    0x2B000
    Description:         CFG register for IO GPIO43. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO43CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO43CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO43CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO43CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO43CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO43CFG_IE                                           0x00000800U
#define IOMUX_GPIO43CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO43CFG_IE_S                                         11U
#define IOMUX_GPIO43CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO43CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO43CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO43CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO43CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO43CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO43CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO43CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO43CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO43CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO43CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO43CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO43CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO43CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO43CFG_IOSTR_S                                      14U
#define IOMUX_GPIO43CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO43CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO43PCTL
    Offset name:         IOMUX_O_GPIO43PCTL
    Relative address:    0x2B004
    Description:         Pull control register of IO GPIO43
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO43PCTL_CTL_W                                       2U
#define IOMUX_GPIO43PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO43PCTL_CTL_S                                       0U
#define IOMUX_GPIO43PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO43PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO43PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO43PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO43PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO43PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO43PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO43PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO43PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO43PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO43PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO43PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO43PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO43PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO43CTL
    Offset name:         IOMUX_O_GPIO43CTL
    Relative address:    0x2B008
    Description:         Control register of IO GPIO43
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO43CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO43CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO43CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO43CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO43CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO43CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO43CTL_OUT                                          0x00000100U
#define IOMUX_GPIO43CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO43CTL_OUT_S                                        8U
#define IOMUX_GPIO43CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO43CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO43CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO43CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO43CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO43CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO43CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO43ECTL
    Offset name:         IOMUX_O_GPIO43ECTL
    Relative address:    0x2B00C
    Description:         Event control register for IO GPIO43
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO43ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO43ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO43ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO43ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO43ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO43ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO43ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO43ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO43ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO43ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO43ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO43ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO43ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO43ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO43ECTL_CLR_S                                       3U
#define IOMUX_GPIO43ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO43ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO44CFG
    Offset name:         IOMUX_O_GPIO44CFG
    Relative address:    0x2C000
    Description:         CFG register for IO GPIO44. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO44CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO44CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO44CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO44CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO44CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO44CFG_IE                                           0x00000800U
#define IOMUX_GPIO44CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO44CFG_IE_S                                         11U
#define IOMUX_GPIO44CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO44CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO44CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO44CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO44CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO44CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO44CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO44CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO44CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO44CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO44CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO44CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO44CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO44CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO44CFG_IOSTR_S                                      14U
#define IOMUX_GPIO44CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO44CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO44PCTL
    Offset name:         IOMUX_O_GPIO44PCTL
    Relative address:    0x2C004
    Description:         Pull control register of IO GPIO44
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO44PCTL_CTL_W                                       2U
#define IOMUX_GPIO44PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO44PCTL_CTL_S                                       0U
#define IOMUX_GPIO44PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO44PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO44PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO44PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO44PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO44PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO44PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO44PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO44PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO44PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO44PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO44PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO44PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO44PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO44CTL
    Offset name:         IOMUX_O_GPIO44CTL
    Relative address:    0x2C008
    Description:         Control register of IO GPIO44
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO44CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO44CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO44CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO44CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO44CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO44CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO44CTL_OUT                                          0x00000100U
#define IOMUX_GPIO44CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO44CTL_OUT_S                                        8U
#define IOMUX_GPIO44CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO44CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO44CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO44CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO44CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO44CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO44CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO44ECTL
    Offset name:         IOMUX_O_GPIO44ECTL
    Relative address:    0x2C00C
    Description:         Event control register for IO GPIO44
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO44ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO44ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO44ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO44ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO44ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO44ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO44ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO44ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO44ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO44ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO44ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO44ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO44ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO44ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO44ECTL_CLR_S                                       3U
#define IOMUX_GPIO44ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO44ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOPDIS
    Offset name:         IOMUX_O_SOPDIS
    Relative address:    0x2D000
    Description:         This register disables the SOP overrides when the device was powered in one of the SoP modes.
    Default Value:       NA

        Field:           MEM_SOP_DISABLE
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     The field is to disable SOP

        ENUMs:
            DISABLE:                     Disable SOP
            USE:                         Use SOP
*/
#define IOMUX_SOPDIS_MEM_SOP_DISABLE                                 0x00000001U
#define IOMUX_SOPDIS_MEM_SOP_DISABLE_M                               0x00000001U
#define IOMUX_SOPDIS_MEM_SOP_DISABLE_S                               0U
#define IOMUX_SOPDIS_MEM_SOP_DISABLE_DISABLE                         0x00000001U
#define IOMUX_SOPDIS_MEM_SOP_DISABLE_USE                             0x00000000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SCLKIPCFG
    Offset name:         IOMUX_O_SCLKIPCFG
    Relative address:    0x2D004
    Description:         Port configuration register for IO SLOW_CLOCK_IN
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- slow_clock_in
                         sel 5'd2 -- wifi_gpio_0
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- gpt0_1
                         sel 5'd21 -- coex_req


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       slow_clock_in
            SEL_2:                       wifi_gpio_0
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       gpt1_1
            SEL_10:                      gpt0_1
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      coex_req
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_SCLKIPCFG_IOSEL_W                                      5U
#define IOMUX_SCLKIPCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_SCLKIPCFG_IOSEL_S                                      0U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_SCLKIPCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_SCLKIPCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       LFXTNPCFG
    Offset name:         IOMUX_O_LFXTNPCFG
    Relative address:    0x2D008
    Description:         Port configuration register for IO LFXTAL_N
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- lfxt_n
                         sel 5'd2 -- wifi_gpio_1
                         sel 5'd7 -- gpt1_pre_event
                         sel 5'd8 -- gpt0_pre_event
                         sel 5'd9 -- gpt1_0
                         sel 5'd10 -- gpt0_0
                         sel 5'd11 -- gpt_infrared
                         sel 5'd19 -- sdio_oob_irq
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- coex_req
                         sel 5'd23 -- ant_sel_0


        ENUMs:
            SEL_0:                       lfxt_n
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_1
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       gpt1_pre_event
            SEL_8:                       gpt0_pre_event
            SEL_9:                       gpt1_0
            SEL_10:                      gpt0_0
            SEL_11:                      gpt_infrared
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      sdio_oob_irq
            SEL_20:                      coex_grant
            SEL_21:                      coex_req
            SEL_22:                      reserved
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_LFXTNPCFG_IOSEL_W                                      5U
#define IOMUX_LFXTNPCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_LFXTNPCFG_IOSEL_S                                      0U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_LFXTNPCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_LFXTNPCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO2PCFG
    Offset name:         IOMUX_O_GPIO2PCFG
    Relative address:    0x2D00C
    Description:         Port configuration register for IO GPIO2
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_ram
                         sel 5'd2 -- wifi_gpio_2
                         sel 5'd3 -- sdio_mmc_cd
                         sel 5'd6 -- i2c1_clk
                         sel 5'd9 -- gpt1_3
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- wake_observe_bus_6
                         sel 5'd12 -- debug_bus_4
                         sel 5'd16 -- spi0_cs4
                         sel 5'd18 -- gpt1_pre_event
                         sel 5'd19 -- sdio_oob_irq
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- coex_req
                         sel 5'd22 -- ble_rftrc
                         sel 5'd23 -- ant_sel_2
                         sel 5'd24 -- cca
                         sel 5'd26 -- trclk


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_ram
            SEL_2:                       wifi_gpio_2
            SEL_3:                       sdio_mmc_cd
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       i2c1_clk
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       gpt1_3
            SEL_10:                      dcan_tx
            SEL_11:                      wake_observe_bus_6
            SEL_12:                      debug_bus_4
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs4
            SEL_17:                      reserved
            SEL_18:                      gpt1_pre_event
            SEL_19:                      sdio_oob_irq
            SEL_20:                      coex_grant
            SEL_21:                      coex_req
            SEL_22:                      ble_rftrc
            SEL_23:                      ant_sel_2
            SEL_24:                      cca
            SEL_25:                      reserved
            SEL_26:                      trclk
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO2PCFG_IOSEL_W                                      5U
#define IOMUX_GPIO2PCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_GPIO2PCFG_IOSEL_S                                      0U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_GPIO2PCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_GPIO2PCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO3PCFG
    Offset name:         IOMUX_O_GPIO3PCFG
    Relative address:    0x2D010
    Description:         Port configuration register for IO GPIO3
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- uart1_tx
                         sel 5'd2 -- wifi_gpio_3
                         sel 5'd3 -- sdio_mmc_wp
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart1_rts
                         sel 5'd6 -- i2s_mclk
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt1_0
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- wake_observe_bus_7
                         sel 5'd12 -- debug_bus_0
                         sel 5'd16 -- spi0_cs3
                         sel 5'd17 -- xspi_cs_ram
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd19 -- sdio_clk
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- gpt0_0_n
                         sel 5'd22 -- gpt_infrared
                         sel 5'd23 -- ant_sel_3
                         sel 5'd24 -- ble_rfc_gpo_7
                         sel 5'd25 -- swo_m3
                         sel 5'd27 -- swo_m33
                         sel 5'd28 -- i2c1_data
                         sel 5'd30 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       uart1_tx
            SEL_2:                       wifi_gpio_3
            SEL_3:                       sdio_mmc_wp
            SEL_4:                       spi1_clk
            SEL_5:                       uart1_rts
            SEL_6:                       i2s_mclk
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data1
            SEL_9:                       gpt1_0
            SEL_10:                      dcan_rx
            SEL_11:                      wake_observe_bus_7
            SEL_12:                      debug_bus_0
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs3
            SEL_17:                      xspi_cs_ram
            SEL_18:                      gpt1_1_n
            SEL_19:                      sdio_clk
            SEL_20:                      coex_req
            SEL_21:                      gpt0_0_n
            SEL_22:                      gpt_infrared
            SEL_23:                      ant_sel_3
            SEL_24:                      ble_rfc_gpo_7
            SEL_25:                      swo_m3
            SEL_26:                      reserved
            SEL_27:                      swo_m33
            SEL_28:                      i2c1_data
            SEL_29:                      reserved
            SEL_30:                      uart2_tx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO3PCFG_IOSEL_W                                      5U
#define IOMUX_GPIO3PCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_GPIO3PCFG_IOSEL_S                                      0U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_GPIO3PCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_GPIO3PCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO4PCFG
    Offset name:         IOMUX_O_GPIO4PCFG
    Relative address:    0x2D014
    Description:         Port configuration register for IO GPIO4
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- uart1_rx
                         sel 5'd2 -- wifi_gpio_4
                         sel 5'd3 -- sdio_mmc_cd
                         sel 5'd4 -- spi1_cs1
                         sel 5'd5 -- uart1_cts
                         sel 5'd6 -- i2s_bclk
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- wake_observe_bus_8
                         sel 5'd12 -- debug_bus_1
                         sel 5'd16 -- spi0_cs2
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd19 -- sdio_cmd
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- gpt0_1_n
                         sel 5'd24 -- ble_rfc_gpo_6
                         sel 5'd28 -- i2c1_clk
                         sel 5'd30 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       uart1_rx
            SEL_2:                       wifi_gpio_4
            SEL_3:                       sdio_mmc_cd
            SEL_4:                       spi1_cs1
            SEL_5:                       uart1_cts
            SEL_6:                       i2s_bclk
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt1_1
            SEL_10:                      dcan_tx
            SEL_11:                      wake_observe_bus_8
            SEL_12:                      debug_bus_1
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs2
            SEL_17:                      ext_clk
            SEL_18:                      gpt1_0_n
            SEL_19:                      sdio_cmd
            SEL_20:                      coex_priority
            SEL_21:                      gpt0_1_n
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      ble_rfc_gpo_6
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      i2c1_clk
            SEL_29:                      reserved
            SEL_30:                      uart2_rx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO4PCFG_IOSEL_W                                      5U
#define IOMUX_GPIO4PCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_GPIO4PCFG_IOSEL_S                                      0U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_GPIO4PCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_GPIO4PCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO5PCFG
    Offset name:         IOMUX_O_GPIO5PCFG
    Relative address:    0x2D018
    Description:         Port configuration register for IO GPIO5
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_ram
                         sel 5'd2 -- wifi_gpio_5
                         sel 5'd3 -- sdio_mmc_pow2
                         sel 5'd4 -- spi1_miso
                         sel 5'd5 -- uart1_tx
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_mclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt1_2
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- jtag_tdi
                         sel 5'd12 -- debug_bus_11
                         sel 5'd16 -- spi0_cs4
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd19 -- sdio_d0
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- gpt0_2_n
                         sel 5'd22 -- ble_rftrc
                         sel 5'd23 -- ant_sel_1
                         sel 5'd25 -- ble_rfc_gpi_2
                         sel 5'd28 -- i2c1_data
                         sel 5'd30 -- uart2_rts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_ram
            SEL_2:                       wifi_gpio_5
            SEL_3:                       sdio_mmc_pow2
            SEL_4:                       spi1_miso
            SEL_5:                       uart1_tx
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_mclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt1_2
            SEL_10:                      dcan_tx
            SEL_11:                      jtag_tdi
            SEL_12:                      debug_bus_11
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs4
            SEL_17:                      ext_clk
            SEL_18:                      gpt1_0_n
            SEL_19:                      sdio_d0
            SEL_20:                      coex_req
            SEL_21:                      gpt0_2_n
            SEL_22:                      ble_rftrc
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      i2c1_data
            SEL_29:                      reserved
            SEL_30:                      uart2_rts
            SEL_31:                      reserved
*/
#define IOMUX_GPIO5PCFG_IOSEL_W                                      5U
#define IOMUX_GPIO5PCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_GPIO5PCFG_IOSEL_S                                      0U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_GPIO5PCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_GPIO5PCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO6PCFG
    Offset name:         IOMUX_O_GPIO6PCFG
    Relative address:    0x2D01C
    Description:         Port configuration register for IO GPIO6
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_6
                         sel 5'd3 -- sdio_mmc_pow1
                         sel 5'd4 -- spi1_mosi
                         sel 5'd5 -- uart1_rx
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt1_3
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- sdio_mmc_wp
                         sel 5'd12 -- debug_bus_12
                         sel 5'd16 -- spi0_cs4
                         sel 5'd17 -- i2s_bclk
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd19 -- sdio_d1
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- gpt0_3_n
                         sel 5'd22 -- gpt1_pre_event
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- cca
                         sel 5'd25 -- ble_rfc_gpi_3
                         sel 5'd26 -- coex_grant
                         sel 5'd28 -- i2c1_clk
                         sel 5'd29 -- sdio_mmc_pow2
                         sel 5'd30 -- uart2_cts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_6
            SEL_3:                       sdio_mmc_pow1
            SEL_4:                       spi1_mosi
            SEL_5:                       uart1_rx
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_data0
            SEL_9:                       gpt1_3
            SEL_10:                      dcan_rx
            SEL_11:                      sdio_mmc_wp
            SEL_12:                      debug_bus_12
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs4
            SEL_17:                      i2s_bclk
            SEL_18:                      gpt1_1_n
            SEL_19:                      sdio_d1
            SEL_20:                      coex_priority
            SEL_21:                      gpt0_3_n
            SEL_22:                      gpt1_pre_event
            SEL_23:                      ant_sel_0
            SEL_24:                      cca
            SEL_25:                      ble_rfc_gpi_3
            SEL_26:                      coex_grant
            SEL_27:                      reserved
            SEL_28:                      i2c1_clk
            SEL_29:                      sdio_mmc_pow2
            SEL_30:                      uart2_cts
            SEL_31:                      reserved
*/
#define IOMUX_GPIO6PCFG_IOSEL_W                                      5U
#define IOMUX_GPIO6PCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_GPIO6PCFG_IOSEL_S                                      0U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_GPIO6PCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_GPIO6PCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWDIOPCFG
    Offset name:         IOMUX_O_SWDIOPCFG
    Relative address:    0x2D020
    Description:         Port configuration register for IO SWDIO
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- swdio
                         sel 5'd2 -- wifi_gpio_7
                         sel 5'd3 -- sdio_mmc_pow2
                         sel 5'd4 -- jtag_tms
                         sel 5'd23 -- ant_sel_0


        ENUMs:
            SEL_0:                       swdio
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_7
            SEL_3:                       sdio_mmc_pow2
            SEL_4:                       jtag_tms
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_SWDIOPCFG_IOSEL_W                                      5U
#define IOMUX_SWDIOPCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_SWDIOPCFG_IOSEL_S                                      0U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_SWDIOPCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_SWDIOPCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWCLKPCFG
    Offset name:         IOMUX_O_SWCLKPCFG
    Relative address:    0x2D024
    Description:         Port configuration register for IO SWCLK
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- swclk
                         sel 5'd2 -- wifi_gpio_8
                         sel 5'd3 -- sdio_mmc_pow1
                         sel 5'd4 -- jtag_tck
                         sel 5'd23 -- ant_sel_1


        ENUMs:
            SEL_0:                       swclk
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_8
            SEL_3:                       sdio_mmc_pow1
            SEL_4:                       jtag_tck
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_SWCLKPCFG_IOSEL_W                                      5U
#define IOMUX_SWCLKPCFG_IOSEL_M                                      0x0000001FU
#define IOMUX_SWCLKPCFG_IOSEL_S                                      0U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_0                                  0x00000000U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_1                                  0x00000001U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_2                                  0x00000002U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_3                                  0x00000003U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_4                                  0x00000004U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_5                                  0x00000005U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_6                                  0x00000006U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_7                                  0x00000007U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_8                                  0x00000008U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_9                                  0x00000009U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_10                                 0x0000000AU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_11                                 0x0000000BU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_12                                 0x0000000CU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_13                                 0x0000000DU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_14                                 0x0000000EU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_15                                 0x0000000FU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_16                                 0x00000010U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_17                                 0x00000011U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_18                                 0x00000012U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_19                                 0x00000013U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_20                                 0x00000014U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_21                                 0x00000015U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_22                                 0x00000016U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_23                                 0x00000017U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_24                                 0x00000018U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_25                                 0x00000019U
#define IOMUX_SWCLKPCFG_IOSEL_SEL_26                                 0x0000001AU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_27                                 0x0000001BU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_28                                 0x0000001CU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_29                                 0x0000001DU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_30                                 0x0000001EU
#define IOMUX_SWCLKPCFG_IOSEL_SEL_31                                 0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       LOGGERPCFG
    Offset name:         IOMUX_O_LOGGERPCFG
    Relative address:    0x2D028
    Description:         Port configuration register for IO LOGGER
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- logger
                         sel 5'd2 -- wifi_gpio_9
                         sel 5'd3 -- sdio_mmc_cd
                         sel 5'd4 -- ble_rftrc
                         sel 5'd11 -- jtag_tdo
                         sel 5'd23 -- ant_sel_2
                         sel 5'd26 -- swo_m3
                         sel 5'd27 -- swo_m33


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       logger
            SEL_2:                       wifi_gpio_9
            SEL_3:                       sdio_mmc_cd
            SEL_4:                       ble_rftrc
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      jtag_tdo
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_2
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      swo_m3
            SEL_27:                      swo_m33
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_LOGGERPCFG_IOSEL_W                                     5U
#define IOMUX_LOGGERPCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_LOGGERPCFG_IOSEL_S                                     0U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_LOGGERPCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_LOGGERPCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO10PCFG
    Offset name:         IOMUX_O_GPIO10PCFG
    Relative address:    0x2D02C
    Description:         Port configuration register for IO GPIO10
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- uart1_tx
                         sel 5'd2 -- wifi_gpio_10
                         sel 5'd3 -- sdio_mmc_data_3
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart1_rts
                         sel 5'd6 -- i2c1_data
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt1_0
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- uart_rs232_rx
                         sel 5'd12 -- debug_bus_10
                         sel 5'd16 -- spi0_cs3
                         sel 5'd18 -- gpt1_3_n
                         sel 5'd19 -- sdio_d3
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- coex_grant
                         sel 5'd23 -- ant_sel_2
                         sel 5'd24 -- cca
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd26 -- trdata_0
                         sel 5'd30 -- uart2_rts
                         sel 5'd31 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       uart1_tx
            SEL_2:                       wifi_gpio_10
            SEL_3:                       sdio_mmc_data_3
            SEL_4:                       spi1_clk
            SEL_5:                       uart1_rts
            SEL_6:                       i2c1_data
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_data1
            SEL_9:                       gpt1_0
            SEL_10:                      dcan_rx
            SEL_11:                      uart_rs232_rx
            SEL_12:                      debug_bus_10
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs3
            SEL_17:                      reserved
            SEL_18:                      gpt1_3_n
            SEL_19:                      sdio_d3
            SEL_20:                      coex_priority
            SEL_21:                      coex_grant
            SEL_22:                      reserved
            SEL_23:                      ant_sel_2
            SEL_24:                      cca
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      trdata_0
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      uart2_rts
            SEL_31:                      uart2_tx
*/
#define IOMUX_GPIO10PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO10PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO10PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO10PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO10PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO11PCFG
    Offset name:         IOMUX_O_GPIO11PCFG
    Relative address:    0x2D030
    Description:         Port configuration register for IO GPIO11
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- uart1_rx
                         sel 5'd2 -- wifi_gpio_11
                         sel 5'd3 -- sdio_mmc_data_2
                         sel 5'd4 -- spi1_cs1
                         sel 5'd5 -- uart1_cts
                         sel 5'd6 -- i2c1_clk
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- uart_rs232_tx
                         sel 5'd12 -- debug_bus_9
                         sel 5'd16 -- spi0_cs2
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt1_2_n
                         sel 5'd19 -- sdio_d2
                         sel 5'd20 -- coex_req
                         sel 5'd23 -- ant_sel_3
                         sel 5'd24 -- cca
                         sel 5'd25 -- swo_m3
                         sel 5'd26 -- trdata_1
                         sel 5'd30 -- uart2_cts
                         sel 5'd31 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       uart1_rx
            SEL_2:                       wifi_gpio_11
            SEL_3:                       sdio_mmc_data_2
            SEL_4:                       spi1_cs1
            SEL_5:                       uart1_cts
            SEL_6:                       i2c1_clk
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data0
            SEL_9:                       gpt1_1
            SEL_10:                      dcan_tx
            SEL_11:                      uart_rs232_tx
            SEL_12:                      debug_bus_9
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs2
            SEL_17:                      ext_clk
            SEL_18:                      gpt1_2_n
            SEL_19:                      sdio_d2
            SEL_20:                      coex_req
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_3
            SEL_24:                      cca
            SEL_25:                      swo_m3
            SEL_26:                      trdata_1
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      uart2_cts
            SEL_31:                      uart2_rx
*/
#define IOMUX_GPIO11PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO11PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO11PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO11PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO11PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO12PCFG
    Offset name:         IOMUX_O_GPIO12PCFG
    Relative address:    0x2D034
    Description:         Port configuration register for IO GPIO12
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_12
                         sel 5'd3 -- sdio_mmc_data_1
                         sel 5'd4 -- spi1_cs1
                         sel 5'd5 -- uart1_rts
                         sel 5'd6 -- uart0_rts
                         sel 5'd7 -- i2s_wclk
                         sel 5'd9 -- gpt1_2
                         sel 5'd10 -- uart_rs232_tx
                         sel 5'd11 -- jtag_tdo
                         sel 5'd12 -- debug_bus_8
                         sel 5'd16 -- gpt0_pre_event
                         sel 5'd17 -- gpt1_pre_event
                         sel 5'd18 -- gpt1_3_n
                         sel 5'd19 -- sdio_clk
                         sel 5'd22 -- ble_rfc_gpo_7
                         sel 5'd23 -- ant_sel_1
                         sel 5'd25 -- ble_rfc_gpi_2
                         sel 5'd26 -- trdata_2
                         sel 5'd31 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_12
            SEL_3:                       sdio_mmc_data_1
            SEL_4:                       spi1_cs1
            SEL_5:                       uart1_rts
            SEL_6:                       uart0_rts
            SEL_7:                       i2s_wclk
            SEL_8:                       reserved
            SEL_9:                       gpt1_2
            SEL_10:                      uart_rs232_tx
            SEL_11:                      jtag_tdo
            SEL_12:                      debug_bus_8
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      gpt0_pre_event
            SEL_17:                      gpt1_pre_event
            SEL_18:                      gpt1_3_n
            SEL_19:                      sdio_clk
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_7
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      trdata_2
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      uart2_tx
*/
#define IOMUX_GPIO12PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO12PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO12PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO12PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO12PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO13PCFG
    Offset name:         IOMUX_O_GPIO13PCFG
    Relative address:    0x2D038
    Description:         Port configuration register for IO GPIO13
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_13
                         sel 5'd3 -- sdio_mmc_data_0
                         sel 5'd4 -- spi1_mosi
                         sel 5'd5 -- uart1_cts
                         sel 5'd6 -- uart0_tx
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- i2s_mclk
                         sel 5'd9 -- gpt1_3
                         sel 5'd11 -- wake_observe_bus_14
                         sel 5'd12 -- debug_bus_7
                         sel 5'd18 -- gpt1_2_n
                         sel 5'd19 -- sdio_cmd
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- ble_rftrc
                         sel 5'd22 -- ble_rfc_gpo_6
                         sel 5'd23 -- ant_sel_0
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd26 -- trdata_3
                         sel 5'd31 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_13
            SEL_3:                       sdio_mmc_data_0
            SEL_4:                       spi1_mosi
            SEL_5:                       uart1_cts
            SEL_6:                       uart0_tx
            SEL_7:                       i2s_bclk
            SEL_8:                       i2s_mclk
            SEL_9:                       gpt1_3
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_14
            SEL_12:                      debug_bus_7
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      gpt1_2_n
            SEL_19:                      sdio_cmd
            SEL_20:                      coex_priority
            SEL_21:                      ble_rftrc
            SEL_22:                      ble_rfc_gpo_6
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      trdata_3
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      uart2_rx
*/
#define IOMUX_GPIO13PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO13PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO13PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO13PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO13PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO14PCFG
    Offset name:         IOMUX_O_GPIO14PCFG
    Relative address:    0x2D03C
    Description:         Port configuration register for IO GPIO14
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_14
                         sel 5'd3 -- sdio_mmc_clk
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart1_tx
                         sel 5'd6 -- uart0_rx
                         sel 5'd9 -- gpt1_0
                         sel 5'd11 -- wake_observe_bus_15
                         sel 5'd12 -- debug_bus_clk
                         sel 5'd16 -- spi0_cs2
                         sel 5'd17 -- gpt1_pre_event
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd19 -- sdio_d0
                         sel 5'd20 -- coex_grant
                         sel 5'd22 -- ble_rfc_gpo_4
                         sel 5'd24 -- ble_rfc_gpi_2
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd26 -- trclk
                         sel 5'd27 -- digital_fast_clk_in


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_14
            SEL_3:                       sdio_mmc_clk
            SEL_4:                       spi1_clk
            SEL_5:                       uart1_tx
            SEL_6:                       uart0_rx
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       gpt1_0
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_15
            SEL_12:                      debug_bus_clk
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs2
            SEL_17:                      gpt1_pre_event
            SEL_18:                      gpt1_1_n
            SEL_19:                      sdio_d0
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_4
            SEL_23:                      reserved
            SEL_24:                      ble_rfc_gpi_2
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      trclk
            SEL_27:                      digital_fast_clk_in
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO14PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO14PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO14PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO14PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO14PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO15PCFG
    Offset name:         IOMUX_O_GPIO15PCFG
    Relative address:    0x2D040
    Description:         Port configuration register for IO GPIO15
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_15
                         sel 5'd3 -- sdio_mmc_cmd
                         sel 5'd4 -- spi1_miso
                         sel 5'd5 -- uart1_rx
                         sel 5'd6 -- uart0_cts
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- uart_rs232_rx
                         sel 5'd11 -- jtag_tdi
                         sel 5'd12 -- debug_bus_6
                         sel 5'd16 -- spi1_cs2
                         sel 5'd17 -- gpt0_pre_event
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd19 -- sdio_d1
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- ble_rftrc
                         sel 5'd22 -- ble_rfc_gpo_5
                         sel 5'd25 -- ble_rfc_gpi_3
                         sel 5'd26 -- swo_m3
                         sel 5'd27 -- swo_m33


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_15
            SEL_3:                       sdio_mmc_cmd
            SEL_4:                       spi1_miso
            SEL_5:                       uart1_rx
            SEL_6:                       uart0_cts
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       gpt1_1
            SEL_10:                      uart_rs232_rx
            SEL_11:                      jtag_tdi
            SEL_12:                      debug_bus_6
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs2
            SEL_17:                      gpt0_pre_event
            SEL_18:                      gpt1_0_n
            SEL_19:                      sdio_d1
            SEL_20:                      coex_req
            SEL_21:                      ble_rftrc
            SEL_22:                      ble_rfc_gpo_5
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_3
            SEL_26:                      swo_m3
            SEL_27:                      swo_m33
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO15PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO15PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO15PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO15PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO15PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO16PCFG
    Offset name:         IOMUX_O_GPIO16PCFG
    Relative address:    0x2D044
    Description:         Port configuration register for IO GPIO16
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_16
                         sel 5'd3 -- sdio_mmc_data_7
                         sel 5'd4 -- spi0_cs1
                         sel 5'd5 -- uart0_rts
                         sel 5'd6 -- i2c1_data
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt0_0
                         sel 5'd10 -- uart_rs232_rx
                         sel 5'd11 -- wake_observe_bus_12
                         sel 5'd12 -- debug_bus_5
                         sel 5'd16 -- spi1_cs2
                         sel 5'd18 -- gpt0_1_n
                         sel 5'd19 -- sdio_d2
                         sel 5'd21 -- gpt1_0_n
                         sel 5'd22 -- gpt_infrared
                         sel 5'd23 -- ant_sel_0
                         sel 5'd26 -- trdata_0
                         sel 5'd30 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_16
            SEL_3:                       sdio_mmc_data_7
            SEL_4:                       spi0_cs1
            SEL_5:                       uart0_rts
            SEL_6:                       i2c1_data
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt0_0
            SEL_10:                      uart_rs232_rx
            SEL_11:                      wake_observe_bus_12
            SEL_12:                      debug_bus_5
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs2
            SEL_17:                      reserved
            SEL_18:                      gpt0_1_n
            SEL_19:                      sdio_d2
            SEL_20:                      reserved
            SEL_21:                      gpt1_0_n
            SEL_22:                      gpt_infrared
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      trdata_0
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      uart2_tx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO16PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO16PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO16PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO16PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO16PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO17PCFG
    Offset name:         IOMUX_O_GPIO17PCFG
    Relative address:    0x2D048
    Description:         Port configuration register for IO GPIO17
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- sdio_mmc_wp
                         sel 5'd2 -- wifi_gpio_17
                         sel 5'd3 -- sdio_mmc_data_6
                         sel 5'd4 -- spi0_clk
                         sel 5'd5 -- uart0_tx
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt0_1
                         sel 5'd10 -- uart_rs232_tx
                         sel 5'd11 -- wake_observe_bus_9
                         sel 5'd12 -- debug_bus_2
                         sel 5'd16 -- spi1_cs3
                         sel 5'd17 -- sdio_oob_irq
                         sel 5'd18 -- gpt0_0_n
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- gpt1_1_n
                         sel 5'd23 -- ant_sel_1
                         sel 5'd26 -- trdata_1


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       sdio_mmc_wp
            SEL_2:                       wifi_gpio_17
            SEL_3:                       sdio_mmc_data_6
            SEL_4:                       spi0_clk
            SEL_5:                       uart0_tx
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_data0
            SEL_9:                       gpt0_1
            SEL_10:                      uart_rs232_tx
            SEL_11:                      wake_observe_bus_9
            SEL_12:                      debug_bus_2
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs3
            SEL_17:                      sdio_oob_irq
            SEL_18:                      gpt0_0_n
            SEL_19:                      reserved
            SEL_20:                      coex_grant
            SEL_21:                      gpt1_1_n
            SEL_22:                      reserved
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      trdata_1
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO17PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO17PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO17PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO17PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO17PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO18PCFG
    Offset name:         IOMUX_O_GPIO18PCFG
    Relative address:    0x2D04C
    Description:         Port configuration register for IO GPIO18
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_18
                         sel 5'd3 -- sdio_mmc_data_5
                         sel 5'd4 -- spi0_miso
                         sel 5'd5 -- uart0_rx
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt0_2
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- wake_observe_bus_10
                         sel 5'd12 -- debug_bus_3
                         sel 5'd16 -- spi1_cs4
                         sel 5'd17 -- sdio_oob_irq
                         sel 5'd18 -- gpt0_0_n
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- gpt1_2_n
                         sel 5'd23 -- ant_sel_2
                         sel 5'd26 -- trdata_2


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_18
            SEL_3:                       sdio_mmc_data_5
            SEL_4:                       spi0_miso
            SEL_5:                       uart0_rx
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data1
            SEL_9:                       gpt0_2
            SEL_10:                      dcan_tx
            SEL_11:                      wake_observe_bus_10
            SEL_12:                      debug_bus_3
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs4
            SEL_17:                      sdio_oob_irq
            SEL_18:                      gpt0_0_n
            SEL_19:                      reserved
            SEL_20:                      coex_req
            SEL_21:                      gpt1_2_n
            SEL_22:                      reserved
            SEL_23:                      ant_sel_2
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      trdata_2
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO18PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO18PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO18PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO18PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO18PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO19PCFG
    Offset name:         IOMUX_O_GPIO19PCFG
    Relative address:    0x2D050
    Description:         Port configuration register for IO GPIO19
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_19
                         sel 5'd3 -- sdio_mmc_data_4
                         sel 5'd4 -- spi0_mosi
                         sel 5'd5 -- uart0_cts
                         sel 5'd6 -- i2c1_clk
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt0_3
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- wake_observe_bus_11
                         sel 5'd12 -- debug_bus_4
                         sel 5'd16 -- gpt0_pre_event
                         sel 5'd17 -- sdio_oob_irq
                         sel 5'd18 -- gpt0_1_n
                         sel 5'd19 -- sdio_d3
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- gpt1_3_n
                         sel 5'd22 -- gpt_infrared
                         sel 5'd23 -- ant_sel_3
                         sel 5'd26 -- trdata_3
                         sel 5'd30 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_19
            SEL_3:                       sdio_mmc_data_4
            SEL_4:                       spi0_mosi
            SEL_5:                       uart0_cts
            SEL_6:                       i2c1_clk
            SEL_7:                       i2s_bclk
            SEL_8:                       pdm_data0
            SEL_9:                       gpt0_3
            SEL_10:                      dcan_rx
            SEL_11:                      wake_observe_bus_11
            SEL_12:                      debug_bus_4
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      gpt0_pre_event
            SEL_17:                      sdio_oob_irq
            SEL_18:                      gpt0_1_n
            SEL_19:                      sdio_d3
            SEL_20:                      coex_priority
            SEL_21:                      gpt1_3_n
            SEL_22:                      gpt_infrared
            SEL_23:                      ant_sel_3
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      trdata_3
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      uart2_rx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO19PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO19PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO19PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO19PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO19PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO20PCFG
    Offset name:         IOMUX_O_GPIO20PCFG
    Relative address:    0x2D054
    Description:         Port configuration register for IO GPIO20
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_cs_flash
                         sel 5'd2 -- wifi_gpio_20


        ENUMs:
            SEL_0:                       xspi_cs_flash
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_20
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO20PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO20PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO20PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO20PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO20PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO21PCFG
    Offset name:         IOMUX_O_GPIO21PCFG
    Relative address:    0x2D058
    Description:         Port configuration register for IO GPIO21
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_1
                         sel 5'd2 -- wifi_gpio_21


        ENUMs:
            SEL_0:                       xspi_data_1
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_21
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO21PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO21PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO21PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO21PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO21PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO22PCFG
    Offset name:         IOMUX_O_GPIO22PCFG
    Relative address:    0x2D05C
    Description:         Port configuration register for IO GPIO22
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_2
                         sel 5'd2 -- wifi_gpio_22


        ENUMs:
            SEL_0:                       xspi_data_2
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_22
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO22PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO22PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO22PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO22PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO22PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO23PCFG
    Offset name:         IOMUX_O_GPIO23PCFG
    Relative address:    0x2D060
    Description:         Port configuration register for IO GPIO23
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_3
                         sel 5'd2 -- wifi_gpio_23


        ENUMs:
            SEL_0:                       xspi_data_3
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_23
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO23PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO23PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO23PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO23PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO23PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO24PCFG
    Offset name:         IOMUX_O_GPIO24PCFG
    Relative address:    0x2D064
    Description:         Port configuration register for IO GPIO24
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_clk
                         sel 5'd2 -- wifi_gpio_24


        ENUMs:
            SEL_0:                       xspi_clk
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_24
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO24PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO24PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO24PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO24PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO24PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO25PCFG
    Offset name:         IOMUX_O_GPIO25PCFG
    Relative address:    0x2D068
    Description:         Port configuration register for IO GPIO25
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_0
                         sel 5'd2 -- wifi_gpio_25


        ENUMs:
            SEL_0:                       xspi_data_0
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_25
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO25PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO25PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO25PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO25PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO25PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO26PCFG
    Offset name:         IOMUX_O_GPIO26PCFG
    Relative address:    0x2D06C
    Description:         Port configuration register for IO GPIO26
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_data_4
                         sel 5'd2 -- wifi_gpio_26
                         sel 5'd4 -- spi0_cs1
                         sel 5'd5 -- uart0_rts
                         sel 5'd6 -- i2c1_clk
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt0_0
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- wake_observe_bus_0
                         sel 5'd12 -- debug_bus_13
                         sel 5'd16 -- spi1_cs2
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt0_1_n
                         sel 5'd19 -- gpt1_0_n
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- coex_req
                         sel 5'd22 -- ble_rfc_gpo_4
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- gpt_infrared
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd26 -- ble_rfc_gpi_3
                         sel 5'd30 -- sdio_oob_irq
                         sel 5'd31 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_data_4
            SEL_2:                       wifi_gpio_26
            SEL_3:                       reserved
            SEL_4:                       spi0_cs1
            SEL_5:                       uart0_rts
            SEL_6:                       i2c1_clk
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt0_0
            SEL_10:                      dcan_tx
            SEL_11:                      wake_observe_bus_0
            SEL_12:                      debug_bus_13
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs2
            SEL_17:                      ext_clk
            SEL_18:                      gpt0_1_n
            SEL_19:                      gpt1_0_n
            SEL_20:                      coex_grant
            SEL_21:                      coex_req
            SEL_22:                      ble_rfc_gpo_4
            SEL_23:                      ant_sel_0
            SEL_24:                      gpt_infrared
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      ble_rfc_gpi_3
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_oob_irq
            SEL_31:                      uart2_tx
*/
#define IOMUX_GPIO26PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO26PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO26PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO26PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO26PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO27PCFG
    Offset name:         IOMUX_O_GPIO27PCFG
    Relative address:    0x2D070
    Description:         Port configuration register for IO GPIO27
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_data_5
                         sel 5'd2 -- wifi_gpio_27
                         sel 5'd4 -- spi0_clk
                         sel 5'd5 -- uart0_tx
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt0_1
                         sel 5'd11 -- wake_observe_bus_1
                         sel 5'd12 -- debug_bus_14
                         sel 5'd16 -- spi1_cs3
                         sel 5'd18 -- gpt0_0_n
                         sel 5'd19 -- gpt1_1_n
                         sel 5'd20 -- coex_req
                         sel 5'd22 -- ble_rfc_gpo_5
                         sel 5'd23 -- ant_sel_1
                         sel 5'd25 -- ble_rfc_gpi_2
                         sel 5'd31 -- uart2_rts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_data_5
            SEL_2:                       wifi_gpio_27
            SEL_3:                       reserved
            SEL_4:                       spi0_clk
            SEL_5:                       uart0_tx
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data0
            SEL_9:                       gpt0_1
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_1
            SEL_12:                      debug_bus_14
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs3
            SEL_17:                      reserved
            SEL_18:                      gpt0_0_n
            SEL_19:                      gpt1_1_n
            SEL_20:                      coex_req
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_5
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      uart2_rts
*/
#define IOMUX_GPIO27PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO27PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO27PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO27PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO27PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO28PCFG
    Offset name:         IOMUX_O_GPIO28PCFG
    Relative address:    0x2D074
    Description:         Port configuration register for IO GPIO28
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_data_6
                         sel 5'd2 -- wifi_gpio_28
                         sel 5'd4 -- spi0_miso
                         sel 5'd5 -- uart0_rx
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt0_2
                         sel 5'd11 -- wake_observe_bus_2
                         sel 5'd12 -- debug_bus_15
                         sel 5'd16 -- spi1_cs4
                         sel 5'd18 -- gpt0_0_n
                         sel 5'd19 -- gpt1_2_n
                         sel 5'd20 -- coex_priority
                         sel 5'd22 -- ble_rfc_gpo_6
                         sel 5'd23 -- ant_sel_2
                         sel 5'd24 -- gpt0_pre_event
                         sel 5'd25 -- ble_rfc_gpi_3
                         sel 5'd31 -- uart2_cts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_data_6
            SEL_2:                       wifi_gpio_28
            SEL_3:                       reserved
            SEL_4:                       spi0_miso
            SEL_5:                       uart0_rx
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt0_2
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_2
            SEL_12:                      debug_bus_15
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs4
            SEL_17:                      reserved
            SEL_18:                      gpt0_0_n
            SEL_19:                      gpt1_2_n
            SEL_20:                      coex_priority
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_6
            SEL_23:                      ant_sel_2
            SEL_24:                      gpt0_pre_event
            SEL_25:                      ble_rfc_gpi_3
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      uart2_cts
*/
#define IOMUX_GPIO28PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO28PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO28PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO28PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO28PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO29PCFG
    Offset name:         IOMUX_O_GPIO29PCFG
    Relative address:    0x2D078
    Description:         Port configuration register for IO GPIO29
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_data_7
                         sel 5'd2 -- wifi_gpio_29
                         sel 5'd4 -- spi0_mosi
                         sel 5'd5 -- uart0_cts
                         sel 5'd6 -- i2c1_data
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt0_3
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- wake_observe_bus_3
                         sel 5'd12 -- i2s_mclk
                         sel 5'd16 -- spi1_cs4
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt0_1_n
                         sel 5'd19 -- gpt1_3_n
                         sel 5'd20 -- coex_grant
                         sel 5'd22 -- ble_rfc_gpo_7
                         sel 5'd23 -- ant_sel_3
                         sel 5'd30 -- sdio_oob_irq
                         sel 5'd31 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_data_7
            SEL_2:                       wifi_gpio_29
            SEL_3:                       reserved
            SEL_4:                       spi0_mosi
            SEL_5:                       uart0_cts
            SEL_6:                       i2c1_data
            SEL_7:                       i2s_bclk
            SEL_8:                       pdm_data1
            SEL_9:                       gpt0_3
            SEL_10:                      dcan_rx
            SEL_11:                      wake_observe_bus_3
            SEL_12:                      i2s_mclk
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi1_cs4
            SEL_17:                      ext_clk
            SEL_18:                      gpt0_1_n
            SEL_19:                      gpt1_3_n
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_7
            SEL_23:                      ant_sel_3
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_oob_irq
            SEL_31:                      uart2_rx
*/
#define IOMUX_GPIO29PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO29PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO29PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO29PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO29PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO30PCFG
    Offset name:         IOMUX_O_GPIO30PCFG
    Relative address:    0x2D07C
    Description:         Port configuration register for IO GPIO30
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_dqs
                         sel 5'd2 -- wifi_gpio_30
                         sel 5'd3 -- xspi_reset_flash
                         sel 5'd4 -- xspi_reset_ram
                         sel 5'd5 -- i2c1_clk
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- dcan_tx
                         sel 5'd11 -- wake_observe_bus_4
                         sel 5'd12 -- xspi_cs_ram
                         sel 5'd16 -- spi0_cs2
                         sel 5'd17 -- spi0_cs2
                         sel 5'd18 -- gpt0_2_n
                         sel 5'd19 -- coex_grant
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- ble_rftrc
                         sel 5'd22 -- ble_rfc_gpo_4
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- cca
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd26 -- swo_m3
                         sel 5'd27 -- swo_m33
                         sel 5'd28 -- gpt1_pre_event
                         sel 5'd29 -- gpt0_pre_event
                         sel 5'd30 -- sdio_d3
                         sel 5'd31 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_dqs
            SEL_2:                       wifi_gpio_30
            SEL_3:                       xspi_reset_flash
            SEL_4:                       xspi_reset_ram
            SEL_5:                       i2c1_clk
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data0
            SEL_9:                       gpt1_1
            SEL_10:                      dcan_tx
            SEL_11:                      wake_observe_bus_4
            SEL_12:                      xspi_cs_ram
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs2
            SEL_17:                      spi0_cs2
            SEL_18:                      gpt0_2_n
            SEL_19:                      coex_grant
            SEL_20:                      coex_req
            SEL_21:                      ble_rftrc
            SEL_22:                      ble_rfc_gpo_4
            SEL_23:                      ant_sel_0
            SEL_24:                      cca
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      swo_m3
            SEL_27:                      swo_m33
            SEL_28:                      gpt1_pre_event
            SEL_29:                      gpt0_pre_event
            SEL_30:                      sdio_d3
            SEL_31:                      uart2_tx
*/
#define IOMUX_GPIO30PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO30PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO30PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO30PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO30PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO31PCFG
    Offset name:         IOMUX_O_GPIO31PCFG
    Relative address:    0x2D080
    Description:         Port configuration register for IO GPIO31
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_31
                         sel 5'd3 -- xspi_reset_flash
                         sel 5'd4 -- spi1_cs1
                         sel 5'd5 -- uart1_rts
                         sel 5'd6 -- i2c1_clk
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt1_0
                         sel 5'd10 -- dcan_tx
                         sel 5'd16 -- spi0_cs3
                         sel 5'd17 -- ext_clk
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd19 -- gpt0_0_n
                         sel 5'd20 -- coex_grant
                         sel 5'd22 -- ble_rfc_gpo_6
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- gpt_infrared
                         sel 5'd25 -- ble_rfc_gpi_3
                         sel 5'd30 -- sdio_d2
                         sel 5'd31 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_31
            SEL_3:                       xspi_reset_flash
            SEL_4:                       spi1_cs1
            SEL_5:                       uart1_rts
            SEL_6:                       i2c1_clk
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt1_0
            SEL_10:                      dcan_tx
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs3
            SEL_17:                      ext_clk
            SEL_18:                      gpt1_1_n
            SEL_19:                      gpt0_0_n
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_6
            SEL_23:                      ant_sel_0
            SEL_24:                      gpt_infrared
            SEL_25:                      ble_rfc_gpi_3
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_d2
            SEL_31:                      uart2_tx
*/
#define IOMUX_GPIO31PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO31PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO31PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO31PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO31PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO32PCFG
    Offset name:         IOMUX_O_GPIO32PCFG
    Relative address:    0x2D084
    Description:         Port configuration register for IO GPIO32
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_32
                         sel 5'd3 -- spi1_cs1
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart1_tx
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- wake_observe_bus_5
                         sel 5'd16 -- spi0_cs3
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd19 -- gpt0_1_n
                         sel 5'd20 -- coex_req
                         sel 5'd23 -- ant_sel_1
                         sel 5'd30 -- sdio_d1
                         sel 5'd31 -- uart2_rts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_32
            SEL_3:                       spi1_cs1
            SEL_4:                       spi1_clk
            SEL_5:                       uart1_tx
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt1_1
            SEL_10:                      dcan_rx
            SEL_11:                      wake_observe_bus_5
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs3
            SEL_17:                      reserved
            SEL_18:                      gpt1_0_n
            SEL_19:                      gpt0_1_n
            SEL_20:                      coex_req
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_d1
            SEL_31:                      uart2_rts
*/
#define IOMUX_GPIO32PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO32PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO32PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO32PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO32PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO33PCFG
    Offset name:         IOMUX_O_GPIO33PCFG
    Relative address:    0x2D088
    Description:         Port configuration register for IO GPIO33
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd2 -- wifi_gpio_33
                         sel 5'd4 -- spi1_miso
                         sel 5'd5 -- uart1_rx
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt1_2
                         sel 5'd10 -- dcan_tx
                         sel 5'd16 -- spi0_cs4
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd19 -- gpt0_2_n
                         sel 5'd20 -- coex_grant
                         sel 5'd23 -- ant_sel_2
                         sel 5'd24 -- gpt1_pre_event
                         sel 5'd25 -- ble_rfc_gpi_2
                         sel 5'd30 -- sdio_d0
                         sel 5'd31 -- uart2_cts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_33
            SEL_3:                       reserved
            SEL_4:                       spi1_miso
            SEL_5:                       uart1_rx
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data0
            SEL_9:                       gpt1_2
            SEL_10:                      dcan_tx
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs4
            SEL_17:                      reserved
            SEL_18:                      gpt1_0_n
            SEL_19:                      gpt0_2_n
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_2
            SEL_24:                      gpt1_pre_event
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_d0
            SEL_31:                      uart2_cts
*/
#define IOMUX_GPIO33PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO33PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO33PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO33PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO33PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO34PCFG
    Offset name:         IOMUX_O_GPIO34PCFG
    Relative address:    0x2D08C
    Description:         Port configuration register for IO GPIO34
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_ram
                         sel 5'd2 -- wifi_gpio_34
                         sel 5'd4 -- spi1_mosi
                         sel 5'd5 -- uart1_cts
                         sel 5'd6 -- i2c1_data
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt1_3
                         sel 5'd10 -- dcan_rx
                         sel 5'd16 -- spi0_cs2
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd19 -- gpt0_3_n
                         sel 5'd20 -- coex_req
                         sel 5'd22 -- ble_rfc_gpo_7
                         sel 5'd23 -- ant_sel_3
                         sel 5'd25 -- ble_rfc_gpi_1
                         sel 5'd30 -- sdio_clk
                         sel 5'd31 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_ram
            SEL_2:                       wifi_gpio_34
            SEL_3:                       reserved
            SEL_4:                       spi1_mosi
            SEL_5:                       uart1_cts
            SEL_6:                       i2c1_data
            SEL_7:                       i2s_bclk
            SEL_8:                       pdm_data1
            SEL_9:                       gpt1_3
            SEL_10:                      dcan_rx
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs2
            SEL_17:                      reserved
            SEL_18:                      gpt1_1_n
            SEL_19:                      gpt0_3_n
            SEL_20:                      coex_req
            SEL_21:                      reserved
            SEL_22:                      ble_rfc_gpo_7
            SEL_23:                      ant_sel_3
            SEL_24:                      reserved
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      sdio_clk
            SEL_31:                      uart2_rx
*/
#define IOMUX_GPIO34PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO34PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO34PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO34PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO34PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO35PCFG
    Offset name:         IOMUX_O_GPIO35PCFG
    Relative address:    0x2D090
    Description:         Port configuration register for IO GPIO35
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_flash
                         sel 5'd2 -- wifi_gpio_35
                         sel 5'd3 -- spi1_clk
                         sel 5'd4 -- xspi_reset_ram
                         sel 5'd5 -- uart1_rx
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_data1
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt0_1
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- i2c1_data
                         sel 5'd12 -- xspi_cs_ram
                         sel 5'd16 -- spi0_cs4
                         sel 5'd17 -- spi0_cs3
                         sel 5'd18 -- gpt0_2_n
                         sel 5'd19 -- gpt1_2_n
                         sel 5'd20 -- coex_priority
                         sel 5'd21 -- ble_rftrc
                         sel 5'd22 -- ble_rfc_gpo_5
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- gpt1_pre_event
                         sel 5'd25 -- ble_rfc_gpi_2
                         sel 5'd26 -- swo_m3
                         sel 5'd27 -- swo_m33
                         sel 5'd28 -- xspi_dqs
                         sel 5'd29 -- coex_req
                         sel 5'd30 -- sdio_cmd
                         sel 5'd31 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_flash
            SEL_2:                       wifi_gpio_35
            SEL_3:                       spi1_clk
            SEL_4:                       xspi_reset_ram
            SEL_5:                       uart1_rx
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_data1
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt0_1
            SEL_10:                      dcan_rx
            SEL_11:                      i2c1_data
            SEL_12:                      xspi_cs_ram
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      spi0_cs4
            SEL_17:                      spi0_cs3
            SEL_18:                      gpt0_2_n
            SEL_19:                      gpt1_2_n
            SEL_20:                      coex_priority
            SEL_21:                      ble_rftrc
            SEL_22:                      ble_rfc_gpo_5
            SEL_23:                      ant_sel_0
            SEL_24:                      gpt1_pre_event
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      swo_m3
            SEL_27:                      swo_m33
            SEL_28:                      xspi_dqs
            SEL_29:                      coex_req
            SEL_30:                      sdio_cmd
            SEL_31:                      uart2_rx
*/
#define IOMUX_GPIO35PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO35PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO35PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO35PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO35PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO36PCFG
    Offset name:         IOMUX_O_GPIO36PCFG
    Relative address:    0x2D094
    Description:         Port configuration register for IO GPIO36
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- fast_clk_req
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_36
                         sel 5'd3 -- sdio_mmc_pow2
                         sel 5'd4 -- sdio_mmc_wp
                         sel 5'd11 -- wake_observe_bus_13
                         sel 5'd12 -- debug_bus_1
                         sel 5'd19 -- coex_req
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- fast_clk_req
                         sel 5'd22 -- ble_rfc_gpo_5
                         sel 5'd23 -- ant_sel_1
                         sel 5'd24 -- cca
                         sel 5'd25 -- ble_rfc_gpi_2


        ENUMs:
            SEL_0:                       fast_clk_req
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_36
            SEL_3:                       sdio_mmc_pow2
            SEL_4:                       sdio_mmc_wp
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_13
            SEL_12:                      debug_bus_1
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      coex_req
            SEL_20:                      coex_grant
            SEL_21:                      fast_clk_req
            SEL_22:                      ble_rfc_gpo_5
            SEL_23:                      ant_sel_1
            SEL_24:                      cca
            SEL_25:                      ble_rfc_gpi_2
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO36PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO36PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO36PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO36PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO36PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO37PCFG
    Offset name:         IOMUX_O_GPIO37PCFG
    Relative address:    0x2D098
    Description:         Port configuration register for IO GPIO37
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_37
                         sel 5'd3 -- sdio_mmc_pow1
                         sel 5'd4 -- sdio_mmc_wp
                         sel 5'd11 -- wake_observe_bus_12
                         sel 5'd12 -- debug_bus_0
                         sel 5'd18 -- coex_req
                         sel 5'd19 -- sdio_oob_irq
                         sel 5'd20 -- coex_grant
                         sel 5'd21 -- fast_clk_req
                         sel 5'd22 -- ble_rfc_gpo_4
                         sel 5'd23 -- ant_sel_0
                         sel 5'd24 -- cca
                         sel 5'd25 -- ble_rfc_gpi_1


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_37
            SEL_3:                       sdio_mmc_pow1
            SEL_4:                       sdio_mmc_wp
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      wake_observe_bus_12
            SEL_12:                      debug_bus_0
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      coex_req
            SEL_19:                      sdio_oob_irq
            SEL_20:                      coex_grant
            SEL_21:                      fast_clk_req
            SEL_22:                      ble_rfc_gpo_4
            SEL_23:                      ant_sel_0
            SEL_24:                      cca
            SEL_25:                      ble_rfc_gpi_1
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO37PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO37PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO37PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO37PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO37PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO38PCFG
    Offset name:         IOMUX_O_GPIO38PCFG
    Relative address:    0x2D09C
    Description:         Port configuration register for IO GPIO38
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_38
                         sel 5'd3 -- ext_clk
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart0_cts
                         sel 5'd6 -- i2c1_clk
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt1_0
                         sel 5'd10 -- dcan_tx
                         sel 5'd18 -- gpt1_1_n
                         sel 5'd20 -- coex_grant
                         sel 5'd23 -- ant_sel_0
                         sel 5'd29 -- coex_req
                         sel 5'd30 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_38
            SEL_3:                       ext_clk
            SEL_4:                       spi1_clk
            SEL_5:                       uart0_cts
            SEL_6:                       i2c1_clk
            SEL_7:                       i2s_bclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt1_0
            SEL_10:                      dcan_tx
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      gpt1_1_n
            SEL_19:                      reserved
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_req
            SEL_30:                      uart2_rx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO38PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO38PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO38PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO38PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO38PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO39PCFG
    Offset name:         IOMUX_O_GPIO39PCFG
    Relative address:    0x2D0A0
    Description:         Port configuration register for IO GPIO39
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_ram
                         sel 5'd2 -- wifi_gpio_39
                         sel 5'd3 -- uart0_rx
                         sel 5'd4 -- spi1_miso
                         sel 5'd5 -- uart0_rts
                         sel 5'd6 -- i2c1_data
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt1_1
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- xspi_dqs
                         sel 5'd18 -- gpt1_0_n
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- coex_grant
                         sel 5'd23 -- ant_sel_1
                         sel 5'd29 -- coex_priority
                         sel 5'd30 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_ram
            SEL_2:                       wifi_gpio_39
            SEL_3:                       uart0_rx
            SEL_4:                       spi1_miso
            SEL_5:                       uart0_rts
            SEL_6:                       i2c1_data
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_data0
            SEL_9:                       gpt1_1
            SEL_10:                      dcan_rx
            SEL_11:                      xspi_dqs
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      gpt1_0_n
            SEL_19:                      reserved
            SEL_20:                      coex_req
            SEL_21:                      coex_grant
            SEL_22:                      reserved
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_priority
            SEL_30:                      uart2_tx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO39PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO39PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO39PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO39PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO39PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO40PCFG
    Offset name:         IOMUX_O_GPIO40PCFG
    Relative address:    0x2D0A4
    Description:         Port configuration register for IO GPIO40
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_40
                         sel 5'd4 -- spi1_mosi
                         sel 5'd5 -- uart0_tx
                         sel 5'd7 -- i2s_data0
                         sel 5'd8 -- pdm_data1
                         sel 5'd9 -- gpt1_2
                         sel 5'd16 -- gpt1_pre_event
                         sel 5'd17 -- gpt0_pre_event
                         sel 5'd18 -- gpt1_2_n
                         sel 5'd20 -- coex_priority
                         sel 5'd22 -- gpt_infrared
                         sel 5'd23 -- ant_sel_2
                         sel 5'd29 -- coex_grant
                         sel 5'd30 -- uart2_rts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_40
            SEL_3:                       reserved
            SEL_4:                       spi1_mosi
            SEL_5:                       uart0_tx
            SEL_6:                       reserved
            SEL_7:                       i2s_data0
            SEL_8:                       pdm_data1
            SEL_9:                       gpt1_2
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      gpt1_pre_event
            SEL_17:                      gpt0_pre_event
            SEL_18:                      gpt1_2_n
            SEL_19:                      reserved
            SEL_20:                      coex_priority
            SEL_21:                      reserved
            SEL_22:                      gpt_infrared
            SEL_23:                      ant_sel_2
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_grant
            SEL_30:                      uart2_rts
            SEL_31:                      reserved
*/
#define IOMUX_GPIO40PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO40PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO40PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO40PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO40PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO41PCFG
    Offset name:         IOMUX_O_GPIO41PCFG
    Relative address:    0x2D0A8
    Description:         Port configuration register for IO GPIO41
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_41
                         sel 5'd4 -- spi1_miso
                         sel 5'd5 -- uart1_cts
                         sel 5'd7 -- i2s_data0
                         sel 5'd9 -- gpt0_0
                         sel 5'd16 -- gpt1_pre_event
                         sel 5'd17 -- gpt0_pre_event
                         sel 5'd18 -- gpt0_1_n
                         sel 5'd20 -- coex_grant
                         sel 5'd22 -- gpt_infrared
                         sel 5'd23 -- ant_sel_0
                         sel 5'd29 -- coex_grant
                         sel 5'd30 -- uart2_rx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_41
            SEL_3:                       reserved
            SEL_4:                       spi1_miso
            SEL_5:                       uart1_cts
            SEL_6:                       reserved
            SEL_7:                       i2s_data0
            SEL_8:                       reserved
            SEL_9:                       gpt0_0
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      gpt1_pre_event
            SEL_17:                      gpt0_pre_event
            SEL_18:                      gpt0_1_n
            SEL_19:                      reserved
            SEL_20:                      coex_grant
            SEL_21:                      reserved
            SEL_22:                      gpt_infrared
            SEL_23:                      ant_sel_0
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_grant
            SEL_30:                      uart2_rx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO41PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO41PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO41PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO41PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO41PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO42PCFG
    Offset name:         IOMUX_O_GPIO42PCFG
    Relative address:    0x2D0AC
    Description:         Port configuration register for IO GPIO42
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_reset_ram
                         sel 5'd2 -- wifi_gpio_42
                         sel 5'd3 -- uart1_rx
                         sel 5'd4 -- spi1_mosi
                         sel 5'd5 -- uart1_rts
                         sel 5'd6 -- i2c0_data
                         sel 5'd7 -- i2s_wclk
                         sel 5'd8 -- pdm_data0
                         sel 5'd9 -- gpt0_1
                         sel 5'd10 -- dcan_rx
                         sel 5'd11 -- xspi_dqs
                         sel 5'd18 -- gpt0_0_n
                         sel 5'd20 -- coex_req
                         sel 5'd21 -- coex_grant
                         sel 5'd23 -- ant_sel_1
                         sel 5'd29 -- coex_req
                         sel 5'd30 -- uart2_tx


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_reset_ram
            SEL_2:                       wifi_gpio_42
            SEL_3:                       uart1_rx
            SEL_4:                       spi1_mosi
            SEL_5:                       uart1_rts
            SEL_6:                       i2c0_data
            SEL_7:                       i2s_wclk
            SEL_8:                       pdm_data0
            SEL_9:                       gpt0_1
            SEL_10:                      dcan_rx
            SEL_11:                      xspi_dqs
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      gpt0_0_n
            SEL_19:                      reserved
            SEL_20:                      coex_req
            SEL_21:                      coex_grant
            SEL_22:                      reserved
            SEL_23:                      ant_sel_1
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_req
            SEL_30:                      uart2_tx
            SEL_31:                      reserved
*/
#define IOMUX_GPIO42PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO42PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO42PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO42PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO42PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO43PCFG
    Offset name:         IOMUX_O_GPIO43PCFG
    Relative address:    0x2D0B0
    Description:         Port configuration register for IO GPIO43
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd1 -- xspi_cs_ram
                         sel 5'd2 -- wifi_gpio_43
                         sel 5'd4 -- spi1_clk
                         sel 5'd5 -- uart1_tx
                         sel 5'd6 -- i2c0_clk
                         sel 5'd7 -- i2s_bclk
                         sel 5'd8 -- pdm_bclk
                         sel 5'd9 -- gpt0_2
                         sel 5'd10 -- dcan_tx
                         sel 5'd18 -- gpt0_2_n
                         sel 5'd20 -- coex_priority
                         sel 5'd23 -- ant_sel_2
                         sel 5'd29 -- coex_priority
                         sel 5'd30 -- uart2_rts


        ENUMs:
            SEL_0:                       reserved
            SEL_1:                       xspi_cs_ram
            SEL_2:                       wifi_gpio_43
            SEL_3:                       reserved
            SEL_4:                       spi1_clk
            SEL_5:                       uart1_tx
            SEL_6:                       i2c0_clk
            SEL_7:                       i2s_bclk
            SEL_8:                       pdm_bclk
            SEL_9:                       gpt0_2
            SEL_10:                      dcan_tx
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      gpt0_2_n
            SEL_19:                      reserved
            SEL_20:                      coex_priority
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      ant_sel_2
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      coex_priority
            SEL_30:                      uart2_rts
            SEL_31:                      reserved
*/
#define IOMUX_GPIO43PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO43PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO43PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO43PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO43PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO44PCFG
    Offset name:         IOMUX_O_GPIO44PCFG
    Relative address:    0x2D0B4
    Description:         Port configuration register for IO GPIO44
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_clk_input
                         sel 5'd2 -- wifi_gpio_44


        ENUMs:
            SEL_0:                       xspi_clk_input
            SEL_1:                       reserved
            SEL_2:                       wifi_gpio_44
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO44PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO44PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO44PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO44PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO44PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       PROCCOMP
    Offset name:         IOMUX_O_PROCCOMP
    Relative address:    0x2D0BC
    Description:         The IO Process compensation is used to override the process compensation bits form the eFuse:IO Process: Common for all IOs.
    Default Value:       NA

        Field:           PROGIONVAL
        From..to bits:   0...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the value of override PROG IO N

*/
#define IOMUX_PROCCOMP_PROGIONVAL_W                                  3U
#define IOMUX_PROCCOMP_PROGIONVAL_M                                  0x00000007U
#define IOMUX_PROCCOMP_PROGIONVAL_S                                  0U
/*

        Field:           PROGIONOVR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     The field selects the PROGIO N override between Fuse ROM and MMR

        ENUMs:
            DISABLE:                      Use Fuse ROM (bits (10:8))
            ENABLE:                      Use MMR (bits (2:0))
*/
#define IOMUX_PROCCOMP_PROGIONOVR                                    0x00000008U
#define IOMUX_PROCCOMP_PROGIONOVR_M                                  0x00000008U
#define IOMUX_PROCCOMP_PROGIONOVR_S                                  3U
#define IOMUX_PROCCOMP_PROGIONOVR_DISABLE                            0x00000000U
#define IOMUX_PROCCOMP_PROGIONOVR_ENABLE                             0x00000008U
/*

        Field:           PROGIOPVAL
        From..to bits:   4...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the value of override PROG IO N

*/
#define IOMUX_PROCCOMP_PROGIOPVAL_W                                  3U
#define IOMUX_PROCCOMP_PROGIOPVAL_M                                  0x00000070U
#define IOMUX_PROCCOMP_PROGIOPVAL_S                                  4U
/*

        Field:           PROGIOPOVR
        From..to bits:   7...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     The field selects the PROGIO P override between Fuse ROM and MMR

        ENUMs:
            DISABLE:                      Use Fuse ROM (bits (14:12))
            ENABLE:                      Use MMR (bits (6:4))
*/
#define IOMUX_PROCCOMP_PROGIOPOVR                                    0x00000080U
#define IOMUX_PROCCOMP_PROGIOPOVR_M                                  0x00000080U
#define IOMUX_PROCCOMP_PROGIOPOVR_S                                  7U
#define IOMUX_PROCCOMP_PROGIOPOVR_DISABLE                            0x00000000U
#define IOMUX_PROCCOMP_PROGIOPOVR_ENABLE                             0x00000080U
/*

        Field:           FUSEPROGION
        From..to bits:   8...10
        DefaultValue:    NA
        Access type:     read-only
        Description:     PROG IO N value from fuse ROM

*/
#define IOMUX_PROCCOMP_FUSEPROGION_W                                 3U
#define IOMUX_PROCCOMP_FUSEPROGION_M                                 0x00000700U
#define IOMUX_PROCCOMP_FUSEPROGION_S                                 8U
/*

        Field:           FUSEPROGIOP
        From..to bits:   12...14
        DefaultValue:    NA
        Access type:     read-only
        Description:     PROG IO P value from fuse ROM

*/
#define IOMUX_PROCCOMP_FUSEPROGIOP_W                                 3U
#define IOMUX_PROCCOMP_FUSEPROGIOP_M                                 0x00007000U
#define IOMUX_PROCCOMP_FUSEPROGIOP_S                                 12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO45PCFG
    Offset name:         IOMUX_O_GPIO45PCFG
    Relative address:    0x2D0C0
    Description:         Port configuration register for IO GPIO45
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_0_ram


        ENUMs:
            SEL_0:                       xspi_data_0_ram
            SEL_1:                       reserved
            SEL_2:                       reserved
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO45PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO45PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO45PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO45PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO45PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO46PCFG
    Offset name:         IOMUX_O_GPIO46PCFG
    Relative address:    0x2D0C4
    Description:         Port configuration register for IO GPIO46
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_1_ram


        ENUMs:
            SEL_0:                       xspi_data_1_ram
            SEL_1:                       reserved
            SEL_2:                       reserved
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO46PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO46PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO46PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO46PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO46PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO47PCFG
    Offset name:         IOMUX_O_GPIO47PCFG
    Relative address:    0x2D0C8
    Description:         Port configuration register for IO GPIO47
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_2_ram


        ENUMs:
            SEL_0:                       xspi_data_2_ram
            SEL_1:                       reserved
            SEL_2:                       reserved
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO47PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO47PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO47PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO47PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO47PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO48PCFG
    Offset name:         IOMUX_O_GPIO48PCFG
    Relative address:    0x2D0CC
    Description:         Port configuration register for IO GPIO48
    Default Value:       NA

        Field:           IOSEL
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Pinmux selection Control
                         Mode can be used to select the IO functionality or drive 0/1/Hi-Z
                         sel 5'd0 -- xspi_data_3_ram


        ENUMs:
            SEL_0:                       xspi_data_3_ram
            SEL_1:                       reserved
            SEL_2:                       reserved
            SEL_3:                       reserved
            SEL_4:                       reserved
            SEL_5:                       reserved
            SEL_6:                       reserved
            SEL_7:                       reserved
            SEL_8:                       reserved
            SEL_9:                       reserved
            SEL_10:                      reserved
            SEL_11:                      reserved
            SEL_12:                      reserved
            SEL_13:                      reserved
            SEL_14:                      reserved
            SEL_15:                      reserved
            SEL_16:                      reserved
            SEL_17:                      reserved
            SEL_18:                      reserved
            SEL_19:                      reserved
            SEL_20:                      reserved
            SEL_21:                      reserved
            SEL_22:                      reserved
            SEL_23:                      reserved
            SEL_24:                      reserved
            SEL_25:                      reserved
            SEL_26:                      reserved
            SEL_27:                      reserved
            SEL_28:                      reserved
            SEL_29:                      reserved
            SEL_30:                      reserved
            SEL_31:                      reserved
*/
#define IOMUX_GPIO48PCFG_IOSEL_W                                     5U
#define IOMUX_GPIO48PCFG_IOSEL_M                                     0x0000001FU
#define IOMUX_GPIO48PCFG_IOSEL_S                                     0U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_0                                 0x00000000U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_1                                 0x00000001U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_2                                 0x00000002U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_3                                 0x00000003U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_4                                 0x00000004U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_5                                 0x00000005U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_6                                 0x00000006U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_7                                 0x00000007U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_8                                 0x00000008U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_9                                 0x00000009U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_10                                0x0000000AU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_11                                0x0000000BU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_12                                0x0000000CU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_13                                0x0000000DU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_14                                0x0000000EU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_15                                0x0000000FU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_16                                0x00000010U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_17                                0x00000011U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_18                                0x00000012U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_19                                0x00000013U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_20                                0x00000014U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_21                                0x00000015U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_22                                0x00000016U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_23                                0x00000017U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_24                                0x00000018U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_25                                0x00000019U
#define IOMUX_GPIO48PCFG_IOSEL_SEL_26                                0x0000001AU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_27                                0x0000001BU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_28                                0x0000001CU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_29                                0x0000001DU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_30                                0x0000001EU
#define IOMUX_GPIO48PCFG_IOSEL_SEL_31                                0x0000001FU


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO45CFG
    Offset name:         IOMUX_O_GPIO45CFG
    Relative address:    0x2E000
    Description:         CFG register for IO GPIO45. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO45CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO45CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO45CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO45CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO45CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO45CFG_IE                                           0x00000800U
#define IOMUX_GPIO45CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO45CFG_IE_S                                         11U
#define IOMUX_GPIO45CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO45CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO45CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO45CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO45CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO45CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO45CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO45CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO45CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO45CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO45CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO45CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO45CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO45CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO45CFG_IOSTR_S                                      14U
#define IOMUX_GPIO45CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO45CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO45PCTL
    Offset name:         IOMUX_O_GPIO45PCTL
    Relative address:    0x2E004
    Description:         Pull control register of IO GPIO45
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO45PCTL_CTL_W                                       2U
#define IOMUX_GPIO45PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO45PCTL_CTL_S                                       0U
#define IOMUX_GPIO45PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO45PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO45PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO45PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO45PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO45PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO45PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO45PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO45PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO45PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO45PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO45PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO45PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO45PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO45CTL
    Offset name:         IOMUX_O_GPIO45CTL
    Relative address:    0x2E008
    Description:         Control register of IO GPIO45
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO45CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO45CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO45CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO45CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO45CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO45CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO45CTL_OUT                                          0x00000100U
#define IOMUX_GPIO45CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO45CTL_OUT_S                                        8U
#define IOMUX_GPIO45CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO45CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO45CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO45CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO45CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO45CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO45CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO45ECTL
    Offset name:         IOMUX_O_GPIO45ECTL
    Relative address:    0x2E00C
    Description:         Event control register for IO GPIO45
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO45ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO45ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO45ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO45ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO45ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO45ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO45ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO45ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO45ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO45ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO45ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO45ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO45ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO45ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO45ECTL_CLR_S                                       3U
#define IOMUX_GPIO45ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO45ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO46CFG
    Offset name:         IOMUX_O_GPIO46CFG
    Relative address:    0x2F000
    Description:         CFG register for IO GPIO46. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO46CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO46CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO46CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO46CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO46CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO46CFG_IE                                           0x00000800U
#define IOMUX_GPIO46CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO46CFG_IE_S                                         11U
#define IOMUX_GPIO46CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO46CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO46CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO46CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO46CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO46CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO46CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO46CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO46CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO46CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO46CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO46CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO46CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO46CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO46CFG_IOSTR_S                                      14U
#define IOMUX_GPIO46CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO46CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO46PCTL
    Offset name:         IOMUX_O_GPIO46PCTL
    Relative address:    0x2F004
    Description:         Pull control register of IO GPIO46
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO46PCTL_CTL_W                                       2U
#define IOMUX_GPIO46PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO46PCTL_CTL_S                                       0U
#define IOMUX_GPIO46PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO46PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO46PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO46PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO46PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO46PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO46PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO46PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO46PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO46PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO46PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO46PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO46PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO46PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO46CTL
    Offset name:         IOMUX_O_GPIO46CTL
    Relative address:    0x2F008
    Description:         Control register of IO GPIO46
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO46CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO46CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO46CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO46CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO46CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO46CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO46CTL_OUT                                          0x00000100U
#define IOMUX_GPIO46CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO46CTL_OUT_S                                        8U
#define IOMUX_GPIO46CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO46CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO46CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO46CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO46CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO46CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO46CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO46ECTL
    Offset name:         IOMUX_O_GPIO46ECTL
    Relative address:    0x2F00C
    Description:         Event control register for IO GPIO46
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO46ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO46ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO46ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO46ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO46ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO46ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO46ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO46ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO46ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO46ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO46ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO46ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO46ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO46ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO46ECTL_CLR_S                                       3U
#define IOMUX_GPIO46ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO46ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO47CFG
    Offset name:         IOMUX_O_GPIO47CFG
    Relative address:    0x30000
    Description:         CFG register for IO GPIO47. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO47CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO47CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO47CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO47CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO47CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO47CFG_IE                                           0x00000800U
#define IOMUX_GPIO47CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO47CFG_IE_S                                         11U
#define IOMUX_GPIO47CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO47CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO47CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO47CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO47CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO47CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO47CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO47CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO47CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO47CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO47CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO47CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO47CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO47CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO47CFG_IOSTR_S                                      14U
#define IOMUX_GPIO47CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO47CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO47PCTL
    Offset name:         IOMUX_O_GPIO47PCTL
    Relative address:    0x30004
    Description:         Pull control register of IO GPIO47
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO47PCTL_CTL_W                                       2U
#define IOMUX_GPIO47PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO47PCTL_CTL_S                                       0U
#define IOMUX_GPIO47PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO47PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO47PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO47PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO47PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO47PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO47PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO47PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO47PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO47PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO47PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO47PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO47PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO47PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO47CTL
    Offset name:         IOMUX_O_GPIO47CTL
    Relative address:    0x30008
    Description:         Control register of IO GPIO47
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO47CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO47CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO47CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO47CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO47CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO47CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO47CTL_OUT                                          0x00000100U
#define IOMUX_GPIO47CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO47CTL_OUT_S                                        8U
#define IOMUX_GPIO47CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO47CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO47CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO47CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO47CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO47CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO47CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO47ECTL
    Offset name:         IOMUX_O_GPIO47ECTL
    Relative address:    0x3000C
    Description:         Event control register for IO GPIO47
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO47ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO47ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO47ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO47ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO47ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO47ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO47ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO47ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO47ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO47ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO47ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO47ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO47ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO47ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO47ECTL_CLR_S                                       3U
#define IOMUX_GPIO47ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO47ECTL_CLR_CLEAR                                   0x00000008U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO48CFG
    Offset name:         IOMUX_O_GPIO48CFG
    Relative address:    0x31000
    Description:         CFG register for IO GPIO48. This register configures the corresponding pad
    Default Value:       0x00000000

        Field:           OUTDISVAL
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The field gives the status of [OUTDIS]

        ENUMs:
            ENABLED:                     Output is enabled
            DISABLED:                    Output is disabled
*/
#define IOMUX_GPIO48CFG_OUTDISVAL                                    0x00000040U
#define IOMUX_GPIO48CFG_OUTDISVAL_M                                  0x00000040U
#define IOMUX_GPIO48CFG_OUTDISVAL_S                                  6U
#define IOMUX_GPIO48CFG_OUTDISVAL_ENABLED                            0x00000000U
#define IOMUX_GPIO48CFG_OUTDISVAL_DISABLED                           0x00000040U
/*

        Field:           IE
        From..to bits:   11...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field enables the receiver operation from the pad

        ENUMs:
            DISABLE:                     Disable the receiver operation
            ENABLE:                      Enable the receiver operation
*/
#define IOMUX_GPIO48CFG_IE                                           0x00000800U
#define IOMUX_GPIO48CFG_IE_M                                         0x00000800U
#define IOMUX_GPIO48CFG_IE_S                                         11U
#define IOMUX_GPIO48CFG_IE_DISABLE                                   0x00000000U
#define IOMUX_GPIO48CFG_IE_ENABLE                                    0x00000800U
/*

        Field:           OUTDIS
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field configures the output from the pad
                         Note:This field is applicable only if [OUTDISOVREN] is enabled

        ENUMs:
            DISABLE:                     Output from the pad is disabled
            ENABLE:                      Output from the pad is enabled
*/
#define IOMUX_GPIO48CFG_OUTDIS                                       0x00001000U
#define IOMUX_GPIO48CFG_OUTDIS_M                                     0x00001000U
#define IOMUX_GPIO48CFG_OUTDIS_S                                     12U
#define IOMUX_GPIO48CFG_OUTDIS_DISABLE                               0x00001000U
#define IOMUX_GPIO48CFG_OUTDIS_ENABLE                                0x00000000U
/*

        Field:           OUTDISOVREN
        From..to bits:   13...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the [OUTDIS] override

        ENUMs:
            DISABLE:                     Disable the override
            ENABLE:                      Enable the override
*/
#define IOMUX_GPIO48CFG_OUTDISOVREN                                  0x00002000U
#define IOMUX_GPIO48CFG_OUTDISOVREN_M                                0x00002000U
#define IOMUX_GPIO48CFG_OUTDISOVREN_S                                13U
#define IOMUX_GPIO48CFG_OUTDISOVREN_DISABLE                          0x00000000U
#define IOMUX_GPIO48CFG_OUTDISOVREN_ENABLE                           0x00002000U
/*

        Field:           IOSTR
        From..to bits:   14...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This field controls the IO drive strength

        ENUMs:
            LOW:                         IO drives low power
            HIGH:                        IO drives high power
*/
#define IOMUX_GPIO48CFG_IOSTR                                        0x00004000U
#define IOMUX_GPIO48CFG_IOSTR_M                                      0x00004000U
#define IOMUX_GPIO48CFG_IOSTR_S                                      14U
#define IOMUX_GPIO48CFG_IOSTR_LOW                                    0x00000000U
#define IOMUX_GPIO48CFG_IOSTR_HIGH                                   0x00004000U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO48PCTL
    Offset name:         IOMUX_O_GPIO48PCTL
    Relative address:    0x31004
    Description:         Pull control register of IO GPIO48
                        This register configures the pull control
    Default Value:       0x00000001

        Field:           CTL
        From..to bits:   0...1
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The fields defines the pull control

        ENUMs:
            IPCTRL:                      IP Pull Control
            DOWN:                        Pull down
            UP:                          Pull up
            DISABLE:                     Pull disable
*/
#define IOMUX_GPIO48PCTL_CTL_W                                       2U
#define IOMUX_GPIO48PCTL_CTL_M                                       0x00000003U
#define IOMUX_GPIO48PCTL_CTL_S                                       0U
#define IOMUX_GPIO48PCTL_CTL_IPCTRL                                  0x00000000U
#define IOMUX_GPIO48PCTL_CTL_DOWN                                    0x00000002U
#define IOMUX_GPIO48PCTL_CTL_UP                                      0x00000001U
#define IOMUX_GPIO48PCTL_CTL_DISABLE                                 0x00000003U
/*

        Field:           PULLUPSTA
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull up level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull up
*/
#define IOMUX_GPIO48PCTL_PULLUPSTA                                   0x00000100U
#define IOMUX_GPIO48PCTL_PULLUPSTA_M                                 0x00000100U
#define IOMUX_GPIO48PCTL_PULLUPSTA_S                                 8U
#define IOMUX_GPIO48PCTL_PULLUPSTA_DISABLED                          0x00000000U
#define IOMUX_GPIO48PCTL_PULLUPSTA_ENABLED                           0x00000100U
/*

        Field:           PULLDWNSTA
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This field gives the IO pull down level status

        ENUMs:
            DISABLED:                    Pull disabled
            ENABLED:                     Pull down
*/
#define IOMUX_GPIO48PCTL_PULLDWNSTA                                  0x00000200U
#define IOMUX_GPIO48PCTL_PULLDWNSTA_M                                0x00000200U
#define IOMUX_GPIO48PCTL_PULLDWNSTA_S                                9U
#define IOMUX_GPIO48PCTL_PULLDWNSTA_DISABLED                         0x00000000U
#define IOMUX_GPIO48PCTL_PULLDWNSTA_ENABLED                          0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO48CTL
    Offset name:         IOMUX_O_GPIO48CTL
    Relative address:    0x31008
    Description:         Control register of IO GPIO48
                        This register controls the IO state
    Default Value:       NA

        Field:           PADVAL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the received value from pad

*/
#define IOMUX_GPIO48CTL_PADVAL                                       0x00000001U
#define IOMUX_GPIO48CTL_PADVAL_M                                     0x00000001U
#define IOMUX_GPIO48CTL_PADVAL_S                                     0U
/*

        Field:           PADVALSYNC
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field captures the sychronized(to SOC clock) received value

*/
#define IOMUX_GPIO48CTL_PADVALSYNC                                   0x00000002U
#define IOMUX_GPIO48CTL_PADVALSYNC_M                                 0x00000002U
#define IOMUX_GPIO48CTL_PADVALSYNC_S                                 1U
/*

        Field:           OUT
        From..to bits:   8...8
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the IO drive out value. This field is valid only when [OUTOVREN] is configured ENABLE

        ENUMs:
            LOW:                         IO drives 0
            HIGH:                        IO drives 1
*/
#define IOMUX_GPIO48CTL_OUT                                          0x00000100U
#define IOMUX_GPIO48CTL_OUT_M                                        0x00000100U
#define IOMUX_GPIO48CTL_OUT_S                                        8U
#define IOMUX_GPIO48CTL_OUT_LOW                                      0x00000000U
#define IOMUX_GPIO48CTL_OUT_HIGH                                     0x00000100U
/*

        Field:           OUTOVREN
        From..to bits:   9...9
        DefaultValue:    NA
        Access type:     read-write
        Description:      This field contols the override on output

        ENUMs:
            DISABLE:                     Output controlled by IP
            ENABLE:                      Enable override on output
*/
#define IOMUX_GPIO48CTL_OUTOVREN                                     0x00000200U
#define IOMUX_GPIO48CTL_OUTOVREN_M                                   0x00000200U
#define IOMUX_GPIO48CTL_OUTOVREN_S                                   9U
#define IOMUX_GPIO48CTL_OUTOVREN_DISABLE                             0x00000000U
#define IOMUX_GPIO48CTL_OUTOVREN_ENABLE                              0x00000200U


/*-----------------------------------REGISTER------------------------------------
    Register name:       GPIO48ECTL
    Offset name:         IOMUX_O_GPIO48ECTL
    Relative address:    0x3100C
    Description:         Event control register for IO GPIO48
                        This register controls the Event configuration and behaviour
    Default Value:       NA

        Field:           EVTDETCFG
        From..to bits:   0...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field is to be configured to define the IO detection method

        ENUMs:
            MASK:                        Masking the event
            POS_EDGE:                    Rising edge/Positive edge detection
            NEG_EDGE:                    Falling edge/Negative edge detection
            LEVEL:                       Level detection
*/
#define IOMUX_GPIO48ECTL_EVTDETCFG_W                                 2U
#define IOMUX_GPIO48ECTL_EVTDETCFG_M                                 0x00000003U
#define IOMUX_GPIO48ECTL_EVTDETCFG_S                                 0U
#define IOMUX_GPIO48ECTL_EVTDETCFG_MASK                              0x00000000U
#define IOMUX_GPIO48ECTL_EVTDETCFG_POS_EDGE                          0x00000001U
#define IOMUX_GPIO48ECTL_EVTDETCFG_NEG_EDGE                          0x00000002U
#define IOMUX_GPIO48ECTL_EVTDETCFG_LEVEL                             0x00000003U
/*

        Field:           TRGLVL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field configures the io event polarity. This field is applicable only when [EVTDETCFG] is configured LEVEL

        ENUMs:
            HIGH:                        Non Inverted polarity
            LOW:                         Inverted polarity
*/
#define IOMUX_GPIO48ECTL_TRGLVL                                      0x00000004U
#define IOMUX_GPIO48ECTL_TRGLVL_M                                    0x00000004U
#define IOMUX_GPIO48ECTL_TRGLVL_S                                    2U
#define IOMUX_GPIO48ECTL_TRGLVL_HIGH                                 0x00000000U
#define IOMUX_GPIO48ECTL_TRGLVL_LOW                                  0x00000004U
/*

        Field:           CLR
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     This bit is to be used to generate CLR pulse for the event

        ENUMs:
            NOEFF:                       No effect
            CLEAR:                       Clear the event
*/
#define IOMUX_GPIO48ECTL_CLR                                         0x00000008U
#define IOMUX_GPIO48ECTL_CLR_M                                       0x00000008U
#define IOMUX_GPIO48ECTL_CLR_S                                       3U
#define IOMUX_GPIO48ECTL_CLR_NOEFF                                   0x00000000U
#define IOMUX_GPIO48ECTL_CLR_CLEAR                                   0x00000008U

#endif /* __HW_IOMUX_H__*/
