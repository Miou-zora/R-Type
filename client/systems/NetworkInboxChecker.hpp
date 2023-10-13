/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkInboxChecker
*/

#pragma once

#include "Client.hpp"

namespace rtype::system {
/**
 * @brief A system that checks all the message in the buffer and put them in the inbox
 */
class NetworkInboxChecker {
public:
    NetworkInboxChecker() = default;
    ~NetworkInboxChecker() = default;

    void operator()(ecs::Registry& registry) const
    {
        while (!network::Client::getInstance().getRecvMsgBuffer()->empty()) {
            std::tuple<boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t> message = network::Client::getInstance().getRecvMsgBuffer()->back();
            network::Client::getInstance().getRecvMsgBuffer()->pop_back();
            if (!rtype::network::message::server::checkMessageIntegrity(std::get<0>(message), std::get<1>(message))) {
                std::cerr << "Network error (checkMessageIntegrity): malformed message." << std::endl;
                continue;
            }
            network::Client::getInstance().getInbox()->push(std::get<0>(message));
        }
    }
};
}
