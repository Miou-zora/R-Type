#pragma once

#include <queue>

#include <boost/chrono.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "NetworkMessage.hpp"

namespace rtype::component {
    struct NetworkServer {
        NetworkServer(int _port)
        {
            port = _port;
            ioContext = std::make_shared<boost::asio::io_context>();
            socket = std::make_shared<boost::asio::ip::udp::socket>(*ioContext);
            endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::v4(), port);
            lastTick = std::chrono::high_resolution_clock::now();
            recvMsgBuffer = std::make_shared<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>>();
            socket->open(endpoint->protocol());
            socket->bind(*endpoint);
            socket->async_receive_from(boost::asio::buffer(recvBuffer), *endpoint, boost::bind(
                    &NetworkServer::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        ~NetworkServer() = default;

        NetworkServer(const NetworkServer &other) = default;
        NetworkServer &operator=(const NetworkServer &other) = default;

        /**
         * @brief Handle receive callback for boost asio socket
         * @param error Error code
         * @param bytes_transferred Bytes transferred from the socket
        */
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
        {
            if (error) {
                std::cerr << "Network error (handleReceive): " << error.message() << std::endl;
            } else {
                recvMsgBuffer->push_back(std::make_tuple(*endpoint, recvBuffer, bytes_transferred));
            }
            socket->async_receive_from(boost::asio::buffer(recvBuffer), *endpoint, boost::bind(
                &NetworkServer::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }

        /**
         * @brief Handle send callback for boost asio socket
         * @param error Error code
         * @param bytes_transferred Bytes transferred to the endpoint
        */
        void handleSend(const boost::system::error_code &error, std::size_t bytes_transferred)
        {
            if (error) {
                std::cerr << "Network error (handleSend): " << error.message() << std::endl;
            }
        }

        int port;
        std::shared_ptr<boost::asio::io_context> ioContext;
        std::shared_ptr<boost::asio::ip::udp::socket> socket;
        std::shared_ptr<boost::asio::ip::udp::endpoint> endpoint;
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> recvBuffer;
        std::shared_ptr<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>> recvMsgBuffer;
        std::chrono::high_resolution_clock::time_point lastTick;
    };
}
