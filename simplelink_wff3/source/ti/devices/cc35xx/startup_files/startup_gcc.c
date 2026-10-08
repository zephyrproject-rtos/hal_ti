/******************************************************************************
 *  Filename:       startup_gcc.c
 *
 *  Description:    Startup code for CC35XX device family for use with GCC.
 *
 *  Copyright (c) 2024-2026 Texas Instruments Incorporated
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
// Check if compiler is GNU
//
//*****************************************************************************
#if !(defined(__GNUC__))
    #error "startup_gcc.c: Unsupported compiler!"
#endif

#include <string.h>

#include "../cmsis/device.h"
#include "../driverlib/interrupt.h"
#include "../driverlib/setup.h"
#include "../inc/hw_ints.h"

//*****************************************************************************
//
//! Forward declaration of the reset ISR and the default fault handlers.
//
//*****************************************************************************
void resetISR(void);
static void nmiISR(void);
static void faultISR(void);
static void defaultHandler(void);
static void busFaultHandler(void);
static void secureFaultHandler(void);

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Linker variable that marks the top of stack.
//
//*****************************************************************************
extern unsigned long _stack_end;

//*****************************************************************************
//
//! The vector table. Note that the proper constructs must be placed on this to
//! ensure that it ends up at physical address 0x14002000, which is the start
//! of the FLASH_INT_VEC region defined in the linker file.
//!
//! Marked as used due to being removed by LTO, but is used in resetISR().
//
//*****************************************************************************
__attribute__((section(".resetVecs"), used)) void (*const resetVectors[])(void) = {
    (void (*)(void))((uint32_t)&_stack_end), /* 0 The initial stack pointer. */
    resetISR,                                /* 1 The reset handler. */
    nmiISR,                                  /* 2 The NMI handler. */
    faultISR,                                /* 3 The hard fault handler. */
    defaultHandler,                          /* 4 The MPU fault handler. */
    busFaultHandler,                         /* 5 The bus fault handler. */
    defaultHandler,                          /* 6 The usage fault handler. */
    secureFaultHandler,                      /* 7 The secure fault handler. */
    0,                                       /* 8 Reserved. */
    0,                                       /* 9 Reserved. */
    0,                                       /* 10 Reserved. */
    defaultHandler,                          /* 11 SVCall handler. */
    defaultHandler,                          /* 12 Debug monitor handler. */
    0,                                       /* 13 Reserved. */
    defaultHandler,                          /* 14 The PendSV handler. */
    defaultHandler,                          /* 15 The SysTick handler. */
    /* --- External interrupts --- */
    defaultHandler, /* 16 INT_SP_UART_0_INT_REQ. */
    defaultHandler, /* 17 INT_SP_UART_1_INT_REQ. */
    defaultHandler, /* 18 INT_SP_I2C_0_INTREQ. */
    defaultHandler, /* 19 INT_SP_I2C_1_INTREQ. */
    defaultHandler, /* 20 INT_SP_SPI_0_EVT_REQ. */
    defaultHandler, /* 21 INT_SP_SPI_1_EVT_REQ. */
    defaultHandler, /* 22 INT_GPTIMER_0_EVT_CPU_IRQ. */
    defaultHandler, /* 23 INT_GPTIMER_1_EVT_CPU_IRQ. */
    defaultHandler, /* 24 INT_SP_UART_2_INT_REQ. */
    defaultHandler, /* 25 INT_I2S_IRQ_REQ. */
    defaultHandler, /* 26 INT_EVT_PDM_EVENT_REQ. */
    defaultHandler, /* 27 INT_EVT_SWINT0_REQ. */
    defaultHandler, /* 28 INT_EVT_SWINT1_REQ. */
    defaultHandler, /* 29 INT_EVT_SDMMC_PUB_REQ. */
    defaultHandler, /* 30 INT_SDIO_CARD_IRQ_REQ. */
    defaultHandler, /* 31 INT_ULL_USC_ULPADCHP_PUB_EVT0_REQ. */
    defaultHandler, /* 32 INT_NON_SECURED_GPIO_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 33 INT_SECURED_GPIO_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 34 INT_OSPR_HSM_HOST_0_SEC_IRQ. */
    defaultHandler, /* 35 INT_OSPR_HSM_HOST_0_IRQ. */
    defaultHandler, /* 36 INT_OSPR_HSM_HOST_1_IRQ. */
    defaultHandler, /* 37 INT_SVT_EVT_COMBINED_SYSTIM_OUT_IRQ. */
    defaultHandler, /* 38 INT_SVT_EVT_SYSTIMER_BIT_OUT_IRQ. */
    defaultHandler, /* 39 INT_SVT_EVT_SYSTIMER_OUT_0_IRQ. */
    defaultHandler, /* 40 INT_SVT_EVT_SYSTIMER_OUT_1_IRQ. */
    defaultHandler, /* 41 INT_NON_SECURED_DMA_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 42 INT_SECURED_DMA_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 43 INT_NON_SECURED_DOORBELL_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 44 INT_SECURED_DOORBELL_IRQ_EVT_IND_OUT. */
    defaultHandler, /* 45 INT_ICACHE_ERR_IRQ. */
    defaultHandler, /* 46 INT_OSPI_IRQ. */
    defaultHandler, /* 47 INT_OTFDE_IRQ. */
    defaultHandler, /* 48 INT_XIP_ARB_IRQ. */
    defaultHandler, /* 49 INT_XIP_DMA_SEC_IRQ. */
    defaultHandler, /* 50 INT_XIP_DMA_NONSEC_IRQ. */
    defaultHandler, /* 51 INT_SW_INTERRUPT_0. */
    defaultHandler, /* 52 INT_SW_INTERRUPT_1. */
    defaultHandler, /* 53 INT_SW_INTERRUPT_2. */
    defaultHandler, /* 54 INT_SW_INTERRUPT_3. */
    defaultHandler, /* 55 INT_SW_INTERRUPT_4. */
    defaultHandler, /* 56 INT_SW_INTERRUPT_5. */
    defaultHandler, /* 57 INT_SW_INTERRUPT_6. */
    defaultHandler, /* 58 INT_SW_INTERRUPT_7. */
    defaultHandler, /* 59 INT_PRCM_IRQ. */
    defaultHandler, /* 60 INT_OCLA_IRQ. */
    defaultHandler, /* 61 INT_HIF_FIFO_IRQ. */
    defaultHandler, /* 62 INT_HOST_ELP_TMR_WAKEUP_REQ. */
    defaultHandler, /* 63 INT_NAB_HOST_IRQ. */
    defaultHandler, /* 64 INT_BLE_RFC_GPO_8_IRQ. */
    defaultHandler, /* 65 INT_RTC_EVENT_IRQ. */
    defaultHandler, /* 66 INT_DEBUGSS_HOST_CSYSPWRUPREQ. */
    defaultHandler, /* 67 INT_DEBUGSS_HOST_FORCEACTIVE. */
    defaultHandler, /* 68 INT_SECURED_ERROR_IRQ_EVT_IND_OUT. */
};

//*****************************************************************************
//
// The following are arrays of pointers to constructor functions that need to
// be called during startup to initialize global objects.
//
//*****************************************************************************
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

//*****************************************************************************
//
// The following global variable is required for C++ support.
//
//*****************************************************************************
void *__dso_handle = (void *)&__dso_handle;

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// "data" and "bss" segments reside in memory. The initializers for the
// "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern uint32_t __bss_start__, __bss_end__;
extern uint32_t __psram_bss_start__, __psram_bss_end__;
extern uint32_t __tcm_data_load__, __tcm_data_start__, __tcm_data_end__;
extern uint32_t __data_load__, __data_start__, __data_end__;
extern uint32_t __psram_data_load__, __psram_data_start__, __psram_data_end__;
extern uint32_t __ramfunc_load__, __ramfunc_start__, __ramfunc_end__;

//*****************************************************************************
//
//! Initialize the .data and .bss sections and copy the first 16 vectors from
//! the read-only/reset table to the runtime RAM table. Fill the remaining
//! vectors with a stub. This vector table will be updated at runtime.
//!
//! Marked as used due to being removed by LTO, but is used in resetISR().
//
//*****************************************************************************
__attribute__((used)) void localProgramStart(void)
{
    uint32_t *bs;
    uint32_t *be;
    uint32_t *dl;
    uint32_t *ds;
    uint32_t *de;
    uint32_t count;
    uint32_t i;

#if defined(__VFP_FP__) && !defined(__SOFTFP__)
    volatile uint32_t *pui32Cpacr = (uint32_t *)0xE000ED88;

    /* Enable Coprocessor Access Control (CPAC) */
    *pui32Cpacr |= (0xF << 20);
#endif

    IntDisableMaster();

    /* Final trim of device. */
    SetupTrimDevice();

    /* Initialize .bss to zero. */
    bs = &__bss_start__;
    be = &__bss_end__;
    while (bs < be)
    {
        *bs = 0;
        bs++;
    }

    /* Initialize .psram_bss to zero. */
    bs = &__psram_bss_start__;
    be = &__psram_bss_end__;
    while (bs < be)
    {
        *bs = 0;
        bs++;
    }

    /* Relocate the .TI.ramfunc section to CRAM. PowerWFF3_enterSleep and
     * other RAM functions must execute from CRAM since flash is powered down
     * during deep sleep.
     */
    dl = &__ramfunc_load__;
    ds = &__ramfunc_start__;
    de = &__ramfunc_end__;
    if (dl != ds)
    {
        while (ds < de)
        {
            *ds = *dl;
            dl++;
            ds++;
        }
    }

    /* Relocate the .tcm_data section. */
    dl = &__tcm_data_load__;
    ds = &__tcm_data_start__;
    de = &__tcm_data_end__;
    if (dl != ds)
    {
        while (ds < de)
        {
            *ds = *dl;
            dl++;
            ds++;
        }
    }

    /* Relocate the .data section. */
    dl = &__data_load__;
    ds = &__data_start__;
    de = &__data_end__;
    if (dl != ds)
    {
        while (ds < de)
        {
            *ds = *dl;
            dl++;
            ds++;
        }
    }

    /* Relocate the .psram_data section. */
    dl = &__psram_data_load__;
    ds = &__psram_data_start__;
    de = &__psram_data_end__;
    if (dl != ds)
    {
        while (ds < de)
        {
            *ds = *dl;
            dl++;
            ds++;
        }
    }

    /* Run any constructors. */
    count = (uint32_t)(__init_array_end - __init_array_start);
    for (i = 0; i < count; i++)
    {
        __init_array_start[i]();
    }

    /* Call the application's entry point. */
    main();

    /* If we ever return signal Error. */
    faultISR();
}

//*****************************************************************************
//
//! This is the code that gets called when the processor first starts execution
//! following a reset event. Only the absolutely necessary set is performed,
//! after which the application supplied entry() routine is called. Any fancy
//! actions (such as making decisions based on the reset cause register, and
//! resetting the bits in that register) are left solely in the hands of the
//! application.
//!
//! .ltorg is added to avoid literal pool errors when LTO is enabled.
//
//*****************************************************************************
void __attribute__((naked)) resetISR(void)
{
    __asm__ __volatile__(" movw r0, #:lower16:resetVectors\n"
                         " movt r0, #:upper16:resetVectors\n"
                         " ldr r0, [r0]\n"
                         " mov sp, r0\n"
                         " bl localProgramStart\n"
                         " .ltorg\n");
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
//! This is the code that gets called when the processor receives a bus fault.
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//
//*****************************************************************************
static void busFaultHandler(void)
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
static void defaultHandler(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives a secure fault.
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//
//*****************************************************************************
static void secureFaultHandler(void)
{
    /* Enter an infinite loop. */
    while (1) {}
}

//*****************************************************************************
//
//! This function is called by __libc_fini_array which gets called when exit()
//! is called. In order to support exit(), an empty _fini() stub function is
//! required.
//
//*****************************************************************************
void _fini(void)
{
    /* Function body left empty intentionally. */
}
