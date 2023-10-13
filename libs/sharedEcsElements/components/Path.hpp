/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Path
*/

#pragma once

#include <vector>
#include <memory>
#include <ctime>
#include <cmath>
#include "Vector.hpp"
#include "ECS.hpp"

namespace rtype::component
{
    /**
     * @brief Path component. Used to move an entity along a Path. The Path is a list of points. The entity will move from one point to another at a constant speed.
     */
    struct Path
    {
        /**
         * @brief Context of the point. Global means that when you add a point, it will be added as world position.
         * Local means that when you add a point, it will be added as a local position to the last point added.
        */
        enum class Context
        {
            Global,
            Local
        };

        /**
         * @brief Referential of the point. World means that the point is in world position and will be updated using the world position of the entity.
         * Entity means that the point is in local position and will be updated using the current position of the entity.
        */
        enum class Referential
        {
            World,
            Entity
        };

        /**
         * @brief Type of the path. OneShot means that the entity will stop at the end of the path.
         * Loop means that the entity will restart at the beginning of the path.
        */
        enum class Type
        {
            OneShot,
            Loop
        };

        using PointType = float;
        typedef struct Point {
            Point(const rtype::utils::Vector<PointType> &point, Path::Referential referential) : vector(point), referential(referential), startVector(point) {};
            rtype::utils::Vector<PointType> vector;
            Path::Referential referential;
            rtype::utils::Vector<PointType> startVector;
        } Point;
        // using Point = std::pair<rtype::utils::Vector<PointType>, Path::Referential>;

        /**
         * @brief Construct a new Path object using speed, a list of points and a boolean to know if the entity should be destroyed at the end of the path.
         * The path will be only a direct line between the points.
         *
         * @param speed_ Speed of the entity along the path. It will be constant except if the user or system change it.
         * @param path_ List of points to follow.
         * @param destroyAtEnd_ Boolean to know if the entity should be destroyed at the end of the path.
        */
        Path(float speed_ = 100, const std::vector<Point> &path_ = std::vector<Point>(), bool destroyAtEnd_ = false, Type type_ = Type::OneShot) : listOfPoints(path_), speed(speed_), destroyAtEnd(destroyAtEnd_), type(type_){};

        /**
         * @brief Construct a new Path object using speed and a boolean to know if the entity should be destroyed at the end of the path.
         * The path will be only a direct line between the points.
         *
         * @param speed_ Speed of the entity along the path. It will be constant except if the user or system change it.
         * @param destroyAtEnd_ Boolean to know if the entity should be destroyed at the end of the path.
        */
        Path(float speed_, bool destroyAtEnd_) : speed(speed_), destroyAtEnd(destroyAtEnd_){};
        ~Path(void) = default;
        Path(const Path &other) = default;
        Path &operator=(const Path &other) = default;

        /**
         * @brief Add a point to the path. The point will be added as a global context with world referential as default.
         * The point will be added at the end of the path.
         *
         * @param point Point to add to the path.
         * @param context Context of the point.
         * @param referential Referential of the point.
        */
        Path &addPoint(const rtype::utils::Vector<PointType> &point, Path::Context context = Path::Context::Global, Path::Referential referential = Path::Referential::World)
        {
            if (context == Path::Context::Global)
                listOfPoints.push_back(Point(point, referential));
            else if (context == Path::Context::Local)
            {
                if (listOfPoints.empty())
                    listOfPoints.push_back(Point(point, referential));
                else
                    listOfPoints.push_back(Point(listOfPoints.back().vector + point, referential));
            }
            return (*this);
        }

        /**
         * @brief Add a point to the path. The point will be added as a global context with world referential as default.
         *
         * @param x X coordinate of the point. It will be modified depending on the context.
         * @param y Y coordinate of the point. It will be modified depending on the context.
         * @param context Context of the point.
         * @param referential Referential of the point.
        */
        Path &addPoint(PointType x, PointType y, Path::Context context = Path::Context::Global, Path::Referential referential = Path::Referential::World)
        {
            return (addPoint(rtype::utils::Vector<PointType>(x, y), context, referential));
        }

        /**
         * @brief Add a point to the path. The point will be added as a global context with world referential as default.
         *
         * @param point Point to add to the path.
        */
        Path &addPoint(const Point &point)
        {
            listOfPoints.push_back(point);
            return (*this);
        }

        /**
         * @brief Add a path (list of point) to the current path. It will be added at the end of the current path.
         *
         * @param other Path to add to the current path.
        */
        Path &addPoint(const Path &other)
        {
            for (auto &&point : other.listOfPoints)
                addPoint(point);
            return (*this);
        }

        /**
         * @brief Set if the entity should be destroyed at the end of the path.
         *
         * @param destroy Boolean to know if the entity should be destroyed at the end of the path.
         * @return Path& Reference to the current path.
        */
        Path &setDestroyAtEnd(bool destroy)
        {
            destroyAtEnd = destroy;
            return (*this);
        }

        /**
         * @brief Set the speed of the entity along the path.
         *
         * @param speed_ Speed of the entity along the path.
         * @return Path& Reference to the current path.
        */
        Path &setSpeed(float speed_)
        {
            speed = speed_;
            return (*this);
        }

        /**
         * @brief Set the type of the path.
         *
         * @param type_ Type of the path.
         * @return Path& Reference to the current path.
        */
        Path &setType(Type type_)
        {
            type = type_;
            return (*this);
        }

        std::vector<Point> listOfPoints;
        float speed;
        bool destroyAtEnd;
        Type type;
    };
}
