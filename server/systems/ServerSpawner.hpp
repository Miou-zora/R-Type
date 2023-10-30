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
#include "NetworkPlayer.hpp"
#include "PrefabManager.hpp"
#include "Transform.hpp"
#include "components/Spawner.hpp"
#include "systems/Spawner.hpp"
#include "PrefabsMapping.hpp"

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
            if (registry.hasComponent<rtype::component::Transform>(entity) && registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(index))) {
                rtype::component::Transform& entityTransform = registry.getComponents<rtype::component::Transform>()[entity].value();
                entityTransform.position += registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value().position;
                entityTransform.position += spawner.spawnList[0].position;
            }
            if (registry.hasComponent<rtype::component::EntityInformation>(entity)) {
                onEntitySpawn(registry, entity);
            }
            if (registry.hasComponent<rtype::component::GameRoom>(entity)) {
                registry.getComponents<rtype::component::GameRoom>()[entity].value().id = spawnerGameRoomId;
                sendSpawnToNetworkPlayers(registry, entity, spawner.spawnList[0].entityName);
            }
            if (spawner.looping) {
                spawner.spawnList.push_back(spawner.spawnList[0]);
                spawner.timer = 0;
            }
            spawner.spawnList.erase(spawner.spawnList.begin());
        }
    }

    void sendSpawnToNetworkPlayers(rtype::ecs::Registry& registry, rtype::ecs::Entity entity, const std::string &entityPrefabsName) const
    {
        auto& entityGameRoom = registry.getComponents<rtype::component::GameRoom>()[entity].value();
        auto msg = getSpawnMessage(registry, entity, entityPrefabsName);
        if (!msg.has_value())
            return;
        for (auto&& [index, networkPlayer, gameRoom] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            if (gameRoom.value().id == entityGameRoom.id) {
                addToCriticalMessages(networkPlayer.value(), msg.value());
            }
        }
    }

    void onEntitySpawn(rtype::ecs::Registry& registry, rtype::ecs::Entity entity) const
    {
        auto& serverID = registry.getComponents<rtype::component::ServerID>()[entity].value();
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        std::copy_n(uuid.data, 16, serverID.uuid);
    }

    std::optional<boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>> getSpawnMessage(rtype::ecs::Registry& registry, std::size_t index, const std::string &entityPrefabsName) const
    {
        if (!registry.hasComponent<rtype::component::ServerID>(registry.entityFromIndex(index)))
            return std::nullopt;
        auto& serverID = registry.getComponents<rtype::component::ServerID>()[index].value();
        if (registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index))) {
            const auto& transform = registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value();
            if (registry.hasComponent<rtype::component::EntityInformation>(registry.entityFromIndex(index))) {
                auto msg = rtype::network::message::createEvent<rtype::network::message::server::EntitySpawn>(serverID.uuid, transform.position.x, transform.position.y, static_cast<u_int8_t>(rtype::utils::PrefabsMapping::namesMapping.at(entityPrefabsName)), 0);
                if (registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index)))
                    msg.team = 1;
                return std::make_optional<boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>>(rtype::network::message::pack(msg));
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Add the message to critical messages if needed
     * @param player Network player
     * @param msg Message
     */
    void addToCriticalMessages(rtype::component::NetworkPlayer& player, const boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& msg) const
    {
        const auto& unpacked = reinterpret_cast<const rtype::network::message::NetworkMessageHeader*>(msg.data());
        (*player.criticalMessages)[unpacked->id] = msg;
    }
};
}
