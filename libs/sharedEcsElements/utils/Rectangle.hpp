/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Rectangle
*/

#pragma once

namespace raylib
{
#include "raylib.h"
}

namespace rtype::utils
{
    /**
     * @brief Rectangle class used to store a rectangle
     */
    class Rectangle
    {
    public:
        Rectangle(float x, float y, float width, float height)
            : rectangle{x, y, width, height}
        {
        };
        Rectangle(const raylib::Rectangle &rectangle_ = raylib::Rectangle({0.f, 0.f, 0.f, 0.f})) : rectangle(rectangle_){};
        ~Rectangle() = default;

        Rectangle(const Rectangle &other) = default;
        Rectangle &operator=(const Rectangle &other) = default;

        raylib::Rectangle rectangle;
    };
}
