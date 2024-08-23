/**
 *    @file builder.cpp
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>
#include "person.h"
#include "person-builder.h"


/**
 *   @fn printTitle
 *   @brief class header
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 15:\e[0m Builder Facets" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    const int earning = 10e6;

    Person p = Person::create()
        .lives().at("123 London Road").withPostcode("SW1 1GB").in("London")
        .works().at("PragmaSoft").asA("Consultant").earning(earning);

    std::cout << p << std::endl;
    return 0;
}
