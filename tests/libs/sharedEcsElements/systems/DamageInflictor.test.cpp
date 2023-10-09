/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** DamageInflictor.test
*/

#include "DamageInflictor.hpp"
#include "Collision.hpp"

#include <gtest/gtest.h>

TEST(DamageInflictor, init)
{
    rtype::system::DamageInflictor damageInflictor;
}

TEST(DamageInflictor, noCollisionAllyEnemy)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Damage>();
    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Health>();
    registry.registerComponent<rtype::tag::Ally>();
    registry.registerComponent<rtype::tag::Enemy>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::Collision());
    registry.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());

    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();

    registry.addComponent<rtype::component::Damage>(entity1, 10);
    registry.addComponent<rtype::component::Collider>(entity1, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity1, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::tag::Ally>(entity1);

    registry.addComponent<rtype::component::Health>(entity2, 100);
    registry.addComponent<rtype::component::Collider>(entity2, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity2, rtype::utils::Vector<float>(100, 100));
    registry.emplaceComponent<rtype::tag::Enemy>(entity2);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[entity2].value().value, 100);
}

TEST(DamageInflictor, collisionAllyEnemy)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Damage>();
    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Health>();
    registry.registerComponent<rtype::tag::Ally>();
    registry.registerComponent<rtype::tag::Enemy>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::Collision());
    registry.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());

    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();

    registry.addComponent<rtype::component::Damage>(entity1, 10);
    registry.addComponent<rtype::component::Collider>(entity1, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity1, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::tag::Ally>(entity1);

    registry.addComponent<rtype::component::Health>(entity2, 100);
    registry.addComponent<rtype::component::Collider>(entity2, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity2, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::tag::Enemy>(entity2);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[entity2].value().value, 90);
}

TEST(DamageInflictor, noCollision)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Damage>();
    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Health>();
    registry.registerComponent<rtype::tag::Ally>();
    registry.registerComponent<rtype::tag::Enemy>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::Collision());
    registry.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());

    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();

    registry.addComponent<rtype::component::Damage>(entity1, 10);
    registry.addComponent<rtype::component::Collider>(entity1, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity1, rtype::utils::Vector<float>(0, 0));

    registry.addComponent<rtype::component::Health>(entity2, 100);
    registry.addComponent<rtype::component::Collider>(entity2, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity2, rtype::utils::Vector<float>(100, 100));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[entity2].value().value, 100);
}

TEST(DamageInflictor, collision)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Damage>();
    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Health>();
    registry.registerComponent<rtype::tag::Ally>();
    registry.registerComponent<rtype::tag::Enemy>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::Collision());
    registry.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());

    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();

    registry.addComponent<rtype::component::Damage>(entity1, 10);
    registry.addComponent<rtype::component::Collider>(entity1, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity1, rtype::utils::Vector<float>(0, 0));

    registry.addComponent<rtype::component::Health>(entity2, 100);
    registry.addComponent<rtype::component::Collider>(entity2, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity2, rtype::utils::Vector<float>(0, 0));

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[entity2].value().value, 90);
}

TEST(DamageInflictor, collisionAllyAlly)
{
    rtype::ecs::Registry registry;

    registry.registerComponent<rtype::component::Damage>();
    registry.registerComponent<rtype::component::Collider>();
    registry.registerComponent<rtype::component::Health>();
    registry.registerComponent<rtype::tag::Ally>();
    registry.registerComponent<rtype::tag::Enemy>();
    registry.registerComponent<rtype::component::Transform>();

    registry.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::Collision());
    registry.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());

    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();

    registry.addComponent<rtype::component::Damage>(entity1, 10);
    registry.addComponent<rtype::component::Collider>(entity1, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity1, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::tag::Ally>(entity1);

    registry.addComponent<rtype::component::Health>(entity2, 100);
    registry.addComponent<rtype::component::Collider>(entity2, rtype::utils::Vector<float>(10, 10));
    registry.addComponent<rtype::component::Transform>(entity2, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::tag::Ally>(entity2);

    registry.runSystems();

    ASSERT_EQ(registry.getComponents<rtype::component::Health>()[entity2].value().value, 100);
}
