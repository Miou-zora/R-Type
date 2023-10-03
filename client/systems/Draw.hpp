/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Draw
*/

#pragma once

#include "ECS.hpp"
#include "Drawable.hpp"
#include "AssetsManager.hpp"
#include "Transformable.hpp"

namespace raylib {
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
                        ecs::SparseArray<rtype::component::Transformable> &transformables,
                        ecs::SparseArray<rtype::component::Drawable> &drawables) const
        {
            (void)registry;
            raylib::BeginDrawing();
            raylib::ClearBackground(raylib::BLACK);
            for (auto &&[transformable, drawable] : rtype::ecs::containers::Zipper(transformables, drawables))
            {
                const raylib::Texture2D &texture = rtype::utils::AssetsManager::getInstance().getTexture(drawable.value().textureName);
                const raylib::Rectangle &sourceRec = raylib::Rectangle{0, 0, (float) texture.width, (float) texture.height};
                const raylib::Rectangle &destRec = raylib::Rectangle{transformable.value().position.x, transformable.value().position.y,
                                                    (float) texture.width * transformable.value().scale * drawable.value().scale,
                                                    (float) texture.height * transformable.value().scale * drawable.value().scale};
                raylib::DrawTexturePro(texture, sourceRec, destRec, raylib::Vector2{0, 0}, transformable.value().rotation, raylib::WHITE);
            }
            raylib::EndDrawing();
        }
    };
}