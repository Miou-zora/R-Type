/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Taker
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief Taker component used to indicate that an entity can take loot
     */
    struct Taker
    {
        Taker(void) = default;
        ~Taker() = default;

        Taker(const Taker &other) = default;
        Taker &operator=(const Taker &other) = default;
    };
}
