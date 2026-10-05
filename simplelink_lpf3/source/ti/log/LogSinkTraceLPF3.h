/*
 * Copyright (c) 2024-2025 Texas Instruments Incorporated - http://www.ti.com
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

/*!*****************************************************************************
 *  @file       LogSinkTraceLPF3.h
 *  @brief      <b>PRELIMINARY</b> LogSinkTraceLPF3 interface
 *
 *  <b>WARNING</b> These APIs are <b>PRELIMINARY</b>, and subject to
 *  change in the next few months.
 *
 *  The LogSinkTraceLPF3 module is a sink that can be used in conjunction with
 *  the Log.h API. The API defined in this file should not be used directly, but
 *  is made available to the Logging framework and used as a transport layer for
 *  Log.h
 *
 *  To use the LogSinkTraceLPF3 sink, ensure that the correct library for your
 *  device is linked in and include this header file as follows:
 *  @code
 *  #include <ti/log/LogSinkTraceLPF3.h>
 *  @endcode
 *
 *  Additionally, LogSinkTraceLPF3_init must be called before LogSinkTraceLPF3
 *  can be used. It is called from Board_init() and thus can only be called if
 *  SysConfig is used and the LogSinkTraceLPF3 module is enabled.
 *  @code
 *  // Initialize LogSinkTraceLPF3 sink
 *  LogSinkTraceLPF3_init();
 *  @endcode
 *
 *  This module implements one function that is required by the Log API:
 *   - printf(const Log_Module *handle, uint32_t header, uint32_t headerPtr,
 *     uint32_t numArgs, ...);
 *
 *  Whenever a log-statement is invoked, that uses LogSinkTraceLPF3 as its sink,
 *  the function above is ultimately invoked.
 *
 *  Note: buf(const Log_Module *handle, uint32_t header, uint32_t headerPtr,
 *  uint8_t *data, size_t size) is not implemented due to hardware limitations
 *  with this sink.
 *
 *  @anchor ti_log_LogSinkTraceLPF3_Overview
 *  # Overview
 *  LogSinkTraceLPF3 is a sink/transport layer that is able to output
 *  log-statements over the tracer. The tracer is a hardware module inside the
 *  radio core which can extract logs at high speed. LogSinkTraceLPF3 uses the
 *  tracer to stream data out onto a user-selectable pin. The frequency of the
 *  data stream is set by the RF tracer prescaler which divides the internal 24
 *  MHz clock. Hardware and software needed to decode the data stream is
 *  currently only available through TI.
 *
 *  @anchor ti_log_LogSinkTraceLPF3_Channels
 *  # Tracer Channels
 *  LogSinkTraceLPF3 uses certain channels for different purposes. Separate
 *  channels are used for data transfer, time synchronization, etc. Channel 1 is
 *  used for logs inside the CPU. The other channels are used by the internal
 *  parts of the radio.
 *
 *  @anchor ti_log_LogSinkTraceLPF3_Timestamps
 *  # Tracer Timestamps
 *  Timestamps are automatically generated internally by the tracer hardware
 *  inside the radio core. A synchronization timestamp is sent over the tracer
 *  pin when a log statement is sent. The timestamp resolution is fixed to 0.5
 *  us with a max range of 32 ms.
 *
 *  @anchor ti_log_LogSinkTraceLPF3_Parameters The tracer supports a maximum of
 *  four 16bit parameters inside each log statement. If using two parameters or
 *  less, the parameters can be of 32bit.
 *  ============================================================================
 */

#ifndef ti_log_LogSinkTraceLPF3__include
#define ti_log_LogSinkTraceLPF3__include

/*
 * Helpers to set the configuration for the tracer
 */
#define LogSinkTraceLPF3_CONFIG_CHANNELS_CPU_ONLY LRFDTRC_CFG_CH1EN_NORM | LRFDTRC_CFG_CH2EN_OFF | LRFDTRC_CFG_CH3EN_OFF
#define LogSinkTraceLPF3_CONFIG_CHANNELS_RADIO_ONLY \
    LRFDTRC_CFG_CH1EN_OFF | LRFDTRC_CFG_CH2EN_TOPSM | LRFDTRC_CFG_CH3EN_TOPSM
#define LogSinkTraceLPF3_CONFIG_CHANNELS_CPU_RADIO \
    LRFDTRC_CFG_CH1EN_NORM | LRFDTRC_CFG_CH2EN_TOPSM | LRFDTRC_CFG_CH3EN_TOPSM

#define LogSinkTraceLPF3_CONFIG_TIMESTAMP_ENABLED  LRFDTRC_CFG_TSEN_ON
#define LogSinkTraceLPF3_CONFIG_TIMESTAMP_DISABLED LRFDTRC_CFG_TSEN_OFF

#define LogSinkTraceLPF3_CONFIG_PRESCALER_DIV1 LRFDTRC_CFG_PRESCAL_DIV1
#define LogSinkTraceLPF3_CONFIG_PRESCALER_DIV2 LRFDTRC_CFG_PRESCAL_DIV2
#define LogSinkTraceLPF3_CONFIG_PRESCALER_DIV3 LRFDTRC_CFG_PRESCAL_DIV3
#define LogSinkTraceLPF3_CONFIG_PRESCALER_DIV4 LRFDTRC_CFG_PRESCAL_DIV4

#include <stdint.h>
#include <ti/log/Log.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdtrc.h)

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 *  @brief  LogSinkTraceLPF3 global configuration
 *
 *  The LogSinkTraceLPF3_Config structure contains settings used to configure
 *  RFtracer.
 *
 *  The tracerConfig member needs a 3 element combination of the configuration
 *  defines above put together with an OR operation. A valid configuration would
 *  be:
 *
 *  tracerConfig = LogSinkTraceLPF3_CHANNELS_RADIO_ONLY |
 *  LogSinkTraceLPF3_TIMESTAMP_ENABLED | LogSinkTraceLPF3_PRESCALER_DIV3
 *  LRFDTRC_CFG_PRESCAL_DIV3
 *
 *  lrfdTracerPin, tracerPinMux, tracerPin are all settings needed for the
 *  internal muxing of the tracer pin.
 */

typedef struct
{
    uint32_t tracerConfig;  /*!< Configuration for tracer */
    uint32_t lrfdTracerPin; /*!< LRFD tracer pin for the LRF muxing */
    int32_t tracerPinMux;   /*!< Tracer PIN mux value */
    uint32_t tracerPin;     /*!< DIO pin for the tracer */
} LogSinkTraceLPF3_Config;

extern const LogSinkTraceLPF3_Config LogSinkTraceLPF3_config;
/*!
 *  @brief      Array with the configuration of each sink.
 */

/*!
 *  @cond NODOC
 *  @brief Create a packet from a #Log_printf() call and send it out over RF
 *  Tracer.
 *
 *  Function to create a packet from a #Log_printf() call and send it out over
 *  RF Tracer.
 *
 *  This is a singleton implementation. It assumes that there is only one
 *  #LogSinkTraceLPF3 instance in the application.
 *  This allows the compiler in an LTO-enabled application to avoid generating
 *  instructions that load the @c handle since it is not needed.
 *
 *  @note Applications must not call this function directly. This is a helper
 *  function to implement #Log_printf()
 *
 *  @param[in]  handle     Handle to log module
 *
 *  @param[in]  level      Level of this log statement to compare against
 *                         enabled module level
 *
 *  @param[in]  headerPtr  Pointer to metadata pointer
 *
 *  @param[in]  numArgs    Number of arguments
 *
 *  @param[in]  ...        Variable number of arguments
 *
 *  @endcond
 */
extern void LogSinkTraceLPF3_printfSingleton(const Log_Module *handle,
                                             Log_Level level,
                                             uint32_t headerPtr,
                                             uint32_t numArgs,
                                             ...);

extern void LogSinkTraceLPF3_printfSingleton0(const Log_Module *handle, Log_Level level, uint32_t headerPtr, ...);

extern void LogSinkTraceLPF3_printfSingleton1(const Log_Module *handle, Log_Level level, uint32_t headerPtr, ...);

extern void LogSinkTraceLPF3_printfSingleton2(const Log_Module *handle, Log_Level level, uint32_t headerPtr, ...);

extern void LogSinkTraceLPF3_printfSingleton3(const Log_Module *handle, Log_Level level, uint32_t headerPtr, ...);

extern void LogSinkTraceLPF3_init(void);
/*!
 *  @cond NODOC
 *  @brief Create a packet from a #Log_buf() call and send it out over RF
 *  Tracer.
 *
 *  This function has not been implemented since it is not supported by the
 *  hardware.
 *
 *  Function to create a packet from a #Log_buf() call and send it out over
 *  RF Tracer.
 *
 *  This is a singleton implementation. It assumes that there is only one
 *  #LogSinkTraceLPF3 instance in the application.
 *  This allows the compiler in an LTO-enabled application to avoid generating
 *  instructions that load the @c handle since it is not needed.
 *
 *  @note Applications must not call this function directly. This is a helper
 *  function to implement #Log_buf
 *
 *  @param[in]  handle     Handle to log module
 *
 *  @param[in]  level      Level of this log statement to compare against
 *                         enabled module level
 *
 *  @param[in]  headerPtr  Pointer to metadata pointer
 *
 *  @param[in]  data       Pointer to data to send out
 *
 *  @param[in]  size       Size of @c data in bytes
 *
 *  @endcond
 */
extern void LogSinkTraceLPF3_bufSingleton(const Log_Module *handle,
                                          Log_Level level,
                                          uint32_t headerPtr,
                                          uint8_t *data,
                                          size_t size);

/*
 * Helpers to define/use instance. Tracer is a singleton so no arguments are taken.
 */

#define Log_MODULE_INIT_SINK_TRACELPF3(name, _levels, printfDelegate, bufDelegatee, _dynamicLevelsPtr)                \
    {                                                                                                                 \
        .sinkConfig = NULL, .printf = LogSinkTraceLPF3_printfSingleton, .printf0 = LogSinkTraceLPF3_printfSingleton0, \
        .printf1 = LogSinkTraceLPF3_printfSingleton1, .printf2 = LogSinkTraceLPF3_printfSingleton2,                   \
        .printf3 = LogSinkTraceLPF3_printfSingleton3, .buf = LogSinkTraceLPF3_bufSingleton, .levels = _levels,        \
        .dynamicLevelsPtr = _dynamicLevelsPtr,                                                                        \
    }

#if defined(__cplusplus)
}
#endif

#endif /* ti_log_LogSinkTraceLPF3__include */
