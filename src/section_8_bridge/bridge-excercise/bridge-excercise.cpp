/**
 *    @file bridge-excercise.cpp
 *    @brief **Bridge Coding Exercise**
 *           You are given an example of an inheritance hierarchy 
 *           which results in Cartesian-product duplication.
 *           Please refactor this hierarchy, giving the base class Shape  
 *           an initializer that takes a Renderer  defined as
 *    
 *           ~~~C++
 *           struct Renderer{
 *             virtual string what_to_render_as() const = 0;
 *           }
 *
 *           as well as `VectorRenderer` and `RasterRenderer`.
 *           The expectation is that each constructed object has a member 
 *           called `str()`  that returns its textual representation, for example:
 *
 *           `Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels"`
 *
 *    @author rouxfederico@gmail.com
 */

#include <string>
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <tuple>

struct Renderer {
  [[nodiscard]] virtual std::string render(std::string shapeName) const = 0;
};

struct VectorRenderer: Renderer {
  [[nodiscard]] std::string render(std::string shapeName) const override {
    return "Drawing " + shapeName + " as lines";
  }
};

struct RasterRenderer: Renderer {
  [[nodiscard]] std::string render(std::string shapeName) const override {
    return "Drawing " + shapeName + " as pixels";
  }
};

struct Shape {
  explicit Shape(Renderer&r): renderer_{r} {}

  void setName(const std::string name) {
    name_ = name;
  }

  [[nodiscard]] std::string getName() const {
    return name_;
  }

  [[nodiscard]] Renderer& getRenderer() const {
    return renderer_;
  }

  [[nodiscard]] std::string str() const {
    std::cout << renderer_.render(name_) << std::endl;
    return renderer_.render(name_);
  }

 private:
  std::string name_;
  Renderer& renderer_;
};

struct Triangle : Shape {
  explicit Triangle(Renderer&r): Shape{r} {
      setName("Circle");
  }
  std::string name;
};

struct Square : Shape {
  explicit Square(Renderer&r): Shape{r}  {
      setName("Square");
  }
  std::string name;
};

struct VectorSquare : Square {
  [[nodiscard]] std::string str() const {
      return "Drawing " + name + " as lines";
  }
};

struct RasterSquare : Square {
    [[nodiscard]] std::string str() const {
        return "Drawing " + name + " as pixels";
    }
};

// imagine e.g. VectorTriangle/RasterTriangle etc. here


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 8:\e[0m Bridge" << std::endl;
  std::cout << "\e[1mBridge Coding excercise\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  VectorRenderer vr;
  RasterRenderer rr;

  Square vectorSquare{vr};
  Square rasterSquare{rr};

  printTitle();
  std::ignore = vectorSquare.str();
  std::ignore = rasterSquare.str();
  return 0;
}
