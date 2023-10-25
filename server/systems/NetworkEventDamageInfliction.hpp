/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** NetworkEventDamageInfliction
*/

#pragma once

#include "ECS.hpp"
#include "SingletonWrapper.hpp"
#include "EventManager.hpp"
#include "DamageInfliction.hpp"
#include "NetworkPlayer.hpp"
#include "Communication.hpp"

namespace rtype::system
{
    /**
     * @brief NetworkEventDamageInfliction system, used to send PlayerLife infos to clients
     */
    class NetworkEventDamageInfliction
    {
    public:
        NetworkEventDamageInfliction() = default;
        ~NetworkEventDamageInfliction() = default;

        void operator()(rtype::ecs::Registry &registry) const
        {
            const std::vector<rtype::event::DamageInfliction> &events = rtype::utils::SingletonWrapper<rtype::utils::EventManager>::getInstance().getEvents<rtype::event::DamageInfliction>();
            std::vector<const rtype::event::DamageInfliction *> eventsToSend;

            for (const rtype::event::DamageInfliction &event : events)
            {
                if (registry.hasComponent<rtype::component::NetworkPlayer>(event.to))
                {
                    eventsToSend.push_back(&event);
                }
            }
            for (const rtype::event::DamageInfliction *event : eventsToSend)
            {
                if (!registry.hasComponent<rtype::component::ServerID>(event->to))
                    return;
                rtype::utils::Communication::sendToPlayerInSameRoom<rtype::network::message::server::PlayerLife>(registry, rtype::utils::Communication::CommunicationType::CRITICAL, registry.getComponents<rtype::component::GameRoom>()[event->to].value().id, registry.getComponents<rtype::component::ServerID>()[event->to].value().uuid, event->currentLife);
            }
        }
    };
}
