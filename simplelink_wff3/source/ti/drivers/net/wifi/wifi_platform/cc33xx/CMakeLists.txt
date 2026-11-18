zephyr_library()

zephyr_compile_definitions(DeviceFamily_CC33XX ${COMPILER})

zephyr_library_sources(
  plat/bus_spi.c
  plat/init_device.c
  plat/io.c
  plat/tls_mbedtls.c
  plat/crypto_mbedtls.c
)

zephyr_include_directories(
  inc_adapt
  plat
)

