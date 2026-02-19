/**
 *    @file binary-tree-iterator.cpp
 *    @brief ch-89 Binary Tree Iterator
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>
#include <utility>

template <typename T>
struct BinaryTree;

/**
 *     A
 *    / \
 *   B   C
 */

template <typename T>
struct Node {
    T value = T();
    Node<T>* left{nullptr};
    Node<T>* right{nullptr};
    Node<T>* parent{nullptr};

    BinaryTree<T>* tree{nullptr};

    Node(T value) : value(std::move(value)) {}

    Node() = default;
    Node(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;

    Node(T value, Node<T>* left, Node<T>* right)
        : value(std::move(value)), left(left), right(right) {
        this->left->tree = this->tree;
        this->right->tree = this->tree;
        this->left->parent = this;
        this->right->parent = this;
    }

    void setTree(BinaryTree<T>* tree) {
        this->tree = tree;
        this->left->tree = tree;
        this->right->tree = tree;
    }

    ~Node() {
        if (this->left) {
            delete this->left;
        }
        if (this->right) {
            delete this->right;
        }
    }
};

template <typename T>
struct BinaryTree {
    Node<T>* root{nullptr};

    BinaryTree(Node<T>* root) : root(root) {
        root->tree = this;
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

    ~BinaryTree() {
        if (this->root) {
            delete this->root;
        }
    }

    template <typename U>
    struct PreOrderIterator {
        Node<U>* current;

        PreOrderIterator(Node<U>* current) : current(current) {}

        // PreOrderIterator() = default;
        // PreOrderIterator(const PreOrderIterator&) = delete;
        // PreOrderIterator(PreOrderIterator&&) = delete;
        // PreOrderIterator& operator=(const PreOrderIterator&) = delete;
        // PreOrderIterator& operator=(PreOrderIterator&&) = delete;

        bool operator!=(const PreOrderIterator<U>& other) const {
            return current != other.current;
        }

        PreOrderIterator<U>& operator++() {
            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                Node<U>* p = current->parent;
                while (p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() {
            return *current;
        }
    };  // PreOrderIterator

    using iterator = PreOrderIterator<T>;

    iterator begin() {
        Node<T>* n = root;
        if (n) {
            while (n->left) {
                n = n->left;
            }
        }
        return iterator{n};
    }

    iterator end() {
        return iterator{nullptr};
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 17 :\e[0m Iterator" << std::endl;
    std::cout << "\e[1mChapter 89 : Binary Tree Iterator\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    /**
     *         me
     *        / \
     *    mother father
     *    /  \    /   \
     *   mm  mf  fm   ff
     */
    BinaryTree<std::string> family{new Node<std::string>{
        "me",
        new Node<std::string>{"mother", new Node<std::string>{"mm"}, new Node<std::string>{"mf"}},
        new Node<std::string>{"father", new Node<std::string>{"fm"}, new Node<std::string>{"ff"}}}};

    for (auto& it : family) {
        std::cout << it.value << std::endl;
    }
    return 0;
}
