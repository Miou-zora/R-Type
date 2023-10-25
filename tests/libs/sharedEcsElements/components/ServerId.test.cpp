/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** ServerId.test
*/

#include <gtest/gtest.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "ServerID.hpp"

TEST(ServerIdTest, testConstructor)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::component::ServerID serverId(uuid.data);

    ASSERT_EQ(std::memcmp(serverId.uuid, uuid.data, sizeof(uuid.data)), 0);
}

TEST(ServerIdTest, testDefaultConstructor)
{
    rtype::component::ServerID serverId;
    boost::uuids::uuid uuid = boost::uuids::nil_uuid();

    ASSERT_EQ(std::memcmp(serverId.uuid, uuid.data, sizeof(uuid.data)), 0);
}