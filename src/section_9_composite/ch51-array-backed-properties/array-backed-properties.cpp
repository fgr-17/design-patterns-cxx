/**
 *    @file geometric-shapes.cpp
 *    @brief Geometric shapes - example on composition
 *    @author rouxfederico@gmail.com
 */

#include <algorithm>
#include <array>
#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <numeric>
#include <string>
#include <utility>

class Creature {
 public:
  [[nodiscard]] int getStrength() const {
    return strength_;
  }

  [[nodiscard]] int getAgility() const {
    return agility_;
  }

  [[nodiscard]] int getIntelligence() const {
    return intelligence_;
  }

  void setStrength(int strength) {
    Creature::strength_ = strength;
  }

  void setAgility(int agility) {
    Creature::agility_ = agility;
  }

  void setIntelligence(int intelligence) {
    Creature::intelligence_ = intelligence;
  }

  [[nodiscard]] double sum() const {
    return strength_ + agility_ + intelligence_;
  }

  [[nodiscard]] double average() const {
    return sum()/static_cast<float>(maxProperties);
  }

  [[nodiscard]] int max() const {
    return std::max(std::max(strength_, agility_), intelligence_);
  }

 private:
  int strength_, agility_, intelligence_;
  static constexpr uint32_t maxProperties = 3;
};

class BetterCreature {
 public:
  BetterCreature(std::string name, int strength, int agility, int intelligence): name_{std::move(name)}, abilities_{} {
    setStrength(strength);
    setAgility(agility);
    setIntelligence(intelligence);
  }

  [[nodiscard]] int getStrength() const {
    return abilities_[strength];
  }

  void setStrength(int value) {
    abilities_[strength] = value;
  }

  [[nodiscard]] int getAgility() const {
    return abilities_[strength];
  }

  void setAgility(int value) {
    abilities_[agility] = value;
  }

  [[nodiscard]] int getIntelligence() const {
    return abilities_[intelligence];
  }

  void setIntelligence(int value) {
    abilities_[intelligence] = value;
  }

  [[nodiscard]] int sum() const {
    return std::accumulate(abilities_.begin(), abilities_.end(), 0);
  }

  [[nodiscard]] double average() const {
    return sum() / static_cast<double>(count);
  }

  [[nodiscard]] int max() const {
    return *std::max_element(abilities_.begin(), abilities_.end());
  }

  friend std::ostream& operator<<(std::ostream& os, const BetterCreature& obj) {
    os << obj.name_ << ": " << std::endl;
    os << "\tstrength: " << obj.getStrength() << std::endl;
    os << "\tagility: " << obj.getAgility() << std::endl;
    os << "\tintelligence: " << obj.getIntelligence() << std::endl;
    os << "\t-------------" << std::endl;
    os << "\tsum: " << obj.sum() << std::endl;
    os << "\taverage: " << obj.average() << std::endl;
    os << "\tmax: " << obj.max() << std::endl;
    return os;
  }

 private:
  std::string name_;
  enum Abilities {
    strength, agility, intelligence, count
  };
  std::array<int, count> abilities_;
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 9:\e[0m Composition" << std::endl;
  std::cout << "\e[1mCH51: Array-Backed Properties\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  printTitle();
  const int orcStr = 16;
  const int orcAgl = 11;
  const int orcInt = 9;

  BetterCreature orc{"orc", orcStr, orcAgl, orcInt};

  std::cout << orc;

  return 0;
}
