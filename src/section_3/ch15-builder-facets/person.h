/**
 *    @file person.h
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#include <string>
#include <ostream>

#pragma once

class PersonBuilder;

class Person {
    // address info
    std::string streetAddress, postCode, city;
    // employment info
    std::string companyName, position;
    int annualIncome{0};

 public:
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

    friend std::ostream& operator<< (std::ostream&os, const Person &person) {
        os  << "street address: "   << person.streetAddress
            << "post code: "        << person.postCode
            << "city: "             << person.city
            << "Company name: "     << person.companyName
            << "Position: "         << person.position
            << "Annual income: "    << person.annualIncome;

        return os;
    }
};
