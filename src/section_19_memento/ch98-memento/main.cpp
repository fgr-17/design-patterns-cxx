/**
 *    @file main.cpp
 *    @brief ch-98 Memento
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

class Memento {
   private:
   // memento doesn't expose its internal state for modification
    int balance_{0};

   public:
    Memento(int balance) : balance_(balance) {}

    [[nodiscard]] int getBalance() const {
        return balance_;
    }
};

class BankAccount {
    int balance_{0};

   public:
    BankAccount(int balance) : balance_(balance) {}

    Memento deposit(int amount) {
        balance_ += amount;
        return {balance_};
    }

    void restore(const Memento& memento) {
        balance_ = memento.getBalance();
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Balance: " << account.balance_ << std::endl;
        return os;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 19 :\e[0m Memento" << std::endl;
    std::cout << "\e[1mChapter 98 : Memento\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static constexpr int initialBalance = 100;
    static constexpr int depositAmount = 50;
    static constexpr int depositAmount2 = 25;
    BankAccount account{initialBalance};
    std::cout << account << std::endl;

    auto m1 = account.deposit(depositAmount);
    auto m2 = account.deposit(depositAmount2);
    std::cout << account << std::endl;

    account.restore(m1);
    std::cout << account << std::endl;

    account.restore(m2);
    std::cout << account << std::endl;

    return 0;
}
