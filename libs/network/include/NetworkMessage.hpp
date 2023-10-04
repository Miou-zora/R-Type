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

#include <boost/array.hpp>

namespace rtype::network {
    #ifdef _WIN32
        typedef uint8_t u_int8_t;
        typedef uint16_t u_int16_t;
        typedef uint32_t u_int32_t;
        typedef uint64_t u_int64_t;
        typedef int8_t int8_t;
        typedef int16_t int16_t;
        typedef int32_t int32_t;
        typedef int64_t int64_t;
    #endif

    namespace message {
        static const u_int32_t MAX_PACKET_SIZE = 512;
        static const char HEADER_MAGIC[2] = {'R', 'T'};
        static const char FOOTER_MAGIC[2] = {'T', 'R'};
        static u_int64_t g_packetId = 0;

        #pragma pack(push, 1)
        struct NetworkMessageHeader {
            char magic[2];
            u_int16_t type;
            u_int64_t id;
        };

        struct NetworkMessageFooter {
            char magic[2];
        };
        #pragma pack(pop)

        // comparator for priority queue _Compare
        struct NetworkMessageHeaderCompare {
            bool operator()(const NetworkMessageHeader &lhs, const NetworkMessageHeader &rhs) const
            {
                return (lhs.id > rhs.id);
            }

            bool operator()(const NetworkMessageHeader &lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(lhs, *header));
            }

            bool operator()(const char *lhs, const NetworkMessageHeader &rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                return (this->operator()(*header, rhs));
            }

            bool operator()(const char *lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(*header_lhs, *header_rhs));
            }

            bool operator()(const boost::array<char, MAX_PACKET_SIZE> &lhs, const boost::array<char, MAX_PACKET_SIZE> &rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs.data());
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs.data());
                return (this->operator()(*header_lhs, *header_rhs));
            }
        };

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
            std::memcpy(message.footer.magic, FOOTER_MAGIC, sizeof(FOOTER_MAGIC));
            return (message);
        }

        /**
         * @brief Check if the header magic is correct from a raw byte buffer
         * @param buffer The raw byte buffer
         * @return true The header magic is correct
        */
        bool checkHeaderMagic(char *buffer)
        {
            return std::memcmp(buffer, HEADER_MAGIC, sizeof(HEADER_MAGIC)) == 0;
        }

        /**
         * @brief Check if the footer magic is correct from a raw byte buffer
         * @param buffer The raw byte buffer
         * @return true The footer magic is correct
        */
        bool checkFooterMagic(char *buffer)
        {
            return std::memcmp(buffer, FOOTER_MAGIC, sizeof(FOOTER_MAGIC)) == 0;
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
        boost::array<char, MAX_PACKET_SIZE> pack(T &message)
        {
            boost::array<char, MAX_PACKET_SIZE> buffer;
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
         * @brief Unpack a message from a boost array
         * @tparam T Type of the message to unpack
         * @param buffer The boost array
         * @return T The unpacked message
        */
        template<typename T>
        T unpack(boost::array<char, MAX_PACKET_SIZE> &buffer)
        {
            return (*reinterpret_cast<T *>(buffer.data()));
        }

        namespace client {
            #pragma pack(push, 1)
            struct Connect {
                Connect() = default;

                static const u_int16_t type = 0x0000;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct Disconnect {
                Disconnect() = default;

                static const u_int16_t type = 0x0001;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct ChooseRoom {
                ChooseRoom(u_int16_t roomId)
                    : roomId(roomId)
                {
                }

                static const u_int16_t type = 0x0002;
                NetworkMessageHeader header;
                u_int16_t roomId;
                NetworkMessageFooter footer;
            };

            struct ChooseLevel {
                ChooseLevel(u_int16_t levelId)
                    : levelId(levelId)
                {
                }

                static const u_int16_t type = 0x0003;
                NetworkMessageHeader header;
                u_int16_t levelId;
                NetworkMessageFooter footer;
            };

            struct StartGame {
                StartGame() = default;

                static const u_int16_t type = 0x0004;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct CreateRoom {
                CreateRoom() = default;

                static const u_int16_t type = 0x0005;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct PlayerMovement {
                PlayerMovement(u_int16_t _x, u_int16_t _y, bool keys_pressed[4])
                    : x(_x), y(_y)
                {
                    std::memcpy(this->keys_pressed, keys_pressed, sizeof(this->keys_pressed));
                }

                static const u_int16_t type = 0x0010;
                NetworkMessageHeader header;
                u_int16_t x;
                u_int16_t y;
                bool keys_pressed[4];
                NetworkMessageFooter footer;
            };

            struct PlayerShoot {
                PlayerShoot() = default;

                static const u_int16_t type = 0x0011;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct PlayerReload {
                PlayerReload() = default;

                static const u_int16_t type = 0x0012;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct PlayerSwitchWeapon {
                PlayerSwitchWeapon(int16_t _weaponType)
                    : weaponType(_weaponType)
                {
                }

                static const u_int16_t type = 0x0013;
                NetworkMessageHeader header;
                int16_t weaponType;
                NetworkMessageFooter footer;
            };

            struct Ack {
                Ack() = default;

                static const u_int16_t type = 0xFF00;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };
            #pragma pack(pop)
        }

        namespace server {
            #pragma pack(push, 1)
            struct ConnectAck {
                ConnectAck(size_t _playerId)
                    : playerId(_playerId)
                {
                }

                static const u_int16_t type = 0x0000;
                NetworkMessageHeader header;
                size_t playerId;
                NetworkMessageFooter footer;
            };

            struct RoomInformation {
                RoomInformation(u_int16_t _roomId)
                    : roomId(_roomId)
                {
                }

                static const u_int16_t type = 0x0001;
                NetworkMessageHeader header;
                u_int16_t roomId;
                NetworkMessageFooter footer;
            };

            struct LevelInformation {
                LevelInformation(u_int16_t _levelId)
                    : levelId(_levelId)
                {
                }

                static const u_int16_t type = 0x0002;
                NetworkMessageHeader header;
                u_int16_t levelId;
                NetworkMessageFooter footer;
            };

            struct GameStarted {
                GameStarted() = default;

                static const u_int16_t type = 0x0003;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct GameEnded {
                GameEnded() = default;

                static const u_int16_t type = 0x0004;
                NetworkMessageHeader header;
                NetworkMessageFooter footer;
            };

            struct PlayerSpawn {
                PlayerSpawn(u_int16_t _playerId, u_int16_t _x, u_int16_t _y)
                    : playerId(_playerId), x(_x), y(_y)
                {
                }

                static const u_int16_t type = 0x0010;
                NetworkMessageHeader header;
                u_int16_t playerId;
                u_int16_t x;
                u_int16_t y;
                NetworkMessageFooter footer;
            };

            struct PlayerDeath {
                PlayerDeath(u_int16_t _playerId, bool _crashed)
                    : playerId(_playerId), crashed(_crashed)
                {
                }

                static const u_int16_t type = 0x0011;
                NetworkMessageHeader header;
                u_int16_t playerId;
                bool crashed;
                NetworkMessageFooter footer;
            };

            struct PlayerMovement {
                PlayerMovement(u_int16_t _playerId, u_int16_t _x, u_int16_t _y)
                    : playerId(_playerId), x(_x), y(_y)
                {
                }

                static const u_int16_t type = 0x0012;
                NetworkMessageHeader header;
                u_int16_t playerId;
                u_int16_t x;
                u_int16_t y;
                NetworkMessageFooter footer;
            };

            struct PlayerWeaponSwitch {
                PlayerWeaponSwitch(u_int16_t _playerId, int16_t _weaponType)
                    : playerId(_playerId), weaponType(_weaponType)
                {
                }

                static const u_int16_t type = 0x0013;
                NetworkMessageHeader header;
                u_int16_t playerId;
                int16_t weaponType;
                NetworkMessageFooter footer;
            };

            struct EnemySpawn {
                EnemySpawn(u_int16_t _enemyId, u_int16_t _x, u_int16_t _y)
                    : enemyId(_enemyId), x(_x), y(_y)
                {
                }

                static const u_int16_t type = 0x0020;
                NetworkMessageHeader header;
                u_int16_t enemyId;
                u_int16_t x;
                u_int16_t y;
                NetworkMessageFooter footer;
            };

            struct EnemyDeath {
                EnemyDeath(u_int16_t _enemyId)
                    : enemyId(_enemyId)
                {
                }

                static const u_int16_t type = 0x0021;
                NetworkMessageHeader header;
                u_int16_t enemyId;
                NetworkMessageFooter footer;
            };

            struct EnemyMovement {
                EnemyMovement(u_int16_t _enemyId, u_int16_t _x, u_int16_t _y)
                    : enemyId(_enemyId), x(_x), y(_y)
                {
                }

                static const u_int16_t type = 0x0022;
                NetworkMessageHeader header;
                u_int16_t enemyId;
                u_int16_t x;
                u_int16_t y;
                NetworkMessageFooter footer;
            };

            struct BulletShoot {
                BulletShoot(u_int16_t _playerId, int32_t _x, int32_t _y, int32_t _xVelocity, int32_t _yVelocity)
                    : playerId(_playerId), x(_x), y(_y), xVelocity(_xVelocity), yVelocity(_yVelocity)
                {
                }

                static const u_int16_t type = 0x0030;
                NetworkMessageHeader header;
                u_int16_t playerId;
                int32_t x;
                int32_t y;
                int32_t xVelocity;
                int32_t yVelocity;
                NetworkMessageFooter footer;
            };

            struct BulletPosition {
                BulletPosition(u_int16_t _bulletId, int32_t _x, int32_t _y)
                    : bulletId(_bulletId), x(_x), y(_y)
                {
                }

                static const u_int16_t type = 0x0031;
                NetworkMessageHeader header;
                u_int16_t bulletId;
                int32_t x;
                int32_t y;
                NetworkMessageFooter footer;
            };

            struct BulletHit {
                BulletHit(u_int16_t _bulletId, u_int16_t _hitId)
                    : bulletId(_bulletId), hitId(_hitId)
                {
                }

                static const u_int16_t type = 0x0032;
                NetworkMessageHeader header;
                u_int16_t bulletId;
                u_int16_t hitId;
                NetworkMessageFooter footer;
            };

            struct BulletDespawn {
                BulletDespawn(u_int16_t _bulletId)
                    : bulletId(_bulletId)
                {
                }

                static const u_int16_t type = 0x0033;
                NetworkMessageHeader header;
                u_int16_t bulletId;
                NetworkMessageFooter footer;
            };
            #pragma pack(pop)
        }
    }
}