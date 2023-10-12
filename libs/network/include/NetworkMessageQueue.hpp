/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** NetworkMessageQueue
*/

#pragma once

#include <vector>
#include <queue>
#include <mutex>

#include "NetworkMessage.hpp"

namespace rtype::network {
    namespace message {
        // comparator for priority queue _Compare
        struct NetworkMessageHeaderCompare {
            bool operator()(const NetworkMessageHeader &lhs, const NetworkMessageHeader &rhs) const
            {
                return (lhs.id > rhs.id);
            }

            bool operator()(const NetworkMessageHeader &lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(lhs, *header));
            }

            bool operator()(const char *lhs, const NetworkMessageHeader &rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                return (this->operator()(*header, rhs));
            }

            bool operator()(const char *lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(*header_lhs, *header_rhs));
            }

            bool operator()(const boost::array<char, MAX_PACKET_SIZE> &lhs, const boost::array<char, MAX_PACKET_SIZE> &rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs.data());
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs.data());
                return (this->operator()(*header_lhs, *header_rhs));
            }
        };

        struct NetworkMessageHeaderEquality {
            bool operator()(const NetworkMessageHeader &lhs, const NetworkMessageHeader &rhs) const
            {
                return (lhs.id == rhs.id);
            }

            bool operator()(const NetworkMessageHeader &lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(lhs, *header));
            }

            bool operator()(const char *lhs, const NetworkMessageHeader &rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                return (this->operator()(*header, rhs));
            }

            bool operator()(const char *lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(*header_lhs, *header_rhs));
            }

            bool operator()(const boost::array<char, MAX_PACKET_SIZE> &lhs, const boost::array<char, MAX_PACKET_SIZE> &rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs.data());
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs.data());
                return (this->operator()(*header_lhs, *header_rhs));
            }
        };

        /**
         * @brief UniqueVector is a vector that can only contain unique elements, according to a templated comparator that checks for equality.
         * It is a SequenceContainer and behaves exactly like a std::vector, except that it can only contain unique elements.
         * @tparam T the type of the elements
         * @tparam Compare the comparator that checks for equality
         */
        template<typename T, typename Compare = std::equal_to<T>>
        class UniqueVector : public std::vector<T> {
        public:
            using std::vector<T>::vector;

            /**
             * @brief push_back adds an element to the vector if it is not already present
             * @param value the element to add
             */
            void push_back(const T &value)
            {
                if (std::find_if(this->begin(), this->end(), [&](const T &elem) { return Compare()(elem, value); }) == this->end())
                    std::vector<T>::push_back(value);
            }
        };

        /**
         * @brief NetworkMessageQueue is a priority queue that can contain messages as boost arrays.
         */
        template<typename Message = boost::array<char, MAX_PACKET_SIZE>, typename EqCompare = NetworkMessageHeaderEquality, typename LessCompare = NetworkMessageHeaderCompare>
        class NetworkMessageQueue {
        public:
            /**
             * @brief push adds a message to the queue
             * @param msg the message to add
             */
            void push(const Message &msg)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_queue.push(msg);
            }

            /**
             * @brief pop removes the first message from the queue
             */
            void pop()
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_queue.pop();
            }

            /**
             * @brief top returns the first message from the queue
             * @return the first message from the queue
             */
            const Message &top() const
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                return (m_queue.top());
            }

            /**
             * @brief size returns the size of the queue
             * @return the size of the queue
             */
            std::size_t size() const
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                return (m_queue.size());
            }

            /**
             * @brief empty checks if the queue is empty
             * @return true if the queue is empty, false otherwise
             */
            bool empty() const
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                return (m_queue.empty());
            }

            /**
             * @brief clear clears the queue
             */
            void clear()
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                while (!m_queue.empty())
                    m_queue.pop();
            }
        private:
            std::priority_queue<Message, UniqueVector<Message, EqCompare>, LessCompare> m_queue;
            mutable std::mutex m_mutex;
        };
    }
}
