/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** EnemyNumber
*/

#pragma once
#include <chrono>

namespace rtype::component {
/**
 * @brief LastUpdate component used to store the number of an ally
 */
struct LastUpdate {
    LastUpdate(std::chrono::time_point<std::chrono::system_clock> lastUpdate_ = std::chrono::system_clock::now())
        : lastUpdate(lastUpdate_) {};
    ~LastUpdate(void) = default;

    LastUpdate(const LastUpdate& other) = default;
    LastUpdate& operator=(const LastUpdate& other) = default;

    void tick(void)
    {
        lastUpdate = std::chrono::system_clock::now();
    }
    
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
};
}
