/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** assets_manager
*/

#pragma once

#include <unordered_map>
#include <iostream>
namespace raylib {
    #include <raylib.h>
}
#include <cmrc/cmrc.hpp>
#include <cstring>

CMRC_DECLARE(assets);

#define FONT_TTF_DEFAULT_NUMCHARS 95
#define FONT_TTF_DEFAULT_SIZE 32

namespace rtype::utils
{
    /**
     * @brief A singleton class to manage assets (textures, sounds, fonts).
    */
    class AssetsManager
    {
    public:
        static constexpr const char *DEFAULT_FONT = "default";

        // Singleton part
    private:
        AssetsManager(): m_fs(cmrc::assets::get_filesystem()) {
            // Load default font
            m_fonts[DEFAULT_FONT] = raylib::GetFontDefault();
        };
    public:
        /**
         * @brief Get the instance of the AssetsManager. If it doesn't exist, it will be created.
        */
        static AssetsManager &getInstance()
        {
            if (!m_instance)
                m_instance = new AssetsManager();
            return (*m_instance);
        }
    private:
        static AssetsManager *m_instance;
        cmrc::embedded_filesystem m_fs;

    public:
        /**
         * @brief The type of a texture.
        */
        using texture_t = raylib::Texture2D;
        /**
         * @brief The type of a sound.
        */
        using sound_t = raylib::Sound;
        /**
         * @brief The type of a font.
        */
        using font_t = raylib::Font;

        /**
         * @brief Destroy the AssetsManager object.
        */
        virtual ~AssetsManager() = default;

        /**
         * @brief Load a texture from a file.
         * @param name The name of the texture.
         * @param path The path to the file.
         * @return true if the texture was loaded successfully, false otherwise.
        */
        bool loadTexture(const std::string &name, const std::string &path);

        /**
         * @brief Get a texture.
         * @param name The name of the texture.
         * @return The texture.
        */
        texture_t &getTexture(const std::string &name);

        /**
         * @brief Load a sound from a file.
         * @param name The name of the sound.
         * @param path The path to the file.
         * @return true if the sound was loaded successfully, false otherwise.
        */
        bool loadSound(const std::string &name, const std::string &path);

        /**
         * @brief Get a sound.
         * @param name The name of the sound.
         * @return The sound.
        */
        sound_t &getSound(const std::string &name);

        /**
         * @brief Load a font from a file.
         * @param name The name of the font.
         * @param path The path to the file.
         * @return true if the font was loaded successfully, false otherwise.
        */
        bool loadFont(const std::string &name, const std::string &path);

        /**
         * @brief Get a font.
         * @param name The name of the font.
         * @return The font.
        */
        font_t &getFont(const std::string &name);

    private:
        std::unordered_map<std::string, texture_t> m_textures;
        std::unordered_map<std::string, sound_t> m_sounds;
        std::unordered_map<std::string, font_t> m_fonts;
    };

    inline AssetsManager *AssetsManager::m_instance = nullptr;
}
