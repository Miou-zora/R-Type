/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkInboxHandler
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"
#include "PrefabManager.hpp"
#include "SceneManager.hpp"
#include "ServerID.hpp"

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
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        while (!network::Client::getInstance().getInbox()->empty()) {
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE> message = network::Client::getInstance().getInbox()->top();
            network::message::NetworkMessageHeader header = reinterpret_cast<network::message::NetworkMessageHeader&>(message[0]);
            switch (header.type) {
            case network::message::server::ConnectAck::type:
                network::Client::getInstance().setConnected(true);
                sceneManager.setNextScene(rtype::utils::Scene::MENU);
                sendAck(header.id);
                break;
            case network::message::server::RoomInformation::type:
                sceneManager.setNextScene(rtype::utils::Scene::ROOM);
                sendAck(header.id);
                // TODO: save room info with roomInfo component
                break;
            case network::message::server::LevelInformation::type:
                // TODO: save level info in roomInfo component
                sendAck(header.id);
                break;
            case network::message::server::GameStarted::type:
                sceneManager.setNextScene(rtype::utils::Scene::GAME);
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
     * @brief Sends an Ack message to the server
     * @param msgId the id of the message to acknowledge
     */
    void sendAck(int msgId) const
    {
        network::message::client::Ack ack = network::message::createEvent<network::message::client::Ack>(msgId);
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = network::message::pack<network::message::client::Ack>(ack);
        network::Client::getInstance().getOutbox()->push(packed);
    }
};
}
