/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Drawable
*/

#pragma once

#include "Rectangle.hpp"
#include <string>

namespace rtype::component {
/**
 * @brief A component use to draw a texture.
 */
struct Drawable {
    const static std::string NO_TEXTURE;
    Drawable(const std::string& textureName_ = NO_TEXTURE, float scale_ = 1.0f, const rtype::utils::Rectangle& sourceRectangle_ = rtype::utils::Rectangle(), int zIndex_ = 0)
        : textureName(textureName_)
        , scale(scale_)
        , sourceRectangle(sourceRectangle_)
        , zIndex(zIndex_)
    {
    }
    ~Drawable() = default;

    Drawable(const Drawable& other) = default;
    Drawable& operator=(const Drawable& other) = default;

    std::string textureName;
    float scale;
    rtype::utils::Rectangle sourceRectangle;
    int zIndex;
};
inline const std::string Drawable::NO_TEXTURE = "NO TEXTURE";
}
