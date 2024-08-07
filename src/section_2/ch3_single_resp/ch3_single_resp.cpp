/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */


#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

struct Journal {
  
  string title;
  vector<string> entries;

  Journal(const string &title): title(title) {}

  void add_entry(const string& entry) {
      static int count = 1;
      entries.push_back(to_string(count) + ": " + entry);
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
  void save(const Journal& j, const string& filename) {
    ofstream ofs(filename);
    for (auto& e: j.entries) {
      ofs << e << endl;
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

  PersistenceManager pm;

  pm.save(journal, "diary.txt");

  cout << "\e[1mDesign Patterns in Modern C++\e[0m" << endl;
  cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << endl;
  cout << "\e[1mChapter 3:\e[0m Single Responsibility Principle" << endl;

  return 0;
}