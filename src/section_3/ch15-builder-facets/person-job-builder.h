/**
 *    @file person-job-builder.h
 *    @brief Chapter 15: Builder Facets
 *    @author rouxfederico@gmail.com
 */

#include "person-builder.h"

class PersonJobBuilder : public PersonBuilderBase {

 public:
    explicit PersonJobBuilder(Person &person) : PersonBuilderBase(person) {}

    PersonJobBuilder& at(std::string companyName) {
        person.companyName = companyName;
        return *this;
    }

    PersonJobBuilder& asA(std::string position) {
        person.position = position;
        return *this;
    }

    PersonJobBuilder& earning(int annualIncome) {
        person.annualIncome = annualIncome;
        return *this;
    }
};
