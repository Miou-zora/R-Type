/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Loot
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief Loot component used as a tag to identify loot
     */
    struct Loot
    {
        enum class Type {
            WEAPON
        };

        struct Weapon {
            std::string projName;
            float cooldown;
        };

        Loot(void) = default;
        ~Loot() = default;

        Loot(const Loot &other) = default;
        Loot &operator=(const Loot &other) = default;

        Type type;
        Weapon weapon;
    };
}
