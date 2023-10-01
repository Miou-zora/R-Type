/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Draw
*/

#include "Draw.hpp"
#include "Zipper.hpp"
#include <raylib.h>
#include "AssetsManager.hpp"

void rtype::system::Draw::operator()(rtype::ecs::Registry &registry,
                                     rtype::ecs::SparseArray<rtype::component::Transformable> &transformables,
                                     rtype::ecs::SparseArray<rtype::component::Drawable> &drawables)
{
    (void)registry;
    for (auto &&[transformable, drawable] : rtype::ecs::containers::Zipper(transformables, drawables))
    {
        const Texture2D &texture = rtype::utils::AssetsManager::getInstance().getTexture(drawable.value().textureName);
        const Rectangle &sourceRec = Rectangle{0, 0, (float) texture.width, (float) texture.height};
        const Rectangle &destRec = Rectangle{transformable.value().position.x, transformable.value().position.y,
                                             (float) texture.width * transformable.value().scale * drawable.value().scale,
                                             (float) texture.height * transformable.value().scale * drawable.value().scale};
        DrawTexturePro(texture, sourceRec, destRec, Vector2{0, 0}, transformable.value().rotation, WHITE);
    }
}
