add_subdirectory(source/ti/devices)

if(CONFIG_HAS_MSPM0_SDK)
  zephyr_include_directories(
    .
    source
    source/ti
    source/ti/driverlib
    source/ti/driverlib/m0p
    source/ti/driverlib/m0p/sysctl
    )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    source/ti/driverlib/dl_uart.c
    source/ti/driverlib/dl_common.c
    source/ti/driverlib/dl_i2c.c
    source/ti/driverlib/dl_adc12.c
    source/ti/driverlib/dl_vref.c
    source/ti/driverlib/dl_mcan.c
    source/ti/driverlib/m0p/sysctl/dl_sysctl_mspm0g1x0x_g3x0x.c
    source/ti/driverlib/m0p/sysctl/dl_sysctl_mspm0l122x_l222x.c
    )
endif()
