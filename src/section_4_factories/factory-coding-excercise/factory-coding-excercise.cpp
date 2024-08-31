/**
 *    @file point-example.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>
#include <utility>

struct Person {
  int id;
  std::string name;

  Person(int id, std::string name) : id(id), name(std::move(name)) {}

  friend std::ostream& operator<<(std::ostream& os, Person&p) {
      os << p.name << " - id : " << p.id;
      return os;
  }
};

class PersonFactory {
    int index_ = 0;
 public:
  Person createPerson(const std::string& name) {
    Person p{index_++, name};
    return p;
  }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 4:\e[0m Factories" << std::endl;
  std::cout << "\e[1mCoding Excercise\e[0m" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    PersonFactory pf;
    auto p0 = pf.createPerson("Juan Perez");
    std::cout << p0 << std::endl;

    auto p1 = pf.createPerson("Pedro Jimenez");
    std::cout << p1 << std::endl;

    return 0;
}
