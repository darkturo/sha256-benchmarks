cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(wolfsha256 main.cc)

target_link_libraries(wolfsha256 wolfssl)
