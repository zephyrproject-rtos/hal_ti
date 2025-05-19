# Copyright (c) 2022-2024, Texas Instruments Incorporated
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

zephyr_include_directories(
  .
  )

zephyr_library()

zephyr_library_sources(
  driverlib/aes_gcc.s
  driverlib/udma.c
  driverlib/gpio.c
  driverlib/interrupt.c
  driverlib/lrfd.c
  driverlib/setup.c
  driverlib/uart.c
  driverlib/spi.c
  driverlib/adc.c
  driverlib/cpu.c
  driverlib/i2c.c
  )

# RF patches
if(CONFIG_SIMPLELINK_F3_RADIO_DRIVER)
  zephyr_library_sources(
    rf_patches/lrf_mce_binary_ble5_cc23x0r5.c
    rf_patches/lrf_mce_binary_ble_cs_cc23x0r5.c
    rf_patches/lrf_mce_binary_common_cc23x0r5.c
    rf_patches/lrf_mce_binary_genfsk_cc23x0r5.c
    rf_patches/lrf_mce_binary_ieee_cc23x0r5.c
    rf_patches/lrf_pbe_binary_ble5_cc23x0r5.c
    rf_patches/lrf_pbe_binary_ble_cs_cc23x0r5.c
    rf_patches/lrf_pbe_binary_common_cc23x0r5.c
    rf_patches/lrf_pbe_binary_generic_cc23x0r5.c
    rf_patches/lrf_pbe_binary_ieee_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ble5_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ble5_nopll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ble_cs_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ble_cs_nopll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_coherent_pll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_coherent_pll_nopll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_common_cc23x0r5.c
    rf_patches/lrf_rfe_binary_common_nopll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_genfsk_cc23x0r5.c
    rf_patches/lrf_rfe_binary_genfsk_nopll_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ieee_cc23x0r5.c
    rf_patches/lrf_rfe_binary_ieee_nopll_cc23x0r5.c
    )
endif()