/**
 *    @file command.cpp
 *    @brief ch-78 Command
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <vector>

struct BankAccount {
    int balance{0};

    void deposit(unsigned int amount) {
        balance += static_cast<int>(amount);
        std::cout << "Deposited " << amount << " - balance: " << balance << std::endl;
    }

    void withdraw(unsigned int amount) {
        if (balance - static_cast<int>(amount) >= overdraftLimit) {
            balance -= static_cast<int>(amount);
        }
        std::cout << "Withdrew " << amount << " - balance: " << balance << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Balance: " << account.balance << std::endl;
        return os;
    }

   private:
    static constexpr int overdraftLimit = -500;
};

struct Command {
    virtual void call() = 0;
    virtual ~Command() = default;
    Command() = default;
    Command(const Command&) = default;
    Command(Command&&) = default;
    Command& operator=(const Command&) = default;
    Command& operator=(Command&&) = default;
};

struct BankAccountCommand final : Command {
    BankAccount& account;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    enum Action { DEPOSIT, WITHDRAW } action;
    unsigned int amount;

    BankAccountCommand(BankAccount& account, Action action, unsigned int amount)
        : Command(), account(account), action(action), amount(amount) {}

    void call() override {
        switch (action) {
            case Action::DEPOSIT:
                account.deposit(amount);
                break;
            case Action::WITHDRAW:
                account.withdraw(amount);
                break;
        }
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 15 :\e[0m Command" << std::endl;
    std::cout << "\e[1mChapter 78 : Command\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    const unsigned int depositAmount = 100;
    const unsigned int withdrawAmount = 50;

    BankAccount account;
    BankAccountCommand deposit{account, BankAccountCommand::Action::DEPOSIT, depositAmount};
    BankAccountCommand withdraw{account, BankAccountCommand::Action::WITHDRAW, withdrawAmount};

    deposit.call();
    withdraw.call();

    std::vector<BankAccountCommand> cmds{
        BankAccountCommand{account, BankAccountCommand::Action::DEPOSIT, depositAmount},
        BankAccountCommand{account, BankAccountCommand::Action::WITHDRAW, withdrawAmount},
    };
    for (auto& cmd : cmds) {
        cmd.call();
    }

    return 0;
}
