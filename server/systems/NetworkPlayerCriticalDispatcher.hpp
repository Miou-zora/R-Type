#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
/**
 * @brief NetworkPlayerCriticalDispatcher system used to dispatch critical messages to the network
 */
class NetworkPlayerCriticalDispatcher {
public:
    NetworkPlayerCriticalDispatcher() = default;
    ~NetworkPlayerCriticalDispatcher() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            auto& outbox = networkPlayer.outbox;
            for (auto&& [id, msg] : (*networkPlayer.criticalMessages)) {
                if (networkPlayer.criticalMessagesTime->find(id) == networkPlayer.criticalMessagesTime->end()) {
                    outbox->push(msg);
                    (*networkPlayer.criticalMessagesTime)[id] = std::chrono::high_resolution_clock::now();
                } else if (std::chrono::high_resolution_clock::now() - (*networkPlayer.criticalMessagesTime)[id] > std::chrono::milliseconds(500)) {
                    outbox->push(msg);
                    (*networkPlayer.criticalMessagesTime)[id] = std::chrono::high_resolution_clock::now();
                }
            }
        }
    }
};
}
