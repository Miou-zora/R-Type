/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** IndexedZipper
*/

#pragma once

#include "IndexedZipperIterator.hpp"
#include <algorithm>

namespace rtype::ecs
{
    namespace containers
    {
        /**
         * @brief IndexedZipper is a container that allow to iterate over multiple containers at the same time.
         *
         * @example
         * [](ecs::Registry &reg, ecs::SparseArray<Position> &pos, ecs::SparseArray<Velocity> &vel)
         * {
         *     for (auto &&[index, pos, vel] : ecs::containers::IndexedZipper(pos, vel))
         *     {
         *         std::cout << "index: " << index;
         *         std::cout << "pos: " << pos.value().x << ", " << pos.value().y;
         *         std::cout << "vel: " << vel.value().x << ", " << vel.value().y;
         *     }
         * }
         */
        template <class... Containers>
        class IndexedZipper
        {
        public:
            /**
             * @brief Iterator is the type of the iterator of the container
             */
            using Iterator = ecs::IndexedZipperIterator<Containers...>;
            /**
             * @brief IteratorTuple is the type of the tuple of iterators of the container
             */
            using IteratorTuple = typename Iterator::IteratorTuple;

            /**
             * @brief Construct a new IndexedZipper object
             */
            IndexedZipper(Containers &...cs)
            {
                m_begin = IteratorTuple(cs.begin()...);
                m_end = _computeEnd(cs...);
                m_size = _computeSize(cs...);
            }

            /**
             * @brief get the begin iterator of the container
             */
            Iterator begin()
            {
                return (Iterator(m_begin, m_size));
            }

            /**
             * @brief get the end iterator of the container
             */
            Iterator end()
            {
                return (Iterator(m_end, 0));
            }

        private:
            // helper function to know the maximum index of our Iterators .
            static size_t _computeSize(Containers &...containers)
            {
                return (std::min({containers.size()...}));
            }

            // helper function to compute an IteratorTuple that will allow us to build our end Iterator.
            static IteratorTuple _computeEnd(Containers &...containers)
            {
                size_t size = _computeSize(containers...);
                return (IteratorTuple((containers.begin() + size)...));
            }

        private:
            IteratorTuple m_begin;
            IteratorTuple m_end;
            size_t m_size;
        };
    }
}
