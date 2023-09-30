/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Controllable.test
*/

#include "Controllable.hpp"

#include <gtest/gtest.h>

TEST(Controllable, initWithValues)
{
    component::Controllable controllable(
        []() {return true;},
        []() {return false;},
        []() {return true;},
        []() {return false;}
    );

    ASSERT_EQ(controllable.is_key_up_pressed(), true);
    ASSERT_EQ(controllable.is_key_down_pressed(), false);
    ASSERT_EQ(controllable.is_key_left_pressed(), true);
    ASSERT_EQ(controllable.is_key_right_pressed(), false);
}

TEST(Controllable, copy)
{
    component::Controllable controllable(
        []() {return true;},
        []() {return false;},
        []() {return true;},
        []() {return false;}
    );
    component::Controllable controllable2(controllable);

    ASSERT_EQ(controllable2.is_key_up_pressed(), true);
    ASSERT_EQ(controllable2.is_key_down_pressed(), false);
    ASSERT_EQ(controllable2.is_key_left_pressed(), true);
    ASSERT_EQ(controllable2.is_key_right_pressed(), false);
}

TEST(Controllable, assignation)
{
    component::Controllable controllable(
        []() {return true;},
        []() {return false;},
        []() {return true;},
        []() {return false;}
    );
    component::Controllable controllable2(
        []() {return false;},
        []() {return true;},
        []() {return false;},
        []() {return true;}
    );

    controllable2 = controllable;
    ASSERT_EQ(controllable2.is_key_up_pressed(), true);
    ASSERT_EQ(controllable2.is_key_down_pressed(), false);
    ASSERT_EQ(controllable2.is_key_left_pressed(), true);
    ASSERT_EQ(controllable2.is_key_right_pressed(), false);
}
