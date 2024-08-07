/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */


#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map> 

using namespace std;

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

enum class Color {red, green, blue};
enum class Size  {small, medium, large};

map<Color, std::string> color_string = {
  {Color::red, "red"},
  {Color::green, "green"},
  {Color::blue, "blue"}
};

map<Size, std::string> size_string = {
  {Size::small, "small"},
  {Size::medium, "medium"},
  {Size::large, "large"}
};

struct Product {
  string name;
  Color color;
  Size size;
};

struct ProductFilter {

  // needs a new function for each filter requested <<< this is not closed for modification
  vector <Product*> by_color (vector<Product*> items, Color color) {
    vector <Product*> result;
    for(auto&i: items) {
      if(i->color == color) result.push_back(i);
    }
    return result;
  }

  vector <Product*> by_size (vector<Product*> items, Size size) {
    vector <Product*> result;
    for(auto&i: items) {
      if(i->size == size) result.push_back(i);
    }
    return result;
  }

  vector <Product*> by_size_and_color (vector<Product*> items, Color color, Size size) {
    vector <Product*> result;
    for(auto&i: items) {
      if((i->color == color) && (i->size == size)) result.push_back(i);
    }
    return result;
  }
  /////////////////////////////////////
  
  
  int print_output (vector<Product*> items) {
    for(auto& i:items) {
      cout << i->name << " - color: " << color_string[i->color] << " - size: " << size_string[i->size] << endl;
    }

    return 0;
  }
};


template <typename T> struct Specification {
    virtual bool is_satisfied(T*item) = 0;

    // adding this to avoid concatenating many specs: This does not work due to cross dependencies!
    // AndSpecification<T> operator&& (Specification<T>&& other) {
    //   return AndSpecification<T> (*this, other);
    // }
  };

template <typename T> struct Filter {
  virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
  vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) override {
    vector<Product*> result;

    for(auto&item: items)
      if(spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};

template <typename T> struct AndSpecification: Specification<T> {
  Specification<T>& first;
  Specification<T>& second;

  AndSpecification(Specification<T>& first, Specification<T>& second): first(first), second(second) {}

  bool is_satisfied(T*item) override {
    return (first.is_satisfied(item) && second.is_satisfied(item));
  }
};

struct ColorSpecification: Specification<Product> {
  Color color;
  ColorSpecification(Color color) : color(color) {}

  bool is_satisfied(Product*item) override {
    return (item->color == color);
  }
};

struct SizeSpecification: Specification<Product> {
  Size size;
  SizeSpecification(Size size) : size(size) {}

  bool is_satisfied(Product*item) override {
    return (item->size == size);
  }
};

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte(void) {
  cout << "\e[1mDesign Patterns in Modern C++\e[0m" << endl;
  cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << endl;
  cout << "\e[1mChapter 4:\e[0m Open-Closed Principle" << endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {

  print_tilte();

  Product apple {"Apple", Color::green, Size::small};
  Product tree {"Tree", Color::green, Size::large};
  Product house {"House", Color::blue, Size::large};

  vector<Product*> items {&apple, &tree, &house};

  ProductFilter pf;
  auto green_things = pf.by_color(items, Color::green);

  pf.print_output(green_things);
  
  BetterFilter bf;
  ColorSpecification green(Color::green);

  for (auto& item: bf.filter(items, green))
    std::cout << item->name << " is green" << std::endl;


  SizeSpecification large(Size::large);
  AndSpecification<Product> green_and_large(green, large);

  for (auto& item: bf.filter(items, green_and_large))
    std::cout << item->name << " is green and large" << std::endl;



  return 0;
}
