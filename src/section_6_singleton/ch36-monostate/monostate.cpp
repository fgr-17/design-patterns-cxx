/**
 *    @file monostate .cpp
 *    @brief Chapter 36: Monostate
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mChapter 36:\e[0m Monostate" << std::endl;
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
