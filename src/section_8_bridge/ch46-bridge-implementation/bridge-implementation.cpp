/**
 *    @file bridge-implementation.cpp
 *    @brief Bridge implementation
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
    std::cout << "vectorizing circle of r = " << r <<
                 " center: {" << center.x << ", " << center.y << "}"
                 << std::endl;
  }
};

struct RasterRenderer : Renderer {
  void renderCircle(Point center, float r) override {
    std::cout << "rasterizing circle of r = " << r <<
                 " center: {" << center.x << ", " << center.y << "}"
                 << std::endl;
  }
};

struct Shape {
 private:
  Renderer& renderer_;
 protected:
  explicit Shape(Renderer& renderer): renderer_(renderer) {}
  [[nodiscard]] Renderer& getRenderer() const {
    return renderer_;
  }

 public:
  virtual void draw() = 0;
  virtual void resize(float factor) = 0;
};

struct Circle: Shape {
  Circle(Renderer&renderer, float x, float y, float r): Shape(renderer), center{x, y}, radius{r} {}

  Point center;
  float radius;

  void draw() override {
    getRenderer().renderCircle(center, radius);
  }

  void resize(float factor) override {
    radius = radius*factor;
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
  const float r = 5.0;
  const float x = 1.0, y = 2.0;
  RasterRenderer rr;
  VectorRenderer vr;

  Circle rasterCircle{rr, x, y, r};
  Circle vectorCircle{vr, x, y, r};

  printTitle();

  rasterCircle.draw();
  rasterCircle.resize(3);
  rasterCircle.draw();

  vectorCircle.draw();
  vectorCircle.resize(2);
  vectorCircle.draw();

  return 0;
}
