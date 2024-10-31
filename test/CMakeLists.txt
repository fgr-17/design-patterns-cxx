# disable quality tools to avoid analyzing google test lib
unset(CMAKE_CXX_CPPLINT)
unset(CMAKE_CXX_CLANG_TIDY)
unset(CMAKE_CXX_INCLUDE_WHAT_YOU_USE)

# --------------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/df1544bcee0c7ce35cd5ea0b3eb8cc81855a4140.zip
)
FetchContent_MakeAvailable(googletest)
# --------------------------------------------------------------------------------------


set(testapp_name main_test)


add_executable(
  ${testapp_name}
  main_test.cpp
  ${CMAKE_SOURCE_DIR}/src/section_6_singleton/ch33-testeability-issues/singleton-database.cpp
)

target_include_directories(${testapp_name} PUBLIC
 ${CMAKE_SOURCE_DIR}/src/section_6_singleton/ch33-testeability-issues)

enable_testing()


target_link_libraries(
  ${testapp_name}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${testapp_name})
