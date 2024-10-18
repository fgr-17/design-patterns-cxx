/**
 *    @file record-keeping.cpp
 *    @brief Chapter 28: Prototype Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 *
 */

#include <iostream>
#include <cmath>        // IWYU pragma: keep
#include <memory>
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

    friend std::ostream& operator<<(std::ostream&os, const Contact2& c) {
        os << "Name: " << c.name << "\n";
        os << *c.address;
        return os;
    }
};

struct EmployeeFactory {
    static std::unique_ptr<Contact2> newMainOfficeEmployee(const std::string&name, const int suite) {
        static Contact2 p{"", new Address{"123 East Dr", "London", 0}};
        return newEmployee(name, suite, p);
    }

 private:
    static std::unique_ptr<Contact2> newEmployee(const std::string&name, const int suite, const Contact2& prototype) {
        auto result = std::make_unique<Contact2> (prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
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
  std::cout << "\e[1mChapter 28:\e[0m Prototype Factory" << std::endl;
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
    jane2.name = "Jane";
    jane2.address.suite = janeAddressNo;
    std::cout << jane2 << std::endl;


    // using a pointer for the address
    Contact2 john2{"John Doe", new Address{"123 East Dr", "London", johnAddressNo}};
    std::cout << john2 << std::endl;

    Contact2 jane3 = john2;
    jane3.name = "Jane";
    jane3.address->suite = janeAddressNo;
    std::cout << jane3 << std::endl;
    // shows Jane's suite instead of John's
    std::cout << john2 << std::endl;

    // Creating contacts from factory

    auto john3 = EmployeeFactory::newMainOfficeEmployee("John", johnAddressNo);
    std::cout << "Employees from factory\n";
    std::cout << *john3 << std::endl;


    return 0;
}
