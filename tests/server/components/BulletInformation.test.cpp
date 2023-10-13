#include "BulletInformation.hpp"

#include <gtest/gtest.h>

TEST(BulletInformation, constructor)
{
    rtype::component::BulletInformation bulletInformation;

    ASSERT_EQ(bulletInformation.type, 0);
}

TEST(BulletInformation, constructor_with_parameters)
{
    rtype::component::BulletInformation bulletInformation(42);

    ASSERT_EQ(bulletInformation.type, 42);
}

TEST(BulletInformation, copy_constructor)
{
    rtype::component::BulletInformation bulletInformation(42);
    rtype::component::BulletInformation bulletInformation2(bulletInformation);

    ASSERT_EQ(bulletInformation2.type, 42);
}

TEST(BulletInformation, equal_operator)
{
    rtype::component::BulletInformation bulletInformation(42);
    rtype::component::BulletInformation bulletInformation2;

    bulletInformation2 = bulletInformation;
    ASSERT_EQ(bulletInformation2.type, 42);
}

TEST(BulletInformation, not_equal_operator)
{
    rtype::component::BulletInformation bulletInformation(42);
    rtype::component::BulletInformation bulletInformation2;

    ASSERT_NE(bulletInformation2.type, 42);
}

TEST(BulletInformation, move)
{
    rtype::component::BulletInformation bulletInformation(42);
    rtype::component::BulletInformation bulletInformation2(std::move(bulletInformation));

    ASSERT_EQ(bulletInformation2.type, 42);
}

TEST(BulletInformation, move_operator)
{
    rtype::component::BulletInformation bulletInformation(42);
    rtype::component::BulletInformation bulletInformation2;

    bulletInformation2 = std::move(bulletInformation);
    ASSERT_EQ(bulletInformation2.type, 42);
}
