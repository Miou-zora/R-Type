/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Health
*/

#pragma once
namespace rtype::component
{
    struct Health
    {
        Health(int value_ = 1) : value(value_){};
        ~Health() = default;

        Health(const Health &other) = default;
        Health &operator=(const Health &other) = default;

        int value;
    };
}
