add_subdirectory(source/ti/devices)

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
endif()
