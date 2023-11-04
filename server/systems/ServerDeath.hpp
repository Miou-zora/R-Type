/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Death
*/

#pragma once

#include "Ally.hpp"
#include "ECS.hpp"
#include "Enemy.hpp"
#include "GameRoom.hpp"
#include "Health.hpp"
#include "NetworkPlayer.hpp"
#include "Communication.hpp"
#include "Points.hpp"

namespace rtype::system
{
    /**
     * @brief Death system used to kill entities with a health component with a value of 0 or less
     */
    class ServerDeath
    {
    public:
        ServerDeath() = default;
        ~ServerDeath() = default;

        /**
         * @brief Kills entities with a health component with a value of 0 or less
         *
         * @param registry
         * @param health component
         */
        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Health> &healths,
                        ecs::SparseArray<rtype::component::Killable> &killables) const
        {
            for (auto &&[index, health, killable] : ecs::containers::IndexedZipper(healths, killables))
            {
                if (health.value().value <= 0)
                {
                    killable.value().to_kill = true;
                }
            }
        }
    };
}
