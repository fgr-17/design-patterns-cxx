/**
 *    @file person.cpp
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */


#include <person.h>


PersonBuilder Person::create() {
    return PersonBuilder();
}

std::ostream & Person::operator<< (std::ostream&os, const Person &person) {
    os  << "street address: "   << person.streetAddress
        << "post code: "        << person.postCode
        << "city: "             << person.city
        << "Company name: "     << person.companyName
        << "Position: "         << person.position
        << "Annual income: "    << person.annualIncome;

    return os;
}
