/**
 *    @file person-builder.h
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <utility>
#include "person-address-builder.h"
#include "person-job-builder.h"


class PersonBuilderBase {
 protected:
    // the base class has a reference of the object to avoid replicating it
    Person& person;
 public:
    explicit PersonBuilderBase(PersonBuilder &person);

    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase{
 public:
    PersonBuilder();
 private:
    // the builder class has the object itself
    Person p;


};
