set(app_name ch34-singleton-dep-injection)
message("App name: " ${app_name})

add_executable (${app_name} singleton-dep-injection.cpp singleton-database.cpp)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
