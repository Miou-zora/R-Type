/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** DebugColliderDisplay
*/

#pragma once

#include <functional>

namespace rtype::component {
/**
 * @brief ColliderDisplay component used to store the display state of an entity
 */
struct DebugColliderDisplay {
    DebugColliderDisplay(bool display_ = false)
        : display(display_) {};
    ~DebugColliderDisplay(void) = default;

    DebugColliderDisplay(const DebugColliderDisplay& other) = default;
    DebugColliderDisplay& operator=(const DebugColliderDisplay& other) = default;

    bool display;
};
}
