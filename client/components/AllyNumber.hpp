/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL: Ubuntu]
** File description:
** EnemyNumber
*/

#pragma once

namespace rtype::component {
/**
 * @brief AllyNumber component used to store the number of an ally
 */
struct AllyNumber {
    AllyNumber(int id_ = -1)
        : id(id_) {};
    ~AllyNumber(void) = default;

    AllyNumber(const AllyNumber& other) = default;
    AllyNumber& operator=(const AllyNumber& other) = default;

    int id;
};
}
