/**
 *    @file main.cpp
 *    @brief ch-125 Acyclic Visitor
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <sstream>

template <typename Visitable>
struct Visitor {
    virtual void visit(Visitable &visitable) = 0;
    Visitor() = default;
    Visitor(const Visitor &) = default;
    Visitor(Visitor &&) = default;
    Visitor &operator=(const Visitor &) = default;
    Visitor &operator=(Visitor &&) = default;
    virtual ~Visitor() = default;
};

struct VisitorBase {
    virtual ~VisitorBase() = default;
    VisitorBase() = default;
    VisitorBase(const VisitorBase &) = default;
    VisitorBase(VisitorBase &&) = default;
    VisitorBase &operator=(const VisitorBase &) = default;
    VisitorBase &operator=(VisitorBase &&) = default;
};

struct Expression {
    virtual ~Expression() = default;
    Expression() = default;
    Expression(const Expression &) = default;
    Expression(Expression &&) = default;
    Expression &operator=(const Expression &) = default;
    Expression &operator=(Expression &&) = default;

    virtual void accept(VisitorBase &visitor) {
        if (auto ev = dynamic_cast<Visitor<Expression> *>(&visitor)) {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression final : public Expression {
    double value;
    DoubleExpression(double value) : Expression(), value(value) {}
    void accept(VisitorBase &visitor) override {
        if (auto ev = dynamic_cast<Visitor<DoubleExpression> *>(&visitor)) {
            ev->visit(*this);
        }
    }
};

struct AddExpression final : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : Expression(), left(std::move(left)), right(std::move(right)) {}
    void accept(VisitorBase &visitor) override {
        if (auto ev = dynamic_cast<Visitor<AddExpression> *>(&visitor)) {
            ev->visit(*this);
        }
    }
};

struct ExpressionPrinter final : public VisitorBase,
                                //  Visitor<DoubleExpression>,
                                 Visitor<AddExpression> {
    void visit(DoubleExpression &expression) override {
        oss_ << expression.value;
    }
    void visit(AddExpression &expression) override {
        oss_ << "(";
        expression.left->accept(*this);
        oss_ << " + ";
        expression.right->accept(*this);
        oss_ << ")";
    }

    [[nodiscard]] std::string str() const {
        return oss_.str();
    }

   private:
    std::ostringstream oss_;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 125 : Acyclic Visitor\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    auto e = std::make_unique<AddExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<AddExpression>(std::make_unique<DoubleExpression>(2),
                                        std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter printer;
    printer.visit(*e);
    std::cout << printer.str() << std::endl;
    return 0;
}
