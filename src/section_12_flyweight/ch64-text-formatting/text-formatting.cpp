/**
 *    @file text-formatting.cpp
 *    @brief Text Formatting
 *    @author rouxfederico@gmail.com
 */

#include <cctype>   // IWYU pragma: keep
#include <cstddef>  // IWYU pragma: keep
#include <cstdint>  // IWYU pragma: keep
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

class FormattedText {
    std::string plainText_;
    /* @brief inefficient way to store the capitalization state */
    std::vector<bool> caps_;

   public:
    FormattedText(std::string plainText) : plainText_(std::move(plainText)) {
        caps_ = std::vector<bool>(plainText_.length(), false);
    }

    void capitalize(size_t start, size_t end) {
        for (size_t i = start; i <= end; ++i) {
            caps_.at(i) = true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const FormattedText& text) {
        std::string s;
        for (size_t i = 0; i < text.plainText_.length(); ++i) {
            char c = text.plainText_[i];
            s += text.caps_[i] ? static_cast<char>(std::toupper(static_cast<unsigned char>(c))) : c;
        }
        return os << s;
    }
};

class BetterFormattedText {
   public:
    struct TextRange {
        size_t start, end;
        bool capitalize;

        [[nodiscard]] bool covers(size_t position) const {
            return position >= start && position <= end;
        }
    };

    BetterFormattedText(std::string plainText) : plainText_(std::move(plainText)) {}

    [[nodiscard]] TextRange& getRange(size_t start, size_t end) {
        formatting_.emplace_back(TextRange{.start = start, .end = end, .capitalize = false});
        return *formatting_.rbegin();
    }

    friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& text) {
        std::string s;
        for (size_t i = 0; i < text.plainText_.length(); ++i) {
            char c = text.plainText_[i];
            for (auto& range : text.formatting_) {
                if (range.covers(i)) {
                    s += range.capitalize
                             ? static_cast<char>(std::toupper(static_cast<unsigned char>(c)))
                             : c;
                } else {
                    s += c;
                }
            }
        }
        return os << s;
    }

   private:
    std::string plainText_;
    std::vector<TextRange> formatting_;
};
/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 12 :\e[0m Flyweight" << std::endl;
    std::cout << "\e[1mChapter 64: Text Formatting\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Text Formatting
 */

int main() {
    static constexpr size_t start = 5;
    static constexpr size_t end = 6;
    printTitle();

    FormattedText ft("This is a test");
    ft.capitalize(start, end);
    std::cout << ft << std::endl;

    BetterFormattedText bft("This is a test");
    bft.getRange(start, end).capitalize = true;
    std::cout << bft << std::endl;

    return 0;
}
