/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Path
*/

#pragma once

#include "ECS.hpp"
#include "components/Path.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"

namespace rtype::system
{
    class Path
    {
    public:
        Path() = default;
        ~Path() = default;

        void operator()(ecs::Registry &registry,
                        ecs::SparseArray<rtype::component::Transform> &transformables,
                        ecs::SparseArray<rtype::component::Velocity> &velocities,
                        ecs::SparseArray<rtype::component::Path> &paths) const
        {
            float deltaTime = registry.getDeltaTime();
            for (auto &&[index, transformable, velocity, path] : ecs::containers::IndexedZipper(transformables, velocities, paths))
            {
                if (path.value().listOfPoints.empty())
                    continue;
                rtype::component::Path::Point &targetPoint = path.value().listOfPoints[0];
                rtype::utils::Vector<float> vectorToNextPoint = rtype::utils::Vector<float>::getVector(transformable.value().position, targetPoint.vector);
                if (targetPoint.referential == rtype::component::Path::Referential::Entity)
                    vectorToNextPoint = targetPoint.vector;
                _updatePath(transformable.value(), velocity.value(), path.value(), targetPoint, deltaTime * path->speed, registry, index, vectorToNextPoint);
            }
        }

    private:
        void _updatePath(rtype::component::Transform &transformable, rtype::component::Velocity &velocity, rtype::component::Path &path,
                         rtype::component::Path::Point targetPoint, float lengthToTravel, ecs::Registry &registry, int index, rtype::utils::Vector<float> &vectorToNextPoint) const
        {
            while (lengthToTravel > 0.0f && !path.listOfPoints.empty())
            {
                if ((targetPoint.vector.distance(transformable.position) >= (vectorToNextPoint.normalized() * lengthToTravel).getLength() && targetPoint.referential == rtype::component::Path::Referential::World) ||
                    (targetPoint.vector.getLength() >= (vectorToNextPoint.normalized() * lengthToTravel).getLength() && targetPoint.referential == rtype::component::Path::Referential::Entity))
                {
                    velocity.vector += vectorToNextPoint.normalized() * lengthToTravel;
                    lengthToTravel = 0.0f;
                    if (targetPoint.referential == rtype::component::Path::Referential::Entity) {
                        targetPoint.vector -= velocity.vector;
                        path.listOfPoints[0].vector -= velocity.vector;
                    }
                }
                else // if length to travel < the distance to the next point
                {
                    if (path.listOfPoints.size() == 1)
                    {
                        velocity.vector += vectorToNextPoint;
                        lengthToTravel -= vectorToNextPoint.getLength();
                        if (targetPoint.referential == rtype::component::Path::Referential::Entity) {
                            targetPoint.vector -= vectorToNextPoint;
                        }
                    }
                    else
                    {
                        velocity.vector += vectorToNextPoint;
                        lengthToTravel -= vectorToNextPoint.getLength();
                        vectorToNextPoint = rtype::utils::Vector<float>::getVector(transformable.position + velocity.vector, path.listOfPoints[1].vector);
                        if (path.type == rtype::component::Path::Type::Loop)
                            path.listOfPoints.push_back(rtype::component::Path::Point(path.listOfPoints[0].startVector, path.listOfPoints[0].referential));
                        path.listOfPoints.erase(path.listOfPoints.begin());
                        targetPoint = path.listOfPoints[0];
                        if (targetPoint.referential == rtype::component::Path::Referential::Entity)
                            vectorToNextPoint = targetPoint.vector;
                    }
                }
                if (((rtype::component::Path::Referential::Entity == targetPoint.referential && targetPoint.vector.getLength() == 0) ||
                     (rtype::component::Path::Referential::World == targetPoint.referential && std::abs((targetPoint.vector).distance(transformable.position + velocity.vector)) == 0)) &&
                    path.listOfPoints.size())
                {
                    if (path.type == rtype::component::Path::Type::Loop)
                        path.listOfPoints.push_back(rtype::component::Path::Point(path.listOfPoints[0].startVector, path.listOfPoints[0].referential));
                    path.listOfPoints.erase(path.listOfPoints.begin());
                }
            }
            if (path.listOfPoints.empty() && path.destroyAtEnd)
            {
                registry.killEntity(registry.entityFromIndex(index));
            }
        }
    };
}
