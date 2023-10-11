/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-rtype-lucas.hauszler [WSL : Ubuntu]
** File description:
** TextInput
*/

#pragma once

#include "ECS.hpp"
#include "Selectable.hpp"
#include "Text.hpp"
#include "TextInputable.hpp"
namespace raylib
{
#include <raylib.h>
}

namespace rtype::system
{
    class TextInput
    {
    public:
        TextInput() = default;
        ~TextInput() = default;

        void operator()(ecs::Registry &registry,
                        rtype::ecs::SparseArray<rtype::component::Selectable> &selectables,
                        rtype::ecs::SparseArray<rtype::component::TextInputable> &textInputs,
                        rtype::ecs::SparseArray<rtype::component::Text> &texts) const
        {
            int key = raylib::GetCharPressed();
            if (key < 0)
                return;
            for (auto &&[selectable, textInput, text] : rtype::ecs::containers::Zipper(selectables, textInputs, texts))
            {
                if (selectable->selected)
                {
                    while (key > 0 && textInput->maxLength > text->text.size())
                    {   
                        if ((key >= 32) && (key <= 125))
                            text->text += (char)key;
                        key = raylib::GetCharPressed();
                    }

                    if (raylib::IsKeyPressed(raylib::KEY_BACKSPACE) && text->text.size() > 0) {
                        if (raylib::IsKeyDown(raylib::KEY_LEFT_CONTROL) || raylib::IsKeyDown(raylib::KEY_RIGHT_CONTROL))
                            text->text = text->text.substr(0, 0);
                        else
                            text->text = text->text.substr(0, text->text.size() - 1);
                    }
                }
            }
        }
    };
}
