/**
 *    @file shrink-wrapped-pimpl.cpp
 *    @brief Shrink Wrapped Pimpl idiom
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep

// shapes: circle, square
// renderer: raster, vector
// bridge pattern: avoid cartesian product of combinations
// - RasterCircleRenderer, RasterSquareRenderer, VectorCircleRenderer...

struct Point {
  float x = 0.0;
  float y = 0.0;
};

struct Renderer {
  virtual void renderCircle(Point center, float radius) = 0;
};

struct VectorRenderer : Renderer {
  void renderCircle(Point center, float r) override {
    std::cout << "rasterizing circle of r = " << r <<
                 " center: {" << center.x << ", " << center.y << "}"
                 << std::endl;
  }
};



/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 8:\e[0m Bridge" << std::endl;
  std::cout << "\e[1mCH46: Bridge Implementation\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  printTitle();
  return 0;
}
