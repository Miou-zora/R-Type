/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Explosive
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief TextInputable component used indicate that the entity is an explosive
     */
    struct Explosive
    {
        Explosive() = default;
        ~Explosive() = default;

        Explosive(const Explosive &other) = default;
        Explosive &operator=(const Explosive &other) = default;
    };
}
