/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** KeyInput
*/

#pragma once

#include "ECS.hpp"
#include "Key.hpp"
#include "Selectable.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
/**
 * @brief System used to handle the key input
 */
class KeyInput {
public:
    KeyInput() = default;
    ~KeyInput() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Key>& keys,
        ecs::SparseArray<rtype::component::Selectable> &selectables) const
    {
        int inputKey = raylib::GetKeyPressed();

        if (inputKey == 0) {
            return;
        }
        for (auto&& [key, selectable] : ecs::containers::Zipper(keys, selectables)) {
            if (selectable->selected) {
                key->key = inputKey;
            }
        }
    }
};
}
