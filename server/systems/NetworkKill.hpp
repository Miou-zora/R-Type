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
                if (killable.value().to_kill && !killable.value().killed)
                {
                    killable.value().killed = true;
                    killable.value().to_kill = false;
                    if (!registry.hasComponent<rtype::component::ServerID>(registry.entityFromIndex(index)))
                        continue;
                    if (registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(index)))
                        rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::EntityDeath>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, registry.getComponents<rtype::component::GameRoom>()[registry.entityFromIndex(index)].value().id, registry.getComponents<rtype::component::ServerID>()[registry.entityFromIndex(index)].value().uuid);
                    bossBehaviour(registry, registry.entityFromIndex(index));
                    if (registry.hasComponent<rtype::component::NetworkPlayer>(registry.entityFromIndex(index)))
                    {
                        if (registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(index)))
                            registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value().position.y = -20000.0f;
                    }
                    else
                    {
                        registry.killEntity(registry.entityFromIndex(index));
                        updatePoints(registry, registry.entityFromIndex(index));
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
    };
}
