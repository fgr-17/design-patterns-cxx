/**
 *    @file observable.h
 *    @brief ch-106 Deps Problem
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <string>
#include <vector>

#include "observer.h"

template <typename T>
class Observable {
    std::vector<Observer<T>*> observers_;

   public:
    void notify(T& source, const std::string& fieldName) {
        for (auto observer : observers_) {
            observer->fieldChanged(source, fieldName);
        }
    }

    void subscribe(Observer<T>& observer) {
        observers_.emplace_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // observers_.erase(std::remove(observers_.begin(), observers_.end(), &observer),
        //                  observers_.end());
        std::erase(observers_, &observer);
    }
};