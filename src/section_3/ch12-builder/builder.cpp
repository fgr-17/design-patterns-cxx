/**
 *    @file builder.cpp
 *    @brief Chapter 12: Builders
 *    @brief showing string concatenation for html from a non-OO perspective: does not scale
 *    @author rouxfederico@gmail.com
 *
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <utility>
#include <array>


/**
 *   @struct HtmlElement
 *   @brief Html builder
 */

struct HtmlElement{
  std::string name, text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() = default;

  explicit HtmlElement(const std::string name) : name(std::move(name)) {}

  HtmlElement(const std::string name, const std::string text) : name(std::move(name)), text(std::move(text)) {}

  [[nodiscard]] std::string str(int indent = 0) const {
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
  HtmlElement root_;

  explicit HtmlBuilder(std::string root__name) : root_(root__name) {}

  void addChild(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root_.elements.push_back(e);
  }

  [[nodiscard]] std::string str() const { return root_.str(); }
};

/**
 *   @fn main
 *   @brief main program
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 12:\e[0m Builders" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
  printTitle();

  auto text = "hello";
  // first example:
  std::string output;

  output += "<p>";
  output += text;
  output += "</p>";

  std::cout << output << std::endl;

  // 2nd example:

  std::array<std::string, 2> words = {"hello", "world"};
  std::ostringstream oss;

  oss << "<ul>";
  for (auto w : words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  std::cout << oss.str() << std::endl;

  // OO struct for builder

  HtmlBuilder builder{"ul"};
  builder.addChild("li", "hello");
  builder.addChild("li", "world");
  std::cout << builder.str() << std::endl;

  return 0;
}
