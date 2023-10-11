/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SceneManager.test
*/

#include "ECS.hpp"
#include "Transform.hpp"
#include "PrefabManager.hpp"
#include "SceneManager.hpp"

#include <gtest/gtest.h>

TEST(SceneManager, getInstance)
{
    auto &sceneManager = rtype::utils::SceneManager::getInstance();

    ASSERT_EQ(&sceneManager, &rtype::utils::SceneManager::getInstance());
}

TEST(SceneManager, unloadCurrentScene)
{
    rtype::ecs::Registry reg;
    rtype::ecs::Entity entity = reg.spawnEntity();

    reg.registerComponent<rtype::component::Transform>();

    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();

    prefabManager.createPrefab("exit_button")
    .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 0));

    prefabManager.createPrefab("login_play_button")
    .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0));

    sceneManager.loadScene(rtype::utils::Scene::LOGIN, reg);

    sceneManager.unloadCurrentScene(reg);

    ASSERT_EQ(sceneManager.getCurrentScene(), rtype::utils::Scene::NONE);
    ASSERT_EQ(sceneManager.getPreviousScene(), rtype::utils::Scene::LOGIN);
    ASSERT_EQ(sceneManager.getEntities().size(), 0);
}

TEST(SceneManager, loadScene)
{
    rtype::ecs::Registry reg;
    rtype::ecs::Entity entity = reg.spawnEntity();

    reg.registerComponent<rtype::component::Transform>();

    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();

    prefabManager.createPrefab("exit_button")
    .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 0));

    prefabManager.createPrefab("login_play_button")
    .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0));

    sceneManager.loadScene(rtype::utils::Scene::LOGIN, reg);

    ASSERT_EQ(sceneManager.getCurrentScene(), rtype::utils::Scene::LOGIN);
    ASSERT_EQ(sceneManager.getPreviousScene(), rtype::utils::Scene::NONE);
    ASSERT_EQ(sceneManager.getEntities().size(), 2);
}
