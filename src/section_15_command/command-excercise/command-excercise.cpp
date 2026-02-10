/**
 *    @file command-excercise.cpp
 *    @brief Command Coding Exercise
 *    @brief Implement the `Account::process()` function to process different account commands. The
 * rules are obvious:
 *    @brief `success`: indicates whether the operation was successful
 *    @brief You can only withdraw money if you have enough in your account
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

struct Command {
    enum Action { deposit, withdraw } action;
    int amount{0};
    bool success{false};

    Command(Action action, int amount) : action(action), amount(amount) {}
};

struct Account {
    int balance{0};
    void process(Command& cmd) {
        switch (cmd.action) {
            case Command::Action::deposit:
                balance += cmd.amount;
                cmd.success = true;
                break;
            case Command::Action::withdraw:
                if (balance - cmd.amount >= 0) {
                    balance -= cmd.amount;
                    cmd.success = true;
                } else {
                    cmd.success = false;
                }
                break;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << "Balance: " << account.balance << std::endl;
        return os;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 15 :\e[0m Command" << std::endl;
    std::cout << "\e[1mCommand Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static const int depositAmount = 100;
    static const int withdrawAmount = 50;

    Account account;
    Command cmd{Command::Action::deposit, depositAmount};
    account.process(cmd);
    std::cout << account << std::endl;

    cmd.action = Command::Action::withdraw;
    cmd.amount = withdrawAmount;
    account.process(cmd);
    std::cout << account << std::endl;
    return 0;
}
