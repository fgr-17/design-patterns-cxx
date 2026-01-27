/**
 *    @file decorator-excercise.cpp
 *    @brief Decorator Excercise
 *    @brief Decorator Coding Exercise
 *    @brief Roses can be red, blue or red and blue. Given the class interface 
 *    @brief Flower and class Rose, build decorators RedFlower and BlueFlower 
 *    @brief that would print the following:
 *    @brief ~~~C++
 *    @brief Rose rose;
 *    @brief RedFlower red_rose{rose};
 *    @brief RedFlower red_red_rose{red_rose};
 *    @brief BlueFlower blue_red_rose{red_rose};
 *    @brief cout << rose.str();          // "A rose"
 *    @brief cout << red_rose.str();      // "A rose that is red"
 *    @brief cout << red_red_rose.str();  // "A rose that is red"
 *    @brief cout << blue_red_rose.str(); // "A rose that is red and blue"
 *    @brief ~~~
 *    @author rouxfederico@gmail.com
 */


#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>       // IWYU pragma: keep
#include <utility>      // IWYU pragma: keep

struct Flower {
  [[nodiscard]] virtual std::string str() const = 0;
};

struct Rose : Flower {
  [[nodiscard]] std::string str() const override {
    return "A rose";
  }
};

struct ColoredRose : Rose {
  Rose& rose;
  std::string color;
  explicit ColoredRose(Rose& rose, const std::string color) : rose(rose), color(std::move(color)) {}

  [[nodiscard]] std::string str() const override {
    auto baseStr = rose.str();
    if (baseStr == "A rose") {
      return "A rose that is " + color;
    } else if (baseStr.find(color)  != std::string::npos) {
      return baseStr;
    }
    else {
      return baseStr + " and " + color;
    }
  }
};

struct RedFlower : ColoredRose {
  explicit RedFlower(Rose& rose) : ColoredRose(rose, "red") {}
};

struct BlueFlower : ColoredRose {
  explicit BlueFlower(Rose& rose) : ColoredRose(rose, "blue") {}
};

/**
 *   @fn printTitle
 *   @brief chapter title 
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 10 :\e[0m Decorator" << std::endl;
  std::cout << "\e[1mDecorator Coding Exercise\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

int main() {
  printTitle();

  Rose rose;
  RedFlower redRose{rose};
  RedFlower redRedRose{redRose};
  BlueFlower blueRedRose{redRose};
  RedFlower redBlueRedRose{blueRedRose};

  std::cout << rose.str() << std::endl;             // "A rose"
  std::cout << redRose.str() << std::endl;          // "A rose that is red"
  std::cout << redRedRose.str() << std::endl;       // "A rose that is red"
  std::cout << blueRedRose.str() << std::endl;      // "A rose that is red and blue"
  std::cout << redBlueRedRose.str() << std::endl;   // "A rose that is red and blue and red"
  std::cout << std::endl;
  return 0;
}
