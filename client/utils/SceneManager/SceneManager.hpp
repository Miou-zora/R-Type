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
public:
    SceneManager() : m_currentScene(Scene::NONE), m_previousScene(Scene::NONE) {};
    ~SceneManager() = default;

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

    Scene getCurrentScene() const { return m_currentScene; }
    Scene getPreviousScene() const { return m_previousScene; }

    #ifdef UNIT_TEST
        std::vector<ecs::Entity> &getEntities() { return m_entities; }
    #endif

private:
    static SceneManager *m_instance;
    Scene m_currentScene;
    Scene m_previousScene;
    std::map<Scene, std::vector<std::string>> m_scenes = {
        {Scene::LOGIN, {"login_play_button", "exit_button"}},
        {Scene::MENU, {"exit_button"}},
        {Scene::LOBBY, {""}},
        {Scene::OPTIONS, {""}},
        {Scene::GAME, {""}},
        {Scene::NONE, {""}}
    };
    std::vector<ecs::Entity> m_entities;
};
    inline SceneManager *SceneManager::m_instance = nullptr;
}
