/*
 * Copyright (c) 2022-2026 Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       PowerWFF3.h
 *
 *  @brief      Power manager interface for WFF3 devices
 *
 *  The Power header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/Power.h>
 *  @endcode
 *
 *  Refer to @ref Power.h for a complete description of APIs.
 *
 *  ## Implementation #
 *  This header file defines the power resources, constraints, events, sleep
 *  states and transition latencies for WFF3 devices.
 *
 *  ============================================================================
 */

#ifndef ti_drivers_power_PowerWFF3__include
#define ti_drivers_power_PowerWFF3__include

#include <stdint.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_prcm_scratchpad.h)

#ifdef __cplusplus
extern "C" {
#endif

/*! The latency to reserve for resume from Sleep (usec) */
#define PowerWFF3_RESUMETIMESLEEP 15000

/*! The total latency to reserve for entry to and exit from Sleep (usec) */
#define PowerWFF3_TOTALTIMESLEEP 16000

/*! The initial delay when waking from Sleep (usec) */
#define PowerWFF3_WAKEDELAYSLEEP 15000

/* Resource IDs */

/*! Resource ID: DCAN */
#define PowerWFF3_PERIPH_DCAN 0

/*! Resource ID: GPTIMER 0 */
#define PowerWFF3_PERIPH_GPTIMER0 1

/*! Resource ID: GPTIMER 1 */
#define PowerWFF3_PERIPH_GPTIMER1 2

/*! Resource ID: I2C 0 */
#define PowerWFF3_PERIPH_I2C0 3

/*! Resource ID: I2C 1 */
#define PowerWFF3_PERIPH_I2C1 4

/*! Resource ID: I2S */
#define PowerWFF3_PERIPH_I2S 5

/*! Resource ID: SDMMC */
#define PowerWFF3_PERIPH_SDMMC 6

/*! Resource ID: SPI 0 */
#define PowerWFF3_PERIPH_SPI0 7

/*! Resource ID: SPI 1 */
#define PowerWFF3_PERIPH_SPI1 8

/*! Resource ID: SysTimer */
#define PowerWFF3_PERIPH_SYSTIMER 9

/*! Resource ID: UARTLIN 0 */
#define PowerWFF3_PERIPH_UARTLIN0 10

/*! Resource ID: UARTLIN 1 */
#define PowerWFF3_PERIPH_UARTLIN1 11

/*! Resource ID: SDIO */
#define PowerWFF3_PERIPH_SDIO 12

/*! Resource ID: ADC */
#define PowerWFF3_PERIPH_ADC0 13

/*! Resource ID: UARTLIN 2 */
#define PowerWFF3_PERIPH_UARTLIN2 14

/*! Resource ID: PDM */
#define PowerWFF3_PERIPH_PDM 15

/* \cond */
/* Number of resources in database.
 */
#define PowerWFF3_NUMRESOURCES 16
/* \endcond */

#define PowerWFF3_SLEEP   0x1 /*!< The SLEEP state */
/* \cond */
/* Internal flags for enabling/disabling resources */
#define PowerWFF3_ENABLE  1
#define PowerWFF3_DISABLE 0
/* \endcond */

/* Constraints
 *
 * Constraints restrict a specific system behavior from occurring or guarantee
 * a specified effect until released.
 * TODO: Update list of constraints for WFF3
 */

/*! Constraint: Disallow a transition to the SHUTDOWN state */
#define PowerWFF3_DISALLOW_SHUTDOWN 0

/*! Constraint: Disallow a transition to the SLEEP state */
#define PowerWFF3_DISALLOW_SLEEP 1

/*! Constraint: Disallow a transition to the IDLE state */
#define PowerWFF3_DISALLOW_IDLE 2

/* \cond */
#define PowerWFF3_NUMCONSTRAINTS 3 /* Number of constraints supported */
/* \endcond */

/*
 *  Events
 *
 *  Each event must be a power of two and must be sequential
 *  without any gaps.
 * TODO: Update list of events for WFF3
 */

/*! Power event: The device is entering the SLEEP state */
#define PowerWFF3_ENTERING_SLEEP (1 << 0)

/*! Power event: The device is entering the SHUTDOWN state */
#define PowerWFF3_ENTERING_SHUTDOWN (1 << 1)

/*! Power event: The device is waking up from the SLEEP state */
#define PowerWFF3_AWAKE_SLEEP (1 << 2)

/* \cond */
#define PowerWFF3_NUMEVENTS 3 /* Number of events supported */
/* \endcond */

/* \cond */
typedef uint8_t PowerWFF3_Resource; /* Power resource identifier */
/* \endcond */

/*! @brief Global configuration structure */
typedef struct
{
    /*!
     *  @brief The Power Policy's initialization function
     *
     *  If the policy does not have an initialization function, 'NULL'
     *  should be specified.
     */
    Power_PolicyInitFxn policyInitFxn;
    /*!
     *  @brief The Power Policy function
     *
     *  When enabled, this function is invoked in the idle loop, to
     *  opportunistically select and activate sleep states.
     *
     *  Two reference policies are provided:
     *
     *    PowerWFF3_doWFI() - a simple policy that invokes CPU wait for
     *    interrupt (WFI)
     *
     *    PowerWFF3_sleepPolicy() - an aggressive policy that considers
     *    constraints, time until next scheduled work, and SLEEP state
     *    latencies, and optionally puts the device into the SLEEP state,
     *    the IDLE state, or as a minimum, WFI.
     *
     *  Custom policies can be written, and specified via this function pointer.
     *
     *  In addition to this static selection, the Power Policy can be
     *  dynamically changed at runtime, via the Power_setPolicy() API.
     *
     *  If not NULL, the policy function will be invoked once for each pass
     *  of the idle loop.
     *
     *  The power policy can be dynamically
     *  enabled and disabled at runtime, via the Power_enablePolicy() and
     *  Power_disablePolicy() functions, respectively.
     */
    Power_PolicyFxn policyFxn;
} PowerWFF3_Config;

/*!
 * @brief Reasons the device has booted or rebooted.
 */
typedef enum
{
    /*! Device reset due to pin reset or power on reset */
    PowerWFF3_RESET_PIN_POR = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M,
    /*! Device reset due to low side rail voltage monitor tripping */
    PowerWFF3_RESET_RVML    = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M |
                           PRCM_SCRATCHPAD_RSTCAUS_RVML_M,
    /*! Device reset due to high side rail voltage monitor tripping */
    PowerWFF3_RESET_RVMH = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M |
                           PRCM_SCRATCHPAD_RSTCAUS_RVMH_M,
    /*! Device reset due to brownout event*/
    PowerWFF3_RESET_BOD = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M |
                          PRCM_SCRATCHPAD_RSTCAUS_BOD_M,
    /*! Device reset due to debug subsystem reset request */
    PowerWFF3_RESET_DSSM = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M |
                           PRCM_SCRATCHPAD_RSTCAUS_DBGSS_M,
    /*! Device reset due to watchdog timeout */
    PowerWFF3_RESET_M33WD = PRCM_SCRATCHPAD_RSTCAUS_RSTLINE_M | PRCM_SCRATCHPAD_RSTCAUS_POR_M |
                            PRCM_SCRATCHPAD_RSTCAUS_M33WD_M,
    /*! Device reset due to CPU reset event (for example triggered during OTA operation) */
    PowerWFF3_RESET_CPU = PRCM_SCRATCHPAD_RSTCAUS_SOCAONH_M | PRCM_SCRATCHPAD_RSTCAUS_OOFSLP_M |
                          PRCM_SCRATCHPAD_RSTCAUS_M33CRSLSTA_M,
    /*! RF core reset */
    PowerWFF3_RESET_RFCORE  = PRCM_SCRATCHPAD_RSTCAUS_M33CRSLSTA_M,
    /*! Unknown reset reason */
    PowerWFF3_RESET_UNKNOWN = UINT16_MAX,
} PowerWFF3_ResetReason;

/*!
 *  @brief  The wait for interrupt (WFI) policy
 *
 *  This is a lightweight Power Policy which simply invokes CPU wait for
 *  interrupt.
 *
 *  This policy can be selected statically via the policyFxn pointer in the
 *  PowerWFF3_Config structure, or dynamically at runtime, via
 *  Power_setPolicy().
 */
void PowerWFF3_doWFI(void);

/*!
 * @brief Returns the reason for the most recent reset or wakeup
 *
 * @return #PowerWFF3_ResetReason
 */
PowerWFF3_ResetReason PowerWFF3_getResetReason(void);

/*!
 *  @brief  The SLEEP Power Policy
 *
 *  This is an aggressive Power Policy, which considers active constraints,
 *  SLEEP state transition latencies, and time until the next scheduled
 *  work, and automatically transitions the device into the lowest power state
 *  possible.
 *
 *  The first goal is to enter SLEEP; if that is not appropriate
 *  given current conditions (e.g., the SLEEP transition latency is greater
 *  greater than the time until the next scheduled Clock event), then
 *  the secondary goal is the IDLE state; if that is disallowed (e.g., if
 *  the PowerWFF3_DISALLOW_IDLE constraint is declared), then the policy
 *  will fallback and simply invoke WFI, to clock gate the CPU until the next
 *  interrupt.
 *
 *  In order for this policy to run, it must be selected as the Power
 *  Policy (either by being specified as the 'policyFxn' in the
 *  PowerWFF3_Config structure, or specified at runtime with
 *  Power_setPolicy()), and the Power Policy must be enabled (either via
 *  'enablePolicy' in the PowerWFF3_Config structure, or via a call to
 *  Power_enablePolicy() at runtime).
 */
void PowerWFF3_sleepPolicy(void);
void PowerWFF3_schedulerDisable(void);
void PowerWFF3_schedulerRestore(void);

/*!
 *  @brief Select LFXT as the LFCLK source
 *
 *  This function configures the LFXT and sets it as the LFCLK source.
 *
 *  @pre Power_init()
 */
void PowerWFF3_selectLFXT(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_power_PowerWFF3__include */
