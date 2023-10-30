/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Sound
*/

#pragma once

#include <iostream>

namespace rtype::component {
enum class AudioType {
    MUSIC,
    SOUND
};
/**
 * @brief A component use to play sound
 */
struct Sound {
    Sound(const std::string& soundName_ = "", bool play_ = false, AudioType type_ = AudioType::SOUND)
        : soundName(soundName_), play(play_), type(type_)
    {
    }
    ~Sound() = default;

    Sound(const Sound& other) = default;
    Sound& operator=(const Sound& other) = default;

    std::string soundName;
    bool play;
    AudioType type;
};
}
