/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Kill
*/

#pragma once

#include "ECS.hpp"
#include "Killable.hpp"

namespace rtype::system
{
    /**
     * @brief Logging system used to log informations
     */
    class Kill
    {
    public:
        Kill() = default;
        ~Kill() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Killable> &killables)
        {
            for (auto &&[entityIndex, killable] : rtype::ecs::containers::IndexedZipper(killables))
            {
                if (killable.value().to_kill && !killable.value().killed) {
                    registry.killEntity(registry.entityFromIndex(entityIndex));
                    killable.value().killed = true;
                    killable.value().to_kill = false;
                }
                if (killable.value().killed && killable.value().to_kill)
                    killable.value().to_kill = false;
            }
        }
    };
}
