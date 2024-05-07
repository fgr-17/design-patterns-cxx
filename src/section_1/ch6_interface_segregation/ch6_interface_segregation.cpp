/**
 *    @file main.cpp
 *    @brief Interface Segregation Principle: not create interfaces that are too large
 *    @author rouxfederico@gmail.com
 * 
 */

#include <cassert>
#include <iostream>

#define BOLD        "\e[1m"
#define NON_BOLD    "\e[0m"

struct Document;

// struct IMachine {
//   virtual void print(Document&doc) = 0;
//   virtual void scan(Document&doc) = 0;
//   virtual void fax(Document&doc) = 0;
// };


// struct MultiFunctionPrinter: IMachine {
//   void print(Document&doc) override {
//     // ok
//     return;
//   }
//   void scan(Document&doc) override {
//     // ok
//     return;
//   }
//   void fax(Document&doc) override {
//     // ok
//     return;
//   }
// };

// struct Scanner: IMachine {
//   // the implementation of this class gives a wrong message about a Scanner that can print
//   void print(Document&doc) override {
//     return;
//   }
//   void scan(Document&doc) override {
//     // ok
//     return;
//   }
//   void fax(Document&doc) override {
//     return;
//   }
// };

struct IPrinter {
  virtual void print(Document&doc) = 0;
};

struct IScanner {
  virtual void scan(Document&doc) = 0;
};

struct IFax {
  virtual void fax(Document&doc) = 0;
};


struct Printer: IPrinter {
  void print(Document&doc) override {
    return;
  }
};

struct Scanner: IScanner {
  void scan(Document&doc) override {
    return;
  }
};


struct IMachine: IPrinter, IScanner {};

struct Machine: IMachine {
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter&printer, IScanner&scanner): printer(printer), scanner(scanner) {}

  void print(Document&doc) override {
    printer.print(doc);
  }
  void scan(Document&doc) override {
    scanner.scan(doc);
  }
};


/**
 *   @fn print_title
 *   @brief show the title, section and chapter
 */

static int print_tilte(void) {
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 2:\e[0m SOLID Design Principles" << std::endl;
  std::cout << "\e[1mChapter 6:\e[0m Interface Segregation Principle" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main(void) {
  print_tilte();

  return 0;
}