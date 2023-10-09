#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkServer.hpp"
#include "NetworkPlayer.hpp"

namespace rtype::system {
    class NetworkServerInboxDispatcher {
    public:
        NetworkServerInboxDispatcher() = default;
        ~NetworkServerInboxDispatcher() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkServer> &networkServers,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers) const
        {
            for (auto &&[networkServerOpt] : ecs::containers::Zipper(networkServers)) {
                if (!networkServerOpt.has_value())
                    continue;
                rtype::component::NetworkServer &networkServer = networkServerOpt.value();
                auto recvMsgBuffer = networkServer.recvMsgBuffer;
                while (!recvMsgBuffer->empty()) {
                    auto [endpoint, recvBuffer, size] = recvMsgBuffer->back();
                    recvMsgBuffer->pop_back();
                    if (rtype::network::message::client::checkMessageIntegrity(recvBuffer, size) == false) {
                        std::cerr << "Network error (checkMessageIntegrity): malformed message for endpoint " << endpoint << std::endl;
                        continue;
                    }
                    auto networkPlayerEntity = getNetworkPlayerEntity(registry, endpoint);
                    auto &networkPlayer = registry.getComponents<rtype::component::NetworkPlayer>()[networkPlayerEntity].value();
                    networkPlayer.inbox->push(recvBuffer);
                }
            }
        }

    private:
        /**
         * @brief Get network player entity
         * @param registry ECS registry
         * @param endpoint Endpoint
        */
        rtype::ecs::Entity getNetworkPlayerEntity(ecs::Registry &registry, boost::asio::ip::udp::endpoint &endpoint) const
        {
            for (auto &&[i, networkPlayerOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>())) {
                if (!networkPlayerOpt.has_value())
                    continue;
                rtype::component::NetworkPlayer &networkPlayer = networkPlayerOpt.value();
                if (networkPlayer.endpoint == endpoint)
                    return rtype::ecs::Entity(i);
            }
            rtype::ecs::Entity entity = registry.spawnEntity();
            registry.emplaceComponent<rtype::component::NetworkPlayer>(entity, endpoint);
            return entity;
        }
    };
}