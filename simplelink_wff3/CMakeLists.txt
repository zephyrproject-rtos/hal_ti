cmake_minimum_required(VERSION 3.21)

set(TICLANG_ARMCOMPILER $ENV{TICLANG_ARMCOMPILER})
set(IAR_ARMCOMPILER $ENV{IAR_ARMCOMPILER})
set(GCC_ARMCOMPILER $ENV{GCC_ARMCOMPILER})

# Only look in local folders for components and platforms
set(CMAKE_ONLY_WRAPPER_COMPONENTS 1)
set(CMAKE_ONLY_LOCAL_PLATFORMS 1)

# Setup the CMake build environment
set(CMAKE_COMMON_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(source/cmake/scripts/cmake-common/Configure.cmake)
project(coresdk LANGUAGES)



############# uppermac content ############

#add compiler definitions
add_compile_definitions(CC35XX)
add_compile_definitions(DeviceFamily_CC35XX)

#add compiler/linker options from cmake-common
set(CMAKE_COMMON_LIBRARY CMakeCommon::${TI_TOOLCHAIN_NAME}_${ARCH_cc35xx})

#set the destination path for the libraries
set(LIB_DEST_DIR lib/${TI_TOOLCHAIN_NAME})

#set output libraries prefix/suffix
set(CMAKE_STATIC_LIBRARY_PREFIX_C   "")
set(CMAKE_STATIC_LIBRARY_PREFIX_CXX "")

# Set the CoreSDK root
set(CORESDK_WFF3 "${CMAKE_CURRENT_LIST_DIR}")

#Determine if SDK is being built as a subproject using add_subdirectory()
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    set(TI_SDK_ROOT_DIR "${REL_PATH}/")
endif()

###########################################

# Include directories that participate in the library build
add_subdirectory(kernel/nortos)
add_subdirectory(source/ti/devices/cc35xx)
add_subdirectory(source/ti/display)
add_subdirectory(source/ti/drivers)
add_subdirectory(source/ti/drivers/secure)
add_subdirectory(source/ti/log)
add_subdirectory(source/ti/utils)
add_subdirectory(source/ti/utils/json)
add_subdirectory(source/third_party/fatfs)
add_subdirectory(source/third_party/spiffs)
add_subdirectory(source/third_party/hsmddk)
add_subdirectory(source/third_party/lwip)
add_subdirectory(source/third_party/hostap)
add_subdirectory(source/third_party/nimble)
add_subdirectory(source/ti/net/ble_interface)
add_subdirectory(source/ti/net/wifi_stack)
add_subdirectory(source/ti/drivers/net/wifi/wifi_host_driver)
add_subdirectory(source/ti/drivers/net/wifi/wifi_platform/cc35xx)