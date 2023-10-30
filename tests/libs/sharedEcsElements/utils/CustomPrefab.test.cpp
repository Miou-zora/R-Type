/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** CustomPrefab.test
*/

#include "CustomPrefab.hpp"
#include <variant>

#include <gtest/gtest.h>

TEST(CustomPrefab, casualUse)
{
    using PREFAB = std::string;
    using CUSTOM_PREFAB = rtype::utils::CustomPrefab;
    struct TEST_COMPONENT { TEST_COMPONENT(int a): a(a) {}; int a; };

    rtype::utils::CustomPrefab cPrefab("test");
    std::vector<std::variant<CUSTOM_PREFAB, PREFAB>> prefabs;
    rtype::ecs::Registry reg;

    reg.registerComponent<TEST_COMPONENT>();

    // Prefab creation
    rtype::utils::PrefabManager::getInstance().createPrefab("test");
    rtype::utils::PrefabManager::getInstance().addComponent<TEST_COMPONENT>("test", 42);

    // Customization
    cPrefab.emplaceCustomComponent<TEST_COMPONENT>(21);

    prefabs.push_back("test");
    prefabs.push_back(cPrefab);

    // Instantiation using the variant
    for (std::size_t i = 0; i < 2; i++)
    {
        std::visit([&](auto&& arg)
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, PREFAB>)
                rtype::utils::PrefabManager::getInstance().instantiate(arg, reg);
            else
                arg.instantiate(reg);
        }, prefabs[i]);
    }

    ASSERT_EQ(reg.getComponents<TEST_COMPONENT>()[0].value().a, 42);
    ASSERT_EQ(reg.getComponents<TEST_COMPONENT>()[1].value().a, 21);
}
