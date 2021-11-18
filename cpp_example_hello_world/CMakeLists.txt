cmake_minimum_required(VERSION 3.17)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(hello C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

if (TARGET tinyusb_device)
    add_executable(
        ${CMAKE_PROJECT_NAME} 
        main.cpp
    )

    # pull in common dependencies
    target_link_libraries(${CMAKE_PROJECT_NAME}  pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
    pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

    # # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(${CMAKE_PROJECT_NAME} )

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
