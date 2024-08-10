/**
 *    @file builder.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
// #include <cstdio>
#include <string>
#include <vector>
// #include <fstream>
// #include <tuple>
// #include <sstream>
// #include <memory>
#include <utility>


struct Tag {
  std::string name, text;
  std::vector<Tag> children;
  std::vector<std::pair<std::string, std::string>> attributes;
};


/**
 *   @fn main
 *   @brief main program
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 14:\e[0m Groovy-Style Builder" << std::endl;
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
