/**
 *    @file flyweight-excercise.cpp
 *    @brief Flyweight Excercise
 *    @brief Flyweight Coding Exercise
 *    @brief You are given a class called Sentence , which takes a string such as "hello world".
 *    @brief You need to provide an interface such that the indexer (operator [] ) returns a
 *    @brief WordToken that can be used to capitalize a particular word in the sentence.
 *    @brief Typical use would be something like:
 *    @brief ~~~C++
 *    @brief Sentence sentence("hello world");
 *    @brief sentence[1].capitalize = true;
 *    @brief std::cout << sentence.str(); // prints "hello WORLD"
 *    @brief ~~~
 *    @author rouxfederico@gmail.com
 */

#include <cctype>   // IWYU pragma: keep
#include <cstddef>  // IWYU pragma: keep
#include <cstdint>  // IWYU pragma: keep
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <memory>     // for allocator_traits<>::value_type
#include <ostream>    // IWYU pragma: keep
#include <sstream>    // IWYU pragma: keep
#include <stdexcept>  // for out_of_range
#include <string>     // IWYU pragma: keep
#include <utility>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

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
        formatting_.emplace_back(TextRange{start, end, false});
        return *formatting_.rbegin();
    }

    friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& text) {
        return os << text.str();
    }

    [[nodiscard]] std::string str() const {
        std::string s;
        for (size_t i = 0; i < plainText_.length(); ++i) {
            char c = plainText_[i];
            for (const auto& range : formatting_) {
                if (range.covers(i)) {
                    c = range.capitalize ? static_cast<char>(std::toupper(c)) : c;
                    break;  // Found matching range, stop searching
                }
            }
            s += c;  // Add character once, after checking all ranges
        }
        return s;
    }

   private:
    std::string plainText_;
    std::vector<TextRange> formatting_;
};

struct Sentence {
   public:
    struct WordToken {
        bool capitalize;
    };

    Sentence(std::string text)
        : betterFormattedText_(std::move(text)),
          wordTokens_(wordCount(betterFormattedText_.str())) {}

    WordToken& operator[](size_t index) {
        if (index >= wordCount(betterFormattedText_.str())) {
            throw std::out_of_range("Index out of range");
        }
        return wordTokens_[index];
    }

    [[nodiscard]] size_t wordCount(const std::string& text) const {
        std::istringstream iss(text);
        std::string word;
        size_t count = 0;
        while (iss >> word) {
            ++count;
        }
        return count;
    }

    [[nodiscard]] size_t getWordStart(size_t index) const {
        std::istringstream iss(betterFormattedText_.str());
        std::string word;
        size_t currentIndex = 0;
        size_t start = 0;

        if (index >= wordCount(betterFormattedText_.str())) {
            return betterFormattedText_.str().length();
        }

        while (iss >> word) {
            if (index == currentIndex) {
                return start;
            }
            start += word.length() + 1;
            ++currentIndex;
        }
        return start;
    }

    [[nodiscard]] size_t getWordEnd(size_t index) const {
        std::istringstream iss(betterFormattedText_.str());
        std::string word;
        size_t currentIndex = 0;
        size_t end = 0;

        while (iss >> word) {
            if (index == currentIndex) {
                return end + word.length();
            }
            end += word.length() + 1;
            ++currentIndex;
        }
        return end;
    }

    [[nodiscard]] std::string str() {
        for (size_t i = 0; i < wordTokens_.size(); ++i) {
            if (wordTokens_[i].capitalize) {
                betterFormattedText_.getRange(getWordStart(i), getWordEnd(i)).capitalize = true;
            }
        }
        return betterFormattedText_.str();
    }

   private:
    BetterFormattedText betterFormattedText_;
    std::vector<WordToken> wordTokens_;
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 12 :\e[0m Flyweight" << std::endl;
    std::cout << "\e[1mFlyweight Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Flyweight Excercise
 */

int main() {
    printTitle();

    Sentence sentence("hello world");
    sentence[1].capitalize = true;
    std::cout << sentence.str() << std::endl;  // prints "hello WORLD"

    return 0;
}
