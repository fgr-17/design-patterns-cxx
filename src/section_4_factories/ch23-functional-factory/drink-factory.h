/**
 *    @file drink-factory.h
 *    @brief Chapter 22: Abstract Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 */

 #pragma once


#include <algorithm>
#include <map>
#include <string>
#include <functional>

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

class DrinkWithVolumeFactory {
    std::map<std::string, std::function<std::unique_ptr<HotDrink>(const int&)>> factories;
 public:
    DrinkWithVolumeFactory() {
        factories["tea"] = [] (const int& vol){
          auto tea = std::make_unique<Tea>();
          tea->prepare(vol);
          return tea;
        };

        factories["coffee"] = [] (const int& vol) {
          auto coffee = std::make_unique<Coffee>();
          coffee->prepare(vol);
          return coffee;
        };
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name, const int& vol) {
        return factories[name](vol);
    }
};
