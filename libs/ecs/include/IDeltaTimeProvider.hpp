/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** IDeltaTimeProvider
*/

#pragma once

namespace rtype::ecs
{
    /**
     * @brief Interface for a class that provides the delta time
    */
    class IDeltaTimeProvider
    {
        public:
            virtual float getDeltaTime(void) = 0;
    };
}
