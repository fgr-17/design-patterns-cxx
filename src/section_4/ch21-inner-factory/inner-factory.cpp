/**
 *    @file inner-factory.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep


enum class PointType {
    cartesian,
    polar
};

/**
 *   @fn Point
 *   @brief
 */

class Point {
    friend struct PointFactory;                 // hits on OCP
    Point(float x, float y) : x(x), y(y) {}

 public:
    float x, y;

    friend std::ostream& operator<<(std::ostream& os, const Point&p) {
        os << "P(x, y) = (" << p.x << ", " << p.y << ")";
        return os;
    }
};

/**
 *   @fn PointFactory
 *   @brief
 */

struct PointFactory {
    static Point newCartesian(float x, float y) {
        return {x, y};
    }

    static Point newPolar(float r, float theta) {
        return {r*std::cos(theta), r*std::sin(theta)};
    }
};


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 4:\e[0m Factories" << std::endl;
  std::cout << "\e[1mChapter 21:\e[0m Inner Factory" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    const float x = 3.3, y = 3.2;
    const float rho = 5.0, th = M_PI_4;

    auto p0 = PointFactory::newCartesian(x, y);
    auto p1 = PointFactory::newPolar(rho, th);

    std::cout << p0 << std::endl;
    std::cout << p1 << std::endl;

    return 0;
}
