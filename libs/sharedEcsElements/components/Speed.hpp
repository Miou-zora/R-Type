/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Speed
*/

#pragma once

namespace rtype::component
{
    struct Speed
    {
        Speed(int value_ = 100) : value(value_){};
        ~Speed() = default;

        Speed(const Speed &other) = default;
        Speed &operator=(const Speed &other) = default;

        int value;
    };
}