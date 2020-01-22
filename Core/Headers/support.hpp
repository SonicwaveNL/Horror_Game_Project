#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <SFML/Graphics.hpp>
///@file

///\brief
/// Enum class that contains input types.
enum class inputType { keyboard, controller };

enum class objectType {
    Abstract,
    GridCell,
    Floor,
    Wall,
    Switch,
    Door,
    Player,
    Monster
};

///\brief
/// Enum class that contains keywords representing actions.
enum class actionKeyword {
    escape,
    select,
    left,
    up,
    right,
    down,
    // Reserved action keywords, usage depends on game state.
    action1,
    action2,
    action3,
    action4
};

#endif