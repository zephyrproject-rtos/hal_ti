/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_commands_adc_noise_h__include
#define ti_drivers_RCL_commands_adc_noise_h__include

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/handlers/adc_noise.h>

typedef struct RCL_CMD_ADC_NOISE_GET RCL_CmdAdcNoiseGet;

/* Command IDs */
#define RCL_CMDID_ADC_NOISE_GET 0x0001

/* Max number of samples that can be collected in one session */
#define RCL_ADC_NOISE_MAX_NUM_WORDS (1024)

/**
 *  @brief ADC noise command
 *
 *  Command to collect ADC samples from radio.
 *
 *  This command is used to collect ADC samples from the radio. The samples represent noise (random data),
 *  and is intended only to be used as input for entropy generation.
 *
 *  If the output buffer is set to NULL, the samples must be read out by the caller before submitting a new RCL command.
 *  The location of the samples can always be read from the output-pointer, which will be updated by the RCL-handler
 *  in the case where a NULL-pointer is passed.
 *
 *  # Data format #
 *
 *  The data format of the output is described below
 *
 *  |  Word  |   word[31]   |   word[30..26]   |   word[25..21]   |   word[20..16]   |   word[15]   |   word[14..10]   |   word[9..5]   |   word[4..0]   |
 *  | --- | --- | --- | --- | --- | --- | --- | --- | --- |
 *  |  0  |  ‘0’  |  IAC2  |  IAC1  |  IAC0  |  ‘0’  |  QAC2  |  QAC1  |  QAC0  |
 *  |  1  |  ‘0’  |  IAC5  |  IAC4  |  IAC3  |  ‘0’  |  QAC5  |  QAC4  |  QAC3  |
 *  |  ...  |      |      |      |      |      |      |      |      |
 *  |   i   |  ‘0’  |  IAC(3i+2)  |  IAC(3i+1)  |  IAC(3i)  |  ‘0’  |  QAC(3i+2)  |  QAC(3i+1)  |  QAC(3i)  |
 *
 *
 */
struct RCL_CMD_ADC_NOISE_GET
{
    RCL_Command common;
    uint32_t numWords; /*!< Number of ADC sample words to collect. Range [1..1024] */
    uint32_t *output;  /*!< Buffer for storing ADC samples. NULL: Do not copy samples, but leave them in the LRF RAM.
                        *   This pointer will be updated by the RCL-handler to point to the location in RAM where
                        *   the data is stored.
                        */
};

#define RCL_CmdAdcNoiseGet_Default()                                    \
    (RCL_CmdAdcNoiseGet)                                                \
    {                                                                   \
        .common = RCL_Command_Default(RCL_CMDID_ADC_NOISE_GET,          \
                                      RCL_Handler_ADC_Noise_getNoise),  \
        .numWords = RCL_ADC_NOISE_MAX_NUM_WORDS,                        \
        .output = NULL,                                                 \
    }

#endif // ti_drivers_RCL_commands_adc_noise_h__include
