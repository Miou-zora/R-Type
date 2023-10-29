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
        enum class prefabs {
            // Enemies
            PATA_PATA,
            SCANT,
            ZOYDO,
            // Misc
            TOP_WALL,
            BOTTOM_WALL
        };
        /**
         * @brief map that contains all the prefabs names and their corresponding enum
        */
        static const std::unordered_map<prefabs, std::string> prefabsMapping;
    };
    /**
     * @brief instantiation of the map that contains all the prefabs names and their corresponding enum
    */
    inline const std::unordered_map<PrefabsMapping::prefabs, std::string> PrefabsMapping::prefabsMapping = {
        {prefabs::PATA_PATA, "Pata-Pata"},
        {prefabs::SCANT, "Scant"},
        {prefabs::ZOYDO, "Zoydo"},
        {prefabs::TOP_WALL, "TopWall"},
        {prefabs::BOTTOM_WALL, "BottomWall"}
    };
}
