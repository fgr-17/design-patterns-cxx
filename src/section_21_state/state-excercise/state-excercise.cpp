/**
 *    @file state-excercise.cpp
 *    @brief SState Coding Exercise
 *    @brief A combination lock is a lock that opens after the right digits have been entered. A
 *    @brief lock is preprogrammed with a combination (e.g., 12345) and the user is expected to
 *    @brief enter this combination to unlock the lock.
 *    @brief The lock has a status  field that indicates the state of the lock. The rules are:
 *    @brief    * If the lock has just been locked (or at startup), the status is LOCKED.
 *    @brief    * If a digit has been entered, that digit is shown on the screen. As the user enters
 *    @brief more digits, they are added to Status.
 *    @brief    * If the user has entered the correct sequence of digits, the lock status changes to
 *    @brief OPEN.
 *    @brief    * If the user enters an incorrect sequence of digits, the lock status changes to
 *    @brief ERROR.
 *    @brief Please implement the CombinationLock  class to enable this behavior. Be sure to test
 *    @brief both correct and incorrect inputs.
 *    @brief Here is an example unit test for the lock:
 *    @brief ~~~C++
 *    @brief CombinationLock cl({1,2,3});
 *    @brief ASSERT_EQ("LOCKED", cl.status);
 *    @brief cl.enterDigit(1);
 *    @brief ASSERT_EQ("1", cl.status);
 *    @brief cl.enterDigit(2);
 *    @brief ASSERT_EQ("12", cl.status);
 *    @brief cl.enterDigit(3);
 *    @brief ASSERT_EQ("OPEN", cl.status);
 *    @brief ~~~
 *    @author rouxfederico@gmail.com
 */

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

enum class State { LOCKED, OPEN, ERROR };

inline std::ostream& operator<<(std::ostream& os, State state) {
    switch (state) {
        case State::LOCKED:
            return os << "LOCKED";
        case State::OPEN:
            return os << "OPEN";
        case State::ERROR:
            return os << "ERROR";
        default:
            return os << "UNKNOWN";
    }
    return os;
}

class CombinationLock {
   public:
    State state_{State::LOCKED};
    std::string status{"LOCKED"};
    std::vector<int> combination_;

    uint8_t digits_entered_{0};

    CombinationLock(const std::vector<int>& combination) : combination_(combination) {};

    void enterDigit(int digit) {
        std::cout << digit << std::endl;
        switch (state_) {
            case State::LOCKED:
                if (digit == combination_[digits_entered_]) {
                    digits_entered_++;
                    if (digits_entered_ == combination_.size()) {
                        state_ = State::OPEN;
                        status = "OPEN";
                    } else {
                        status.clear();
                        for (size_t i = 0; i < digits_entered_; i++) {
                            status += std::to_string(combination_[i]);
                        }
                    }
                } else {
                    state_ = State::ERROR;
                    status = "ERROR";
                }
                break;

            case State::ERROR:
                status = "ERROR";
                break;
            case State::OPEN:
                status = "OPEN";
                break;
            default:
                status = "UNKNOWN";
                break;
        }
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 21 :\e[0m State" << std::endl;
    std::cout << "\e[1mState Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    CombinationLock cl({1, 2, 3});
    EXPECT_EQ("LOCKED", cl.status);
    cl.enterDigit(1);
    EXPECT_EQ("1", cl.status);
    cl.enterDigit(2);
    EXPECT_EQ("12", cl.status);
    cl.enterDigit(3);
    EXPECT_EQ("OPEN", cl.status);
    return 0;
}
