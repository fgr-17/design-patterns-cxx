/**
 *    @file template-method-excercise.cpp
 *    @brief **Template Method Coding Exercise**
 *    @brief Imagine a typical collectible card game which has cards representing creatures. Each
 *    @brief creature has two values: Attack and Health. Creatures can fight each other, dealing
 *    @brief their Attack damage, thereby reducing their opponent's health.
 *    @brief The class `CardGame` implements the logic for two creatures fighting one another.
 *    @brief However, the exact mechanics of how damage is dealt is different:
 *    @brief * `TemporaryCardDamage` : In some games (e.g., Magic: the Gathering), unless the
 *    @brief creature has been killed, its health returns to the original value at the end of
 *    @brief combat.
 *    @brief * `PermanentCardDamage` : In other games (e.g., Hearthstone), health damage persists.
 *    @brief You are asked to implement classes `TemporaryCardDamageGame` and
 *    @brief `PermanentCardDamageGame` that would allow us to simulate combat between creatures.
 *    @brief Some examples:
 *    @brief * With temporary damage, creatures 1/2 and 1/3 can never kill one another. With
 *    @brief permanent damage, second creature will win after 2 rounds of combat.
 *    @brief * With either temporary or permanent damage, two 2/2 creatures kill one another.
 *    @author rouxfederico@gmail.com
 */

#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

struct Creature {
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
    virtual ~Creature() = default;
    Creature(const Creature &) = default;
    Creature(Creature &&) = default;
    Creature &operator=(const Creature &) = default;
    Creature &operator=(Creature &&) = default;
};

struct CardGame {
    std::vector<Creature> creatures;

    CardGame(const std::vector<Creature> &creatures) : creatures(creatures) {}
    virtual ~CardGame() = default;
    CardGame(const CardGame &) = default;
    CardGame(CardGame &&) = default;
    CardGame &operator=(const CardGame &) = default;
    CardGame &operator=(CardGame &&) = default;

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2) {
        hit(creatures[creature1], creatures[creature2]);
        hit(creatures[creature2], creatures[creature1]);
        if (creatures[creature1].health <= 0 && creatures[creature2].health <= 0) {
            return -1;
        } else if (creatures[creature1].health <= 0) {
            return creature2;
        } else if (creatures[creature2].health <= 0) {
            return creature1;
        }
        return -1;
    }

    virtual void hit(Creature &attacker, Creature &other) = 0;
};

struct TemporaryCardDamageGame final : public CardGame {
    TemporaryCardDamageGame(const std::vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        if (other.health <= attacker.attack) {
            other.health = 0;
        }
    }
};

struct PermanentCardDamageGame final : public CardGame {
    PermanentCardDamageGame(const std::vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        other.health -= attacker.attack;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 23 :\e[0m Template Method" << std::endl;
    std::cout << "\e[1mTemplate Method Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    return 0;
}
