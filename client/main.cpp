/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** main
*/

#include "AckSystem.hpp"
#include "Click.hpp"
#include "Client.hpp"
#include "Control.hpp"
#include "Draw.hpp"
#include "NetworkControl.hpp"
#include "NetworkInboxChecker.hpp"
#include "NetworkInboxHandler.hpp"
#include "NetworkOutboxHandler.hpp"
#include "Scroll.hpp"
#include "Selection.hpp"
#include "SwitchScene.hpp"
#include "UpdateRoomInformations.hpp"
#include "VelocityApplicator.hpp"
#include "loads.hpp"
#include "Animator.hpp"
#include "systems/TextInput.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>
namespace raylib {
#include <raylib.h>
}

int main(int ac, char* av[])
{
    raylib::InitWindow(1536, 1024, "Rtype");
    rtype::ecs::Registry reg;

    // add systems
    reg.addSystem<rtype::component::Animation, rtype::component::Drawable>(rtype::system::Animator());
    reg.addSystem<rtype::component::Controllable, rtype::component::Velocity>(rtype::system::Control());
    reg.addSystem<rtype::component::Transform, rtype::component::Velocity>(rtype::system::VelocityApplicator());
    reg.addSystem<>(rtype::system::Draw());
    reg.addSystem<rtype::component::Selectable, rtype::component::Transform, rtype::component::Collider>(rtype::system::Selection());
    reg.addSystem<rtype::component::Selectable, rtype::component::TextInputable, rtype::component::Text>(rtype::system::TextInput());
    reg.addSystem<rtype::component::DebugColliderDisplay, rtype::component::Transform, rtype::component::Collider>(rtype::system::DebugColliderDisplayer());
    reg.addSystem<rtype::component::Clickable, rtype::component::Transform, rtype::component::Collider>(rtype::system::Click());
    reg.addSystem<rtype::component::Drawable, rtype::component::Scrollable>(rtype::system::Scroll());
    reg.addSystem<>(rtype::system::NetworkOutboxHandler());
    reg.addSystem<>(rtype::system::NetworkInboxChecker());
    reg.addSystem<>(rtype::system::NetworkInboxHandler());
    reg.addSystem<>(rtype::system::SwitchScene());
    reg.addSystem<>(rtype::system::AckSystem());
    reg.addSystem<rtype::component::RoomInformations>(rtype::system::UpdateRoomInformations());
    reg.addSystem<rtype::component::Controllable, rtype::component::Velocity>(rtype::system::NetworkControl());

    // add components
    reg.registerComponent<rtype::component::Controllable>();
    reg.registerComponent<rtype::component::Transform>();
    reg.registerComponent<rtype::component::Velocity>();
    reg.registerComponent<rtype::component::Drawable>();
    reg.registerComponent<rtype::component::Collider>();
    reg.registerComponent<rtype::component::Text>();
    reg.registerComponent<rtype::component::DebugColliderDisplay>();
    reg.registerComponent<rtype::component::Selectable>();
    reg.registerComponent<rtype::component::TextInputable>();
    reg.registerComponent<rtype::component::Clickable>();
    reg.registerComponent<rtype::component::Scrollable>();
    reg.registerComponent<rtype::component::Nameable>();
    reg.registerComponent<rtype::component::RoomInformations>();
    reg.registerComponent<rtype::component::ServerID>();
    reg.registerComponent<rtype::component::AllyNumber>();
    reg.registerComponent<rtype::component::Speed>();
    reg.registerComponent<rtype::component::Animation>();

    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initLogin(reg);
    initMenu(reg);
    initJoin(reg);
    initRoom(reg);
    initGamePrefabs(reg);

    // remember to load the first scene LOGIN
    sceneManager.setNextScene(rtype::utils::Scene::LOGIN);

    while (!raylib::WindowShouldClose()) {
        reg.runSystems();
    }
    return 0;
}
