/**
 *    @file singleton-database.cpp
 *    @brief Chapter 33: Testeability Issues
 *    @author rouxfederico@gmail.com
 */

#include "singleton-database.h"

#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <map>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>
#include <utility>
#include <vector>

SingletonDatabase::SingletonDatabase() {
    std::cout << "Initializing db" << std::endl;
    std::ifstream ifs("/workspace/src/section_6_singleton/ch32-singleton-implementation/capitals");

    std::string cityLine, populationLine;

    while (getline(ifs, cityLine)) {
        getline(ifs, populationLine);
        int pop = std::stoi(populationLine);
        capitals_[cityLine] = pop;
    }
}

SingletonDatabase& SingletonDatabase::get() {
    static SingletonDatabase db;
    return db;
}

int SingletonDatabase::getPopulation(const std::string& city) {
    return capitals_[city];
}

void SingletonDatabase::print() {
    for (auto const& capital : capitals_) {
        std::cout << capital.first << ": " << capital.second << std::endl;
    }
}

int SingletonRecordFinder::totalPopulation(std::vector<std::string> cities) {
    int result{0};
    for (auto& city : cities) {
        result += SingletonDatabase::get().getPopulation(city);
    }
    return result;
    ;
}
