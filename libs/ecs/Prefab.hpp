/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** Prefab
*/

#pragma once

#include "Registry.hpp"
#include <any>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace rtype::ecs
{
    /**
     * @brief Prefab is a container that store a list of components and can instantiate an entity with those components.
    */
    class Prefab
    {
    public:
        /**
         * @brief Construct a new Prefab object
        */
        Prefab() = default;

        /**
         * @brief Destroy the Prefab object
        */
        virtual ~Prefab() = default;

        /**
         * @brief Add a component to the prefab
        */
        template <class Component, typename... Args>
        Prefab &addComponent(Args... args)
        {
            m_components[std::type_index(typeid(Component))] = ([args...](ecs::Registry &reg, const Entity &entity) -> void
                                                               { reg.addComponent<Component>(entity, Component(args...)); });
            return (*this);
        }

        /**
         * @brief Instantiate an entity with the components of the prefab
        */
        Entity instantiate(ecs::Registry &reg)
        {
            Entity entity = reg.spawnEntity();

            for (auto &component : m_components)
            {
                component.second(reg, entity);
            }
            return (entity);
        }

    private:
        std::unordered_map<std::type_index, std::function<void(ecs::Registry &, const Entity &)>> m_components;
    };
}
