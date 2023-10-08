/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Spawner.test
*/

#include "Spawner.hpp"

#include <gtest/gtest.h>

TEST(Spawner, init)
{
    {
        rtype::component::Spawner spawner;
        ASSERT_EQ(spawner.looping, false);
        ASSERT_EQ(spawner.spawnList.size(), 0);
    }
    {
        rtype::component::Spawner spawner(true);
        ASSERT_EQ(spawner.looping, true);
        ASSERT_EQ(spawner.spawnList.size(), 0);
    }
    {
        rtype::component::Spawner spawner(false);
        ASSERT_EQ(spawner.looping, false);
        ASSERT_EQ(spawner.spawnList.size(), 0);
    }
}

TEST(Spawner, addEntityToSpawnListGlobal)
{
    rtype::component::Spawner spawner;

    spawner.addEntityToSpawnList("entityName", 1);
    ASSERT_EQ(spawner.spawnList.size(), 1);
    ASSERT_EQ(spawner.spawnList[0].entityName, "entityName");
    ASSERT_EQ(spawner.spawnList[0].spawnDelay, 1);

    spawner.addEntityToSpawnList("entityName2", 2);
    ASSERT_EQ(spawner.spawnList.size(), 2);
    ASSERT_EQ(spawner.spawnList[1].entityName, "entityName2");
    ASSERT_EQ(spawner.spawnList[1].spawnDelay, 1);

    spawner.addEntityToSpawnList("entityName3", 1.75);
    ASSERT_EQ(spawner.spawnList.size(), 3);
    ASSERT_EQ(spawner.spawnList[1].entityName, "entityName3");
    ASSERT_EQ(spawner.spawnList[1].spawnDelay, 0.75);
    ASSERT_EQ(spawner.spawnList[2].spawnDelay, 0.25);

    spawner.addEntityToSpawnList("entityName4", 0.5);
    ASSERT_EQ(spawner.spawnList.size(), 4);
    ASSERT_EQ(spawner.spawnList[0].entityName, "entityName4");
    ASSERT_EQ(spawner.spawnList[0].spawnDelay, 0.5);
    ASSERT_EQ(spawner.spawnList[1].entityName, "entityName");
    ASSERT_EQ(spawner.spawnList[1].spawnDelay, 0.5);

    spawner.addEntityToSpawnList("entityName5", 3);
    ASSERT_EQ(spawner.spawnList.size(), 5);
    ASSERT_EQ(spawner.spawnList[4].entityName, "entityName5");
    ASSERT_EQ(spawner.spawnList[4].spawnDelay, 1);

    spawner.addEntityToSpawnList("entityName6", 1.75);
    ASSERT_EQ(spawner.spawnList.size(), 6);
    ASSERT_EQ(spawner.spawnList[2].entityName, "entityName6");
    ASSERT_EQ(spawner.spawnList[2].spawnDelay, 0.75);
    ASSERT_EQ(spawner.spawnList[3].entityName, "entityName3");
    ASSERT_EQ(spawner.spawnList[3].spawnDelay, 0);
}
