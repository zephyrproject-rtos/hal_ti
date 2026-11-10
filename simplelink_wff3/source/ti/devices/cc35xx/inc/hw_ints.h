/******************************************************************************
*  Filename:       hw_ints.h
*
*  Copyright (c) 2022-2025 Texas Instruments Incorporated
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
*  3) Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
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
*
******************************************************************************/

#ifndef __HW_INTS_H__
#define __HW_INTS_H__

//*****************************************************************************
//
// The following are defines for the interrupt assignments.
//
//*****************************************************************************
#define INT_NMI_FAULT           2   //-14  NMI Fault
#define INT_HARD_FAULT          3   //-13  Hard Fault
#define INT_MEMMANAGE_FAULT     4   //-12  Memory Management (MemManage) Fault
#define INT_BUS_FAULT           5   //-11  Bus Fault
#define INT_USAGE_FAULT         6   //-10  Usage Fault
#define INT_SVCALL              11  //-5   Supervisor Call (SVCall)
#define INT_DEBUG               12  //-4   Debug Monitor
#define INT_PENDSV              14  //-2   Pending Service Call (PendSV)
#define INT_SYSTICK             15  //-1   SysTick Interrupt from the System Timer
                                    // in NVIC.


#define INT_SP_UART_0_INT_REQ                        16      //0   UART   0            interrupt
#define INT_SP_UART_1_INT_REQ                        17      //1   UART   2            interrupt
#define INT_SP_I2C_0_INTREQ                          18      //2   I2C    0            interrupt
#define INT_SP_I2C_1_INTREQ                          19      //3   I2C    1            interrupt
#define INT_SP_SPI_0_EVT_REQ                         20      //4   SPI    0            interrupt
#define INT_SP_SPI_1_EVT_REQ                         21      //5   SPI    1            interrupt
#define INT_GPTIMER_0_EVT_CPU_IRQ                    22      //6   GPT    0            interrupt
#define INT_GPTIMER_1_EVT_CPU_IRQ                    23      //7   GPT    1            interrupt
#define INT_SP_UART_2_INT_REQ                        24      //8   UART   2            interrupt
#define INT_I2S_IRQ_REQ                              25      //9   I2S                 interrupt
#define INT_EVT_PDM_EVENT_REQ                        26      //10  PDM                 interrupt
#define INT_EVT_SWINT0_REQ                           27      //11  SWINT  0            interrupt
#define INT_EVT_SWINT1_REQ                           28      //12  SWINT  1            interrupt
#define INT_EVT_SDMMC_PUB_REQ                        29      //13  SDMMC               interrupt
#define INT_SDIO_CARD_IRQ_REQ                        30      //14  SDIO                interrupt
#define INT_ULL_USC_ULPADCHP_PUB_EVT0_REQ            31      //15
#define INT_NON_SECURED_GPIO_IRQ_EVT_IND_OUT         32      //16  GPIO_NS             interrupt
#define INT_SECURED_GPIO_IRQ_EVT_IND_OUT             33      //17  GPIO_S              interrupt
#define INT_OSPR_HSM_HOST_0_SEC_IRQ                  34      //18  HSM_S  0            interrupt
#define INT_OSPR_HSM_HOST_0_IRQ                      35      //19  HSM_NS 0            interrupt
#define INT_OSPR_HSM_HOST_1_IRQ                      36      //20  HSM_NS 1            interrupt
#define INT_SVT_EVT_COMBINED_SYSTIM_OUT_IRQ          37      //21  SYSTIM_COMB         interrupt
#define INT_SVT_EVT_SYSTIMER_BIT_OUT_IRQ             38      //22  SYSTIM_BIT          interrupt
#define INT_SVT_EVT_SYSTIMER_OUT_0_IRQ               39      //23  SYSTIM 0            interrupt
#define INT_SVT_EVT_SYSTIMER_OUT_1_IRQ               40      //24  SYSTIM 1            interrupt
#define INT_NON_SECURED_DMA_IRQ_EVT_IND_OUT          41      //25  DMA_NS              interrupt
#define INT_SECURED_DMA_IRQ_EVT_IND_OUT              42      //26  DMA_S               interrupt
#define INT_NON_SECURED_DOORBELL_IRQ_EVT_IND_OUT     43      //27  DOORBELL_NS         interrupt
#define INT_SECURED_DOORBELL_IRQ_EVT_IND_OUT         44      //28  DOORBELL_S          interrupt
#define INT_ICACHE_ERR_IRQ                           45      //29  ICACHE_ERR          interrupt
#define INT_OSPI_IRQ                                 46      //30  OSPI                interrupt
#define INT_OTFDE_IRQ                                47      //31  OTFDE               interrupt
#define INT_XIP_ARB_IRQ                              48      //32  XIP_ARN             interrupt
#define INT_XIP_DMA_SEC_IRQ                          49      //33  XIP_DMA_S           interrupt
#define INT_XIP_DMA_NONSEC_IRQ                       50      //34  XIP_DMA_NS          interrupt
#define INT_SW_INTERRUPT_0                           51      //35  SW     0            interrupt
#define INT_SW_INTERRUPT_1                           52      //36  SW     1            interrupt
#define INT_SW_INTERRUPT_2                           53      //37  SW     2            interrupt
#define INT_SW_INTERRUPT_3                           54      //38  SW     3            interrupt
#define INT_SW_INTERRUPT_4                           55      //39  SW     4            interrupt
#define INT_SW_INTERRUPT_5                           56      //40  SW     5            interrupt
#define INT_SW_INTERRUPT_6                           57      //41  SW     6            interrupt
#define INT_SW_INTERRUPT_7                           58      //42  SW     7            interrupt
#define INT_PRCM_IRQ                                 59      //43  PRCM                interrupt
#define INT_OCLA_IRQ                                 60      //44  OCLA                interrupt
#define INT_HIF_FIFO_IRQ                             61      //45  HIF                 interrupt
//Wakeup events
#define INT_HOST_ELP_TMR_WAKEUP_REQ                  62      //46  ELP_TMR             interrupt
#define INT_NAB_HOST_IRQ                             63      //47  NAB_HOST            interrupt
#define INT_BLE_RFC_GPO_8_IRQ                        64      //48  BLE_RFC             interrupt
#define INT_RTC_EVENT_IRQ                            65      //49  RTC                 interrupt
#define INT_DEBUGSS_HOST_CSYSPWRUPREQ                66      //50  DEBUGSS_PWRUP       interrupt
#define INT_DEBUGSS_HOST_FORCEACTIVE                 67      //51  DEBUGSS_FORCEACTIVE interrupt
#define INT_SECURED_ERROR_IRQ_EVT_IND_OUT            68      //52


#define NUM_INTERRUPTS                               69      //Number of interrupts
#define NUM_PRIORITY                                 16      //Number of priority levels
#define NUM_PRIORITY_BITS                            4       //Number of priority bits

#endif // __HW_INTS__
