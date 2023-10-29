/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SceneManager
*/

#include "SceneManager.hpp"
#include "Ally.hpp"
#include "Enemy.hpp"

void rtype::utils::SceneManager::unloadCurrentScene(rtype::ecs::Registry &registry)
{
    if (m_entities.empty()) {
        m_currentScene = Scene::NONE;
        return;
    }
    for (auto &entity : m_entities) {
        registry.killEntity(entity);
    }
    for (auto&& [index, enemy] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::tag::Enemy>())) {
        if (m_currentScene == Scene::GAME) {
            registry.killEntity(registry.entityFromIndex(index));
        }
    }
    for (auto&& [index, ally] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::tag::Ally>())) {
        if (m_currentScene == Scene::GAME) {
            registry.killEntity(registry.entityFromIndex(index));
        }
    }

    m_entities.clear();
    m_currentScene = Scene::NONE;
}

bool rtype::utils::SceneManager::loadScene(rtype::utils::Scene scene, rtype::ecs::Registry &registry)
{
    m_previousScene = m_currentScene;
    unloadCurrentScene(registry);
    m_currentScene = scene;
    for (auto &prefab : m_scenes[scene]) {
        rtype::ecs::Entity entity = rtype::utils::PrefabManager::getInstance().instantiate(prefab, registry);
        m_entities.push_back(entity);
    }
    return true;
}
