/**
 *    @file main.cpp
 *    @brief ch-95 Event Broker
 *    @author rouxfederico@gmail.com
 */

#include <boost/signals2.hpp>  // IWYU pragma: keep
#include <iostream>
#include <string>
#include <utility>

// Event broker: mediator + observer pattern

struct EventData {
    virtual void print() const = 0;
    virtual ~EventData() = default;
    EventData() = default;
    EventData(const EventData&) = delete;
    EventData(EventData&&) = delete;
    EventData& operator=(const EventData&) = delete;
    EventData& operator=(EventData&&) = delete;
};

struct PlayerScoredData final : EventData {
    std::string playerName;
    int goalsScoredSoFar;

    PlayerScoredData(std::string playerName, int goalsScoredSoFar)
        : playerName(std::move(playerName)), goalsScoredSoFar(goalsScoredSoFar) {}

    void print() const override {
        std::cout << playerName << " scored " << goalsScoredSoFar << " goals" << std::endl;
    }
};

struct Game {
    boost::signals2::signal<void(EventData*)> events;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 18 :\e[0m Mediator" << std::endl;
    std::cout << "\e[1mChapter 95 : Event Broker\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

struct Player {
    std::string name;
    int goalsScored{0};
    Game& game_;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    Player(std::string name, Game& game) : name(std::move(name)), game_(game) {}
    void score() {
        goalsScored++;
        std::cout << "Player " << name << " scored " << goalsScored << " goals" << std::endl;
        PlayerScoredData event(name, goalsScored);
        game_.events(&event);
    }
};

struct Coach {
    Game& game_;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    boost::signals2::connection connection_;
    Coach(Game& game) : game_(game) {
        connection_ = game_.events.connect([](EventData* event) {
            auto* ps = dynamic_cast<PlayerScoredData*>(event);
            if (ps && ps->goalsScoredSoFar < 3) {
                std::cout << "Coach: well done, " << ps->playerName << "!" << std::endl;
            }
        });
    }
};

int main() {
    printTitle();

    Game game;
    Player player("John", game);
    Coach coach(game);

    player.score();
    player.score();
    player.score();

    return 0;
}
