/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** VelocityApplicator
*/

#pragma once

#include "ECS.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"

namespace rtype::system
{
    /**
     * @brief VelocityApplicator system used to apply the velocity to the position
     */
    class VelocityApplicator
    {
    public:
        VelocityApplicator() = default;
        ~VelocityApplicator() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Transform> &transformables,
            ecs::SparseArray<rtype::component::Velocity> &velocities) const
        {
            (void)registry;
            for (auto &&[transformable, velocity] : ecs::containers::Zipper(transformables, velocities))
            {
                transformable.value().position += velocity.value().vector;
                velocity.value().vector = 0;
            }
        }
    };
}
