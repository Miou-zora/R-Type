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
     * @brief GameLevel component used to store informations about the game level
     */
    struct GameLevel {
        GameLevel(u_int16_t level)
            : level(level) {}
        ~GameLevel() = default;

        GameLevel(const GameLevel &other) = default;
        GameLevel &operator=(const GameLevel &other) = default;

        GameLevel(GameLevel &&other) = default;
        GameLevel &operator=(GameLevel &&other) = default;

        u_int16_t level;
    };
}
