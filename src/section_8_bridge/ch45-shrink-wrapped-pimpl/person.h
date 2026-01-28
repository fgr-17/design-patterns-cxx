/**
 *   @file foo.h
 *   @brief realization of pimpl template class
 */

#pragma once

#include <pimpl.h>

#include <iostream>
#include <string>

class Person {
   private:
    std::string name_;
    // needs to be defined here because defining pimpl<impl>
    // needs impl to be a complete type
    class impl {
       public:
        void greet(const Person& p) const {
            std::cout << "hello I'm " << p.name_ << "\n";
        }
    };
    pimpl<impl> impl;

   public:
    Person(const std::string name);
    void greet();
};