#pragma once

#include "BulletInformation.hpp"
#include "ECS.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "components/Path.hpp"

namespace rtype::system {
/**
 * @brief BulletDestroyer system used to destroy bullets when they reach the end of their path
 */
class BulletDestroyer {
public:
    BulletDestroyer() = default;
    ~BulletDestroyer() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::BulletInformation>& bullets,
        ecs::SparseArray<rtype::component::Path>& paths) const
    {
        for (auto&& [index, bullet, path] : ecs::containers::IndexedZipper(bullets, paths)) {
            if (!registry.hasComponent<rtype::component::GameRoom>(registry.entityFromIndex(index)))
                continue;
            if (path.value().listOfPoints.empty()) {
                auto& bulletGameRoom = registry.getComponents<rtype::component::GameRoom>()[index].value();
                registry.killEntity(registry.entityFromIndex(index));
                sendBulletDespawn(registry, bulletGameRoom.id, index);
            }
        }
    }

private:
    /**
     * @brief Sends the bullet despawn message to all players in the room
     * @param registry ECS registry
     * @param roomId Room id
     * @param bulletId Bullet id
     */
    void sendBulletDespawn(ecs::Registry& registry, const u_int16_t& roomId, size_t bulletId) const
    {
        auto& gameRooms = registry.getComponents<rtype::component::GameRoom>();
        auto& networkPlayers = registry.getComponents<rtype::component::NetworkPlayer>();
        auto msg = rtype::network::message::createEvent<rtype::network::message::server::BulletDespawn>(bulletId);
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