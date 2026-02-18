/**
 *    @file std-iterators.cpp
 *    @brief ch-88 Std Iterators
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 17 :\e[0m Iterator" << std::endl;
    std::cout << "\e[1mChapter 88 : Std Iterators\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    std::vector<std::string> names = {"John", "Jane", "Jim", "Jill"};
    // std::vector<std::string>::iterator it = names.begin();
    auto it = names.begin();  // using auto because of clang-tidy

    std::cout << "First name is: " << *it << std::endl;

    ++it;
    it->append(" Doe");  // access to the underlying object
    std::cout << "Second name is: " << *it << std::endl;

    // 1 2 3 4  end()
    //          ^
    while (++it != names.end()) {
        std::cout << "Name is: " << *it << std::endl;
    }

    // printing in reverse order
    //       1 2 3 4
    //    ^ rend()  rbegin()
    // doesn't work for containers like single linked list
    for (auto it = std::rbegin(names); it != std::rend(names); ++it) {
        std::cout << *it;

        if (it + 1 != std::rend(names)) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // const iterator
    // std::vector<std::string>::const_iterator const_it = std::crbegin(names);
    // const_it->append(" Doe");  // doesn't work for const iterator

    // range based for loop, only works for forward iterators
    // begin/end
    // creates iterator and dereferences it

    std::cout << "\nRange based for loop:" << std::endl;
    for (const auto& name : names) {
        std::cout << name << std::endl;
    }

    // range based for with double reference
    /**
        What auto&& does:
    auto&& is a forwarding reference: it can bind to both lvalues and rvalues.
    * If the range gives lvalues (e.g. elements of a std::vector<std::string>), name is deduced as
    std::string& → no copy, you refer to the element.
    * If the range gives rvalues (e.g. temporaries or a range that yields by value), name is deduced
    as std::string&& → still no copy, and the temporary’s lifetime is extended for the duration of
    the loop body.

    So you avoid unnecessary copies and avoid dangling references when the range yields temporaries.

    Compared to other options

    Loop variable	Behavior
    `auto name`	Copies each element. Expensive for non-trivial types and you’re not referring to the
    original. `auto& name`	Lvalue reference only. Does not bind to rvalues. If the range yields
    temporaries (e.g. some range adaptors), this can be invalid or not compile. `const auto& name`
    No copy, read-only. Binds to rvalues and extends their lifetime. Good when you don’t need to
    modify. `auto&& name`	Binds to both lvalues and rvalues, no copy, extends lifetime of
    temporaries. Works with normal containers, proxy iterators, and range adaptors that return by
    value.

    Why it’s “safer”

    1. No accidental copies – you don’t pay for copies when the range already gives you references
    or temporaries.
    2. Works with rvalues – if the range yields temporaries (e.g. range | views::transform(...)),
    auto&& binds correctly and keeps them alive in the loop; auto& would not.
    3. Works with proxy iterators – some iterators (e.g. std::vector<bool>) return proxy objects;
    auto&& handles those without unnecessary copies or wrong types.

    So “safer” here means: correct and efficient for more kinds of ranges (including those that
    yield rvalues or proxies), without copies and without dangling references. For a simple
    std::vector<std::string> names, const auto& name would also be fine and clear if you’re only
    reading; auto&& is the one that stays correct when you move to more complex or generic ranges.
    **/
    std::cout << "\nRange based for with double reference:" << std::endl;
    for (auto&& name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}
