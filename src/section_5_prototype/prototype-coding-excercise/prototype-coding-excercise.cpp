/**
 *    @file prototype-via-serialization.cpp
 *    @brief Chapter 29: prototype-via-serialization
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <memory>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <utility>


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
     Point() = default;
     Point(const int x, const int y) : x{x}, y{y} {}

     friend std::ostream& operator<< (std::ostream&oss, const Point&p){
         oss << "P(" << p.x << "," << p.y << ")";
         return oss;
     }
};

struct Line {
     std::unique_ptr<Point> start, end;

     Line(std::unique_ptr<Point> start, std::unique_ptr<Point> end): start(std::move(start)), end(std::move(end)) {}

     [[nodiscard]] Line deepCopy() const {
         auto startNew = std::make_unique<Point>(start->x, start->y);
         auto endNew = std::make_unique<Point>(end->x, end->y);
         return Line{std::move(startNew), std::move(endNew)};
     }

     friend std::ostream& operator<< (std::ostream&oss, const Line&l){
         oss << *l.start << "->" << *l.end;
         return oss;
     }
};

int main() {
    printTitle();

    auto p1 = std::make_unique<Point>(3, 2);
    std::cout << "p1 = " << *p1 << std::endl;

    auto p2 = std::make_unique<Point>(4, 4);
    std::cout << "p2 = " << *p2 << std::endl;

    auto l1 = Line(std::move(p1), std::move(p2));
    std::cout << "line: " << l1 << std::endl;

    return 0;
}
