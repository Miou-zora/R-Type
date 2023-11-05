    /*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** PrefabManager
*/

#pragma once

#include <map>
#include <string>
#include "ECS.hpp"
#include <memory>

namespace rtype::utils
{
    /**
     * @brief PrefabManager is a singleton that manages prefabs. It is used to create prefabs, instantiate and add component to them.
    */
    class PrefabManager
    {
        // Singleton part
    private:
        PrefabManager(void) = default;
    public:
        static PrefabManager &getInstance()
        {
            if (!m_instance)
                m_instance = new PrefabManager();
            return (*m_instance);
        }

    private:
        static PrefabManager *m_instance;

    private:
        struct PrefabInfos
        {
            std::unique_ptr<ecs::Prefab> prefab;
            std::function<ecs::Entity(ecs::Registry &, ecs::Entity &)> onInstantiate = [](ecs::Registry &, ecs::Entity &entity) { return (entity); };
        };

    public:
        ~PrefabManager();

        ecs::Prefab &createPrefab(const std::string &name)
        {
            m_prefabs[name] = {std::make_unique<ecs::Prefab>()};
            return (*(m_prefabs[name].prefab));
        }

        template <class Component, typename... Args>
        ecs::Prefab &addComponent(const std::string &name, Args... args)
        {
            if (m_prefabs.find(name) == m_prefabs.end())
                throw ecs::OutOfRange("Prefab not found: " + name);
            return (m_prefabs.at(name).prefab->addComponent<Component>(args...));
        }

        ecs::Entity instantiate(const std::string &name, ecs::Registry &registry) const
        {
            if (m_prefabs.find(name) == m_prefabs.end())
                throw ecs::OutOfRange("Prefab not found: " + name);
            ecs::Entity entity = m_prefabs.at(name).prefab->instantiate(registry);
            return (m_prefabs.at(name).onInstantiate(registry, entity));
        }



        friend std::ostream &operator<<(std::ostream &os, const PrefabManager &manager);

    private:
        std::map<std::string, PrefabInfos> m_prefabs;
    };

    inline std::ostream &operator<<(std::ostream &os, const PrefabManager &manager)
    {
        os << "(";
        for (auto &&[name, prefab] : manager.m_prefabs)
        {
            os << name;
            if (prefab.prefab != manager.m_prefabs.rbegin()->second.prefab)
                os << ", ";
        }
        os << ")";
        return (os);
    }

    inline PrefabManager *PrefabManager::m_instance = nullptr;
}
