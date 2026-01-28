/**
 *   @file person.cpp
 *   @brief person class implementation
 *   @brief hide details of implementation of Person class
 *   @brief to the consumers of the Person lib
 *   @brief The header file can be shared without showing anything private
 *   @brief The cpp file is not shipped to the client as source, only compiled
 */

#include <person.h>

#include <iostream>  // IWYU pragma: keep
#include <string>
#include <utility>

class Person::PersonImpl {
   public:
    void greet(const Person* p) const {
        std::cout << "hello I'm " << p->name << "\n";
    }

   private:
    void secretStuff();
};

Person::Person(const std::string name) : name(std::move(name)), impl(new PersonImpl) {}

Person::~Person() {
    delete impl;
}

void Person::greet() const {
    impl->greet(this);
}
