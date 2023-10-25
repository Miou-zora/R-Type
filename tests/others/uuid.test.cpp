/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler
** File description:
** Uuid.test
*/

#include <gtest/gtest.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

TEST(uuid, basic_comparaison)
{
    boost::uuids::uuid uuid1 = boost::uuids::random_generator()();
    uint8_t uuid2[16] = {0};
    std::copy_n(uuid1.begin(), 16, uuid2);

    ASSERT_EQ(std::memcmp(uuid1.data, uuid2, sizeof(uuid2)), 0);
}

TEST(uuid, equal_comparison)
{
    boost::uuids::uuid uuid1 = boost::uuids::random_generator()();
    uint8_t uuid2[16] = {0};
    std::copy_n(uuid1.begin(), 16, uuid2);

    boost::uuids::uuid uuid3 = uuid1;
    uint8_t uuid4[16] = {0};
    std::copy_n(uuid3.begin(), 16, uuid4);

    ASSERT_EQ(std::memcmp(uuid2, uuid4, sizeof(uuid2)), 0);
}
