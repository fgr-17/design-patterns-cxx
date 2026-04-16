/**
 *    @file main.cpp
 *    @brief ch-123 Reflective Visitor
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
};

struct DoubleExpression final : public Expression {
    double value;
    DoubleExpression(double value) : Expression(), value(value) {}
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
};

/**
 * @brief ExpressionPrinter is a reflective visitor
 *
 * @details Moving the logic of printing the expression to a separate class.
 */

class ExpressionPrinter {
   private:
    std::ostringstream oss_;

   public:
    std::string str() const {
        return oss_.str();
    }

    void print(const Expression &expression) {
        if (auto de = dynamic_cast<const DoubleExpression *>(&expression)) {
            print(*de);
        } else if (auto ae = dynamic_cast<const AddExpression *>(&expression)) {
            print(*ae);
        }
    }

    void print(const DoubleExpression &expression) {
        oss_ << expression.value;
    }

    void print(const AddExpression &expression) {
        oss_ << "(";
        print(*expression.left);
        oss_ << " + ";
        print(*expression.right);
        oss_ << ")";
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 123 : Reflective Visitor\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    auto expression = std::make_unique<AddExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<AddExpression>(std::make_unique<DoubleExpression>(2),
                                        std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter printer;
    printer.print(*expression);
    std::cout << printer.str() << std::endl;
    return 0;
}
