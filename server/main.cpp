#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

#include "ECS.hpp"
#include "GameLevel.hpp"
#include "GameRoom.hpp"
#include "NetworkPlayer.hpp"
#include "NetworkPlayerHandlerSystem.hpp"
#include "NetworkServer.hpp"
#include "NetworkServerInboxDispatcher.hpp"
#include "NetworkServerOutboxDispatcher.hpp"

#include "NetworkMessageQueue.hpp"

int main(int ac, char* av[])
{
    rtype::ecs::Registry reg;
    rtype::ecs::Entity entity = reg.spawnEntity();
    int port = 12345;

    if (ac > 1)
        port = std::stoi(av[1]);
    rtype::network::NetworkServer::initInstance(port);
    reg.registerComponent<rtype::component::NetworkPlayer>();
    reg.registerComponent<rtype::component::GameRoom>();
    reg.registerComponent<rtype::component::GameLevel>();
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkServerInboxDispatcher());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkPlayerHandlerSystem());
    reg.addSystem<rtype::component::NetworkPlayer>(rtype::system::NetworkServerOutboxDispatcher());

    while (true) {
        reg.runSystems();
    }
    return 0;
}
