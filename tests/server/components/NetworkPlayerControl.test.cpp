#include "NetworkPlayerControl.hpp"

#include <gtest/gtest.h>

TEST(NetworkPlayerControl, constructor)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;

    ASSERT_EQ(networkPlayerControl.up.get(), false);
    ASSERT_EQ(networkPlayerControl.down.get(), false);
    ASSERT_EQ(networkPlayerControl.left.get(), false);
    ASSERT_EQ(networkPlayerControl.right.get(), false);
    ASSERT_EQ(networkPlayerControl.shoot.get(), false);
}

TEST(NetworkPlayerControl, toggleBoolWorks)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;

    networkPlayerControl.up.toggle();
    ASSERT_EQ(networkPlayerControl.up.get(), true);
    ASSERT_EQ(networkPlayerControl.up.get(), false);
}

TEST(NetworkPlayerControl, copy)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;
    rtype::component::NetworkPlayerControl networkPlayerControl2(networkPlayerControl);

    ASSERT_EQ(networkPlayerControl2.up.get(), false);
    ASSERT_EQ(networkPlayerControl2.down.get(), false);
    ASSERT_EQ(networkPlayerControl2.left.get(), false);
    ASSERT_EQ(networkPlayerControl2.right.get(), false);
    ASSERT_EQ(networkPlayerControl2.shoot.get(), false);
}

TEST(NetworkPlayerControl, equal_operator)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;
    rtype::component::NetworkPlayerControl networkPlayerControl2;

    networkPlayerControl2 = networkPlayerControl;
    ASSERT_EQ(networkPlayerControl2.up.get(), false);
    ASSERT_EQ(networkPlayerControl2.down.get(), false);
    ASSERT_EQ(networkPlayerControl2.left.get(), false);
    ASSERT_EQ(networkPlayerControl2.right.get(), false);
    ASSERT_EQ(networkPlayerControl2.shoot.get(), false);
}

TEST(NetworkPlayerControl, not_equal_operator)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;
    rtype::component::NetworkPlayerControl networkPlayerControl2;

    ASSERT_NE(networkPlayerControl2.up.get(), true);
    ASSERT_NE(networkPlayerControl2.down.get(), true);
    ASSERT_NE(networkPlayerControl2.left.get(), true);
    ASSERT_NE(networkPlayerControl2.right.get(), true);
    ASSERT_NE(networkPlayerControl2.shoot.get(), true);
}

TEST(NetworkPlayerControl, move)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;
    rtype::component::NetworkPlayerControl networkPlayerControl2(std::move(networkPlayerControl));

    ASSERT_EQ(networkPlayerControl2.up.get(), false);
    ASSERT_EQ(networkPlayerControl2.down.get(), false);
    ASSERT_EQ(networkPlayerControl2.left.get(), false);
    ASSERT_EQ(networkPlayerControl2.right.get(), false);
    ASSERT_EQ(networkPlayerControl2.shoot.get(), false);
}

TEST(NetworkPlayerControl, moveWithValues)
{
    rtype::component::NetworkPlayerControl networkPlayerControl;

    networkPlayerControl.up.toggle();
    networkPlayerControl.down.toggle();
    networkPlayerControl.left.toggle();
    networkPlayerControl.right.toggle();
    networkPlayerControl.shoot.toggle();
    rtype::component::NetworkPlayerControl networkPlayerControl2(std::move(networkPlayerControl));

    ASSERT_EQ(networkPlayerControl2.up.get(), true);
    ASSERT_EQ(networkPlayerControl2.down.get(), true);
    ASSERT_EQ(networkPlayerControl2.left.get(), true);
    ASSERT_EQ(networkPlayerControl2.right.get(), true);
    ASSERT_EQ(networkPlayerControl2.shoot.get(), true);
}
