/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Collision
*/

#pragma once

#include "ECS.hpp"
#include "Collider.hpp"
#include "Transformable.hpp"
#include "IndexedZipper.hpp"

namespace rtype::system
{
    class Collision
    {
    public:
        Collision() = default;
        ~Collision() = default;

        /**
         * @brief Checks for collisions between entities with a collider component. If a collision is detected, the entity is added to the collider's collideWith vector
         * @param registry The registry containing the entities
         * @param colliders The sparse array containing the colliders
         * @param transformables The sparse array containing the transformables
         */
        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Collider> &colliders,
                        ecs::SparseArray<rtype::component::Transformable> &transformables) const
        {
            for (auto &&[firstIndex, firstCollider, firstTransformable] : ecs::containers::IndexedZipper(colliders, transformables))
            {
                firstCollider.value().collideWith.clear();
                for (auto &&[secondIndex, secondCollider, secondTransformable] : ecs::containers::IndexedZipper(colliders, transformables))
                {
                    if (firstIndex == secondIndex)
                        continue;
                    if (collideWith(firstCollider.value().size, firstTransformable.value().position, secondCollider.value().size, secondTransformable.value().position))
                    {
                        firstCollider.value().collideWith.push_back(registry.entityFromIndex(secondIndex));
                    }
                }
            }
        }
    private:
        static bool collideWith(const rtype::utils::Vector<float> &lSize, const rtype::utils::Vector<float> &lPos, const rtype::utils::Vector<float> &rSize, const rtype::utils::Vector<float> &rPos)
        {
            return (lPos.x < rPos.x + rSize.x &&
                    lPos.x + lSize.x > rPos.x &&
                    lPos.y < rPos.y + rSize.y &&
                    lPos.y + lSize.y > rPos.y);
        }
    };
}
