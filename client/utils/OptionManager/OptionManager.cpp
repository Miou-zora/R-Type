/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** OptionManager
*/

#include "OptionManager.hpp"

int rtype::utils::OptionManager::setSoundVolume(int volume)
{
    if (volume < 0) {
        volume = 0;
    } else if (volume > 100) {
        volume = 100;
    } else {
        m_soundVolume = volume;
    }
    return m_soundVolume;
}

int rtype::utils::OptionManager::setMusicVolume(int volume)
{
    if (volume < 0) {
        volume = 0;
    } else if (volume > 100) {
        volume = 100;
    } else {
        m_musicVolume = volume;
    }
    return m_musicVolume;
}

int rtype::utils::OptionManager::increaseSoundVolume(int volume)
{
    if (m_soundVolume + volume < 0) {
        m_soundVolume = 0;
    } else if (m_soundVolume + volume > 100) {
        m_soundVolume = 100;
    } else {
        m_soundVolume += volume;
    }
    return m_soundVolume;
}

int rtype::utils::OptionManager::increaseMusicVolume(int volume)
{
    if (m_musicVolume + volume < 0) {
        m_musicVolume = 0;
    } else if (m_musicVolume + volume > 100) {
        m_musicVolume = 100;
    } else {
        m_musicVolume += volume;
    }
    return m_musicVolume;
}

int rtype::utils::OptionManager::decreaseSoundVolume(int volume)
{
    if (m_soundVolume - volume < 0) {
        m_soundVolume = 0;
    } else if (m_soundVolume - volume > 100) {
        m_soundVolume = 100;
    } else {
        m_soundVolume -= volume;
    }
    return m_soundVolume;
}

int rtype::utils::OptionManager::decreaseMusicVolume(int volume)
{
    if (m_musicVolume - volume < 0) {
        m_musicVolume = 0;
    } else if (m_musicVolume - volume > 100) {
        m_musicVolume = 100;
    } else {
        m_musicVolume -= volume;
    }
    return m_musicVolume;
}

void rtype::utils::OptionManager::setKeyUp(int keyUp)
{
    m_keyUp = keyUp;
}

void rtype::utils::OptionManager::setKeyDown(int keyDown)
{
    m_keyDown = keyDown;
}

void rtype::utils::OptionManager::setKeyLeft(int keyLeft)
{
    m_keyLeft = keyLeft;
}

void rtype::utils::OptionManager::setKeyRight(int keyRight)
{
    m_keyRight = keyRight;
}

void rtype::utils::OptionManager::setKeyShoot(int keyShoot)
{
    m_keyShoot = keyShoot;
}

int rtype::utils::OptionManager::getSoundVolume() const
{
    return m_soundVolume;
}

int rtype::utils::OptionManager::getMusicVolume() const
{
    return m_musicVolume;
}

int rtype::utils::OptionManager::getKeyUp() const
{
    return m_keyUp;
}

int rtype::utils::OptionManager::getKeyDown() const
{
    return m_keyDown;
}

int rtype::utils::OptionManager::getKeyLeft() const
{
    return m_keyLeft;
}

int rtype::utils::OptionManager::getKeyRight() const
{
    return m_keyRight;
}

int rtype::utils::OptionManager::getKeyShoot() const
{
    return m_keyShoot;
}
