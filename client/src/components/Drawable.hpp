/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Drawable
*/

#pragma once

#include <string>

namespace rtype::component
{
    struct Drawable {
        const static std::string NO_TEXTURE;


        Drawable(const std::string &textureName_ = Drawable::NO_TEXTURE, float scale_ = 1)
            : textureName(textureName_), scale(scale_) {}
        ~Drawable() = default;

        Drawable(const Drawable &other) = default;
        Drawable &operator=(const Drawable &other) = default;

        std::string textureName;
        float scale;
    };

    const std::string Drawable::NO_TEXTURE = "NO TEXTURE";
}
