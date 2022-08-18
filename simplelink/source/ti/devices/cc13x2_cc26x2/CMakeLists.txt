# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
  .
  )

zephyr_library()

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
  # Required for newer HAL TI >= 4.40 (for PRCMPowerDomainsAllOn)
  driverlib/prcm.c
  )

# Required for IEEE 802.15.4 support
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX
  rf_patches/rf_patch_cpe_multi_protocol.c)
# Required for IEEE 802.15.4 support
# (until driver is changed to use multi-protocol rf patch)
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX
  rf_patches/rf_patch_cpe_ieee_802_15_4.c)
# Required for RFCDoorbellSendTo which is not in ROM
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX driverlib/rfc.c)

# Required for IEEE 802.15.4g support
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX_SUB_GHZ
  rf_patches/rf_patch_cpe_multi_protocol.c)
# Required for RFCDoorbellSendTo which is not in ROM
zephyr_library_sources_ifdef(CONFIG_IEEE802154_CC13XX_CC26XX_SUB_GHZ driverlib/rfc.c)

# Required for BLE support
zephyr_library_sources_ifdef(CONFIG_BLE_CC13XX_CC26XX
  rf_patches/rf_patch_cpe_multi_protocol.c)
# Required for RFCDoorbellSendTo which is not in ROM
zephyr_library_sources_ifdef(CONFIG_BLE_CC13XX_CC26XX driverlib/rfc.c)

# Required for on-chip flash support
zephyr_library_sources_ifdef(CONFIG_SOC_FLASH_CC13XX_CC26XX driverlib/flash.c)

# Required for AUX ADC support
zephyr_library_sources_ifdef(CONFIG_ADC_CC13XX_CC26XX driverlib/aux_adc.c)
