/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Animator.test
*/

#include "Animator.hpp"

#include <gtest/gtest.h>

class TestDeltaTimeProvider: public rtype::ecs::IDeltaTimeProvider
{
public:
    TestDeltaTimeProvider(float dt): m_deltaTime(dt) {};
    ~TestDeltaTimeProvider() = default;

    float getDeltaTime(void) override
    {
        return m_deltaTime;
    }
    float m_deltaTime = 0.1;
};

TEST(Animator, init)
{
    rtype::system::Animator animator;
}

TEST(Animator, noAnimation)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(0.5));

    registry.registerComponent<rtype::component::Animation>();
    registry.registerComponent<rtype::component::Drawable>();
    registry.addSystem<rtype::component::Animation, rtype::component::Drawable>(rtype::system::Animator());

    auto entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::Drawable>(entity);
    registry.emplaceComponent<rtype::component::Animation>(entity);
    {
        rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
        animator.currentFrame = 0;
        animator.time = 0;
        animator.loop = false;
        animator.finished = false;
        animator.playing = true;
    }
    registry.runSystems();
    rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, true);
    ASSERT_EQ(animator.playing, false);

    animator.playing = true;
    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, true);
    ASSERT_EQ(animator.playing, false);
}

TEST(Animator, casualUse)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(0.5));

    registry.registerComponent<rtype::component::Animation>();
    registry.registerComponent<rtype::component::Drawable>();
    registry.addSystem<rtype::component::Animation, rtype::component::Drawable>(rtype::system::Animator());

    auto entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::Drawable>(entity);
    registry.emplaceComponent<rtype::component::Animation>(entity);
    {
        rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
        animator.currentFrame = 0;
        animator.time = 0;
        animator.loop = false;
        animator.finished = false;
        animator.playing = false;
        animator.framesPosition.push_back(rtype::utils::Vector<int>(10, 10));
        animator.frameTimes.push_back(1);
        animator.framesPosition.push_back(rtype::utils::Vector<int>(20, 20));
        animator.frameTimes.push_back(1);
    }
    registry.runSystems();
    rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, false);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 0);

    animator.playing = true;
    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.5f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 10);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 10);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 1);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 1);
    ASSERT_EQ(animator.time, 0.5f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, true);
    ASSERT_EQ(animator.playing, false);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, false);
    ASSERT_EQ(animator.finished, true);
    ASSERT_EQ(animator.playing, false);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);
}

TEST(Animator, casualUseLooping)
{
    rtype::ecs::Registry registry(std::make_unique<TestDeltaTimeProvider>(0.5));

    registry.registerComponent<rtype::component::Animation>();
    registry.registerComponent<rtype::component::Drawable>();
    registry.addSystem<rtype::component::Animation, rtype::component::Drawable>(rtype::system::Animator());

    auto entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::Drawable>(entity);
    registry.emplaceComponent<rtype::component::Animation>(entity);
    {
        rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
        animator.currentFrame = 0;
        animator.time = 0;
        animator.loop = true;
        animator.finished = false;
        animator.playing = false;
        animator.framesPosition.push_back(rtype::utils::Vector<int>(10, 10));
        animator.frameTimes.push_back(1);
        animator.framesPosition.push_back(rtype::utils::Vector<int>(20, 20));
        animator.frameTimes.push_back(1);
    }
    registry.runSystems();
    rtype::component::Animation &animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0);
    ASSERT_EQ(animator.loop, true);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, false);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 0);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 0);

    animator.playing = true;
    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.5f);
    ASSERT_EQ(animator.loop, true);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 10);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 10);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 1);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, true);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 1);
    ASSERT_EQ(animator.time, 0.5f);
    ASSERT_EQ(animator.loop, true);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 20);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 20);

    registry.runSystems();
    animator = registry.getComponents<rtype::component::Animation>()[0].value();
    ASSERT_EQ(animator.currentFrame, 0);
    ASSERT_EQ(animator.time, 0.f);
    ASSERT_EQ(animator.loop, true);
    ASSERT_EQ(animator.finished, false);
    ASSERT_EQ(animator.playing, true);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.x, 10);
    ASSERT_EQ(registry.getComponents<rtype::component::Drawable>()[entity]->sourceRectangle.rectangle.y, 10);
}
