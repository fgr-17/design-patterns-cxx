set(app_name undo-and-redo)
message("App name: " ${app_name})

add_executable(${app_name} main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
