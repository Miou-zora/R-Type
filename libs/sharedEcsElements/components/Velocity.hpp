/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Velocity
*/

#pragma once

#include "Vector.hpp"

namespace rtype::component
{
    struct Velocity {

        Velocity(void) : vector(0, 0) {};
        template<typename ...Args>
        Velocity(Args... args) : vector(args...) {};
        ~Velocity() = default;

        Velocity(const Velocity &pos) = default;
        Velocity &operator=(const Velocity &pos) = default;

        rtype::utils::Vector<float> vector;
    };
};
