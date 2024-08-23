/**
 *    @file person.h
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <string>
#include <ostream>
#include "person-builder.h"


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

    std::ostream &operator<< (std::ostream&os, const Person &person) {}
};
