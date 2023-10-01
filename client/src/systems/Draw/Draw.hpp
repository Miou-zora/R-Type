/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Draw
*/

#pragma once

#include "Registry.hpp"
#include "Transformable.hpp"
#include "Drawable.hpp"

namespace rtype::system
{
    class Draw
    {
    public:
        Draw() = default;
        ~Draw() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Transformable> &transformables,
                        ecs::SparseArray<rtype::component::Drawable> &drawables);
    };
}
