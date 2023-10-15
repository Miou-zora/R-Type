#pragma once

#include "ECS.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"

namespace rtype::system {
/**
 * @brief RoomCleanup system used to clean up empty game rooms
 */
class RoomCleanup {
public:
    RoomCleanup() = default;
    ~RoomCleanup() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::GameRoom>& gameRooms) const
    {
        for (auto&& [index, gameRoom] : ecs::containers::IndexedZipper(gameRooms)) {
            if (isGameRoomEmpty(registry, gameRoom.value())) {
                deleteEntitiesWithSameGameRoomId(registry, gameRoom.value());
            }
        }
    }

private:
    /**
     * @brief Check if the current game room has any players in it
     * @param registry ECS registry
     * @param gameRoom Game room
     * @return true if the game room is empty, false otherwise
     */
    bool isGameRoomEmpty(ecs::Registry& registry, rtype::component::GameRoom& gameRoom) const
    {
        auto& networkPlayers = registry.getComponents<rtype::component::NetworkPlayer>();
        auto& gameRooms = registry.getComponents<rtype::component::GameRoom>();
        for (auto&& [index, networkPlayerOpt, gameRoomOpt] : ecs::containers::IndexedZipper(networkPlayers, gameRooms)) {
            auto& playerGameRoom = gameRoomOpt.value();
            if (playerGameRoom.id == gameRoom.id)
                return false;
        }
        return true;
    }

    /**
     * @brief Delete all entities that have the same game room id as the given game room
     * @param registry ECS registry
     * @param gameRoom Game room
     */
    void deleteEntitiesWithSameGameRoomId(ecs::Registry& registry, rtype::component::GameRoom& gameRoom) const
    {
        std::vector<rtype::ecs::Entity> entitiesToDelete;
        auto& gameRooms = registry.getComponents<rtype::component::GameRoom>();

        for (auto&& [index, gameRoomOpt] : ecs::containers::IndexedZipper(gameRooms)) {
            if (!gameRoomOpt.has_value())
                continue;
            auto& currentGameRoom = gameRoomOpt.value();
            if (currentGameRoom.id == gameRoom.id) {
                entitiesToDelete.push_back(rtype::ecs::Entity(index));
            }
        }
        for (auto&& entity : entitiesToDelete) {
            registry.killEntity(entity);
        }
    }
};
}
