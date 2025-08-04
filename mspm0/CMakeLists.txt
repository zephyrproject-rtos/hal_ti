add_subdirectory(source/ti/devices/msp)

if(CONFIG_HAS_MSPM0_SDK)
  zephyr_include_directories(
	.
	source
	source/ti
	source/ti/driverlib
	source/ti/driverlib/m0p
	source/ti/driverlib/m0p/sysctl
	)

  file(GLOB sysctl source/ti/driverlib/m0p/sysctl/*.c)

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(${sysctl})
  zephyr_library_sources(source/ti/driverlib/dl_common.c)
  zephyr_library_sources(source/ti/driverlib/m0p/dl_factoryregion.c)

  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_ADC source/ti/driverlib/dl_adc12.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_AES source/ti/driverlib/dl_aes.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_AESADV source/ti/driverlib/dl_aesadv.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_COMP source/ti/driverlib/dl_comp.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_CRC source/ti/driverlib/dl_crc.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_CRCP source/ti/driverlib/dl_crcp.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_DAC12 source/ti/driverlib/dl_dac12.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_DMA source/ti/driverlib/dl_dma.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_FLASHCTL source/ti/driverlib/dl_flashctl.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_GPAMP source/ti/driverlib/dl_gpamp.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_GPIO source/ti/driverlib/dl_gpio.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_I2C source/ti/driverlib/dl_i2c.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_IWDT source/ti/driverlib/dl_iwdt.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_KEYSTORECTL source/ti/driverlib/dl_keystorectl.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_LCD source/ti/driverlib/dl_lcd.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_LFSS source/ti/driverlib/dl_lfss.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_MATHACL source/ti/driverlib/dl_mathacl.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_MCAN source/ti/driverlib/dl_mcan.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_OPA source/ti/driverlib/dl_opa.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_RTC source/ti/driverlib/dl_rtc_a.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_RTC source/ti/driverlib/dl_rtc_b.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_RTC_COMMON source/ti/driverlib/dl_rtc_common.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_RTC source/ti/driverlib/dl_rtc.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_SCRATCHPAD source/ti/driverlib/dl_scratchpad.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_SPI source/ti/driverlib/dl_spi.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_TAMPERIO source/ti/driverlib/dl_tamperio.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_TIMER source/ti/driverlib/dl_timer.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_TIMER source/ti/driverlib/dl_timera.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_TIMER source/ti/driverlib/dl_timerg.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_TRNG source/ti/driverlib/dl_trng.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_UART source/ti/driverlib/dl_uart.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_VREF source/ti/driverlib/dl_vref.c)
  zephyr_library_sources_ifdef(CONFIG_USE_MSPM0_DL_WWDT source/ti/driverlib/dl_wwdt.c)
endif()
