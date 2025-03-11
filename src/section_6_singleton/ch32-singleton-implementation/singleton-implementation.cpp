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
    SingletonDatabase() {
        std::cout << "Initializing db" << std::endl;
        std::ifstream ifs("/workspace/src/section_6_singleton/ch32-singleton-implementation/capitals");

        std::string cityLine, populationLine;

        while (getline(ifs, cityLine)) {
            getline(ifs, populationLine);
            int pop = std::stoi(populationLine);
            capitals_[cityLine] = pop;
        }
    }
    std::map<std::string, int> capitals_;

 public:
    // deleting copy constructor and assignment:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    // for clang-tidy compliance:
    SingletonDatabase(SingletonDatabase&&) = default;
    SingletonDatabase& operator=(SingletonDatabase&&) = default;
    ~SingletonDatabase() = default;


    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int getPopulation(const std::string& city) {
        return capitals_[city];
    }


    void print() {
        for (auto const&capital : capitals_) {
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

    std::string city = "Tokyo";

    SingletonDatabase::get().print();
    std::cout << "\n" << city << " has population of " << SingletonDatabase::get().getPopulation(city) << std::endl;
    return 0;
}
