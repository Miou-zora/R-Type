/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkInboxHandler
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"
#include "ServerID.hpp"
#include "PrefabManager.hpp"
#include "SceneManager.hpp"

namespace rtype::system
{
    /**
     * @brief System that handles all the messages in the inbox of the network client
     */
    class NetworkInboxHandler
    {
    public:
        NetworkInboxHandler() = default;
        ~NetworkInboxHandler() = default;

        void operator()(ecs::Registry &registry) const
        {
            rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
            while (!network::Client::getInstance().getInbox()->empty())
            {
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> message = network::Client::getInstance().getInbox()->top();
                network::message::NetworkMessageHeader header = reinterpret_cast<network::message::NetworkMessageHeader &>(message[0]);
                switch (header.type)
                {
                    case network::message::server::ConnectAck::type:
                        network::Client::getInstance().setConnected(true);
                        sceneManager.setNextScene(rtype::utils::Scene::MENU);
                        break;
                    case network::message::server::RoomInformation::type:
                        sceneManager.setNextScene(rtype::utils::Scene::ROOM);
                        // TODO: save room info with roomInfo component
                        break;
                    case network::message::server::LevelInformation::type:
                        // TODO: save level info in roomInfo component
                        break;
                    case network::message::server::GameStarted::type:
                        sceneManager.setNextScene(rtype::utils::Scene::GAME);
                        break;
                    case network::message::server::GameEnded::type:
                        break;
                    case network::message::server::PlayerSpawn::type:
                        break;
                    case network::message::server::PlayerDeath::type:
                        break;
                    case network::message::server::PlayerMovement::type:
                        break;
                    case network::message::server::PlayerWeaponSwitch::type:
                        break;
                    case network::message::server::EnemySpawn::type:
                        break;
                    case network::message::server::EnemyDeath::type:
                        break;
                    case network::message::server::EnemyMovement::type:
                        break;
                    case network::message::server::BulletShoot::type:
                        break;
                    case network::message::server::BulletPosition::type:
                        break;
                    case network::message::server::BulletHit::type:
                        break;
                    case network::message::server::BulletDespawn::type:
                        break;
                    default:
                        break;
                }
                network::Client::getInstance().getInbox()->pop();
            }
        }
    private:
    };
}
