/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** NetworkControl
*/

#pragma once

#include "Client.hpp"
#include "Controllable.hpp"
#include "ECS.hpp"
#include "Velocity.hpp"

namespace rtype::system {
/**
 * @brief A system that takes the user inputs and adds them to the outbox
 */
class NetworkControl {
public:
    NetworkControl() = default;
    ~NetworkControl() = default;

    void operator()(ecs::Registry& registry,
        ecs::SparseArray<rtype::component::Controllable> const& controllables,
        ecs::SparseArray<rtype::component::Velocity>& velocities) const
    {
        bool noKeysPressed;

        for (auto&& [controllable, velocity] : ecs::containers::Zipper(controllables, velocities)) {
            noKeysPressed = true;
            bool keys[4] = { controllable.value().is_key_up_pressed(), controllable.value().is_key_down_pressed(),
                controllable.value().is_key_left_pressed(), controllable.value().is_key_right_pressed() };
            for (int i = 0; i < 4; i++) {
                if (keys[i]) {
                    noKeysPressed = false;
                    break;
                }
            }
            if (!noKeysPressed) {
                network::message::client::PlayerMovement message = network::message::createEvent<network::message::client::PlayerMovement>(
                    velocity.value().vector.x, velocity.value().vector.y, keys);
                boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> packed = network::message::pack<network::message::client::PlayerMovement>(message);
                network::Client::getInstance().getOutbox()->push(packed);
            }
        }
    }
};
}
