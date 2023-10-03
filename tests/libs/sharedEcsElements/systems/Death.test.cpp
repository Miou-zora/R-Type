/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Death.test
*/

#include "Death.hpp"

#include <gtest/gtest.h>

TEST(Death, init)
{
    rtype::system::Death death;
}

TEST(Death, casual)
{
    rtype::ecs::Registry registry;
    rtype::system::Death death;
    rtype::ecs::Entity player = registry.spawnEntity();
    rtype::ecs::Entity enemy = registry.spawnEntity();

    registry.registerComponent<rtype::component::Health>();
    registry.addSystem<rtype::component::Health>(rtype::system::Death());

    registry.addComponent<rtype::component::Health>(player, rtype::component::Health(1));
    registry.addComponent<rtype::component::Health>(enemy, rtype::component::Health(0));

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[0].has_value(), true);
    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[1].has_value(), false);
}

TEST(Death, no_death)
{
    rtype::ecs::Registry registry;
    rtype::system::Death death;
    rtype::ecs::Entity player = registry.spawnEntity();
    rtype::ecs::Entity enemy = registry.spawnEntity();

    registry.registerComponent<rtype::component::Health>();
    registry.addSystem<rtype::component::Health>(rtype::system::Death());

    registry.addComponent<rtype::component::Health>(player, rtype::component::Health(1));
    registry.addComponent<rtype::component::Health>(enemy, rtype::component::Health(1));

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[0].has_value(), true);
    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[1].has_value(), true);
}
