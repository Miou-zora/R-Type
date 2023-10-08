/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** VelocityApplicator.test
*/

#include "VelocityApplicator.hpp"

#include <gtest/gtest.h>

TEST(VelocityApplicator, init)
{
    rtype::system::VelocityApplicator velocityApplicator;
}

TEST(VelocityApplicator, apply)
{
    rtype::system::VelocityApplicator velocityApplicator;
    rtype::ecs::Registry registry;
    rtype::ecs::SparseArray<rtype::component::Transform> transformables;
    rtype::ecs::SparseArray<rtype::component::Velocity> velocities;

    transformables.insertAt(0, rtype::component::Transform());
    ASSERT_EQ(transformables[0].value().position.x, 0);
    ASSERT_EQ(transformables[0].value().position.y, 0);
    velocities.insertAt(0, rtype::component::Velocity(rtype::utils::Vector<float>(1, 1)));
    velocityApplicator(registry, transformables, velocities);
    ASSERT_EQ(transformables[0].value().position.x, 1);
    ASSERT_EQ(transformables[0].value().position.y, 1);
    ASSERT_EQ(velocities[0].value().vector.x, 0);
    ASSERT_EQ(velocities[0].value().vector.y, 0);
}
