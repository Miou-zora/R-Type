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

        Transformable(utils::Vector<float> position_ = utils::Vector<float>(0, 0), float scale_ = 1, float rotation_ = 0): position(position_), scale(scale_), rotation(rotation_) {};
        ~Transformable() = default;

        Transformable(const Transformable &other) = default;
        Transformable &operator=(const Transformable &other) = default;

        utils::Vector<float> position;
        float scale;
        float rotation;
    };
}
