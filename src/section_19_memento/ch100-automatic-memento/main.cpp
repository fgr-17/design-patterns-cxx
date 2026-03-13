/**
 *    @file main.cpp
 *    @brief ch-100 Automatic Memento
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

class BankAccountMemento {
   private:
    int balance_{0};

   public:
    BankAccountMemento(int balance) : balance_(balance) {}
    ~BankAccountMemento() = default;
    BankAccountMemento(const BankAccountMemento&) = default;
    BankAccountMemento(BankAccountMemento&&) = default;
    BankAccountMemento& operator=(const BankAccountMemento&) = default;
    BankAccountMemento& operator=(BankAccountMemento&&) = default;

    [[nodiscard]] int getBalance() const {
        return balance_;
    }
};

class BankAccount {
    int balance_{0};

   public:
    BankAccount(int balance) : balance_(balance) {}

    BankAccountMemento deposit(int amount) {
        balance_ += amount;
        return {balance_};
    }

    [[nodiscard]] BankAccountMemento getMemento() const {
        return {balance_};
    }

    void restore(const BankAccountMemento& memento) {
        balance_ = memento.getBalance();
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Balance: " << account.balance_ << std::endl;
        return os;
    }
};

struct ScopeToken {
   private:
    BankAccount& account_;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    BankAccountMemento memento_;

   public:
    explicit ScopeToken(BankAccount& account) : account_(account), memento_(account.getMemento()) {}
    ~ScopeToken() {
        account_.restore(memento_);
        std::cout << "Restored balance [memento dtor]" << std::endl;
    }
    ScopeToken(const ScopeToken&) = delete;
    ScopeToken(ScopeToken&&) = delete;
    ScopeToken& operator=(const ScopeToken&) = delete;
    ScopeToken& operator=(ScopeToken&&) = delete;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 19 :\e[0m Memento" << std::endl;
    std::cout << "\e[1mChapter 100 : Automatic Memento\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    static constexpr int initialBalance = 100;
    static constexpr int depositAmount = 50;

    printTitle();

    BankAccount account{initialBalance};
    std::cout << account << std::endl;
    {
        ScopeToken scopeToken{account};

        std::cout << "Depositing " << depositAmount << "..." << std::endl;
        account.deposit(depositAmount);
        std::cout << "After depositing: " << account << std::endl;
    }
    std::cout << "After scope: " << account << std::endl;

    return 0;
}
