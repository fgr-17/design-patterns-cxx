/**
 *    @file main.cpp
 *    @brief ch-122 Intrusive Visitor
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <sstream>

struct Expression {
    virtual ~Expression() = default;
    Expression() = default;
    Expression(const Expression &) = default;
    Expression(Expression &&) = default;
    Expression &operator=(const Expression &) = default;
    Expression &operator=(Expression &&) = default;

    virtual void print(std::ostream &os) const = 0;  // intrusive visitor
};

struct DoubleExpression final : public Expression {
    double value;
    DoubleExpression(double value) : Expression(), value(value) {}

    void print(std::ostream &os) const override {
        os << value;
    }
};

struct AddExpression final : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : Expression(), left(std::move(left)), right(std::move(right)) {}
    ~AddExpression() override = default;
    AddExpression(const AddExpression &) = delete;
    AddExpression(AddExpression &&) = delete;
    AddExpression &operator=(const AddExpression &) = delete;
    AddExpression &operator=(AddExpression &&) = delete;

    void print(std::ostream &os) const override {
        os << "(";
        left->print(os);
        os << " + ";
        right->print(os);
        os << ")";
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 122 : Intrusive Visitor\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    auto expression = std::make_unique<AddExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<AddExpression>(std::make_unique<DoubleExpression>(2),
                                        std::make_unique<DoubleExpression>(3)));

    std::ostringstream oss;
    expression->print(oss);
    std::cout << oss.str() << std::endl;
    return 0;
}
