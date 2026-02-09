/**
 *    @file broker-chain.cpp
 *    @brief ch-75 Broker Chain
 *    @brief broker: cor + observer + cqs
 *    @brief cor: chain of responsibility
 *    @brief observer: observer pattern (signals2)
 *    @brief cqs: command query separation
 *    @author rouxfederico@gmail.com
 */

#include <boost/signals2.hpp>  // IWYU pragma: keep
#include <iostream>
#include <string>
#include <utility>

struct Query {
    std::string creatureName;
    int result = 0;
    enum Argument { ATTACK, DEFENSE } argument;

    Query(const std::string& creatureName, int result, Argument argument)
        : creatureName(std::move(creatureName)), result(result), argument(argument) {}
};

struct Game {  // mediator
    boost::signals2::signal<void(Query&)> queries;
};

struct Creature {
   private:
    Game& game_;
    std::string name_;
    int attack_;
    int defense_;

   public:
    Creature(Game& game, const std::string name, int attack, int defense)
        : game_(game), name_(std::move(name)), attack_(attack), defense_(defense) {}

    [[nodiscard]] int getAttack() const {
        Query query(name_, attack_, Query::Argument::ATTACK);
        game_.queries(query);
        return query.result;
    }

    [[nodiscard]] int getDefense() const {
        Query query(name_, defense_, Query::Argument::DEFENSE);
        game_.queries(query);
        return query.result;
    }

    [[nodiscard]] const std::string& getName() const {
        return name_;
    }

    [[nodiscard]] Game& getGame() {
        return game_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature& creature) {
        os << "Creature: " << creature.getName() << " (Attack: " << creature.getAttack()
           << ", Defense: " << creature.getDefense() << ")";
        return os;
    }
};

class CreatureModifier {
   public:
    CreatureModifier() = default;
    CreatureModifier(const CreatureModifier&) = delete;
    CreatureModifier(CreatureModifier&&) = delete;
    CreatureModifier& operator=(const CreatureModifier&) = delete;
    CreatureModifier& operator=(CreatureModifier&&) = delete;

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier {
    boost::signals2::connection connection_;

   public:
    DoubleAttackModifier(Creature& creature) {
        connection_ = creature.getGame().queries.connect([&](Query& query) {
            if (query.creatureName == creature.getName() &&
                query.argument == Query::Argument::ATTACK) {
                query.result *= modifier;
            }
        });
    }

    DoubleAttackModifier(const DoubleAttackModifier&) = delete;
    DoubleAttackModifier(DoubleAttackModifier&&) = delete;
    DoubleAttackModifier& operator=(const DoubleAttackModifier&) = delete;
    DoubleAttackModifier& operator=(DoubleAttackModifier&&) = delete;

    ~DoubleAttackModifier() override {
        connection_.disconnect();
    }

   private:
    static constexpr int modifier = 2;
};

class IncreaseDefenseModifier : public CreatureModifier {
    boost::signals2::connection connection_;

   public:
    IncreaseDefenseModifier(Creature& creature) {
        connection_ = creature.getGame().queries.connect([&](Query& query) {
            if (query.creatureName == creature.getName() &&
                query.argument == Query::Argument::DEFENSE) {
                query.result += modifier;
            }
        });
    }

    IncreaseDefenseModifier(const IncreaseDefenseModifier&) = delete;
    IncreaseDefenseModifier(IncreaseDefenseModifier&&) = delete;
    IncreaseDefenseModifier& operator=(const IncreaseDefenseModifier&) = delete;
    IncreaseDefenseModifier& operator=(IncreaseDefenseModifier&&) = delete;

    ~IncreaseDefenseModifier() override {
        connection_.disconnect();
    }

   private:
    static constexpr int modifier = 1;
};
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 14 :\e[0m Chain of Responsibility" << std::endl;
    std::cout << "\e[1mChapter 75 : Broker Chain\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Game game;
    Creature goblin(game, "Goblin", 2, 2);
    std::cout << goblin << std::endl;

    {
        DoubleAttackModifier doubleAttackModifier(goblin);
        std::cout << goblin << std::endl;

        {
            IncreaseDefenseModifier increaseDefenseModifier(goblin);
            std::cout << goblin << std::endl;
        }

        std::cout << goblin << std::endl;
    }
    std::cout << goblin << std::endl;

    return 0;
}
