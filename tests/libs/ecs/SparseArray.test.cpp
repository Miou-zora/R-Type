/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** test_SparseArray
*/

#include "SparseArray.hpp"

#include <gtest/gtest.h>

TEST(SparseArray, init)
{
    rtype::ecs::SparseArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(SparseArray, insert_at)
{
    rtype::ecs::SparseArray<int> arr;

    // extends
    arr.insertAt(3, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // add value in empty place
    arr.insertAt(1, 21);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value(), 21);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // modify value
    arr.insertAt(1, 84);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value(), 84);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);
}

TEST(SparseArray, emplace_at)
{
    class A
    {
    public:
        A(int _a, int _b) : a(_a), b(_b) {}
        int a;
        int b;
    };

    rtype::ecs::SparseArray<A> arr;

    // extends
    arr.emplaceAt(3, std::in_place, 42, 21);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // add value in empty place
    arr.emplaceAt(1, std::in_place, 21, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value().a, 21);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // modify value
    arr.emplaceAt(1, std::in_place, 84, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].value().a, 84);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);

    // add value with move
    A value(1024, 2048);
    arr.emplaceAt(0, std::move(value));
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].value().a, 1024);
    EXPECT_EQ(arr[0].value().b, 2048);
    EXPECT_EQ(arr[1].value().a, 84);
    EXPECT_EQ(arr[1].value().b, 42);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value().a, 42);
    EXPECT_EQ(arr[3].value().b, 21);
}

TEST(SparseArray, erase)
{
    rtype::ecs::SparseArray<int> arr;

    // extends
    arr.insertAt(3, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // erase
    arr.erase(3);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].has_value(), false);

    // erase at empty place
    arr.erase(1);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].has_value(), false);

    // erase at an index bigger than the size of the array
    try {
        arr.erase(4);
        FAIL();
    } catch (std::out_of_range const &e) {  // TODO: throw a proper exception
        EXPECT_STREQ(e.what(), "SparseArray::erase");
    }
}

TEST(SparseArray, get_index)
{
    rtype::ecs::SparseArray<int> arr;

    // extends
    arr.insertAt(3, 42);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].has_value(), false);
    EXPECT_EQ(arr[1].has_value(), false);
    EXPECT_EQ(arr[2].has_value(), false);
    EXPECT_EQ(arr[3].value(), 42);

    // get index
    EXPECT_EQ(arr.getIndex(arr[3]), 3);
    EXPECT_EQ(arr.getIndex(arr[2]), 2);
    EXPECT_EQ(arr.getIndex(arr[1]), 1);
    EXPECT_EQ(arr.getIndex(arr[0]), 0);
}
