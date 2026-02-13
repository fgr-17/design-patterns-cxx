/**
 *    @file interpreter-excercise.cpp
 *    @brief Interpreter Coding Exercise
 *    @brief You are asked to write an expression processor for simple numeric expressions with the
 *    @brief following constraints:
 *    @brief * Expressions use integral values (e.g., "13" ), single-letter variables defined in
 *    @brief variables , as well as + and - operators only
 *    @brief * There is no need to support braces or any other operations
 *    @brief * If a variable is not found in Variables  (or if we encounter a variable with >1
 *    @brief letter, e.g. ab), the evaluator returns 0 (zero)
 *    @brief * In case of any parsing failure, evaluator returns 0
 *    @brief Example:
 *    @brief `calculate("1+2+3")`  should return 6
 *    @brief `calculate("1+2+xy")`  should return 0
 *    @brief `calculate("10-2-x")`  when x=3 is in variables should return 5
 *    @author rouxfederico@gmail.com
 */

#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <span>
#include <sstream>  // IWYU pragma: keep
#include <string>
#include <utility>
#include <vector>

struct Token {
    enum class Type { integer, plus, minus, variable } type;
    std::string text;

    Token(Type type, std::string text) : type(type), text(std::move(text)) {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "[" << token.text << "]";
        return os;
    }
};

struct Element {
    [[nodiscard]] virtual int eval() const = 0;
    Element() = default;
    Element(const Element&) = delete;
    Element(Element&&) = delete;
    Element& operator=(const Element&) = delete;
    Element& operator=(Element&&) = delete;
    virtual ~Element() = default;
};

struct Integer : Element {
    int value;
    Integer(int value) : value(value) {}

    [[nodiscard]] int eval() const override {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Integer& integer) {
        os << integer.value;
        return os;
    }
};

struct BinaryOperation : Element {
    enum class Type { addition, subtraction } type{Type::addition};
    std::shared_ptr<Element> lhs{nullptr}, rhs{nullptr};

    [[nodiscard]] int eval() const override {
        switch (type) {
            case Type::addition:
                return lhs->eval() + rhs->eval();
            case Type::subtraction:
                return lhs->eval() - rhs->eval();
        }
        return 0;
    }

    [[nodiscard]] bool hasLhs() const {
        return lhs != nullptr;
    }

    [[nodiscard]] bool hasRhs() const {
        return rhs != nullptr;
    }

    [[nodiscard]] bool isCompleted() const {
        return hasLhs() && hasRhs();
    }

    void cleanRhs() {
        rhs.reset();
    }

    [[nodiscard]] std::string typeToString() const {
        switch (type) {
            case Type::addition:
                return "+";
            case Type::subtraction:
                return "-";
        }
        return "";
    }

    friend std::ostream& operator<<(std::ostream& os, const BinaryOperation& operation) {
        int l = operation.lhs ? operation.lhs->eval() : 0;
        int r = operation.rhs ? operation.rhs->eval() : 0;
        os << "(" << l << " " << operation.typeToString() << " " << r << ")";
        return os;
    }
};

struct Expression : std::vector<Token> {
    Expression() = default;
    Expression(const std::string& input) {
        lex(input);
    }

    void lex(const std::string& input) {
        bool lastTokenWasVariable = false;
        for (int i = 0; i < static_cast<int>(input.size()); i++) {
            switch (input[i]) {
                case '+':
                    this->emplace_back(Token::Type::plus, "+");
                    lastTokenWasVariable = false;
                    break;
                case '-':
                    this->emplace_back(Token::Type::minus, "-");
                    lastTokenWasVariable = false;
                    break;
                case 'a' ... 'z':
                    if (lastTokenWasVariable) {
                        isValid_ = false;
                        break;
                    } else {
                        this->emplace_back(Token::Type::variable, std::string(1, input[i]));
                        lastTokenWasVariable = true;
                        break;
                    }
                default: {
                    lastTokenWasVariable = false;
                    std::ostringstream buf;
                    for (int j = i; j < static_cast<int>(input.size()); j++) {
                        if (isdigit(input[j])) {
                            buf << input[j];
                            ++i;
                        } else {
                            break;
                        }
                    }
                    if (!buf.str().empty()) {
                        this->emplace_back(Token::Type::integer, buf.str());
                        i--;
                    }
                }
            }
        }
    }

    [[nodiscard]] int eval(const std::map<char, int>& variables) const {
        auto expression = std::make_unique<BinaryOperation>();
        bool haveLhs = false;
        for (const auto& token : *this) {
            switch (token.type) {
                case Token::Type::integer: {
                    int value = std::stoi(token.text);
                    auto integer = std::make_shared<Integer>(value);
                    if (!haveLhs) {
                        expression->lhs = integer;
                        haveLhs = true;
                    } else {
                        expression->rhs = integer;
                    }
                    break;
                }
                case Token::Type::plus:
                    expression->type = BinaryOperation::Type::addition;
                    break;
                case Token::Type::minus:
                    expression->type = BinaryOperation::Type::subtraction;
                    break;
                case Token::Type::variable: {
                    int value = 0;
                    if (variables.find(token.text[0]) != variables.end()) {
                        value = variables.at(token.text[0]);
                    } else {
                        return 0;
                    }
                    auto variable = std::make_shared<Integer>(value);
                    if (!haveLhs) {
                        expression->lhs = variable;
                        haveLhs = true;
                    } else {
                        expression->rhs = variable;
                    }
                    break;
                }
            }
            if (expression->isCompleted()) {
                auto ret = expression->eval();
                std::cout << "partial result: " << *expression << " = " << ret << std::endl;
                expression->cleanRhs();
                expression->lhs = std::make_shared<Integer>(ret);
            }
        }
        if (expression->lhs && !expression->rhs) {
            return expression->lhs->eval();  // collapsed to single value
        }
        return expression->eval();
    }

    friend std::ostream& operator<<(std::ostream& os, const Expression& expression) {
        if (expression.isValid_) {
            for (const auto& token : expression) {
                os << token;
            }
        } else {
            os << "Invalid expression" << std::endl;
        }
        return os;
    }

    [[nodiscard]] bool isValid() const {
        return isValid_;
    }

   private:
    bool isValid_{true};
};

struct ExpressionProcessor {
    std::map<char, int> variables = {{'a', 4}, {'b', 0}};

    int calculate(const std::string& expression) {
        Expression expr(expression);
        if (!expr.isValid()) {
            return 0;
        }
        return expr.eval(variables);
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 16 :\e[0m Interpreter" << std::endl;
    std::cout << "\e[1mInterpreter Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    printTitle();

    auto args = std::span(argv, static_cast<size_t>(argc));
    if (args.size() < 2) {
        std::cout << "Usage: " << args[0] << " <expression>" << std::endl;
        return 1;
    }
    std::string expression = args[1];
    ExpressionProcessor exprProcessor;
    std::cout << "result: " << exprProcessor.calculate(expression) << std::endl;
    return 0;
}
