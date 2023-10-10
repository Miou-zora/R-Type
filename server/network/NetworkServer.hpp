#pragma once

#include <queue>

#include <boost/chrono.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "NetworkMessage.hpp"

namespace rtype::network {
    class NetworkServer {
    public:
        /**
         * @brief init the instance of the singleton
         * @param port Port to listen on
        */
        static void initInstance(int port, size_t tickRate = 64)
        {
            instance = std::make_shared<NetworkServer>(port, tickRate);
        }

        /**
         * @brief Get the instance of the singleton
         * @return NetworkServer&
        */
        static NetworkServer &getInstance()
        {
            return *instance;
        }

        NetworkServer(int port, size_t tickRate = 64)
        {
            m_port = port;
            m_tickRate = tickRate;
            m_ioContext = std::make_shared<boost::asio::io_context>();
            m_socket = std::make_shared<boost::asio::ip::udp::socket>(*m_ioContext);
            m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::v4(), m_port);
            m_recvMsgBuffer = std::make_shared<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>>();
            m_socket->open(m_endpoint->protocol());
            m_socket->bind(*m_endpoint);
            m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint, boost::bind(
                    &NetworkServer::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            m_thread = std::make_shared<boost::thread>([this](){
                m_ioContext->run();
            });
            m_lastTick = std::chrono::high_resolution_clock::now();
        }

        ~NetworkServer()
        {
            m_ioContext->stop();
            m_thread->join();
        }

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
                m_recvMsgBuffer->push_back(std::make_tuple(*m_endpoint, m_recvBuffer, bytes_transferred));
            }
            m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint, boost::bind(
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

        /**
         * @brief Get the last tick time point
         * @return std::chrono::high_resolution_clock::time_point
        */
        std::chrono::high_resolution_clock::time_point getLastTick() const
        {
            return m_lastTick;
        }

        /**
         * @brief Update the last tick time point
        */
        void updateLastTick()
        {
            m_lastTick = std::chrono::high_resolution_clock::now();
        }

        /**
         * @brief Check if the server should send a tick to the clients
         * @param lastTick The last tick sent to the clients
         * @param currentTime The current time
         * @return true if the server should send a tick to the clients
        */
        bool shouldTick() const
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_lastTick).count() >= 1000 / m_tickRate;
        }

        /**
         * @brief Get the recv message buffer
         * @return std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>
        */
        std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>> &getRecvMsgBuffer()
        {
            return *m_recvMsgBuffer;
        }

        /**
         * @brief Get the socket
         * @return boost::asio::ip::udp::socket
        */
        boost::asio::ip::udp::socket &getSocket()
        {
            return *m_socket;
        }

    private:
        int m_port;
        std::shared_ptr<boost::asio::io_context> m_ioContext;
        std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
        std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
        boost::array<char, rtype::network::message::MAX_PACKET_SIZE> m_recvBuffer;
        std::shared_ptr<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>> m_recvMsgBuffer;
        std::shared_ptr<boost::thread> m_thread;
        std::chrono::high_resolution_clock::time_point m_lastTick;
        size_t m_tickRate;
        static std::shared_ptr<NetworkServer> instance;
    };

    std::shared_ptr<NetworkServer> NetworkServer::instance = nullptr;
}
