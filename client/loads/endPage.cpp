/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** endPage
*/

#include "ECS.hpp"
#include "SceneManager.hpp"
#include "PrefabManager.hpp"
#include "AssetsManager.hpp"
#include "Text.hpp"
#include "Nameable.hpp"
#include "Transform.hpp"
#include "Drawable.hpp"
#include "Clickable.hpp"
#include "Collider.hpp"

void initTextEnd(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    prefabManager.createPrefab("win_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(625.0f, 500.0f))
        .addComponent<rtype::component::Text>("GAME WIN", rtype::component::Text::DEFAULT_FONT, 50, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("lose_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(625.0f, 500.0f))
        .addComponent<rtype::component::Text>("GAME LOSE", rtype::component::Text::DEFAULT_FONT, 50, 3.0f, raylib::WHITE);
}

void initEnd(rtype::ecs::Registry& reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initTextEnd(reg);

    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::WIN);
    sceneManager.addPrefabToScene("back_button", rtype::utils::Scene::WIN);
    sceneManager.addPrefabToScene("win_text", rtype::utils::Scene::WIN);
    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::LOSE);
    sceneManager.addPrefabToScene("back_button", rtype::utils::Scene::LOSE);
    sceneManager.addPrefabToScene("lose_text", rtype::utils::Scene::LOSE);
}
