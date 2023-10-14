/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Spawner.test
*/

#include "systems/Spawner.hpp"

#include <gtest/gtest.h>

TEST(SpawnerSystem, init)
{
    rtype::system::Spawner spawner;
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
    float m_deltaTime = 0.1f;
};


TEST(SpawnerSystem, noEntityNoLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(5.0f));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();
    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3.0f, 4.0f)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);
}

TEST(SpawnerSystem, oneEntityNoLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(0.5f));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::utils::PrefabManager::getInstance().createPrefab("test");
    rtype::utils::PrefabManager::getInstance().addComponent<rtype::component::Transform>("test", rtype::component::Transform(rtype::utils::Vector<float>(1, 2)));

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    spawnerComponent.addEntityToSpawnList("test", 1);
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3, 4)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[1].value().position.x, 1.0f + 3.0f);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[1].value().position.y, 2.0f + 4.0f);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);
}

TEST(SpawnerSystem, manyEntityNoLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(3));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::utils::PrefabManager::getInstance().createPrefab("test");
    rtype::utils::PrefabManager::getInstance().addComponent<rtype::component::Transform>("test", rtype::component::Transform(rtype::utils::Vector<float>(1, 2)));

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    spawnerComponent.addEntityToSpawnList("test", 1);
    spawnerComponent.addEntityToSpawnList("test", 2);
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3, 4)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 3);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);
}

TEST(SpawnerSystem, noEntityLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(5.0f));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();
    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    spawnerComponent.looping = true;
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3.0f, 4.0f)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);
}

TEST(SpawnerSystem, oneEntityLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(0.5f));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::utils::PrefabManager::getInstance().createPrefab("test");
    rtype::utils::PrefabManager::getInstance().addComponent<rtype::component::Transform>("test", rtype::component::Transform(rtype::utils::Vector<float>(1, 2)));

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    spawnerComponent.looping = true;
    spawnerComponent.addEntityToSpawnList("test", 1);
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3.0f, 4.0f)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[1].value().position.x, 1.0f + 3.0f);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[1].value().position.y, 2.0f + 4.0f);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 3);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[2].value().position.x, 1.0f + 3.0f);
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[2].value().position.y, 2.0f + 4.0f);
}

TEST(SpawnerSystem, manyEntityLoop)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(5));

    registry.registerComponent<rtype::component::Spawner>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Spawner>(rtype::system::Spawner());

    rtype::utils::PrefabManager::getInstance().createPrefab("test");
    rtype::utils::PrefabManager::getInstance().addComponent<rtype::component::Transform>("test", rtype::component::Transform(rtype::utils::Vector<float>(1, 2)));

    rtype::ecs::Entity spawner = registry.spawnEntity();
    rtype::component::Spawner spawnerComponent;
    spawnerComponent.looping = true;
    spawnerComponent.addEntityToSpawnList("test", 1);
    spawnerComponent.addEntityToSpawnList("test", 2);
    registry.addComponent<rtype::component::Spawner>(spawner, std::move(spawnerComponent));
    registry.addComponent<rtype::component::Transform>(spawner, rtype::component::Transform(rtype::utils::Vector<float>(3.0f, 4.0f)));

    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);

    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>().size(), 6);
    ASSERT_EQ(registry.getComponents<rtype::component::Spawner>().size(), 1);
}
