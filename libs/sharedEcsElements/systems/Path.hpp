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
                rtype::utils::Vector<float> vectorToNextPoint = rtype::utils::Vector<float>::getVector(transformable.value().position, targetPoint.first);
                if (targetPoint.second == rtype::component::Path::Referential::Entity)
                    vectorToNextPoint = targetPoint.first;
                _updatePath(transformable.value(), velocity.value(), path.value(), targetPoint, deltaTime * path->speed, registry, index, vectorToNextPoint);
            }
        }

    private:
        void _updatePath(rtype::component::Transform &transformable, rtype::component::Velocity &velocity, rtype::component::Path &path,
                         rtype::component::Path::Point &targetPoint, float lengthToTravel, ecs::Registry &registry, int index, rtype::utils::Vector<float> &vectorToNextPoint) const
        {
            while (lengthToTravel > 0 && !path.listOfPoints.empty())
            {
                // if length to travel > the distance to the next point
                if (targetPoint.first.distance(transformable.position) >= (vectorToNextPoint.normalized() * lengthToTravel).getLength())
                {
                    velocity.vector += vectorToNextPoint.normalized() * lengthToTravel;
                    lengthToTravel = 0;
                    if (targetPoint.second == rtype::component::Path::Referential::Entity)
                        targetPoint.first -= velocity.vector;
                }
                else // if length to travel < the distance to the next point
                {
                    if (path.listOfPoints.size() == 1)
                    {
                        velocity.vector += vectorToNextPoint;
                        lengthToTravel = 0;
                        if (targetPoint.second == rtype::component::Path::Referential::Entity)
                            targetPoint.first -= vectorToNextPoint;
                    }
                    else
                    {
                        velocity.vector += vectorToNextPoint;
                        lengthToTravel -= vectorToNextPoint.getLength();
                        vectorToNextPoint = rtype::utils::Vector<float>::getVector(transformable.position + velocity.vector, path.listOfPoints[1].first);
                        path.listOfPoints.erase(path.listOfPoints.begin());
                        targetPoint = path.listOfPoints[0];
                        if (targetPoint.second == rtype::component::Path::Referential::Entity)
                            vectorToNextPoint = targetPoint.first;
                    }
                }
                if (rtype::component::Path::Referential::Entity == targetPoint.second && targetPoint.first.getLength() == 0)
                    path.listOfPoints.erase(path.listOfPoints.begin());
                if (rtype::component::Path::Referential::World == targetPoint.second && std::abs((targetPoint.first).distance(transformable.position + velocity.vector)) == 0)
                    path.listOfPoints.erase(path.listOfPoints.begin());
            }
            if (path.listOfPoints.empty() && path.destroyAtEnd) {
                registry.killEntity(registry.entityFromIndex(index));
            }
        }
    };
}
