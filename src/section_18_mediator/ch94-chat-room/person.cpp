/**
 *    @file person.cpp
 *    @brief ch-94 Chat Room
 *    @author rouxfederico@gmail.com
 */

#include "person.h"

#include <iostream>

#include "chatroom.h"

void Person::say(const std::string& message) const {
    room->broadcast(name, message);
}

void Person::pm(const std::string& who, const std::string& message) const {
    room->message(name, who, message);
}

void Person::receive(const std::string& origin, const std::string& message) {
    std::string s{origin + ": \"" + message + "\"\n"};
    std::cout << "[" << name << "'s chat session] " << s;
    chatLog.emplace_back(s);
}

bool Person::operator==(const Person& rhs) const {
    return name == rhs.name;
}

bool Person::operator!=(const Person& rhs) const {
    return name != rhs.name;
}