/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Path.test
*/

#include "Path.hpp"

#include <gtest/gtest.h>

TEST(Path, init)
{
    {
        rtype::component::Path path;
        ASSERT_EQ(path.speed, 100);
        ASSERT_EQ(path.listOfPoints.size(), 0);
        ASSERT_EQ(path.destroyAtEnd, false);
    }
    {
        rtype::component::Path path(50);
        ASSERT_EQ(path.speed, 50);
        ASSERT_EQ(path.listOfPoints.size(), 0);
        ASSERT_EQ(path.destroyAtEnd, false);
    }
    {
        rtype::component::Path path(50, true);
        ASSERT_EQ(path.speed, 50);
        ASSERT_EQ(path.listOfPoints.size(), 0);
        ASSERT_EQ(path.destroyAtEnd, true);
    }
    {
        rtype::component::Path::Point point = std::make_pair(rtype::utils::Vector<float>(0, 0), rtype::component::Path::Referential::World);
        rtype::component::Path path(50, {point}, true);
        ASSERT_EQ(path.speed, 50);
        ASSERT_EQ(path.listOfPoints.size(), 1);
        ASSERT_EQ(path.destroyAtEnd, true);
    }
}

TEST(Path, addPoint)
{
    {
        rtype::component::Path path;
        rtype::component::Path::Point point = std::make_pair(rtype::utils::Vector<float>(0, 0), rtype::component::Path::Referential::World);
        path.addPoint(point);
        ASSERT_EQ(path.listOfPoints.size(), 1);
        ASSERT_EQ(path.listOfPoints[0].first, point.first);
        ASSERT_EQ(path.listOfPoints[0].second, point.second);

        rtype::component::Path::Point point2 = std::make_pair(rtype::utils::Vector<float>(1, 1), rtype::component::Path::Referential::World);
        path.addPoint(point2);
        ASSERT_EQ(path.listOfPoints.size(), 2);
        ASSERT_EQ(path.listOfPoints[1].first, point2.first);
        ASSERT_EQ(path.listOfPoints[1].second, point2.second);
    }
    {
        rtype::component::Path path;
        rtype::component::Path::Point point = std::make_pair(rtype::utils::Vector<float>(1, 1), rtype::component::Path::Referential::Entity);
        path.addPoint(point);
        ASSERT_EQ(path.listOfPoints.size(), 1);
        ASSERT_EQ(path.listOfPoints[0].first, point.first);
        ASSERT_EQ(path.listOfPoints[0].second, point.second);

        rtype::utils::Vector<float> point2(1, 1);
        path.addPoint(point2, rtype::component::Path::Context::Local, rtype::component::Path::Referential::Entity);
        ASSERT_EQ(path.listOfPoints.size(), 2);
        ASSERT_EQ(path.listOfPoints[1].first, point2 + point.first);
        ASSERT_EQ(path.listOfPoints[1].second, rtype::component::Path::Referential::Entity);
    }
    {
        rtype::component::Path path;
        path.addPoint(1, 1);
        ASSERT_EQ(path.listOfPoints.size(), 1);
        ASSERT_EQ(path.listOfPoints[0].first, rtype::utils::Vector<float>(1, 1));
        ASSERT_EQ(path.listOfPoints[0].second, rtype::component::Path::Referential::World);
    }
    {
        rtype::component::Path path;
        rtype::utils::Vector<float> point(1, 1);
        path.addPoint(point);
        ASSERT_EQ(path.listOfPoints.size(), 1);
        ASSERT_EQ(path.listOfPoints[0].first, point);
        ASSERT_EQ(path.listOfPoints[0].second, rtype::component::Path::Referential::World);
    }
    {
        rtype::component::Path path1;
        rtype::component::Path path2;

        path1.addPoint(1, 1);
        path2.addPoint(2, 2, rtype::component::Path::Context::Global, rtype::component::Path::Referential::Entity);
        path1.addPoint(path2);
        ASSERT_EQ(path1.listOfPoints.size(), 2);
        ASSERT_EQ(path1.listOfPoints[0].first, rtype::utils::Vector<float>(1, 1));
        ASSERT_EQ(path1.listOfPoints[0].second, rtype::component::Path::Referential::World);
        ASSERT_EQ(path1.listOfPoints[1].first, rtype::utils::Vector<float>(2, 2));
        ASSERT_EQ(path1.listOfPoints[1].second, rtype::component::Path::Referential::Entity);
    }
}

TEST(Path, setDestroyAtEnd)
{
    rtype::component::Path path;
    ASSERT_EQ(path.destroyAtEnd, false);
    path.setDestroyAtEnd(true);
    ASSERT_EQ(path.destroyAtEnd, true);
}
