/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** NetworkClient
*/

#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include <set>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "NetworkMessage.hpp"
#include "NetworkMessageQueue.hpp"

namespace rtype::network {
/**
 * @brief A singleton class to manage the network client.
 */
class Client {
    // Singleton part
private:
    Client()
    {
        m_connected = false;
        m_ioService = std::make_shared<boost::asio::io_service>();
        m_resolver = std::make_shared<boost::asio::ip::udp::resolver>(*m_ioService);
        m_socket = std::make_shared<boost::asio::ip::udp::socket>(*m_ioService);
        m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>();
        m_outbox = std::make_shared<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>>();
        m_inbox = std::make_shared<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>>();
        m_recvMsgBuffer = std::make_shared<std::vector<std::tuple<boost::array<char, network::message::MAX_PACKET_SIZE>, size_t>>>();
        m_lastTick = std::chrono::high_resolution_clock::now();
        m_loginSequenceIds = std::make_shared<std::set<u_int64_t>>();
        m_killedEntities = std::make_shared<std::set<std::array<uint8_t, 16>>>();
    }

public:
    /**
     * @brief Get the instance of the Client. If it doesn't exist, it will be created.
     */
    static Client& getInstance()
    {
        if (!m_instance)
            m_instance = new Client();
        return (*m_instance);
    }

private:
    static Client* m_instance;

public:
    ~Client();
    /**
     * @brief Connect to a server.
     * @param ip The ip of the server.
     * @param port The port of the server.
     */
    void connect(std::string ip, int port);
    /**
     * @brief Disconnect from the server.
     */
    void disconnect();
    /**
     * @brief Handle the receive of a packet.
     * @param error The error code.
     * @param bytes_transferred The number of bytes transferred.
     */
    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
    /**
     * @brief Handle the send of a packet.
     * @param error The error code.
     * @param bytes_transferred The number of bytes transferred.
     */
    void handleSend(const boost::system::error_code& error, std::size_t bytes_transferred);
    /**
     * @brief Handle the send of the first packet.
     * @param error The error code.
     * @param bytes_transferred The number of bytes transferred.
     */
    void handleHello(const boost::system::error_code& error, std::size_t bytes_transferred);
    /**
     * @brief Handle the connection to the server.
     * @param error The error code.
     */
    void handleConnect(const boost::system::error_code& error);
    /**
     * @brief Handle the disconnection from the server.
     * @param error The error code.
     */
    void handleDisconnect(const boost::system::error_code& error);
    /**
     * @brief Get the inbox of the client.
     * @return The inbox of the client.
     */
    std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> getInbox() const;
    /**
     * @brief Get the outbox of the client.
     * @return The outbox of the client.
     */
    std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> getOutbox() const;
    /**
     * @brief Get the socket of the client.
     * @return The socket of the client.
     */
    std::shared_ptr<boost::asio::ip::udp::socket> getSocket() const;
    /**
     * @brief Get the endpoint of the client.
     * @return The endpoint of the client.
     */
    std::shared_ptr<boost::asio::ip::udp::endpoint> getEndpoint() const;
    /**
     * @brief Get whether the client is connected to a server or not.
     * @return True if the client is connected to a server, false otherwise.
     */
    bool isConnected() const;
    /**
     * @brief Set whether the client is connected to a server or not.
     * @param connected True if the client is connected to a server, false otherwise.
     */
    void setConnected(bool connected);
    /**
     * @brief Get the buffer of the received messages.
     * @return The buffer of the received messages.
     */
    std::shared_ptr<std::vector<std::tuple<boost::array<char, network::message::MAX_PACKET_SIZE>, size_t>>> getRecvMsgBuffer() const;
    /**
     * @brief Set the Client Id object
     *
     * @param id as uint8_t*
     */
    void setClientId(uint8_t id[16]);
    /**
     * @brief   Get the Client Id object
     * @return  uint8_t*
     */
    uint8_t* getClientId() const;
    /**
     * @brief   Get the login sequence ids object
     * @return  std::shared_ptr<std::set<u_int64_t>>
     */
    std::shared_ptr<std::set<u_int64_t>> getLoginSequenceIds() const;
    /**
     * @brief   Get the last tick time point
     * @return  std::chrono::high_resolution_clock::time_point
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> getLastTick() const;
    /**
     * @brief   Set the last tick time point
     * @param   lastTick
     */
    void setLastTick(std::chrono::time_point<std::chrono::high_resolution_clock> lastTick);
    /**
     * @brief   Insert an entity id in the killed entities set
     * @param   id The entity id to insert
     */
    void insertKilledEntity(std::array<uint8_t, 16> id);
    /**
     * @brief   Insert an entity id in the killed entities set
     * @param   id The entity id to insert
     */
    void insertKilledEntity(uint8_t id[16]);
    /**
     * @brief   Checks if a entity got killed
     * @param   id The entity id to check
     * @return  true if the entity got killed
     */
    bool isEntityKilled(std::array<uint8_t, 16> id) const;
    /**
     * @brief   Checks if a entity got killed
     * @param   id The entity id to check
     * @return  true if the entity got killed
     */
    bool isEntityKilled(uint8_t id[16]) const;

private:
    std::string m_ip;
    int m_port;
    std::shared_ptr<boost::asio::io_service> m_ioService;
    std::shared_ptr<boost::asio::ip::udp::resolver> m_resolver;
    std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
    std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
    std::shared_ptr<std::thread> m_thread;
    boost::array<char, network::message::MAX_PACKET_SIZE> m_recvBuffer;
    std::shared_ptr<std::vector<std::tuple<boost::array<char, network::message::MAX_PACKET_SIZE>, size_t>>> m_recvMsgBuffer;
    std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> m_inbox;
    std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> m_outbox;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;
    std::shared_ptr<std::set<u_int64_t>> m_loginSequenceIds;
    std::shared_ptr<std::set<std::array<uint8_t, 16>>> m_killedEntities;
    bool m_connected;
    uint8_t m_clientId[16];
};

inline Client* Client::m_instance = nullptr;
}
