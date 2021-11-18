cmake_minimum_required(VERSION 3.17)

if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(blink_rgb C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(
    ${CMAKE_PROJECT_NAME} 
    main.cpp
)

# pull in common dependencies
target_link_libraries(${CMAKE_PROJECT_NAME}  pico_stdlib)

# # create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${CMAKE_PROJECT_NAME} )

