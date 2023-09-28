/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsEntity
*/

#include "Entity.hpp"

#include <gtest/gtest.h>

TEST(entity, init)
{
    ecs::Entity entity(42);

    ASSERT_EQ(entity, 42);
}
