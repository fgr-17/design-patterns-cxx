/**
 *    @file hot-drink.h
 *    @brief Chapter 22: Abstract Factory
 *    @brief
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <iostream>

struct HotDrink {
  virtual ~HotDrink() = default;
  virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
    void prepare(int volume) override {
        std::cout << "Take tea bag,  boil water, pour " << volume << "ml, add some lemon" << std::endl;
    }
};

struct Coffee : HotDrink {
    void prepare(int volume) override {
        std::cout << "Grab some beans,  boil water, pour " << volume << "ml, add cream" << std::endl;
    }
};
