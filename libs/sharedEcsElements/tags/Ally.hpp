/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Ally
*/

#pragma once

namespace rtype::tag
{
    /**
     * @brief Ally tag used to mark an entity as an ally
     */
    struct Ally {
        Ally() = default;
        ~Ally() = default;
        Ally(const Ally &) = default;
        Ally &operator=(const Ally &) = default;
    };
}
