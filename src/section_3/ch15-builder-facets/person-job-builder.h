#pragma once

#include <string>
#include "person-builder.h"
#include "person.h"

class PersonJobBuilder : public PersonBuilderBase {

 public:
    PersonJobBuilder(Person &person) : PersonBuilderBase(person) {}

    PersonJobBuilder& at(std::string companyName) {
        person.companyName = companyName;
        return *this;
    }

    PersonAddressBuilder& asA(std::string position) {
        person.position = position;
        return *this;
    }

    PersonAddressBuilder& earning(int annualIncome) {
        person.annualIncome = annualIncome;
        return *this;
    }
};
