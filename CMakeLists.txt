cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(MIDIKeyboard)

pico_sdk_init()

add_executable(MIDIKeyboard)

target_sources(MIDIKeyboard PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
)

target_include_directories(MIDIKeyboard PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(MIDIKeyboard PUBLIC pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(MIDIKeyboard)