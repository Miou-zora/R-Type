/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Damage.test
*/

#include "Damage.hpp"

#include <gtest/gtest.h>

TEST(Damage, init)
{
    rtype::component::Damage Damage;

    ASSERT_EQ(Damage.value, 1);
}

TEST(Damage, initWithValues)
{
    rtype::component::Damage Damage(4);

    ASSERT_EQ(Damage.value, 4);
}

TEST(Damage, copy)
{
    rtype::component::Damage Damage(4);
    rtype::component::Damage Damage2(Damage);

    ASSERT_EQ(Damage2.value, 4);
}

TEST(Damage, assignation)
{
    rtype::component::Damage Damage(4);
    rtype::component::Damage Damage2;

    Damage2 = Damage;
    ASSERT_EQ(Damage2.value, 4);
}

