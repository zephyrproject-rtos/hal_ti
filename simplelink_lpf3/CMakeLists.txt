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
    # Utils
    source/ti/drivers/utils/List.c

    # Drivers
    source/ti/drivers/Temperature.c
    source/ti/drivers/power/PowerCC23X0.c
    source/ti/drivers/temperature/TemperatureLPF3.c
    source/ti/drivers/batterymonitor/BatMonSupportLPF3.c
    source/ti/drivers/batterymonitor/BatteryMonitorLPF3.c

    # DPL
    kernel/zephyr/dpl/ClockP_zephyr.c
    kernel/zephyr/dpl/HwiP_zephyr.c
    )
endif()
