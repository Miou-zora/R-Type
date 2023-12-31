/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsIndexedZipper
*/

#include "NetworkMessage.hpp"

#include <gtest/gtest.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#define CHECK_MAGICS(msg) ASSERT_EQ(msg.header.magic[0], 'R'); \
                        ASSERT_EQ(msg.header.magic[1], 'T');

TEST(NetworkMessage, createEventConnect)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0000);
}

TEST(NetworkMessage, createEventDisconnect)
{
    rtype::network::message::client::Disconnect msg = rtype::network::message::createEvent<rtype::network::message::client::Disconnect>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0001);
}

TEST(NetworkMessage, createEventChooseRoom)
{
    rtype::network::message::client::ChooseRoom msg = rtype::network::message::createEvent<rtype::network::message::client::ChooseRoom>(42);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0002);
    ASSERT_EQ(msg.roomId, 42);
}

TEST(NetworkMessage, createEventChooseLevel)
{
    rtype::network::message::client::ChooseLevel msg = rtype::network::message::createEvent<rtype::network::message::client::ChooseLevel>(42);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0003);
    ASSERT_EQ(msg.levelId, 42);
}

TEST(NetworkMessage, createEventStartGame)
{
    rtype::network::message::client::StartGame msg = rtype::network::message::createEvent<rtype::network::message::client::StartGame>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0004);
}

TEST(NetworkMessage, createEventCreateRoom)
{
    rtype::network::message::client::CreateRoom msg = rtype::network::message::createEvent<rtype::network::message::client::CreateRoom>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0005);
}

TEST(NetworkMessage, createEventPlayerMovement)
{
    bool keys_pressed[4] = {true, false, true, false};
    rtype::network::message::client::PlayerMovement msg = rtype::network::message::createEvent<rtype::network::message::client::PlayerMovement>(42, 42, keys_pressed);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0010);
    ASSERT_EQ(msg.x, 42);
    ASSERT_EQ(msg.y, 42);
    ASSERT_EQ(msg.keys_pressed[0], true);
    ASSERT_EQ(msg.keys_pressed[1], false);
    ASSERT_EQ(msg.keys_pressed[2], true);
    ASSERT_EQ(msg.keys_pressed[3], false);
}

TEST(NetworkMessage, createEventPlayerShoot)
{
    rtype::network::message::client::PlayerShoot msg = rtype::network::message::createEvent<rtype::network::message::client::PlayerShoot>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0011);
}

TEST(NetworkMessage, createEventPlayerReload)
{
    rtype::network::message::client::PlayerReload msg = rtype::network::message::createEvent<rtype::network::message::client::PlayerReload>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0012);
}

TEST(NetworkMessage, createEventPlayerSwitchWeapon)
{
    rtype::network::message::client::PlayerSwitchWeapon msg = rtype::network::message::createEvent<rtype::network::message::client::PlayerSwitchWeapon>(667);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0013);
    ASSERT_EQ(msg.weaponType, 667);
}

TEST(NetworkMessage, createEventAck)
{
    rtype::network::message::client::Ack msg = rtype::network::message::createEvent<rtype::network::message::client::Ack>(-1);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0xFF00);
}

TEST(NetworkMessage, serverCreateEventConnectAck)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    rtype::network::message::server::ConnectAck msg = rtype::network::message::createEvent<rtype::network::message::server::ConnectAck>(uuid.data);
    CHECK_MAGICS(msg);
    ASSERT_EQ(msg.header.type, 0x0000);
    ASSERT_EQ(std::memcmp(uuid.data, msg.playerUuid, 16), 0);
}

TEST(NetworkMessage, serverCreateEventRoomInformation)
{
    rtype::network::message::server::RoomInformation msg = rtype::network::message::createEvent<rtype::network::message::server::RoomInformation>(42, 1);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0001);
    ASSERT_EQ(msg.roomId, 42);
    ASSERT_EQ(msg.playersCount, 1);
}

TEST(NetworkMessage, serverCreateEventLevelInformation)
{
    rtype::network::message::server::LevelInformation msg = rtype::network::message::createEvent<rtype::network::message::server::LevelInformation>(42);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0002);
    ASSERT_EQ(msg.levelId, 42);
}

TEST(NetworkMessage, serverCreateEventGameStarted)
{
    rtype::network::message::server::GameStarted msg = rtype::network::message::createEvent<rtype::network::message::server::GameStarted>();
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0003);
}

TEST(NetworkMessage, serverCreateEventGameEnded)
{
    rtype::network::message::server::GameEnded msg = rtype::network::message::createEvent<rtype::network::message::server::GameEnded>(true);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0004);
    ASSERT_EQ(msg.win, true);
}

TEST(NetworkMessage, serverCreateEventPlayerSpawn)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::PlayerSpawn msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerSpawn>(uuid.data, 24, 42);


    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0010);
    ASSERT_EQ(std::memcmp(uuid.data, msg.playerUuid, 16), 0);
    ASSERT_EQ(msg.x, 24);
    ASSERT_EQ(msg.y, 42);
}

TEST(NetworkMessage, serverCreateEventPlayerDeath)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::PlayerDeath msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerDeath>(uuid.data, true);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0011);
    ASSERT_EQ(std::memcmp(uuid.data, msg.playerUuid, 16), 0);
    ASSERT_EQ(msg.crashed, true);
}

TEST(NetworkMessage, serverCreateEventPlayerMovement)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::PlayerMovement msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerMovement>(uuid.data, 24, 42);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0012);
    ASSERT_EQ(std::memcmp(uuid.data, msg.playerUuid, 16), 0);
    ASSERT_EQ(msg.x, 24);
    ASSERT_EQ(msg.y, 42);
}

TEST(NetworkMessage, serverCreateEventPlayerWeaponSwitch)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::PlayerWeaponSwitch msg = rtype::network::message::createEvent<rtype::network::message::server::PlayerWeaponSwitch>(uuid.data, 667);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0013);
    ASSERT_EQ(std::memcmp(uuid.data, msg.playerUuid, 16), 0);
    ASSERT_EQ(msg.weaponType, 667);
}

TEST(NetworkMessage, serverCreateEventEntitySpawn)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::EntitySpawn msg = rtype::network::message::createEvent<rtype::network::message::server::EntitySpawn>(uuid.data, 24, 42, 84, 168);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0020);
    ASSERT_EQ(std::memcmp(uuid.data, msg.uuid, 16), 0);
    ASSERT_EQ(msg.x, 24);
    ASSERT_EQ(msg.y, 42);
    ASSERT_EQ(msg.entityType, 84);
    ASSERT_EQ(msg.team, 168);
}

TEST(NetworkMessage, serverCreateEventEntityDeath)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::EntityDeath msg = rtype::network::message::createEvent<rtype::network::message::server::EntityDeath>(uuid.data);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0021);
    ASSERT_EQ(std::memcmp(uuid.data, msg.uuid, 16), 0);
}

TEST(NetworkMessage, serverCreateEventEntityMovement)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::EntityMovement msg = rtype::network::message::createEvent<rtype::network::message::server::EntityMovement>(uuid.data, 24, 42);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0022);
    ASSERT_EQ(std::memcmp(uuid.data, msg.uuid, 16), 0);
    ASSERT_EQ(msg.x, 24);
    ASSERT_EQ(msg.y, 42);
}

TEST(NetworkMessage, serverCreateEventBulletHit)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    boost::uuids::uuid uuid1 = boost::uuids::random_generator()();

    rtype::network::message::server::BulletHit msg = rtype::network::message::createEvent<rtype::network::message::server::BulletHit>(uuid.data, uuid1.data);
    CHECK_MAGICS(msg)
    ASSERT_EQ(msg.header.type, 0x0032);
    ASSERT_EQ(std::memcmp(uuid.data, msg.bulletUuid, 16), 0);
    ASSERT_EQ(std::memcmp(uuid1.data, msg.hitUuid, 16), 0);
}

TEST(NetworkMessage, checkMagics)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(reinterpret_cast<char *>(&msg.header)));
}

TEST(NetworkMessage, MessagePacking)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
}

TEST(NetworkMessage, MessagePackingBoostArray)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> buffer = rtype::network::message::pack(msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer.data()));
}

TEST(NetworkMessage, MessagePackingDataCheck)
{
    bool keys_pressed[4] = {true, false, true, false};
    rtype::network::message::client::PlayerMovement msg = 
    rtype::network::message::createEvent<rtype::network::message::client::PlayerMovement>(42, 24, keys_pressed);
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
    // not a real unpack here because we don't want to test the unpack function
    rtype::network::message::client::PlayerMovement *unpackLike 
    = reinterpret_cast<rtype::network::message::client::PlayerMovement *>(buffer);
    ASSERT_EQ(unpackLike->header.magic[0], 'R');
    ASSERT_EQ(unpackLike->header.magic[1], 'T');
    ASSERT_EQ(unpackLike->header.type, 0x0010);
    ASSERT_EQ(unpackLike->x, 42);
    ASSERT_EQ(unpackLike->y, 24);
    ASSERT_EQ(unpackLike->keys_pressed[0], true);
    ASSERT_EQ(unpackLike->keys_pressed[1], false);
    ASSERT_EQ(unpackLike->keys_pressed[2], true);
    ASSERT_EQ(unpackLike->keys_pressed[3], false);
}

TEST(NetworkMessage, MessagePackingDataCheckBoostArray)
{
    bool keys_pressed[4] = {true, false, true, false};
    rtype::network::message::client::PlayerMovement msg = 
    rtype::network::message::createEvent<rtype::network::message::client::PlayerMovement>(42, 24, keys_pressed);
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> buffer = rtype::network::message::pack(msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer.data()));
    // not a real unpack here because we don't want to test the unpack function
    rtype::network::message::client::PlayerMovement *unpackLike 
    = reinterpret_cast<rtype::network::message::client::PlayerMovement *>(buffer.data());
    ASSERT_EQ(unpackLike->header.magic[0], 'R');
    ASSERT_EQ(unpackLike->header.magic[1], 'T');
    ASSERT_EQ(unpackLike->header.type, 0x0010);
    ASSERT_EQ(unpackLike->x, 42);
    ASSERT_EQ(unpackLike->y, 24);
    ASSERT_EQ(unpackLike->keys_pressed[0], true);
    ASSERT_EQ(unpackLike->keys_pressed[1], false);
    ASSERT_EQ(unpackLike->keys_pressed[2], true);
    ASSERT_EQ(unpackLike->keys_pressed[3], false);
}

TEST(NetworkMessage, MessagePackUnpackSimple)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
    rtype::network::message::client::Connect unpacked = rtype::network::message::unpack<rtype::network::message::client::Connect>(buffer);
    ASSERT_EQ(unpacked.header.magic[0], 'R');
    ASSERT_EQ(unpacked.header.magic[1], 'T');
    ASSERT_EQ(unpacked.header.type, 0x0000);
}

TEST(NetworkMessage, MessagePackUnpackData)
{
    bool keys_pressed[4] = {true, false, true, false};
    rtype::network::message::client::PlayerMovement msg = 
    rtype::network::message::createEvent<rtype::network::message::client::PlayerMovement>(42, 24, keys_pressed);
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
    rtype::network::message::client::PlayerMovement unpacked = rtype::network::message::unpack<rtype::network::message::client::PlayerMovement>(buffer);
    ASSERT_EQ(unpacked.header.magic[0], 'R');
    ASSERT_EQ(unpacked.header.magic[1], 'T');
    ASSERT_EQ(unpacked.header.type, 0x0010);
    ASSERT_EQ(unpacked.x, 42);
    ASSERT_EQ(unpacked.y, 24);
    ASSERT_EQ(unpacked.keys_pressed[0], true);
    ASSERT_EQ(unpacked.keys_pressed[1], false);
    ASSERT_EQ(unpacked.keys_pressed[2], true);
    ASSERT_EQ(unpacked.keys_pressed[3], false);
}

TEST(NetworkMessage, ClientCheckIntegrity)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
    ASSERT_TRUE(rtype::network::message::client::checkMessageIntegrity(buffer));
}

TEST(NetworkMessage, ServerCheckIntegrity)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::ConnectAck msg = rtype::network::message::createEvent<rtype::network::message::server::ConnectAck>(uuid.data);
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer));
    ASSERT_TRUE(rtype::network::message::server::checkMessageIntegrity(buffer));
}

TEST(NetworkMessage, ClientCheckIntegrityBoostArray)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> buffer = rtype::network::message::pack(msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer.data()));
    ASSERT_TRUE(rtype::network::message::client::checkMessageIntegrity(buffer.data()));
}

TEST(NetworkMessage, ServerCheckIntegrityBoostArray)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::ConnectAck msg = rtype::network::message::createEvent<rtype::network::message::server::ConnectAck>(uuid.data);
    boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> buffer = rtype::network::message::pack(msg);
    ASSERT_TRUE(rtype::network::message::checkHeaderMagic(buffer.data()));
    ASSERT_TRUE(rtype::network::message::server::checkMessageIntegrity(buffer.data()));
}

TEST(NetworkMessage, ClientCheckIntegrityFalse)
{
    rtype::network::message::client::Connect msg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    buffer[0] = 'A';
    ASSERT_FALSE(rtype::network::message::client::checkMessageIntegrity(buffer));
}

TEST(NetworkMessage, ServerCheckIntegrityFalse)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    rtype::network::message::server::ConnectAck msg = rtype::network::message::createEvent<rtype::network::message::server::ConnectAck>(uuid.data);
    char buffer[sizeof(msg)] = {0};
    rtype::network::message::pack(buffer, msg);
    buffer[0] = 'A';
    ASSERT_FALSE(rtype::network::message::server::checkMessageIntegrity(buffer));
}

TEST(NetworkMessageSize, getNetworkMessageSizes)
{
    rtype::network::message::client::Connect connectMsg = rtype::network::message::createEvent<rtype::network::message::client::Connect>();
    ASSERT_EQ(rtype::network::message::client::getMessageSize(rtype::network::message::pack<rtype::network::message::client::Connect>(connectMsg)), sizeof(rtype::network::message::client::Connect));
}
