#include <boost/asio.hpp>

#include "NetworkPlayer.hpp"

#include <gtest/gtest.h>

TEST(NetworkPlayer, constructor)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);

    ASSERT_EQ(networkPlayer.endpoint, endpoint);
    ASSERT_EQ(networkPlayer.inbox->empty(), true);
    ASSERT_EQ(networkPlayer.outbox->empty(), true);
}

TEST(NetworkPlayer, copyConstructor)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);
    rtype::component::NetworkPlayer networkPlayerCopy(networkPlayer);

    ASSERT_EQ(networkPlayerCopy.endpoint, endpoint);
}

TEST(NetworkPlayer, copyAssignmentOperator)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);
    rtype::component::NetworkPlayer networkPlayerCopy = networkPlayer;

    ASSERT_EQ(networkPlayerCopy.endpoint, endpoint);
}

TEST(NetworkPlayer, moveConstructor)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);
    rtype::component::NetworkPlayer networkPlayerCopy(std::move(networkPlayer));

    ASSERT_EQ(networkPlayerCopy.endpoint, endpoint);
}

TEST(NetworkPlayer, moveAssignmentOperator)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);
    rtype::component::NetworkPlayer networkPlayerCopy = std::move(networkPlayer);

    ASSERT_EQ(networkPlayerCopy.endpoint, endpoint);
}

TEST(NetworkPlayer, inboxTests)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);

    ASSERT_EQ(networkPlayer.inbox->empty(), true);
    networkPlayer.inbox->push(boost::array<char, 512UL>());
    ASSERT_EQ(networkPlayer.inbox->empty(), false);
    networkPlayer.inbox->pop();
    ASSERT_EQ(networkPlayer.inbox->empty(), true);
}

TEST(NetworkPlayer, outboxTests)
{
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 4242);
    rtype::component::NetworkPlayer networkPlayer(endpoint);

    ASSERT_EQ(networkPlayer.outbox->empty(), true);
    networkPlayer.outbox->push(boost::array<char, 512UL>());
    ASSERT_EQ(networkPlayer.outbox->empty(), false);
    networkPlayer.outbox->pop();
    ASSERT_EQ(networkPlayer.outbox->empty(), true);
}