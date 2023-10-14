/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** UpdateRoomInformations
*/

#pragma once

#include "Drawable.hpp"
#include "ECS.hpp"
#include "Nameable.hpp"
#include "RoomInformations.hpp"
#include "SceneManager.hpp"
#include "Text.hpp"

namespace rtype::system {
class UpdateRoomInformations {
public:
    UpdateRoomInformations() = default;
    ~UpdateRoomInformations() = default;

    /**
     * @brief Update the room informations on the window
     *
     * @param registry
     * @param infos component that contains the room informations (only link to one entity)
     */
    void operator()(rtype::ecs::Registry& registry,
        rtype::ecs::SparseArray<rtype::component::RoomInformations>& infos) const
    {
        rtype::utils::SceneManager& sceneManager = rtype::utils::SceneManager::getInstance();
        if (sceneManager.getCurrentScene() != rtype::utils::Scene::ROOM)
            return;
        std::size_t nbPlayers = 0;
        for (auto&& [index_name, name] : rtype::ecs::containers::IndexedZipper(registry.getComponents<rtype::component::Nameable>())) {
            for (auto&& [index_infos, info] : rtype::ecs::containers::IndexedZipper(infos)) {
                if (name->name == "ROOM ID" && registry.hasComponent<rtype::component::Text>(registry.entityFromIndex(index_name)))
                    registry.getComponents<rtype::component::Text>()[index_name]->text = "ROOM ID: " + std::to_string(registry.getComponents<rtype::component::RoomInformations>()[index_infos]->id);
                if (name->name == "ROOM LEVEL" && registry.hasComponent<rtype::component::Text>(registry.entityFromIndex(index_name)))
                    registry.getComponents<rtype::component::Text>()[index_name]->text = "LEVEL: " + std::to_string(registry.getComponents<rtype::component::RoomInformations>()[index_infos]->level);
                if (registry.hasComponent<rtype::component::RoomInformations>(registry.entityFromIndex(index_infos)))
                    nbPlayers = registry.getComponents<rtype::component::RoomInformations>()[index_infos]->playersCount;
                if (spaceShips.find(name->name) != spaceShips.end() && registry.hasComponent<rtype::component::Drawable>(registry.entityFromIndex(index_name)))
                    registry.getComponents<rtype::component::Drawable>()[index_name]->scale = nbPlayers >= (spaceShips.at(name->name)) ? 5 : 0;
            }
        }
    }

    std::map<std::string, std::size_t> spaceShips = {
        { "SPACE SHIP 1", 1 },
        { "SPACE SHIP 2", 2 },
        { "SPACE SHIP 3", 3 },
        { "SPACE SHIP 4", 4 }
    };
};
}
