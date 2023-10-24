#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"
#include "PrefabManager.hpp"

namespace rtype::system {
/**
 * @brief NetworkServerInboxDispatcher system used to dispatch inbox messages to the according network player
 */
class NetworkServerInboxDispatcher {
public:
    NetworkServerInboxDispatcher() = default;
    ~NetworkServerInboxDispatcher() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        rtype::network::NetworkServer& networkServer = rtype::network::NetworkServer::getInstance();
        auto& recvMsgBuffer = networkServer.getRecvMsgBuffer();
        while (!networkServer.getRecvMsgBuffer().empty()) {
            const auto& [endpoint, recvBuffer, size] = networkServer.getRecvMsgBuffer().back();
            auto networkPlayerEntity = getNetworkPlayerEntity(registry, endpoint);
            auto& networkPlayer = registry.getComponents<rtype::component::NetworkPlayer>()[networkPlayerEntity].value();
            auto msgs = rtype::network::message::client::splitPacketInMessages(recvBuffer);
            for (auto &msg : msgs) {
                networkPlayer.inbox->push(msg);
            }
            networkPlayer.lastMessage = std::chrono::high_resolution_clock::now();
            networkServer.getRecvMsgBuffer().pop_back();
        }
    }

private:
    /**
     * @brief Get network player entity
     * @param registry ECS registry
     * @param endpoint Endpoint
     */
    rtype::ecs::Entity getNetworkPlayerEntity(ecs::Registry& registry, const boost::asio::ip::udp::endpoint& endpoint) const
    {
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>())) {
            if (!networkPlayerOpt.has_value())
                continue;
            if (networkPlayerOpt.value().endpoint == endpoint)
                return registry.entityFromIndex(i);
        }
        rtype::ecs::Entity entity = rtype::utils::GameLogicManager::getInstance().createNewPlayer(registry, endpoint);
        return entity;
    }
};
}