#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "BulletInformation.hpp"
#include "ECS.hpp"
#include "EnemyInformation.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"
#include "Transform.hpp"

namespace rtype::system {
/**
 * @brief NetworkServerTickUpdater system used to send all the game informations to the players using tick
 */
class NetworkServerTickUpdater {
public:
    NetworkServerTickUpdater() = default;
    ~NetworkServerTickUpdater() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        auto& networkServer = rtype::network::NetworkServer::getInstance();

        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            const rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            sendInformationsToPlayer(i, registry, networkPlayer);
        }
    }

private:
    /**
     * @brief Send all the useful informations to a player
     * @param i Index of the player
     * @param registry Registry of the game
     * @param networkPlayer NetworkPlayer component of the player
     */
    void sendInformationsToPlayer(size_t i, ecs::Registry& registry, const rtype::component::NetworkPlayer& networkPlayer) const
    {
        sendPlayerPositions(i, registry, networkPlayer);
        sendBulletPositions(i, registry, networkPlayer);
        sendEnemyPositions(i, registry, networkPlayer);
    }

    /**
     * @brief Send all the positions of the game players to a player
     * @param i Index of the player
     * @param registry Registry of the game
     * @param networkPlayer NetworkPlayer component of the player
     */
    void sendPlayerPositions(size_t i, ecs::Registry& registry, const rtype::component::NetworkPlayer& networkPlayer) const
    {
        auto& outbox = networkPlayer.outbox;
        if (!registry.hasComponent<rtype::component::GameRoom>(rtype::ecs::Entity(i)))
            return;
        auto& playerRoom = registry.getComponents<rtype::component::GameRoom>()[i].value();

        for (auto&& [j, gameRoomOpt, transformOpt, networkPlayerOpt] :
            ecs::containers::IndexedZipper(registry.getComponents<rtype::component::GameRoom>(),
                registry.getComponents<rtype::component::Transform>(),
                registry.getComponents<rtype::component::NetworkPlayer>())) {
            auto& gameRoom = gameRoomOpt.value();
            if (gameRoom.id != playerRoom.id) {
                continue;
            }
            auto& transform = transformOpt.value();
            auto& serverID = registry.getComponents<rtype::component::ServerID>()[j].value();
            auto msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerMovement>(serverID.uuid, transform.position.x, transform.position.y);
            outbox->push(rtype::network::message::pack(msg));
        }
    }

    /**
     * @brief Send all the positions of the game bullets to a player
     * @param i Index of the player
     * @param registry Registry of the game
     * @param networkPlayer NetworkPlayer component of the player
     */
    void sendBulletPositions(size_t i, ecs::Registry& registry, const rtype::component::NetworkPlayer& networkPlayer) const
    {
        auto& outbox = networkPlayer.outbox;
        if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(i)))
            return;
        auto& playerRoom = registry.getComponents<rtype::component::GameRoom>()[i].value();

        for (auto&& [j, gameRoomOpt, transformOpt, bulletOpt] :
            ecs::containers::IndexedZipper(registry.getComponents<rtype::component::GameRoom>(),
                registry.getComponents<rtype::component::Transform>(),
                registry.getComponents<rtype::component::BulletInformation>())) {
            auto& gameRoom = gameRoomOpt.value();
            if (gameRoom.id != playerRoom.id) {
                continue;
            }

            auto& transform = transformOpt.value();
            auto& bullet = bulletOpt.value();
            auto& serverID = registry.getComponents<rtype::component::ServerID>()[j].value();
            auto msg = rtype::network::message::createEvent<rtype::network::message::server::BulletPosition>(serverID.uuid, transform.position.x, transform.position.y);
            outbox->push(rtype::network::message::pack(msg));
        }
    }

    /**
     * @brief Send all the positions of the game enemies to a player
     * @param i Index of the player
     * @param registry Registry of the game
     * @param networkPlayer NetworkPlayer component of the player
     */
    void sendEnemyPositions(size_t i, ecs::Registry& registry, const rtype::component::NetworkPlayer& networkPlayer) const
    {
        auto& outbox = networkPlayer.outbox;
        if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(i)))
            return;
        auto& playerRoom = registry.getComponents<rtype::component::GameRoom>()[i].value();

        for (auto&& [j, gameRoomOpt, transformOpt, enemyOpt, enemyInformations] :
            ecs::containers::IndexedZipper(registry.getComponents<rtype::component::GameRoom>(),
                registry.getComponents<rtype::component::Transform>(),
                registry.getComponents<rtype::tag::Enemy>(),
                registry.getComponents<rtype::component::EnemyInformation>())) {
            auto& gameRoom = gameRoomOpt.value();
            if (gameRoom.id != playerRoom.id) {
                continue;
            }
            auto& transform = transformOpt.value();
            auto& serverID = registry.getComponents<rtype::component::ServerID>()[j].value();
            auto msg = rtype::network::message::createEvent<rtype::network::message::server::EnemyMovement>(serverID.uuid, transform.position.x, transform.position.y);
            outbox->push(rtype::network::message::pack(msg));
        }
    }
};
}