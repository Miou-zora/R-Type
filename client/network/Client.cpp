/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** Client
*/

#include "Client.hpp"

namespace rtype::network {
Client::~Client()
{
    disconnect();
}

void Client::connect(std::string ip, int port)
{
    if (m_connected) {
        std::cerr << "Did not connect: Client already connected" << std::endl;
        return;
    }
    if (m_socket->is_open()) {
        disconnect();
    }
    m_ip = ip;
    m_port = port;
    m_endpoint->port(port);
    m_endpoint->address(boost::asio::ip::address::from_string(ip));
    try {
        m_socket->open(boost::asio::ip::udp::v4());
        m_socket->async_connect(*m_endpoint, boost::bind(&Client::handleConnect, this, boost::asio::placeholders::error));
    } catch (const std::exception &e) {
        std::cerr << "Did not connect: failed to connect to server: " << e.what() << std::endl;
        return;
    }
    m_thread = std::make_shared<std::thread>([this]() { m_ioService->run(); });
}

void Client::disconnect()
{
    if (m_socket) {
        m_socket->close();
        if (m_thread) {
            m_ioService->stop();
            m_thread->join();
            m_thread = nullptr;
        }
        m_inbox->clear();
        m_outbox->clear();
        m_recvBuffer.fill(0);
        m_recvMsgBuffer->clear();
        m_connected = false;
        m_ip = "";
        m_port = 0;
        m_resolver.reset();
        m_socket.reset(); // socket needs to be destroyed before io service
        m_ioService.reset();
        m_endpoint.reset();
        m_thread.reset();
        m_ioService = std::make_shared<boost::asio::io_service>();
        m_resolver = std::make_shared<boost::asio::ip::udp::resolver>(*m_ioService);
        m_socket = std::make_shared<boost::asio::ip::udp::socket>(*m_ioService);
        m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>();
    }
}

void Client::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cerr << "Network error (handleReceive): " << error.message() << std::endl;
    } else {
        m_recvMsgBuffer->push_back(std::make_tuple(m_recvBuffer, bytes_transferred));
        m_recvBuffer.fill(0);
    }
    m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint,
        boost::bind(&Client::handleReceive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleConnect(const boost::system::error_code& error)
{
    if (!error) {
        auto message = network::message::createEvent<network::message::client::Connect>();
        const auto packed = network::message::pack<network::message::client::Connect>(message);
        boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> compressedBuffer;
        std::size_t compressedSize = rtype::network::message::compressBuffer<rtype::network::message::MAX_MESSAGE_SIZE>(packed, compressedBuffer, sizeof(network::message::client::Disconnect));
        m_socket->async_send_to(boost::asio::buffer(compressedBuffer, compressedSize), *m_endpoint,
            boost::bind(&Client::handleHello, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        std::cerr << "Failed to connect to server" << std::endl;
    }
}

void Client::handleDisconnect(const boost::system::error_code& error)
{
    if (!error) {
        auto message = network::message::createEvent<network::message::client::Disconnect>();
        const auto packed = network::message::pack<network::message::client::Disconnect>(message);
        boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> compressedBuffer;
        std::size_t compressedSize = rtype::network::message::compressBuffer<rtype::network::message::MAX_MESSAGE_SIZE>(packed, compressedBuffer, sizeof(network::message::client::Disconnect));
        m_socket->async_send_to(boost::asio::buffer(compressedBuffer, compressedSize), *m_endpoint,
            boost::bind(&Client::handleSend, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        std::cerr << "Failed to disconnect from server" << std::endl;
    }
}

void Client::handleSend(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cerr << "Network error (handleSend): " << error.message() << std::endl;
    }
}

void Client::handleHello(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cerr << "Network error (handleSend): " << error.message() << std::endl;
    } else {
        m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint,
            boost::bind(&Client::handleReceive, this, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> Client::getInbox() const
{
    return m_inbox;
}

std::shared_ptr<network::message::NetworkMessageQueue<boost::array<char, network::message::MAX_MESSAGE_SIZE>, network::message::NetworkMessageHeaderEquality, network::message::NetworkMessageHeaderCompare>> Client::getOutbox() const
{
    return m_outbox;
}

std::shared_ptr<boost::asio::ip::udp::socket> Client::getSocket() const
{
    return m_socket;
}

std::shared_ptr<boost::asio::ip::udp::endpoint> Client::getEndpoint() const
{
    return m_endpoint;
}

bool Client::isConnected() const
{
    return m_connected;
}

void Client::setConnected(bool connected)
{
    m_connected = connected;
}

std::shared_ptr<std::vector<std::tuple<boost::array<char, network::message::MAX_PACKET_SIZE>, std::size_t>>> Client::getRecvMsgBuffer() const
{
    return m_recvMsgBuffer;
}

void Client::setClientId(uint8_t id[16])
{
    std::copy_n(id, 16, m_clientId);
}

uint8_t* Client::getClientId() const
{
    return const_cast<uint8_t*>(m_clientId);
}

std::shared_ptr<std::set<u_int64_t>> Client::getLoginSequenceIds() const
{
    return m_loginSequenceIds;
}

void Client::insertKilledEntity(std::array<uint8_t, 16> id)
{
    m_killedEntities->insert(id);
}

void Client::insertKilledEntity(uint8_t id[16])
{
    std::array<uint8_t, 16> idArray;
    std::copy_n(id, 16, idArray.begin());
    m_killedEntities->insert(idArray);
}

bool Client::isEntityKilled(std::array<uint8_t, 16> id) const
{
    return m_killedEntities->find(id) != m_killedEntities->end();
}

bool Client::isEntityKilled(uint8_t id[16]) const
{
    std::array<uint8_t, 16> idArray;
    std::copy_n(id, 16, idArray.begin());
    return m_killedEntities->find(idArray) != m_killedEntities->end();
}

std::chrono::time_point<std::chrono::high_resolution_clock> Client::getLastTick() const
{
    return m_lastTick;
}

void Client::setLastTick(std::chrono::time_point<std::chrono::high_resolution_clock> lastTick)
{
    m_lastTick = lastTick;
}
}