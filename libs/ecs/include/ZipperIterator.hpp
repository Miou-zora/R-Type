/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** ZipperIterator
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
        class Zipper;
    }

    /**
     * @brief ZipperIterator is an iterator that iterate over multiple containers at the same time.
     * It is used by the Zipper container.
     *
     * @example
     * [](ecs::Registry &reg, ecs::SparseArray<Position> &pos, ecs::SparseArray<Velocity> &vel)
     * {
     *     for (auto &&[pos, vel] : ecs::containers::Zipper(pos, vel)) // ZipperIterator is used here by the intermediate of ecs::Zipper
     *     {
     *         pos.value().x += vel.value().x;
     *         pos.value().y += vel.value().y;
     *     }
     * }
     */
    template <class... Containers>
    class ZipperIterator
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
        using ValueType = std::tuple<ItReference<Containers> &...>;
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

        friend containers::Zipper<Containers...>;
        ZipperIterator(IteratorTuple const &itTuple, size_t max)
        {
            this->m_current = itTuple;
            this->m_max = max;
            this->m_idx = 0;
        }

    public:
        /**
         * @brief Copy constructor
         */
        ZipperIterator(ZipperIterator const &z)
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
        ZipperIterator &operator++()
        {
            if (m_idx < m_max)
            {
                incrAll(m_seq);
            }
            return (*this);
        }

        /**
         * @brief increment all iterators while they are not at the end or optional
         *
         * @return ZipperIterator& reference to the iterator
         */
        ZipperIterator operator++(int)
        {
            ZipperIterator tmp(*this);
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
            if (!allSet(m_seq))
            {
                incrAll(m_seq);
            }
            return (toValue(m_seq));
        }

        /**
         * @brief dereference the iterator
         *
         * @return ValueType the value of the iterator
         */
        ValueType operator->()
        {
            if (!allSet(m_seq))
            {
                incrAll(m_seq);
            }
            return (toValue(m_seq));
        }

        friend bool operator==(ZipperIterator const &lhs, ZipperIterator const &rhs)
        {
            return (std::tie(lhs.m_current) == std::tie(rhs.m_current));
        }

        friend bool operator!=(ZipperIterator const &lhs, ZipperIterator const &rhs)
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
            return (std::tie(*std::get<Is>(m_current)...));
        }

    private:
        IteratorTuple m_current;
        size_t m_max;
        size_t m_idx;
        static constexpr std::index_sequence_for<Containers...> m_seq{};
    };
}
