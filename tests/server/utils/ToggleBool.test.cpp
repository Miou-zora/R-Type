#include "ECS.hpp"
#include "ToggleBool.hpp"

#include <gtest/gtest.h>

TEST(ToggleBool, toggle)
{
    rtype::utils::ToggleBool toggle;

    ASSERT_EQ(toggle.get(), false);
    toggle.toggle();
    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
}

TEST(ToggleBool, creator)
{
    rtype::utils::ToggleBool toggle(true);

    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    toggle.toggle();
    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
}

TEST(ToggleBool, copy)
{
    rtype::utils::ToggleBool toggle(true);
    rtype::utils::ToggleBool toggle2(toggle);

    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), true);
    ASSERT_EQ(toggle2.get(), false);
    toggle.toggle();
    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
}

TEST(ToggleBool, copy_assignment)
{
    rtype::utils::ToggleBool toggle(true);
    rtype::utils::ToggleBool toggle2(false);

    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
    ASSERT_EQ(toggle2.get(), false);
    toggle2 = toggle;
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle.get(), false);
    toggle.toggle();
    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
}

TEST(ToggleBool, move)
{
    rtype::utils::ToggleBool toggle(true);
    rtype::utils::ToggleBool toggle2(std::move(toggle));

    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), true);
    ASSERT_EQ(toggle2.get(), false);
    toggle.toggle();
    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
}

TEST(ToggleBool, move_assignment)
{
    rtype::utils::ToggleBool toggle(true);
    rtype::utils::ToggleBool toggle2(false);

    ASSERT_EQ(toggle.get(), true);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
    ASSERT_EQ(toggle2.get(), false);
    toggle2 = std::move(toggle);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle.get(), false);
    ASSERT_EQ(toggle2.get(), false);
}
