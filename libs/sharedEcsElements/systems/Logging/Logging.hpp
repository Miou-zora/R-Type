/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Logging
*/

#pragma once

#include "Registry.hpp"
#include "Transformable.hpp"

namespace rtype::system
{
    class Logging
    {
    public:
        Logging() = default;
        ~Logging() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Transformable> &transformables);
    };
}
