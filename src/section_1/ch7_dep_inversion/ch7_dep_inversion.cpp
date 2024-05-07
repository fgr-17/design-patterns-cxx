/**
 *    @file main.cpp
 *    @brief Dependency Inversion Principle: 
 *    @brief A. High-level modules should not depend on low-level modules. Both should depend on abstractions
 *    @brief B. Abstractions should not depend on details. Details should depend on abstractions
 *    @author rouxfederico@gmail.com
 * 
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

enum class Relationship {
  parent, 
  child,
  sibling
};

struct Person {
  std::string name;
};

// struct Relationships {    // low-level module
//   std::vector<std::tuple<Person, Relationship, Person>> relations;

//   void add_parent_and_child(const Person&parent, const Person& child) {
//     relations.push_back({parent, Relationship::parent, child});
//     relations.push_back({child, Relationship::child, parent});
//   }

// };

// old version
// struct Research {  // high-level

//   Research(Relationships& relationships) { // <<<< this offends the deps inversion principle
//     auto& relations = relationships.relations;

//     for (auto&& [first, rel, second]: relations) {
//       if (first.name == "John" && rel == Relationship::parent) {
//         std::cout << "John has a child called " << second.name << std::endl;
//       }
//     }
//   }
// };

// to avoid connecting Research (high level module) to Relationships (low level), a new abstraction should be created:

struct RelationshipBrowser {
  virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};

struct Relationships: RelationshipBrowser {    // low-level module
  std::vector<std::tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person&parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  std::vector<Person> find_all_children_of(const std::string &name) override
  {
    std::vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }

};

// solid version
struct Research {  // high-level

  Research(RelationshipBrowser& browser) { // <<<< this offends the deps inversion principle
    for(auto&child: browser.find_all_children_of("John")) {
      std::cout << "John has a child called " << child.name << std::endl;
    }

  }
};

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 7:\e[0m Dependency Inversion Principle" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  print_tilte();

  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);


  return 0;
}