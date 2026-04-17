/**
 *    @file main.cpp
 *    @brief ch-127 Variant std::visit
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <variant>

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 127 : Variant and std::visit\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

// functor approach
struct AddressPrinter {
    void operator()(const std::string &address) const {
        std::cout << "Address called: " << address << std::endl;
    }
    void operator()(const int &address) const {
        std::cout << "Address number: " << address << std::endl;
    }
};

int main() {
    printTitle();

    AddressPrinter printer;
    std::variant<int, std::string> house1 = 1;
    std::variant<int, std::string> house2 = "123 Main St";

    std::visit(printer, house1);
    std::visit(printer, house2);

    std::visit(
        [](const auto &address) {
            using T = std::decay_t<decltype(address)>;
            if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "Address called: " << address << std::endl;
            } else {
                std::cout << "Address number: " << address << std::endl;
            }
        },
        house1);

    return 0;
}
