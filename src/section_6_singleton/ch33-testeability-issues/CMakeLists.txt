set(app_name ch33-testeability-issues)
message("App name: " ${app_name})

add_executable (${app_name} testeability-issues.cpp singleton-database.cpp)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
