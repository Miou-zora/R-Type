/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** IndexedZipperIterator
*/

#pragma once

#include <iterator>
#include <tuple>
#include <utility>

namespace rtype::ecs
{
    namespace containers
    {
        template <class... Containers>
        class IndexedZipper;
    }

    /**
     * @brief IndexedZipperIterator is the same iterator as ZipperIterator but it also contains the index of the current value.
     *
     * @example
     * [](ecs::Registry &reg, ecs::SparseArray<Position> &pos, ecs::SparseArray<Velocity> &vel)
     * {
     *     for (auto &&[index, pos, vel] : ecs::containers::IndexedZipper(pos, vel)) // IndexedZipperIterator is used here by the intermediate of ecs::IndexedZipper
     *     {
     *         std::cout << "index: " << index;
     *         std::cout << "pos: " << pos.value().x << ", " << pos.value().y;
     *         std::cout << "vel: " << vel.value().x << ", " << vel.value().y;
     *     }
     * }
     */
    template <class... Containers>
    class IndexedZipperIterator
    {
        /**
         * @brief Iterator is the type of the iterator of the container
         */
        template <class Container>
        using Iterator = decltype(std::declval<Container>().begin());
        /**
         * @brief ItReference is the type of the reference of the iterator of the container
         */
        template <class Container>
        using ItReference = typename Iterator<Container>::reference;

    public:
        /**
         * @brief ValueType is the type of the value that the iterator is pointing to
         */
        using ValueType = std::tuple<size_t, ItReference<Containers> &...>;
        /**
         * @brief Reference is the type of the reference of the iterator
         */
        using Reference = ValueType;
        /**
         * @brief DifferenceType is the type of the difference between two iterators
         */
        using DifferenceType = size_t;
        /**
         * @brief IteratorCategory is the type of the category of the iterator
         */
        using IteratorCategory = std::input_iterator_tag;
        /**
         * @brief IteratorTuple is the type of the tuple of iterators
         */
        using IteratorTuple = std::tuple<Iterator<Containers>...>;
        // If we want IndexedZipperIterator to be built by zipper only .
        friend containers::IndexedZipper<Containers...>;
        IndexedZipperIterator(IteratorTuple const &itTuple, size_t max)
        {
            this->m_current = itTuple;
            this->m_max = max;
            this->m_idx = 0;
            if (m_idx < m_max && !allSet(m_seq))
            {
                incrAll(m_seq);
            }
        }

    public:
        /**
         * @brief Copy constructor
         */
        IndexedZipperIterator(IndexedZipperIterator const &z)
        {
            this->m_current = z.m_current;
            this->m_max = z.m_max;
            this->m_idx = z.m_idx;
        }

        /**
         * @brief increment all iterators while they are not at the end or optional
         *
         * @return ZipperIterator& reference to the iterator
         */
        IndexedZipperIterator &operator++()
        {
            incrAll(m_seq);
            return (*this);
        }

        /**
         * @brief increment all iterators while they are not at the end or optional
         *
         * @return ZipperIterator& reference to the iterator
         */
        IndexedZipperIterator operator++(int)
        {
            IndexedZipperIterator tmp(*this);
            incrAll(m_seq);
            return (tmp);
        }

        /**
         * @brief dereference the iterator
         *
         * @return ValueType the value of the iterator
         */
        ValueType operator*()
        {
            return (toValue(m_seq));
        }

        /**
         * @brief dereference the iterator
         *
         * @return ValueType the value of the iterator
         */
        ValueType operator->()
        {
            return (toValue(m_seq));
        }

        friend bool operator==(IndexedZipperIterator const &lhs, IndexedZipperIterator const &rhs)
        {
            return (std::tie(lhs.m_current) == std::tie(rhs.m_current));
        }

        friend bool operator!=(IndexedZipperIterator const &lhs, IndexedZipperIterator const &rhs)
        {
            return (!(lhs == rhs));
        }

    private:
        template <size_t... Is>
        void incrAll(std::index_sequence<Is...>)
        {
            do
            {
                (++std::get<Is>(m_current), ...);
                m_idx++;
            } while (m_idx < m_max && !allSet(m_seq));
        }

        template <size_t... Is>
        bool allSet(std::index_sequence<Is...>)
        {
            return ((std::get<Is>(m_current)->has_value() && ...));
        }

        template <size_t... Is>
        ValueType toValue(std::index_sequence<Is...>)
        {
            return (std::tie(m_idx, *std::get<Is>(m_current)...));
        }

    private:
        IteratorTuple m_current;
        size_t m_max;
        size_t m_idx;
        static constexpr std::index_sequence_for<Containers...> m_seq{};
    };
}
