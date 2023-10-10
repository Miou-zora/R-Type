/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Click
*/

#pragma once

#include "Clickable.hpp"
#include "Collider.hpp"
#include "ECS.hpp"
#include "Transform.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
/**
 * @brief System that handle click on clickable entity
 *
 */
class Click {
public:
    Click() = default;
    ~Click() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Clickable>& clickables,
        ecs::SparseArray<rtype::component::Transform> const& transforms,
        ecs::SparseArray<rtype::component::Collider> const& colliders) const
    {
        for (auto&& [clickable, transform, collider] : ecs::containers::Zipper(clickables, transforms, colliders)) {
            if (arePositionsMatching(raylib::GetMousePosition(), transform.value().position, collider.value().size)) {
                clickable->isHover = true;
                if (raylib::IsMouseButtonReleased(raylib::MOUSE_LEFT_BUTTON)) {
                    clickable->isDown = false;
                    clickable->onClick();
                } else if (raylib::IsMouseButtonPressed(raylib::MOUSE_LEFT_BUTTON)) {
                    clickable->isDown = true;
                }
            } else {
                clickable->isDown = false;
                clickable->isHover = false;
            }
        }
    }

private:
    static bool arePositionsMatching(const raylib::Vector2& mousePos, const rtype::utils::Vector<float>& position, const rtype::utils::Vector<float>& size)
    {
        if (mousePos.x >= position.x && mousePos.x <= position.x + size.x && mousePos.y >= position.y && mousePos.y <= position.y + size.y)
            return true;
        return false;
    }
};
}