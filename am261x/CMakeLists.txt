set(AM261X_SOURCE_DIR ${ZEPHYR_HAL_TI_MODULE_DIR}/am261x/source)
set(AM261X_SOURCE_KERNELS_DIR ${AM261X_SOURCE_DIR}/kernel)

zephyr_library()

if(CONFIG_SOC_SERIES_AM261X)
  zephyr_include_directories(
    ${AM261X_SOURCE_DIR}
    ${AM261X_SOURCE_DIR}/drivers
  )

  zephyr_compile_definitions(
    SOC_AM261X
    DebugP_ASSERT_ENABLED=0
    DebugP_LOG_ENABLED=0
  )

  zephyr_library_sources(
    ${AM261X_SOURCE_DIR}/drivers/edma/v0/edma.c
    )

endif() # CONFIG_SOC_SERIES_AM261X