/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class Color {red, green, blue};
enum class Size  {small, medium, large};

const std::map<Color, std::string> colorString = {
  {Color::red, "red"},
  {Color::green, "green"},
  {Color::blue, "blue"}
};

const std::map<Size, std::string> sizeString = {
  {Size::small, "small"},
  {Size::medium, "medium"},
  {Size::large, "large"}
};

struct Product {
  std::string name;
  Color color;
  Size size;
};

struct ProductFilter {
  // needs a new function for each filter requested <<< this is not closed for modification
  static std::vector <Product*> byColor(const std::vector<Product*>& items, Color color) {
    std::vector <Product*> result;
    for (const auto&i : items) {
      if (i->color == color) result.push_back(i);
    }
    return result;
  }

  static std::vector <Product*> bySize(const std::vector<Product*>& items, const Size size) {
    std::vector <Product*> result;
    for (const auto&i : items) {
      if (i->size == size) result.push_back(i);
    }
    return result;
  }

  static std::vector <Product*> bySizeAndColor(const std::vector<Product*>& items, const Color color, const Size size) {
    std::vector <Product*> result;
    for (const auto&i : items) {
      if ((i->color == color) && (i->size == size)) result.push_back(i);
    }
    return result;
  }
  /////////////////////////////////////

  static int printOutput(const std::vector<Product*>& items) {
    for (const auto& i : items) {
      std::cout << i->name << " - color: " << colorString.at(i->color) << " - size: " << sizeString.at(i->size) << std::endl;
    }

    return 0;
  }
};

template <typename T> struct Specification {
    virtual bool isSatisfied(T*item) const = 0;

    // adding this to avoid concatenating many specs: This does not work due to cross dependencies!
    // AndSpecification<T> operator&& (Specification<T>&& other) {
    //   return AndSpecification<T> (*this, other);
    // }
};

template <typename T> struct Filter {
  virtual std::vector<T*> filter(std::vector<T*> items, const Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
  std::vector<Product*> filter(std::vector<Product*> items, const Specification<Product> &spec) override {
    std::vector<Product*> result;

    for (auto&item : items)
      if (spec.isSatisfied(item))
        result.push_back(item);

    return result;
  }
};

template <typename T> struct AndSpecification: Specification<T> {
  const Specification<T>& first;
  const Specification<T>& second;

  AndSpecification(const Specification<T>& first, const Specification<T>& second): first(first), second(second) {}

  bool isSatisfied(T*item) const override {
    return (first.isSatisfied(item) && second.isSatisfied(item));
  }
};

struct ColorSpecification: Specification<Product> {
  Color color;
  explicit ColorSpecification(Color color) : color(color) {}

  bool isSatisfied(Product*item) const override {
    return (item->color == color);
  }
};

struct SizeSpecification: Specification<Product> {
  Size size;
  explicit SizeSpecification(Size size) : size(size) {}

  bool isSatisfied(Product*item) const override {
    return (item->size == size);
  }
};

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 4:\e[0m Open-Closed Principle" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
  printTitle();

  Product apple {"Apple", Color::green, Size::small};
  Product tree {"Tree", Color::green, Size::large};
  Product house {"House", Color::blue, Size::large};

  std::vector<Product*> items {&apple, &tree, &house};

  auto greenThings = ProductFilter::byColor(items, Color::green);

  ProductFilter::printOutput(greenThings);

  BetterFilter bf;
  ColorSpecification green(Color::green);

  for (auto& item : bf.filter(items, green))
    std::cout << item->name << " is green" << std::endl;

  SizeSpecification large(Size::large);
  AndSpecification<Product> greenAndLarge(green, large);

  for (auto& item : bf.filter(items, greenAndLarge))
    std::cout << item->name << " is green and large" << std::endl;

  return 0;
}
