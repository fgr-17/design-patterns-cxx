/**
 *    @file composite-command-macro.cpp
 *    @brief ch-80 Composite Command Macro
 *    @author rouxfederico@gmail.com
 */

#include <initializer_list>
#include <iostream>
#include <vector>

struct BankAccount {
    int balance{0};

    void deposit(unsigned int amount) {
        balance += static_cast<int>(amount);
        std::cout << "Deposited " << amount << " - balance: " << balance << std::endl;
    }

    bool withdraw(unsigned int amount) {
        if (balance - static_cast<int>(amount) >= overdraftLimit) {
            balance -= static_cast<int>(amount);
            std::cout << "Withdrew " << amount << " - balance: " << balance << std::endl;
            return true;
        }
        std::cout << "Withdraw failed - balance: " << balance << std::endl;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Balance: " << account.balance << std::endl;
        return os;
    }

   private:
    static constexpr int overdraftLimit = -500;
};

struct Command {
    bool succeeded{false};

    Command() = default;
    Command(bool succeeded) : succeeded(succeeded) {}

    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand final : Command {
    BankAccount& account;
    enum Action { DEPOSIT, WITHDRAW } action;
    unsigned int amount;

    BankAccountCommand(BankAccount& account, Action action, unsigned int amount)
        : Command(false), account(account), action(action), amount(amount) {}

    void call() override {
        switch (action) {
            case Action::DEPOSIT:
                account.deposit(amount);
                succeeded = true;
                break;
            case Action::WITHDRAW:
                succeeded = account.withdraw(amount);
                break;
        }
    }

    void undo() override {
        if (!succeeded) return;

        switch (action) {
            case Action::DEPOSIT:
                account.withdraw(amount);
                break;
            case Action::WITHDRAW:
                account.deposit(amount);
                break;
        }
    }
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command {
    CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand>& commands)
        : std::vector<BankAccountCommand>(commands) {}

    void call() override {
        for (auto& cmd : *this) {
            cmd.call();
        }
    }

    void undo() override {
        for (auto it = rbegin(); it != rend(); ++it) {
            it->undo();
        }
    };
};

struct DependentCompositeCommand : CompositeBankAccountCommand {
    DependentCompositeCommand(const std::initializer_list<BankAccountCommand>& commands)
        : CompositeBankAccountCommand(commands) {}

    void call() override {
        bool ok = true;
        for (auto& cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded;
            } else {
                cmd.succeeded = false;
            }
        }
    };
};

struct MoneyTransferCommand : DependentCompositeCommand {
    MoneyTransferCommand(BankAccount& from, BankAccount& to, unsigned int amount)
        : DependentCompositeCommand{
              BankAccountCommand{from, BankAccountCommand::Action::WITHDRAW, amount},
              BankAccountCommand{to, BankAccountCommand::Action::DEPOSIT, amount},
          } {}
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 15 :\e[0m Command" << std::endl;
    std::cout << "\e[1mChapter 80 : Composite Command Macro\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static const unsigned int amount = 100;
    static const unsigned int amount2 = 1000;
    BankAccount ba1, ba2;
    std::cout << "ba1: ";
    ba1.deposit(amount);

    MoneyTransferCommand mtc{ba1, ba2, amount / 2};
    mtc.call();
    std::cout << "ba1: " << ba1 << std::endl;
    std::cout << "ba2: " << ba2 << std::endl;

    mtc.undo();
    std::cout << "ba1: " << ba1 << std::endl;
    std::cout << "ba2: " << ba2 << std::endl;

    MoneyTransferCommand mtc2{ba2, ba1, amount2};
    mtc2.call();
    std::cout << "ba1: " << ba1 << std::endl;
    std::cout << "ba2: " << ba2 << std::endl;

    mtc2.undo();
    std::cout << "ba1: " << ba1 << std::endl;
    std::cout << "ba2: " << ba2 << std::endl;

    return 0;
}
