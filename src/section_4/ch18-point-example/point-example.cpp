/**
 *    @file builder.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 4:\e[0m Factories" << std::endl;
  std::cout << "\e[1mChapter 14:\e[0m Point example" << std::endl;
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
