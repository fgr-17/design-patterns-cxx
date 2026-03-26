/**
 *    @file main.cpp
 *    @brief ch-112 Boost MSM
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>
#include <vector>

#include "boost/msm/back/state_machine.hpp"
#include "boost/msm/front/functor_row.hpp"
#include "boost/msm/front/state_machine_def.hpp"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;
using namespace std::string_literals;

const std::vector<std::string> stateNames{
    "off_hook"s, "connecting"s, "connected"s, "on_hold"s, "on_hook"s,
};

struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine> {
    bool angry_{true};
    struct OffHook : state<> {};
    struct Connecting : state<> {
        template <class Event, class FSM>
        void on_entry([[maybe_unused]] const Event& ev, [[maybe_unused]] FSM& fsm) {
            std::cout << "Connecting..." << std::endl;
        }
    };

    struct Connected : state<> {};
    struct OnHold : state<> {};
    struct PhoneDestroyed : state<> {};

    struct PhoneBeingDestroyed {
        template <class EVT, class FSM, class SourceState, class TargetState>
        void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
            std::cout << "Phone being destroyed..." << std::endl;
        }
    };

    struct CanDestroyPhone {
        template <class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(EVT const&, FSM& fms, SourceState&, TargetState&) {
            return fms.angry_;
        }
    };

    // NOLINTNEXTLINE(readability-identifier-naming)
    struct transition_table
        : mpl::vector<Row<OffHook, CallDialed, Connecting>,
                      Row<Connecting, CallConnected, Connected>,
                      Row<Connected, PlacedOnHold, OnHold>,
                      Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed,
                          CanDestroyPhone>>  // with guard condition and action
    {};

    using initial_state = OffHook;

    template <class Event, class FSM>
    void no_transition(Event const& e, FSM&, int state) {
        std::cout << "No transition from " << stateNames[state] << " on " << typeid(e).name()
                  << std::endl;
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 21 :\e[0m State" << std::endl;
    std::cout << "\e[1mChapter 112 : Boost MSM\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    msm::back::state_machine<PhoneStateMachine> phone;
    auto info = [&]() {
        const auto states = phone.current_state();
        const auto i = *states;
        std::cout << "The phone is currently " << stateNames[i] << std::endl;
    };

    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();

    // using no_transition handler
    phone.process_event(CallDialed{});
    info();

    return 0;
}
