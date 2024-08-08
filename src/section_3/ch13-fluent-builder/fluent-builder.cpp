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

// forward declaration due to cross ref
struct HtmlBuilder;

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

  static HtmlBuilder build(std::string root_name);

  static std::unique_ptr<HtmlBuilder> build_2(std::string root_name);
};

/**
 * @brief HtmlBuilder
 * 
 */

struct HtmlBuilder{
  HtmlElement root;

  explicit HtmlBuilder(std::string root_name) : root(root_name) {}

  HtmlBuilder& add_child(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.push_back(e);
    return *this;
  }

  // return pointer instead of ref
  HtmlBuilder* add_child_2(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.push_back(e);
    return this;
  }

  std::string str() const { return root.str(); }

  operator HtmlElement() const {
    // returns copy of the op
    // return root;

    return std::move(root);
  }
};

/**
 * @brief definition of build method outside the class due to cross ref
 * 
 * @param root_name 
 * @return HtmlBuilder 
 */
HtmlBuilder HtmlElement::build(std::string root_name) {
  return HtmlBuilder{root_name};
}

/**
 * @brief another example of builders using unique pointers
 * 
 * @param root_name 
 * @return HtmlBuilder 
 */
std::unique_ptr<HtmlBuilder> HtmlElement::build_2(std::string root_name) {
  return std::make_unique<HtmlBuilder>(HtmlBuilder{root_name});
}



/**
 *   @fn main
 *   @brief main program
 */

static int print_title(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 13:\e[0m Fluent Builder" << std::endl;
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
  builder.add_child("li", "hello").add_child("li", "world");
  std::cout << builder.str() << std::endl;

  auto builder2 = HtmlElement::build("ul").add_child("li", "hello").add_child("li", "world");
  std::cout << builder2.str() << std::endl;

  HtmlElement builder3 = HtmlElement::build("ul").add_child("li", "hello").add_child("li", "world");
  std::cout << builder3.str() << std::endl;

  HtmlElement builder4 = HtmlElement::build("ul").add_child_2("li", "hello")->add_child("li", "world");
  std::cout << builder4.str() << std::endl;

  return 0;
}
