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
        enum class prefabs
        {
            // Enemies
            PATA_PATA,
            SCANT,
            ZOYDO,
            // Misc
            TOP_WALL,
            BOTTOM_WALL,
            // Bullets
            SIMPLE_BULLET,
            TRIPLE_BULLET,
            ALLY_BULLET,
            TARGET_BULLET,
            BOSS_BULLET,
            TRIPLE_BOSS_BULLET
        };
        /**
         * @brief map that contains all the prefabs enum and their corresponding names
         */
        static const std::unordered_map<prefabs, std::string> prefabsMapping;
        /**
         * @brief map that contains all the prefabs names and their corresponding enum
         */
        static const std::unordered_map<std::string, prefabs> namesMapping;
    };
    /**
     * @brief instantiation of the map that contains all the prefabs enum and their corresponding names
     */
    inline const std::unordered_map<PrefabsMapping::prefabs, std::string> PrefabsMapping::prefabsMapping = {
        {prefabs::PATA_PATA, "Pata-Pata"},
        {prefabs::SCANT, "Scant"},
        {prefabs::ZOYDO, "Zoydo"},
        {prefabs::TOP_WALL, "TopWall"},
        {prefabs::BOTTOM_WALL, "BottomWall"},
        {prefabs::SIMPLE_BULLET, "SimpleBullet"},
        {prefabs::TRIPLE_BULLET, "TripleBullet"},
        {prefabs::ALLY_BULLET, "AllyBullet"},
        {prefabs::TARGET_BULLET, "TargetBullet"},
        {prefabs::BOSS_BULLET, "BossBullet"},
        {prefabs::TRIPLE_BOSS_BULLET, "TripleBossBullet"}};
    /**
     * @brief instantiation of the map that contains all the prefabs names and their corresponding enum
    */
    inline const std::unordered_map<std::string, PrefabsMapping::prefabs> PrefabsMapping::namesMapping = {
        {PrefabsMapping::prefabsMapping.at(prefabs::PATA_PATA), prefabs::PATA_PATA},
        {PrefabsMapping::prefabsMapping.at(prefabs::SCANT), prefabs::SCANT},
        {PrefabsMapping::prefabsMapping.at(prefabs::ZOYDO), prefabs::ZOYDO},
        {PrefabsMapping::prefabsMapping.at(prefabs::TOP_WALL), prefabs::TOP_WALL},
        {PrefabsMapping::prefabsMapping.at(prefabs::BOTTOM_WALL), prefabs::BOTTOM_WALL},
        {PrefabsMapping::prefabsMapping.at(prefabs::SIMPLE_BULLET), prefabs::SIMPLE_BULLET},
        {PrefabsMapping::prefabsMapping.at(prefabs::TRIPLE_BULLET), prefabs::TRIPLE_BULLET},
        {PrefabsMapping::prefabsMapping.at(prefabs::ALLY_BULLET), prefabs::ALLY_BULLET},
        {PrefabsMapping::prefabsMapping.at(prefabs::TARGET_BULLET), prefabs::TARGET_BULLET},
        {PrefabsMapping::prefabsMapping.at(prefabs::BOSS_BULLET), prefabs::BOSS_BULLET},
        {PrefabsMapping::prefabsMapping.at(prefabs::TRIPLE_BOSS_BULLET), prefabs::TRIPLE_BOSS_BULLET}};
}
