/**
 *    @file testeability-issues.cpp
 *    @brief Chapter 35: Singleton Lifetime in DI Container
 *    @author rouxfederico@gmail.com
 */

#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>
#include <memory>

#include <boost/di.hpp>  // IWYU pragma: keep


struct IFoo {
  virtual std::string name() = 0;
  virtual ~IFoo() = default;  // Virtual destructor

  // IFoo(IFoo&) = default;
  // IFoo(IFoo&&) = default;
  // IFoo& operator=(const IFoo&) = default;
  // IFoo& operator=(IFoo&&) = default;
};

struct Foo : IFoo {
 private:
  static int id;

 public:
  Foo() : IFoo() { ++id; }

  std::string name() override {
    return "foo " + std::to_string(id);
  }
};

int Foo::id = 0;

struct Bar {
  std::shared_ptr<IFoo> foo;
};


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 6:\e[0m Singleton" << std::endl;
  std::cout << "\e[1mChapter 35:\e[0m Singleton Lifetime in DI Container" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Singleton Implementation
 */

int main() {
    printTitle();

    // create an injector with policies about how dependencies are solved
    auto injector = boost::di::make_injector(
      boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton));    // map IFoo to Foo when asked for instance, also specify creating a singleton

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    std::cout << "bar1 name:" << bar1->foo->name() << std::endl;
    std::cout << "bar2 name:" << bar2->foo->name() << std::endl;

    std::cout << std::boolalpha << (bar1->foo.get() == bar2->foo.get()) << "\n";

    return 0;
}
