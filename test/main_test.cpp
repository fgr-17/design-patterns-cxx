#include <gtest/gtest.h>

#include <testeability-issues.cpp>

TEST(HelloTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
}
