/**
 *    @file pimpl-idiom.cpp
 *    @brief Pimpl idiom
 *    @author rouxfederico@gmail.com
 */

#include <person.h>
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 8:\e[0m Bridge" << std::endl;
  std::cout << "\e[1mCH44: Pimpl idiom\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  Person p("fede");
  printTitle();

  p.greet();
  return 0;
}
