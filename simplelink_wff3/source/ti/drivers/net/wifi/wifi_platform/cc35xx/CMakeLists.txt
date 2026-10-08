cmake_minimum_required(VERSION ${TI_MIN_CMAKE_VERSION})

cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PARENT_PATH)
cmake_path(GET PARENT_PATH              FILENAME    PARENT_NAME)
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME    TARGET_NAME)
set(TARGET_NAME ${PARENT_NAME}_${TARGET_NAME})


message(STATUS "Generating target           ${TARGET_NAME}")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_LIST_DIR}/plat/bus_hif.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/init_device.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/time_util.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/otfde_driver.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/wlan_irq_adapt.c    
    
    ${CMAKE_CURRENT_LIST_DIR}/plat/hif.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/tls_iperf_mbedtls.c
    $<$<BOOL:CRYPTO_MBEDTLS>:
    ${CMAKE_CURRENT_LIST_DIR}/plat/tls_mbedtls.c
    ${CMAKE_CURRENT_LIST_DIR}/plat/crypto_mbedtls.c>

)

set (${TARGET_NAME}_HEADERS

     $<TARGET_PROPERTY:hostap,PRECOMPILE_HEADERS>
)

set(${TARGET_NAME}_INCLUDES

    ${CMAKE_CURRENT_LIST_DIR}/inc_common
    ${CMAKE_CURRENT_LIST_DIR}/plat        

    #external includes
    ${CORESDK_WFF3}/source
    ${CORESDK_WFF3}/source/ti/drivers/xmem/flash/
    ${CORESDK_WFF3}/source/third_party/mbedtls
    ${CORESDK_WFF3}/source/third_party/mbedtls/ti/configs/
    ${CORESDK_WFF3}/source/third_party/mbedtls/ti/port/
    ${CORESDK_WFF3}/source/third_party/mbedtls/include/
    ${CORESDK_WFF3}/source/ti/posix/${TI_TOOLCHAIN_NAME}


       
    $<TARGET_PROPERTY:wifi_host_driver,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:hostap,INCLUDE_DIRECTORIES>
)

set (${TARGET_NAME}_LIBRARIES 

    hostap
    ${CMAKE_COMMON_LIBRARY}

)


set (${TARGET_NAME}_COMPILER_FLAGS 

     -Wno-error
     --include=$<TARGET_PROPERTY:hostap,PRECOMPILE_HEADERS>

)

set (${TARGET_NAME}_DEFINITIONS 
    MBEDTLS_CONFIG_FILE="config-hsm.h" 
    MBEDTLS_PSA_CRYPTO_CONFIG_FILE="config-psa-crypto-hsm.h"
)

set (${TARGET_NAME}_HEADERS )


add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
target_link_libraries     (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_LIBRARIES})

#set install option
install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/${LIB_DEST_DIR})
