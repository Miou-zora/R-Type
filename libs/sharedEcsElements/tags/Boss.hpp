/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Boss
*/

#pragma once

namespace rtype::tag
{
    /**
     * @brief Boss tag used to mark an entity as a boss
     */
    struct Boss {
        Boss() = default;
        ~Boss() = default;
        Boss(const Boss &) = default;
        Boss &operator=(const Boss &) = default;
    };
}
