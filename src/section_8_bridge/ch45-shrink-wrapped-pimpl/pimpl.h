/**
 *   @file pimpl.h
 *   @brief abstract implementation
 */
#pragma once

#include <memory>

template <typename T>
class pimpl {
   private:
    std::unique_ptr<T> impl;

   public:
    pimpl() : impl(new T{}){};

    template <typename... Args>
    pimpl(Args&&... args) : impl(new T{std::forward<Args>(args)...}) {}

    // to simplify the access to impl underlying implementation
    T* operator->() {
        return impl.get();
    }

    T& operator*() {
        return *impl.get();
    }
};