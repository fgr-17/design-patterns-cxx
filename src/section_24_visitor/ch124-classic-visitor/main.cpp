/**
 *    @file main.cpp
 *    @brief ch-123 Reflective Visitor
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <sstream>

struct DoubleExpression;
struct AddExpression;
struct SubExpression;

struct ExpressionVisitor {
    virtual void visit(const DoubleExpression &expression) = 0;
    virtual void visit(const AddExpression &expression) = 0;
    virtual void visit(const SubExpression &expression) = 0;

    ExpressionVisitor() = default;
    ExpressionVisitor(const ExpressionVisitor &) = default;
    ExpressionVisitor(ExpressionVisitor &&) = default;
    ExpressionVisitor &operator=(const ExpressionVisitor &) = default;
    ExpressionVisitor &operator=(ExpressionVisitor &&) = default;
    virtual ~ExpressionVisitor() = default;
};

struct ExpressionPrinter final : public ExpressionVisitor {
    std::ostringstream oss_;
    std::string str() const {
        return oss_.str();
    }
    void visit(const DoubleExpression &expression) override;
    void visit(const AddExpression &expression) override;
    void visit(const SubExpression &expression) override;
};

struct ExpressionEvaluator final : public ExpressionVisitor {
    double result{0};
    void visit(const DoubleExpression &expression) override;
    void visit(const AddExpression &expression) override;
    void visit(const SubExpression &expression) override;
};

struct Expression {
    virtual ~Expression() = default;
    Expression() = default;
    Expression(const Expression &) = default;
    Expression(Expression &&) = default;
    Expression &operator=(const Expression &) = default;
    Expression &operator=(Expression &&) = default;

    virtual void accept(ExpressionVisitor &visitor) = 0;
};

struct DoubleExpression final : public Expression {
    double value;
    DoubleExpression(double value) : Expression(), value(value) {}

    void accept(ExpressionVisitor &visitor) override {
        visitor.visit(*this);
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

    void accept(ExpressionVisitor &visitor) override {
        visitor.visit(*this);
    }
};

struct SubExpression final : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    SubExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : Expression(), left(std::move(left)), right(std::move(right)) {}
    ~SubExpression() override = default;
    SubExpression(const SubExpression &) = delete;
    SubExpression(SubExpression &&) = delete;
    SubExpression &operator=(const SubExpression &) = delete;
    SubExpression &operator=(SubExpression &&) = delete;

    void accept(ExpressionVisitor &visitor) override {
        visitor.visit(*this);
    }
};

void ExpressionPrinter::visit(const DoubleExpression &expression) {
    oss_ << expression.value;
}
void ExpressionPrinter::visit(const AddExpression &expression) {
    bool needBraces = dynamic_cast<const AddExpression *>(expression.right.get()) != nullptr;

    if (needBraces) oss_ << "(";
    expression.left->accept(*this);
    oss_ << " + ";
    expression.right->accept(*this);
    if (needBraces) oss_ << ")";
}

void ExpressionPrinter::visit(const SubExpression &expression) {
    bool needBraces = dynamic_cast<const SubExpression *>(expression.right.get()) != nullptr;

    if (needBraces) oss_ << "(";
    expression.left->accept(*this);
    oss_ << " - ";
    expression.right->accept(*this);
    if (needBraces) oss_ << ")";
}

void ExpressionEvaluator::visit(const DoubleExpression &expression) {
    result = expression.value;
}

void ExpressionEvaluator::visit(const AddExpression &expression) {
    expression.left->accept(*this);
    auto temp = result;
    expression.right->accept(*this);
    result += temp;
}

void ExpressionEvaluator::visit(const SubExpression &expression) {
    expression.left->accept(*this);
    auto temp = result;
    expression.right->accept(*this);
    result = temp - result;
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 124 : Classic Visitor\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    auto e = std::make_unique<AddExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<SubExpression>(std::make_unique<DoubleExpression>(2),
                                        std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter printer;
    printer.visit(*e);

    ExpressionEvaluator evaluator;
    evaluator.visit(*e);
    std::cout << printer.str() << " = " << evaluator.result << std::endl;
    return 0;
}
