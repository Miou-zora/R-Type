/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** VelocityApplicator
*/

#pragma once

#include "Registry.hpp"
#include "Transformable.hpp"
#include "Velocity.hpp"

namespace rtype::system
{
    class VelocityApplicator
    {
    public:
        VelocityApplicator() = default;
        ~VelocityApplicator() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Transformable> &transformables,
            ecs::SparseArray<rtype::component::Velocity> &velocities);
    };
}
