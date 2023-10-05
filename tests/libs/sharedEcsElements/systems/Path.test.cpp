/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Path.test
*/

#include "systems/Path.hpp"
#include "VelocityApplicator.hpp"
#include <gtest/gtest.h>

#define SETUP(DTPValue) rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>((DTPValue))); \
    registry.registerComponent<rtype::component::Transformable>(); \
    registry.registerComponent<rtype::component::Velocity>(); \
    registry.registerComponent<rtype::component::Path>(); \
    registry.addSystem<rtype::component::Transformable, rtype::component::Velocity, rtype::component::Path>(rtype::system::Path()); \
    registry.addSystem<rtype::component::Transformable, rtype::component::Velocity>(rtype::system::VelocityApplicator()); \
    rtype::ecs::Entity entity = registry.spawnEntity();

TEST(PathSystem, init)
{
    rtype::system::Path pathSystem;
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

TEST(PathSystem, casualUseWorld)
{
    SETUP(1);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, casualUseWorldBrutalEnd)
{
    SETUP(3);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsWorld)
{
    SETUP(1);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0).addPoint(2, 2)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 2);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsWorldBrutalEnd)
{
    SETUP(5);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0).addPoint(2, 2)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsWorldBrutalEndGoBack)
{
    SETUP(7);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0).addPoint(2, 2).addPoint(0, 2)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsWorldGoBack)
{
    SETUP(5);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0).addPoint(2, 2).addPoint(0, 2)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);
}

TEST(PathSystem, casualUseEntity)
{
    SETUP(1);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable());
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(2, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity).addPoint(0, 2, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 2);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, casualUseEntityBrutalEnd)
{
    SETUP(2);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1).addPoint(1, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);

}

TEST(PathSystem, useMultipleDotsEntity)
{
    SETUP(1);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(0, 1, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsEntityBrutalEnd)
{
    SETUP(3);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(0, 1, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsEntityBrutalEndGoBack)
{
    SETUP(5);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(0, 1, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(-1, -1, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 0);
}

TEST(PathSystem, useMultipleDotsEntityGoBack)
{
    SETUP(3);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(0, 1, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
    .addPoint(-2, 0, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.x, 1);
    ASSERT_EQ(registry.getComponents<rtype::component::Transformable>()[entity].value().position.y, 2);
    ASSERT_EQ(registry.getComponents<rtype::component::Path>()[entity].value().listOfPoints.size(), 1);
}

TEST(PathSystem, useWorldDestroyEntityAtEnd)
{
    SETUP(3);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0)
    .setDestroyAtEnd(true)));

    registry.runSystems();

    ASSERT_FALSE(registry.hasComponent<rtype::component::Transformable>(entity));
    ASSERT_FALSE(registry.hasComponent<rtype::component::Velocity>(entity));
    ASSERT_FALSE(registry.hasComponent<rtype::component::Path>(entity));
}

TEST(PathSystem, useEntityDestroyEntityAtEnd)
{
    SETUP(3);

    registry.addComponent<rtype::component::Transformable>(entity, rtype::component::Transformable(rtype::utils::Vector<float>(1, 1)));
    registry.addComponent<rtype::component::Velocity>(entity, rtype::component::Velocity());
    registry.addComponent<rtype::component::Path>(entity, std::move(rtype::component::Path(1)
    .addPoint(1, 0)
    .setDestroyAtEnd(true)));

    registry.runSystems();

    ASSERT_FALSE(registry.hasComponent<rtype::component::Transformable>(entity));
    ASSERT_FALSE(registry.hasComponent<rtype::component::Velocity>(entity));
    ASSERT_FALSE(registry.hasComponent<rtype::component::Path>(entity));
}
