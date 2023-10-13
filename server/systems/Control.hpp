/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control
*/

#pragma once

#include "ECS.hpp"
#include "GameLogicManager.hpp"
#include "NetworkPlayerControl.hpp"
#include "Speed.hpp"
#include "Vector.hpp"
#include "Velocity.hpp"

namespace rtype::system {
class Control {
public:
    Control() = default;
    ~Control() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayerControl>& controllables,
        ecs::SparseArray<rtype::component::Velocity>& velocities,
        ecs::SparseArray<rtype::component::Speed>& speeds) const
    {
        for (auto&& [index, controllable, velocity, speed] : ecs::containers::IndexedZipper(controllables, velocities, speeds)) {
            rtype::utils::Vector<float> direction((controllable.value().right.get() - controllable.value().left.get()), (controllable.value().down.get() - controllable.value().up.get()));
            if (direction.getLength() != 0)
                velocity.value().vector = direction.normalized() * registry.getDeltaTime() * speed.value().value;
            else
                velocity.value().vector = rtype::utils::Vector<float>(0, 0);
        }
    }
};
}
