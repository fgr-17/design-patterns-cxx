/**
 *    @file main.cpp
 *    @brief ch-107 Thread Safety Reentrancy
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

#include "observable.h"
#include "observer.h"
#include "safer-observable.h"

class Person : public SaferObservable<Person> {  // observable
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

class TrafficAdmin : public Observer<Person> {
    void fieldChanged(Person& source, const std::string& fieldName) override {
        if (fieldName == "age") {
            if (source.getAge() < ageLimit) {
                std::cout << "TrafficAdmin: Person is too young to drive" << std::endl;
            } else {
                std::cout << "TrafficAdmin: Person can drive - unsubscribing from this observer"
                          << std::endl;
                source.unsubscribe(*this);
            }
        }
    }

   private:
    static constexpr int ageLimit = 17;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 20 :\e[0m Observer" << std::endl;
    std::cout << "\e[1mChapter 107 : Thread Safety and Reentrancy\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    static const int age = 15;
    Person person(age);
    ConsolePersonObserver observer;
    TrafficAdmin trafficAdmin;
    person.subscribe(observer);
    person.subscribe(trafficAdmin);
    person.setAge(age + 1);
    person.setAge(age + 2);

    person.unsubscribe(observer);
    person.setAge(age + 3);

    return 0;
}
