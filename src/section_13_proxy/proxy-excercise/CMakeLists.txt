set(app_name proxy-excercise)
message("App name: " ${app_name})

add_executable(${app_name} ${app_name}.cpp)

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
