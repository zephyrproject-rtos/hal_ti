cmake_minimum_required(VERSION ${TI_MIN_CMAKE_VERSION})

cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME    TARGET_NAME)
message(STATUS "Generating target           ${TARGET_NAME}")

#read the version file
file(READ inc_adapt/upper_mac_versions.h uppermac_versions)
#set the version
string(REGEX MATCH "version_upper_mac[ \t]+\"upper_mac_([0-9|.]+)\"" _ ${uppermac_versions})
set(UPPERMAC_VERSION       ${CMAKE_MATCH_1} CACHE INTERNAL "")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/commands.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/fw_event_handle.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/fw_event_if.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/rx.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/trnspt_if.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/trnspt_thread.c
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer/txn_bus_drv.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/ip_utils.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/osi_common.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/w_queue.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/timer.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/event.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/errors.c

)

set (${TARGET_NAME}_INCLUDES

    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc_common
    ${CMAKE_CURRENT_LIST_DIR}/inc_adapt
    ${CMAKE_CURRENT_LIST_DIR}/trnspt_layer

)

set (${TARGET_NAME}_LIBRARIES

    ${CMAKE_COMMON_LIBRARY}
)

set (${TARGET_NAME}_COMPILER_FLAGS )

set (${TARGET_NAME}_DEFINITIONS     

    OS_NO_C_LIB_DEFINES
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
