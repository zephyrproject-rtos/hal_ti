if (CONFIG_HAS_AM13X_MCU_SDK)
  set(SDK_PATH ti)
  set(DEVICE am13e230x)

  zephyr_include_directories(
    .

    ${SDK_PATH}/source/driverlib/${DEVICE}

    ${SDK_PATH}/source/device/${DEVICE}/include/
    ${SDK_PATH}/source/device/${DEVICE}/include/hw
  )

  FILE(GLOB driverlib_sources ${SDK_PATH}/source/driverlib/${DEVICE}/*.c)
  target_sources(app PRIVATE ${driverlib_sources})

  zephyr_compile_options(
    -Wno-unused-variable
    -Wno-maybe-uninitialized
  )

  # Needed because Zephyr expects MemoryManagement_IRQn,
  # but SDK hw_ints.h for AM13E230X defines MemManage_IRQn
  zephyr_compile_definitions(MemoryManagement_IRQn=MemManage_IRQn)

  # type aliases for compatibility with MSP drivers
  zephyr_compile_definitions(UNICOMM_Inst_Regs=DL_UNICOMM_Inst_Regs)
endif()
