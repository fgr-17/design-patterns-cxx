/**
 *    @file visitor-excercise.cpp
 *    @brief Visitor Coding Exercise
 *    @brief You are asked to implement a double-dispatch visitor called ExpressionPrinter  for
 *    @brief printing different mathematical expressions. The range of expressions covers addition
 *    @brief and multiplication - please put round brackets around addition but not around
 *    @brief multiplication! Also, please avoid any blank spaces in output.
 *    @brief Example:
 *    @brief Input: `AdditionExpression{Literal{2}, Literal{3}}`  -- btw, this is pseudocode, you
 *    @brief cannot inline those references unfortunately
 *    @brief Output: (2+3)
 *    @brief Here is the corresponding unit test:
 *    @brief Value v2{2};
 *    @brief Value v3{3};
 *    @brief AdditionExpression simple{v2,v3};
 *    @brief ExpressionPrinter ep;
 *    @brief ep.accept(simple);
 *    @brief ASSERT_EQ("(2+3)", ep.str());
 *    @author rouxfederico@gmail.com
 */

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor {
    virtual ~ExpressionVisitor() = default;
    ExpressionVisitor() = default;
    ExpressionVisitor(const ExpressionVisitor &) = default;
    ExpressionVisitor(ExpressionVisitor &&) = default;
    ExpressionVisitor &operator=(const ExpressionVisitor &) = default;
    ExpressionVisitor &operator=(ExpressionVisitor &&) = default;

    virtual void accept(const Value &expression) = 0;
    virtual void accept(const AdditionExpression &expression) = 0;
    virtual void accept(const MultiplicationExpression &expression) = 0;
};

struct Expression {
    virtual void visit(ExpressionVisitor &visitor) = 0;

    virtual ~Expression() = default;
    Expression() = default;
    Expression(const Expression &) = default;
    Expression(Expression &&) = default;
    Expression &operator=(const Expression &) = default;
    Expression &operator=(Expression &&) = default;
};

struct Value final : Expression {
    int value;

    Value(int value) : value(value) {}

    void visit(ExpressionVisitor &visitor) override {
        visitor.accept(*this);
    }
};

struct AdditionExpression final : Expression {
    Expression &lhs, &rhs;  // NOLINT

    AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor &visitor) override {
        visitor.accept(*this);
    }
};

struct MultiplicationExpression final : Expression {
    Expression &lhs, &rhs;  // NOLINT

    MultiplicationExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor &visitor) override {
        visitor.accept(*this);
    }
};

struct ExpressionPrinter : ExpressionVisitor {
    std::ostringstream oss_;

    [[nodiscard]] std::string str() const {
        return oss_.str();
    }

    void accept(const Value &expression) override {
        oss_ << expression.value;
    }

    void accept(const AdditionExpression &expression) override {
        oss_ << "(";
        expression.lhs.visit(*this);
        oss_ << "+";
        expression.rhs.visit(*this);
        oss_ << ")";
    }
    void accept(const MultiplicationExpression &expression) override {
        expression.lhs.visit(*this);
        oss_ << "*";
        expression.rhs.visit(*this);
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mVisitor Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Value v2{2};
    Value v3{3};
    AdditionExpression simple{v2, v3};
    ExpressionPrinter ep;
    ep.accept(simple);
    EXPECT_EQ("(2+3)", ep.str());
    return 0;
}
