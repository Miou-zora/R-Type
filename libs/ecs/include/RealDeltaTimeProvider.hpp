/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** IDeltaTimeProvider
*/

#pragma once
#include "IDeltaTimeProvider.hpp"
#include <chrono>

namespace rtype::ecs
{
    class RealDeltaTimeProvider : virtual public IDeltaTimeProvider
    {
        public:
            RealDeltaTimeProvider() = default;
            ~RealDeltaTimeProvider() = default;

            float getDeltaTime(void) override
            {
                static std::chrono::time_point<std::chrono::system_clock> last = std::chrono::system_clock::now();
                std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsedSeconds = now - last;
                last = now;
                return (elapsedSeconds.count());
            }
    };
}
