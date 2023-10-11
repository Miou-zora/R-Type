/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

void rtype::utils::SceneManager::unloadCurrentScene(rtype::ecs::Registry &registry)
{
    m_previousScene = m_currentScene;
    if (m_entities.empty()) {
        m_currentScene = Scene::NONE;
        return;
    }
    for (auto &entity : m_entities) {
        registry.killEntity(entity);
    }
    m_entities.clear();
    m_currentScene = Scene::NONE;
}

bool rtype::utils::SceneManager::loadScene(rtype::utils::Scene scene, rtype::ecs::Registry &registry)
{
    if (m_currentScene == scene)
        return false;
    unloadCurrentScene(registry);
    m_currentScene = scene;
    for (auto &prefab : m_scenes[scene]) {
        m_entities.push_back(rtype::utils::PrefabManager::getInstance().instantiate(prefab, registry));
    }
    return true;
}
