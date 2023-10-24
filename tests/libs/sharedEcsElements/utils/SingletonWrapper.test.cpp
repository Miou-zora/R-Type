/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** SingletonWrapper.test
*/

#include "SingletonWrapper.hpp"

#include <gtest/gtest.h>

TEST(SingletonWrapper, init)
{
    struct TestEventA { TestEventA(int a_ = 1): a(a_) {}; int a; };
    struct TestEventB { TestEventB(int a_ = 2): a(a_) {}; int a; };
    ASSERT_EQ(rtype::utils::SingletonWrapper<TestEventA>::getInstance().a, 1);
    ASSERT_EQ(rtype::utils::SingletonWrapper<TestEventB>::getInstance().a, 2);
    rtype::utils::SingletonWrapper<TestEventA>::getInstance().a = 42;
    rtype::utils::SingletonWrapper<TestEventB>::getInstance().a = 84;
    ASSERT_EQ(rtype::utils::SingletonWrapper<TestEventA>::getInstance().a, 42);
    ASSERT_EQ(rtype::utils::SingletonWrapper<TestEventB>::getInstance().a, 84);
}
