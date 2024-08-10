/**
 *    @file main.cpp
 *    @brief Liksov subs principle: subtypes should be inmediatly substitutable by its parents types
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>


class Rectangle {
 private:
  int width, height;

 public:
  Rectangle(int width, int height): width(width), height(height) {}

  [[nodiscard]] int getWidth() const {
    return width;
  }

  virtual void setWidth(int width) {
    Rectangle::width = width;
  }

  [[nodiscard]] int getHeight() const {
    return height;
  }

  virtual void setHeight(int height) {
    Rectangle::height = height;
  }

  [[nodiscard]] int area() const {return width*height;}
};


class Square : public Rectangle {
 public:
  explicit Square(int size): Rectangle(size, size) {}

  void setWidth(int width) override {
    Rectangle::setWidth(width);
    Rectangle::setHeight(width);
  }

  void setHeight(int height) override{
      Rectangle::setWidth(height);
      Rectangle::setHeight(height);
  }
};

void process(Rectangle* r) {
  const int magic_number = 10;
  int w = r->getWidth();
  r->setHeight(magic_number);

  std::cout << "expected area = " << (w * magic_number)
            << ", got: " << r->area() << std::endl;
}

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 5:\e[0m Liksov Substitution Principle" << std::endl;
  return 0;
}

struct RectangleFactory {
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int s);
};


/**
 *   @fn main
 *   @brief main program
 */

int main() {
  const int side1 = 3, side2 = 4;
  const int side3 = 5;

  print_tilte();

  Rectangle r{side1, side2};
  process(&r);

  Square sq{side3};
  process(&sq);
  // the function "process" does not aligns with Liksov subs principle as the argument of process() of type Rectangle cannot be substituted by a child class


  return 0;
}
