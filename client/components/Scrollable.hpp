/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Scrollable
*/

#pragma once

#include "Vector.hpp"

namespace rtype::component
{
    /**
     * @brief Scrollable component used to store the scroll state of an entity.
     */
    struct Scrollable
    {
        Scrollable(rtype::utils::Vector<float> scroll_ = rtype::utils::Vector<float>(0, 0), float speed_ = 1)
            : scroll(scroll_), speed(speed_){};
        ~Scrollable(void) = default;

        Scrollable(const Scrollable &other) = default;
        Scrollable &operator=(const Scrollable &other) = default;

        rtype::utils::Vector<float> scroll;
        float speed;
    };
}
