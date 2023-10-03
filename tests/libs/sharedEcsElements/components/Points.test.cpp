/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Points.test
*/

#include "Points.hpp"

#include <gtest/gtest.h>

TEST(Points, init)
{
    rtype::component::Points points;

    ASSERT_EQ(points.value, 0);
}

TEST(Points, initWithValues)
{
    rtype::component::Points points(4);

    ASSERT_EQ(points.value, 4);
}

TEST(Points, copy)
{
    rtype::component::Points points(4);
    rtype::component::Points points2(points);

    ASSERT_EQ(points2.value, 4);
}

TEST(Points, assignation)
{
    rtype::component::Points points(4);
    rtype::component::Points points2;

    points2 = points;
    ASSERT_EQ(points2.value, 4);
}
