/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** AssetsManager
*/

#include "AssetsManager.hpp"

bool utils::AssetsManager::loadTexture(const std::string &name, const std::string &path)
{
    _textures[name] = LoadTexture(path.c_str());
    bool result = _textures[name].id != 0;
    if (result)
        std::cout << "Loaded texture " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load texture " << name << " from " << path << std::endl;
    return (result);
}

utils::AssetsManager::texture_t &utils::AssetsManager::getTexture(const std::string &name)
{
    return (_textures[name]);
}

bool utils::AssetsManager::loadSound(const std::string &name, const std::string &path)
{
    _sounds[name] = LoadSound(path.c_str());
    bool result = _sounds[name].frameCount != 0;
    if (result)
        std::cout << "Loaded sound " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load sound " << name << " from " << path << std::endl;
    return (result);
}

utils::AssetsManager::sound_t &utils::AssetsManager::getSound(const std::string &name)
{
    return (_sounds[name]);
}

bool utils::AssetsManager::loadFont(const std::string &name, const std::string &path)
{
    _fonts[name] = LoadFont(path.c_str());
    bool result = _fonts[name].baseSize != 0;
    if (result)
        std::cout << "Loaded font " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load font " << name << " from " << path << std::endl;
    return (result);
}

utils::AssetsManager::font_t &utils::AssetsManager::getFont(const std::string &name)
{
    return (_fonts[name]);
}
