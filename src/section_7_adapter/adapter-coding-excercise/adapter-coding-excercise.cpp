/**
 *    @file adapter-coding-excercise .cpp
 *    @brief Singleton Coding Exercise
 *    @brief
 *    @brief Adapter Coding Exercise
 *    @brief Here's a very synthetic example for you to try.
 *    @brief
 *    @brief You are given a Rectangle protocol and an extension method on it.
 *    @brief Try to define a SquareToRectangleAdapter that adapts the Square  to the Rectangle
 * interface.
 *    @author rouxfederico@gmail.com
 */

#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep

struct Square {
    int side{0};
    explicit Square(const int side) : side(side) {}
};

struct Rectangle {
    virtual ~Rectangle() = default;
    Rectangle() = default;
    Rectangle(const Rectangle& other) = default;
    Rectangle& operator=(const Rectangle& other) = default;
    Rectangle(Rectangle&& other) = default;
    Rectangle& operator=(Rectangle&& other) = default;

    [[nodiscard]] virtual int width() const = 0;
    [[nodiscard]] virtual int height() const = 0;

    [[nodiscard]] int area() const {
        return width() * height();
    }
};

struct SquareToRectangleAdapter final : Rectangle {
    explicit SquareToRectangleAdapter(const Square& square)
        : width_(square.side), height_(square.side) {}

    int width_;
    int height_;

    [[nodiscard]] int width() const override {
        return width_;
    };
    [[nodiscard]] int height() const override {
        return height_;
    };
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 7:\e[0m Adapter" << std::endl;
    std::cout << "\e[1mCoding Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
    printTitle();
    return 0;
}
