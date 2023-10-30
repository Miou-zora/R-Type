/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** UpdateKeyInputBox
*/

#pragma once

#include "ECS.hpp"
#include "Key.hpp"
#include "Text.hpp"
#include "KeyToString.hpp"

namespace rtype::system {
    /**
     * @brief System used to update the key input box on the window
     */
    class UpdateKeyInputBox {
        public:
            UpdateKeyInputBox() = default;
            ~UpdateKeyInputBox() = default;

            void operator()(ecs::Registry& registry,
                rtype::ecs::SparseArray<rtype::component::Key>& keys,
                rtype::ecs::SparseArray<rtype::component::Text>& texts) const
            {
                for (auto&& [key, text] : rtype::ecs::containers::Zipper(keys, texts)) {
                    if (key->key != raylib::KEY_NULL)
                        text->text = rtype::utils::keyToString(static_cast<raylib::KeyboardKey>(key->key));
                }
            }
    };
}
