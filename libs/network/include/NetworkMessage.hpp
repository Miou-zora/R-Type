/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** NetworkMessage
*/

#pragma once

#include <string>
#include <ctime>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

#include <boost/uuid/uuid.hpp>

#include <boost/array.hpp>
#include <boost/crc.hpp>
namespace zstd {
    #include <zstd.h>
}

#ifdef _WIN32
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
    typedef uint64_t u_int64_t;
    typedef int8_t int8_t;
    typedef int16_t int16_t;
    typedef int32_t int32_t;
    typedef int64_t int64_t;
    typedef float float_t;
    typedef double double_t;
#endif

namespace rtype::network {
    namespace message {
        static const u_int32_t MAX_MESSAGE_SIZE = 128;
        static const u_int32_t MAX_PACKET_SIZE = 1024;
        static const char HEADER_MAGIC[2] = {'R', 'T'};
        static const char FOOTER_MAGIC[2] = {'T', 'R'};
        static u_int64_t g_packetId = 0;

        #pragma pack(push, 1)
        struct NetworkMessageHeader {
            char magic[2];
            u_int16_t type;
            u_int64_t id;
        };
        #pragma pack(pop)

        /**
         * @brief Create a new event object
         * @tparam T Type of the event to create
         * @tparam Args Types of the arguments to pass to the event constructor
         * @param args Arguments to pass to the event constructor
         * @return T The created event
        */
        template<typename T, class ...Args>
        T createEvent(Args &&...args)
        {
            T message(std::forward<Args>(args)...);
            std::memcpy(message.header.magic, HEADER_MAGIC, sizeof(HEADER_MAGIC));
            message.header.type = T::type;
            message.header.id = g_packetId++;
            return (message);
        }

        /**
         * @brief Check if the header magic is correct from a raw byte buffer
         * @param buffer The raw byte buffer
         * @return true The header magic is correct
        */
        inline bool checkHeaderMagic(const char *buffer)
        {
            return std::memcmp(buffer, HEADER_MAGIC, sizeof(HEADER_MAGIC)) == 0;
        }

        /**
         * @brief Pack a message into a raw byte buffer
         * @tparam T Type of the message to pack
         * @param buffer The raw byte buffer
         * @param message The message to pack
         * @return void
        */
        template<typename T>
        void pack(char *buffer, T &message)
        {
            std::memcpy(buffer, &message, sizeof(T));
        }

        /**
         * @brief Pack a message into a raw byte buffer
         * @tparam T Type of the message to pack
         * @param buffer The raw byte buffer
         * @param message The message to pack
         * @return void
        */
        template<typename T>
        boost::array<char, MAX_MESSAGE_SIZE> pack(T &message)
        {
            boost::array<char, MAX_MESSAGE_SIZE> buffer;
            std::memcpy(buffer.data(), &message, sizeof(T));
            return (buffer);
        }
        
        /**
         * @brief Unpack a message from a raw byte buffer
         * @tparam T Type of the message to unpack
         * @param buffer The raw byte buffer
         * @return T The unpacked message
        */
        template<typename T>
        T unpack(char *buffer)
        {
            return (*reinterpret_cast<T *>(buffer));
        }

        /**
         * @brief Unpack a message from a raw byte buffer
         * @tparam T Type of the message to unpack
         * @param buffer The raw byte buffer
         * @return T The unpacked message
        */
        template<typename T>
        const T unpack(const char *buffer)
        {
            return (*reinterpret_cast<const T *>(buffer));
        }

        /**
         * @brief Unpack a message from a boost array
         * @tparam T Type of the message to unpack
         * @param buffer The boost array
         * @return T The unpacked message
        */
        template<typename T>
        const T unpack(const boost::array<char, MAX_MESSAGE_SIZE> &buffer)
        {
            return (*reinterpret_cast<const T *>(buffer.data()));
        }

        inline size_t getMessageSize(const char *data, const std::size_t lookup[][2])
        {
            auto *header = reinterpret_cast<const NetworkMessageHeader *>(data);

            for (std::size_t i = 0; lookup[i][0] != 0xFFFF; i++) {
                if (static_cast<u_int16_t>(lookup[i][0]) == header->type)
                    return lookup[i][1];
            }
            throw std::runtime_error("Unknown message type");
        }

        inline size_t getMessageSize(const boost::array<char, MAX_MESSAGE_SIZE> &array, const std::size_t lookup[][2])
        {
            return getMessageSize(array.data(), lookup);
        }

        /**
         * @brief Check whole message integrity
         * @param array The boost array
         * @return true The message is correct
        */
        inline bool checkMessageIntegrity(const char *data, const std::size_t lookup[][2])
        {
            std::size_t size = getMessageSize(data, lookup);
            auto *header = reinterpret_cast<const NetworkMessageHeader *>(data);
            if (checkHeaderMagic(header->magic) == false)
                return false;
            return true;
        }

        /**
         * @brief Check whole message integrity
         * @param array The boost array
         * @param size The size of the message
         * @return true The message is correct
        */
        inline bool checkMessageIntegrity(const boost::array<char, MAX_MESSAGE_SIZE> &array, const std::size_t lookup[][2])
        {
            return checkMessageIntegrity(array.data(), lookup);
        }

        /**
         * @brief Split a packet in multiple messages
         * @param array The array to split
         * @param lookup The lookup table
         * @return std::vector<boost::array<char, MAX_MESSAGE_SIZE>> The splitted messages
        */
        inline std::vector<boost::array<char, MAX_MESSAGE_SIZE>> splitPacketInMessages(const boost::array<char, MAX_PACKET_SIZE> &array, const std::size_t lookup[][2])
        {
            std::vector<boost::array<char, MAX_MESSAGE_SIZE>> messages;

            for (std::size_t i = 0; i < array.size() - sizeof(NetworkMessageHeader); i++) {
                auto header = reinterpret_cast<const NetworkMessageHeader *>(&array[i]);
                if (checkHeaderMagic(header->magic) == false)
                    continue;
                std::size_t estimatedMsgSize = 0;
                try {
                    estimatedMsgSize = getMessageSize(&array[i], lookup);
                } catch (const std::runtime_error &e) {
                    continue;
                }
                if (i + estimatedMsgSize > array.size())
                    break;
                messages.emplace_back();
                std::memcpy(messages.back().data(), &array[i], estimatedMsgSize);
                i += estimatedMsgSize - 1;
            }
            return (messages);
        }

        /**
         * @brief Compress a message
         * @param buffer The buffer to compress
         * @param compressedBuffer The compressed buffer
         * @param bufferSize The size of the buffer
         * @return std::size_t The size of the compressed buffer
         * @throw std::runtime_error If the compression failed
        */
        template<std::size_t N = MAX_PACKET_SIZE>
        std::size_t compressBuffer(const boost::array<char, N> &buffer, boost::array<char, N> &compressedBuffer, std::size_t bufferSize)
        {
            std::size_t compressedSize = zstd::ZSTD_compress(compressedBuffer.data(), N, buffer.data(), bufferSize, 1);
            if (zstd::ZSTD_isError(compressedSize)) {
                throw std::runtime_error(zstd::ZSTD_getErrorName(compressedSize));
            }
            return compressedSize;
        }

        /** 
         * @brief Decompress a message
         * @param buffer The buffer to decompress
         * @param decompressedBuffer The decompressed buffer
         * @param bufferSize The size of the buffer
         * @return std::size_t The size of the decompressed buffer
         * @throw std::runtime_error If the decompression failed
        */
        template<std::size_t N = MAX_PACKET_SIZE>
        std::size_t decompressBuffer(const boost::array<char, N> &buffer, boost::array<char, N> &decompressedBuffer, std::size_t bufferSize)
        {
            std::size_t decompressedSize = zstd::ZSTD_decompress(decompressedBuffer.data(), N, buffer.data(), bufferSize);
            if (zstd::ZSTD_isError(decompressedSize)) {
                throw std::runtime_error(zstd::ZSTD_getErrorName(decompressedSize));
            }
            return decompressedSize;
        }

        namespace client {
            #pragma pack(push, 1)
            struct Connect {
                Connect() = default;

                static const u_int16_t type = 0x0000;
                NetworkMessageHeader header;
            };

            struct Disconnect {
                Disconnect() = default;

                static const u_int16_t type = 0x0001;
                NetworkMessageHeader header;
            };

            struct ChooseRoom {
                ChooseRoom(u_int16_t roomId)
                    : roomId(roomId)
                {
                }

                static const u_int16_t type = 0x0002;
                NetworkMessageHeader header;
                u_int16_t roomId;
            };

            struct ChooseLevel {
                ChooseLevel(u_int16_t levelId)
                    : levelId(levelId)
                {
                }

                static const u_int16_t type = 0x0003;
                NetworkMessageHeader header;
                u_int16_t levelId;
            };

            struct StartGame {
                StartGame() = default;

                static const u_int16_t type = 0x0004;
                NetworkMessageHeader header;
                
            };

            struct CreateRoom {
                CreateRoom() = default;

                static const u_int16_t type = 0x0005;
                NetworkMessageHeader header;
            };

            struct LeaveRoom {
                LeaveRoom() = default;

                static const u_int16_t type = 0x0006;
                NetworkMessageHeader header;
                
            };

            struct PlayerMovement {
                PlayerMovement(float _x, float _y, bool keys_pressed[4])
                    : x(_x), y(_y)
                {
                    std::memcpy(this->keys_pressed, keys_pressed, sizeof(this->keys_pressed));
                }

                static const u_int16_t type = 0x0010;
                NetworkMessageHeader header;
                float x;
                float y;
                bool keys_pressed[4];
            };

            struct PlayerShoot {
                PlayerShoot() = default;

                static const u_int16_t type = 0x0011;
                NetworkMessageHeader header;
            };

            struct PlayerReload {
                PlayerReload() = default;

                static const u_int16_t type = 0x0012;
                NetworkMessageHeader header;
            };

            struct PlayerSwitchWeapon {
                PlayerSwitchWeapon(int16_t _weaponType)
                    : weaponType(_weaponType)
                {
                }

                static const u_int16_t type = 0x0013;
                NetworkMessageHeader header;
                int16_t weaponType;
            };

            struct Ack {
                Ack(u_int64_t _msgId)
                    : msgId(_msgId)
                {
                }

                static const u_int16_t type = 0xFF00;
                NetworkMessageHeader header;
                u_int64_t msgId;
            };
            #pragma pack(pop)

            static constexpr std::size_t g_sizeLookup[][2] = {
                {Connect::type, sizeof(Connect)},
                {Disconnect::type, sizeof(Disconnect)},
                {ChooseRoom::type, sizeof(ChooseRoom)},
                {ChooseLevel::type, sizeof(ChooseLevel)},
                {StartGame::type, sizeof(StartGame)},
                {CreateRoom::type, sizeof(CreateRoom)},
                {LeaveRoom::type, sizeof(LeaveRoom)},
                {PlayerMovement::type, sizeof(PlayerMovement)},
                {PlayerShoot::type, sizeof(PlayerShoot)},
                {PlayerReload::type, sizeof(PlayerReload)},
                {PlayerSwitchWeapon::type, sizeof(PlayerSwitchWeapon)},
                {Ack::type, sizeof(Ack)},
                {0xFFFF, 0}
            };

            inline bool checkMessageIntegrity(const char *data)
            {
                return rtype::network::message::checkMessageIntegrity(data, g_sizeLookup);
            }

            inline bool checkMessageIntegrity(const boost::array<char, MAX_MESSAGE_SIZE> &array)
            {
                return rtype::network::message::checkMessageIntegrity(array, g_sizeLookup);
            }

            inline size_t getMessageSize(const char *data)
            {
                return rtype::network::message::getMessageSize(data, g_sizeLookup);
            }

            inline size_t getMessageSize(const boost::array<char, MAX_MESSAGE_SIZE> &array)
            {
                return rtype::network::message::getMessageSize(array, g_sizeLookup);
            }

            inline std::vector<boost::array<char, MAX_MESSAGE_SIZE>> splitPacketInMessages(const boost::array<char, MAX_PACKET_SIZE> &array)
            {
                return rtype::network::message::splitPacketInMessages(array, g_sizeLookup);
            }
        }

        namespace server {
            #pragma pack(push, 1)
            struct ConnectAck {
                ConnectAck(uint8_t playerUuid_[16])
                {
                    std::copy_n(playerUuid_, 16, playerUuid);
                }

                static const u_int16_t type = 0x0000;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
            };

            struct RoomInformation {
                RoomInformation(u_int16_t _roomId, u_int16_t _playersCount)
                    : roomId(_roomId), playersCount(_playersCount)
                {
                }

                static const u_int16_t type = 0x0001;
                NetworkMessageHeader header;
                u_int16_t roomId;
                u_int16_t playersCount;
            };

            struct LevelInformation {
                LevelInformation(u_int16_t _levelId)
                    : levelId(_levelId)
                {
                }

                static const u_int16_t type = 0x0002;
                NetworkMessageHeader header;
                u_int16_t levelId;
            };

            struct GameStarted {
                GameStarted() = default;

                static const u_int16_t type = 0x0003;
                NetworkMessageHeader header;
            };

            struct GameEnded {
                GameEnded(bool _win)
                    : win(_win)
                {
                }

                static const u_int16_t type = 0x0004;
                NetworkMessageHeader header;
                bool win;
            };

            struct PlayerSpawn {
                PlayerSpawn(uint8_t _playerUuid[16], float _x, float _y)
                    : x(_x), y(_y)
                {
                    std::copy_n(_playerUuid, 16, playerUuid);
                }

                static const u_int16_t type = 0x0010;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
                float x;
                float y;
            };

            struct PlayerDeath {
                PlayerDeath(uint8_t _playerUuid[16], bool _crashed)
                    : crashed(_crashed)
                {
                    std::copy_n(_playerUuid, 16, playerUuid);
                }

                static const u_int16_t type = 0x0011;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
                bool crashed;
            };

            struct PlayerMovement {
                PlayerMovement(uint8_t _playerUuid[16], float _x, float _y)
                    : x(_x), y(_y)
                {
                    std::copy_n(_playerUuid, 16, playerUuid);
                }

                static const u_int16_t type = 0x0012;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
                float x;
                float y;
            };

            struct PlayerWeaponSwitch {
                PlayerWeaponSwitch(uint8_t _playerUuid[16], int16_t _weaponType)
                    : weaponType(_weaponType)
                {
                    std::copy_n(_playerUuid, 16, playerUuid);
                }

                static const u_int16_t type = 0x0013;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
                int16_t weaponType;
            };

            struct PlayerLife {
                PlayerLife(uint8_t _playerUuid[16], u_int32_t _life)
                    : life(_life)
                {
                    std::copy_n(_playerUuid, 16, playerUuid);
                }

                static const u_int16_t type = 0x0014;
                NetworkMessageHeader header;
                uint8_t playerUuid[16];
                u_int32_t life;
            };

            struct EntitySpawn {
                EntitySpawn(uint8_t uuid_[16], float x_, float y_, u_int8_t type_, u_int8_t team_)
                    : x(x_), y(y_), entityType(type_), team(team_)
                {
                    std::copy_n(uuid_, 16, uuid);
                }

                static const u_int16_t type = 0x0020;
                NetworkMessageHeader header;
                uint8_t uuid[16];
                float x;
                float y;
                u_int8_t entityType;
                u_int8_t team;
            };

            struct EntityDeath {
                EntityDeath(uint8_t uuid_[16])
                {
                    std::copy_n(uuid_, 16, uuid);
                }

                static const u_int16_t type = 0x0021;
                NetworkMessageHeader header;
                uint8_t uuid[16];
            };

            struct EntityMovement {
                EntityMovement(uint8_t uuid_[16], float x_, float y_)
                    : x(x_), y(y_)
                {
                    std::copy_n(uuid_, 16, uuid);
                }

                static const u_int16_t type = 0x0022;
                NetworkMessageHeader header;
                uint8_t uuid[16];
                float x;
                float y;
            };

            struct BulletHit {
                BulletHit(uint8_t _bulletUuid[16], uint8_t _hitUuid[16])
                {
                    std::copy_n(_hitUuid, 16, hitUuid);
                    std::copy_n(_bulletUuid, 16, bulletUuid);
                }

                static const u_int16_t type = 0x0032;
                NetworkMessageHeader header;
                uint8_t bulletUuid[16];
                uint8_t hitUuid[16];
            };
            #pragma pack(pop)

            static constexpr std::size_t g_sizeLookup[][2] = {
                {ConnectAck::type, sizeof(ConnectAck)},
                {RoomInformation::type, sizeof(RoomInformation)},
                {LevelInformation::type, sizeof(LevelInformation)},
                {GameStarted::type, sizeof(GameStarted)},
                {GameEnded::type, sizeof(GameEnded)},
                {PlayerSpawn::type, sizeof(PlayerSpawn)},
                {PlayerDeath::type, sizeof(PlayerDeath)},
                {PlayerMovement::type, sizeof(PlayerMovement)},
                {PlayerWeaponSwitch::type, sizeof(PlayerWeaponSwitch)},
                {PlayerLife::type, sizeof(PlayerLife)},
                {EntitySpawn::type, sizeof(EntitySpawn)},
                {EntityDeath::type, sizeof(EntityDeath)},
                {EntityMovement::type, sizeof(EntityMovement)},
                {BulletHit::type, sizeof(BulletHit)},
                {0xFFFF, 0}
            };

            inline bool checkMessageIntegrity(const char *data)
            {
                return rtype::network::message::checkMessageIntegrity(data, g_sizeLookup);
            }

            inline bool checkMessageIntegrity(const boost::array<char, MAX_MESSAGE_SIZE> &array)
            {
                return rtype::network::message::checkMessageIntegrity(array, g_sizeLookup);
            }

            inline size_t getMessageSize(const char *data)
            {
                return rtype::network::message::getMessageSize(data, g_sizeLookup);
            }

            inline size_t getMessageSize(const boost::array<char, MAX_MESSAGE_SIZE> &array)
            {
                return rtype::network::message::getMessageSize(array, g_sizeLookup);
            }

            inline std::vector<boost::array<char, MAX_MESSAGE_SIZE>> splitPacketInMessages(const boost::array<char, MAX_PACKET_SIZE> &array)
            {
                return rtype::network::message::splitPacketInMessages(array, g_sizeLookup);
            }
        }
    }
}
