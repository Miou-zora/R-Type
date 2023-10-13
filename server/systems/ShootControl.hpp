/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control
*/

#pragma once

#include "ECS.hpp"
#include "GameLogicManager.hpp"
#include "NetworkPlayerControl.hpp"
#include "PrefabManager.hpp"
#include "Shooter.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Vector.hpp"
#include "components/Path.hpp"

namespace rtype::system {
class ShootControl {
public:
    ShootControl() = default;
    ~ShootControl() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayerControl>& controllables,
        ecs::SparseArray<rtype::component::Shooter>& shooters) const
    {
        for (auto&& [index, controllable, shooter] : ecs::containers::IndexedZipper(controllables, shooters)) {
            shooter.value().update(registry.getDeltaTime());
            if (controllable.value().shoot.get() && shooter.value().canShoot()) {
                rtype::utils::GameLogicManager::getInstance().createShootedBullet(registry, index);
                shooter.value().reset();
            }
        }
    }
};
}
