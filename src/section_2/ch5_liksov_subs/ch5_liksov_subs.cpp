/**
 *    @file main.cpp
 *    @brief Liksov subs principle: subtypes should be inmediatly substitutable by its parents types 
 *    @author rouxfederico@gmail.com
 * 
 */

#include <cassert>
#include <iostream>

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

class Rectangle {

protected:
  int width, height;

public:
  Rectangle(int width, int height): width(width), height(height) {}

  int getWidth() {
    return width;
  }

  virtual void setWidth(int width) {
    Rectangle::width = width;
  }

 int getHeight() {
    return height;
  }

  virtual void setHeight(int height) {
    Rectangle::height = height;
  }

  int area() const {return width*height;}
};


class Square : public Rectangle {
  public:

  Square(int size): Rectangle(size, size) {}

  void setWidth(int width) override {
    this->width = this->height = width;
  }

  void setHeight(int width) override {
    this->width = this->height = width;
  }
};

void process(Rectangle& r) {
  int w = r.getWidth();
  r.setHeight(10);

  std::cout << "expected area = " << (w*10)
            << ", got: " << r.area() << std::endl;
}

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 5:\e[0m Liksov Substitution Principle" << std::endl;
  return 0;
};

struct RectangleFactory {
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int s);
};


/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  print_tilte();

  Rectangle r{3, 4};
  process(r);

  Square sq{5};
  process(sq);
  // the function "process" does not aligns with Liksov subs principle as the argument of process() of type Rectangle cannot be substituted by a child class


  return 0;
}