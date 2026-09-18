# Copyright (c) 2024-2026, Texas Instruments Incorporated
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

if(CONFIG_TI_SIMPLELINK_CONFIG_DIR)
    cmake_path(ABSOLUTE_PATH CONFIG_TI_SIMPLELINK_CONFIG_DIR
        BASE_DIRECTORY ${APPLICATION_SOURCE_DIR}
        OUTPUT_VARIABLE TI_SIMPLELINK_CONFIG_DIR
    )
else()
    set(TI_SIMPLELINK_CONFIG_DIR ${CMAKE_CURRENT_LIST_DIR}/generated/${CONFIG_BOARD})
endif()

if(NOT EXISTS ${TI_SIMPLELINK_CONFIG_DIR}/ti_drivers_config.c)
    message(FATAL_ERROR
        "No SimpleLink configuration found for board '${CONFIG_BOARD}' in "
        "${TI_SIMPLELINK_CONFIG_DIR}. Set CONFIG_TI_SIMPLELINK_CONFIG_DIR to a "
        "directory containing the SysConfig generated files."
    )
endif()

if(CONFIG_RCL_DRIVER)

    zephyr_library_sources_ifdef(CONFIG_RCL_RF_SETTING_PREGEN ${TI_SIMPLELINK_CONFIG_DIR}/ti_radio_config.c)

endif()

zephyr_include_directories(
    ${TI_SIMPLELINK_CONFIG_DIR}
)

zephyr_library_sources(
    ${TI_SIMPLELINK_CONFIG_DIR}/ti_drivers_config.c
)

zephyr_linker_sources(RAM_SECTIONS ${TI_SIMPLELINK_CONFIG_DIR}/ti_utils_build_linker.cmd.genmap)
