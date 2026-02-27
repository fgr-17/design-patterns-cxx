/**
 *    @file multiton .cpp
 *    @brief Chapter 37: Multiton
 *    @author rouxfederico@gmail.com
 */

#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <map>
#include <memory>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>

class Printer;

enum class Importance { primary, secondary, tertiary };

template <typename T, typename Key = std::string>
class Multiton {
   public:
    static std::shared_ptr<T> get(const Key& key) {
        if (const auto it = instances.find(key); it != instances.end()) {
            return it->second;
        }
        auto instance = std::make_shared<T>();
        instances[key] = instance;
        return instance;
    }

    Multiton(const Multiton&) = delete;
    Multiton& operator=(const Multiton&) = delete;
    Multiton(Multiton&&) = delete;
    Multiton& operator=(Multiton&&) = delete;

   protected:
    Multiton() = default;
    ~Multiton() = default;

   private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static std::map<Key, std::shared_ptr<T>> instances;
};

template <typename T, typename Key>
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class Printer {
   public:
    Printer() {
        std::cout << "A total of " << ++totalInstanceCount << " instances created so far\n";
    }

   private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static int totalInstanceCount;
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
int Printer::totalInstanceCount = 0;

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
    std::cout << "\e[1mChapter 37:\e[0m Multiton" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    using mt = Multiton<Printer, Importance>;

    printTitle();

    auto main = mt::get(Importance::primary);
    auto sec = mt::get(Importance::secondary);
    auto sec2 = mt::get(Importance::secondary);

    return 0;
}
