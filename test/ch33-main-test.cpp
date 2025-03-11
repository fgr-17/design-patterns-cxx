#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <singleton-database.h>

TEST(HelloTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
}

TEST(RecordFinderTests, SingletonTotalPopulationTest) {
  SingletonRecordFinder rf;
  std::vector<std::string> cities = {"Seoul", "Mexico City"};
  auto tp = rf.totalPopulation(cities);

  // This is not a unit test, this is an integration test because:
  // * we're not testing only the record finder, but also the database -> STRONG COUPLING
  // * this test may fail bc of the hardcoded data, if the db changes
  EXPECT_EQ(17500000 + 17400000, tp);
}