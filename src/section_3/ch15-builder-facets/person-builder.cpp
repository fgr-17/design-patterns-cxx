/**
 *    @file person-builder.cpp
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#include "person-builder.h"
#include "person-address-builder.h"
#include "person-job-builder.h"


// PersonBuilderBase::PersonBuilderBase(Person&person) : person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const {
     return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}

// PersonBuilder::PersonBuilder() : PersonBuilderBase(p) {}
