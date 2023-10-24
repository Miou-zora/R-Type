/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsIndexedZipper
*/

#include "NetworkMessageQueue.hpp"

#include <gtest/gtest.h>

TEST(UniqueVector, basicTestString)
{
    rtype::network::message::UniqueVector<std::string> vec;

    vec.push_back("test");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], "test");
    vec.push_back("test");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], "test");
    vec.push_back("test2");
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], "test");
    ASSERT_EQ(vec[1], "test2");
    vec.push_back("test2");
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], "test");
    ASSERT_EQ(vec[1], "test2");
}

TEST(UniqueVector, basicTestInts)
{
    rtype::network::message::UniqueVector<int> vec;

    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], 1);
    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], 1);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

// Weird equal comparaison that compares absolute values (for testing purposes)
struct EqualCompare {
    bool operator()(const int &lhs, const int &rhs) const
    {
        return (std::abs(lhs) == std::abs(rhs));
    }
};

TEST(UniqueVector, customCompare)
{
    rtype::network::message::UniqueVector<int, EqualCompare> vec;

    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], 1);
    vec.push_back(-1);
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], 1);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
    vec.push_back(-2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

TEST(NetworkMessageQueue, basicTests)
{
    rtype::network::message::NetworkMessageQueue queue;
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg1;
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg2;

    std::copy("test", "test" + 4, msg1.begin());
    std::copy("test2", "test2" + 5, msg2.begin());

    ASSERT_TRUE(queue.empty());
    queue.push(msg1);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 1);
    queue.push(msg2);
    ASSERT_EQ(queue.size(), 2);
    queue.pop();
    ASSERT_EQ(queue.size(), 1);
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(NetworkMessageQueue, identicalMessages)
{
    rtype::network::message::NetworkMessageQueue queue;
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg1 = rtype::network::message::pack(msg);
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg2 = rtype::network::message::pack(msg);

    ASSERT_TRUE(queue.empty());
    queue.push(msg1);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 1);
    queue.push(msg2);
    ASSERT_EQ(queue.size(), 1);
    queue.pop();
    ASSERT_TRUE(queue.empty());
}

TEST(NetworkMessageQueue, differentMessages)
{
    rtype::network::message::NetworkMessageQueue queue;
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg1 = rtype::network::message::pack(msg);
    msg.header.id++;
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg2 = rtype::network::message::pack(msg);

    ASSERT_TRUE(queue.empty());
    queue.push(msg1);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 1);
    queue.push(msg2);
    ASSERT_EQ(queue.size(), 2);
    queue.pop();
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 1);
}

TEST(NetworkMessageQueue, MessageTopGet)
{
    rtype::network::message::NetworkMessageQueue queue;
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> msg1 = rtype::network::message::pack(msg);

    ASSERT_TRUE(queue.empty());
    queue.push(msg1);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.top(), msg1);
    queue.pop();
    ASSERT_TRUE(queue.empty());
}