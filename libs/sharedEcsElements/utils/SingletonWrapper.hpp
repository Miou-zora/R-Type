/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Singleton
*/

#pragma once

namespace rtype::utils
{
    /**
     * @brief SingletonWrapper class. Use to create a singleton.
     * To use it, use the SingletonWrapper<T>::getInstance() method.
    */
    template <typename T>
    class SingletonWrapper
    {
    public:
        /**
         * @brief Get singleton instance of the given type through the singleton wrapper.
         *
         * @return T& The singleton instance.
        */
        static T &getInstance()
        {
            static T instance;
            return instance;
        }
    };
}
