/**
 *    @file builder.cpp
 *    @brief Chapter 13: Fluent builders
 *    @brief adding fluency to builders
 *    @author rouxfederico@gmail.com
 *
 */

#include <array>
#include <cstdio>
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <memory>
#include <sstream>  // IWYU pragma: keep
#include <string>
#include <utility>
#include <vector>

// forward declaration due to cross ref
class HtmlBuilder;

/**
 *   @struct HtmlElement
 *   @brief Html builder
 */
// struct HtmlElement{
// avoid exposing the constructor to users:
//
//

// test.cpp


class HtmlElement {
    friend class HtmlBuilder;
    std::string name_, text_;
    std::vector<HtmlElement> elements_;
    const size_t indentSize_ = 2;

    HtmlElement() = default;
    explicit HtmlElement(const std::string name) : name_(std::move(name)) {}
    HtmlElement(const std::string name, const std::string text) : name_(std::move(name)), text_(std::move(text)) {}

 public:
    [[nodiscard]] std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indentSize_ * indent, ' ');
        oss << i << "<" << name_ << ">" << std::endl;

        if (text_.size() > 0)
            oss << std::string(indentSize_ * (indent + 1), ' ') << text_ << std::endl;

        for (const auto& e : elements_) oss << e.str(indent + 1);

        oss << i << "</" << name_ << ">" << std::endl;
        return oss.str();
    }

    static HtmlBuilder create(std::string root_name);

    static std::unique_ptr<HtmlBuilder> build2(std::string root_name);
};

/**
 * @brief HtmlBuilder
 *
 */

// struct HtmlBuilder{
// adding visibility control to data
class HtmlBuilder {
    HtmlElement root_;

 public:
    explicit HtmlBuilder(std::string root_name) : root_(root_name) {}

    HtmlBuilder& addChild(std::string child_name, std::string child_text) {
        HtmlElement e{child_name, child_text};
        root_.elements_.push_back(e);
        return *this;
    }

    // return pointer instead of ref
    HtmlBuilder* addChild2(std::string child_name, std::string child_text) {
        HtmlElement e{child_name, child_text};
        root_.elements_.push_back(e);
        return this;
    }

    // small method to close the builder process
    HtmlElement build() {
        return root_;
    }

    [[nodiscard]] std::string str() const {
        return root_.str();
    }

    operator HtmlElement() const {
        // returns copy of the op
        // return root;

        return std::move(root_);
    }
};

/**
 * @brief definition of create method outside the class due to cross ref
 *
 * @param root_name
 * @return HtmlBuilder
 */
HtmlBuilder HtmlElement::create(std::string root_name) {
    return HtmlBuilder{root_name};
}

/**
 * @brief another example of builders using unique pointers
 *
 * @param root_name
 * @return HtmlBuilder
 */
std::unique_ptr<HtmlBuilder> HtmlElement::build2(std::string root_name) {
    return std::make_unique<HtmlBuilder>(HtmlBuilder{root_name});
}

/**
 *   @fn main
 *   @brief main program
 */

static int printTitle() {
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 3:\e[0m Builder" << std::endl;
    std::cout << "\e[1mChapter 13:\e[0m Fluent Builder" << std::endl;
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
    for (auto w : words) oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    std::cout << oss.str() << std::endl;

    // OO struct for builder

    HtmlBuilder builder{"ul"};
    builder.addChild("li", "hello").addChild("li", "world");
    std::cout << "without builders: " << std::endl;
    std::cout << builder.str() << std::endl;

    auto builder2 = HtmlElement::create("ul").addChild("li", "hello").addChild("li", "world");
    std::cout << "fluent builder: " << std::endl;
    std::cout << builder2.str() << std::endl;

    HtmlElement builder3 =
        HtmlElement::create("ul").addChild("li", "hello").addChild("li", "world");
    std::cout << "overloading assign operator: " << std::endl;
    std::cout << builder3.str() << std::endl;

    HtmlElement builder4 =
        HtmlElement::create("ul").addChild2("li", "hello")->addChild("li", "world");
    std::cout << "using add child with pointer logic: " << std::endl;
    std::cout << builder4.str() << std::endl;

    auto e = HtmlElement::create("ul").addChild("li", "hello").addChild("li", "world").build();
    std::cout << "using create()...build() seq: " << std::endl;
    std::cout << e.str() << std::endl;

    return 0;
}
