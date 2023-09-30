/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Transformable
*/

#pragma once

#include <string>
#include "Vector.hpp"

namespace component
{
    struct Transformable {

        Transformable() {}
        ~Transformable() = default;

        Transformable(const Transformable &other) = default;
        Transformable &operator=(const Transformable &other) = default;

        Vector<float> position;
        float rotation;
        float scale;
    };
}
