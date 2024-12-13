set(app_name ch35-singleton-lifetime)
message("App name: " ${app_name})

add_executable (${app_name} singleton-lifetime.cpp)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
