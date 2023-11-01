/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Killable
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief Killable component used to store the killable state of an entity
     */
    struct Killable
    {
        Killable(void) = default;
        ~Killable() = default;

        Killable(const Killable &other) = default;
        Killable &operator=(const Killable &other) = default;

        bool to_kill = false;
        bool killed = false;
    };
}
