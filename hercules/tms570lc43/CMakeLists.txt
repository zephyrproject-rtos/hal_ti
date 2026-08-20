if(CONFIG_HAS_TMS570_HALCOGEN_CODE)
  zephyr_include_directories(
    include
  )
  
  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    source/soc_init.c
    source/asm_funcs.S
    source/soc_pll_errata.c
  )
endif()