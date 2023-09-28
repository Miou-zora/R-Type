# Entity Component System

ECS (Entity Component System) is a design pattern that is used to decouple data and logic from each other. It is a very popular pattern in game development, but can be used in other areas as well. In this case, ECS is used for the game engine.

## ECS

### Entity

Entity is just a unique identifier. It is used to identify a game object. It's a class that contains only an ID.

### Component

Component is a class that contains data. It is used to store data about a game object. For example, a position component would contain the position of the game object.

### System

System is a class that contains logic. It is used to manipulate data. For example, a movement system would move game objects based on their position.

## Exemple

```cpp
#include "registry.hpp"

namespace component {
    struct Position {
        Position(float _x, float _y) : x(_x), y(_y) {}
        float x;
        float y;
    };

    struct Velocity {
        Velocity(float _x, float _y) : x(_x), y(_y) {}
        float x;
        float y;
    };
}

namespace system {
    void movement_system(ecs::Registry &reg, ecs::SparseArray<Position> &pos, ecs::SparseArray<Velocity> &vel)
    {
        for (auto &&[pos, vel] : ecs::containers::Zipper(pos, vel))
        {
            pos.value().x += vel.value().x;
            pos.value().y += vel.value().y;
        }
    };
}

auto main(int ac, char **av) -> int
{
    (void)ac; (void)av;
    ecs::Registry reg;

    reg.addComponent<component::Position>();
    reg.addComponent<component::Velocity>();

    reg.addSystem<component::Position, component::Velocity>(system::movement_system);

    auto entity = reg.create_entity();
    reg.add_component<component::Position>(entity, {0.0f, 0.0f});
    reg.add_component<component::Velocity>(entity, {1.0f, 1.0f});

    reg.runSystem();

    return 0;
}
```

In this exemple, we create a registry, register two components (Position and Velocity) and a system (movement_system). Then we create an entity, add the two components to it and run the system. The system will move the entity by 1 on the x and y axis.
