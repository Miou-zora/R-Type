/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** test
*/

#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>
#include "Exceptions.hpp"

namespace ecs
{
    /**
     * @brief SparseArray is a container that store a list of optional components.
     * It resize itself when a component is added at a position greater than its size.
     * In the case we get a component of an entity that doesn't have it, it return a std::nullopt, otherwise it return the std::optional<Component>.
     *
     * @tparam Component Component type to store
     * @tparam Allocator Allocator type to use
    */
    template <typename Component, typename Allocator = std::allocator<std::optional<Component>>>
    class SparseArray
    {
    public:
        /**
         * @brief Type of the value stored in the container
        */
        using ValueType = std::optional<Component>;
        /**
         * @brief Type of the reference to the value stored in the container
        */
        using ReferenceType = ValueType &;
        /**
         * @brief Type of the const reference to the value stored in the container
        */
        using ConstReferenceType = ValueType const &;
        /**
         * @brief Type of the container
        */
        using Container = std::vector<ValueType, Allocator>;
        /**
         * @brief Type of the size of the container
        */
        using SizeType = typename Container::size_type;
        /**
         * @brief Type of the iterator of the container
        */
        using Iterator = typename Container::iterator;
        /**
         * @brief Type of the const iterator of the container
        */
        using ConstIterator = typename Container::const_iterator;

    public:
        /**
         * @brief Construct a new SparseArray object
        */
        SparseArray() = default;

        /**
         * @brief Copy constructor of SparseArray
        */
        SparseArray(SparseArray const &other)
        {
            m_data = other.m_data;
        }

        /**
         * @brief Move constructor of SparseArray
        */
        SparseArray(SparseArray &&other) noexcept
        {
            m_data = std::move(other.m_data);
        }

        /**
         * @brief Destroy the SparseArray object
        */
        ~SparseArray() = default;

        /**
         * @brief Copy assignment operator of SparseArray
        */
        SparseArray &operator=(SparseArray const &other)
        {
            m_data = other.m_data;
        }

        /**
         * @brief Move assignment operator of SparseArray
        */
        SparseArray &operator=(SparseArray &&other) noexcept
        {
            m_data = std::move(other.m_data);
        }

        /**
         * @brief Get the ReferenceType of an entity
         *
         * @param idx Index of the entity
         * @return ReferenceType Component of the entity
        */
        ReferenceType operator[](size_t idx)
        {
            if (idx >= m_data.size())
                throw ecs::OutOfRange("SparseArray::operator[]");
            return (m_data[idx]);
        }

        /**
         * @brief Get the ConstReferenceType of an entity
         *
         * @param idx Index of the entity
         * @return ConstReferenceType Component of the entity
        */
        ConstReferenceType operator[](size_t idx) const
        {
            if (idx >= m_data.size())
                throw ecs::OutOfRange("SparseArray::operator[]");
            return (m_data[idx]);
        }

        /**
         * @brief Get the begin iterator of the container
         *
         * @return Iterator begin iterator of the container
        */
        Iterator begin()
        {
            return (m_data.begin());
        }

        /**
         * @brief Get the begin iterator of the container
         *
         * @return ConstIterator begin iterator of the container
        */
        ConstIterator begin() const
        {
            return (m_data.begin());
        }

        /**
         * @brief Get the cbegin iterator of the container
         *
         * @return ConstIterator cbegin iterator of the container
        */
        ConstIterator cbegin() const
        {
            return (m_data.cbegin());
        }

        /**
         * @brief Get the end iterator of the container
         *
         * @return Iterator end iterator of the container
        */
        Iterator end()
        {
            return (m_data.end());
        }

        /**
         * @brief Get the end iterator of the container
         *
         * @return ConstIterator end iterator of the container
        */
        ConstIterator end() const
        {
            return (m_data.end());
        }

        /**
         * @brief Get the cend iterator of the container
         *
         * @return ConstIterator cend iterator of the container
        */
        ConstIterator cend() const
        {
            return (m_data.cend());
        }

        /**
         * @brief Get the size of the container
         *
         * @return SizeType size of the container
        */
        SizeType size() const
        {
            return (m_data.size());
        }

        /**
         * @brief It should insert the component at a specific index, erasing the old value and resizing the vector if needed.
         *
         * @param pos Index of the component
         * @param other Component to insert
        */
        ReferenceType insertAt(SizeType pos, Component const &other)
        {
            Allocator alloc = m_data.get_allocator();

            if (m_data.size() <= pos)
            {
                m_data.resize(pos + 1);
            }
            std::allocator_traits<Allocator>::destroy(alloc, std::addressof(m_data[pos]));
            m_data[pos] = other;
            return (m_data[pos]);
        }

        /**
         * @brief It should insert the component at a specific index, erasing the old value and resizing the vector if needed.
         *
         * @param pos Index of the component
         * @param other Component to insert
        */
        ReferenceType insertAt(SizeType pos, Component &&other)
        {
            Allocator alloc = m_data.get_allocator();

            if (m_data.size() <= pos)
            {
                m_data.resize(pos + 1);
            }
            std::allocator_traits<Allocator>::destroy(alloc, std::addressof(m_data[pos]));
            m_data[pos] = std::move(other);
            return (m_data[pos]);
        }

        /**
         * @brief Same as insert_at, but the component is built in-place, or std::move’d into the container.
         *
         * @param pos Index of the component
         * @param other... parameters to forward to the constructor of the component (in this case, don't forget to add std::in_place for std::optional)
        */
        template <class... Params>
        ReferenceType emplaceAt(SizeType pos, Params &&...other)
        {
            Allocator alloc = m_data.get_allocator();

            if (m_data.size() <= pos)
            {
                m_data.resize(pos + 1);
            }
            std::allocator_traits<Allocator>::destroy(alloc, std::addressof(m_data[pos]));
            std::allocator_traits<Allocator>::construct(alloc, std::addressof(m_data[pos]), std::forward<Params>(other)...);
            return (m_data[pos]);
        }

        /**
         * @brief Erase a value at a specified index
         *
         * @param pos Index of the value to erase
         * @throw ecs::OutOfRange if the index is greater than the size of the container
        */
        void erase(SizeType pos)
        {
            Allocator alloc = m_data.get_allocator();

            if (m_data.size() <= pos)
                throw ecs::OutOfRange("SparseArray::erase");
            std::allocator_traits<Allocator>::destroy(alloc, std::addressof(m_data[pos]));
            m_data[pos] = std::nullopt;
        }

        /**
         * @brief Get the index of a value
         *
         * @param other Value to get the index
         * @return SizeType Index of the value, or the size of the container if the value is not in the container
        */
        SizeType getIndex(ValueType const &other) const
        {
            for (SizeType i = 0; i < m_data.size(); i++)
            {
                if (std::addressof(m_data[i]) == std::addressof(other))
                {
                    return (i);
                }
            }
            return (m_data.size());
        }

    private:
        Container m_data;
    };
}
