#pragma once

#include "ECS.hpp"

namespace rtype::component {
struct EnemyInformation {
    EnemyInformation(int type_ = 0)
        : type(type_) {};
    ~EnemyInformation() = default;

    EnemyInformation(const EnemyInformation& other) = default;
    EnemyInformation& operator=(const EnemyInformation& other) = default;

    int type = 0;
};
}
