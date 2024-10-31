/**
 *    @file testeability-issues.cpp
 *    @brief Chapter 33: Testeability Issues
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>

#include <singleton-database.h>

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mChapter 33:\e[0m Testeability Issues" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    printTitle();

    std::string city = "Tokyo";

    SingletonDatabase::get().print();
    std::cout << "\n" << city << " has population of " << SingletonDatabase::get().getPopulation(city) << std::endl;
    return 0;
}
