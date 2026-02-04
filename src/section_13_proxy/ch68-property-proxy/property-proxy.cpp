/**
 *    @file property-proxy.cpp
 *    @brief Property Proxy
 *    @brief The only visible effect is the log line "assignment - new value: 21" when you assign to
 *    @brief betterStrength / betterAgility. So in this minimal form it’s mostly a demo that the
 *    @brief proxy is invoked.
 *    @brief The advantage appears when you use that hook for something useful, for example:
 *    @brief Validation: e.g. clamp strength to 0–100, reject invalid values.
 *    @brief Observability: notify other parts of the program when a value changes.
 *    @brief Debugging: log or trace all reads/writes.
 *    @brief Persistence / dirty flags: mark the object as changed so it can be saved.
 *    @brief So in this case the advantage is: you get a single, reusable way to run code on every
 *    @brief read/write while keeping the usage syntax as if it were a plain field. The current
 *    @brief program only uses that to log; in a real codebase you'd plug in validation,
 *    @brief notifications, or similar logic there.
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

template <typename T>
struct Property {
    T value_{};

    Property(T value) {
        // @brief this assignment will call the operator=
        *this = value;
    }

    T operator=(T newValue) noexcept {  // NOLINT(cppcoreguidelines-c-copy-assignment-signature)
        std::cout << "assignment - new value: " << newValue << "\n" << std::endl;
        return value_ = newValue;
    }

    operator T() const noexcept {
        return value_;
    }
};

struct Creature {
    int strength{defaultStrength};
    int agility{defaultAgility};

    Property<int> betterStrength{defaultStrength};
    Property<int> betterAgility{defaultAgility};

    [[nodiscard]] int getStrength() const noexcept {
        return betterStrength;
    }

    void setStrength(int value) noexcept {
        betterStrength = value;
    }

    [[nodiscard]] int getAgility() const noexcept {
        return betterAgility;
    }

    void setAgility(int value) noexcept {
        betterAgility = value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature& c) {
        os << "Strength: " << c.betterStrength << ", Agility: " << c.betterAgility;
        return os;
    }

    static constexpr int defaultStrength = 8;
    static constexpr int defaultAgility = 9;
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 13 :\e[0m Proxy" << std::endl;
    std::cout << "\e[1mChapter 68 : Property Proxy\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Property Proxy
 */

int main() {
    static constexpr int strength = 20;
    static constexpr int agility = 21;
    printTitle();

    std::cout << "1. direct manipulation of the attributes" << std::endl;
    Creature c;
    c.betterStrength = strength;
    c.betterAgility = agility;
    std::cout << c << std::endl;

    std::cout << "2. using getters and setters" << std::endl;
    c.setStrength(strength + 1);
    c.setAgility(agility + 1);
    std::cout << c << std::endl;

    std::cout << "3. using property proxies" << std::endl;
    c.betterStrength = strength + 1;
    c.betterAgility = agility + 1;
    std::cout << c << std::endl;
    return 0;
}
