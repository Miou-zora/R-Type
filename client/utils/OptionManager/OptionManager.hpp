/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** OptionManager
*/

#pragma once

namespace raylib {
    #include <raylib.h>
}

namespace rtype::utils
{
    /**
     * @brief OptionManager singleton that handle all the options infos
     *
     */
    class OptionManager {
        // Singleton part
        private:
            OptionManager() = default;
        public:
            /**
             * @brief Get the instance of the OptionManager. If it doesn't exist, it will be created.
             */
            static OptionManager &getInstance()
            {
                if (!m_instance)
                    m_instance = new OptionManager();
                return (*m_instance);
            }
            OptionManager(OptionManager const &) = delete;
            void operator=(OptionManager const &) = delete;
        private:
            static OptionManager *m_instance;
        public:
            /**
             * @brief Set the Sound Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int setSoundVolume(int volume);
            /**
             * @brief Set the Music Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int setMusicVolume(int volume);
            /**
             * @brief Increase the Sound Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int increaseSoundVolume(int volume);
            /**
             * @brief Increase the Music Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int increaseMusicVolume(int volume);
            /**
             * @brief Decrease the Sound Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int decreaseSoundVolume(int volume);
            /**
             * @brief Decrease the Music Volume object
             *
             * @param volume
             * @return int the volume set
             */
            int decreaseMusicVolume(int volume);
            /**
             * @brief Set the Key Up object
             *
             * @param keyUp
             */
            void setKeyUp(int keyUp);
            /**
             * @brief Set the Key Down object
             *
             * @param keyDown
             */
            void setKeyDown(int keyDown);
            /**
             * @brief Set the Key Left object
             *
             * @param keyLeft
             */
            void setKeyLeft(int keyLeft);
            /**
             * @brief Set the Key Right object
             *
             * @param keyLeft
             */
            void setKeyRight(int keyRight);
            /**
             * @brief Set the Key Shoot object
             *
             * @param keyShoot
             */
            void setKeyShoot(int keyShoot);
            /**
             * @brief Get the Sound Volume object
             *
             * @return int
             */
            int getSoundVolume() const;
            /**
             * @brief Get the Music Volume object
             *
             * @return int
             */
            int getMusicVolume() const;
            /**
             * @brief Get the Key Up object
             *
             * @return int
             */
            int getKeyUp() const;
            /**
             * @brief Get the Key Down object
             *
             * @return int
             */
            int getKeyDown() const;
            /**
             * @brief Get the Key Left object
             *
             * @return int
             */
            int getKeyLeft() const;
            /**
             * @brief Get the Key Right object
             *
             * @return int
             */
            int getKeyRight() const;
            /**
             * @brief Get the Key Shoot object
             *
             * @return int
             */
            int getKeyShoot() const;

        private:
            int m_soundVolume = 100;
            int m_musicVolume = 100;
            int m_keyUp = raylib::KEY_UP;
            int m_keyDown = raylib::KEY_DOWN;
            int m_keyLeft = raylib::KEY_LEFT;
            int m_keyRight = raylib::KEY_RIGHT;
            int m_keyShoot = raylib::KEY_SPACE;
    };
    inline OptionManager *OptionManager::m_instance = nullptr;
}
