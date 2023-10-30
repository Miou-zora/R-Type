/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Spawner
*/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Vector.hpp"

namespace rtype::component
{
    /**
     * @brief Spawner component used to store the informations about the spawner and the entities to spawn
     */
    struct Spawner
    {
    private:
        struct EntitySpawnInfo
        {
            std::string entityName;
            float spawnDelay;
            rtype::utils::Vector<float> position;
        };

    public:
        enum class Context
        {
            Global,
            Local
        };

        Spawner(bool looping_ = false): looping(looping_) {};
        ~Spawner() = default;

        Spawner(const Spawner &other) = default;
        Spawner &operator=(const Spawner &other) = default;

        Spawner &addEntityToSpawnList(std::string entityName, float spawnDelay, Context context = Context::Global, rtype::utils::Vector<float> position = {0, 0})
        {
            if (context == Context::Global) {
                if (spawnList.size() == 0)
                    spawnList.push_back({entityName, spawnDelay, position});
                else {
                    insertEntityInSpawnList(entityName, spawnDelay, position);
                }
            } else
                spawnList.push_back({entityName, spawnDelay, position});
            return (*this);
        }

        private:
            void insertEntityInSpawnList(std::string entityName, float spawnDelay, rtype::utils::Vector<float> position)
            {
                float delay = 0;
                std::size_t index = 0;

                for (auto &value : spawnList) {
                    if (delay + value.spawnDelay >= spawnDelay) {
                        value.spawnDelay -= spawnDelay - delay  ;
                        spawnList.insert(spawnList.begin() + index, {entityName, spawnDelay - delay, position});
                        return;
                    }
                    index++;
                    delay += value.spawnDelay;
                }
                spawnList.push_back({entityName, spawnDelay - delay, position});
            }
        public:

        std::vector<EntitySpawnInfo> spawnList;
        bool looping;
        float timer = 0;
    };
}
