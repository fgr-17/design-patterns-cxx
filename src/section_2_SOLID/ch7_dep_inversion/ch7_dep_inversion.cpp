/**
 *    @file main.cpp
 *    @brief Dependency Inversion Principle:
 *    @brief A. High-level modules should not depend on low-level modules. Both should depend on abstractions
 *    @brief B. Abstractions should not depend on details. Details should depend on abstractions
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

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

//   void addParentAndChild(const Person&parent, const Person& child) {
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
  [[nodiscard]] virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
};

struct Relationships: RelationshipBrowser {    // low-level module
  std::vector<std::tuple<Person, Relationship, Person>> relations;

  void addParentAndChild(const Person&parent, const Person& child) {
    relations.emplace_back(parent, Relationship::parent, child);
    relations.emplace_back(child, Relationship::child, parent);
  }

  [[nodiscard]] std::vector<Person> findAllChildrenOf(const std::string &name) const override{
    std::vector<Person> result;
    for (auto&& [first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) {
        result.push_back(second);
      }
    }
    return result;
  }
};

// solid version
struct Research {  // high-level
  explicit Research(const RelationshipBrowser& browser) {  // <<<< this offends the deps inversion principle
    for (auto&child : browser.findAllChildrenOf("John")) {
      std::cout << "John has a child called " << child.name << std::endl;
    }
  }
};

/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int printTitle() {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 7:\e[0m Dependency Inversion Principle" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
  printTitle();

  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  Relationships relationships;
  relationships.addParentAndChild(parent, child1);
  relationships.addParentAndChild(parent, child2);


  // research class is connected to an abstract class, but it can be implemented using the concrete class
  Research _(relationships);


  return 0;
}
