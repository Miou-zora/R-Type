/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SceneManager
*/

#pragma once

#include <map>
#include <functional>
#include "Vector.hpp"
#include "ECS.hpp"
#include "PrefabManager.hpp"
#include "Scenes.hpp"

namespace rtype::utils
{
/**
 * @brief SceneManager singleton that handle scene switching
 *
 */
class SceneManager {
private:
    SceneManager() : m_currentScene(Scene::NONE), m_previousScene(Scene::NONE), m_nextScene(Scene::NONE) {};
public:
    ~SceneManager() = default;
    SceneManager(const SceneManager &) = delete;
    SceneManager &operator=(const SceneManager &) = delete;

    /**
     * @brief Get the instance of the SceneManager. If it doesn't exist, it will be created.
    */
    static SceneManager &getInstance()
    {
        if (!m_instance)
            m_instance = new SceneManager();
        return (*m_instance);
    }

    /**
     * @brief Unload the current scene and destroy all entities
     *
     * @param registry
     */
    void unloadCurrentScene(ecs::Registry& registry);

    /**
     * @brief Load a scene by destroying all entities and creating new ones
     *
     * @param registry
     * @param scene the scene to load
     * @return true in case of success
     * @return false in case of failure (if the scene is already loaded)
     */
    bool loadScene(Scene scene, ecs::Registry& registry);

    void addPrefabToScene(std::string prefabName, Scene scene) {
        m_scenes[scene].push_back(prefabName);
    }

    Scene getCurrentScene() const { return m_currentScene; }
    Scene getPreviousScene() const { return m_previousScene; }
    void setNextScene(Scene scene) { m_nextScene = scene; }
    Scene getNextScene() const { return m_nextScene; }

    #ifdef UNIT_TEST
        std::vector<ecs::Entity> &getEntities() { return m_entities; }
        std::map<Scene, std::vector<std::string>> &getScenes() { return m_scenes; }
    #endif

private:
    static SceneManager *m_instance;
    Scene m_currentScene;
    Scene m_previousScene;
    Scene m_nextScene;
    std::map<Scene, std::vector<std::string>> m_scenes = {
        {Scene::LOGIN, {}},
        {Scene::MENU, {}},
        {Scene::ROOM, {}},
        {Scene::JOIN, {}},
        {Scene::OPTIONS, {}},
        {Scene::GAME, {}},
        {Scene::NONE, {}}
    };
    std::vector<ecs::Entity> m_entities;
};
    inline SceneManager *SceneManager::m_instance = nullptr;
}
