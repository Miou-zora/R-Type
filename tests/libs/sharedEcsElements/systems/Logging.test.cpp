/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Logging.test
*/

#include "Logging.hpp"

#include <gtest/gtest.h>

TEST(Logging, init)
{
    rtype::system::Logging logging;
}

TEST(Logging, casual)
{
    rtype::ecs::Registry registry;
    rtype::ecs::SparseArray<rtype::component::Transform> transformables;
    rtype::system::Logging logging;

    transformables.insertAt(0, rtype::component::Transform(rtype::utils::Vector<float>(1, 2), 3, 4));
    transformables.insertAt(1, rtype::component::Transform(rtype::utils::Vector<float>(5, 6), 7, 8));

    testing::internal::CaptureStdout();

    logging(registry, transformables);

    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "Entity(0): position: (1, 2), scale: 3, rotation: 4\nEntity(1): position: (5, 6), scale: 7, rotation: 8\n";
    ASSERT_EQ(output, expectedOutput);
}
