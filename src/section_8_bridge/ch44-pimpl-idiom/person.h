/**
 *   @file person.h
 *   @brief person class define
 */
#pragma once
#include <string>
#include <iostream> // IWYU pragma: keep


class Person {

 public:

    std::string name;

    class PersonImpl;
    PersonImpl* impl;

    Person(std::string name);
    ~Person();

    void greet() const;

// secret stuff goes inside cpp
//  private:
//     void secretFun();
};