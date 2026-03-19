/**
 *    @file main.cpp
 *    @brief ch-106 Deps Problem
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

#include "observable.h"
#include "observer.h"

class Person : public Observable<Person> {  // observable
    int age_{0};
    static constexpr int votingAge = 18;

   public:
    Person(int age) : age_{age} {}

    [[nodiscard]] int getAge() const {
        return age_;
    }

    void setAge(int age) {
        if (age_ == age) return;

        auto oldCanVote = canVote();
        age_ = age;
        auto newCanVote = canVote();
        notify(*this, "age");
        if (oldCanVote != newCanVote) {
            notify(*this, "canVote");
        }
    }

    [[nodiscard]] bool canVote() const {
        return age_ >= votingAge;
    }
};

class ConsolePersonObserver : public Observer<Person> {
    void fieldChanged(Person& source, const std::string& fieldName) override {
        if (fieldName == "age") {
            std::cout << "Person's age has changed to " << source.getAge() << std::endl;
        } else if (fieldName == "canVote") {
            std::cout << "Person's canVote has changed to " << std::boolalpha << source.canVote()
                      << std::endl;
        } else {
            std::cout << "Unknown field: " << fieldName << std::endl;
        }
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 20 :\e[0m Observer" << std::endl;
    std::cout << "\e[1mChapter 106 : Deps Problem\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static const int age = 16;
    Person person(age);
    ConsolePersonObserver observer;
    person.subscribe(observer);
    person.setAge(age + 1);
    person.setAge(age + 2);

    person.unsubscribe(observer);
    person.setAge(age + 3);

    return 0;
}
