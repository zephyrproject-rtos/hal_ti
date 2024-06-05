/*
 * Copyright (c) 2023-2024, Texas Instruments Incorporated
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
/*
 *  ======== adc_noise.c ========
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Types.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>

#include <ti/drivers/rcl/commands/adc_noise.h>

#include <ti/log/Log.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe32.h)
#include DeviceFamily_constructPath(inc/rfe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/hw_lrfds2r.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)

/* Storage location of S2R samples */
#define ADC_NOISE_SAMPLE_MEM (PBE_RAM_BASE_ADDR)
#define ADC_NOISE_SAMPLE_PTR ((uint32_t *)ADC_NOISE_SAMPLE_MEM)
/* Start-address of PBE RAM in S2R address-space */
#ifdef DeviceFamily_CC23X0R2
#define ADC_NOISE_SAMPLE_MEM_S2R_START 1024
#else
#define ADC_NOISE_SAMPLE_MEM_S2R_START 2048
#endif

struct
{
    uint8_t synthRefsys:1;
    uint8_t powerUp:1;
    uint8_t s2rConversion:1;
} adcNoiseHandlerState;

static void RCL_Handler_Adc_Noise_configureS2R(uint32_t numWords);
static void RCL_Handler_Adc_Noise_powerUp(void);
static void RCL_Handler_Adc_Noise_powerDown(void);

/*
 *  ======== RCL_Handler_ADC_Noise_getNoise ========
 */
RCL_Events RCL_Handler_ADC_Noise_getNoise(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdAdcNoiseGet *adcCmd = (RCL_CmdAdcNoiseGet *)cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_CommandStatus startTimeStatus;

        /* Verify that length is greater than 0, and does not exceed maximum.
         * A length of 0 is not handled by the S2R module, so abort here.
         */
        if ((adcCmd->numWords == 0) || (adcCmd->numWords > RCL_ADC_NOISE_MAX_NUM_WORDS))
        {
            cmd->status = RCL_CommandStatus_Error_Param;
            rclEvents.lastCmdDone = 1;
            return rclEvents;
        }

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        /* Schedule new command start-time to wait for refsys */
        startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);

        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
            LRF_disableSynthRefsys();
        }
        else
        {
            /* Initialise handler state */
            adcNoiseHandlerState.powerUp = 0;
            adcNoiseHandlerState.s2rConversion = 0;

            /* Indicate that command has been accepted and is active */
            cmd->status = RCL_CommandStatus_Active;
            /* Update handler state */
            adcNoiseHandlerState.synthRefsys = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            if (adcNoiseHandlerState.synthRefsys != 0)
            {
                /* Power up hardware */
                RCL_Handler_Adc_Noise_powerUp();

                /* Configure S2R */
                RCL_Handler_Adc_Noise_configureS2R(adcCmd->numWords);

                Log_printf(RclCore, Log_VERBOSE, "RFE powered up. Configured S2R for %d words, buffer: 0x%x", adcCmd->numWords, adcCmd->output);

                adcNoiseHandlerState.synthRefsys = 0;
                adcNoiseHandlerState.powerUp = 1;
                rclEvents.cmdStarted = 1;
            }

            if (adcNoiseHandlerState.s2rConversion != 0)
            {
                /* Make sure S2R is complete */
                while (HWREG_READ_LRF(LRFDS2R_BASE + LRFDS2R_O_STAT) & LRFDS2R_STAT_RUNNING_M);

                /* Power down hardware */
                RCL_Handler_Adc_Noise_powerDown();

                if (adcCmd->output == NULL)
                {
                    /* Update output pointer if it was NULL */
                    adcCmd->output = ADC_NOISE_SAMPLE_PTR;
                }
                else
                {
                    /* Copy data from ADC_NOISE_SAMPLE_MEM to output buffer */
                    memcpy(adcCmd->output, ADC_NOISE_SAMPLE_PTR, adcCmd->numWords * sizeof(uint32_t));
                    /* Clear data from LRF RAM */
                    memset(ADC_NOISE_SAMPLE_PTR, 0, adcCmd->numWords * sizeof(uint32_t));
                }

                /* Command is complete */
                adcNoiseHandlerState.s2rConversion = 0;
                cmd->status = RCL_CommandStatus_Finished;
                rclEvents.lastCmdDone = 1;
            }
        }

        if (lrfEvents.rfedone != 0)
        {
            /* Hardware is powered up - proceed to start collecting samples */
            if (adcNoiseHandlerState.powerUp != 0)
            {
                RCL_CommandStatus startTimeStatus;

                /* Clear messagebox */
                HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX) = 0;
                /* Start RX */
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEAPI) = 3;
                /* Wait until RX is up and running */
                while ((HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_RFECMDIN) & 0x08) == 0);

                /* Disable LNA and mixer clocks to reduce impact of any signal received on the antenna */
                HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_LNA) & (~LRFDRFE_LNA_EN_M);
                HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_DIVCTL) = HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_DIVCTL) & (~(LRFDRFE_DIVCTL_RXPH90DIV_M | LRFDRFE_DIVCTL_RXPH0DIV_M));

                /* Initialize and enable ADC digital interface */
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_INIT) = (LRFDMDM_INIT_ADCDIG_RESET);
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_ENABLE) = (LRFDMDM_ENABLE_ADCDIG_EN);

                /* Trigger one shot capture */
                HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_TRIG) = LRFDS2R_TRIG_TRIG_ARM;

                /* Wait for S2R to complete by setting new handler start time.
                 * ADC sampling frequency is ~11.5 MSamples/s, or 3 words / 260 ns.
                 * We wait for (words / 3) * 250 ns, as there is no need to sleep for too long.
                 * The handler will poll for the last few us before reading out the samples
                 */
                startTimeStatus = RCL_Scheduler_setNewStartAbsTime(RCL_Scheduler_getCurrentTime() + adcCmd->numWords / 3, true);

                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                    RCL_Handler_Adc_Noise_powerDown();
                }
                else
                {
                    adcNoiseHandlerState.s2rConversion = 1;
                }

                adcNoiseHandlerState.powerUp = 0;
            }
        }
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Adc_Noise_configureS2R ========
 */
static void RCL_Handler_Adc_Noise_configureS2R(uint32_t numWords)
{
    /* Enable S2R module */
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_S2R_M);

    /* Configure S2R */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_ADCDIGCONF) = (1 << LRFDMDM_ADCDIGCONF_QBRANCHEN_S) | (1 << LRFDMDM_ADCDIGCONF_IBRANCHEN_S);

    /* Setup Sample capture, use PBE RAM for storing samples */
    HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_CFG) = ((LRFDS2R_CFG_TRIGMODE_ONESHOT) |
                                                    (LRFDS2R_CFG_SEL_ADCDIG) |
                                                    (LRFDS2R_CFG_CTL_EN));

    /* Set start-address of where to store samples */
    HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_START) = ADC_NOISE_SAMPLE_MEM_S2R_START;
    /* Set stop-address */
    HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_STOP) = ADC_NOISE_SAMPLE_MEM_S2R_START + numWords - 1;
}

/*
 *  ======== RCL_Handler_Adc_Noise_powerUp ========
 */
static void RCL_Handler_Adc_Noise_powerUp(void)
{
    /* Write precomputed frequency words, based on frequency: 2440000000 */
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_K5) = 0x9160;
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_CALMMID_CALMCRS) = 0x098604C4;
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PLLM0) = 0x130E0000;
    HWREG_WRITE_LRF(LRFDRFE32_BASE + LRFDRFE32_O_PLLM1) = 0x163B0000;
    HWREGH_WRITE_LRF(LRFD_RFERAM_BASE + RFE_COMMON_RAM_O_RXIF) = 0;

    /* Initialize and enable RFE TOPsm */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_INIT) = (1 << LRFDRFE_INIT_TOPSM_S);
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ENABLE) = (1 << LRFDRFE_ENABLE_TOPSM_S);

    /* Wait for boot done */
    while(HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX) != 4);

    /* Clear message box */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX) = 0;
    /* Calibrate PLL */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEAPI) = 4;

    /* Enable RFEDONE interrupt */
    LRF_enableHwInterrupt(LRFDDBELL_IMASK0_RFEDONE_M);
}

/*
 *  ======== RCL_Handler_Adc_Noise_powerDown ========
 */
static void RCL_Handler_Adc_Noise_powerDown(void)
{
    /* Disable RFEDONE interrupt */
    LRF_disableHwInterrupt(LRFDDBELL_IMASK0_RFEDONE_M);

    /* Clear message box */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX) = 0;
    /* Stop Radio */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEAPI) = 1;

    /* Wait until radio stops */
    while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEMSGBOX) == 0);

    /* Clear message box */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX) = 0;
    /* Stop PLL */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEAPI) = 5;

    /* Wait until radio stops */
    while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RFEMSGBOX) == 0);

    /* Disable S2R module */
    HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_CFG) = 0;
    /* Initialize/Reset (needed for safe shut down of ADCDIG) */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_INIT) = 0xFFFF;
    /* Stop modem */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_ENABLE) = 0;

    /* Request RFE powerdown */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PDREQ) = LRFDRFE_PDREQ_TOPSMPDREQ_M;
    /* Disable all RFE modules */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_ENABLE) = 0;
    /* Stop powerdown request */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PDREQ) = 0;

    /* Disable S2R module */
    LRF_clearRclClockEnable(LRFDDBELL_CLKCTL_S2R_M);

    /* Disable refsys */
    LRF_disableSynthRefsys();
}
