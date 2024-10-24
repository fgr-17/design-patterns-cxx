
cmake_minimum_required(VERSION 3.18)

project(CXX_PROJECT)

### C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard required for build")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "is C++ stndard a requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "enable/disable compiler specific extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -std=c++11")

set(CMAKE_CXX_CPPLINT "cpplint")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
# set(CMAKE_CXX_CLANG_FORMAT "clang-format")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu")

set(SRC_DIR src)

add_subdirectory(src/section_2_SOLID/ch3_single_resp)
add_subdirectory(src/section_2_SOLID/ch4_open_closed)
add_subdirectory(src/section_2_SOLID/ch5_liksov_subs)
add_subdirectory(src/section_2_SOLID/ch6_interface_segregation)
add_subdirectory(src/section_2_SOLID/ch7_dep_inversion)

add_subdirectory(src/section_3_builder/ch11-no-builder)
add_subdirectory(src/section_3_builder/ch12-builder)
add_subdirectory(src/section_3_builder/ch13-fluent-builder)
add_subdirectory(src/section_3_builder/ch14-groovy-style-builder)
add_subdirectory(src/section_3_builder/ch15-builder-facets)
add_subdirectory(src/section_3_builder/builder-coding-excercise)

add_subdirectory(src/section_4_factories/ch18-point-example)
add_subdirectory(src/section_4_factories/ch19-factory-method)
add_subdirectory(src/section_4_factories/ch20-factory)
add_subdirectory(src/section_4_factories/ch21-inner-factory)
add_subdirectory(src/section_4_factories/ch22-abstract-factory)
add_subdirectory(src/section_4_factories/ch23-functional-factory)
add_subdirectory(src/section_4_factories/factory-coding-excercise)

add_subdirectory(src/section_5_prototype/ch26-record-keeping)
add_subdirectory(src/section_5_prototype/ch27-prototype)
add_subdirectory(src/section_5_prototype/ch28-prototype-factory)
add_subdirectory(src/section_5_prototype/ch29-prototype-via-serialization)
add_subdirectory(src/section_5_prototype/prototype-coding-excercise)
