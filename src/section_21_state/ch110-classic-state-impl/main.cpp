/**
 *    @file main.cpp
 *    @brief ch-110 Classic State Implementation
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>

class LightSwitch;

class State {
   public:
    virtual void on([[maybe_unused]] LightSwitch& sw) {
        std::cout << "Light is already on" << std::endl;
    }

    virtual void off([[maybe_unused]] LightSwitch& sw) {
        std::cout << "Light is already off" << std::endl;
    }

    virtual ~State() = default;
    State() = default;
    State(const State& other) = delete;
    State& operator=(const State& other) = delete;
    State(State&& other) = delete;
    State& operator=(State&& other) = delete;
};

class OnState final : public State {
   public:
    OnState() {
        std::cout << "Light is on" << std::endl;
    }

    void off(LightSwitch& sw) override;
};

class OffState final : public State {
   public:
    OffState() {
        std::cout << "Light is off" << std::endl;
    }

    void on(LightSwitch& sw) override;
};

class LightSwitch {
   private:
    std::unique_ptr<State> state_;

   public:
    LightSwitch(std::unique_ptr<State> state) : state_(std::move(state)) {}
    LightSwitch() : state_(std::make_unique<OffState>()) {}
    void setState(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }

    void on() {
        state_->on(*this);
    }

    void off() {
        state_->off(*this);
    }
};

void OnState::off(LightSwitch& sw) {
    std::cout << "Turning light off..." << std::endl;
    sw.setState(std::make_unique<OffState>());
}

void OffState::on(LightSwitch& sw) {
    std::cout << "Turning light on..." << std::endl;
    sw.setState(std::make_unique<OnState>());
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 21 :\e[0m State" << std::endl;
    std::cout << "\e[1mChapter 110 : Classic State Implementation\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    LightSwitch ls;
    ls.off();
    ls.on();
    ls.off();
    ls.off();

    return 0;
}
