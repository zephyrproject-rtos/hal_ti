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

# All targets in this file are for Cortex-M0P

if(CONFIG_HAS_CC23X0_SDK)

  add_subdirectory(source/ti/devices)
  add_subdirectory(source/ti/boards)
  add_subdirectory(source/ti/log)

  include(${CMAKE_CURRENT_LIST_DIR}/CMakeSources.cmake)

  if(CONFIG_SOC_CC2340R5)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  if(CONFIG_SOC_CC2340R53)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  if(CONFIG_SOC_CC2340R5_WCSP)
      zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  if(CONFIG_SOC_CC2340R5MODA)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  zephyr_include_directories(
    .
    source
    )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    ${SOURCES_DRIVERS_LPF3}
    ${SOURCES_DRIVERS_CC23X0}
    ${SOURCES_KERNEL}
    )
  zephyr_linker_sources(RAM_SECTIONS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ti/drivers/dma/dma.ld
  )

  # Radio Control Layer (RCL) driver
  if(CONFIG_RCL_DRIVER)
    zephyr_library_sources(
        ${SOURCES_RCL}
        ${SOURCES_RCL_LPF3}
      )
    # GCC/Clang/ArmClang workaround:
    # LRF.c and ble_cs.c contain inline ARM asm
    # that explicitly clobbers r7. When using -O0 compilation level, these
    # compilers use r7 as frame pointer, so it's unavailable for inline asm.
    # Omitting the frame pointer for these files avoids r7 conflicts. IAR is
    # intentionally excluded because it uses different flags and asm semantics.
    set_property(SOURCE
        source/ti/drivers/rcl/LRF.c
        source/ti/drivers/rcl/handlers/ble_cs.c
        PROPERTY COMPILE_OPTIONS
        "$<$<COMPILE_LANG_AND_ID:C,GNU,Clang,ARMClang>:-fomit-frame-pointer>"
      )
  endif()

  zephyr_compile_definitions(
    -DCONFIG_ZEPHYR
  )

endif()
