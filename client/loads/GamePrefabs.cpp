/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** EnemyPrefabs
*/

#include "AllyNumber.hpp"
#include "Animation.hpp"
#include "AssetsManager.hpp"
#include "Controllable.hpp"
#include "Drawable.hpp"
#include "ECS.hpp"
#include "InputShooter.hpp"
#include "PrefabManager.hpp"
#include "SceneManager.hpp"
#include "Scrollable.hpp"
#include "ServerID.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"

void initGamePrefabs(rtype::ecs::Registry& registry)
{
    rtype::utils::PrefabManager& prefabManagerInstance = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManagerInstance = rtype::utils::AssetsManager::getInstance();

    std::string ShipsSheet = "assets/textures/ships.png";
    std::string enemySheet = "assets/textures/r-typesheet5.png";
    std::string enemyProjectileSheet = "assets/textures/r-typesheet43.png";
    std::string allyProjectileSheet = "assets/textures/bullet.png";
    std::string gameBackground = "assets/textures/layers/parallax-space-background.png";
    std::string stars = "assets/textures/layers/parallax-space-stars.png";
    std::string bigPlanet = "assets/textures/layers/parallax-space-big-planet.png";
    std::string planetRing = "assets/textures/layers/parallax-space-ring-planet.png";
    std::string farPlanets = "assets/textures/layers/parallax-space-far-planets.png";

    assetsManagerInstance.loadTexture("ShipsSheet", ShipsSheet);
    assetsManagerInstance.loadTexture("enemySheet", enemySheet);
    assetsManagerInstance.loadTexture("enemyProjectileSheet", enemyProjectileSheet);
    assetsManagerInstance.loadTexture("allyProjectileSheet", allyProjectileSheet);
    assetsManagerInstance.loadTexture("gameBackground", gameBackground);
    assetsManagerInstance.loadTexture("stars", stars);
    assetsManagerInstance.loadTexture("bigPlanet", bigPlanet);
    assetsManagerInstance.loadTexture("planetRing", planetRing);
    assetsManagerInstance.loadTexture("farPlanets", farPlanets);

    prefabManagerInstance.createPrefab("EnemyProjectile") // Can add animation component
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemyProjectileSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("enemyProjectileSheet").width, assetsManagerInstance.getTexture("enemyProjectileSheet").height), 5)
        .addComponent<rtype::component::ServerID>();
    rtype::component::Animation enemyAnimation;
    enemyAnimation.currentFrame = 0;
    enemyAnimation.finished = false;
    enemyAnimation.loop = true;
    enemyAnimation.playing = true;
    for (std::size_t frame = 0; frame < 8; frame++) {
        enemyAnimation.framesPosition.push_back(rtype::utils::Vector<int>(1 + frame * 33, 0));
        enemyAnimation.frameTimes.push_back(0.15);
    }
    prefabManagerInstance.createPrefab("Enemy") // Can add animation component
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemySheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("enemySheet").width / 16, assetsManagerInstance.getTexture("enemySheet").height), 5)
        .addComponent<rtype::component::Animation>(enemyAnimation)
        .addComponent<rtype::component::ServerID>();
    prefabManagerInstance.createPrefab("Player")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 5, rtype::utils::Rectangle(1, 3, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Controllable>(
            []() { return raylib::IsKeyDown(raylib::KEY_UP); },
            []() { return raylib::IsKeyDown(raylib::KEY_DOWN); },
            []() { return raylib::IsKeyDown(raylib::KEY_LEFT); },
            []() { return raylib::IsKeyDown(raylib::KEY_RIGHT); })
        .addComponent<rtype::component::InputShooter>(
            []() { return raylib::IsKeyDown(raylib::KEY_SPACE); },
            "AllyProjectile",
            0.5,
            0)
        .addComponent<rtype::component::Speed>(200)
        .addComponent<rtype::component::Velocity>()
        .addComponent<rtype::component::AllyNumber>(0);
    prefabManagerInstance.createPrefab("AllyProjectile")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("allyProjectileSheet", 5, rtype::utils::Rectangle(248, 88, 17, 6), 5)
        .addComponent<rtype::component::ServerID>();
    prefabManagerInstance.createPrefab("Ally1")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 5, rtype::utils::Rectangle(1, 20, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(1);
    prefabManagerInstance.createPrefab("Ally2")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 5, rtype::utils::Rectangle(1, 37, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(2);
    prefabManagerInstance.createPrefab("Ally3")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 5, rtype::utils::Rectangle(1, 54, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(3);
    prefabManagerInstance.createPrefab("gameBackground")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("gameBackground", 6, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("gameBackground").width, assetsManagerInstance.getTexture("gameBackground").height), 0)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 5);
    prefabManagerInstance.createPrefab("stars")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("stars", 6, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("stars").width, assetsManagerInstance.getTexture("stars").height), 4)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 40);
    prefabManagerInstance.createPrefab("bigPlanet")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("bigPlanet", 6, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("bigPlanet").width, assetsManagerInstance.getTexture("bigPlanet").height), 3)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 30);
    prefabManagerInstance.createPrefab("planetRing")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("planetRing", 6, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("planetRing").width, assetsManagerInstance.getTexture("planetRing").height), 2)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 20);
    prefabManagerInstance.createPrefab("farPlanets")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("farPlanets", 6, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("farPlanets").width, assetsManagerInstance.getTexture("farPlanets").height), 1)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 10);

    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    sceneManager.addPrefabToScene("gameBackground", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("stars", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("bigPlanet", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("planetRing", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("farPlanets", rtype::utils::Scene::GAME);
}
