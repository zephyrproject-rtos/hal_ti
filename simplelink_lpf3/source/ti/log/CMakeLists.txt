# Copyright (c) 2026, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

if(CONFIG_SIMPLELINK_LPF3_TRACE)

    zephyr_library_sources(LogSinkTraceLPF3.c)

    # Pre-generated log configuration which defines and declares TI log modules
    # Currently enables RCL (Radio Control Layer) logging only
    # To enable logging for other TI modules:
    #   1. Add Log_MODULE_DEFINE() in zephyr/ti_log_config.c to define the module
    #   2. Add Log_MODULE_USE() in zephyr/ti_log_config.h to declare the module
    #   3. Configure log levels and sinks in the module definition
    zephyr_library_sources_ifdef(CONFIG_SIMPLELINK_LPF3_TRACE_CONFIG_PREGEN zephyr/ti_log_config.c)
    zephyr_include_directories_ifdef(CONFIG_SIMPLELINK_LPF3_TRACE_CONFIG_PREGEN zephyr)

    zephyr_linker_sources(SECTIONS ${CMAKE_CURRENT_SOURCE_DIR}/zephyr/log.ld)

    zephyr_include_directories(
        .
    )

endif()
