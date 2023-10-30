/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsRegistry
*/

#include "Registry.hpp"

#include <gtest/gtest.h>


TEST(Registry, entity)
{
    rtype::ecs::Registry registry;

    // Test entity creation
    ASSERT_EQ(registry.spawnEntity(), 0);

    // test id incrementation
    ASSERT_EQ(registry.spawnEntity(), 1);
    rtype::ecs::Entity entity = registry.spawnEntity();
    ASSERT_EQ(entity, 2);
    ASSERT_EQ(registry.spawnEntity(), 3);

    // Test entity deletion
    registry.killEntity(entity);
    registry.addSystem([](rtype::ecs::Registry &registry) {
        (void)registry;
    });
    registry.runSystems();

    // Test entity reusing
    ASSERT_EQ(registry.spawnEntity(), 2);
    ASSERT_EQ(registry.spawnEntity(), 4);

    // Test entity from index
    ASSERT_EQ(registry.entityFromIndex(0), 0);
    ASSERT_EQ(registry.entityFromIndex(4), 4);
}

TEST(Registry, componentManagement)
{
    struct ComponentA {
        int value;
    };

    struct ComponentB {
        float value;
    };

    rtype::ecs::Registry registry;

    ASSERT_EQ(registry.registerComponent<ComponentA>().size(), 0);

    // Test get ref component valid
    rtype::ecs::SparseArray<ComponentA> &refSparseArrayA = registry.getComponents<ComponentA>();
    ASSERT_EQ(refSparseArrayA.size(), 0);

    // Test get const ref component valid
    rtype::ecs::SparseArray<ComponentA> const &constRefSparseArrayA = registry.getComponents<ComponentA>();
    ASSERT_EQ(constRefSparseArrayA.size(), 0);

    // Test get ref component invalid
    try {
        rtype::ecs::SparseArray<ComponentB> &refSparseArrayB = registry.getComponents<ComponentB>();
        FAIL();
    } catch (rtype::ecs::BadAnyCast const &e) {
        SUCCEED();
    }

    // Test get const ref component invalid
    try {
        rtype::ecs::SparseArray<ComponentB> const &constRefSparseArrayB = registry.getComponents<ComponentB>();
        FAIL();
    } catch (rtype::ecs::BadAnyCast const &e) {
        SUCCEED();
    }
}

TEST(Registry, componentAssignationAddComponentGetComponentHasComponent)
{
    struct ComponentA {
        ComponentA(int a): value(a) { }
        int value;
    };

    struct ComponentB {
        ComponentB(float b): value(b) { }
        float value;
    };

    rtype::ecs::Registry registry;

    registry.registerComponent<ComponentA>();
    registry.registerComponent<ComponentB>();

    rtype::ecs::Entity entityA = registry.entityFromIndex(0);
    rtype::ecs::Entity entityB = registry.entityFromIndex(1);

    registry.addComponent<ComponentA>(entityA, 42);
    registry.addComponent<ComponentB>(entityB, 2.5f);

    ASSERT_EQ(registry.getComponents<ComponentA>().size(), 1);
    ASSERT_EQ(registry.getComponents<ComponentB>().size(), 2);

    ASSERT_TRUE(registry.hasComponent<ComponentA>(entityA));
    ASSERT_FALSE(registry.hasComponent<ComponentA>(entityB));
    ASSERT_EQ(registry.getComponents<ComponentA>()[entityA].value().value, 42);
    ASSERT_TRUE(registry.hasComponent<ComponentB>(entityB));
    ASSERT_FALSE(registry.hasComponent<ComponentB>(entityA));
    ASSERT_EQ(registry.getComponents<ComponentB>()[entityB].value().value, 2.5f);

    try {
        registry.getComponents<ComponentA>()[entityB].value();
        FAIL();
    } catch (rtype::ecs::OutOfRange const &e) {
        SUCCEED();
    }

    EXPECT_FALSE(registry.getComponents<ComponentB>()[entityA].has_value());

    registry.addComponent<ComponentA>(entityA, 21);

    ASSERT_EQ(registry.getComponents<ComponentA>().size(), 1);

    ASSERT_EQ(registry.getComponents<ComponentA>()[entityA].value().value, 21);
}

TEST(Registry, componentAssignationRemoveComponent)
{
    struct ComponentA {
        ComponentA(int a): value(a) { }
        int value;
    };

    struct ComponentB {
        ComponentB(float b): value(b) { }
        float value;
    };

    rtype::ecs::Registry registry;

    registry.registerComponent<ComponentA>();
    registry.registerComponent<ComponentB>();

    rtype::ecs::Entity entityA = registry.entityFromIndex(0);
    rtype::ecs::Entity entityB = registry.entityFromIndex(1);

    registry.addComponent<ComponentA>(entityA, 42);
    registry.addComponent<ComponentB>(entityB, 2.5f);

    ASSERT_EQ(registry.getComponents<ComponentA>().size(), 1);
    ASSERT_EQ(registry.getComponents<ComponentB>().size(), 2);

    ASSERT_TRUE(registry.hasComponent<ComponentA>(entityA));
    ASSERT_FALSE(registry.hasComponent<ComponentA>(entityB));
    ASSERT_EQ(registry.getComponents<ComponentA>()[entityA].value().value, 42);
    ASSERT_TRUE(registry.hasComponent<ComponentB>(entityB));
    ASSERT_FALSE(registry.hasComponent<ComponentB>(entityA));
    ASSERT_EQ(registry.getComponents<ComponentB>()[entityB].value().value, 2.5f);

    registry.removeComponent<ComponentA>(entityA);

    ASSERT_EQ(registry.getComponents<ComponentA>().size(), 1);
    ASSERT_EQ(registry.getComponents<ComponentB>().size(), 2);

    ASSERT_FALSE(registry.hasComponent<ComponentA>(entityA));
    ASSERT_FALSE(registry.hasComponent<ComponentA>(entityB));
    ASSERT_TRUE(registry.hasComponent<ComponentB>(entityB));
    ASSERT_FALSE(registry.hasComponent<ComponentB>(entityA));
    ASSERT_EQ(registry.getComponents<ComponentB>()[entityB].value().value, 2.5f);

    // remove non existent entity

    try {
        registry.removeComponent<ComponentA>(rtype::ecs::Entity(42));
        FAIL();
    } catch (rtype::ecs::OutOfRange const &e) {
        SUCCEED();
    }

    registry.killEntity(entityB);
}

void systemA(rtype::ecs::Registry &registry)
{
    std::cout << "System A" << std::endl;
};

TEST(Registry, system)
{
    rtype::ecs::Registry registry;

    registry.addSystem(systemA);
    registry.addSystem([](rtype::ecs::Registry &registry) {
        std::cout << "System B" << std::endl;
    });

    testing::internal::CaptureStdout();
    registry.runSystems();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "System A\nSystem B\n");
}
