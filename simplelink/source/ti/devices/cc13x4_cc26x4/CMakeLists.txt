  zephyr_include_directories(
      .
    )

  zephyr_library()

  zephyr_library_sources(
    driverlib/setup.c
    driverlib/chipinfo.c
    driverlib/aux_sysif.c
    driverlib/cpu.c
    driverlib/sys_ctrl.c
    driverlib/osc.c
    driverlib/prcm.c
    driverlib/ddi.c
    driverlib/ioc.c
    driverlib/interrupt.c
    driverlib/setup_rom.c
    driverlib/uart.c
    driverlib/udma.c
    driverlib/aux_adc.c
    driverlib/spi.c
    driverlib/aon_batmon.c
    driverlib/driverlib_release.c
    driverlib/aon_rtc.c
    driverlib/aon_event.c
  )
