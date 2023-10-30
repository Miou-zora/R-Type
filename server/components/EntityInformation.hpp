#pragma once

#include "ECS.hpp"

namespace rtype::component
{
    /**
     * @brief Component that contains the type of the entity
    */
    struct EntityInformation
    {
        EntityInformation(int type_ = 0)
            : type(type_){};
        ~EntityInformation() = default;

        EntityInformation(const EntityInformation &other) = default;
        EntityInformation &operator=(const EntityInformation &other) = default;

        int type = 0;
    };
}
