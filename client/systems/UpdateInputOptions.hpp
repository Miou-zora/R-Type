/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** UpdateInputOptions
*/

#pragma once

#include <ECS.hpp>
#include "OptionManager.hpp"
#include "Nameable.hpp"
#include "Key.hpp"

namespace rtype::system {
    /**
     * @brief System used to update the input options in the manager
     */
    class UpdateInputOptions {
        public:
            UpdateInputOptions() = default;
            ~UpdateInputOptions() = default;

            void operator()(ecs::Registry& registry,
                ecs::SparseArray<rtype::component::Nameable>& names,
                ecs::SparseArray<rtype::component::Key>& keys) const
            {
                auto& optionManager = rtype::utils::OptionManager::getInstance();

                for (auto&& [key, name] : rtype::ecs::containers::Zipper(keys, names)) {
                    if (name->name == "UP_INBOX") {
                        optionManager.setKeyUp(key->key);
                    }
                    if (name->name == "DOWN_INBOX") {
                        optionManager.setKeyDown(key->key);
                    }
                    if (name->name == "LEFT_INBOX") {
                        optionManager.setKeyLeft(key->key);
                    }
                    if (name->name == "RIGHT_INBOX") {
                        optionManager.setKeyRight(key->key);
                    }
                    if (name->name == "SHOOT_INBOX") {
                        optionManager.setKeyShoot(key->key);
                    }
                }
            }
    };
}
