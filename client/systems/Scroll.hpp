/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Scroll
*/

#pragma once

#include "Drawable.hpp"
#include "ECS.hpp"
#include "Scrollable.hpp"

namespace rtype::system {
/**
 * @brief Scroll system used to scroll the texture of an entity.
 */
class Scroll {
public:
    Scroll() = default;
    ~Scroll() = default;

    void operator()(ecs::Registry& registry,
        rtype::ecs::SparseArray<rtype::component::Drawable>& drawables,
        rtype::ecs::SparseArray<rtype::component::Scrollable>& scrollables) const
    {
        for (auto&& [drawable, scrollable] : ecs::containers::Zipper(drawables, scrollables)) {
            auto& scrollableComponent = scrollable.value();
            auto& drawableComponent = drawable.value();

            drawableComponent.sourceRectangle.rectangle.x += scrollableComponent.speed * scrollableComponent.scroll.x * registry.getDeltaTime();
            drawableComponent.sourceRectangle.rectangle.y += scrollableComponent.speed * scrollableComponent.scroll.y * registry.getDeltaTime();
            if (drawableComponent.sourceRectangle.rectangle.x >= drawableComponent.sourceRectangle.rectangle.width)
                drawableComponent.sourceRectangle.rectangle.x -= drawableComponent.sourceRectangle.rectangle.width;
            if (drawableComponent.sourceRectangle.rectangle.y >= drawableComponent.sourceRectangle.rectangle.height)
                drawableComponent.sourceRectangle.rectangle.y -= drawableComponent.sourceRectangle.rectangle.height;
        }
    }
};
}
