set(app_name tree-iterator-coroutines)
message("App name: " ${app_name})

add_executable(${app_name} ${app_name}.cpp)

# C++20 coroutines: <coroutine> needs -fcoroutines (GCC 10, Clang)
# Disable clang-tidy/iwyu: they can fail on coroutine code
set_target_properties(${app_name} PROPERTIES
  CXX_STANDARD 23
  CXX_CLANG_TIDY ""
  CXX_INCLUDE_WHAT_YOU_USE ""
)
target_compile_options(${app_name} PRIVATE -fcoroutines)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
