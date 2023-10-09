/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control.test
*/

#include "Control.hpp"

#include <gtest/gtest.h>
#include <thread>

TEST(Control, init)
{
    rtype::system::Control control;
}

class TestDeltaTimeProvider: public rtype::ecs::IDeltaTimeProvider
{
public:
    TestDeltaTimeProvider(float dt): m_deltaTime(dt) {};
    ~TestDeltaTimeProvider() = default;

    float getDeltaTime(void) override
    {
        return m_deltaTime;
    }
    float m_deltaTime = 0.1;
};

TEST(Control, operatorParenthesisStatic)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(1.2));
    rtype::system::Control control;
    rtype::ecs::SparseArray<rtype::component::Controllable> controllables;
    rtype::ecs::SparseArray<rtype::component::Velocity> velocities;

    controllables.insertAt(0, rtype::component::Controllable(
        []() { return false; },
        []() { return false; },
        []() { return false; },
        []() { return false; }
    ));
    velocities.insertAt(0, rtype::component::Velocity());
    registry.runSystems();

    control(registry, controllables, velocities);

    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.x), 0);
    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.y), 0);
}

TEST(Control, operatorParenthesisMovement)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(1.2));
    rtype::system::Control control;
    rtype::ecs::SparseArray<rtype::component::Controllable> controllables;
    rtype::ecs::SparseArray<rtype::component::Velocity> velocities;

    controllables.insertAt(0, rtype::component::Controllable(
        []() { return true; },
        []() { return false; },
        []() { return false; },
        []() { return false; }
    ));
    velocities.insertAt(0, rtype::component::Velocity());
    registry.runSystems();

    control(registry, controllables, velocities);

    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.x), 0);
    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.y), -120);
}

TEST(Control, changeWithNewSpeed)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(1));
    rtype::ecs::Entity player = registry.spawnEntity();

    rtype::component::Controllable shipControls(
        std::function<bool()>([]() { return true; }),
        std::function<bool()>([]() { return false; }),
        std::function<bool()>([]() { return false; }),
        std::function<bool()>([]() { return false; }));
    registry.addSystem<rtype::component::Controllable, rtype::component::Velocity>(rtype::system::Control());
    registry.registerComponent<rtype::component::Controllable>();
    registry.registerComponent<rtype::component::Velocity>();
    registry.registerComponent<rtype::component::Speed>();

    registry.addComponent<rtype::component::Controllable>(player, std::move(shipControls));
    registry.emplaceComponent<rtype::component::Velocity>(player);
    registry.emplaceComponent<rtype::component::Speed>(player, 200);

    registry.runSystems();

    ASSERT_EQ(static_cast<int>(registry.getComponents<rtype::component::Velocity>()[player].value().vector.x), 0);
    ASSERT_EQ(static_cast<int>(registry.getComponents<rtype::component::Velocity>()[player].value().vector.y), -200);
}

