zephyr_library()

zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})

zephyr_library_sources(
  plat/bus_hif.c
  plat/init_device.c
  plat/time_util.c
  plat/otfde_driver.c
  plat/wlan_irq_adapt.c
  plat/hif.c
)

if(CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_MBEDTLS)
  zephyr_library_compile_definitions(
    TI_WIFI_CRYPTO_BACKEND_ZEPHYR_MBEDTLS
  )
  zephyr_library_sources(
    ../platform/zephyr/crypto_mbedtls_zephyr.c
  )
  zephyr_include_directories(../platform/zephyr)
  zephyr_library_link_libraries(mbedTLS)
elseif(CONFIG_WIFI_TI_CC35XX_USE_TI_MBEDTLS)
  zephyr_library_sources(
    platform/ti/crypto_mbedtls_ti.c
    platform/ti/tls_mbedtls_ti.c
    plat/tls_iperf_mbedtls.c
  )
  ti_mbedtls_configure_target(${ZEPHYR_CURRENT_LIBRARY})
else()
  message(FATAL_ERROR "Select a CC35XX Wi-Fi mbedTLS platform")
endif()

zephyr_include_directories(
  inc_common
  plat
)
