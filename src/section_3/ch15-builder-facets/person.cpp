/**
 *    @file person.cpp
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#include "person.h"
#include "person-builder.h"


PersonBuilder Person::create() {
    return PersonBuilder();
}
