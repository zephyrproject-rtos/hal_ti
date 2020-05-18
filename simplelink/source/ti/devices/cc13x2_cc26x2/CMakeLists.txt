# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
  .
  )

zephyr_library()
zephyr_library_compile_definitions(${COMPILER})
zephyr_library_sources(
  # Required for SystemTrimDevice which is not in ROM
  driverlib/setup.c
  driverlib/chipinfo.c
  driverlib/aux_sysif.c
  # Required for CPUdelay which is not in ROM
  driverlib/cpu.c
  # Required functions to support the TI Power module
  driverlib/sys_ctrl.c
  driverlib/osc.c
  driverlib/driverlib_release.c
  )

if(CONFIG_SOC_CC1352R)
  # Required for RFCDoorbellSendTo which is not in ROM
  zephyr_library_sources(driverlib/rfc.c)
  set_source_files_properties(driverlib/rfc.c
    PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
elseif(CONFIG_SOC_CC2652R)
  # Required for RFCDoorbellSendTo which is not in ROM
  zephyr_library_sources(driverlib/rfc.c)
  set_source_files_properties(driverlib/rfc.c
    PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
endif()
