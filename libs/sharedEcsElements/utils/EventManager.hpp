/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** EventManager
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>

namespace rtype::utils
{
    /**
     * @brief EventManager class. Use to store events (events are like component but they are more customizable and easier to use).
     * This class should be used as a singleton. To do so, use the SingletonWrapper class like: SingletonWrapper<EventManager>::getInstance().
    */
    class EventManager
    {
    private:
        typedef struct event_s
        {
            std::any listOfInstances;
            std::function<void(EventManager &)> clear;
        } event_t;

    public:
        /**
         * @brief Construct a new Event Manager object. This class should be used as a singleton. To do so, use the SingletonWrapper class like: SingletonWrapper<EventManager>::getInstance().
        */
        EventManager(void) = default;
        /**
         * @brief Destroy the Event Manager object.
        */
        ~EventManager(void) = default;

        /**
         * @brief Get a std::vector of all the events of the given type. If the type is not found, it will be created.
         * It returns a const std::vector<EventType>& because you should not modify the events directly.
         *
         * @tparam EventType The type of the event to get.
         * @return const std::vector<EventType>& A std::vector of all the events of the given type.
        */
        template <typename EventType>
        const std::vector<EventType> &getEvents(void)
        {
            if (m_events.find(std::type_index(typeid(EventType))) == m_events.end())
                loadEvents<EventType>();
            return std::any_cast<std::vector<EventType> &>(m_events.at(std::type_index(typeid(EventType))).listOfInstances);
        }

        /**
         * @brief Clear all the events. This will call the clear std::vector of all the events.
        */
        void clearEvents(void)
        {
            for (auto &event : m_events)
                event.second.clear(*this);
        }

        /**
         * @brief Add an event to the list of events. If the type is not found, it will be created.
         *
         * @tparam EventType The type of the event to add.
         * @param event The event to add. It will be added to the std::vector of the given type useing std::vector::push_back.
        */
        template <typename EventType>
        EventType &addEvent(EventType &&event)
        {
            if (m_events.find(std::type_index(typeid(EventType))) == m_events.end())
                loadEvents<EventType>();
            std::vector<EventType> &vec = std::any_cast<std::vector<EventType> &>(m_events[std::type_index(typeid(EventType))].listOfInstances);
            vec.push_back(event);
            return vec.back();
        }

        /**
         * @brief Add an event to the list of events. If the type is not found, it will be created.
         * This function is used to construct the event in place.
         *
         * @tparam EventType The type of the event to add.
         * @param args The arguments to construct the event.
        */
        template <typename EventType, typename... Args>
        EventType &addEvent(Args &&...args)
        {
            if (m_events.find(std::type_index(typeid(EventType))) == m_events.end())
                loadEvents<EventType>();
            std::vector<EventType> &vec = std::any_cast<std::vector<EventType> &>(m_events[std::type_index(typeid(EventType))].listOfInstances);
            vec.push_back(EventType(std::forward<Args>(args)...));
            return vec.back();
        }

    private:
        /**
         * @brief Create space to load event of the given type. It will create a std::vector of the given type and a clear function that will clear the std::vector.
         *
         * @tparam EventType The type of the event to load.
        */
        template <typename EventType>
        void loadEvents(void)
        {
            m_events[std::type_index(typeid(EventType))] = event_t{
                std::vector<EventType>(),
                [](EventManager &em)
                {
                    if (em.m_events.find(std::type_index(typeid(EventType))) == em.m_events.end())
                        return;
                    std::vector<EventType> &vec = std::any_cast<std::vector<EventType> &>(em.m_events[std::type_index(typeid(EventType))].listOfInstances);
                    vec.clear();
                }};
        }

    private:
        std::unordered_map<std::type_index, event_t> m_events;
    };
}
