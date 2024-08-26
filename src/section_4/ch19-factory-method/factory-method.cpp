/**
 *    @file builder.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep


enum class PointType {
    cartesian,
    polar
};


struct Point {
    // initialize with cartesian coordinates
    // Point(float x, float y) : x(x), y(y) {}

    // initialize with polar coordinates --> ERROR
    // Point(float rho, float theta) : x(x), y(y) {}

    // a and b aren't good names, they don't represent anything useful
    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) {
            x = a;
            y = b;
        } else {
            x = a*std::cos(b);
            y = a*std::sin(b);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Point&p) {
        os << "P(x, y) = (" << p.x << ", " << p.y << ")";
        return os;
    }

    float x, y;
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 4:\e[0m Factories" << std::endl;
  std::cout << "\e[1mChapter 19:\e[0m Factory Method" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    const float x = 3.3, y = 3.2;
    const float rho = 4.1, th = 0.3;

    std::cout << Point(x, y) << std::endl;
    std::cout << Point(rho, th, PointType::polar) << std::endl;

    return 0;
}
