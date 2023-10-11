/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Scroll.test
*/

#include <gtest/gtest.h>
#include "Scroll.hpp"

class TestDeltaTimeProvider : public rtype::ecs::IDeltaTimeProvider
{
public:
    TestDeltaTimeProvider(float dt) : m_deltaTime(dt){};
    ~TestDeltaTimeProvider() = default;

    float getDeltaTime(void) override
    {
        return m_deltaTime;
    }
    float m_deltaTime = 0.1;
};

TEST(Scroll, init)
{
    rtype::system::Scroll scroll;
}

TEST(Scroll, casualUse)
{
    rtype::ecs::Registry registry(std::make_shared<TestDeltaTimeProvider>(1.5));

    registry.registerComponent<rtype::component::Drawable>();
    registry.registerComponent<rtype::component::Scrollable>();

    registry.addSystem<rtype::component::Drawable, rtype::component::Scrollable>(rtype::system::Scroll());

    auto entity = registry.spawnEntity();

    registry.addComponent<rtype::component::Drawable>(entity, rtype::component::Drawable(rtype::component::Drawable::NO_TEXTURE, 1, rtype::utils::Rectangle(0, 0, 100, 100)));
    registry.addComponent<rtype::component::Scrollable>(entity, rtype::component::Scrollable(rtype::utils::Vector<float>(50, 50)));

    registry.runSystems();
    {
        auto &drawable = registry.getComponents<rtype::component::Drawable>()[entity].value();
        auto &scrollable = registry.getComponents<rtype::component::Scrollable>()[entity].value();

        ASSERT_EQ(drawable.sourceRectangle.rectangle.x, 75);
        ASSERT_EQ(drawable.sourceRectangle.rectangle.y, 75);
    }
    registry.runSystems();
    {
        auto &drawable = registry.getComponents<rtype::component::Drawable>()[entity].value();
        auto &scrollable = registry.getComponents<rtype::component::Scrollable>()[entity].value();

        ASSERT_EQ(drawable.sourceRectangle.rectangle.x, 50);
        ASSERT_EQ(drawable.sourceRectangle.rectangle.y, 50);
    }
    registry.runSystems();
    {
        auto &drawable = registry.getComponents<rtype::component::Drawable>()[entity].value();
        auto &scrollable = registry.getComponents<rtype::component::Scrollable>()[entity].value();

        ASSERT_EQ(drawable.sourceRectangle.rectangle.x, 25);
        ASSERT_EQ(drawable.sourceRectangle.rectangle.y, 25);
    }
    registry.runSystems();
    {
        auto &drawable = registry.getComponents<rtype::component::Drawable>()[entity].value();
        auto &scrollable = registry.getComponents<rtype::component::Scrollable>()[entity].value();

        ASSERT_EQ(drawable.sourceRectangle.rectangle.x, 0);
        ASSERT_EQ(drawable.sourceRectangle.rectangle.y, 0);
    }
}
