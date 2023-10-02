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
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <ctime>
#include "ECS.hpp"
#include "Drawable.hpp"
#include "Draw.hpp"
#include "Controllable.hpp"
#include "Control.hpp"
#include "AssetsManager.hpp"
#include "VelocityApplicator.hpp"

int main(int ac, char *av[])
{
    raylib::InitWindow(800, 600, "Rtype");
    rtype::ecs::Registry reg;
    rtype::ecs::Entity player = reg.spawnEntity();
    rtype::component::Controllable shipControls(
        std::function<bool()>([]() {return raylib::IsKeyDown(raylib::KEY_Z);}),
        std::function<bool()>([]() {return raylib::IsKeyDown(raylib::KEY_S);}),
        std::function<bool()>([]() {return raylib::IsKeyDown(raylib::KEY_Q);}),
        std::function<bool()>([]() {return raylib::IsKeyDown(raylib::KEY_D);})
    );
    rtype::component::Drawable playerDrawable;
    reg.addSystem<rtype::component::Controllable, rtype::component::Velocity>(rtype::system::Control());
    reg.addSystem<rtype::component::Transformable, rtype::component::Velocity>(rtype::system::VelocityApplicator());
    reg.addSystem<rtype::component::Transformable, rtype::component::Drawable>(rtype::system::Draw());
    reg.registerComponent<rtype::component::Controllable>();
    reg.registerComponent<rtype::component::Transformable>();
    reg.registerComponent<rtype::component::Velocity>();
    reg.registerComponent<rtype::component::Drawable>();
    rtype::utils::AssetsManager &assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("ship", "assets/textures/ship.png");
    playerDrawable = rtype::component::Drawable("ship");
    reg.addComponent<rtype::component::Controllable>(player, std::move(shipControls));
    reg.addComponent<rtype::component::Drawable>(player, std::move(playerDrawable));
    reg.emplaceComponent<rtype::component::Transformable>(player);
    reg.emplaceComponent<rtype::component::Velocity>(player);
    while (!raylib::WindowShouldClose()) {
        reg.runSystems();
    }
    return 0;
}
