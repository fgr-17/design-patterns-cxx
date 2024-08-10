/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 *
 */


#include <iostream>
#include <vector>
#include <fstream>

struct Journal {
  std::string title;
  std::vector<std::string> entries;

  explicit Journal(const std::string &title): title(title) {}

  void add_entry(const std::string& entry) {
      static int count = 1;
      entries.push_back(std::to_string(count) + ": " + entry);
  }

  // this method would violate single resp principle:
  // void save(const string& filename) {
  //   ofstream ofs(filename);
  //   for (auto& e: entries) {
  //     ofs << e << endl;
  //   }
  // }
};


struct PersistenceManager {
  // in this site, it shouldn't break the single resp principle:
  static void save(const Journal& j, const std::string& filename) {
    std::ofstream ofs(filename);
    for (const auto& e : j.entries) {
      ofs << e << std::endl;
    }
  }
};

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  Journal journal{"Dear diary"};
  journal.add_entry("I ate a bug");
  journal.add_entry("I cried today");

  PersistenceManager::save(journal, "diary.txt");

  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 3:\e[0m Single Responsibility Principle" << std::endl;

  return 0;
}
