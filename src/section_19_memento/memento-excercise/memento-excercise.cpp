/**
 *    @file memento-excercise.cpp
 *    @brief Memento Coding Exercise
 *    @brief A `TokenMachine`  is in charge of keeping tokens. Each `Token`  is a reference type
 *    @brief with a single numerical value.
 *    @brief The machine supports adding tokens and, when it does, it returns a memento
 *    @brief representing the state of that system *at that given* time.
 *    @brief You are asked to fill in the gaps and implement the Memento design pattern for this
 *    @brief scenario. Pay close attention to the situation where a token is fed in as a smart
 *    @brief pointer and its value is subsequently changed on that pointer - you still need to
 *    @brief return the correct system snapshot!
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <vector>

struct Token {
    int value;

    Token(int value) : value(value) {}
};

struct Memento {
    std::vector<std::shared_ptr<Token>> tokens;

    Memento(std::vector<std::shared_ptr<Token>> tokens) : tokens(std::move(tokens)) {}
};

struct TokenMachine {
    std::vector<std::shared_ptr<Token>> tokens;

    Memento addToken(int value) {
        return addToken(std::make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the
    // snapshot of the entire system
    [[nodiscard]] Memento addToken(const std::shared_ptr<Token>& token) {
        tokens.emplace_back(token);

        std::vector<std::shared_ptr<Token>> tokensCopy;

        tokensCopy.reserve(tokens.size());
        for (const auto& token : tokens) {
            tokensCopy.emplace_back(std::make_shared<Token>(token->value));
        }
        return {tokensCopy};
    }

    // reverts the system to a state represented by the token
    void revert(const Memento& m) {
        tokens.clear();
        tokens = m.tokens;
    }

    friend std::ostream& operator<<(std::ostream& os, const TokenMachine& tokenMachine) {
        os << "Tokens: ";
        for (const auto& token : tokenMachine.tokens) {
            os << token->value << " ";
        }
        os << std::endl;
        return os;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 19 :\e[0m Memento" << std::endl;
    std::cout << "\e[1mMemento Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    auto t1 = std::make_shared<Token>(1);
    auto t2 = std::make_shared<Token>(2);
    auto t3 = std::make_shared<Token>(3);

    TokenMachine tokenMachine;
    auto m1 = tokenMachine.addToken(t1);
    auto m2 = tokenMachine.addToken(t2);
    auto m3 = tokenMachine.addToken(t3);

    std::cout << "tokenMachine: " << tokenMachine << std::endl;

    tokenMachine.revert(m1);
    std::cout << "tokenMachine: " << tokenMachine << std::endl;

    t1->value = 4;
    std::cout << "tokenMachine: " << tokenMachine << std::endl;

    return 0;
}
