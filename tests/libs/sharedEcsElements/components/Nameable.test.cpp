/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Nameable.test
*/

#include "Nameable.hpp"

#include <gtest/gtest.h>

TEST(Nameable, init)
{
    rtype::component::Nameable nameable;

    ASSERT_EQ(nameable.name, "");
}

TEST(Nameable, initWithValues)
{
    rtype::component::Nameable nameable("player1");

    ASSERT_EQ(nameable.name, "player1");
}

TEST(Nameable, copy)
{
    rtype::component::Nameable nameable("player1");
    rtype::component::Nameable nameable2(nameable);

    ASSERT_EQ(nameable2.name, "player1");
}

TEST(Nameable, assignation)
{
    rtype::component::Nameable nameable("player1");
    rtype::component::Nameable nameable2;

    nameable2 = nameable;
    ASSERT_EQ(nameable2.name, "player1");
}
