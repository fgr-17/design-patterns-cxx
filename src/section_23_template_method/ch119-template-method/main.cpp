/**
 *    @file main.cpp
 *    @brief ch-119 Template Method
 *    @author rouxfederico@gmail.com
 */

#include <iostream>

class Game {
   public:
    Game(int numberOfPlayers) : numberOfPlayers_(numberOfPlayers) {}
    virtual ~Game() = default;
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void run() {
        start();
        while (!haveWinner()) {
            takeTurn();
        }
        std::cout << "Player " << getWinner() << " wins." << std::endl;
    }

   protected:
    virtual void start() = 0;
    [[nodiscard]] virtual bool haveWinner() = 0;
    virtual void takeTurn() = 0;
    [[nodiscard]] virtual int getWinner() = 0;

    [[nodiscard]] int numberOfPlayers() const {
        return numberOfPlayers_;
    }

    [[nodiscard]] int currentPlayer() const {
        return currentPlayer_;
    }

    void setCurrentPlayer(int player) {
        currentPlayer_ = player;
    }

   private:
    int numberOfPlayers_;
    int currentPlayer_{0};
};

class Chess final : public Game {
   public:
    Chess() : Game(2) {}

    void start() override {
        std::cout << "Starting chess game with " << numberOfPlayers() << " players." << std::endl;
    }

    bool haveWinner() override {
        return turns_ >= maxTurns;
    }

    void takeTurn() override {
        std::cout << "Turn " << turns_ << " taken by player " << currentPlayer() << std::endl;
        turns_++;
        setCurrentPlayer((currentPlayer() + 1) % numberOfPlayers());
    }

    [[nodiscard]] int getWinner() override {
        return currentPlayer();
    }

   private:
    int turns_{0};
    static constexpr int maxTurns{10};
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 23 :\e[0m Template Method" << std::endl;
    std::cout << "\e[1mChapter 119 : Template Method\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();
    Chess chess;
    chess.run();
    return 0;
}
