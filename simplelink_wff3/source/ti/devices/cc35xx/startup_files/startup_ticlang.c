/******************************************************************************
 *  Filename:       startup_ticlang.c
 *
 *  Description:    Startup code for CC35XX device family for use with
 *                  TI Clang/LLVM.
 *
 *  Copyright (c) 2022-2026 Texas Instruments Incorporated
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

//*****************************************************************************
//
// Check if compiler is TICLANG
//
//*****************************************************************************
#if !(defined(__clang__))
    #error "startup_ticlang.c: Unsupported compiler!"
#endif

#include "../cmsis/device.h"
#include "../driverlib/interrupt.h"
#include "../driverlib/setup.h"
#include "../inc/hw_ints.h"
#include "../inc/hw_types.h"

//*****************************************************************************
//
//! Forward declaration of the reset ISR and the default fault handlers.
//
//*****************************************************************************
void resetISR(void);
static void nmiISR(void);
static void faultISR(void);
static void intDefaultHandler(void);
static void secureFaultHandler(void);

//*****************************************************************************
//
// The entry point for the application startup code.
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// TIClang: Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern unsigned long __STACK_END;

//*****************************************************************************
//
//! The vector table. Note that the proper constructs must be placed on this to
//! ensure that it ends up at physical address 0x14002000, which is the start
//! of the FLASH_INT_VEC region defined in the linker file.
//
//*****************************************************************************
__attribute__((section(".resetVecs"), retain)) void (*const resetVectors[])(void) = {
    (void (*)(void))((unsigned long)&__STACK_END), /*  0 The initial stack pointer. */
    resetISR,                                      /*  1 The reset handler. */
    nmiISR,                                        /*  2 The NMI handler. */
    faultISR,                                      /*  3 The hard fault handler. */
    intDefaultHandler,                             /*  4 The MPU fault handler. */
    intDefaultHandler,                             /*  5 The bus fault handler. */
    intDefaultHandler,                             /*  6 The usage fault handler. */
    secureFaultHandler,                            /*  7 The secure fault handler. */
    0,                                             /*  8 Reserved. */
    0,                                             /*  9 Reserved. */
    0,                                             /* 10 Reserved. */
    intDefaultHandler,                             /* 11 SVCall handler. */
    intDefaultHandler,                             /* 12 Debug monitor handler. */
    0,                                             /* 13 Reserved. */
    intDefaultHandler,                             /* 14 The PendSV handler. */
    intDefaultHandler,                             /* 15 The SysTick handler. */
    /* --- External interrupts --- */
    intDefaultHandler, /* 16 INT_SP_UART_0_INT_REQ. */
    intDefaultHandler, /* 17 INT_SP_UART_1_INT_REQ. */
    intDefaultHandler, /* 18 INT_SP_I2C_0_INTREQ. */
    intDefaultHandler, /* 19 INT_SP_I2C_1_INTREQ. */
    intDefaultHandler, /* 20 INT_SP_SPI_0_EVT_REQ. */
    intDefaultHandler, /* 21 INT_SP_SPI_1_EVT_REQ. */
    intDefaultHandler, /* 22 INT_GPTIMER_0_EVT_CPU_IRQ. */
    intDefaultHandler, /* 23 INT_GPTIMER_1_EVT_CPU_IRQ. */
    intDefaultHandler, /* 24 INT_SP_UART_2_INT_REQ. */
    intDefaultHandler, /* 25 INT_I2S_IRQ_REQ. */
    intDefaultHandler, /* 26 INT_EVT_PDM_EVENT_REQ. */
    intDefaultHandler, /* 27 INT_EVT_SWINT0_REQ. */
    intDefaultHandler, /* 28 INT_EVT_SWINT1_REQ. */
    intDefaultHandler, /* 29 INT_EVT_SDMMC_PUB_REQ. */
    intDefaultHandler, /* 30 INT_SDIO_CARD_IRQ_REQ. */
    intDefaultHandler, /* 31 INT_ULL_USC_ULPADCHP_PUB_EVT0_REQ. */
    intDefaultHandler, /* 32 INT_NON_SECURED_GPIO_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 33 INT_SECURED_GPIO_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 34 INT_OSPR_HSM_HOST_0_SEC_IRQ. */
    intDefaultHandler, /* 35 INT_OSPR_HSM_HOST_0_IRQ. */
    intDefaultHandler, /* 36 INT_OSPR_HSM_HOST_1_IRQ. */
    intDefaultHandler, /* 37 INT_SVT_EVT_COMBINED_SYSTIM_OUT_IRQ. */
    intDefaultHandler, /* 38 INT_SVT_EVT_SYSTIMER_BIT_OUT_IRQ. */
    intDefaultHandler, /* 39 INT_SVT_EVT_SYSTIMER_OUT_0_IRQ. */
    intDefaultHandler, /* 40 INT_SVT_EVT_SYSTIMER_OUT_1_IRQ. */
    intDefaultHandler, /* 41 INT_NON_SECURED_DMA_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 42 INT_SECURED_DMA_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 43 INT_NON_SECURED_DOORBELL_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 44 INT_SECURED_DOORBELL_IRQ_EVT_IND_OUT. */
    intDefaultHandler, /* 45 INT_ICACHE_ERR_IRQ. */
    intDefaultHandler, /* 46 INT_OSPI_IRQ. */
    intDefaultHandler, /* 47 INT_OTFDE_IRQ. */
    intDefaultHandler, /* 48 INT_XIP_ARB_IRQ. */
    intDefaultHandler, /* 49 INT_XIP_DMA_SEC_IRQ. */
    intDefaultHandler, /* 50 INT_XIP_DMA_NONSEC_IRQ. */
    intDefaultHandler, /* 51 INT_SW_INTERRUPT_0. */
    intDefaultHandler, /* 52 INT_SW_INTERRUPT_1. */
    intDefaultHandler, /* 53 INT_SW_INTERRUPT_2. */
    intDefaultHandler, /* 54 INT_SW_INTERRUPT_3. */
    intDefaultHandler, /* 55 INT_SW_INTERRUPT_4. */
    intDefaultHandler, /* 56 INT_SW_INTERRUPT_5. */
    intDefaultHandler, /* 57 INT_SW_INTERRUPT_6. */
    intDefaultHandler, /* 58 INT_SW_INTERRUPT_7. */
    intDefaultHandler, /* 59 INT_PRCM_IRQ. */
    intDefaultHandler, /* 60 INT_OCLA_IRQ. */
    intDefaultHandler, /* 61 INT_HIF_FIFO_IRQ. */
    intDefaultHandler, /* 62 INT_HOST_ELP_TMR_WAKEUP_REQ. */
    intDefaultHandler, /* 63 INT_NAB_HOST_IRQ. */
    intDefaultHandler, /* 64 INT_BLE_RFC_GPO_8_IRQ. */
    intDefaultHandler, /* 65 INT_RTC_EVENT_IRQ. */
    intDefaultHandler, /* 66 INT_DEBUGSS_HOST_CSYSPWRUPREQ. */
    intDefaultHandler, /* 67 INT_DEBUGSS_HOST_FORCEACTIVE. */
    intDefaultHandler, /* 68 INT_SECURED_ERROR_IRQ_EVT_IND_OUT. */
};

//*****************************************************************************
//
//! This is the code that gets called when the processor first starts execution
//! following a reset event. Only the absolutely necessary set is performed,
//! after which the application supplied entry() routine is called. Any fancy
//! actions (such as making decisions based on the reset cause register, and
//! resetting the bits in that register) are left solely in the hands of the
//! application.
//
//*****************************************************************************
void resetISR(void)
{
    IntDisableMaster();

    /* Final trim of device. */
    SetupTrimDevice();

    /* Jump to the C Initialization Routine. */
    __asm(" .global _c_int00\n"
          " bl      _c_int00");

    /* If we ever return, signal Error. */
    faultISR();
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives an NMI. This
//! simply enters an infinite loop, preserving the system state for examination
//! by a debugger.
//
//*****************************************************************************
static void nmiISR(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives a fault
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void faultISR(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives an unexpected
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void intDefaultHandler(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives a secure fault
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void secureFaultHandler(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}
