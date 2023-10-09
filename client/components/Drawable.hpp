/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Drawable
*/

#pragma once

#include <string>
#include "Rectangle.hpp"

namespace rtype::component {
struct Drawable {
    const static std::string NO_TEXTURE;
    Drawable(const std::string& textureName_ = NO_TEXTURE, float scale_ = 1, const rtype::utils::Rectangle& sourceRectangle_ = rtype::utils::Rectangle())
        : textureName(textureName_)
        , scale(scale_)
        , sourceRectangle(sourceRectangle_)
    {
    }
    ~Drawable() = default;

    Drawable(const Drawable& other) = default;
    Drawable& operator=(const Drawable& other) = default;

    std::string textureName;
    float scale;
    rtype::utils::Rectangle sourceRectangle;
};
const std::string Drawable::NO_TEXTURE = "NO TEXTURE";
}
