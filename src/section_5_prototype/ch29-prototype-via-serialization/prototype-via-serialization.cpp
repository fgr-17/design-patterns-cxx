/**
 *    @file prototype-via-serialization.cpp
 *    @brief Chapter 29: prototype-via-serialization
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
        os << a.street << "\n";
        os << a.city << "\n";
        os << a.suite << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Address& address) {
        std::getline(is, address.street);
        std::getline(is, address.city);
        is >> address.suite;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return is;
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

    friend std::ostream& operator<<(std::ostream& os, const Contact2& contact) {
        os << contact.name << "\n";
        if (contact.address) {
            os << *contact.address;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Contact2& contact) {
        std::getline(is, contact.name);
        contact.address = new Address();  // Allocate memory for the address
        is >> *contact.address;           // Deserialize into the Address object
        return is;
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
  std::cout << "\e[1mChapter 29:\e[0m Prototype Via Serialization" << std::endl;
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

    auto clone = [] (const Contact2& c) {
        std::ostringstream oss;
        oss << c;
        std::string s = oss.str();
        std::cout << s << std::endl;

        std::istringstream iss;
        Contact2 result;
        iss >> result;
        return result;
    };

    auto john = EmployeeFactory::newMainOfficeEmployee("john", johnAddressNo);
    auto jane = clone(john);

    return 0;
}
