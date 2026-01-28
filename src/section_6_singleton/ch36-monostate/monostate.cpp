/**
 *    @file monostate .cpp
 *    @brief Chapter 36: Monostate
 *    @author rouxfederico@gmail.com
 */

#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep

class Printer {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static int id;

   public:
    [[nodiscard]] int getId() const {
        return id;
    }
    void setId(const int val) {
        id = val;
    }
};
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
int Printer::id = 0;

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
    std::cout << "\e[1mChapter 36:\e[0m Monostate" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    printTitle();
    const int magicNumber = 6;

    Printer p0, p1;

    p1.setId(magicNumber);
    std::cout << "p0::id: " << p0.getId() << "\n";

    return 0;
}
