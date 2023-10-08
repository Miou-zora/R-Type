/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** InputInputShooter
*/

#pragma once

#include <string>
#include "Vector.hpp"
#include "Shooter.hpp"
#include <functional>

namespace rtype::component
{
    /**
     * @brief InputShooter component used to shoot projectiles (prefabs) from an entity with a cooldown timer and using a function to know if the entity can shoot
    */
    struct InputShooter: virtual public Shooter
    {
        /**
         * @brief Construct a new InputShooter object
         *
         * @param projectileName_ name of the projectile prefab
         * @param cooldown_ cooldown between each shot
         * @param timer_ timer used to know when the entity can shoot again
         * @param keyFunction_ function used to know if the entity can shoot so basically if key is pressed or not
        */
        InputShooter(std::function<bool(void)> keyFunction_ = [](){ return false; }, const std::string &projectileName_ = "", const float &cooldown_ = 0.5, const float &timer_ = 0) : rtype::component::Shooter(projectileName_, cooldown_, timer_), keyFunction(keyFunction_) {};
        ~InputShooter() = default;

        InputShooter(const InputShooter &other) = default;
        InputShooter &operator=(const InputShooter &other) = default;

        virtual bool canShoot(void) override
        {
            return (rtype::component::Shooter::canShoot() && keyFunction());
        }

        std::function<bool(void)> keyFunction;
    };
}
