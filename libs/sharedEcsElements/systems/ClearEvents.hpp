/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** ClearEvents
*/

#pragma once

#include "ECS.hpp"
#include "SingletonWrapper.hpp"
#include "EventManager.hpp"

namespace rtype::system
{
    /**
     * @brief System used to clear events from eventManager
     */
    class ClearEvents
    {
    public:
        ClearEvents() = default;
        ~ClearEvents() = default;

        /**
         * @brief Clear events from eventManager
         *
         * @param registry The registry of the game
         */
        void operator()(ecs::Registry &registry) const
        {
            rtype::utils::SingletonWrapper<rtype::utils::EventManager>::getInstance().clearEvents();
        }
    };
}
