/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Controllable
*/

#pragma once

#include "OptionManager.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::component {
/**
 * @brief Controllable component used to store informations about the controls of an entity
 */
struct Controllable {
    Controllable() = default;
    ~Controllable() = default;

    Controllable(const Controllable& other) = default;
    Controllable& operator=(const Controllable& other) = default;

    bool isKeyUpPressed() const
    {
        return raylib::IsKeyDown(rtype::utils::OptionManager::getInstance().getKeyUp());
    }
    bool isKeyDownPressed() const
    {
        return raylib::IsKeyDown(rtype::utils::OptionManager::getInstance().getKeyDown());
    }
    bool isKeyLeftPressed() const
    {
        return raylib::IsKeyDown(rtype::utils::OptionManager::getInstance().getKeyLeft());
    }
    bool isKeyRightPressed() const
    {
        return raylib::IsKeyDown(rtype::utils::OptionManager::getInstance().getKeyRight());
    }
};
};
