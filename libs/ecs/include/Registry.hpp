/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** Registry
*/

#pragma once

#include "Entity.hpp"
#include "SparseArray.hpp"
#include "Exceptions.hpp"
#include <any>
#include <chrono>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include "RealDeltaTimeProvider.hpp"

namespace rtype::ecs
{
    /**
     * @brief The registry is the main class of the ECS. It is used to create, kill and manage entities.
     * It is also used to register and get components. These registered components can be used by systems.
     * After registering all the components and systems, the user can call the runSystems() method to run all the systems.
     * To use ECS, you need to create a registry and register all the components and systems you need and after that
     * you can create entities and add components to them.
     *
     * @example
     * ecs::Registry reg;
     *
     * reg.addSystem<Position, Velocity>([](ecs::Registry &reg, ecs::SparseArray<Position> &pos, ecs::SparseArray<Velocity> &vel)
     * {
     *     for (auto &&[pos, vel] : ecs::containers::Zipper(pos, vel))
     *     {
     *         pos.value().x += vel.value().x;
     *         pos.value().y += vel.value().y;
     *     }
     * });
     * reg.addSystem<Position>([](ecs::Registry &reg, ecs::SparseArray<Position> &pos)
     * {
     *     for (auto &&[pos] : ecs::Zipper(pos))
     *         std::cout << "Position: " << pos.value().x << ", " << pos.value().y << std::endl;
     * });
     * reg.registerComponent<Position>();
     * reg.registerComponent<Velocity>();
     *
     * ecs::Entity e = reg.spawnEntity();
     * reg.addComponent(e, Position{10, 10});
     * reg.addComponent(e, Velocity{1, 1});
     *
     * while (reg.getComponents<Position>()[e].value().x < 100)
     * {
     *     reg.runSystems();
     * }
     * reg.killEntity(e);
     */
    class Registry
    {
    private:
        typedef struct component_s
        {
            std::any listOfInstances;
            std::function<void(Registry &, Entity const &)> destructor;
        } component_t;

    public:
        /**
         * @brief Construct a new Registry object.
         *
         * @param deltaTimeProvider The delta time provider to use.
         */
        Registry(std::shared_ptr<IDeltaTimeProvider> deltaTimeProvider = std::make_shared<RealDeltaTimeProvider>()) : m_id(0), m_deltaTime(0), m_deltaTimeProvider(deltaTimeProvider) {};

        /**
         * @brief Destroy the Registry object.
         */
        ~Registry() {}

        /**
         * @brief Register a component to the registry. This allows to use this component in ecs.
         *
         * @tparam Component The component to register.
         */
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            m_components[std::type_index(typeid(Component))] = component_t{
                SparseArray<Component>(),
                [](Registry &reg, Entity const &entity)
                {
                    SparseArray<Component> &arr = reg.getComponents<Component>();
                    if (reg.hasComponent<Component>(entity))
                        arr.erase(entity);
                }};
            return (std::any_cast<SparseArray<Component> &>(m_components[std::type_index(typeid(Component))].listOfInstances));
        }

        /**
         * @brief Get the list of component.
         *
         * @tparam Component The list of component to get.
         * @return SparseArray<Component>& The list of component.
         * @throw ecs::BadOptionalAccess If the component is not registered.
         */
        template <class Component>
        SparseArray<Component> &getComponents()
        {
            try
            {
                return (std::any_cast<SparseArray<Component> &>(m_components[std::type_index(typeid(Component))].listOfInstances));
            }
            catch (std::bad_any_cast const &e)
            {
                throw ecs::BadAnyCast("Registry::getComponents::BadAnyCast: Component not registered");
            };
        }

        /**
         * @brief Get the list of component.
         *
         * @tparam Component The list of component to get.
         * @return SparseArray<Component> const& The list of component.
         * @throw ecs::BadOptionalAccess If the component is not registered.
         */
        template <class Component>
        SparseArray<Component> const &getComponents() const
        {
            try
            {
                return (std::any_cast<SparseArray<Component> const &>(m_components.at(std::type_index(typeid(Component))).listOfInstances));
            }
            catch (std::bad_any_cast const &e)
            {
                throw ecs::BadAnyCast("Registry::getComponents::BadAnyCast: Component not registered");
            };
        }

        /**
         * @brief Create an entity. Use dead entitie places if there is any.
         *
         * @return Entity The entity created.
         */
        Entity spawnEntity()
        {
            if (m_deadEntities.empty())
            {
                return (Entity(m_id++));
            }

            Entity e = m_deadEntities.back();
            m_deadEntities.pop_back();
            return (e);
        }

        /**
         * @brief Get the entity from an index.
         *
         * @param idx The index of the entity.
         * @return Entity The entity.
         */
        Entity entityFromIndex(std::size_t idx)
        {
            return (Entity(idx));
        }

        /**
         * @brief Kill an entity. This will remove all the components of this entity.
         *
         * @param e The entity to kill.
         */
        void killEntity(Entity const &e)
        {
            m_entitiesToKill.push_back(e);
        }

        /**
         * @brief Add a component to an entity.
         *
         * @tparam Component The component to add.
         * @param to The entity to add the component to.
         * @param c The component to add.
         * @return typename SparseArray<Component>::ReferenceType The reference to the component added.
         * @throw ecs::BadOptionalAccess If the component is not registered.
         */
        template <typename Component>
        typename SparseArray<Component>::ReferenceType addComponent(Entity const &to,
                                                                    Component &&c)
        {
            SparseArray<Component> &arr = getComponents<Component>();
            arr.insertAt(to, std::forward<Component>(c));
            return (arr[to]);
        }

        /**
         * @brief Add a component to an entity.
         *
         * @tparam Component The component to add.
         * @param to The entity to add the component to.
         * @param p... The parameters to construct the component.
         * @return typename SparseArray<Component>::ReferenceType The reference to the component added.
         * @throw ecs::BadOptionalAccess If the component is not registered.
         */
        template <typename Component, typename... Params>
        typename SparseArray<Component>::ReferenceType emplaceComponent(Entity const &to, Params &&...p)
        {
            SparseArray<Component> &arr = getComponents<Component>();
            arr.emplaceAt(to, std::in_place, std::forward<Params>(p)...);
            return (arr[to]);
        }

        /**
         * @brief Get a boolean indicating if an entity has a component.
         *
         * @tparam Component The component to check.
         * @param e The entity to check.
         */
        template <class Component>
        bool hasComponent(Entity const &e) const
        {
            if (m_components.find(std::type_index(typeid(Component))) == m_components.end())
                return (false);
            if (getComponents<Component>().size() > e)
                if (getComponents<Component>()[e].has_value())
                    return (true);
            return (false);
        }

        /**
         * @brief Remove a component from an entity.
         *
         * @tparam Component The component to remove.
         * @param from The entity to remove the component from.
         * @throw ecs::BadOptionalAccess If the component is not registered.
         */
        template <typename Component>
        void removeComponent(Entity const &from)
        {
            SparseArray<Component> &arr = getComponents<Component>();
            arr.erase(from);
        }

        /**
         * @brief Add system to the registry. A system is a function that will be called by the registry.
         * The function must take a registry as first parameter and the components as next parameters.
         * The components must be in the same order as the template parameters.
         * The function must return void.
         * The function will be called by the registry in the order they were added.
         *
         * @tparam Components The components to use in the system.
         * @param f The function to add.
         */
        template <class... Components, typename Function>
        void addSystem(Function &&f)
        {
            m_systems.push_back([f](Registry &reg)
                                { f(reg, reg.getComponents<Components>()...); });
        }

        /**
         * @brief Add system to the registry. A system is a function that will be called by the registry.
         * The function must take a registry as first parameter and the components as next parameters.
         * The components must be in the same order as the template parameters.
         * The function must return void.
         * The function will be called by the registry in the order they were added.
         *
         * @tparam Components The components to use in the system.
         * @param f The function to add.
         */
        template <class... Components, typename Function>
        void addSystem(Function const &f)
        {
            m_systems.push_back([f](Registry &reg)
                                { f(reg, reg.getComponents<Components>()...); });
        }

        /**
         * @brief Run all the systems. The systems will be called in the order they were added. It will also update the delta time.
         */
        void runSystems()
        {
            _updateDeltaTime();
            for (auto &system : m_systems)
            {
                system(*this);
            }
            _killEntityPostUpdate();
        }

        /**
         * @brief Get the delta time between the last update of the delta time.
         */
        float getDeltaTime() const
        {
            return (m_deltaTime);
        }

        /**
         * @brief Set the delta time provider.
        */
        void setDeltaTimeProvider(std::shared_ptr<IDeltaTimeProvider> deltaTimeProvider)
        {
            m_deltaTimeProvider = deltaTimeProvider;
        }

    private:
        void _updateDeltaTime()
        {
            m_deltaTime = m_deltaTimeProvider->getDeltaTime();
        }

        void _killEntityPostUpdate(void)
        {
            for (auto &entity : m_entitiesToKill)
            {
                for (auto &component : m_components)
                {
                    component.second.destructor(*this, entity);
                }
                m_deadEntities.push_back(entity);
            }
            m_entitiesToKill.clear();
        }

    private:
        std::unordered_map<std::type_index, component_t> m_components;
        std::vector<std::function<void(Registry &)>> m_systems;
        std::vector<Entity> m_deadEntities;
        std::vector<Entity> m_entitiesToKill;
        size_t m_id;
        float m_deltaTime;
        std::shared_ptr<IDeltaTimeProvider> m_deltaTimeProvider;
    };

}
