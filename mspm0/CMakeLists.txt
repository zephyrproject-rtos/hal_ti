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

  file(GLOB driverlib source/ti/driverlib/*.c)
  file(GLOB sysctl source/ti/driverlib/m0p/sysctl/*.c)

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
	${driverlib}
	${sysctl}
	)
endif()
