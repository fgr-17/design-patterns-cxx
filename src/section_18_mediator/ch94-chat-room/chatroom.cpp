/**
 *    @file chatroom.cpp
 *    @brief ch-94 Chat Room
 *    @author rouxfederico@gmail.com
 */

#include <chatroom.h>
#include <person.h>

#include <ranges>

void ChatRoom::broadcast(const std::string& origin, const std::string& message) const {
    for (const auto& person : people) {
        if (person->name != origin) {
            person->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* person) {
    const std::string joinMsg = person->name + " joins the chat";
    broadcast("room", joinMsg);
    person->room = this;
    people.push_back(person);
}

void ChatRoom::message(const std::string& origin, const std::string& who,
                       const std::string& message) {
    auto target = std::ranges::find_if(people, [&](const Person* p) { return p->name == who; });
    if (target != std::end(people)) {
        (*target)->receive(origin, message);
    }
}
