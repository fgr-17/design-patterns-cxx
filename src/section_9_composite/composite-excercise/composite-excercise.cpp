/**
 *    @file composite-excercise.cpp
 *    @brief Composite Coding Exercise
 *    @brief Consider the code presented below. The `sum()`  function takes a vector 
 *    @brief of pointers to either `SingleValue` or `ManyValues` instances and adds 
 *    @brief up all their elements together.
 *    @brief Please complete the implementation so that the `sum()`  function starts 
 *    @brief to operate correctly. This may involve giving the classes a common interface, 
 *    @brief among other things.
 *    @brief Here is an example of how the function might be used:
 *    @brief ~~~C++
 *    @brief SingleValue single_value{ 1 };
 *    @brief ManyValues other_values;
 *    @brief other_values.add(2);
 *    @brief other_values.add(3);
 *    @brief sum({ &single_value, &other_values }); // 
 *    @brief ~~~
 *    @author rouxfederico@gmail.com
 */

#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <vector>

#include "excercise.h"  // IWYU pragma: keep

[[nodiscard]] int sum(const std::vector<ContainsIntegers*>& items) {
  int sum = 0;
  for (const auto& item : items) {
    sum += item->sum();
  }
  return sum;
}

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 9:\e[0m Composition" << std::endl;
  std::cout << "\e[1mComposite Coding Excercise\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  printTitle();
  SingleValue singleValue{ 1 };
  ManyValues otherValues;
  otherValues.add(2);
  otherValues.add(3);
  std::cout << sum({ &singleValue, &otherValues }) << std::endl;
  return 0;
}
