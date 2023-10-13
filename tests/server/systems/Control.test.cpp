#include <boost/asio.hpp>

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerControl.hpp"
#include "Speed.hpp"
#include "Vector.hpp"
#include "Velocity.hpp"
#include "server/systems/Control.hpp"
#include "IDeltaTimeProvider.hpp"
#include <gtest/gtest.h>

void registerRegistryComponents(rtype::ecs::Registry& registry)
{
    registry.registerComponent<rtype::component::NetworkPlayerControl>();
    registry.registerComponent<rtype::component::Velocity>();
    registry.registerComponent<rtype::component::Transform>();
    registry.registerComponent<rtype::component::Speed>();
}

TEST(Control, noEntity)
{
    rtype::ecs::Registry registry;
    registerRegistryComponents(registry);
    registry.addSystem<rtype::component::NetworkPlayerControl, rtype::component::Velocity, rtype::component::Speed>(rtype::system::Control());
    registry.runSystems();
}

TEST(Control, basicTests)
{
    rtype::ecs::Registry registry;
    registerRegistryComponents(registry);
    registry.addSystem<rtype::component::NetworkPlayerControl, rtype::component::Velocity, rtype::component::Speed>(rtype::system::Control());
    rtype::ecs::Entity entity = registry.spawnEntity();
    registry.emplaceComponent<rtype::component::NetworkPlayerControl>(entity);
    registry.emplaceComponent<rtype::component::Velocity>(entity, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::component::Speed>(entity, 10);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Velocity>()[entity].value().vector, rtype::utils::Vector<float>(0, 0));
}

class MockDeltaTimeProvider : virtual public rtype::ecs::IDeltaTimeProvider {
public:
    MockDeltaTimeProvider() = default;
    ~MockDeltaTimeProvider() = default;

    float getDeltaTime(void) override
    {
        return 0.1;
    }
};

TEST(Control, basicMovement)
{
    rtype::ecs::Registry registry;
    registerRegistryComponents(registry);
    registry.setDeltaTimeProvider(std::make_unique<MockDeltaTimeProvider>());
    registry.addSystem<rtype::component::NetworkPlayerControl, rtype::component::Velocity, rtype::component::Speed>(rtype::system::Control());
    rtype::ecs::Entity entity = registry.spawnEntity();
    rtype::component::NetworkPlayerControl control;
    control.down.toggle();
    registry.emplaceComponent<rtype::component::NetworkPlayerControl>(entity, std::move(control));
    registry.emplaceComponent<rtype::component::Velocity>(entity, rtype::utils::Vector<float>(0, 0));
    registry.emplaceComponent<rtype::component::Transform>(entity);
    registry.emplaceComponent<rtype::component::Speed>(entity, 10);
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Velocity>()[entity].value().vector, rtype::utils::Vector<float>(0, 1));
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[entity].value().position, rtype::utils::Vector<float>(0, 0));
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Velocity>()[entity].value().vector, rtype::utils::Vector<float>(0, 0));
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[entity].value().position, rtype::utils::Vector<float>(0, 0));
    control.down.toggle();
    registry.runSystems();
    ASSERT_EQ(registry.getComponents<rtype::component::Velocity>()[entity].value().vector, rtype::utils::Vector<float>(0, 0));
    ASSERT_EQ(registry.getComponents<rtype::component::Transform>()[entity].value().position, rtype::utils::Vector<float>(0, 0));
}
