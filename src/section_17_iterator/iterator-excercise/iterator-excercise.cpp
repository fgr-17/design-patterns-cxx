/**
 *    @file iterator-excercise.cpp
 *    @brief Iterator Coding Exercise:
 *    @brief Given the following definition of a `Node<T>`, please implement preorder traversal that
 *    @brief returns a sequence of `T`ßs. I have greatly simplified the problem by adding an
 *    @brief accumulator argument into the `preorderTraversal()` function.
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <vector>

template <typename T>
struct Node {
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
        if (left) {
            left->parent = this;
        }
        if (right) {
            right->parent = this;
        }
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorderTraversal(std::vector<Node<T> *> &result) {
        result.push_back(this);
        if (left) {
            left->preorderTraversal(result);
        }
        if (right) {
            right->preorderTraversal(result);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
        os << node.value;
        return os;
    }
};
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 17 :\e[0m Iterator" << std::endl;
    std::cout << "\e[1mIterator Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Node<int> left{2, nullptr, nullptr};
    Node<int> right{3, nullptr, nullptr};
    Node<int> root{1, &left, &right};

    std::vector<Node<int> *> result;
    root.preorderTraversal(result);
    for (const auto &n : result) {
        std::cout << n->value << std::endl;
    }

    return 0;
}
