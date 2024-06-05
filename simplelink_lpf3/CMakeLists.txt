# Copyright (c) 2024, Texas Instruments Incorporated
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

add_subdirectory(source/ti/devices)
add_subdirectory(source/ti/boards)

if(CONFIG_HAS_CC23X0_SDK)

  if(CONFIG_SOC_CC2340R5)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  zephyr_include_directories(
    .
    source
    )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    # Default Simplelink configurations
    source/ti/drivers/config_defaults.c

    # Utils
    source/ti/drivers/utils/List.c
    source/ti/drivers/utils/Random.c

    # Drivers
    source/ti/drivers/AESCCM.c
    source/ti/drivers/AESCMAC.c
    source/ti/drivers/AESCTR.c
    source/ti/drivers/AESCTRDRBG.c
    source/ti/drivers/AESECB.c
    source/ti/drivers/ECDH.c
    source/ti/drivers/RNG.c
    source/ti/drivers/aesccm/AESCCMLPF3.c
    source/ti/drivers/aescmac/AESCMACLPF3.c
    source/ti/drivers/aesctr/AESCTRLPF3.c
    source/ti/drivers/aesctrdrbg/AESCTRDRBGXX.c
    source/ti/drivers/aesecb/AESECBLPF3.c
    source/ti/drivers/cryptoutils/aes/AESCommonLPF3.c
    source/ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.c
    source/ti/drivers/cryptoutils/sharedresources/CryptoResourceLPF3.c
    source/ti/drivers/cryptoutils/utils/CryptoUtils.c
    source/ti/drivers/dma/UDMALPF3.c
    source/ti/drivers/rng/RNGLPF3RF.c

    source/ti/drivers/Temperature.c
    source/ti/drivers/power/PowerCC23X0.c
    source/ti/drivers/temperature/TemperatureLPF3.c
    source/ti/drivers/batterymonitor/BatMonSupportLPF3.c
    source/ti/drivers/batterymonitor/BatteryMonitorLPF3.c

    # DPL
    kernel/zephyr/dpl/MutexP_zephyr.c
    kernel/zephyr/dpl/SemaphoreP_zephyr.c
    kernel/zephyr/dpl/ClockP_zephyr.c
    kernel/zephyr/dpl/HwiP_zephyr.c
    kernel/zephyr/dpl/SwiP_zephyr.c
    kernel/zephyr/dpl/TaskP_zephyr.c
    kernel/zephyr/dpl/MessageQueueP_zephyr.c
    )
  if(CONFIG_EVENTS)
    zephyr_library_sources(kernel/zephyr/dpl/EventP_zephyr.c)
  endif()
  zephyr_linker_sources(RAM_SECTIONS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ti/drivers/dma/dma.ld
  )

  # Radio Control Layer (RCL) driver
  if(CONFIG_SIMPLELINK_F3_RADIO_DRIVER)
    zephyr_library_sources(
      source/ti/drivers/rcl/LRF.c
      source/ti/drivers/rcl/LRFCC23X0.c
      source/ti/drivers/rcl/RCL_Buffer.c
      source/ti/drivers/rcl/RCL_Debug.c
      source/ti/drivers/rcl/RCL_Profiling.c
      source/ti/drivers/rcl/RCL_Scheduler.c
      source/ti/drivers/rcl/RCL_Tracer.c
      source/ti/drivers/rcl/RCL.c
      source/ti/drivers/rcl/handlers/adc_noise.c
      source/ti/drivers/rcl/handlers/ble_cs.c
      source/ti/drivers/rcl/handlers/ble5.c
      source/ti/drivers/rcl/handlers/generic.c
      source/ti/drivers/rcl/hal/cc23x0/hal_cc23x0.c
      source/ti/drivers/rcl/wrappers/RCL_AdcNoise.c
      )
  endif()
endif()
