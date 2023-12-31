#pragma once

#include "ToggleBool.hpp"

namespace rtype::component {
/**
 * @brief NetworkPlayerControl component used to store informations about the controls of an entity through the network
 */
struct NetworkPlayerControl {
    NetworkPlayerControl() = default;
    ~NetworkPlayerControl() = default;

    NetworkPlayerControl(const NetworkPlayerControl& other) = default;
    NetworkPlayerControl& operator=(const NetworkPlayerControl& other) = default;

    NetworkPlayerControl(NetworkPlayerControl&& other) = default;
    NetworkPlayerControl& operator=(NetworkPlayerControl&& other) = default;

    rtype::utils::ToggleBool up;
    rtype::utils::ToggleBool down;
    rtype::utils::ToggleBool left;
    rtype::utils::ToggleBool right;
    rtype::utils::ToggleBool shoot;
};
}
