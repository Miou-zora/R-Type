/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** ServerID
*/

#pragma once

namespace rtype::component {
/**
 * @brief ServerID component used to store the server id of an entity
 */
struct ServerID {
    ServerID(int id_ = -1)
        : id(id_) {};
    ~ServerID(void) = default;

    ServerID(const ServerID& other) = default;
    ServerID& operator=(const ServerID& other) = default;

    int id;
};
}
