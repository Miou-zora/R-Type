#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include <boost/asio.hpp>

#include "Ally.hpp"
#include "BulletInformation.hpp"
#include "Collider.hpp"
#include "Damage.hpp"
#include "ECS.hpp"
#include "Enemy.hpp"
#include "GameRoom.hpp"
#include "Health.hpp"
#include "NetworkPlayerControl.hpp"
#include "Path.hpp"
#include "PrefabManager.hpp"
#include "Shooter.hpp"
#include "Spawner.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"

namespace rtype::utils {
/**
 * @brief Game logic helper class that defines game logic elements like player speed, bullet speed, etc.
 */
class GameLogicManager {
private:
    /**
     * @brief GameLogicManager constructor
     * @note Define const values here
     */
    GameLogicManager()
    {
        addValue<int>("playerSpeed", 200);
        addValue<rtype::utils::Vector<float>>("defaultPlayerPosition", rtype::utils::Vector<float>(50, 50));
        addValue<float>("playerShootCooldown", 0.5);
        addValue<int>("playerHealth", 100);
        addValue<float>("playerHitboxWidth", 64);
        addValue<float>("playerHitboxHeight", 64);
        addValue<float>("enemySpawnerMovementSpeed", 30);
        addValue<float>("enemySpawnCooldown", 2);
        addValue<int>("enemySpeed", 400);
        addValue<int>("enemyHealth", 1);
        addValue<float>("enemyHitboxWidth", 64);
        addValue<float>("enemyHitboxHeight", 64);
        addValue<rtype::utils::Vector<float>>("defaultEnemyPosition", rtype::utils::Vector<float>(500, 500));
        addValue<float>("enemyShootCooldown", 2);
        addValue<float>("bulletSpeed", 500);
        addValue<float>("bulletHitboxWidth", 5);
        addValue<float>("bulletHitboxHeight", 5);
        addValue<int>("bulletDamage", 1);
    }

public:
    /**
     * @brief Get the GameLogicManager instance
     * @return GameLogicManager instance
     */
    static GameLogicManager& getInstance()
    {
        static GameLogicManager instance;
        return instance;
    }

    /**
     * @brief Add a value to the game logic
     * @param key Key of the value
     * @param value Value to add
     */
    template <typename T>
    void addValue(const std::string& key, const T& value)
    {
        m_gameLogicValues[key] = value;
    }

    /**
     * @brief Get a value from the game logic
     * @param key Key of the value
     * @return Value
     */
    template <typename T>
    T getValue(const std::string& key) const
    {
        return std::any_cast<T>(m_gameLogicValues.at(key));
    }

    /**
     * @brief Create a new player
     * @param registry ECS registry
     * @return Entity index of the new player
     */
    rtype::ecs::Entity createNewPlayer(rtype::ecs::Registry& registry, const boost::asio::ip::udp::endpoint& endpoint)
    {
        rtype::ecs::Entity entity = rtype::utils::PrefabManager::getInstance().instantiate("player", registry);
        registry.emplaceComponent<rtype::component::NetworkPlayer>(entity, endpoint);
        return entity;
    }

    /**
     * @brief Handle creation of a bullet when a player shoots
     * @param registry ECS registry
     * @param playerIndex Player entity index
     */
    void createShootedBullet(rtype::ecs::Registry& registry, size_t playerIndex)
    {
        rtype::ecs::Entity bullet = rtype::utils::PrefabManager::getInstance().instantiate("bullet", registry);
        auto& playerTransform = registry.getComponents<rtype::component::Transform>()[playerIndex].value();
        auto& bulletTransform = registry.getComponents<rtype::component::Transform>()[bullet].value();
        bulletTransform.position = playerTransform.position;
        auto& path = registry.getComponents<rtype::component::Path>()[bullet].value();
        path.addPoint(playerTransform.position.x + 1000, playerTransform.position.y);
        auto& gameRoom = registry.getComponents<rtype::component::GameRoom>()[bullet].value();
        auto& playerGameRoom = registry.getComponents<rtype::component::GameRoom>()[playerIndex].value();
        gameRoom = playerGameRoom;
    }

    /**
     * @brief Start game handler
     * @param registry ECS registry
     * @param playerIndex Player entity index
     */
    void startGame(rtype::ecs::Registry& registry, size_t playerIndex)
    {
        auto& playerGameRoom = registry.getComponents<rtype::component::GameRoom>()[playerIndex].value();
        rtype::component::GameRoom gameRoom = playerGameRoom;
        rtype::ecs::Entity spawner = rtype::utils::PrefabManager::getInstance().instantiate("enemySpawner", registry);
        registry.getComponents<rtype::component::GameRoom>()[spawner].value() = gameRoom;
        registry.getComponents<rtype::component::Spawner>()[spawner].value().addEntityToSpawnList("enemy", getValue<float>("enemySpawnCooldown"));
    }

    /**
     * @brief Create all the game prefabs
     */
    void createPrefabs()
    {
        rtype::utils::PrefabManager& manager = rtype::utils::PrefabManager::getInstance();
        rtype::ecs::Prefab& player = manager.createPrefab("player");
        player.addComponent<rtype::component::Transform>();
        player.addComponent<rtype::component::Velocity>();
        player.addComponent<rtype::component::GameRoom>();
        player.addComponent<rtype::component::Health>(getValue<int>("playerHealth"));
        player.addComponent<rtype::component::Collider>(getValue<float>("playerHitboxWidth"), getValue<float>("playerHitboxHeight"));
        player.addComponent<rtype::component::Speed>(getValue<int>("playerSpeed"));
        player.addComponent<rtype::tag::Ally>();
        player.addComponent<rtype::component::NetworkPlayerControl>();
        player.addComponent<rtype::component::Shooter>("bullet", getValue<float>("playerShootCooldown"));

        rtype::ecs::Prefab& enemy = manager.createPrefab("enemy");
        enemy.addComponent<rtype::component::Transform>();
        enemy.addComponent<rtype::component::Velocity>();
        enemy.addComponent<rtype::component::Health>(getValue<int>("enemyHealth"));
        enemy.addComponent<rtype::component::Collider>(getValue<float>("enemyHitboxWidth"), getValue<float>("enemyHitboxHeight"));
        enemy.addComponent<rtype::component::GameRoom>();
        enemy.addComponent<rtype::component::Speed>(getValue<int>("enemySpeed"));
        enemy.addComponent<rtype::tag::Enemy>();
        enemy.addComponent<rtype::component::Shooter>("willCrash", getValue<float>("enemyShootCooldown"));
        std::vector<rtype::component::Path::Point> enemyPath;
        enemyPath.push_back(rtype::component::Path::Point(rtype::utils::Vector<float>(-50, 300), rtype::component::Path::Referential::World));
        enemy.addComponent<rtype::component::Path>(getValue<float>("enemySpawnerMovementSpeed"), enemyPath);

        rtype::ecs::Prefab& bullet = manager.createPrefab("bullet");
        bullet.addComponent<rtype::component::Transform>();
        bullet.addComponent<rtype::component::Velocity>();
        bullet.addComponent<rtype::component::Collider>(getValue<float>("bulletHitboxWidth"), getValue<float>("bulletHitboxHeight"));
        bullet.addComponent<rtype::component::Damage>(getValue<int>("bulletDamage"));
        bullet.addComponent<rtype::component::GameRoom>();
        bullet.addComponent<rtype::component::BulletInformation>();
        bullet.addComponent<rtype::component::Path>(getValue<float>("bulletSpeed"));
        bullet.addComponent<rtype::tag::Ally>();

        rtype::ecs::Prefab& enemySpawner = manager.createPrefab("enemySpawner");
        enemySpawner.addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(800, 0));
        enemySpawner.addComponent<rtype::component::Spawner>(true);
        enemySpawner.addComponent<rtype::component::Velocity>();
        enemySpawner.addComponent<rtype::component::GameRoom>();
        std::vector<rtype::component::Path::Point> enemySpawnerPath;
        // TODO: use infinite entity path when it gets implemented
        for (std::size_t c = 0; c < 12; c++) {
            enemySpawnerPath.push_back(rtype::component::Path::Point(rtype::utils::Vector<float>(800, 150), rtype::component::Path::Referential::World));
            enemySpawnerPath.push_back(rtype::component::Path::Point(rtype::utils::Vector<float>(800, 450), rtype::component::Path::Referential::World));
        }
        enemySpawner.addComponent<rtype::component::Path>(getValue<float>("enemySpawnerMovementSpeed"), enemySpawnerPath);
    }

private:
    std::unordered_map<std::string, std::any> m_gameLogicValues;
};
}