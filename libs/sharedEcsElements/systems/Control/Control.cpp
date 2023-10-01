/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** Control
*/

#include "Control.hpp"
#include "Zipper.hpp"
#include "Vector.hpp"

void rtype::system::Control::operator()(ecs::Registry &registry,
                                 ecs::SparseArray<rtype::component::Controllable> const &controllables,
                                 ecs::SparseArray<rtype::component::Velocity> &velocities)
{
    for (auto &&[controllable, velocity] : ecs::containers::Zipper(controllables, velocities))
    {
        rtype::utils::Vector<float> direction((controllable.value().is_key_right_pressed() - controllable.value().is_key_left_pressed()), (controllable.value().is_key_down_pressed() - controllable.value().is_key_up_pressed()));
        if (direction.getLength() != 0)
            velocity.value().vector = direction.normalized() * registry.getDeltaTime();
        else
            velocity.value().vector = rtype::utils::Vector<float>(0, 0);
    }
}
