#pragma once

#include <string>

template <typename T>
class Observer {
    virtual void fieldChanged(T& source, const std::string& fieldName) = 0;

   public:
    Observer() = default;
    Observer(const Observer& other) = default;
    Observer& operator=(const Observer& other) = default;
    Observer(Observer&& other) = default;
    Observer& operator=(Observer&& other) = default;
    virtual ~Observer() = default;
};