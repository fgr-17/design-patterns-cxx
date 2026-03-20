/**
 *    @file observer-excercise.cpp
 *    @brief Observer Coding Exercise
 *    @brief Imagine a game where one or more rats can attack a player. Each individual rat has an
 *    @brief attack  value of 1. However, rats attack as a swarm, so each rat's attack  value is
 *    @brief equal to the total number of rats in play.
 *    @brief Given that a rat enters play through the constructor and leaves play (dies) via its
 *    @brief destructor, please implement the Game  and Rat  classes so that, at any point in the
 *    @brief game, the attack  value of a rat is always consistent.
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>
#include <vector>

struct Rat;

template <typename T>
class Observer {
   public:
    Observer() = default;
    Observer(const Observer& other) = default;
    Observer& operator=(const Observer& other) = default;
    Observer(Observer&& other) = default;
    Observer& operator=(Observer&& other) = default;
    virtual ~Observer() = default;

    virtual void fieldChanged(T& source, const std::string& fieldName) = 0;
};

template <typename T>
class Observable {
    std::vector<Observer<T>*> observers_;

   public:
    void notify(T& source, const std::string& fieldName) {
        for (auto observer : observers_) {
            observer->fieldChanged(source, fieldName);
        }
    }

    void subscribe(Observer<T>& observer) {
        observers_.emplace_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // observers_.erase(std::remove(observers_.begin(), observers_.end(), &observer),
        //                  observers_.end());
        std::erase(observers_, &observer);
    }
};

struct Game : Observable<Game> {
   private:
    int ratCount_{0};

   public:
    [[nodiscard]] int getRatCount() const {
        return ratCount_;
    }

    void setRatCount(int ratCount_) {
        if (this->ratCount_ == ratCount_) return;
        this->ratCount_ = ratCount_;
        notify(*this, "ratCount_");
    }

    void increaseRatCount() {
        setRatCount(ratCount_ + 1);
    }

    void decreaseRatCount() {
        setRatCount(ratCount_ - 1);
    }
};

struct Rat : Observer<Game> {
    Game& game;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    int attack{1};
    std::string name;

    Rat(Game& game) : game(game) {
        game.subscribe(*this);
        game.increaseRatCount();
        name = "Rat " + std::to_string(game.getRatCount());
    }

    ~Rat() override {
        game.decreaseRatCount();
        game.unsubscribe(*this);
    }

    Rat(Rat& other) = delete;
    Rat(Rat&& other) = delete;
    Rat& operator=(Rat& other) = delete;
    Rat& operator=(Rat&& other) = delete;

    void fieldChanged(Game& source, const std::string& fieldName) override {
        if (fieldName == "ratCount_") {
            attack = source.getRatCount();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Rat& rat) {
        os << rat.name;
        os << " has attack " << rat.attack;
        return os;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 20 :\e[0m Observer" << std::endl;
    std::cout << "\e[1mObserver Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Game game;
    Rat rat1(game);
    std::cout << rat1 << std::endl;
    Rat rat2(game);
    std::cout << rat1 << std::endl;
    std::cout << rat2 << std::endl;

    {
        Rat rat3(game);
        std::cout << rat1 << std::endl;
        std::cout << rat2 << std::endl;
        std::cout << rat3 << std::endl;
    }

    std::cout << rat1 << std::endl;
    std::cout << rat2 << std::endl;

    return 0;
}
