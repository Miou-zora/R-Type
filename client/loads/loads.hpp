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

void initLogin(rtype::ecs::Registry& reg);
void initMenu(rtype::ecs::Registry& reg);
