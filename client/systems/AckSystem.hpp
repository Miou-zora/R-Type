/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** AckSystem
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"

namespace rtype::system {
/**
 * @brief A system that adds the Ack Message to the outbox to avoid server kick
 */
class AckSystem {
public:
    AckSystem() = default;
    ~AckSystem() = default;

    void operator()(ecs::Registry& registry) const
    {
        network::message::client::Ack message = network::message::createEvent<network::message::client::Ack>();
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = network::message::pack<network::message::client::Ack>(message);
        network::Client::getInstance().getOutbox()->push(packed);
    }
};
}
