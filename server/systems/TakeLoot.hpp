/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TakeLoot
*/

#pragma once

#include "ECS.hpp"
#include "Collider.hpp"
#include "Loot.hpp"
#include "Ally.hpp"
#include "Enemy.hpp"
#include "Shooter.hpp"
#include "Killable.hpp"
#include "Taker.hpp"

namespace rtype::system
{

    class TakeLoot
    {
    public:
        TakeLoot() = default;
        ~TakeLoot() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Collider> &colliders,
                        ecs::SparseArray<rtype::component::Loot> &loots) const
        {
            for (auto &&[index, collider, loot] : ecs::containers::IndexedZipper(colliders, loots))
            {
                ecs::Entity lootEntity = registry.entityFromIndex(index);
                for (ecs::Entity &collidedEntity: collider.value().collideWith) {
                    if (!isFriendly(registry, lootEntity, collidedEntity) || !registry.hasComponent<rtype::component::Taker>(collidedEntity))
                        continue;
                    if (loot.value().type == rtype::component::Loot::Type::WEAPON)
                        weaponLootBehavior(registry, lootEntity, collidedEntity, loot.value());
                    if (registry.hasComponent<rtype::component::Killable>(lootEntity))
                        registry.getComponents<rtype::component::Killable>()[lootEntity].value().to_kill = true;
                    else
                        registry.killEntity(lootEntity);
                }
            }
        }
    private:
        static bool isFriendly(const ecs::Registry &registry, const ecs::Entity &lEntity, const ecs::Entity &rEntity)
        {
            if (registry.hasComponent<rtype::tag::Ally>(lEntity) && registry.hasComponent<rtype::tag::Ally>(rEntity))
                return true;
            if (registry.hasComponent<rtype::tag::Enemy>(lEntity) && registry.hasComponent<rtype::tag::Enemy>(rEntity))
                return true;
            return false;
        }

        static void weaponLootBehavior(ecs::Registry &registry, ecs::Entity &loot, ecs::Entity &collidedEntity, rtype::component::Loot &lootComponent)
        {
            if (!registry.hasComponent<rtype::component::Shooter>(collidedEntity))
                return;

            rtype::component::Shooter &shooter = registry.getComponents<rtype::component::Shooter>()[collidedEntity].value();
            shooter.projectileName = lootComponent.weapon.projName;
            shooter.cooldown = lootComponent.weapon.cooldown;
            shooter.timer = 0;
        }
    };
}
