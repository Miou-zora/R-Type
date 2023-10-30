/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** SoundSystem
*/

#pragma once

#include "AssetsManager.hpp"
#include "ECS.hpp"
#include "Sound.hpp"
#include "OptionManager.hpp"
namespace raylib {
#include <raylib.h>
}

namespace rtype::system {
/**
 * @brief System used to play sound
 */
class SoundSystem {
public:
    SoundSystem() = default;
    ~SoundSystem() = default;

    void operator()(rtype::ecs::Registry& registry,
        rtype::ecs::SparseArray<rtype::component::Sound>& sounds) const
    {
        for (auto&& [index, sound] : ecs::containers::IndexedZipper(sounds)) {
            if (registry.getComponents<rtype::component::Sound>()[index].value().type == rtype::component::AudioType::MUSIC) {
                if (!raylib::IsSoundPlaying(rtype::utils::AssetsManager::getInstance().getSound("theme")))
                    registry.getComponents<rtype::component::Sound>()[index].value().play = true;
                float volume = static_cast<float>(rtype::utils::OptionManager::getInstance().getMusicVolume()) / 100;
                raylib::SetSoundVolume(rtype::utils::AssetsManager::getInstance().getSound(registry.getComponents<rtype::component::Sound>()[index].value().soundName), volume);
            }
            if (sound.value().soundName == "" || sound.value().play == false)
                continue;
            playSound(registry, sound.value(), index);
        }
    }
private:
    void playSound(rtype::ecs::Registry& registry, rtype::component::Sound& sound, size_t index) const
    {
        const raylib::Sound& soundToPlay = rtype::utils::AssetsManager::getInstance().getSound(sound.soundName);
        raylib::PlaySound(soundToPlay);
        float volume = static_cast<float>(rtype::utils::OptionManager::getInstance().getSoundVolume()) / 100;
        raylib::SetSoundVolume(soundToPlay, volume);
        sound.play = false;
    }
};
}