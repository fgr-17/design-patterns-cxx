/**
 *    @file smart-pointers.cpp
 *    @brief Smart Pointers
 *    @author rouxfederico@gmail.com
 */

#include <cctype>   // IWYU pragma: keep
#include <cstddef>  // IWYU pragma: keep
#include <cstdint>  // IWYU pragma: keep
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <memory>   // IWYU pragma: keep
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep|

struct BankAccount {
    virtual ~BankAccount() = default;

    BankAccount() = default;
    BankAccount(const BankAccount&) = delete;
    BankAccount& operator=(const BankAccount&) = delete;
    BankAccount(BankAccount&&) = delete;
    BankAccount& operator=(BankAccount&&) = delete;

    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount {
   public:
    explicit CurrentAccount(const int balance) : balance_(balance) {}

    void deposit(int amount) override {
        balance_ += amount;
    }

    void withdraw(int amount) override {
        if (amount <= balance_) balance_ -= amount;
    }

    friend std::ostream& operator<<(std::ostream& os, const CurrentAccount& account) {
        os << "CurrentAccount balance: " << account.balance_;
        return os;
    }

   private:
    int balance_;
};
/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 13 :\e[0m Proxy" << std::endl;
    std::cout << "\e[1mSmart Pointers\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Smart Pointers
 */

int main() {
    static constexpr int initialBalance = 100;
    static constexpr int depositAmount = 50;
    static constexpr int withdrawAmount = 20;
    printTitle();

    // @brief using raw pointers
    BankAccount* account = new CurrentAccount(initialBalance);
    account->deposit(depositAmount);
    account->withdraw(withdrawAmount);
    // std::cout << *account << std::endl;
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete account;

    // smart pointers work as a proxy to the raw pointer
    auto b = std::make_shared<CurrentAccount>(initialBalance);
    b->deposit(depositAmount);
    b->withdraw(withdrawAmount);
    std::cout << *b << std::endl;
    [[maybe_unused]] BankAccount* b2 = b.get();

    return 0;
}
