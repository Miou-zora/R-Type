/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** loginPage
*/

#include "loads.hpp"

void initLoginStartButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("login_start_button", "assets/textures/buttons/StartButton.png");

    prefabManager.createPrefab("login_start_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(660, 700))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                std::string ip = "";
                std::string port = "";
                std::size_t error = -1;
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "IP")
                        ip = reg.getComponents<rtype::component::Text>()[index]->text;
                    if (name->name == "PORT")
                        port = reg.getComponents<rtype::component::Text>()[index]->text;
                    if (name->name == "ERROR LOGIN")
                        error = index;
                }
                boost::system::error_code ec;
                boost::asio::ip::address::from_string(ip, ec);
                if (ec || !std::all_of(port.begin(), port.end(), ::isdigit) || port.empty() || ip.empty()) {
                    std::cerr << "Invalid IP or PORT" << std::endl;
                    if (error != -1) {
                        reg.getComponents<rtype::component::Text>()[error]->text = "INVALID IP OR PORT";
                        reg.getComponents<rtype::component::Transform>()[error]->position = rtype::utils::Vector<float>(510, 375);
                    }
                    return;
                }
                rtype::network::Client& client = rtype::network::Client::getInstance();
                client.connect(ip, stoi(port));
            })
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("login_start_button").width, assetsManager.getTexture("login_start_button").height)
        .addComponent<rtype::component::Drawable>("login_start_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("login_start_button").width, assetsManager.getTexture("login_start_button").height), 1);

    prefabManager.createPrefab("login_error_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Text>("", rtype::component::Text::DEFAULT_FONT, 50, 3, raylib::RED)
        .addComponent<rtype::component::Nameable>("ERROR LOGIN");
}

void initInputIp(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("ip_zone", "assets/textures/buttons/IPZone.png");

    prefabManager.createPrefab("ip_zone")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(660, 500))
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("ip_zone").width, assetsManager.getTexture("ip_zone").height)
        .addComponent<rtype::component::Drawable>("ip_zone", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("ip_zone").width, assetsManager.getTexture("ip_zone").height), 1)
        .addComponent<rtype::component::TextInputable>(15)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Text>("127.0.0.1", rtype::component::Text::DEFAULT_FONT, 25)
        .addComponent<rtype::component::Nameable>("IP");
    prefabManager.createPrefab("ip_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(610, 510))
        .addComponent<rtype::component::Text>("IP:", rtype::component::Text::DEFAULT_FONT, 25, 3, raylib::WHITE);
}

void initInputPort(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("port_zone", "assets/textures/buttons/PortZone.png");

    prefabManager.createPrefab("port_zone")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(710, 600))
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("port_zone").width, assetsManager.getTexture("port_zone").height)
        .addComponent<rtype::component::Drawable>("port_zone", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("port_zone").width, assetsManager.getTexture("port_zone").height), 1)
        .addComponent<rtype::component::TextInputable>(5)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Text>("12345", rtype::component::Text::DEFAULT_FONT, 25)
        .addComponent<rtype::component::Nameable>("PORT");

    prefabManager.createPrefab("port_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(610, 610))
        .addComponent<rtype::component::Text>("PORT:", rtype::component::Text::DEFAULT_FONT, 25, 3, raylib::WHITE);
}

void initExitButton(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("exit_button", "assets/textures/buttons/ExitButton.png");

    prefabManager.createPrefab("exit_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(685, 800))
        .addComponent<rtype::component::DebugColliderDisplay>(true)
        .addComponent<rtype::component::Clickable>(
            [&]() {
                raylib::CloseWindow();
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("exit_button").width, assetsManager.getTexture("exit_button").height)
        .addComponent<rtype::component::Drawable>("exit_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("exit_button").width, assetsManager.getTexture("exit_button").height), 1);
}

void background(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("main_background", "assets/textures/spacebg.png");

    prefabManager.createPrefab("main_background")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(0, 0))
        .addComponent<rtype::component::Drawable>("main_background", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("main_background").width * 2, assetsManager.getTexture("main_background").height), 0)
        .addComponent<rtype::component::Scrollable>(rtype::utils::Vector<float>(1, 0), 100);
}

void title(rtype::ecs::Registry& reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    assetsManager.loadTexture("main_title", "assets/textures/R-Type_Logo.png");

    prefabManager.createPrefab("main_title")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(510, 200))
        .addComponent<rtype::component::Drawable>("main_title", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("main_title").width, assetsManager.getTexture("main_title").height), 1);
}

void initLogin(rtype::ecs::Registry& reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();

    initLoginStartButton(reg);
    initInputIp(reg);
    initInputPort(reg);
    initExitButton(reg);
    background(reg);
    title(reg);

    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("main_title", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("exit_button", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("port_text", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("port_zone", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("ip_text", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("ip_zone", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("login_error_text", rtype::utils::Scene::LOGIN);
    sceneManager.addPrefabToScene("login_start_button", rtype::utils::Scene::LOGIN);
}
