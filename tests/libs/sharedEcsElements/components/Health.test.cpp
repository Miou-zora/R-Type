/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Health.test
*/

#include "Health.hpp"

#include <gtest/gtest.h>

TEST(Health, init)
{
    rtype::component::Health health;

    ASSERT_EQ(health.value, 1);
}

TEST(Health, initWithValues)
{
    rtype::component::Health health(4);

    ASSERT_EQ(health.value, 4);
}

TEST(Health, copy)
{
    rtype::component::Health health(4);
    rtype::component::Health health2(health);

    ASSERT_EQ(health2.value, 4);
}

TEST(Health, assignation)
{
    rtype::component::Health health(4);
    rtype::component::Health health2;

    health2 = health;
    ASSERT_EQ(health2.value, 4);
}
