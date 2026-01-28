#pragma once

#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct ContainsIntegers {
    [[nodiscard]] virtual int sum() const = 0;
};

struct SingleValue : ContainsIntegers {
    int value{0};

    SingleValue() = default;
    explicit SingleValue(const int value) : value{value} {}

    [[nodiscard]] int sum() const override {
        return value;
    }
};

struct ManyValues : ContainsIntegers, std::vector<int> {
    void add(const int value) {
        push_back(value);
    }

    [[nodiscard]] int sum() const override {
        return std::accumulate(begin(), end(), 0);
    }
};

[[nodiscard]] int sum(const std::vector<ContainsIntegers*>& items);