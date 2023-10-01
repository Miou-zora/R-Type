/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Transformable.test
*/

#include "Transformable.hpp"

#include <gtest/gtest.h>

TEST(Transformable, init)
{
    rtype::component::Transformable transformable;

    ASSERT_EQ(transformable.position.x, 0);
    ASSERT_EQ(transformable.position.y, 0);
    ASSERT_EQ(transformable.scale, 1);
    ASSERT_EQ(transformable.rotation, 0);
}

TEST(Transformable, initWithValues)
{
    rtype::component::Transformable transformable(rtype::utils::Vector<float>(1, 2), 3, 4);

    ASSERT_EQ(transformable.position.x, 1);
    ASSERT_EQ(transformable.position.y, 2);
    ASSERT_EQ(transformable.scale, 3);
    ASSERT_EQ(transformable.rotation, 4);
}

TEST(Transformable, copy)
{
    rtype::component::Transformable transformable(rtype::utils::Vector<float>(1, 2), 3, 4);
    rtype::component::Transformable transformable2(transformable);

    ASSERT_EQ(transformable2.position.x, 1);
    ASSERT_EQ(transformable2.position.y, 2);
    ASSERT_EQ(transformable2.scale, 3);
    ASSERT_EQ(transformable2.rotation, 4);
}

TEST(Transformable, assignation)
{
    rtype::component::Transformable transformable(rtype::utils::Vector<float>(1, 2), 3, 4);
    rtype::component::Transformable transformable2;

    transformable2 = transformable;
    ASSERT_EQ(transformable2.position.x, 1);
    ASSERT_EQ(transformable2.position.y, 2);
    ASSERT_EQ(transformable2.scale, 3);
    ASSERT_EQ(transformable2.rotation, 4);
}
