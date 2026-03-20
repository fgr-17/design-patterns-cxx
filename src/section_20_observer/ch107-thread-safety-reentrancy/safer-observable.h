/**
 *    @file safer-observable.h
 *    @brief ch-107 Thread Safety Reentrancy
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <mutex>
#include <string>
#include <vector>

#include "observer.h"

template <typename T>
class SaferObservable {
    std::vector<Observer<T>*> observers_;
    std::mutex mutex_;

   public:
    void notify(T& source, const std::string& fieldName) {
        std::scoped_lock lock(mutex_);
        for (auto observer : observers_) {
            if (observer) {
                observer->fieldChanged(source, fieldName);
            }
        }
    }

    void subscribe(Observer<T>& observer) {
        std::scoped_lock lock(mutex_);
        observers_.emplace_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // observers_.erase(std::remove(observers_.begin(), observers_.end(), &observer),
        //                  observers_.end());
        // std::scoped_lock lock(mutex_);
        // std::erase(observers_, &observer);

        auto it = std::find(std::begin(observers_), std::end(observers_), &observer);
        if (it != std::end(observers_)) {
            *it = nullptr;
        }
    }
};
