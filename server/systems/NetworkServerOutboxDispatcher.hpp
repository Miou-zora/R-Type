#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
/**
 * @brief NetworkServerOutboxDispatcher system used to dispatch outbox messages to the according network player
 */
class NetworkServerOutboxDispatcher {
public:
    NetworkServerOutboxDispatcher() = default;
    ~NetworkServerOutboxDispatcher() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        auto& networkServer = rtype::network::NetworkServer::getInstance();
        auto& recvMsgBuffer = networkServer.getRecvMsgBuffer();
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            auto& outbox = networkPlayer.outbox;
            while (!outbox->empty()) {
                const auto& msg = outbox->top();
                std::size_t size = rtype::network::message::server::getMessageSize(msg);
                const auto bufferSized = boost::asio::buffer(msg, size);
                networkServer.getSocket().async_send_to(bufferSized, networkPlayer.endpoint,
                    boost::bind(&rtype::network::NetworkServer::handleSend, &networkServer,
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                outbox->pop();
            }
        }
    }
};
}
