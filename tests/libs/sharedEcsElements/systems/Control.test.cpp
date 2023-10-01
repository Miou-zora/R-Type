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

TEST(Control, operatorParenthesisStatic)
{
    rtype::ecs::Registry registry;
    rtype::system::Control control;
    registry.runSystems();
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    registry.runSystems();
    rtype::ecs::SparseArray<rtype::component::Controllable> controllables;
    rtype::ecs::SparseArray<rtype::component::Velocity> velocities;

    controllables.insertAt(0, rtype::component::Controllable(
        []() { return false; },
        []() { return false; },
        []() { return false; },
        []() { return false; }
    ));
    velocities.insertAt(0, rtype::component::Velocity());

    control(registry, controllables, velocities);

    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.x), 0);
    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.y), 0);
}

TEST(Control, operatorParenthesisMovement)
{
    rtype::ecs::Registry registry;
    rtype::system::Control control;
    registry.runSystems();
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    registry.runSystems();
    rtype::ecs::SparseArray<rtype::component::Controllable> controllables;
    rtype::ecs::SparseArray<rtype::component::Velocity> velocities;

    controllables.insertAt(0, rtype::component::Controllable(
        []() { return true; },
        []() { return false; },
        []() { return false; },
        []() { return false; }
    ));
    velocities.insertAt(0, rtype::component::Velocity());

    control(registry, controllables, velocities);

    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.x), 0);
    ASSERT_EQ(static_cast<int>(velocities[0].value().vector.y), -1);
}
