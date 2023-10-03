/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Shooter.test
*/

#include "Shooter.hpp"

#include <gtest/gtest.h>

TEST(Shooter, init)
{
    {
        rtype::component::Shooter shooter;

        ASSERT_EQ(shooter.projectileName, "");
        ASSERT_GT(shooter.cooldown, 0);
        ASSERT_LT(shooter.cooldown, 10);
        ASSERT_EQ(shooter.timer, 0);
    }
    {
        rtype::component::Shooter shooter("projectileName", 1, 2);

        ASSERT_EQ(shooter.projectileName, "projectileName");
        ASSERT_EQ(shooter.cooldown, 1);
        ASSERT_EQ(shooter.timer, 2);
    }
}

TEST(Shooter, update)
{
    rtype::component::Shooter shooter("projectileName", 1, 2);

    shooter.update(1);
    ASSERT_EQ(shooter.timer, 3);
}

TEST(Shooter, reset)
{
    rtype::component::Shooter shooter("projectileName", 1, 2);

    shooter.reset();
    ASSERT_EQ(shooter.timer, 0);
}

TEST(Shooter, canShoot)
{
    rtype::component::Shooter shooter("projectileName", 1, 0);

    ASSERT_EQ(shooter.canShoot(), false);
    shooter.update(0.5);
    ASSERT_EQ(shooter.canShoot(), false);
    shooter.update(0.5);
    ASSERT_EQ(shooter.canShoot(), true);
}
