/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TextInput
*/

#pragma once
#include <string>

namespace rtype::component
{
    /**
     * @brief TextInput component used indicate that the entity is a text input
     */
    struct TextInput
    {
        TextInput() = default;
        ~TextInput() = default;

        TextInput(const TextInput &other) = default;
        TextInput &operator=(const TextInput &other) = default;
    };
}
