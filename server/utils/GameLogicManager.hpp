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
#include "EntityInformation.hpp"
#include "GameRoom.hpp"
#include "Health.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerControl.hpp"
#include "Path.hpp"
#include "Points.hpp"
#include "PrefabManager.hpp"
#include "ServerID.hpp"
#include "Shooter.hpp"
#include "Spawner.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "PrefabsMapping.hpp"
#include "Boss.hpp"
#include "Killable.hpp"
#include "Lootable.hpp"
#include "Loot.hpp"
#include "Taker.hpp"
#include <set>

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
        addValue<int>("playerSpeed", 600);
        addValue<rtype::utils::Vector<float>>("defaultPlayerPosition", rtype::utils::Vector<float>(100, 300));
        addValue<rtype::utils::Vector<float>>("playerPositionOffset", rtype::utils::Vector<float>(0, 100));
        addValue<float>("playerShootCooldown", 0.35);
        addValue<int>("playerHealth", 10);
        addValue<int>("playerHitboxDamage", 1);
        addValue<float>("playerHitboxWidth", 68);
        addValue<float>("playerHitboxHeight", 68);
        addValue<float>("enemySpawnerMovementSpeed", 200);
        addValue<float>("enemySpawnCooldown", 3.0f);
        addValue<std::size_t>("enemySpawnerCount", 1);
        addValue<int>("enemySpeed", 1);
        addValue<int>("enemyCollideDamage", 1);
        addValue<int>("enemyHealth", 1);
        addValue<float>("enemyHitboxWidth", 120);
        addValue<float>("enemyHitboxHeight", 144);
        addValue<rtype::utils::Vector<float>>("defaultEnemyPosition", rtype::utils::Vector<float>(500, 500));
        addValue<float>("enemyShootCooldown", 1.8f);
        addValue<float>("bulletSpeed", 2000);
        addValue<float>("bulletHitboxWidth", 80);
        addValue<float>("bulletHitboxHeight", 20);
        addValue<int>("bulletDamage", 1);
        addValue<float>("bulletDistance", 1700);
        addValue<float>("enemyBulletSpeed", 700);
        addValue<float>("enemyBulletHitboxWidth", 20);
        addValue<float>("enemyBulletHitboxHeight", 20);
        addValue<int>("enemyBulletDamage", 1);
        addValue<float>("enemyBulletDistance", 2500);
        addValue<int>("bossHealth", 12);
        addValue<int>("bossSpeed", 1);
        addValue<int>("bossCollideDamage", 1);
        addValue<float>("bossHitboxWidth", 120);
        addValue<float>("bossHitboxHeight", 144);
        addValue<float>("bossShootCooldown", 1);
        addValue<float>("bossPathSpeed", 200);
        addValue<int>("pointsOnEnemyKill", 100);
        addValue<int>("scantHealth", 2);
        addValue<float>("patapataMovementSpeed", 150);
        addValue<float>("scantMovementSpeed", 320);
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
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        registry.emplaceComponent<rtype::component::ServerID>(entity, uuid.data);
        return entity;
    }

    void manageTarget(rtype::ecs::Registry& registry, rtype::ecs::Entity bullet)
    {
        std::vector<std::size_t> targets;
        const rtype::component::GameRoom &gameRoom = registry.getComponents<rtype::component::GameRoom>()[bullet].value();
        // add player of same room
        for (auto&& [index, networkPlayerOpt, gameRoomOpt, transformOpt, killableOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>(), registry.getComponents<rtype::component::Transform>(), registry.getComponents<rtype::component::Killable>())) {
            if (killableOpt.value().killed)
                continue;
            auto& networkPlayer = networkPlayerOpt.value();
            auto& playerGameRoom = gameRoomOpt.value();
            if (playerGameRoom.id == gameRoom.id && transformOpt.value().position.y > 0.0f) {
                targets.push_back(index);
            }
        }
        if (targets.size() == 0) {
            registry.getComponents<rtype::component::Path>()[bullet].value().addPoint(-2000, 0.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity);
            return;
        }
        std::size_t target = rand() % targets.size();
        const std::optional<rtype::component::Transform> &targetTransform = registry.getComponents<rtype::component::Transform>()[targets.at(target)];
        const std::optional<rtype::component::Transform> &bulletTransform = registry.getComponents<rtype::component::Transform>()[bullet];
        if (!targets.size() || !targetTransform.has_value() || !bulletTransform.has_value())
            registry.getComponents<rtype::component::Path>()[bullet].value().addPoint(-2000, 0.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity);
        else
            registry.getComponents<rtype::component::Path>()[bullet].value().addPoint((targetTransform.value().position.x - bulletTransform.value().position.x) * 10.f, (targetTransform.value().position.y - bulletTransform.value().position.y) * 10.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity).setDestroyAtEnd(true);
    }

    std::size_t createEntityFrom(rtype::ecs::Registry& registry, size_t parent, const rtype::utils::PrefabsMapping::prefabs &childPrefab)
    {
        rtype::ecs::Entity bullet = instantiateFrom(childPrefab, registry.entityFromIndex(parent), registry);
        if (registry.hasComponent<rtype::component::EntityInformation>(bullet) && registry.getComponents<rtype::component::EntityInformation>()[bullet].value().type == static_cast<int>(rtype::utils::PrefabsMapping::prefabs::TARGET_BULLET))
            manageTarget(registry, bullet);
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        registry.emplaceComponent<rtype::component::ServerID>(bullet, uuid.data);
        return bullet;
    }

    std::size_t createEntityFrom(rtype::ecs::Registry& registry, size_t parent, const std::string &childsPrefabName)
    {
        return createEntityFrom(registry, parent, rtype::utils::PrefabsMapping::namesMapping.at(childsPrefabName));
    }

    static rtype::ecs::Entity instantiateFrom(const rtype::utils::PrefabsMapping::prefabs &childPrefab, const rtype::ecs::Entity &parent, rtype::ecs::Registry &registry)
    {
        rtype::ecs::Entity child = rtype::utils::PrefabManager::getInstance().instantiate(rtype::utils::PrefabsMapping::prefabsMapping.at(childPrefab), registry);

        if (registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(parent)) &&
            registry.hasComponent<rtype::component::Transform>(child)) {
            auto& childTransform = registry.getComponents<rtype::component::Transform>()[child].value();
            auto& parentTransform = registry.getComponents<rtype::component::Transform>()[parent].value();
            childTransform.position += parentTransform.position;
        }
        if (registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(parent)) &&
            registry.hasComponent<rtype::component::GameRoom>(child)) {
            auto& childgameRoom = registry.getComponents<rtype::component::GameRoom>()[child].value();
            auto& parentGameRoom = registry.getComponents<rtype::component::GameRoom>()[parent].value();
            childgameRoom = parentGameRoom;
        }
        return child;
    }

    /**
     * @brief Start game handler
     * @param registry ECS registry
     * @param playerIndex Player entity index
     */
    void startGame(rtype::ecs::Registry& registry, size_t playerIndex)
    {
        auto& playerGameRoom = registry.getComponents<rtype::component::GameRoom>()[playerIndex].value();
        u_int16_t playerGameRoomId = playerGameRoom.id;
        rtype::utils::Vector<float> pos = getValue<rtype::utils::Vector<float>>("defaultPlayerPosition");
        for (auto&& [index, networkPlayerOpt, gameRoomOpt, pointsOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>(), registry.getComponents<rtype::component::Points>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            auto& gameRoom = gameRoomOpt.value();
            auto& points = pointsOpt.value();
            if (gameRoom.id == playerGameRoom.id) {
                registry.emplaceComponent<rtype::component::Transform>(registry.entityFromIndex(index), pos);
                if (registry.hasComponent<rtype::component::Shooter>(registry.entityFromIndex(index))) {
                    registry.getComponents<rtype::component::Shooter>()[registry.entityFromIndex(index)].value().projectileName = rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET);
                }
                pos += getValue<rtype::utils::Vector<float>>("playerPositionOffset");
                points.value = 0;
                if (registry.hasComponent<rtype::component::Killable>(registry.entityFromIndex(index))) {
                    registry.getComponents<rtype::component::Killable>()[registry.entityFromIndex(index)].value().to_kill = false;
                    registry.getComponents<rtype::component::Killable>()[registry.entityFromIndex(index)].value().killed = false;
                }
            }
        }
        rtype::component::GameRoom gameRoom = playerGameRoom;
        for (std::size_t i = 0; i < getValue<std::size_t>("enemySpawnerCount"); i++) {
            rtype::ecs::Entity spawner = rtype::utils::PrefabManager::getInstance().instantiate("enemySpawner", registry);
            registry.getComponents<rtype::component::GameRoom>()[spawner].value() = gameRoom;
        }
        for (auto&& [gameRoomOpt, networkPlayerOpt] : ecs::containers::Zipper(registry.getComponents<rtype::component::GameRoom>(), registry.getComponents<rtype::component::NetworkPlayer>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            if (gameRoomOpt.value().id != playerGameRoomId) {
                continue;
            }
            auto startGameAck = rtype::network::message::createEvent<rtype::network::message::server::GameStarted>();
            (*networkPlayer.criticalMessages)[startGameAck.header.id] = rtype::network::message::pack(startGameAck);
            for (auto&& [pIndex, gameRoomOpt, networkPlayerOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::GameRoom>(), registry.getComponents<rtype::component::NetworkPlayer>())) {
                if (gameRoomOpt.value().id != playerGameRoomId) {
                    continue;
                }
                auto& playerTransform = registry.getComponents<rtype::component::Transform>()[pIndex].value();
                auto& playerServerID = registry.getComponents<rtype::component::ServerID>()[pIndex].value();
                auto playerSpawned = rtype::network::message::createEvent<rtype::network::message::server::PlayerSpawn>(playerServerID.uuid, playerTransform.position.x, playerTransform.position.y);
                (*networkPlayer.criticalMessages)[playerSpawned.header.id] = rtype::network::message::pack(playerSpawned);
            }
        }
    }

    /**
     * @brief Count the numbers of players in a game room
     * @param registry ECS registry
     * @param gameRoom Game room
     * @return Number of players in the game room
     */
    static std::size_t countPlayersInGameRoom(rtype::ecs::Registry& registry, const rtype::component::GameRoom& gameRoom)
    {
        std::size_t count = 0;

        for (auto&& [index, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            auto& playerGameRoom = gameRoomOpt.value();
            if (playerGameRoom.id == gameRoom.id) {
                count++;
            }
        }
        return count;
    }

    /**
     * @brief Check if the game already started
     * @param registry ECS registry
     * @param gameRoom Game room
     * @return true if the game already started, false otherwise
     */
    static bool isGameStarted(rtype::ecs::Registry& registry, const rtype::component::GameRoom& gameRoom)
    {
        for (auto&& [index, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            auto& playerGameRoom = gameRoomOpt.value();
            if (playerGameRoom.id == gameRoom.id) {
                if (registry.hasComponent<rtype::component::Transform>(registry.entityFromIndex(index))) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Check if the game exists
     * @param registry ECS registry
     * @param gameRoom Game room
     * @return true if the game exists, false otherwise
     */
    static bool gameExists(rtype::ecs::Registry& registry, const rtype::component::GameRoom& gameRoom)
    {
        for (auto&& [index, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
            auto& networkPlayer = networkPlayerOpt.value();
            auto& playerGameRoom = gameRoomOpt.value();
            if (playerGameRoom.id == gameRoom.id) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Create all the game prefabs
     */
    void createPrefabs()
    {
        rtype::utils::PrefabManager& manager = rtype::utils::PrefabManager::getInstance();
        rtype::ecs::Prefab& player = manager.createPrefab("player");
        player.addComponent<rtype::component::Velocity>();
        player.addComponent<rtype::component::Health>(getValue<int>("playerHealth"));
        player.addComponent<rtype::component::Damage>(getValue<int>("playerHitboxDamage"));
        player.addComponent<rtype::component::Collider>(getValue<float>("playerHitboxWidth"), getValue<float>("playerHitboxHeight"));
        player.addComponent<rtype::component::Speed>(getValue<int>("playerSpeed"));
        player.addComponent<rtype::tag::Ally>();
        player.addComponent<rtype::component::NetworkPlayerControl>();
        player.addComponent<rtype::component::Shooter>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET), getValue<float>("playerShootCooldown"));
        player.addComponent<rtype::component::ServerID>();
        player.addComponent<rtype::component::Points>();
        player.addComponent<rtype::component::Killable>();
        player.addComponent<rtype::component::Taker>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100.f, 25.f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Collider>(getValue<float>("enemyBulletHitboxWidth"), getValue<float>("enemyBulletHitboxHeight"))
            .addComponent<rtype::component::Damage>(getValue<int>("enemyBulletDamage"))
            .addComponent<rtype::component::Health>(getValue<int>("bulletDamage"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::ALLY_BULLET))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("enemyBulletSpeed"))
                .addPoint(rtype::utils::Vector<float>(getValue<float>("enemyBulletDistance"), 0.f), rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .setDestroyAtEnd(true))
            .addComponent<rtype::tag::Ally>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        std::vector<rtype::utils::Vector<float>> ultraAllyBulletPointsPath;
        for (float i = 0; i < 1000; i++) {
            ultraAllyBulletPointsPath.push_back(rtype::utils::Vector<float>(1.f, cos(i * 0.1)) * 10.f);
        }
        rtype::component::Path ultraAllyBulletPath(getValue<float>("enemyBulletSpeed"));
        for (auto& point : ultraAllyBulletPointsPath) {
            ultraAllyBulletPath.addPoint(point, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity);
        }
        ultraAllyBulletPath.setDestroyAtEnd(true);
        ultraAllyBulletPath.setType(rtype::component::Path::Type::OneShot);
        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ULTRA_ALLY_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100.f, 25.f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Collider>(getValue<float>("enemyBulletHitboxWidth"), getValue<float>("enemyBulletHitboxHeight"))
            .addComponent<rtype::component::Damage>(getValue<int>("enemyBulletDamage"))
            .addComponent<rtype::component::Health>(getValue<int>("bulletDamage"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::ULTRA_ALLY_BULLET))
            .addComponent<rtype::component::Path>(ultraAllyBulletPath)
            .addComponent<rtype::tag::Ally>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 50.f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Collider>(14 * 4, 14 * 4)
            .addComponent<rtype::component::Damage>(getValue<int>("enemyBulletDamage"))
            .addComponent<rtype::component::Health>(getValue<int>("bulletDamage"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("enemyBulletSpeed"))
                .addPoint(rtype::utils::Vector<float>(-getValue<float>("enemyBulletDistance"), 0.f), rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .setDestroyAtEnd(true))
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1600.0f, 1024.0f / 2.0f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Health>(getValue<int>("enemyHealth"))
            .addComponent<rtype::component::Collider>(getValue<float>("enemyHitboxWidth"), getValue<float>("enemyHitboxHeight"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::Speed>(getValue<int>("enemySpeed"))
            .addComponent<rtype::component::Damage>(getValue<int>("enemyCollideDamage"))
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Shooter>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TARGET_BULLET), getValue<float>("enemyShootCooldown"))
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::PATA_PATA))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("patapataMovementSpeed"))
                .addPoint(-2000.0f, 0.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .setDestroyAtEnd(true))
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Lootable>(rtype::component::Lootable()
                .addDroppableEntity(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::DEFAULT_WEAPON_LOOT), 20))
            .addComponent<rtype::component::ServerID>()
            .addComponent<rtype::component::Points>(100);

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::DEFAULT_WEAPON_LOOT))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 0.f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Collider>(10.f, 10.f)
            .addComponent<rtype::component::Speed>(1)
            .addComponent<rtype::component::Path>(rtype::component::Path(100)
                .addPoint(0.f, 1000.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .setDestroyAtEnd(true))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::tag::Ally>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::DEFAULT_WEAPON_LOOT))
            .addComponent<rtype::component::Loot>({rtype::component::Loot::Type::WEAPON, {rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ULTRA_ALLY_BULLET), 0.5}})
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1600.0f, 1024.0f / 2.0f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Health>(getValue<int>("scantHealth"))
            .addComponent<rtype::component::Collider>(getValue<float>("enemyHitboxWidth"), getValue<float>("enemyHitboxHeight"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::Speed>(getValue<int>("enemySpeed"))
            .addComponent<rtype::component::Damage>(getValue<int>("enemyCollideDamage"))
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Shooter>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET), getValue<float>("enemyShootCooldown") / 2.0f)
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::SCANT))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("scantMovementSpeed"))
                .addPoint(-100.0f, 100.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, 200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, 200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, 200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, 200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, 200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .addPoint(-200.0f, -200.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
                .setDestroyAtEnd(true))
            .addComponent<rtype::component::ServerID>()
            .addComponent<rtype::component::Points>(200);

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ZOYDO))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1600.0f, 1024.0f / 2.0f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Health>(getValue<int>("bossHealth"))
            .addComponent<rtype::component::Collider>(getValue<float>("bossHitboxWidth"), getValue<float>("bossHitboxHeight"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::Speed>(getValue<int>("bossSpeed"))
            .addComponent<rtype::component::Damage>(getValue<int>("bossCollideDamage"))
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Shooter>(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TRIPLE_BOSS_BULLET), getValue<float>("bossShootCooldown"))
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::ZOYDO))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("bossPathSpeed"))
                .addPoint(-300.0f, 0.f, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity))
            .addComponent<rtype::component::ServerID>()
            .addComponent<rtype::tag::Boss>()
            .addComponent<rtype::component::Points>(1000);

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.0f, -2 * 55.0f))
            .addComponent<rtype::component::Collider>(1600.0f, 4 * 55.0f)
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::TOP_WALL))
            .addComponent<rtype::component::Damage>(999)
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 1024.f -2 * 55.f))
            .addComponent<rtype::component::Collider>(1600.0f, 4 * 55.0f)
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL))
            .addComponent<rtype::component::Damage>(999)
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        rtype::ecs::Prefab& enemyBullet = manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET));
        enemyBullet.addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 50.f));
        enemyBullet.addComponent<rtype::component::Velocity>();
        enemyBullet.addComponent<rtype::component::Collider>(getValue<float>("enemyBulletHitboxWidth"), getValue<float>("enemyBulletHitboxHeight"));
        enemyBullet.addComponent<rtype::component::Damage>(getValue<int>("enemyBulletDamage"));
        enemyBullet.addComponent<rtype::component::Health>(getValue<int>("bulletDamage"));
        enemyBullet.addComponent<rtype::component::GameRoom>();
        enemyBullet.addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET));
        enemyBullet.addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("enemyBulletSpeed"))
            .addPoint(rtype::utils::Vector<float>(-getValue<float>("enemyBulletDistance"), 0.f), rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity)
            .setDestroyAtEnd(true));
        enemyBullet.addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>();
        enemyBullet.addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TARGET_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 50.f))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::Collider>(getValue<float>("enemyBulletHitboxWidth"), getValue<float>("enemyBulletHitboxHeight"))
            .addComponent<rtype::component::Damage>(getValue<int>("enemyBulletDamage"))
            .addComponent<rtype::component::Health>(getValue<int>("bulletDamage"))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::EntityInformation>(static_cast<int>(rtype::utils::PrefabsMapping::prefabs::TARGET_BULLET))
            .addComponent<rtype::component::Path>(rtype::component::Path(getValue<float>("enemyBulletSpeed"))
                .setDestroyAtEnd(true))
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TRIPLE_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 0.f))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Spawner>(rtype::component::Spawner()
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET), 0.f)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET), 0.1f)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SIMPLE_BULLET), 0.2f))
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TRIPLE_BOSS_BULLET))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.f, 0.f))
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::tag::Enemy>()
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Spawner>(rtype::component::Spawner()
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET), 0.f, rtype::component::Spawner::Context::Local)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET), 0.1f, rtype::component::Spawner::Context::Local)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOSS_BULLET), 0.1f, rtype::component::Spawner::Context::Local))
            .addComponent<rtype::component::ServerID>();

        manager.createPrefab("enemySpawner")
            .addComponent<rtype::component::Killable>()
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.0f, 0.0f))
            .addComponent<rtype::component::Spawner>(rtype::component::Spawner(false)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::TOP_WALL), 0.f)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::BOTTOM_WALL), 0.f)
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), getValue<float>("enemySpawnCooldown"), rtype::component::Spawner::Context::Local, {0.f, static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), getValue<float>("enemySpawnCooldown"), rtype::component::Spawner::Context::Local, {0.f, static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), getValue<float>("enemySpawnCooldown"), rtype::component::Spawner::Context::Local, {0.f, 200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), getValue<float>("enemySpawnCooldown"), rtype::component::Spawner::Context::Local, {0.f, 200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), getValue<float>("enemySpawnCooldown") * 2.f, rtype::component::Spawner::Context::Local, {0.f, 100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), 0.f, rtype::component::Spawner::Context::Local, {0.f, -100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.1f, rtype::component::Spawner::Context::Local, {0.f, 200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), getValue<float>("enemySpawnCooldown") * 2.f, rtype::component::Spawner::Context::Local, {0.f, 100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), 0.f, rtype::component::Spawner::Context::Local, {0.f, -100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), getValue<float>("enemySpawnCooldown") * 2.f, rtype::component::Spawner::Context::Local, {0.f, 100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::SCANT), 0.f, rtype::component::Spawner::Context::Local, {0.f, -100.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.1f, rtype::component::Spawner::Context::Local, {0.f, 200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::PATA_PATA), 0.f, rtype::component::Spawner::Context::Local, {0.f, -200.f + static_cast<float>(50 - std::rand() % (100))})
                .addEntityToSpawnList(rtype::utils::PrefabsMapping::prefabsMapping.at(rtype::utils::PrefabsMapping::prefabs::ZOYDO), getValue<float>("enemySpawnCooldown") * 2.f, rtype::component::Spawner::Context::Local))
            .addComponent<rtype::component::Velocity>()
            .addComponent<rtype::component::GameRoom>()
            .addComponent<rtype::component::ServerID>();
    }

private:
    std::unordered_map<std::string, std::any> m_gameLogicValues;
};
}
