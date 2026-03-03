set(app_name communication-proxy)
message("App name: " ${app_name})

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include(FetchContent)
FetchContent_Declare(
  cpprestsdk
  GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
  GIT_TAG        v2.10.18
  PATCH_COMMAND
    sed -i "s/cmake_minimum_required(VERSION [0-9.]*)/cmake_minimum_required(VERSION 3.10)/" CMakeLists.txt
  COMMAND
    sed -i "s/cmake_minimum_required(VERSION [0-9.]*)/cmake_minimum_required(VERSION 3.10)/" Release/CMakeLists.txt
  COMMAND
    sed -i "2a cmake_policy(SET CMP0167 NEW)" Release/CMakeLists.txt
)
  
set(SAVED_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY})
set(SAVED_IWYU ${CMAKE_CXX_INCLUDE_WHAT_YOU_USE})
set(SAVED_STANDARD ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_CLANG_TIDY "")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "")
set(CMAKE_CXX_STANDARD 17)

set(CPPREST_EXCLUDE_WEBSOCKETS ON CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(cpprestsdk)

set_target_properties(cpprest PROPERTIES CXX_CLANG_TIDY "")
target_compile_definitions(cpprest PRIVATE BOOST_BIND_GLOBAL_PLACEHOLDERS)
target_compile_options(cpprest PRIVATE -Wno-dev -Wno-format-truncation)


set(CMAKE_CXX_CLANG_TIDY ${SAVED_CLANG_TIDY})
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${SAVED_IWYU})
set(CMAKE_CXX_STANDARD ${SAVED_STANDARD})

add_executable(${app_name} ${app_name}.cpp)

set_target_properties(${app_name} PROPERTIES CXX_CLANG_TIDY "")
target_compile_options(${app_name} PRIVATE -Wno-deprecated)
target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${app_name} PRIVATE cpprest)