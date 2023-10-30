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
#include "Health.hpp"
#include "PrefabsMapping.hpp"

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
            boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> message = network::Client::getInstance().getInbox()->top();
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
                handleGameEnded(registry, message);
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
            case network::message::server::PlayerLife::type:
                handlePlayerLife(registry, message);
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
    void handleConnectAck(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::ConnectAck connectAck = reinterpret_cast<network::message::server::ConnectAck&>(message[0]);
        if (network::Client::getInstance().getLoginSequenceIds()->find(connectAck.header.id) != network::Client::getInstance().getLoginSequenceIds()->end()) {
            return;
        }
        network::Client::getInstance().getLoginSequenceIds()->insert(connectAck.header.id);
        network::Client& client = network::Client::getInstance();
        client.setConnected(true);
        client.setClientId(connectAck.playerUuid);
        sceneManager.setNextScene(rtype::utils::Scene::MENU);
    }

    /**
     * @brief Handles the room information message when the client joins a room
     *
     * @param registry
     * @param message the message received from tTexthe server
     */
    void handleRoomInformation(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::RoomInformation roomInformation = reinterpret_cast<network::message::server::RoomInformation&>(message[0]);
        if (network::Client::getInstance().getLoginSequenceIds()->find(roomInformation.header.id) != network::Client::getInstance().getLoginSequenceIds()->end()) {
            return;
        }
        network::Client::getInstance().getLoginSequenceIds()->insert(roomInformation.header.id);
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
    void handleLevelInformation(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::LevelInformation levelInformation = reinterpret_cast<network::message::server::LevelInformation&>(message[0]);
        if (network::Client::getInstance().getLoginSequenceIds()->find(levelInformation.header.id) != network::Client::getInstance().getLoginSequenceIds()->end()) {
            return;
        }
        network::Client::getInstance().getLoginSequenceIds()->insert(levelInformation.header.id);
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
    void handleGameStarted(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::GameStarted gameStarted = reinterpret_cast<network::message::server::GameStarted&>(message[0]);
        if (network::Client::getInstance().getLoginSequenceIds()->find(gameStarted.header.id) != network::Client::getInstance().getLoginSequenceIds()->end()) {
            return;
        }
        network::Client::getInstance().getLoginSequenceIds()->insert(gameStarted.header.id);
        sceneManager.setNextScene(rtype::utils::Scene::GAME);
    }

    /**
     * @brief Handles the game ended message when the game ends
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleGameEnded(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        network::message::server::GameEnded gameEnded = reinterpret_cast<network::message::server::GameEnded&>(message[0]);

        if (network::Client::getInstance().getLoginSequenceIds()->find(gameEnded.header.id) != network::Client::getInstance().getLoginSequenceIds()->end()) {
            return;
        }
        network::Client::getInstance().getLoginSequenceIds()->insert(gameEnded.header.id);
        if (gameEnded.win) {
            sceneManager.setNextScene(rtype::utils::Scene::WIN);
        } else {
            sceneManager.setNextScene(rtype::utils::Scene::LOSE);
        }
    }

    /**
     * @brief Handles the player spawn message when a player spawns
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerSpawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::PlayerSpawn playerSpawn = reinterpret_cast<network::message::server::PlayerSpawn&>(message[0]);
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        int existingPlayers = 0;
        if (network::Client::getInstance().isEntityKilled(playerSpawn.playerUuid)) {
            std::cerr << "NetworkInboxHandler: Detected spawn of player that was already killed" << std::endl;
            return;
        }
        for (auto&& [index, serverID, allyNumber] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>(), registry.getComponents<rtype::component::AllyNumber>())) {
            if (memcmp(serverID->uuid, playerSpawn.playerUuid, sizeof(playerSpawn.playerUuid)) == 0) {
                std::cerr << "NetworkInboxHandler: Detected spawn of player that already exists" << std::endl;
                return;
            }
        }
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::AllyNumber>())) {
            if (registry.getComponents<rtype::component::AllyNumber>()[index]->id > existingPlayers) {
                existingPlayers = registry.getComponents<rtype::component::AllyNumber>()[index]->id;
            }
        }
        if (memcmp(playerSpawn.playerUuid, network::Client::getInstance().getClientId(), sizeof(playerSpawn.playerUuid)) == 0) {
            rtype::ecs::Entity newPlayer = prefabManager.instantiate("Player", registry);
            registry.getComponents<rtype::component::Transform>()[newPlayer]->position.x = playerSpawn.x;
            registry.getComponents<rtype::component::Transform>()[newPlayer]->position.y = playerSpawn.y;
            std::copy_n(playerSpawn.playerUuid, 16, registry.getComponents<rtype::component::ServerID>()[newPlayer]->uuid);
        } else {
            rtype::ecs::Entity newAlly = prefabManager.instantiate("Ally" + std::to_string(existingPlayers + 1), registry);
            registry.getComponents<rtype::component::Transform>()[newAlly]->position.x = playerSpawn.x;
            registry.getComponents<rtype::component::Transform>()[newAlly]->position.y = playerSpawn.y;
            std::copy_n(playerSpawn.playerUuid, 16, registry.getComponents<rtype::component::ServerID>()[newAlly]->uuid);
        }
    }

    /**
     * @brief Handles the player death message when a player dies
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerDeath(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::PlayerDeath playerDeath = reinterpret_cast<network::message::server::PlayerDeath&>(message[0]);
        network::Client::getInstance().insertKilledEntity(playerDeath.playerUuid);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, playerDeath.playerUuid, sizeof(playerDeath.playerUuid)) == 0) {
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
    void handlePlayerMovement(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::PlayerMovement playerMovement = reinterpret_cast<network::message::server::PlayerMovement&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, playerMovement.playerUuid, sizeof(playerMovement.playerUuid)) == 0) {
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
    void handlePlayerWeaponSwitch(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
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
    void handleEnemySpawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        network::message::server::EnemySpawn enemySpawn = reinterpret_cast<network::message::server::EnemySpawn&>(message[0]);
        if (network::Client::getInstance().isEntityKilled(enemySpawn.enemyUuid)) {
            std::cerr << "NetworkInboxHandler: Detected spawn of enemy that was already killed" << std::endl;
            return;
        }
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, enemySpawn.enemyUuid, sizeof(enemySpawn.enemyUuid)) == 0) {
                std::cerr << "NetworkInboxHandler: Detected spawn of enemy that already exists" << std::endl;
                return;
            }
        }
        try {
            rtype::ecs::Entity enemy = prefabManager.instantiate(rtype::utils::PrefabsMapping::prefabsMapping.at(static_cast<rtype::utils::PrefabsMapping::prefabs>(enemySpawn.enemytype)), registry);
            std::copy_n(enemySpawn.enemyUuid, 16, registry.getComponents<rtype::component::ServerID>()[enemy]->uuid);
            registry.getComponents<rtype::component::Transform>()[enemy]->position.x = enemySpawn.x;
            registry.getComponents<rtype::component::Transform>()[enemy]->position.y = enemySpawn.y;
        } catch (ecs::OutOfRange &error) {
            std::cerr << "handleEnemySpawn::NotImplemented: " << error.what() << std::endl;
            return;
        }
    }

    /**
     * @brief Handles the enemy death message when an enemy dies
     *
     * @param registry
     * @param message the message received from the server
     */
    void handleEnemyDeath(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        network::message::server::EnemyDeath enemyDeath = reinterpret_cast<network::message::server::EnemyDeath&>(message[0]);
        network::Client::getInstance().insertKilledEntity(enemyDeath.enemyUuid);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, enemyDeath.enemyUuid, sizeof(enemyDeath.enemyUuid)) == 0) {
                registry.killEntity(registry.entityFromIndex(index));
                rtype::ecs::Entity explosion = prefabManager.instantiate("EnemyExplosion", registry);
                registry.getComponents<rtype::component::Transform>()[explosion]->position.x = registry.getComponents<rtype::component::Transform>()[index]->position.x;
                registry.getComponents<rtype::component::Transform>()[explosion]->position.y = registry.getComponents<rtype::component::Transform>()[index]->position.y;
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
    void handleEnemyMovement(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::EnemyMovement enemyMovement = reinterpret_cast<network::message::server::EnemyMovement&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, enemyMovement.enemyUuid, sizeof(enemyMovement.enemyUuid)) == 0) {
                registry.getComponents<rtype::component::Transform>()[index]->position.x = enemyMovement.x;
                registry.getComponents<rtype::component::Transform>()[index]->position.y = enemyMovement.y;
                registry.getComponents<rtype::component::LastUpdate>()[index]->tick();
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
    void handleBulletShoot(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
        network::message::server::BulletShoot bulletShoot = reinterpret_cast<network::message::server::BulletShoot&>(message[0]);
        if (network::Client::getInstance().isEntityKilled(bulletShoot.bulletUuid)) {
            std::cerr << "NetworkInboxHandler: Detected spawn of bullet that was already killed" << std::endl;
            return;
        }
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, bulletShoot.bulletUuid, sizeof(bulletShoot.bulletUuid)) == 0) {
                std::cerr << "NetworkInboxHandler: Detected spawn of bullet that already exists" << std::endl;
                return;
            }
        }
        if (bulletShoot.team == 0) {
            rtype::ecs::Entity bullet = prefabManager.instantiate("AllyProjectile", registry);
            std::copy_n(bulletShoot.bulletUuid, 16, registry.getComponents<rtype::component::ServerID>()[bullet]->uuid);
            registry.getComponents<rtype::component::Transform>()[bullet]->position.x = bulletShoot.x;
            registry.getComponents<rtype::component::Transform>()[bullet]->position.y = bulletShoot.y;
        } else {
            rtype::ecs::Entity bullet = prefabManager.instantiate("EnemyProjectile", registry);
            std::copy_n(bulletShoot.bulletUuid, 16, registry.getComponents<rtype::component::ServerID>()[bullet]->uuid);
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
    void handleBulletPosition(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::BulletPosition bulletPosition = reinterpret_cast<network::message::server::BulletPosition&>(message[0]);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, bulletPosition.bulletUuid, sizeof(bulletPosition.bulletUuid)) == 0) {
                registry.getComponents<rtype::component::Transform>()[index]->position.x = bulletPosition.x;
                registry.getComponents<rtype::component::Transform>()[index]->position.y = bulletPosition.y;
                registry.getComponents<rtype::component::LastUpdate>()[index]->tick();
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
    void handleBulletHit(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::BulletHit bulletHit = reinterpret_cast<network::message::server::BulletHit&>(message[0]);
        network::Client::getInstance().insertKilledEntity(bulletHit.bulletUuid);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, bulletHit.bulletUuid, sizeof(bulletHit.bulletUuid)) == 0) {
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
    void handleBulletDespawn(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::BulletDespawn bulletDespawn = reinterpret_cast<network::message::server::BulletDespawn&>(message[0]);
        network::Client::getInstance().insertKilledEntity(bulletDespawn.bulletUuid);
        for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::ServerID>())) {
            if (memcmp(registry.getComponents<rtype::component::ServerID>()[index]->uuid, bulletDespawn.bulletUuid, sizeof(bulletDespawn.bulletUuid)) == 0) {
                registry.killEntity(registry.entityFromIndex(index));
                break;
            }
        }
    }

    /**
     * @brief Handles the player life message when a player loses life
     *
     * @param registry
     * @param message the message received from the server
     */
    void handlePlayerLife(ecs::Registry& registry, boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& message) const
    {
        network::message::server::PlayerLife playerLife = reinterpret_cast<network::message::server::PlayerLife&>(message[0]);
        for (auto&& [index, health, serverId] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::Health>(), registry.getComponents<rtype::component::ServerID>())) {
            if (std::memcmp(serverId.value().uuid, playerLife.playerUuid, 16) == 0) {
                health.value().value = playerLife.life;
                // This part shouldn't be here, but I don't know how to do it properly for now
                for (auto&& [text, name]: rtype::ecs::containers::Zipper(registry.getComponents<rtype::component::Text>(), registry.getComponents<rtype::component::Nameable>()))
                {
                    if (name.value().name == "playerLifeVariable") {
                        text.value().text = std::to_string(std::max(0, health.value().value));
                    }
                }
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
        boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> packed = network::message::pack<network::message::client::Ack>(ack);
        network::Client::getInstance().getOutbox()->push(packed);
    }
};
}
