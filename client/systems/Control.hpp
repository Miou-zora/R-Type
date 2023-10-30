/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control
*/

#pragma once

#include "Controllable.hpp"
#include "ECS.hpp"
#include "Speed.hpp"
#include "Vector.hpp"
#include "Velocity.hpp"

namespace rtype::system {
/**
 * @brief Control system used to update the velocity of the entities based on inputs
 */
class Control {
public:
    Control() = default;
    ~Control() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Controllable> const& controllables,
        ecs::SparseArray<rtype::component::Velocity>& velocities) const
    {
        for (auto&& [index, controllable, velocity] : ecs::containers::IndexedZipper(controllables, velocities)) {
            rtype::utils::Vector<float> direction((controllable.value().isKeyRightPressed() - controllable.value().isKeyLeftPressed()), (controllable.value().isKeyDownPressed() - controllable.value().isKeyUpPressed()));
            if (direction.getLength() != 0)
                velocity.value().vector = direction.normalized() * registry.getDeltaTime() * (registry.hasComponent<rtype::component::Speed>(registry.entityFromIndex(index)) ? registry.getComponents<rtype::component::Speed>()[registry.entityFromIndex(index)].value().value : 100);
            else
                velocity.value().vector = rtype::utils::Vector<float>(0, 0);
        }
    }
};
}
