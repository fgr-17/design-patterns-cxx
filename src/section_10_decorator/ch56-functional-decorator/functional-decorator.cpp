/**
 *    @file functional-decorator.cpp
 *    @brief Functional Decorator
 *    @author rouxfederico@gmail.com
 */


#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>       // IWYU pragma: keep

/**
 *   @fn printTitle
 *   @brief chapter title 
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 10 :\e[0m Decorator" << std::endl;
  std::cout << "\e[1mCH56: Functional Decorator\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Functional Decorator
 */

int main() {
  printTitle();
  return 0;
}
