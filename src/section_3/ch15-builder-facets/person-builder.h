/**
 *    @file person-builder.h
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <utility>
#include "person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
 protected:
    // the base class has a reference of the object to avoid replicating it
    Person& person;
    explicit PersonBuilderBase(Person &person) : person{person} {}

 public:
    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase{
 public:
    PersonBuilder(): PersonBuilderBase{p} {}
 private:
    // the builder class has the object itself
    Person p;
};
