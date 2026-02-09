/**
 *    @file cor-excercise.cpp
 *    @brief Chain of Responsibility Coding Exercise
 *    @brief You are given a game scenario with classes Goblin and GoblinKing . Please implement the
 *    @brief following rules:
 *    @brief * A goblin has base 1 attack/1 defense (1/1), a goblin king is 3/3.
 *    @brief *When the Goblin King is in play, every other goblin gets +1 Attack.
 *    @brief *Goblins get +1 to Defense for every other Goblin in play (a GoblinKing is a Goblin!).
 *    @brief Example:
 *    @brief Suppose you have 3 ordinary goblins in play. Each one is a 1/3 (1/1 + 0/2 defense
 *    @brief bonus).
 *    @brief A goblin king comes into play. Now every ordinary goblin is a 2/4 (1/1 + 0/3 defense
 *    @brief bonus from each other + 1/0 from goblin king)
 *    @brief Meanwhile, the goblin king itself is 3/6 (3/3 + 0/3 defense bonus from other goblins)
 *    @brief Here is an example of the kind of test that will be run on the system:
 *    @code
 *      Game game;
 *      Goblin goblin(game);
 *      game.creatures.push_back(&goblin);
 *      ASSERT_EQ(1, goblin.getAttack());
 *      ASSERT_EQ(1, goblin.getDefense());
 *    @endcode
 *    @author rouxfederico@gmail.com
 */

#include <gtest/gtest.h>

#include <boost/signals2.hpp>  // IWYU pragma: keep
#include <iostream>
#include <memory>
#include <vector>

// forward declarations
struct Creature;
class GoblinDefenseModifier;
class GoblinAttackModifier;

struct StatQuery {
    enum Statistic { attack, defense } statistic;
    int result;

    StatQuery(Statistic statistic, int result) : statistic(statistic), result(result) {}
};

struct Game {
    std::vector<Creature*> creatures;
    boost::signals2::signal<void(StatQuery&)> queries;

    Game()
        : defenseModifier_(std::make_unique<GoblinDefenseModifier>(*this)),
          attackModifier_(std::make_unique<GoblinAttackModifier>(*this)) {}

   private:
    std::unique_ptr<GoblinDefenseModifier> defenseModifier_;
    std::unique_ptr<GoblinAttackModifier> attackModifier_;
};

struct Creature {
   private:
    Game& game_;
    int baseAttack_, baseDefense_;

   public:
    Creature(Game& game, int baseAttack, int baseDefense)
        : game_(game), baseAttack_(baseAttack), baseDefense_(baseDefense) {}
    [[nodiscard]] virtual int getAttack() const = 0;
    [[nodiscard]] virtual int getDefense() const = 0;

    [[nodiscard]] int getBaseAttack() const {
        return baseAttack_;
    }

    [[nodiscard]] int getBaseDefense() const {
        return baseDefense_;
    }

    [[nodiscard]] Game& getGame() const {
        return game_;
    }
};

class Goblin : public Creature {
   public:
    Goblin(Game& game, int baseAttack, int baseDefense) : Creature(game, baseAttack, baseDefense) {}
    Goblin(Game& game) : Creature(game, 1, 1) {}

    [[nodiscard]] int getAttack() const override {
        StatQuery query(StatQuery::Statistic::attack, getBaseAttack());
        getGame().queries(query);
        return query.result;
    }

    [[nodiscard]] int getDefense() const override {
        StatQuery query(StatQuery::Statistic::defense, getBaseDefense());
        getGame().queries(query);
        return query.result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Goblin& goblin) {
        os << "Goblin: " << goblin.getAttack() << "/" << goblin.getDefense();
        return os;
    }
};

class GoblinKing : public Goblin {
   public:
    GoblinKing(Game& game) : Goblin(game, 3, 3) {}

    [[nodiscard]] int getAttack() const override {
        return getBaseAttack();
    }

    friend std::ostream& operator<<(std::ostream& os, const GoblinKing& goblinKing) {
        os << "GoblinKing: " << goblinKing.getAttack() << "/" << goblinKing.getDefense();
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

class GoblinDefenseModifier : public CreatureModifier {
   public:
    GoblinDefenseModifier(Game& game) {
        connection_ = game.queries.connect([&](StatQuery& query) {
            if (query.statistic == StatQuery::Statistic::defense) {
                query.result += (modifier * static_cast<int>(game.creatures.size() - 1));
            }
        });
    }

    GoblinDefenseModifier(const GoblinDefenseModifier&) = delete;
    GoblinDefenseModifier(GoblinDefenseModifier&&) = delete;
    GoblinDefenseModifier& operator=(const GoblinDefenseModifier&) = delete;
    GoblinDefenseModifier& operator=(GoblinDefenseModifier&&) = delete;

    ~GoblinDefenseModifier() override {
        connection_.disconnect();
    }

   private:
    boost::signals2::connection connection_;
    static constexpr int modifier = 1;
};

class GoblinAttackModifier : public CreatureModifier {
   public:
    GoblinAttackModifier(Game& game) {
        connection_ = game.queries.connect([&](StatQuery& query) {
            if (query.statistic == StatQuery::Statistic::attack) {
                int goblinKingCount = 0;
                for (Creature* c : game.creatures) {
                    if (dynamic_cast<GoblinKing*>(c) != nullptr) {
                        ++goblinKingCount;
                    }
                }
                query.result += (modifier * goblinKingCount);
            }
        });
    }

    GoblinAttackModifier(const GoblinAttackModifier&) = delete;
    GoblinAttackModifier(GoblinAttackModifier&&) = delete;
    GoblinAttackModifier& operator=(const GoblinAttackModifier&) = delete;
    GoblinAttackModifier& operator=(GoblinAttackModifier&&) = delete;

    ~GoblinAttackModifier() override {
        connection_.disconnect();
    }

   private:
    boost::signals2::connection connection_;
    static constexpr int modifier = 1;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 14 :\e[0m Chain of Responsibility" << std::endl;
    std::cout << "\e[1mChain of Responsibility Excercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

TEST(GoblinTest, TestGoblin) {  // NOLINT
    Game game;

    std::cout << "creating goblin" << std::endl;
    Goblin goblin(game);
    game.creatures.push_back(&goblin);
    std::cout << "goblin: " << goblin << std::endl;
    ASSERT_EQ(1, goblin.getAttack());
    ASSERT_EQ(1, goblin.getDefense());

    std::cout << "creating goblin2" << std::endl;
    Goblin goblin2(game);
    game.creatures.push_back(&goblin2);
    std::cout << "gobli2: " << goblin << std::endl;
    std::cout << "goblin2: " << goblin2 << std::endl;
    ASSERT_EQ(1, goblin.getAttack());
    ASSERT_EQ(2, goblin.getDefense());
    ASSERT_EQ(1, goblin2.getAttack());
    ASSERT_EQ(2, goblin2.getDefense());

    std::cout << "creating goblin king" << std::endl;
    GoblinKing goblinKing(game);
    game.creatures.push_back(&goblinKing);
    std::cout << "goblin king: " << goblinKing << std::endl;
    ASSERT_EQ(2, goblin.getAttack());
    ASSERT_EQ(3, goblin.getDefense());
    ASSERT_EQ(2, goblin2.getAttack());
    ASSERT_EQ(3, goblin2.getDefense());
    ASSERT_EQ(3, goblinKing.getAttack());
    ASSERT_EQ(5, goblinKing.getDefense());
}

int main(int argc, char** argv) {
    printTitle();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
