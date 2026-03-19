/**
 *    @file main.cpp
 *    @brief ch-105 Observable Boost
 *    @author rouxfederico@gmail.com
 */

#include <boost/signals2.hpp>
#include <iostream>

#include "observable.h"
#include "observer.h"

class Person : public Observable<Person> {  // observable (boost)
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

template <typename T>
struct Observable2 {
    boost::signals2::signal<void(T&, const std::string&)> fieldChanged;
};

class Person2 : public Observable2<Person2> {
   private:
    int age_{0};

   public:
    [[nodiscard]] int getAge() const {
        return age_;
    }

    void setAge(int age) {
        if (age_ == age) return;
        age_ = age;
        fieldChanged(*this, "age");
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 20 :\e[0m Observer" << std::endl;
    std::cout << "\e[1mChapter 105 : Observable (Boost)\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    static const int age = 20;
    Person2 p2;

    auto conn = p2.fieldChanged.connect([](Person2& p, const std::string& fieldName) {
        std::cout << "Person's " << fieldName << " has changed to " << p.getAge() << std::endl;
    });

    p2.setAge(age + 1);
    p2.setAge(age + 2);

    conn.disconnect();
    p2.setAge(age + 3);

    return 0;
}
