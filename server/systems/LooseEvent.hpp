/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** LooseEvent
*/

#pragma once

#include "ECS.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "Health.hpp"
#include "Transform.hpp"

#include "Communication.hpp"

#include <map>

namespace rtype::system {
class LooseEvent {
public:
    LooseEvent() = default;
    ~LooseEvent() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::GameRoom>& gameRooms,
        ecs::SparseArray<rtype::component::NetworkPlayer>& players,
        ecs::SparseArray<rtype::component::Health>& healths
    ) const
    {
        std::map<u_int16_t, bool> looseMap;
        for (auto&& [gameRoom, player, health, transform] : ecs::containers::Zipper(gameRooms, players, healths, registry.getComponents<rtype::component::Transform>())) {
            if (looseMap.find(gameRoom->id) == looseMap.end()) {
                looseMap[gameRoom->id] = (health->value <= 0) ? true : false;
            } else if (looseMap[gameRoom->id] == true && health->value > 0) {
                looseMap[gameRoom->id] = false;
            }
        }
        for (auto&& [index, gameRoom, player, health, transform] : ecs::containers::IndexedZipper(gameRooms, players, healths, registry.getComponents<rtype::component::Transform>())) {
            if (looseMap[gameRoom->id] == true) {
                auto& gameRoom = registry.getComponents<rtype::component::GameRoom>()[index].value();
                rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::GameEnded>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, gameRoom.id, false);
                registry.removeComponent<rtype::component::GameRoom>(registry.entityFromIndex(index));
                registry.removeComponent<rtype::component::Transform>(registry.entityFromIndex(index));
                registry.emplaceComponent<rtype::component::Health>(registry.entityFromIndex(index), 10);
            }
        }
    }
};
}