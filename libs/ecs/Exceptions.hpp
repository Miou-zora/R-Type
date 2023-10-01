/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Exceptions
*/

#pragma once

#include <exception>
#include <stdexcept>
#include <optional>
#include <string>
#include <any>

namespace rtype::ecs
{
    /**
     * @brief BadOptionalAccess is an exception that is thrown when we try to access an optional that doesn't contain a value
    */
    class BadOptionalAccess: public std::bad_optional_access
    {
        public:
            BadOptionalAccess(const std::string &message): std::bad_optional_access(), m_message(message) {}
            ~BadOptionalAccess() = default;
            const char *what(void) const noexcept override
            {
                return m_message.c_str();
            }
        private:
            std::string m_message;
    };

    /**
     * @brief BadAnyCast is an exception that is thrown when we try to cast an any to a type that is not the one it contains
    */
    class BadAnyCast: public std::bad_any_cast
    {
        public:
            BadAnyCast(const std::string &message): std::bad_any_cast(), m_message(message) {}
            ~BadAnyCast() = default;
            const char *what(void) const noexcept override
            {
                return m_message.c_str();
            }
        private:
            std::string m_message;
    };

    /**
     * @brief OutOfRange is an exception that is thrown when we try to access an element of a container that is out of range
    */
    class OutOfRange: public std::out_of_range
    {
        public:
            OutOfRange(const std::string &message): std::out_of_range(message), m_message(message) {}
            ~OutOfRange() = default;
            const char *what(void) const noexcept override
            {
                return m_message.c_str();
            }
        private:
            std::string m_message;
    };
}
