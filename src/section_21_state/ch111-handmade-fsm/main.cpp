/**
 *    @file main.cpp
 *    @brief ch-111 Handmade FSM
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <map>
#include <vector>

enum class State { off_hook, connecting, connected, on_hold, on_hook };

inline std::ostream& operator<<(std::ostream& os, State state) {
    switch (state) {
        case State::off_hook:
            return os << "off_hook";
        case State::connecting:
            return os << "connecting";
        case State::connected:
            return os << "connected";
        case State::on_hold:
            return os << "on_hold";
        case State::on_hook:
            return os << "on_hook";
        default:
            return os << "unknown state";
    }
    return os;
}

enum class Trigger {
    call_dialed,
    hung_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};

inline std::ostream& operator<<(std::ostream& os, Trigger trigger) {
    switch (trigger) {
        case Trigger::call_dialed:
            return os << "call_dialed";
        case Trigger::hung_up:
            return os << "hung_up";
        case Trigger::call_connected:
            return os << "call_connected";
        case Trigger::placed_on_hold:
            return os << "placed_on_hold";
        case Trigger::taken_off_hold:
            return os << "taken_off_hold";
        case Trigger::left_message:
            return os << "left_message";
        case Trigger::stop_using_phone:
            return os << "stop_using_phone";
        default:
            return os << "unknown trigger";
    }
    return os;
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 21 :\e[0m State" << std::endl;
    std::cout << "\e[1mChapter 111 : Handmade FSM\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    std::map<State, std::vector<std::pair<Trigger, State>>> rules;

    rules[State::off_hook] = {
        {Trigger::call_dialed, State::connecting},
        {Trigger::stop_using_phone, State::on_hook},
    };

    rules[State::connecting] = {
        {Trigger::call_connected, State::connected},
        {Trigger::hung_up, State::off_hook},
    };

    rules[State::connected] = {
        {Trigger::left_message, State::off_hook},
        {Trigger::hung_up, State::off_hook},
        {Trigger::placed_on_hold, State::on_hold},
    };

    rules[State::on_hold] = {
        {Trigger::taken_off_hold, State::connected},
        {Trigger::hung_up, State::off_hook},
    };

    State currentState{State::off_hook};
    State exitState{State::on_hook};

    while (true) {
        std::cout << "The phone is currently " << currentState << std::endl;
        std::cout << "Select a trigger:" << std::endl;

        int index{0};
        for (const auto& [trigger, state] : rules[currentState]) {
            std::cout << "\t" << index << "." << trigger << " -> " << state << std::endl;
            index++;
        }

        std::cout << "Select a trigger: " << std::endl;
        int input{0};
        std::cin >> input;

        if (input < 0 || input >= static_cast<int>(rules[currentState].size())) {
            std::cout << "Invalid trigger" << std::endl;
            continue;
        }

        currentState = rules[currentState][input].second;

        if (currentState == exitState) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }

    return 0;
}
