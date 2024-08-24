
set(app_name ch15-builder-facets)
message("App name: " ${app_name})

add_executable (${app_name} builder-facets.cpp person-builder.cpp person.cpp)
target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
