cmake_minimum_required(VERSION 3.17)

include(C:/VSARM/sdk/pico/pico-sdk/external/pico_sdk_import.cmake)

# include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(
    blink 
    main.cpp
)

# pull in common dependencies
target_link_libraries(blink pico_stdlib)

# # create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
