set(TEST_NAME test_suite)

set(LIB_DIR lib)
set(FAKEIT_DIR FakeIt)

include_directories(
  ${CMAKE_SOURCE_DIR}/${LIB_DIR}/${FAKEIT_DIR}
)
  
set(Sources 
  main_test.cpp
)

## Testing 
find_package(Catch2 3 REQUIRED)

add_executable(${TEST_NAME} ${Sources})
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
