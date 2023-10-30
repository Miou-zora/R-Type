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
/**
 * @brief ShootControl system used to shoot bullets for players
 */
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
                std::size_t bulletI = rtype::utils::GameLogicManager::getInstance().createEntityFrom(registry, index, shooter.value().projectileName);
                shooter.value().reset();
                sendShootToPlayers(registry, bulletI, shooter.value().projectileName);
            }
        }
    }

private:
    void sendShootToPlayers(rtype::ecs::Registry& registry, std::size_t index, const std::string &projectilePrefabsName) const
    {
        auto& entityGameRoom = registry.getComponents<rtype::component::GameRoom>()[index].value();
        auto msg = getShootMessage(registry, index, projectilePrefabsName);
        for (auto&& [index, networkPlayer, gameRoom] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            if (gameRoom.value().id == entityGameRoom.id) {
                addToCriticalMessages(networkPlayer.value(), msg);
            }
        }
    }

    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> getShootMessage(rtype::ecs::Registry& registry, std::size_t index, const std::string &projectilePrefabsName) const
    {
        const auto& transform = registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value();
        auto& serverID = registry.getComponents<rtype::component::ServerID>()[index].value();
        auto msg = rtype::network::message::createEvent<rtype::network::message::server::EntitySpawn>(serverID.uuid, transform.position.x, transform.position.y, static_cast<u_int8_t>(rtype::utils::PrefabsMapping::namesMapping.at(projectilePrefabsName)), 0);
        if (registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index)))
            msg.team = 1;
        return rtype::network::message::pack(msg);
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
