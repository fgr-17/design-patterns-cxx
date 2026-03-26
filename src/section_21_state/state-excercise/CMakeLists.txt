set(app_name state-excercise)
message("App name: " ${app_name})

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# Don't build and run tests; we only need the library
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Boost 1.60 REQUIRED)
set(BoostDI_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/boostdi-src")

add_executable(${app_name} ${app_name}.cpp)
set_target_properties(${app_name} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "")

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${app_name} GTest::gtest)