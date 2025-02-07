set(app_name ch35-singleton-lifetime)
message("App name: " ${app_name})

add_executable (${app_name} singleton-lifetime.cpp)

find_package(Boost 1.74 REQUIRED)

if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${app_name} Boost::boost)
else()
    message(FATAL_ERROR "Could not find Boost")
endif()

unset(CXX_CLANG_TIDY)
unset(CXX_CPPLINT)
unset(CXX_INCLUDE_WHAT_YOU_USE)