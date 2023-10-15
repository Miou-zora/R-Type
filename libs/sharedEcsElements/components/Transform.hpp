/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Transform
*/

#pragma once

#include <string>
#include "Vector.hpp"

namespace rtype::component
{
    /**
     * @brief Transform component used to store the position, scale and rotation of an entity
     */
    struct Transform {

        Transform(rtype::utils::Vector<float> position_ = rtype::utils::Vector<float>(0, 0), float scale_ = 1, float rotation_ = 0): position(position_), scale(scale_), rotation(rotation_) {};
        ~Transform() = default;

        Transform(const Transform &other) = default;
        Transform &operator=(const Transform &other) = default;

        rtype::utils::Vector<float> position;
        float scale;
        float rotation;
    };
}
