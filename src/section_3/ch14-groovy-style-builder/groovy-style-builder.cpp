/**
 *    @file builder.cpp
 *    @brief Chapter 13: Groovy-Style Builders
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
// #include <cstdio>
#include <ostream>   // IWYU pragma: keep
#include <sstream>   // IWYU pragma: keep
#include <string>
#include <vector>
// #include <fstream>
// #include <tuple>
// #include <sstream>
// #include <memory>
#include <utility>
#include <initializer_list>
#include <type_traits>


struct Tag {
    std::string name, text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string> > attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
        os << "<" << tag.name;

        for (const auto& att : tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << std::endl;
        } else {
            os << ">" << std::endl;

            if (tag.text.length())
            os << tag.text << std::endl;

        for (const auto&child : tag.children)
            os << child;

        os << "</" << tag.name << ">" << std::endl;
        }

    return os;
  }

 protected:
    Tag(const std::string name, const std::string text) : name(std::move(name)), text(std::move(text)) {}
    Tag(const std::string name, const std::vector<Tag> children) : name(std::move(name)), children(std::move(children)) {}
};

/**
 * @brief paragraph
 */

struct P : Tag {
    explicit P(const std::string text) : Tag("p", std::move(text)) {}
    P(std::initializer_list<Tag> children) : Tag{"p", std::move(children)} {}
};

struct IMG : Tag {
    explicit IMG(const std::string url) : Tag{"img", ""} {
        attributes.emplace_back(std::make_pair("src", std::move(url)));
    }
};


/**
 *   @fn main
 *   @brief main program
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
  std::cout << "\e[1mChapter 14:\e[0m Groovy-Style Builder" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();

    std::cout <<

        P {
            IMG { "http://image-source.com/image.png"}
        }

        << std::endl;


    return 0;
}
