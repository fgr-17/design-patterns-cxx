/**
 *    @file factory.cpp
 *    @brief Chapter 22 : Abstract Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 */

#define _USE_MATH_DEFINES
#include <cmath>        // IWYU pragma: keep
#include <iostream>
#include <memory>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>

#include "hot-drink.h"
#include "drink-factory.h"


std::unique_ptr<HotDrink> makeDrink(std::string type) {
    std::unique_ptr<HotDrink> drink;
    const auto vol = 200;

    if (type == "tea") {
        drink = std::make_unique<Tea>();
        drink->prepare(vol);
    } else {
        drink = std::make_unique<Coffee>();
        drink->prepare(vol);
    }
    return drink;
}

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 4:\e[0m Factories" << std::endl;
  std::cout << "\e[1mChapter 23:\e[0m Functional Factory" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    auto d = makeDrink("Coffee");

    DrinkFactory df;
    auto c = df.makeDrink("tea");

    DrinkWithVolumeFactory dwvf;
    const auto vol = 500;
    auto e = dwvf.makeDrink("coffee", vol);


    return 0;
}
