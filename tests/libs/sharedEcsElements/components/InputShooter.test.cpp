/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** InputInputShooter.test
*/

#include "InputShooter.hpp"

#include <gtest/gtest.h>

TEST(InputShooter, init)
{
    {
        rtype::component::InputShooter shooter;

        ASSERT_EQ(shooter.keyFunction(), false);
        ASSERT_EQ(shooter.projectileName, "");
        ASSERT_GT(shooter.cooldown, 0);
        ASSERT_LT(shooter.cooldown, 10);
        ASSERT_EQ(shooter.timer, 0);
    }
    {
        rtype::component::InputShooter shooter([&]()
                                               { return true; },
                                               "projectileName", 1, 2);

        ASSERT_EQ(shooter.keyFunction(), true);
        ASSERT_EQ(shooter.projectileName, "projectileName");
        ASSERT_EQ(shooter.cooldown, 1);
        ASSERT_EQ(shooter.timer, 2);
    }
}

TEST(InputShooter, canShoot)
{
    {
        rtype::component::InputShooter shooter([]()
                                               { return true; },
                                               "projectileName", 1, 0);

        ASSERT_EQ(shooter.canShoot(), false);
        shooter.update(0.5);
        ASSERT_EQ(shooter.canShoot(), false);
        shooter.update(0.5);
        ASSERT_EQ(shooter.canShoot(), true);
    }
    {
        rtype::component::InputShooter shooter([]()
                                               { return false; },
                                               "projectileName", 1, 0);

        ASSERT_EQ(shooter.canShoot(), false);
        shooter.update(0.5);
        ASSERT_EQ(shooter.canShoot(), false);
        shooter.update(0.5);
        ASSERT_EQ(shooter.canShoot(), false);
    }
}
