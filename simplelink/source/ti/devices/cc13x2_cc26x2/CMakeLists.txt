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

# Required for IEEE 802.15.4 support
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX
	rf_patches/rf_patch_cpe_ieee_802_15_4.c)
# Required for RFCDoorbellSendTo which is not in ROM
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX driverlib/rfc.c)

# Required for BLE support
zephyr_library_sources_ifdef(CONFIG_BLE_CC13XX_CC26XX
  rf_patches/rf_patch_cpe_bt5.c)
# Required for RFCDoorbellSendTo which is not in ROM
zephyr_library_sources_ifdef(CONFIG_BLE_CC13XX_CC26XX driverlib/rfc.c)

if(CONFIG_SOC_CC1352R)
  # Required for RFCDoorbellSendTo which is not in ROM
  set_source_files_properties(driverlib/rfc.c
    PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
elseif(CONFIG_SOC_CC2652R)
  # Required for RFCDoorbellSendTo which is not in ROM
  set_source_files_properties(driverlib/rfc.c
    PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
endif()
