/**
 *    @file singleton-implementation.cpp
 *    @brief Chapter 32: Singleton Implementation
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <map>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>
#include <utility>


class SingletonDatabase {
 public:
    SingletonDatabase() {
        std::cout << "Initializing db" << std::endl;
        std::ifstream ifs("/workspace/src/section_6_singleton/ch32-singleton-implementation/capitals");

        std::string cityLine, populationLine;

        while (getline(ifs, cityLine)) {
            getline(ifs, populationLine);
            int pop = std::stoi(populationLine);
            capitals[cityLine] = pop;
        }
    }
    std::map<std::string, int> capitals;

    void print() {
        for (auto const&capital : capitals) {
            std::cout << capital.first << ": " << capital.second << std::endl;
        }
    }
};


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mChapter 32:\e[0m Singleton Implementation" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    printTitle();

    SingletonDatabase db;
    db.print();

    return 0;
}
