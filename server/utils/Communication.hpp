/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Communication
*/

#pragma once

#include "ECS.hpp"
#include "NetworkPlayer.hpp"
#include "GameRoom.hpp"

namespace rtype::utils
{
    /**
     * @brief Communication class, used to send messages to clients using generic methods
    */
    class Communication
    {
    public:
        /**
         * @brief CommunicationType enum, used to specify the type of communication, if critical, the client must return an ack, if not, the client can ignore the message
        */
        enum class CommunicationType {
            CRITICAL,
            NON_CRITICAL
        };
    public:
        /**
         * @brief We don't want instances of this class because it's a static class only used for static methods
        */
        Communication() = delete;

        /**
         * @brief Send a message all player in the same room
        */
        template<typename ServerStruct, typename... Args>
        static void sendToPlayerInSameRoom(ecs::Registry& registry, CommunicationType communicationType, u_int16_t roomId, Args&&... args)
        {
            ServerStruct event = rtype::network::message::createEvent<ServerStruct>(std::forward<Args>(args)...);
            boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE> networkPacket = rtype::network::message::pack<ServerStruct>(event);
            for (auto&& [networkPlayer, gameRoom] : ecs::containers::Zipper(registry.getComponents<rtype::component::NetworkPlayer>(), registry.getComponents<rtype::component::GameRoom>())) {
                if (gameRoom.value().id != roomId)
                    continue;
                if (communicationType == CommunicationType::CRITICAL)
                    sendCriticalMessages(networkPlayer.value(), networkPacket);
            }
        }


    private:
        /**
         * @brief Send a critical message to a player
        */
        static void sendCriticalMessages(rtype::component::NetworkPlayer& player, const boost::array<char, rtype::network::message::MAX_MESSAGE_SIZE>& msg)
        {
            const auto& unpacked = reinterpret_cast<const rtype::network::message::NetworkMessageHeader*>(msg.data());
            (*player.criticalMessages)[unpacked->id] = msg;
        }
    };
}
