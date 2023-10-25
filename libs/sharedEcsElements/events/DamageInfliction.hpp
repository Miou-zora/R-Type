/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** DamageInfliction
*/

#pragma once
#include "ECS.hpp"

namespace rtype::event
{
    /**
     * @brief DamageInfliction event, used to inflict damage to an entity
    */
    struct DamageInfliction
    {
        rtype::ecs::Entity to;
        int damage;
        int currentLife;
    };
}
