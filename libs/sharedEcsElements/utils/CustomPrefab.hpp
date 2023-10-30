/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** CustomPrefab
*/

#pragma once
#include <string>
#include "ECS.hpp"
#include "PrefabManager.hpp"

namespace rtype::utils
{
    /**
     * @brief CustomPrefab is a container that store a list of components and can instantiate an entity with those components.
    */
    class CustomPrefab : virtual public rtype::ecs::Prefab {
        public:
            /**
             * @brief Construct a new CustomPrefab object
             *
             * @param prefabName The name of the prefab to instantiate
            */
            CustomPrefab(const std::string &prefabName): m_prefabName(prefabName) {};

            /**
             * @brief Destroy the CustomPrefab object
            */
            ~CustomPrefab() = default;

            /**
             * @brief Instantiate an entity with the components of the prefab and the custom components
             *
             * @param reg The registry to use to instantiate the entity
             * @return rtype::ecs::Entity The instantiated entity
            */
            rtype::ecs::Entity instantiate(ecs::Registry &reg)
            {
                rtype::ecs::Entity entity = rtype::utils::PrefabManager::getInstance().instantiate(m_prefabName, reg);
                for (auto &component : m_components)
                {
                    component.second(reg, entity);
                }
                return (entity);
            }

            /**
             * @brief Add a custom component to the prefab
             *
             * @tparam Component The type of the component to add
             * @param args The arguments to pass to the constructor of the component
             * @return CustomPrefab& A reference to the prefab
            */
            template <class Component, typename... Args>
            CustomPrefab &emplaceCustomComponent(Args... args)
            {
                m_components[std::type_index(typeid(Component))] = ([args...](ecs::Registry &reg, const rtype::ecs::Entity &entity) -> void
                                                                   { reg.emplaceComponent<Component>(entity, args...); });
                return (*this);
            }

        private:
            /**
             * @brief The name of the prefab to instantiate
            */
            std::string m_prefabName;

            /**
             * @brief The list of custom components to add to the prefab
            */
            std::unordered_map<std::type_index, std::function<void(ecs::Registry &, const rtype::ecs::Entity &)>> m_components;
    };
}
