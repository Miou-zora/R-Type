/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Damage
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief Damage component used to store the damage of an entity
     *
     */
    struct Damage
    {
        Damage(int value_ = 1) : value(value_){};
        ~Damage() = default;

        Damage(const Damage &other) = default;
        Damage &operator=(const Damage &other) = default;

        int value;
    };
}
