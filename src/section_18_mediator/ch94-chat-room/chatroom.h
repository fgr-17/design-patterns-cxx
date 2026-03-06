/**
 *    @file chatroom.h
 *    @brief ch-94 Chat Room
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <vector>

#include "person.h"

struct ChatRoom {
    std::vector<Person*> people;

    void broadcast(const std::string& origin, const std::string& message) const;
    void join(Person* person);
    void message(const std::string& origin, const std::string& who, const std::string& message);
};