/**
 *    @file dynamic-decoratorcpp
 *    @brief Dynamic Decorator
 *    @author rouxfederico@gmail.com
 */

#include <cstdint>  // IWYU pragma: keep
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>   // IWYU pragma: keep
#include <utility>

struct Shape {
    [[nodiscard]] virtual std::string str() const = 0;
};

struct Circle : Shape {
    float radius{};

    Circle() = default;
    explicit Circle(float radius) : radius{radius} {}

    void resize(float factor) {
        radius *= factor;
    }

    [[nodiscard]] std::string str() const override {
        std::ostringstream oss;
        oss << "Circle with radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float side{};

    Square() = default;
    explicit Square(float side) : side(side) {}

    void resize(float factor) {
        side *= factor;
    }

    [[nodiscard]] std::string str() const override {
        std::ostringstream oss;
        oss << "Square with side " << side;
        return oss.str();
    }
};

struct ColoredShape : Shape {
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, std::string color) : shape(shape), color(std::move(color)) {}

    [[nodiscard]] std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape {
    Shape& shape;
    uint8_t transparency;
    static constexpr float transparencyFactor = 255.0f;
    static constexpr float transparencyPercentage = 100.0f;

    TransparentShape(Shape& shape, uint8_t transparency)
        : shape(shape), transparency(transparency) {}

    [[nodiscard]] std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the transparency "
            << static_cast<float>(transparency) / transparencyFactor * transparencyPercentage
            << "%";
        return oss.str();
    }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 10 :\e[0m Decorator" << std::endl;
    std::cout << "\e[1mCH54: Dynamic Decorator\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
    printTitle();
    const float factor = 2;
    const float radius = 5;
    const float side = 4;
    const uint8_t transparency = 50;

    Circle circle{radius};
    std::cout << circle.str() << std::endl;
    circle.resize(factor);
    std::cout << circle.str() << std::endl;

    Square square{side};
    std::cout << square.str() << std::endl;
    square.resize(factor);
    std::cout << square.str() << std::endl;

    ColoredShape redCircle{circle, "red"};
    std::cout << redCircle.str() << std::endl;

    ColoredShape blueSquare{square, "blue"};
    std::cout << blueSquare.str() << std::endl;

    // stack decorators
    TransparentShape transparentRedCircle{redCircle, transparency};
    std::cout << transparentRedCircle.str() << std::endl;

    TransparentShape transparentBlueSquare{blueSquare, transparency};
    std::cout << transparentBlueSquare.str() << std::endl;

    // downside of dynamic decorators: need to rewrite APIs for all underlying methods

    return 0;
}
