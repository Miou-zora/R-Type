/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control
*/

#pragma once

#include "Registry.hpp"
#include "Controllable.hpp"
#include "Velocity.hpp"

namespace rtype::system
{
    class Control
    {
    public:
        Control() = default;
        ~Control() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Controllable> const &controllables,
            ecs::SparseArray<rtype::component::Velocity> &velocities);

    };
}
