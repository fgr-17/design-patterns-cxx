/**
 *    @file handmade-interpreter-parsing.cpp
 *    @brief ch-84 Handmade Interpreter Parsing
 *    @author rouxfederico@gmail.com
 */

#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>  // IWYU pragma: keep
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct Token {
    enum class Type { integer, plus, minus, lparen, rparen } type;
    std::string text;

    Token(Type type, std::string text) : type(type), text(std::move(text)) {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "[" << token.text << "]";
        return os;
    }
};

std::vector<Token> lex(const std::string& input) {
    std::vector<Token> tokens;
    for (int i = 0; i < static_cast<int>(input.size()); i++) {
        switch (input[i]) {
            case '+':
                tokens.emplace_back(Token::Type::plus, "+");
                break;
            case '-':
                tokens.emplace_back(Token::Type::minus, "-");
                break;
            case '(':
                tokens.emplace_back(Token::Type::lparen, "(");
                break;
            case ')':
                tokens.emplace_back(Token::Type::rparen, ")");
                break;
            default:
                std::ostringstream buf;
                buf << input[i];
                for (int j = i + 1; j < static_cast<int>(input.size()); j++) {
                    if (isdigit(input[j])) {
                        buf << input[j];
                        ++i;
                    } else {
                        tokens.emplace_back(Token::Type::integer, buf.str());
                        break;
                    }
                }
        }
    }
    return tokens;
}

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
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens) {
    auto expression = std::make_unique<BinaryOperation>();
    bool haveLhs = false;
    for (int i = 0; i < static_cast<int>(tokens.size()); ++i) {
        auto& token = tokens[i];
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
            case Token::Type::lparen: {
                int j = i;
                for (; j < static_cast<int>(tokens.size()); ++j) {
                    if (tokens[j].type == Token::Type::rparen) {
                        break;
                    }
                }
                std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                auto element = parse(subexpression);
                if (!haveLhs) {
                    expression->lhs = element;
                    haveLhs = true;
                } else {
                    expression->rhs = element;
                }
                i = j - 1;
                break;
            }
            case Token::Type::rparen:
                break;
            default:
                std::cout << "Unexpected token: " << token << std::endl;
        }
    }
    return expression;
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 16 :\e[0m Interpreter" << std::endl;
    std::cout << "\e[1mChapter 84 : Handmade Interpreter - Parsing\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    std::string input = "(1+2)+(33+44)";
    auto tokens = lex(input);
    for (const auto& token : tokens) {
        std::cout << token;
    }
    std::cout << std::endl;

    try {
        auto parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
