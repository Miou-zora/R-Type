/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** VelocityApplicator
*/

#include "VelocityApplicator.hpp"
#include "Zipper.hpp"
#include "Vector.hpp"

void rtype::system::VelocityApplicator::operator()(ecs::Registry &registry,
                                 ecs::SparseArray<rtype::component::Transformable> &transformables,
                                 ecs::SparseArray<rtype::component::Velocity> &velocities)
{
    (void)registry;
    for (auto &&[transformable, velocity] : ecs::containers::Zipper(transformables, velocities))
    {
        transformable.value().position += velocity.value().vector;
        velocity.value().vector = 0;
    }
}
