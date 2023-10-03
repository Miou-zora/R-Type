/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Shooter
*/

#pragma once

#include <string>
#include "Vector.hpp"

namespace rtype::component
{
    /**
     * @brief Shooter component used to shoot projectiles (prefabs) from an entity with a cooldown timer
    */
    struct Shooter
    {
        /**
         * @brief Construct a new Shooter object
         *
         * @param projectileName_ name of the projectile prefab
         * @param cooldown_ cooldown between each shot
         * @param timer_ timer used to know when the entity can shoot again
        */
        Shooter(const std::string &projectileName_ = "", const float &cooldown_ = 0.5, const float &timer_ = 0) : projectileName(projectileName_), cooldown(cooldown_), timer(timer_){};
        ~Shooter() = default;

        Shooter(const Shooter &other) = default;
        Shooter &operator=(const Shooter &other) = default;

        virtual void update(float deltaTime)
        {
            timer += deltaTime;
        }

        virtual void reset(void)
        {
            timer = 0;
        }

        virtual bool canShoot(void)
        {
            return (timer >= cooldown);
        }

        std::string projectileName;
        float cooldown;
        float timer;
    };
}
