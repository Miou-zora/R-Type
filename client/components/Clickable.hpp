/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Clickable
*/

#pragma once

#include <functional>

namespace rtype::component
{
    /**
     * @brief Clickable component used to store the click state of an entity. It also stores a callback function to be called when the entity is clicked
    */
    struct Clickable
    {
        Clickable(void) = default;
        ~Clickable(void) = default;

        Clickable(const Clickable &other) = default;
        Clickable &operator=(const Clickable &other) = default;

        bool isHover = false;
        bool isDown = false;
        std::function<void(void)> onClick = [](){};
    };
}
