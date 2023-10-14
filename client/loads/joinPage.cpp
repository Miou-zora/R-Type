/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** joinPage
*/

#include "loads.hpp"

void initJoinRoomButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("join_page_join_room_button", "assets/textures/buttons/JoinRoomButton.png");

    prefabManager.createPrefab("join_page_join_room_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(700, 600))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                std::string roomId = "";
                std::size_t error = -1;
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "ROOM_ID")
                        roomId = reg.getComponents<rtype::component::Text>()[index]->text;
                    if (name->name == "ERROR JOIN")
                        error = index;
                }
                if (roomId.empty() || !std::all_of(roomId.begin(), roomId.end(), ::isdigit)) {
                    std::cerr << "Invalid ROOM ID" << std::endl;
                    if (error != -1) {
                        reg.getComponents<rtype::component::Text>()[error]->text = "INVALID ID FORMAT";
                        reg.getComponents<rtype::component::Transform>()[error]->position = rtype::utils::Vector<float>(550, 375);
                    }
                    return;
                }
                rtype::network::message::client::ChooseRoom message = rtype::network::message::createEvent<rtype::network::message::client::ChooseRoom>(std::stoi(roomId));
                boost::array<char, rtype::network::message::MAX_PACKET_SIZE> packed = rtype::network::message::pack<rtype::network::message::client::ChooseRoom>(message);
                rtype::network::Client::getInstance().getOutbox()->push(packed);
            })
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("join_page_join_room_button").width, assetsManager.getTexture("join_page_join_room_button").height)
        .addComponent<rtype::component::Drawable>("join_page_join_room_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("join_page_join_room_button").width, assetsManager.getTexture("join_page_join_room_button").height), 1);

    prefabManager.createPrefab("join_error_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Text>("", rtype::component::Text::DEFAULT_FONT, 50, 3, raylib::RED)
        .addComponent<rtype::component::Nameable>("ERROR JOIN");
}

void initInputRoomId(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("room_id_zone", "assets/textures/buttons/PortZone.png");

    prefabManager.createPrefab("room_id_zone")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(810, 500))
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("room_id_zone").width, assetsManager.getTexture("room_id_zone").height)
        .addComponent<rtype::component::Drawable>("room_id_zone", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("room_id_zone").width, assetsManager.getTexture("room_id_zone").height), 1)
        .addComponent<rtype::component::TextInputable>(5)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Text>("", rtype::component::Text::DEFAULT_FONT, 25)
        .addComponent<rtype::component::Nameable>("ROOM_ID");

    prefabManager.createPrefab("room_id_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(685, 510))
        .addComponent<rtype::component::Text>("ROOM ID:", rtype::component::Text::DEFAULT_FONT, 25, 3, raylib::WHITE);
}

void initBackButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("back_button", "assets/textures/buttons/BackButton.png");

    prefabManager.createPrefab("back_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(725, 700))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
                sceneManager.setNextScene(rtype::utils::Scene::MENU);
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("back_button").width, assetsManager.getTexture("back_button").height)
        .addComponent<rtype::component::Drawable>("back_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("back_button").width, assetsManager.getTexture("back_button").height), 1);
}

void initJoin(rtype::ecs::Registry& reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initBackButton(reg);
    initInputRoomId(reg);
    initJoinRoomButton(reg);

    sceneManager.addPrefabToScene("join_error_text", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("main_title", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("back_button", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("room_id_zone", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("room_id_text", rtype::utils::Scene::JOIN);
    sceneManager.addPrefabToScene("join_page_join_room_button", rtype::utils::Scene::JOIN);
}
