/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** Entity
*/

#pragma once

#include <cstddef>

namespace ecs
{
    /**
     * @brief Entity is a simple wrapper around a size_t that represent an entity
    */
    class Entity
    {
    public:
        /**
         * @brief Construct a new Entity object
        */
        explicit Entity(std::size_t id)
            : m_id(id){};

        /**
         * @brief Destroy the Entity object
        */
        virtual ~Entity() = default;
    
        /**
         * @brief Get the id of the entity
        */
        operator std::size_t() const
        {
            return (m_id);
        }

    private:
        std::size_t m_id;
    };
}
