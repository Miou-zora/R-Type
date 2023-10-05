/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Collision.test
*/

#include "Collision.hpp"

#include <gtest/gtest.h>

TEST(Collision, init)
{
    rtype::system::Collision collisionSystem;
}

TEST(Collision, casualCollision)
{
    rtype::ecs::Registry registry;
    rtype::system::Collision collisionSystem;
    rtype::ecs::Entity player = registry.spawnEntity();
    rtype::ecs::Entity enemy = registry.spawnEntity();

    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Transformable>();
    registry.addSystem<rtype::component::Collider, rtype::component::Transformable>(rtype::system::Collision());

    registry.addComponent<rtype::component::Collider>(player, rtype::component::Collider(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Transformable>(player, rtype::component::Transformable(rtype::utils::Vector<float>(0, 0)));

    registry.addComponent<rtype::component::Collider>(enemy, rtype::component::Collider(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Transformable>(enemy, rtype::component::Transformable(rtype::utils::Vector<float>(0.8, 0.8)));

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 1);

    registry.getComponents<rtype::component::Transformable>()[enemy].value().position = rtype::utils::Vector<float>(-0.8, -0.8);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 1);

    registry.getComponents<rtype::component::Transformable>()[enemy].value().position = rtype::utils::Vector<float>(-0.8, 0.8);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 1);

    registry.getComponents<rtype::component::Transformable>()[enemy].value().position = rtype::utils::Vector<float>(0.8, -0.8);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 1);

    registry.getComponents<rtype::component::Transformable>()[enemy].value().position = rtype::utils::Vector<float>(0, 0);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 1);
}

TEST(Collision, casualNoCollision)
{
    rtype::ecs::Registry registry;
    rtype::system::Collision collisionSystem;
    rtype::ecs::Entity player = registry.spawnEntity();
    rtype::ecs::Entity enemy = registry.spawnEntity();

    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Transformable>();
    registry.addSystem<rtype::component::Collider, rtype::component::Transformable>(rtype::system::Collision());

    registry.addComponent<rtype::component::Collider>(player, rtype::component::Collider(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Transformable>(player, rtype::component::Transformable(rtype::utils::Vector<float>(0, 0)));

    registry.addComponent<rtype::component::Collider>(enemy, rtype::component::Collider(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Transformable>(enemy, rtype::component::Transformable(rtype::utils::Vector<float>(1.2, 1.2)));

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[player].value().collideWith.size(), 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Collider>()[enemy].value().collideWith.size(), 0);
}
