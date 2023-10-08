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

namespace rtype::component
{
    struct Spawner
    {
    private:
        struct EntitySpawnInfo
        {
            std::string entityName;
            float spawnDelay;
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

        void addEntityToSpawnList(std::string entityName, float spawnDelay, Context context = Context::Global)
        {
            if (context == Context::Global) {
                if (spawnList.size() == 0)
                    spawnList.push_back({entityName, spawnDelay});
                else {
                    insertEntityInSpawnList(entityName, spawnDelay);
                }
            } else
                spawnList.push_back({entityName, spawnDelay});
        }

        private:
            void insertEntityInSpawnList(std::string entityName, float spawnDelay)
            {
                float delay = 0;
                std::size_t index = 0;

                for (auto &value : spawnList) {
                    if (delay + value.spawnDelay >= spawnDelay) {
                        value.spawnDelay -= spawnDelay - delay  ;
                        spawnList.insert(spawnList.begin() + index, {entityName, spawnDelay - delay});
                        return;
                    }
                    index++;
                    delay += value.spawnDelay;
                }
                spawnList.push_back({entityName, spawnDelay - delay});
            }
        public:

        std::vector<EntitySpawnInfo> spawnList;
        bool looping;
        float timer = 0;
    };
}
