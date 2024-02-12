set(PICO_BOARD pico_w)

cmake_minimum_required(VERSION 3.12)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(bt_test C CXX ASM)
pico_sdk_init()

add_executable(bt_test bt_test.c)

target_compile_options(bt_test PRIVATE -O1 -g)

target_link_options(bt_test PRIVATE -g)

add_subdirectory (.. bt)
target_link_libraries(bt_test
  pico_stdio
  bluetooth_stdio
  pico_cyw43_arch_none
  )

pico_add_extra_outputs(bt_test)
pico_enable_stdio_usb(bt_test 1)
pico_enable_stdio_uart(bt_test 0)
