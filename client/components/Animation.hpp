/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Animation
*/

#pragma once

#include "Vector.hpp"
#include <string>
#include <vector>

namespace rtype::component {
struct Animation {
    Animation() = default;
    ~Animation() = default;
    Animation(const Animation& other) = default;
    Animation& operator=(const Animation& other) = default;

    std::vector<rtype::utils::Vector<int>> framesPosition;
    std::vector<float> frameTimes;
    std::size_t currentFrame;
    float time;
    bool loop;
    bool finished;
    bool playing;
};
}
