#include <person.h>

#include <iostream>  // IWYU pragma: keep
#include <string>
#include <utility>

#include "pimpl.h"

Person::Person(const std::string name) : name_(std::move(name)), impl() {}

// todo: check how this function can be const even using ->
void Person::greet() {
    impl->greet(*this);
}
