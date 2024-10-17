/**
 *    @file prototype-via-serialization.cpp
 *    @brief Chapter 29: prototype-via-serialization
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 5:\e[0m Prototype" << std::endl;
  std::cout << "\e[1mChapter 29:\e[0m Prototype Coding Excercise" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Prototype Coding Exercise
 *   @brief Given the provided code, you are asked to implement Line::deep_copy()  to perform a deep copy of the current Line  object.
 *   @brief Beware memory leaks!
 */

 struct Point {
   int x{0}, y{0};

   Point(){}

   Point(const int x, const int y) : x{x}, y{y} {}
 };

 struct Line {
   Point *start, *end;

   Line(Point* const start, Point* const end)
     : start(start), end(end) {

   }

   ~Line() {
     delete start;
     delete end;
   }

   Line deep_copy() const
   {
     // TODO
   }
 };

int main() {
    printTitle();
    return 0;
}
