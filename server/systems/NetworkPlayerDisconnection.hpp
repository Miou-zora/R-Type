#pragma once

#include <memory>
#include <unordered_map>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "GameLevel.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerControl.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
// Class to kick players that got inactive for too long in a gameroom
class NetworkPlayerDisconnection {
public:
    NetworkPlayerDisconnection(std::chrono::milliseconds timeout)
        : m_timeout(timeout)
    {
    }
    ~NetworkPlayerDisconnection() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        ecs::SparseArray<rtype::component::GameRoom>& gameRooms) const
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::vector<std::size_t> toDelete;

        for (auto&& [i, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(networkPlayers, gameRooms)) {
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            if (currentTime - networkPlayer.lastMessage > m_timeout) {
                std::cerr << "NetworkPlayerDisconnection: Player " << i << " disconnected (timeout)" << std::endl;
                toDelete.push_back(i);
            }
        }
        sendDisconnectMessagesToPlayers(registry, networkPlayers, toDelete);
        for (auto&& i : toDelete) {
            registry.killEntity(rtype::ecs::Entity(i));
        }
    }

private:
    /**
     * @brief Send disconnect messages to players
     * @param registry ECS registry
     * @param networkPlayers Network players
     * @param toDelete Players to delete
     */
    void sendDisconnectMessagesToPlayers(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers,
        std::vector<std::size_t>& toDelete) const
    {
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            auto& networkPlayer = networkPlayerOpt.value();
            if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(i)))
                continue;
            auto& playerRoom = registry.getComponents<rtype::component::GameRoom>()[i].value();
            for (auto&& [j, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::GameRoom>())) {
                if (!gameRoomOpt.has_value())
                    continue;
                auto& gameRoom = gameRoomOpt.value();
                if (gameRoom.id != playerRoom.id)
                    continue;
                auto msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerDeath>(i, true);
                networkPlayer.outbox->push(rtype::network::message::pack<rtype::network::message::server::PlayerDeath>(msg));
            }
        }
    }

    std::chrono::milliseconds m_timeout;
};
}
