#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
    class NetworkServerTickSystem {
    public:
        NetworkServerTickSystem(size_t tickRate)
            : m_tickRate(tickRate)
        {}
        ~NetworkServerTickSystem() = default;

        void operator()(ecs::Registry &registry,
            ecs::SparseArray<rtype::component::NetworkServer> &networkServers) const
        {
            (void)registry;
            for (auto &&[networkServerOpt] : ecs::containers::Zipper(networkServers)) {
                if (!networkServerOpt.has_value())
                    continue;
                rtype::component::NetworkServer &networkServer = networkServerOpt.value();
                auto lastTick = networkServer.lastTick;
                auto currentTime = getCurrentTime();
                auto tickDuration = getTickDuration() - (currentTime - lastTick);
                networkServer.ioContext->run_for(tickDuration);
                auto end_time = getCurrentTime();
                networkServer.lastTick = end_time;
            }
        }

        /**
         * @brief Get the tick duration in microseconds
         * @return std::chrono::microseconds
        */
        std::chrono::microseconds getTickDuration() const
        {
            return std::chrono::microseconds(1000000 / m_tickRate);
        }

    private:
        /**
         * @brief Get the current time as a std::chrono::high_resolution_clock::time_point
         * @return std::chrono::high_resolution_clock::time_point
        */
        std::chrono::high_resolution_clock::time_point getCurrentTime() const
        {
            return std::chrono::high_resolution_clock::now();
        }

        size_t m_tickRate;
    };
}