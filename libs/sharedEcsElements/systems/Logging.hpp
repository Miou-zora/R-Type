/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Logging
*/

#pragma once

#include "ECS.hpp"
#include "Transform.hpp"

namespace rtype::system
{
    /**
     * @brief Logging system used to log informations
     */
    class Logging
    {
    public:
        Logging() = default;
        ~Logging() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::Transform> &transformables)
        {
            (void)registry;
            for (auto &&[entityIndex, transformable] : rtype::ecs::containers::IndexedZipper(transformables))
            {
                std::cout << "Entity(" << entityIndex << "): position: " << transformable.value().position << ", scale: " << transformable.value().scale << ", rotation: " << transformable.value().rotation << std::endl;
            }
        }
    };
}
