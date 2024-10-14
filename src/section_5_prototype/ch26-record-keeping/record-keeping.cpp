/**
 *    @file record-keeping.cpp
 *    @brief Chapter 26: Record Keeping
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <cstdlib>
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


struct Contact2 {
    std::string name;
    Address* address;

    Contact2(const std::string name, Address* address): name(std::move(name)), address(address) {}

    Contact2(const Contact2& other) : name{other.name},
        address{new Address {other.address->street, other.address->city, other.address->suite}} {}


    // for clang-tidy check: if having a copy constructor, needs to define:
    // ---------------------------------------------------------------------

    Contact2(const Contact2&&) = delete;                // move constructor
    Contact2& operator=(const Contact2&) = delete;      // copy assignment operator
    Contact2& operator=(const Contact2&&) = delete;     // move assignment operator

    ~Contact2() {free(address);}
    // ---------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream&os, const Contact2& c) {
        os << "Name: " << c.name << "\n";
        os << *c.address;
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
    // resusing the object John
    Contact jane2 = john;
    jane2.name = "Jane";
    jane2.address.suite = janeAddressNo;
    std::cout << jane2 << std::endl;


    // using a pointer for the address
    Contact2 john2{"John Doe", new Address{"123 East Dr", "London", johnAddressNo}};
    std::cout << john2 << std::endl;

    // shallow copy: does not copy the memory pointed
    Contact2 jane3 = john2;
    jane3.name = "Jane";
    jane3.address->suite = janeAddressNo;
    std::cout << jane3 << std::endl;
    // shows Jane's suite instead of John's
    std::cout << john2 << std::endl;


    return 0;
}
