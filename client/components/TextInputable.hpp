/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TextInputable
*/

#pragma once
#include <string>

namespace rtype::component
{
    /**
     * @brief TextInputable component used indicate that the entity is a text input
     */
    struct TextInputable
    {
        TextInputable(std::size_t maxLength_ = 80): maxLength(maxLength_) {};
        ~TextInputable() = default;

        TextInputable(const TextInputable &other) = default;
        TextInputable &operator=(const TextInputable &other) = default;

        std::size_t maxLength;
    };
}
