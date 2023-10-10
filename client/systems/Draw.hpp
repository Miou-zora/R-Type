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
#include "Transform.hpp"
#include <functional>
namespace raylib
{
#include <raylib.h>
}

namespace rtype::system
{
    class Draw
    {
    public:
        Draw() = default;
        ~Draw() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Transform> &transformables,
                        ecs::SparseArray<rtype::component::Drawable> &drawables) const
        {
            (void)registry;
            raylib::BeginDrawing();
            raylib::ClearBackground(raylib::BLACK);
            std::map<int, std::pair<rtype::component::Transform, rtype::component::Drawable>> sorted;
            for (auto &&[transformable, drawable] : rtype::ecs::containers::Zipper(transformables, drawables))
            {
                sorted.insert({drawable->zIndex, {transformable.value(), drawable.value()}});
            }
            for (auto &&[zIndex, transformableAndDrawable] : sorted)
                draw(transformableAndDrawable.first, transformableAndDrawable.second);
            raylib::EndDrawing();
        }

    private:
        void draw(rtype::component::Transform &transform, rtype::component::Drawable &drawable) const
        {
            const raylib::Texture2D &texture = rtype::utils::AssetsManager::getInstance().getTexture(drawable.textureName);
            const raylib::Rectangle &sourceRec = drawable.sourceRectangle.rectangle;
            const raylib::Rectangle &destRec = raylib::Rectangle{transform.position.x, transform.position.y,
                                                                 (float)drawable.sourceRectangle.rectangle.width * transform.scale * drawable.scale,
                                                                 (float)drawable.sourceRectangle.rectangle.height * transform.scale * drawable.scale};
            raylib::DrawTexturePro(texture, sourceRec, destRec, raylib::Vector2{0, 0}, transform.rotation, raylib::WHITE);
        }
    };
}
