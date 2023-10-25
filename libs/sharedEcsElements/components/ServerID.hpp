/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** ServerID
*/

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace rtype::component {
/**
 * @brief ServerID component used to store the server id of an entity
 */
struct ServerID {
    ServerID(uint8_t uuid_[16] = boost::uuids::nil_uuid().data)
    {
        std::copy_n(uuid_, 16, uuid);
    };
    ~ServerID(void) = default;

    ServerID(const ServerID& other) = default;
    ServerID& operator=(const ServerID& other) = default;

    uint8_t uuid[16];
};
}
