/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Selectable
*/

#pragma once

#include <functional>

namespace rtype::component {
/**
 * @brief Selectable component used to store the selected state of an entity
 */
struct Selectable {
    Selectable(bool selected_ = false)
        : selected(selected_) {};
    ~Selectable(void) = default;

    Selectable(const Selectable& other) = default;
    Selectable& operator=(const Selectable& other) = default;

    bool selected;
};
}
