add_subdirectory(source/ti/devices)

if(CONFIG_HAS_CC35XX_SDK)
  if(CONFIG_SOC_SERIES_CC35XXE)
    zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})
    zephyr_compile_definitions(CC35XX)
    zephyr_compile_definitions(CONFIG_DYNAMIC_DPL_OBJECTS)
    zephyr_include_directories(
      .
      source
      source/ti/drivers
      source/ti/drivers/xmem/flash
      source/ti/drivers/cryptoutils/cryptokey
      third_party/hsmddk/include/Kit/Log/incl/
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
  endif()
endif()

