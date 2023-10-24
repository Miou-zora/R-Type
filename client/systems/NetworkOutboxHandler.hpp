/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkOutboxHandler
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"

namespace rtype::system {
/**
 * @brief A system that sends all the outbox message to the server
 */
class NetworkOutboxHandler {
public:
    NetworkOutboxHandler() = default;
    ~NetworkOutboxHandler() = default;

    void operator()(ecs::Registry& registry) const
    {
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packet;
        std::size_t packetSize = 0;
        while (!network::Client::getInstance().getOutbox()->empty()) {
            boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> message = network::Client::getInstance().getOutbox()->top();
            std::size_t msgSize = rtype::network::message::client::getMessageSize(message);
            if (packetSize + msgSize > rtype::network::message::MAX_PACKET_SIZE) {
                sendBuffers(*network::Client::getInstance().getEndpoint(), packet, packetSize);
                packetSize = 0;
                packet.fill(0);
            }
            std::memcpy(packet.data() + packetSize, message.data(), msgSize);
            packetSize += msgSize;
            network::Client::getInstance().getOutbox()->pop();
        }
        if (packetSize > 0) {
            sendBuffers(*network::Client::getInstance().getEndpoint(), packet, packetSize);
        }
    }

private:
    void sendBuffers(boost::asio::ip::udp::endpoint &endpoint, const boost::array<char, rtype::network::message::MAX_PACKET_SIZE> &buffer, std::size_t bufferSize) const
    {
        network::Client::getInstance().getSocket()->async_send_to(boost::asio::buffer(buffer, bufferSize),
        *network::Client::getInstance().getEndpoint(),
            boost::bind(&network::Client::handleSend, &network::Client::getInstance(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
};
}
