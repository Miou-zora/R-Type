#pragma once

#include <memory>
#include <unordered_map>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "GameRoom.hpp"
#include "GameLevel.hpp"
#include "NetworkServer.hpp"
#include "NetworkPlayer.hpp"

namespace rtype::system {
    class NetworkPlayerHandlerSystem {
            public:
        NetworkPlayerHandlerSystem() = default;
        ~NetworkPlayerHandlerSystem() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers) const
        {
            for (auto &&[i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
                if (!networkPlayerOpt.has_value())
                    continue;
                rtype::component::NetworkPlayer &networkPlayer = networkPlayerOpt.value();
                auto &inbox = networkPlayer.inbox;
                while (!inbox->empty()) {
                    auto &msg = inbox->top();
                    inbox->pop();
                    handleAnyCallback(registry, networkPlayers, networkPlayer, i, msg);
                }
            }
        }

    private:
        /**
         * @brief Handle any callback
         * @param registry ECS registry
         * @param networkPlayers Network players
         * @param networkPlayer Network player
         * @param networkPlayerEntity Network player entity
         * @param msg Message
        */
        void handleAnyCallback(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers,
            rtype::component::NetworkPlayer &networkPlayer,
            size_t networkPlayerEntity,
            const boost::array<char, 512UL> &msg) const
        {
            auto msgHeader = reinterpret_cast<const rtype::network::message::NetworkMessageHeader *>(msg.data());
            switch (msgHeader->type) {
                case rtype::network::message::client::Connect::type:
                    handleConnectCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
                    break;
                case rtype::network::message::client::ChooseLevel::type:
                    handleChooseLevelCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
                    break;
                case rtype::network::message::client::CreateRoom::type:
                    handleCreateRoomCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
                    break;
                case rtype::network::message::client::StartGame::type:
                    handleStartGameCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
                    break;
                default:
                    std::cerr << "Unknown message type " << static_cast<int>(msgHeader->type) << std::endl;
                    break;
            }
        }

        /**
         * @brief Handle connect callback
         * @param registry ECS registry
         * @param networkPlayers Network players
         * @param networkPlayer Network player
         * @param networkPlayerEntity Network player entity
         * @param msg Message
        */
        void handleConnectCallback(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers,
            rtype::component::NetworkPlayer &networkPlayer,
            size_t networkPlayerEntity,
            const boost::array<char, 512UL> &msg) const
        {
            auto connectAck = rtype::network::message::createEvent<rtype::network::message::server::ConnectAck>(networkPlayerEntity);
            networkPlayer.outbox->push(rtype::network::message::pack(connectAck));
        }

        /**
         * @brief Handle create room callback
         * @param registry ECS registry
         * @param networkPlayers Network players
         * @param networkPlayer Network player
         * @param networkPlayerEntity Network player entity
         * @param msg Message
        */
        void handleCreateRoomCallback(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers,
            rtype::component::NetworkPlayer &networkPlayer,
            size_t networkPlayerEntity,
            const boost::array<char, 512UL> &msg) const
        {
            auto component = rtype::component::GameRoom();
            registry.emplaceComponent<rtype::component::GameRoom>(rtype::ecs::Entity(networkPlayerEntity), std::move(component));
            auto roomInformation = rtype::network::message::createEvent<rtype::network::message::server::RoomInformation>(component.id);
            networkPlayer.outbox->push(rtype::network::message::pack(roomInformation));
        }

        /**
         * @brief Handle choose level callback
         * @param registry ECS registry
         * @param networkPlayers Network players
         * @param networkPlayer Network player
         * @param networkPlayerEntity Network player entity
         * @param msg Message
        */
        void handleChooseLevelCallback(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers,
            rtype::component::NetworkPlayer &networkPlayer,
            size_t networkPlayerEntity,
            boost::array<char, 512UL> msg) const
        {
            auto chooseLevel = rtype::network::message::unpack<rtype::network::message::client::ChooseLevel>(msg);
            auto gameLevel = rtype::component::GameLevel(chooseLevel.levelId);
            registry.emplaceComponent<rtype::component::GameLevel>(rtype::ecs::Entity(networkPlayerEntity), std::move(gameLevel));
            auto levelInformation = rtype::network::message::createEvent<rtype::network::message::server::LevelInformation>(gameLevel.level);
            networkPlayer.outbox->push(rtype::network::message::pack(levelInformation));
        }

        /**
         * @brief Handle start game callback
         * @param registry ECS registry
         * @param networkPlayers Network players
         * @param networkPlayer Network player
         * @param networkPlayerEntity Network player entity
         * @param msg Message
        */
        void handleStartGameCallback(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers,
            rtype::component::NetworkPlayer &networkPlayer,
            size_t networkPlayerEntity,
            boost::array<char, 512UL> msg) const
        {
            auto startGameAck = rtype::network::message::createEvent<rtype::network::message::server::GameStarted>();
            networkPlayer.outbox->push(rtype::network::message::pack(startGameAck));
        }
    };
}