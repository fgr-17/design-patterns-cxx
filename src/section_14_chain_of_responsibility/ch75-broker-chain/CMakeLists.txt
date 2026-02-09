set(app_name broker-chain)
message("App name: " ${app_name})

find_package(Boost 1.60 REQUIRED)

include(FetchContent)

FetchContent_Declare(
  BoostDI
  GIT_REPOSITORY https://github.com/boost-ext/di.git
  GIT_TAG cpp14  
)
FetchContent_MakeAvailable(BoostDI)
set(BoostDI_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/boostdi-src")

add_executable(${app_name} ${app_name}.cpp)
set_target_properties(${app_name} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "")

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${app_name} PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${app_name} PRIVATE ${BoostDI_SOURCE_DIR}/include)
target_link_libraries(${app_name} Boost::boost)
