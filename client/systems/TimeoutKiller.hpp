/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** TimeoutKiller
*/

#pragma once

#include "Client.hpp"
#include "ECS.hpp"
#include "LastUpdate.hpp"

namespace rtype::system {
/**
 * @brief A system that kills the entity if it has not been updated for a while
 */
class TimeoutKiller {
public:
    TimeoutKiller() = default;
    ~TimeoutKiller() = default;

    void operator()(ecs::Registry& registry, ecs::SparseArray<rtype::component::LastUpdate>& lastUpdate) const
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        auto lastTick = std::chrono::time_point_cast<std::chrono::system_clock::duration>(network::Client::getInstance().getLastTick());
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count() > 1200)
            return;
        std::vector<std::size_t> toKill;
        for (auto&& [index, lastUpdate] : ecs::containers::IndexedZipper(lastUpdate)) {
            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - lastUpdate.value().lastUpdate).count() > 2) {
                toKill.push_back(index);
            }
        }
        for (auto &index : toKill) {
            registry.killEntity(registry.entityFromIndex(index));
        }
    }
};
}
