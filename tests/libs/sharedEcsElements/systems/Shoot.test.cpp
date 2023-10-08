/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Shoot.test
*/

#include "Shoot.hpp"

#include <gtest/gtest.h>

TEST(Shoot, init)
{
    rtype::system::Shoot shootSystem;
}

class TestDeltaTimeProvider : public rtype::ecs::IDeltaTimeProvider
{
public:
    TestDeltaTimeProvider(float dt) : m_deltaTime(dt){};
    ~TestDeltaTimeProvider() = default;

    float getDeltaTime(void) override
    {
        return m_deltaTime;
    }
    float m_deltaTime = 0.1;
};

TEST(Shoot, casualUse)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Shooter>();
    registry.addSystem<rtype::component::Shooter>(rtype::system::Shoot());

    registry.setDeltaTimeProvider(std::make_shared<TestDeltaTimeProvider>(0.5));
    rtype::utils::PrefabManager::getInstance().createPrefab("projectile")
        .addComponent<rtype::component::Shooter>("", 1, 0);

    rtype::ecs::Entity entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::Shooter>(entity, "projectile", 1, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 1);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0.5);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 1);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 2);
}

TEST(Shoot, checkTransformOfInstance)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Shooter>();
    registry.registerComponent<rtype::component::Transform>();
    registry.addSystem<rtype::component::Shooter>(rtype::system::Shoot());

    registry.setDeltaTimeProvider(std::make_shared<TestDeltaTimeProvider>(0.5));
    rtype::utils::PrefabManager::getInstance().createPrefab("projectile")
        .addComponent<rtype::component::Shooter>("", 1, 0)
        .addComponent<rtype::component::Transform>(rtype::component::Transform(rtype::utils::Vector<float>(84, 42)));

    rtype::ecs::Entity entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::Shooter>(entity, "projectile", 1, 0);
    registry.emplaceComponent<rtype::component::Transform>(entity, rtype::component::Transform(rtype::utils::Vector<float>(42, 84)));
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0.5);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().timer, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>()[entity].value().cooldown, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Shooter>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[entity + 1].value().position, rtype::utils::Vector<float>(84 + 42, 42 + 84));
}
