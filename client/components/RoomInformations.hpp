/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** RoomInformations
*/

#pragma once

namespace rtype::component
{
    /**
     * @brief RoomInformations component used to store the room informations
     *
     */
    struct RoomInformations
    {
        RoomInformations(int playersCount_ = 1, int level_ = 1) : playersCount(playersCount_), level(level_){};
        ~RoomInformations() = default;

        RoomInformations(const RoomInformations &other) = default;
        RoomInformations &operator=(const RoomInformations &other) = default;

        int playersCount;
        int level;
    };
}


