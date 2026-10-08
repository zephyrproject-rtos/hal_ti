# Copyright (c) 2022-2025, Texas Instruments Incorporated
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
cmake_minimum_required(VERSION ${TI_MIN_CMAKE_VERSION})

include(${CMAKE_CURRENT_LIST_DIR}/CMakeSources_common.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/CMakeSources_cc27xx.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/CMakeSources_cc35xx.cmake)

# Regular expressions used to split SUPPORTED_PLATFORMS into a per-family list.
# Lists are stringified on the form "cc13x1;cc35xx;...", so the resulting list
# should include everything until (but not including) the next semicolon (;),
# or when end of string ($) is reached.
set(LPF3_REGEX "cc(23|27)[^;$]*")
set(WFF3_REGEX "cc35[^;$]*")

# For each item in SUPPORTED_PLATFORMS, add it to a family-specific list
string(REGEX MATCHALL "${LPF3_REGEX}" LPF3_PLATFORMS "${SUPPORTED_PLATFORMS}")
string(REGEX MATCHALL "${WFF3_REGEX}" WFF3_PLATFORMS "${SUPPORTED_PLATFORMS}")

if(LPF3_PLATFORMS)
    ti_init_package(NAMESPACE ThirdPartyHSMDDKLib
        PACKAGE_NAME
            LPF3
            DEPENDS_ON
            DriversLPF3
    )
    foreach(TI_PLATFORM ${LPF3_PLATFORMS})
        if(${TI_PLATFORM} MATCHES "cc27xxx")
            if(${TI_PLATFORM} STREQUAL "cc27xxx10")
                ti_add_package_dependency(DriverlibCC27XXX10)
            elseif(${TI_PLATFORM} STREQUAL "cc27xxx20")
                ti_add_package_dependency(DriverlibCC27XXX20)
            endif()

            ti_add_package_dependency(DriversLPF3)

            ti_add_library(
                hsmddk_${TI_PLATFORM}
                OUTPUT_NAME hsmddk_${TI_PLATFORM}
                SOURCES ${SOURCES_CC27XX}
                ARCH m33f
                ADD_SDK_INCLUDE_PATH source
                LINK_PUBLIC Drivers::drivers_${TI_PLATFORM} CMakeCommon::${TI_TOOLCHAIN_NAME}_${ARCH_${TI_PLATFORM}}
                Driverlib::${TI_PLATFORM}
            )

            ti_add_library(
                hsmddk_${TI_PLATFORM}_its
                OUTPUT_NAME hsmddk_${TI_PLATFORM}_its
                SOURCES ${SOURCES_ITS_CC27XX}
                ARCH m33f
                ADD_SDK_INCLUDE_PATH source
                LINK_PUBLIC Drivers::drivers_${TI_PLATFORM} CMakeCommon::${TI_TOOLCHAIN_NAME}_${ARCH_${TI_PLATFORM}}
                Driverlib::${TI_PLATFORM}
            )

            if (${TI_TOOLCHAIN_NAME} MATCHES "ticlang|gcc")
                target_compile_options(hsmddk_${TI_PLATFORM}_its PRIVATE -mcmse)
            elseif (${TI_TOOLCHAIN_NAME} MATCHES "iar")
                target_compile_options(hsmddk_${TI_PLATFORM}_its PRIVATE --cmse)
            endif()

        endif()
    endforeach()

    ti_export_package()
endif() # if(LPF3_PLATFORMS)

if(WFF3_PLATFORMS)
    ti_init_package(NAMESPACE ThirdPartyHSMDDKLib
        PACKAGE_NAME
            WFF3
            DEPENDS_ON
            DriversWFF3
    )
    foreach(TI_PLATFORM ${WFF3_PLATFORMS})
        if(${TI_PLATFORM} MATCHES "cc35")
            ti_add_package_dependency(DriverlibCC35XX)
            ti_add_package_dependency(DriversWFF3)

            ti_add_library(
                hsmddk_${TI_PLATFORM}
                OUTPUT_NAME hsmddk_${TI_PLATFORM}
                SOURCES ${SOURCES_CC35XX}
                ARCH m33f
                ADD_SDK_INCLUDE_PATH source
                LINK_PUBLIC Drivers::drivers_${TI_PLATFORM} CMakeCommon::${TI_TOOLCHAIN_NAME}_${ARCH_${TI_PLATFORM}}
                Driverlib::${TI_PLATFORM}
            )

            ti_add_library(
                hsmddk_${TI_PLATFORM}_its
                OUTPUT_NAME hsmddk_${TI_PLATFORM}_its
                SOURCES ${SOURCES_ITS_CC35XX}
                ARCH m33f
                ADD_SDK_INCLUDE_PATH source
                LINK_PUBLIC Drivers::drivers_${TI_PLATFORM} CMakeCommon::${TI_TOOLCHAIN_NAME}_${ARCH_${TI_PLATFORM}}
                Driverlib::${TI_PLATFORM}
            )

        endif()
    endforeach()

    ti_export_package()
endif() # if(WFF3_PLATFORMS)