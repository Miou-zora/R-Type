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
        if (!network::Client::getInstance().getRecvMsgBuffer()->empty())
            network::Client::getInstance().setLastTick(std::chrono::high_resolution_clock::now());
        while (!network::Client::getInstance().getRecvMsgBuffer()->empty()) {
            try {
                std::tuple<boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t> message = network::Client::getInstance().getRecvMsgBuffer()->back();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> decompressedBuffer;
                decompressedBuffer.fill(0);
                std::size_t decompressedSize = rtype::network::message::decompressBuffer(std::get<0>(message), decompressedBuffer, std::get<1>(message));
                auto msgs = rtype::network::message::server::splitPacketInMessages(decompressedBuffer);
                for (auto &msg : msgs) {
                    network::Client::getInstance().getInbox()->push(msg);
                }
            } catch (const std::exception &e) {
                std::cerr << "NetworkInboxChecker: " << e.what() << std::endl;
            }
            network::Client::getInstance().getRecvMsgBuffer()->pop_back();
        }
    }
private:
    std::size_t decompressBuffer(const boost::array<char, rtype::network::message::MAX_PACKET_SIZE> &buffer, boost::array<char, rtype::network::message::MAX_PACKET_SIZE> &decompressedBuffer, std::size_t bufferSize) const
    {
        std::size_t decompressedSize = zstd::ZSTD_decompress(decompressedBuffer.data(), rtype::network::message::MAX_PACKET_SIZE, buffer.data(), bufferSize);
        if (zstd::ZSTD_isError(decompressedSize)) {
            throw std::runtime_error(zstd::ZSTD_getErrorName(decompressedSize));
        }
        return decompressedSize;
    }
};
}
