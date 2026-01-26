/**
 *    @file functional-decorator.cpp
 *    @brief Functional Decorator
 *    @author rouxfederico@gmail.com
 */


#include <cstdint>      // IWYU pragma: keep
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>       // IWYU pragma: keep
#include <functional>
#include <utility>

// Functional approach
struct Logger {
  std::function<void()> func;
  std::string name;

  Logger(const std::function<void()> log, const std::string name): func(log), name(name) {}

  void operator()() const {
    std::cout << "Entering " << name << std::endl;
    func();
    std::cout << "Exiting " << name << std::endl;
  }
};

// Template approach: presents the issue that templates cannot specify function arguments
template <typename Func>
struct Logger2 {
  Func func;
  std::string name;

  Logger2(const Func& func, const std::string name): func(func), name(name) {}

  void operator()() const {
    std::cout << "Entering " << name << std::endl;
    func();
    std::cout << "Exiting " << name << std::endl;
  }
};

// Needs a helper function to create the logger - factory pattern
template <typename Func>
Logger2<Func> makeLogger(Func func, const std::string name) {
  return Logger2<Func>(func, name);
}

/**
 *   @fn printTitle
 *   @brief chapter title 
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 10 :\e[0m Decorator" << std::endl;
  std::cout << "\e[1mCH56: Functional Decorator\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

double add(double a, double b) {
  std::cout << a << " + " << b << " = " << a + b << std::endl;
  return a + b;
}

template <typename>
struct Logger3;

// partial specialization of Logger3 for function pointers
template <typename R, typename... Args>
struct Logger3<R(Args...)> {
  std::function<R(Args...)> func;
  std::string name;

  Logger3(std::function<R(Args...)> func, const std::string name): func(std::move(func)), name(std::move(name)) {}

  R operator()(Args... args)  {
    std::cout << "Entering " << name << std::endl;
    auto result = func(args...);
    std::cout << "Exiting " << name << std::endl;
    return result;
  }
};

template <typename R, typename... Args>
auto makeLogger3(R(*func)(Args...), const std::string name) {
  return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

/**
 *   @fn main
 *   @brief Functional Decorator
 */

int main() {
  printTitle();
  Logger([]() {
    std::cout << "Hello, world!" << std::endl;
  }, "Hello, world!")();

  // makeLogger needed before C++17 because CTAD (class template argument deduction) is not supported
  auto log = makeLogger([]() {
    std::cout << "Hello, world 2!" << std::endl;
  }, "HelloFun2");
  log();

  // CTAD (class template argument deduction) is supported since C++17
  Logger2 log2([]() {
    std::cout << "Hello, world 3!" << std::endl;
  }, "HelloFun3");
  log2();

  auto loggedAdd = makeLogger3(add, "add");
  auto result = loggedAdd(1, 2);
  std::cout << "[main] Result: " << result << std::endl;

  return 0;
}
