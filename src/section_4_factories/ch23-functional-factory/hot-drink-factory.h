/**
 *    @file hot-drink-factory.h
 *    @brief Chapter 22: Abstract Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <algorithm>
#include <memory>
#include <type_traits>
#include "hot-drink.h"

struct HotDrinkFactory {    // abstract factory
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};
