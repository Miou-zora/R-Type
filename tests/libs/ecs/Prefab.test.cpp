/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsPrefab
*/

#include "Prefab.hpp"

#include <gtest/gtest.h>

TEST(Prefab, init)
{
    ecs::Prefab prefab;
    ecs::Registry registry;

    ASSERT_EQ(prefab.instantiate(registry), 0);
}

TEST(prefab, casualCase)
{
    struct ComponentA {
        ComponentA(int _value): value(_value) { }
        int value;
    };

    struct ComponentB {
        ComponentB(float _value): value(_value) { }
        float value;
    };
    ecs::Registry reg;

    reg.registerComponent<ComponentA>();
    reg.registerComponent<ComponentB>();

    {
        ecs::Prefab prefab;
        prefab.addComponent<ComponentA>(42);
        ecs::Entity entity = prefab.instantiate(reg);
        EXPECT_EQ(reg.getComponents<ComponentA>()[entity].value().value, 42);
        EXPECT_FALSE(reg.hasComponent<ComponentB>(entity));
    }

    {
        ecs::Prefab prefab;
        prefab.addComponent<ComponentA>(42);
        prefab.addComponent<ComponentB>(42.42f);
        ecs::Entity entity = prefab.instantiate(reg);
        EXPECT_TRUE(reg.hasComponent<ComponentA>(entity));
        EXPECT_EQ(reg.getComponents<ComponentA>()[entity].value().value, 42);
        EXPECT_TRUE(reg.hasComponent<ComponentB>(entity));
        EXPECT_EQ(reg.getComponents<ComponentB>()[entity].value().value, 42.42f);
    }

    {
        ecs::Prefab prefab;
        prefab.addComponent<ComponentA>(42);
        prefab.addComponent<ComponentB>(42.42f);
        prefab.addComponent<ComponentA>(41);
        prefab.addComponent<ComponentB>(41.41f);
        ecs::Entity entity = prefab.instantiate(reg);
        EXPECT_TRUE(reg.hasComponent<ComponentA>(entity));
        EXPECT_EQ(reg.getComponents<ComponentA>()[entity].value().value, 41);
        EXPECT_TRUE(reg.hasComponent<ComponentB>(entity));
        EXPECT_EQ(reg.getComponents<ComponentB>()[entity].value().value, 41.41f);
    }
}
