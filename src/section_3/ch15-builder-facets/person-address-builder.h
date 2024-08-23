#pragma once

#include <string>
#include "person.h"
#include "person-builder.h"

class PersonAddressBuilder : public PersonBuilderBase {

 public:
    PersonAddressBuilder(Person &person) : PersonBuilderBase(person) {}

    PersonAddressBuilder& at(std::string streetAddress) {
        person.streetAddress = streetAddress;
        return *this;
    }

    PersonAddressBuilder& withPostcode(std::string postCode) {
        person.postCode = postCode;
        return *this;
    }

    PersonAddressBuilder& in(std::string city) {
        person.city = city;
        return *this;
    }
};
