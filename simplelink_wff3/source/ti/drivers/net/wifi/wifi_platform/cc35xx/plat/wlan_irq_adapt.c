/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "osi_type.h"
#include "osi_kernel.h"
#include "wlan_if.h"
#include "ti/devices/cc35xx/driverlib/interrupt.h" //from driverlib
#include "ti/devices/cc35xx/inc/hw_prcm_aon.h"
#include "ti/devices/cc35xx/inc/hw_memmap.h"
#include "ti/devices/cc35xx/inc/hw_soc_aon.h"
#include "ti/devices/cc35xx/inc/hw_hostmcu_aon.h"

#define IRQ_OFFSET 0

#define NUM_OF_SYS_INTER  (16)
/****************************************************************************
 *
 *                      Internal helper functions and macros
 *
 ****************************************************************************/

/*!
    \brief initialize the input coming from the wifi part
    \param cb - ISR called upon assertion
    \note
        - input should be triggered either -
          - Falling edge - no need to implement Wlan_IRQ_enable_int Wlan_IRQ_disable_int and Wlan_IRQ_clear_int
          - Active low - must implement Wlan_IRQ_enable_int amd Wlan_IRQ_disable_int
    \return
    \warning
*/
void wlan_IRQInit(void *cb)
{
    uint32_t regVal = 0;
    osi_EnterCriticalSection();

    // Set callback func to host IRQ
    IntRegister(INT_NAB_HOST_IRQ - IRQ_OFFSET,cb);
    IntSetPriority(INT_NAB_HOST_IRQ - IRQ_OFFSET,INT_PRI_LEVEL2);//must be >= configMAX_SYSCALL_INTERRUPT_PRIORITY (0x20); INI_PRI_LEVEL2=0x20 satisfies this
    //Set HIF as Wakeup Source
    regVal = HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS); //HOSTMCU_AON__HOST_ELP_CFG_WICSENSE
    regVal |= 0x800; // Set  Bit 11 : nab_host_irq
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) = regVal;

    //fast wakeup source
    regVal = HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWUTP);
    regVal |= 0x800; // Set  Bit 11 : nab_host_irq
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWUTP) = regVal;
    
    osi_ExitCriticalSection(0);
}
void wlan_IRQInitBeforeHwInit(void *cb)
{
    wlan_IRQInit(cb);
}
/*!
    \brief removes the input from the system's interrupts
    \note
    \return
    \warning
*/
void wlan_IRQDeinit()
{
    osi_EnterCriticalSection();

    // Clear callback func to host IRQ
    IntUnregister(INT_NAB_HOST_IRQ - IRQ_OFFSET);

    // Disable IRQ
    IntDisable(INT_NAB_HOST_IRQ - IRQ_OFFSET);

    osi_ExitCriticalSection(0);
}

/*!
    \brief wlan enable input interrupt
    \note need to implement only if working with active low assertion
    \return
    \warning
*/
void wlan_IRQEnableInt()
{
    osi_EnterCriticalSection();

    // Enable NVIC IRQ
    IntEnable(INT_NAB_HOST_IRQ - IRQ_OFFSET);

    osi_ExitCriticalSection(0);
}

/*!
    \brief wlan disable input interrupt
    \note need to implement only if working with active low assertion
    \return
    \warning
*/
void wlan_IRQDisableInt()
{
    osi_EnterCriticalSection();

    // Enable IRQ
    IntDisable(INT_NAB_HOST_IRQ - IRQ_OFFSET);

    osi_ExitCriticalSection(0);
}



/*!
    \brief wlan clear pending interrupt
    \note need to implement only if working with active low assertion
    \return
    \warning
*/
void wlan_IRQClearInt()
{
    osi_EnterCriticalSection();

    //this is edge triggered so no need to mask the interrupt
    IntClearPend(INT_NAB_HOST_IRQ - IRQ_OFFSET);

    osi_ExitCriticalSection(0);
}



/*!
    \brief use pre - configured output  to turn off the WiFi device
    \note
        - need to use pre configured  - set  output to 0 for off and 1 for on
    \return
    \warning
*/
void wlan_TurnOffWlan()
{
//    HWREG(SOC_AON_BASE + SOC_AON_O_CONNSTPCTL) = SOC_AON_CONNSTPCTL_SWITCH;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_CONNSTP) = PRCM_AON_CONNSTP_SET;
    osi_uSleep(500);
#if 0 
    if(0 == gWlanENGpioAddr)
    {
        /* Get address after translation translate */
        gWlanENGpioAddr = (uint32_t) AddrTranslateP_getLocalAddr(WLAN_EN_BASE_ADDR);
        GPIO_setDirMode(gWlanENGpioAddr, WLAN_EN_PIN, WLAN_EN_DIR);
    }


    GPIO_pinWriteLow(gWlanENGpioAddr, WLAN_EN_PIN);
#endif 
}

/*!
    \brief use pre - configured output  to turn on the WiFi device
    \note
        - need to use pre configured GPIO - set output to 0 for off and 1 for on
    \return
    \warning
*/
void wlan_TurnOnWlan()
{
//    HWREG(SOC_AON_BASE + SOC_AON_O_CONNSTPCTL) = SOC_AON_CONNSTPCTL_SWITCH;
    HWREG(PRCM_AON_BASE + PRCM_AON_O_CONNSTP) = 0;

#if 0 

    if(0 == gWlanENGpioAddr)
    {
        /* Get address after translation translate */
        gWlanENGpioAddr = (uint32_t) AddrTranslateP_getLocalAddr(WLAN_EN_BASE_ADDR);
        GPIO_setDirMode(gWlanENGpioAddr, WLAN_EN_PIN, WLAN_EN_DIR);
    }

    if(1 == GPIO_pinOutValueRead(gWlanENGpioAddr, WLAN_EN_PIN))
    {
        TurnOff_WL();
    }
    osi_Sleep(2);
    GPIO_pinWriteHigh(gWlanENGpioAddr, WLAN_EN_PIN);

    osi_Sleep(2);

#endif 
}

/*!
    \brief get the state of the pre - configured output GPIO
    \note
    \return 0 or 1 output
    \warning
*/
int wlan_GetStateWlan()
{
#if 0 // TODO to add detection if wlan is already up.

    if(0 == gWlanENGpioAddr)
    {
        /* Get address after translation translate */
        gWlanENGpioAddr = (uint32_t) AddrTranslateP_getLocalAddr(WLAN_EN_BASE_ADDR);
        GPIO_setDirMode(gWlanENGpioAddr, WLAN_EN_PIN, WLAN_EN_DIR);
    }
    return GPIO_pinOutValueRead(gWlanENGpioAddr, WLAN_EN_PIN);

#else
    return DEVICE_OFF;
#endif
}

/*!
    \brief disables the irq on the function IRQ handler
    \note
    \return 0 or 1 output
    \warning
*/
void wlan_IRQDisableOnIRQHandler()
{
    /* Called from ISR context - use IntDisable directly to avoid calling
     * vTaskSuspendAll/xTaskResumeAll from ISR via osi_EnterCriticalSection. */
    IntDisable(INT_NAB_HOST_IRQ - IRQ_OFFSET);
}
