/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Animator
*/

#pragma once

#include "Animation.hpp"
#include "Drawable.hpp"
#include "ECS.hpp"

namespace rtype::system {
/**
 * @brief Animator system used to update the animations
 */
class Animator {
public:
    Animator() = default;
    ~Animator() = default;

    void operator()(rtype::ecs::Registry& registry,
        rtype::ecs::SparseArray<rtype::component::Animation>& animations,
        rtype::ecs::SparseArray<rtype::component::Drawable>& drawables) const
    {
        for (auto&& [index, animation, drawable] : ecs::containers::IndexedZipper(animations, drawables)) {
            if (!animation.value().playing)
                continue;
            updateAnimation(registry, animation.value(), drawable.value(), index);
        }
    }

private:
    void updateAnimation(rtype::ecs::Registry& registry,
        rtype::component::Animation& animation,
        rtype::component::Drawable& drawable,
        std::size_t index) const
    {
        if (animation.frameTimes.size() <= animation.currentFrame) {
            if (!animation.loop) {
                animation.finished = true;
                animation.playing = false;
            }
            return;
        }
        animation.time += registry.getDeltaTime();
        if (animation.time >= animation.frameTimes[animation.currentFrame]) {
            animation.time -= animation.frameTimes[animation.currentFrame];
            animation.currentFrame++;
            if (animation.currentFrame >= animation.framesPosition.size()) {
                if (animation.loop) {
                    animation.currentFrame = 0;
                } else {
                    animation.currentFrame = 0;
                    animation.time = 0;
                    animation.playing = false;
                    animation.finished = true;
                    if (animation.killWhenFinished)
                        registry.killEntity(registry.entityFromIndex(index));
                    return;
                }
            }
        }
        drawable.sourceRectangle.rectangle.x = animation.framesPosition[animation.currentFrame].x;
        drawable.sourceRectangle.rectangle.y = animation.framesPosition[animation.currentFrame].y;
    }
};
}
