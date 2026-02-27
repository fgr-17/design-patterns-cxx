/**
 *    @file undo-operations.cpp
 *    @brief ch-79 Undo Operations
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
    virtual ~Command() = default;
    Command(const Command&) = default;
    Command(Command&&) = default;
    Command& operator=(const Command&) = default;
    Command& operator=(Command&&) = default;
    Command(bool succeeded) : succeeded(succeeded) {}

    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand final : Command {
    BankAccount& account;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
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

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 15 :\e[0m Command" << std::endl;
    std::cout << "\e[1mChapter 79 : Undo Operations\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    const unsigned int depositAmount = 100;
    const unsigned int withdrawAmount = 200;

    std::cout << "=== First example ===" << std::endl;
    {
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
    }
    std::cout << "=== Second example ===" << std::endl;
    {
        BankAccount account;
        std::vector<BankAccountCommand> cmds{
            BankAccountCommand{account, BankAccountCommand::Action::DEPOSIT, depositAmount},
            BankAccountCommand{account, BankAccountCommand::Action::WITHDRAW, withdrawAmount},
        };
        for (auto& cmd : cmds) {
            cmd.call();
        }

        // for (auto it = cmds.rbegin(); it != cmds.rend(); ++it) {
        //     it->undo();
        // }

        for (auto cmd : cmds) {
            cmd.undo();
        }

        std::cout << account << std::endl;
    }
    return 0;
}
