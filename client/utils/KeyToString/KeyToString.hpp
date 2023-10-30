/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** KeyToString
*/

#pragma once

#include <map>
#include <string>
namespace raylib {
#include <raylib.h>
}

namespace rtype::utils
{
    /**
     * @brief Convert a raylib KeyboardKey to a string
     * @param key The KeyboardKey to convert
     * @return The string corresponding to the KeyboardKey
     */
    std::string keyToString(raylib::KeyboardKey key);
}
