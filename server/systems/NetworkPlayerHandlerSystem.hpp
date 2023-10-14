#pragma once

#include <memory>
#include <unordered_map>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "GameLevel.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerControl.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
class NetworkPlayerHandlerSystem {
public:
    NetworkPlayerHandlerSystem() = default;
    ~NetworkPlayerHandlerSystem() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            auto& inbox = networkPlayer.inbox;
            while (!inbox->empty()) {
                const auto& msg = inbox->top();
                handleAnyCallback(registry, networkPlayers, networkPlayer, i, msg);
                inbox->pop();
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
    void handleAnyCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        auto msgHeader = reinterpret_cast<const rtype::network::message::NetworkMessageHeader*>(msg.data());
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
        case rtype::network::message::client::ChooseRoom::type:
            handleChooseRoomCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
            break;
        case rtype::network::message::client::StartGame::type:
            handleStartGameCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
            break;
        case rtype::network::message::client::PlayerMovement::type:
            handlePlayerMoveCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
            break;
        case rtype::network::message::client::PlayerShoot::type:
            handlePlayerShootCallback(registry, networkPlayers, networkPlayer, networkPlayerEntity, msg);
            break;
        case rtype::network::message::client::Ack::type:
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
    void handleConnectCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
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
    void handleCreateRoomCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        auto component = rtype::component::GameRoom();
        registry.emplaceComponent<rtype::component::GameRoom>(registry.entityFromIndex(networkPlayerEntity), std::move(component));
        auto roomInformation = rtype::network::message::createEvent<rtype::network::message::server::RoomInformation>(component.id);
        networkPlayer.outbox->push(rtype::network::message::pack(roomInformation));
    }

    /**
     * @brief Handle choose room callback
     * @param registry ECS registry
     * @param networkPlayers Network players
     * @param networkPlayer Network player
     * @param networkPlayerEntity Network player entity
     * @param msg Message
     */
    void handleChooseRoomCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        // TODO: make something useful like send error message if room does not exist
        auto& chooseRoom = rtype::network::message::unpack<rtype::network::message::client::ChooseRoom>(msg);
        auto component = rtype::component::GameRoom(chooseRoom.roomId);
        registry.emplaceComponent<rtype::component::GameRoom>(registry.entityFromIndex(networkPlayerEntity), std::move(component));
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
    void handleChooseLevelCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        auto& chooseLevel = rtype::network::message::unpack<rtype::network::message::client::ChooseLevel>(msg);
        auto gameLevel = rtype::component::GameLevel(chooseLevel.levelId);
        // TODO : check if it exist or add in perfab
        registry.emplaceComponent<rtype::component::GameLevel>(registry.entityFromIndex(networkPlayerEntity), std::move(gameLevel));
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
    void handleStartGameCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        auto startGameAck = rtype::network::message::createEvent<rtype::network::message::server::GameStarted>();
        rtype::utils::GameLogicManager::getInstance().startGame(registry, networkPlayerEntity);
        networkPlayer.outbox->push(rtype::network::message::pack(startGameAck));
    }

    /**
     * @brief Handle player move callback
     * @param registry ECS registry
     * @param networkPlayers Network players
     * @param networkPlayer Network player
     * @param networkPlayerEntity Network player entity
     * @param msg Message
     */
    void handlePlayerMoveCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        if (!registry.hasComponent<rtype::component::NetworkPlayerControl>(registry.entityFromIndex(networkPlayerEntity))) {
            return;
        }
        auto& playerMove = rtype::network::message::unpack<rtype::network::message::client::PlayerMovement>(msg);
        auto& playerControl = registry.getComponents<rtype::component::NetworkPlayerControl>()[networkPlayerEntity].value();
        playerControl.up = playerMove.keys_pressed[0];
        playerControl.down = playerMove.keys_pressed[1];
        playerControl.left = playerMove.keys_pressed[2];
        playerControl.right = playerMove.keys_pressed[3];
    }

    /**
     * @brief Handle player shoot callback
     * @param registry ECS registry
     * @param networkPlayers Network players
     * @param networkPlayer Network player
     * @param networkPlayerEntity Network player entity
     * @param msg Message
     * @return void
     */
    void handlePlayerShootCallback(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        rtype::component::NetworkPlayer& networkPlayer,
        size_t networkPlayerEntity,
        const boost::array<char, 512UL>& msg) const
    {
        if (!registry.hasComponent<rtype::component::NetworkPlayerControl>(registry.entityFromIndex(networkPlayerEntity))) {
            return;
        }
        auto& playerControl = registry.getComponents<rtype::component::NetworkPlayerControl>()[networkPlayerEntity].value();
        playerControl.shoot = true;
    }
};
}