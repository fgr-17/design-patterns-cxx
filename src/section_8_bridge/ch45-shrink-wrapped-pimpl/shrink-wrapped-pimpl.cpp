/**
 *    @file shrink-wrapped-pimpl.cpp
 *    @brief Shrink Wrapped Pimpl idiom
 *    @author rouxfederico@gmail.com
 */

#include <person.h>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>    // for allocator, string

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 8:\e[0m Bridge" << std::endl;
  std::cout << "\e[1mCH45: Shrink Wrapped Pimpl\e[0m" << std::endl;
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
