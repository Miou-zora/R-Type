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
#include "LastUpdate.hpp"
#include "PrefabManager.hpp"
#include "SceneManager.hpp"
#include "Scrollable.hpp"
#include "ServerID.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "Health.hpp"
#include "Text.hpp"
#include "Nameable.hpp"
#include "Ally.hpp"
#include "Enemy.hpp"
#include "PrefabsMapping.hpp"
#include "Enemy.hpp"
#include "Explosive.hpp"
#include "Sound.hpp"

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
    std::string enemyExplosion = "assets/textures/r-typesheet44.png";
    std::string allyExplosion = "assets/textures/bullet.png";
    std::string enemy2 = "assets/textures/r-typesheet14.png";

    std::string blasterSound = "assets/sounds/blaster.mp3";
    std::string explosionSound = "assets/sounds/explosions.wav";
    std::string theme = "assets/sounds/theme.mp3";
    std::string bossShot = "assets/sounds/boss-shot.wav";
    std::string enemyShot = "assets/sounds/enemy-shot.wav";

    assetsManagerInstance.loadTexture("ShipsSheet", ShipsSheet);
    assetsManagerInstance.loadTexture("enemySheet", enemySheet);
    assetsManagerInstance.loadTexture("enemyProjectileSheet", enemyProjectileSheet);
    assetsManagerInstance.loadTexture("allyProjectileSheet", allyProjectileSheet);
    assetsManagerInstance.loadTexture("gameBackground", gameBackground);
    assetsManagerInstance.loadTexture("stars", stars);
    assetsManagerInstance.loadTexture("bigPlanet", bigPlanet);
    assetsManagerInstance.loadTexture("planetRing", planetRing);
    assetsManagerInstance.loadTexture("farPlanets", farPlanets);
    assetsManagerInstance.loadTexture("enemyExplosion", enemyExplosion);
    assetsManagerInstance.loadTexture("allyExplosion", allyExplosion);
    assetsManagerInstance.loadTexture("enemy2", enemy2);
    assetsManagerInstance.loadTexture(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ZOYDO), "assets/textures/r-typesheet18.png");
    assetsManagerInstance.loadTexture(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL), "assets/textures/Top_wall.png");
    assetsManagerInstance.loadTexture(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL), "assets/textures/Bot_wall.png");
    assetsManagerInstance.loadTexture("allyBullet", "assets/textures/ally_bullets.png");

    rtype::component::Animation bossBulletAnimation;
    bossBulletAnimation.currentFrame = 0;
    bossBulletAnimation.finished = false;
    bossBulletAnimation.loop = true;
    bossBulletAnimation.playing = true;
    bossBulletAnimation.time = 0;
    bossBulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(101, 118));
    bossBulletAnimation.frameTimes.push_back(0.15);
    bossBulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(118, 118));
    bossBulletAnimation.frameTimes.push_back(0.15);
    bossBulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(135, 118));
    bossBulletAnimation.frameTimes.push_back(0.15);
    bossBulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(152, 118));
    bossBulletAnimation.frameTimes.push_back(0.15);

    assetsManagerInstance.loadSound("blaster", blasterSound);
    assetsManagerInstance.loadSound("explosion", explosionSound);
    assetsManagerInstance.loadSound("theme", theme);
    assetsManagerInstance.loadSound("bossShot", bossShot);
    assetsManagerInstance.loadSound("enemyShot", enemyShot);

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemyProjectileSheet", 5, rtype::utils::Rectangle(135, 5, 7, 6), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::Sound>("enemyShot")
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TARGET_BULLET))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemyProjectileSheet", 5, rtype::utils::Rectangle(135, 5, 7, 6), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::Sound>("enemyShot")
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("allyBullet", 3, rtype::utils::Rectangle(101, 118, 14, 14), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Animation>(bossBulletAnimation)
        .addComponent<rtype::component::Sound>("bossShot")
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TRIPLE_BULLET))
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TRIPLE_BOSS_BULLET))
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    rtype::component::Animation enemyAnimation;
    enemyAnimation.currentFrame = 0;
    enemyAnimation.finished = false;
    enemyAnimation.loop = true;
    enemyAnimation.playing = true;
    enemyAnimation.time = 0;
    for (std::size_t frame = 0; frame < 8; frame++) {
        enemyAnimation.framesPosition.push_back(rtype::utils::Vector<int>(1 + frame * 33, 0));
        enemyAnimation.frameTimes.push_back(0.15);
    }
    rtype::component::Animation enemyExplosionAnimation;
    enemyExplosionAnimation.currentFrame = 0;
    enemyExplosionAnimation.finished = false;
    enemyExplosionAnimation.loop = false;
    enemyExplosionAnimation.playing = true;
    enemyExplosionAnimation.time = 0;
    enemyExplosionAnimation.killWhenFinished = true;
    for (std::size_t frame = 0; frame < 6; frame++) {
        enemyExplosionAnimation.framesPosition.push_back(rtype::utils::Vector<int>(129 + frame * 33, 1));
        enemyExplosionAnimation.frameTimes.push_back(0.1);
    }

    rtype::component::Animation allyExplosionAnimation;
    allyExplosionAnimation.currentFrame = 0;
    allyExplosionAnimation.finished = false;
    allyExplosionAnimation.loop = false;
    allyExplosionAnimation.playing = true;
    allyExplosionAnimation.time = 0;
    allyExplosionAnimation.killWhenFinished = true;
    for (std::size_t frame = 0; frame < 6; frame++) {
        allyExplosionAnimation.framesPosition.push_back(rtype::utils::Vector<int>(67 + frame * 33, 343));
        allyExplosionAnimation.frameTimes.push_back(0.1);
    }

    rtype::component::Animation zoydoAnimation;
    zoydoAnimation.currentFrame = 0;
    zoydoAnimation.finished = false;
    zoydoAnimation.loop = true;
    zoydoAnimation.playing = true;
    zoydoAnimation.time = 0;
    zoydoAnimation.framesPosition.push_back(rtype::utils::Vector<int>(1, 67));
    zoydoAnimation.frameTimes.push_back(0.15);
    zoydoAnimation.framesPosition.push_back(rtype::utils::Vector<int>(34, 67));
    zoydoAnimation.frameTimes.push_back(0.15);
    zoydoAnimation.framesPosition.push_back(rtype::utils::Vector<int>(67, 67));
    zoydoAnimation.frameTimes.push_back(0.15);
    zoydoAnimation.framesPosition.push_back(rtype::utils::Vector<int>(100, 67));
    zoydoAnimation.frameTimes.push_back(0.15);
    rtype::component::Animation bulletAnimation;
    bulletAnimation.currentFrame = 0;
    bulletAnimation.finished = false;
    bulletAnimation.loop = true;
    bulletAnimation.playing = true;
    bulletAnimation.time = 0;
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(136, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(153, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(170, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(188, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(205, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(223, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(240, 6));
    bulletAnimation.frameTimes.push_back(0.15);
    bulletAnimation.framesPosition.push_back(rtype::utils::Vector<int>(257, 6));
    bulletAnimation.frameTimes.push_back(0.15);

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemySheet", 4, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("enemySheet").width / 16, assetsManagerInstance.getTexture("enemySheet").height), 5)
        .addComponent<rtype::component::Animation>(enemyAnimation)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Explosive>("ExplosionEnemy")
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemy2", 3, rtype::utils::Rectangle(138, 52, 60, 47), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Explosive>("ExplosionEnemy")
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ZOYDO))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ZOYDO), 4, rtype::utils::Rectangle(1, 67, 32, 32), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Explosive>("ExplosionEnemy")
        .addComponent<rtype::component::Animation>(zoydoAnimation)
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Drawable>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL), 4, rtype::utils::Rectangle(0, 0, 1536, rtype::utils::AssetsManager::getInstance().getTexture(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL)).height), 5)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 75)
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Drawable>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL), 4, rtype::utils::Rectangle(0, 0, 1536, rtype::utils::AssetsManager::getInstance().getTexture(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL)).height), 5)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 75)
        .addComponent<rtype::tag::Enemy>()
        .addComponent<rtype::component::LastUpdate>();

    prefabManagerInstance.createPrefab("Player")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 4, rtype::utils::Rectangle(1, 3, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 6)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Controllable>()
        .addComponent<rtype::component::InputShooter>(
            rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET),
            0.5,
            0)
        .addComponent<rtype::component::Speed>(200)
        .addComponent<rtype::component::Health>(10)
        .addComponent<rtype::component::Velocity>()
        .addComponent<rtype::component::AllyNumber>(0)
        .addComponent<rtype::component::Explosive>("ExplosionAlly")
        .addComponent<rtype::tag::Ally>();
    prefabManagerInstance.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET))
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("allyProjectileSheet", 4, rtype::utils::Rectangle(248, 88, 17, 6), 5)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::Sound>("blaster")
        .addComponent<rtype::tag::Ally>()
        .addComponent<rtype::component::LastUpdate>();
    prefabManagerInstance.createPrefab("Ally1")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 4, rtype::utils::Rectangle(1, 20, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 6)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(1)
        .addComponent<rtype::component::Explosive>("ExplosionAlly")
        .addComponent<rtype::tag::Ally>();
    prefabManagerInstance.createPrefab("Ally2")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 4, rtype::utils::Rectangle(1, 37, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 6)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(2)
        .addComponent<rtype::component::Explosive>("ExplosionAlly")
        .addComponent<rtype::tag::Ally>();
    prefabManagerInstance.createPrefab("Ally3")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("ShipsSheet", 4, rtype::utils::Rectangle(1, 54, assetsManagerInstance.getTexture("ShipsSheet").width / 5, assetsManagerInstance.getTexture("ShipsSheet").height / 5), 6)
        .addComponent<rtype::component::ServerID>()
        .addComponent<rtype::component::AllyNumber>(3)
        .addComponent<rtype::component::Explosive>("ExplosionAlly")
        .addComponent<rtype::tag::Ally>();
    prefabManagerInstance.createPrefab("gameBackground")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("gameBackground", 7, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("gameBackground").width, assetsManagerInstance.getTexture("gameBackground").height), 0)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 5);
    prefabManagerInstance.createPrefab("stars")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("stars", 7, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("stars").width, assetsManagerInstance.getTexture("stars").height), 4)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 40);
    prefabManagerInstance.createPrefab("bigPlanet")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("bigPlanet", 7, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("bigPlanet").width, assetsManagerInstance.getTexture("bigPlanet").height), 3)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 30);
    prefabManagerInstance.createPrefab("planetRing")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("planetRing", 7, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("planetRing").width, assetsManagerInstance.getTexture("planetRing").height), 2)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 20);
    prefabManagerInstance.createPrefab("farPlanets")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("farPlanets", 7, rtype::utils::Rectangle(0, 0, assetsManagerInstance.getTexture("farPlanets").width, assetsManagerInstance.getTexture("farPlanets").height), 1)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 10);
    prefabManagerInstance.createPrefab("ExplosionEnemy")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("enemyExplosion", 5, rtype::utils::Rectangle(129, 1, 32, 32), 5)
        .addComponent<rtype::component::Animation>(enemyExplosionAnimation)
        .addComponent<rtype::component::Sound>("explosion")
        .addComponent<rtype::tag::Enemy>();
    prefabManagerInstance.createPrefab("ExplosionAlly")
        .addComponent<rtype::component::Transform>()
        .addComponent<rtype::component::Drawable>("allyExplosion", 5, rtype::utils::Rectangle(129, 1, 32, 32), 5)
        .addComponent<rtype::component::Animation>(allyExplosionAnimation)
        .addComponent<rtype::component::Sound>("explosion")
        .addComponent<rtype::tag::Ally>();
    prefabManagerInstance.createPrefab("playerLifeText")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(10, 1000))
        .addComponent<rtype::component::Text>("Life:", rtype::component::Text::DEFAULT_FONT, 20, 3.f, raylib::WHITE)
        .addComponent<rtype::component::Nameable>("playerLifeText");
    prefabManagerInstance.createPrefab("playerLifeVariable")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(60, 1000))
        .addComponent<rtype::component::Text>("10", rtype::component::Text::DEFAULT_FONT, 20, 3.f, raylib::WHITE)
        .addComponent<rtype::component::Nameable>("playerLifeVariable");

    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    sceneManager.addPrefabToScene("gameBackground", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("stars", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("bigPlanet", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("planetRing", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("farPlanets", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("playerLifeText", rtype::utils::Scene::GAME);
    sceneManager.addPrefabToScene("playerLifeVariable", rtype::utils::Scene::GAME);
}
