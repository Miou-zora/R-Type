/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SwitchScene
*/

#pragma once

#include "ECS.hpp"
#include "SceneManager.hpp"
#include "loads.hpp"

namespace rtype::system {
/**
 * @brief A system that switch scenes using next scene
 */
class SwitchScene {
public:
    SwitchScene() = default;
    ~SwitchScene() = default;

    void operator()(ecs::Registry& registry) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        if (sceneManager.getCurrentScene() != sceneManager.getNextScene()) {
            if (sceneManager.getCurrentScene() == rtype::utils::Scene::OPTIONS) {
                initKeyBindingButtons(registry);
                initSoundTextBox(registry);
                initMusicTextBox(registry);
            }
            sceneManager.loadScene(sceneManager.getNextScene(), registry);
        }
    }
};
}
