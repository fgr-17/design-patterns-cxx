/**
 *    @file geometric-shapes.cpp
 *    @brief Geometric shapes - example on composition
 *    @author rouxfederico@gmail.com
 */

#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>   // for string
#include <utility>  // for move
#include <vector>

struct GraphicObject {
    virtual void draw() const = 0;
};

struct Circle : GraphicObject {
    void draw() const override {
        std::cout << "Circle" << std::endl;
    }
};

struct Group : GraphicObject {
    std::string name;
    std::vector<GraphicObject*> objects;

    explicit Group(const std::string name) : name(std::move(name)) {}

    void draw() const override {
        std::cout << "Group " << name.c_str() << " contains: " << std::endl;
        for (const auto& o : objects) {
            o->draw();
        }
    }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 9:\e[0m Composition" << std::endl;
    std::cout << "\e[1mCH49: Geometric shapes\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
    Circle c1, c2;
    Group g{"root"};
    Group sg("subgroup");
    printTitle();

    c1.draw();
    c2.draw();

    g.objects.push_back(&c1);
    g.draw();

    sg.objects.push_back(&c2);
    g.objects.push_back(&sg);
    sg.draw();
    g.draw();

    return 0;
}
