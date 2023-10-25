#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

#include "Ally.hpp"
#include "BulletDestroyer.hpp"
#include "BulletInformation.hpp"
#include "Collision.hpp"
#include "Control.hpp"
#include "DamageInflictor.hpp"
#include "ECS.hpp"
#include "Enemy.hpp"
#include "EnemyDespawner.hpp"
#include "EnemyInformation.hpp"
#include "EnemyShootControl.hpp"
#include "GameLevel.hpp"
#include "GameLogicManager.hpp"
#include "GameRoom.hpp"
#include "GameRoomCollision.hpp"
#include "IntervalTimer.hpp"
#include "NetworkMessageQueue.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerControl.hpp"
#include "NetworkPlayerCriticalDispatcher.hpp"
#include "NetworkPlayerDisconnection.hpp"
#include "NetworkPlayerHandlerSystem.hpp"
#include "NetworkServer.hpp"
#include "NetworkServerInboxDispatcher.hpp"
#include "NetworkServerOutboxDispatcher.hpp"
#include "NetworkServerTickUpdater.hpp"
#include "PrefabManager.hpp"
#include "RoomCleanup.hpp"
#include "ServerDeath.hpp"
#include "ServerID.hpp"
#include "ServerSpawner.hpp"
#include "ShootControl.hpp"
#include "Shooter.hpp"
#include "Speed.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "VelocityApplicator.hpp"
#include "ClearEvents.hpp"
#include "NetworkEventDamageInfliction.hpp"

#include "components/Path.hpp"
#include "components/Spawner.hpp"
#include "systems/Path.hpp"

void registerComponents(rtype::ecs::Registry& reg)
{
    reg.registerComponent<rtype::component::NetworkPlayer>();
    reg.registerComponent<rtype::component::NetworkPlayerControl>();
    reg.registerComponent<rtype::component::GameRoom>();
    reg.registerComponent<rtype::component::GameLevel>();
    reg.registerComponent<rtype::component::Transform>();
    reg.registerComponent<rtype::component::Velocity>();
    reg.registerComponent<rtype::component::Speed>();
    reg.registerComponent<rtype::component::Health>();
    reg.registerComponent<rtype::component::Damage>();
    reg.registerComponent<rtype::component::Collider>();
    reg.registerComponent<rtype::tag::Ally>();
    reg.registerComponent<rtype::tag::Enemy>();
    reg.registerComponent<rtype::component::Spawner>();
    reg.registerComponent<rtype::component::Shooter>();
    reg.registerComponent<rtype::component::Path>();
    reg.registerComponent<rtype::component::BulletInformation>();
    reg.registerComponent<rtype::component::EnemyInformation>();
    reg.registerComponent<rtype::component::ServerID>();
}

void addSystems(rtype::ecs::Registry& reg)
{
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkServerInboxDispatcher());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkServerOutboxDispatcher());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkPlayerHandlerSystem());
    reg.addSystem<rtype::component::NetworkPlayerControl, rtype::component::Velocity, rtype::component::Speed>(rtype::system::Control());
    reg.addSystem<rtype::component::Transform, rtype::component::Velocity>(rtype::system::VelocityApplicator());
    reg.addSystem<rtype::component::NetworkPlayerControl, rtype::component::Shooter>(rtype::system::ShootControl());
    reg.addSystem<rtype::component::Shooter>(rtype::system::EnemyShootControl());
    reg.addSystem<rtype::component::BulletInformation, rtype::component::Path>(rtype::system::BulletDestroyer());
    reg.addSystem<rtype::component::EnemyInformation, rtype::component::Path>(rtype::system::EnemyDespawner());
    reg.addSystem<rtype::component::Collider, rtype::component::Transform>(rtype::system::GameRoomCollision());
    reg.addSystem<rtype::component::Damage, rtype::component::Collider>(rtype::system::DamageInflictor());
    reg.addSystem(rtype::system::NetworkEventDamageInfliction());
    reg.addSystem<rtype::component::Transform, rtype::component::Velocity, rtype::component::Path>(rtype::system::Path());
    reg.addSystem<rtype::component::Spawner>(rtype::system::ServerSpawner());
    reg.addSystem<rtype::component::GameRoom>(rtype::system::RoomCleanup());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkPlayerCriticalDispatcher());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkServerTickUpdater());
    reg.addSystem<rtype::component::Health>(rtype::system::ServerDeath());
    reg.addSystem<rtype::component::NetworkPlayer, rtype::component::GameRoom>(rtype::system::NetworkPlayerDisconnection(std::chrono::milliseconds(10000)));
    reg.addSystem(rtype::system::ClearEvents());
}

int main(int ac, char* av[])
{
    rtype::ecs::Registry reg;
    int port = 12345;
    int tickRate = 64;

    if (ac > 1)
        port = std::stoi(av[1]);
    try {
        rtype::network::NetworkServer::initInstance(port);
    } catch (const std::exception& e) {
        std::cerr << av[0] << ": cannot init network server: " << e.what() << std::endl;
        return 84;
    }

    registerComponents(reg);
    addSystems(reg);
    rtype::utils::GameLogicManager::getInstance().createPrefabs();

    rtype::network::IntervalTimer timer(
        rtype::network::ContextManager::getInstance().getContext("ecsUpdater"), [&reg]() {
            reg.runSystems();
        },
        std::chrono::microseconds(1000000 / tickRate));
    timer.start();
    rtype::network::ContextManager::getInstance().runAllContexts();
    rtype::network::ContextManager::getInstance().joinAllContexts();
    return 0;
}
