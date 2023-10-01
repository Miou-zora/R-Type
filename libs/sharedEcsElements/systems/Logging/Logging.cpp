/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Logging
*/

#include "Logging.hpp"

#include "Zipper.hpp"
#include "IndexedZipper.hpp"

void rtype::system::Logging::operator()(rtype::ecs::Registry &registry,
                                        rtype::ecs::SparseArray<rtype::component::Transformable> &transformables)
{
    (void)registry;
    for (auto &&[entityIndex, transformable] : rtype::ecs::containers::IndexedZipper(transformables))
    {
        std::cout << "Entity(" << entityIndex << "): position: " << transformable.value().position << ", scale: " << transformable.value().scale << ", rotation: " << transformable.value().rotation << std::endl;
    }
}
