/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Lootable
*/

#pragma once
#include <string>
#include <map>
#include <memory>

namespace rtype::component
{
    /**
     * @brief Lootable component used to store prefab to drop on death
     */
    struct Lootable
    {
        using PrefabName = std::string;
        using Chance = unsigned int; // between 0 and 100
        using ListOfDroppableEntity = std::map<PrefabName, Chance>;

        Lootable() : listOfDroppableEntity(std::make_shared<ListOfDroppableEntity>()) {};
        ~Lootable() = default;

        Lootable(const Lootable &other)
        {
            if (other.listOfDroppableEntity == nullptr)
                return;
            listOfDroppableEntity = std::make_shared<ListOfDroppableEntity>();
            for (auto &&[prefabName, chance] : *(other.listOfDroppableEntity))
                (*listOfDroppableEntity)[prefabName] = chance;
        };
        Lootable &operator=(const Lootable &other) = default;

        std::shared_ptr<ListOfDroppableEntity> listOfDroppableEntity;

        Lootable &addDroppableEntity(const std::string &prefabName, float chance)
        {
            if (listOfDroppableEntity == nullptr)
                listOfDroppableEntity = std::make_shared<ListOfDroppableEntity>();
            (*listOfDroppableEntity)[prefabName] = clamp<int>(chance, 0, 100);
            return *this;
        }

        private:
            template<typename T>
            T clamp(T value, T min, T max)
            {
                if (value < min)
                    return min;
                if (value > max)
                    return max;
                return value;
            }
    };
}
