/**
 *    @file proxy-excercise.cpp
 *    @brief Proxy Coding Exercise:
 *    @brief You are given the Person  class and asked to write a ResponsiblePerson  wrapper/proxy
 *    @brief that does the following:
 *    @brief    * Allows person to drink unless they are younger than 18 (in that case, return "too
 *    @brief young")
 *    @brief    * Allows person to drive unless they are younger than 16 (otherwise, "too young")
 *    @brief    * In case of driving while drink, returns "dead"
 *    @brief The interface of ResponsiblePerson  has to match that of Person , except for the
 * constructor, which takes an underlying Person object..
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>

class Person {
    friend class ResponsiblePerson;
    int age_{0};

   public:
    Person(int age) : age_{age} {}

    [[nodiscard]] int getAge() const {
        return age_;
    }

    void setAge(const int age) {
        this->age_ = age;
    }

    [[nodiscard]] std::string drink() const {
        return "drinking";
    }

    [[nodiscard]] std::string drive() const {
        return "driving";
    }

    [[nodiscard]] std::string drinkAndDrive() const {
        return "driving while drunk";
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Person(age: " << person.getAge() << ")" << std::endl;
        os << "drink: " << person.drink() << std::endl;
        os << "drive: " << person.drive() << std::endl;
        os << "drinkAndDrive: " << person.drinkAndDrive() << std::endl;
        return os;
    }
};

class ResponsiblePerson {
   public:
    ResponsiblePerson(const Person& person) : person_(person) {}

    [[nodiscard]] int getAge() const {
        return person_.getAge();
    }

    void setAge(const int age) {
        person_.setAge(age);
    }

    [[nodiscard]] std::string drink() const {
        return person_.getAge() >= minAgeToDrink ? person_.drink() : "too young";
    }

    [[nodiscard]] std::string drive() const {
        return person_.getAge() >= minAgeToDrive ? person_.drive() : "too young";
    }

    [[nodiscard]] std::string drinkAndDrive() const {
        return "dead";
    }

    friend std::ostream& operator<<(std::ostream& os, const ResponsiblePerson& responsiblePerson) {
        os << "ResponsiblePerson(age: " << responsiblePerson.person_.getAge() << ")" << std::endl;
        os << "drink: " << responsiblePerson.drink() << std::endl;
        os << "drive: " << responsiblePerson.drive() << std::endl;
        os << "drinkAndDrive: " << responsiblePerson.drinkAndDrive() << std::endl;
        return os;
    }

   private:
    Person person_;
    static constexpr int minAgeToDrink = 18;
    static constexpr int minAgeToDrive = 16;
};

/**
 *   @fn printTitle
 *   @brief section/exercise title
 */
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 13 :\e[0m Proxy" << std::endl;
    std::cout << "\e[1mProxy Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Proxy Excercise
 */
int main() {
    printTitle();

    const int age = 17;

    Person person(age);
    ResponsiblePerson responsiblePerson(person);

    std::cout << person << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << responsiblePerson << std::endl;

    return 0;
}
