/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** GameRoomCollision
*/

#pragma once

#include "Collider.hpp"
#include "ECS.hpp"
#include "GameRoom.hpp"
#include "Transform.hpp"

namespace rtype::system {
class GameRoomCollision {
public:
    GameRoomCollision() = default;
    ~GameRoomCollision() = default;

    /**
     * @brief Checks for collisions between entities with a collider component. If a collision is detected, the entity is added to the collider's collideWith vector
     * @param registry The registry containing the entities
     * @param colliders The sparse array containing the colliders
     * @param transformables The sparse array containing the transformables
     */
    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Collider>& colliders,
        ecs::SparseArray<rtype::component::Transform>& transformables) const
    {
        for (auto&& [firstIndex, firstCollider, firstTransform] : ecs::containers::IndexedZipper(colliders, transformables)) {
            firstCollider.value().collideWith.clear();
            for (auto&& [secondIndex, secondCollider, secondTransform] : ecs::containers::IndexedZipper(colliders, transformables)) {
                if (firstIndex == secondIndex)
                    continue;
                if (collideWith(firstCollider.value().size, firstTransform.value().position, secondCollider.value().size, secondTransform.value().position)) {
                    if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(firstIndex))
                        || !registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(secondIndex)))
                        continue;
                    auto& firstGameRoom = registry.getComponents<rtype::component::GameRoom>()[registry.entityFromIndex(firstIndex)].value();
                    auto& secondGameRoom = registry.getComponents<rtype::component::GameRoom>()[registry.entityFromIndex(secondIndex)].value();
                    if (firstGameRoom.id == secondGameRoom.id)
                        firstCollider.value().collideWith.push_back(registry.entityFromIndex(secondIndex));
                }
            }
        }
    }

private:
    static bool collideWith(const rtype::utils::Vector<float>& lSize, const rtype::utils::Vector<float>& lPos, const rtype::utils::Vector<float>& rSize, const rtype::utils::Vector<float>& rPos)
    {
        return (lPos.x < rPos.x + rSize.x && lPos.x + lSize.x > rPos.x && lPos.y < rPos.y + rSize.y && lPos.y + lSize.y > rPos.y);
    }
};
}
