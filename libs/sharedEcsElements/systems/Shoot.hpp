/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Shoot
*/

#pragma once

#include "ECS.hpp"
#include "Shooter.hpp"
#include "PrefabManager.hpp"
#include "Transform.hpp"

namespace rtype::system
{
    /**
     * @brief Shoot system used to shoot projectiles
     */
    class Shoot
    {
    public:
        Shoot() = default;
        ~Shoot() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Shooter> &shooters) const
        {
            for (auto &&[index, shooter] : ecs::containers::IndexedZipper(shooters))
            {
                if (shooter.value().projectileName.empty())
                    continue;
                rtype::ecs::Entity proj = rtype::utils::PrefabManager::getInstance().instantiate(shooter.value().projectileName, registry);
                if (registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(index)) &&
                    registry.hasComponent<rtype::component::Transform>(proj))
                {
                    registry.getComponents<rtype::component::Transform>()[proj].value().position += registry.getComponents<component::Transform>()[index].value().position;
                }
            }
        }
    };
}
