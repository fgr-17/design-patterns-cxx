/**
 *    @file boost-iterator-facade.cpp
 *    @brief ch-91 Boost Iterator Facade
 *    @author rouxfederico@gmail.com
 */

#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <iostream>
#include <string>
#include <utility>

struct Node {
    std::string value;
    Node* next;

    Node(std::string value) : value(std::move(value)), next(nullptr) {}
    Node(std::string value, Node* parent) : value(std::move(value)), next(nullptr) {
        parent->next = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag> {
    Node* current{nullptr};

    ListIterator() = default;
    ListIterator(Node* current) : current(current) {}

   private:
    friend class boost::iterator_core_access;

    void increment() {
        current = current->next;
    }

    [[nodiscard]] bool equal(const ListIterator& other) const {
        return current == other.current;
    }

    [[nodiscard]] Node& dereference() const {
        return *current;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 17 :\e[0m Iterator" << std::endl;
    std::cout << "\e[1mChapter 91 : Boost Iterator Facade\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Node alpha{"alpha"};
    Node beta{"beta", &alpha};
    Node gamma{"gamma", &beta};

    std::for_each(ListIterator{&alpha}, ListIterator{},
                  [](Node& node) { std::cout << node.value << std::endl; });

    return 0;
}
