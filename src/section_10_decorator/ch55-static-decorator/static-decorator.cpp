/**
 *    @file static-decorator.cpp
 *    @brief Static Decorator
 *    @author rouxfederico@gmail.com
 */


#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>       // IWYU pragma: keep
#include <utility>
#include <type_traits>

struct Shape {
  [[nodiscard]] virtual std::string str() const = 0;
};

struct Circle : Shape {
  float radius{};

  Circle() = default;
  explicit Circle(float radius) : radius{radius} {}

  void resize(float factor) {
    radius *= factor;
  }

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << "Circle with radius " << radius;
    return oss.str();
  }
};

struct Square : Shape {
  float side{};

  Square() = default;
  explicit Square(float side) : side(side) {}

  void resize(float factor) {
    side *= factor;
  }

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << "Square with side " << side;
    return oss.str();
  }
};

struct ColoredShape : Shape {
  Shape& shape;
  std::string color;

  ColoredShape(Shape& shape,  std::string color) : shape(shape), color(std::move(color)) {}

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

struct TransparentShape : Shape {
  Shape& shape;
  uint8_t transparency;

  static constexpr float maxInt = 255.0f;
  static constexpr float percentageFactor = 100.0f;

  TransparentShape(Shape& shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << shape.str() << " has the transparency " << static_cast<float>(transparency) / maxInt * percentageFactor << "%";
    return oss.str();
  }
};

// mixing inheritance
// perfect forwarding
template<typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template<IsAShape T>
struct ColoredShape2 : T {
  std::string color;

  ColoredShape2() = default;

  template <typename ...Args>
  ColoredShape2(std::string color,  Args ...args):
  T(std::forward<Args>(args)...), color(std::move(color)) {}

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template<IsAShape T>
struct TransparentShape2 : T {
  float transparency;
  static constexpr float maxInt = 255.0f;
  static constexpr float percentageFactor = 100.0f;

  template <typename ...Args>
  TransparentShape2(float transparency,  Args ...args):
  T(std::forward<Args>(args)...), transparency(transparency) {}

  [[nodiscard]] std::string str() const override {
    std::ostringstream oss;
    oss << T::str() << " has the transparency " << static_cast<float>(transparency) / maxInt * percentageFactor << "%";
    return oss.str();
  }
};

/**
 *   @fn printTitle
 *   @brief chapter title 
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 10 :\e[0m Decorator" << std::endl;
  std::cout << "\e[1mCH55: Static Decorator\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Static Decorator
 */

int main() {
  static constexpr float transparency = 50;
  static constexpr float radius = 5;
  ColoredShape2<Circle> greenCircle{"green", radius};
  printTitle();
  std::cout << greenCircle.str() << std::endl;

  TransparentShape2<ColoredShape2<Circle>> transparentGreenCircle{transparency, "green", radius};
  std::cout << transparentGreenCircle.str() << std::endl;
  // has access to the underlying methods
  transparentGreenCircle.color = "red";
  transparentGreenCircle.resize(2);
  std::cout << transparentGreenCircle.str() << std::endl;

  return 0;
}
