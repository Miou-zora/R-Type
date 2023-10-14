/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkInboxHandler
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"
#include "Nameable.hpp"
#include "PrefabManager.hpp"
#include "RoomInformations.hpp"
#include "SceneManager.hpp"
#include "ServerID.hpp"
#include "Text.hpp"

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
                sendAck(header.id);
                break;
            case network::message::server::PlayerDeath::type:
                sendAck(header.id);
                break;
            case network::message::server::PlayerMovement::type:
                break;
            case network::message::server::PlayerWeaponSwitch::type:
                sendAck(header.id);
                break;
            case network::message::server::EnemySpawn::type:
                sendAck(header.id);
                break;
            case network::message::server::EnemyDeath::type:
                sendAck(header.id);
                break;
            case network::message::server::EnemyMovement::type:
                break;
            case network::message::server::BulletShoot::type:
                sendAck(header.id);
                break;
            case network::message::server::BulletPosition::type:
                break;
            case network::message::server::BulletHit::type:
                sendAck(header.id);
                break;
            case network::message::server::BulletDespawn::type:
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
        network::Client::getInstance().setConnected(true);
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
