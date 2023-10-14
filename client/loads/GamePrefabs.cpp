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
#include "PrefabManager.hpp"
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

    assetsManagerInstance.loadTexture("ShipsSheet", ShipsSheet);
    assetsManagerInstance.loadTexture("enemySheet", enemySheet);
    assetsManagerInstance.loadTexture("enemyProjectileSheet", enemyProjectileSheet);
    assetsManagerInstance.loadTexture("allyProjectileSheet", allyProjectileSheet);

    prefabManagerInstance.createPrefab("EnemyProjectile") // Can add animation component
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemyProjectileSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("enemyProjectileSheet").width, assetsManagerInstance.getTexture("enemyProjectileSheet").height), 1)
        .addComponent<rtype::component::ServerID>();
    prefabManagerInstance.createPrefab("Enemy") // Can add animation component
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemySheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("enemySheet").width / 16, assetsManagerInstance.getTexture("enemySheet").height), 1)
        .addComponent<rtype::component::ServerID>();
    prefabManagerInstance.createPrefab("Player")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 5, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 1)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Controllable>(
            []() { return raylib::IsKeyDown(raylib::KEY_UP); },
            []() { return raylib::IsKeyDown(raylib::KEY_DOWN); },
            []() { return raylib::IsKeyDown(raylib::KEY_LEFT); },
            []() { return raylib::IsKeyDown(raylib::KEY_RIGHT); })
        .addComponent<rtype::component::Speed>(200)
        .addComponent<rtype::component::Velocity>()
        .addComponent<rtype::component::AllyNumber>(0);
    prefabManagerInstance.createPrefab("AllyProjectile")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("allyProjectileSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("allyProjectileSheet").width, assetsManagerInstance.getTexture("allyProjectileSheet").height), 1)
        .addComponent<rtype::component::ServerID>();
    prefabManagerInstance.createPrefab("Ally1")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("ShipsSheet").width, assetsManagerInstance.getTexture("ShipsSheet").height), 1)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(1);
    prefabManagerInstance.createPrefab("Ally2")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("ShipsSheet").width, assetsManagerInstance.getTexture("ShipsSheet").height), 1)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(2);
    prefabManagerInstance.createPrefab("Ally3")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 1, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("ShipsSheet").width, assetsManagerInstance.getTexture("ShipsSheet").height), 1)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(3);
}
