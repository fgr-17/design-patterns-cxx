/**
 *    @file main.cpp
 *    @brief ch-103 Observer
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

#include "observer.h"

class Person {  // observable
    int age_{0};

   public:
    Person(int age) : age_{age} {}

    [[nodiscard]] int getAge() const {
        return age_;
    }

    void setAge(int age) {
        age_ = age;
    }
};

class ConsolePersonObserver : public Observer<Person> {
    void fieldChanged(Person& source, const std::string& fieldName) override {
        std::cout << "Person's " << fieldName << " has changed to " << source.getAge() << std::endl;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 20 :\e[0m Observer" << std::endl;
    std::cout << "\e[1mChapter 103 : Observer\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    return 0;
}
