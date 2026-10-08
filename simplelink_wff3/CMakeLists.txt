set(TI_MBEDTLS_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/mbedtls")

function(ti_mbedtls_configure_target target)
  target_compile_options(${target} PRIVATE
    -UMBEDTLS_CONFIG_FILE
    -UTF_PSA_CRYPTO_CONFIG_FILE
    -DMBEDTLS_CONFIG_FILE="mbedtls_ti_config.h"
  )
  target_include_directories(${target} BEFORE PRIVATE
    "${TI_MBEDTLS_DIR}/ti/configs"
    "${TI_MBEDTLS_DIR}/include"
  )
endfunction()

add_subdirectory(source/ti/devices)
if(CONFIG_WIFI_TI_CC35XX)
  add_subdirectory(source/ti/drivers/net/wifi/wifi_host_driver)
  add_subdirectory(source/ti/drivers/net/wifi/wifi_platform/cc35xx)
  add_subdirectory(third_party/hostap)
  if(NOT CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_MBEDTLS)
    add_subdirectory(third_party/mbedtls)
  endif()
  add_subdirectory(source/ti/net/wifi_stack)
  add_subdirectory(source/ti/net/ble_interface)
endif()

if(CONFIG_HAS_CC35XX_SDK)
  if(CONFIG_SOC_SERIES_CC35XXE)
    zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})
    zephyr_compile_definitions(CC35XX)
    zephyr_compile_definitions(CONFIG_DYNAMIC_DPL_OBJECTS)
    if(CONFIG_WIFI_TI_CC35XX_TX_CTRL_BLK_NUM)
      zephyr_compile_definitions(CTRL_BLK_ENTRIES_NUM=${CONFIG_WIFI_TI_CC35XX_TX_CTRL_BLK_NUM})
    endif()
    zephyr_include_directories(
      .
      source
      source/ti/drivers
      source/ti/drivers/xmem/flash
      source/ti/drivers/cryptoutils/cryptokey
      third_party/hsmddk/include/Kit/Log/incl/
    )
    if(CONFIG_WIFI_TI_CC35XX)
      zephyr_include_directories(
        # shared between host driver and hostap
        source/ti/drivers/net/wifi/wifi_host_driver
        source/ti/drivers/net/wifi/wifi_host_driver/inc_common
        source/ti/drivers/net/wifi/wifi_host_driver/inc_adapt
        source/ti/drivers/net/wifi/wifi_host_driver/trnspt_layer
      )
    endif()
    if(CONFIG_CC35XXE_FWU)
      zephyr_include_directories(
        source/ti/utils/FWU
        source/ti/utils/FWU/headers
        source/ti/drivers/xmem
        source/ti/drivers/net/wifi/wifi_host_driver/inc_common
        source/ti/drivers/net/wifi/wifi_host_driver/inc_adapt
        source/ti/drivers/net/wifi/wifi_platform/cc35xx/inc_common
        source/ti/drivers/net/wifi/wifi_platform/cc35xx/plat
      )
    endif()

    zephyr_library()
    zephyr_library_compile_definitions(${COMPILER})
    zephyr_library_sources(
      kernel/zephyr/dpl/ClockP_zephyr.c
      kernel/zephyr/dpl/HwiP_zephyr.c
      kernel/zephyr/dpl/MessageQueueP_zephyr.c
      kernel/zephyr/dpl/SwiP_zephyr.c
      kernel/zephyr/dpl/SemaphoreP_zephyr.c
      kernel/zephyr/dpl/TaskP_zephyr.c
      kernel/zephyr/dpl/QueueP_zephyr.c
      kernel/zephyr/dpl/MutexP_zephyr.c

      source/ti/drivers/UART2.c
      source/ti/drivers/uart2/UART2WFF3.c
      source/ti/devices/cc35xx/driverlib/adc.c
      source/ti/devices/cc35xx/driverlib/dcache.c
      source/ti/devices/cc35xx/driverlib/interrupt.c
      source/ti/devices/cc35xx/driverlib/uart.c
      source/ti/devices/cc35xx/driverlib/spi.c
      source/ti/devices/cc35xx/driverlib/watchdog.c
      source/ti/drivers/GPIO.c
      source/ti/drivers/gpio/GPIOWFF3.c
      source/ti/drivers/dma/DMAWFF3.c
      source/ti/devices/cc35xx/driverlib/dma.c
      source/ti/drivers/power/PowerWFF3.c
      source/ti/drivers/xmem/flash/FlashWFF3.c
      source/ti/drivers/xmem/XMEMWFF3.c
      source/ti/devices/cc35xx/driverlib/xip.c
      source/ti/devices/cc35xx/driverlib/ospi.c
      source/ti/devices/cc35xx/driverlib/i2c.c
      source/ti/drivers/utils/RingBuf.c
      source/ti/drivers/utils/List.c
    )
    if(CONFIG_TI_CC35XX_HSM)
      # TI HSM sources are provided by the SDK and are not warning-clean with -Werror.
      zephyr_library_compile_options(-Wno-error)
      zephyr_library_include_directories(
        third_party/mbedtls/include
        third_party/mbedtls/ti/configs
      )
      zephyr_library_compile_definitions(ENABLE_KEY_STORAGE=1)
      if(NOT CONFIG_PSA_CRYPTO_DRIVER_CC35XX AND
         NOT CONFIG_MBEDTLS_PSA_CRYPTO_C)
        zephyr_library_compile_definitions(
          MBEDTLS_CONFIG_FILE="mbedtls_ti_config.h"
        )
      endif()

      zephyr_library_sources(
        source/ti/drivers/cryptoutils/hsm/HSMXXF3.c
        source/ti/drivers/cryptoutils/sharedresources/HSMResourceXXF3.c
        source/ti/drivers/cryptoutils/sharedresources/CommonResourceXXF3.c
        kernel/zephyr/dpl/ti_hsm_bounce_buffers.c
        third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.c
        third_party/hsmddk/include/Integration/Adapter_DriverInit/Driver/src/adapter_init.c
        third_party/hsmddk/include/Integration/Adapter_DriverInit/Driver/src/adapter_driver_init.c
        third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_init.c
        third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_device.c
        third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_physicaltoken.c
        third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_identity.c
        third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_mailbox.c
        third_party/hsmddk/include/Integration/Adapter_Generic/src/adapter_interrupts.c
        third_party/hsmddk/include/Integration/DriverFramework/src/device_generic.c
        third_party/hsmddk/include/Integration/DriverFramework/src/hwpal_device_mb.c
        third_party/hsmddk/include/Kit/EIP130/DomainHelper/src/eip130_domain_ecc_getcurve.c
        third_party/hsmddk/include/Kit/EIP130/MailboxControl/src/eip130.c
        third_party/hsmddk/include/Kit/EIP130/TokenHelper/src/eip130_token_common.c
        third_party/hsmddk/include/Kit/EIP201/src/eip201.c
        third_party/hsmddk/include/Kit/Log/src/log.c
        source/ti/drivers/TRNG.c
        source/ti/drivers/SHA3.c
        source/ti/drivers/trng/TRNGXXF3HSM.c
        source/ti/drivers/sha3/SHA3XXF3HSM.c
      )
      if(CONFIG_TI_CC35XX_HSM_ITS)
        zephyr_library_sources(
          kernel/zephyr/dpl/ti_its_init.c
          kernel/zephyr/dpl/ti_psa_key_config.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/Driver_Flash.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_flash.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_flash_fs.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_flash_fs_dblock.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_flash_fs_mblock.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_flash_nor.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/its_utils.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/tfm_hal_its.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/tfm_internal_trusted_storage.c
          third_party/hsmddk/include/Integration/Adapter_ITS/src/tfm_its_local_api.c
        )
      endif()
      if(CONFIG_TI_CC35XX_HSM_PSA_ADAPTER)
        zephyr_library_include_directories(
          third_party/mbedtls/include
          third_party/mbedtls/ti/configs
          third_party/hsmddk/include/Integration/Adapter_PSA/incl
          kernel/zephyr/dpl
        )
        zephyr_library_compile_options(
          -UMBEDTLS_CONFIG_FILE
          -UTF_PSA_CRYPTO_CONFIG_FILE
          -DMBEDTLS_CONFIG_FILE="mbedtls_ti_hsm_zephyr_config.h"
        )
        zephyr_library_compile_definitions(ENABLE_KEY_STORAGE=1)
        zephyr_library_sources(
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_asset.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_asym_parse.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_asym_write.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_exchangetoken.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_init.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_internal.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_key_derivation.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_key_management.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_preprovisioned_keys.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/adapter_psa_system.c
          third_party/hsmddk/include/Integration/Adapter_PSA/src/psa_key_store.c
          third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/src/platform.c
          third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/src/psa_crypto_client.c
          third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/src/psa_crypto_storage.c
          third_party/hsmddk/include/Integration/Asn1Der/src/asn1der_parse.c
          third_party/hsmddk/include/Integration/Asn1Der/src/asn1der_write.c
          source/ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.c
          source/ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA.c
          source/ti/drivers/cryptoutils/cryptokey/CryptoKeyKeyStore_PSA_helpers.c
        )
      endif()
    endif()
    if(CONFIG_CRYPTO_TI_CC35XX)
      zephyr_library_sources(
        source/ti/drivers/aesecb/AESECBXXF3.c
        source/ti/drivers/aesccm/AESCCMXXF3.c
        source/ti/drivers/aesctr/AESCTRXXF3.c
      )
    endif()
    if(CONFIG_PSA_CRYPTO_DRIVER_CC35XX)
      zephyr_library_sources(
        source/ti/drivers/AESGCM.c
        source/ti/drivers/ECDH.c
        source/ti/drivers/ECDSA.c
        source/ti/drivers/SHA2.c
        source/ti/drivers/SHA3.c
        source/ti/drivers/cryptoutils/cryptokey/CryptoKeyPlaintext.c
        source/ti/drivers/cryptoutils/hsm/HSMXXF3Utility.c
        source/ti/drivers/aesccm/AESCCMXXF3.c
        source/ti/drivers/aesctr/AESCTRXXF3.c
        source/ti/drivers/aesecb/AESECBXXF3.c
        source/ti/drivers/aesgcm/AESGCMXXF3HSM.c
        source/ti/drivers/ecdh/ECDHXXF3HSM.c
        source/ti/drivers/ecdsa/ECDSAXXF3HSM.c
        source/ti/drivers/sha2/SHA2XXF3HSM.c
        source/ti/drivers/sha3/SHA3XXF3HSM.c
      )
    endif()
    if(CONFIG_CC35XXE_FWU)
      zephyr_library_sources(
        source/ti/utils/FWU/psa_fwu.c
      )
      if(NOT CONFIG_WIFI_TI_CC35XX)
        zephyr_library_sources(
          source/ti/drivers/net/wifi/wifi_platform/cc35xx/plat/otfde_driver.c
        )
      endif()
    endif()
    if(CONFIG_TI_CC35XX_HSM_ITS OR CONFIG_WIFI_TI_CC35XX OR CONFIG_CC35XXE_FWU)
      set(ti_flash_map_config_source kernel/zephyr/dpl/ti_flash_map_config.c)
      set(ti_flash_map_config_target)

      if(CONFIG_CC35XXE_GENERATE_FLASH_MAP_CONFIG)
        get_property(ti_flash_map_config_source GLOBAL PROPERTY
                     CC35XXE_FLASH_MAP_CONFIG_SOURCE)
        if(NOT ti_flash_map_config_source)
          set(ti_flash_map_config_source "${ZEPHYR_BINARY_DIR}/ti_flash_map_config.c")
        endif()
        get_property(ti_flash_map_config_target GLOBAL PROPERTY
                     CC35XXE_FLASH_MAP_CONFIG_TARGET)
        set_source_files_properties(${ti_flash_map_config_source}
                                    PROPERTIES GENERATED TRUE)
      endif()

      zephyr_include_directories(
        kernel/zephyr/dpl
      )
      zephyr_library_sources(
        ${ti_flash_map_config_source}
      )
      if(ti_flash_map_config_target)
        add_dependencies(${ZEPHYR_CURRENT_LIBRARY} ${ti_flash_map_config_target})
      endif()
    endif()
    if(CONFIG_WIFI_TI_CC35XX OR CONFIG_CC35XXE_FWU)
      zephyr_library_sources(
        kernel/zephyr/dpl/osi_dpl.c
      )
      if(CONFIG_WIFI_TI_CC35XX)
        zephyr_library_sources(
          kernel/zephyr/dpl/osi_filesystem.c
          kernel/zephyr/dpl/osi_term.c
        )
      endif()
    endif()
  endif()
endif()

if(CONFIG_WIFI_TI_CC33XX)
  add_subdirectory(source/ti/drivers/net/wifi/wifi_host_driver)
  add_subdirectory(source/ti/drivers/net/wifi/wifi_platform/cc33xx)
  add_subdirectory(third_party/hostap)
  add_subdirectory(third_party/mbedTLS)
  add_subdirectory(source/ti/net/wifi_stack)
  add_subdirectory(source/ti/net/ble_interface)
  zephyr_compile_definitions(DeviceFamily_CC33XX ${COMPILER})
  zephyr_compile_definitions(CONFIG_DYNAMIC_DPL_OBJECTS)
  zephyr_compile_definitions(CC33XX)
  if(CONFIG_WIFI_TI_CC3XXX_TX_CTRL_BLK_NUM)
    zephyr_compile_definitions(CTRL_BLK_ENTRIES_NUM=${CONFIG_WIFI_TI_CC3XXX_TX_CTRL_BLK_NUM})
  endif()
  zephyr_include_directories(
    .
    firmware
    source
    source/ti/drivers
    source/ti/drivers/net/wifi/wifi_host_driver
    source/ti/drivers/net/wifi/wifi_host_driver/inc_common
    source/ti/drivers/net/wifi/wifi_host_driver/inc_adapt
    source/ti/drivers/net/wifi/wifi_host_driver/trnspt_layer
  )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    kernel/zephyr/dpl/ClockP_zephyr.c
    kernel/zephyr/dpl/HwiP_zephyr.c
    kernel/zephyr/dpl/MessageQueueP_zephyr.c
    kernel/zephyr/dpl/SwiP_zephyr.c
    kernel/zephyr/dpl/SemaphoreP_zephyr.c
    kernel/zephyr/dpl/TaskP_zephyr.c
    kernel/zephyr/dpl/QueueP_zephyr.c
    kernel/zephyr/dpl/osi_dpl.c
    kernel/zephyr/dpl/osi_filesystem.c
    kernel/zephyr/dpl/osi_term.c
  )

endif()
