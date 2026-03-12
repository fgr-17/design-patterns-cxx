/**
 *    @file main.cpp
 *    @brief ch-99 Undo and Redo
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <vector>

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

class BankAccount2 {
    int balance_{0};
    std::vector<std::shared_ptr<Memento>> history_;
    int current_{0};

   public:
    BankAccount2(int balance) : balance_(balance) {
        history_.emplace_back(std::make_shared<Memento>(balance_));
    }

    void saveMemento(const std::shared_ptr<Memento>& memento) {
        history_.emplace_back(memento);
        current_++;
    }

    std::shared_ptr<Memento> deposit(int amount) {
        balance_ += amount;
        auto memento = std::make_shared<Memento>(balance_);
        saveMemento(memento);
        return memento;
    }

    void restore(const std::shared_ptr<Memento>& memento) {
        if (memento) {
            balance_ = memento->getBalance();
            saveMemento(memento);
        }
    }

    std::shared_ptr<Memento> undo() {
        if (current_ > 0) {
            current_--;
            auto m = history_[current_];
            balance_ = m->getBalance();
            return m;
        }
        return {};
    }

    std::shared_ptr<Memento> redo() {
        if (current_ + 1 < static_cast<int>(history_.size())) {
            current_++;
            auto m = history_[current_];
            balance_ = m->getBalance();
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount2& account) {
        os << "Balance: " << account.balance_ << std::endl;
        return os;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 19 :\e[0m Memento" << std::endl;
    std::cout << "\e[1mChapter 99 : Undo and Redo\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static constexpr int initialBalance = 100;
    static constexpr int depositAmount = 50;
    static constexpr int depositAmount2 = 25;
    BankAccount2 ba{initialBalance};
    std::cout << "Initial balance: " << ba << std::endl;

    auto m1 = ba.deposit(depositAmount);
    auto m2 = ba.deposit(depositAmount2);
    std::cout << "After deposits [" << depositAmount << ", " << depositAmount2 << "]: " << ba
              << std::endl;

    ba.undo();
    std::cout << "After 1st undo: " << ba << std::endl;

    ba.undo();
    std::cout << "After 2nd undo: " << ba << std::endl;

    ba.redo();
    std::cout << "After redo: " << ba << std::endl;

    return 0;
}
