/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Nameable
*/

#pragma once

#include <string>

namespace rtype::component
{
    /**
     * @brief Nameable component used to store the name of an entity
     *
     */
    struct Nameable {
        Nameable(std::string name_ = ""): name(name_) {};
        ~Nameable() = default;

        Nameable(const Nameable &other) = default;
        Nameable &operator=(const Nameable &other) = default;

        std::string name;
    };
}
