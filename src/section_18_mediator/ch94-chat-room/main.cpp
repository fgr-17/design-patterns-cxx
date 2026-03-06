/**
 *    @file main.cpp
 *    @brief ch-94 Chat Room
 *    @author rouxfederico@gmail.com
 */

#include <chatroom.h>
#include <person.h>

#include <iostream>

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 18 :\e[0m Mediator" << std::endl;
    std::cout << "\e[1mChapter 94 : Chat Room\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    ChatRoom room;
    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.say("hi room");
    jane.say("oh, hey John");

    Person simon{"Simon"};
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("Simon", "glad you could join us!");

    return 0;
}
