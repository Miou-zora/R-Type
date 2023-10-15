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
 * @brief EnemyShootControl system used to shoot bullets
 */
class EnemyShootControl {
public:
    EnemyShootControl() = default;
    ~EnemyShootControl() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Shooter>& shooters) const
    {
        for (auto&& [index, shooter] : ecs::containers::IndexedZipper(shooters)) {
            if (!registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index)))
                continue;
            shooter.value().update(registry.getDeltaTime());
            if (shooter.value().canShoot()) {
                std::size_t bulletI = rtype::utils::GameLogicManager::getInstance().createEnemyShootedBullet(registry, index);
                shooter.value().reset();
                sendShootToPlayers(registry, bulletI);
            }
        }
    }

private:
    void sendShootToPlayers(rtype::ecs::Registry& registry, std::size_t index) const
    {
        auto& entityGameRoom = registry.getComponents<rtype::component::GameRoom>()[index].value();
        auto msg = getShootMessage(registry, index);
        for (auto&& [index, networkPlayer, gameRoom] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            if (gameRoom.value().id == entityGameRoom.id) {
                addToCriticalMessages(networkPlayer.value(), msg);
            }
        }
    }

    boost::array<char, rtype::network::message::MAX_PACKET_SIZE> getShootMessage(rtype::ecs::Registry& registry, std::size_t index) const
    {
        const auto& transform = registry.getComponents<rtype::component::Transform>()[registry.entityFromIndex(index)].value();
        auto msg = rtype::network::message::createEvent<rtype::network::message::server::BulletShoot>(index, transform.position.x, transform.position.y, 0.0f, 0.0f, 0);
        if (registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index)))
            msg.team = 1;
        return rtype::network::message::pack(msg);
    }

    /**
     * @brief Add the message to critical messages if needed
     * @param player Network player
     * @param msg Message
     */
    void addToCriticalMessages(rtype::component::NetworkPlayer& player, const boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& msg) const
    {
        const auto& unpacked = reinterpret_cast<const rtype::network::message::NetworkMessageHeader*>(msg.data());
        (*player.criticalMessages)[unpacked->id] = msg;
    }
};
}
