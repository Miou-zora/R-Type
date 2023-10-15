/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Enemy
*/

#pragma once

namespace rtype::tag
{
    /**
     * @brief Enemy tag used to mark an entity as an enemy
     */
    struct Enemy {
        Enemy() = default;
        ~Enemy() = default;
        Enemy(const Enemy &) = default;
        Enemy &operator=(const Enemy &) = default;
    };
}
