/**
 *    @file handmade-interpreter-lexing.cpp
 *    @brief ch-83 Handmade Interpreter Lexing
 *    @author rouxfederico@gmail.com
 */

#include <cctype>
#include <iostream>
#include <sstream>  // IWYU pragma: keep
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

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 16 :\e[0m Interpreter" << std::endl;
    std::cout << "\e[1mChapter 83 : Handmade Interpreter - Lexing\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    std::string input = "((1+2)+33+(11+654))";
    auto tokens = lex(input);
    for (const auto& token : tokens) {
        std::cout << token;
    }
    std::cout << std::endl;
    return 0;
}
