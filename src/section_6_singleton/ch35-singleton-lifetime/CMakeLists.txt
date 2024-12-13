set(app_name ch35-singleton-lifetime)
message("App name: " ${app_name})

include(FetchContent)


FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.81.0  # Use a specific version
)
FetchContent_MakeAvailable(Boost)

FetchContent_Declare(
  BoostDI
  GIT_REPOSITORY https://github.com/boost-ext/di.git
  GIT_TAG cpp14  # You can specify a specific tag or branch if needed
)
FetchContent_MakeAvailable(BoostDI)

add_executable (${app_name} singleton-lifetime.cpp)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${app_name} PRIVATE 
                            ${Boost_SOURCE_DIR}
                            ${BoostDI_SOURCE_DIR}/include)

unset(CXX_CLANG_TIDY)
unset(CXX_CPPLINT)
unset(CXX_INCLUDE_WHAT_YOU_USE)