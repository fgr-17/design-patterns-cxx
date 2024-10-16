/**
 *    @file drink-factory.h
 *    @brief Chapter 22: Abstract Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 */

 #pragma once


 #include <map>
#include <string>
#include "hot-drink-factory.h"

class DrinkFactory {
   std::map<std::string, std::unique_ptr<HotDrinkFactory>> hotFactories;

 public:

    DrinkFactory() {
        hotFactories["coffee"] = std::make_unique<CoffeeFactory>();
        hotFactories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name) {
        auto drink = hotFactories[name]->make();
        auto vol = 200;
        drink->prepare(vol);
        return drink;
    }

};
