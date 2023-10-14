#pragma once

#include <memory>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkServer.hpp"

namespace rtype::system {
class NetworkServerOutboxDispatcher {
public:
    NetworkServerOutboxDispatcher() = default;
    ~NetworkServerOutboxDispatcher() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::NetworkPlayer>& networkPlayers) const
    {
        auto& networkServer = rtype::network::NetworkServer::getInstance();
        auto& recvMsgBuffer = networkServer.getRecvMsgBuffer();
        for (auto&& [i, networkPlayerOpt] : ecs::containers::IndexedZipper(networkPlayers)) {
            rtype::component::NetworkPlayer& networkPlayer = networkPlayerOpt.value();
            auto& outbox = networkPlayer.outbox;
            while (!outbox->empty()) {
                const auto& msg = outbox->top();
                std::size_t size = rtype::network::message::server::getMessageSize(msg);
                const auto& unpacked = reinterpret_cast<const rtype::network::message::NetworkMessageHeader*>(msg.data());
                const auto bufferSized = boost::asio::buffer(msg, size);
                for (size_t c = 0; c < getNumberOfIterations(*unpacked); c++) {
                    networkServer.getSocket().async_send_to(bufferSized, networkPlayer.endpoint,
                        boost::bind(&rtype::network::NetworkServer::handleSend, &networkServer,
                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                }
                outbox->pop();
            }
        }
    }

private:
    /**
     * @brief Get the number of iterations needed to ensure message safety
     * @param header Message header
     * @return Number of iterations
     */
    std::size_t getNumberOfIterations(const rtype::network::message::NetworkMessageHeader& header) const
    {
        std::size_t iterations = 1;

        switch (header.type) {
        case rtype::network::message::server::ConnectAck::type:
        case rtype::network::message::server::RoomInformation::type:
        case rtype::network::message::server::LevelInformation::type:
        case rtype::network::message::server::GameStarted::type:
        case rtype::network::message::server::GameEnded::type:
        case rtype::network::message::server::BulletShoot::type:
        case rtype::network::message::server::BulletDespawn::type:
        case rtype::network::message::server::PlayerDeath::type:
        case rtype::network::message::server::PlayerWeaponSwitch::type:
        case rtype::network::message::server::EnemySpawn::type:
        case rtype::network::message::server::EnemyDeath::type:
            iterations = 12;
            break;
        }
        return iterations;
    }
};
}
