/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** roomPage
*/

#include "loads.hpp"

void initBoxPlayers(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("white_square", "assets/textures/buttons/white_square.png");
    for (std::size_t i = 0; i < 4; i++) {

        prefabManager.createPrefab("white_square_" + std::to_string(i))
            .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(265.0f * (static_cast<float>(i) + 1.0f), 350.0f))
            .addComponent<rtype::component::DebugColliderDisplay>(true)
            .addComponent<rtype::component::Collider>(static_cast<float>(assetsManager.getTexture("white_square").width), static_cast<float>(assetsManager.getTexture("white_square").height))
            .addComponent<rtype::component::Drawable>("white_square", 2.0f, rtype::utils::Rectangle(0.0f, 0.0f, static_cast<float>(assetsManager.getTexture("white_square").width), static_cast<float>(assetsManager.getTexture("white_square").height)), 1);
    }
}

void initTextRoom(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();

    prefabManager.createPrefab("room_id")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.0f, 0.0f))
        .addComponent<rtype::component::Text>("ROOM ID:", rtype::component::Text::DEFAULT_FONT, 50, 3.0f, raylib::WHITE)
        .addComponent<rtype::component::Nameable>("ROOM ID");

    prefabManager.createPrefab("room_level")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0.0f, 100.0f))
        .addComponent<rtype::component::Text>("LEVEL: Loading...", rtype::component::Text::DEFAULT_FONT, 50, 3.0f, raylib::WHITE)
        .addComponent<rtype::component::Nameable>("ROOM LEVEL");
}

void initStartGameButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    assetsManager.loadTexture("start_game_button", "assets/textures/buttons/StartButton.png");
    prefabManager.createPrefab("start_game_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(660.0f, 600.0f))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::network::message::client::StartGame startMessage = rtype::network::message::createEvent<rtype::network::message::client::StartGame>();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> startPacked = rtype::network::message::pack<rtype::network::message::client::StartGame>(startMessage);
                rtype::network::Client::getInstance().getOutbox()->push(startPacked);
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("start_game_button").width, assetsManager.getTexture("login_start_button").height)
        .addComponent<rtype::component::Drawable>("start_game_button", 1.0f, rtype::utils::Rectangle(0.0f, 0.0f, assetsManager.getTexture("login_start_button").width, assetsManager.getTexture("login_start_button").height), 1);
}

void initSpaceShip(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    assetsManager.loadTexture("space_ship", "assets/textures/ships.png");
    prefabManager.createPrefab("space_ship_1")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(285.0f, 410.0f))
        .addComponent<rtype::component::Drawable>("space_ship", 0, rtype::utils::Rectangle(1.0f, 3.0f, 32.0f, 16.0f), 2)
        .addComponent<rtype::component::Nameable>("SPACE SHIP 1");
    prefabManager.createPrefab("space_ship_2")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(550.0f, 410.0f))
        .addComponent<rtype::component::Drawable>("space_ship", 0, rtype::utils::Rectangle(1.0f, 20.0f, 32.0f, 16.0f), 2)
        .addComponent<rtype::component::Nameable>("SPACE SHIP 2");
    prefabManager.createPrefab("space_ship_3")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(815.0f, 410.0f))
        .addComponent<rtype::component::Drawable>("space_ship", 0, rtype::utils::Rectangle(1.0f, 37.0f, 32.0f, 16.0f), 2)
        .addComponent<rtype::component::Nameable>("SPACE SHIP 3");
    prefabManager.createPrefab("space_ship_4")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1080.0f, 410.0f))
        .addComponent<rtype::component::Drawable>("space_ship", 0, rtype::utils::Rectangle(1.0f, 54.0f, 32.0f, 16.0f), 2)
        .addComponent<rtype::component::Nameable>("SPACE SHIP 4");
}

void initBackRoomButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("back_room_button", "assets/textures/buttons/BackButton.png");

    prefabManager.createPrefab("back_room_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(685.0f, 700.0f))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::network::message::client::LeaveRoom leaveMessage = rtype::network::message::createEvent<rtype::network::message::client::LeaveRoom>();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> leavePacked = rtype::network::message::pack<rtype::network::message::client::LeaveRoom>(leaveMessage);
                rtype::network::Client::getInstance().getOutbox()->push(leavePacked);
                rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
                sceneManager.setNextScene(sceneManager.getPreviousScene());
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("back_room_button").width, assetsManager.getTexture("back_room_button").height)
        .addComponent<rtype::component::Drawable>("back_room_button", 1.0f, rtype::utils::Rectangle(0.0f, 0.0f, assetsManager.getTexture("back_room_button").width, assetsManager.getTexture("back_room_button").height), 1);
}

void initRoom(rtype::ecs::Registry& reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initBoxPlayers(reg);
    initTextRoom(reg);
    initStartGameButton(reg);
    initSpaceShip(reg);
    initBackRoomButton(reg);

    for (std::size_t i = 0; i < 4; i++) {
        sceneManager.addPrefabToScene("white_square_" + std::to_string(i), rtype::utils::Scene::ROOM);
        sceneManager.addPrefabToScene("space_ship_" + std::to_string(i + 1), rtype::utils::Scene::ROOM);
    }
    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::ROOM);
    sceneManager.addPrefabToScene("room_id", rtype::utils::Scene::ROOM);
    sceneManager.addPrefabToScene("room_level", rtype::utils::Scene::ROOM);
    sceneManager.addPrefabToScene("start_game_button", rtype::utils::Scene::ROOM);
    sceneManager.addPrefabToScene("back_room_button", rtype::utils::Scene::ROOM);

    rtype::ecs::Entity roomInfos = reg.spawnEntity();
    reg.emplaceComponent<rtype::component::RoomInformations>(roomInfos);
}