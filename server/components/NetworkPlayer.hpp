#pragma once

#include <queue>

#include "ECS.hpp"
#include "NetworkMessage.hpp"
#include "NetworkMessageQueue.hpp"

namespace rtype::component {
struct NetworkPlayer {
    NetworkPlayer(boost::asio::ip::udp::endpoint _endpoint)
    {
        endpoint = _endpoint;
        lastMessage = std::chrono::high_resolution_clock::now();
        inbox = std::make_shared<rtype::network::message::NetworkMessageQueue<
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE>,
            rtype::network::message::NetworkMessageHeaderEquality,
            rtype::network::message::NetworkMessageHeaderCompare>>();
        outbox = std::make_shared<rtype::network::message::NetworkMessageQueue<
            boost::array<char, rtype::network::message::MAX_PACKET_SIZE>,
            rtype::network::message::NetworkMessageHeaderEquality,
            rtype::network::message::NetworkMessageHeaderCompare>>();
    }
    ~NetworkPlayer() = default;

    NetworkPlayer(const NetworkPlayer& other) = default;
    NetworkPlayer& operator=(const NetworkPlayer& other) = default;

    boost::asio::ip::udp::endpoint endpoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastMessage;
    std::shared_ptr<rtype::network::message::NetworkMessageQueue<
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE>,
        rtype::network::message::NetworkMessageHeaderEquality,
        rtype::network::message::NetworkMessageHeaderCompare>>
        inbox;
    std::shared_ptr<rtype::network::message::NetworkMessageQueue<
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE>,
        rtype::network::message::NetworkMessageHeaderEquality,
        rtype::network::message::NetworkMessageHeaderCompare>>
        outbox;
    std::unordered_map<u_int64_t, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>> criticalMessages;
    std::unordered_map<u_int64_t, std::chrono::time_point<std::chrono::high_resolution_clock>> criticalMessagesTime;
};
}
