/**
 *    @file handmade-flyweight.cpp
 *    @brief Handmade Flyweight
 *    @author rouxfederico@gmail.com
 */

#include <boost/bimap/bimap.hpp>                                // for bimap
#include <boost/bimap/container_adaptor/container_adaptor.hpp>  // for conta...
#include <boost/bimap/detail/bimap_core.hpp>                    // for right...
#include <boost/bimap/detail/map_view_iterator.hpp>             // for map_v...
#include <boost/bimap/detail/set_view_iterator.hpp>             // for set_v...
#include <boost/bimap/relation/mutant_relation.hpp>             // for mutan...
#include <boost/bimap/relation/structured_pair.hpp>             // for struc...
#include <boost/bimap/relation/symmetrical_base.hpp>            // for symme...
#include <boost/iterator/iterator_facade.hpp>                   // for opera...
#include <boost/mpl/aux_/na_fwd.hpp>                            // for na
#include <boost/multi_index/detail/bidir_node_iterator.hpp>     // for opera...
#include <boost/multi_index_container.hpp>                      // for get
#include <boost/tuple/detail/tuple_basic.hpp>                   // for get
#include <cstddef>                                              // IWYU pragma: keep
#include <cstdint>                                              // IWYU pragma: keep
#include <fstream>                                              // IWYU pragma: keep
#include <iostream>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep

// IWYU pragma: no_include <boost/flyweight/flyweight.hpp>
// IWYU pragma: no_include <boost/operators.hpp>
#include <boost/flyweight.hpp>                                  // IWYU pragma: keep


struct User {
    std::string firstName;
    std::string lastName;

    User(std::string firstName, std::string lastName)
        : firstName(std::move(firstName)), lastName(std::move(lastName)) {}

    friend std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "User: " << user.firstName << " " << user.lastName;
        return os;
    }

    [[nodiscard]] size_t getTotalMemory() const {
        return sizeof(*this) + firstName.capacity() + lastName.capacity();
    }

    [[nodiscard]] size_t getUsedMemory() const {
        return firstName.size() + lastName.size();
    }
};

using key = uint32_t;

struct FlyweightUser {
   public:
    FlyweightUser(const std::string& firstName, const std::string& lastName)
        : firstNameKey_(add(firstName)), lastNameKey_(add(lastName)) {}

    [[nodiscard]] const std::string& getFirstName() const {
        return names.left.find(firstNameKey_)->second;
    }

    [[nodiscard]] const std::string& getLastName() const {
        return names.left.find(lastNameKey_)->second;
    }

    [[nodiscard]] static size_t getTotalMemory() {
        size_t totalMemory = 0;
        for (const auto& [_, value] : names) {
            totalMemory += sizeof(key) + value.capacity();
        }
        return totalMemory;
    }

    [[nodiscard]] static size_t getUsedMemory() {
        size_t usedMemory = 0;
        for (const auto& [_, value] : names) {
            usedMemory += value.size();
        }
        return usedMemory;
    }

   private:
    key firstNameKey_;
    key lastNameKey_;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static boost::bimaps::bimap<key, std::string> names;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static key seed;

    static key add(const std::string& s) {
        auto it = names.right.find(s);
        if (it == names.right.end()) {
            key id = ++seed;
            names.insert({seed, s});
            return id;
        }
        return it->second;
    }
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
boost::bimaps::bimap<key, std::string> FlyweightUser::names;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
key FlyweightUser::seed{0};

std::ostream& operator<<(std::ostream& os, const FlyweightUser& user) {
    os << "FlyweightUser: " << user.getFirstName() << " " << user.getLastName();
    return os;
}

struct BoostFlyweightUser {
    boost::flyweights::flyweight<std::string> firstName;
    boost::flyweights::flyweight<std::string> lastName;

    BoostFlyweightUser(const std::string& firstName, const std::string& lastName)
        : firstName(firstName), lastName(lastName) {}

    friend std::ostream& operator<<(std::ostream& os, const BoostFlyweightUser& user) {
        os << "BoostFlyweightUser: " << user.firstName << " " << user.lastName;
        return os;
    }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 12 :\e[0m Flyweight" << std::endl;
    std::cout << "\e[1mChapter 63: Boost Flyweight\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Boost Flyweight
 */

int main() {
    printTitle();

    User user1("John", "Doe");
    User user2("Jane", "Doe");
    User user3("John", "Smith");
    User user4("Jane", "Smith");

    std::cout << "Inefficient way to store users" << std::endl;
    std::cout << user1 << std::endl;
    std::cout << user2 << std::endl;
    std::cout << user3 << std::endl;
    std::cout << user4 << std::endl;
    std::cout << "Used memory: "
              << user1.getUsedMemory() + user2.getUsedMemory() + user3.getUsedMemory() +
                     user4.getUsedMemory();
    std::cout << " bytes" << std::endl;
    std::cout << "Reserved memory: "
              << user1.getTotalMemory() + user2.getTotalMemory() + user3.getTotalMemory() +
                     user4.getTotalMemory();
    std::cout << " bytes" << std::endl;

    FlyweightUser flyweightUser1("John", "Doe");
    FlyweightUser flyweightUser2("Jane", "Doe");
    FlyweightUser flyweightUser3("John", "Smith");
    FlyweightUser flyweightUser4("Jane", "Smith");
    std::cout << "--------------------------------" << std::endl;

    std::cout << "Flyweight way to store users" << std::endl;
    std::cout << flyweightUser1 << std::endl;
    std::cout << flyweightUser2 << std::endl;
    std::cout << flyweightUser3 << std::endl;
    std::cout << flyweightUser4 << std::endl;
    std::cout << "Used memory: " << FlyweightUser::getUsedMemory() << " bytes" << std::endl;
    std::cout << "Reserved memory: " << FlyweightUser::getTotalMemory() << " bytes" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    
    BoostFlyweightUser boostFlyweightUser1("John", "Doe");
    BoostFlyweightUser boostFlyweightUser2("Jane", "Doe");
    BoostFlyweightUser boostFlyweightUser3("John", "Smith");
    BoostFlyweightUser boostFlyweightUser4("Jane", "Smith");

    std::cout << "Boost Flyweight way to store users" << std::endl;
    std::cout << boostFlyweightUser1 << std::endl;
    std::cout << boostFlyweightUser2 << std::endl;
    std::cout << boostFlyweightUser3 << std::endl;
    std::cout << boostFlyweightUser4 << std::endl;

    std::cout << "Checking first and second users storage:" << std::boolalpha << std::endl;
    std::cout << "First name reuse:" << (&boostFlyweightUser1.firstName.get() == &boostFlyweightUser2.firstName.get()) << std::endl;
    std::cout << "Last name reuse:" << (&boostFlyweightUser1.lastName.get() == &boostFlyweightUser2.lastName.get()) << std::endl;
    std::cout << "Boost doesn't provide a way to measure the memory used by the flyweight" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    return 0;
}
