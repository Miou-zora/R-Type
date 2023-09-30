/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Controllable
*/

#pragma once

#include <functional>

namespace component
{
    struct Controllable
    {
        Controllable(
            std::function<bool(void)> is_key_up_pressed_,
            std::function<bool(void)> is_key_down_pressed_,
            std::function<bool(void)> is_key_left_pressed_,
            std::function<bool(void)> is_key_right_pressed_
        ) : is_key_up_pressed(is_key_up_pressed_), is_key_down_pressed(is_key_down_pressed_), is_key_left_pressed(is_key_left_pressed_), is_key_right_pressed(is_key_right_pressed_) {};
        ~Controllable() = default;

        Controllable(const Controllable &other) = default;
        Controllable &operator=(const Controllable &other) = default;

        std::function<bool(void)> is_key_up_pressed;
        std::function<bool(void)> is_key_down_pressed;
        std::function<bool(void)> is_key_left_pressed;
        std::function<bool(void)> is_key_right_pressed;
    };
};
