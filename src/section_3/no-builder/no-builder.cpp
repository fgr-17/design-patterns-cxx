/**
 *    @file builder.cpp
 *    @brief Life without buidlers
 *    @brief showing string concatenation for html from a non-OO perspective: does not scale
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

  auto text = "hello";


  // first example:
  std::string output;

  output += "<p>";
  output += text;
  output += "</p>";

  std::cout << output << std::endl;

  // 2nd example:

  std::string words[] = {"hello", "world"};
  std::ostringstream oss;

  
  oss << "<ul>";
  for (auto w: words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  std::cout << oss.str() << std::endl;

  return 0;
}