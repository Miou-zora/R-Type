/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** DamageInflictor
*/

#pragma once

#include "ECS.hpp"
#include "Damage.hpp"
#include "Collider.hpp"
#include "Health.hpp"
#include "Ally.hpp"
#include "Enemy.hpp"
#include "NetworkPlayer.hpp"
#include "GameRoom.hpp"
#include "EntityInformation.hpp"
#include "SingletonWrapper.hpp"
#include "EventManager.hpp"
#include "DamageInfliction.hpp"

namespace rtype::system
{
    /**
     * @brief System used to inflict damage to entities that collide with the entity
     */
    class DamageInflictor
    {
    public:
        DamageInflictor() = default;
        ~DamageInflictor() = default;

        /**
         * @brief Inflict damage to entities that collide with the entity
         *
         * @param registry The registry of the game
         * @param damagers The sparse array of damagers
         * @param colliders The sparse array of colliders
         */
        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Damage> &damagers,
            ecs::SparseArray<rtype::component::Collider> &colliders) const
        {
            for (auto &&[index, damager, collider] : ecs::containers::IndexedZipper(damagers, colliders))
            {
                std::vector<rtype::ecs::Entity> &collisions = collider.value().collideWith;
                for (auto &&entity : collisions) {
                    if (registry.hasComponent<rtype::component::Health>(entity)) {
                        if (
                            !((registry.hasComponent<rtype::tag::Ally>(entity) && registry.hasComponent<rtype::tag::Ally>(registry.entityFromIndex(index))) ||
                            (registry.hasComponent<rtype::tag::Enemy>(entity) && registry.hasComponent<rtype::tag::Enemy>(registry.entityFromIndex(index))))
                            ) {
                            registry.getComponents<rtype::component::Health>()[entity].value().value -= damager.value().value;
                            rtype::utils::SingletonWrapper<rtype::utils::EventManager>::getInstance().addEvent<rtype::event::DamageInfliction>({entity, damager.value().value, registry.getComponents<rtype::component::Health>()[entity].value().value});
                        }
                    }
                }
            }
        }
    };
}
