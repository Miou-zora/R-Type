/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** PrefabsMapping
*/

#pragma once

#include <unordered_map>
#include <string>

namespace rtype::utils
{
    /**
     * @brief PrefabsMapping static class that contains all the prefabs names and their corresponding enum
    */
    class PrefabsMapping
    {
    public:
        PrefabsMapping() = delete;

        /**
         * @brief enum of all enemy's prefabs
        */
        enum class enemiesPrefabs {
            PATA_PATA,
            SCANT,
            ZOYDO
        };
        /**
         * @brief map that contains all the prefabs names and their corresponding enum
        */
        static const std::unordered_map<enemiesPrefabs, std::string> enemiesPrefabsMapping;
    };
    /**
     * @brief instantiation of the map that contains all the prefabs names and their corresponding enum
    */
    inline const std::unordered_map<PrefabsMapping::enemiesPrefabs, std::string> PrefabsMapping::enemiesPrefabsMapping = {
        {enemiesPrefabs::PATA_PATA, "Pata-Pata"},
        {enemiesPrefabs::SCANT, "Scant"},
        {enemiesPrefabs::ZOYDO, "Zoydo"}
    };
}
