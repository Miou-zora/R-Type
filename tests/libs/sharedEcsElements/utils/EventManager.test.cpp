/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** EventManager.test
*/

#include "EventManager.hpp"
#include "SingletonWrapper.hpp"

#include <gtest/gtest.h>

TEST(EventManager, init)
{
    rtype::utils::EventManager manager;
}

TEST(EventManager, casualUse)
{
    rtype::utils::EventManager manager;

    struct TestEventA { TestEventA(int a_): a(a_) {}; int a; };
    struct TestEventB { TestEventB(int a_): a(a_) {}; int a; };
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 0);
    manager.addEvent<TestEventA>(std::move(TestEventA(42)));
    manager.addEvent<TestEventA>(std::move(TestEventA(21)));
    manager.addEvent<TestEventB>(84);
    manager.addEvent<TestEventB>(168);
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 2);
    ASSERT_EQ(manager.getEvents<TestEventA>()[0].a, 42);
    ASSERT_EQ(manager.getEvents<TestEventA>()[1].a, 21);
    ASSERT_EQ(manager.getEvents<TestEventB>().size(), 2);
    ASSERT_EQ(manager.getEvents<TestEventB>()[0].a, 84);
    ASSERT_EQ(manager.getEvents<TestEventB>()[1].a, 168);
    manager.clearEvents();
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 0);
    ASSERT_EQ(manager.getEvents<TestEventB>().size(), 0);
}

TEST(EventManager, casualUseSingleton)
{
    rtype::utils::EventManager &manager = rtype::utils::SingletonWrapper<rtype::utils::EventManager>::getInstance();

    struct TestEventA { TestEventA(int a_): a(a_) {}; int a; };
    struct TestEventB { TestEventB(int a_): a(a_) {}; int a; };
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 0);
    manager.addEvent<TestEventA>(std::move(TestEventA(42)));
    manager.addEvent<TestEventA>(std::move(TestEventA(21)));
    manager.addEvent<TestEventB>(84);
    manager.addEvent<TestEventB>(168);
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 2);
    ASSERT_EQ(manager.getEvents<TestEventA>()[0].a, 42);
    ASSERT_EQ(manager.getEvents<TestEventA>()[1].a, 21);
    ASSERT_EQ(manager.getEvents<TestEventB>().size(), 2);
    ASSERT_EQ(manager.getEvents<TestEventB>()[0].a, 84);
    ASSERT_EQ(manager.getEvents<TestEventB>()[1].a, 168);
    manager.clearEvents();
    ASSERT_EQ(manager.getEvents<TestEventA>().size(), 0);
    ASSERT_EQ(manager.getEvents<TestEventB>().size(), 0);
}
