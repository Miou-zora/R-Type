/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Vector.test
*/

#include "Vector.hpp"

#include <gtest/gtest.h>

TEST(Vector, init)
{
    rtype::utils::Vector<int> vector(42, 21);

    ASSERT_EQ(vector.x, 42);
    ASSERT_EQ(vector.y, 21);
}

TEST(Vector, copy)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(vector);

    ASSERT_EQ(vector2.x, 42);
    ASSERT_EQ(vector2.y, 21);
}

TEST(Vector, assign)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = vector;
    ASSERT_EQ(vector2.x, 42);
    ASSERT_EQ(vector2.y, 21);
}

TEST(Vector, add)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = vector + vector;
    ASSERT_EQ(vector2.x, 84);
    ASSERT_EQ(vector2.y, 42);
}

TEST(Vector, sub)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(1, 1);

    vector2 = vector - vector2;
    ASSERT_EQ(vector2.x, 41);
    ASSERT_EQ(vector2.y, 20);
}

TEST(Vector, mul)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(2, 2);

    vector2 = vector * vector2;
    ASSERT_EQ(vector2.x, 84);
    ASSERT_EQ(vector2.y, 42);
}

TEST(Vector, div)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(2, 2);

    vector2 = vector / vector2;
    ASSERT_EQ(vector2.x, 21);
    ASSERT_EQ(vector2.y, 10);
}

TEST(Vector, mul2)
{
    rtype::utils::Vector<int> vector(42, 21);

    vector = vector * 2;
    ASSERT_EQ(vector.x, 84);
    ASSERT_EQ(vector.y, 42);
}

TEST(Vector, div2)
{
    rtype::utils::Vector<int> vector(42, 21);

    vector = vector / 2;
    ASSERT_EQ(vector.x, 21);
    ASSERT_EQ(vector.y, 10);
}

TEST(Vector, addAssign)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 += vector;
    ASSERT_EQ(vector2.x, 42);
    ASSERT_EQ(vector2.y, 21);
}

TEST(Vector, subAssign)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(1, 1);

    vector2 -= vector;
    ASSERT_EQ(vector2.x, -41);
    ASSERT_EQ(vector2.y, -20);
}

TEST(Vector, mulAssign)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(2, 2);

    vector2 *= vector;
    ASSERT_EQ(vector2.x, 84);
    ASSERT_EQ(vector2.y, 42);
}

TEST(Vector, divAssign)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(2, 2);

    vector /= vector2;
    ASSERT_EQ(vector.x, 21);
    ASSERT_EQ(vector.y, 10);
}

TEST(Vector, mulAssign2)
{
    rtype::utils::Vector<int> vector(42, 21);

    vector *= 2;
    ASSERT_EQ(vector.x, 84);
    ASSERT_EQ(vector.y, 42);
}


TEST(Vector, divAssign2)
{
    rtype::utils::Vector<int> vector(42, 21);

    vector /= 2;
    ASSERT_EQ(vector.x, 21);
    ASSERT_EQ(vector.y, 10);
}

TEST(Vector, equal)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(42, 21);

    ASSERT_EQ(vector, vector2);
}

TEST(Vector, notEqual)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    ASSERT_NE(vector, vector2);
}

TEST(Vector, less)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    ASSERT_LT(vector2, vector);
}

TEST(Vector, lessEqual)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);
    rtype::utils::Vector<int> vector3(42, 21);

    ASSERT_LE(vector2, vector);
    ASSERT_LE(vector3, vector);
}

TEST(Vector, greater)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    ASSERT_GT(vector, vector2);
}

TEST(Vector, greaterEqual)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);
    rtype::utils::Vector<int> vector3(42, 21);

    ASSERT_GE(vector, vector2);
    ASSERT_GE(vector3, vector);
}

TEST(Vector, ostream)
{
    rtype::utils::Vector<int> vector(42, 21);
    std::stringstream ss;

    ss << vector;
    ASSERT_EQ(ss.str(), "(42, 21)");
}

TEST(Vector, getLength)
{
    rtype::utils::Vector<int> vector(42, 21);

    ASSERT_EQ(vector.getLength(), static_cast<int>(std::sqrt(std::pow(42, 2) + std::pow(21, 2))));
}

TEST(Vector, normalized)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = vector.normalized();
    ASSERT_EQ(vector2.x, 42 / vector.getLength());
    ASSERT_EQ(vector2.y, 21 / vector.getLength());
}

TEST(Vector, distance)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(21, 100);

    int distance = std::sqrt(std::pow(42 - 21, 2) + std::pow(21 - 100, 2));

    ASSERT_EQ(vector.distance(vector2), distance);
}

TEST(Vector, getVector)
{
    rtype::utils::Vector<int> vector(42, 21);
    rtype::utils::Vector<int> vector2(21, 100);
    rtype::utils::Vector<int> vector3(0, 0);

    vector3 = rtype::utils::Vector<int>::getVector(vector, vector2);
    ASSERT_EQ(vector3.x, 21 - 42);
    ASSERT_EQ(vector3.y, 100 - 21);
}

TEST(Vector, operatorDiv)
{
    rtype::utils::Vector<int> vector(10, 10);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = 100 / vector;
    ASSERT_EQ(vector2.x, 100 / vector.getLength());
    ASSERT_EQ(vector2.y, 100 / vector.getLength());
}

TEST(Vector, operatorMul)
{
    rtype::utils::Vector<int> vector(10, 10);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = 100 * vector;
    ASSERT_EQ(vector2.x, 100 * vector.getLength());
    ASSERT_EQ(vector2.y, 100 * vector.getLength());
}

TEST(Vector, operatorPlus)
{
    rtype::utils::Vector<int> vector(10, 10);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = 100 + vector;
    ASSERT_EQ(vector2.x, 100 + vector.getLength());
    ASSERT_EQ(vector2.y, 100 + vector.getLength());
}

TEST(Vector, operatorMinus)
{
    rtype::utils::Vector<int> vector(10, 10);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = 100 - vector;
    ASSERT_EQ(vector2.x, 100 - vector.getLength());
    ASSERT_EQ(vector2.y, 100 - vector.getLength());
}

TEST(Vector, minusConversion)
{
    rtype::utils::Vector<int> vector(10, 10);
    rtype::utils::Vector<int> vector2(0, 0);

    vector2 = -vector;
    ASSERT_EQ(vector2.x, -vector.x);
    ASSERT_EQ(vector2.y, -vector.y);
}
