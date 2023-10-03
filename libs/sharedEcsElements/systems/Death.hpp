/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Death
*/

#pragma once

#include "ECS.hpp"
#include "Health.hpp"

namespace rtype::system
{
    class Death
    {
    public:
        Death() = default;
        ~Death() = default;

        /**
         * @brief Kills entities with a health component with a value of 0 or less
         *
         * @param registry
         * @param health component
         */
        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Health> &health) const
        {
            for (auto &&[index, health] : ecs::containers::IndexedZipper(health))
            {
                if (health.value().value <= 0) {
                    registry.killEntity(registry.entityFromIndex(index));
                }
            }
        }
    };
}