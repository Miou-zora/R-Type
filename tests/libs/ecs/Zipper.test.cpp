/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TestsZipper
*/

#include "Zipper.hpp"
#include "SparseArray.hpp"

#include <gtest/gtest.h>

TEST(Zipper, init)
{
    rtype::ecs::SparseArray<int> sa;
    sa.insertAt(0, 1);
    sa.insertAt(1, 2);
    sa.insertAt(2, 3);
    sa.insertAt(3, 4);
    sa.insertAt(4, 5);
    rtype::ecs::SparseArray<int> sa2;
    sa2.insertAt(0, 6);
    sa2.insertAt(1, 7);
    sa2.insertAt(2, 8);
    sa2.insertAt(3, 9);
    sa2.insertAt(4, 10);
    rtype::ecs::SparseArray<int> sa3;
    sa3.insertAt(0, 11);
    sa3.insertAt(1, 12);
    sa3.insertAt(2, 13);
    sa3.insertAt(3, 14);
    sa3.insertAt(4, 15);
    rtype::ecs::containers::Zipper<rtype::ecs::SparseArray<int>, rtype::ecs::SparseArray<int>, rtype::ecs::SparseArray<int>> iz(sa, sa2, sa3);
    EXPECT_EQ(std::get<0>(*(iz.begin())).value(), 1);
    EXPECT_EQ(std::get<1>(*(iz.begin())).value(), 6);
    EXPECT_EQ(std::get<2>(*(iz.begin())).value(), 11);

    EXPECT_EQ(std::get<0>(*(++++++++iz.begin())).value(), 5);
    EXPECT_EQ(std::get<1>(*(++++++++iz.begin())).value(), 10);
    EXPECT_EQ(std::get<2>(*(++++++++iz.begin())).value(), 15);
}

TEST(Zipper, forEach)
{
    rtype::ecs::SparseArray<int> sa;
    sa.insertAt(0, 1);
    sa.insertAt(1, 2);
    sa.insertAt(2, 3);
    sa.insertAt(3, 4);
    sa.insertAt(4, 5);
    rtype::ecs::SparseArray<int> sa2;
    sa2.insertAt(0, 6);
    sa2.insertAt(1, 7);
    sa2.insertAt(2, 8);
    sa2.insertAt(3, 9);
    sa2.insertAt(4, 10);
    rtype::ecs::SparseArray<int> sa3;
    sa3.insertAt(0, 11);
    sa3.insertAt(1, 12);
    sa3.insertAt(2, 13);
    sa3.insertAt(3, 14);
    sa3.insertAt(4, 15);
    int i = 0;
    for (auto &&[value1, value2, value3]: rtype::ecs::containers::Zipper(sa, sa2, sa3))
    {
        EXPECT_EQ(value1.value(), i + 1);
        EXPECT_EQ(value2.value(), i + 6);
        EXPECT_EQ(value3.value(), i + 11);
        i++;
    }
}

TEST(Zipper, forEachWithEmptyValue)
{
    rtype::ecs::SparseArray<int> sa;
    sa.insertAt(0, 1);
    sa.insertAt(1, 2);
    sa.insertAt(2, 3);
    sa.insertAt(3, 4);
    sa.insertAt(4, 5);
    sa.insertAt(5, 4324);
    sa.erase(5);
    rtype::ecs::SparseArray<int> sa2;
    sa2.insertAt(0, 6);
    sa2.insertAt(1, 7);
    sa2.insertAt(3, 9);
    sa2.insertAt(4, 10);
    sa2.insertAt(5, 4324);
    sa2.erase(5);
    rtype::ecs::SparseArray<int> sa3;
    sa3.insertAt(0, 11);
    sa3.insertAt(1, 12);
    sa3.insertAt(2, 13);
    sa3.insertAt(3, 14);
    sa3.insertAt(4, 15);
    sa3.insertAt(5, 4324);
    sa3.erase(5);
    int i = 0;
    for (auto &&[value1, value2, value3]: rtype::ecs::containers::Zipper(sa, sa2, sa3))
    {
        EXPECT_EQ(value1.value(), i + 1);
        EXPECT_EQ(value2.value(), i + 6);
        EXPECT_EQ(value3.value(), i + 11);
        if (i == 1)
            i++;
        i++;
    }
}
