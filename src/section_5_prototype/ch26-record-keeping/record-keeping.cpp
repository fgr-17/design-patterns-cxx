/**
 *    @file record-keeping.cpp
 *    @brief Chapter 26: Record Keeping
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <string>
#include <utility>

struct Address {
    std::string street, city;
    int suite;

    Address(const std::string street, const std::string city, int suite) : street(std::move(street)), city(std::move(city)), suite(suite) {}

    friend std::ostream& operator<<(std::ostream&os, const Address& a) {
        os << "Street: " << a.street << "\n";
        os << "City: " << a.city << "\n";
        os << "Suite: " << a.suite << "\n";
        return os;
    }
};

struct Contact {
    std::string name;
    Address address;

    Contact(const std::string name, const Address address): name(std::move(name)), address(std::move(address)) {}

    friend std::ostream& operator<<(std::ostream&os, const Contact& c) {
        os << "Name: " << c.name << "\n";
        os << c.address;
        return os;
    }
};


/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 5:\e[0m Prototype" << std::endl;
  std::cout << "\e[1mChapter 26:\e[0m Record Keeping" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief main program
 */

int main() {
    printTitle();
    const int johnAddressNo = 123;
    const int janeAddressNo = 103;
    const int juanAddressNo = 124;

    // problem: many contacts with the same address
    Contact john{"John Doe", Address{"123 East Dr", "London", johnAddressNo}};
    Contact jane{"Jane Smith", Address{"123 East Dr", "London", janeAddressNo}};
    Contact juan{"Juan Valdez", Address{"123 East Dr", "London", juanAddressNo}};

    std::cout << john << std::endl;
    std::cout << jane << std::endl;
    std::cout << juan << std::endl;

    // another way to construct Jane

    Contact jane2 = john;
    jane.name = "Jane";
    jane.address.suite = janeAddressNo;
    std::cout << jane2 << std::endl;


    return 0;
}
