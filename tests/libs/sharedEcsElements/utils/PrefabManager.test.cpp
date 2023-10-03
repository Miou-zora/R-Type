/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** PrefabManager.test
*/

#include "PrefabManager.hpp"

#include <gtest/gtest.h>

TEST(PrefabManager, init)
{
    rtype::utils::PrefabManager &manager = rtype::utils::PrefabManager::getInstance();
    rtype::ecs::Registry registry;

    struct TestComponent {};
    registry.registerComponent<TestComponent>();
    try {
        manager.addComponent<TestComponent>("prefab that doesn't exist");
        FAIL();
    } catch (rtype::ecs::OutOfRange) {
        SUCCEED();
    }

    try {
        manager.instantiate("prefab that doesn't exist", registry);
        FAIL();
    } catch (rtype::ecs::OutOfRange) {
        SUCCEED();
    }
}

TEST(PrefabManager, casualUse)
{
    struct TestComponent { TestComponent(int a_): a(a_) {}; int a; };

    rtype::utils::PrefabManager &manager = rtype::utils::PrefabManager::getInstance();
    rtype::ecs::Registry registry;

    registry.registerComponent<TestComponent>();
    manager.createPrefab("testPrefab");
    manager.addComponent<TestComponent>("testPrefab", 42);
    rtype::ecs::Entity entity1 = manager.instantiate("testPrefab", registry);
    rtype::ecs::Entity entity2 = manager.instantiate("testPrefab", registry);
    registry.getComponents<TestComponent>()[entity2].value().a = 21;
    ASSERT_EQ(registry.getComponents<TestComponent>()[entity1].value().a, 42);
    ASSERT_EQ(registry.getComponents<TestComponent>()[entity2].value().a, 21);
}
