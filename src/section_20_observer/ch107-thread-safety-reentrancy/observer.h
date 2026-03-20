/**
 *    @file observer.h
 *    @brief ch-107 Thread Safety Reentrancy
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <string>

template <typename T>
class Observer {
   public:
    Observer() = default;
    Observer(const Observer& other) = default;
    Observer& operator=(const Observer& other) = default;
    Observer(Observer&& other) = default;
    Observer& operator=(Observer&& other) = default;
    virtual ~Observer() = default;

    virtual void fieldChanged(T& source, const std::string& fieldName) = 0;
};
