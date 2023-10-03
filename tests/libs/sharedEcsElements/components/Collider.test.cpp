/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Collider.test
*/

#include "Collider.hpp"

#include <gtest/gtest.h>

TEST(Collider, init)
{
    rtype::component::Collider collider;

    ASSERT_EQ(collider.size.x, 0);
    ASSERT_EQ(collider.size.y, 0);
    ASSERT_EQ(collider.collideWith.size(), 0);
}

TEST(Collider, initWithValues)
{
    rtype::component::Collider collider(4, 8);

    ASSERT_EQ(collider.size.x, 4);
    ASSERT_EQ(collider.size.y, 8);
    ASSERT_EQ(collider.collideWith.size(), 0);
}

TEST(Collider, copy)
{
    rtype::component::Collider collider(4, 8);
    rtype::component::Collider collider2(collider);

    ASSERT_EQ(collider2.size.x, 4);
    ASSERT_EQ(collider2.size.y, 8);
}

TEST(Collider, assignation)
{
    rtype::component::Collider collider(4, 8);
    rtype::component::Collider collider2;

    collider2 = collider;
    ASSERT_EQ(collider2.size.x, 4);
    ASSERT_EQ(collider2.size.y, 8);
}
