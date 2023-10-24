/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** NetworkInputShoot
*/

#pragma once

#include "Client.hpp"
#include "Controllable.hpp"
#include "ECS.hpp"
#include "InputShooter.hpp"
#include "PrefabManager.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"

namespace rtype::system {
/**
 * @brief A system that takes the user inputs and adds them to the outbox
 */
class NetworkInputShoot {
public:
    NetworkInputShoot() = default;
    ~NetworkInputShoot() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::InputShooter>& shooters) const
    {
        for (auto&& [index, shooter] : ecs::containers::IndexedZipper(shooters)) {
            shooter.value().update(registry.getDeltaTime());
            if (shooter.value().canShoot()) {
                shooter.value().timer = 0;
                network::message::client::PlayerShoot message = network::message::createEvent<network::message::client::PlayerShoot>();
                boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> packed = network::message::pack<network::message::client::PlayerShoot>(message);
                network::Client::getInstance().getOutbox()->push(packed);
            }
        }
    }
};
}
