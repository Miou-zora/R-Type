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
        auto& recvMsgBuffer = rtype::network::NetworkServer::getInstance().getRecvMsgBuffer();
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE> gBuffer;
            std::size_t totalSize = 0;
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            auto& outbox = networkPlayer.outbox;
            while (!outbox->empty()) {
                const auto& msg = outbox->top();
                auto header = reinterpret_cast<const rtype::network::message::NetworkMessageHeader *>(msg.data());
                std::size_t size = rtype::network::message::server::getMessageSize(msg);
                if (totalSize + size > rtype::network::message::MAX_PACKET_SIZE) {
                    sendBuffers(registry, networkPlayer.endpoint, gBuffer, totalSize);
                    totalSize = 0;
                }
                std::copy(msg.begin(), msg.begin() + size, gBuffer.begin() + totalSize);
                totalSize += size;
                outbox->pop();
            }
            if (totalSize > 0) {
                sendBuffers(registry, networkPlayer.endpoint, gBuffer, totalSize);
            }
        }
    }
private:
    void sendBuffers(ecs::Registry& registry, boost::asio::ip::udp::endpoint &endpoint, const boost::array<char, rtype::network::message::MAX_PACKET_SIZE> &buffer, std::size_t bufferSize) const
    {
        try {
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE> compressedBuffer;
            compressedBuffer.fill(0);
            std::size_t compressedSize = rtype::network::message::compressBuffer(buffer, compressedBuffer, bufferSize);
            rtype::network::NetworkServer::getInstance().getSocket().async_send_to(boost::asio::buffer(compressedBuffer, compressedSize), endpoint,
            boost::bind(&rtype::network::NetworkServer::handleSend, &rtype::network::NetworkServer::getInstance(),
                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        } catch (const std::exception& e) {
            std::cerr << "NetworkServerOutboxDispatcher: " << e.what() << std::endl;
        }
    }
};
}
