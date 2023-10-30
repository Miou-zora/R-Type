/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** OptionPage
*/

#include "loads.hpp"

void initMusicButtons(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    rtype::utils::OptionManager& optionManager = rtype::utils::OptionManager::getInstance();

    prefabManager.createPrefab("plus_music_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1200, 400))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "MUSIC_VOLUME") {
                        auto& text = reg.getComponents<rtype::component::Text>()[index]->text = std::to_string(optionManager.increaseMusicVolume(1));
                    }
                }
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("plus_button").width, assetsManager.getTexture("plus_button").height)
        .addComponent<rtype::component::Drawable>("plus_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("plus_button").width, assetsManager.getTexture("plus_button").height), 1);
    prefabManager.createPrefab("minus_music_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1000, 400))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "MUSIC_VOLUME") {
                        auto& text = reg.getComponents<rtype::component::Text>()[index]->text = std::to_string(optionManager.decreaseMusicVolume(1));
                    }
                }
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("minus_button").width, assetsManager.getTexture("minus_button").height)
        .addComponent<rtype::component::Drawable>("minus_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("minus_button").width, assetsManager.getTexture("minus_button").height), 1);
}

void initSoundButtons(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();
    rtype::utils::OptionManager& optionManager = rtype::utils::OptionManager::getInstance();

    prefabManager.createPrefab("plus_sound_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1200, 700))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "SOUND_VOLUME") {
                        reg.getComponents<rtype::component::Text>()[index]->text = std::to_string(optionManager.increaseSoundVolume(1));
                    }
                }
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("plus_button").width, assetsManager.getTexture("plus_button").height)
        .addComponent<rtype::component::Drawable>("plus_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("plus_button").width, assetsManager.getTexture("plus_button").height), 1);
    prefabManager.createPrefab("minus_sound_button")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1000, 700))
        .addComponent<rtype::component::Clickable>(
            [&]() {
                for (auto&& [index, name] : rtype::ecs::containers::IndexedZipper(reg.getComponents<rtype::component::Nameable>())) {
                    if (name->name == "SOUND_VOLUME") {
                        reg.getComponents<rtype::component::Text>()[index]->text = std::to_string(optionManager.decreaseSoundVolume(1));
                    }
                }
            })
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("minus_button").width, assetsManager.getTexture("minus_button").height)
        .addComponent<rtype::component::Drawable>("minus_button", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("minus_button").width, assetsManager.getTexture("minus_button").height), 1);
}

void initMusicTextBox(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    prefabManager.createPrefab("music_text_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1100, 400))
        .addComponent<rtype::component::Drawable>("option_text_box", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_box").width, assetsManager.getTexture("option_text_box").height), 1)
        .addComponent<rtype::component::Text>("100", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::BLACK)
        .addComponent<rtype::component::Nameable>("MUSIC_VOLUME");
}

void initSoundTextBox(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    prefabManager.createPrefab("sound_text_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1100, 700))
        .addComponent<rtype::component::Drawable>("option_text_box", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_box").width, assetsManager.getTexture("option_text_box").height), 1)
        .addComponent<rtype::component::Text>("100", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::BLACK)
        .addComponent<rtype::component::Nameable>("SOUND_VOLUME");
}

void initKeyBindingButtons(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    prefabManager.createPrefab("up_input_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100, 100))
        .addComponent<rtype::component::Drawable>("option_text_rectangle", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height), 1)
        .addComponent<rtype::component::Nameable>("UP_INBOX")
        .addComponent<rtype::component::Key>(raylib::KEY_UP)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height)
        .addComponent<rtype::component::Text>(rtype::utils::keyToString(raylib::KEY_UP), rtype::component::Text::DEFAULT_FONT, 20, 3.0f, raylib::BLACK);
    prefabManager.createPrefab("down_input_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100, 300))
        .addComponent<rtype::component::Drawable>("option_text_rectangle", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height), 1)
        .addComponent<rtype::component::Nameable>("DOWN_INBOX")
        .addComponent<rtype::component::Key>(raylib::KEY_DOWN)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height)
        .addComponent<rtype::component::Text>(rtype::utils::keyToString(raylib::KEY_DOWN), rtype::component::Text::DEFAULT_FONT, 20, 3.0f, raylib::BLACK);
    prefabManager.createPrefab("left_input_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100, 500))
        .addComponent<rtype::component::Drawable>("option_text_rectangle", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height), 1)
        .addComponent<rtype::component::Nameable>("LEFT_INBOX")
        .addComponent<rtype::component::Key>(raylib::KEY_LEFT)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height)
        .addComponent<rtype::component::Text>(rtype::utils::keyToString(raylib::KEY_LEFT), rtype::component::Text::DEFAULT_FONT, 20, 3.0f, raylib::BLACK);
    prefabManager.createPrefab("right_input_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100, 700))
        .addComponent<rtype::component::Drawable>("option_text_rectangle", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height), 1)
        .addComponent<rtype::component::Nameable>("RIGHT_INBOX")
        .addComponent<rtype::component::Key>(raylib::KEY_RIGHT)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height)
        .addComponent<rtype::component::Text>(rtype::utils::keyToString(raylib::KEY_RIGHT), rtype::component::Text::DEFAULT_FONT, 20, 3.0f, raylib::BLACK);
    prefabManager.createPrefab("shoot_inbox_box")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(100, 900))
        .addComponent<rtype::component::Drawable>("option_text_rectangle", 1, rtype::utils::Rectangle(0, 0, assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height), 1)
        .addComponent<rtype::component::Nameable>("SHOOT_INBOX")
        .addComponent<rtype::component::Key>(raylib::KEY_SPACE)
        .addComponent<rtype::component::Selectable>()
        .addComponent<rtype::component::Collider>(assetsManager.getTexture("option_text_rectangle").width, assetsManager.getTexture("option_text_rectangle").height)
        .addComponent<rtype::component::Text>(rtype::utils::keyToString(raylib::KEY_SPACE), rtype::component::Text::DEFAULT_FONT, 20, 3.0f, raylib::BLACK);
}

void initMusicAndSoundText(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();

    prefabManager.createPrefab("music_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1050, 300))
        .addComponent<rtype::component::Text>("Music", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("sound_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(1050, 600))
        .addComponent<rtype::component::Text>("Sound", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
}

void initKeyBindingText(rtype::ecs::Registry &reg)
{
    rtype::utils::PrefabManager& prefabManager = rtype::utils::PrefabManager::getInstance();

    prefabManager.createPrefab("up_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 75))
        .addComponent<rtype::component::Text>("Up", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("down_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 275))
        .addComponent<rtype::component::Text>("Down", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("left_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 475))
        .addComponent<rtype::component::Text>("Left", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("right_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 675))
        .addComponent<rtype::component::Text>("Right", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
    prefabManager.createPrefab("shoot_text")
        .addComponent<rtype::component::Transform>(rtype::utils::Vector<float>(400, 875))
        .addComponent<rtype::component::Text>("Shoot", rtype::component::Text::DEFAULT_FONT, 75, 3.0f, raylib::WHITE);
}

void initOption(rtype::ecs::Registry &reg)
{
    rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
    rtype::utils::AssetsManager& assetsManager = rtype::utils::AssetsManager::getInstance();

    assetsManager.loadTexture("minus_button", "assets/textures/buttons/MinusButton.png");
    assetsManager.loadTexture("plus_button", "assets/textures/buttons/PlusButton.png");
    assetsManager.loadTexture("option_text_box", "assets/textures/buttons/white_square.png");
    assetsManager.loadTexture("option_text_rectangle", "assets/textures/buttons/white_rectangle.png");

    initMusicButtons(reg);
    initSoundButtons(reg);
    initMusicTextBox(reg);
    initSoundTextBox(reg);
    initMusicAndSoundText(reg);
    initKeyBindingText(reg);
    initKeyBindingButtons(reg);

    sceneManager.addPrefabToScene("main_background", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("back_button", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("plus_music_button", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("minus_music_button", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("plus_sound_button", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("minus_sound_button", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("music_text_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("sound_text_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("up_input_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("down_input_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("left_input_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("right_input_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("shoot_inbox_box", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("music_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("sound_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("up_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("down_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("left_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("right_text", rtype::utils::Scene::OPTIONS);
    sceneManager.addPrefabToScene("shoot_text", rtype::utils::Scene::OPTIONS);
}
