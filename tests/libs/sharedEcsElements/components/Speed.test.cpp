/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Speed.test
*/

#include "Speed.hpp"

#include <gtest/gtest.h>

TEST(Speed, init)
{
    rtype::component::Speed speed;

    ASSERT_EQ(speed.value, 100);
}

TEST(Speed, initWithValues)
{
    rtype::component::Speed speed(4);

    ASSERT_EQ(speed.value, 4);
}

TEST(Speed, copy)
{
    rtype::component::Speed speed(4);
    rtype::component::Speed speed2(speed);

    ASSERT_EQ(speed2.value, 4);
}

TEST(Speed, assignation)
{
    rtype::component::Speed speed(4);
    rtype::component::Speed speed2;

    speed2 = speed;
    ASSERT_EQ(speed2.value, 4);
}

