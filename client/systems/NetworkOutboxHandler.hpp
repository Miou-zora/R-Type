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
        while (!network::Client::getInstance().getOutbox()->empty()) {
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE> message = network::Client::getInstance().getOutbox()->top();
            network::Client::getInstance().getSocket()->async_send_to(boost::asio::buffer(message, rtype::network::message::client::getMessageSize(message)), *network::Client::getInstance().getEndpoint(),
                boost::bind(&network::Client::handleSend, &network::Client::getInstance(), boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            network::Client::getInstance().getOutbox()->pop();
        }
    }
};
}
