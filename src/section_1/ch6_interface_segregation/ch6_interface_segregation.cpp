/**
 *    @file main.cpp
 *    @brief Liksov subs principle: subtypes should be inmediatly substitutable by its parents types 
 *    @author rouxfederico@gmail.com
 * 
 */

#include <cassert>
#include <iostream>

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 6:\e[0m Interface Segregation Principle" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  print_tilte();

  return 0;
}