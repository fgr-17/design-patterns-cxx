/**
 *    @file builder.cpp
 *    @brief Chapter 12: Builders
 *    @brief showing string concatenation for html from a non-OO perspective: does not scale
 *    @author rouxfederico@gmail.com
 * 
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

/**
 *   @struct HtmlElement
 *   @brief Html builder
 */

struct HtmlElement{
  std::string name, text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}

  explicit HtmlElement(const std::string&name) : name(name) {}

  HtmlElement(const std::string&name, const std::string&text) : name(name), text(text) {}

  std::string str(int indent = 0) const {
    std::ostringstream oss;
    std::string i(indent_size*indent, ' ');
    oss << i << "<" << name << ">" << std::endl;

    if (text.size() > 0)
      oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << std::endl;
    return oss.str();
  }
};


struct HtmlBuilder{
  HtmlElement root;

  explicit HtmlBuilder(std::string root_name) : root(root_name) {}

  void add_child(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.push_back(e);
  }

  std::string str() const { return root.str(); }
};

/**
 *   @fn main
 *   @brief main program
 */

static int print_title(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 12:\e[0m Builders" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  print_title();

  auto text = "hello";
  // first example:
  std::string output;

  output += "<p>";
  output += text;
  output += "</p>";

  std::cout << output << std::endl;

  // 2nd example:

  std::string words[] = {"hello", "world"};
  std::ostringstream oss;

  oss << "<ul>";
  for (auto w : words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  std::cout << oss.str() << std::endl;

  // OO struct for builder

  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "world");
  std::cout << builder.str() << std::endl;

  return 0;
}
