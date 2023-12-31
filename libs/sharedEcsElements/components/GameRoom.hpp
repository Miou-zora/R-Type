#pragma once

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

#include <queue>

namespace rtype::component {
    

    /**
     * @brief GameRoom component used to store informations about the game room
     */
    struct GameRoom {
        GameRoom()
            : id(0) {}
        GameRoom(u_int16_t id)
            : id(id) {}
        ~GameRoom() = default;

        GameRoom(const GameRoom &other) = default;
        GameRoom &operator=(const GameRoom &other) = default;

        GameRoom(GameRoom &&other) = default;
        GameRoom &operator=(GameRoom &&other) = default;

        u_int16_t id;
        inline static u_int16_t g_nextGameRoomId = 1;
    };
}
