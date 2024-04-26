cmake_minimum_required(VERSION 3.16)

set(lib_name common)

add_library(${lib_name} common.cpp)
target_include_directories (${lib_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})