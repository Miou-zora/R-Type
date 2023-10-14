/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Spawner
*/

#pragma once

#include <unordered_map>

#include "ECS.hpp"
#include "GameRoom.hpp"
#include "PrefabManager.hpp"
#include "Transform.hpp"
#include "components/Spawner.hpp"
#include "systems/Spawner.hpp"

namespace rtype::system {
/**
 * @brief System that spawn entities. It use the Spawner Transform's position as a reference if it has one.
 */
class ServerSpawner : public Spawner {
public:
    ServerSpawner() = default;
    ~ServerSpawner() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Spawner>& spawners) const
    {
        for (auto&& [index, spawner] : rtype::ecs::containers::IndexedZipper(spawners)) {
            updateSpawner(registry, spawner.value(), index);
        }
    }

private:
    void updateSpawner(ecs::Registry& registry, rtype::component::Spawner& spawner, std::size_t index) const
    {
        u_int16_t spawnerGameRoomId = registry.getComponents<rtype::component::GameRoom>()[index].value().id;
        if (spawner.spawnList.size() == 0)
            return;
        spawner.timer += registry.getDeltaTime();
        while (spawner.spawnList.size() != 0 && spawner.timer >= spawner.spawnList[0].spawnDelay) {
            spawner.timer -= spawner.spawnList[0].spawnDelay;
            auto entity = rtype::utils::PrefabManager::getInstance().instantiate(spawner.spawnList[0].entityName, registry);
            if (registry.hasComponent<rtype::component::GameRoom>(entity))
                registry.getComponents<rtype::component::GameRoom>()[entity].value().id = spawnerGameRoomId;
            if (registry.hasComponent<rtype::component::Transform>(entity) && registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(index))) {
                rtype::component::Transform& entityTransform = registry.getComponents<rtype::component::Transform>()[entity].value();
                entityTransform.position += registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value().position;
            }
            if (spawner.looping) {
                spawner.spawnList.push_back(spawner.spawnList[0]);
                spawner.timer = 0;
            }
            spawner.spawnList.erase(spawner.spawnList.begin());
        }
    }
};
}
