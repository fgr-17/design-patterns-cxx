set(app_name communication-proxy)
message("App name: " ${app_name})

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include(FetchContent)
FetchContent_Declare(
  cpprestsdk
  GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
  GIT_TAG        v2.10.18
)
set(CPPREST_EXCLUDE_WEBSOCKETS ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpprestsdk)

# Third-party: no clang-tidy, use C++17 to avoid C++20 [=] deprecation in pplxtasks.h
set_target_properties(cpprest PROPERTIES
  CXX_CLANG_TIDY ""
  CXX_STANDARD 17
)

target_compile_definitions(cpprest PRIVATE BOOST_BIND_GLOBAL_PLACEHOLDERS)


add_executable(${app_name} ${app_name}.cpp)
set_target_properties(${app_name} PROPERTIES CXX_STANDARD 17)
target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${app_name} PRIVATE cpprest)