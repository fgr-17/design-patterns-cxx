/**
 *    @file facade.cpp
 *    @brief Facade
 *    @author rouxfederico@gmail.com
 */


#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>       // IWYU pragma: keep
#include <utility>      // IWYU pragma: keep
#include <vector>
#include <memory>

// Some complex window implementation
class Window {
 public:
    explicit Window(const std::string title, uint8_t columnCount, uint8_t columnWidth, uint8_t charHeight): title_(std::move(title)), columnCount_(columnCount), columnWidth_(columnWidth), charHeight_(charHeight) {}
    void draw() {
      std::cout << "Drawing window" << title_ << " with " << columnCount_ << " columns, " << columnWidth_ << " width and " << charHeight_ << " height" << std::endl;
    }

 private:
  std::string title_;
  uint8_t columnCount_;
  uint8_t columnWidth_;
  uint8_t charHeight_;
};

// facade is a singleton
class Console {
 public:
    static Console& instance() {
      static Console instance;
      return instance;
    }

    Console() = default;
    ~Console() = default;
    Console(const Console&) = delete;
    Console& operator=(const Console&) = delete;
    Console(Console&&) = delete;
    Console& operator=(Console&&) = delete;

    std::vector<std::shared_ptr<Window>> windows_;

    // create APIs to manage the underlying class more confortable
    std::shared_ptr<Window> multicolumn(const std::string& title, uint8_t columnCount, uint8_t columnWidth, uint8_t charHeight) {
      auto window = std::make_shared<Window>(title, columnCount, columnWidth, charHeight);
      for (uint8_t i = 0; i < columnCount; i++) {
        std::cout << "Doing some complex drawing for column " << i << std::endl;
        windows_.push_back(window);
      }
      return window;
    }

 private:
    static constexpr int charWidth = 10, charHeight = 15;
};

/**
 *   @fn printTitle
 *   @brief chapter title 
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 11 :\e[0m Facade" << std::endl;
  std::cout << "\e[1mChapter 59: Facade\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Facade
 */

int main() {
  printTitle();
  Console::instance().multicolumn("Test", 3, 10, 15);
  return 0;
}
