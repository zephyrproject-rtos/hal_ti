zephyr_include_directories(
  .
  driverlib
  )

zephyr_library()

zephyr_library_sources(
  # driverlib/aes_gcc.s
  # driverlib/udma.c
  # driverlib/lrfd.c
  driverlib/setup.c
  # driverlib/uart.c
  # driverlib/spi.c
  # driverlib/vims.c
  # driverlib/adc.c
  driverlib/cpu.c
  # driverlib/i2c.c
  )
