/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Death
*/

#pragma once

#include "Ally.hpp"
#include "ECS.hpp"
#include "Enemy.hpp"
#include "GameRoom.hpp"
#include "Health.hpp"
#include "NetworkPlayer.hpp"
#include "Communication.hpp"

namespace rtype::system {
/**
 * @brief Death system used to kill entities with a health component with a value of 0 or less
 */
class ServerDeath {
public:
    ServerDeath() = default;
    ~ServerDeath() = default;

    /**
     * @brief Kills entities with a health component with a value of 0 or less
     *
     * @param registry
     * @param health component
     */
    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Health>& health) const
    {
        for (auto&& [index, health] : ecs::containers::IndexedZipper(health)) {
            if (health.value().value <= 0) {
                sendEntityKill(registry, index);
                if (registry.hasComponent<rtype::tag::Boss>(registry.entityFromIndex(index)) && registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(index)))
                    rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::GameEnded>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, registry.getComponents<rtype::component::GameRoom>()[registry.entityFromIndex(index)].value().id);
                if (registry.hasComponent<rtype::component::NetworkPlayer>(registry.entityFromIndex(index))) {
                    registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value().position.y = -20000.0f;
                } else {
                    registry.killEntity(registry.entityFromIndex(index));
                }
            }
        }
    }

private:
    /**
     * @brief Sends a packet to the client to tell it to kill an entity. Automatically evaluates the kill type (ally, enemy...)
     * @param registry The registry containing the entities
     * @param index The index of the entity to kill
     */
    void sendEntityKill(ecs::Registry& registry, std::size_t index) const
    {
        if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(index)))
            return;
        auto& killedEntityRoom = registry.getComponents<rtype::component::GameRoom>()[registry.entityFromIndex(index)].value();
        auto networkPacket = buildPacket(registry, index);
        if (!networkPacket.has_value())
            return;
        for (auto&& [pIndex, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            if (gameRoomOpt.value().id != killedEntityRoom.id)
                continue;
            addToCriticalMessages(networkPlayer, networkPacket.value());
        }
    }

    /**
     * @brief Builds the packet to send to the client to tell it to kill an entity. Automatically evaluates the kill type (ally, enemy...)
     * @param registry The registry containing the entities
     * @param index The index of the entity to kill
     * @return The packet to send to the client
     */
    std::optional<boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>> buildPacket(ecs::Registry& registry, std::size_t index) const
    {
        if (!registry.hasComponent<rtype::component::ServerID>(registry.entityFromIndex(index)))
            return std::nullopt;
        auto& serverID = registry.getComponents<rtype::component::ServerID>()[index].value();
        if (registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index))
            && registry.hasComponent<rtype::component::EnemyInformation>(registry.entityFromIndex(index))) {
            auto msg = rtype::network::message::createEvent<rtype::network::message::server::EnemyDeath>(serverID.uuid);
            return std::make_optional<boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>>(rtype::network::message::pack(msg));
        }
        if (registry.hasComponent<rtype::component::BulletInformation>(registry.entityFromIndex(index))) {
            uint8_t hitId[16] = {0}; // TODO: change with real hit UUID
            auto msg = rtype::network::message::createEvent<rtype::network::message::server::BulletHit>(serverID.uuid, hitId);
            return std::make_optional<boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>>(rtype::network::message::pack(msg));
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
