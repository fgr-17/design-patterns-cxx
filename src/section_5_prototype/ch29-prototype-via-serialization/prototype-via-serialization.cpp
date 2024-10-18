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
#include <limits>

struct Address {
    std::string street{""}, city{""};
    int suite{0};

    Address(const std::string street, const std::string city, int suite) : street(std::move(street)), city(std::move(city)), suite(suite) {}

    Address(const Address&other) = default;
    Address() = default;
    // for clang-tidy check: if having a copy constructor, needs to define:
    // ---------------------------------------------------------------------
    ~Address() = default;                                   // dtor
    Address& operator=(const Address&other) = default;      // copy assignment operator
    Address(Address&&other) = default;                      // move ctor
    Address& operator=(Address&&other) = default;           // move assignment operator
    // ---------------------------------------------------------------------

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

struct AddressFactory {
    static std::unique_ptr<Address> newAddress(std::string street, std::string city, const int&suite) {
        return std::make_unique<Address> (std::move(street), std::move(city), suite);
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
    std::string name{""};
    std::unique_ptr<Address> address;

    Contact2(std::string name, Address* address): name(std::move(name)), address(address ? std::make_unique<Address>(*address) : nullptr) {}

    // Contact2(const Contact2& other) : name{other.name},
        // address{new Address {other.address->street, other.address->city, other.address->suite}} {}
    Contact2(const Contact2& other) : name{other.name}, address(other.address ? std::make_unique<Address>(*other.address) : nullptr) {}
    Contact2() = default;
    // for clang-tidy check: if having a copy constructor, needs to define:
    // ---------------------------------------------------------------------
    Contact2(Contact2&&) = default;                         // move constructor
    Contact2& operator=(const Contact2&) = delete;         // copy assignment operator
    Contact2& operator=(Contact2&&) = default;              // move assignment operator
    ~Contact2() = default;                                  // default dtor
    // ---------------------------------------------------------------------


    friend std::ostream& operator<<(std::ostream& os, const Contact2& contact) {
        os << contact.name << "\n";
        if (contact.address) {
            os << *contact.address;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Contact2& contact) {
        std::getline(is, contact.name);
        contact.address = std::make_unique<Address>();
        is >> *contact.address;
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

    auto clone = [] (const Contact2& c) {
        std::ostringstream oss;
        oss << c;
        std::string s = oss.str();
        std::cout << "serialized contact\n" << c << std::endl;

        std::istringstream iss{s};
        Contact2 result;
        iss >> result;
        return result;
    };

    auto john = EmployeeFactory::newMainOfficeEmployee("john", johnAddressNo);
    auto jane = clone(*john);
    jane.name = "Jane";

    std::cout << *john << std::endl;
    std::cout << jane << std::endl;
    return 0;
}
