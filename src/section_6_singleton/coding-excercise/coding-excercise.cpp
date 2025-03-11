/**
 *    @file multiton .cpp
 *    @brief Singleton Coding Exercise

Implementing a singleton is a bit too easy, so you've got a different challenge. 
You are given the function SingletonTester::is_singleton()  defined below. This function takes a factory, 
and needs to return true  or false  depending on whether that factory produces singletons.
This one's actually easy. Ask yourself: what traits do two 'instances' of a singleton have in common?

*    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <functional>


struct SingletonTester {
  template <typename T>
  bool isSingleton(std::function<T*()> factory) {
    T* instance1 = factory();
    T* instance2 = factory();
    return (instance1 == instance2);
  }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mCoding Excercise\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  printTitle();
  return 0;
}
