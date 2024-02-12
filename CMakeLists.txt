if (NOT TARGET bluetooth_stdio)

  cmake_policy(SET CMP0079 NEW)
  
  add_library(bluetooth_stdio INTERFACE)

  target_include_directories(bluetooth_stdio INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    )

  target_sources(bluetooth_stdio INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/stdio_bt.c
    )

  target_link_libraries(bluetooth_stdio INTERFACE
    pico_stdlib
    pico_btstack_classic
    pico_btstack_cyw43
    pico_cyw43_arch_none
    hardware_clocks
    )
  
endif()
