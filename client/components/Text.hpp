/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Text
*/

#pragma once
#include <string>
namespace raylib {
#include <raylib.h>
}

namespace rtype::component {
/**
 * @brief Text component used to store the text of an entity
 */
struct Text {
    const static std::string DEFAULT_FONT;
    Text(const std::string& text_ = "", const std::string& font_ = DEFAULT_FONT, int size_ = 10, float spacing_ = 3.0f, raylib::Color color_ = raylib::BLACK)
        : text(text_)
        , font(font_)
        , size(size_)
        , spacing(spacing_)
        , color(color_) {};
    ~Text() = default;

    Text(const Text& other) = default;
    Text& operator=(const Text& other) = default;

    std::string text;
    std::string font;
    int size;
    float spacing;
    raylib::Color color;
};
inline const std::string Text::DEFAULT_FONT = "default";
}
