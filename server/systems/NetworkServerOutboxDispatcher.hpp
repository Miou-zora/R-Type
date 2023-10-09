#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkServer.hpp"
#include "NetworkPlayer.hpp"

namespace rtype::system {
    class NetworkServerOutboxDispatcher {
    public:
        NetworkServerOutboxDispatcher() = default;
        ~NetworkServerOutboxDispatcher() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkServer> &networkServers,
            ecs::SparseArray<rtype::component::NetworkPlayer> &networkPlayers) const
        {
            for (auto &&[networkServerOpt] : ecs::containers::Zipper(networkServers)) {
                if (!networkServerOpt.has_value())
                    continue;
                rtype::component::NetworkServer &networkServer = networkServerOpt.value();
                for (auto &&[networkPlayerOpt] : ecs::containers::Zipper(networkPlayers)) {
                    if (!networkPlayerOpt.has_value())
                        continue;
                    rtype::component::NetworkPlayer &networkPlayer = networkPlayerOpt.value();
                    auto &outbox = networkPlayer.outbox;
                    while (!outbox->empty()) {
                        auto &msg = outbox->top();
                        std::size_t size = rtype::network::message::server::getMessageSize(msg);
                        outbox->pop();
                        networkServer.socket->async_send_to(boost::asio::buffer(msg, size), networkPlayer.endpoint,
                        boost::bind(&rtype::component::NetworkServer::handleSend, &networkServer,
                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                    }
                }
            }
        }
    };
}