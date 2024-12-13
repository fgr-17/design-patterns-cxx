/**
 *    @file testeability-issues.cpp
 *    @brief Chapter 35: Singleton Lifetime in DI Container
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>


class IFoo {
  virtual std::string name() = 0;
};

class Foo : IFoo {
 private:
  static int id;
 
 public: 
  Foo() { ++id; }

  std::string name() override {
    return "foo " + std::to_string(id);
  }
};

int Foo::id = 0;

struct Bar {
  std::shared_ptr<IFoo> foo;
};


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mChapter 35:\e[0m Singleton Lifetime in DI Container" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    printTitle();
    return 0;
}
