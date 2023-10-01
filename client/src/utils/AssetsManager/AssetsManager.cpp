/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** AssetsManager
*/

#include "AssetsManager.hpp"

bool rtype::utils::AssetsManager::loadTexture(const std::string &name, const std::string &path)
{
    auto texture = m_fs.open(path);

    std::string extension = strrchr(const_cast<char *>(path.c_str()), '.');
    const unsigned char *data = reinterpret_cast<const unsigned char *>(texture.begin());

    Image image = LoadImageFromMemory(extension.c_str(), data, texture.size());
    m_textures[name] = LoadTextureFromImage(image);
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
    auto sound = m_fs.open(path);

    std::string extension = strrchr(const_cast<char *>(path.c_str()), '.');
    const unsigned char *data = reinterpret_cast<const unsigned char *>(sound.begin());
    Wave wave = LoadWaveFromMemory(extension.c_str(), data, sound.size());
    m_sounds[name] = LoadSoundFromWave(wave);
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
    auto font = m_fs.open(path);

    std::string extension = strrchr(const_cast<char *>(path.c_str()), '.');
    const unsigned char *data = reinterpret_cast<const unsigned char *>(font.begin());

    m_fonts[name] = LoadFontFromMemory(extension.c_str(), data, font.size(), FONT_TTF_DEFAULT_SIZE, NULL, FONT_TTF_DEFAULT_NUMCHARS);
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
