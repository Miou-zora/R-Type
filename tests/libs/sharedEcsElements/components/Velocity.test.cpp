/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Velocity.test
*/

#include "Velocity.hpp"

#include <gtest/gtest.h>

TEST(Velocity, init)
{
    rtype::component::Velocity velocity;

    ASSERT_EQ(velocity.vector.x, 0);
    ASSERT_EQ(velocity.vector.y, 0);
}

TEST(Velocity, initWithValues)
{
    rtype::component::Velocity velocity(1, 2);

    ASSERT_EQ(velocity.vector.x, 1);
    ASSERT_EQ(velocity.vector.y, 2);

    rtype::component::Velocity velocity2(rtype::utils::Vector<float>(3, 4));

    ASSERT_EQ(velocity2.vector.x, 3);
    ASSERT_EQ(velocity2.vector.y, 4);
}

TEST(Velocity, copy)
{
    rtype::component::Velocity velocity(1, 2);
    rtype::component::Velocity velocity2(velocity);

    ASSERT_EQ(velocity2.vector.x, 1);
    ASSERT_EQ(velocity2.vector.y, 2);
}

TEST(Velocity, assignation)
{
    rtype::component::Velocity velocity(1, 2);
    rtype::component::Velocity velocity2;

    velocity2 = velocity;
    ASSERT_EQ(velocity2.vector.x, 1);
    ASSERT_EQ(velocity2.vector.y, 2);
}
