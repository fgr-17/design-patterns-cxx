/**
 *    @file mediator-excercise.cpp
 *    @brief
 *    @brief Mediator Coding Exercise
 *    @brief Our system has any number of instances of Participant  classes. Each Participant has a
 *    @brief value  integer, initially zero.
 *    @brief A participant can `say(int value)` a particular value, which is broadcast to all other
 *    @brief participants. At this point in time, every other participant is obliged to increase
 *    @brief their value by the value being broadcast.
 *    @brief Example:
 *    @brief * Two participants start with values 0 and 0 respectively
 *    @brief * Participant 1 broadcasts the value 3. We now have Participant 1 value = 0,
 *    @brief   Participant 2 value = 3
 *    @brief * Participant 2 broadcasts the value 2. We now have Participant 1 value = 2,
 *    @brief   Participant 2 value = 3
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <ostream>
#include <vector>

struct IParticipant {
    virtual void say(int value) = 0;
    virtual ~IParticipant() = default;
    IParticipant() = default;
    IParticipant(const IParticipant&) = delete;
    IParticipant(IParticipant&&) = delete;
    IParticipant& operator=(const IParticipant&) = delete;
    IParticipant& operator=(IParticipant&&) = delete;
};

struct Mediator;

struct Participant : IParticipant {
    int value{0};
    Mediator& mediator;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

    explicit Participant(Mediator& mediator);
    void say(int value) override;
};

struct Mediator {
    std::vector<Participant*> participants;

    void broadcast(const Participant* participant, int value) {
        for (auto* p : participants) {
            if (p != participant) {
                p->value += value;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Mediator& m) {
        for (const auto* p : m.participants) {
            os << p->value << " ";
        }
        return os;
    }
};

inline Participant::Participant(Mediator& m) : mediator(m) {
    mediator.participants.push_back(this);
}

inline void Participant::say(int value) {
    mediator.broadcast(this, value);
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 18 :\e[0m Mediator" << std::endl;
    std::cout << "\e[1mMediator Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Mediator mediator;
    Participant p1(mediator);
    Participant p2(mediator);

    p1.say(3);
    p2.say(2);

    std::cout << mediator << std::endl;
    return 0;
}
