/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Collider
*/

#pragma once

#include <vector>
#include "ECS.hpp"
#include "Vector.hpp"

namespace rtype::component
{
    /**
     * @brief Collider component that store size of collider of entity and store a list of other entity that collide with it
    */
    struct Collider
    {
        Collider(float width = 0, float height = 0) : size(width, height)
        {
            if (width < 0)
                size.x = 0;
            if (height < 0)
                size.y = 0;
        };

        Collider(rtype::utils::Vector<float> size_) : size(size_)
        {
            if (size.x < 0)
                size.x = 0;
            if (size.y < 0)
                size.y = 0;
        };

        ~Collider() = default;

        Collider(const Collider &other) = default;
        Collider &operator=(const Collider &other) = default;

        rtype::utils::Vector<float> size;
        std::vector<rtype::ecs::Entity> collideWith;
    };
}
