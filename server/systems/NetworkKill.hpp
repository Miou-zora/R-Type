/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** NetworkKill
*/

#pragma once

#include "ECS.hpp"
#include "Points.hpp"
#include "Killable.hpp"
#include "ServerID.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "Communication.hpp"

namespace rtype::system
{
    class NetworkKill
    {
    public:
        NetworkKill() = default;
        ~NetworkKill() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Killable> killables) const
        {
            for (auto &&[index, killable] : ecs::containers::IndexedZipper(killables))
            {
                ecs::Entity entity = registry.entityFromIndex(index);
                if (killable.value().to_kill && !killable.value().killed)
                {
                    killable.value().killed = true;
                    killable.value().to_kill = false;
                    if (!registry.hasComponent<rtype::component::ServerID>(entity))
                        continue;
                    if (registry.hasComponent<rtype::component::GameRoom>(entity))
                        rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::EntityDeath>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, registry.getComponents<rtype::component::GameRoom>()[entity].value().id, registry.getComponents<rtype::component::ServerID>()[entity].value().uuid);
                    bossBehaviour(registry, entity);
                    if (registry.hasComponent<rtype::component::Lootable>(entity) && registry.hasComponent<rtype::component::GameRoom>(entity))
                    {
                        generateLoot(registry, entity);
                    }
                    if (registry.hasComponent<rtype::component::NetworkPlayer>(entity))
                    {
                        if (registry.hasComponent<rtype::component::Transform>(entity))
                            registry.getComponents<rtype::component::Transform>()[entity].value().position.y = -20000.0f;
                    }
                    else
                    {
                        registry.killEntity(entity);
                        updatePoints(registry, entity);
                    }
                }
                if (killable.value().killed && killable.value().to_kill)
                    killable.value().to_kill = false;
            }
        };

    private:
        void updatePoints(ecs::Registry &registry, ecs::Entity entity) const
        {
            if (!registry.hasComponent<rtype::component::Points>(entity) || registry.hasComponent<rtype::component::NetworkPlayer>(entity))
                return;
            for (auto&& [indexPlayer, networkPlayerOpt, serverIdOpt, gameRoomOpt, pointsOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::ServerID>(), registry.getComponents<rtype::component::GameRoom>(), registry.getComponents<rtype::component::Points>())) {
                if (registry.getComponents<rtype::component::GameRoom>()[entity].value().id == gameRoomOpt.value().id) {
                    pointsOpt.value().value += registry.getComponents<rtype::component::Points>()[entity].value().value;
                    rtype::network::message::server::PlayerScore msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerScore>(serverIdOpt.value().uuid, pointsOpt.value().value);
                    (*networkPlayerOpt.value().criticalMessages)[msg.header.id] = rtype::network::message::pack(msg);
                }
            }
        }
        void bossBehaviour(ecs::Registry &registry, ecs::Entity entity) const
        {
            if (registry.hasComponent<rtype::tag::Boss>(entity) && registry.hasComponent<rtype::component::GameRoom>(entity))
            {
                rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::GameEnded>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, registry.getComponents<rtype::component::GameRoom>()[entity].value().id, true);
                for (auto &&[index_player, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>()))
                {
                    ecs::Entity player = registry.entityFromIndex(index_player);
                    if (registry.getComponents<rtype::component::GameRoom>()[entity].value().id == gameRoomOpt.value().id)
                    {
                        registry.removeComponent<rtype::component::GameRoom>(player);
                        registry.removeComponent<rtype::component::Transform>(player);
                        registry.emplaceComponent<rtype::component::Health>(player, 10);
                        registry.emplaceComponent<rtype::component::Points>(player, 0);
                    }
                }
            }
        }

        void generateLoot(ecs::Registry &registry, const ecs::Entity entity) const
        {
            const rtype::component::Lootable &lootables = registry.getComponents<rtype::component::Lootable>()[entity].value();
            const std::optional<rtype::component::Transform> &transform = registry.getComponents<rtype::component::Transform>()[entity];

            if (lootables.listOfDroppableEntity == nullptr || (*lootables.listOfDroppableEntity).empty())
                return;
            for (const auto &[prefabName, chance] : *lootables.listOfDroppableEntity)
            {
                if (willSpawn(chance))
                {
                    const ecs::Entity loot = rtype::utils::PrefabManager::getInstance().instantiate(prefabName, registry);
                    if (!registry.hasComponent<rtype::component::ServerID>(loot) || !registry.hasComponent<rtype::component::Transform>(loot) || !registry.hasComponent<rtype::component::GameRoom>(loot))
                    {
                        registry.killEntity(loot);
                        continue;
                    }
                    std::copy_n(boost::uuids::random_generator()().data, 16, registry.getComponents<rtype::component::ServerID>()[loot].value().uuid);
                    registry.getComponents<rtype::component::GameRoom>()[loot].value().id = registry.getComponents<rtype::component::GameRoom>()[entity].value().id;
                    if (transform.has_value())
                    {
                        registry.getComponents<rtype::component::Transform>()[loot].value().position += transform.value().position;
                    }
                    rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::EntitySpawn>(
                        registry,
                        rtype::utils::Communication::CommunicationType::CRITICAL,
                        registry.getComponents<rtype::component::GameRoom>()[entity].value().id,
                        registry.getComponents<rtype::component::ServerID>()[loot].value().uuid,
                        registry.getComponents<rtype::component::Transform>()[loot].value().position.x,
                        registry.getComponents<rtype::component::Transform>()[loot].value().position.y,
                        static_cast<u_int8_t>(rtype::utils::PrefabsMapping::namesMapping.at(prefabName)),
                        getTeam(registry, entity));
                }
            }
        }

        int getTeam(const ecs::Registry &registry, const ecs::Entity entity) const
        {
            if (registry.hasComponent<rtype::tag::Ally>(entity))
                return 0;
            return 1;
        }

        bool willSpawn(const int &chance) const
        {
            return (std::rand() % 100) < chance;
        }
    };
}
