/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
namespace raylib {
#include <raylib.h>
}
#include "AssetsManager.hpp"
#include "Control.hpp"
#include "Controllable.hpp"
#include "DebugColliderDisplayer.hpp"
#include "Draw.hpp"
#include "Drawable.hpp"
#include "ECS.hpp"
#include "Selection.hpp"
#include "VelocityApplicator.hpp"
#include "systems/TextInput.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <string>

int main(int ac, char* av[])
{
    raylib::InitWindow(800, 600, "Rtype");
    rtype::ecs::Registry reg;
    rtype::ecs::Entity player = reg.spawnEntity();
    rtype::component::Controllable shipControls(
        std::function<bool()>([]() { return raylib::IsKeyDown(raylib::KEY_Z); }),
        std::function<bool()>([]() { return raylib::IsKeyDown(raylib::KEY_S); }),
        std::function<bool()>([]() { return raylib::IsKeyDown(raylib::KEY_Q); }),
        std::function<bool()>([]() { return raylib::IsKeyDown(raylib::KEY_D); }));
    rtype::component::Drawable playerDrawable;
    reg.addSystem<rtype::component::Controllable, rtype::component::Velocity>(rtype::system::Control());
    reg.addSystem<rtype::component::Transform, rtype::component::Velocity>(rtype::system::VelocityApplicator());
    reg.addSystem<>(rtype::system::Draw());
    reg.addSystem<rtype::component::DebugColliderDisplay, rtype::component::Transform, rtype::component::Collider>(rtype::system::DebugColliderDisplayer());
    reg.addSystem<rtype::component::Selectable, rtype::component::Transform, rtype::component::Collider>(rtype::system::Selection());
    reg.addSystem<rtype::component::Selectable, rtype::component::TextInputable, rtype::component::Text>(rtype::system::TextInput());
    reg.registerComponent<rtype::component::Controllable>();
    reg.registerComponent<rtype::component::Transform>();
    reg.registerComponent<rtype::component::Velocity>();
    reg.registerComponent<rtype::component::Drawable>();
    reg.registerComponent<rtype::component::Collider>();
    reg.registerComponent<rtype::component::Text>();
    reg.registerComponent<rtype::component::DebugColliderDisplay>();
    reg.registerComponent<rtype::component::Selectable>();
    reg.registerComponent<rtype::component::TextInputable>();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("ship", "assets/textures/ship.png");
    rtype::utils::Rectangle shipRectangle(0, 0, assetsManager.getTexture("ship").width, assetsManager.getTexture("ship").height);
    playerDrawable = rtype::component::Drawable("ship", 1, shipRectangle);
    reg.addComponent<rtype::component::Controllable>(player, std::move(shipControls));
    reg.addComponent<rtype::component::Drawable>(player, std::move(playerDrawable));
    reg.emplaceComponent<rtype::component::Transform>(player);
    reg.emplaceComponent<rtype::component::Velocity>(player);
    reg.emplaceComponent<rtype::component::DebugColliderDisplay>(player, true);
    reg.emplaceComponent<rtype::component::Collider>(player, assetsManager.getTexture("ship").width, assetsManager.getTexture("ship").height);
    reg.emplaceComponent<rtype::component::Selectable>(player);

    rtype::ecs::Entity inputText = reg.spawnEntity();
    reg.emplaceComponent<rtype::component::Text>(inputText, "Hello World");
    reg.emplaceComponent<rtype::component::Transform>(inputText, rtype::utils::Vector<float>(100, 100));
    reg.emplaceComponent<rtype::component::TextInputable>(inputText);
    reg.emplaceComponent<rtype::component::Selectable>(inputText);
    reg.emplaceComponent<rtype::component::Collider>(inputText, 100, 20);
    reg.emplaceComponent<rtype::component::DebugColliderDisplay>(inputText, true);
    while (!raylib::WindowShouldClose()) {
        reg.runSystems();
    }
    return 0;
}
