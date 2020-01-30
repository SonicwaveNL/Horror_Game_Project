#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

//Defines the size of the tiles in the game.
#define PIXEL16 16

///@file
///\brief
/// inputType contains the types of input a user can use (for now only keyboard is implented).
enum class inputType { keyboard, controller };

///\brief
///gameState contains the states in which the game can be.
enum class gameState { Menu, SelectMap, Play, Editor, Quit, WinState, LoseState, Store };

///\brief
///objectType contaings the various types of objects a cell can have.
enum class objectType : size_t {
    Wall,
    Floor,
    Door,
    Switch,
    Player,
    Monster,
    Abstract,
    UIElement,
    GridCell,
    Powerup
};

///\brief
/*actionKeyword contains the various actions a user can take but not explicitly which actual keyboard key or controller button is needed for the action.
    This creates a layer of abstraction.*/
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

///\brief
///BuffType contains the types of buffs a player can have.
enum class BuffType : int{
    PlayerSpeed = 1,
    EnemySpeed = 2
};
#endif