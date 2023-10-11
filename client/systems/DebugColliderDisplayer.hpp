/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** DebugColliderDisplayer
*/

#pragma once

#include "Collider.hpp"
#include "DebugColliderDisplay.hpp"
#include "ECS.hpp"
#include "Transform.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
class DebugColliderDisplayer {
public:
    DebugColliderDisplayer(void) = default;
    ~DebugColliderDisplayer(void) = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::DebugColliderDisplay>& debugColliderDisplays,
        ecs::SparseArray<rtype::component::Transform> const& transforms,
        ecs::SparseArray<rtype::component::Collider> const& colliders) const
    {
        for (auto&& [index, debugColliderDisplay, transform, collider] : ecs::containers::IndexedZipper(debugColliderDisplays, transforms, colliders)) {
            if (debugColliderDisplay->display)
                drawCollider(transform->position, collider->size);
        }
    }

private:
    void drawCollider(const rtype::utils::Vector<float>& position, const rtype::utils::Vector<float>& size) const
    {
        raylib::Rectangle rect = { position.x, position.y, size.x, size.y };
        raylib::DrawRectangleLinesEx(rect, 1, raylib::RED);
    }
};
}
