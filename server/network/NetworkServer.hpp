#pragma once

#include <queue>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "ContextManager.hpp"
#include "NetworkMessage.hpp"

namespace rtype::network {
class NetworkServer {
public:
    /**
     * @brief init the instance of the singleton
     * @param port Port to listen on
     */
    static void initInstance(int port)
    {
        instance = std::make_shared<NetworkServer>(port);
    }

    /**
     * @brief Get the instance of the singleton
     * @return NetworkServer&
     */
    static NetworkServer& getInstance()
    {
        return *instance;
    }

    /**
     * @brief Construct a new Network Server object
     * @param port Port to listen on
     */
    NetworkServer(int port)
    {
        m_port = port;
        m_socket = std::make_shared<boost::asio::ip::udp::socket>(rtype::network::ContextManager::getInstance().getContext("server"));
        m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::v4(), m_port);
        m_recvMsgBuffer = std::make_shared<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>>();
        m_socket->open(m_endpoint->protocol());
        m_socket->bind(*m_endpoint);
        m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint, boost::bind(&NetworkServer::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        m_lastTick = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Destroy the Network Server object
     */
    ~NetworkServer() = default;

    /**
     * @brief Handle receive callback for boost asio socket
     * @param error Error code
     * @param bytes_transferred Bytes transferred from the socket
     */
    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error) {
            std::cerr << "Network error (handleReceive): " << error.message() << std::endl;
        } else {
            m_recvMsgBuffer->push_back(std::make_tuple(*m_endpoint, m_recvBuffer, bytes_transferred));
        }
        m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint, boost::bind(&NetworkServer::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    /**
     * @brief Handle send callback for boost asio socket
     * @param error Error code
     * @param bytes_transferred Bytes transferred to the endpoint
     */
    void handleSend(const boost::system::error_code& error, std::size_t bytes_transferred)
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
     * @brief Get the recv message buffer
     * @return std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>
     */
    std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>& getRecvMsgBuffer()
    {
        return *m_recvMsgBuffer;
    }

    /**
     * @brief Get the socket
     * @return boost::asio::ip::udp::socket
     */
    boost::asio::ip::udp::socket& getSocket()
    {
        return *m_socket;
    }

private:
    int m_port;
    std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
    std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
    boost::array<char, rtype::network::message::MAX_PACKET_SIZE> m_recvBuffer;
    std::shared_ptr<std::vector<std::tuple<boost::asio::ip::udp::endpoint, boost::array<char, rtype::network::message::MAX_PACKET_SIZE>, size_t>>> m_recvMsgBuffer;
    std::chrono::high_resolution_clock::time_point m_lastTick;
    static std::shared_ptr<NetworkServer> instance;
};

std::shared_ptr<NetworkServer> NetworkServer::instance = nullptr;
}
