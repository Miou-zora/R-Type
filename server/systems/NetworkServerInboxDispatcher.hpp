#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"
#include "PrefabManager.hpp"

void printHexBytes(const char *arr, std::size_t bytes)
{
    for (std::size_t i = 0; i < bytes; i++) {
        std::cout << std::hex << (int)arr[i] << " ";
    }
    std::cout << std::endl;
}

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
            try {
                const auto& [endpoint, recvBuffer, size] = networkServer.getRecvMsgBuffer().back();
                auto networkPlayerEntity = getNetworkPlayerEntity(registry, endpoint);
                auto& networkPlayer = registry.getComponents<rtype::component::NetworkPlayer>()[networkPlayerEntity].value();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> decompressedBuffer;
                decompressedBuffer.fill(0);
                std::size_t decompressedSize = rtype::network::message::decompressBuffer(recvBuffer, decompressedBuffer, size);
                auto msgs = rtype::network::message::client::splitPacketInMessages(decompressedBuffer);
                for (auto &msg : msgs) {
                    networkPlayer.inbox->push(msg);
                }
                networkPlayer.lastMessage = std::chrono::high_resolution_clock::now();
            } catch (const std::exception &e) {
                std::cerr << "NetworkServerInboxDispatcher: " << e.what() << std::endl;
            }
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