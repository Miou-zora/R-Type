/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** Key
*/

#pragma once

namespace rtype::component {
/**
 * @brief Key component used to store a key
 */
struct Key {
    Key(int key_ = 0)
        : key(key_) {};
    ~Key() = default;

    Key(const Key& other) = default;
    Key& operator=(const Key& other) = default;

    int key;
};
}
