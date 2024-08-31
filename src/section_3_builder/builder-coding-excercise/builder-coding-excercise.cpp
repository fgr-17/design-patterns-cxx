/**
 *    @file builder.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
// // #include <cstdio>
#include <ostream>   // IWYU pragma: keep
#include <sstream>   // IWYU pragma: keep
// #include <string>
// #include <vector>
// // #include <fstream>
// // #include <tuple>
// // #include <sstream>
// // #include <memory>
// #include <utility>
// #include <initializer_list>
// #include <type_traits>

#include <string>
#include <utility>
#include <vector>

class CodeBuilder {
    using field = std::pair<std::string, std::string>;
    std::vector<field> fields_;
    std::string className_;
 public:
  explicit CodeBuilder(const std::string className) : className_{std::move(className)} {}

  CodeBuilder& addField(const std::string name, const std::string type) {
    fields_.emplace_back(std::make_pair(type, name));
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
      os << "class " << obj.className_ << std::endl;
      os << "{" << std::endl;

      for (auto& field : obj.fields_) {
          os << "  " << field.first << " " << field.second << ";" << std::endl;
      }
      os << "};" << std::endl;
      return os;
  }
};

/**
 *   @fn printTitle
 *   @brief prints chapter name
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mCoding exercise\e[0m" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();
    auto cb = CodeBuilder{"Person"}.addField("name", "string").addField("age", "int");
    std::cout << cb;
    return 0;
}
