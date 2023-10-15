#pragma once

#include "ECS.hpp"
#include "EnemyInformation.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "components/Path.hpp"

namespace rtype::system {
/**
 * @brief EnemyDespawner system used to destroy enemies when they reach the end of their path
 */
class EnemyDespawner {
public:
    EnemyDespawner() = default;
    ~EnemyDespawner() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::EnemyInformation>& enemyInfos,
        ecs::SparseArray<rtype::component::Path>& paths) const
    {
        for (auto&& [index, enemyInfo, path] : ecs::containers::IndexedZipper(enemyInfos, paths)) {
            if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(index)))
                continue;
            if (path.value().listOfPoints.empty()) {
                auto& enemyGameRoom = registry.getComponents<rtype::component::GameRoom>()[index].value();
                registry.killEntity(registry.entityFromIndex(index));
                sendEnemyDespawn(registry, enemyGameRoom.id, index);
            }
        }
    }

private:
    /**
     * @brief Sends the enemy despawn message to all players in the room
     * @param registry ECS registry
     * @param roomId Room id
     * @param enemyId Enemy id
     */
    void sendEnemyDespawn(ecs::Registry& registry, const u_int16_t& roomId, size_t enemyId) const
    {
        auto& gameRooms = registry.getComponents<rtype::component::GameRoom>();
        auto& networkPlayers = registry.getComponents<rtype::component::NetworkPlayer>();
        auto msg = rtype::network::message::createEvent<rtype::network::message::server::EnemyDeath>(enemyId);
        auto packedMsg = rtype::network::message::pack(msg);

        for (auto&& [index, gameRoom, networkPlayer] : ecs::containers::IndexedZipper(gameRooms, networkPlayers)) {
            if (!gameRoom.has_value() || !networkPlayer.has_value())
                continue;
            if (gameRoom.value().id == roomId) {
                networkPlayer.value().outbox->push(packedMsg);
            }
        }
    };
};
}