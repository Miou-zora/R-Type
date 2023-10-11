/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Selection
*/

#pragma once

#include "Collider.hpp"
#include "ECS.hpp"
#include "Selectable.hpp"
#include "Transform.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
class Selection {
public:
    Selection() = default;
    ~Selection() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Selectable>& selectables,
        ecs::SparseArray<rtype::component::Transform> const& transforms,
        ecs::SparseArray<rtype::component::Collider> const& colliders) const
    {
        bool isMouseRelease = raylib::IsMouseButtonPressed(raylib::MOUSE_LEFT_BUTTON);
        if (!isMouseRelease)
            return;
        raylib::Vector2 mousePos = raylib::GetMousePosition();
        for (auto&& [index, selectable, transform, collider] : ecs::containers::IndexedZipper(selectables, transforms, colliders)) {
            if (isMouseOver(mousePos, transform->position, collider->size))
                selectable->selected = true;
            else
                selectable->selected = false;
        }
    }

private:
    static bool isMouseOver(raylib::Vector2 mousePos, rtype::component::Transform const& transform, rtype::component::Collider const& collider)
    {
        return (mousePos.x >= transform.position.x && mousePos.x <= transform.position.x + collider.size.x && mousePos.y >= transform.position.y && mousePos.y <= transform.position.y + collider.size.y);
    }
};
}
