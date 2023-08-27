/******************************************************************************
*  Filename:       hw_ints_h
******************************************************************************
*  Copyright (c) 2021 Texas Instruments Incorporated. All rights reserved.
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
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
******************************************************************************/

#ifndef __HW_INTS_H__
#define __HW_INTS_H__

//*****************************************************************************
//
// The following are defines for the interrupt assignments.
//
//*****************************************************************************
#define INT_NMI_FAULT            2 // NMI Fault
#define INT_HARD_FAULT           3 // Hard Fault
#define INT_SVCALL              11 // Supervisor Call (SVCall)
#define INT_PENDSV              14 // Pending Service Call (PendSV)
#define INT_SYSTICK             15 // SysTick Interrupt from the System Timer
                                   // in NVIC.
#define INT_CPUIRQ0             16 // IRQ0: Configurable source controlled by
                                   // EVTSVT.CPUIRQ0SEL
#define INT_CPUIRQ1             17 // IRQ1: Configurable source controlled by
                                   // EVTSVT.CPUIRQ1SEL
#define INT_CPUIRQ2             18 // IRQ2: Configurable source controlled by
                                   // EVTSVT.CPUIRQ2SEL
#define INT_CPUIRQ3             19 // IRQ3: Configurable source controlled by
                                   // EVTSVT.CPUIRQ3SEL
#define INT_CPUIRQ4             20 // IRQ4: Configurable source controlled by
                                   // EVTSVT.CPUIRQ4SEL
#define INT_GPIO_COMB           21 // GPIO combined wake up interrupt,
                                   // interrupt flags can be found here
                                   // GPIO:MIS
#define INT_LRFD_IRQ0           22 // LRFD combined event, interrupt flags can
                                   // be found here LRFDDBELL:MIS0
#define INT_LRFD_IRQ1           23 // LRFD combined event, interrupt flags can
                                   // be found here LRFDDBELL:MIS1
#define INT_DMA_DONE_COMB       24 // DMA combined done interrupt,
                                   // corresponding flags can be found here
                                   // DMA:REQDONE
#define INT_AES_COMB            25 // AES accelerator combined interrupt
                                   // request, interrupt flags can be found
                                   // here AES:MIS
#define INT_SPI0_COMB           26 // SPI0 combined interrupt request,
                                   // interrupt flags can be found here
                                   // SPI0:MIS
#define INT_UART0_COMB          27 // UART0 combined interrupt, interrupt
                                   // flags are found here UART0:MIS
#define INT_I2C0_IRQ            28 // Interrupt event from I2C0, interrupt
                                   // flags can be found here I2C0:MIS
#define INT_LGPT0_COMB          29 // LGPT0 combined interrupt, interrupt
                                   // flags are found here LGPT0:MIS
#define INT_LGPT1_COMB          30 // LGPT1 combined interrupt, interrupt
                                   // flags are found here LGPT1:MIS
#define INT_ADC_COMB            31 // ADC combined interrupt request,
                                   // interrupt flags can be found here
                                   // ADC:MIS0
#define INT_CPUIRQ16            32 // IRQ16: Configurable source controlled by
                                   // EVTSVT.CPUIRQ16SEL
#define INT_LGPT2_COMB          33 // LGPT2 combined interrupt, interrupt
                                   // flags are found here LGPT2:MIS
#define INT_LGPT3_COMB          34 // LGPT3 combined interrupt, interrupt
                                   // flags are found here LGPT3:MIS

//*****************************************************************************
//
// The following are defines for number of interrupts and priority levels.
//
//*****************************************************************************
#define INT_PRI_LEVEL0          0x00000000 // Priority level 0 value
#define INT_PRI_LEVEL1          0x00000040 // Priority level 1 value
#define INT_PRI_LEVEL2          0x00000080 // Priority level 2 value
#define INT_PRI_LEVEL3          0x000000C0 // Priority level 3 value
#define INT_PRIORITY_MASK       0x000000C0 // Priority level mask
#define NUM_INTERRUPTS          35 // Number of exceptions
#define NUM_PRIORITY             4 // Number of exception priority levels
#define NUM_PRIORITY_BITS        2 // Number of exception priority bits

#endif // __HW_INTS__
