/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** AssetsManager
*/

#include "AssetsManager.hpp"

bool rtype::utils::AssetsManager::loadTexture(const std::string &name, const std::string &path)
{
    m_textures[name] = LoadTexture(path.c_str());
    bool result = m_textures[name].id != 0;
    if (result)
        std::cout << "Loaded texture " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load texture " << name << " from " << path << std::endl;
    return (result);
}

rtype::utils::AssetsManager::texture_t &rtype::utils::AssetsManager::getTexture(const std::string &name)
{
    return (m_textures[name]);
}

bool rtype::utils::AssetsManager::loadSound(const std::string &name, const std::string &path)
{
    m_sounds[name] = LoadSound(path.c_str());
    bool result = m_sounds[name].frameCount != 0;
    if (result)
        std::cout << "Loaded sound " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load sound " << name << " from " << path << std::endl;
    return (result);
}

rtype::utils::AssetsManager::sound_t &rtype::utils::AssetsManager::getSound(const std::string &name)
{
    return (m_sounds[name]);
}

bool rtype::utils::AssetsManager::loadFont(const std::string &name, const std::string &path)
{
    m_fonts[name] = LoadFont(path.c_str());
    bool result = m_fonts[name].baseSize != 0;
    if (result)
        std::cout << "Loaded font " << name << " from " << path << std::endl;
    else
        std::cerr << "Failed to load font " << name << " from " << path << std::endl;
    return (result);
}

rtype::utils::AssetsManager::font_t &rtype::utils::AssetsManager::getFont(const std::string &name)
{
    return (m_fonts[name]);
}
