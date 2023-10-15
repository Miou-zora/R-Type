/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkInboxHandler
*/

#pragma once

#include "AllyNumber.hpp"
#include "Client.hpp"
#include "ECS.hpp"
#include "Nameable.hpp"
#include "PrefabManager.hpp"
#include "RoomInformations.hpp"
#include "SceneManager.hpp"
#include "ServerID.hpp"
#include "Text.hpp"
#include "Transform.hpp"

namespace rtype::system {
/**
 * @brief System that handles all the messages in the inbox of the network client
 */
class NetworkInboxHandler {
public:
    NetworkInboxHandler() = default;
    ~NetworkInboxHandler() = default;

    void operator()(ecs::Registry& registry) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        while (!network::Client::getInstance().getInbox()->empty()) {
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE> message = network::Client::getInstance().getInbox()->top();
            network::message::NetworkMessageHeader header = reinterpret_cast<network::message::NetworkMessageHeader&>(message[0]);
            switch (header.type) {
            case network::message::server::ConnectAck::type:
                handleConnectAck(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::RoomInformation::type:
                handleRoomInformation(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::LevelInformation::type:
                handleLevelInformation(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::GameStarted::type:
                handleGameStarted(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::GameEnded::type:
                sendAck(header.id);
                break;
            case network::message::server::PlayerSpawn::type:
                handlePlayerSpawn(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::PlayerDeath::type:
                handlePlayerDeath(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::PlayerMovement::type:
                handlePlayerMovement(registry, message);
                break;
            case network::message::server::PlayerWeaponSwitch::type:
                handlePlayerWeaponSwitch(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::EnemySpawn::type:
                handleEnemySpawn(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::EnemyDeath::type:
                handleEnemyDeath(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::EnemyMovement::type:
                handleEnemyMovement(registry, message);
                break;
            case network::message::server::BulletShoot::type:
                handleBulletShoot(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::BulletPosition::type:
                handleBulletPosition(registry, message);
                break;
            case network::message::server::BulletHit::type:
                handleBulletHit(registry, message);
                sendAck(header.id);
                break;
            case network::message::server::BulletDespawn::type:
                handleBulletDespawn(registry, message);
                sendAck(header.id);
                break;
            default:
                break;
            }
            network::Client::getInstance().getInbox()->pop();
        }
    }

private:
    /**
     * @brief Handles the connect ack message when the client connects to the server
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleConnectAck(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::ConnectAck connectAck = reinterpret_cast<network::message::server::ConnectAck&>(message[0]);
        network::Client& client = network::Client::getInstance();
        client.setConnected(true);
        client.setClientId(connectAck.playerId);
        sceneManager.setNextScene(rtype::utils::Scene::MENU);
    }

    /**
     * @brief Handles the room information message when the client joins a room
     *
     * @param registry
     * @param message the message received from tTexthe server
     */
    void handleRoomInformation(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::RoomInformation roomInformation = reinterpret_cast<network::message::server::RoomInformation&>(message[0]);
        sceneManager.setNextScene(rtype::utils::Scene::ROOM);

        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::RoomInformations>())) {
            registry.getComponents<rtype::component::RoomInformations>()[index]->id = roomInformation.roomId;
        }
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::RoomInformations>())) {
            registry.getComponents<rtype::component::RoomInformations>()[index]->playersCount = roomInformation.playersCount;
        }
    }

    /**
     * @brief Handles the level information message when the client joins a room
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleLevelInformation(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::LevelInformation levelInformation = reinterpret_cast<network::message::server::LevelInformation&>(message[0]);
        sceneManager.setNextScene(rtype::utils::Scene::ROOM);

        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::RoomInformations>())) {
            registry.getComponents<rtype::component::RoomInformations>()[index]->level = levelInformation.levelId;
        }
    }

    /**
     * @brief Handles the game started message when the game starts
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleGameStarted(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::GameStarted gameStarted = reinterpret_cast<network::message::server::GameStarted&>(message[0]);
        sceneManager.setNextScene(rtype::utils::Scene::GAME);
    }

    /**
     * @brief Handles the player spawn message when a player spawns
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerSpawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::PlayerSpawn playerSpawn = reinterpret_cast<network::message::server::PlayerSpawn&>(message[0]);
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        int existingPlayers = 0;
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::AllyNumber>())) {
            if (registry.getComponents<rtype::component::AllyNumber>()[index]->id > existingPlayers) {
                existingPlayers = registry.getComponents<rtype::component::AllyNumber>()[index]->id;
            }
        }
        if (playerSpawn.playerId == network::Client::getInstance().getClientId()) {
            rtype::ecs::Entity newPlayer = prefabManager.instantiate("Player", registry);
            registry.getComponents<rtype::component::Transform>()[newPlayer]->position.x = playerSpawn.x;
            registry.getComponents<rtype::component::Transform>()[newPlayer]->position.y = playerSpawn.y;
            registry.getComponents<rtype::component::ServerID>()[newPlayer]->id = playerSpawn.playerId;
        } else {
            rtype::ecs::Entity newAlly = prefabManager.instantiate("Ally" + std::to_string(existingPlayers + 1), registry);
            registry.getComponents<rtype::component::Transform>()[newAlly]->position.x = playerSpawn.x;
            registry.getComponents<rtype::component::Transform>()[newAlly]->position.y = playerSpawn.y;
            registry.getComponents<rtype::component::ServerID>()[newAlly]->id = playerSpawn.playerId;
        }
    }

    /**
     * @brief Handles the player death message when a player dies
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerDeath(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::PlayerDeath playerDeath = reinterpret_cast<network::message::server::PlayerDeath&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == playerDeath.playerId) {
                registry.killEntity(registry.entityFromIndex(index));
                break;
            }
        }
    }

    /**
     * @brief Handles the player movement message when a player moves
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerMovement(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::PlayerMovement playerMovement = reinterpret_cast<network::message::server::PlayerMovement&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == playerMovement.playerId) {
                registry.getComponents<rtype::component::Transform>()[index]->position.x = playerMovement.x;
                registry.getComponents<rtype::component::Transform>()[index]->position.y = playerMovement.y;
                break;
            }
        }
    }

    /**
     * @brief Handles the player weapon switch message when a player switches weapon
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerWeaponSwitch(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        (void)registry;
        (void)message;
    }

    /**
     * @brief Handles the enemy spawn message when an enemy spawns
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleEnemySpawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        network::message::server::EnemySpawn enemySpawn = reinterpret_cast<network::message::server::EnemySpawn&>(message[0]);
        {
            rtype::ecs::Entity enemy = prefabManager.instantiate("Enemy", registry);
            registry.getComponents<rtype::component::ServerID>()[enemy]->id = enemySpawn.enemyId;
            registry.getComponents<rtype::component::Transform>()[enemy]->position.x = enemySpawn.x;
            registry.getComponents<rtype::component::Transform>()[enemy]->position.y = enemySpawn.y;
        }
    }

    /**
     * @brief Handles the enemy death message when an enemy dies
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleEnemyDeath(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::EnemyDeath enemyDeath = reinterpret_cast<network::message::server::EnemyDeath&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == enemyDeath.enemyId) {
                registry.killEntity(registry.entityFromIndex(index));
                break;
            }
        }
    }

    /**
     * @brief Handles the enemy movement message when an enemy moves
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleEnemyMovement(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::EnemyMovement enemyMovement = reinterpret_cast<network::message::server::EnemyMovement&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == enemyMovement.enemyId) {
                registry.getComponents<rtype::component::Transform>()[index]->position.x = enemyMovement.x;
                registry.getComponents<rtype::component::Transform>()[index]->position.y = enemyMovement.y;
                break;
            }
        }
    }

    /**
     * @brief Handles the bullet shoot message when a bullet is shot
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleBulletShoot(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        network::message::server::BulletShoot bulletShoot = reinterpret_cast<network::message::server::BulletShoot&>(message[0]);
        {
            rtype::ecs::Entity bullet = prefabManager.instantiate("AllyProjectile", registry);
            registry.getComponents<rtype::component::ServerID>()[bullet]->id = bulletShoot.playerId;
            registry.getComponents<rtype::component::Transform>()[bullet]->position.x = bulletShoot.x;
            registry.getComponents<rtype::component::Transform>()[bullet]->position.y = bulletShoot.y;
        }
    }

    /**
     * @brief Handles the bullet position message when a bullet moves
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleBulletPosition(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::BulletPosition bulletPosition = reinterpret_cast<network::message::server::BulletPosition&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == bulletPosition.bulletId) {
                registry.getComponents<rtype::component::Transform>()[index]->position.x = bulletPosition.x;
                registry.getComponents<rtype::component::Transform>()[index]->position.y = bulletPosition.y;
                break;
            }
        }
    }

    /**
     * @brief Handles the bullet hit message when a bullet hits something
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleBulletHit(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::BulletHit bulletHit = reinterpret_cast<network::message::server::BulletHit&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == bulletHit.bulletId) {
                registry.killEntity(registry.entityFromIndex(index));
                break;
            }
        }
    }

    /**
     * @brief Handles the bullet despawn message when a bullet despawns
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleBulletDespawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>& message) const
    {
        network::message::server::BulletDespawn bulletDespawn = reinterpret_cast<network::message::server::BulletDespawn&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (registry.getComponents<rtype::component::ServerID>()[index]->id == bulletDespawn.bulletId) {
                registry.killEntity(registry.entityFromIndex(index));
                break;
            }
        }
    }

    /**
     * @brief Sends an Ack message to the server
     * @param msgId the id of the message to acknowledge
     */
    void sendAck(u_int64_t msgId) const
    {
        network::message::client::Ack ack = network::message::createEvent<network::message::client::Ack>(msgId);
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = network::message::pack<network::message::client::Ack>(ack);
        network::Client::getInstance().getOutbox()->push(packed);
    }
};
}
