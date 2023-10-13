#pragma once

#include "ECS.hpp"

namespace rtype::component {
struct BulletInformation {
    BulletInformation(int type_ = 0)
        : type(type_) {};
    ~BulletInformation() = default;

    BulletInformation(const BulletInformation& other) = default;
    BulletInformation& operator=(const BulletInformation& other) = default;

    int type = 0;
};
}
