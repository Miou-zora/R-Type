/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** menuPage
*/

#include "loads.hpp"

void initMenuSingleButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("single_button", "assets/textures/buttons/SingleButton.png");

    prefabManager.createPrefab("single_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(700, 500))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::network::message::client::CreateRoom message = rtype::network::message::createEvent<rtype::network::message::client::CreateRoom>();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = rtype::network::message::pack<rtype::network::message::client::CreateRoom>(message);
                rtype::network::Client::getInstance().getOutbox()->push(packed);
                rtype::network::message::client::ChooseLevel levelMessage = rtype::network::message::createEvent<rtype::network::message::client::ChooseLevel>(1);
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> levelPacked = rtype::network::message::pack<rtype::network::message::client::ChooseLevel>(levelMessage);
                rtype::network::Client::getInstance().getOutbox()->push(levelPacked);
                rtype::network::message::client::StartGame startMessage = rtype::network::message::createEvent<rtype::network::message::client::StartGame>();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> startPacked = rtype::network::message::pack<rtype::network::message::client::StartGame>(startMessage);
                rtype::network::Client::getInstance().getOutbox()->push(startPacked);
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("single_button").width, assetsManager.getTexture("login_start_button").height)
        .addComponent<rtype::component::Drawable>("single_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("login_start_button").width, assetsManager.getTexture("login_start_button").height), 1);
}

void initMenuCreateRoomButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("create_room_button", "assets/textures/buttons/CreateRoomButton.png");

    prefabManager.createPrefab("create_room_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(700, 600))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::network::message::client::CreateRoom message = rtype::network::message::createEvent<rtype::network::message::client::CreateRoom>();
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = rtype::network::message::pack<rtype::network::message::client::CreateRoom>(message);
                rtype::network::Client::getInstance().getOutbox()->push(packed);
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("create_room_button").width, assetsManager.getTexture("create_room_button").height)
        .addComponent<rtype::component::Drawable>("create_room_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("create_room_button").width, assetsManager.getTexture("create_room_button").height), 1);
}

void initMenuJoinRoomButton(rtype::ecs::Registry& reg)
{
rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("join_room_button", "assets/textures/buttons/JoinRoomButton.png");

    prefabManager.createPrefab("join_room_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(700, 700))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
                sceneManager.loadScene(rtype::utils::Scene::JOIN, reg);
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("join_room_button").width, assetsManager.getTexture("join_room_button").height)
        .addComponent<rtype::component::Drawable>("join_room_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("join_room_button").width, assetsManager.getTexture("join_room_button").height), 1);
}

void initMenu(rtype::ecs::Registry& reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initMenuSingleButton(reg);
    initMenuCreateRoomButton(reg);
    initMenuJoinRoomButton(reg);

    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::MENU);
    sceneManager.addPrefabToScene("main_title", rtype::utils::Scene::MENU);
    sceneManager.addPrefabToScene("exit_button", rtype::utils::Scene::MENU);
    sceneManager.addPrefabToScene("single_button", rtype::utils::Scene::MENU);
    sceneManager.addPrefabToScene("create_room_button", rtype::utils::Scene::MENU);
    sceneManager.addPrefabToScene("join_room_button", rtype::utils::Scene::MENU);
}