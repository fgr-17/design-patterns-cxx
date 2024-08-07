/**
 *    @file builder.cpp
 *    @brief Dependency Inversion Principle: 
 *    @brief A. High-level modules should not depend on low-level modules. Both should depend on abstractions
 *    @brief B. Abstractions should not depend on details. Details should depend on abstractions
 *    @author rouxfederico@gmail.com
 * 
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>


static int print_tilte(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 11:\e[0m Life Without Builders" << std::endl;
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