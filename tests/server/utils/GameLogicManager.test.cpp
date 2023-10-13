#include <boost/asio.hpp>

#include "NetworkPlayer.hpp"
#include "GameLogicManager.hpp"

#include <gtest/gtest.h>

TEST(GameLogicManager, getInstance)
{
    auto &gameLogicManager = rtype::utils::GameLogicManager::getInstance();

    ASSERT_EQ(&gameLogicManager, &rtype::utils::GameLogicManager::getInstance());
}

TEST(GameLogicManager, addValue)
{
    rtype::utils::GameLogicManager& gameLogicManager = rtype::utils::GameLogicManager::getInstance();

    gameLogicManager.addValue<int>("testValue", 42);
    ASSERT_EQ(gameLogicManager.getValue<int>("testValue"), 42);
}

TEST(GameLogicManager, addFloat)
{
    rtype::utils::GameLogicManager& gameLogicManager = rtype::utils::GameLogicManager::getInstance();

    gameLogicManager.addValue<float>("testValue", 42.42f);
    ASSERT_EQ(gameLogicManager.getValue<float>("testValue"), 42.42f);
}
