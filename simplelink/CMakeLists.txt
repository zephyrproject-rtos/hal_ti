add_subdirectory(source/ti/devices)

if(CONFIG_SIMPLELINK_HOST_DRIVER)
  zephyr_include_directories(
    .
    source
    kernel/zephyr/dpl
    source/ti/drivers/net/wifi/porting
    )
  zephyr_compile_definitions(
    SL_SUPPORT_IPV6
    SL_PLATFORM_MULTI_THREADED
    )
endif()

if(CONFIG_HAS_CC3220SDK)
  if(CONFIG_SIMPLELINK_HOST_DRIVER)
    zephyr_library()
    zephyr_library_compile_definitions(${COMPILER})
    zephyr_library_sources(
      source/ti/drivers/SPI.c
      source/ti/drivers/spi/SPICC32XXDMA.c
      source/ti/drivers/dma/UDMACC32XX.c
      source/ti/drivers/power/PowerCC32XX.c
      source/ti/drivers/utils/List.c
      source/ti/drivers/net/wifi/source/driver.c
      source/ti/drivers/net/wifi/source/device.c
      source/ti/drivers/net/wifi/source/flowcont.c
      source/ti/drivers/net/wifi/source/fs.c
      source/ti/drivers/net/wifi/source/netapp.c
      source/ti/drivers/net/wifi/source/netcfg.c
      source/ti/drivers/net/wifi/source/netutil.c
      source/ti/drivers/net/wifi/source/nonos.c
      source/ti/drivers/net/wifi/source/spawn.c
      source/ti/drivers/net/wifi/source/wlan.c
      source/ti/drivers/net/wifi/porting/CC3220SF_LAUNCHXL.c
      source/ti/drivers/net/wifi/porting/cc_pal.c
      source/ti/drivers/net/wifi/eventreg.c
      source/ti/drivers/net/wifi/source/sl_socket.c
      source/ti/drivers/net/wifi/slnetif/slnetifwifi.c
      source/ti/net/slnetif.c
      source/ti/net/slnetsock.c
      source/ti/net/slnetutils.c

      source/ti/devices/cc32xx/driverlib/timer.c
      source/ti/devices/cc32xx/driverlib/udma.c

      kernel/zephyr/dpl/dpl.c
      kernel/zephyr/dpl/MutexP_zephyr.c
      kernel/zephyr/dpl/SemaphoreP_zephyr.c
      kernel/zephyr/dpl/ClockP_zephyr.c
      kernel/zephyr/dpl/HwiP_zephyr.c
      )

    set_source_files_properties(source/ti/drivers/net/wifi/source/driver.c
      PROPERTIES COMPILE_DEFINITIONS "__LINUX_ERRNO_EXTENSIONS__;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/net/wifi/source/driver.c
      PROPERTIES COMPILE_FLAGS -Wno-incompatible-pointer-types) # driver.c warns on incompatible-pointer-types
  endif()

elseif(CONFIG_HAS_CC13X2_CC26X2_SDK)
  zephyr_include_directories(
    .
    source
    )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    source/ti/drivers/power/PowerCC26X2.c
    source/ti/drivers/power/PowerCC26X2_calibrateRCOSC.c
    source/ti/drivers/utils/List.c
    source/ti/drivers/rf/RFCC26X2_multiMode.c
    source/ti/drivers/temperature/TemperatureCC26X2.c

    kernel/zephyr/dpl/config.c
    kernel/zephyr/dpl/ClockP_zephyr.c
    kernel/zephyr/dpl/HwiP_zephyr.c
    kernel/zephyr/dpl/SwiP_zephyr.c
    kernel/zephyr/dpl/SemaphoreP_zephyr.c
    kernel/zephyr/dpl/QueueP_zephyr.c
    )

  if(CONFIG_SOC_CC1352R)
    set_source_files_properties(source/ti/drivers/power/PowerCC26X2.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/power/PowerCC26X2_calibrateRCOSC.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/rf/RFCC26X2_multiMode.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/temperature/TemperatureCC26X2.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC13X2;${COMPILER}" )
  elseif(CONFIG_SOC_CC2652R)
    set_source_files_properties(source/ti/drivers/power/PowerCC26X2.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/power/PowerCC26X2_calibrateRCOSC.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/rf/RFCC26X2_multiMode.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
    set_source_files_properties(source/ti/drivers/temperature/TemperatureCC26X2.c
      PROPERTIES COMPILE_DEFINITIONS "DeviceFamily_CC26X2;${COMPILER}" )
  endif()

elseif(CONFIG_HAS_MSP432P4XXSDK)
  zephyr_include_directories(
    source
    )
endif()
