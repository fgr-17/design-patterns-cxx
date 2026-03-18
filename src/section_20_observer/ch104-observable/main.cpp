/**
 *    @file main.cpp
 *    @brief ch-104 Observable
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

#include "observable.h"
#include "observer.h"

class Person : public Observable<Person> {  // observable
    int age_{0};

   public:
    Person(int age) : age_{age} {}

    [[nodiscard]] int getAge() const {
        return age_;
    }

    void setAge(int age) {
        if (age_ == age) return;
        age_ = age;
        notify(*this, "age");
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
    std::cout << "\e[1mChapter 104 : Observable\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static const int age = 20;
    Person person(age);
    ConsolePersonObserver observer;
    person.subscribe(observer);
    person.setAge(age + 1);
    person.setAge(age + 2);

    person.unsubscribe(observer);
    person.setAge(age + 3);

    return 0;
}
