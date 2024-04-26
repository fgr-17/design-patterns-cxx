#include <catch2/catch_test_macros.hpp>
#include <fakeit.hpp>

TEST_CASE("dummy test", "[C++ Template]") {
  int i = 0;

  INFO("Basic info from test app: " << i);
  REQUIRE(true);
}
