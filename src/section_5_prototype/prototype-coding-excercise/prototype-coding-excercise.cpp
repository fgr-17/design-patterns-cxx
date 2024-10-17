/**
 *    @file prototype-via-serialization.cpp
 *    @brief Chapter 29: prototype-via-serialization
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 5:\e[0m Prototype" << std::endl;
  std::cout << "\e[1mChapter 29:\e[0m Prototype Coding Excercise" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();
    return 0;
}
