/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Draw
*/

#pragma once

#include "AssetsManager.hpp"
#include "Drawable.hpp"
#include "ECS.hpp"
#include "Text.hpp"
#include "Transform.hpp"
#include <functional>
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
/**
 * @brief System used to draw the entities
 */
class Draw {
public:
    Draw() = default;
    ~Draw() = default;

    void operator()(ecs::Registry& registry) const
    {
        raylib::BeginDrawing();
        raylib::ClearBackground(raylib::BLACK);

        operator()(registry.getComponents<rtype::component::Transform>(), registry.getComponents<rtype::component::Drawable>());
        operator()(registry.getComponents<rtype::component::Transform>(), registry.getComponents<rtype::component::Text>());

        raylib::EndDrawing();
    }

    void operator()(ecs::SparseArray<rtype::component::Transform>& transformables,
        ecs::SparseArray<rtype::component::Drawable>& drawables) const
    {
        std::map<int, std::vector<std::pair<rtype::component::Transform, rtype::component::Drawable>>> sorted;
        for (auto&& [transformable, drawable] : rtype::ecs::containers::Zipper(transformables, drawables))
            sorted[drawable->zIndex].push_back({ transformable.value(), drawable.value() });
        for (auto&& [zIndex, transformableAndDrawable] : sorted)
            for (auto&& [transformable, drawable] : transformableAndDrawable)
                drawTexture(transformable, drawable);
    }

    void operator()(ecs::SparseArray<rtype::component::Transform>& transformables,
        ecs::SparseArray<rtype::component::Text>& texts) const
    {
        for (auto&& [transformable, text] : rtype::ecs::containers::Zipper(transformables, texts)) {
            const raylib::Font& font = rtype::utils::AssetsManager::getInstance().getFont(text->font);
            const raylib::Vector2 position = raylib::Vector2 { transformable->position.x, transformable->position.y };
            const std::string& textToDraw = text->text;
            const float& fontSize = (float)text->size * transformable->scale;
            const float& spacing = text->spacing * transformable->scale;
            const raylib::Color& color = text->color;
            raylib::DrawTextPro(font, textToDraw.c_str(), position, raylib::Vector2 { 0, 0 }, transformable->rotation, fontSize, spacing, color);
        }
    }

private:
    void drawTexture(rtype::component::Transform& transform, rtype::component::Drawable& drawable) const
    {
        const raylib::Texture2D& texture = rtype::utils::AssetsManager::getInstance().getTexture(drawable.textureName);
        const raylib::Rectangle& sourceRec = drawable.sourceRectangle.rectangle;
        const raylib::Rectangle& destRec = raylib::Rectangle { transform.position.x, transform.position.y,
            (float)drawable.sourceRectangle.rectangle.width * transform.scale * drawable.scale,
            (float)drawable.sourceRectangle.rectangle.height * transform.scale * drawable.scale };
        raylib::DrawTexturePro(texture, sourceRec, destRec, raylib::Vector2 { 0, 0 }, transform.rotation, raylib::WHITE);
    }
};
}
