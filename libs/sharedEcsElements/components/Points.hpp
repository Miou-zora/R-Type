/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Points
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief Points component used to store the points(score) of an entity
     *
     */
    struct Points {
        Points(int value_ = 0) : value(value_){};
        ~Points() = default;

        Points(const Points &other) = default;
        Points &operator=(const Points &other) = default;

        int value;
    };
}
