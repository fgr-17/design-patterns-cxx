#include <string>
#include <vector>
#include <map>


#include <gtest/gtest.h>

#include <singleton-database.h>

class DummyDatabase : public Database {
  std::map<std::string, int> cities;
 public:

  DummyDatabase() {
    cities["alpha"] = 1;
    cities["beta"] = 2;
    cities["gamma"] = 3;
  }

  int getPopulation(const std::string& cityName) override {
    return cities[cityName];
  }
};

TEST(RecordFinderTests, DependantTotalPopulationTest) {
  
  DummyDatabase db;
  ConfigurableRecordFinder rf{db};
  std::vector<std::string> cities = {"alpha", "beta"};
  auto tp = rf.totalPopulation(cities);

  EXPECT_EQ(1 + 2, tp);
}

TEST(HelloTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
}
