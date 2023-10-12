/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Form
*/

#pragma once

#include "ECS.hpp"
#include <vector>

namespace rtype::component {
/**
 * @brief Form component used to call a lambda function with multiple text inputs.
 */
struct Form {
    Form(
        std::unordered_map<std::string, rtype::ecs::Entity> entities_ = std::unordered_map<std::string, rtype::ecs::Entity>(), std::function<void(std::unordered_map<std::string, std::string>)> callback_ = [](std::unordered_map<std::string, std::string>) {})
        : entities(entities_)
        , callback(callback_) {};
    ~Form(void) = default;

    Form(const Form& other) = default;
    Form& operator=(const Form& other) = default;

    std::unordered_map<std::string, rtype::ecs::Entity> entities;
    std::function<void(std::unordered_map<std::string, std::string>)> callback;
};
}
