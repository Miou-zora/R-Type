#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <ctime>

#include "ECS.hpp"
#include "NetworkServerTickSystem.hpp"
#include "NetworkPlayerHandlerSystem.hpp"
#include "NetworkServerInboxDispatcher.hpp"
#include "NetworkServerOutboxDispatcher.hpp"
#include "NetworkServer.hpp"
#include "NetworkPlayer.hpp"
#include "GameRoom.hpp"
#include "GameLevel.hpp"

#include "NetworkMessageQueue.hpp"

int main(int ac, char *av[])
{
    rtype::ecs::Registry reg;
    rtype::ecs::Entity entity = reg.spawnEntity();

    reg.registerComponent<rtype::component::NetworkServer>();
    reg.registerComponent<rtype::component::NetworkPlayer>();
    reg.registerComponent<rtype::component::GameRoom>();
    reg.registerComponent<rtype::component::GameLevel>();
    reg.emplaceComponent<rtype::component::NetworkServer>(entity, 12345);
    reg.addSystem<rtype::component::NetworkServer, rtype::component::NetworkPlayer>(rtype::system::NetworkServerInboxDispatcher());
    reg.addSystem<rtype::component::NetworkServer, rtype::component::NetworkPlayer>(rtype::system::NetworkServerOutboxDispatcher());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkPlayerHandlerSystem());
    reg.addSystem<rtype::component::NetworkServer>(rtype::system::NetworkServerTickSystem(64)); // should be put last

    while (true) {
        reg.runSystems();
    }
    return 0;
}
