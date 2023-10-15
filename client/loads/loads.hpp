/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** loads
*/

#pragma once

#include "AssetsManager.hpp"
#include "Clickable.hpp"
#include "Client.hpp"
#include "Collider.hpp"
#include "Controllable.hpp"
#include "DebugColliderDisplayer.hpp"
#include "Drawable.hpp"
#include "ECS.hpp"
#include "Nameable.hpp"
#include "PrefabManager.hpp"
#include "Rectangle.hpp"
#include "SceneManager.hpp"
#include "Scenes.hpp"
#include "Scrollable.hpp"
#include "Selectable.hpp"
#include "Text.hpp"
#include "TextInputable.hpp"
#include "Transform.hpp"
namespace raylib {
#include <raylib.h>
}
#include "NetworkMessage.hpp"
#include "RoomInformations.hpp"

/**
 * @brief Init the Login scene (prefabs)
 * @param reg The ECS registry
 */
void initLogin(rtype::ecs::Registry& reg);
/**
 * @brief Init the Menu scene (prefabs)
 * @param reg The ECS registry
 */
void initMenu(rtype::ecs::Registry& reg);
/**
 * @brief Init the Join scene (prefabs)
 * @param reg The ECS registry
 */
void initJoin(rtype::ecs::Registry& reg);
/**
 * @brief Init the Create scene (prefabs)
 * @param reg The ECS registry
 */
void initRoom(rtype::ecs::Registry& reg);
/**
 * @brief Init the Game scene (prefabs)
 * @param reg The ECS registry
 */
void initGamePrefabs(rtype::ecs::Registry& reg);
